/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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

#include "hal_ll_tim.h"
#include "hal_ll_rcu.h"
#include "hal_ll_gpio.h"
#include "hal_ll_tim_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ];

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((hal_ll_tim_base_handle_t *)_handle)
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

/*!< @brief Helper macro for enabling counter, which utilizes Control Register 0 (TIMERx_CTL0). */
#define HAL_LL_TIM_ENABLE_COUNTER_BIT 0

/*!< @brief Helper macros for enabling specific Timer module clocks (APB2 and APB1 registers). */
#define HAL_LL_TIM_ENABLE_0 11
#define HAL_LL_TIM_ENABLE_1 0
#define HAL_LL_TIM_ENABLE_2 1
#define HAL_LL_TIM_ENABLE_3 2
#define HAL_LL_TIM_ENABLE_4 3

/*!< @brief Helper macros for appropriate Clock Bus selection. */
#define HAL_LL_APB2_TIMER_CLOCK 0
#define HAL_LL_APB1_TIMER_CLOCK 1

/*!< @brief Helper macro for configuring counter to be used as a upcounter, which utilizes Control Register 0 (TIMERx_CTL0). */
#define HAL_LL_TIM_COUNTER_DIRECTION 4

/*!< @brief Helper macros for applying "PWM mode 0" for channels 0 and 2, which utilizes Channel Control Register (TIMERx_CHCTL 0 and 1). */
#define HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_0_AND_2_BIT_0 5
#define HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_0_AND_2_BIT_1 6

/*!< @brief Helper macros for applying "PWM mode 0" for channels 1 and 3, which utilizes Channel Control Register (TIMERx_CHCTL 0 and 1). */
#define HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_1_AND_3_BIT_0 13
#define HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_1_AND_3_BIT_1 14

/*!< @brief Helper macro for displaying total number of standard PWM channels. */
#define HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS 4

/*!< @brief Helper macro for enabling complementary PWM pin outputs, which utilizes Complementary Channel Register (TIMERx_CCHP). */
#define HAL_LL_TIM_PRIMARY_OUTPUT_EN_BIT 15

/*!< @brief Helper macro for retrieving complementary enable bit number. */
#define HAL_LL_TIM_COMPLEMENTARY_OUTPUT_ENABLE_BIT 2

/*!< @brief Helper macro for retrieving complementary polarity bit number. */
#define HAL_LL_TIM_COMPLEMENTARY_OUTPUT_POLARITY_BIT 3

/*!< @brief Helper macro for retrieving standard polarity bit number. */
#define HAL_LL_TIM_STANDARD_OUTPUT_POLARITY_BIT 1

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM register structure. */
typedef struct {
    uint32_t timer_ctl0; /* Control register 0 for both Advanced timer and General timers. */
    uint32_t timer_ctl1; /* Control register 1 for both Advanced timer and General timers. */
    uint32_t timer_smcfg; /* Slave mode configuration register. */
    uint32_t timer_dmainten; /* DMA and Interrupt enable register. */
    uint32_t timer_intf; /* Interrupt Flag register. */
    uint32_t timer_swevg; /* Software Event Generation register. */
    uint32_t timer_chctl0; /* Channel Control register 0. */
    uint32_t timer_chctl1; /* Channel Control register 1. */
    uint32_t timer_chctl2; /* Channel Control register 2. */
    uint32_t timer_cnt; /* Counter register. */
    uint32_t timer_psc; /* Prescaler register. */
    uint32_t timer_car; /* Counter Auto-Reload register. */
    uint32_t timer_crep; /* Counter Repetition register. */
    uint32_t timer_ch0cv; /* Channel 0 Capture/Compare value register. */
    uint32_t timer_ch1cv; /* Channel 1 Capture/Compare value register. */
    uint32_t timer_ch2cv; /* Channel 2 Capture/Compare value register. */
    uint32_t timer_ch3cv; /* Channel 3 Capture/Compare value register. */
    uint32_t timer_cchp; /*  Complementary Channel Protection register (AVAILABLE ONLY FOR ADVANCED TIMER 0). */
    uint32_t timer_dmacfg; /* DMA Configuration register. */
    uint32_t timer_dmatb; /* DMA Transfer Buffer register. */
} hal_ll_tim_base_handle_t;

