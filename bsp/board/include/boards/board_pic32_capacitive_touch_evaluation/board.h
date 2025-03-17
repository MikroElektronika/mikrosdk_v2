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

#define BOARD_NAME "PIC32 CAPACITIVE TOUCH EVALUATION BOARD"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_J1_D1       // Pin not routed
#define HEADER_CONNECTOR_J1_D2       // Pin not routed
#define HEADER_CONNECTOR_J1_D3       // Pin not routed
#define HEADER_CONNECTOR_J1_D4       GPIO_PB7
#define HEADER_CONNECTOR_J1_D5       GPIO_PB6
#define HEADER_CONNECTOR_J1_D6       // Pin not routed

#define HEADER_CONNECTOR_J2_D1       // Pin not routed
#define HEADER_CONNECTOR_J2_D2       // Pin not routed
#define HEADER_CONNECTOR_J2_D3       // Pin not routed
#define HEADER_CONNECTOR_J2_D4       // Pin not routed
#define HEADER_CONNECTOR_J2_D5       GPIO_PF0
#define HEADER_CONNECTOR_J2_D6       GPIO_PD11
#define HEADER_CONNECTOR_J2_D7       GPIO_PF1
#define HEADER_CONNECTOR_J2_D8       GPIO_PD10
#define HEADER_CONNECTOR_J2_D9       // Pin not routed
#define HEADER_CONNECTOR_J2_D10      GPIO_PD9
#define HEADER_CONNECTOR_J2_D11      GPIO_PF4
#define HEADER_CONNECTOR_J2_D12      GPIO_PF5

#define HEADER_CONNECTOR_J3_D1       // Pin not routed
#define HEADER_CONNECTOR_J3_D2       GPIO_PB15
#define HEADER_CONNECTOR_J3_D3       GPIO_PB14
#define HEADER_CONNECTOR_J3_D4       // Pin not routed
#define HEADER_CONNECTOR_J3_D5       GPIO_PB13
#define HEADER_CONNECTOR_J3_D6       GPIO_PB12
#define HEADER_CONNECTOR_J3_D7       // Pin not routed
#define HEADER_CONNECTOR_J3_D8       GPIO_PB11
#define HEADER_CONNECTOR_J3_D9       GPIO_PB10
#define HEADER_CONNECTOR_J3_D10      // Pin not routed
#define HEADER_CONNECTOR_J3_D11      GPIO_PB9
#define HEADER_CONNECTOR_J3_D12      GPIO_PB8

#define HEADER_CONNECTOR_J4_D1       // Pin not routed
#define HEADER_CONNECTOR_J4_D2       GPIO_PB7
#define HEADER_CONNECTOR_J4_D3       GPIO_PB6
#define HEADER_CONNECTOR_J4_D4       // Pin not routed
#define HEADER_CONNECTOR_J4_D5       GPIO_PB5
#define HEADER_CONNECTOR_J4_D6       GPIO_PB4
#define HEADER_CONNECTOR_J4_D7       // Pin not routed
#define HEADER_CONNECTOR_J4_D8       GPIO_PB3
#define HEADER_CONNECTOR_J4_D9       GPIO_PB2
#define HEADER_CONNECTOR_J4_D10      // Pin not routed
#define HEADER_CONNECTOR_J4_D11      GPIO_PB1
#define HEADER_CONNECTOR_J4_D12      GPIO_PB0

// LEDS
#define LED1        GPIO_PD0
#define LED2        GPIO_PD1
#define LED3        GPIO_PD2
#define LED4        GPIO_PD3
#define LED5        GPIO_PD4
#define LED6        GPIO_PD5
#define LED7        GPIO_PD6
#define LED8        GPIO_PD7
#define LED9        GPIO_PE0
#define LED10       GPIO_PE1
#define LED11       GPIO_PE2
#define LED12       GPIO_PE3
#define LED13       GPIO_PE4
#define LED14       GPIO_PE5
#define LED15       GPIO_PE6
#define LED16       GPIO_PE7

#define BUTTON0       GPIO_PB0
#define BUTTON1       GPIO_PB1
#define BUTTON2       GPIO_PB2
#define BUTTON3       GPIO_PB3
#define BUTTON4       GPIO_PB4
#define BUTTON5       GPIO_PB5
#define BUTTON8       GPIO_PB8
#define BUTTON9       GPIO_PB9
#define BUTTON10      GPIO_PB10
#define BUTTON11      GPIO_PB11
#define BUTTON12      GPIO_PB12
#define BUTTON13      GPIO_PB13
#define BUTTON14      GPIO_PB14
#define BUTTON15      GPIO_PB15

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
