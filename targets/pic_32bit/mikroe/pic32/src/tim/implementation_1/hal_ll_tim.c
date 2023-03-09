/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

static volatile hal_ll_tim_handle_register_t hal_ll_module_state[ TIM_MODULE_COUNT ] = { (handle_t *)NULL, (handle_t *)NULL, false };
// ------------------------------------------------------------- PRIVATE MACROS
#define HAL_LL_TIM_PRESCALER_1                                                  0
#define HAL_LL_TIM_PRESCALER_2                                                  1
#define HAL_LL_TIM_PRESCALER_4                                                  2
#define HAL_LL_TIM_PRESCALER_8                                                  3
#define HAL_LL_TIM_PRESCALER_16                                                 4
#define HAL_LL_TIM_PRESCALER_32                                                 5
#define HAL_LL_TIM_PRESCALER_64                                                 6
#define HAL_LL_TIM_PRESCALER_256                                                7

#define HAL_LL_TIM_PRESCALER_1_VALUE                                            1
#define HAL_LL_TIM_PRESCALER_2_VALUE                                            2
#define HAL_LL_TIM_PRESCALER_4_VALUE                                            4
#define HAL_LL_TIM_PRESCALER_8_VALUE                                            8
#define HAL_LL_TIM_PRESCALER_16_VALUE                                           16
#define HAL_LL_TIM_PRESCALER_32_VALUE                                           32
#define HAL_LL_TIM_PRESCALER_64_VALUE                                           64
#define HAL_LL_TIM_PRESCALER_256_VALUE                                          256

#define HAL_LL_TCON_TCKPS                                                       4
#define HAL_LL_TIM_TMRON_BIT                                                    15
#define HAL_LL_TIM_FREQ_PRESCALER_16                                            16

#define port_mask                                                               0xF0
#define pin_mask                                                                0x0F

#define HAL_LL_TIM_START                                                        0x8006
#define HAL_LL_TIM_STOP                                                         0xFFF8

#define write_reg_bitwise_and(_reg,_val)                                        ( *(uint8_t *)_reg &= _val )
#define write_reg_bitwise_or(_reg,_val)                                         ( *(uint8_t *)_reg |= _val )

#define hal_ll_tim_get_prescaler(freq_hz)                                       (Get_Fosc_kHz())+1/freq_hz

#if defined(PIC32MZxx)
#define hal_ll_tim_get_period(freq_hz,prescaler)                                (Get_Fosc_kHz()*1000/hal_ll_clock_divisor_control_reg)/(freq_hz*prescaler) - 1
#elif defined(PIC32MXxx)
#define hal_ll_tim_get_period(freq_hz,prescaler)                                (Get_Fosc_kHz()*1000)/(freq_hz*prescaler) - 1
#endif

#define hal_ll_clock_divisor_control_reg                                        (((*(uint32_t *)HAL_LL_PB3DIV_ADDRESS) & 0x007F) + 1)

#define _hal_ll_tim_freq_formula(freq,_presc)                                   (((float)1/freq )/(((float)1/((Get_Fosc_kHz()*1000)/4))*_presc))

#define _hal_ll_tim_get_freq                                                    (float)1/(UINT8_MAX*(((float)1/((Get_Fosc_kHz()*1000)/4))*HAL_LL_TIM_FREQ_PRESCALER_16));

#define _hal_ll_tim_desired_freq(_freq)                                         (_hal_ll_tim_freq_formula(freq,1)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,1):\
                                                                                (_hal_ll_tim_freq_formula(freq,2)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,2):\
                                                                                (_hal_ll_tim_freq_formula(freq,4)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,4):\
                                                                                (_hal_ll_tim_freq_formula(freq,8)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,8):\
                                                                                (_hal_ll_tim_freq_formula(freq,16)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,16):\
                                                                                (_hal_ll_tim_freq_formula(freq,32)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,32):\
                                                                                (_hal_ll_tim_freq_formula(freq,64)<UINT16_MAX)?_hal_ll_tim_freq_formula(freq,64):\
                                                                                _hal_ll_tim_freq_formula(freq,256)

