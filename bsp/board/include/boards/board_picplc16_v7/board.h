/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (00)

#define BOARD_NAME "PICPLC16 v7"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PF0
#define MIKROBUS_1_RST PG6
#define MIKROBUS_1_CS PJ2
#define MIKROBUS_1_SCK PD6
#define MIKROBUS_1_MISO PD5
#define MIKROBUS_1_MOSI PD4
#define MIKROBUS_1_PWM PC1
#define MIKROBUS_1_INT PB0
#define MIKROBUS_1_RX PG2
#define MIKROBUS_1_TX PG1
#define MIKROBUS_1_SCL PC3
#define MIKROBUS_1_SDA PC4

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PF1
#define MIKROBUS_2_RST PG5
#define MIKROBUS_2_CS PF7
#define MIKROBUS_2_SCK PD6
#define MIKROBUS_2_MISO PD5
#define MIKROBUS_2_MOSI PD4
#define MIKROBUS_2_PWM PC2
#define MIKROBUS_2_INT PB1
#define MIKROBUS_2_RX PG2
#define MIKROBUS_2_TX PG1
#define MIKROBUS_2_SCL PC3
#define MIKROBUS_2_SDA PC4

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PF2
#define MIKROBUS_3_RST PF6
#define MIKROBUS_3_CS PG7
#define MIKROBUS_3_SCK PD6
#define MIKROBUS_3_MISO PD5
#define MIKROBUS_3_MOSI PD4
#define MIKROBUS_3_PWM PG3
#define MIKROBUS_3_INT PB2
#define MIKROBUS_3_RX PC7
#define MIKROBUS_3_TX PC6
#define MIKROBUS_3_SCL PC3
#define MIKROBUS_3_SDA PC4

// Isolated inputs
#define OC_IN0 PA2
#define OC_IN1 PA4
#define OC_IN2 PA5
#define OC_IN3 PB3
#define OC_IN4 PB4
#define OC_IN5 PB5
#define OC_IN6 PC0
#define OC_IN7 PC5
#define OC_IN8 PD0
#define OC_IN9 PD2
#define OC_IN10 PD3
#define OC_IN11 PD7
#define OC_IN12 PF3
#define OC_IN13 PF4
#define OC_IN14 PF5
#define OC_IN15 PG0
// EOF Isolated inputs

// Relay control
#define RLY1 PE0
#define RLY2 PE1
#define RLY3 PE2
#define RLY4 PE3
#define RLY5 PE4
#define RLY6 PE5
#define RLY7 PE6
#define RLY8 PE7
#define RLY9 PH0
#define RLY10 PH1
#define RLY11 PH2
#define RLY12 PH3
#define RLY13 PH4
#define RLY14 PH5
#define RLY15 PH6
#define RLY16 PH7
// EOF Relay control

// Lin communication
#define LIN_TX PG1
#define LIN_RX PG2
#define LIN_CS PJ0
#define LIN_WK PJ1
// EOF Lin communication

// Buzzer
#define BUZZER PG4
// EOF Buzzer

// No TFT connector on board
#define TFT_8BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
