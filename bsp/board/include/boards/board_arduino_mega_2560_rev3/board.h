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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (3)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Arduino Mega 2560 Rev3"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_D0  GPIO_PE0
#define HEADER_CONNECTOR_D1  GPIO_PE1
#define HEADER_CONNECTOR_D2  GPIO_PE4
#define HEADER_CONNECTOR_D3  GPIO_PE5
#define HEADER_CONNECTOR_D4  GPIO_PG5
#define HEADER_CONNECTOR_D5  GPIO_PE3
#define HEADER_CONNECTOR_D6  GPIO_PH3
#define HEADER_CONNECTOR_D7  GPIO_PH4
#define HEADER_CONNECTOR_D8  GPIO_PH5
#define HEADER_CONNECTOR_D9  GPIO_PH6
#define HEADER_CONNECTOR_D10 GPIO_PB4
#define HEADER_CONNECTOR_D11 GPIO_PB5
#define HEADER_CONNECTOR_D12 GPIO_PB6
#define HEADER_CONNECTOR_D13 GPIO_PB7
#define HEADER_CONNECTOR_D14 GPIO_PJ1
#define HEADER_CONNECTOR_D15 GPIO_PJ0
#define HEADER_CONNECTOR_D16 GPIO_PH1
#define HEADER_CONNECTOR_D17 GPIO_PH0
#define HEADER_CONNECTOR_D18 GPIO_PD3
#define HEADER_CONNECTOR_D19 GPIO_PD2
#define HEADER_CONNECTOR_D20 GPIO_PD1
#define HEADER_CONNECTOR_D21 GPIO_PD0

#define HEADER_CONNECTOR_D22 GPIO_PA0
#define HEADER_CONNECTOR_D23 GPIO_PA1
#define HEADER_CONNECTOR_D24 GPIO_PA2
#define HEADER_CONNECTOR_D25 GPIO_PA3
#define HEADER_CONNECTOR_D26 GPIO_PA4
#define HEADER_CONNECTOR_D27 GPIO_PA5
#define HEADER_CONNECTOR_D28 GPIO_PA6
#define HEADER_CONNECTOR_D29 GPIO_PA7
#define HEADER_CONNECTOR_D30 GPIO_PC7
#define HEADER_CONNECTOR_D31 GPIO_PC6
#define HEADER_CONNECTOR_D32 GPIO_PC5
#define HEADER_CONNECTOR_D33 GPIO_PC4
#define HEADER_CONNECTOR_D34 GPIO_PC3
#define HEADER_CONNECTOR_D35 GPIO_PC2
#define HEADER_CONNECTOR_D36 GPIO_PC1
#define HEADER_CONNECTOR_D37 GPIO_PC0
#define HEADER_CONNECTOR_D38 GPIO_PD7
#define HEADER_CONNECTOR_D39 GPIO_PG2
#define HEADER_CONNECTOR_D40 GPIO_PG1
#define HEADER_CONNECTOR_D41 GPIO_PG0
#define HEADER_CONNECTOR_D42 GPIO_PL7
#define HEADER_CONNECTOR_D43 GPIO_PL6
#define HEADER_CONNECTOR_D44 GPIO_PL5
#define HEADER_CONNECTOR_D45 GPIO_PL4
#define HEADER_CONNECTOR_D46 GPIO_PL3
#define HEADER_CONNECTOR_D47 GPIO_PL2
#define HEADER_CONNECTOR_D48 GPIO_PL1
#define HEADER_CONNECTOR_D49 GPIO_PL0
#define HEADER_CONNECTOR_D50 GPIO_PB3
#define HEADER_CONNECTOR_D51 GPIO_PB2
#define HEADER_CONNECTOR_D52 GPIO_PB1
#define HEADER_CONNECTOR_D53 GPIO_PB0

#define HEADER_CONNECTOR_D54 GPIO_PF0
#define HEADER_CONNECTOR_D55 GPIO_PF1
#define HEADER_CONNECTOR_D56 GPIO_PF2
#define HEADER_CONNECTOR_D57 GPIO_PF3
#define HEADER_CONNECTOR_D58 GPIO_PF4
#define HEADER_CONNECTOR_D59 GPIO_PF5
#define HEADER_CONNECTOR_D60 GPIO_PF6
#define HEADER_CONNECTOR_D61 GPIO_PF7
#define HEADER_CONNECTOR_D62 GPIO_PK0
#define HEADER_CONNECTOR_D63 GPIO_PK1
#define HEADER_CONNECTOR_D64 GPIO_PK2
#define HEADER_CONNECTOR_D65 GPIO_PK3
#define HEADER_CONNECTOR_D66 GPIO_PK4
#define HEADER_CONNECTOR_D67 GPIO_PK5
#define HEADER_CONNECTOR_D68 GPIO_PK6
#define HEADER_CONNECTOR_D69 GPIO_PK7

// LEDs
#define TX_LED GPIO_PD5
#define RX_LED GPIO_PD4
#define LED_BUILTIN GPIO_PB7

// UART
#define HEADER_CONNECTOR_TX0 GPIO_PE1
#define HEADER_CONNECTOR_RX0 GPIO_PE0

#define HEADER_CONNECTOR_TX1 GPIO_PD3
#define HEADER_CONNECTOR_RX1 GPIO_PD2

#define HEADER_CONNECTOR_TX2 GPIO_PH1
#define HEADER_CONNECTOR_RX2 GPIO_PH0

#define HEADER_CONNECTOR_TX3 GPIO_PJ1
#define HEADER_CONNECTOR_RX3 GPIO_PJ0

#define HEADER_CONNECTOR_SDA GPIO_PD1
#define HEADER_CONNECTOR_SCL GPIO_PD0

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
