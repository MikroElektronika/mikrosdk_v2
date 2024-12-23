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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
#include "hal_ll_pmc.h"
#include "hal_ll_tim.h"
#include "hal_ll_tim_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Register bits macros. */
#define HAL_LL_TC_CCR_CLKEN_BIT     0
#define HAL_LL_TC_CCR_CLKDIS_BIT    1
#define HAL_LL_TC_CCR_SWTRG_BIT     2
#define HAL_LL_TC_EMR_NODIVCLK_BIT  8
#define HAL_LL_TC_CMR_WAVE_BIT      15
#define HAL_LL_PID_TC6_BIT          15
#define HAL_LL_PID_TC7_BIT          16
#define HAL_LL_PID_TC8_BIT          17
#define HAL_LL_PID_TC9_BIT          18
#define HAL_LL_PID_TC10_BIT         19
#define HAL_LL_PID_TC11_BIT         20
#define HAL_LL_PID_TC0_BIT          23
#define HAL_LL_PID_TC1_BIT          24
#define HAL_LL_PID_TC2_BIT          25
#define HAL_LL_PID_TC3_BIT          26
#define HAL_LL_PID_TC4_BIT          27
#define HAL_LL_PID_TC5_BIT          28

/*!< @brief Register masks macros. */
#define HAL_LL_TC_CMR_TIMER_CLOCK2_MASK 0x1
#define HAL_LL_TC_CMR_TIMER_CLOCK3_MASK 0x2
#define HAL_LL_TC_CMR_TIMER_CLOCK4_MASK 0x3
#define HAL_LL_TC_CMR_EEVT_XC0_MASK     0x0400
#define HAL_LL_TC_CMR_WAVSEL_UP_RC_MASK 0x4000
#define HAL_LL_TC_CMR_ACPA_CLEAR_MASK   0x20000
#define HAL_LL_TC_CMR_ACPC_SET_MASK     0x40000
#define HAL_LL_TC_CMR_BCPB_CLEAR_MASK   0x2000000
#define HAL_LL_TC_CMR_BCPC_SET_MASK     0x4000000

/*!< @brief Helper macro fpr getting clock speed */
#define hal_ll_get_system_clock (Get_Fosc_kHz() * 1000)
#define hal_ll_tim_timer_clock_2 (hal_ll_get_system_clock / 8)
#define hal_ll_tim_timer_clock_3 (hal_ll_get_system_clock / 32)
#define hal_ll_tim_timer_clock_4 (hal_ll_get_system_clock / 128)

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
/*!< @brief TIM channel register ctructure. */
typedef struct
{
    hal_ll_base_addr_t ccr;
    hal_ll_base_addr_t cmr;
    hal_ll_base_addr_t smmr;
    hal_ll_base_addr_t rab;
    hal_ll_base_addr_t cv;
    hal_ll_base_addr_t ra;
    hal_ll_base_addr_t rb;
    hal_ll_base_addr_t rc;
    hal_ll_base_addr_t sr;
    hal_ll_base_addr_t ier;
    hal_ll_base_addr_t idr;
    hal_ll_base_addr_t imr;
    hal_ll_base_addr_t emr;
    hal_ll_base_addr_t _unused[3];
} hal_ll_tim_channel_handle_t;

/*!< @brief TIM register structure. */
typedef struct
{
    hal_ll_tim_channel_handle_t channel[3];
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_channel_t  channel;
    uint8_t af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    hal_ll_base_addr_t  base;
    hal_ll_tim_t        config;
    uint16_t            max_period;
    uint32_t            freq_hz;
    uint8_t   module_index;
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
/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] =
{
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDRESS, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0)},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDRESS, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1)},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDRESS, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2)},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDRESS, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3)},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, HAL_LL_PIN_NC}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief  Enable TIM module 0 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @param  channel - TIM0 channel.
 * @return none
 */
static inline void _hal_ll_tim0_set_clock( hal_ll_channel_t channel, bool hal_ll_state );

/**
 * @brief  Enable TIM module 1 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @param  channel - TIM1 channel.
 * @return none
 */
