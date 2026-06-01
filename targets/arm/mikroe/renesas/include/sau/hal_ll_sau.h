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
 * @file  hal_ll_sau.h
 * @brief API for SAU sub-implementation of I2C and UART modules.
 */

#ifndef _HAL_LL_SAU_H_
#define _HAL_LL_SAU_H_

#include "hal_ll_target.h"
#include "hal_ll_sau_uart.h"
#include "hal_ll_sau_i2c.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

#define hal_ll_sau_module_num(_module_num) (_module_num - 1)

/**
  * @brief  Enable clock for SAU module on hardware level.
  *
  * Initializes SAU module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  module_index - SAU module index.
  * @param[in]  hal_ll_stat - True(enable clock)/False(disable clock).
  *
  * @return void None.
  */
void hal_ll_sau_set_clock( hal_ll_pin_name_t module_index, bool hal_ll_state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SAU_H_
// ------------------------------------------------------------------------- END
