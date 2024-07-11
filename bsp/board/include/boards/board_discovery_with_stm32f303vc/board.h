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
#define BOARD_REV_MAJOR (E)
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "STM32F3_DISCOVERY"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_P1_D1  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D2  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D3  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D4  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D5  PC1
#define HEADER_CONNECTOR_P1_D6  PC0
#define HEADER_CONNECTOR_P1_D7  PC3
#define HEADER_CONNECTOR_P1_D8  PC2
#define HEADER_CONNECTOR_P1_D9  PA1
#define HEADER_CONNECTOR_P1_D10 PF2
#define HEADER_CONNECTOR_P1_D11 PA3
#define HEADER_CONNECTOR_P1_D12 PA0
#define HEADER_CONNECTOR_P1_D13 PF4
#define HEADER_CONNECTOR_P1_D14 PA2
#define HEADER_CONNECTOR_P1_D15 PA5
#define HEADER_CONNECTOR_P1_D16 PA4
#define HEADER_CONNECTOR_P1_D17 PA7
#define HEADER_CONNECTOR_P1_D18 PA6
#define HEADER_CONNECTOR_P1_D19 PC5
#define HEADER_CONNECTOR_P1_D20 PC4
#define HEADER_CONNECTOR_P1_D21 PB1
#define HEADER_CONNECTOR_P1_D22 PB0
#define HEADER_CONNECTOR_P1_D23 PE7
#define HEADER_CONNECTOR_P1_D24 PB2
#define HEADER_CONNECTOR_P1_D25 PE9
#define HEADER_CONNECTOR_P1_D26 PE8
#define HEADER_CONNECTOR_P1_D27 PE11
#define HEADER_CONNECTOR_P1_D28 PE10
#define HEADER_CONNECTOR_P1_D29 PE13
#define HEADER_CONNECTOR_P1_D30 PE12
#define HEADER_CONNECTOR_P1_D31 PE15
#define HEADER_CONNECTOR_P1_D32 PE14
#define HEADER_CONNECTOR_P1_D33 PB11
#define HEADER_CONNECTOR_P1_D34 PB10
#define HEADER_CONNECTOR_P1_D35 PB13
#define HEADER_CONNECTOR_P1_D36 PB12
#define HEADER_CONNECTOR_P1_D37 PB15
#define HEADER_CONNECTOR_P1_D38 PB14
#define HEADER_CONNECTOR_P1_D39 PD9
#define HEADER_CONNECTOR_P1_D40 PD8
#define HEADER_CONNECTOR_P1_D41 PD11
#define HEADER_CONNECTOR_P1_D42 PD10
#define HEADER_CONNECTOR_P1_D43 PD13
#define HEADER_CONNECTOR_P1_D44 PD12
#define HEADER_CONNECTOR_P1_D45 PD15
#define HEADER_CONNECTOR_P1_D46 PD14
#define HEADER_CONNECTOR_P1_D47 PC6
#define HEADER_CONNECTOR_P1_D48 PC7
#define HEADER_CONNECTOR_P1_D49 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P1_D50 // Pin not routed to mikroBUS

#define HEADER_CONNECTOR_P2_D1  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D2  // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D3  PF9
#define HEADER_CONNECTOR_P2_D4  PF10
#define HEADER_CONNECTOR_P2_D5  PF0
#define HEADER_CONNECTOR_P2_D6  PF1
#define HEADER_CONNECTOR_P2_D7  PC14
#define HEADER_CONNECTOR_P2_D8  PC15
#define HEADER_CONNECTOR_P2_D9  PE6
#define HEADER_CONNECTOR_P2_D10 PC13
#define HEADER_CONNECTOR_P2_D11 PE4
#define HEADER_CONNECTOR_P2_D12 PE5
#define HEADER_CONNECTOR_P2_D13 PE2
#define HEADER_CONNECTOR_P2_D14 PE3
#define HEADER_CONNECTOR_P2_D15 PE0
#define HEADER_CONNECTOR_P2_D16 PE1
#define HEADER_CONNECTOR_P2_D17 PB8
#define HEADER_CONNECTOR_P2_D18 PB9
#define HEADER_CONNECTOR_P2_D19 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D20 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D21 PB6
#define HEADER_CONNECTOR_P2_D22 PB7
#define HEADER_CONNECTOR_P2_D23 PB4
#define HEADER_CONNECTOR_P2_D24 PB5
#define HEADER_CONNECTOR_P2_D25 PD7
#define HEADER_CONNECTOR_P2_D26 PB3
#define HEADER_CONNECTOR_P2_D27 PD5
#define HEADER_CONNECTOR_P2_D28 PD6
#define HEADER_CONNECTOR_P2_D29 PD3
#define HEADER_CONNECTOR_P2_D30 PD4
#define HEADER_CONNECTOR_P2_D31 PD1
#define HEADER_CONNECTOR_P2_D32 PD2
#define HEADER_CONNECTOR_P2_D33 PC12
#define HEADER_CONNECTOR_P2_D34 PD0
#define HEADER_CONNECTOR_P2_D35 PC10
#define HEADER_CONNECTOR_P2_D36 PC11
#define HEADER_CONNECTOR_P2_D37 PA14
#define HEADER_CONNECTOR_P2_D38 PA15
#define HEADER_CONNECTOR_P2_D39 PF6
#define HEADER_CONNECTOR_P2_D40 PA13
#define HEADER_CONNECTOR_P2_D41 PA12
#define HEADER_CONNECTOR_P2_D42 PA11
#define HEADER_CONNECTOR_P2_D43 PA10
#define HEADER_CONNECTOR_P2_D44 PA9
#define HEADER_CONNECTOR_P2_D45 PA8
#define HEADER_CONNECTOR_P2_D46 PC9
#define HEADER_CONNECTOR_P2_D47 PC8
#define HEADER_CONNECTOR_P2_D48 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D49 // Pin not routed to mikroBUS
#define HEADER_CONNECTOR_P2_D50 // Pin not routed to mikroBUS

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
