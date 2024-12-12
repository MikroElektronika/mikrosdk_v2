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

#define BOARD_NAME "PICPLC16 v7"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PF0
#define MIKROBUS_1_RST GPIO_PG6
#define MIKROBUS_1_CS GPIO_PJ2
#define MIKROBUS_1_SCK GPIO_PD6
#define MIKROBUS_1_MISO GPIO_PD5
#define MIKROBUS_1_MOSI GPIO_PD4
#define MIKROBUS_1_PWM GPIO_PC1
#define MIKROBUS_1_INT GPIO_PB0
#define MIKROBUS_1_RX GPIO_PG2
#define MIKROBUS_1_TX GPIO_PG1
#define MIKROBUS_1_SCL GPIO_PC3
#define MIKROBUS_1_SDA GPIO_PC4

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PF1
#define MIKROBUS_2_RST GPIO_PG5
#define MIKROBUS_2_CS GPIO_PF7
#define MIKROBUS_2_SCK GPIO_PD6
#define MIKROBUS_2_MISO GPIO_PD5
#define MIKROBUS_2_MOSI GPIO_PD4
#define MIKROBUS_2_PWM GPIO_PC2
#define MIKROBUS_2_INT GPIO_PB1
#define MIKROBUS_2_RX GPIO_PG2
#define MIKROBUS_2_TX GPIO_PG1
#define MIKROBUS_2_SCL GPIO_PC3
#define MIKROBUS_2_SDA GPIO_PC4

#define MIKROBUS_3 3
#define MIKROBUS_3_AN GPIO_PF2
#define MIKROBUS_3_RST GPIO_PF6
#define MIKROBUS_3_CS GPIO_PG7
#define MIKROBUS_3_SCK GPIO_PD6
#define MIKROBUS_3_MISO GPIO_PD5
#define MIKROBUS_3_MOSI GPIO_PD4
#define MIKROBUS_3_PWM GPIO_PG3
#define MIKROBUS_3_INT GPIO_PB2
#define MIKROBUS_3_RX GPIO_PC7
#define MIKROBUS_3_TX GPIO_PC6
#define MIKROBUS_3_SCL GPIO_PC3
#define MIKROBUS_3_SDA GPIO_PC4

// Isolated inputs
#define OC_IN0 GPIO_PA2
#define OC_IN1 GPIO_PA4
#define OC_IN2 GPIO_PA5
#define OC_IN3 GPIO_PB3
#define OC_IN4 GPIO_PB4
#define OC_IN5 GPIO_PB5
#define OC_IN6 GPIO_PC0
#define OC_IN7 GPIO_PC5
#define OC_IN8 GPIO_PD0
#define OC_IN9 GPIO_PD2
#define OC_IN10 GPIO_PD3
#define OC_IN11 GPIO_PD7
#define OC_IN12 GPIO_PF3
#define OC_IN13 GPIO_PF4
#define OC_IN14 GPIO_PF5
#define OC_IN15 GPIO_PG0
// EOF Isolated inputs

// Relay control
#define RLY1 GPIO_PE0
#define RLY2 GPIO_PE1
#define RLY3 GPIO_PE2
#define RLY4 GPIO_PE3
#define RLY5 GPIO_PE4
#define RLY6 GPIO_PE5
#define RLY7 GPIO_PE6
#define RLY8 GPIO_PE7
#define RLY9 GPIO_PH0
#define RLY10 GPIO_PH1
#define RLY11 GPIO_PH2
#define RLY12 GPIO_PH3
#define RLY13 GPIO_PH4
#define RLY14 GPIO_PH5
#define RLY15 GPIO_PH6
#define RLY16 GPIO_PH7
// EOF Relay control

// Lin communication
#define LIN_TX GPIO_PG1
#define LIN_RX GPIO_PG2
#define LIN_CS GPIO_PJ0
#define LIN_WK GPIO_PJ1
// EOF Lin communication

// Buzzer
#define BUZZER GPIO_PG4
// EOF Buzzer

// No TFT connector on board
#define TFT_8BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