static inline void _hal_ll_tim1_set_clock( hal_ll_channel_t channel, bool hal_ll_state );

/**
 * @brief  Enable TIM module 2 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @param  channel - TIM2 channel.
 * @return none
 */
static inline void _hal_ll_tim2_set_clock( hal_ll_channel_t channel, bool hal_ll_state );

/**
 * @brief  Enable TIM module 3 clock.
 * @param  hal_ll_stat - True(enable clock)/False(disable clock).
 * @param  channel - TIM3 channel.
 * @return none
 */
static inline void _hal_ll_tim3_set_clock( hal_ll_channel_t channel, bool hal_ll_state );

/**
  * @brief  Enable TIM module gate clock.
  * @param  map - Object specific context handler.
  * @return None
  */
static void _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Based on selected TIM,
  *         return clock speed.
  * @param  map - Object specific context handler.
  * @return uint32_t clock source.
  */
static uint32_t _hal_ll_tim_get_clock_speed( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param  map - Object specific context handler.
  * @return none
  *
  */
static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Full TIM module initialization procedure.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param  map - Object specific context handler.
  * @return none
  *
  */
static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

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
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

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
static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

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
static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {

    uint8_t index;
    uint16_t pin_check_result;

    if ( ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( hal_ll_tim_hw_specifics_map[ pin_check_result ].config.pin != pin ){
        // Clear previous module alternate functions
        _hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );

        _hal_ll_tim_map_pin( pin_check_result, index );

        _hal_ll_tim_alternate_functions_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );

        handle_map[ pin_check_result ].init_ll_state = false;

        hal_ll_module_state[ pin_check_result ].init_ll_state = false;

    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_handle_register_t *hal_handle = ( hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    if ( HAL_LL_TIM_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->max_period )
        return HAL_LL_TIM_MODULE_ERROR;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {

    uint8_t channel_num;
    uint32_t ck_psc;
    uint32_t tmp_freq;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    channel_num = hal_ll_tim_hw_specifics_map_local->config.channel;

    // Stop capture/compare.
    set_reg_bit( &hal_ll_hw_reg->channel[ channel_num ].ccr, HAL_LL_TC_CCR_CLKDIS_BIT );

    // Check if the pin uses channel signal A or B (0x00 for signal A and 0x10 for signal B).
    if ( !( hal_ll_tim_hw_specifics_map_local->config.af & HAL_LL_SIGNAL_CHANNEL_AB_MASK ) )
        clear_reg( &hal_ll_hw_reg->channel[ channel_num ].ra );
    else
        clear_reg( &hal_ll_hw_reg->channel[ channel_num ].rb );

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    if ( HAL_LL_TIM_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->max_period )
        return HAL_LL_TIM_MODULE_ERROR;

    low_level_handle->init_ll_state = true;

    return tmp_freq;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {

    float    tmp_duty;
    uint8_t channel_num = hal_ll_tim_hw_specifics_map_local->config.channel;
    uint32_t max_duty = 0;
    uint16_t max_period;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( low_level_handle->init_ll_state == false ) {
        hal_ll_tim_start( handle );
        low_level_handle->init_ll_state = true;
    }

    tmp_duty = duty_ratio * 100;
    max_period = hal_ll_tim_hw_specifics_map_local->max_period;

    max_duty = ( ( float )max_period / 100 ) * tmp_duty;

    // Check if the pin uses channel signal A or B (0x00 for signal A and 0x10 for signal B).
    if ( !( hal_ll_tim_hw_specifics_map_local->config.af & HAL_LL_SIGNAL_CHANNEL_AB_MASK ) ) {
        // Set duty for TIOAx pin.
        write_reg( &hal_ll_hw_reg->channel[ channel_num ].ra, max_duty );
    } else {
        // Set duty for TIOBx pin.
        write_reg( &hal_ll_hw_reg->channel[ channel_num ].rb, max_duty );
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    uint8_t channel_num = hal_ll_tim_hw_specifics_map_local->config.channel;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // Set UP mode with automatic trigger on RC Compare Position (go from 0 to RC value).
    set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_WAVSEL_UP_RC_MASK );

    // Check if the pin uses channel signal A or B (0x00 for signal A and 0x10 for signal B).
    if ( !( hal_ll_tim_hw_specifics_map_local->config.af & HAL_LL_SIGNAL_CHANNEL_AB_MASK ) ) {
        // Clear TIOAx pin on RA compare and set on RC compare.
        set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_ACPA_CLEAR_MASK );
        set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_ACPC_SET_MASK );
    } else {
        // Clear TIOBx pin on RB compare and set on RC compare. Also set TIOBx as output.
        set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_BCPB_CLEAR_MASK );
        set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_BCPC_SET_MASK );
        set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_EEVT_XC0_MASK );
    }

    // Enable counter.
    set_reg_bit( &hal_ll_hw_reg->channel[ channel_num ].ccr, HAL_LL_TC_CCR_CLKEN_BIT );

    // Trigger the counter.
    set_reg_bit( &hal_ll_hw_reg->channel[ channel_num ].ccr, HAL_LL_TC_CCR_SWTRG_BIT );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    uint8_t channel_num = hal_ll_tim_hw_specifics_map_local->config.channel;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // Disable counter.
    set_reg_bit( &hal_ll_hw_reg->channel[ channel_num ].ccr, HAL_LL_TC_CCR_CLKDIS_BIT );

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

        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, true );
        _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local->base, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.channel = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.af = NULL;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static inline void _hal_ll_tim0_set_clock( hal_ll_channel_t channel_num, bool hal_ll_state ) {
    uint8_t id_pos;

    // Get the appropriate PID number.
    switch ( channel_num )
    {
        case HAL_LL_TIM_CHANNEL_0:
            id_pos = HAL_LL_PID_TC0_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_1:
            id_pos = HAL_LL_PID_TC1_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_2:
            id_pos = HAL_LL_PID_TC2_BIT;
            break;

        default:
            break;
    }

    // Enable/disable clock for appropriate channel and timer.
    if( hal_ll_state ) {
        set_reg_bit( _PMC_PCER0, id_pos );
    } else {
        set_reg_bit( _PMC_PCDR0, id_pos );
    }
}

