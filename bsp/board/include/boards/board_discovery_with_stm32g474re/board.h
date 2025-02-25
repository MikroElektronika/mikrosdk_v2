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
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "STM32G474RE_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN8_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D8 	GPIO_PC9
#define HEADER_CONNECTOR_CN8_D9 	GPIO_PC8
#define HEADER_CONNECTOR_CN8_D10	GPIO_PC7
#define HEADER_CONNECTOR_CN8_D11	GPIO_PC6
#define HEADER_CONNECTOR_CN8_D12	GPIO_PB15
#define HEADER_CONNECTOR_CN8_D13	GPIO_PB14
#define HEADER_CONNECTOR_CN8_D14	GPIO_PB13
#define HEADER_CONNECTOR_CN8_D15	GPIO_PB12
#define HEADER_CONNECTOR_CN8_D16	GPIO_PB11
#define HEADER_CONNECTOR_CN8_D17	GPIO_PC5
#define HEADER_CONNECTOR_CN8_D18	GPIO_PB10
#define HEADER_CONNECTOR_CN8_D19	GPIO_PB1
#define HEADER_CONNECTOR_CN8_D20	GPIO_PB0
#define HEADER_CONNECTOR_CN8_D21	GPIO_PB2
#define HEADER_CONNECTOR_CN8_D22	GPIO_PC4
#define HEADER_CONNECTOR_CN8_D23	GPIO_PA7
#define HEADER_CONNECTOR_CN8_D24	GPIO_PA6
#define HEADER_CONNECTOR_CN8_D25	GPIO_PA5
#define HEADER_CONNECTOR_CN8_D26	GPIO_PA4
#define HEADER_CONNECTOR_CN8_D27	GPIO_PA3
#define HEADER_CONNECTOR_CN8_D28	GPIO_PA2
#define HEADER_CONNECTOR_CN8_D29	GPIO_PA1
#define HEADER_CONNECTOR_CN8_D30	GPIO_PA0
#define HEADER_CONNECTOR_CN8_D31	GPIO_PC3

#define HEADER_CONNECTOR_CN9_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D4 	GPIO_PA8
#define HEADER_CONNECTOR_CN9_D5 	GPIO_PA9
#define HEADER_CONNECTOR_CN9_D6 	GPIO_PA10
#define HEADER_CONNECTOR_CN9_D7 	GPIO_PA11
#define HEADER_CONNECTOR_CN9_D8 	GPIO_PA12
#define HEADER_CONNECTOR_CN9_D9 	GPIO_PA13
#define HEADER_CONNECTOR_CN9_D10	GPIO_PA14
#define HEADER_CONNECTOR_CN9_D11	GPIO_PA15
#define HEADER_CONNECTOR_CN9_D12	GPIO_PC10
#define HEADER_CONNECTOR_CN9_D13	GPIO_PC11
#define HEADER_CONNECTOR_CN9_D14	GPIO_PC12
#define HEADER_CONNECTOR_CN9_D15	GPIO_PD2
#define HEADER_CONNECTOR_CN9_D16	GPIO_PB3
#define HEADER_CONNECTOR_CN9_D17	GPIO_PB4
#define HEADER_CONNECTOR_CN9_D18	GPIO_PB5
#define HEADER_CONNECTOR_CN9_D19	GPIO_PB6
#define HEADER_CONNECTOR_CN9_D20	GPIO_PB7
#define HEADER_CONNECTOR_CN9_D21	GPIO_PB8
#define HEADER_CONNECTOR_CN9_D22	GPIO_PB9
#define HEADER_CONNECTOR_CN9_D23	GPIO_PC13
#define HEADER_CONNECTOR_CN9_D24	GPIO_PC14
#define HEADER_CONNECTOR_CN9_D25	GPIO_PC15
#define HEADER_CONNECTOR_CN9_D26	GPIO_PF0
#define HEADER_CONNECTOR_CN9_D27	GPIO_PF1
#define HEADER_CONNECTOR_CN9_D28	GPIO_PC0
#define HEADER_CONNECTOR_CN9_D29	GPIO_PC1
#define HEADER_CONNECTOR_CN9_D30	GPIO_PG10
#define HEADER_CONNECTOR_CN9_D31	GPIO_PC2

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
