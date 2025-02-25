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
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Clicker 4 for STM32"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PF3
#define MIKROBUS_1_RST GPIO_PI9
#define MIKROBUS_1_CS GPIO_PC3
#define MIKROBUS_1_SCK GPIO_PI1
#define MIKROBUS_1_MISO GPIO_PI2
#define MIKROBUS_1_MOSI GPIO_PI3
#define MIKROBUS_1_PWM GPIO_PF6
#define MIKROBUS_1_INT GPIO_PA4
#define MIKROBUS_1_RX GPIO_PD9
#define MIKROBUS_1_TX GPIO_PD8
#define MIKROBUS_1_SCL GPIO_PF1
#define MIKROBUS_1_SDA GPIO_PF0

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PC0
#define MIKROBUS_2_RST GPIO_PI10
#define MIKROBUS_2_CS GPIO_PH2
#define MIKROBUS_2_SCK GPIO_PI1
#define MIKROBUS_2_MISO GPIO_PI2
#define MIKROBUS_2_MOSI GPIO_PI3
#define MIKROBUS_2_PWM GPIO_PF7
#define MIKROBUS_2_INT GPIO_PF11
#define MIKROBUS_2_RX GPIO_PB7
#define MIKROBUS_2_TX GPIO_PB6
#define MIKROBUS_2_SCL GPIO_PF1
#define MIKROBUS_2_SDA GPIO_PF0

#define MIKROBUS_3 3
#define MIKROBUS_3_AN GPIO_PF5
#define MIKROBUS_3_RST GPIO_PI11
#define MIKROBUS_3_CS GPIO_PH3
#define MIKROBUS_3_SCK GPIO_PC10
#define MIKROBUS_3_MISO GPIO_PC11
#define MIKROBUS_3_MOSI GPIO_PC12
#define MIKROBUS_3_PWM GPIO_PF8
#define MIKROBUS_3_INT GPIO_PB0
#define MIKROBUS_3_RX GPIO_PC7
#define MIKROBUS_3_TX GPIO_PC6
#define MIKROBUS_3_SCL GPIO_PH7
#define MIKROBUS_3_SDA GPIO_PH8

#define MIKROBUS_4 4
#define MIKROBUS_4_AN GPIO_PF10
#define MIKROBUS_4_RST GPIO_PF2
#define MIKROBUS_4_CS GPIO_PH4
#define MIKROBUS_4_SCK GPIO_PC10
#define MIKROBUS_4_MISO GPIO_PC11
#define MIKROBUS_4_MOSI GPIO_PC12
#define MIKROBUS_4_PWM GPIO_PF9
#define MIKROBUS_4_INT GPIO_PB1
#define MIKROBUS_4_RX GPIO_PE7
#define MIKROBUS_4_TX GPIO_PE8
#define MIKROBUS_4_SCL GPIO_PH7
#define MIKROBUS_4_SDA GPIO_PH8

// LEDs
#define LED_1 GPIO_PG0
#define LED_2 GPIO_PG1
#define LED_3 GPIO_PG2
#define LED_4 GPIO_PG3
#define LED_5 GPIO_PG4
#define LED_6 GPIO_PG5
#define LED_7 GPIO_PG6
#define LED_8 GPIO_PG7

// Buttons
#define BUTTON_1 GPIO_PG8
#define BUTTON_2 GPIO_PG9
#define BUTTON_3 GPIO_PG10
#define BUTTON_4 GPIO_PG11
#define BUTTON_5 GPIO_PG12
#define BUTTON_6 GPIO_PG13
#define BUTTON_7 GPIO_PG14
#define BUTTON_8 GPIO_PG15

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
