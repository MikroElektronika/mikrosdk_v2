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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Easy24-33 v6"

/// Mapping

// Buttons
#define BUTTON_T1 GPIO_PA0
#define BUTTON_T2 GPIO_PA1
#define BUTTON_T3 GPIO_PA2
#define BUTTON_T4 GPIO_PA3
#define BUTTON_T5 GPIO_PA4
#define BUTTON_T7 GPIO_PA6
#define BUTTON_T8 GPIO_PA7

#define BUTTON_T9  GPIO_PB0
#define BUTTON_T10 GPIO_PB1
#define BUTTON_T11 GPIO_PB2
#define BUTTON_T12 GPIO_PB3
#define BUTTON_T13 GPIO_PB4
#define BUTTON_T14 GPIO_PB5
#define BUTTON_T15 GPIO_PB6
#define BUTTON_T16 GPIO_PB7

#define BUTTON_T17 GPIO_PB8
#define BUTTON_T18 GPIO_PB9
#define BUTTON_T19 GPIO_PB10
#define BUTTON_T20 GPIO_PB11
#define BUTTON_T21 GPIO_PB12
#define BUTTON_T22 GPIO_PB13
#define BUTTON_T23 GPIO_PB14
#define BUTTON_T24 GPIO_PB15
// EOF Buttons

// LEDs
#define LED_LD1 GPIO_PA0
#define LED_LD2 GPIO_PA1
#define LED_LD3 GPIO_PA2
#define LED_LD4 GPIO_PA3
#define LED_LD5 GPIO_PA4
#define LED_LD7 GPIO_PA6
#define LED_LD8 GPIO_PA7

#define LED_LD9  GPIO_PB0
#define LED_LD10 GPIO_PB1
#define LED_LD11 GPIO_PB2
#define LED_LD12 GPIO_PB3
#define LED_LD13 GPIO_PB4
#define LED_LD14 GPIO_PB5
#define LED_LD15 GPIO_PB6
#define LED_LD16 GPIO_PB7

#define LED_LD17 GPIO_PB8
#define LED_LD18 GPIO_PB9
#define LED_LD19 GPIO_PB10
#define LED_LD20 GPIO_PB11
#define LED_LD21 GPIO_PB12
#define LED_LD22 GPIO_PB13
#define LED_LD23 GPIO_PB14
#define LED_LD24 GPIO_PB15
// EOF LEDs

// SPI
// EOF SPI

// Buzzer
#define BUZZER_PB8 GPIO_PB8
#define BUZZER_PB9 GPIO_PB9
// EOF Buzzer

// USB Uart connections
#ifdef GPIO_PB15
#define USB_UART_RX GPIO_PB15
#endif
#ifdef GPIO_PB1
#define USB_UART_RX GPIO_PB1
#endif
#ifdef GPIO_PB14
#define USB_UART_TX GPIO_PB14
#endif
#ifdef GPIO_PB0
#define USB_UART_RX GPIO_PB0
#endif
// EOF USB Uart connections

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
