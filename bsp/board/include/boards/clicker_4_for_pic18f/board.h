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
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Clicker 4 for PIC18F"

#include "hal_target.h"
#include "mikrobus.h"

// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PA5
#define MIKROBUS_1_RST GPIO_PJ4
#define MIKROBUS_1_CS GPIO_PL1
#define MIKROBUS_1_SCK GPIO_PD6
#define MIKROBUS_1_MISO GPIO_PD5
#define MIKROBUS_1_MOSI GPIO_PD4
#define MIKROBUS_1_PWM GPIO_PG4
#define MIKROBUS_1_INT GPIO_PB0
#define MIKROBUS_1_RX GPIO_PE0
#define MIKROBUS_1_TX GPIO_PE1
#define MIKROBUS_1_SCL GPIO_PC3
#define MIKROBUS_1_SDA GPIO_PC4

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PA2
#define MIKROBUS_2_RST GPIO_PJ5
#define MIKROBUS_2_CS GPIO_PL2
#define MIKROBUS_2_SCK GPIO_PD6
#define MIKROBUS_2_MISO GPIO_PD5
#define MIKROBUS_2_MOSI GPIO_PD4
#define MIKROBUS_2_PWM GPIO_PF6
#define MIKROBUS_2_INT GPIO_PB5
#define MIKROBUS_2_RX GPIO_PG2
#define MIKROBUS_2_TX GPIO_PG1
#define MIKROBUS_2_SCL GPIO_PC3
#define MIKROBUS_2_SDA GPIO_PC4

#define MIKROBUS_3 3
#define MIKROBUS_3_AN GPIO_PA1
#define MIKROBUS_3_RST GPIO_PJ6
#define MIKROBUS_3_CS GPIO_PL3
#define MIKROBUS_3_SCK GPIO_PD6
#define MIKROBUS_3_MISO GPIO_PD5
#define MIKROBUS_3_MOSI GPIO_PD4
#define MIKROBUS_3_PWM GPIO_PF5
#define MIKROBUS_3_INT GPIO_PB4
#define MIKROBUS_3_RX GPIO_PG2
#define MIKROBUS_3_TX GPIO_PG1
#define MIKROBUS_3_SCL GPIO_PC3
#define MIKROBUS_3_SDA GPIO_PC4

#define MIKROBUS_4 4
#define MIKROBUS_4_AN GPIO_PA0
#define MIKROBUS_4_RST GPIO_PJ7
#define MIKROBUS_4_CS GPIO_PL4
#define MIKROBUS_4_SCK GPIO_PD3
#define MIKROBUS_4_MISO GPIO_PD0
#define MIKROBUS_4_MOSI GPIO_PD1
#define MIKROBUS_4_PWM GPIO_PF2
#define MIKROBUS_4_INT GPIO_PB3
#define MIKROBUS_4_RX GPIO_PC7
#define MIKROBUS_4_TX GPIO_PC6
#define MIKROBUS_4_SCL GPIO_PC3
#define MIKROBUS_4_SDA GPIO_PC4

// Buttons
#define BUTTON_B1 GPIO_PJ2
#define BUTTON_B2 GPIO_PJ3
#define BUTTON_B3 GPIO_PJ1
#define BUTTON_B4 GPIO_PJ0
#define BUTTON_B5 GPIO_PC0
#define BUTTON_B6 GPIO_PD7

// LEDs
#define LED_L1 GPIO_PL6
#define LED_L2 GPIO_PL7
#define LED_L3 GPIO_PK0
#define LED_L4 GPIO_PK1
#define LED_L5 GPIO_PK2
#define LED_L6 GPIO_PK3

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
