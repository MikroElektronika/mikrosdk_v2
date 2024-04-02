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
 * @brief TIMER HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_tim.h"
#include "hal_ll_gpio.h"
#include "hal_ll_tim_pin_map.h"
#include "hal_ll_pps.h"

static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ] = { ( handle_t * )NULL, ( handle_t * )NULL, false };
// ------------------------------------------------------------- PRIVATE MACROS
#define HAL_LL_TIM_PRESCALER_1                                                  (0)
#define HAL_LL_TIM_PRESCALER_8                                                  (1)
#define HAL_LL_TIM_PRESCALER_64                                                 (2)
#define HAL_LL_TIM_PRESCALER_256                                                (3)

#define HAL_LL_TIM_PRESCALER_VALUE_1                                            (1)
#define HAL_LL_TIM_PRESCALER_VALUE_8                                            (8)
#define HAL_LL_TIM_PRESCALER_VALUE_64                                           (64)
#define HAL_LL_TIM_PRESCALER_VALUE_256                                          (256)

#define HAL_LL_TCON_TCKPS                                                       (4)
#define HAL_LL_TIM_TMRON_BIT                                                    (15)
#define HAL_LL_TIM_FREQ_PRESCALER_1                                             (1)

#define HAL_LL_TIM_START                                                        (0x0006)
#define HAL_LL_TIM_STOP                                                         (0xFFF8)

#define HAL_LL_TIM_NOT_VALID                                                    (0)

#define HAL_LL_OCXCON2_VALUE                                                    (0x001F)

#ifdef HAL_LL_TIM_IMP_1
#define HAL_LL_SELECT_TIM_2                                                     (0x0000)
#define HAL_LL_SELECT_TIM_3                                                     (0x0008)
#else
#define HAL_LL_SELECT_TIM_1                                                     (0x1000)
#define HAL_LL_SELECT_TIM_2                                                     (0x0000)
#define HAL_LL_SELECT_TIM_3                                                     (0x0400)
#define HAL_LL_SELECT_TIM_5                                                     (0x0C00)
#define HAL_LL_SELECT_TIM_4                                                     (0x0800)
#endif

#define write_reg_bitwise_and(_reg,_val)                                        ( *(uint16_t *)_reg &= _val )
#define write_reg_bitwise_or(_reg,_val)                                         ( *(uint16_t *)_reg |= _val )

#define hal_ll_tim_get_period(freq_hz,prescaler)                                (Get_Fosc_kHz()*TIM_DIV_CONST)/(freq_hz*prescaler) - 1

#define _hal_ll_tim_freq_formula(freq,_presc)                                   (((float)1/freq )/(((float)1/((Get_Fosc_kHz()*1000UL)/4))*_presc))

#define _hal_ll_tim_get_freq                                                    (float)1/(UINT16_MAX*(((float)1/((Get_Fosc_kHz()*1000UL)/4))*HAL_LL_TIM_FREQ_PRESCALER_1));