static inline void _hal_ll_tim1_set_clock( hal_ll_channel_t channel_num, bool hal_ll_state ) {
    uint8_t id_pos;

    // Get the appropriate PID number.
    switch ( channel_num )
    {
        case HAL_LL_TIM_CHANNEL_0:
            id_pos = HAL_LL_PID_TC3_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_1:
            id_pos = HAL_LL_PID_TC4_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_2:
            id_pos = HAL_LL_PID_TC5_BIT;
            break;

        default:
            break;
    }

    // Enable/disable clock for appropriate channel and timer.
    if( hal_ll_state ) {
        set_reg_bit( _PMC_PCER0, id_pos );
    } else {
        set_reg_bit( _PMC_PCDR0, id_pos );
    }
}

static inline void _hal_ll_tim2_set_clock( hal_ll_channel_t channel_num, bool hal_ll_state ) {
    uint8_t id_pos;

    // Get the appropriate PID number.
    switch ( channel_num )
    {
        case HAL_LL_TIM_CHANNEL_0:
            id_pos = HAL_LL_PID_TC6_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_1:
            id_pos = HAL_LL_PID_TC7_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_2:
            id_pos = HAL_LL_PID_TC8_BIT;
            break;

        default:
            break;
    }

    // Enable/disable clock for appropriate channel and timer.
    if( hal_ll_state ) {
        set_reg_bit( _PMC_PCER1, id_pos );
    } else {
        set_reg_bit( _PMC_PCDR1, id_pos );
    }
}

static inline void _hal_ll_tim3_set_clock( hal_ll_channel_t channel_num, bool hal_ll_state ) {
    uint8_t id_pos;

    // Get the appropriate PID number.
    switch ( channel_num )
    {
        case HAL_LL_TIM_CHANNEL_0:
            id_pos = HAL_LL_PID_TC9_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_1:
            id_pos = HAL_LL_PID_TC10_BIT;
            break;
        case HAL_LL_TIM_CHANNEL_2:
            id_pos = HAL_LL_PID_TC11_BIT;
            break;

        default:
            break;
    }

    // Enable/disable clock for appropriate channel and timer.
    if( hal_ll_state ) {
        set_reg_bit( _PMC_PCER1, id_pos );
    } else {
        set_reg_bit( _PMC_PCDR1, id_pos );
    }
}

