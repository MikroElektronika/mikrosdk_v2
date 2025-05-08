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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.3/new_hw/2025-05-08.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "STM32F411VE_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2	GPIO_PA14
#define HEADER_CONNECTOR_CN2_D3	// Pin not routed
#define HEADER_CONNECTOR_CN2_D4	GPIO_PA13
#define HEADER_CONNECTOR_CN2_D5	// Pin not routed
#define HEADER_CONNECTOR_CN2_D6	GPIO_PB3

#define HEADER_CONNECTOR_CN5_D1	GPIO_PA9
#define HEADER_CONNECTOR_CN5_D2	GPIO_PA11
#define HEADER_CONNECTOR_CN5_D3	GPIO_PA12
#define HEADER_CONNECTOR_CN5_D4	GPIO_PA10
#define HEADER_CONNECTOR_CN5_D5	// Pin not routed

#define HEADER_CONNECTOR_P1_D1 	// Pin not routed
#define HEADER_CONNECTOR_P1_D2 	// Pin not routed
#define HEADER_CONNECTOR_P1_D3 	// Pin not routed
#define HEADER_CONNECTOR_P1_D4 	// Pin not routed
#define HEADER_CONNECTOR_P1_D5 	// Pin not routed
#define HEADER_CONNECTOR_P1_D6 	// Pin not routed
#define HEADER_CONNECTOR_P1_D7 	GPIO_PC1
#define HEADER_CONNECTOR_P1_D8 	GPIO_PC0
#define HEADER_CONNECTOR_P1_D9 	GPIO_PC3
#define HEADER_CONNECTOR_P1_D10	GPIO_PC2
#define HEADER_CONNECTOR_P1_D11	// Pin not routed
#define HEADER_CONNECTOR_P1_D12	// Pin not routed
#define HEADER_CONNECTOR_P1_D13	GPIO_PA3
#define HEADER_CONNECTOR_P1_D14	GPIO_PA2
#define HEADER_CONNECTOR_P1_D15	GPIO_PA5
#define HEADER_CONNECTOR_P1_D16	GPIO_PA4
#define HEADER_CONNECTOR_P1_D17	GPIO_PA7
#define HEADER_CONNECTOR_P1_D18	GPIO_PA6
#define HEADER_CONNECTOR_P1_D19	GPIO_PC5
#define HEADER_CONNECTOR_P1_D20	GPIO_PC4
#define HEADER_CONNECTOR_P1_D21	GPIO_PB1
#define HEADER_CONNECTOR_P1_D22	GPIO_PB0
#define HEADER_CONNECTOR_P1_D23	// Pin not routed
#define HEADER_CONNECTOR_P1_D24	GPIO_PB2
#define HEADER_CONNECTOR_P1_D25	GPIO_PE7
#define HEADER_CONNECTOR_P1_D26	GPIO_PE8
#define HEADER_CONNECTOR_P1_D27	GPIO_PE9
#define HEADER_CONNECTOR_P1_D28	GPIO_PE10
#define HEADER_CONNECTOR_P1_D29	GPIO_PE11
#define HEADER_CONNECTOR_P1_D30	GPIO_PE12
#define HEADER_CONNECTOR_P1_D31	GPIO_PE13
#define HEADER_CONNECTOR_P1_D32	GPIO_PE14
#define HEADER_CONNECTOR_P1_D33	GPIO_PE15
#define HEADER_CONNECTOR_P1_D34	GPIO_PB10
#define HEADER_CONNECTOR_P1_D35	// Pin not routed
#define HEADER_CONNECTOR_P1_D36	GPIO_PB12
#define HEADER_CONNECTOR_P1_D37	GPIO_PB13
#define HEADER_CONNECTOR_P1_D38	GPIO_PB14
#define HEADER_CONNECTOR_P1_D39	GPIO_PB15
#define HEADER_CONNECTOR_P1_D40	GPIO_PD8
#define HEADER_CONNECTOR_P1_D41	GPIO_PD9
#define HEADER_CONNECTOR_P1_D42	GPIO_PD10
#define HEADER_CONNECTOR_P1_D43	GPIO_PD11
#define HEADER_CONNECTOR_P1_D44	GPIO_PD12
#define HEADER_CONNECTOR_P1_D45	GPIO_PD13
#define HEADER_CONNECTOR_P1_D46	GPIO_PD14
#define HEADER_CONNECTOR_P1_D47	GPIO_PD15
#define HEADER_CONNECTOR_P1_D48	// Pin not routed
#define HEADER_CONNECTOR_P1_D49	// Pin not routed
#define HEADER_CONNECTOR_P1_D50	// Pin not routed

