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

#define BOARD_NAME "PIC18F87J72 Energy Monitoring PICTail Plus Daughter Board"

#include "hal_target.h"

// Mapping
// IN CIRCUIT DEBUG/PROGRAMING HEADER
#define HEADER_CONNECTOR_J1_D1        // Pin not routed
#define HEADER_CONNECTOR_J1_D2        // Pin not routed
#define HEADER_CONNECTOR_J1_D3        // Pin not routed
#define HEADER_CONNECTOR_J1_D4        GPIO_PB7
#define HEADER_CONNECTOR_J1_D5        GPIO_PB6
#define HEADER_CONNECTOR_J1_D6        // Pin not routed

// PICTAIL PLUS
#define HEADER_CONNECTOR_J7_D2        GPIO_PC7
#define HEADER_CONNECTOR_J7_D4        GPIO_PC6
#define HEADER_CONNECTOR_J7_D9        // Pin not routed
#define HEADER_CONNECTOR_J7_D10       // Pin not routed
#define HEADER_CONNECTOR_J7_D15       // Pin not routed
#define HEADER_CONNECTOR_J7_D16       // Pin not routed
#define HEADER_CONNECTOR_J7_D21       // Pin not routed
#define HEADER_CONNECTOR_J7_D22       // Pin not routed
#define HEADER_CONNECTOR_J7_D41       // Pin not routed
#define HEADER_CONNECTOR_J7_D42       // Pin not routed
#define HEADER_CONNECTOR_J7_D47       // Pin not routed
#define HEADER_CONNECTOR_J7_D48       // Pin not routed
#define HEADER_CONNECTOR_J7_D53       // Pin not routed
#define HEADER_CONNECTOR_J7_D54       // Pin not routed
#define HEADER_CONNECTOR_J7_D107      // Pin not routed
#define HEADER_CONNECTOR_J7_D108      // Pin not routed
#define HEADER_CONNECTOR_J7_D119      // Pin not routed
#define HEADER_CONNECTOR_J7_D120      // Pin not routed

// EEPROM
#define EEPROM_D1   GPIO_PA1
#define EEPROM_D2   GPIO_PC4
#define EEPROM_D3   // Pin not routed
#define EEPROM_D4   // Pin not routed
#define EEPROM_D5   GPIO_PC5
#define EEPROM_D6   GPIO_PC3
#define EEPROM_D7   // Pin not routed
#define EEPROM_D8   // Pin not routed

// USB INTERFACE
#define USB_TX      GPIO_PC6
#define USB_RX      GPIO_PC7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
