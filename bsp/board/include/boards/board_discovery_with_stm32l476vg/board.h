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
 * @file  board.h
 * @brief Main board pin mapping.
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.4/v2.14.4/new_hw/2025-05-16.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "STM32L476VG_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_P1_D1      // Pin not routed
#define HEADER_CONNECTOR_P1_D2      // Pin not routed
#define HEADER_CONNECTOR_P1_D3      // Pin not routed
#define HEADER_CONNECTOR_P1_D4      // Pin not routed
#define HEADER_CONNECTOR_P1_D5      // Pin not routed
#define HEADER_CONNECTOR_P1_D6      // Pin not routed
#define HEADER_CONNECTOR_P1_D7      GPIO_PB3
#define HEADER_CONNECTOR_P1_D8      GPIO_PB2
#define HEADER_CONNECTOR_P1_D9      GPIO_PE8
#define HEADER_CONNECTOR_P1_D10     GPIO_PA0
#define HEADER_CONNECTOR_P1_D11     GPIO_PA5
#define HEADER_CONNECTOR_P1_D12     GPIO_PA1
#define HEADER_CONNECTOR_P1_D13     GPIO_PA2
#define HEADER_CONNECTOR_P1_D14     GPIO_PA3
#define HEADER_CONNECTOR_P1_D15     GPIO_PB6
#define HEADER_CONNECTOR_P1_D16     GPIO_PB7
#define HEADER_CONNECTOR_P1_D17     GPIO_PD0
#define HEADER_CONNECTOR_P1_D18     // Pin not routed
#define HEADER_CONNECTOR_P1_D19     // Pin not routed
#define HEADER_CONNECTOR_P1_D20     // Pin not routed

#define HEADER_CONNECTOR_P2_D1      // Pin not routed
#define HEADER_CONNECTOR_P2_D2      // Pin not routed
#define HEADER_CONNECTOR_P2_D3      // Pin not routed
#define HEADER_CONNECTOR_P2_D4      // Pin not routed
#define HEADER_CONNECTOR_P2_D5      // Pin not routed
#define HEADER_CONNECTOR_P2_D6      // Pin not routed
#define HEADER_CONNECTOR_P2_D7      GPIO_PC14
#define HEADER_CONNECTOR_P2_D8      GPIO_PC15
#define HEADER_CONNECTOR_P2_D9      GPIO_PH0
#define HEADER_CONNECTOR_P2_D10     GPIO_PH1
#define HEADER_CONNECTOR_P2_D11     // Pin not routed
#define HEADER_CONNECTOR_P2_D12     // Pin not routed
#define HEADER_CONNECTOR_P2_D13     GPIO_PE11
#define HEADER_CONNECTOR_P2_D14     GPIO_PE10
#define HEADER_CONNECTOR_P2_D15     GPIO_PE12
#define HEADER_CONNECTOR_P2_D16     GPIO_PE13
#define HEADER_CONNECTOR_P2_D17     GPIO_PE14
#define HEADER_CONNECTOR_P2_D18     GPIO_PE15
#define HEADER_CONNECTOR_P2_D19     // Pin not routed
#define HEADER_CONNECTOR_P2_D20     // Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
