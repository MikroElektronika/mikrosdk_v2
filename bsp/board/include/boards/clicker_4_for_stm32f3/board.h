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
#define BOARD_REV_MINOR (00)

#define BOARD_NAME "Clicker 4 for STM32F3"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PF4
#define MIKROBUS_1_RST PF10
#define MIKROBUS_1_CS PA4
#define MIKROBUS_1_SCK PA5
#define MIKROBUS_1_MISO PA6
#define MIKROBUS_1_MOSI PA7
#define MIKROBUS_1_PWM PE9
#define MIKROBUS_1_INT PD0
#define MIKROBUS_1_RX PA3
#define MIKROBUS_1_TX PA2
#define MIKROBUS_1_SCL PA9
#define MIKROBUS_1_SDA PA10

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PC4
#define MIKROBUS_2_RST PB1
#define MIKROBUS_2_CS PE8
#define MIKROBUS_2_SCK PA5
#define MIKROBUS_2_MISO PA6
#define MIKROBUS_2_MOSI PA7
#define MIKROBUS_2_PWM PD12
#define MIKROBUS_2_INT PB0
#define MIKROBUS_2_RX PB7
#define MIKROBUS_2_TX PB6
#define MIKROBUS_2_SCL PA9
#define MIKROBUS_2_SDA PA10

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PC5
#define MIKROBUS_3_RST PD11
#define MIKROBUS_3_CS PD13
#define MIKROBUS_3_SCK PA5
#define MIKROBUS_3_MISO PA6
#define MIKROBUS_3_MOSI PA7
#define MIKROBUS_3_PWM PC6
#define MIKROBUS_3_INT PC7
#define MIKROBUS_3_RX PB7
#define MIKROBUS_3_TX PB6
#define MIKROBUS_3_SCL PA9
#define MIKROBUS_3_SDA PA10

#define MIKROBUS_4 4
#define MIKROBUS_4_AN PB2
#define MIKROBUS_4_RST PD14
#define MIKROBUS_4_CS PD15
#define MIKROBUS_4_SCK PC10
#define MIKROBUS_4_MISO PC11
#define MIKROBUS_4_MOSI PC12
#define MIKROBUS_4_PWM PC9
#define MIKROBUS_4_INT PB14
#define MIKROBUS_4_RX PD9
#define MIKROBUS_4_TX PD8
#define MIKROBUS_4_SCL PA9
#define MIKROBUS_4_SDA PA10

// LEDs
#define LED_1 PC8
#define LED_2 PA8
#define LED_3 PB13
#define LED_4 PE6
#define LED_5 PB15
#define LED_6 PE15

// Buttons
#define BUTTON_1 PE7
#define BUTTON_2 PE10
#define BUTTON_3 PE11
#define BUTTON_4 PE12
#define BUTTON_5 PB12
#define BUTTON_6 PD10

// Header
#define HEADER_CONNECTOR_HDR1   PD0
#define HEADER_CONNECTOR_HDR1   PE1
#define HEADER_CONNECTOR_HDR1   PE4
#define HEADER_CONNECTOR_HDR1   PE5
#define HEADER_CONNECTOR_HDR1   PB5
#define HEADER_CONNECTOR_HDR1   PB9
#define HEADER_CONNECTOR_HDR1   PE2
#define HEADER_CONNECTOR_HDR1   PE3
#define HEADER_CONNECTOR_HDR1   PA3
#define HEADER_CONNECTOR_HDR1   PA2
#define HEADER_CONNECTOR_HDR1   PB7
#define HEADER_CONNECTOR_HDR1   PB6
#define HEADER_CONNECTOR_HDR1   PA9
#define HEADER_CONNECTOR_HDR1   PA10
#define HEADER_CONNECTOR_HDR1   PE13
#define HEADER_CONNECTOR_HDR1   PE14
#define HEADER_CONNECTOR_HDR1   PB4
#define HEADER_CONNECTOR_HDR1   PC10
#define HEADER_CONNECTOR_HDR1   PC11
#define HEADER_CONNECTOR_HDR1   PC12

#define HEADER_CONNECTOR_HDR2   PD1
#define HEADER_CONNECTOR_HDR2   PB6
#define HEADER_CONNECTOR_HDR2   PE0
#define HEADER_CONNECTOR_HDR2   PD2
#define HEADER_CONNECTOR_HDR2   PD3
#define HEADER_CONNECTOR_HDR2   PD4
#define HEADER_CONNECTOR_HDR2   PD5
#define HEADER_CONNECTOR_HDR2   PD6
#define HEADER_CONNECTOR_HDR2   PD7
#define HEADER_CONNECTOR_HDR2   PC0
#define HEADER_CONNECTOR_HDR2   PC1
#define HEADER_CONNECTOR_HDR2   PC2
#define HEADER_CONNECTOR_HDR2   PC3
#define HEADER_CONNECTOR_HDR2   PF2
#define HEADER_CONNECTOR_HDR2   // Pin not routed
#define HEADER_CONNECTOR_HDR2   // Pin not routed
#define HEADER_CONNECTOR_HDR2   // Pin not routed
#define HEADER_CONNECTOR_HDR2   // Pin not routed
#define HEADER_CONNECTOR_HDR2   // Pin not routed
#define HEADER_CONNECTOR_HDR2   // Pin not routed

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
