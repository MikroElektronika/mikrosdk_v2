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
 * @brief TIMER HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_tim.h"
#include "hal_ll_gpio.h"
#include "hal_ll_tim_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macros for getting module specific index. */
#define HAL_LL_TIM_8_BIT_MODULE_0 (0)
#define HAL_LL_TIM_8_BIT_MODULE_2 (2)

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((hal_ll_tim_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

/*!< @brief Helper macros for getting module specific prescaler register bit values. */
#define HAL_LL_TIM_PRESCALER_REG_VALUE_1 (1)
#define HAL_LL_TIM_PRESCALER_REG_VALUE_5 (5)
#define HAL_LL_TIM_PRESCALER_REG_VALUE_7 (7)
#define HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT (1)

/*!< @brief Helper macro for stopping a timer module. */
#define HAL_LL_TIM_8_BIT_TIMER_STOPPED (0x07)
#define HAL_LL_TIM_16_BIT_TIMER_STOPPED (0x30)

/*!< @brief Helper mask macros. */
#define HAL_LL_TIM_8_BIT_MASK (0xFF)
#define HAL_LL_TIM_8_BIT_SHIFT (8)
#define HAL_LL_TIM_FORCE_OUTPUT_COMPARE_MATCH_BIT (7)

/*!< @brief Helper macros for determining duty cycle ranges. */
#define HAL_LL_TIM_DUTY_RATIO_MAX (1.0)
#define HAL_LL_TIM_DUTY_RATIO_MIN (0.0)

/*!< @brief Helper macros for getting appropriate PWM resolution. */
#define HAL_LL_TIM_8_BIT_RESOLUTION (255)
#define HAL_LL_TIM_8_BIT_RESOLUTION_MASK (256)
#define HAL_LL_TIM_10_BIT_RESOLUTION (1024)
#define HAL_LL_TIM_10_BIT_PWM_RESOLUTION_MASK (0x03)

/*!< @brief Helper macros for applying non-inverting PWM mode. */
#define HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_0 (4)
#define HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_1 (5)
#define HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_2 (7)

/*!< @brief Helper macros for applying Fast PWM 10-bit resolution mode. */
#define HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_0 (0)
#define HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_1 (1)
#define HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_2 (3)
#define HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_3 (4)

/*!< @brief Helper macros for applying Fast PWM 8-bit resolution mode. */
#define HAL_LL_TIM_FAST_PWM_8_BIT_RESOLUTION_BIT_0 (6)
#define HAL_LL_TIM_FAST_PWM_8_BIT_RESOLUTION_BIT_1 (3)

/*!< @brief Helper macros for disconnecting PWM driver units. */
#define HAL_LL_TIM_DISCONNECT_PWM_UNIT_A (0xC0)
#define HAL_LL_TIM_DISCONNECT_PWM_UNIT_B (0x30)

/*!< @brief Helper macro for getting current MCU clock value (in Hertz). */
#define _fosc (Get_Fosc_kHz()*1000)
// -------------------------------------------------------------- PRIVATE TYPES
typedef struct {
    /*!< @brief 8-bit Timer/Counter register specifics. */
    hal_ll_base_addr_t pwm_tccrxa_reg_addr; // 8/16-bit Timer/Counter Control register A.
    hal_ll_base_addr_t pwm_tcntx_reg_addr; // Timer/Counter register.
    hal_ll_base_addr_t pwm_ocrxa_reg_addr; // Output Compare register A.
    /*!< @brief 16-bit Timer/Counter register specifics. */
    hal_ll_base_addr_t pwm_tccrxb_reg_addr; // Timer/Counter Control register B.
    hal_ll_base_addr_t pwm_tcntxh_reg_addr; // Timer/Counter High register.
    hal_ll_base_addr_t pwm_tcntxl_reg_addr; // Timer/Counter Low register.
    hal_ll_base_addr_t pwm_ocrxah_reg_addr; // Output Compare register A High.
    hal_ll_base_addr_t pwm_ocrxal_reg_addr; // Output Compare register A Low.
    hal_ll_base_addr_t pwm_ocrxbh_reg_addr; // Output Compare register B High.
    hal_ll_base_addr_t pwm_ocrxbl_reg_addr; // Output Compare register B Low.
} hal_ll_tim_base_handle_t;

/*!< @brief TIM hw specific pointers to functions. */
typedef struct {
    void ( *mapped_function_signal_start )( hal_ll_tim_base_handle_t *, uint8_t );
    void ( *mapped_function_signal_stop )( hal_ll_tim_base_handle_t * );
    void ( *mapped_function_set_duty )( hal_ll_tim_base_handle_t *, float );
    void ( *mapped_function_set_prescaler )( hal_ll_tim_base_handle_t * );
    void ( *mapped_function_hw_init_pwm_mode )( hal_ll_tim_base_handle_t * );
} hal_ll_tim_functions;

/*!< @brief TIM hw specific structure */
typedef struct {
    hal_ll_tim_base_handle_t *base;
    hal_ll_pin_name_t pin;
    uint32_t max_period;
    uint32_t freq_hz;
    uint8_t module_index;
    uint8_t clock_divider;
    uint8_t channel;
    hal_ll_tim_functions mapped_functions;
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hw specific error values */
typedef enum {
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief PWM ( CCP ) array */
static hal_ll_tim_base_handle_t tim_ll_reg_offsets[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef TIM_MODULE_0
    { HAL_LL_TIM0_TCCR0A_REG_ADDRESS, HAL_LL_TIM0_TCNT0_REG_ADDRESS, HAL_LL_TIM0_OCR0A_REG_ADDRESS },
    #endif
    #ifdef TIM_MODULE_1
    { HAL_LL_TIM1_TCCR1A_REG_ADDRESS, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_TIM1_TCCR1B_REG_ADDRESS,
      HAL_LL_TIM1_TCNT1H_REG_ADDRESS, HAL_LL_TIM1_TCNT1L_REG_ADDRESS, HAL_LL_TIM1_OCR1AH_REG_ADDRESS,
      HAL_LL_TIM1_OCR1AL_REG_ADDRESS, HAL_LL_TIM1_OCR1BH_REG_ADDRESS, HAL_LL_TIM1_OCR1BL_REG_ADDRESS },
    #endif
    #ifdef TIM_MODULE_2
    { HAL_LL_TIM2_TCCR2A_REG_ADDRESS, HAL_LL_TIM2_TCNT2_REG_ADDRESS, HAL_LL_TIM2_OCR2A_REG_ADDRESS },
    #endif
    #ifdef TIM_MODULE_3
    { HAL_LL_TIM3_TCCR3A_REG_ADDRESS, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_TIM3_TCCR3B_REG_ADDRESS,
      HAL_LL_TIM3_TCNT3H_REG_ADDRESS, HAL_LL_TIM3_TCNT3L_REG_ADDRESS, HAL_LL_TIM3_OCR3AH_REG_ADDRESS,
      HAL_LL_TIM3_OCR3AL_REG_ADDRESS, HAL_LL_TIM3_OCR3BH_REG_ADDRESS, HAL_LL_TIM3_OCR3BL_REG_ADDRESS },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
      HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef TIM_MODULE_0
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_0) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT, HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif
    #ifdef TIM_MODULE_1
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_1) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT, HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif
    #ifdef TIM_MODULE_2
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_2) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT, HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif
    #ifdef TIM_MODULE_3
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_3) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT, HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    { &tim_ll_reg_offsets[ TIM_MODULE_COUNT ], HAL_LL_PIN_NC, 0, 0, HAL_LL_MODULE_ERROR, HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT, HAL_LL_TIM_CH_DEFAULT, NULL }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief Get local hardware specific map.
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
  * @brief Full TIM module initialization procedure.
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
 * @brief Maps new-found module specific values.
 *
 * Maps pin names and PPS function values for
 * TIM pin.
 *
 * @param[in] module_index TIM HW module index -- 0,1,2...
 * @param[in] index Array with TIM pin map index values.
 *
 * @return  None
 */
static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief Check if pin is adequate.
  *
  * Checks tim pin the user has passed with pre-defined
  * pin in tim map.
  *
  * @param[in] pin - TIM pre-defined pin name.
  * @param[in] *index Array with TIM pin map index values.
  * @param[in] *handle_map Structure with info about available TIM modules.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

/**
 * @brief Set GPIO state.
 *
 * Sets adequate register
 * values for adequate functionality.
 *
 * @param[in] *map - Object specific context handler.
 * @param[in] hal_ll_state - init or deinit
 *
 * @return  none.
 */
static void _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief Map adequate function addresses.
  *
  * Function maps adequate function addresses.
  *
  * @param[in] hal_ll_module_id - Module index.
  *
  * @return none
  *
  */
static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t channel );

