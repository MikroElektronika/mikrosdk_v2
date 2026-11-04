/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_tim.c
 * @brief TIM HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_tim.h"
#include "hal_ll_tim_pin_map.h"
#include "hal_ll_per.h"
#include "hal_ll_pior_defines.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((volatile hal_ll_tim_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

/*!< @brief Volatile register accessors, the bit control macros don't add volatile themselves. */
#define hal_ll_tim_reg8(_addr)          ( ( volatile uint8_t * )( _addr ) )
#define hal_ll_tim_reg16(_addr)         ( ( volatile uint16_t * )( _addr ) )

/*!< @brief CPU/peripheral clock (fCLK) feeding the TAU prescaler. */
#define HAL_LL_TIM_FCLK_HZ              ( ( uint32_t )Get_Fosc_kHz() * 1000UL )

/*!< @brief Register addresses outside of the TAU register block. */
#define HAL_LL_TIM_PER0_ADDR            ( 0xF00F0UL )
#define HAL_LL_TIM_PRR0_ADDR            ( 0xF00F1UL )

/*!< @brief TIMx uses master channel 2x and slave channel 2x + 1, output TO0(2x+1). */
#define hal_ll_tim_master_channel(_index)   ( ( _index ) << 1 )
#define hal_ll_tim_slave_channel(_index)    ( hal_ll_tim_master_channel( _index ) + 1 )
#define hal_ll_tim_channels(_index)         ( 3U << hal_ll_tim_master_channel( _index ) )
/*!< @brief Master TDR (TDR00/02/04/06) sits right below the slave TDR. */
#define hal_ll_tim_master_tdr(_base)        ( ( _base ) - 2 )
/*!< @brief TIM0/TIM2 use CK00, TIM1/TIM3 use CK01. */
#define hal_ll_tim_cks(_index)              ( ( _index ) & 1 )
/*!< @brief Channels of all modules sharing the prescaler of the given module. */
#define hal_ll_tim_cks_channels(_index)     ( hal_ll_tim_cks( _index ) ? 0xCCU : 0x33U )

/*!< @brief TMRmn bits. */
#define HAL_LL_TIM_TMR_CKS_CK1          ( 0x8000U ) // CKSmn1:0 = 10, CKm1. 00 selects CKm0.
#define HAL_LL_TIM_TMR_MASTER           ( 0x0800U ) // Only on channels 2, 4 and 6, channel 0 is always a master.
#define HAL_LL_TIM_TMR_STS_MASTER_INT   ( 0x0400U ) // Start on INTTMmn of the master channel.
#define HAL_LL_TIM_TMR_MD_INTERVAL_INT  ( 0x0001U ) // Interval timer, INTTMmn generated at count start.
#define HAL_LL_TIM_TMR_MD_ONE_COUNT_RT  ( 0x0009U ) // One-count, start trigger valid during counting.

/*!< @brief TPSm prescaler fields. */
#define HAL_LL_TIM_PRS_MAX              ( 15 )
#define HAL_LL_TIM_PRS_MASK             ( 0x0FU )
#define HAL_LL_TIM_PERIOD_MAX           ( 0x10000UL )

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TAU0 register block, TMR00 (F0190H) up to TOM0. */
typedef struct
{
    uint16_t tmr[8];    /*!< 0x00 TMR0n - mode. */
    uint16_t tsr[8];    /*!< 0x10 TSR0n - status. */
    uint16_t te;        /*!< 0x20 TE0   - channel enable status. */
    uint16_t ts;        /*!< 0x22 TS0   - channel start trigger. */
    uint16_t tt;        /*!< 0x24 TT0   - channel stop trigger. */
    uint16_t tps;       /*!< 0x26 TPS0  - prescaler select. */
    uint16_t to;        /*!< 0x28 TO0   - output level. */
    uint16_t toe;       /*!< 0x2A TOE0  - output enable. */
    uint16_t tol;       /*!< 0x2C TOL0  - output level inversion. */
    uint16_t tom;       /*!< 0x2E TOM0  - output mode. */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    hal_ll_base_addr_t       base;          /*!< TDR of the slave channel, identifies the module. */
    hal_ll_tim_t             config;
    uint32_t                 max_period;    /*!< Counts per PWM period, TDR of the master channel + 1. */
    uint32_t                 freq_hz;
    hal_ll_pin_name_t        module_index;
    uint8_t                  pior_reg;
    uint8_t                  pior_shift;
    uint8_t                  pior_width;
    float                    duty_ratio;
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hw specific error values */
typedef enum
{
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM hardware specific info, PIOR fields. */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] =
{
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, 0}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0), 0, 2, 3, 0},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, 0}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1), 1, 0, 3, 0},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, 0}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2), 1, 5, 3, 0},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, 0}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3), 2, 2, 2, 0},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0}, 0, 0, HAL_LL_PIN_NC, 0, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Initializes a TIM module at the hardware level.
  *
  * Configures the selected module according to its previously set configuration.
  * Enables the module in the MCU, sets appropriate pin alternate functions,
  * and initializes the module clock and period.
  *
  * @param  map: Pointer to the hardware-specific module configuration structure.
  * @return uint32_t: Counts per PWM period.
  */