#define _hal_ll_tim_presc_values(freq)                                          (_hal_ll_tim_freq_formula(freq,1)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_1:\
                                                                                (_hal_ll_tim_freq_formula(freq,2)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_2:\
                                                                                (_hal_ll_tim_freq_formula(freq,4)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_4:\
                                                                                (_hal_ll_tim_freq_formula(freq,8)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_8:\
                                                                                (_hal_ll_tim_freq_formula(freq,16)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_16:\
                                                                                (_hal_ll_tim_freq_formula(freq,32)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_32:\
                                                                                (_hal_ll_tim_freq_formula(freq,64)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_64:\
                                                                                HAL_LL_TIM_PRESCALER_256

#define _hal_ll_tim_get_presc_value(freq)                                       (_hal_ll_tim_freq_formula(freq,1)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_1_VALUE:\
                                                                                (_hal_ll_tim_freq_formula(freq,2)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_2_VALUE:\
                                                                                (_hal_ll_tim_freq_formula(freq,4)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_4_VALUE:\
                                                                                (_hal_ll_tim_freq_formula(freq,8)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_8_VALUE:\
                                                                                (_hal_ll_tim_freq_formula(freq,16)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_16_VALUE:\
                                                                                (_hal_ll_tim_freq_formula(freq,32)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_32_VALUE:\
                                                                                (_hal_ll_tim_freq_formula(freq,64)<UINT16_MAX)?HAL_LL_TIM_PRESCALER_64_VALUE:\
                                                                                HAL_LL_TIM_PRESCALER_256_VALUE

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_tim_get_base_struct(_handle) (( hal_ll_tim_base_handle_t *)_handle) //!!
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_tim_get_module_state_address (hal_ll_tim_handle_register_t *)((hal_ll_tim_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_tim_get_handle ( hal_ll_tim_handle_register_t * )hal_ll_tim_get_module_state_address->hal_ll_tim_handle
#define hal_ll_tim_get_base_from_hal_handle ((hal_ll_tim_hw_specifics_map_t *)((low_level_handle->hal_ll_tim_handle)))->base

// -------------------------------------------------------------- PRIVATE TYPES
typedef struct
{
    uint32_t hal_tcon_reg_addr;
    uint32_t hal_tmr_reg_addr;
    uint32_t hal_pr_reg_addr;
} hal_ll_tim_regs_struct_t;

typedef struct
{
    uint32_t hal_occon_reg_addr;
    uint32_t __unused_1[3];
    uint32_t hal_ocr_reg_addr;
    uint32_t __unused_2[3];
    uint32_t hal_ocrs_reg_addr;

} hal_ll_tim_base_handle_t;

typedef struct
{
    uint32_t            base;
    hal_ll_pin_name_t   pin;
    uint16_t            max_period;
    uint32_t            freq_hz;
    uint8_t             timer;
    uint8_t             module_index;
    uint8_t             hal_ll_pps_module_index;
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
/*!< @brief PWM ( OCR ) module registers access structure */
static const hal_ll_tim_regs_struct_t tim_regs_map[] = {
    #if defined (HAL_LL_T2CON_ADDRESS) && defined (HAL_LL_PR2_ADDRESS) && defined (HAL_LL_TMR2_ADDRESS)
    { HAL_LL_T2CON_ADDRESS, HAL_LL_TMR2_ADDRESS, HAL_LL_PR2_ADDRESS },
    #endif

    #if defined (HAL_LL_T3CON_ADDRESS) && defined (HAL_LL_PR3_ADDRESS) && defined (HAL_LL_TMR3_ADDRESS)
    { HAL_LL_T3CON_ADDRESS, HAL_LL_TMR3_ADDRESS, HAL_LL_PR3_ADDRESS },
    #endif

    #if defined (HAL_LL_T4CON_ADDRESS) && defined (HAL_LL_PR4_ADDRESS) && defined (HAL_LL_TMR4_ADDRESS)
    { HAL_LL_T4CON_ADDRESS, HAL_LL_TMR4_ADDRESS, HAL_LL_PR4_ADDRESS },
    #endif

    #if defined (HAL_LL_T5CON_ADDRESS) && defined (HAL_LL_PR5_ADDRESS) && defined (HAL_LL_TMR5_ADDRESS)
    { HAL_LL_T5CON_ADDRESS, HAL_LL_TMR5_ADDRESS, HAL_LL_PR5_ADDRESS },
    #endif

    #if defined (HAL_LL_T6CON_ADDRESS) && defined (HAL_LL_PR6_ADDRESS) && defined (HAL_LL_TMR6_ADDRESS)
    { HAL_LL_T6CON_ADDRESS, HAL_LL_TMR6_ADDRESS, HAL_LL_PR6_ADDRESS },
    #endif

    #if defined (HAL_LL_T7CON_ADDRESS) && defined (HAL_LL_PR7_ADDRESS) && defined (HAL_LL_TMR7_ADDRESS)
    { HAL_LL_T7CON_ADDRESS, HAL_LL_TMR7_ADDRESS, HAL_LL_PR7_ADDRESS },
    #endif

    #if defined (HAL_LL_T8CON_ADDRESS) && defined (HAL_LL_PR8_ADDRESS) && defined (HAL_LL_TMR8_ADDRESS)
    { HAL_LL_T8CON_ADDRESS, HAL_LL_TMR8_ADDRESS, HAL_LL_PR8_ADDRESS },
    #endif

    #if defined (HAL_LL_T9CON_ADDRESS) && defined (HAL_LL_PR9_ADDRESS) && defined (HAL_LL_TMR9_ADDRESS)
    { HAL_LL_T9CON_ADDRESS, HAL_LL_TMR9_ADDRESS, HAL_LL_PR9_ADDRESS },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, }
};

static hal_ll_tim_hw_specifics_map_t hal_ll_tim_hw_specifics_map[ TIM_MODULE_COUNT + 1 ] = {
    #ifdef OCR_MODULE_1
    { HAL_LL_OC1CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_1), HAL_LL_OCR_MODULE_1 - 1 },
    #endif
    #ifdef OCR_MODULE_2
    { HAL_LL_OC2CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_2), HAL_LL_OCR_MODULE_2 - 1 },
    #endif
    #ifdef OCR_MODULE_3
    { HAL_LL_OC3CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_3), HAL_LL_OCR_MODULE_3 - 1 },
    #endif
    #ifdef OCR_MODULE_4
    { HAL_LL_OC4CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_4), HAL_LL_OCR_MODULE_4 - 1 },
    #endif
    #ifdef OCR_MODULE_5
    { HAL_LL_OC5CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_5), HAL_LL_OCR_MODULE_5 - 1 },
    #endif
    #ifdef OCR_MODULE_6
    { HAL_LL_OC6CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_6), HAL_LL_OCR_MODULE_6 - 1 },
    #endif
    #ifdef OCR_MODULE_7
    { HAL_LL_OC7CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_7), HAL_LL_OCR_MODULE_7 - 1 },
    #endif
    #ifdef OCR_MODULE_8
    { HAL_LL_OC8CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_8), HAL_LL_OCR_MODULE_8 - 1 },
    #endif
    #ifdef OCR_MODULE_9
    { HAL_LL_OC9CON_ADDRESS, HAL_LL_PIN_NC, 0, 0, 0xFF, hal_ll_tim_module_num(OCR_MODULE_9), HAL_LL_OCR_MODULE_9 - 1 },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, 0, 0, 0xFF, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC }
};

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
  * @return hal_ll_tim_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_tim_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

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
 * HAL_LL_PPS_SUCCESS -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t _hal_ll_pps_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state );

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
    uint16_t pin_check_result;
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

        #if HAL_LL_TIM_PPS_ENABLED == true
        _hal_ll_pps_set_state( &hal_ll_tim_hw_specifics_map[ pin_check_result ], true );
        #endif

        handle_map[ pin_check_result ]->init_ll_state = false;
        hal_ll_module_state[ pin_check_result ].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;
    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = ( handle_t * )&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;
    handle_map[ pin_check_result ]->hal_ll_tim_handle = ( handle_t *)&hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle ) {
    uint8_t index;
    uint16_t pin_check_result;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );

    if ( ( pin_check_result = _hal_ll_tim_check_pin( hal_ll_tim_hw_specifics_map_local->pin, &index, (void *)0 ) ) == HAL_LL_PIN_NC ) {
        return HAL_LL_TIM_WRONG_PIN;
    }

    _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_local );
    hal_ll_module_state[ pin_check_result ].hal_ll_tim_handle = (handle_t *)&hal_ll_tim_hw_specifics_map[ pin_check_result ].base;

    return HAL_LL_TIM_SUCCESS;
}

uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz ) {
    uint32_t tmp_period;
    uint32_t tmp_freq;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    low_level_handle->init_ll_state = false;

    tmp_period=_hal_ll_tim_freq_formula( freq_hz, HAL_LL_TIM_FREQ_PRESCALER_16 );
    write_reg_bitwise_and( tim_regs_map[hal_ll_tim_hw_specifics_map_local->timer].hal_tcon_reg_addr, HAL_LL_TIM_TMRON_BIT );

    clear_reg(&hal_ll_hw_reg->hal_ocrs_reg_addr);

    hal_ll_tim_stop(handle);

    if ( tmp_period > UINT16_MAX ) {
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
    float tmp_duty;
    uint32_t max_duty = 0;
    uint16_t max_period;

    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    max_period = hal_ll_tim_hw_specifics_map_local->max_period;
    tmp_duty = duty_ratio * 100;
    max_duty = ( ( float )max_period / 100 ) * tmp_duty;
    hal_ll_hw_reg->hal_ocrs_reg_addr= max_duty;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_start( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    hal_ll_hw_reg->hal_occon_reg_addr |= HAL_LL_TIM_START;

    return HAL_LL_TIM_SUCCESS;
}

hal_ll_err_t hal_ll_tim_stop( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_tim_get_module_state_address );
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( hal_ll_tim_hw_specifics_map_local->base );

    hal_ll_hw_reg->hal_occon_reg_addr &= HAL_LL_TIM_STOP;

    return HAL_LL_TIM_SUCCESS;
}

void hal_ll_tim_close( handle_t *handle ) {
    low_level_handle = hal_ll_tim_get_handle;
    hal_ll_tim_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_tim_get_module_state_address );

    if( low_level_handle->hal_ll_tim_handle != NULL ) {
        low_level_handle->hal_ll_tim_handle = NULL;
        low_level_handle->hal_drv_tim_handle = NULL;
        low_level_handle->init_ll_state = false;

        _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, false );

        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
        _hal_ll_tim_set_module_state( hal_ll_tim_hw_specifics_map_local->module_index, false );
        #endif

        hal_ll_tim_hw_specifics_map_local->freq_hz = 0;
        hal_ll_tim_hw_specifics_map_local->timer = 0xFF;
        hal_ll_tim_hw_specifics_map_local->max_period = 0;
        hal_ll_tim_hw_specifics_map_local->pin = HAL_LL_PIN_NC;
        hal_ll_tim_hw_specifics_map_local->module_index = HAL_LL_MODULE_ERROR;
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t _hal_ll_tim_check_pin( hal_ll_pin_name_t pin, uint8_t *index, hal_ll_tim_handle_register_t *handle_map  ) {
    //PIN CHECK
    uint8_t index_counter = 0;
    hal_ll_pin_name_t pin_num;
    uint8_t hal_ll_module_id = 0;
    static const uint16_t map_size = ( sizeof( _tim_map ) / sizeof( hal_ll_tim_pin_map_t ) );

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
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
         if ( hal_ll_tim_get_base_from_hal_handle == hal_ll_tim_hw_specifics_map [ hal_ll_module_count ].base ) {
            return &hal_ll_tim_hw_specifics_map[ hal_ll_module_count ];
         }
    }

    return &hal_ll_tim_hw_specifics_map[ hal_ll_module_error ];
}

