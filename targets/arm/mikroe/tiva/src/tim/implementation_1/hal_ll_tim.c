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

#include "hal_ll_rcc.h"
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

/*!< @brief Helper macros for choosing CCP based on pin parity. */
#define HAL_LL_TIM_CCP_0                    (0)
#define HAL_LL_TIM_CCP_1                    (1)

/*!< @brief Helper macros for getting TIMER clocks operational. */
#define HAL_LL_TIM_RCGCTIMER_T0             (0)
#define HAL_LL_TIM_RCGCTIMER_T1             (1)
#define HAL_LL_TIM_RCGCTIMER_T2             (2)
#define HAL_LL_TIM_RCGCTIMER_T3             (3)
#define HAL_LL_TIM_RCGCTIMER_T4             (4)
#define HAL_LL_TIM_RCGCTIMER_T5             (5)
#define HAL_LL_TIM_RCGCTIMER_T6             (6)
#define HAL_LL_TIM_RCGCTIMER_T7             (7)

/*!< @brief Helper macro for getting TIMER clock in on/off state - TIMER A. */
#define HAL_LL_TIM_CTL_TAEN                 (0)

/*!< @brief Helper macro for PWM Output Level (output non-inverted/inverted) - TIMER A. */
#define HAL_LL_TIM_CTL_TAPWML               (6)

/*!< @brief Helper macro for applying PWM mode in TIMER A module. */
#define HAL_LL_TIM_TAMR_TAAMS               (3)

/*!< @brief Helper macro for getting TIMER clock in on/off state - TIMER B. */
#define HAL_LL_TIM_CTL_TBEN                 (8)

/*!< @brief Helper macro for PWM Output Level (output non-inverted/inverted) - TIMER A. */
#define HAL_LL_TIM_CTL_TBPWML               (14)

/*!< @brief Helper macro for applying PWM mode in TIMER B module. */
#define HAL_LL_TIM_TBMR_TBAMS               (3)

/*!< @brief Helper macro for configuring TIMER module as a 16-bit timer. */
#define HAL_LL_TIM_CFG_SET_16BIT_TIMER      (4)

/*!< @brief Helper macro for configuring basic TIMER module settings for PWM capability. */
#define HAL_LL_TIM_PWM_MODE                 (10)

/*!< @brief Helper macro for cleaning global operation of General Purpose Timer Module Register. */
#define HAL_LL_TIM_CLEAN_GLOBAL_TIM_CONFIG  (7)

/*!< @brief Helper macro for cleaning General Purpose Timer Module Mode Register. */
#define HAL_LL_TIM_CLEAN_MODE_TIM_CONFIG    (15)

/*!< @brief Helper macro for regulating configuration of duty cycle. */
#define HAL_LL_TIM_REG_CLEAN_MASK1          (0xFF)
#define HAL_LL_TIM_REG_CLEAN_MASK2          (0xFFFF)

