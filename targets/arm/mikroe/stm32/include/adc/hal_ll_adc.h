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
 * @file  hal_ll_adc.h
 * @brief This file contains all the functions prototypes for the ADC library.
 */

#ifndef _HAL_LL_ADC_H_
#define _HAL_LL_ADC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_target.h"
#include "hal_ll_rcc.h"

#define HAL_ADC_6BIT_RES_VAL             0x003FU
#define HAL_ADC_8BIT_RES_VAL             0x00FFU
#define HAL_ADC_10BIT_RES_VAL            0x03FFU
#define HAL_ADC_12BIT_RES_VAL            0x0FFFU
#define HAL_ADC_14BIT_RES_VAL            0x3FFFU
#define HAL_ADC_16BIT_RES_VAL            0xFFFFU

/**
 * @brief ADC low level handle.
 *
 * The context for storing low level object handler.
 * User is not to change these values or unexpected behaviour
 * may occur.
 */
typedef struct
{
    handle_t *hal_ll_adc_handle;
    handle_t *hal_drv_adc_handle;
    bool init_ll_state;
} hal_ll_adc_handle_register_t;

/**
 * ADC VREF.
 */
typedef enum
{
    HAL_LL_ADC_VREF_EXTERNAL = 0,
    HAL_LL_ADC_VREF_DEFAULT = HAL_LL_ADC_VREF_EXTERNAL
} hal_ll_adc_voltage_reference_t;

/**
 * ADC resolution.
 */
typedef enum
{
    HAL_LL_ADC_RESOLUTION_NOT_SET = 0,
    HAL_LL_ADC_RESOLUTION_6_BIT,     /**< 6  bit resolution */
    HAL_LL_ADC_RESOLUTION_8_BIT,     /**< 8  bit resolution */
    HAL_LL_ADC_RESOLUTION_10_BIT,    /**< 10 bit resolution */
    HAL_LL_ADC_RESOLUTION_12_BIT,    /**< 12 bit resolution */
    HAL_LL_ADC_RESOLUTION_14_BIT,    /**< 14 bit resolution */
    HAL_LL_ADC_RESOLUTION_16_BIT,    /**< 16 bit resolution */

    /*!< Default resolution. */
    HAL_LL_ADC_RESOLUTION_DEFAULT = HAL_LL_ADC_RESOLUTION_CMAKE
} hal_ll_adc_resolution_t;

/**
 * @brief ADC low level specific structure.
 *
 * User is not to change these values or unexpected behaviour
 * may occur.
 */
typedef struct
{
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_adc_voltage_reference_t vref_input;
    float vref_value;
    uint32_t resolution;
    uint8_t channel;
} hal_ll_adc_hw_specifics_map_t;

/**
 * @brief  Configures specified module.
 *
 * Performs module configuration on the hardware
 * level.
 *
 * @param[in]  *handle HAL context object handle.
 *
 * @return  hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_module_configure_adc( handle_t *handle );

/**
 * @brief  Registers handler for future use.
 *
 * Registers low level and hal level handlers
 * for use with appropriate functions.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] pin Analog input pin.
 * @param[in] vref_input Voltage reference source.
 * @param[in] resolution Analog data resolution.
 * @param[in] *handle_map HAL layer local handle map.
 * @param[in] *hal_module_id HAL layer module number.

 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined error values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_adc_register_handle(hal_ll_pin_name_t pin, hal_ll_adc_voltage_reference_t vref_input, hal_ll_adc_resolution_t resolution, hal_ll_adc_handle_register_t *handle_map, uint8_t *hal_module_id);

/**
 * @brief  Sets ADC resolution.
 *
 * Sets specified ADC resolution for module.
 * Take into consideration that the module
 * will be re-initialized on the hardware level.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] resolution ADC resolution.
 *
 * @return hal_ll_err_t Module specific error or success.
 */
hal_ll_err_t hal_ll_adc_set_resolution(handle_t *handle, hal_ll_adc_resolution_t resolution);

/**
 * @brief  Sets ADC reference voltage source.
 *
 * Sets ADC reference voltage source for specified
 * object. Take into consideration that the module
 * will be re-initialized on the hardware level.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] vref_input ADC reference voltage source.
 *
 * @return hal_ll_err_t Module specific error or success.
 */
hal_ll_err_t hal_ll_adc_set_vref_input(handle_t *handle, hal_ll_adc_voltage_reference_t vref_input);

/**
 * @brief  Sets ADC reference voltage value.
 *
 * Sets ADC reference voltage value for specified
 * object.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] vref_input ADC reference voltage value.
 *
 * @return void None.
 */
void hal_ll_adc_set_vref_value(handle_t *handle, float vref_value);

/**
 * @brief Executes data read via ADC module.
 *
 * Function shall read raw unsigned analog value.
 *
 * @param handle ADC handle.
 * @param *readDatabuf Data buffer where read data
 *                     shall be placed.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined error values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_adc_read(handle_t *handle, uint16_t *readDatabuf );

/**
 * @brief  Closes ADC HAL and HAL_LOW_LEVEL context object.
 *
 * De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 *
 * @param[in] *handle HAL context object handle.
 *
 * @return void None.
 */
void hal_ll_adc_close( handle_t *handle );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ADC_H_
// ------------------------------------------------------------------------- END
