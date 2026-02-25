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

#define BOARD_NAME "CLICKER 4 for R7FA4M2A"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN   GPIO_P000
#define MIKROBUS_1_RST  GPIO_P211
#define MIKROBUS_1_CS   GPIO_P414
#define MIKROBUS_1_SCK  GPIO_P412
#define MIKROBUS_1_MISO GPIO_P410
#define MIKROBUS_1_MOSI GPIO_P411
#define MIKROBUS_1_PWM  GPIO_P205
#define MIKROBUS_1_INT  GPIO_P404
#define MIKROBUS_1_RX   GPIO_P408
#define MIKROBUS_1_TX   GPIO_P409
#define MIKROBUS_1_SCL  GPIO_P400
#define MIKROBUS_1_SDA  GPIO_P401

#define MIKROBUS_2 2
#define MIKROBUS_2_AN   GPIO_P001
#define MIKROBUS_2_RST  GPIO_P210
#define MIKROBUS_2_CS   GPIO_P708
#define MIKROBUS_2_SCK  GPIO_P412
#define MIKROBUS_2_MISO GPIO_P410
#define MIKROBUS_2_MOSI GPIO_P411
#define MIKROBUS_2_PWM  GPIO_P214
#define MIKROBUS_2_INT  GPIO_P415
#define MIKROBUS_2_RX   GPIO_P206
#define MIKROBUS_2_TX   GPIO_P207
#define MIKROBUS_2_SCL  GPIO_P400
#define MIKROBUS_2_SDA  GPIO_P401

#define MIKROBUS_3 3
#define MIKROBUS_3_AN   GPIO_P002
#define MIKROBUS_3_RST  GPIO_P209
#define MIKROBUS_3_CS   GPIO_P406
#define MIKROBUS_3_SCK  GPIO_P412
#define MIKROBUS_3_MISO GPIO_P410
#define MIKROBUS_3_MOSI GPIO_P411
#define MIKROBUS_3_PWM  GPIO_P610
#define MIKROBUS_3_INT  GPIO_P006
#define MIKROBUS_3_RX   GPIO_P301
#define MIKROBUS_3_TX   GPIO_P302
#define MIKROBUS_3_SCL  GPIO_P400
#define MIKROBUS_3_SDA  GPIO_P401

#define MIKROBUS_4 4
#define MIKROBUS_4_AN   GPIO_P004
#define MIKROBUS_4_RST  GPIO_P208
#define MIKROBUS_4_CS   GPIO_P405
#define MIKROBUS_4_SCK  GPIO_P412
#define MIKROBUS_4_MISO GPIO_P410
#define MIKROBUS_4_MOSI GPIO_P411
#define MIKROBUS_4_PWM  GPIO_P105
#define MIKROBUS_4_INT  GPIO_P101
#define MIKROBUS_4_RX   GPIO_P601
#define MIKROBUS_4_TX   GPIO_P602
#define MIKROBUS_4_SCL  GPIO_P400
#define MIKROBUS_4_SDA  GPIO_P401

// LEDs
#define LED_1 GPIO_P307
#define LED_2 GPIO_P305
#define LED_3 GPIO_P303
#define LED_4 GPIO_P112
#define LED_5 GPIO_P114
#define LED_6 GPIO_P608

// Buttons
#define BUTTON_1 GPIO_P201
#define BUTTON_2 GPIO_P306
#define BUTTON_3 GPIO_P304
#define BUTTON_4 GPIO_P111
#define BUTTON_5 GPIO_P113
#define BUTTON_6 GPIO_P116

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END