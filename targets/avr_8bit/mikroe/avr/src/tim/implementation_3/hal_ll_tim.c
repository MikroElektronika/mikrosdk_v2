/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @brief TIMER HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_tim.h"
#include "hal_ll_gpio.h"
#include "hal_ll_tim_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ] = { (handle_t *)NULL, (handle_t *)NULL, false };

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

/*!< @brief Helper macro for TIM module sync time. */
#define hal_ll_tim_wait_for_sync(_hal_sync_val) while( _hal_sync_val-- ){asm nop;}

/*!< @brief Helper macros for setting or clearing th Wave Generator's output compare value. */
#define HAL_LL_TIM_CMPA_BIT (0)
#define HAL_LL_TIM_CMPB_BIT (1)
#define HAL_LL_TIM_CMPC_BIT (2)
#define HAL_LL_TIM_CMPD_BIT (3)

/*!< @brief Helper macro for selecting PWM clock. */
#define HAL_LL_TIM_NO_PRESCALER (0)

/*!< @brief Helper macro for configuring Waveform Generator for "Single-Slope PWM". */
#define HAL_LL_TIM_SET_SINGLE_SLOPE_PWM (0x3)

/*!< @brief Helper macro for clearing Waveform Generator. */
#define HAL_LL_TIM_RESET_WAFEFORM_GENERATOR (0x7)

/*!< @brief Helper macro for enabling PWM channels. */
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_A (4)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_A_ATXMEGA_E5_SERIES (0)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_B (5)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_B_ATXMEGA_E5_SERIES (2)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_C (6)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_C_ATXMEGA_E5_SERIES (4)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_D (7)
#define HAL_LL_TIM_OUTPUT_COMPARE_CH_D_ATXMEGA_E5_SERIES (6)

/*!< @brief Helper macro for configuring Timer/Counter (PWM) operation mode. */
#define HAL_LL_TIM_BYTE_MODE_NORMAL (0)

/*!< @brief Helper macro for retrieving MCU clock in Hz. */
#define _fosc (Get_Fosc_kHz()*1000)

// -------------------------------------------------------------- PRIVATE TYPES
typedef struct{
    uint16_t hal_ll_pwm_ctrla_reg_address;
    uint16_t hal_ll_pwm_ctrlb_reg_address;
    uint16_t hal_ll_pwm_ctrlc_reg_address;
    uint16_t hal_ll_pwm_ctrld_reg_address;
    uint16_t hal_ll_pwm_ctrle_reg_address;
    uint16_t hal_ll_pwm_ccabuf_reg_address;
    uint16_t hal_ll_pwm_ccbbuf_reg_address;
    uint16_t hal_ll_pwm_cccbuf_reg_address;
    uint16_t hal_ll_pwm_ccdbuf_reg_address;
    uint16_t hal_ll_pwm_perl_reg_address;
    uint16_t hal_ll_pwm_perh_reg_address;
} hal_ll_tim_base_handle_t;

/*!< @brief TIM hw specific pointers to functions. */
typedef struct {
    void ( *mapped_function_signal_start )( hal_ll_tim_base_handle_t * );
    void ( *mapped_function_signal_stop )( hal_ll_tim_base_handle_t * );
    void ( *mapped_function_hw_init_pwm_mode )( hal_ll_tim_base_handle_t * );
    void ( *mapped_function_set_duty )( hal_ll_tim_base_handle_t *, uint16_t );
} hal_ll_tim_functions;

