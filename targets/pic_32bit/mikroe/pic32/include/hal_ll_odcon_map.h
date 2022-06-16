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
 * @file  hal_ll_odcon_map.h
 * @brief HAL LOW LEVEL MAP FOR PIN/PORT ODCON REGISTERS.
 */

#ifndef _HAL_LL_ODCON_MAP_H_
#define _HAL_LL_ODCON_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

typedef enum
{
    HAL_LL_HW_MODULES_CCP = 0,
    HAL_LL_HW_MODULES_SPI,
    HAL_LL_HW_MODULES_UART,

    HAL_LL_HW_MODULES_DEFAULT = 0xFF
} hal_ll_hw_modules_t;

/*!< @brief Hal low level slew rate map structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t odcon_address_bit;
    uint8_t module_index;
    hal_ll_base_addr_t odcon_address;
    hal_ll_hw_modules_t is_odconx_numeric;
} hal_ll_odconx_t;

/*!< @brief Hal low level map list */
// TODO -- implementation shall be added in a future release
static const hal_ll_odconx_t odconx_map[] =
{
    //------------ ODCONx LAST ARRAY ELEMENT
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_HW_MODULES_DEFAULT, HAL_LL_MODULE_ERROR, HAL_LL_HW_MODULES_DEFAULT }
    //------------ END ODCONx
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ODCON_MAP_H_
// ------------------------------------------------------------------------- END
