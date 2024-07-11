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
    #ifdef CAN0_RX_PF0_AF3
    {hal_ll_can_module_num(CAN_MODULE_0), PF0, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF3},
    #endif
    #ifdef CAN0_RX_PE4_AF8
    {hal_ll_can_module_num(CAN_MODULE_0), PE4, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF8},
    #endif
    #ifdef CAN0_RX_PB4_AF8
    {hal_ll_can_module_num(CAN_MODULE_0), PB4, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF8},
    #endif
    #ifdef CAN0_RX_PN0_AF1
    {hal_ll_can_module_num(CAN_MODULE_0), PN0, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF1},
    #endif
    #ifdef CAN1_RX_PA0_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PA0, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN1_RX_PE6_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PE6, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN0_RX_PA0_AF7
    {hal_ll_can_module_num(CAN_MODULE_0), PA0, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF7},
    #endif
    #ifdef CAN1_RX_PB0_AF7
    {hal_ll_can_module_num(CAN_MODULE_1), PB0, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF7},
    #endif
    #ifdef CAN1_RX_PT2_AF7
    {hal_ll_can_module_num(CAN_MODULE_1), PT2, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF7},
    #endif
    #ifdef CAN0_RX_PT0_AF7
    {hal_ll_can_module_num(CAN_MODULE_0), PT0, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF7},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

/*!< @brief CAN TX pins */
static const hal_ll_can_pin_map_t hal_ll_can_tx_map[] =
{
    //------------ BEGIN TX
    #ifdef CAN0_TX_PE5_AF8
    {hal_ll_can_module_num(CAN_MODULE_0), PE5, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF8},
    #endif
    #ifdef CAN0_TX_PB5_AF8
    {hal_ll_can_module_num(CAN_MODULE_0), PB5, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF8},
    #endif
    #ifdef CAN0_TX_PF3_AF3
    {hal_ll_can_module_num(CAN_MODULE_0), PF3, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF3},
    #endif
    #ifdef CAN0_TX_PN1_AF1
    {hal_ll_can_module_num(CAN_MODULE_0), PN1, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF1},
    #endif
    #ifdef CAN1_TX_PA1_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PA1, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN1_TX_PE7_AF8
    {hal_ll_can_module_num(CAN_MODULE_1), PE7, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF8},
    #endif
    #ifdef CAN1_TX_PB1_AF7
    {hal_ll_can_module_num(CAN_MODULE_1), PB1, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF7},
    #endif
    #ifdef CAN0_TX_PA1_AF7
    {hal_ll_can_module_num(CAN_MODULE_0), PA1, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF7},
    #endif
    #ifdef CAN1_TX_PT3_AF7
    {hal_ll_can_module_num(CAN_MODULE_1), PT3, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_GPIO_AF7},
    #endif
    #ifdef CAN0_TX_PT1_AF7
    {hal_ll_can_module_num(CAN_MODULE_0), PT1, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_GPIO_AF7},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_PIN_MAP_H_
// ------------------------------------------------------------------------- END
