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
#define MIKROBUS_1_AN PA5
#define MIKROBUS_1_RST PJ4
#define MIKROBUS_1_CS PL1
#define MIKROBUS_1_SCK PD6
#define MIKROBUS_1_MISO PD5
#define MIKROBUS_1_MOSI PD4
#define MIKROBUS_1_PWM PG4
#define MIKROBUS_1_INT PB0
#define MIKROBUS_1_RX PE0
#define MIKROBUS_1_TX PE1
#define MIKROBUS_1_SCL PC3
#define MIKROBUS_1_SDA PC4

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PA2
#define MIKROBUS_2_RST PJ5
#define MIKROBUS_2_CS PL2
#define MIKROBUS_2_SCK PD6
#define MIKROBUS_2_MISO PD5
#define MIKROBUS_2_MOSI PD4
#define MIKROBUS_2_PWM PF6
#define MIKROBUS_2_INT PB5
#define MIKROBUS_2_RX PG2
#define MIKROBUS_2_TX PG1
#define MIKROBUS_2_SCL PC3
#define MIKROBUS_2_SDA PC4

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PA1
#define MIKROBUS_3_RST PJ6
#define MIKROBUS_3_CS PL3
#define MIKROBUS_3_SCK PD6
#define MIKROBUS_3_MISO PD5
#define MIKROBUS_3_MOSI PD4
#define MIKROBUS_3_PWM PF5
#define MIKROBUS_3_INT PB4
#define MIKROBUS_3_RX PG2
#define MIKROBUS_3_TX PG1
#define MIKROBUS_3_SCL PC3
#define MIKROBUS_3_SDA PC4

#define MIKROBUS_4 4
#define MIKROBUS_4_AN PA0
#define MIKROBUS_4_RST PJ7
#define MIKROBUS_4_CS PL4
#define MIKROBUS_4_SCK PD3
#define MIKROBUS_4_MISO PD0
#define MIKROBUS_4_MOSI PD1
#define MIKROBUS_4_PWM PF2
#define MIKROBUS_4_INT PB3
#define MIKROBUS_4_RX PC7
#define MIKROBUS_4_TX PC6
#define MIKROBUS_4_SCL PC3
#define MIKROBUS_4_SDA PC4

// Buttons
#define BUTTON_B1 PJ2
#define BUTTON_B2 PJ3
#define BUTTON_B3 PJ1
#define BUTTON_B4 PJ0
#define BUTTON_B5 PC0
#define BUTTON_B6 PD7

// LEDs
#define LED_L1 PL6
#define LED_L2 PL7
#define LED_L3 PK0
#define LED_L4 PK1
#define LED_L5 PK2
#define LED_L6 PK3

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