static void _hal_ll_tim_set_module_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index + 1 ) {
        #ifdef HAL_LL_PMD3_ADDRESS
            #ifdef OCR_MODULE_1
            case OCR_MODULE_1:
                    if ( hal_ll_state ) {
                        clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC1MD_ENABLE_BIT );
                    } else {
                        set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC1MD_ENABLE_BIT );
                    }
                break;
            #endif

            #ifdef OCR_MODULE_2
            case OCR_MODULE_2:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC2MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC2MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_3
            case OCR_MODULE_3:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC3MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC3MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_4
            case OCR_MODULE_4:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC4MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC4MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_5
            case OCR_MODULE_5:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC5MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC5MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_6
            case OCR_MODULE_6:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC6MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC6MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_7
            case OCR_MODULE_7:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC7MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC7MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_8
            case OCR_MODULE_8:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC8MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC8MD_ENABLE_BIT );
                }
                break;
            #endif

            #ifdef OCR_MODULE_9
            case OCR_MODULE_9:
                if ( hal_ll_state ) {
                    clear_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC9MD_ENABLE_BIT );
                } else {
                    set_reg_bit( HAL_LL_PMD3_ADDRESS, HAL_LL_OC9MD_ENABLE_BIT );
                }
                break;
            #endif
        #endif

            default:
                break;
    }
}

