/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Hal low level slew rate map structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t srconx_address_bit;
    hal_ll_base_addr_t srconx_address[2];
} hal_ll_slew_rate_t;

/*!< @brief Hal low level map list */
__weak static const hal_ll_slew_rate_t slew_rate_map[] =
{
    #ifdef PIC32MZxx
    // PORTA
    #ifdef __RA6_CN
    { PA6,  6,  {HAL_LL_SRCON0A_ADDRESS,HAL_LL_SRCON1A_ADDRESS} },
    #endif
    #ifdef __RA7_CN
    { PA7,  7,  {HAL_LL_SRCON0A_ADDRESS,HAL_LL_SRCON1A_ADDRESS} },
    #endif
    // PORTB
    #ifdef __RB3_CN
    { PB3,  3,  {HAL_LL_SRCON0B_ADDRESS,HAL_LL_SRCON1B_ADDRESS} },
    #endif
    #ifdef __RB5_CN
    { PB5,  5,  {HAL_LL_SRCON0B_ADDRESS,HAL_LL_SRCON1B_ADDRESS} },
    #endif
    #ifdef __RB8_CN
    { PB8,  8,  {HAL_LL_SRCON0B_ADDRESS,HAL_LL_SRCON1B_ADDRESS} },
    #endif
    #ifdef __RB9_CN
    { PB9,  9,  {HAL_LL_SRCON0B_ADDRESS,HAL_LL_SRCON1B_ADDRESS} },
    #endif
    #ifdef __RB10_CN
    { PB10, 10, {HAL_LL_SRCON0B_ADDRESS,HAL_LL_SRCON1B_ADDRESS} },
    #endif
    #ifdef __RB14_CN
    { PB14, 14, {HAL_LL_SRCON0B_ADDRESS,HAL_LL_SRCON1B_ADDRESS} },
    #endif
    // PORTE
    #ifdef __RE0_CN
    { PE0,  0,  {HAL_LL_SRCON0E_ADDRESS,HAL_LL_SRCON1E_ADDRESS} },
    #endif
    #ifdef __RE1_CN
    { PE1,  1,  {HAL_LL_SRCON0E_ADDRESS,HAL_LL_SRCON1E_ADDRESS} },
    #endif
    #ifdef __RE2_CN
    { PE2,  2,  {HAL_LL_SRCON0E_ADDRESS,HAL_LL_SRCON1E_ADDRESS} },
    #endif
    #ifdef __RE3_CN
    { PE3,  3,  {HAL_LL_SRCON0E_ADDRESS,HAL_LL_SRCON1E_ADDRESS} },
    #endif
    // PORTF
    #ifdef __RF0_CN
    { PF0,  0,  {HAL_LL_SRCON0F_ADDRESS,HAL_LL_SRCON1F_ADDRESS} },
    #endif
    #ifdef __RF1_CN
    { PF1,  1,  {HAL_LL_SRCON0F_ADDRESS,HAL_LL_SRCON1F_ADDRESS} },
    #endif
    // PORTG
    #ifdef __RG6_CN
    { PG6,  6,  {HAL_LL_SRCON0G_ADDRESS,HAL_LL_SRCON1G_ADDRESS} },
    #endif
    #ifdef __RG9_CN
    { PG9,  9,  {HAL_LL_SRCON0G_ADDRESS,HAL_LL_SRCON1G_ADDRESS} },
    #endif
    #ifdef __RG12_CN
    { PG12, 12, {HAL_LL_SRCON0G_ADDRESS,HAL_LL_SRCON1G_ADDRESS} },
    #endif
    #ifdef __RG13_CN
    { PG13, 13, {HAL_LL_SRCON0G_ADDRESS,HAL_LL_SRCON1G_ADDRESS} },
    #endif
    #ifdef __RG14_CN
    { PG14, 14, {HAL_LL_SRCON0G_ADDRESS,HAL_LL_SRCON1G_ADDRESS} },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, {HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR} }
    //------------ END SLRCON
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SLRCON_MAP_H_
// ------------------------------------------------------------------------- END
