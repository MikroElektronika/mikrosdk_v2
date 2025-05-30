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

#define BOARD_NAME "FlowPaw"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_PC0
#define MIKROBUS_1_RST  GPIO_PA8
#define MIKROBUS_1_CS   GPIO_PE7
#define MIKROBUS_1_SCK  GPIO_PA5
#define MIKROBUS_1_MISO GPIO_PA6
#define MIKROBUS_1_MOSI GPIO_PA7
#define MIKROBUS_1_PWM  GPIO_PE6
#define MIKROBUS_1_INT  GPIO_PC13
#define MIKROBUS_1_RX   GPIO_PA3
#define MIKROBUS_1_TX   GPIO_PA2
#define MIKROBUS_1_SCL  GPIO_PB10
#define MIKROBUS_1_SDA  GPIO_PB11

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   GPIO_PC1
#define MIKROBUS_2_RST  GPIO_PA9
#define MIKROBUS_2_CS   GPIO_PE8
#define MIKROBUS_2_SCK  GPIO_PA5
#define MIKROBUS_2_MISO GPIO_PA6
#define MIKROBUS_2_MOSI GPIO_PA7
#define MIKROBUS_2_PWM  GPIO_PB3
#define MIKROBUS_2_INT  GPIO_PE4
#define MIKROBUS_2_RX   GPIO_PA1
#define MIKROBUS_2_TX   GPIO_PA0
#define MIKROBUS_2_SCL  GPIO_PB10
#define MIKROBUS_2_SDA  GPIO_PB11

#define MIKROBUS_3      3
#define MIKROBUS_3_AN   GPIO_PC2
#define MIKROBUS_3_RST  GPIO_PA10
#define MIKROBUS_3_CS   GPIO_PD0
#define MIKROBUS_3_SCK  GPIO_PC10
#define MIKROBUS_3_MISO GPIO_PC11
#define MIKROBUS_3_MOSI GPIO_PC12
#define MIKROBUS_3_PWM  GPIO_PB9
#define MIKROBUS_3_INT  GPIO_PE3
#define MIKROBUS_3_RX   GPIO_PD9
#define MIKROBUS_3_TX   GPIO_PD8
#define MIKROBUS_3_SCL  GPIO_PB6
#define MIKROBUS_3_SDA  GPIO_PB7

#define MIKROBUS_4      4
#define MIKROBUS_4_AN   GPIO_PC3
#define MIKROBUS_4_RST  GPIO_PA12
#define MIKROBUS_4_CS   GPIO_PA15
#define MIKROBUS_4_SCK  GPIO_PC10
#define MIKROBUS_4_MISO GPIO_PC11
#define MIKROBUS_4_MOSI GPIO_PC12
#define MIKROBUS_4_PWM  GPIO_PB8
#define MIKROBUS_4_INT  GPIO_PE2
#define MIKROBUS_4_RX   GPIO_PC7
#define MIKROBUS_4_TX   GPIO_PC6
#define MIKROBUS_4_SCL  GPIO_PB6
#define MIKROBUS_4_SDA  GPIO_PB7

// Headers
#define HEADER_A0 GPIO_PB0
#define HEADER_A1 GPIO_PC5
#define HEADER_A2 GPIO_PC4
#define HEADER_A3 GPIO_PA7

#define HEADER_D0 GPIO_PE10
#define HEADER_D1 GPIO_PE12
#define HEADER_D2 GPIO_PE14
#define HEADER_D3 GPIO_PE15

#define HEADER_SERVO_0 GPIO_PA11
#define HEADER_SERVO_1 GPIO_PC9
#define HEADER_SERVO_2 GPIO_PC8
#define HEADER_SERVO_3 GPIO_PD15
#define HEADER_SERVO_4 GPIO_PD14
#define HEADER_SERVO_5 GPIO_PD13
#define HEADER_SERVO_6 GPIO_PD12
#define HEADER_SERVO_7 GPIO_PE13

// Buttons
#define BUTTON_1 GPIO_PD6
#define BUTTON_2 GPIO_PD5
#define BUTTON_3 GPIO_PD4
#define BUTTON_4 GPIO_PD3

// LED's
#define LED_1 GPIO_PE11
#define LED_2 GPIO_PE5
#define LED_3 GPIO_PB4
#define LED_4 GPIO_PE9

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
