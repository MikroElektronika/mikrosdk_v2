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
#include "hal_ll_pclkdis.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS

// MAX32690 TMR RevB register bit definitions.
#define HAL_LL_TIM_CTRL0_MODE_A_MASK              (0xFUL << 0)
#define HAL_LL_TIM_CTRL0_MODE_A_PWM               (0x3UL << 0)
#define HAL_LL_TIM_CTRL0_CLKDIV_A_MASK            (0xFUL << 4)
#define HAL_LL_TIM_CTRL0_CLKDIV_A_POS             (4U)
#define HAL_LL_TIM_CTRL0_POL_A                    (1UL << 8)
#define HAL_LL_TIM_CTRL0_PWMSYNC_A                (1UL << 9)
#define HAL_LL_TIM_CTRL0_CLKEN_A                  (1UL << 14)
#define HAL_LL_TIM_CTRL0_EN_A                     (1UL << 15)
#define HAL_LL_TIM_CTRL0_MODE_B_MASK              (0xFUL << 16)
#define HAL_LL_TIM_CTRL0_MODE_B_PWM               (0x3UL << 16)
#define HAL_LL_TIM_CTRL0_CLKDIV_B_MASK            (0xFUL << 20)
#define HAL_LL_TIM_CTRL0_CLKDIV_B_POS             (20U)
#define HAL_LL_TIM_CTRL0_CLKEN_B                  (1UL << 30)
#define HAL_LL_TIM_CTRL0_EN_B                     (1UL << 31)

#define HAL_LL_TIM_CTRL1_CLKSEL_A_MASK            (0x3UL << 0)
#define HAL_LL_TIM_CTRL1_CLKEN_A                  (1UL << 2)
#define HAL_LL_TIM_CTRL1_CLKRDY_A                 (1UL << 3)
#define HAL_LL_TIM_CTRL1_OUTEN_A                  (1UL << 13)
#define HAL_LL_TIM_CTRL1_OUTBEN_A                 (1UL << 14)
#define HAL_LL_TIM_CTRL1_CLKSEL_B_MASK            (0x3UL << 16)
#define HAL_LL_TIM_CTRL1_CLKEN_B                  (1UL << 18)
#define HAL_LL_TIM_CTRL1_CLKRDY_B                 (1UL << 19)
#define HAL_LL_TIM_CTRL1_OUTEN_B                  (1UL << 29)
#define HAL_LL_TIM_CTRL1_CASCADE                  (1UL << 31)

#define HAL_LL_TIM_INTFL_WRDONE_B                 (1UL << 24)

#define HAL_LL_TIM_16BIT_MASK                     (0xFFFFUL)
#define HAL_LL_TIM_16BIT_MAX_PERIOD               (0xFFFFUL)
#define HAL_LL_TIM_MAX_PRESCALER_CODE             (12U)

#define HAL_LL_TIM_PERIPHERAL_CLOCK               ((((uint32_t)FOSC_KHZ_VALUE) * 1000UL) / 2UL)

// The MAX32690 IBRO is fixed at 7.3728 MHz.
#define HAL_LL_TIM_IBRO_CLOCK                     (7372800UL)

// -------------------------------------------------------

#define HAL_LL_TIM_AF_CONFIG (GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PORT_PULL_UP_ENABLE)

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((hal_ll_tim_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM register structure. */
typedef struct
{
    uint32_t cnt;                  /* TMR CNT Register */
    uint32_t cmp;                  /* TMR CMP Register */
    uint32_t pwm;                  /* TMR PWM Register */
    uint32_t intfl;                /* TMR INTFL Register */
    uint32_t ctrl0;                /* TMR CTRL0 Register */
    uint32_t nolcmp;               /* TMR NOLCMP Register */
    uint32_t ctrl1;                /* TMR CTRL1 Register */
    uint32_t wkfl;                 /* TMR WKFL Register */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_tim_pin_type_t pin_type;
    uint32_t af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    hal_ll_base_addr_t       base;
    hal_ll_tim_t             config;
    uint32_t                 max_period;
    uint32_t                 freq_hz;
    hal_ll_pin_name_t        module_index;
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
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] =
{
    // MAX32690 general-purpose TMR modules
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif
    #ifdef TIM_MODULE_4
    {HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_4)},
    #endif
    #ifdef TIM_MODULE_5
    {HAL_LL_TIM5_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_5)},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, 0, HAL_LL_PIN_NC}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Initializes a GPT or AGT module at the hardware level.
  *
  * Configures the selected module according to its previously set configuration.
  * Enables the module in the MCU, sets appropriate pin alternate functions,
  * and initializes the module clock and period.
  *
  * @param  map: Pointer to the hardware-specific module configuration structure.
  * @return uint32_t: The configured timer period (reload value) for the module.
  */
