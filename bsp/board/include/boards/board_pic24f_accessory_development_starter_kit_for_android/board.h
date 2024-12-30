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
 * @file  board.h
 * @brief Main board pin mapping.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "MPLab Starter Kit For PIC24H MCUs"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_J3_D1       GPIO_PD8
#define HEADER_CONNECTOR_J3_D2       GPIO_PD9
#define HEADER_CONNECTOR_J3_D3       GPIO_PD10
#define HEADER_CONNECTOR_J3_D4       GPIO_PC4
#define HEADER_CONNECTOR_J3_D5       GPIO_PG6
#define HEADER_CONNECTOR_J3_D6       GPIO_PG7
#define HEADER_CONNECTOR_J3_D7       // Pin not routed
#define HEADER_CONNECTOR_J3_D8       GPIO_PA9

#define HEADER_CONNECTOR_J4_D1       // Pin not routed
#define HEADER_CONNECTOR_J4_D2       // Pin not routed
#define HEADER_CONNECTOR_J4_D3       // Pin not routed
#define HEADER_CONNECTOR_J4_D4       GPIO_PB7
#define HEADER_CONNECTOR_J4_D5       GPIO_PB6
#define HEADER_CONNECTOR_J4_D6       // Pin not routed

#define HEADER_CONNECTOR_J5_D1       GPIO_PB0
#define HEADER_CONNECTOR_J5_D2       GPIO_PB1
#define HEADER_CONNECTOR_J5_D3       GPIO_PB2
#define HEADER_CONNECTOR_J5_D4       GPIO_PB3
#define HEADER_CONNECTOR_J5_D5       GPIO_PB4
#define HEADER_CONNECTOR_J5_D6       GPIO_PB8

#define HEADER_CONNECTOR_J6_D1       // Pin not routed
#define HEADER_CONNECTOR_J6_D2       GPIO_PG3
#define HEADER_CONNECTOR_J6_D3       GPIO_PG2
#define HEADER_CONNECTOR_J6_D4       // Pin not routed
#define HEADER_CONNECTOR_J6_D5       // Pin not routed

#define HEADER_CONNECTOR_J7_D1       GPIO_PF8
#define HEADER_CONNECTOR_J7_D2       GPIO_PF2
#define HEADER_CONNECTOR_J7_D3       GPIO_PF3
#define HEADER_CONNECTOR_J7_D4       GPIO_PF5
#define HEADER_CONNECTOR_J7_D5       GPIO_PF4
#define HEADER_CONNECTOR_J7_D6       GPIO_PD15
#define HEADER_CONNECTOR_J7_D7       GPIO_PD14
#define HEADER_CONNECTOR_J7_D8       GPIO_PB15
#define HEADER_CONNECTOR_J7_D9       GPIO_PB14
#define HEADER_CONNECTOR_J7_D10      GPIO_PB13
#define HEADER_CONNECTOR_J7_D11      GPIO_PB12
#define HEADER_CONNECTOR_J7_D12      // Pin not routed

#define HEADER_CONNECTOR_J8_D1       GPIO_PD10
#define HEADER_CONNECTOR_J8_D2       GPIO_PD9
#define HEADER_CONNECTOR_J8_D3       GPIO_PD8
#define HEADER_CONNECTOR_J8_D4       GPIO_PA15
#define HEADER_CONNECTOR_J8_D5       GPIO_PA14
#define HEADER_CONNECTOR_J8_D6       GPIO_PA5
#define HEADER_CONNECTOR_J7_D7       GPIO_PA4
#define HEADER_CONNECTOR_J8_D8       GPIO_PA3
#define HEADER_CONNECTOR_J8_D9       GPIO_PA2
#define HEADER_CONNECTOR_J8_D10      // Pin not routed
#define HEADER_CONNECTOR_J8_D11      // Pin not routed
#define HEADER_CONNECTOR_J8_D12      // Pin not routed

#define HEADER_CONNECTOR_J10_D1      // Pin not routed
#define HEADER_CONNECTOR_J10_D2      // Pin not routed
#define HEADER_CONNECTOR_J10_D3      // Pin not routed
#define HEADER_CONNECTOR_J10_D4      // Pin not routed
#define HEADER_CONNECTOR_J10_D5      // Pin not routed
#define HEADER_CONNECTOR_J10_D6      // Pin not routed

#define HEADER_CONNECTOR_J14_D1      GPIO_PD11
#define HEADER_CONNECTOR_J14_D2      GPIO_PD0
#define HEADER_CONNECTOR_J14_D3      GPIO_PD1
#define HEADER_CONNECTOR_J14_D4      GPIO_PD2
#define HEADER_CONNECTOR_J14_D5      GPIO_PD3
#define HEADER_CONNECTOR_J14_D6      GPIO_PD12
#define HEADER_CONNECTOR_J14_D7      GPIO_PD4
#define HEADER_CONNECTOR_J14_D8      GPIO_PD5

// LEDS
#define LED1    GPIO_PE0
#define LED2    GPIO_PE1
#define LED3    GPIO_PE2
#define LED4    GPIO_PE3
#define LED5    GPIO_PE4
#define LED6    GPIO_PE5
#define LED7    GPIO_PE6
#define LED8    GPIO_PE7

// BUTTONS
#define BUTTON1 GPIO_PA1
#define BUTTON2 GPIO_PB11
#define BUTTON3 GPIO_PF12
#define BUTTON4 GPIO_PF13

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END