/*!< @brief Helper macro for retrieving user-defined MCU (Necto Setups Wizard) frequency. */
#define _fosc                               ( Get_Fosc_kHz() * 1000 )

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
    hal_ll_base_addr_t cfg;       // General-Purpose Timer Module Config Register.
    hal_ll_base_addr_t tamr;      // General-Purpose Timer Module timer A Register.
    hal_ll_base_addr_t tbmr;      // General-Purpose Timer Module timer B Register.
    hal_ll_base_addr_t ctl;       // General-Purpose Timer Module Control Register.
    hal_ll_base_addr_t sync;      // General-Purpose Timer Module Sync Register.
    hal_ll_base_addr_t __unused1; // Reserved memory space.
    hal_ll_base_addr_t imr;       // General-Purpose Timer Module Interrupt Mask Register.
    hal_ll_base_addr_t ris;       // General-Purpose Timer Module Raw Interrupt Status Register.
    hal_ll_base_addr_t mis;       // General-Purpose Timer Module Masked Interrupt Status Register.
    hal_ll_base_addr_t icr;       // General-Purpose Timer Module Interrupt Clear Register.
    hal_ll_base_addr_t tailr;     // General-Purpose Timer Module timer A Interval Load Register.
    hal_ll_base_addr_t tbilr;     // General-Purpose Timer Module timer B Interval Load Register.
    hal_ll_base_addr_t tamatchr;  // General-Purpose Timer Module timer A Match Register.
    hal_ll_base_addr_t tbmatchr;  // General-Purpose Timer Module timer B Match Register.
    hal_ll_base_addr_t tapr;      // General-Purpose Timer Module timer A Prescale Register.
    hal_ll_base_addr_t tbpr;      // General-Purpose Timer Module timer B Prescale Register.
    hal_ll_base_addr_t tapmr;     // General-Purpose Timer Module timer A Prescale Match Register.
    hal_ll_base_addr_t tbpmr;     // General-Purpose Timer Module timer B Prescale Match Register.
    hal_ll_base_addr_t tar;       // General-Purpose Timer Module timer A Register.
    hal_ll_base_addr_t tbr;       // General-Purpose Timer Module timer B Register.
    hal_ll_base_addr_t tav;       // General-Purpose Timer Module timer A Value Register.
    hal_ll_base_addr_t tbv;       // General-Purpose Timer Module timer B Value Register.
    hal_ll_base_addr_t rtcpd;     // General-Purpose Timer Module RTC Predivide Register.
    hal_ll_base_addr_t taps;      // General-Purpose Timer Module timer A Prescale Snapshot Register.
    hal_ll_base_addr_t tbps;      // General-Purpose Timer Module timer B Prescale Snapshot Register.
    /* Commented out for memory optimization;
     * Uncomment if needed.
     */
    // hal_ll_base_addr_t __unused2[2];   // Reserved memory space.
    // hal_ll_base_addr_t dmaev;          // General-Purpose Timer Module DMA Event Register.
    // hal_ll_base_addr_t adcev;          // General-Purpose Timer Module ADC Event Register.
    // hal_ll_base_addr_t __unused4[979]; // Reserved memory space.
    // hal_ll_base_addr_t mpp;            // General-Purpose Timer Module Peripheral Properties.
    // hal_ll_base_addr_t __unused5;      // Reserved memory space.
    // hal_ll_base_addr_t mcc;            // General-Purpose Timer Module Clock Configuration.
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
    uint32_t period;
    uint32_t tmp_freq;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    low_level_handle->init_ll_state = false;

    hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;

    period =  ( _fosc ) / freq_hz;

    if ( period > ( UINT16_MAX * UINT8_MAX ) ) {
        tmp_freq = ( _fosc ) / ( UINT16_MAX * UINT8_MAX );
        hal_ll_tim_hw_specifics_map_local->freq_hz = tmp_freq;
        hal_ll_tim_hw_specifics_map_local->max_period = UINT16_MAX * UINT8_MAX;
    } else {
        tmp_freq = freq_hz;
        hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;
        hal_ll_tim_hw_specifics_map_local->max_period = period;
    }

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    _hal_ll_tim_set_period( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return tmp_freq;
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
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address);

    if ( low_level_handle->hal_ll_tim_handle != NULL ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;

        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local, true );
        _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_local, false );
        _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->config.pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->config.pin_parity = HAL_LL_TIM_CCP_0;
        hal_ll_tim_hw_specifics_map_local->config.af = NULL;

        map_pointer_functions(hal_ll_tim_hw_specifics_map_local->module_index, HAL_LL_TIM_CCP_0);
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void _hal_ll_tim_alternate_functions_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    module_struct module;
    uint32_t tim_config = 0;

    if( map->config.pin != HAL_LL_PIN_NC ) {
        if( hal_ll_state != false ) {
            tim_config |= GPIO_CFG_DIGITAL_INPUT | GPIO_CFG_ALT_FUNCTION;
        }

        module.pins[ 0 ] = VALUE( map->config.pin, map->config.af );
        module.pins[ 1 ] = GPIO_MODULE_STRUCT_END;

        module.configs[ 0 ] = tim_config;
        module.configs[ 1 ] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
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
        if ( pin == _tim_map[ pin_num ].pin ) {
            // Get module number.
            hal_ll_module_id = _tim_map[ pin_num ].module_index;
            map_pointer_functions( hal_ll_module_id, pin % 2 );

            if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_tim_handle ) {
                *index = pin_num;
                return hal_ll_module_id;
            } else if( TIM_MODULE_COUNT == ++index_counter ) {
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

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin = _tim_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].config.af  = _tim_map[ index ].af;
    hal_ll_tim_hw_specifics_map[ module_index ].config.pin_parity = _tim_map[ index ].pin % 2;
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

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    // Enable specific clock module.
    _hal_ll_tim_set_clock( map, true );

    // Enable specific alternate functions.
    _hal_ll_tim_alternate_functions_set_state( map, true );

    // Finally, write user-defined settings into hardware registers.
    _hal_ll_tim_hw_init( map );
}

