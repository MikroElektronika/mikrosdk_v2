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

#define BOARD_NAME "TM4C123G LaunchPad Evaluation Kit"

#include "hal_target.h"

// Mapping
// BoosterPack 1
#define HEADER_CONNECTOR_J1_D1       // Pin not routed
#define HEADER_CONNECTOR_J1_D2       GPIO_PB5
#define HEADER_CONNECTOR_J1_D3       GPIO_PB0
#define HEADER_CONNECTOR_J1_D4       GPIO_PB1
#define HEADER_CONNECTOR_J1_D5       GPIO_PE4
#define HEADER_CONNECTOR_J1_D6       GPIO_PE5
#define HEADER_CONNECTOR_J1_D7       GPIO_PB4
#define HEADER_CONNECTOR_J1_D8       GPIO_PA5
#define HEADER_CONNECTOR_J1_D9       GPIO_PA6
#define HEADER_CONNECTOR_J1_D10      GPIO_PA7

#define HEADER_CONNECTOR_J2_D1       // Pin not routed
#define HEADER_CONNECTOR_J2_D2       GPIO_PB2
#define HEADER_CONNECTOR_J2_D3       GPIO_PE0
#define HEADER_CONNECTOR_J2_D4       GPIO_PF0
#define HEADER_CONNECTOR_J2_D5       // Pin not routed
#define HEADER_CONNECTOR_J2_D6       GPIO_PB7
#define HEADER_CONNECTOR_J2_D7       GPIO_PB6
#define HEADER_CONNECTOR_J2_D8       GPIO_PA4
#define HEADER_CONNECTOR_J2_D9       GPIO_PA3
#define HEADER_CONNECTOR_J2_D10      GPIO_PA2

#define HEADER_CONNECTOR_J3_D1       // Pin not routed
#define HEADER_CONNECTOR_J3_D2       // Pin not routed
#define HEADER_CONNECTOR_J3_D3       GPIO_PD0
#define HEADER_CONNECTOR_J3_D4       GPIO_PD1
#define HEADER_CONNECTOR_J3_D5       GPIO_PD2
#define HEADER_CONNECTOR_J3_D6       GPIO_PD3
#define HEADER_CONNECTOR_J3_D7       GPIO_PE1
#define HEADER_CONNECTOR_J3_D8       GPIO_PE2
#define HEADER_CONNECTOR_J3_D9       GPIO_PE3
#define HEADER_CONNECTOR_J3_D10      GPIO_PF1

#define HEADER_CONNECTOR_J4_D1       GPIO_PF2
#define HEADER_CONNECTOR_J4_D2       GPIO_PF3
#define HEADER_CONNECTOR_J4_D3       GPIO_PB3
#define HEADER_CONNECTOR_J4_D4       GPIO_PC4
#define HEADER_CONNECTOR_J4_D5       GPIO_PC5
#define HEADER_CONNECTOR_J4_D6       GPIO_PC6
#define HEADER_CONNECTOR_J4_D7       GPIO_PC7
#define HEADER_CONNECTOR_J4_D8       GPIO_PD6
#define HEADER_CONNECTOR_J4_D9       GPIO_PD7
#define HEADER_CONNECTOR_J4_D10      GPIO_PF4

// LEDS
#define LED1    GPIO_PF1     // RED
#define LED2    GPIO_PF2     // BLUE
#define LED3    GPIO_PF3     // GREEN

// BUTTONS
#define BUTTON1 GPIO_PF4     // SW1
#define BUTTON2 GPIO_PF0     // SW2

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END