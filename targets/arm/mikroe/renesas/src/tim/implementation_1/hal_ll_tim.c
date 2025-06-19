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

#include "hal_ll_tim.h"
#include "hal_ll_gpio.h"
#include "hal_ll_tim_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ] = {(handle_t *)NULL, (handle_t *)NULL, false};

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


// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM hw specific error values. */
typedef enum {
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

/*!< @brief TIM hw specific config structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    uint8_t pin_parity;
    uint32_t af;
} hal_ll_tim_t;

/*!< @brief TIM hw specific pin parity pointers to functions. */
typedef struct {
    void ( *mapped_function_duty )( struct hal_ll_tim_base_handle_t *, uint32_t, uint32_t );
    void ( *mapped_function_signal_start )( struct hal_ll_tim_base_handle_t * );
    void ( *mapped_function_signal_stop )( struct hal_ll_tim_base_handle_t * );
    void ( *mapped_function_period )( struct hal_ll_tim_base_handle_t *, uint32_t );
    void ( *mapped_function_hw_init_control )( struct hal_ll_tim_base_handle_t * );
    void ( *mapped_function_hw_init_pwm_mode )( struct hal_ll_tim_base_handle_t * );
} hal_ll_tim_functions;

/*!< @brief TIM hw specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_tim_t config;
    uint32_t max_period;
    uint32_t freq_hz;
    hal_ll_pin_name_t module_index;
    /* NOTE Added pointer function structure.
     * Chips have two CCP's.
     */
    hal_ll_tim_functions mapped_functions;
} hal_ll_tim_hw_specifics_map_t;

typedef struct {

} hal_ll_tim_base_handle_t;

// ------------------------------------------------------------------ VARIABLES

/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef TIM_MODULE_0
    {HAL_LL_TIM0_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_0},
    #endif
    #ifdef TIM_MODULE_1
    {HAL_LL_TIM1_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_1},
    #endif
    #ifdef TIM_MODULE_2
    {HAL_LL_TIM2_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_2},
    #endif
    #ifdef TIM_MODULE_3
    {HAL_LL_TIM3_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_3},
    #endif
    #ifdef TIM_MODULE_4
    {HAL_LL_TIM4_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_4},
    #endif
    #ifdef TIM_MODULE_5
    {HAL_LL_TIM5_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_5},
    #endif
    #ifdef TIM_MODULE_6
    {HAL_LL_TIM6_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_6},
    #endif
    #ifdef TIM_MODULE_7
    {HAL_LL_TIM7_BASE_ADDR, {HAL_LL_PIN_NC, HAL_LL_TIM_CCP_0, HAL_LL_PIN_NC}, 0, 0, TIM_MODULE_7},
    #endif

    {HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, NULL, HAL_LL_PIN_NC}, 0, 0, HAL_LL_PIN_NC}
};

/*!< @brief Global handle variables used in functions. */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Sets TIM pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if TIM is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init.
  * @return none
  *
  */
static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * TIM pin.
 *
 * @param[in]   module_index - TIM HW module index -- 0,1,2...
 * @param[in]   index  - Index from the TIM pin map.
 *
 * @return  None
 */
static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief  Check if pin is adequate.
  *
  * Checks tim pin the user has passed with pre-defined
  * pin in tim map.
  *
  * @param[in]  pin - TIM pre-defined pin name.
  * @param[out] index - Output parameter which is used to return pin index within the PIN map.
  * @param[out] *handle_map - TIMER HAL low lever handle register.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_tim_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_tim_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Full TIM module initialization procedure.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return none
  *
  */
static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map );

/**
 * @brief  Sets the TIM PWM period register and prescaler values.
 *
 * Using max_period from the map parameter it calculates values
 * for the period and prescaler registers and modifies them.
 *
 * @param[in]   *map - Object specific context handler.
 *
 * @return  None
 */
static void _hal_ll_tim_set_period( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Enable TIM module gate clock.
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  *
  * @return None
  */
static void _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_t* map, bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 0 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim0_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 1 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim1_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 2 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim2_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 3 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim3_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 4 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim4_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 5 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim5_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 6 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim6_set_clock( bool hal_ll_state );

/**
  * @brief  Enables or disables TIM module 7 clock.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return none
  */
static void _hal_ll_tim7_set_clock( bool hal_ll_state );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return none
  *
  */
static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map );