static void _hal_ll_tim_set_clock( hal_ll_tim_hw_specifics_map_t* map, bool hal_ll_state ) {
    switch (map->module_index) {
    #ifdef TIM_MODULE_0
        case ( TIM_MODULE_0 ):
            _hal_ll_tim0_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_1
        case ( TIM_MODULE_1 ):
            _hal_ll_tim1_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_2
        case ( TIM_MODULE_2 ):
            _hal_ll_tim2_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_3
        case ( TIM_MODULE_3 ):
            _hal_ll_tim3_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_4
        case ( TIM_MODULE_4 ):
            _hal_ll_tim4_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_5
        case ( TIM_MODULE_5 ):
            _hal_ll_tim5_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_6
        case ( TIM_MODULE_6 ):
            _hal_ll_tim6_set_clock( hal_ll_state );
            break;
    #endif
    #ifdef TIM_MODULE_7
        case ( TIM_MODULE_7 ):
            _hal_ll_tim7_set_clock( hal_ll_state );
            break;
    #endif

        default:
            break;
    }
}

static void _hal_ll_tim0_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T0 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T0);
    }
}

static void _hal_ll_tim1_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T1 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T1);
    }
}

static void _hal_ll_tim2_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T2 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T2);
    }
}

static void _hal_ll_tim3_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T3 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T3);
    }
}

static void _hal_ll_tim4_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T4 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T4);
    }
}

static void _hal_ll_tim5_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T5 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T5);
    }
}

static void _hal_ll_tim6_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T6 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T6);
    }
}

static void _hal_ll_tim7_set_clock( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        set_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T7 );
    } else {
        clear_reg_bit(_SYSCTL_RCGCTIMER, HAL_LL_TIM_RCGCTIMER_T7);
    }
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    (hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_hw_init_control)
    (hal_ll_tim_hw_specifics_map_local->base);

    hal_ll_hw_reg->cfg &= ~(hal_ll_base_addr_t)( HAL_LL_TIM_CLEAN_GLOBAL_TIM_CONFIG );
    hal_ll_hw_reg->cfg |= (hal_ll_base_addr_t)(HAL_LL_TIM_CFG_SET_16BIT_TIMER);

    (hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_hw_init_pwm_mode)
    (hal_ll_tim_hw_specifics_map_local->base);
}

static void _hal_ll_tim_set_period( hal_ll_tim_hw_specifics_map_t *map ) {
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    (hal_ll_tim_hw_specifics_map_local->mapped_functions.mapped_function_period)
    (hal_ll_tim_hw_specifics_map_local->base, hal_ll_tim_hw_specifics_map_local->max_period);
}

// ---------------------------------------------------- STATIC POINTER FUNCTIONS

static inline void map_pointer_functions( uint8_t hal_ll_module_id, uint8_t pin_parity ) {
    if ( pin_parity ) {
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_duty = &ptr_function_timer_b_duty;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_signal_start = &ptr_function_timer_b_start;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_signal_stop = &ptr_function_timer_b_stop;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_period = &ptr_function_timer_b_period;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_hw_init_control = &ptr_function_timer_b_hw_init_control;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_b_pwm_mode_set;
    } else {
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_duty = &ptr_function_timer_a_duty;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_signal_start = &ptr_function_timer_a_start;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_signal_stop = &ptr_function_timer_a_stop;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_period = &ptr_function_timer_a_period;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_hw_init_control = &ptr_function_timer_a_hw_init_control;
        hal_ll_tim_hw_specifics_map[hal_ll_module_id].mapped_functions.mapped_function_hw_init_pwm_mode = &ptr_function_timer_a_pwm_mode_set;
    }
}

static inline void ptr_function_timer_a_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                              uint32_t duty_cycle_timeout,
                                              uint32_t max_period ) {
    /* Turns PWM off if the duty cycle is 0 (this is done because
     * if duty cycle is configured to max_period it will behave the same as max duty - 100%)
     */
    if ( duty_cycle_timeout == max_period ) {
        clear_reg_bit(&hal_ll_hw_reg->tamr,HAL_LL_TIM_TAMR_TAAMS);
    } else {
        set_reg_bit(&hal_ll_hw_reg->tamr,HAL_LL_TIM_TAMR_TAAMS);
    }

    // Clean TimerA Prescale Match Register.
    hal_ll_hw_reg->tapmr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_REG_CLEAN_MASK1 );

    // Insert appropriate value in this register.
    hal_ll_hw_reg->tapmr |= ( hal_ll_base_addr_t )( duty_cycle_timeout >> 16 ) & HAL_LL_TIM_REG_CLEAN_MASK1;

    // Clean TimerA Match Register.
    hal_ll_hw_reg->tamatchr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_REG_CLEAN_MASK2 );

    // Insert appropriate value in this register.
    hal_ll_hw_reg->tamatchr |= ( hal_ll_base_addr_t )( duty_cycle_timeout ) & HAL_LL_TIM_REG_CLEAN_MASK2;
}

