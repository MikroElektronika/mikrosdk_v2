/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  hal_ll_can_pin_map.h
 * @brief CAN HAL LOW LEVEL PIN MAPS.
 */

#ifndef _HAL_LL_CAN_PIN_MAP_H_
#define _HAL_LL_CAN_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_can_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
} hal_ll_can_pin_map_t;

/*!< @brief CAN RX pins */
static const hal_ll_can_pin_map_t hal_ll_can_rx_map[] =
{
    //------------ BEGIN RX
    #ifdef CAN1_RX_RE5
    {hal_ll_can_module_num(CAN_MODULE_1), PE5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG7
    {hal_ll_can_module_num(CAN_MODULE_1), PG7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB3
    {hal_ll_can_module_num(CAN_MODULE_1), PB3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RB1
    {hal_ll_can_module_num(CAN_MODULE_1), PB1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF5
    {hal_ll_can_module_num(CAN_MODULE_1), PF5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD11
    {hal_ll_can_module_num(CAN_MODULE_1), PD11, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC13
    {hal_ll_can_module_num(CAN_MODULE_1), PC13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD3
    {hal_ll_can_module_num(CAN_MODULE_1), PD3, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF0
    {hal_ll_can_module_num(CAN_MODULE_1), PF0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RC4
    {hal_ll_can_module_num(CAN_MODULE_1), PC4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD15
    {hal_ll_can_module_num(CAN_MODULE_1), PD15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RA15
    {hal_ll_can_module_num(CAN_MODULE_1), PA15, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RG0
    {hal_ll_can_module_num(CAN_MODULE_1), PG0, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF5_ALT
    {hal_ll_can_module_num(CAN_MODULE_1), PF5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RF12_ALT
    {hal_ll_can_module_num(CAN_MODULE_1), PF12, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB14
    {hal_ll_can_module_num(CAN_MODULE_2), PB14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC3_ALT
    {hal_ll_can_module_num(CAN_MODULE_2), PC3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG0
    {hal_ll_can_module_num(CAN_MODULE_2), PG0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RG6
    {hal_ll_can_module_num(CAN_MODULE_2), PG6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB0
    {hal_ll_can_module_num(CAN_MODULE_2), PB0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB7
    {hal_ll_can_module_num(CAN_MODULE_2), PB7, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB8
    {hal_ll_can_module_num(CAN_MODULE_2), PB8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RB15
    {hal_ll_can_module_num(CAN_MODULE_2), PB15, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD9
    {hal_ll_can_module_num(CAN_MODULE_2), PD9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD4
    {hal_ll_can_module_num(CAN_MODULE_2), PD4, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE3
    {hal_ll_can_module_num(CAN_MODULE_2), PE3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RC3
    {hal_ll_can_module_num(CAN_MODULE_2), PC3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RE9
    {hal_ll_can_module_num(CAN_MODULE_2), PE9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF12
    {hal_ll_can_module_num(CAN_MODULE_2), PF12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RF8
    {hal_ll_can_module_num(CAN_MODULE_2), PF8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_RX_RD12
    {hal_ll_can_module_num(CAN_MODULE_2), PD12, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_RX_RD7
    {hal_ll_can_module_num(CAN_MODULE_1), PD7, HAL_LL_CAN1_BASE_ADDRESS},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR}
    //------------ END RX
};

/*!< @brief CAN TX pins */
static const hal_ll_can_pin_map_t hal_ll_can_tx_map[] =
{
    //------------ BEGIN TX
    #ifdef CAN1_TX_RG8
    {hal_ll_can_module_num(CAN_MODULE_1), PG8, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB5
    {hal_ll_can_module_num(CAN_MODULE_1), PB5, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB9
    {hal_ll_can_module_num(CAN_MODULE_1), PB9, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RB10
    {hal_ll_can_module_num(CAN_MODULE_1), PB10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF4
    {hal_ll_can_module_num(CAN_MODULE_1), PF4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD10
    {hal_ll_can_module_num(CAN_MODULE_1), PD10, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC14
    {hal_ll_can_module_num(CAN_MODULE_1), PC14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD2
    {hal_ll_can_module_num(CAN_MODULE_1), PD2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF1
    {hal_ll_can_module_num(CAN_MODULE_1), PF1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RC1
    {hal_ll_can_module_num(CAN_MODULE_1), PC1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD14
    {hal_ll_can_module_num(CAN_MODULE_1), PD14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF2
    {hal_ll_can_module_num(CAN_MODULE_1), PF2, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RA14
    {hal_ll_can_module_num(CAN_MODULE_1), PA14, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RG1
    {hal_ll_can_module_num(CAN_MODULE_1), PG1, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF4_ALT
    {hal_ll_can_module_num(CAN_MODULE_1), PF4, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RF13_ALT
    {hal_ll_can_module_num(CAN_MODULE_1), PF13, HAL_LL_CAN1_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB8
    {hal_ll_can_module_num(CAN_MODULE_2), PB8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC2_ALT
    {hal_ll_can_module_num(CAN_MODULE_2), PC2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG1
    {hal_ll_can_module_num(CAN_MODULE_2), PG1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RG9
    {hal_ll_can_module_num(CAN_MODULE_2), PG9, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB2
    {hal_ll_can_module_num(CAN_MODULE_2), PB2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB6
    {hal_ll_can_module_num(CAN_MODULE_2), PB6, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RB14
    {hal_ll_can_module_num(CAN_MODULE_2), PB14, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF3
    {hal_ll_can_module_num(CAN_MODULE_2), PF3, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD0
    {hal_ll_can_module_num(CAN_MODULE_2), PD0, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD1
    {hal_ll_can_module_num(CAN_MODULE_2), PD1, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RD5
    {hal_ll_can_module_num(CAN_MODULE_2), PD5, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RC2
    {hal_ll_can_module_num(CAN_MODULE_2), PC2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RE8
    {hal_ll_can_module_num(CAN_MODULE_2), PE8, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF13
    {hal_ll_can_module_num(CAN_MODULE_2), PF13, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN2_TX_RF2
    {hal_ll_can_module_num(CAN_MODULE_2), PF2, HAL_LL_CAN2_BASE_ADDRESS},
    #endif
    #ifdef CAN1_TX_RD6
    {hal_ll_can_module_num(CAN_MODULE_1), PD6, HAL_LL_CAN1_BASE_ADDRESS},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR}
    //------------ END TX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_PIN_MAP_H_
// ------------------------------------------------------------------------- END
