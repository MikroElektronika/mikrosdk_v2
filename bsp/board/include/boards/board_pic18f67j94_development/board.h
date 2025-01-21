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

#define BOARD_NAME "PIC18F67J94 Development Board"

#include "hal_target.h"

// Mapping
// ICSP
#define HEADER_CONNECTOR_P1_D1        // Pin not routed
#define HEADER_CONNECTOR_P1_D2        // Pin not routed
#define HEADER_CONNECTOR_P1_D3        // Pin not routed
#define HEADER_CONNECTOR_P1_D4        GPIO_PB7
#define HEADER_CONNECTOR_P1_D5        GPIO_PB6
#define HEADER_CONNECTOR_P1_D6        // Pin not routed

// OLED Display
#define DISPLAY_CONNECTOR_DC1_D1      GPIO_PE3
#define DISPLAY_CONNECTOR_DC1_D2      GPIO_PE4
#define DISPLAY_CONNECTOR_DC1_D3      GPIO_PE5
#define DISPLAY_CONNECTOR_DC1_D4      GPIO_PE6
#define DISPLAY_CONNECTOR_DC1_D5      GPIO_PD0
#define DISPLAY_CONNECTOR_DC1_D6      GPIO_PD1
#define DISPLAY_CONNECTOR_DC1_D7      GPIO_PD2
#define DISPLAY_CONNECTOR_DC1_D8      GPIO_PD3
#define DISPLAY_CONNECTOR_DC1_D9      GPIO_PD4
#define DISPLAY_CONNECTOR_DC1_D10     GPIO_PD5
#define DISPLAY_CONNECTOR_DC1_D11     GPIO_PD6
#define DISPLAY_CONNECTOR_DC1_D12     GPIO_PD7

// LEDS
#define LED1        GPIO_PG0    //RED
#define LED2        GPIO_PG1    //RED
#define LED3        GPIO_PG2    //RED
#define LED4        GPIO_PG3    //RED
#define LED5        GPIO_PB0    //BLUE
#define LED6        GPIO_PB1    //BLUE
#define LED7        GPIO_PB2    //BLUE
#define LED8        GPIO_PB3    //BLUE

// CAPACITIVE TOUCH BUTTON
#define BUTTON1     GPIO_PA2

// ACCELEROMETER
#define ACCEL_D1    // Pin not routed
#define ACCEL_D2    // Pin not routed
#define ACCEL_D3    // Pin not routed
#define ACCEL_D4    GPIO_PA6
#define ACCEL_D5    // Pin not routed
#define ACCEL_D6    GPIO_PA4
#define ACCEL_D7    GPIO_PA5
#define ACCEL_D8    GPIO_PC7
#define ACCEL_D9    GPIO_PC5
#define ACCEL_D10   // Pin not routed
#define ACCEL_D11   GPIO_PC4
#define ACCEL_D12   // Pin not routed
#define ACCEL_D13   // Pin not routed
#define ACCEL_D14   // Pin not routed
#define ACCEL_D15   // Pin not routed
#define ACCEL_D16   // Pin not routed

// RADIO
#define RADIO_D1    // Pin not routed
#define RADIO_D2    GPIO_PC3
#define RADIO_D3    GPIO_PC2
#define RADIO_D4    GPIO_PC6
#define RADIO_D5    GPIO_PA1
#define RADIO_D6    GPIO_PA3
#define RADIO_D7    GPIO_PA0
#define RADIO_D8    GPIO_PF2
#define RADIO_D9    // Pin not routed
#define RADIO_D10   // Pin not routed
#define RADIO_D11   // Pin not routed
#define RADIO_D12   // Pin not routed

// USB INTERFACE
#define USB_D_N     GPIO_PF3
#define USB_D_P     GPIO_PF4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
