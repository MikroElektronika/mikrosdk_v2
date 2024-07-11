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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (3)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Arduino Mega 2560 Rev3"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_D0  PE0
#define HEADER_CONNECTOR_D1  PE1
#define HEADER_CONNECTOR_D2  PE4
#define HEADER_CONNECTOR_D3  PE5
#define HEADER_CONNECTOR_D4  PG5
#define HEADER_CONNECTOR_D5  PE3
#define HEADER_CONNECTOR_D6  PH3
#define HEADER_CONNECTOR_D7  PH4
#define HEADER_CONNECTOR_D8  PH5
#define HEADER_CONNECTOR_D9  PH6
#define HEADER_CONNECTOR_D10 PB4
#define HEADER_CONNECTOR_D11 PB5
#define HEADER_CONNECTOR_D12 PB6
#define HEADER_CONNECTOR_D13 PB7
#define HEADER_CONNECTOR_D14 PJ1
#define HEADER_CONNECTOR_D15 PJ0
#define HEADER_CONNECTOR_D16 PH1
#define HEADER_CONNECTOR_D17 PH0
#define HEADER_CONNECTOR_D18 PD3
#define HEADER_CONNECTOR_D19 PD2
#define HEADER_CONNECTOR_D20 PD1
#define HEADER_CONNECTOR_D21 PD0

#define HEADER_CONNECTOR_D22 PA0
#define HEADER_CONNECTOR_D23 PA1
#define HEADER_CONNECTOR_D24 PA2
#define HEADER_CONNECTOR_D25 PA3
#define HEADER_CONNECTOR_D26 PA4
#define HEADER_CONNECTOR_D27 PA5
#define HEADER_CONNECTOR_D28 PA6
#define HEADER_CONNECTOR_D29 PA7
#define HEADER_CONNECTOR_D30 PC7
#define HEADER_CONNECTOR_D31 PC6
#define HEADER_CONNECTOR_D32 PC5
#define HEADER_CONNECTOR_D33 PC4
#define HEADER_CONNECTOR_D34 PC3
#define HEADER_CONNECTOR_D35 PC2
#define HEADER_CONNECTOR_D36 PC1
#define HEADER_CONNECTOR_D37 PC0
#define HEADER_CONNECTOR_D38 PD7
#define HEADER_CONNECTOR_D39 PG2
#define HEADER_CONNECTOR_D40 PG1
#define HEADER_CONNECTOR_D41 PG0
#define HEADER_CONNECTOR_D42 PL7
#define HEADER_CONNECTOR_D43 PL6
#define HEADER_CONNECTOR_D44 PL5
#define HEADER_CONNECTOR_D45 PL4
#define HEADER_CONNECTOR_D46 PL3
#define HEADER_CONNECTOR_D47 PL2
#define HEADER_CONNECTOR_D48 PL1
#define HEADER_CONNECTOR_D49 PL0
#define HEADER_CONNECTOR_D50 PB3
#define HEADER_CONNECTOR_D51 PB2
#define HEADER_CONNECTOR_D52 PB1
#define HEADER_CONNECTOR_D53 PB0

#define HEADER_CONNECTOR_D54 PF0
#define HEADER_CONNECTOR_D55 PF1
#define HEADER_CONNECTOR_D56 PF2
#define HEADER_CONNECTOR_D57 PF3
#define HEADER_CONNECTOR_D58 PF4
#define HEADER_CONNECTOR_D59 PF5
#define HEADER_CONNECTOR_D60 PF6
#define HEADER_CONNECTOR_D61 PF7
#define HEADER_CONNECTOR_D62 PK0
#define HEADER_CONNECTOR_D63 PK1
#define HEADER_CONNECTOR_D64 PK2
#define HEADER_CONNECTOR_D65 PK3
#define HEADER_CONNECTOR_D66 PK4
#define HEADER_CONNECTOR_D67 PK5
#define HEADER_CONNECTOR_D68 PK6
#define HEADER_CONNECTOR_D69 PK7

// LEDs
#define TX_LED PD5
#define RX_LED PD4
#define LED_BUILTIN PB7

// UART
#define HEADER_CONNECTOR_TX0 PE1
#define HEADER_CONNECTOR_RX0 PE0

#define HEADER_CONNECTOR_TX1 PD3
#define HEADER_CONNECTOR_RX1 PD2

#define HEADER_CONNECTOR_TX2 PH1
#define HEADER_CONNECTOR_RX2 PH0

#define HEADER_CONNECTOR_TX3 PJ1
#define HEADER_CONNECTOR_RX3 PJ0

#define HEADER_CONNECTOR_SDA PD1
#define HEADER_CONNECTOR_SCL PD0

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