static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Enable TAU0 clock.
  *
  * The clock is only stopped if no TAU0 channel is running,
  * since all TIM modules share the unit.
  *
  * @param  map - Object specific context handler.
  * @param  hal_ll_state - True(enable clock)/False(disable clock).
  * @return None
  */
static void hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_tim_hw_specifics_map array index.
  *
  * @param  handle - Object specific context handler.
  * @return hal_ll_tim_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Check if pin is adequate.
  *
  * Checks tim pin the user has passed with pre-defined
  * pin in tim map.
  *
  * @param  pin - TIM pre-defined pin name.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                               hal_ll_tim_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin name and PIOR value for
 * TIM pin.
 *
 * @param[in]  module_index TIM HW module index -- 0,1,2...
 * @param[in]  index  TIM map index value
 *
 * @return  None
 */
static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief  Sets TIM pin alternate function state.
  *
  * Routes TO0p through PIOR0/PIOR1/PIOR2 and sets the pin
  * as an output with a low latch, since the pin outputs
  * the latch ORed with the timer output.
  *
  * @param  map - Object specific context handler.
  * @param  hal_ll_state - Init/De-init
  * @return none
  */
static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map,
                                                      bool hal_ll_state );

/**
  * @brief  Calculate TIM period.
  *
  * Calculates the TPS0 prescaler and the number of counts per
  * PWM period. If another module sharing the prescaler is running,
  * its prescaler is kept and only the period is calculated.
  *
  * @param[in]  map - Object specific context handler.
  * @param[out] prs - Prescaler value for TPS0.
  * @return uint32_t - Counts per PWM period.
  */
static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map, uint8_t *prs );

/**
  * @brief  Calculate slave channel compare value.
  *
  * @param[in] map - Object specific context handler.
  * @return uint16_t - TDR value of the slave channel.
  */