/**
  * @brief Timer/Counter 0 and Timer/Counter 2 start function.
  *
  * Function starts generating PWM signal on Timer/Counter 0 and Timer/Counter 2 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @param[in] clock_divider - Clock divider value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_0_and_timer_2_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t clock_divider );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 start function (channel A).
  *
  * Function starts generating PWM signal on Timer/Counter 1 and Timer/Counter 3 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @param[in] clock_divider - Clock divider value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_start_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t clock_divider );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 start function (channel B).
  *
  * Function starts generating PWM signal on Timer/Counter 1 and Timer/Counter 3 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @param[in] clock_divider - Clock divider value.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_start_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t clock_divider );

/**
  * @brief Timer/Counter 0 and Timer/Counter 2 start function.
  *
  * Function stops generating PWM signal on Timer/Counter 0 and Timer/Counter 2 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_0_and_timer_2_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 stop function (channel A).
  *
  * Function stops generating PWM signal on Timer/Counter 1 and Timer/Counter 3 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_stop_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 stop function (channel B).
  *
  * Function stops generating PWM signal on Timer/Counter 1 and Timer/Counter 3 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_stop_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter 0 and Timer/Counter 2 set duty function.
  *
  * Function configures duty cycle on Timer/Counter 0 and Timer/Counter 2 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] user_defined_duty - Defined PWM duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_0_and_timer_2_set_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg, float user_defined_duty );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 set duty function (channel A).
  *
  * Function configures duty cycle on Timer/Counter 1 and Timer/Counter 3 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] user_defined_duty - Defined PWM duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_set_duty_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg, float user_defined_duty );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 set duty function (channel B).
  *
  * Function configures duty cycle on Timer/Counter 1 and Timer/Counter 3 PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] user_defined_duty - Defined PWM duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_set_duty_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg, float user_defined_duty );

/**
  * @brief Timer/Counter 0 set prescaler function.
  *
  * Function configures prescaler value on Timer/Counter 0 module.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_0_set_prescaler( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter 2 set prescaler function.
  *
  * Function configures prescaler value on Timer/Counter 2 module.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_2_set_prescaler( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter 1 and Timer/Counter 3 set prescaler function.
  *
  * Function configures prescaler value on Timer/Counter 1 and Timer/Counter 3 modules.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_set_prescaler( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Initialize Timer/Counter 0 and Timer/Counter 2 on hardware level (channel B).
  *
  * Initializes Timer/Counter 0 and/or Timer/Counter 2 modules on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_0_and_timer_2_hw_init_pwm_mode( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Initialize Timer/Counter 1 and Timer/Counter 3 on hardware level.
  *
  * Initializes Timer/Counter 1 and/or Timer/Counter 3 modules on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_1_and_timer_3_hw_init_pwm_mode( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    uint8_t pin_check_result;
    uint8_t index;

    if (  HAL_LL_PIN_NC == ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( ( hal_ll_tim_hw_specifics_map[ pin_check_result ].pin != pin ) ) {
        _hal_ll_tim_map_pin( pin_check_result, index );

        handle_map[ pin_check_result ]->init_ll_state = false;

        hal_ll_module_state[ pin_check_result ].init_ll_state = false;

        /*!< @brief Variable holding last set clock divider for given module. */
        hal_ll_tim_hw_specifics_map->clock_divider = HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ]->hal_ll_tim_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

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
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    // Configure PWM prescaler value (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_set_prescaler )
    ( hal_ll_tim_hw_specifics_map_local->base );

    low_level_handle->init_ll_state = true;

    return hal_ll_tim_hw_specifics_map_local->max_period;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( low_level_handle->init_ll_state == false ) {
        _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );
        low_level_handle->init_ll_state = true;
    }

    // Set appropriate PWM duty cycle (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_set_duty )
    ( hal_ll_tim_hw_specifics_map_local->base, duty_ratio );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    // Enable PWM driver circuit, non-inverting submode (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_signal_start )
    ( hal_ll_tim_hw_specifics_map_local->base, hal_ll_tim_hw_specifics_map_local->clock_divider );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    // Disconnect PWM driver circuit (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_signal_stop )
    ( hal_ll_tim_hw_specifics_map_local->base );

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if( low_level_handle->hal_ll_tim_handle != NULL ) {

        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;
        low_level_handle->init_ll_state = false;

        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;
        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->clock_divider = HAL_LL_TIM_PRESCALER_REG_VALUE_DEFAULT;
        hal_ll_tim_hw_specifics_map_local->channel = HAL_LL_TIM_CH_DEFAULT;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map ) {
    uint8_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    static uint16_t map_size = ( sizeof( _tim_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    // Check if the selected pin is valid.
    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( _tim_map[ pin_num ].pin == pin ) {
            // Get module number
            hal_ll_module_id = _tim_map[ pin_num ].module_index;
            map_pointer_functions( hal_ll_module_id, _tim_map[ pin_num ].channel );
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
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base ) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t pin;
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    if ( hal_ll_state ) {
        hal_ll_gpio_configure_pin( &pin, map->pin, HAL_LL_GPIO_DIGITAL_OUTPUT );
    } else {
        hal_ll_gpio_configure_pin( &pin, map->pin, HAL_LL_GPIO_DIGITAL_INPUT );
    }
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Memorize PWM pin.
    hal_ll_tim_hw_specifics_map[ module_index ].pin = _tim_map[ index ].pin;

    // Memorize PWM pin channel.
    hal_ll_tim_hw_specifics_map[ module_index ].channel = _tim_map[ index ].channel;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    // Configure PWM pin.
    _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );

    // Hardware initialization of a Timer/Counter (PWM) module (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_hw_init_pwm_mode )
    ( hal_ll_tim_hw_specifics_map_local->base );
}

// ---------------------------------------------------- STATIC POINTER FUNCTIONS
static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t channel ) {
    if ( ( HAL_LL_TIM_8_BIT_MODULE_0 == hal_ll_module_id ) || ( HAL_LL_TIM_8_BIT_MODULE_2 == hal_ll_module_id ) ) {
        hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_0_and_timer_2_start;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_0_and_timer_2_stop;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_0_and_timer_2_set_duty;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_0_and_timer_2_hw_init_pwm_mode;

        if ( HAL_LL_TIM_8_BIT_MODULE_0 == hal_ll_module_id ) {
            hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_set_prescaler = &ptr_function_timer_0_set_prescaler;
        } else {
            hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_set_prescaler = &ptr_function_timer_2_set_prescaler;
        }
    } else {
        switch ( channel ) {
            case ( HAL_LL_TIM_CH_A ):
                hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_1_and_timer_3_start_ch_a;
                hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_1_and_timer_3_stop_ch_a;
                hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_1_and_timer_3_set_duty_ch_a;
                break;
            case ( HAL_LL_TIM_CH_B ):
                hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_1_and_timer_3_start_ch_b;
                hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_1_and_timer_3_stop_ch_b;
                hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_1_and_timer_3_set_duty_ch_b;
                break;
        }

        hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_1_and_timer_3_hw_init_pwm_mode;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id]->mapped_functions.mapped_function_set_prescaler = &ptr_function_timer_1_and_timer_3_set_prescaler;
    }
}