/**
  * @brief  Map adequate function addresses.
  *
  * Function maps adequate function addresses based on]
  * pin parity.
  *
  * @param[in]  hal_ll_module_id - Module index.
  * @param[in]  pin_parity - CCP value (0/1).
  *
  * @return none
  *
  */
static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t pin_parity );

/**
  * @brief  CCP0 duty function.
  *
  * Function sets duty value for CCP0 pins.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  * @param[in]  duty_cycle_timeout - Duty cycle timeout value.
  * @param[in]  max_period - Maximum period value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_a_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                              uint32_t duty_cycle_timeout,
                                              uint32_t max_period );

/**
  * @brief  CCP1 duty function.
  *
  * Function sets duty value for CCP1 pins.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  * @param[in]  duty_cycle_timeout - Duty cycle timeout value.
  * @param[in]  max_period - Maximum period value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_b_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                              uint32_t duty_cycle_timeout,
                                              uint32_t max_period );

/**
  * @brief  CCP0 start function.
  *
  * Function starts generating PWM signal on CCP0 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_a_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP1 start function.
  *
  * Function starts generating PWM signal on CCP1 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_b_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP0 stop function.
  *
  * Function stops PWM signal generation on CCP0 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_a_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP1 stop function.
  *
  * Function stops PWM signal generation on CCP1 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_b_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP0 period function.
  *
  * Function sets adequate period level on CCP0 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  * @param[in]  max_period - Maximum period value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_a_period( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                                uint32_t max_period );

/**
  * @brief  CCP1 period function.
  *
  * Function sets adequate period level on CCP1 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  * @param[in]  max_period - Maximum period value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_b_period( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                                uint32_t max_period );

/**
  * @brief  CCP0 control init function.
  *
  * Function sets adequate values in control registers
  * for CCP0 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_a_hw_init_control( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP1 control init function.
  *
  * Function sets adequate values in control registers
  * for CCP1 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_b_hw_init_control( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP0 timer init function.
  *
  * Function sets adequate values in timer registers
  * for CCP0 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_a_pwm_mode_set( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief  CCP1 timer init function.
  *
  * Function sets adequate values in timer registers
  * for CCP1 pin.
  *
  * @param[in]  *hal_ll_hw_reg - Timer base structure.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_b_pwm_mode_set( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {
    uint8_t index;
    uint16_t pin_check_result;

    if ( ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( hal_ll_tim_hw_specifics_map[ pin_check_result].config.pin != pin ) {
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
    return 0;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    uint32_t duty_cycle_timeout;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( low_level_handle->init_ll_state == false ) {
        hal_ll_tim_start( handle );
        low_level_handle->init_ll_state = true;
    }

    duty_cycle_timeout = hal_ll_tim_hw_specifics_map_local->max_period  * ( 1.0 - duty_ratio );

    (hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_duty)
    (hal_ll_tim_hw_specifics_map_local->base, duty_cycle_timeout, hal_ll_tim_hw_specifics_map_local->max_period);

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    (hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_signal_start)
    (hal_ll_tim_hw_specifics_map_local->base);

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    (hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_signal_stop)
    (hal_ll_tim_hw_specifics_map_local->base);

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {

}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

}

static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map ) {
    return 0;
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
}

static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    return 0;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

}

static void _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_t* map, bool hal_ll_state ) {

}

static void _hal_ll_tim0_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim1_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim2_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim3_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim4_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim5_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim6_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim7_set_clock( bool hal_ll_state ) {

}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {

}

static void _hal_ll_tim_set_period( hal_ll_tim_hw_specifics_map_t *map ) {

}

// ---------------------------------------------------- STATIC POINTER FUNCTIONS

static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t pin_parity ) {

}

static inline void ptr_function_timer_a_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                              uint32_t duty_cycle_timeout,
                                              uint32_t max_period ) {

}

static inline void ptr_function_timer_b_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                              uint32_t duty_cycle_timeout,
                                              uint32_t max_period ) {

}

static inline void ptr_function_timer_a_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_b_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_a_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_b_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_a_period( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                                uint32_t max_period ) {

}

static inline void ptr_function_timer_b_period( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                                uint32_t max_period ) {

}

static inline void ptr_function_timer_a_hw_init_control( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_b_hw_init_control( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_a_pwm_mode_set( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

static inline void ptr_function_timer_b_pwm_mode_set( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {

}

// ------------------------------------------------------------------------- END