static uint16_t hal_ll_tim_duty_count( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * PWM function procedure.
  * The master channel runs in interval timer mode and sets the
  * period, the slave channel runs in one-count mode, is started
  * by the master and sets the duty.
  *
  * @param  map - Object specific context handler.
  * @return uint32_t - Counts per PWM period.
  */
static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Stop both channels of the module.
  *
  * Leaves the TO0p output at the inactive (low) level.
  *
  * @param  map - Object specific context handler.
  * @return none
  */
static void hal_ll_tim_stop_channels( hal_ll_tim_hw_specifics_map_t *map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {

    uint8_t index;
    uint16_t pin_check_result;

    if ( ( pin_check_result = hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( hal_ll_tim_hw_specifics_map[ pin_check_result].config.pin != pin ) {
        hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );

        hal_ll_tim_map_pin( pin_check_result, index );

        hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;

        hal_ll_module_state[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle =
                        ( handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle =
                        ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_handle_register_t *hal_handle = (hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle =
                         (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    volatile hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( HAL_LL_TAU0_BASE_ADDR );
    uint8_t module_index = hal_ll_tim_hw_specifics_map_local->module_index;
    bool running;

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    // TMR0n can't be rewritten while counting, so the channels are stopped and restarted.
    running = read_reg( &hal_ll_hw_reg->te ) & hal_ll_tim_channels( module_index );

    hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    if ( running ) {
        write_reg( &hal_ll_hw_reg->ts, hal_ll_tim_channels( module_index ) );
    }

    low_level_handle->init_ll_state = true;

    return hal_ll_tim_hw_specifics_map_local->max_period;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    hal_ll_tim_hw_specifics_map_local->duty_ratio = duty_ratio;

    // TDR0p may be changed at any time, it is loaded on the next INTTM0n of the master channel.
    write_reg( hal_ll_tim_reg16( hal_ll_tim_hw_specifics_map_local->base ),
               hal_ll_tim_duty_count( hal_ll_tim_hw_specifics_map_local ) );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    volatile hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( HAL_LL_TAU0_BASE_ADDR );
    uint8_t module_index = hal_ll_tim_hw_specifics_map_local->module_index;

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    set_reg_bit( &hal_ll_hw_reg->toe, hal_ll_tim_slave_channel( module_index ) );

    // Master and slave must be started at the same time.
    write_reg( &hal_ll_hw_reg->ts, hal_ll_tim_channels( module_index ) );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    hal_ll_tim_stop_channels( hal_ll_tim_hw_specifics_map_local );

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);

    if( low_level_handle->hal_ll_tim_handle != NULL ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;
        hal_ll_tim_hw_specifics_map_local->duty_ratio = 0;

        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, true );
        hal_ll_tim_stop_channels( hal_ll_tim_hw_specifics_map_local );
        hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index,
                                                hal_ll_tim_handle_register_t *handle_map ) {
    hal_ll_pin_name_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    uint16_t map_size = ( sizeof( hal_ll_tim_pin_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( hal_ll_tim_pin_map[ pin_num ].pin == pin ) {
            hal_ll_module_id = hal_ll_tim_pin_map[ pin_num ].module_index;

            for ( uint8_t map_member = 0; map_member < TIM_MODULE_COUNT + 1; map_member++  ) {
                if ( hal_ll_tim_hw_specifics_map[map_member].module_index ==  hal_ll_module_id ) {
                    hal_ll_module_id = map_member;
                    break;
                }
            }

            if ( NULL == handle_map[hal_ll_module_id].hal_drv_tim_handle ) {
                *index = pin_num;
                return hal_ll_module_id;
            } else if ( TIM_MODULE_COUNT == ++index_counter ) {
                return --index_counter;
            }
        }
    }
    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {

    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );

    while( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base ) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_tim_module_enable ( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    volatile hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( HAL_LL_TAU0_BASE_ADDR );

    if ( hal_ll_state ) {
        // TAU0RES shares the PER0 bit position in PRR0.
        clear_reg_bit( hal_ll_tim_reg8( HAL_LL_TIM_PRR0_ADDR ), PER0_TAU0EN_POS );
        set_reg_bit( hal_ll_tim_reg8( HAL_LL_TIM_PER0_ADDR ), PER0_TAU0EN_POS );
    } else if ( !read_reg( &hal_ll_hw_reg->te ) ) {
        // All TIM modules share TAU0, keep the clock while any channel runs.
        clear_reg_bit( hal_ll_tim_reg8( HAL_LL_TIM_PER0_ADDR ), PER0_TAU0EN_POS );
    }
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( map->config.pin != HAL_LL_PIN_NC ) {
        if ( hal_ll_state ) {
            hal_ll_pior_set_field( map->pior_reg, map->pior_shift, map->pior_width, map->config.af );
        }

        module.pins[0] = map->config.pin;
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        // Digital output configuration clears the port latch, TO0p needs it low.
        module.configs[0] = GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map, uint8_t *prs ) {
    volatile hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( HAL_LL_TAU0_BASE_ADDR );
    uint8_t cks_shift = hal_ll_tim_cks( map->module_index ) << 2;
    uint32_t freq_hz = map->freq_hz ? map->freq_hz : 1;
    uint32_t period = 1;
    bool prs_locked;

    // TPS0 CK0k bits must not change while a channel using CK0k runs, use its setting then.
    prs_locked = ( read_reg( &hal_ll_hw_reg->te ) & hal_ll_tim_cks_channels( map->module_index ) &
                   ~hal_ll_tim_channels( map->module_index ) );
    *prs = prs_locked ? ( ( read_reg( &hal_ll_hw_reg->tps ) >> cks_shift ) & HAL_LL_TIM_PRS_MASK ) : 0;

    // The lowest prescaler that fits keeps the most duty resolution.
    for ( ; *prs <= HAL_LL_TIM_PRS_MAX; ( *prs )++ ) {
        period = ( ( HAL_LL_TIM_FCLK_HZ >> *prs ) + ( freq_hz / 2 ) ) / freq_hz;

        if ( ( period <= HAL_LL_TIM_PERIOD_MAX ) || prs_locked ) {
            break;
        }
    }

    // Requested frequency is below the slowest setting, use the slowest one.
    if ( *prs > HAL_LL_TIM_PRS_MAX ) {
        *prs = HAL_LL_TIM_PRS_MAX;
    }
    if ( period > HAL_LL_TIM_PERIOD_MAX ) {
        period = HAL_LL_TIM_PERIOD_MAX;
    } else if ( !period ) {
        period = 1;
    }

    return period;
}

static uint16_t hal_ll_tim_duty_count( hal_ll_tim_hw_specifics_map_t *map ) {
    // 0% output: TDR0p = 0, 100% output: TDR0p >= TDR0n + 1.
    uint32_t count = ( uint32_t )( map->duty_ratio * ( float )map->max_period + 0.5f );

    if ( count > 0xFFFFUL ) {
        count = 0xFFFFUL;
    }

    return ( uint16_t )count;
}

static void hal_ll_tim_stop_channels( hal_ll_tim_hw_specifics_map_t *map ) {
    volatile hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( HAL_LL_TAU0_BASE_ADDR );
    uint8_t slave = hal_ll_tim_slave_channel( map->module_index );

    // Master and slave must be stopped at the same time, TT0 is a trigger register.
    write_reg( &hal_ll_hw_reg->tt, hal_ll_tim_channels( map->module_index ) );

    // TO0p keeps its last level after stopping, force it inactive.
    clear_reg_bit( &hal_ll_hw_reg->toe, slave );
    clear_reg_bit( &hal_ll_hw_reg->to, slave );
}

static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    volatile hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( HAL_LL_TAU0_BASE_ADDR );
    uint8_t master = hal_ll_tim_master_channel( map->module_index );
    uint8_t slave = hal_ll_tim_slave_channel( map->module_index );
    uint8_t cks_shift = hal_ll_tim_cks( map->module_index ) << 2;
    uint16_t cks = hal_ll_tim_cks( map->module_index ) ? HAL_LL_TIM_TMR_CKS_CK1 : 0;
    uint16_t master_mode = cks | HAL_LL_TIM_TMR_MD_INTERVAL_INT;
    uint8_t prs;

    // TMR0n may only be written while TE0n = 0.
    hal_ll_tim_stop_channels( map );

    map->max_period = hal_ll_tim_set_freq_bare_metal( map, &prs );

    // Only this module's own CK00/CK01 nibble, left alone if another module already set it.
    if ( ( ( read_reg( &hal_ll_hw_reg->tps ) >> cks_shift ) & HAL_LL_TIM_PRS_MASK ) != prs ) {
        clear_reg_bits( &hal_ll_hw_reg->tps, ( uint16_t )( HAL_LL_TIM_PRS_MASK << cks_shift ) );
        set_reg_bits( &hal_ll_hw_reg->tps, ( uint16_t )( prs << cks_shift ) );
    }

    // Channel 0 has no MASTER bit, it is always a master.
    if ( master ) {
        master_mode |= HAL_LL_TIM_TMR_MASTER;
    }
    write_reg( &hal_ll_hw_reg->tmr[ master ], master_mode );
    // Slave uses the same clock as the master, 16-bit mode (SPLIT = 0 on channels 1 and 3).
    write_reg( &hal_ll_hw_reg->tmr[ slave ], cks | HAL_LL_TIM_TMR_STS_MASTER_INT | HAL_LL_TIM_TMR_MD_ONE_COUNT_RT );

    // Period = (TDR0n + 1) counts, duty = TDR0p counts.
    write_reg( hal_ll_tim_reg16( hal_ll_tim_master_tdr( map->base ) ), ( uint16_t )( map->max_period - 1 ) );
    write_reg( hal_ll_tim_reg16( map->base ), hal_ll_tim_duty_count( map ) );

    // Master output unused, slave in slave channel output mode, active high, starting low.
    clear_reg_bit( &hal_ll_hw_reg->tom, master );
    clear_reg_bit( &hal_ll_hw_reg->tol, master );
    clear_reg_bit( &hal_ll_hw_reg->toe, master );
    set_reg_bit( &hal_ll_hw_reg->tom, slave );
    clear_reg_bit( &hal_ll_hw_reg->tol, slave );
    clear_reg_bit( &hal_ll_hw_reg->to, slave );
    set_reg_bit( &hal_ll_hw_reg->toe, slave );

    return map->max_period;
}

static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    hal_ll_tim_module_enable( map, true );
    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