/*!< @brief TIM pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_channel_t  channel;
    uint32_t af;
} hal_ll_tim_t;

/*!< @brief TIM hardware specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_tim_t config;
    uint16_t max_period;
    uint32_t freq_hz;
    uint8_t module_index;
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hardware specific error values. */
typedef enum {
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM hardware specific info. */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] = {
    #ifdef TIM_MODULE_0
    { HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0) },
    #endif
    #ifdef TIM_MODULE_1
    { HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1) },
    #endif
    #ifdef TIM_MODULE_2
    { HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2) },
    #endif
    #ifdef TIM_MODULE_3
    { HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3) },
    #endif
    #ifdef TIM_MODULE_4
    { HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC}, 0, 0, hal_ll_tim_module_num(TIM_MODULE_4) },
    #endif

    { HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_CHANNEL_ERROR, HAL_LL_PIN_NC}, 0, 0, 0 }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

/*!< @brief Global handle for PWM pin to be standard or complementary. */
static bool HAL_LL_TIM_IS_COMPLEMENTARY;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief  Enable TIM module 0 clock.
 * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
 * @return none
 */
static void _hal_ll_tim0_set_clock( bool hal_ll_state );

/**
 * @brief  Enable TIM module 1 clock.
 * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
 * @return none
 */
static void _hal_ll_tim1_set_clock( bool hal_ll_state );

/**
  * @brief  Enable TIM module 2 clock.
  * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim2_set_clock( bool hal_ll_state );

/**
  * @brief  Enable TIM module 3 clock.
  * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim3_set_clock( bool hal_ll_state );

/**
  * @brief  Enable TIM module 4 clock.
  * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static inline void _hal_ll_tim4_set_clock( bool hal_ll_state );

/**
  * @brief  Enable TIM module gate clock.
  * @param[in] base - TIM module base address
  * @param[in] hal_ll_state - True(enable clock)/False(disable clock).
  * @return None
  */
static void _hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state );

/**
  * @brief  Select TIM clock source
  * @param[in]  selector - clock source selector
  * @return uint32_t - clock source
  */
static uint32_t _hal_ll_tim_clock_source( uint8_t selector );

/**
  * @brief  Based on selected TIM,
  *         return clock speed.
  * @param[in] base - TIM module base address
  * @return uint32_t clock source.
  */
static uint32_t _hal_ll_tim_get_clock_speed( hal_ll_base_addr_t base );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *map - Object specific context handler.
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
  * @param[in] *map - Object specific context handler.
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
  * @param[in] handle - Object specific context handler.
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
  * @param[in] pin - TIM pre-defined pin name.
  * @param[out] *index - Index list address.
  * @param[out] *handle_map - TIM HAL low level handle register.
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
 * @param[in] module_index TIM HW module index -- 0,1,2...
 * @param[in] index_list  Array with TIM map index values
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
  * @param[in] *map - Object specific context handler.
  * @param[in] hal_ll_state - Init/De-init
  * @return none
  *
  */
