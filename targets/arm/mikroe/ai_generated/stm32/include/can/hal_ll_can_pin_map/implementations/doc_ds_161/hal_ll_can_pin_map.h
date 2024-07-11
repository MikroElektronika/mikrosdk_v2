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
#define hal_ll_fdcan_module_num(_module_num) hal_ll_can_module_num(_module_num)

/*!< @brief Pin structure */
typedef struct
{
    uint8_t module_index;
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint32_t af;
} hal_ll_can_pin_map_t;

#ifdef CAN_MODULE_1
#define CAN1_BASE_ADDRESS (0x40006400UL)
#define CAN1_BASE_ADDR CAN1_BASE_ADDRESS
#define HAL_LL_CAN1_BASE_ADDR CAN1_BASE_ADDRESS
#define HAL_LL_CAN1_BASE_ADDRESS CAN1_BASE_ADDRESS
#endif

/*!< @brief CAN RX pins */
static const hal_ll_can_pin_map_t hal_ll_can_rx_map[] =
{
    #ifdef CAN1_RX_PA11_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PA11, CAN1_BASE_ADDRESS, 9},
    #endif
    #ifdef CAN1_RX_PB8_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PB8, CAN1_BASE_ADDRESS, 9},
    #endif
    #ifdef CAN1_RX_PD0_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PD0, CAN1_BASE_ADDRESS, 9},
    #endif
    #ifdef CAN1_RX_PI9_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PI9, CAN1_BASE_ADDRESS, 9},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< @brief CAN TX pins */
static const hal_ll_can_pin_map_t hal_ll_can_tx_map[] =
{
    #ifdef CAN1_TX_PA12_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PA12, CAN1_BASE_ADDRESS, 9},
    #endif
    #ifdef CAN1_TX_PB9_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PB9, CAN1_BASE_ADDRESS, 9},
    #endif
    #ifdef CAN1_TX_PD1_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PD1, CAN1_BASE_ADDRESS, 9},
    #endif
    #ifdef CAN1_TX_PH13_AF9
    {hal_ll_can_module_num(CAN_MODULE_1), PH13, CAN1_BASE_ADDRESS, 9},
    #endif
    {HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CAN_PIN_MAP_H_
// ------------------------------------------------------------------------- END
