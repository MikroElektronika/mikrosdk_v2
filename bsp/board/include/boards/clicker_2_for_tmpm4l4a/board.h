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

#define BOARD_NAME "Clicker 2 for TMPM4L4A"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN   GPIO_PF0
#define MIKROBUS_1_RST  GPIO_PE6
#define MIKROBUS_1_CS   GPIO_PG3
#define MIKROBUS_1_SCK  GPIO_PG2
#define MIKROBUS_1_MISO GPIO_PG1
#define MIKROBUS_1_MOSI GPIO_PG0
#define MIKROBUS_1_PWM  GPIO_PJ0
#define MIKROBUS_1_INT  GPIO_PF4
#define MIKROBUS_1_RX   GPIO_PA7
#define MIKROBUS_1_TX   GPIO_PJ2
#define MIKROBUS_1_SCL  GPIO_PA5
#define MIKROBUS_1_SDA  GPIO_PA6

#define MIKROBUS_2 2
#define MIKROBUS_2_AN   GPIO_PF1
#define MIKROBUS_2_RST  GPIO_PE7
#define MIKROBUS_2_CS   GPIO_PC5
#define MIKROBUS_2_SCK  GPIO_PG2
#define MIKROBUS_2_MISO GPIO_PG1
#define MIKROBUS_2_MOSI GPIO_PG0
#define MIKROBUS_2_PWM  GPIO_PJ1
#define MIKROBUS_2_INT  GPIO_PF5
#define MIKROBUS_2_RX   GPIO_PD4
#define MIKROBUS_2_TX   GPIO_PD5
#define MIKROBUS_2_SCL  GPIO_PA5
#define MIKROBUS_2_SDA  GPIO_PA6

#define LED_SDA_PIN GPIO_PA5
#define LED_SCL_PIN GPIO_PA6
#define LED_INT_PIN GPIO_PF3

#define SLIDER_PIN  GPIO_PF2

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
