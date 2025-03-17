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
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
extern "C"
{
#endif

#define BOARD_NAME "Explorer 8 Development Kit"

#include "mikrobus.h"
#ifdef _MSDK_MCU_CARD_NAME_
#include "pim_socket.h"
#else
#include "dip_socket.h"
#endif

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_2      2

#ifdef _MSDK_MCU_CARD_NAME_
#define MIKROBUS_1_AN   PIM_PIN_21
#define MIKROBUS_1_RST  PIM_PIN_47
#define MIKROBUS_1_CS   PIM_PIN_34
#define MIKROBUS_1_SCK  PIM_PIN_44
#define MIKROBUS_1_MISO PIM_PIN_45
#define MIKROBUS_1_MOSI PIM_PIN_46
#define MIKROBUS_1_PWM  PIM_PIN_35
#define MIKROBUS_1_INT  PIM_PIN_57
#define MIKROBUS_1_RX   PIM_PIN_38
#define MIKROBUS_1_TX   PIM_PIN_37
#define MIKROBUS_1_SCL  PIM_PIN_44
#define MIKROBUS_1_SDA  PIM_PIN_43

#define MIKROBUS_2_AN   PIM_PIN_04
#define MIKROBUS_2_RST  PIM_PIN_63
#define MIKROBUS_2_CS   PIM_PIN_78
#define MIKROBUS_2_SCK  PIM_PIN_64
#define MIKROBUS_2_MISO PIM_PIN_65
#define MIKROBUS_2_MOSI PIM_PIN_66
#define MIKROBUS_2_PWM  PIM_PIN_36
#define MIKROBUS_2_INT  PIM_PIN_58
#define MIKROBUS_2_RX   PIM_PIN_07
#define MIKROBUS_2_TX   PIM_PIN_06
#define MIKROBUS_2_SCL  PIM_PIN_44
#define MIKROBUS_2_SDA  PIM_PIN_45

#define LED_1   PIM_PIN_72
#define LED_2   PIM_PIN_69
#define LED_3   PIM_PIN_68
#define LED_4   PIM_PIN_67
#define LED_5   PIM_PIN_58
#define LED_6   PIM_PIN_57
#define LED_7   PIM_PIN_56
#define LED_8   PIM_PIN_55
#else
#define MIKROBUS_1_AN   MIKROBUS_1_DIP_AN
#define MIKROBUS_1_RST  MIKROBUS_1_DIP_RST
#define MIKROBUS_1_CS   MIKROBUS_1_DIP_CS
#define MIKROBUS_1_SCK  MIKROBUS_1_DIP_SCK
#define MIKROBUS_1_MISO MIKROBUS_1_DIP_MISO
#define MIKROBUS_1_MOSI MIKROBUS_1_DIP_MOSI
#define MIKROBUS_1_PWM  MIKROBUS_1_DIP_PWM
#define MIKROBUS_1_INT  MIKROBUS_1_DIP_INT
#define MIKROBUS_1_RX   MIKROBUS_1_DIP_RX
#define MIKROBUS_1_TX   MIKROBUS_1_DIP_TX
#define MIKROBUS_1_SCL  MIKROBUS_1_DIP_SCL
#define MIKROBUS_1_SDA  MIKROBUS_1_DIP_SDA

#define MIKROBUS_2_AN   MIKROBUS_2_DIP_AN
#define MIKROBUS_2_RST  MIKROBUS_2_DIP_RST
#define MIKROBUS_2_CS   MIKROBUS_2_DIP_CS
#define MIKROBUS_2_SCK  MIKROBUS_2_DIP_SCK
#define MIKROBUS_2_MISO MIKROBUS_2_DIP_MISO
#define MIKROBUS_2_MOSI MIKROBUS_2_DIP_MOSI
#define MIKROBUS_2_PWM  MIKROBUS_2_DIP_PWM
#define MIKROBUS_2_INT  MIKROBUS_2_DIP_INT
#define MIKROBUS_2_RX   MIKROBUS_2_DIP_RX
#define MIKROBUS_2_TX   MIKROBUS_2_DIP_TX
#define MIKROBUS_2_SCL  MIKROBUS_2_DIP_SCL
#define MIKROBUS_2_SDA  MIKROBUS_2_DIP_SDA

#ifdef GPIO_PD0
#define LED_1   GPIO_PD0
#endif
#ifdef GPIO_PD1
#define LED_2   GPIO_PD1
#endif
#ifdef GPIO_PD2
#define LED_3   GPIO_PD2
#endif
#ifdef GPIO_PD3
#define LED_4   GPIO_PD3
#endif
#ifdef GPIO_PB0
#define LED_5   GPIO_PB0
#endif
#ifdef GPIO_PB1
#define LED_6   GPIO_PB1
#endif
#ifdef GPIO_PB2
#define LED_7   GPIO_PB2
#endif
#ifdef GPIO_PB3
#define LED_8   GPIO_PB3
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
