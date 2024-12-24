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

#define BOARD_NAME "MPLab Starter Kit For PIC18F MCUs"

#include "hal_target.h"

// Mapping
// ICSP/TEST/DEBUG HEADER
#define HEADER_CONNECTOR_J1_D1       // Pin not routed
#define HEADER_CONNECTOR_J1_D2       // Pin not routed
#define HEADER_CONNECTOR_J1_D3       // Pin not routed
#define HEADER_CONNECTOR_J1_D4       GPIO_PB7
#define HEADER_CONNECTOR_J1_D5       GPIO_PB6
#define HEADER_CONNECTOR_J1_D6       // Pin not routed

// MICROSD CARD
#define HEADER_CONNECTOR_J5_D1       // Pin not routed
#define HEADER_CONNECTOR_J5_D2       GPIO_PC6
#define HEADER_CONNECTOR_J5_D3       GPIO_PB3
#define HEADER_CONNECTOR_J5_D4       // Pin not routed
#define HEADER_CONNECTOR_J5_D5       GPIO_PC2
#define HEADER_CONNECTOR_J5_D6       // Pin not routed
#define HEADER_CONNECTOR_J5_D7       GPIO_PD6
#define HEADER_CONNECTOR_J5_D8       // Pin not routed

// PICKIT 2 (NOT POPULATED)
#define HEADER_CONNECTOR_J6_D1       GPIO_PC2
#define HEADER_CONNECTOR_J6_D2       // Pin not routed
#define HEADER_CONNECTOR_J6_D3       // Pin not routed
#define HEADER_CONNECTOR_J6_D4       GPIO_PB7
#define HEADER_CONNECTOR_J6_D5       GPIO_PB6
#define HEADER_CONNECTOR_J6_D6       // Pin not routed

// HEADER CONNECTOR
#define HEADER_CONNECTOR_J4_D1       GPIO_PB1
#define HEADER_CONNECTOR_J4_D2       GPIO_PB2
#define HEADER_CONNECTOR_J4_D3       GPIO_PD0
#define HEADER_CONNECTOR_J4_D4       GPIO_PD1
#define HEADER_CONNECTOR_J4_D5       GPIO_PD2
#define HEADER_CONNECTOR_J4_D6       GPIO_PD3
#define HEADER_CONNECTOR_J4_D7       GPIO_PD4
#define HEADER_CONNECTOR_J4_D8       GPIO_PD5
#define HEADER_CONNECTOR_J4_D9       GPIO_PD6
#define HEADER_CONNECTOR_J4_D10      GPIO_PD7
#define HEADER_CONNECTOR_J4_D11      GPIO_PE0
#define HEADER_CONNECTOR_J4_D12      GPIO_PE1
#define HEADER_CONNECTOR_J4_D13      GPIO_PB5
#define HEADER_CONNECTOR_J4_D14      GPIO_PB4
#define HEADER_CONNECTOR_J4_D15      GPIO_PC2
#define HEADER_CONNECTOR_J4_D16      GPIO_PB3
#define HEADER_CONNECTOR_J4_D17      // Pin not routed
#define HEADER_CONNECTOR_J4_D18      // Pin not routed

// OLED Display
#define DISPLAY_CONNECTOR_DC1_D1     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D2     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D3     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D4     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D5     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D6     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D7     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D8     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D9     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D10    // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D11    GPIO_PE2
#define DISPLAY_CONNECTOR_DC1_D12    GPIO_PB4
#define DISPLAY_CONNECTOR_DC1_D13    GPIO_PB5
#define DISPLAY_CONNECTOR_DC1_D14    GPIO_PE1
#define DISPLAY_CONNECTOR_DC1_D15    GPIO_PE0
#define DISPLAY_CONNECTOR_DC1_D16    // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D17    // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D18    GPIO_PD0
#define DISPLAY_CONNECTOR_DC1_D19    GPIO_PD1
#define DISPLAY_CONNECTOR_DC1_D20    GPIO_PD2
#define DISPLAY_CONNECTOR_DC1_D21    GPIO_PD3
#define DISPLAY_CONNECTOR_DC1_D22    GPIO_PD4
#define DISPLAY_CONNECTOR_DC1_D23    GPIO_PD5
#define DISPLAY_CONNECTOR_DC1_D24    GPIO_PD6
#define DISPLAY_CONNECTOR_DC1_D25    GPIO_PD7
#define DISPLAY_CONNECTOR_DC1_D26    // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D27    // Pin not routed

// TOUCH PAD
#define BUTTON      GPIO_PB0

// POTENTIOMETER
#define POT1        GPIO_PA0

// SERIAL EEPROM
#define EEPROM_SI   GPIO_PC5
#define EEPROM_SCK  GPIO_PC3
#define EEPROM_CS   GPIO_PD3
#define EEPROM_WP   GPIO_PB4
#define EEPROM_SO   GPIO_PC4

// USB INTERFACE
#define USB_D_N     GPIO_PF3
#define USB_D_P     GPIO_PF4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
