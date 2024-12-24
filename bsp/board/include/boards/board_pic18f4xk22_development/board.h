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

#define BOARD_NAME "PIC18F4XK22 Development Board"

#include "hal_target.h"

// Mapping
// PICTAIL HEADER J1
#define HEADER_CONNECTOR_J1_D1        GPIO_PE2
#define HEADER_CONNECTOR_J1_D2        GPIO_PA5
#define HEADER_CONNECTOR_J1_D3        GPIO_PE3
#define HEADER_CONNECTOR_J1_D4        GPIO_PA4
#define HEADER_CONNECTOR_J1_D5        GPIO_PA7
#define HEADER_CONNECTOR_J1_D6        GPIO_PA3
#define HEADER_CONNECTOR_J1_D7        GPIO_PA6
#define HEADER_CONNECTOR_J1_D8        GPIO_PC5
#define HEADER_CONNECTOR_J1_D9        GPIO_PC7
#define HEADER_CONNECTOR_J1_D10       GPIO_PC4
#define HEADER_CONNECTOR_J1_D11       GPIO_PC6
#define HEADER_CONNECTOR_J1_D12       GPIO_PC3
#define HEADER_CONNECTOR_J1_D13       GPIO_PB7
#define HEADER_CONNECTOR_J1_D14       GPIO_PA0
#define HEADER_CONNECTOR_J1_D15       GPIO_PB6
#define HEADER_CONNECTOR_J1_D16       GPIO_PA1
#define HEADER_CONNECTOR_J1_D17       GPIO_PB5
#define HEADER_CONNECTOR_J1_D18       GPIO_PA2
#define HEADER_CONNECTOR_J1_D19       GPIO_PB4
#define HEADER_CONNECTOR_J1_D20       // Pin not routed
#define HEADER_CONNECTOR_J1_D21       GPIO_PB3
#define HEADER_CONNECTOR_J1_D22       // Pin not routed
#define HEADER_CONNECTOR_J1_D23       GPIO_PB2
#define HEADER_CONNECTOR_J1_D24       GPIO_PC2
#define HEADER_CONNECTOR_J1_D25       GPIO_PB1
#define HEADER_CONNECTOR_J1_D26       // Pin not routed
#define HEADER_CONNECTOR_J1_D27       GPIO_PB0
#define HEADER_CONNECTOR_J1_D28       // Pin not routed

// PICTAIL HEADER J2
#define HEADER_CONNECTOR_J2_D1        GPIO_PD1
#define HEADER_CONNECTOR_J2_D2        GPIO_PD0
#define HEADER_CONNECTOR_J2_D3        GPIO_PD3
#define HEADER_CONNECTOR_J2_D4        GPIO_PD2
#define HEADER_CONNECTOR_J2_D5        GPIO_PD5
#define HEADER_CONNECTOR_J2_D6        GPIO_PD4
#define HEADER_CONNECTOR_J2_D7        GPIO_PD7
#define HEADER_CONNECTOR_J2_D8        GPIO_PD6
#define HEADER_CONNECTOR_J2_D9        GPIO_PE1
#define HEADER_CONNECTOR_J2_D10       GPIO_PE0
#define HEADER_CONNECTOR_J2_D11       // Pin not routed
#define HEADER_CONNECTOR_J2_D12       // Pin not routed

// POWER ANALIZER
#define HEADER_CONNECTOR_J6_D1        // Pin not routed
#define HEADER_CONNECTOR_J6_D2        // Pin not routed
#define HEADER_CONNECTOR_J6_D3        // Pin not routed
#define HEADER_CONNECTOR_J6_D4        GPIO_PB4
#define HEADER_CONNECTOR_J6_D5        // Pin not routed
#define HEADER_CONNECTOR_J6_D6        // Pin not routed
#define HEADER_CONNECTOR_J6_D7        // Pin not routed

// ICSP - 6-PIN HEADER
#define HEADER_CONNECTOR_P1_D1        GPIO_PE3
#define HEADER_CONNECTOR_P1_D2        // Pin not routed
#define HEADER_CONNECTOR_P1_D3        // Pin not routed
#define HEADER_CONNECTOR_P1_D4        GPIO_PB7
#define HEADER_CONNECTOR_P1_D5        GPIO_PB6
#define HEADER_CONNECTOR_P1_D6        // Pin not routed

// PICKIT SERIAL ANALYZER HEADER
#define HEADER_CONNECTOR_P2_D1        GPIO_PC7
#define HEADER_CONNECTOR_P2_D2        // Pin not routed
#define HEADER_CONNECTOR_P2_D3        // Pin not routed
#define HEADER_CONNECTOR_P2_D4        // Pin not routed
#define HEADER_CONNECTOR_P2_D5        // Pin not routed
#define HEADER_CONNECTOR_P2_D6        GPIO_PC6

// ICSP - RJ-11 HEADER
#define HEADER_CONNECTOR_P3_D1        GPIO_PE3
#define HEADER_CONNECTOR_P3_D2        // Pin not routed
#define HEADER_CONNECTOR_P3_D3        // Pin not routed
#define HEADER_CONNECTOR_P3_D4        GPIO_PB7
#define HEADER_CONNECTOR_P3_D5        GPIO_PB6
#define HEADER_CONNECTOR_P3_D6        // Pin not routed


// AUDIO/ANALOG OUT
#define HEADER_CONNECTOR_J4_D1        GPIO_PC2

// AUDIO/ANALOG IN WITH ADJUSTABLE GAIN
#define HEADER_CONNECTOR_J5_D1        GPIO_PE2


// OLED Display
#define DISPLAY_CONNECTOR_DC1_D1      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D2      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D3      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D4      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D5      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D6      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D7      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D8      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D9      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D10     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D11     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D12     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D13     GPIO_PA7
#define DISPLAY_CONNECTOR_DC1_D14     GPIO_PA4
#define DISPLAY_CONNECTOR_DC1_D15     GPIO_PA5
#define DISPLAY_CONNECTOR_DC1_D16     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D17     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D18     GPIO_PC3
#define DISPLAY_CONNECTOR_DC1_D19     GPIO_PC5
#define DISPLAY_CONNECTOR_DC1_D20     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D21     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D22     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D23     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D24     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D25     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D26     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D27     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D28     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D29     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D30     // Pin not routed


// LEDS
#define LED2        GPIO_PD0
#define LED3        GPIO_PD1
#define LED4        GPIO_PD2
#define LED5        GPIO_PD3
#define LED6        GPIO_PD4
#define LED7        GPIO_PD5
#define LED8        GPIO_PD6
#define LED9        GPIO_PD7


// BUTTON
#define BUTTON1     GPIO_PB0
#define BUTTON2     GPIO_PB1
#define BUTTON3     GPIO_PB2
#define BUTTON4     GPIO_PB3


// POTENTIOMETER
#define POT1        GPIO_PE0


// TEMPERATURE SENSOR
#define TEMP_VOUT   GPIO_PE1


// SERIAL EEPROM
#define SEPR_CS     GPIO_PA6
#define SEPR_SCK    GPIO_PC3
#define SEPR_MOSI   GPIO_PC5
#define SEPR_MISO   GPIO_PC4
#define SEPR_WP     // Pin not routed


#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
