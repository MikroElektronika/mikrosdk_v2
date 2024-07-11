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

#define BOARD_NAME "FlowPaw"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   PC0
#define MIKROBUS_1_RST  PA8
#define MIKROBUS_1_CS   PE7
#define MIKROBUS_1_SCK  PA5
#define MIKROBUS_1_MISO PA6
#define MIKROBUS_1_MOSI PA7
#define MIKROBUS_1_PWM  PE6
#define MIKROBUS_1_INT  PC13
#define MIKROBUS_1_RX   PA3
#define MIKROBUS_1_TX   PA2
#define MIKROBUS_1_SCL  PB10
#define MIKROBUS_1_SDA  PB11

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   PC1
#define MIKROBUS_2_RST  PA9
#define MIKROBUS_2_CS   PE8
#define MIKROBUS_2_SCK  PA5
#define MIKROBUS_2_MISO PA6
#define MIKROBUS_2_MOSI PA7
#define MIKROBUS_2_PWM  PB3
#define MIKROBUS_2_INT  PE4
#define MIKROBUS_2_RX   PA1
#define MIKROBUS_2_TX   PA0
#define MIKROBUS_2_SCL  PB10
#define MIKROBUS_2_SDA  PB11

#define MIKROBUS_3      3
#define MIKROBUS_3_AN   PC2
#define MIKROBUS_3_RST  PA10
#define MIKROBUS_3_CS   PD0
#define MIKROBUS_3_SCK  PC10
#define MIKROBUS_3_MISO PC11
#define MIKROBUS_3_MOSI PC12
#define MIKROBUS_3_PWM  PB9
#define MIKROBUS_3_INT  PE3
#define MIKROBUS_3_RX   PD9
#define MIKROBUS_3_TX   PD8
#define MIKROBUS_3_SCL  PB6
#define MIKROBUS_3_SDA  PB7

#define MIKROBUS_4      4
#define MIKROBUS_4_AN   PC3
#define MIKROBUS_4_RST  PA12
#define MIKROBUS_4_CS   PA15
#define MIKROBUS_4_SCK  PC10
#define MIKROBUS_4_MISO PC11
#define MIKROBUS_4_MOSI PC12
#define MIKROBUS_4_PWM  PB8
#define MIKROBUS_4_INT  PE2
#define MIKROBUS_4_RX   PC7
#define MIKROBUS_4_TX   PC6
#define MIKROBUS_4_SCL  PB6
#define MIKROBUS_4_SDA  PB7

// Headers
#define HEADER_A0 PB0
#define HEADER_A1 PC5
#define HEADER_A2 PC4
#define HEADER_A3 PA7

#define HEADER_D0 PE10
#define HEADER_D1 PE12
#define HEADER_D2 PE14
#define HEADER_D3 PE15

#define HEADER_SERVO_0 PA11
#define HEADER_SERVO_1 PC9
#define HEADER_SERVO_2 PC8
#define HEADER_SERVO_3 PD15
#define HEADER_SERVO_4 PD14
#define HEADER_SERVO_5 PD13
#define HEADER_SERVO_6 PD12
#define HEADER_SERVO_7 PE13

// Buttons
#define BUTTON_1 PD6
#define BUTTON_2 PD5
#define BUTTON_3 PD4
#define BUTTON_4 PD3

// LED's
#define LED_1 PE11
#define LED_2 PE5
#define LED_3 PB4
#define LED_4 PE9

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
