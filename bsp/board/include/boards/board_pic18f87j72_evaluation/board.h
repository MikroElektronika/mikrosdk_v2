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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.5/new_hw/2025-07-08.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "PIC18F87J72 Evaluation Board"

#include "hal_target.h"

// Mapping
// HEADER J2
#define HEADER_CONNECTOR_J2_D1        // Pin not routed
#define HEADER_CONNECTOR_J2_D2        // Pin not routed
#define HEADER_CONNECTOR_J2_D3        // Pin not routed
#define HEADER_CONNECTOR_J2_D4        GPIO_PB7
#define HEADER_CONNECTOR_J2_D5        GPIO_PB6
#define HEADER_CONNECTOR_J2_D6        // Pin not routed

// PICTAIL HEADER J7
#define HEADER_CONNECTOR_J7_D1        GPIO_PE2
#define HEADER_CONNECTOR_J7_D2        GPIO_PA5
#define HEADER_CONNECTOR_J7_D3        GPIO_PE3
#define HEADER_CONNECTOR_J7_D4        GPIO_PA4
#define HEADER_CONNECTOR_J7_D5        GPIO_PA7
#define HEADER_CONNECTOR_J7_D6        GPIO_PA3
#define HEADER_CONNECTOR_J7_D7        GPIO_PA6
#define HEADER_CONNECTOR_J7_D8        // Pin not routed
#define HEADER_CONNECTOR_J7_D9        GPIO_PC7
#define HEADER_CONNECTOR_J7_D10       GPIO_PC4
#define HEADER_CONNECTOR_J7_D11       GPIO_PC6
#define HEADER_CONNECTOR_J7_D12       GPIO_PC3
#define HEADER_CONNECTOR_J7_D13       GPIO_PB7
#define HEADER_CONNECTOR_J7_D14       GPIO_PA0
#define HEADER_CONNECTOR_J7_D15       GPIO_PB6
#define HEADER_CONNECTOR_J7_D16       GPIO_PA1
#define HEADER_CONNECTOR_J7_D17       GPIO_PB5
#define HEADER_CONNECTOR_J7_D18       GPIO_PA2
#define HEADER_CONNECTOR_J7_D19       GPIO_PB4
#define HEADER_CONNECTOR_J7_D20       GPIO_PC0
#define HEADER_CONNECTOR_J7_D21       GPIO_PB3
#define HEADER_CONNECTOR_J7_D22       GPIO_PC1
#define HEADER_CONNECTOR_J7_D23       GPIO_PB2
#define HEADER_CONNECTOR_J7_D24       GPIO_PC2
#define HEADER_CONNECTOR_J7_D25       GPIO_PB1
#define HEADER_CONNECTOR_J7_D26       // Pin not routed
#define HEADER_CONNECTOR_J7_D27       // Pin not routed
#define HEADER_CONNECTOR_J7_D28       // Pin not routed

// PICTAIL HEADER J8
#define HEADER_CONNECTOR_J8_D1        GPIO_PD1
#define HEADER_CONNECTOR_J8_D2        GPIO_PD0
#define HEADER_CONNECTOR_J8_D3        GPIO_PD3
#define HEADER_CONNECTOR_J8_D4        GPIO_PD2
#define HEADER_CONNECTOR_J8_D5        GPIO_PD5
#define HEADER_CONNECTOR_J8_D6        GPIO_PD4
#define HEADER_CONNECTOR_J8_D7        GPIO_PD7
#define HEADER_CONNECTOR_J8_D8        GPIO_PD6
#define HEADER_CONNECTOR_J8_D9        GPIO_PE1
#define HEADER_CONNECTOR_J8_D10       GPIO_PE0
#define HEADER_CONNECTOR_J8_D11       // Pin not routed
#define HEADER_CONNECTOR_J8_D12       // Pin not routed

// LCD Display
#define DISPLAY_CONNECTOR_DC1_D1      GPIO_PF2
#define DISPLAY_CONNECTOR_DC1_D2      GPIO_PF3
#define DISPLAY_CONNECTOR_DC1_D3      GPIO_PF4
#define DISPLAY_CONNECTOR_DC1_D4      GPIO_PG4
#define DISPLAY_CONNECTOR_DC1_D5      GPIO_PD5
#define DISPLAY_CONNECTOR_DC1_D6      GPIO_PF1
#define DISPLAY_CONNECTOR_DC1_D7      GPIO_PD7
#define DISPLAY_CONNECTOR_DC1_D8      GPIO_PE7
#define DISPLAY_CONNECTOR_DC1_D9      GPIO_PB2
#define DISPLAY_CONNECTOR_DC1_D10     GPIO_PD6
#define DISPLAY_CONNECTOR_DC1_D11     GPIO_PA4
#define DISPLAY_CONNECTOR_DC1_D12     GPIO_PD4
#define DISPLAY_CONNECTOR_DC1_D13     GPIO_PD1
#define DISPLAY_CONNECTOR_DC1_D14     GPIO_PD2
#define DISPLAY_CONNECTOR_DC1_D15     GPIO_PD3
#define DISPLAY_CONNECTOR_DC1_D16     GPIO_PB4
#define DISPLAY_CONNECTOR_DC1_D17     GPIO_PB5
#define DISPLAY_CONNECTOR_DC1_D18     GPIO_PB1
#define DISPLAY_CONNECTOR_DC1_D19     GPIO_PE3
#define DISPLAY_CONNECTOR_DC1_D20     GPIO_PE4
#define DISPLAY_CONNECTOR_DC1_D21     GPIO_PE5
#define DISPLAY_CONNECTOR_DC1_D22     GPIO_PE6

// CAPACITIVE TOUCH BUTTONS
#define BUTTON1     GPIO_PA2
#define BUTTON2     GPIO_PA3
#define BUTTON3     GPIO_PA5
#define BUTTON4     GPIO_PF7

// TEMPERATURE SENSOR
#define TEMP_VOUT   GPIO_PA1

// USB INTERFACE
#define USB_TXD     GPIO_PC6
#define USB_RXD     GPIO_PC7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
