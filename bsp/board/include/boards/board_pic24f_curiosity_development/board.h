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

#define BOARD_NAME "PIC24F Curiosity Development Board"

#include "mikrobus.h"

// Mapping

#define MIKROBUS_1                  1
#define MIKROBUS_1_AN               GPIO_PA0
#define MIKROBUS_1_RST              GPIO_PA1
#define MIKROBUS_1_CS               GPIO_PC3
#define MIKROBUS_1_SCK              GPIO_PC4
#define MIKROBUS_1_MISO             GPIO_PB8
#define MIKROBUS_1_MOSI             GPIO_PB9
#define MIKROBUS_1_PWM              GPIO_PB10
#define MIKROBUS_1_INT              GPIO_PB7
#define MIKROBUS_1_RX               GPIO_PB5
#define MIKROBUS_1_TX               GPIO_PB6
#define MIKROBUS_1_SCL              GPIO_PB3
#define MIKROBUS_1_SDA              GPIO_PB2

#define HEADER_CONNECTOR_J1_D1       // Pin not routed
#define HEADER_CONNECTOR_J1_D2       // Pin not routed
#define HEADER_CONNECTOR_J1_D3       // Pin not routed
#define HEADER_CONNECTOR_J1_D4       GPIO_PB7
#define HEADER_CONNECTOR_J1_D5       GPIO_PB6
#define HEADER_CONNECTOR_J1_D6       // Pin not routed

#define HEADER_CONNECTOR_J2_D1       GPIO_PB9
#define HEADER_CONNECTOR_J2_D2       GPIO_PC6
#define HEADER_CONNECTOR_J2_D3       GPIO_PC7
#define HEADER_CONNECTOR_J2_D4       GPIO_PC8
#define HEADER_CONNECTOR_J2_D5       GPIO_PC9
#define HEADER_CONNECTOR_J2_D6       // Pin not routed
#define HEADER_CONNECTOR_J2_D7       // Pin not routed
#define HEADER_CONNECTOR_J2_D8       GPIO_PB10
#define HEADER_CONNECTOR_J2_D9       GPIO_PB11
#define HEADER_CONNECTOR_J2_D10      GPIO_PB12
#define HEADER_CONNECTOR_J2_D11      GPIO_PB13
#define HEADER_CONNECTOR_J2_D12      GPIO_PA10
#define HEADER_CONNECTOR_J2_D13      GPIO_PA7
#define HEADER_CONNECTOR_J2_D14      GPIO_PB14
#define HEADER_CONNECTOR_J2_D15      GPIO_PB15
#define HEADER_CONNECTOR_J2_D16      // Pin not routed
#define HEADER_CONNECTOR_J2_D17      // Pin not routed
#define HEADER_CONNECTOR_J2_D18      // Pin not routed
#define HEADER_CONNECTOR_J2_D19      GPIO_PA0
#define HEADER_CONNECTOR_J2_D20      GPIO_PA1
#define HEADER_CONNECTOR_J2_D21      GPIO_PB0
#define HEADER_CONNECTOR_J2_D22      GPIO_PB1
#define HEADER_CONNECTOR_J2_D23      GPIO_PB2
#define HEADER_CONNECTOR_J2_D24      GPIO_PB3
#define HEADER_CONNECTOR_J2_D25      // Pin not routed
#define HEADER_CONNECTOR_J2_D26      // Pin not routed
#define HEADER_CONNECTOR_J2_D27      // Pin not routed
#define HEADER_CONNECTOR_J2_D28      // Pin not routed

#define HEADER_CONNECTOR_J3_D1       GPIO_PB7
#define HEADER_CONNECTOR_J3_D2       GPIO_PB8
#define HEADER_CONNECTOR_J3_D3       GPIO_PB5
#define HEADER_CONNECTOR_J3_D4       GPIO_PB6
#define HEADER_CONNECTOR_J3_D5       // Pin not routed
#define HEADER_CONNECTOR_J3_D6       // Pin not routed
#define HEADER_CONNECTOR_J3_D7       GPIO_PC4
#define HEADER_CONNECTOR_J3_D8       GPIO_PC5
#define HEADER_CONNECTOR_J3_D9       GPIO_PA9
#define HEADER_CONNECTOR_J3_D10      GPIO_PC3
#define HEADER_CONNECTOR_J3_D11      GPIO_PB4
#define HEADER_CONNECTOR_J3_D12      GPIO_PA4
#define HEADER_CONNECTOR_J3_D13      GPIO_PA3
#define HEADER_CONNECTOR_J3_D14      GPIO_PA8
#define HEADER_CONNECTOR_J3_D15      // Pin not routed
#define HEADER_CONNECTOR_J3_D16      GPIO_PA2
#define HEADER_CONNECTOR_J3_D17      GPIO_PC2
#define HEADER_CONNECTOR_J3_D18      // Pin not routed
#define HEADER_CONNECTOR_J3_D19      GPIO_PC0
#define HEADER_CONNECTOR_J3_D20      GPIO_PC1
#define HEADER_CONNECTOR_J3_D21      // Pin not routed
#define HEADER_CONNECTOR_J3_D22      // Pin not routed
#define HEADER_CONNECTOR_J3_D23      // Pin not routed
#define HEADER_CONNECTOR_J3_D24      // Pin not routed
#define HEADER_CONNECTOR_J3_D25      // Pin not routed
#define HEADER_CONNECTOR_J3_D26      // Pin not routed
#define HEADER_CONNECTOR_J3_D27      // Pin not routed
#define HEADER_CONNECTOR_J3_D28      // Pin not routed

#define HEADER_CONNECTOR_J5_D1       // Pin not routed
#define HEADER_CONNECTOR_J5_D2       // Pin not routed
#define HEADER_CONNECTOR_J5_D3       // Pin not routed
#define HEADER_CONNECTOR_J5_D4       GPIO_PB0
#define HEADER_CONNECTOR_J5_D5       BP1
#define HEADER_CONNECTOR_J5_D6       // Pin not routed

// LEDS
#define LED1        GPIO_PA9
#define LED2        GPIO_PA10
#define LED3_RED    GPIO_PC5
#define LED4_GREEN  GPIO_PC6
#define LED5_BLUE   GPIO_PC7

// BUTTONS
#define BUTTON1     GPIO_PC9
#define BUTTON2     GPIO_PC8

// POTENTIOMETER
#define POT1        GPIO_PC0

// PKOB SERIAL EEPROM
#define PKEE_CS     GPIO_PD5
#define PKEE_SCK    GPIO_PD8
#define PKEE_MOSI   GPIO_PD0
#define PKEE_MISO   GPIO_PD11
#define PKEE_WP     GPIO_PD7

// PKOB USB INTERFACE
#define PKOB_D_N    GPIO_PG3
#define PKOB_D_P    GPIO_PG2

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END