static void _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_gpio_pin_t pin;

    if ( hal_ll_state ) {
        hal_ll_gpio_configure_pin( &pin, map->pin, HAL_LL_GPIO_DIGITAL_OUTPUT );
    } else {
        hal_ll_gpio_configure_pin( &pin, map->pin, HAL_LL_GPIO_DIGITAL_INPUT );
    }
}

static hal_ll_pps_err_t _hal_ll_pps_set_state( hal_ll_tim_hw_specifics_map_t *map, bool hal_ll_state ) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ( map->pin != HAL_LL_PIN_NC ) {
        hal_ll_status = hal_ll_pps_map( ( map->pin & port_mask ) >> 4, map->pin & pin_mask, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_PWM, map->hal_ll_pps_module_index, hal_ll_state );
    }

    if ( hal_ll_status != HAL_LL_PPS_SUCCESS ) {
        return hal_ll_status;
    }

    return hal_ll_status;
}

static void _hal_ll_tim_map_pin( uint8_t module_index, uint8_t index ) {
    // Map new pins
    hal_ll_tim_hw_specifics_map[ module_index ].pin = _tim_map[ index ].pin;
    hal_ll_tim_hw_specifics_map[ module_index ].timer = _tim_map[ index ].timer;
}

static void _hal_ll_tim_hw_init( hal_ll_tim_hw_specifics_map_t *map ) {
    uint16_t temp_prescaler,timer_presc;
    hal_ll_tim_base_handle_t *hal_ll_hw_reg = hal_ll_tim_get_base_struct( map->base );

    hal_ll_hw_reg->hal_ocr_reg_addr = 0;
    hal_ll_hw_reg->hal_ocrs_reg_addr  = 0;
    hal_ll_hw_reg->hal_occon_reg_addr = 0;

    timer_presc = _hal_ll_tim_get_presc_value( map->freq_hz );
    temp_prescaler = _hal_ll_tim_presc_values( map->freq_hz );

    *( uint32_t * )tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_pr_reg_addr = hal_ll_tim_get_period(map->freq_hz,timer_presc);
    map->max_period = hal_ll_tim_get_period(map->freq_hz,timer_presc);

    *( uint32_t * )tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_tmr_reg_addr = 0;
    *( uint32_t * )tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_tcon_reg_addr = 0;
    *( uint32_t * )tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_tcon_reg_addr |= temp_prescaler << HAL_LL_TCON_TCKPS;

     set_reg_bit( tim_regs_map[ hal_ll_tim_hw_specifics_map_local->timer ].hal_tcon_reg_addr, HAL_LL_TIM_TMRON_BIT );
}

static void _hal_ll_tim_init( hal_ll_tim_hw_specifics_map_t *map ) {
    #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
    _hal_ll_tim_set_module_state( map, true );
    #endif

    _hal_ll_tim_configure_pin( hal_ll_tim_hw_specifics_map_local, true );

    // Used only for chips which have TIM PPS pins
    #if HAL_LL_TIM_PPS_ENABLED == true
    // Set pps functions for mapped pins
    _hal_ll_pps_set_state( map, true );
    #endif

    _hal_ll_tim_hw_init( map );
}
// ------------------------------------------------------------------------- END