static inline void ptr_function_timer_0_and_timer_2_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t clock_divider ) {
    // PWM driver enabled, non-inverting submode.
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_0 );
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_1 );
    set_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, clock_divider );
}

static inline void ptr_function_timer_1_and_timer_3_start_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t clock_divider ){
    // PWM driver enabled, non-inverting submode.
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_2 );
    set_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, clock_divider );
}

static inline void ptr_function_timer_1_and_timer_3_start_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint8_t clock_divider ){
    // PWM driver enabled, non-inverting submode.
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_1 );
    set_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, clock_divider );
}

static inline void ptr_function_timer_0_and_timer_2_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    // PWM driver disconnected.
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_0 );
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_1 );

    // Timer/Counter stopped (no clock source).
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_8_BIT_TIMER_STOPPED );
}

static inline void ptr_function_timer_1_and_timer_3_stop_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg ){
    // PWM driver disconnected for Unit A, TCCR1A<7:6>
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_DISCONNECT_PWM_UNIT_A );

    // No clock source (Timer/Counter stopped), TCCR1B<2:0>
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxb_reg_addr, HAL_LL_TIM_16_BIT_TIMER_STOPPED );
}

static inline void ptr_function_timer_1_and_timer_3_stop_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg ){
    // PWM driver disconnected for Unit B, TCCR1A<5:4>
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_DISCONNECT_PWM_UNIT_B );

    // No clock source (Timer/Counter stopped), TCCR1B<2:0>
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxb_reg_addr, HAL_LL_TIM_16_BIT_TIMER_STOPPED );
}

