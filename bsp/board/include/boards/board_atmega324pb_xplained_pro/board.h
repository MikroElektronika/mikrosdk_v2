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

#define BOARD_NAME "ATMEGA324PB XPLAINED PRO"

#include "hal_target.h"

// Mapping
// EXTENSION HEADER EXT1
#define HEADER_CONNECTOR_EXT1_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT1_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT1_D3      GPIO_PA0
#define HEADER_CONNECTOR_EXT1_D4      GPIO_PA1
#define HEADER_CONNECTOR_EXT1_D5      GPIO_PA2
#define HEADER_CONNECTOR_EXT1_D6      GPIO_PA3
#define HEADER_CONNECTOR_EXT1_D7      GPIO_PD5
#define HEADER_CONNECTOR_EXT1_D8      GPIO_PD4
#define HEADER_CONNECTOR_EXT1_D9      GPIO_PC1
#define HEADER_CONNECTOR_EXT1_D10     GPIO_PC0
#define HEADER_CONNECTOR_EXT1_D11     GPIO_PE5
#define HEADER_CONNECTOR_EXT1_D12     GPIO_PE6
#define HEADER_CONNECTOR_EXT1_D13     GPIO_PD0
#define HEADER_CONNECTOR_EXT1_D14     GPIO_PD1
#define HEADER_CONNECTOR_EXT1_D15     GPIO_PB4
#define HEADER_CONNECTOR_EXT1_D16     GPIO_PB5
#define HEADER_CONNECTOR_EXT1_D17     GPIO_PB6
#define HEADER_CONNECTOR_EXT1_D18     GPIO_PB7
#define HEADER_CONNECTOR_EXT1_D19     // Pin not routed
#define HEADER_CONNECTOR_EXT1_D20     // Pin not routed

// EXTENSION HEADER EXT3
#define HEADER_CONNECTOR_EXT3_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT3_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT3_D3      GPIO_PC5
#define HEADER_CONNECTOR_EXT3_D4      GPIO_PC7
#define HEADER_CONNECTOR_EXT3_D5      GPIO_PE4
#define HEADER_CONNECTOR_EXT3_D6      GPIO_PC2
#define HEADER_CONNECTOR_EXT3_D7      GPIO_PC4
#define HEADER_CONNECTOR_EXT3_D8      GPIO_PC3
#define HEADER_CONNECTOR_EXT3_D9      GPIO_PC6
#define HEADER_CONNECTOR_EXT3_D10     GPIO_PB1
#define HEADER_CONNECTOR_EXT3_D11     GPIO_PE5
#define HEADER_CONNECTOR_EXT3_D12     GPIO_PE6
#define HEADER_CONNECTOR_EXT3_D13     GPIO_PD2
#define HEADER_CONNECTOR_EXT3_D14     GPIO_PD3
#define HEADER_CONNECTOR_EXT3_D15     GPIO_PD6
#define HEADER_CONNECTOR_EXT3_D16     GPIO_PB5
#define HEADER_CONNECTOR_EXT3_D17     GPIO_PB6
#define HEADER_CONNECTOR_EXT3_D18     GPIO_PB7
#define HEADER_CONNECTOR_EXT3_D19     // Pin not routed
#define HEADER_CONNECTOR_EXT3_D20     // Pin not routed

// EXTENSION HEADER EXT4
#define HEADER_CONNECTOR_EXT4_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT4_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT4_D3      GPIO_PA4
#define HEADER_CONNECTOR_EXT4_D4      GPIO_PA5
#define HEADER_CONNECTOR_EXT4_D5      GPIO_PA6
#define HEADER_CONNECTOR_EXT4_D6      GPIO_PA7
#define HEADER_CONNECTOR_EXT4_D7      GPIO_PB3
#define HEADER_CONNECTOR_EXT4_D8      GPIO_PE4
#define HEADER_CONNECTOR_EXT4_D9      GPIO_PB2
#define HEADER_CONNECTOR_EXT4_D10     GPIO_PD7
#define HEADER_CONNECTOR_EXT4_D11     GPIO_PE5
#define HEADER_CONNECTOR_EXT4_D12     GPIO_PE6
#define HEADER_CONNECTOR_EXT4_D13     GPIO_PE2
#define HEADER_CONNECTOR_EXT4_D14     GPIO_PE3
#define HEADER_CONNECTOR_EXT4_D15     GPIO_PB0
#define HEADER_CONNECTOR_EXT4_D16     GPIO_PB5
#define HEADER_CONNECTOR_EXT4_D17     GPIO_PB6
#define HEADER_CONNECTOR_EXT4_D18     GPIO_PB7
#define HEADER_CONNECTOR_EXT4_D19     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D20     // Pin not routed

// ANALOG COMPARATOR HEADER
#define HEADER_CONNECTOR_AC_D1        GPIO_PB2
#define HEADER_CONNECTOR_AC_D2        GPIO_PB3
#define HEADER_CONNECTOR_AC_D3        GPIO_PC5
#define HEADER_CONNECTOR_AC_D4        // Pin not routed
#define HEADER_CONNECTOR_AC_D5        // Pin not routed

// DGI GPIO HEADER
#define HEADER_CONNECTOR_DGI_D1       GPIO_PB4
#define HEADER_CONNECTOR_DGI_D2       GPIO_PB2
#define HEADER_CONNECTOR_DGI_D3       GPIO_PC1
#define HEADER_CONNECTOR_DGI_D4       GPIO_PC6
#define HEADER_CONNECTOR_DGI_D5       // Pin not routed

// LEDS
#define LED1    GPIO_PC7

// BUTTONS
#define BUTTON1 GPIO_PC6


#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END