static inline void ptr_function_timer_b_duty( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                              uint32_t duty_cycle_timeout,
                                              uint32_t max_period ) {
    /* Turns PWM off if the duty cycle is 0 (this is done because
     * if duty cycle is configured to max_period it will behave the same as max duty - 100%)
     */
    if ( duty_cycle_timeout == max_period ) {
        clear_reg_bit(&hal_ll_hw_reg->tbmr,HAL_LL_TIM_TBMR_TBAMS);
    } else {
        set_reg_bit(&hal_ll_hw_reg->tbmr,HAL_LL_TIM_TBMR_TBAMS);
    }

    // Clean TimerB Prescale Match Register.
    hal_ll_hw_reg->tbpmr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_REG_CLEAN_MASK1 );

    // Insert appropriate value in this register.
    hal_ll_hw_reg->tbpmr |= ( hal_ll_base_addr_t )( duty_cycle_timeout >> 16 ) & HAL_LL_TIM_REG_CLEAN_MASK1;

    // Clean TimerB Match Register.
    hal_ll_hw_reg->tbmatchr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_REG_CLEAN_MASK2 );

    // Insert appropriate value in this register.
    hal_ll_hw_reg->tbmatchr |= ( hal_ll_base_addr_t )( duty_cycle_timeout ) & HAL_LL_TIM_REG_CLEAN_MASK2;
}

static inline void ptr_function_timer_a_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    set_reg_bit( &hal_ll_hw_reg->tamr, HAL_LL_TIM_TAMR_TAAMS );
    set_reg_bit( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TAEN );
}

static inline void ptr_function_timer_b_start( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    set_reg_bit( &hal_ll_hw_reg->tbmr, HAL_LL_TIM_TBMR_TBAMS );
    set_reg_bit( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TBEN );
}

static inline void ptr_function_timer_a_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TAEN );
    clear_reg_bit( &hal_ll_hw_reg->tamr, HAL_LL_TIM_TAMR_TAAMS );
}

static inline void ptr_function_timer_b_stop( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TBEN );
    clear_reg_bit( &hal_ll_hw_reg->tbmr, HAL_LL_TIM_TBMR_TBAMS );
}

static inline void ptr_function_timer_a_period( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                                uint32_t max_period ) {
    hal_ll_hw_reg->tapr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_REG_CLEAN_MASK1 );
    hal_ll_hw_reg->tapr |= ( max_period >> 16 ) & HAL_LL_TIM_REG_CLEAN_MASK1;
    hal_ll_hw_reg->tailr = max_period & HAL_LL_TIM_REG_CLEAN_MASK2;
}

static inline void ptr_function_timer_b_period( hal_ll_tim_base_handle_t *hal_ll_hw_reg,
                                                uint32_t max_period ) {
    hal_ll_hw_reg->tbpr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_REG_CLEAN_MASK1 );
    hal_ll_hw_reg->tbpr |= ( max_period >> 16 ) & HAL_LL_TIM_REG_CLEAN_MASK1;
    hal_ll_hw_reg->tbilr = max_period & HAL_LL_TIM_REG_CLEAN_MASK2;
}

static inline void ptr_function_timer_a_hw_init_control( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit ( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TAEN );
    clear_reg_bit ( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TAPWML );
}

static inline void ptr_function_timer_b_hw_init_control( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    clear_reg_bit ( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TBEN );
    clear_reg_bit ( &hal_ll_hw_reg->ctl, HAL_LL_TIM_CTL_TBPWML );
}

static inline void ptr_function_timer_a_pwm_mode_set( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    hal_ll_hw_reg->tamr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_CLEAN_MODE_TIM_CONFIG );
    hal_ll_hw_reg->tamr |= ( hal_ll_base_addr_t )( HAL_LL_TIM_PWM_MODE );
}

static inline void ptr_function_timer_b_pwm_mode_set( hal_ll_tim_base_handle_t *hal_ll_hw_reg ) {
    hal_ll_hw_reg->tbmr &= ~( hal_ll_base_addr_t )( HAL_LL_TIM_CLEAN_MODE_TIM_CONFIG );
    hal_ll_hw_reg->tbmr |= ( hal_ll_base_addr_t )( HAL_LL_TIM_PWM_MODE );
}

// ------------------------------------------------------------------------- END