static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map, uint8_t *hal_module_id ) {
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
    hal_ll_tim_handle_register_t *hal_handle = (hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {
    uint32_t pwm_clock_prescaler;
    uint32_t minimal_pwm_frequency;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    // If complementary output channel is used.
    if ( HAL_LL_TIM_IS_COMPLEMENTARY ) {
        // Stop capture/compare.
        clear_reg_bit( &hal_ll_hw_reg->timer_chctl2, ( ( hal_ll_tim_hw_specifics_map_local->config.channel * \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS ) + \
        HAL_LL_TIM_COMPLEMENTARY_OUTPUT_ENABLE_BIT ) );
    // Else, normal channel is being used.
    } else {
        // Stop capture/compare.
        clear_reg_bit( &hal_ll_hw_reg->timer_chctl2, ( hal_ll_tim_hw_specifics_map_local->config.channel * \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS ) );
    }

    // Set TIM duty to 0.
    *( &hal_ll_hw_reg->timer_ch0cv + hal_ll_tim_hw_specifics_map_local->config.channel ) = 0;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    pwm_clock_prescaler = _hal_ll_tim_get_clock_speed( hal_ll_tim_hw_specifics_map_local->base ) / hal_ll_tim_hw_specifics_map_local->freq_hz;
    minimal_pwm_frequency = _hal_ll_tim_get_clock_speed( hal_ll_tim_hw_specifics_map_local->base ) / UINT16_MAX;

    // If user-defined PWM frequency is less then eligible hardware frequency, set PWM frequency to be the minimal possible.
    if ( pwm_clock_prescaler > UINT16_MAX ) {
        // Insert modified user-defined PWM frequency into local map.
        hal_ll_tim_hw_specifics_map_local->freq_hz = minimal_pwm_frequency;
    } else {
        // Insert original user-defined PWM frequency into local map.
        hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;
    }

    // Init once again, but with updated PWM frequency value.
    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_tim_hw_specifics_map_local->freq_hz;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    uint16_t max_period;
    uint16_t final_duty_value = 0;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    final_duty_value = hal_ll_tim_hw_specifics_map_local->max_period * duty_ratio;

    switch ( hal_ll_tim_hw_specifics_map_local->config.channel ) {
        case 0:
            hal_ll_hw_reg->timer_ch0cv = final_duty_value;
            break;
        case 1:
            hal_ll_hw_reg->timer_ch1cv = final_duty_value;
            break;
        case 2:
            hal_ll_hw_reg->timer_ch2cv = final_duty_value;
            break;
        case 3:
            hal_ll_hw_reg->timer_ch3cv = final_duty_value;
            break;
    }

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    // Enable PWM channel.
    if ( HAL_LL_TIM_IS_COMPLEMENTARY ) {
        // Enable appropriate channel (available channels: 0, 1 and 2).
        set_reg_bit( &hal_ll_hw_reg->timer_chctl2, ( ( hal_ll_tim_hw_specifics_map_local->config.channel ) * \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS + HAL_LL_TIM_COMPLEMENTARY_OUTPUT_ENABLE_BIT) );

        // Make sure channel polarity is active high.
        clear_reg_bit( &hal_ll_hw_reg->timer_chctl2, ( ( hal_ll_tim_hw_specifics_map_local->config.channel ) * \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS + HAL_LL_TIM_COMPLEMENTARY_OUTPUT_POLARITY_BIT ) );
    } else {
        // Enable appropriate channel (available channels: 0, 1, 2 and 3).
        set_reg_bit( &hal_ll_hw_reg->timer_chctl2, ( ( hal_ll_tim_hw_specifics_map_local->config.channel ) * \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS ) );

        // Make sure channel polarity is active high.
        clear_reg_bit( &hal_ll_hw_reg->timer_chctl2, ( ( hal_ll_tim_hw_specifics_map_local->config.channel ) * \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS + HAL_LL_TIM_STANDARD_OUTPUT_POLARITY_BIT ) );
    }

    #if defined(TIM_MODULE_0)
    // Enable OC and OCN outputs if their respective enable bits are set.
    set_reg_bit( &hal_ll_hw_reg->timer_cchp, HAL_LL_TIM_PRIMARY_OUTPUT_EN_BIT );
    #endif

    // Utilizing Channel Control register (TIMERx_CHCTL0 for channels 1 and 0; TIMERx_CHCTL1 for channels 3 and 2).
    switch ( hal_ll_tim_hw_specifics_map_local->config.channel ) {
        case 0:
            // Enable PWM mode.
            set_reg_bit( &hal_ll_hw_reg->timer_chctl0, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_0_AND_2_BIT_0 );
            set_reg_bit( &hal_ll_hw_reg->timer_chctl0, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_0_AND_2_BIT_1 );
            break;
        case 1:
            // Enable PWM mode.
            set_reg_bit( &hal_ll_hw_reg->timer_chctl0, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_1_AND_3_BIT_0 );
            set_reg_bit( &hal_ll_hw_reg->timer_chctl0, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_1_AND_3_BIT_1 );
            break;
        case 2:
            // Enable PWM mode.
            set_reg_bit( &hal_ll_hw_reg->timer_chctl1, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_0_AND_2_BIT_0 );
            set_reg_bit( &hal_ll_hw_reg->timer_chctl1, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_0_AND_2_BIT_1 );
            break;
        case 3:
            // Enable PWM mode.
            set_reg_bit( &hal_ll_hw_reg->timer_chctl1, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_1_AND_3_BIT_0 );
            set_reg_bit( &hal_ll_hw_reg->timer_chctl1, HAL_LL_TIM_ENABLE_PWM_MODE_CHANNELS_1_AND_3_BIT_1 );
            break;
    }

    // Finally, enable counter in order to initiate counting.
    set_reg_bit( &hal_ll_hw_reg->timer_ctl0, HAL_LL_TIM_ENABLE_COUNTER_BIT );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( HAL_LL_MODULE_ERROR == hal_ll_tim_hw_specifics_map_local->base ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }

    if ( HAL_LL_TIM_IS_COMPLEMENTARY ) {
        hal_ll_hw_reg->timer_chctl2 &= ~(1UL << ( hal_ll_tim_hw_specifics_map_local->config.channel *
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS + HAL_LL_TIM_COMPLEMENTARY_OUTPUT_ENABLE_BIT)) ;
    } else {
        hal_ll_hw_reg->timer_chctl2 &= ~(1UL << hal_ll_tim_hw_specifics_map_local->config.channel *
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS);
    }

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
        hal_ll_tim_hw_specifics_map_local->config.channel = HAL_LL_CHANNEL_ERROR;
        hal_ll_tim_hw_specifics_map_local->config.af = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static void _hal_ll_tim0_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit( RCU_APB2EN, HAL_LL_TIM_ENABLE_0 );
    } else {
        clear_reg_bit( RCU_APB2EN, HAL_LL_TIM_ENABLE_0 );
    }
}

static void _hal_ll_tim1_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_1 );
    } else {
        clear_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_1 );
    }
}