/*!< @brief TIM hw specific structure */
typedef struct {
    hal_ll_tim_base_handle_t *base;
    hal_ll_pin_name_t pin;
    uint32_t max_period;
    uint32_t freq_hz;
    uint8_t module_index;
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
/*!< @brief PWM array */
static hal_ll_tim_base_handle_t tim_ll_reg_offsets[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef TIM_MODULE_0
    { HAL_LL_TIM0_CTRLA_REG_ADDRESS, HAL_LL_TIM0_CTRLB_REG_ADDRESS, HAL_LL_TIM0_CTRLC_REG_ADDRESS,
      HAL_LL_TIM0_CTRLD_REG_ADDRESS, HAL_LL_TIM0_CTRLE_REG_ADDRESS, HAL_LL_TIM0_CCABUF_REG_ADDRESS,
      HAL_LL_TIM0_CCBBUF_REG_ADDRESS, HAL_LL_TIM0_CCCBUF_REG_ADDRESS, HAL_LL_TIM0_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM0_PERL_REG_ADDRESS, HAL_LL_TIM0_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_1
    { HAL_LL_TIM1_CTRLA_REG_ADDRESS, HAL_LL_TIM1_CTRLB_REG_ADDRESS, HAL_LL_TIM1_CTRLC_REG_ADDRESS,
      HAL_LL_TIM1_CTRLD_REG_ADDRESS, HAL_LL_TIM1_CTRLE_REG_ADDRESS, HAL_LL_TIM1_CCABUF_REG_ADDRESS,
      HAL_LL_TIM1_CCBBUF_REG_ADDRESS, HAL_LL_TIM1_CCCBUF_REG_ADDRESS, HAL_LL_TIM1_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM1_PERL_REG_ADDRESS, HAL_LL_TIM1_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_2
    { HAL_LL_TIM2_CTRLA_REG_ADDRESS, HAL_LL_TIM2_CTRLB_REG_ADDRESS, HAL_LL_TIM2_CTRLC_REG_ADDRESS,
      HAL_LL_TIM2_CTRLD_REG_ADDRESS, HAL_LL_TIM2_CTRLE_REG_ADDRESS, HAL_LL_TIM2_CCABUF_REG_ADDRESS,
      HAL_LL_TIM2_CCBBUF_REG_ADDRESS, HAL_LL_TIM2_CCCBUF_REG_ADDRESS, HAL_LL_TIM2_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM2_PERL_REG_ADDRESS, HAL_LL_TIM2_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_3
    { HAL_LL_TIM3_CTRLA_REG_ADDRESS, HAL_LL_TIM3_CTRLB_REG_ADDRESS, HAL_LL_TIM3_CTRLC_REG_ADDRESS,
      HAL_LL_TIM3_CTRLD_REG_ADDRESS, HAL_LL_TIM3_CTRLE_REG_ADDRESS, HAL_LL_TIM3_CCABUF_REG_ADDRESS,
      HAL_LL_TIM3_CCBBUF_REG_ADDRESS, HAL_LL_TIM3_CCCBUF_REG_ADDRESS, HAL_LL_TIM3_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM3_PERL_REG_ADDRESS, HAL_LL_TIM3_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_4
    { HAL_LL_TIM4_CTRLA_REG_ADDRESS, HAL_LL_TIM4_CTRLB_REG_ADDRESS, HAL_LL_TIM4_CTRLC_REG_ADDRESS,
      HAL_LL_TIM4_CTRLD_REG_ADDRESS, HAL_LL_TIM4_CTRLE_REG_ADDRESS, HAL_LL_TIM4_CCABUF_REG_ADDRESS,
      HAL_LL_TIM4_CCBBUF_REG_ADDRESS, HAL_LL_TIM4_CCCBUF_REG_ADDRESS, HAL_LL_TIM4_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM4_PERL_REG_ADDRESS, HAL_LL_TIM4_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_5
    { HAL_LL_TIM5_CTRLA_REG_ADDRESS, HAL_LL_TIM5_CTRLB_REG_ADDRESS, HAL_LL_TIM5_CTRLC_REG_ADDRESS,
      HAL_LL_TIM5_CTRLD_REG_ADDRESS, HAL_LL_TIM5_CTRLE_REG_ADDRESS, HAL_LL_TIM5_CCABUF_REG_ADDRESS,
      HAL_LL_TIM5_CCBBUF_REG_ADDRESS, HAL_LL_TIM5_CCCBUF_REG_ADDRESS, HAL_LL_TIM5_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM5_PERL_REG_ADDRESS, HAL_LL_TIM5_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_6
    { HAL_LL_TIM6_CTRLA_REG_ADDRESS, HAL_LL_TIM6_CTRLB_REG_ADDRESS, HAL_LL_TIM6_CTRLC_REG_ADDRESS,
      HAL_LL_TIM6_CTRLD_REG_ADDRESS, HAL_LL_TIM6_CTRLE_REG_ADDRESS, HAL_LL_TIM6_CCABUF_REG_ADDRESS,
      HAL_LL_TIM6_CCBBUF_REG_ADDRESS, HAL_LL_TIM6_CCCBUF_REG_ADDRESS, HAL_LL_TIM6_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM6_PERL_REG_ADDRESS, HAL_LL_TIM6_PERH_REG_ADDRESS },
    #endif

    #ifdef TIM_MODULE_7
    { HAL_LL_TIM7_CTRLA_REG_ADDRESS, HAL_LL_TIM7_CTRLB_REG_ADDRESS, HAL_LL_TIM7_CTRLC_REG_ADDRESS,
      HAL_LL_TIM7_CTRLD_REG_ADDRESS, HAL_LL_TIM7_CTRLE_REG_ADDRESS, HAL_LL_TIM7_CCABUF_REG_ADDRESS,
      HAL_LL_TIM7_CCBBUF_REG_ADDRESS, HAL_LL_TIM7_CCCBUF_REG_ADDRESS, HAL_LL_TIM7_CCDBUF_REG_ADDRESS,
      HAL_LL_TIM7_PERL_REG_ADDRESS, HAL_LL_TIM7_PERH_REG_ADDRESS },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC,
      HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef TIM_MODULE_0
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_0) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_0), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_1
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_1) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_1), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_2
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_2) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_2), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_3
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_3) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_3), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_4
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_4) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_4), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_5
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_5) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_5), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_6
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_6) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_6), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    #ifdef TIM_MODULE_7
    { &tim_ll_reg_offsets[ hal_ll_tim_module_num(TIM_MODULE_7) ], HAL_LL_PIN_NC, 0, 0, hal_ll_tim_module_num(TIM_MODULE_7), HAL_LL_TIM_CH_DEFAULT, NULL },
    #endif

    { &tim_ll_reg_offsets[ TIM_MODULE_COUNT ], HAL_LL_PIN_NC, 0, 0, HAL_LL_MODULE_ERROR, HAL_LL_TIM_CH_DEFAULT, NULL }
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
  * @brief Initialize TIM module on hardware level.
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
 * @brief Maps new-found module specific values.
 *
 * Maps pin name and channel function values for TIM pin.
 *
 * @param[in] module_index TIM HW module index -- 0,1,2...
 * @param[in] index_list  Array with TIM pin map index values.
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
  * @param[in] *index_list - Array with TIM pin map index values.
  * @param[in] *handle_map - Local TIM handle list.
  * @return hal_ll_pin_name_t - Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

