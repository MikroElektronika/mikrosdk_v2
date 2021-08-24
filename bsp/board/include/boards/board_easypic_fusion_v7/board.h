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
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "BOARD_EASYPIC_FUSION_V7"

#include "mcu_card.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   LEFT_CN_PIN_11
#define MIKROBUS_1_RST  UP_CN_PIN_86
#define MIKROBUS_1_CS   UP_CN_PIN_85
#define MIKROBUS_1_SCK  DOWN_CN_PIN_38
#define MIKROBUS_1_MISO DOWN_CN_PIN_37
#define MIKROBUS_1_MOSI DOWN_CN_PIN_40
#define MIKROBUS_1_PWM  DOWN_CN_PIN_49
#define MIKROBUS_1_INT  UP_CN_PIN_96
#define MIKROBUS_1_RX   LEFT_CN_PIN_23
#define MIKROBUS_1_TX   LEFT_CN_PIN_24
#define MIKROBUS_1_SCL  DOWN_CN_PIN_39
#define MIKROBUS_1_SDA  DOWN_CN_PIN_42

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   LEFT_CN_PIN_12
#define MIKROBUS_2_RST  UP_CN_PIN_88
#define MIKROBUS_2_CS   UP_CN_PIN_87
#define MIKROBUS_2_SCK  DOWN_CN_PIN_38
#define MIKROBUS_2_MISO DOWN_CN_PIN_37
#define MIKROBUS_2_MOSI DOWN_CN_PIN_40
#define MIKROBUS_2_PWM  RIGHT_CN_PIN_53
#define MIKROBUS_2_INT  UP_CN_PIN_95
#define MIKROBUS_2_RX   LEFT_CN_PIN_18
#define MIKROBUS_2_TX   LEFT_CN_PIN_15
#define MIKROBUS_2_SCL  DOWN_CN_PIN_39
#define MIKROBUS_2_SDA  DOWN_CN_PIN_42

#define USB_UART_TX     LEFT_CN_PIN_24
#define USB_UART_RX     LEFT_CN_PIN_23
#define USB_UARTB_TX    LEFT_CN_PIN_15
#define USB_UARTB_RX    LEFT_CN_PIN_18

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
