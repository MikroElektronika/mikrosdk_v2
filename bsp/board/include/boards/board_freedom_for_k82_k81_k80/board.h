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

#define BOARD_NAME "Freedom Development Platform for Kinetis K82, K81, and K80 MCUs"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       GPIO_PA5
#define HEADER_CONNECTOR_CN1_D2       GPIO_PB16
#define HEADER_CONNECTOR_CN1_D3       GPIO_PA13
#define HEADER_CONNECTOR_CN1_D4       GPIO_PB17
#define HEADER_CONNECTOR_CN1_D5       GPIO_PA12
#define HEADER_CONNECTOR_CN1_D6       GPIO_PC12
#define HEADER_CONNECTOR_CN1_D7       GPIO_PA17
#define HEADER_CONNECTOR_CN1_D8       GPIO_PD0
#define HEADER_CONNECTOR_CN1_D9       GPIO_PA14
#define HEADER_CONNECTOR_CN1_D10      GPIO_PC11
#define HEADER_CONNECTOR_CN1_D11      GPIO_PC7
#define HEADER_CONNECTOR_CN1_D12      GPIO_PC10
#define HEADER_CONNECTOR_CN1_D13      GPIO_PA16
#define HEADER_CONNECTOR_CN1_D14      GPIO_PC8
#define HEADER_CONNECTOR_CN1_D15      GPIO_PA15
#define HEADER_CONNECTOR_CN1_D16      GPIO_PC9

#define HEADER_CONNECTOR_CN2_D1       GPIO_PB20
#define HEADER_CONNECTOR_CN2_D2       GPIO_PC3
#define HEADER_CONNECTOR_CN2_D3       GPIO_PB21
#define HEADER_CONNECTOR_CN2_D4       GPIO_PC5
#define HEADER_CONNECTOR_CN2_D5       GPIO_PB22
#define HEADER_CONNECTOR_CN2_D6       GPIO_PD4
#define HEADER_CONNECTOR_CN2_D7       GPIO_PB23
#define HEADER_CONNECTOR_CN2_D8       GPIO_PD2
#define HEADER_CONNECTOR_CN2_D9       GPIO_PC0
#define HEADER_CONNECTOR_CN2_D10      GPIO_PD3
#define HEADER_CONNECTOR_CN2_D11      // Pin not routed
#define HEADER_CONNECTOR_CN2_D12      GPIO_PD1
#define HEADER_CONNECTOR_CN2_D13      // Pin not routed
#define HEADER_CONNECTOR_CN2_D14      // Pin not routed
#define HEADER_CONNECTOR_CN2_D15      // Pin not routed
#define HEADER_CONNECTOR_CN2_D16      // Pin not routed
#define HEADER_CONNECTOR_CN2_D17      // Pin not routed
#define HEADER_CONNECTOR_CN2_D18      GPIO_PA1
#define HEADER_CONNECTOR_CN2_D19      // Pin not routed
#define HEADER_CONNECTOR_CN2_D20      GPIO_PA2

#define HEADER_CONNECTOR_CN4_D1       // Pin not routed
#define HEADER_CONNECTOR_CN4_D2       GPIO_PB0
#define HEADER_CONNECTOR_CN4_D3       // Pin not routed
#define HEADER_CONNECTOR_CN4_D4       GPIO_PB1
#define HEADER_CONNECTOR_CN4_D5       // Pin not routed
#define HEADER_CONNECTOR_CN4_D6       GPIO_PC1
#define HEADER_CONNECTOR_CN4_D7       // Pin not routed
#define HEADER_CONNECTOR_CN4_D8       GPIO_PC2
#define HEADER_CONNECTOR_CN4_D9       GPIO_PB20
#define HEADER_CONNECTOR_CN4_D10      GPIO_PB3
#define HEADER_CONNECTOR_CN4_D11      // Pin not routed
#define HEADER_CONNECTOR_CN4_D12      GPIO_PB2

#define HEADER_CONNECTOR_CN5_D1       // Pin not routed
#define HEADER_CONNECTOR_CN5_D2       // Pin not routed
#define HEADER_CONNECTOR_CN5_D3       GPIO_PA2
#define HEADER_CONNECTOR_CN5_D4       GPIO_PA1
#define HEADER_CONNECTOR_CN5_D5       GPIO_PB2
#define HEADER_CONNECTOR_CN5_D6       GPIO_PB3
#define HEADER_CONNECTOR_CN5_D7       GPIO_PB0
#define HEADER_CONNECTOR_CN5_D8       GPIO_PC3
#define HEADER_CONNECTOR_CN5_D9       GPIO_PB23
#define HEADER_CONNECTOR_CN5_D10      GPIO_PB22
#define HEADER_CONNECTOR_CN5_D11      GPIO_PB21
#define HEADER_CONNECTOR_CN5_D12      GPIO_PB20
#define HEADER_CONNECTOR_CN5_D13      GPIO_PB19
#define HEADER_CONNECTOR_CN5_D14      GPIO_PB18
#define HEADER_CONNECTOR_CN5_D15      GPIO_PB11
#define HEADER_CONNECTOR_CN5_D16      GPIO_PB10
#define HEADER_CONNECTOR_CN5_D17      GPIO_PC8
#define HEADER_CONNECTOR_CN5_D18      GPIO_PC9

// LEDS
#define LED1    GPIO_PC8          // RED
#define LED2    GPIO_PC9          // GREEN
#define LED3    GPIO_PC10         // BLUE

// BUTTONS
#define BUTTON2 GPIO_PA4
#define BUTTON3 GPIO_PC6

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