/**
 * @brief Set GPIO state.
 *
 * Sets adequate TRISx register
 * values for adequate functionality.
 *
 * @param[in] *map - Object specific context handler.
 * @param[in] hal_ll_state - init or deinit
 *
 * @return  none.
 *
 * @note AVR specific.
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
  * @brief Timer/Counter module start function (channel A).
  *
  * Function starts generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_start_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module start function (channel B).
  *
  * Function starts generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_start_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module start function (channel C).
  *
  * Function starts generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_start_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module start function (channel D).
  *
  * Function starts generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_start_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module stop function (channel A).
  *
  * Function stops generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_stop_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module stop function (channel B).
  *
  * Function stops generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_stop_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module stop function (channel C).
  *
  * Function stops generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_stop_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Timer/Counter module stop function (channel D).
  *
  * Function stops generating PWM signal on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_stop_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Clears any electronic driver output leftovers (channel A).
  *
  * Clears any output leftovers from the Waveform Generator for channel A.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Clears any electronic driver output leftovers (channel B).
  *
  * Clears any output leftovers from the Waveform Generator for channel B.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Clears any electronic driver output leftovers (channel C).
  *
  * Clears any output leftovers from the Waveform Generator for channel C.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Clears any electronic driver output leftovers (channel D).
  *
  * Clears any output leftovers from the Waveform Generator for channel D.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg );

/**
  * @brief Initialize Timer/Counter set duty function (channel A).
  *
  * Function configures duty cycle on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] duty_cycle_value - Calculated duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_set_duty_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value );

/**
  * @brief Initialize Timer/Counter set duty function (channel B).
  *
  * Function configures duty cycle on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] duty_cycle_value - Calculated duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_set_duty_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value );

/**
  * @brief Initialize Timer/Counter set duty function (channel C).
  *
  * Function configures duty cycle on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] duty_cycle_value - Calculated duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_set_duty_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value );

/**
  * @brief Initialize Timer/Counter set duty function (channel A).
  *
  * Function configures duty cycle on Timer/Counter PWM pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of Timer/Counter module.
  * @param[in] duty_cycle_value - Calculated duty cycle.
  *
  * @return none
  *
  */
