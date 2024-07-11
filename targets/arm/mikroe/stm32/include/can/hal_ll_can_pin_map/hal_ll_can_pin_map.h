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
    uint32_t af;
} hal_ll_can_pin_map_t;

/*!< @brief CAN RX pins */
static const hal_ll_can_pin_map_t hal_ll_can_rx_map[] =
{
    //------------ BEGIN RX
    #ifdef CAN_RX_PA11_AF4
    {hal_ll_can_module_num(CAN_MODULE), PA11, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF4},
    #endif
    #ifdef CAN_RX_PB8_AF4
    {hal_ll_can_module_num(CAN_MODULE), PB8, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF4},
    #endif
    #ifdef CAN_RX_PD0_AF0
    {hal_ll_can_module_num(CAN_MODULE), PD0, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF0},
    #endif
    #ifdef CAN_RX_PA11
    {hal_ll_can_module_num(CAN_MODULE), PA11, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_PA11},
    #endif
    #ifdef CAN_RX_PB8
    {hal_ll_can_module_num(CAN_MODULE), PB8, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_PB8},
    #endif
    #ifdef CAN_RX_PD0
    {hal_ll_can_module_num(CAN_MODULE), PD0, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_PD0},
    #endif
    #ifdef CAN1_RX_PA11_REMAP_NONE
    {hal_ll_can_module_num(CAN_MODULE_1), PA11, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_REMAP_NONE},
    #endif
    #ifdef CAN1_RX_PB8_REMAP_PARTIAL
    {hal_ll_can_module_num(CAN_MODULE_1), PB8, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_REMAP_PARTIAL},
    #endif
    #ifdef CAN1_RX_PD0_REMAP_FULL
    {hal_ll_can_module_num(CAN_MODULE_1), PD0, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_REMAP_FULL},
    #endif
    #ifdef CAN2_RX_PB12_REMAP_NONE
    {hal_ll_can_module_num(CAN_MODULE_2), PB12, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_REMAP_NONE},
    #endif
    #ifdef CAN2_RX_PB5_REMAP_FULL
    {hal_ll_can_module_num(CAN_MODULE_2), PB5, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_REMAP_FULL},
    #endif
    #ifdef CAN2_RX_PB12_AF9
    {hal_ll_can_module_num(CAN_MODULE_2), PB12, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF9},
    #endif
    #ifdef CAN1_RX_PA11_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PA11, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN2_RX_PB5_AF9
    {hal_ll_can_module_num(CAN_MODULE_2), PB5, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF9},
    #endif
    #ifdef CAN1_RX_PB8_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PB8, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN1_RX_PD0_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PD0, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN1_RX_PI9_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PI9, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN_RX_PA11_AF9
    {hal_ll_can_module_num(CAN_MODULE), PA11, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF9},
    #endif
    #ifdef CAN_RX_PB8_AF9
    {hal_ll_can_module_num(CAN_MODULE), PB8, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF9},
    #endif
    #ifdef CAN_RX_PD0_AF7
    {hal_ll_can_module_num(CAN_MODULE), PD0, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF7},
    #endif
    #ifdef CAN1_RX_PB8_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PB8, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN2_RX_PG11_AF9
    {hal_ll_can_module_num(CAN_MODULE_2), PG11, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF9},
    #endif
    #ifdef CAN1_RX_PG0_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PG0, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN3_RX_PA8_AF11
    {hal_ll_can_module_num(CAN_MODULE_3), PA8, HAL_LL_CAN3_BASE_ADDRESS, HAL_LL_CAN3_GPIO_AF11},
    #endif
    #ifdef CAN3_RX_PB3_AF11
    {hal_ll_can_module_num(CAN_MODULE_3), PB3, HAL_LL_CAN3_BASE_ADDRESS, HAL_LL_CAN3_GPIO_AF11},
    #endif
    #ifdef CAN1_RX_PH14_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PH14, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN1_RX_PB12_AF10
    {hal_ll_can_module_num(CAN_MODULE_1), PB12, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF10},
    #endif
    #ifdef CAN1_RX_PB5_AF3
    {hal_ll_can_module_num(CAN_MODULE_1), PB5, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF3},
    #endif
    #ifdef CAN2_RX_PB5_AF3
    {hal_ll_can_module_num(CAN_MODULE_2), PB5, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF3},
    #endif
    #ifdef CAN2_RX_PB12_AF10
    {hal_ll_can_module_num(CAN_MODULE_2), PB12, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF10},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

/*!< @brief CAN TX pins */
static const hal_ll_can_pin_map_t hal_ll_can_tx_map[] =
{
    //------------ BEGIN TX
    #ifdef CAN_TX_PA12_AF4
    {hal_ll_can_module_num(CAN_MODULE), PA12, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF4},
    #endif
    #ifdef CAN_TX_PB9_AF4
    {hal_ll_can_module_num(CAN_MODULE), PB9, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF4},
    #endif
    #ifdef CAN_TX_PD1_AF0
    {hal_ll_can_module_num(CAN_MODULE), PD1, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF0},
    #endif
    #ifdef CAN_TX_PA12
    {hal_ll_can_module_num(CAN_MODULE), PA12, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_PA12},
    #endif
    #ifdef CAN_TX_PB9
    {hal_ll_can_module_num(CAN_MODULE), PB9, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_PB9},
    #endif
    #ifdef CAN_TX_PD1
    {hal_ll_can_module_num(CAN_MODULE), PD1, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_PD1},
    #endif
    #ifdef CAN1_TX_PA12_REMAP_NONE
    {hal_ll_can_module_num(CAN_MODULE_1), PA12, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_REMAP_NONE},
    #endif
    #ifdef CAN1_TX_PB9_REMAP_PARTIAL
    {hal_ll_can_module_num(CAN_MODULE_1), PB9, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_REMAP_PARTIAL},
    #endif
    #ifdef CAN1_TX_PD1_REMAP_FULL
    {hal_ll_can_module_num(CAN_MODULE_1), PD1, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_REMAP_FULL},
    #endif
    #ifdef CAN2_TX_PB13_REMAP_NONE
    {hal_ll_can_module_num(CAN_MODULE_2), PB13, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_REMAP_NONE},
    #endif
    #ifdef CAN2_TX_PB6_REMAP_FULL
    {hal_ll_can_module_num(CAN_MODULE_2), PB6, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_REMAP_FULL},
    #endif
    #ifdef CAN2_TX_PB13_AF9
    {hal_ll_can_module_num(CAN_MODULE_2), PB13, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF9},
    #endif
    #ifdef CAN1_TX_PA12_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PA12, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN2_TX_PB6_AF9
    {hal_ll_can_module_num(CAN_MODULE_2), PB6, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF9},
    #endif
    #ifdef CAN1_TX_PB9_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PB9, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN1_TX_PD1_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PD1, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN1_TX_PH13_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PH13, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN_TX_PA12_AF9
    {hal_ll_can_module_num(CAN_MODULE), PA12, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF9},
    #endif
    #ifdef CAN_TX_PB9_AF9
    {hal_ll_can_module_num(CAN_MODULE), PB9, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF9},
    #endif
    #ifdef CAN_TX_PD1_AF7
    {hal_ll_can_module_num(CAN_MODULE), PD1, HAL_LL_CAN_BASE_ADDRESS, HAL_LL_CAN_GPIO_AF7},
    #endif
    #ifdef CAN1_TX_PB9_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PB9, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN2_TX_PG12_AF9
    {hal_ll_can_module_num(CAN_MODULE_2), PG12, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF9},
    #endif
    #ifdef CAN1_TX_PG1_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PG1, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF9},
    #endif
    #ifdef CAN3_TX_PA15_AF11
    {hal_ll_can_module_num(CAN_MODULE_3), PA15, HAL_LL_CAN3_BASE_ADDRESS, HAL_LL_CAN3_GPIO_AF11},
    #endif
    #ifdef CAN3_TX_PB4_AF11
    {hal_ll_can_module_num(CAN_MODULE_3), PB4, HAL_LL_CAN3_BASE_ADDRESS, HAL_LL_CAN3_GPIO_AF11},
    #endif
    #ifdef CAN1_TX_PB13_AF10
    {hal_ll_can_module_num(CAN_MODULE_1), PB13, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF10},
    #endif
    #ifdef CAN1_TX_PB6_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PB6, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN2_TX_PB6_AF8
    {hal_ll_can_module_num(CAN_MODULE_2), PB6, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF8},
    #endif
    #ifdef CAN2_TX_PB13_AF10
    {hal_ll_can_module_num(CAN_MODULE_2), PB13, HAL_LL_CAN2_BASE_ADDRESS, HAL_LL_CAN2_GPIO_AF10},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_PIN_MAP_H_
// ------------------------------------------------------------------------- END