static inline void ptr_function_timer_0_and_timer_2_set_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg, float user_defined_duty ) {
    if ( user_defined_duty >= HAL_LL_TIM_DUTY_RATIO_MAX ) {
        write_reg( hal_ll_hw_reg->pwm_ocrxa_reg_addr, HAL_LL_TIM_8_BIT_MASK );
    } else if ( user_defined_duty <= HAL_LL_TIM_DUTY_RATIO_MIN ) {
        clear_reg( hal_ll_hw_reg->pwm_ocrxa_reg_addr );
    } else {
        write_reg( hal_ll_hw_reg->pwm_ocrxa_reg_addr, (uint8_t)( user_defined_duty * HAL_LL_TIM_8_BIT_RESOLUTION ) );
    }
}

static inline void ptr_function_timer_1_and_timer_3_set_duty_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg, float user_defined_duty ){
    if ( user_defined_duty >= HAL_LL_TIM_DUTY_RATIO_MAX ) {
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );
        write_reg( hal_ll_hw_reg->pwm_ocrxah_reg_addr, HAL_LL_TIM_10_BIT_PWM_RESOLUTION_MASK );
        write_reg( hal_ll_hw_reg->pwm_ocrxal_reg_addr, HAL_LL_TIM_8_BIT_MASK );
    } else if ( user_defined_duty <= HAL_LL_TIM_DUTY_RATIO_MIN ) {
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, false );
        clear_reg( hal_ll_hw_reg->pwm_ocrxah_reg_addr );
        clear_reg( hal_ll_hw_reg->pwm_ocrxal_reg_addr );
    } else {
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );
        clear_reg( hal_ll_hw_reg->pwm_tcntxh_reg_addr );
        clear_reg( hal_ll_hw_reg->pwm_tcntxl_reg_addr );
        uint16_t test_var = user_defined_duty * HAL_LL_TIM_10_BIT_RESOLUTION;

        write_reg( hal_ll_hw_reg->pwm_ocrxah_reg_addr, test_var >> HAL_LL_TIM_8_BIT_SHIFT );
        write_reg( hal_ll_hw_reg->pwm_ocrxal_reg_addr, (uint8_t)test_var );
    }
}

