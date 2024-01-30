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
    uint32_t af;
} hal_ll_can_pin_map_t;

/*!< @brief CAN RX pins */
static const hal_ll_can_pin_map_t hal_ll_can_rx_map[] =
{
    //------------ BEGIN RX
    #if defined(CAN0_RX_PA11_REMAP_NONE) && defined(PA11)
    {hal_ll_can_module_num(CAN_MODULE_0), PA11, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_REMAP_NONE},
    #endif
    #if defined(CAN0_RX_PB8_REMAP_PARTIAL) && defined(PB8)
    {hal_ll_can_module_num(CAN_MODULE_0), PB8, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_REMAP_PARTIAL},
    #endif
    #if defined(CAN1_RX_PB12_REMAP_NONE) && defined(PB12)
    {hal_ll_can_module_num(CAN_MODULE_1), PB12, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_REMAP_NONE},
    #endif
    #if defined(CAN1_RX_PB5_REMAP_FULL) && defined(PB5)
    {hal_ll_can_module_num(CAN_MODULE_1), PB5, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_REMAP_FULL},
    #endif
    #if defined(CAN0_RX_PD0_REMAP_FULL) && defined(PD0)
    {hal_ll_can_module_num(CAN_MODULE_0), PD0, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_REMAP_FULL},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END RX
};

/*!< @brief CAN TX pins */
static const hal_ll_can_pin_map_t hal_ll_can_tx_map[] =
{
    //------------ BEGIN TX
    #if defined(CAN0_TX_PA12_REMAP_NONE) && defined(PA12)
    {hal_ll_can_module_num(CAN_MODULE_0), PA12, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_REMAP_NONE},
    #endif
    #if defined(CAN0_TX_PB9_REMAP_PARTIAL) && defined(PB9)
    {hal_ll_can_module_num(CAN_MODULE_0), PB9, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_REMAP_PARTIAL},
    #endif
    #if defined(CAN1_TX_PB13_REMAP_NONE) && defined(PB13)
    {hal_ll_can_module_num(CAN_MODULE_1), PB13, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_REMAP_NONE},
    #endif
    #if defined(CAN1_TX_PB6_REMAP_FULL) && defined(PB6)
    {hal_ll_can_module_num(CAN_MODULE_1), PB6, HAL_LL_CAN1_BASE_ADDRESS, HAL_LL_CAN1_REMAP_FULL},
    #endif
    #if defined(CAN0_TX_PD1_REMAP_FULL) && defined(PD1)
    {hal_ll_can_module_num(CAN_MODULE_0), PD1, HAL_LL_CAN0_BASE_ADDRESS, HAL_LL_CAN0_REMAP_FULL},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
    //------------ END TX
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_PIN_MAP_H_
// ------------------------------------------------------------------------- END
