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
 * @brief TIMER HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_tim.h"
#include "hal_ll_gpio.h"
#include "hal_ll_pps.h"
#include "hal_ll_tim_pin_map.h"
#include "hal_ll_odcon_map.h"

#ifdef __XC8__
#if FSR_APPROACH
#include "mcu.h"
#endif
#endif

/*!< @brief Local handle list */
static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ] = { (handle_t *)NULL, (handle_t *) NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< TIM registers bit locations */
#define HAL_LL_TIM_CCP_M2                           2
#define HAL_LL_TIM_CCP_M3                           3
#define HAL_LL_TIM_DC_B0                            4
#define HAL_LL_TIM_DC_B1                            5
#define HAL_LL_TIM_DC_LSBITS                        0x0030

#define HAL_LL_TIM_TMRON_BIT                        2

// Macro for writing to register
#define HAL_LL_TIM_PRESCALER_1                      0
#define HAL_LL_TIM_PRESCALER_4                      1
#define HAL_LL_TIM_PRESCALER_16                     2
#define HAL_LL_TIM_FREQ_PRESCALER_16                16

#ifdef __XC8__
static inline void write_reg_bitwise_and(uint16_t reg, uint8_t bit_mask) {
    uint8_t *addr;
    addr = reg;
    *addr = *addr & bit_mask;
}
#define write_reg_bitwise_or(_reg,_val) set_reg_bits(_reg,_val)
#else
#define write_reg_bitwise_and(_reg,_val)            ( *(uint8_t *)_reg &= _val )
#define write_reg_bitwise_or(_reg,_val)             ( *(uint8_t *)_reg |= _val )
#endif

#define _hal_ll_tim_freq_formula(_freq,_presc)      (((float)1/_freq )/(((float)1/((Get_Fosc_kHz()*1000)/4))*_presc))

#define _hal_ll_tim_get_freq                        (float)1/(UINT8_MAX*(((float)1/((Get_Fosc_kHz()*1000)/4))*HAL_LL_TIM_FREQ_PRESCALER_16));

#define _hal_ll_tim_desired_freq(_freq)             (_hal_ll_tim_freq_formula(_freq,1)<255)?_hal_ll_tim_freq_formula(_freq,1):\
                                                    (_hal_ll_tim_freq_formula(_freq,4)<255)?_hal_ll_tim_freq_formula(_freq,4):\
                                                     _hal_ll_tim_freq_formula(_freq,16)

#define _hal_ll_tim_presc_values(_freq)             (_hal_ll_tim_freq_formula(_freq,1)<255)?HAL_LL_TIM_PRESCALER_1:\
                                                    (_hal_ll_tim_freq_formula(_freq,4)<255)?HAL_LL_TIM_PRESCALER_4:\
                                                      HAL_LL_TIM_PRESCALER_16

/*!< @brief Helper macro for enabling output driver D circuit for enhanced PWM pin. */
#define HAL_LL_TIM_ENHANCED_PWM_STRD_BIT 6

/*!< @brief Helper macros for enabling output driver B circuit for enhanced PWM pin. */
#define HAL_LL_TIM_ENHANCED_PWM_STRB_BIT_1 6
#define HAL_LL_TIM_ENHANCED_PWM_STRB_BIT_2 7

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) ((const hal_ll_tim_base_handle_t *)_handle)

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address ((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

/*!< @brief Helper macros for defining non-existent Pulse Steering Registers. */
#ifndef HAL_LL_PSTR1CON_ADDRESS
    #define HAL_LL_PSTR1CON_ADDRESS 0
#endif
#ifndef HAL_LL_PSTR2CON_ADDRESS
    #define HAL_LL_PSTR2CON_ADDRESS 0
#endif
#ifndef HAL_LL_PSTR3CON_ADDRESS
    #define HAL_LL_PSTR3CON_ADDRESS 0
#endif

// -------------------------------------------------------------- PRIVATE TYPES
typedef struct
{
    uint16_t hal_tcon_reg_addr;
    uint16_t hal_pr_reg_addr;
} hal_ll_tim_regs_struct_t;

typedef struct
{
    uint16_t hal_ccprl_reg_addr;
    uint16_t hal_ccpcon_reg_addr;
    uint16_t hal_pstrcon_reg_addr;
} hal_ll_tim_base_handle_t;

/*!< @brief TIM hw specific structure */
typedef struct
{
    const hal_ll_tim_base_handle_t *base;
    hal_ll_pin_name_t pin;
    uint16_t max_period;
    uint32_t freq_hz;
    hal_ll_pin_name_t timer;
    uint8_t module_index;
    uint8_t hal_ll_pps_module_index;
    hal_ll_tim_pulse_steering_control_t steering;
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hw specific error values */
typedef enum
{
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief PWM ( CCP ) module registers access structure */
static const hal_ll_tim_regs_struct_t tim_regs_map[] = {
    #if defined (HAL_LL_T2CON_ADDRESS) && defined (HAL_LL_PR2_ADDRESS)
    { HAL_LL_T2CON_ADDRESS, HAL_LL_PR2_ADDRESS },
    #endif

    #if defined (HAL_LL_T4CON_ADDRESS) && defined (HAL_LL_PR4_ADDRESS)
    { HAL_LL_T4CON_ADDRESS, HAL_LL_PR4_ADDRESS },
    #endif

    #if defined (HAL_LL_T6CON_ADDRESS) && defined (HAL_LL_PR6_ADDRESS)
    { HAL_LL_T6CON_ADDRESS, HAL_LL_PR6_ADDRESS },
    #endif

    #if defined (HAL_LL_T8CON_ADDRESS) && defined (HAL_LL_PR8_ADDRESS)
    { HAL_LL_T8CON_ADDRESS, HAL_LL_PR8_ADDRESS },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

/*!< @brief PWM ( CCP ) array */
static const hal_ll_tim_base_handle_t tim_ll_reg_offsets[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef CCP_MODULE_1
    { HAL_LL_CCPR1L_ADDRESS, HAL_LL_CCP1CON_ADDRESS, HAL_LL_PSTR1CON_ADDRESS },
    #endif
    #ifdef CCP_MODULE_2
    { HAL_LL_CCPR2L_ADDRESS, HAL_LL_CCP2CON_ADDRESS, HAL_LL_PSTR2CON_ADDRESS },
    #endif
    #ifdef CCP_MODULE_3
    { HAL_LL_CCPR3L_ADDRESS, HAL_LL_CCP3CON_ADDRESS, HAL_LL_PSTR3CON_ADDRESS },
    #endif
    #ifdef CCP_MODULE_4
    { HAL_LL_CCPR4L_ADDRESS, HAL_LL_CCP4CON_ADDRESS, 0 },
    #endif
    #ifdef CCP_MODULE_5
    { HAL_LL_CCPR5L_ADDRESS, HAL_LL_CCP5CON_ADDRESS, 0 },
    #endif
    #ifdef CCP_MODULE_6
    { HAL_LL_CCPR6L_ADDRESS, HAL_LL_CCP6CON_ADDRESS, 0 },
    #endif
    #ifdef CCP_MODULE_7
    { HAL_LL_CCPR7L_ADDRESS, HAL_LL_CCP7CON_ADDRESS, 0 },
    #endif
    #ifdef CCP_MODULE_8
    { HAL_LL_CCPR8L_ADDRESS, HAL_LL_CCP8CON_ADDRESS, 0 },
    #endif
    #ifdef CCP_MODULE_9
    { HAL_LL_CCPR9L_ADDRESS, HAL_LL_CCP9CON_ADDRESS, 0 },
    #endif
    #ifdef CCP_MODULE_10
    { HAL_LL_CCPR10L_ADDRESS, HAL_LL_CCP10CON_ADDRESS, 0 },
    #endif
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, 0 }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef CCP_MODULE_1
    { &tim_ll_reg_offsets[ CCP_MODULE_1 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_1), HAL_LL_CCP_MODULE_1 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_2
    { &tim_ll_reg_offsets[ CCP_MODULE_2 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_2), HAL_LL_CCP_MODULE_2 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_3
    { &tim_ll_reg_offsets[ CCP_MODULE_3 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_3), HAL_LL_CCP_MODULE_3 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_4
    { &tim_ll_reg_offsets[ CCP_MODULE_4 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_4), HAL_LL_CCP_MODULE_4 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_5
    { &tim_ll_reg_offsets[ CCP_MODULE_5 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_5), HAL_LL_CCP_MODULE_5 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_6
    { &tim_ll_reg_offsets[ CCP_MODULE_6 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_6), HAL_LL_CCP_MODULE_6 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_7
    { &tim_ll_reg_offsets[ CCP_MODULE_7 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_7), HAL_LL_CCP_MODULE_7 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_8
    { &tim_ll_reg_offsets[ CCP_MODULE_8 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_8), HAL_LL_CCP_MODULE_8 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_9
    { &tim_ll_reg_offsets[ CCP_MODULE_9 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_9), HAL_LL_CCP_MODULE_9 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif
    #ifdef CCP_MODULE_10
    { &tim_ll_reg_offsets[ CCP_MODULE_10 - 1 ], HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(CCP_MODULE_10), HAL_LL_CCP_MODULE_10 - 1, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE },
    #endif

    { &tim_ll_reg_offsets[ TIM_MODULE_COUNT ], HAL_LL_PIN_NC, 0, 0, 0xFF, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable CCP module 1.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim1_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 2.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim2_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 3.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim3_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 4.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim4_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 5.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim5_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 6.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim6_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 7.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim7_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 8.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim8_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 9.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim9_enable_module( bool hal_ll_state );

/**
  * @brief  Enable CCP module 10.
  * @param  None.
  * @return None.
  */
static inline void _hal_ll_tim10_enable_module( bool hal_ll_state );

/**
  * @brief  Enable module for TIM module on hardware level.
  *
  * Initializes TIM module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param map - Object specific context handler.
  * @param hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return void None.
  */
static void _hal_ll_tim_set_module_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

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
static hal_ll_tim_hw_specifics_map_t *hal_ll_tim_get_specifics( handle_t handle );

/**
 * @brief  Sets ODCONx state.
 *
 * Sets adequate ODCONx register state.
 * TIM pins open drain setting.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return  None.
 */
static void _hal_ll_tim_hw_odcon_set( hal_ll_tim_hw_specifics_map_t *map );

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
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and PPS function values for
 * TIM pin.
 *
 * @param[in]  module_index TIM HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with TIM pin map index values.
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
  * @param  pin - TIM pre-defined pin name.
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

/**
 * @brief  Reset duty cycle for specific CCP.
 *
 * @param map - Object specific context handler.
 *
 * @return none
 */
static void _hal_tim_reset_duty_cycle_bits( hal_ll_tim_hw_specifics_map_t *map );

/**
 * @brief  Timer assignments for CCP modules.
 *
 * @param map - Object specific context handler.
 *
 * @return none
 */
static void _hal_ll_tim_select_timer( hal_ll_tim_hw_specifics_map_t *map );

/**
 * @brief  Set PPS state.
 *
 * Sets adequate RPORx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param map - Object specific context handler.
 * @param hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t _hal_ll_pps_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief  Set GPIO state.
 *
 * Sets adequate TRISx register
 * values for adequate functionality.
 *
 * @param map - Object specific context handler.
 * @param hal_ll_state - init or deinit
 *
 * @return  none.
 *
 * @note PIC specific.
 */
static void _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map,
                                                                uint8_t *hal_module_id ) {

    uint8_t pin_check_result;
    uint8_t index;

    if ( ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( ( hal_ll_tim_hw_specifics_map[ pin_check_result ].pin != pin ) ) {
        // Used only for chips which have TIM PPS pins
        #if HAL_LL_TIM_PPS_ENABLED == true
        // Clear previous module pps
        _hal_ll_pps_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );
        #endif

        // Map new pps
        _hal_ll_tim_map_pin( pin_check_result, index );

        // Used only for chips which have TIM PPS pins
        #if HAL_LL_TIM_PPS_ENABLED == true
        // Set mapped pps
        _hal_ll_pps_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );
        #endif

        handle_map[ pin_check_result ].init_ll_state = false;

        hal_ll_module_state[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_tim_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_handle_register_t *hal_handle = (hal_ll_tim_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_tim_hw_specifics_map_local->module_index;

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {

    uint32_t tmp_period;
    uint32_t tmp_freq;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_tim_get_specifics( hal_ll_tim_get_module_state_address );

    const hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    low_level_handle->init_ll_state = false;

    tmp_period = _hal_ll_tim_freq_formula( freq_hz, HAL_LL_TIM_FREQ_PRESCALER_16 );

    // Set duty to 0.
    _hal_tim_reset_duty_cycle_bits( hal_ll_tim_hw_specifics_map_local );

    // Stop capture/compare.
    write_reg_bitwise_and( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_NIBBLE_HIGH_8BIT );

    if ( tmp_period > UINT8_MAX ) {
        tmp_freq = _hal_ll_tim_get_freq;
        hal_ll_tim_hw_specifics_map_local->freq_hz = tmp_freq;
    } else {
        tmp_freq = freq_hz;
        hal_ll_tim_hw_specifics_map_local->freq_hz = freq_hz;
    }

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return tmp_freq;
}

hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio ) {

    uint16_t max_period;
    uint16_t val;
    uint8_t  temp;
    float    tmp_duty;
    volatile uint16_t max_duty = 0;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_tim_get_specifics( hal_ll_tim_get_module_state_address );

    const hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    if ( low_level_handle->init_ll_state == false ) {
        _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );
        low_level_handle->init_ll_state = true;
    }

    tmp_duty = duty_ratio * 100;
    max_period = hal_ll_tim_hw_specifics_map_local->max_period;

    max_duty = ( ( float )max_period / 100 ) * tmp_duty;

    val = ( uint16_t )( max_duty * ( *( uint8_t * )tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_pr_reg_addr + 1 ) ) >> 6;
    temp = ( uint8_t )( ( val << 4 ) & HAL_LL_TIM_DC_LSBITS );

    write_reg(hal_ll_hw_reg->hal_ccprl_reg_addr, max_duty);

    write_reg_bitwise_and( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_NIBBLE_LOW_8BIT );

    write_reg_bitwise_or(hal_ll_hw_reg->hal_ccpcon_reg_addr, temp);

    #ifdef PSTRXCON_REG_NOT_AVAILABLE
    // If selected pin doesn't have PSTRxCON register, but this pin is Enhanced PWM pin, with output driver D circuit, enable it.
    if ( HAL_LL_TIM_PULSE_STEERING_CONTROL_D == hal_ll_tim_hw_specifics_map_local->steering ) {
        set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_ENHANCED_PWM_STRD_BIT );
    // Else, if selected pin doesn't have PSTRxCON register, but this pin is Enhanced PWM pin, with output driver B circuit, enable it.
    } else if ( HAL_LL_TIM_PULSE_STEERING_CONTROL_B == hal_ll_tim_hw_specifics_map_local->steering ) {
        set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_ENHANCED_PWM_STRB_BIT_1 );
        set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_ENHANCED_PWM_STRB_BIT_2 );
    }
    #endif

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_tim_get_specifics( hal_ll_tim_get_module_state_address );

    const hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    set_reg_bit( tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_tcon_reg_addr, HAL_LL_TIM_TMRON_BIT );

    set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_CCP_M2 );
    set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_CCP_M3 );

    // If selected pin has PSTRxCON register, AND this pin is Enhanced PWM pin, enable its output driver circuit.
    #ifdef PSTRXCON_REG_AVAILABLE
    if ( !( HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE == hal_ll_tim_hw_specifics_map_local->steering ) ) {
        set_reg_bit( hal_ll_hw_reg->hal_pstrcon_reg_addr, hal_ll_tim_hw_specifics_map_local->steering );
    }
    #endif

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_tim_get_specifics( hal_ll_tim_get_module_state_address );

    const hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    write_reg_bitwise_and( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_NIBBLE_HIGH_8BIT );

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_tim_get_specifics( hal_ll_tim_get_module_state_address );

    if( low_level_handle->hal_ll_tim_handle != NULL ) {

        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;
        low_level_handle->init_ll_state = false;

        _hal_ll_tim_set_module_state( hal_ll_tim_hw_specifics_map_local, true );
        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, false );
        _hal_ll_pps_set_state( hal_ll_tim_hw_specifics_map_local, false );
        _hal_ll_tim_set_module_state( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;
        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->timer = 0xFF;
        hal_ll_tim_hw_specifics_map_local->module_index = HAL_LL_MODULE_ERROR;
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

static hal_ll_tim_hw_specifics_map_t *hal_ll_tim_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );
    static uint8_t hal_ll_module_error = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_tim_handle_register_t ) );

    #ifdef __XC8__
    #define REGISTER_HANDLE hal_ll_tim_handle
    #define REGISTER_HANDLE_TYPE hal_ll_tim_handle_register_t
    memory_width tmp_addr = 0;
    #if !(FSR_APPROACH)
    // On 8-bit PIC microcontrollers, pointers are often only 8 bits wide by default,
    // meaning they can only access addresses within a single memory page.
    // Circumvent this issue by concatenating the address to one 16-bit wide variable.
    memory_width *tmp_ptr, tmp_values[NUMBER_OF_BYTES] = {0};
    REGISTER_HANDLE_TYPE *handle_register = (REGISTER_HANDLE_TYPE *)handle;
    memory_width current_addr = &handle_register->REGISTER_HANDLE;

    for (uint8_t i = 0; i < NUMBER_OF_BYTES; i++) {
        current_addr += i;
        tmp_values[i] = read_reg(current_addr);
    }

    current_addr = 0;
    for (uint8_t i=0; i<NUMBER_OF_BYTES; i++) {
        current_addr = current_addr | (tmp_values[i] << (8*i));
    }
    #else
    /**
     * @brief Alternate approach with indirect register access.
     */
    memory_width *tmp_ptr, current_addr = 0;
    REGISTER_HANDLE_TYPE *handle_register = (REGISTER_HANDLE_TYPE *)handle;
    FSR0 = &handle_register->hal_ll_tim_handle;
    for (uint8_t i=0; i<NUMBER_OF_BYTES; i++) {
        current_addr = current_addr | (read_reg(FSR0++) << (8*i));
    }
    #endif
    tmp_ptr = current_addr;
    current_addr = *tmp_ptr;
    #endif

    while( hal_ll_module_count-- ) {
        #ifdef __XC8__
        tmp_addr = &hal_ll_tim_hw_specifics_map[hal_ll_module_count];
        if (current_addr == tmp_addr) {
            return &hal_ll_tim_hw_specifics_map[hal_ll_module_count];
        }
        #else
        if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base ) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
        }
        #endif
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

#ifdef CCP_MODULE_1
#ifdef HAL_LL_PMD_CCP_MODULE_1
static inline void _hal_ll_tim1_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_1, HAL_LL_PMD_CCP_MODULE_1_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_1, HAL_LL_PMD_CCP_MODULE_1_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_2
#ifdef HAL_LL_PMD_CCP_MODULE_2
static inline void _hal_ll_tim2_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_2, HAL_LL_PMD_CCP_MODULE_2_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_2, HAL_LL_PMD_CCP_MODULE_2_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_3
#ifdef HAL_LL_PMD_CCP_MODULE_3
static inline void _hal_ll_tim3_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_3, HAL_LL_PMD_CCP_MODULE_3_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_3, HAL_LL_PMD_CCP_MODULE_3_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_4
#ifdef HAL_LL_PMD_CCP_MODULE_4
static inline void _hal_ll_tim4_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_4, HAL_LL_PMD_CCP_MODULE_4_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_4, HAL_LL_PMD_CCP_MODULE_4_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_5
#ifdef HAL_LL_PMD_CCP_MODULE_5
static inline void _hal_ll_tim5_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_5, HAL_LL_PMD_CCP_MODULE_5_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_5, HAL_LL_PMD_CCP_MODULE_5_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_6
#ifdef HAL_LL_PMD_CCP_MODULE_6
static inline void _hal_ll_tim6_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_6, HAL_LL_PMD_CCP_MODULE_6_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_6, HAL_LL_PMD_CCP_MODULE_6_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_7
#ifdef HAL_LL_PMD_CCP_MODULE_7
static inline void _hal_ll_tim7_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_7, HAL_LL_PMD_CCP_MODULE_7_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_7, HAL_LL_PMD_CCP_MODULE_7_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_8
#ifdef HAL_LL_PMD_CCP_MODULE_8
static inline void _hal_ll_tim8_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_8, HAL_LL_PMD_CCP_MODULE_8_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_8, HAL_LL_PMD_CCP_MODULE_8_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_9
#ifdef HAL_LL_PMD_CCP_MODULE_9
static inline void _hal_ll_tim9_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_9, HAL_LL_PMD_CCP_MODULE_9_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_9, HAL_LL_PMD_CCP_MODULE_9_ENABLE_BIT );
    }
}
#endif
#endif

#ifdef CCP_MODULE_10
#ifdef HAL_LL_PMD_CCP_MODULE_10
static inline void _hal_ll_tim10_enable_module( bool hal_ll_state ) {
    if ( hal_ll_state ) {
        clear_reg_bit( HAL_LL_PMD_CCP_MODULE_10, HAL_LL_PMD_CCP_MODULE_10_ENABLE_BIT );
    } else {
        set_reg_bit( HAL_LL_PMD_CCP_MODULE_10, HAL_LL_PMD_CCP_MODULE_10_ENABLE_BIT );
    }
}
#endif
#endif

static void _hal_ll_tim_set_module_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

    switch ( map->module_index + 1 ) {
        #ifdef CCP_MODULE_1
        #ifdef HAL_LL_PMD_CCP_MODULE_1
        case CCP_MODULE_1:
            _hal_ll_tim1_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_2
        #ifdef HAL_LL_PMD_CCP_MODULE_2
        case CCP_MODULE_2:
            _hal_ll_tim2_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_3
        #ifdef HAL_LL_PMD_CCP_MODULE_3
        case CCP_MODULE_3:
            _hal_ll_tim3_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_4
        #ifdef HAL_LL_PMD_CCP_MODULE_4
        case CCP_MODULE_4:
            _hal_ll_tim4_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_5
        #ifdef HAL_LL_PMD_CCP_MODULE_5
        case CCP_MODULE_5:
            _hal_ll_tim5_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_6
        #ifdef HAL_LL_PMD_CCP_MODULE_6
        case CCP_MODULE_6:
            _hal_ll_tim6_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_7
        #ifdef HAL_LL_PMD_CCP_MODULE_7
        case CCP_MODULE_7:
            _hal_ll_tim7_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_8
        #ifdef HAL_LL_PMD_CCP_MODULE_8
        case CCP_MODULE_8:
            _hal_ll_tim8_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_9
        #ifdef HAL_LL_PMD_CCP_MODULE_9
        case CCP_MODULE_9:
            _hal_ll_tim9_enable_module( hal_ll_state );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_10
        #ifdef HAL_LL_PMD_CCP_MODULE_10
        case CCP_MODULE_10:
            _hal_ll_tim10_enable_module( hal_ll_state );
            break;
        #endif
        #endif
    }
}

static void _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t pin;
    const hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    // Enhanced PWM pins need additional mode set in order for pin to be set to LOW voltage level.
    if ( !( HAL_LL_TIM_PULSE_STEERING_CONTROL_NONE == hal_ll_tim_hw_specifics_map_local->steering ) ) {
        set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_CCP_M2 );
        set_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_CCP_M3 );
        set_reg_bit( hal_ll_hw_reg->hal_pstrcon_reg_addr, hal_ll_tim_hw_specifics_map_local->steering );
    }

    if ( hal_ll_state ) {
        hal_ll_gpio_configure_pin( &pin, map->pin, HAL_LL_GPIO_DIGITAL_OUTPUT );
    } else {
        hal_ll_gpio_configure_pin( &pin, map->pin, HAL_LL_GPIO_DIGITAL_INPUT );
    }
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Memorize PWM pin.
    hal_ll_tim_hw_specifics_map[ module_index ].pin = _tim_map[ index ].pin;

    // Memorize Timer for PWM usage.
    hal_ll_tim_hw_specifics_map[ module_index ].timer = _tim_map[ index ].timer;

    // Memorize Enhanced PWM bit position.
    hal_ll_tim_hw_specifics_map[ module_index ].steering = _tim_map[ index ].steering;
}

static hal_ll_pps_err_t _hal_ll_pps_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {

    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( map->pin != HAL_LL_PIN_NC ) {
        hal_ll_status = hal_ll_pps_map(
            ( map->pin & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4,
            map->pin & HAL_LL_NIBBLE_LOW_8BIT,
            HAL_LL_GPIO_DIGITAL_OUTPUT,
            HAL_LL_PPS_FUNCTIONALITY_PWM,
            map->hal_ll_pps_module_index, hal_ll_state
        );
    }

    if ( hal_ll_status != HAL_LL_PPS_SUCCESS ) {
        return hal_ll_status;
    }

    return hal_ll_status;
}

/* TODO
 * The following code is selection of CCP modules based on TIM2.
 * Currently all modules work via TIM2.
 * This means that if you are working with multiple objects at the same time,
 * the settings for frequency and max period, for all objects,
 * will always be as configured for the last object used.
 * CCP modules based on other Timers will be implemented in a future release.
*/
static void _hal_ll_tim_select_timer( hal_ll_tim_hw_specifics_map_t *map ) {

    switch ( map->module_index + 1 ) {
        #ifdef CCP_MODULE_1
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_1
        case CCP_MODULE_1:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_1, HAL_LL_CCP_MODULE_1_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_2
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_2
        case CCP_MODULE_2:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_2, HAL_LL_CCP_MODULE_2_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_3
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_3
        case CCP_MODULE_3:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_3, HAL_LL_CCP_MODULE_3_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_4
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_4
        case CCP_MODULE_4:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_4, HAL_LL_CCP_MODULE_4_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_5
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_5
        case CCP_MODULE_5:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_5, HAL_LL_CCP_MODULE_5_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_6
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_6
        case CCP_MODULE_6:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_6, HAL_LL_CCP_MODULE_6_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_7
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_7
        case CCP_MODULE_7:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_7, HAL_LL_CCP_MODULE_7_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_8
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_8
        case CCP_MODULE_8:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_8, HAL_LL_CCP_MODULE_8_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_9
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_9
        case CCP_MODULE_9:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_9, HAL_LL_CCP_MODULE_9_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif

        #ifdef CCP_MODULE_10
        #ifdef HAL_LL_CCPTMRS_CCP_MODULE_10
        case CCP_MODULE_10:
            set_reg_bits( HAL_LL_CCPTMRS_CCP_MODULE_10, HAL_LL_CCP_MODULE_10_TIM2_ENABLE_BIT );
            break;
        #endif
        #endif
    }
}

static void _hal_tim_reset_duty_cycle_bits( hal_ll_tim_hw_specifics_map_t *map ) {

    const hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    clear_reg( hal_ll_hw_reg->hal_ccprl_reg_addr );

    clear_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_DC_B0 );
    clear_reg_bit( hal_ll_hw_reg->hal_ccpcon_reg_addr, HAL_LL_TIM_DC_B1 );
}

static void _hal_ll_tim_hw_odcon_set( hal_ll_tim_hw_specifics_map_t *map ) {
    static uint8_t odcon_map_size = sizeof( odconx_map ) / sizeof( hal_ll_odconx_t );
    uint8_t list_index;

    for( list_index = 0; list_index < odcon_map_size; list_index++ ) {
        if ( odconx_map[ list_index ].is_odconx_numeric == HAL_LL_HW_MODULES_DEFAULT ) {
            if ( ( odconx_map[ list_index ].pin == map->pin ) ) {
                clear_reg_bit( odconx_map[ list_index ].odcon_address, odconx_map[ list_index ].odcon_address_bit );
            }
        }else if ( odconx_map[ list_index ].is_odconx_numeric == HAL_LL_HW_MODULES_CCP )
        {
            if ( ( odconx_map[ list_index ].module_index == map->module_index ) ) {
                clear_reg_bit( odconx_map[ list_index ].odcon_address, odconx_map[ list_index ].odcon_address_bit );
            }
        }
    }
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {

    _hal_ll_tim_select_timer( map );

    map->max_period = _hal_ll_tim_desired_freq( map->freq_hz );

    write_reg( tim_regs_map[ map->timer ].hal_pr_reg_addr, map->max_period );

    write_reg( tim_regs_map[ map->timer ].hal_tcon_reg_addr, _hal_ll_tim_presc_values( map->freq_hz) );

    set_reg_bit( tim_regs_map[ map->timer ].hal_tcon_reg_addr, HAL_LL_TIM_TMRON_BIT );

    _hal_tim_reset_duty_cycle_bits( map );
}


static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {

    _hal_ll_tim_set_module_state( map, true );

    _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );

    // Used only for chips which have TIM PPS pins
    #if HAL_LL_TIM_PPS_ENABLED == true
    // Set pps functions for mapped pins
    _hal_ll_pps_set_state( map, true );
    #endif

    _hal_ll_tim_hw_odcon_set( map );

    _hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
