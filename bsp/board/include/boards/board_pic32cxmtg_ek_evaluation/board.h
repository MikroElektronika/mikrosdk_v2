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

#define BOARD_NAME "PIC32CXMTG EK Evaluation Kit"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   GPIO_PA30
#define MIKROBUS_1_RST  GPIO_PA25
#define MIKROBUS_1_CS   GPIO_PA19
#define MIKROBUS_1_SCK  GPIO_PA18
#define MIKROBUS_1_MISO GPIO_PA17
#define MIKROBUS_1_MOSI GPIO_PA16
#define MIKROBUS_1_PWM  GPIO_PD17
#define MIKROBUS_1_INT  GPIO_PC7
#define MIKROBUS_1_RX   GPIO_PD1
#define MIKROBUS_1_TX   GPIO_PD2
#define MIKROBUS_1_SCL  GPIO_PA9
#define MIKROBUS_1_SDA  GPIO_PA8

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   GPIO_PB0
#define MIKROBUS_2_RST  GPIO_PB26
#define MIKROBUS_2_CS   GPIO_PB8
#define MIKROBUS_2_SCK  GPIO_PB7
#define MIKROBUS_2_MISO GPIO_PB6
#define MIKROBUS_2_MOSI GPIO_PB5
#define MIKROBUS_2_PWM  GPIO_PD18
#define MIKROBUS_2_INT  GPIO_PB25
#define MIKROBUS_2_RX   GPIO_PB3
#define MIKROBUS_2_TX   GPIO_PB4
#define MIKROBUS_2_SCL  GPIO_PA13
#define MIKROBUS_2_SDA  GPIO_PA12

#define BUTTON2    GPIO_PA7

#define LED3       GPIO_PD16
#define LED4       GPIO_PD3

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
