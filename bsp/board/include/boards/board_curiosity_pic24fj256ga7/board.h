/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (00)

#define BOARD_NAME "PIC24FJ256GA7 Curiosity Development Board"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PC1
#define MIKROBUS_1_RST PA13
#define MIKROBUS_1_CS PC9
#define MIKROBUS_1_SCK PB15
#define MIKROBUS_1_MISO PB13
#define MIKROBUS_1_MOSI PB14
#define MIKROBUS_1_PWM PC3
#define MIKROBUS_1_INT PC8
#define MIKROBUS_1_RX PB1
#define MIKROBUS_1_TX PB0
#define MIKROBUS_1_SCL PB3
#define MIKROBUS_1_SDA PB2

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PC0
#define MIKROBUS_2_RST PA14
#define MIKROBUS_2_CS PA10
#define MIKROBUS_2_SCK PC6
#define MIKROBUS_2_MISO PB9
#define MIKROBUS_2_MOSI PC2
#define MIKROBUS_2_PWM PC4
#define MIKROBUS_2_INT PC5
#define MIKROBUS_2_RX PB8
#define MIKROBUS_2_TX PB7
#define MIKROBUS_2_SCL PB6
#define MIKROBUS_2_SDA PB5

// LEDs
#define LED_1 PA8
#define LED_2 PA9
#define LED_3 PA0
#define LED_4 PA1
#define LED_5 PC7

// Buttons
#define BUTTON_1 PA11
#define BUTTON_2 PA12

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