static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Enable TIM module gate clock.
  * @param  base - TIM module base
  *                address
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
 * Maps pin names and alternate function values for
 * TIM pin.
 *
 * @param[in]  module_index TIM HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TIM map index values
 *
 * @return  None
 */
static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief  Sets TIM pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if TIM is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param  map - Object specific context handler.
  *
  * @param  hal_ll_state - Init/De-init
  * @return none
  *
  */
static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map,
                                                      bool hal_ll_state );
/**
  * @brief  Set TIM frequency register values.
  *
  * Calculates and writes values to the period registers
  * based on the peripheral clock and desired frequency.
  *
  * @param[in] map - Object specific context handler.
  * @return uint32_t - Set period
  *
  */
static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param  map - Object specific context handler.
  * @return uint32_t - Set period.
  *
  */
static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Select TIM clock source
  * @return uint32_t - clock source
  */
static uint32_t hal_ll_tim_clock_source( hal_ll_tim_hw_specifics_map_t *map );
static bool hal_ll_tim_is_channel_b( hal_ll_tim_hw_specifics_map_t *map );
static bool hal_ll_tim_is_low_power( hal_ll_tim_hw_specifics_map_t *map );
static uint8_t hal_ll_tim_select_prescaler( uint32_t clock_hz, uint32_t freq_hz,
                                            uint32_t max_period, uint32_t *period );