static inline void ptr_function_timer_1_and_timer_3_set_duty_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg, float user_defined_duty ){
    if ( user_defined_duty >= HAL_LL_TIM_DUTY_RATIO_MAX ) {
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );
        write_reg( hal_ll_hw_reg->pwm_ocrxbh_reg_addr, HAL_LL_TIM_10_BIT_PWM_RESOLUTION_MASK );
        write_reg( hal_ll_hw_reg->pwm_ocrxbl_reg_addr, HAL_LL_TIM_8_BIT_MASK );
    } else if ( user_defined_duty <= HAL_LL_TIM_DUTY_RATIO_MIN ) {
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, false );
        clear_reg( hal_ll_hw_reg->pwm_ocrxbh_reg_addr );
        clear_reg( hal_ll_hw_reg->pwm_ocrxbl_reg_addr );
    } else {
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );
        clear_reg( hal_ll_hw_reg->pwm_tcntxh_reg_addr );
        clear_reg( hal_ll_hw_reg->pwm_tcntxl_reg_addr );
        uint16_t test_var = user_defined_duty * HAL_LL_TIM_10_BIT_RESOLUTION;

        write_reg( hal_ll_hw_reg->pwm_ocrxbh_reg_addr, test_var >> HAL_LL_TIM_8_BIT_SHIFT );
        write_reg( hal_ll_hw_reg->pwm_ocrxbl_reg_addr, (uint8_t)test_var );
    }
}

