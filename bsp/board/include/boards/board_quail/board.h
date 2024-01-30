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
#define BOARD_REV_MAJOR (2)
#define BOARD_REV_MINOR (03)

#define BOARD_NAME "Quail"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   PA6
#define MIKROBUS_1_RST  PA2
#define MIKROBUS_1_CS   PA3
#define MIKROBUS_1_SCK  PB3
#define MIKROBUS_1_MISO PB4
#define MIKROBUS_1_MOSI PB5
#define MIKROBUS_1_PWM  PE9
#define MIKROBUS_1_INT  PA1
#define MIKROBUS_1_RX   PD9
#define MIKROBUS_1_TX   PD8
#define MIKROBUS_1_SCL  PB6
#define MIKROBUS_1_SDA  PB7

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   PA4
#define MIKROBUS_2_RST  PE1
#define MIKROBUS_2_CS   PE0
#define MIKROBUS_2_SCK  PB3
#define MIKROBUS_2_MISO PB4
#define MIKROBUS_2_MOSI PB5
#define MIKROBUS_2_PWM  PD15
#define MIKROBUS_2_INT  PB9
#define MIKROBUS_2_RX   PD6
#define MIKROBUS_2_TX   PD5
#define MIKROBUS_2_SCL  PB6
#define MIKROBUS_2_SDA  PB7

#define MIKROBUS_3      3
#define MIKROBUS_3_AN   PA7
#define MIKROBUS_3_RST  PD12
#define MIKROBUS_3_CS   PD11
#define MIKROBUS_3_SCK  PC10
#define MIKROBUS_3_MISO PC11
#define MIKROBUS_3_MOSI PC12
#define MIKROBUS_3_PWM  PD13
#define MIKROBUS_3_INT  PC8
#define MIKROBUS_3_RX   PC7
#define MIKROBUS_3_TX   PC6
#define MIKROBUS_3_SCL  PB6
#define MIKROBUS_3_SDA  PB7

#define MIKROBUS_4      4
#define MIKROBUS_4_AN   PA5
#define MIKROBUS_4_RST  PD0
#define MIKROBUS_4_CS   PD1
#define MIKROBUS_4_SCK  PC10
#define MIKROBUS_4_MISO PC11
#define MIKROBUS_4_MOSI PC12
#define MIKROBUS_4_PWM  PD14
#define MIKROBUS_4_INT  PA14
#define MIKROBUS_4_RX   PA10
#define MIKROBUS_4_TX   PA9
#define MIKROBUS_4_SCL  PB6
#define MIKROBUS_4_SDA  PB7

// Buttons
#define BUTTON_1 HAL_PIN_NC
#define BUTTON_2 HAL_PIN_NC
#define BUTTON_3 HAL_PIN_NC
#define BUTTON_4 HAL_PIN_NC

// Headers
#define HEADER_J2_1 PC5
#define HEADER_J2_2 PB0
#define HEADER_J2_3 PE7
#define HEADER_J2_4 PE8

#define HEADER_J3_1 PE11
#define HEADER_J3_2 PC4
#define HEADER_J3_3 PE13
#define HEADER_J3_4 PE14

#define HEADER_J4_1 PB10
#define HEADER_J4_2 PB11
#define HEADER_J4_3 PB12
#define HEADER_J4_4 PB13

#define HEADER_J6_1 PE2
#define HEADER_J6_2 PE3
#define HEADER_J6_3 PE4

#define HEADER_J7_1 PD2
#define HEADER_J7_2 PD3
#define HEADER_J7_3 PD4
#define HEADER_J7_4 PD7

#define HEADER_J8_1 PA15
#define HEADER_J8_2 PC13
#define HEADER_J8_3 PE6
#define HEADER_J8_4 PE5

#define HEADER_J10_1 PC10
#define HEADER_J10_2 PC11
#define HEADER_J10_3 PC12
#define HEADER_J10_4 PD10

#define HEADER_J12_3 PB6
#define HEADER_J12_4 PB7

// LED's
#define LED_1 PE15
#define LED_2 PE10
#define LED_3 PC3

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
