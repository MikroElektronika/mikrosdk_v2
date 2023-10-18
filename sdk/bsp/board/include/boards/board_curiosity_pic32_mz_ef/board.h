/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

#define BOARD_NAME "Curiosity PIC32MZ EF Development Board"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PB4
#define MIKROBUS_1_RST PA9
#define MIKROBUS_1_CS PD4
#define MIKROBUS_1_SCK PD1
#define MIKROBUS_1_MISO PD14
#define MIKROBUS_1_MOSI PD3
#define MIKROBUS_1_PWM PE8
#define MIKROBUS_1_INT PF13
#define MIKROBUS_1_RX PD10
#define MIKROBUS_1_TX PD15
#define MIKROBUS_1_SCL PA14
#define MIKROBUS_1_SDA PA15

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PA1
#define MIKROBUS_2_RST PA5
#define MIKROBUS_2_CS PD5
#define MIKROBUS_2_SCK PG6
#define MIKROBUS_2_MISO PG0
#define MIKROBUS_2_MOSI PG7
#define MIKROBUS_2_PWM PF2
#define MIKROBUS_2_INT PF12
#define MIKROBUS_2_RX PC3
#define MIKROBUS_2_TX PC2
#define MIKROBUS_2_SCL PA2
#define MIKROBUS_2_SDA PA3

// LEDs
#define LED_1 PE3
#define LED_2 PE4
#define LED_3 PE6
#define LED_4 PB0
#define LED_5 PB1
#define LED_6 PB5

// Buttons
#define BUTTON_1 PG12

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
