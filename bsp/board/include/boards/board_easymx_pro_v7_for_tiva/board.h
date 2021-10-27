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

#define BOARD_NAME "EasyMX PRO v7 for TIVA"

#include "mcu_card.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN DOWN_CN_PIN_44
#define MIKROBUS_1_RST RIGHT_CN_PIN_67
#define MIKROBUS_1_CS LEFT_CN_PIN_16
#define MIKROBUS_1_SCK UP_CN_PIN_84
#define MIKROBUS_1_MISO UP_CN_PIN_86
#define MIKROBUS_1_MOSI UP_CN_PIN_85
#define MIKROBUS_1_PWM RIGHT_CN_PIN_56
#define MIKROBUS_1_INT UP_CN_PIN_93
#define MIKROBUS_1_RX RIGHT_CN_PIN_74
#define MIKROBUS_1_TX RIGHT_CN_PIN_73
#define MIKROBUS_1_SCL LEFT_CN_PIN_18
#define MIKROBUS_1_SDA LEFT_CN_PIN_17

#define MIKROBUS_2 2
#define MIKROBUS_2_AN DOWN_CN_PIN_45
#define MIKROBUS_2_RST RIGHT_CN_PIN_66
#define MIKROBUS_2_CS DOWN_CN_PIN_41
#define MIKROBUS_2_SCK UP_CN_PIN_84
#define MIKROBUS_2_MISO UP_CN_PIN_86
#define MIKROBUS_2_MOSI UP_CN_PIN_85
#define MIKROBUS_2_PWM RIGHT_CN_PIN_55
#define MIKROBUS_2_INT DOWN_CN_PIN_49
#define MIKROBUS_2_RX RIGHT_CN_PIN_76
#define MIKROBUS_2_TX RIGHT_CN_PIN_75
#define MIKROBUS_2_SCL LEFT_CN_PIN_18
#define MIKROBUS_2_SDA LEFT_CN_PIN_17

#define USB_UART_TX DOWN_CN_PIN_48
#define USB_UART_RX DOWN_CN_PIN_47
#define USB_UARTB_TX RIGHT_CN_PIN_75
#define USB_UARTB_RX RIGHT_CN_PIN_76

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