#define HEADER_CONNECTOR_P2_D1 	// Pin not routed
#define HEADER_CONNECTOR_P2_D2 	// Pin not routed
#define HEADER_CONNECTOR_P2_D3 	// Pin not routed
#define HEADER_CONNECTOR_P2_D4 	// Pin not routed
#define HEADER_CONNECTOR_P2_D5 	// Pin not routed
#define HEADER_CONNECTOR_P2_D6 	// Pin not routed
#define HEADER_CONNECTOR_P2_D7 	GPIO_PH0
#define HEADER_CONNECTOR_P2_D8 	GPIO_PH1
#define HEADER_CONNECTOR_P2_D9 	GPIO_PC14
#define HEADER_CONNECTOR_P2_D10	GPIO_PC15
#define HEADER_CONNECTOR_P2_D11	GPIO_PE6
#define HEADER_CONNECTOR_P2_D12	GPIO_PC13
#define HEADER_CONNECTOR_P2_D13	GPIO_PE4
#define HEADER_CONNECTOR_P2_D14	GPIO_PE5
#define HEADER_CONNECTOR_P2_D15	GPIO_PE2
#define HEADER_CONNECTOR_P2_D16	GPIO_PE3
#define HEADER_CONNECTOR_P2_D17	GPIO_PE0
#define HEADER_CONNECTOR_P2_D18	GPIO_PE1
#define HEADER_CONNECTOR_P2_D19	GPIO_PB8
#define HEADER_CONNECTOR_P2_D20	GPIO_PB9
#define HEADER_CONNECTOR_P2_D21	// Pin not routed
#define HEADER_CONNECTOR_P2_D22	// Pin not routed
#define HEADER_CONNECTOR_P2_D23	GPIO_PB6
#define HEADER_CONNECTOR_P2_D24	GPIO_PB7
#define HEADER_CONNECTOR_P2_D25	GPIO_PB4
#define HEADER_CONNECTOR_P2_D26	GPIO_PB5
#define HEADER_CONNECTOR_P2_D27	// Pin not routed
#define HEADER_CONNECTOR_P2_D28	GPIO_PB3
#define HEADER_CONNECTOR_P2_D29	// Pin not routed
#define HEADER_CONNECTOR_P2_D30	// Pin not routed
#define HEADER_CONNECTOR_P2_D31	GPIO_PD3
#define HEADER_CONNECTOR_P2_D32	GPIO_PD4
#define HEADER_CONNECTOR_P2_D33	GPIO_PD1
#define HEADER_CONNECTOR_P2_D34	GPIO_PD2
#define HEADER_CONNECTOR_P2_D35	GPIO_PC12
#define HEADER_CONNECTOR_P2_D36	GPIO_PD0
#define HEADER_CONNECTOR_P2_D37	GPIO_PC10
#define HEADER_CONNECTOR_P2_D38	GPIO_PC11
#define HEADER_CONNECTOR_P2_D39	GPIO_PA14
#define HEADER_CONNECTOR_P2_D40	GPIO_PA15
#define HEADER_CONNECTOR_P2_D41	GPIO_PA10
#define HEADER_CONNECTOR_P2_D42	GPIO_PA13
#define HEADER_CONNECTOR_P2_D43	GPIO_PA8
#define HEADER_CONNECTOR_P2_D44	GPIO_PA9
#define HEADER_CONNECTOR_P2_D45	GPIO_PC8
#define HEADER_CONNECTOR_P2_D46	GPIO_PC9
#define HEADER_CONNECTOR_P2_D47	GPIO_PC6
#define HEADER_CONNECTOR_P2_D48	GPIO_PC7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