static inline void ptr_function_timer_0_set_prescaler( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    uint8_t local_loop_counter = 0;
    uint8_t prescaler_value = 0;

    // Prescaler divider array for Timer/Counter modules 0 and 1.
    const volatile uint8_t prescaler_divider_array_0[HAL_LL_TIM_PRESCALER_REG_VALUE_5] = { 1, 8, 64, 256, 1024 };

    // By default, set minimal PWM frequency available.
    prescaler_value = HAL_LL_TIM_PRESCALER_REG_VALUE_5;
    hal_ll_tim_hw_specifics_map_local->max_period = ( _fosc / ( ( prescaler_divider_array_0[sizeof(prescaler_divider_array_0) - 1] ) * HAL_LL_TIM_8_BIT_RESOLUTION_MASK ) );

    // Check if better PWM frequency can be achieved.
    for ( local_loop_counter = 0; local_loop_counter < sizeof(prescaler_divider_array_0); local_loop_counter++ ) {
        if ( hal_ll_tim_hw_specifics_map_local->freq_hz >= ( _fosc / ( prescaler_divider_array_0[local_loop_counter] * HAL_LL_TIM_8_BIT_RESOLUTION_MASK ) ) ) {
            prescaler_value = local_loop_counter + 1;
            hal_ll_tim_hw_specifics_map_local->max_period = (_fosc / ( prescaler_divider_array_0[local_loop_counter] * HAL_LL_TIM_8_BIT_RESOLUTION_MASK ) );
            break;
        }
    }

    // Timer/Counter stopped (no clock source).
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_8_BIT_TIMER_STOPPED );

    // Set appropriate prescaler value.
    set_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, prescaler_value );

    /*!< @brief Variable holding last set clock divider for given module. */
    hal_ll_tim_hw_specifics_map_local->clock_divider = prescaler_value;
}

