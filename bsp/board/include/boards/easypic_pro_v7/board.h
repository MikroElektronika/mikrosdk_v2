/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
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
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Easy PIC PRO v7"

#include "mcu_card.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   RIGHT_CN_PIN_65
#define MIKROBUS_1_RST  RIGHT_CN_PIN_71
#define MIKROBUS_1_CS   DOWN_CN_PIN_31
#define MIKROBUS_1_SCK  UP_CN_PIN_88
#define MIKROBUS_1_MISO UP_CN_PIN_89
#define MIKROBUS_1_MOSI UP_CN_PIN_90
#define MIKROBUS_1_PWM  RIGHT_CN_PIN_72
#define MIKROBUS_1_INT  UP_CN_PIN_98
#define MIKROBUS_1_RX   RIGHT_CN_PIN_73
#define MIKROBUS_1_TX   RIGHT_CN_PIN_74
#define MIKROBUS_1_SCL  UP_CN_PIN_88
#define MIKROBUS_1_SDA  UP_CN_PIN_89

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   RIGHT_CN_PIN_66
#define MIKROBUS_2_RST  RIGHT_CN_PIN_69
#define MIKROBUS_2_CS   DOWN_CN_PIN_32
#define MIKROBUS_2_SCK  UP_CN_PIN_88
#define MIKROBUS_2_MISO UP_CN_PIN_89
#define MIKROBUS_2_MOSI UP_CN_PIN_90
#define MIKROBUS_2_PWM  UP_CN_PIN_87
#define MIKROBUS_2_INT  UP_CN_PIN_97
#define MIKROBUS_2_RX   RIGHT_CN_PIN_73
#define MIKROBUS_2_TX   RIGHT_CN_PIN_74
#define MIKROBUS_2_SCL  UP_CN_PIN_88
#define MIKROBUS_2_SDA  UP_CN_PIN_89

#define MIKROBUS_3      3
#define MIKROBUS_3_AN   RIGHT_CN_PIN_63
#define MIKROBUS_3_RST  LEFT_CN_PIN_21
#define MIKROBUS_3_CS   LEFT_CN_PIN_22
#define MIKROBUS_3_SCK  UP_CN_PIN_88
#define MIKROBUS_3_MISO UP_CN_PIN_89
#define MIKROBUS_3_MOSI UP_CN_PIN_90
#define MIKROBUS_3_PWM  DOWN_CN_PIN_34
#define MIKROBUS_3_INT  UP_CN_PIN_96
#define MIKROBUS_3_RX   DOWN_CN_PIN_36
#define MIKROBUS_3_TX   DOWN_CN_PIN_33
#define MIKROBUS_3_SCL  UP_CN_PIN_88
#define MIKROBUS_3_SDA  UP_CN_PIN_89

#define USB_UART_TX     RIGHT_CN_PIN_74
#define USB_UART_RX     RIGHT_CN_PIN_73

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
