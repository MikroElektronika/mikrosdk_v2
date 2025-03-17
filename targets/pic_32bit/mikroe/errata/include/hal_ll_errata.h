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
 * @file  hal_ll_errata.h
 * @brief This file contains all function prototypes for the low level ERRATA library functions.
 *        These functions are chip specific.
 */

#ifndef _HAL_LL_ERRATA_H_
#define _HAL_LL_ERRATA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_i2c_master.h"
#include "hal_ll_bit_control.h"
#include "hal_ll_gpio.h"

#ifdef PIC32MZxEC_ERRATA
/**
 * @brief Implements a software-based Stop condition.
 *
 * Implements a software-based Stop condition
 * by manually controlling the SDA and SCL pins
 * and using software delays to ensure proper timing,
 * necessary due to a silicon issue.
 *
 * @param[in] hal_ll_pin_name_t SCL pin
 * @param[in] hal_ll_pin_name_t SDA pin
 * @param[in] uint32_t Delay time period
 * @param[in] uint32_t I2CxCON register address
 *
 * @return void None.
 */
void hal_ll_errata_i2c_master_stop( hal_ll_pin_name_t scl_pin, hal_ll_pin_name_t sda_pin, uint32_t delay_time, uint32_t i2ccon_reg );
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ERRATA_H_
// ------------------------------------------------------------------------- END