static void hal_ll_tim_write_cnt( hal_ll_tim_hw_specifics_map_t *map, uint32_t value );
static void hal_ll_tim_write_pwm( hal_ll_tim_hw_specifics_map_t *map, uint32_t value );
static void hal_ll_tim_write_cmp( hal_ll_tim_hw_specifics_map_t *map, uint32_t value );

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
    uint32_t period;

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    period = hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    // Memorize information about the max period available (PWM duty cycle is dependant of this information).
    return ( hal_ll_tim_hw_specifics_map_local->max_period = period );
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg =
        hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    uint32_t period = hal_ll_tim_hw_specifics_map_local->max_period;
    uint32_t pwm;
    uint32_t en_mask;
    uint32_t enable_status_mask;
    bool is_channel_b = hal_ll_tim_is_channel_b( hal_ll_tim_hw_specifics_map_local );
    bool was_running;

    if ( duty_ratio < 0.0f ) {
        duty_ratio = 0.0f;
    } else if ( duty_ratio > 1.0f ) {
        duty_ratio = 1.0f;
    }

    en_mask = is_channel_b ? HAL_LL_TIM_CTRL0_EN_B : HAL_LL_TIM_CTRL0_EN_A;
    enable_status_mask = is_channel_b ? HAL_LL_TIM_CTRL1_CLKEN_B : HAL_LL_TIM_CTRL1_CLKEN_A;

    /*
     * TimerA has a documented polarity control, so the normal mikroSDK
     * duty ratio maps directly to PWM/CMP with POL_A=1. For exact 100%,
     * POL_A=0 and PWM=0 gives (CMP-PWM)/CMP = 100% while still satisfying
     * the documented PWM < CMP requirement.
     *
     * TimerB is documented as PWM-capable, but MAX32690 does not expose a
     * documented POL_B field. Use the fixed/default low-first relationship:
     *
     *     high_ratio = (CMP - PWM) / CMP
     *
     * Therefore PWM = CMP - high_ticks. Exact 0% is not representable in
     * TimerB PWM mode because PWM must remain strictly less than CMP, so the
     * closest representable value is used (one timer tick high).
     */
    if ( is_channel_b ) {
        uint32_t high_ticks;

        if ( duty_ratio <= 0.0f ) {
            pwm = period - 1UL;
        } else if ( duty_ratio >= 1.0f ) {
            pwm = 0UL;
        } else {
            high_ticks = ( uint32_t )( ( float )period * duty_ratio );

            if ( 0UL == high_ticks ) {
                high_ticks = 1UL;
            }
            if ( high_ticks >= period ) {
                high_ticks = period - 1UL;
            }

            pwm = period - high_ticks;
            if ( pwm >= period ) {
                pwm = period - 1UL;
            }
        }
    } else {
        if ( duty_ratio >= 1.0f ) {
            clear_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_POL_A );
            pwm = 0UL;
        } else {
            set_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_POL_A );
            pwm = ( uint32_t )( ( float )period * duty_ratio );

            if ( ( 0.0f < duty_ratio ) && ( 0UL == pwm ) ) {
                pwm = 1UL;
            }
            if ( pwm >= period ) {
                pwm = period - 1UL;
            }
        }
    }

    /*
     * PWM/CNT updates are made with the selected timer disabled while its
     * timer clock remains enabled.
     */
    was_running = ( 0UL != ( read_reg( &hal_ll_hw_reg->ctrl0 ) & en_mask ) );

    if ( was_running ) {
        clear_reg_bits( &hal_ll_hw_reg->ctrl0, en_mask );
        while ( read_reg( &hal_ll_hw_reg->ctrl1 ) & enable_status_mask ) {
        }
    }

    hal_ll_tim_write_cnt( hal_ll_tim_hw_specifics_map_local, 1UL );
    hal_ll_tim_write_pwm( hal_ll_tim_hw_specifics_map_local, pwm );

    if ( was_running ) {
        set_reg_bits( &hal_ll_hw_reg->ctrl0, en_mask );
        while ( !( read_reg( &hal_ll_hw_reg->ctrl1 ) & enable_status_mask ) ) {
        }
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg =
        hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    bool is_channel_b = hal_ll_tim_is_channel_b( hal_ll_tim_hw_specifics_map_local );
    uint32_t en_mask = is_channel_b ? HAL_LL_TIM_CTRL0_EN_B : HAL_LL_TIM_CTRL0_EN_A;
    uint32_t status_mask = is_channel_b ? HAL_LL_TIM_CTRL1_CLKEN_B : HAL_LL_TIM_CTRL1_CLKEN_A;
    uint32_t cmp_value = read_reg( &hal_ll_hw_reg->cmp );

    if ( is_channel_b ) {
        if ( 0UL == ( cmp_value & 0xFFFF0000UL ) ) {
            return HAL_LL_TIM_ERROR;
        }
    } else if ( hal_ll_tim_is_low_power( hal_ll_tim_hw_specifics_map_local ) ) {
        if ( 0UL == ( cmp_value & HAL_LL_TIM_16BIT_MASK ) ) {
            return HAL_LL_TIM_ERROR;
        }
    } else if ( 0UL == cmp_value ) {
        return HAL_LL_TIM_ERROR;
    }

    set_reg_bits( &hal_ll_hw_reg->ctrl0, en_mask );

    while ( !( read_reg( &hal_ll_hw_reg->ctrl1 ) & status_mask ) ) {
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg =
        hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    bool is_channel_b = hal_ll_tim_is_channel_b( hal_ll_tim_hw_specifics_map_local );
    uint32_t en_mask = is_channel_b ? HAL_LL_TIM_CTRL0_EN_B : HAL_LL_TIM_CTRL0_EN_A;
    uint32_t status_mask = is_channel_b ? HAL_LL_TIM_CTRL1_CLKEN_B : HAL_LL_TIM_CTRL1_CLKEN_A;

    clear_reg_bits( &hal_ll_hw_reg->ctrl0, en_mask );

    while ( read_reg( &hal_ll_hw_reg->ctrl1 ) & status_mask );

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);

    if( low_level_handle->hal_ll_tim_handle != NULL ) {
        hal_ll_tim_base_handle_t *hal_ll_hw_reg =
            hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, true );

        clear_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_EN_A | HAL_LL_TIM_CTRL0_EN_B );

        while ( read_reg( &hal_ll_hw_reg->ctrl1 ) &
                ( HAL_LL_TIM_CTRL1_CLKEN_A | HAL_LL_TIM_CTRL1_CLKEN_B ) );

        clear_reg_bits( &hal_ll_hw_reg->ctrl0,
                        HAL_LL_TIM_CTRL0_CLKEN_A | HAL_LL_TIM_CTRL0_CLKEN_B );

        while ( read_reg( &hal_ll_hw_reg->ctrl1 ) &
                ( HAL_LL_TIM_CTRL1_CLKRDY_A | HAL_LL_TIM_CTRL1_CLKRDY_B ) );

        hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        hal_ll_tim_module_enable( hal_ll_tim_hw_specifics_map_local, false );

        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;
        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.pin_type = HAL_LL_PIN_NC;
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

    // Check if the selected pin is valid.
    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( hal_ll_tim_pin_map[ pin_num ].pin == pin ) {
            // Get module number
            hal_ll_module_id = hal_ll_tim_pin_map[ pin_num ].module_index;

            // Map module number to map index
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
    // By default return last error msg.
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
    switch ( map->module_index ) {
        #ifdef TIM_MODULE_0
        case hal_ll_tim_module_num( TIM_MODULE_0 ):
            hal_ll_state ? clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_15 ) :
                           set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_15 );
            break;
        #endif

        #ifdef TIM_MODULE_1
        case hal_ll_tim_module_num( TIM_MODULE_1 ):
            hal_ll_state ? clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_16 ) :
                           set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_16 );
            break;
        #endif

        #ifdef TIM_MODULE_2
        case hal_ll_tim_module_num( TIM_MODULE_2 ):
            hal_ll_state ? clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_17 ) :
                           set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_17 );
            break;
        #endif

        #ifdef TIM_MODULE_3
        case hal_ll_tim_module_num( TIM_MODULE_3 ):
            hal_ll_state ? clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_18 ) :
                           set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_18 );
            break;
        #endif

        #ifdef TIM_MODULE_4
        case hal_ll_tim_module_num( TIM_MODULE_4 ):
            hal_ll_state ? clear_reg_bit( _LPGCR_PCLKDIS_, LPGCR_PCLKDIS_2 ) :
                           set_reg_bit( _LPGCR_PCLKDIS_, LPGCR_PCLKDIS_2 );
            break;
        #endif

        #ifdef TIM_MODULE_5
        case hal_ll_tim_module_num( TIM_MODULE_5 ):
            hal_ll_state ? clear_reg_bit( _LPGCR_PCLKDIS_, LPGCR_PCLKDIS_3 ) :
                           set_reg_bit( _LPGCR_PCLKDIS_, LPGCR_PCLKDIS_3 );
            break;
        #endif

        default:
            break;
    }
}

