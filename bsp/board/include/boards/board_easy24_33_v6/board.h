/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Easy24-33 v6"

/// Mapping

// Buttons
#define BUTTON_T1 PA0
#define BUTTON_T2 PA1
#define BUTTON_T3 PA2
#define BUTTON_T4 PA3
#define BUTTON_T5 PA4
#define BUTTON_T7 PA6
#define BUTTON_T8 PA7

#define BUTTON_T9  PB0
#define BUTTON_T10 PB1
#define BUTTON_T11 PB2
#define BUTTON_T12 PB3
#define BUTTON_T13 PB4
#define BUTTON_T14 PB5
#define BUTTON_T15 PB6
#define BUTTON_T16 PB7

#define BUTTON_T17 PB8
#define BUTTON_T18 PB9
#define BUTTON_T19 PB10
#define BUTTON_T20 PB11
#define BUTTON_T21 PB12
#define BUTTON_T22 PB13
#define BUTTON_T23 PB14
#define BUTTON_T24 PB15
// EOF Buttons

// LEDs
#define LED_LD1 PA0
#define LED_LD2 PA1
#define LED_LD3 PA2
#define LED_LD4 PA3
#define LED_LD5 PA4
#define LED_LD7 PA6
#define LED_LD8 PA7

#define LED_LD9  PB0
#define LED_LD10 PB1
#define LED_LD11 PB2
#define LED_LD12 PB3
#define LED_LD13 PB4
#define LED_LD14 PB5
#define LED_LD15 PB6
#define LED_LD16 PB7

#define LED_LD17 PB8
#define LED_LD18 PB9
#define LED_LD19 PB10
#define LED_LD20 PB11
#define LED_LD21 PB12
#define LED_LD22 PB13
#define LED_LD23 PB14
#define LED_LD24 PB15
// EOF LEDs

// SPI
// EOF SPI

// Buzzer
#define BUZZER_PB8 PB8
#define BUZZER_PB9 PB9
// EOF Buzzer

// USB Uart connections
#ifdef PB15
#define USB_UART_RX PB15
#endif
#ifdef PB1
#define USB_UART_RX PB1
#endif
#ifdef PB14
#define USB_UART_TX PB14
#endif
#ifdef PB0
#define USB_UART_RX PB0
#endif
// EOF USB Uart connections

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
