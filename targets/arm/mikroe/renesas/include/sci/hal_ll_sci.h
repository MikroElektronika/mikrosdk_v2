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
 * @file  hal_ll_sci.h
 * @brief API for SCI sub-implementation of I2C and SPI modules.
 */

#ifndef _HAL_LL_SCI_H_
#define _HAL_LL_SCI_H_

#include "hal_ll_sci_i2c.h"
#include "hal_ll_sci_spi.h"
#include "hal_ll_target.h"
#include <stdbool.h>

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_sci_module_num(_module_num) (_module_num - 1)

/**
 * @brief SCI module mode selection values.
 *
 * The context structure for determining the SCI module
 * mode of operation, which can be either I2C or SPI.
 *
 */
typedef enum
{
    HAL_LL_SCI_I2C_MODE = 0,
    HAL_LL_SCI_SPI_MODE
} hal_ll_sci_mode_t;

#ifdef __cplusplus
extern "C"{
#endif

/**
  * @brief  Enable or disable the SCI hardware module for I2C Master mode.
  *
  * Controls the clock and power state of the specified I2CSCI hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
void hal_ll_sci_module_enable( hal_ll_sci_i2c_hw_specifics_map_t *map, bool hal_ll_state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SCI_H_
// ------------------------------------------------------------------------- END
