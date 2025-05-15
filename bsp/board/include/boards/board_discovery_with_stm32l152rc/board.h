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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.4/new_hw/2025-05-15.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "STM32L152RC_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_P1_D1 	// Pin not routed
#define HEADER_CONNECTOR_P1_D2 	// Pin not routed
#define HEADER_CONNECTOR_P1_D3 	// Pin not routed
#define HEADER_CONNECTOR_P1_D4 	GPIO_PC13
#define HEADER_CONNECTOR_P1_D5 	GPIO_PC14
#define HEADER_CONNECTOR_P1_D6 	GPIO_PC15
#define HEADER_CONNECTOR_P1_D7 	// Pin not routed
#define HEADER_CONNECTOR_P1_D8 	// Pin not routed
#define HEADER_CONNECTOR_P1_D9 	// Pin not routed
#define HEADER_CONNECTOR_P1_D10	// Pin not routed
#define HEADER_CONNECTOR_P1_D11	GPIO_PC0
#define HEADER_CONNECTOR_P1_D12	GPIO_PC1
#define HEADER_CONNECTOR_P1_D13	GPIO_PC2
#define HEADER_CONNECTOR_P1_D14	GPIO_PC3
#define HEADER_CONNECTOR_P1_D15	GPIO_PA0
#define HEADER_CONNECTOR_P1_D16	GPIO_PA1
#define HEADER_CONNECTOR_P1_D17	GPIO_PA2
#define HEADER_CONNECTOR_P1_D18	GPIO_PA3
#define HEADER_CONNECTOR_P1_D19	GPIO_PA4
#define HEADER_CONNECTOR_P1_D20	GPIO_PA5
#define HEADER_CONNECTOR_P1_D21	GPIO_PB2
#define HEADER_CONNECTOR_P1_D22	GPIO_PB10
#define HEADER_CONNECTOR_P1_D23	GPIO_PB11
#define HEADER_CONNECTOR_P1_D24	GPIO_PB12
#define HEADER_CONNECTOR_P1_D25	GPIO_PB13
#define HEADER_CONNECTOR_P1_D26	GPIO_PB14
#define HEADER_CONNECTOR_P1_D27	GPIO_PB15
#define HEADER_CONNECTOR_P1_D28	// Pin not routed

#define HEADER_CONNECTOR_P2_D1 	// Pin not routed
#define HEADER_CONNECTOR_P2_D2 	// Pin not routed
#define HEADER_CONNECTOR_P2_D3 	GPIO_PB9
#define HEADER_CONNECTOR_P2_D4 	GPIO_PB8
#define HEADER_CONNECTOR_P2_D5 	// Pin not routed
#define HEADER_CONNECTOR_P2_D6 	// Pin not routed
#define HEADER_CONNECTOR_P2_D7 	GPIO_PB7
#define HEADER_CONNECTOR_P2_D8 	GPIO_PB6
#define HEADER_CONNECTOR_P2_D9 	GPIO_PB5
#define HEADER_CONNECTOR_P2_D10	// Pin not routed
#define HEADER_CONNECTOR_P2_D11	// Pin not routed
#define HEADER_CONNECTOR_P2_D12	GPIO_PD2
#define HEADER_CONNECTOR_P2_D13	GPIO_PC12
#define HEADER_CONNECTOR_P2_D14	GPIO_PC11
#define HEADER_CONNECTOR_P2_D15	GPIO_PC10
#define HEADER_CONNECTOR_P2_D16	// Pin not routed
#define HEADER_CONNECTOR_P2_D17	// Pin not routed
#define HEADER_CONNECTOR_P2_D18	// Pin not routed
#define HEADER_CONNECTOR_P2_D19	GPIO_PA12
#define HEADER_CONNECTOR_P2_D20	GPIO_PA11
#define HEADER_CONNECTOR_P2_D21	GPIO_PA10
#define HEADER_CONNECTOR_P2_D22	GPIO_PA9
#define HEADER_CONNECTOR_P2_D23	GPIO_PA8
#define HEADER_CONNECTOR_P2_D24	GPIO_PC9
#define HEADER_CONNECTOR_P2_D25	GPIO_PC8
#define HEADER_CONNECTOR_P2_D26	GPIO_PC7
#define HEADER_CONNECTOR_P2_D27	GPIO_PC6
#define HEADER_CONNECTOR_P2_D28	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