static uint32_t hal_ll_tim_clock_source( hal_ll_tim_hw_specifics_map_t *map ) {
    return hal_ll_tim_is_low_power( map ) ?
           HAL_LL_TIM_IBRO_CLOCK :
           HAL_LL_TIM_PERIPHERAL_CLOCK;
}

static void hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = hal_ll_tim_pin_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin_type = hal_ll_tim_pin_map[ index ].pin_type;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = hal_ll_tim_pin_map[ index ].af;
}

static void hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if( map->config.pin != HAL_LL_PIN_NC ) {
        module.pins[0] = VALUE( map->config.pin, map->config.af );
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_TIM_AF_CONFIG;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static bool hal_ll_tim_is_channel_b( hal_ll_tim_hw_specifics_map_t *map ) {
    return ( HAL_LL_TIM_PIN_B == map->config.pin_type );
}

static bool hal_ll_tim_is_low_power( hal_ll_tim_hw_specifics_map_t *map ) {
    switch ( map->module_index ) {
        #ifdef TIM_MODULE_4
        case hal_ll_tim_module_num( TIM_MODULE_4 ):
            return true;
        #endif

        #ifdef TIM_MODULE_5
        case hal_ll_tim_module_num( TIM_MODULE_5 ):
            return true;
        #endif

        default:
            return false;
    }
}

static uint8_t hal_ll_tim_select_prescaler( uint32_t clock_hz, uint32_t freq_hz,
                                            uint32_t max_period, uint32_t *period ) {
    uint8_t prescaler_code;

    if ( ( 0UL == clock_hz ) || ( 0UL == freq_hz ) || ( NULL == period ) ) {
        if ( NULL != period ) {
            *period = 0UL;
        }
        return 0U;
    }

    for ( prescaler_code = 0U; prescaler_code <= HAL_LL_TIM_MAX_PRESCALER_CODE; prescaler_code++ ) {
        uint32_t divisor = ( 1UL << prescaler_code );
        uint32_t timer_clock = clock_hz / divisor;
        uint32_t candidate = timer_clock / freq_hz;

        if ( candidate < 2UL ) {
            *period = 2UL;
            return prescaler_code;
        }

        if ( candidate <= max_period ) {
            *period = candidate;
            return prescaler_code;
        }
    }

    *period = max_period;
    return HAL_LL_TIM_MAX_PRESCALER_CODE;
}

static void hal_ll_tim_write_cnt( hal_ll_tim_hw_specifics_map_t *map, uint32_t value ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    if ( hal_ll_tim_is_channel_b( map ) ) {
        write_reg( &hal_ll_hw_reg->cnt, ( value & HAL_LL_TIM_16BIT_MASK ) << 16 );

        while ( !( read_reg( &hal_ll_hw_reg->intfl ) & HAL_LL_TIM_INTFL_WRDONE_B ) ) {
        }
    } else if ( hal_ll_tim_is_low_power( map ) ) {
        write_reg( &hal_ll_hw_reg->cnt, value & HAL_LL_TIM_16BIT_MASK );
    } else {
        write_reg( &hal_ll_hw_reg->cnt, value );
    }
}

static void hal_ll_tim_write_pwm( hal_ll_tim_hw_specifics_map_t *map, uint32_t value ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    if ( hal_ll_tim_is_channel_b( map ) ) {
        write_reg( &hal_ll_hw_reg->pwm, ( value & HAL_LL_TIM_16BIT_MASK ) << 16 );

        while ( !( read_reg( &hal_ll_hw_reg->intfl ) & HAL_LL_TIM_INTFL_WRDONE_B ) ) {
        }
    } else if ( hal_ll_tim_is_low_power( map ) ) {
        write_reg( &hal_ll_hw_reg->pwm, value & HAL_LL_TIM_16BIT_MASK );
    } else {
        write_reg( &hal_ll_hw_reg->pwm, value );
    }
}

static void hal_ll_tim_write_cmp( hal_ll_tim_hw_specifics_map_t *map, uint32_t value ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    if ( hal_ll_tim_is_channel_b( map ) ) {
        write_reg( &hal_ll_hw_reg->cmp, ( value & HAL_LL_TIM_16BIT_MASK ) << 16 );
    } else if ( hal_ll_tim_is_low_power( map ) ) {
        write_reg( &hal_ll_hw_reg->cmp, value & HAL_LL_TIM_16BIT_MASK );
    } else {
        write_reg( &hal_ll_hw_reg->cmp, value );
    }
}

static uint32_t hal_ll_tim_set_freq_bare_metal( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint32_t timer_clock = hal_ll_tim_clock_source( map );
    uint32_t max_period;
    uint32_t period;
    uint8_t prescaler_code;

    if ( ( 0UL == map->freq_hz ) || ( 0UL == timer_clock ) ) {
        hal_ll_tim_write_cmp( map, 0UL );
        return 0UL;
    }

    max_period = ( hal_ll_tim_is_channel_b( map ) || hal_ll_tim_is_low_power( map ) ) ?
                 HAL_LL_TIM_16BIT_MAX_PERIOD :
                 0xFFFFFFFFUL;

    prescaler_code = hal_ll_tim_select_prescaler( timer_clock, map->freq_hz,
                                                   max_period, &period );

    if ( hal_ll_tim_is_channel_b( map ) ) {
        clear_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_CLKDIV_B_MASK );
        set_reg_bits( &hal_ll_hw_reg->ctrl0,
                      ( ( uint32_t )prescaler_code << HAL_LL_TIM_CTRL0_CLKDIV_B_POS ) );
    } else if ( hal_ll_tim_is_low_power( map ) ) {
        clear_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_CLKDIV_A_MASK );
        set_reg_bits( &hal_ll_hw_reg->ctrl0,
                      ( ( uint32_t )prescaler_code << HAL_LL_TIM_CTRL0_CLKDIV_A_POS ) );
    } else {
        clear_reg_bits( &hal_ll_hw_reg->ctrl0,
                        HAL_LL_TIM_CTRL0_CLKDIV_A_MASK | HAL_LL_TIM_CTRL0_CLKDIV_B_MASK );
        set_reg_bits( &hal_ll_hw_reg->ctrl0,
                      ( ( uint32_t )prescaler_code << HAL_LL_TIM_CTRL0_CLKDIV_A_POS ) |
                      ( ( uint32_t )prescaler_code << HAL_LL_TIM_CTRL0_CLKDIV_B_POS ) );
    }

    hal_ll_tim_write_cmp( map, period );

    return period;
}

