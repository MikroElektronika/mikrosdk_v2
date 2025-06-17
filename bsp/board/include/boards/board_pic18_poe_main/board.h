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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/{markdown_path}
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "PIC18 POE Main Board"

#include "mikrobus.h"

#define MIKROBUS_1 1
#define MIKROBUS_1_AN   GPIO_PA5
#define MIKROBUS_1_RST  GPIO_PD0
#define MIKROBUS_1_CS   GPIO_PD1
#define MIKROBUS_1_SCK  GPIO_PC3
#define MIKROBUS_1_MISO GPIO_PC4
#define MIKROBUS_1_MOSI GPIO_PC5
#define MIKROBUS_1_PWM  GPIO_PC2
#define MIKROBUS_1_INT  GPIO_PB2
#define MIKROBUS_1_RX   GPIO_PC7
#define MIKROBUS_1_TX   GPIO_PC6
#define MIKROBUS_1_SCL  GPIO_PF6
#define MIKROBUS_1_SDA  GPIO_PF7

// LEDs
#define LED_D3          GPIO_PA0
#define LED_D4          GPIO_PA1
#define LED_D10_RED     GPIO_PE5
#define LED_D10_GREEN   GPIO_PE4

// Buttons
#define BUTTON_1 GPIO_PB0

#define USB_UART_TX GPIO_PC6
#define USB_UART_RX GPIO_PC7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
