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

#define BOARD_NAME "Freedom Development Platform for Kinetis K66, K65, and K26 MCUs"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN3_D1       PA27
#define HEADER_CONNECTOR_CN3_D2       // Pin not routed
#define HEADER_CONNECTOR_CN3_D3       PA26
#define HEADER_CONNECTOR_CN3_D4       // Pin not routed
#define HEADER_CONNECTOR_CN3_D5       PA4
#define HEADER_CONNECTOR_CN3_D6       // Pin not routed
#define HEADER_CONNECTOR_CN3_D7       PA6
#define HEADER_CONNECTOR_CN3_D8       // Pin not routed
#define HEADER_CONNECTOR_CN3_D9       PA7
#define HEADER_CONNECTOR_CN3_D10      // Pin not routed
#define HEADER_CONNECTOR_CN3_D11      PA8
#define HEADER_CONNECTOR_CN3_D12      // Pin not routed
#define HEADER_CONNECTOR_CN3_D13      PA9
#define HEADER_CONNECTOR_CN3_D14      // Pin not routed
#define HEADER_CONNECTOR_CN3_D15      PA1
#define HEADER_CONNECTOR_CN3_D16      // Pin not routed

#define HEADER_CONNECTOR_CN4_D1       // Pin not routed
#define HEADER_CONNECTOR_CN4_D2       PB7
#define HEADER_CONNECTOR_CN4_D3       // Pin not routed
#define HEADER_CONNECTOR_CN4_D4       PB6
#define HEADER_CONNECTOR_CN4_D5       // Pin not routed
#define HEADER_CONNECTOR_CN4_D6       PB5
#define HEADER_CONNECTOR_CN4_D7       // Pin not routed
#define HEADER_CONNECTOR_CN4_D8       PB4
#define HEADER_CONNECTOR_CN4_D9       PB23
#define HEADER_CONNECTOR_CN4_D10      PB3
#define HEADER_CONNECTOR_CN4_D11      // Pin not routed
#define HEADER_CONNECTOR_CN4_D12      PB2

#define HEADER_CONNECTOR_CN2_D1       // Pin not routed
#define HEADER_CONNECTOR_CN2_D2       PB18
#define HEADER_CONNECTOR_CN2_D3       // Pin not routed
#define HEADER_CONNECTOR_CN2_D4       PB19
#define HEADER_CONNECTOR_CN2_D5       // Pin not routed
#define HEADER_CONNECTOR_CN2_D6       PD0
#define HEADER_CONNECTOR_CN2_D7       PB10
#define HEADER_CONNECTOR_CN2_D8       PD2
#define HEADER_CONNECTOR_CN2_D9       PB11
#define HEADER_CONNECTOR_CN2_D10      PD3
#define HEADER_CONNECTOR_CN2_D11      PC0
#define HEADER_CONNECTOR_CN2_D12      PD1
#define HEADER_CONNECTOR_CN2_D13      PE24
#define HEADER_CONNECTOR_CN2_D14      // Pin not routed
#define HEADER_CONNECTOR_CN2_D15      PE25
#define HEADER_CONNECTOR_CN2_D16      // Pin not routed
#define HEADER_CONNECTOR_CN2_D17      PD13
#define HEADER_CONNECTOR_CN2_D18      PC11
#define HEADER_CONNECTOR_CN2_D19      PD12
#define HEADER_CONNECTOR_CN2_D20      PC10

#define HEADER_CONNECTOR_CN1_D1       PE12
#define HEADER_CONNECTOR_CN1_D2       PC3
#define HEADER_CONNECTOR_CN1_D3       PE11
#define HEADER_CONNECTOR_CN1_D4       PC4
#define HEADER_CONNECTOR_CN1_D5       PC1
#define HEADER_CONNECTOR_CN1_D6       PC16
#define HEADER_CONNECTOR_CN1_D7       PC6
#define HEADER_CONNECTOR_CN1_D8       PC8
#define HEADER_CONNECTOR_CN1_D9       PE9
#define HEADER_CONNECTOR_CN1_D10      PC12
#define HEADER_CONNECTOR_CN1_D11      PC11
#define HEADER_CONNECTOR_CN1_D12      PC5
#define HEADER_CONNECTOR_CN1_D13      PE8
#define HEADER_CONNECTOR_CN1_D14      PC2
#define HEADER_CONNECTOR_CN1_D15      PE7
#define HEADER_CONNECTOR_CN1_D16      PA25

// LEDS
#define LED1    PC9         // RED
#define LED2    PE6         // GREEN
#define LED3    PA11        // BLUE

// BUTTONS
#define BUTTON2 PD11
#define BUTTON3 PA10

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END