static inline void ptr_function_timer_counter_set_duty_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value );

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
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ]->hal_ll_tim_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    uint8_t pin_check_result;
    uint8_t index;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( HAL_LL_PIN_NC == ( pin_check_result = _hal_ll_tim_check_pin( hal_ll_tim_hw_specifics_map_local->pin, &index, (void *)0 ) ) ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {
    uint16_t local_freq = 0;
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    // Calculate PWM frequency.
    local_freq = ( ( _fosc / hal_ll_tim_hw_specifics_map_local->freq_hz ) - 1 );

    // Populate appropriate registers.
    write_reg( hal_ll_hw_reg->hal_ll_pwm_perl_reg_address, ( (uint8_t)local_freq ) );
    write_reg( hal_ll_hw_reg->hal_ll_pwm_perh_reg_address, ( local_freq >> 8 ) );

    // Memorize information about the max period available (PWM duty cycle is dependant of this information).
    return ( hal_ll_tim_hw_specifics_map_local->max_period = local_freq ) ;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {
    uint16_t local_duty_cycle_value = 0;
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( low_level_handle->init_ll_state == false ) {
        _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );
        low_level_handle->init_ll_state = true;
    }

    // Calculate duty cycle value in accordance to max period available.
    local_duty_cycle_value = ( duty_ratio * hal_ll_tim_hw_specifics_map_local->max_period );

    // Insert duty cycle value into appropriate register (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_set_duty )
    ( hal_ll_tim_hw_specifics_map_local->base, local_duty_cycle_value );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // Configure Waveform Generator for "Single-Slope PWM".
    set_reg_bits( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_SET_SINGLE_SLOPE_PWM );

    // Enable Compare mode for appropriate PWM driver channel (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_signal_start )
    ( hal_ll_tim_hw_specifics_map_local->base );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    // Detach PWM driver circuit from PWM pin (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_signal_stop )
    ( hal_ll_tim_hw_specifics_map_local->base );

    // Reset Waveform Generator.
    clear_reg_bits( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_RESET_WAFEFORM_GENERATOR );

    // Timer/Counter in OFF state.
    clear_reg( hal_ll_hw_reg->hal_ll_pwm_ctrla_reg_address );

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

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    /*!< @brief Static, because clock doesn't change during runtime. */
    static uint32_t hal_ll_clock_value = Get_Fosc_kHz() * 2;

    // Get hardware register list for user-defined PWM pin.
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    // Set Clock source.
    set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrla_reg_address, HAL_LL_TIM_NO_PRESCALER );

    // Clear any output leftovers from the Waveform Generator (via function pointers).
    ( hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_hw_init_pwm_mode )
    ( hal_ll_tim_hw_specifics_map_local->base );

    // Disable Event Action Engine.
    clear_reg( hal_ll_hw_reg->hal_ll_pwm_ctrld_reg_address );

    // Give it some time to stabilize.
    hal_ll_tim_wait_for_sync( hal_ll_clock_value );
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    // Configure PWM pin.
    _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );

    // Finally, configure Timer/Counter (PWM) registers.
    _hal_ll_tim_hw_init( map );
}

