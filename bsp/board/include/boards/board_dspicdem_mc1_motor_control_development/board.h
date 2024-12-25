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

#define BOARD_NAME "dsPICDEM MC1 Motor Control Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       GPIO_PB10
#define HEADER_CONNECTOR_CN1_D2       GPIO_PB1
#define HEADER_CONNECTOR_CN1_D3       GPIO_PB8
#define HEADER_CONNECTOR_CN1_D4       // Pin not routed
#define HEADER_CONNECTOR_CN1_D5       GPIO_PB13
#define HEADER_CONNECTOR_CN1_D6       GPIO_PD10
#define HEADER_CONNECTOR_CN1_D7       GPIO_PE7
#define HEADER_CONNECTOR_CN1_D8       GPIO_PB9
#define HEADER_CONNECTOR_CN1_D9       // Pin not routed
#define HEADER_CONNECTOR_CN1_D10      GPIO_PD5
#define HEADER_CONNECTOR_CN1_D11      GPIO_PE5
#define HEADER_CONNECTOR_CN1_D12      GPIO_PE3
#define HEADER_CONNECTOR_CN1_D13      GPIO_PE1
#define HEADER_CONNECTOR_CN1_D14      GPIO_PF6
#define HEADER_CONNECTOR_CN1_D15      GPIO_PB15
#define HEADER_CONNECTOR_CN1_D16      GPIO_PB1
#define HEADER_CONNECTOR_CN1_D17      GPIO_PB6
#define HEADER_CONNECTOR_CN1_D18      // Pin not routed
#define HEADER_CONNECTOR_CN1_D19      // Pin not routed
#define HEADER_CONNECTOR_CN1_D20      GPIO_PB2
#define HEADER_CONNECTOR_CN1_D21      GPIO_PB0
#define HEADER_CONNECTOR_CN1_D22      GPIO_PB14
#define HEADER_CONNECTOR_CN1_D23      GPIO_PB14
#define HEADER_CONNECTOR_CN1_D24      GPIO_PB12
#define HEADER_CONNECTOR_CN1_D25      GPIO_PE6
#define HEADER_CONNECTOR_CN1_D26      GPIO_PB11
#define HEADER_CONNECTOR_CN1_D27      // Pin not routed
#define HEADER_CONNECTOR_CN1_D28      GPIO_PD4
#define HEADER_CONNECTOR_CN1_D29      GPIO_PE4
#define HEADER_CONNECTOR_CN1_D30      GPIO_PE2
#define HEADER_CONNECTOR_CN1_D31      GPIO_PE0
#define HEADER_CONNECTOR_CN1_D32      GPIO_PF7
#define HEADER_CONNECTOR_CN1_D33      GPIO_PE9
#define HEADER_CONNECTOR_CN1_D34      GPIO_PB2
#define HEADER_CONNECTOR_CN1_D35      GPIO_PB0
#define HEADER_CONNECTOR_CN1_D36      // Pin not routed
#define HEADER_CONNECTOR_CN1_D37      // Pin not routed

// LCD
#define LCD_EN GPIO_PD13
#define LCD_DB0 GPIO_PD0
#define LCD_DB1 GPIO_PD1
#define LCD_DB2 GPIO_PD2
#define LCD_DB3 GPIO_PD3
#define LCD_R_W GPIO_PC1
#define LCD_D_C GPIO_PC3

// LEDS
#define LED1    GPIO_PA9
#define LED2    GPIO_PA10
#define LED3    GPIO_PA14
#define LED4    GPIO_PA15

// BUTTONS
#define BUTTON1 GPIO_PG6
#define BUTTON2 GPIO_PG7
#define BUTTON3 GPIO_PG8
#define BUTTON4 GPIO_PG9

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END