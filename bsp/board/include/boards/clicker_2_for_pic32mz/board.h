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

#define BOARD_NAME "Clicker 2 for PIC32MZ"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PB4
#define MIKROBUS_1_RST PB3
#define MIKROBUS_1_CS PC2
#define MIKROBUS_1_SCK PG6
#define MIKROBUS_1_MISO PC4
#define MIKROBUS_1_MOSI PC1
#define MIKROBUS_1_PWM PB2
#define MIKROBUS_1_INT PB1
#define MIKROBUS_1_RX PE9
#define MIKROBUS_1_TX PE8
#define MIKROBUS_1_SCL PG8
#define MIKROBUS_1_SDA PG7

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PB13
#define MIKROBUS_2_RST PA10
#define MIKROBUS_2_CS PD9
#define MIKROBUS_2_SCK PD10
#define MIKROBUS_2_MISO PD11
#define MIKROBUS_2_MOSI PA15
#define MIKROBUS_2_PWM PB14
#define MIKROBUS_2_INT PB15
#define MIKROBUS_2_RX PF5
#define MIKROBUS_2_TX PA14
#define MIKROBUS_2_SCL PA2
#define MIKROBUS_2_SDA PA3

// LEDs
#define LED_1 PE7
#define LED_2 PA9

// Buttons
#define BUTTON_1 PC3
#define BUTTON_2 PB0

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
