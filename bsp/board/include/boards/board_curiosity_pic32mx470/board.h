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
extern "C"
{
#endif

#define BOARD_NAME "Curiosity PIC32MX470 Development Board"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   PB4
#define MIKROBUS_1_RST  PE3
#define MIKROBUS_1_CS   PD4
#define MIKROBUS_1_SCK  PD2
#define MIKROBUS_1_MISO PD3
#define MIKROBUS_1_MOSI PD5
#define MIKROBUS_1_PWM  PB14
#define MIKROBUS_1_INT  PD1
#define MIKROBUS_1_RX   PF1
#define MIKROBUS_1_TX   PF0
#define MIKROBUS_1_SCL  PD10
#define MIKROBUS_1_SDA  PD9

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   PB11
#define MIKROBUS_2_RST  PB15
#define MIKROBUS_2_CS   PG9
#define MIKROBUS_2_SCK  PG6
#define MIKROBUS_2_MISO PG7
#define MIKROBUS_2_MOSI PG8
#define MIKROBUS_2_PWM  PD8
#define MIKROBUS_2_INT  PD0
#define MIKROBUS_2_RX   PB9
#define MIKROBUS_2_TX   PE5
#define MIKROBUS_2_SCL  PF5
#define MIKROBUS_2_SDA  PF4

// LEDs
#define LED_1       PE4
#define LED_2       PE6
#define LED_3       PE7
#define LED_4_RED   PB10
#define LED_4_GREEN PB3
#define LED_4_BLUE  PB2

// Buttons
#define BUTTON_1 PD6

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
