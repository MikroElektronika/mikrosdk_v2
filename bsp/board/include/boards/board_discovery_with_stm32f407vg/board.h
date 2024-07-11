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

// Hardware revision number
#define BOARD_REV_MAJOR (D)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "STM32F4_DISCOVERY"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_P1_D1  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D2  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D3  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D4  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D5  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D6  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D7  PC1
#define HEADER_CONNECTOR_P1_D8  PC0
#define HEADER_CONNECTOR_P1_D9  PC3
#define HEADER_CONNECTOR_P1_D10 PC2
#define HEADER_CONNECTOR_P1_D11 PA1
#define HEADER_CONNECTOR_P1_D12 PA0
#define HEADER_CONNECTOR_P1_D13 PA3
#define HEADER_CONNECTOR_P1_D14 PA2
#define HEADER_CONNECTOR_P1_D15 PA5
#define HEADER_CONNECTOR_P1_D16 PA4
#define HEADER_CONNECTOR_P1_D17 PA7
#define HEADER_CONNECTOR_P1_D18 PA6
#define HEADER_CONNECTOR_P1_D19 PC5
#define HEADER_CONNECTOR_P1_D20 PC4
#define HEADER_CONNECTOR_P1_D21 PB1
#define HEADER_CONNECTOR_P1_D22 PB0
#define HEADER_CONNECTOR_P1_D23 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D24 PB2
#define HEADER_CONNECTOR_P1_D25 PE7
#define HEADER_CONNECTOR_P1_D26 PE8
#define HEADER_CONNECTOR_P1_D27 PE9
#define HEADER_CONNECTOR_P1_D28 PE10
#define HEADER_CONNECTOR_P1_D29 PE11
#define HEADER_CONNECTOR_P1_D30 PE12
#define HEADER_CONNECTOR_P1_D31 PE13
#define HEADER_CONNECTOR_P1_D32 PE14
#define HEADER_CONNECTOR_P1_D33 PE15
#define HEADER_CONNECTOR_P1_D34 PB10
#define HEADER_CONNECTOR_P1_D35 PB11
#define HEADER_CONNECTOR_P1_D36 PB12
#define HEADER_CONNECTOR_P1_D37 PB13
#define HEADER_CONNECTOR_P1_D38 PB14
#define HEADER_CONNECTOR_P1_D39 PB15
#define HEADER_CONNECTOR_P1_D40 PD8
#define HEADER_CONNECTOR_P1_D41 PD9
#define HEADER_CONNECTOR_P1_D42 PD10
#define HEADER_CONNECTOR_P1_D43 PD11
#define HEADER_CONNECTOR_P1_D44 PD12
#define HEADER_CONNECTOR_P1_D45 PD13
#define HEADER_CONNECTOR_P1_D46 PD14
#define HEADER_CONNECTOR_P1_D47 PD15
#define HEADER_CONNECTOR_P1_D48 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D49 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D50 // Pin not routed to mikroBUS

#define HEADER_CONNECTOR_P2_D1  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D2  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D3  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D4  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D5  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D6  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D7  PH0
#define HEADER_CONNECTOR_P2_D8  PH1
#define HEADER_CONNECTOR_P2_D9  PC14
#define HEADER_CONNECTOR_P2_D10 PC15
#define HEADER_CONNECTOR_P2_D11 PE6
#define HEADER_CONNECTOR_P2_D12 PC13
#define HEADER_CONNECTOR_P2_D13 PE4
#define HEADER_CONNECTOR_P2_D14 PE5
#define HEADER_CONNECTOR_P2_D15 PE2
#define HEADER_CONNECTOR_P2_D16 PE3
#define HEADER_CONNECTOR_P2_D17 PE0
#define HEADER_CONNECTOR_P2_D18 PE1
#define HEADER_CONNECTOR_P2_D19 PB8
#define HEADER_CONNECTOR_P2_D20 PB9
#define HEADER_CONNECTOR_P2_D21 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D22 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D23 PB6
#define HEADER_CONNECTOR_P2_D24 PB7
#define HEADER_CONNECTOR_P2_D25 PB4
#define HEADER_CONNECTOR_P2_D26 PB5
#define HEADER_CONNECTOR_P2_D27 PD7
#define HEADER_CONNECTOR_P2_D28 PB3
#define HEADER_CONNECTOR_P2_D29 PD5
#define HEADER_CONNECTOR_P2_D30 PD6
#define HEADER_CONNECTOR_P2_D31 PD3
#define HEADER_CONNECTOR_P2_D32 PD4
#define HEADER_CONNECTOR_P2_D33 PD1
#define HEADER_CONNECTOR_P2_D34 PD2
#define HEADER_CONNECTOR_P2_D35 PC12
#define HEADER_CONNECTOR_P2_D36 PD0
#define HEADER_CONNECTOR_P2_D37 PC10
#define HEADER_CONNECTOR_P2_D38 PC11
#define HEADER_CONNECTOR_P2_D39 PA14
#define HEADER_CONNECTOR_P2_D40 PA15
#define HEADER_CONNECTOR_P2_D41 PA10
#define HEADER_CONNECTOR_P2_D42 PA13
#define HEADER_CONNECTOR_P2_D43 PA8
#define HEADER_CONNECTOR_P2_D44 PA9
#define HEADER_CONNECTOR_P2_D45 PC8
#define HEADER_CONNECTOR_P2_D46 PC9
#define HEADER_CONNECTOR_P2_D47 PC6
#define HEADER_CONNECTOR_P2_D48 PC7
#define HEADER_CONNECTOR_P2_D49 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D50 // Pin not routed to mikroBUS

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
