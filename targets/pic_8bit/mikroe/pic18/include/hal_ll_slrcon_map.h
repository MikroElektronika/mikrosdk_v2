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
    uint8_t slrcon_address_bit;
    hal_ll_base_addr_t slrcon_address;
} hal_ll_slew_rate_t;

/*!< @brief Hal low level map list */
static const hal_ll_slew_rate_t slew_rate_map[ HAL_LL_SLRCON_BIT_COUNT + 1 ] =
{
    //------------ BEGIN SLRCON
    #if defined(HAL_LL_SLRCON_PB0_BIT) && defined(GPIO_PB0)
    { GPIO_PB0, HAL_LL_SLRCON_PB0_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC7_BIT) && defined(GPIO_PC7)
    { GPIO_PC7, HAL_LL_SLRCON_PC7_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC4_BIT) && defined(GPIO_PC4)
    { GPIO_PC4, HAL_LL_SLRCON_PC4_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC5_BIT) && defined(GPIO_PC5)
    { GPIO_PC5, HAL_LL_SLRCON_PC5_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC6_BIT) && defined(GPIO_PC6)
    { GPIO_PC6, HAL_LL_SLRCON_PC6_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB5_BIT) && defined(GPIO_PB5)
    { GPIO_PB5, HAL_LL_SLRCON_PB5_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB6_BIT) && defined(GPIO_PB6)
    { GPIO_PB6, HAL_LL_SLRCON_PB6_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB7_BIT) && defined(GPIO_PB7)
    { GPIO_PB7, HAL_LL_SLRCON_PB7_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB4_BIT) && defined(GPIO_PB4)
    { GPIO_PB4, HAL_LL_SLRCON_PB4_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB1_BIT) && defined(GPIO_PB1)
    { GPIO_PB1, HAL_LL_SLRCON_PB1_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB2_BIT) && defined(GPIO_PB2)
    { GPIO_PB2, HAL_LL_SLRCON_PB2_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB3_BIT) && defined(GPIO_PB3)
    { GPIO_PB3, HAL_LL_SLRCON_PB3_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA3_BIT) && defined(GPIO_PA3)
    { GPIO_PA3, HAL_LL_SLRCON_PA3_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA4_BIT) && defined(GPIO_PA4)
    { GPIO_PA4, HAL_LL_SLRCON_PA4_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA5_BIT) && defined(GPIO_PA5)
    { GPIO_PA5, HAL_LL_SLRCON_PA5_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA2_BIT) && defined(GPIO_PA2)
    { GPIO_PA2, HAL_LL_SLRCON_PA2_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE3_BIT) && defined(GPIO_PE3)
    { GPIO_PE3, HAL_LL_SLRCON_PE3_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA0_BIT) && defined(GPIO_PA0)
    { GPIO_PA0, HAL_LL_SLRCON_PA0_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA1_BIT) && defined(GPIO_PA1)
    { GPIO_PA1, HAL_LL_SLRCON_PA1_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC1_BIT) && defined(GPIO_PC1)
    { GPIO_PC1, HAL_LL_SLRCON_PC1_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC2_BIT) && defined(GPIO_PC2)
    { GPIO_PC2, HAL_LL_SLRCON_PC2_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC0_BIT) && defined(GPIO_PC0)
    { GPIO_PC0, HAL_LL_SLRCON_PC0_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA6_BIT) && defined(GPIO_PA6)
    { GPIO_PA6, HAL_LL_SLRCON_PA6_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC3_BIT) && defined(GPIO_PC3)
    { GPIO_PC3, HAL_LL_SLRCON_PC3_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA7_BIT) && defined(GPIO_PA7)
    { GPIO_PA7, HAL_LL_SLRCON_PA7_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD4_BIT) && defined(GPIO_PD4)
    { GPIO_PD4, HAL_LL_SLRCON_PD4_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD5_BIT) && defined(GPIO_PD5)
    { GPIO_PD5, HAL_LL_SLRCON_PD5_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD7_BIT) && defined(GPIO_PD7)
    { GPIO_PD7, HAL_LL_SLRCON_PD7_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD6_BIT) && defined(GPIO_PD6)
    { GPIO_PD6, HAL_LL_SLRCON_PD6_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD3_BIT) && defined(GPIO_PD3)
    { GPIO_PD3, HAL_LL_SLRCON_PD3_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD2_BIT) && defined(GPIO_PD2)
    { GPIO_PD2, HAL_LL_SLRCON_PD2_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE0_BIT) && defined(GPIO_PE0)
    { GPIO_PE0, HAL_LL_SLRCON_PE0_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE2_BIT) && defined(GPIO_PE2)
    { GPIO_PE2, HAL_LL_SLRCON_PE2_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE1_BIT) && defined(GPIO_PE1)
    { GPIO_PE1, HAL_LL_SLRCON_PE1_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD1_BIT) && defined(GPIO_PD1)
    { GPIO_PD1, HAL_LL_SLRCON_PD1_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD0_BIT) && defined(GPIO_PD0)
    { GPIO_PD0, HAL_LL_SLRCON_PD0_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF7_BIT) && defined(GPIO_PF7)
    { GPIO_PF7, HAL_LL_SLRCON_PF7_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF6_BIT) && defined(GPIO_PF6)
    { GPIO_PF6, HAL_LL_SLRCON_PF6_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF2_BIT) && defined(GPIO_PF2)
    { GPIO_PF2, HAL_LL_SLRCON_PF2_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF1_BIT) && defined(GPIO_PF1)
    { GPIO_PF1, HAL_LL_SLRCON_PF1_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF0_BIT) && defined(GPIO_PF0)
    { GPIO_PF0, HAL_LL_SLRCON_PF0_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF5_BIT) && defined(GPIO_PF5)
    { GPIO_PF5, HAL_LL_SLRCON_PF5_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF4_BIT) && defined(GPIO_PF4)
    { GPIO_PF4, HAL_LL_SLRCON_PF4_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF3_BIT) && defined(GPIO_PF3)
    { GPIO_PF3, HAL_LL_SLRCON_PF3_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE7_BIT) && defined(GPIO_PE7)
    { GPIO_PE7, HAL_LL_SLRCON_PE7_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG0_BIT) && defined(GPIO_PG0)
    { GPIO_PG0, HAL_LL_SLRCON_PG0_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG1_BIT) && defined(GPIO_PG1)
    { GPIO_PG1, HAL_LL_SLRCON_PG1_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG4_BIT) && defined(GPIO_PG4)
    { GPIO_PG4, HAL_LL_SLRCON_PG4_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG2_BIT) && defined(GPIO_PG2)
    { GPIO_PG2, HAL_LL_SLRCON_PG2_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG3_BIT) && defined(GPIO_PG3)
    { GPIO_PG3, HAL_LL_SLRCON_PG3_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE6_BIT) && defined(GPIO_PE6)
    { GPIO_PE6, HAL_LL_SLRCON_PE6_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE5_BIT) && defined(GPIO_PE5)
    { GPIO_PE5, HAL_LL_SLRCON_PE5_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE4_BIT) && defined(GPIO_PE4)
    { GPIO_PE4, HAL_LL_SLRCON_PE4_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG5_BIT) && defined(GPIO_PG5)
    { GPIO_PG5, HAL_LL_SLRCON_PG5_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG7_BIT) && defined(GPIO_PG7)
    { GPIO_PG7, HAL_LL_SLRCON_PG7_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG6_BIT) && defined(GPIO_PG6)
    { GPIO_PG6, HAL_LL_SLRCON_PG6_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ3_BIT) && defined(GPIO_PJ3)
    { GPIO_PJ3, HAL_LL_SLRCON_PJ3_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ2_BIT) && defined(GPIO_PJ2)
    { GPIO_PJ2, HAL_LL_SLRCON_PJ2_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ6_BIT) && defined(GPIO_PJ6)
    { GPIO_PJ6, HAL_LL_SLRCON_PJ6_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ7_BIT) && defined(GPIO_PJ7)
    { GPIO_PJ7, HAL_LL_SLRCON_PJ7_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH0_BIT) && defined(GPIO_PH0)
    { GPIO_PH0, HAL_LL_SLRCON_PH0_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH1_BIT) && defined(GPIO_PH1)
    { GPIO_PH1, HAL_LL_SLRCON_PH1_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ1_BIT) && defined(GPIO_PJ1)
    { GPIO_PJ1, HAL_LL_SLRCON_PJ1_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ0_BIT) && defined(GPIO_PJ0)
    { GPIO_PJ0, HAL_LL_SLRCON_PJ0_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH7_BIT) && defined(GPIO_PH7)
    { GPIO_PH7, HAL_LL_SLRCON_PH7_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH6_BIT) && defined(GPIO_PH6)
    { GPIO_PH6, HAL_LL_SLRCON_PH6_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH2_BIT) && defined(GPIO_PH2)
    { GPIO_PH2, HAL_LL_SLRCON_PH2_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH3_BIT) && defined(GPIO_PH3)
    { GPIO_PH3, HAL_LL_SLRCON_PH3_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ4_BIT) && defined(GPIO_PJ4)
    { GPIO_PJ4, HAL_LL_SLRCON_PJ4_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ5_BIT) && defined(GPIO_PJ5)
    { GPIO_PJ5, HAL_LL_SLRCON_PJ5_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH5_BIT) && defined(GPIO_PH5)
    { GPIO_PH5, HAL_LL_SLRCON_PH5_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH4_BIT) && defined(GPIO_PH4)
    { GPIO_PH4, HAL_LL_SLRCON_PH4_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK4_BIT) && defined(GPIO_PK4)
    { GPIO_PK4, HAL_LL_SLRCON_PK4_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK5_BIT) && defined(GPIO_PK5)
    { GPIO_PK5, HAL_LL_SLRCON_PK5_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK3_BIT) && defined(GPIO_PK3)
    { GPIO_PK3, HAL_LL_SLRCON_PK3_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK1_BIT) && defined(GPIO_PK1)
    { GPIO_PK1, HAL_LL_SLRCON_PK1_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK2_BIT) && defined(GPIO_PK2)
    { GPIO_PK2, HAL_LL_SLRCON_PK2_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL0_BIT) && defined(GPIO_PL0)
    { GPIO_PL0, HAL_LL_SLRCON_PL0_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK6_BIT) && defined(GPIO_PK6)
    { GPIO_PK6, HAL_LL_SLRCON_PK6_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK7_BIT) && defined(GPIO_PK7)
    { GPIO_PK7, HAL_LL_SLRCON_PK7_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL3_BIT) && defined(GPIO_PL3)
    { GPIO_PL3, HAL_LL_SLRCON_PL3_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL4_BIT) && defined(GPIO_PL4)
    { GPIO_PL4, HAL_LL_SLRCON_PL4_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL2_BIT) && defined(GPIO_PL2)
    { GPIO_PL2, HAL_LL_SLRCON_PL2_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL1_BIT) && defined(GPIO_PL1)
    { GPIO_PL1, HAL_LL_SLRCON_PL1_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL7_BIT) && defined(GPIO_PL7)
    { GPIO_PL7, HAL_LL_SLRCON_PL7_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK0_BIT) && defined(GPIO_PK0)
    { GPIO_PK0, HAL_LL_SLRCON_PK0_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL6_BIT) && defined(GPIO_PL6)
    { GPIO_PL6, HAL_LL_SLRCON_PL6_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL5_BIT) && defined(GPIO_PL5)
    { GPIO_PL5, HAL_LL_SLRCON_PL5_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SLRCON
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SLRCON_MAP_H_
// ------------------------------------------------------------------------- END
