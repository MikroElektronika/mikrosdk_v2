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
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Flip and Click PIC32MZ"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PB11
#define MIKROBUS_1_RST PE2
#define MIKROBUS_1_CS PA0
#define MIKROBUS_1_SCK PG6
#define MIKROBUS_1_MISO PC4
#define MIKROBUS_1_MOSI PB5
#define MIKROBUS_1_PWM PC14
#define MIKROBUS_1_INT PD9
#define MIKROBUS_1_RX PG9
#define MIKROBUS_1_TX PE3
#define MIKROBUS_1_SCL PA2
#define MIKROBUS_1_SDA PA3

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PE7
#define MIKROBUS_2_RST PG13
#define MIKROBUS_2_CS PE4
#define MIKROBUS_2_SCK PG6
#define MIKROBUS_2_MISO PC4
#define MIKROBUS_2_MOSI PB5
#define MIKROBUS_2_PWM PG0
#define MIKROBUS_2_INT PG1
#define MIKROBUS_2_RX PF0
#define MIKROBUS_2_TX PF1
#define MIKROBUS_2_SCL PA2
#define MIKROBUS_2_SDA PA3

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PA5
#define MIKROBUS_3_RST PG14
#define MIKROBUS_3_CS PD12
#define MIKROBUS_3_SCK PD1
#define MIKROBUS_3_MISO PD2
#define MIKROBUS_3_MOSI PD3
#define MIKROBUS_3_PWM PG7
#define MIKROBUS_3_INT PD5
#define MIKROBUS_3_RX PC1
#define MIKROBUS_3_TX PE5
#define MIKROBUS_3_SCL PA14
#define MIKROBUS_3_SDA PA15

#define MIKROBUS_4 4
#define MIKROBUS_4_AN PE6
#define MIKROBUS_4_RST PG12
#define MIKROBUS_4_CS PD13
#define MIKROBUS_4_SCK PD1
#define MIKROBUS_4_MISO PD2
#define MIKROBUS_4_MOSI PD3
#define MIKROBUS_4_PWM PG8
#define MIKROBUS_4_INT PD4
#define MIKROBUS_4_RX PC3
#define MIKROBUS_4_TX PC2
#define MIKROBUS_4_SCL PA14
#define MIKROBUS_4_SDA PA15

#define USB_UART_TX PD15
#define USB_UART_RX PD14

// LEDs
#define LED_1 PA6  // LEDA
#define LED_2 PA7  // LEDB
#define LED_3 PE0  // LEDC
#define LED_4 PE1  // LEDD

// Buttons
#define BUTTON_1 PD10
#define BUTTON_2 PD11

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
