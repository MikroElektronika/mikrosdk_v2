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

#define BOARD_NAME "Freedom Development Platform for Kinetis K64, K63, and K24 MCUs"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       PB18
#define HEADER_CONNECTOR_CN1_D2       PC16
#define HEADER_CONNECTOR_CN1_D3       PB19
#define HEADER_CONNECTOR_CN1_D4       PC17
#define HEADER_CONNECTOR_CN1_D5       PC1
#define HEADER_CONNECTOR_CN1_D6       PB9
#define HEADER_CONNECTOR_CN1_D7       PC8
#define HEADER_CONNECTOR_CN1_D8       PA1
#define HEADER_CONNECTOR_CN1_D9       PC9
#define HEADER_CONNECTOR_CN1_D10      PB23
#define HEADER_CONNECTOR_CN1_D11      PC0
#define HEADER_CONNECTOR_CN1_D12      PA2
#define HEADER_CONNECTOR_CN1_D13      PC7
#define HEADER_CONNECTOR_CN1_D14      PC2
#define HEADER_CONNECTOR_CN1_D15      PC5
#define HEADER_CONNECTOR_CN1_D16      PC3

#define HEADER_CONNECTOR_CN2_D1       PE26
#define HEADER_CONNECTOR_CN2_D2       PC12
#define HEADER_CONNECTOR_CN2_D3       // Pin not routed
#define HEADER_CONNECTOR_CN2_D4       PC4
#define HEADER_CONNECTOR_CN2_D5       // Pin not routed
#define HEADER_CONNECTOR_CN2_D6       PD0
#define HEADER_CONNECTOR_CN2_D7       // Pin not routed
#define HEADER_CONNECTOR_CN2_D8       PD2
#define HEADER_CONNECTOR_CN2_D9       // Pin not routed
#define HEADER_CONNECTOR_CN2_D10      PD3
#define HEADER_CONNECTOR_CN2_D11      // Pin not routed
#define HEADER_CONNECTOR_CN2_D12      PD1
#define HEADER_CONNECTOR_CN2_D13      // Pin not routed
#define HEADER_CONNECTOR_CN2_D14      // Pin not routed
#define HEADER_CONNECTOR_CN2_D15      // Pin not routed
#define HEADER_CONNECTOR_CN2_D16      // Pin not routed
#define HEADER_CONNECTOR_CN2_D17      PE25
#define HEADER_CONNECTOR_CN2_D18      PE25
#define HEADER_CONNECTOR_CN2_D19      // Pin not routed
#define HEADER_CONNECTOR_CN2_D20      PE24

#define HEADER_CONNECTOR_CN4_D1       // Pin not routed
#define HEADER_CONNECTOR_CN4_D2       PB2
#define HEADER_CONNECTOR_CN4_D3       // Pin not routed
#define HEADER_CONNECTOR_CN4_D4       PB3
#define HEADER_CONNECTOR_CN4_D5       // Pin not routed
#define HEADER_CONNECTOR_CN4_D6       PB10
#define HEADER_CONNECTOR_CN4_D7       // Pin not routed
#define HEADER_CONNECTOR_CN4_D8       PB11
#define HEADER_CONNECTOR_CN4_D9       PB20
#define HEADER_CONNECTOR_CN4_D10      PC11
#define HEADER_CONNECTOR_CN4_D11      // Pin not routed
#define HEADER_CONNECTOR_CN4_D12      PC10

// LEDS
#define LED1    PB22         // RED
#define LED2    PE26         // GREEN
#define LED3    PB21         // BLUE

// BUTTONS
#define BUTTON2 PC6
#define BUTTON3 PA4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END