static inline void ptr_function_timer_2_set_prescaler( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    uint8_t local_loop_counter = 0;
    uint8_t prescaler_value = 0;

    // Prescaler divider array for Timer/Counter module 2.
    const volatile uint8_t prescaler_divider_array_1[HAL_LL_TIM_PRESCALER_REG_VALUE_7] = { 1, 8, 32, 64, 128, 256, 1024 };

    // By default, set minimal PWM frequency available.
    prescaler_value = HAL_LL_TIM_PRESCALER_REG_VALUE_7;
    hal_ll_tim_hw_specifics_map_local->max_period = ( _fosc / ( prescaler_divider_array_1[sizeof(prescaler_divider_array_1) - 1] * HAL_LL_TIM_8_BIT_RESOLUTION_MASK ) );

    // Check if better PWM frequency can be achieved.
    for ( local_loop_counter = 0; local_loop_counter < sizeof(prescaler_divider_array_1); local_loop_counter++ ) {
        if ( hal_ll_tim_hw_specifics_map_local->freq_hz >= ( _fosc / ( prescaler_divider_array_1[local_loop_counter] * HAL_LL_TIM_8_BIT_RESOLUTION_MASK ) ) ) {
            prescaler_value = local_loop_counter + 1;
            hal_ll_tim_hw_specifics_map_local->max_period = (_fosc / ( prescaler_divider_array_1[local_loop_counter] * HAL_LL_TIM_8_BIT_RESOLUTION_MASK ) );
            break;
        }
    }
    // Timer/Counter stopped (no clock source).
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_8_BIT_TIMER_STOPPED );

    // Set appropriate prescaler value.
    set_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, prescaler_value );

    /*!< @brief Variable holding last set clock divider for given module. */
    hal_ll_tim_hw_specifics_map_local->clock_divider = prescaler_value;
}

static inline void ptr_function_timer_1_and_timer_3_set_prescaler( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    uint8_t local_loop_counter = 0;
    uint8_t prescaler_value = 0;

    // Prescaler divider array for Timer/Counter modules 0 and 1.
    const volatile uint8_t prescaler_divider_array_0[HAL_LL_TIM_PRESCALER_REG_VALUE_5] = { 1, 8, 64, 256, 1024 };

    // By default, set max PWM frequency available.
    prescaler_value = HAL_LL_TIM_PRESCALER_REG_VALUE_1;
    hal_ll_tim_hw_specifics_map_local->max_period = ( _fosc / ( prescaler_divider_array_0[sizeof(prescaler_divider_array_0) - 1] * HAL_LL_TIM_10_BIT_RESOLUTION ) );

    // Check if better PWM frequency can be achieved.
    for ( local_loop_counter = 0; local_loop_counter < sizeof(prescaler_divider_array_0); local_loop_counter++ ) {
        if ( hal_ll_tim_hw_specifics_map_local->freq_hz >= _fosc / ( ( prescaler_divider_array_0[local_loop_counter] ) * HAL_LL_TIM_10_BIT_RESOLUTION ) ) {
            prescaler_value = local_loop_counter + 1;
            hal_ll_tim_hw_specifics_map_local->max_period = _fosc / ( ( prescaler_divider_array_0[local_loop_counter] ) * HAL_LL_TIM_10_BIT_RESOLUTION );
            break;
        }
    }

    // Set appropriate prescaler value.
    set_reg_bits( hal_ll_hw_reg->pwm_tccrxb_reg_addr, prescaler_value );

    /*!< @brief Variable holding last set clock divider for given module. */
    hal_ll_tim_hw_specifics_map_local->clock_divider = prescaler_value;
}

static inline void ptr_function_timer_0_and_timer_2_hw_init_pwm_mode( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    // Do not force output compare match.
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_FORCE_OUTPUT_COMPARE_MATCH_BIT );

    // Set Waveform Generation Mode to Fast PWM.
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_FAST_PWM_8_BIT_RESOLUTION_BIT_0 );
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_FAST_PWM_8_BIT_RESOLUTION_BIT_1 );

    // PWM driver disconnected.
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_0 );
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_PWM_NON_INVERTING_MODE_BIT_1 );

    // Timer/Counter stopped (no clock source).
    clear_reg_bits( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_8_BIT_TIMER_STOPPED );
}

static inline void ptr_function_timer_1_and_timer_3_hw_init_pwm_mode( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    // Set Waveform Generation Mode to Fast PWM, 10-bit, for controlling the duty.
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_0 );
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxa_reg_addr, HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_1 );
    set_reg_bit( hal_ll_hw_reg->pwm_tccrxb_reg_addr, HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_2 );
    clear_reg_bit( hal_ll_hw_reg->pwm_tccrxb_reg_addr, HAL_LL_TIM_FAST_PWM_10_BIT_RESOLUTION_BIT_3 );
}

// ------------------------------------------------------------------------- END
