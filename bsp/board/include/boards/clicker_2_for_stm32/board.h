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

#define BOARD_NAME "Clicker 2 for STM32"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PA2
#define MIKROBUS_1_RST GPIO_PE7
#define MIKROBUS_1_CS GPIO_PE8
#define MIKROBUS_1_SCK GPIO_PC10
#define MIKROBUS_1_MISO GPIO_PC11
#define MIKROBUS_1_MOSI GPIO_PC12
#define MIKROBUS_1_PWM GPIO_PE9
#define MIKROBUS_1_INT GPIO_PE10
#define MIKROBUS_1_RX GPIO_PD6
#define MIKROBUS_1_TX GPIO_PD5
#define MIKROBUS_1_SCL GPIO_PA8
#define MIKROBUS_1_SDA GPIO_PC9

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PA3
#define MIKROBUS_2_RST GPIO_PE13
#define MIKROBUS_2_CS GPIO_PE11
#define MIKROBUS_2_SCK GPIO_PB13
#define MIKROBUS_2_MISO GPIO_PB14
#define MIKROBUS_2_MOSI GPIO_PB15
#define MIKROBUS_2_PWM GPIO_PD12
#define MIKROBUS_2_INT GPIO_PE14
#define MIKROBUS_2_RX GPIO_PD9
#define MIKROBUS_2_TX GPIO_PD8
#define MIKROBUS_2_SCL GPIO_PB10
#define MIKROBUS_2_SDA GPIO_PB11

// LEDs
#define LED_1 GPIO_PE12
#define LED_2 GPIO_PE15

// Buttons
#define BUTTON_1 GPIO_PE0
#define BUTTON_2 GPIO_PA10

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