// ---------------------------------------------------- STATIC POINTER FUNCTIONS
static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t channel ) {
    switch ( channel ) {
        case ( HAL_LL_TIM_CH_A ):
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_counter_start_ch_a;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_counter_stop_ch_a;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_counter_hw_init_pwm_mode_ch_a;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_counter_set_duty_ch_a;
            break;
        case ( HAL_LL_TIM_CH_B ):
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_counter_start_ch_b;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_counter_stop_ch_b;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_counter_hw_init_pwm_mode_ch_b;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_counter_set_duty_ch_b;
            break;
        case ( HAL_LL_TIM_CH_C ):
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_counter_start_ch_c;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_counter_stop_ch_c;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_counter_hw_init_pwm_mode_ch_c;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_counter_set_duty_ch_c;
            break;
        case ( HAL_LL_TIM_CH_D ):
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_start = &ptr_function_timer_counter_start_ch_d;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_signal_stop = &ptr_function_timer_counter_stop_ch_d;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_counter_hw_init_pwm_mode_ch_d;
            hal_ll_tim_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_set_duty = &ptr_function_timer_counter_set_duty_ch_d;
            break;
    }
}

static inline void ptr_function_timer_counter_start_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    #ifndef __hal_ll_tim_subset_atxmega_e5_series__
        // Set Byte Mode to be NORMAL.
        write_reg( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_BYTE_MODE_NORMAL );

        // Enable Output Compare channel A.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_A );
    #else
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_A_ATXMEGA_E5_SERIES );
    #endif
}

static inline void ptr_function_timer_counter_start_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    #ifndef __hal_ll_tim_subset_atxmega_e5_series__
        // Set Byte Mode to be NORMAL.
        write_reg( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_BYTE_MODE_NORMAL );

        // Enable Output Compare channel B.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_B );
    #else
        // Enable Output Compare channel B.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_B_ATXMEGA_E5_SERIES );
    #endif
}

static inline void ptr_function_timer_counter_start_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    #ifndef __hal_ll_tim_subset_atxmega_e5_series__
        // Set Byte Mode to be NORMAL.
        write_reg( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_BYTE_MODE_NORMAL );

        // Enable Output Compare channel C.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_C );
    #else
        // Enable Output Compare channel C.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_C_ATXMEGA_E5_SERIES );
    #endif
}

static inline void ptr_function_timer_counter_start_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    #ifndef __hal_ll_tim_subset_atxmega_e5_series__
        // Set Byte Mode to be NORMAL.
        write_reg( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_BYTE_MODE_NORMAL );

        // Enable Output Compare channel D.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_D );
    #else
        // Enable Output Compare channel D.
        set_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrle_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_D_ATXMEGA_E5_SERIES );
    #endif
}

static inline void ptr_function_timer_counter_stop_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_A );
}

static inline void ptr_function_timer_counter_stop_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_B );
}

static inline void ptr_function_timer_counter_stop_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_C );
}

static inline void ptr_function_timer_counter_stop_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlb_reg_address, HAL_LL_TIM_OUTPUT_COMPARE_CH_D );
}

static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlc_reg_address, HAL_LL_TIM_CMPA_BIT );
}

static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlc_reg_address, HAL_LL_TIM_CMPB_BIT );
}

static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlc_reg_address, HAL_LL_TIM_CMPC_BIT );
}

static inline void ptr_function_timer_counter_hw_init_pwm_mode_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( hal_ll_hw_reg->hal_ll_pwm_ctrlc_reg_address, HAL_LL_TIM_CMPD_BIT );
}

static inline void ptr_function_timer_counter_set_duty_ch_a( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value ) {
    *(uint16_t *)hal_ll_hw_reg->hal_ll_pwm_ccabuf_reg_address = duty_cycle_value;
}

static inline void ptr_function_timer_counter_set_duty_ch_b( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value ) {
    *(uint16_t *)hal_ll_hw_reg->hal_ll_pwm_ccbbuf_reg_address = duty_cycle_value;
}

static inline void ptr_function_timer_counter_set_duty_ch_c( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value ) {
    *(uint16_t *)hal_ll_hw_reg->hal_ll_pwm_cccbuf_reg_address = duty_cycle_value;
}

static inline void ptr_function_timer_counter_set_duty_ch_d( hal_ll_tim_base_handle_t *hal_ll_hw_reg, uint16_t duty_cycle_value ) {
    *(uint16_t *)hal_ll_hw_reg->hal_ll_pwm_ccdbuf_reg_address = duty_cycle_value;
}
// ------------------------------------------------------------------------- END