static void _hal_ll_tim2_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_2 );
    } else {
        clear_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_2 );
    }
}

static void _hal_ll_tim3_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_3 );
    } else {
        clear_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_3 );
    }
}

static void _hal_ll_tim4_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_4 );
    } else {
        clear_reg_bit( RCU_APB1EN, HAL_LL_TIM_ENABLE_4 );
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

static void _hal_ll_tim_set_clock( hal_ll_base_addr_t base, bool hal_ll_state ) {
    switch ( ( uint32_t )base ) {
    #ifdef TIM_MODULE_0
        case ( 0x40012C00 ):
            _hal_ll_tim0_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_1
        case ( 0x40000000 ):
            _hal_ll_tim1_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_2
        case ( 0x40000400 ):
            _hal_ll_tim2_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_3
        case ( 0x40000800 ):
            _hal_ll_tim3_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_4
        case ( 0x40000C00 ):
            _hal_ll_tim4_set_clock( hal_ll_state );
            break;
    #endif
    }
}

static uint32_t _hal_ll_tim_clock_source( uint8_t selector ) {
    rcu_clocks_t rcu_clocks;
    system_rcu_get_clocks( &rcu_clocks );

    if( HAL_LL_APB2_TIMER_CLOCK == selector ) {
        if ( rcu_clocks.rcu_clocks_ahb / rcu_clocks.rcu_clocks_apb2 > 1 ) {
            return rcu_clocks.rcu_clocks_apb2 * 2;
        } else {
            return rcu_clocks.rcu_clocks_apb2;
        }
    } else if( HAL_LL_APB1_TIMER_CLOCK == selector ) {
        if ( rcu_clocks.rcu_clocks_ahb / rcu_clocks.rcu_clocks_apb1 > 1 ) {
            return rcu_clocks.rcu_clocks_apb1 * 2;
        } else {
            return rcu_clocks.rcu_clocks_apb1;
        }
    }
}

static uint32_t _hal_ll_tim_get_clock_speed( hal_ll_base_addr_t base ) {
    switch ( ( uint32_t )base ) {
        #ifdef TIM_MODULE_0
        case ( 0x40012C00 ):
            return _hal_ll_tim_clock_source( HAL_LL_APB2_TIMER_CLOCK );
            break;
        #endif
        #ifdef TIM_MODULE_1
        case ( 0x40000000 ):
            return _hal_ll_tim_clock_source( HAL_LL_APB1_TIMER_CLOCK );
            break;
        #endif
        #ifdef TIM_MODULE_2
        case ( 0x40000400 ):
            return _hal_ll_tim_clock_source( HAL_LL_APB1_TIMER_CLOCK );
            break;
        #endif
        #ifdef TIM_MODULE_3
        case ( 0x40000800 ):
            return _hal_ll_tim_clock_source( HAL_LL_APB1_TIMER_CLOCK );
            break;
        #endif
        #ifdef TIM_MODULE_4
        case ( 0x40000C00 ):
            return _hal_ll_tim_clock_source( HAL_LL_APB1_TIMER_CLOCK );
            break;
        #endif
    }
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pin.
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = _tim_map[ index ].pin;

    // Map new alternate function.
    hal_ll_tim_hw_specifics_map[ module_index ].config.af = _tim_map[ index ].af;

    // Map new channel (whether it is standard or complementary).
    if ( _tim_map[ index ].channel >= HAL_LL_TIM_CHANNEL_0N ) {
        HAL_LL_TIM_IS_COMPLEMENTARY = true;
        hal_ll_tim_hw_specifics_map[ module_index ].config.channel = _tim_map[ index ].channel - \
        HAL_LL_TIM_NUM_OF_STANDARD_CHANNELS;
    } else {
        HAL_LL_TIM_IS_COMPLEMENTARY = false;
        hal_ll_tim_hw_specifics_map[ module_index ].config.channel = _tim_map[ index ].channel;
    }
}

static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;
    uint32_t tim_config = 0;

    if( map->config.pin != HAL_LL_PIN_NC ) {
        if( hal_ll_state == false ) {
            tim_config = GPIO_CTL_CFG_OUTPUT_AFIO_PP | GPIO_CTL_MODE_OUTPUT_SPEED_M50;
        } else {
            tim_config = GPIO_CTL_CFG_OUTPUT_AFIO_PP | GPIO_CTL_MODE_OUTPUT_SPEED_M50;
        }

        module.pins[ 0 ] = VALUE( map->config.pin, map->config.af );
        module.pins[ 1 ] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = tim_config;
        module.configs[ 1 ] = GPIO_MODULE_STRUCT_END;

        module.gpio_remap   = map->config.af;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    // Prescaler value.
    uint32_t prescaler_value = 0;

    // Get list of registers needed for appropriate Timer module to be up and running.
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    // Set Timer module counter to be used as upcounter.
    clear_reg_bit( &hal_ll_hw_reg->timer_ctl0, HAL_LL_TIM_COUNTER_DIRECTION );

    // Get current prescaler.
    prescaler_value = _hal_ll_tim_get_clock_speed( map->base ) / map->freq_hz;

    // This should not be the case. ck_psc should not be greater than 65535, which is max value.
    if( prescaler_value > UINT16_MAX ) {
        // In case of duty period being greater than 65535 set ck_psc to max value.
        prescaler_value = UINT16_MAX - 1; // Because of ( ck_psc / UINT16_MAX + 1 ) ), has to be minus 1.
    }else if ( prescaler_value < 1 ) {
        prescaler_value = 1;
    }

    // Reset prescale value.
    hal_ll_hw_reg->timer_psc = 0;

    // Set auto-reload value.
    hal_ll_hw_reg->timer_car = prescaler_value;

    map->max_period = (uint16_t)prescaler_value;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    // Enable specific clock module.
    _hal_ll_tim_set_clock( map->base, true );

    // Configure alternate function for pin which is going to be used for PWM module.
    _hal_ll_tim_alternate_functions_set_state( map, true );

    // Finally, write user-defined settings into hardware registers.
    _hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