static uint32_t hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    bool is_channel_b = hal_ll_tim_is_channel_b( map );
    bool is_low_power = hal_ll_tim_is_low_power( map );
    uint32_t clock_enable_mask;
    uint32_t clock_ready_mask;
    uint32_t period;

    clear_reg_bits( &hal_ll_hw_reg->ctrl0,
                    HAL_LL_TIM_CTRL0_EN_A | HAL_LL_TIM_CTRL0_EN_B );

    while ( read_reg( &hal_ll_hw_reg->ctrl1 ) &
            ( HAL_LL_TIM_CTRL1_CLKEN_A | HAL_LL_TIM_CTRL1_CLKEN_B ) ) {
    }

    clear_reg_bits( &hal_ll_hw_reg->ctrl0,
                    HAL_LL_TIM_CTRL0_CLKEN_A | HAL_LL_TIM_CTRL0_CLKEN_B );

    while ( read_reg( &hal_ll_hw_reg->ctrl1 ) &
            ( HAL_LL_TIM_CTRL1_CLKRDY_A | HAL_LL_TIM_CTRL1_CLKRDY_B ) ) {
    }

    clear_reg_bits( &hal_ll_hw_reg->ctrl0,
                    HAL_LL_TIM_CTRL0_MODE_A_MASK |
                    HAL_LL_TIM_CTRL0_MODE_B_MASK |
                    HAL_LL_TIM_CTRL0_CLKDIV_A_MASK |
                    HAL_LL_TIM_CTRL0_CLKDIV_B_MASK |
                    HAL_LL_TIM_CTRL0_PWMSYNC_A );

    if ( is_low_power ) {
        /*
         * TMR4/TMR5 are single 16-bit low-power timers. Their internal TimerA
         * controls the counter. CLK0 is IBRO. Both low-power CLKSEL fields
         * are written to the same value as required by the MAX32690.
         */
        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_CASCADE );
        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_CLKSEL_A_MASK |
                        HAL_LL_TIM_CTRL1_CLKSEL_B_MASK );

        set_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_MODE_A_PWM |
                      HAL_LL_TIM_CTRL0_POL_A );

        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_OUTEN_A |
                        HAL_LL_TIM_CTRL1_OUTBEN_A );

        clock_enable_mask = HAL_LL_TIM_CTRL0_CLKEN_A;
        clock_ready_mask = HAL_LL_TIM_CTRL1_CLKRDY_A;
    } else if ( is_channel_b ) {
        // TimerB uses the upper 16-bit CNT/CMP/PWM fields in dual-16 mode.
        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_CASCADE );
        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_CLKSEL_B_MASK );

        set_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_MODE_B_PWM );
        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_OUTEN_B );

        clock_enable_mask = HAL_LL_TIM_CTRL0_CLKEN_B;
        clock_ready_mask = HAL_LL_TIM_CTRL1_CLKRDY_B;
    } else {
        // TimerA on TMR0-TMR3 uses the full 32-bit A+B cascade.
        set_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_CASCADE );

        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_CLKSEL_A_MASK |
                        HAL_LL_TIM_CTRL1_CLKSEL_B_MASK );

        set_reg_bits( &hal_ll_hw_reg->ctrl0, HAL_LL_TIM_CTRL0_MODE_A_PWM |
                      HAL_LL_TIM_CTRL0_POL_A );

        clear_reg_bits( &hal_ll_hw_reg->ctrl1, HAL_LL_TIM_CTRL1_OUTEN_A |
                        HAL_LL_TIM_CTRL1_OUTBEN_A );

        clock_enable_mask = HAL_LL_TIM_CTRL0_CLKEN_A;
        clock_ready_mask = HAL_LL_TIM_CTRL1_CLKRDY_A;
    }

    set_reg_bits( &hal_ll_hw_reg->ctrl0, clock_enable_mask );
    while ( !( read_reg( &hal_ll_hw_reg->ctrl1 ) & clock_ready_mask ) ) {
    }

    period = hal_ll_tim_set_freq_bare_metal( map );

    hal_ll_tim_write_cnt( map, 1UL );

    if ( is_channel_b ) {
        // Closest representable value to 0% with TimerB's fixed/default polarity.
        hal_ll_tim_write_pwm( map, ( period > 1UL ) ? period - 1UL : 0UL );
    } else {
        // POL_A = 1 + PWM = 0 gives deterministic 0% duty.
        hal_ll_tim_write_pwm( map, 0UL );
    }

    return period;
}

static uint32_t hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_module_enable( map, true );

    hal_ll_tim_alternate_functions_set_state( map, true );

    return hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
