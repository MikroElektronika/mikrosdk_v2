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
 * @file  hal_ll_pps.h
 * @brief This file contains function prototypes for LOW LEVEL HAL PPS implementation.
 */

#ifndef _HAL_LL_PPS_H_
#define _HAL_LL_PPS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_gpio_port.h"
#include "hal_ll_pps_defines.h"

/**
 * @brief  PPS pin mapping.
 *
 * Maps specfic functionality to specified pin.
 *
 * @param[in]  port_name - desired port
 * @param[in]  pin_num - desired pin
 * @param[in]  direction - Input/Output
 * @param[in]  pps_func - desired function
 * Pre-defined values:
 * HAL_LL_PPS_UART -- UART/USART module
 * HAL_LL_PPS_MSSP -- SPI/I2C module
 * HAL_LL_PPS_PWM -- TIM/PWM module
 * HAL_LL_PPS_IVT -- Interrupt mapping
 * @param[in]  module_num - module index
 * @param[in]  hal_ll_state - init/de-init
 *
 * @return hal_ll_pps_err_t - init status
 * Returns one of pre-defined values:
 * HAL_LL_PPS_SUCCESS -- init success
 * HAL_LL_PPS_DIRECTION_ERROR -- direction non-existent
 * HAL_LL_PPS_PIN_ERROR -- pin non-existent
 * HAL_LL_PPS_MODULE_ERROR -- init failed
 *
 * @note PIC ONLY
 */
hal_ll_pps_err_t hal_ll_pps_map( hal_ll_port_name_t port_name, hal_ll_pin_name_t pin_num, hal_ll_gpio_direction_t direction, hal_ll_pps_functionality_t pps_func, uint8_t module_num, bool hal_ll_state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PPS_H_
// ------------------------------------------------------------------------- END
