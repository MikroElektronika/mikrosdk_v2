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

#define BOARD_NAME "STM32L4R9AI Discovery Kit"

#include "mikrobus.h"

// Connectors
#define CN1_PIN1 PA6
#define CN1_PIN2 PB10
#define CN1_PIN3 PB11
#define CN1_PIN4 PB13
#define CN1_PIN7 PG7
#define CN1_PIN8 PI3
#define CN1_PIN9 PI2
#define CN1_PIN10 PG8
#define CN1_PIN11 PC6
#define CN1_PIN12 PI7
#define CN1_PIN13 PA4
#define CN1_PIN14 PA5
#define CN1_PIN17 PB12
#define CN1_PIN18 PC2
#define CN1_PIN19 PC7
#define CN1_PIN20 PC2

#define CN2_PIN4 PC6
#define CN2_PIN5 PC7
#define CN2_PIN6 PH11
#define CN2_PIN7 PH12
#define CN2_PIN8 PE4
#define CN2_PIN9 PI4
#define CN2_PIN10 PB8
#define CN2_PIN11 PI7
#define CN2_PIN15 PH5
#define CN2_PIN17 PA4
#define CN2_PIN19 PI5
#define CN2_PIN21 PA8
#define CN2_PIN27 PG13
#define CN2_PIN28 PB6

#define CN3_PIN1 PA6
#define CN3_PIN2 PB10
#define CN3_PIN3 PB11
#define CN3_PIN4 PB13

#define CN4_PIN22 PH14

#define CN5_PIN2 PA14

#define CN6_PIN1 PC10
#define CN6_PIN2 PC11
#define CN6_PIN3 PD2
#define CN6_PIN5 PC12
#define CN6_PIN7 PC8
#define CN6_PIN8 PC9

#define CN7_PIN1 PG13
#define CN7_PIN3 PB6

#define CN8_PIN2 PA13
#define CN8_PIN4 PA14

#define CN9_PIN1 PA9
#define CN9_PIN2 PA11
#define CN9_PIN3 PA12
#define CN9_PIN4 PA10

#define CN10_PIN1 PH15
#define CN10_PIN2 PH13
#define CN10_PIN3 PI0
#define CN10_PIN4 PB15
#define CN10_PIN5 PB14
#define CN10_PIN6 PB13
#define CN10_PIN9 PG8
#define CN10_PIN10 PG7

#define CN11_PIN1 PC0
#define CN11_PIN2 PC1
#define CN11_PIN3 PG11
#define CN11_PIN4 PF10
#define CN11_PIN5 PG6
#define CN11_PIN6 PA1
#define CN11_PIN7 PB4
#define CN11_PIN8 PA4

#define CN17_PIN1 PA7
#define CN17_PIN2 PC4
#define CN17_PIN3 PC3
#define CN17_PIN4 PB0
#define CN17_PIN5 PA0
#define CN17_PIN6 PA5

// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN CN1_PIN13
#define MIKROBUS_1_RST CN1_PIN12
#define MIKROBUS_1_CS CN1_PIN1
#define MIKROBUS_1_SCK CN1_PIN4
#define MIKROBUS_1_MISO CN1_PIN9
#define MIKROBUS_1_MOSI CN1_PIN8
#define MIKROBUS_1_PWM CN1_PIN14
#define MIKROBUS_1_INT CN1_PIN11
#define MIKROBUS_1_RX CN1_PIN3
#define MIKROBUS_1_TX CN1_PIN2
#define MIKROBUS_1_SCL CN1_PIN7
#define MIKROBUS_1_SDA CN1_PIN10

// LEDs
#define LD1 PB0
#define LD2 PH4
#define LD3 PB13
#define LD6 PA9
#define LD7 PB14
#define LED_1 LD1
#define LED_2 LD2
#define LED_3 LD3
#define LED_4 LD6
#define LED_5 LD7

// Buttons
#define B2_SELECT PC13
#define B2_UP PB1
#define B2_DOWN PB2
#define B2_RIGHT PB3
#define B2_LEFT PB4
#define BUTTON_1 B2_SELECT
#define BUTTON_2 B2_UP
#define BUTTON_3 B2_DOWN
#define BUTTON_4 B2_RIGHT
#define BUTTON_5 B2_LEFT

#define USB_UART_TX MIKROBUS_1_TX
#define USB_UART_RX MIKROBUS_1_RX

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
