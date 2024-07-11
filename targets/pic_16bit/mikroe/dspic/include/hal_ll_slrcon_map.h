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
 * @file  hal_ll_slrcon_map.h
 * @brief HAL LOW LEVEL MAP FOR PIN/PORT SLEW RATE.
 */

#ifndef _HAL_LL_SLRCON_MAP_H_
#define _HAL_LL_SLRCON_MAP_H_

/*< @brief Macro that will be used in the future updates */
#define HAL_LL_SLRCON_BIT_COUNT 1

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Hal low level slew rate map structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
	uint8_t slrcon_address_bit;
	hal_ll_base_addr_t slrcon_address;
} hal_ll_slew_rate_t;

/*!< @brief Hal low level map list */
static const hal_ll_slew_rate_t slew_rate_map[ HAL_LL_SLRCON_BIT_COUNT + 1 ] = {
    //------------ BEGIN SLRCON
    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SLRCON
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SLRCON_MAP_H_
// ------------------------------------------------------------------------- END
