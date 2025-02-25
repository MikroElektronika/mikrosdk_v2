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
** a written agreement between you and The mikroElektronika Company.
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
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Flip and Click PIC32MZ"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PB11
#define MIKROBUS_1_RST GPIO_PE2
#define MIKROBUS_1_CS GPIO_PA0
#define MIKROBUS_1_SCK GPIO_PG6
#define MIKROBUS_1_MISO GPIO_PC4
#define MIKROBUS_1_MOSI GPIO_PB5
#define MIKROBUS_1_PWM GPIO_PC14
#define MIKROBUS_1_INT GPIO_PD9
#define MIKROBUS_1_RX GPIO_PG9
#define MIKROBUS_1_TX GPIO_PE3
#define MIKROBUS_1_SCL GPIO_PA2
#define MIKROBUS_1_SDA GPIO_PA3

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PE7
#define MIKROBUS_2_RST GPIO_PG13
#define MIKROBUS_2_CS GPIO_PE4
#define MIKROBUS_2_SCK GPIO_PG6
#define MIKROBUS_2_MISO GPIO_PC4
#define MIKROBUS_2_MOSI GPIO_PB5
#define MIKROBUS_2_PWM GPIO_PG0
#define MIKROBUS_2_INT GPIO_PG1
#define MIKROBUS_2_RX GPIO_PF0
#define MIKROBUS_2_TX GPIO_PF1
#define MIKROBUS_2_SCL GPIO_PA2
#define MIKROBUS_2_SDA GPIO_PA3

#define MIKROBUS_3 3
#define MIKROBUS_3_AN GPIO_PA5
#define MIKROBUS_3_RST GPIO_PG14
#define MIKROBUS_3_CS GPIO_PD12
#define MIKROBUS_3_SCK GPIO_PD1
#define MIKROBUS_3_MISO GPIO_PD2
#define MIKROBUS_3_MOSI GPIO_PD3
#define MIKROBUS_3_PWM GPIO_PG7
#define MIKROBUS_3_INT GPIO_PD5
#define MIKROBUS_3_RX GPIO_PC1
#define MIKROBUS_3_TX GPIO_PE5
#define MIKROBUS_3_SCL GPIO_PA14
#define MIKROBUS_3_SDA GPIO_PA15

#define MIKROBUS_4 4
#define MIKROBUS_4_AN GPIO_PE6
#define MIKROBUS_4_RST GPIO_PG12
#define MIKROBUS_4_CS GPIO_PD13
#define MIKROBUS_4_SCK GPIO_PD1
#define MIKROBUS_4_MISO GPIO_PD2
#define MIKROBUS_4_MOSI GPIO_PD3
#define MIKROBUS_4_PWM GPIO_PG8
#define MIKROBUS_4_INT GPIO_PD4
#define MIKROBUS_4_RX GPIO_PC3
#define MIKROBUS_4_TX GPIO_PC2
#define MIKROBUS_4_SCL GPIO_PA14
#define MIKROBUS_4_SDA GPIO_PA15

#define USB_UART_TX GPIO_PD15
#define USB_UART_RX GPIO_PD14

// LEDs
#define LED_1 GPIO_PA6  // LEDA
#define LED_2 GPIO_PA7  // LEDB
#define LED_3 GPIO_PE0  // LEDC
#define LED_4 GPIO_PE1  // LEDD

// Buttons
#define BUTTON_1 GPIO_PD10
#define BUTTON_2 GPIO_PD11

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