#define _hal_ll_tim_presc_values(freq)                                          (_hal_ll_tim_freq_formula(freq,1)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_1:\
                                                                                (_hal_ll_tim_freq_formula(freq,8)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_8:\
                                                                                (_hal_ll_tim_freq_formula(freq,64)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_64:\
                                                                                HAL_LL_TIM_PRESCALER_256

#define _hal_ll_tim_get_presc_value(freq)                                       (_hal_ll_tim_freq_formula(freq,1)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_VALUE_1:\
                                                                                (_hal_ll_tim_freq_formula(freq,8)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_VALUE_8:\
                                                                                (_hal_ll_tim_freq_formula(freq,64)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_VALUE_64:\
                                                                                HAL_LL_TIM_PRESCALER_VALUE_256

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address (hal_ll_tim_handle_register_t *)((hal_ll_tim_handle_register_t *)*handle)

/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle

/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((hal_ll_tim_handle_register_t *)\
                                            (((hal_ll_tim_handle_register_t *)(handle))->hal_ll_tim_handle))->hal_ll_tim_handle)->base

/*!< @brief Helper macros for defining non-existent Timer Registers. */
#if !defined ( HAL_LL_T1CON_REG_ADDRESS ) || !defined ( HAL_LL_TMR1_REG_ADDRESS ) || !defined ( HAL_LL_PR1_REG_ADDRESS )
    #define HAL_LL_T1CON_REG_ADDRESS (0)
    #define HAL_LL_TMR1_REG_ADDRESS (0)
    #define HAL_LL_PR1_REG_ADDRESS (0)
#endif
#if !defined ( HAL_LL_T2CON_REG_ADDRESS ) || !defined ( HAL_LL_TMR2_REG_ADDRESS ) || !defined ( HAL_LL_PR2_REG_ADDRESS )
    #define HAL_LL_T2CON_REG_ADDRESS (0)
    #define HAL_LL_TMR2_REG_ADDRESS (0)
    #define HAL_LL_PR2_REG_ADDRESS (0)
#endif
#if !defined ( HAL_LL_T3CON_REG_ADDRESS ) || !defined ( HAL_LL_TMR3_REG_ADDRESS ) || !defined ( HAL_LL_PR3_REG_ADDRESS )
    #define HAL_LL_T3CON_REG_ADDRESS (0)
    #define HAL_LL_TMR3_REG_ADDRESS (0)
    #define HAL_LL_PR3_REG_ADDRESS (0)
#endif
#if !defined ( HAL_LL_T4CON_REG_ADDRESS ) || !defined ( HAL_LL_TMR4_REG_ADDRESS ) || !defined ( HAL_LL_PR4_REG_ADDRESS )
    #define HAL_LL_T4CON_REG_ADDRESS (0)
    #define HAL_LL_TMR4_REG_ADDRESS (0)
    #define HAL_LL_PR4_REG_ADDRESS (0)
#endif
#if !defined ( HAL_LL_T5CON_REG_ADDRESS ) || !defined ( HAL_LL_TMR5_REG_ADDRESS ) || !defined ( HAL_LL_PR5_REG_ADDRESS )
    #define HAL_LL_T5CON_REG_ADDRESS (0)
    #define HAL_LL_TMR5_REG_ADDRESS (0)
    #define HAL_LL_PR5_REG_ADDRESS (0)
#endif

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief TIM register structure. */
typedef struct {
    hal_ll_base_addr_t hal_tcon_reg_addr;
    hal_ll_base_addr_t hal_tmr_reg_addr;
    hal_ll_base_addr_t hal_pr_reg_addr;
} hal_ll_tim_regs_struct_t;

/*!< @brief Output Compare register structure. */
typedef struct {
    hal_ll_base_addr_t hal_occon_reg_addr;
    hal_ll_base_addr_t hal_occon2_reg_addr;
    hal_ll_base_addr_t hal_ocr_reg_addr;
    hal_ll_base_addr_t hal_ocrs_reg_addr;
} hal_ll_tim_base_handle_t;

/*!< @brief TIM hw specific structure */
typedef struct {
    const hal_ll_tim_base_handle_t  *base;
    hal_ll_pin_name_t   pin;
    uint16_t            max_period;
    uint32_t            freq_hz;
    const hal_ll_tim_regs_struct_t  *timer;
    uint8_t             module_index;
    uint8_t             hal_ll_pps_module_index;
} hal_ll_tim_hw_specifics_map_t;

/*!< @brief TIM hw specific error values */
typedef enum {
    HAL_LL_TIM_SUCCESS = 0,
    HAL_LL_TIM_MODULE_ERROR,
    HAL_LL_TIM_WRONG_PIN,

    HAL_LL_TIM_ERROR = (-1)
} hal_ll_tim_err_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief Timer registers access structure */
static const hal_ll_tim_regs_struct_t tim_regs_map[] = {
    #if defined (HAL_LL_T1CON_REG_ADDRESS) && defined (HAL_LL_TMR1_REG_ADDRESS) && defined (HAL_LL_PR1_REG_ADDRESS)
    { HAL_LL_T1CON_REG_ADDRESS, HAL_LL_TMR1_REG_ADDRESS, HAL_LL_PR1_REG_ADDRESS },
    #endif

    #if defined (HAL_LL_T2CON_REG_ADDRESS) && defined (HAL_LL_TMR2_REG_ADDRESS) && defined (HAL_LL_PR2_REG_ADDRESS)
    { HAL_LL_T2CON_REG_ADDRESS, HAL_LL_TMR2_REG_ADDRESS, HAL_LL_PR2_REG_ADDRESS },
    #endif

    #if defined (HAL_LL_T3CON_REG_ADDRESS) && defined (HAL_LL_TMR3_REG_ADDRESS) && defined (HAL_LL_PR3_REG_ADDRESS)
    { HAL_LL_T3CON_REG_ADDRESS, HAL_LL_TMR3_REG_ADDRESS, HAL_LL_PR3_REG_ADDRESS },
    #endif

    #if defined (HAL_LL_T4CON_REG_ADDRESS) && defined (HAL_LL_TMR4_REG_ADDRESS) && defined (HAL_LL_PR4_REG_ADDRESS)
    { HAL_LL_T4CON_REG_ADDRESS, HAL_LL_TMR4_REG_ADDRESS, HAL_LL_PR4_REG_ADDRESS },
    #endif

    #if defined (HAL_LL_T5CON_REG_ADDRESS) && defined (HAL_LL_TMR5_REG_ADDRESS) && defined (HAL_LL_PR5_REG_ADDRESS)
    { HAL_LL_T5CON_REG_ADDRESS, HAL_LL_TMR5_REG_ADDRESS, HAL_LL_PR5_REG_ADDRESS },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC },
};

/*!< @brief PWM ( CCP ) registers access structure */
static const hal_ll_tim_base_handle_t tim_ll_reg_offsets[] = {
    #ifdef HAL_LL_TIM_IMP_1
    #ifdef HAL_LL_OC1CON_REG_ADDRESS
    { HAL_LL_OC1CON_REG_ADDRESS, NULL, HAL_LL_OC1R_REG_ADDRESS, HAL_LL_OC1RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC2CON_REG_ADDRESS
    { HAL_LL_OC2CON_REG_ADDRESS, NULL, HAL_LL_OC2R_REG_ADDRESS, HAL_LL_OC2RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC3CON_REG_ADDRESS
    { HAL_LL_OC3CON_REG_ADDRESS, NULL, HAL_LL_OC3R_REG_ADDRESS, HAL_LL_OC3RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC4CON_REG_ADDRESS
    { HAL_LL_OC4CON_REG_ADDRESS, NULL, HAL_LL_OC4R_REG_ADDRESS, HAL_LL_OC4RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC5CON_REG_ADDRESS
    { HAL_LL_OC5CON_REG_ADDRESS, NULL, HAL_LL_OC5R_REG_ADDRESS, HAL_LL_OC5RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC6CON_REG_ADDRESS
    { HAL_LL_OC6CON_REG_ADDRESS, NULL, HAL_LL_OC6R_REG_ADDRESS, HAL_LL_OC6RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC7CON_REG_ADDRESS
    { HAL_LL_OC7CON_REG_ADDRESS, NULL, HAL_LL_OC7R_REG_ADDRESS, HAL_LL_OC7RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC8CON_REG_ADDRESS
    { HAL_LL_OC8CON_REG_ADDRESS, NULL, HAL_LL_OC8R_REG_ADDRESS, HAL_LL_OC8RS_REG_ADDRESS },
    #endif
    #endif
    #ifdef HAL_LL_TIM_IMP_2
    #ifdef HAL_LL_OC1CON1_REG_ADDRESS
    { HAL_LL_OC1CON1_REG_ADDRESS, HAL_LL_OC1CON2_REG_ADDRESS, HAL_LL_OC1R_REG_ADDRESS, HAL_LL_OC1RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC2CON1_REG_ADDRESS
    { HAL_LL_OC2CON1_REG_ADDRESS, HAL_LL_OC2CON2_REG_ADDRESS, HAL_LL_OC2R_REG_ADDRESS, HAL_LL_OC2RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC3CON1_REG_ADDRESS
    { HAL_LL_OC3CON1_REG_ADDRESS, HAL_LL_OC3CON2_REG_ADDRESS, HAL_LL_OC3R_REG_ADDRESS, HAL_LL_OC3RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC4CON1_REG_ADDRESS
    { HAL_LL_OC4CON1_REG_ADDRESS, HAL_LL_OC4CON2_REG_ADDRESS, HAL_LL_OC4R_REG_ADDRESS, HAL_LL_OC4RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC5CON1_REG_ADDRESS
    { HAL_LL_OC5CON1_REG_ADDRESS, HAL_LL_OC5CON2_REG_ADDRESS, HAL_LL_OC5R_REG_ADDRESS, HAL_LL_OC5RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC6CON1_REG_ADDRESS
    { HAL_LL_OC6CON1_REG_ADDRESS, HAL_LL_OC6CON2_REG_ADDRESS, HAL_LL_OC6R_REG_ADDRESS, HAL_LL_OC6RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC7CON1_REG_ADDRESS
    { HAL_LL_OC7CON1_REG_ADDRESS, HAL_LL_OC7CON2_REG_ADDRESS, HAL_LL_OC7R_REG_ADDRESS, HAL_LL_OC7RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC8CON1_REG_ADDRESS
    { HAL_LL_OC8CON1_REG_ADDRESS, HAL_LL_OC8CON2_REG_ADDRESS, HAL_LL_OC8R_REG_ADDRESS, HAL_LL_OC8RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC9CON1_REG_ADDRESS
    { HAL_LL_OC9CON1_REG_ADDRESS, HAL_LL_OC9CON2_REG_ADDRESS, HAL_LL_OC9R_REG_ADDRESS, HAL_LL_OC9RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC10CON1_REG_ADDRESS
    { HAL_LL_OC10CON1_REG_ADDRESS, HAL_LL_OC10CON2_REG_ADDRESS, HAL_LL_OC10R_REG_ADDRESS, HAL_LL_OC10RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC11CON1_REG_ADDRESS
    { HAL_LL_OC11CON1_REG_ADDRESS, HAL_LL_OC11CON2_REG_ADDRESS, HAL_LL_OC11R_REG_ADDRESS, HAL_LL_OC11RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC12CON1_REG_ADDRESS
    { HAL_LL_OC12CON1_REG_ADDRESS, HAL_LL_OC12CON2_REG_ADDRESS, HAL_LL_OC12R_REG_ADDRESS, HAL_LL_OC12RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC13CON1_REG_ADDRESS
    { HAL_LL_OC13CON1_REG_ADDRESS, HAL_LL_OC13CON2_REG_ADDRESS, HAL_LL_OC13R_REG_ADDRESS, HAL_LL_OC13RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC14CON1_REG_ADDRESS
    { HAL_LL_OC14CON1_REG_ADDRESS, HAL_LL_OC14CON2_REG_ADDRESS, HAL_LL_OC14R_REG_ADDRESS, HAL_LL_OC14RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC15CON1_REG_ADDRESS
    { HAL_LL_OC15CON1_REG_ADDRESS, HAL_LL_OC15CON2_REG_ADDRESS, HAL_LL_OC15R_REG_ADDRESS, HAL_LL_OC15RS_REG_ADDRESS },
    #endif
    #ifdef HAL_LL_OC16CON1_REG_ADDRESS
    { HAL_LL_OC16CON1_REG_ADDRESS, HAL_LL_OC16CON2_REG_ADDRESS, HAL_LL_OC16R_REG_ADDRESS, HAL_LL_OC16RS_REG_ADDRESS },
    #endif
    #endif
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief TIM specific info */
static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[] = {
    #ifdef CCP_MODULE_1
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_1 ), HAL_LL_CCP_MODULE_1 - 1 },
    #endif
    #ifdef CCP_MODULE_2
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_2 ), HAL_LL_CCP_MODULE_2 - 1 },
    #endif
    #ifdef CCP_MODULE_3
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_3 ), HAL_LL_CCP_MODULE_3 - 1 },
    #endif
    #ifdef CCP_MODULE_4
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_4 ), HAL_LL_CCP_MODULE_4 - 1 },
    #endif
    #ifdef CCP_MODULE_5
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_5 ), HAL_LL_CCP_MODULE_5 - 1 },
    #endif
    #ifdef CCP_MODULE_6
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_6 ), HAL_LL_CCP_MODULE_6 - 1 },
    #endif
    #ifdef CCP_MODULE_7
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_7 ), HAL_LL_CCP_MODULE_7 - 1 },
    #endif
    #ifdef CCP_MODULE_8
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_8 ), HAL_LL_CCP_MODULE_8 - 1 },
    #endif
    #ifdef CCP_MODULE_9
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_9 ), HAL_LL_CCP_MODULE_9 - 1 },
    #endif
    #ifdef CCP_MODULE_10
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], hal_ll_tim_module_num( CCP_MODULE_10 ), HAL_LL_CCP_MODULE_10 - 1 },
    #endif
    { &tim_ll_reg_offsets[ HAL_LL_CCP_CHANNEL_NOT_SET ], HAL_LL_PIN_NC, 0, 0, &tim_regs_map[ HAL_LL_TIM_INDEX_NOT_SET ], HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC }
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_tim_handle_register_t  *low_level_handle;
static volatile hal_ll_tim_hw_specifics_map_t *hal_ll_tim_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_tim_hw_specifics_map array index.
  *
  * @param  handle - Object specific context handler.
  *
  * @return hal_ll_tim_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Initialize TIM module on hardware level.
  *
  * Initializes TIM module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param  map - Object specific context handler.
  *
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
  *
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
 * @param[in]  *index Array with TIM pin map index values.
 *
 * @return hal_ll_err_t Module specific error.
 */
static hal_ll_tim_err_t _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index );

/**
  * @brief  Check if pin is adequate.
  *
  * Checks tim pin the user has passed with pre-defined
  * pin in tim map.
  *
  * @param  pin - TIM pre-defined pin name.
  * @param[out] *index - Index list address.
  * @param[out] *handle_map - TIM HAL low level handle register.
  *
  * @return hal_ll_pin_name_t Module index based on pin.
  *
  * Returns pre-defined module index from pin maps, if pin
  * is adequate.
  */
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map );

/**
 * @brief  Timer assignments for OC modules.
 *
 * @param map - Object specific context handler.
 *
 * @return none
 */
static void _hal_ll_tim_select_timer( hal_ll_tim_hw_specifics_map_t *map );

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

/**
 * @brief Set PPS state.
 *
 * Sets adequate RPORx or RPIRx register
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

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin, hal_ll_tim_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    uint8_t pin_check_result;
    uint8_t index;

    if ( HAL_LL_PIN_NC == ( pin_check_result = _hal_ll_tim_check_pin( pin, &index, handle_map ) ) ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    if ( ( hal_ll_tim_hw_specifics_map[ pin_check_result ].pin != pin ) ) {
        // Used only for chips which have TIM PPS pins
        #if HAL_LL_PWM_PPS_ENABLED == true
        // Clear previous module pps
        _hal_ll_pps_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], false );
        #endif

        if ( _hal_ll_tim_map_pin( pin_check_result, index ) ) {
            return HAL_LL_TIM_ERROR;
        }

        // Used only for chips which have TIM PPS pins
        #if HAL_LL_PWM_PPS_ENABLED == true
        // Set mapped pps
        _hal_ll_pps_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );
        #endif

        handle_map[ pin_check_result ].init_ll_state = false;
        hal_ll_module_state[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

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
    uint32_t tmp_period;
    uint32_t tmp_freq;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    low_level_handle->init_ll_state = false;

    tmp_period = hal_ll_tim_get_period( freq_hz, HAL_LL_TIM_FREQ_PRESCALER_1 );

    write_reg_bitwise_and( hal_ll_tim_hw_specifics_map_local->timer->hal_tcon_reg_addr, HAL_LL_TIM_TMRON_BIT );

    clear_reg( hal_ll_tim_hw_specifics_map_local->base->hal_ocrs_reg_addr );

    hal_ll_tim_stop( handle );

    if ( UINT16_MAX < tmp_period ) {
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
    float    tmp_duty;
    volatile uint16_t max_duty = 0;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( false == low_level_handle->init_ll_state ) {
        _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );
        low_level_handle->init_ll_state = true;
    }

    tmp_duty = duty_ratio * 100;
    max_period = hal_ll_tim_hw_specifics_map_local->max_period;

    max_duty = ( ( float )max_period / 100 ) * tmp_duty;

    #ifdef HAL_LL_TIM_IMP_2
    write_reg( hal_ll_tim_hw_specifics_map_local->base->hal_ocrs_reg_addr, max_period );
    write_reg( hal_ll_tim_hw_specifics_map_local->base->hal_ocr_reg_addr, max_duty );
    #else
    write_reg( hal_ll_tim_hw_specifics_map_local->base->hal_ocrs_reg_addr, max_duty );
    #endif

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    write_reg_bitwise_or( hal_ll_tim_hw_specifics_map_local->base->hal_occon_reg_addr, HAL_LL_TIM_START );

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    write_reg_bitwise_and( hal_ll_tim_hw_specifics_map_local->base->hal_occon_reg_addr, HAL_LL_TIM_STOP );

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( NULL != low_level_handle->hal_ll_tim_handle ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;
        low_level_handle->init_ll_state = false;

        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, false );

        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;
        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->module_index = HAL_LL_MODULE_ERROR;
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map ) {
    uint8_t pin_num;
    uint8_t index_counter = 0;
    uint8_t hal_ll_module_id = 0;
    static const uint16_t map_size = ( sizeof( _tim_map ) / sizeof( hal_ll_tim_pin_map_t ) );

    if ( HAL_LL_PIN_NC == pin ) {
        return HAL_LL_PIN_NC;
    }

    for ( pin_num = 0; pin_num < map_size; pin_num++ ) {
        if ( _tim_map[ pin_num ].pin == pin ) {
            hal_ll_module_id = _tim_map[ pin_num ].module_index;
            *index = pin_num;
            if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_tim_handle ) {
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

    while ( hal_ll_module_count-- ) {
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

static hal_ll_tim_err_t _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    hal_ll_tim_hw_specifics_map[ module_index ].pin = _tim_map[ index ].pin;
    if ( HAL_LL_TIM_NOT_VALID == tim_regs_map[ _tim_map[ index ].timer ].hal_tcon_reg_addr ) {
        return HAL_LL_TIM_MODULE_ERROR;
    }
    hal_ll_tim_hw_specifics_map[ module_index ].timer = &tim_regs_map[ _tim_map[ index ].timer ];
    hal_ll_tim_hw_specifics_map[ module_index ].hal_ll_pps_module_index = _tim_map[ index ].module_index;
    hal_ll_tim_hw_specifics_map[ module_index ].base = &tim_ll_reg_offsets[ _tim_map[ index ].channel ];

    return HAL_LL_TIM_SUCCESS;
}

static void _hal_ll_tim_select_timer( hal_ll_tim_hw_specifics_map_t *map ) {
    #ifdef HAL_LL_TIM_IMP_1
    if ( HAL_LL_T2CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_2 );

    } else if ( HAL_LL_T3CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_3 );
    }
    #else
    if ( HAL_LL_T1CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_1 );

    } else if ( HAL_LL_T2CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_2 );

    } else if ( HAL_LL_T3CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_3 );

    } else if ( HAL_LL_T4CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_4 );

    } else if ( HAL_LL_T5CON_REG_ADDRESS == map->timer->hal_tcon_reg_addr ) {
        write_reg_bitwise_or( map->base->hal_occon_reg_addr, HAL_LL_SELECT_TIM_5 );
    }
    #endif
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    uint16_t temp_prescaler, timer_prescaler;

    clear_reg( map->base->hal_ocr_reg_addr );
    clear_reg( map->base->hal_ocrs_reg_addr );
    clear_reg( map->base->hal_occon_reg_addr );

    #ifdef HAL_LL_TIM_IMP_2
    set_reg_bits( map->base->hal_occon2_reg_addr, HAL_LL_OCXCON2_VALUE );
    #endif

    timer_prescaler = _hal_ll_tim_get_presc_value( map->freq_hz );
    temp_prescaler = _hal_ll_tim_presc_values( map->freq_hz );

    write_reg( map->timer->hal_pr_reg_addr, hal_ll_tim_get_period( map->freq_hz,timer_prescaler ) );

    map->max_period = hal_ll_tim_get_period( map->freq_hz,timer_prescaler );

    clear_reg( map->timer->hal_tmr_reg_addr );
    clear_reg( map->timer->hal_tcon_reg_addr );
    write_reg_bitwise_or( map->timer->hal_tcon_reg_addr, ( temp_prescaler << HAL_LL_TCON_TCKPS ) );

    _hal_ll_tim_select_timer( map );

    set_reg_bit( map->timer->hal_tcon_reg_addr, HAL_LL_TIM_TMRON_BIT );
}

static hal_ll_pps_err_t _hal_ll_pps_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( HAL_LL_PIN_NC != map->pin ) {
        hal_ll_status = hal_ll_pps_map( ( map->pin & HAL_LL_NIBBLE_HIGH_8BIT ) >> 4, map->pin & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_PWM, map->hal_ll_pps_module_index, hal_ll_state );
    }

    if ( HAL_LL_PPS_SUCCESS != hal_ll_status ) {
        return hal_ll_status;
    }

    return hal_ll_status;
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );

    // Used only for chips which have TIM PPS pins
    #if HAL_LL_PWM_PPS_ENABLED == true
    // Set pps functions for mapped pins
    _hal_ll_pps_set_state( map, true );
    #endif

    _hal_ll_tim_hw_init( map );
}

// ------------------------------------------------------------------------- END
