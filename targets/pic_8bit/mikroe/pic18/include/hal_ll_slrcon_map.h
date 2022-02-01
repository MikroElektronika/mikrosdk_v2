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
__weak static const hal_ll_slew_rate_t slew_rate_map[ HAL_LL_SLRCON_BIT_COUNT + 1 ] =
{
    //------------ BEGIN SLRCON
    #if defined(HAL_LL_SLRCON_PB0_BIT) && defined(PB0)
    { PB0, HAL_LL_SLRCON_PB0_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC7_BIT) && defined(PC7)
    { PC7, HAL_LL_SLRCON_PC7_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC4_BIT) && defined(PC4)
    { PC4, HAL_LL_SLRCON_PC4_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC5_BIT) && defined(PC5)
    { PC5, HAL_LL_SLRCON_PC5_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC6_BIT) && defined(PC6)
    { PC6, HAL_LL_SLRCON_PC6_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB5_BIT) && defined(PB5)
    { PB5, HAL_LL_SLRCON_PB5_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB6_BIT) && defined(PB6)
    { PB6, HAL_LL_SLRCON_PB6_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB7_BIT) && defined(PB7)
    { PB7, HAL_LL_SLRCON_PB7_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB4_BIT) && defined(PB4)
    { PB4, HAL_LL_SLRCON_PB4_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB1_BIT) && defined(PB1)
    { PB1, HAL_LL_SLRCON_PB1_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB2_BIT) && defined(PB2)
    { PB2, HAL_LL_SLRCON_PB2_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PB3_BIT) && defined(PB3)
    { PB3, HAL_LL_SLRCON_PB3_BIT, HAL_LL_SLRCONB_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA3_BIT) && defined(PA3)
    { PA3, HAL_LL_SLRCON_PA3_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA4_BIT) && defined(PA4)
    { PA4, HAL_LL_SLRCON_PA4_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA5_BIT) && defined(PA5)
    { PA5, HAL_LL_SLRCON_PA5_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA2_BIT) && defined(PA2)
    { PA2, HAL_LL_SLRCON_PA2_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE3_BIT) && defined(PE3)
    { PE3, HAL_LL_SLRCON_PE3_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA0_BIT) && defined(PA0)
    { PA0, HAL_LL_SLRCON_PA0_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA1_BIT) && defined(PA1)
    { PA1, HAL_LL_SLRCON_PA1_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC1_BIT) && defined(PC1)
    { PC1, HAL_LL_SLRCON_PC1_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC2_BIT) && defined(PC2)
    { PC2, HAL_LL_SLRCON_PC2_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC0_BIT) && defined(PC0)
    { PC0, HAL_LL_SLRCON_PC0_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA6_BIT) && defined(PA6)
    { PA6, HAL_LL_SLRCON_PA6_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PC3_BIT) && defined(PC3)
    { PC3, HAL_LL_SLRCON_PC3_BIT, HAL_LL_SLRCONC_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PA7_BIT) && defined(PA7)
    { PA7, HAL_LL_SLRCON_PA7_BIT, HAL_LL_SLRCONA_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD4_BIT) && defined(PD4)
    { PD4, HAL_LL_SLRCON_PD4_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD5_BIT) && defined(PD5)
    { PD5, HAL_LL_SLRCON_PD5_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD7_BIT) && defined(PD7)
    { PD7, HAL_LL_SLRCON_PD7_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD6_BIT) && defined(PD6)
    { PD6, HAL_LL_SLRCON_PD6_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD3_BIT) && defined(PD3)
    { PD3, HAL_LL_SLRCON_PD3_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD2_BIT) && defined(PD2)
    { PD2, HAL_LL_SLRCON_PD2_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE0_BIT) && defined(PE0)
    { PE0, HAL_LL_SLRCON_PE0_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE2_BIT) && defined(PE2)
    { PE2, HAL_LL_SLRCON_PE2_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE1_BIT) && defined(PE1)
    { PE1, HAL_LL_SLRCON_PE1_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD1_BIT) && defined(PD1)
    { PD1, HAL_LL_SLRCON_PD1_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PD0_BIT) && defined(PD0)
    { PD0, HAL_LL_SLRCON_PD0_BIT, HAL_LL_SLRCOND_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF7_BIT) && defined(PF7)
    { PF7, HAL_LL_SLRCON_PF7_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF6_BIT) && defined(PF6)
    { PF6, HAL_LL_SLRCON_PF6_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF2_BIT) && defined(PF2)
    { PF2, HAL_LL_SLRCON_PF2_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF1_BIT) && defined(PF1)
    { PF1, HAL_LL_SLRCON_PF1_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF0_BIT) && defined(PF0)
    { PF0, HAL_LL_SLRCON_PF0_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF5_BIT) && defined(PF5)
    { PF5, HAL_LL_SLRCON_PF5_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF4_BIT) && defined(PF4)
    { PF4, HAL_LL_SLRCON_PF4_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PF3_BIT) && defined(PF3)
    { PF3, HAL_LL_SLRCON_PF3_BIT, HAL_LL_SLRCONF_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE7_BIT) && defined(PE7)
    { PE7, HAL_LL_SLRCON_PE7_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG0_BIT) && defined(PG0)
    { PG0, HAL_LL_SLRCON_PG0_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG1_BIT) && defined(PG1)
    { PG1, HAL_LL_SLRCON_PG1_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG4_BIT) && defined(PG4)
    { PG4, HAL_LL_SLRCON_PG4_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG2_BIT) && defined(PG2)
    { PG2, HAL_LL_SLRCON_PG2_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG3_BIT) && defined(PG3)
    { PG3, HAL_LL_SLRCON_PG3_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE6_BIT) && defined(PE6)
    { PE6, HAL_LL_SLRCON_PE6_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE5_BIT) && defined(PE5)
    { PE5, HAL_LL_SLRCON_PE5_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PE4_BIT) && defined(PE4)
    { PE4, HAL_LL_SLRCON_PE4_BIT, HAL_LL_SLRCONE_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG5_BIT) && defined(PG5)
    { PG5, HAL_LL_SLRCON_PG5_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG7_BIT) && defined(PG7)
    { PG7, HAL_LL_SLRCON_PG7_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PG6_BIT) && defined(PG6)
    { PG6, HAL_LL_SLRCON_PG6_BIT, HAL_LL_SLRCONG_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ3_BIT) && defined(PJ3)
    { PJ3, HAL_LL_SLRCON_PJ3_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ2_BIT) && defined(PJ2)
    { PJ2, HAL_LL_SLRCON_PJ2_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ6_BIT) && defined(PJ6)
    { PJ6, HAL_LL_SLRCON_PJ6_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ7_BIT) && defined(PJ7)
    { PJ7, HAL_LL_SLRCON_PJ7_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH0_BIT) && defined(PH0)
    { PH0, HAL_LL_SLRCON_PH0_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH1_BIT) && defined(PH1)
    { PH1, HAL_LL_SLRCON_PH1_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ1_BIT) && defined(PJ1)
    { PJ1, HAL_LL_SLRCON_PJ1_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ0_BIT) && defined(PJ0)
    { PJ0, HAL_LL_SLRCON_PJ0_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH7_BIT) && defined(PH7)
    { PH7, HAL_LL_SLRCON_PH7_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH6_BIT) && defined(PH6)
    { PH6, HAL_LL_SLRCON_PH6_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH2_BIT) && defined(PH2)
    { PH2, HAL_LL_SLRCON_PH2_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH3_BIT) && defined(PH3)
    { PH3, HAL_LL_SLRCON_PH3_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ4_BIT) && defined(PJ4)
    { PJ4, HAL_LL_SLRCON_PJ4_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PJ5_BIT) && defined(PJ5)
    { PJ5, HAL_LL_SLRCON_PJ5_BIT, HAL_LL_SLRCONJ_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH5_BIT) && defined(PH5)
    { PH5, HAL_LL_SLRCON_PH5_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PH4_BIT) && defined(PH4)
    { PH4, HAL_LL_SLRCON_PH4_BIT, HAL_LL_SLRCONH_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK4_BIT) && defined(PK4)
    { PK4, HAL_LL_SLRCON_PK4_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK5_BIT) && defined(PK5)
    { PK5, HAL_LL_SLRCON_PK5_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK3_BIT) && defined(PK3)
    { PK3, HAL_LL_SLRCON_PK3_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK1_BIT) && defined(PK1)
    { PK1, HAL_LL_SLRCON_PK1_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK2_BIT) && defined(PK2)
    { PK2, HAL_LL_SLRCON_PK2_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL0_BIT) && defined(PL0)
    { PL0, HAL_LL_SLRCON_PL0_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK6_BIT) && defined(PK6)
    { PK6, HAL_LL_SLRCON_PK6_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK7_BIT) && defined(PK7)
    { PK7, HAL_LL_SLRCON_PK7_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL3_BIT) && defined(PL3)
    { PL3, HAL_LL_SLRCON_PL3_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL4_BIT) && defined(PL4)
    { PL4, HAL_LL_SLRCON_PL4_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL2_BIT) && defined(PL2)
    { PL2, HAL_LL_SLRCON_PL2_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL1_BIT) && defined(PL1)
    { PL1, HAL_LL_SLRCON_PL1_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL7_BIT) && defined(PL7)
    { PL7, HAL_LL_SLRCON_PL7_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PK0_BIT) && defined(PK0)
    { PK0, HAL_LL_SLRCON_PK0_BIT, HAL_LL_SLRCONK_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL6_BIT) && defined(PL6)
    { PL6, HAL_LL_SLRCON_PL6_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif
    #if defined(HAL_LL_SLRCON_PL5_BIT) && defined(PL5)
    { PL5, HAL_LL_SLRCON_PL5_BIT, HAL_LL_SLRCONL_ADDRESS },
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SLRCON
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SLRCON_MAP_H_
// ------------------------------------------------------------------------- END