static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map ) {

    hal_ll_pin_name_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    uint16_t map_size = ( sizeof( _tim_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    // Check if the selected pin is valid.
    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( _tim_map[ pin_num ].pin == pin ) {
            // Get module number
            hal_ll_module_id = _tim_map[ pin_num ].module_index;
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
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

    switch ( map->base ) {
        #ifdef TIM_MODULE_0
        case ( HAL_LL_TIM0_BASE_ADDRESS ):
            _hal_ll_tim0_set_clock( map->config.channel, hal_ll_state );
            break;
        #endif
        #ifdef TIM_MODULE_1
        case ( HAL_LL_TIM1_BASE_ADDRESS ):
            _hal_ll_tim1_set_clock( map->config.channel, hal_ll_state );
            break;
        #endif
        #ifdef TIM_MODULE_2
        case ( HAL_LL_TIM2_BASE_ADDRESS ):
            _hal_ll_tim2_set_clock( map->config.channel, hal_ll_state );
            break;
        #endif
        #ifdef TIM_MODULE_3
        case ( HAL_LL_TIM3_BASE_ADDRESS ):
            _hal_ll_tim3_set_clock( map->config.channel, hal_ll_state );
            break;
        #endif

        default:
            break;
    }
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {

    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = _tim_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.channel = _tim_map[ index ].channel;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = _tim_map[ index ].af;
}

static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;

    if ( ( map->config.pin != HAL_LL_PIN_NC ) && map->config.pin != HAL_LL_PIN_NC ) {
        module.pins[0] = map->config.pin;
        module.pins[1] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = map->config.af & HAL_LL_ALTERNATE_FUNCTION_MASK;
        module.configs[1] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t _hal_ll_tim_get_clock_speed( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint8_t channel_num = map->config.channel;

    if ( UINT16_MAX < hal_ll_get_system_clock / map->freq_hz ) {
        if ( UINT16_MAX < hal_ll_tim_timer_clock_2 / map->freq_hz ) {
            if ( UINT16_MAX < hal_ll_tim_timer_clock_3 / map->freq_hz ) {
                if ( UINT16_MAX < hal_ll_tim_timer_clock_4 / map->freq_hz )
                    // Clock divider can't be more than 16-bit field can handle.
                    return HAL_LL_TIM_MODULE_ERROR;
                // Set TIM clock to be FOSC / 128.
                set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_TIMER_CLOCK4_MASK );
                return hal_ll_tim_timer_clock_4;
            }
            // Set TIM clock to be FOSC / 32.
            set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_TIMER_CLOCK3_MASK );
            return hal_ll_tim_timer_clock_3;
        }
        // Set TIM clock to be FOSC / 8.
        set_reg_bits( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_TIMER_CLOCK2_MASK );
        return hal_ll_tim_timer_clock_2;
    }
    // Set TIM clock to be FOSC.
    set_reg_bit( &hal_ll_hw_reg->channel[ channel_num ].emr, HAL_LL_TC_EMR_NODIVCLK_BIT );
    return hal_ll_get_system_clock;
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );
    uint8_t channel_num = map->config.channel;
    uint32_t  ck_psc;

    // Get clock speed prescaler.
    ck_psc = _hal_ll_tim_get_clock_speed( map ) / map->freq_hz;

    // Write the prescale value to set the desired frequency.
    write_reg( &hal_ll_hw_reg->channel[ channel_num ].rc, ck_psc );

    // Counter is used in waveform mode.
    set_reg_bit( &hal_ll_hw_reg->channel[ channel_num ].cmr, HAL_LL_TC_CMR_WAVE_BIT );

    // Write max period to global array.
    map->max_period = ( uint16_t )ck_psc;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    _hal_ll_tim_set_clock( map, true );

    _hal_ll_tim_alternate_functions_set_state( map, true );

    _hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
