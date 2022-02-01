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
 * @file hal_ll_tim.h
 * @brief Brief file description.
 */

#ifndef _HAL_LL_TIM_H_
#define _HAL_LL_TIM_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_target.h"

typedef struct
{
    handle_t *hal_ll_tim_handle;
    handle_t *hal_drv_tim_handle;
    bool init_ll_state;
} hal_ll_tim_handle_register_t;

/**
 * @brief  Registers handler for future use.
 *
 * Registers low level and hal level handlers
 * for use with appropriate functions.
 *
 * @param pin TIM pin.
 * @param handle_map HAL layer local handle map.
 * @param hal_module_id HAL layer module number.

 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined error values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_tim_register_handle( hal_ll_pin_name_t pin,
                                         hal_ll_tim_handle_register_t *handle_map, uint8_t *hal_module_id );

/**
 * @brief  Configures specified module.
 *
 * Performs module configuration on the hardware
 * level. Enables module specific clock gate and
 * sets adequate alternate function values.
 *
 * @param[in]  *handle HAL context object handle.
 *
 * @return  hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_module_configure_tim( handle_t *handle );

/**
 * @brief  Enables counter for TIM module.
 *
 * Initializes TIM module on hardware level, if not already initialized and
 * starts TIM module.
 *
 * @param handle TIM handle.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined error values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_tim_start( handle_t *handle );

/**
 * @brief  Stops counter for TIM module.
 *
 * The TIM Module needs to be initialized so that
 * the stop can be done.
 *
 * @param handle TIM handle.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined error values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_tim_stop( handle_t *handle );

/**
 * @brief  Set TIM frequency in Hertz.
 *
 * This function is used to set the TIM frequency, it
 * stops TIM module and sets duty_cycle on 0.
 * Take into consideration that the module
 * will be re-initialized on the hardware level.
 *
 * @param handle TIM handle.
 * @param freq_hz TIM frequency in hz.
 *
 * @return This function returns the frequency value in hz,
 *         to which the PWM module is set.
 *
 * @note If the frequency value is less than allowed,
 *       the frequency will be set to the lowest possible value for the specified TIM.
 */
uint32_t hal_ll_tim_set_freq( handle_t *handle, uint32_t freq_hz );

/**
 * @brief Set TIM duty cycle in percentages.
 *
 * The user should enter the duty_ratio in percentages.
 * The dut_ratio value should be between 0 and 1
 * (where 0 represents 0% and 1 represents 100%).
 *
 * @param handle TIM handle.
 * @param duty_ratio TIM duty ratio in percentages.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * @note  Returns one of pre-defined error values.
 *        Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_tim_set_duty( handle_t *handle, float duty_ratio );

/**
 * @brief  Closes TIM master HAL and HAL_LOW_LEVEL context object.
 *
 * De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 *
 * @param handle TIM handle.
 *
 * @return void None.
 */
void hal_ll_tim_close( handle_t *handle );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_TIM_H_
// ------------------------------------------------------------------------- END
