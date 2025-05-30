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
 * @file  can_definitions.h
 * @brief MCU specific CAN module definitions for GD32VF103C4T6.
 */

#ifndef _CAN_DEFINITIONS_H_
#define _CAN_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

// CAN
#define CAN0_RX_PA11_REMAP_NONE
#define CAN0_TX_PA12_REMAP_NONE
#define CAN0_RX_PB8_REMAP_PARTIAL
#define CAN0_TX_PB9_REMAP_PARTIAL
#define CAN1_RX_PB12_REMAP_NONE
#define CAN1_TX_PB13_REMAP_NONE
#define CAN1_RX_PB5_REMAP_FULL
#define CAN1_TX_PB6_REMAP_FULL

#define CAN_MODULE_0 (1)
#define CAN_MODULE_1 (2)

#define CAN_MODULE_COUNT (2)

#define HAL_LL_CAN0_BASE_ADDRESS (0x40006400UL)
#define HAL_LL_CAN1_BASE_ADDRESS (0x40006800UL)

#define HAL_LL_CAN0_REMAP_NONE (0x80000000UL)
#define HAL_LL_CAN0_REMAP_PARTIAL (0x80004000UL)
#define HAL_LL_CAN0_REMAP_FULL (0x80006000UL)
#define HAL_LL_CAN1_REMAP_NONE (0x80000000UL)
#define HAL_LL_CAN1_REMAP_FULL (0x80400000UL)
// EOF CAN

#ifdef __cplusplus
}
#endif

#endif // _CAN_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
