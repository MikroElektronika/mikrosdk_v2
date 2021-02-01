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
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Clicker 2 for STM32"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PA2
#define MIKROBUS_1_RST PE7
#define MIKROBUS_1_CS PE8
#define MIKROBUS_1_SCK PC10
#define MIKROBUS_1_MISO PC11
#define MIKROBUS_1_MOSI PC12
#define MIKROBUS_1_PWM PE9
#define MIKROBUS_1_INT PE10
#define MIKROBUS_1_RX PD6
#define MIKROBUS_1_TX PD5
#define MIKROBUS_1_SCL PA8
#define MIKROBUS_1_SDA PC9

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PA3
#define MIKROBUS_2_RST PE13
#define MIKROBUS_2_CS PE11
#define MIKROBUS_2_SCK PB13
#define MIKROBUS_2_MISO PB14
#define MIKROBUS_2_MOSI PB15
#define MIKROBUS_2_PWM PD12
#define MIKROBUS_2_INT PE14
#define MIKROBUS_2_RX PD9
#define MIKROBUS_2_TX PD8
#define MIKROBUS_2_SCL PB10
#define MIKROBUS_2_SDA PB11

#define USB_UART_TX MIKROBUS_1_TX
#define USB_UART_RX MIKROBUS_1_RX

// LEDs
#define LD1 PE12
#define LD2 PE15

// Buttons
#define B1 PE0
#define B2 PA10

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
