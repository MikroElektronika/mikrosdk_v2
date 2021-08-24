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

#ifdef __cplusplus
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "EasyMX PRO v7 for STM32 ARM"

#include "mcu_card.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   UP_CN_PIN_84
#define MIKROBUS_1_RST  RIGHT_CN_PIN_72
#define MIKROBUS_1_CS   LEFT_CN_PIN_15
#define MIKROBUS_1_SCK  LEFT_CN_PIN_7
#define MIKROBUS_1_MISO LEFT_CN_PIN_10
#define MIKROBUS_1_MOSI LEFT_CN_PIN_9
#define MIKROBUS_1_PWM  RIGHT_CN_PIN_75
#define MIKROBUS_1_INT  LEFT_CN_PIN_14
#define MIKROBUS_1_RX   LEFT_CN_PIN_11
#define MIKROBUS_1_TX   LEFT_CN_PIN_12
#define MIKROBUS_1_SCL  RIGHT_CN_PIN_55
#define MIKROBUS_1_SDA  RIGHT_CN_PIN_58

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   UP_CN_PIN_83
#define MIKROBUS_2_RST  RIGHT_CN_PIN_73
#define MIKROBUS_2_CS   LEFT_CN_PIN_18
#define MIKROBUS_2_SCK  LEFT_CN_PIN_7
#define MIKROBUS_2_MISO LEFT_CN_PIN_10
#define MIKROBUS_2_MOSI LEFT_CN_PIN_9
#define MIKROBUS_2_PWM  LEFT_CN_PIN_16
#define MIKROBUS_2_INT  LEFT_CN_PIN_13
#define MIKROBUS_2_RX   DOWN_CN_PIN_48
#define MIKROBUS_2_TX   DOWN_CN_PIN_45
#define MIKROBUS_2_SCL  RIGHT_CN_PIN_55
#define MIKROBUS_2_SDA  RIGHT_CN_PIN_58

#define USB_UART_TX     DOWN_CN_PIN_30
#define USB_UART_RX     DOWN_CN_PIN_29
#define USB_UARTB_TX    DOWN_CN_PIN_45
#define USB_UARTB_RX    DOWN_CN_PIN_48

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
