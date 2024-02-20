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
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Clicker 4 for STM32"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PF3
#define MIKROBUS_1_RST PI9
#define MIKROBUS_1_CS PC3
#define MIKROBUS_1_SCK PI1
#define MIKROBUS_1_MISO PI2
#define MIKROBUS_1_MOSI PI3
#define MIKROBUS_1_PWM PF6
#define MIKROBUS_1_INT PA4
#define MIKROBUS_1_RX PD9
#define MIKROBUS_1_TX PD8
#define MIKROBUS_1_SCL PF1
#define MIKROBUS_1_SDA PF0

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PC0
#define MIKROBUS_2_RST PI10
#define MIKROBUS_2_CS PH2
#define MIKROBUS_2_SCK PI1
#define MIKROBUS_2_MISO PI2
#define MIKROBUS_2_MOSI PI3
#define MIKROBUS_2_PWM PF7
#define MIKROBUS_2_INT PF11
#define MIKROBUS_2_RX PB7
#define MIKROBUS_2_TX PB6
#define MIKROBUS_2_SCL PF1
#define MIKROBUS_2_SDA PF0

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PF5
#define MIKROBUS_3_RST PI11
#define MIKROBUS_3_CS PH3
#define MIKROBUS_3_SCK PC10
#define MIKROBUS_3_MISO PC11
#define MIKROBUS_3_MOSI PC12
#define MIKROBUS_3_PWM PF8
#define MIKROBUS_3_INT PB0
#define MIKROBUS_3_RX PC7
#define MIKROBUS_3_TX PC6
#define MIKROBUS_3_SCL PH7
#define MIKROBUS_3_SDA PH8

#define MIKROBUS_4 4
#define MIKROBUS_4_AN PF10
#define MIKROBUS_4_RST PF2
#define MIKROBUS_4_CS PH4
#define MIKROBUS_4_SCK PC10
#define MIKROBUS_4_MISO PC11
#define MIKROBUS_4_MOSI PC12
#define MIKROBUS_4_PWM PF9
#define MIKROBUS_4_INT PB1
#define MIKROBUS_4_RX PE7
#define MIKROBUS_4_TX PE8
#define MIKROBUS_4_SCL PH7
#define MIKROBUS_4_SDA PH8

// LEDs
#define LED_1 PG0
#define LED_2 PG1
#define LED_3 PG2
#define LED_4 PG3
#define LED_5 PG4
#define LED_6 PG5
#define LED_7 PG6
#define LED_8 PG7

// Buttons
#define BUTTON_1 PG8
#define BUTTON_2 PG9
#define BUTTON_3 PG10
#define BUTTON_4 PG11
#define BUTTON_5 PG12
#define BUTTON_6 PG13
#define BUTTON_7 PG14
#define BUTTON_8 PG15

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
