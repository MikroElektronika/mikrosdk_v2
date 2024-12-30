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

#define BOARD_NAME "SAM E70 XPLAINED EVALUATION KIT"

#include "hal_target.h"

// Mapping
// EXTENSION HEADER EXT1
#define HEADER_CONNECTOR_EXT1_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT1_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT1_D3      GPIO_PC31
#define HEADER_CONNECTOR_EXT1_D4      GPIO_PA19
#define HEADER_CONNECTOR_EXT1_D5      GPIO_PB3
#define HEADER_CONNECTOR_EXT1_D6      GPIO_PB2
#define HEADER_CONNECTOR_EXT1_D7      GPIO_PA0
#define HEADER_CONNECTOR_EXT1_D8      GPIO_PC30
#define HEADER_CONNECTOR_EXT1_D9      GPIO_PD28
#define HEADER_CONNECTOR_EXT1_D10     GPIO_PC17
#define HEADER_CONNECTOR_EXT1_D11     GPIO_PA3
#define HEADER_CONNECTOR_EXT1_D12     GPIO_PA4
#define HEADER_CONNECTOR_EXT1_D13     GPIO_PB0
#define HEADER_CONNECTOR_EXT1_D14     GPIO_PB1
#define HEADER_CONNECTOR_EXT1_D15     GPIO_PD25
#define HEADER_CONNECTOR_EXT1_D16     GPIO_PD21
#define HEADER_CONNECTOR_EXT1_D17     GPIO_PD20
#define HEADER_CONNECTOR_EXT1_D18     GPIO_PD22
#define HEADER_CONNECTOR_EXT1_D19     // Pin not routed
#define HEADER_CONNECTOR_EXT1_D20     // Pin not routed

// EXTENSION HEADER EXT2
#define HEADER_CONNECTOR_EXT2_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT2_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT2_D3      GPIO_PD30
#define HEADER_CONNECTOR_EXT2_D4      GPIO_PC13
#define HEADER_CONNECTOR_EXT2_D5      GPIO_PA6
#define HEADER_CONNECTOR_EXT2_D6      GPIO_PD11
#define HEADER_CONNECTOR_EXT2_D7      GPIO_PC19
#define HEADER_CONNECTOR_EXT2_D8      GPIO_PD26
#define HEADER_CONNECTOR_EXT2_D9      GPIO_PA2
#define HEADER_CONNECTOR_EXT2_D10     GPIO_PA24
#define HEADER_CONNECTOR_EXT2_D11     GPIO_PA3
#define HEADER_CONNECTOR_EXT2_D12     GPIO_PA4
#define HEADER_CONNECTOR_EXT2_D13     GPIO_PA21
#define HEADER_CONNECTOR_EXT2_D14     GPIO_PB4
#define HEADER_CONNECTOR_EXT2_D15     GPIO_PB3
#define HEADER_CONNECTOR_EXT2_D16     GPIO_PD21
#define HEADER_CONNECTOR_EXT2_D17     GPIO_PD20
#define HEADER_CONNECTOR_EXT2_D18     GPIO_PD22
#define HEADER_CONNECTOR_EXT2_D19     // Pin not routed
#define HEADER_CONNECTOR_EXT2_D20     // Pin not routed

// J400 CAMERA CONNECTOR
#define HEADER_CONNECTOR_J400_D1      // Pin not routed
#define HEADER_CONNECTOR_J400_D2      // Pin not routed
#define HEADER_CONNECTOR_J400_D3      // Pin not routed
#define HEADER_CONNECTOR_J400_D4      // Pin not routed
#define HEADER_CONNECTOR_J400_D5      GPIO_PA13
#define HEADER_CONNECTOR_J400_D6      GPIO_PC19
#define HEADER_CONNECTOR_J400_D7      GPIO_PA4
#define HEADER_CONNECTOR_J400_D8      GPIO_PA3
#define HEADER_CONNECTOR_J400_D9      // Pin not routed
#define HEADER_CONNECTOR_J400_D10     GPIO_PA6
#define HEADER_CONNECTOR_J400_D11     // Pin not routed
#define HEADER_CONNECTOR_J400_D12     GPIO_PD25
#define HEADER_CONNECTOR_J400_D13     // Pin not routed
#define HEADER_CONNECTOR_J400_D14     GPIO_PD24
#define HEADER_CONNECTOR_J400_D15     // Pin not routed
#define HEADER_CONNECTOR_J400_D16     GPIO_PA24
#define HEADER_CONNECTOR_J400_D17     // Pin not routed
#define HEADER_CONNECTOR_J400_D18     GPIO_PD22
#define HEADER_CONNECTOR_J400_D19     GPIO_PD21
#define HEADER_CONNECTOR_J400_D20     GPIO_PB3
#define HEADER_CONNECTOR_J400_D21     GPIO_PA9
#define HEADER_CONNECTOR_J400_D22     GPIO_PA5
#define HEADER_CONNECTOR_J400_D23     GPIO_PD11
#define HEADER_CONNECTOR_J400_D24     GPIO_PD12
#define HEADER_CONNECTOR_J400_D25     GPIO_PA27
#define HEADER_CONNECTOR_J400_D26     GPIO_PD27
#define HEADER_CONNECTOR_J400_D27     GPIO_PD28
#define HEADER_CONNECTOR_J400_D28     GPIO_PD30
#define HEADER_CONNECTOR_J400_D29     GPIO_PD31
#define HEADER_CONNECTOR_J400_D30     // Pin not routed

// J500 HEADER
#define HEADER_CONNECTOR_J500_D1      GPIO_PA17
#define HEADER_CONNECTOR_J500_D2      GPIO_PC9
#define HEADER_CONNECTOR_J500_D3      GPIO_PD25
#define HEADER_CONNECTOR_J500_D4      GPIO_PD21
#define HEADER_CONNECTOR_J500_D5      GPIO_PD20
#define HEADER_CONNECTOR_J500_D6      GPIO_PD22
#define HEADER_CONNECTOR_J500_D7      // Pin not routed
#define HEADER_CONNECTOR_J500_D8      // Pin not routed
#define HEADER_CONNECTOR_J500_D9      GPIO_PA3
#define HEADER_CONNECTOR_J500_D10     GPIO_PA4

// J501 HEADER
#define HEADER_CONNECTOR_J501_D1      // Pin not routed
#define HEADER_CONNECTOR_J501_D2      // Pin not routed
#define HEADER_CONNECTOR_J501_D3      // Pin not routed
#define HEADER_CONNECTOR_J501_D4      // Pin not routed
#define HEADER_CONNECTOR_J501_D5      // Pin not routed
#define HEADER_CONNECTOR_J501_D6      // Pin not routed
#define HEADER_CONNECTOR_J501_D7      // Pin not routed
#define HEADER_CONNECTOR_J501_D8      // Pin not routed

// J502 HEADER
#define HEADER_CONNECTOR_J502_D1      GPIO_PD26
#define HEADER_CONNECTOR_J502_D2      GPIO_PC31
#define HEADER_CONNECTOR_J502_D3      GPIO_PD30
#define HEADER_CONNECTOR_J502_D4      GPIO_PA19
#define HEADER_CONNECTOR_J502_D5      GPIO_PC13
#define HEADER_CONNECTOR_J502_D6      GPIO_PC30
#define HEADER_CONNECTOR_J502_D7      GPIO_PA17
#define HEADER_CONNECTOR_J502_D8      GPIO_PC12

// J503 HEADER
#define HEADER_CONNECTOR_J503_D1      GPIO_PD28
#define HEADER_CONNECTOR_J503_D2      GPIO_PD30
#define HEADER_CONNECTOR_J503_D3      GPIO_PA5
#define HEADER_CONNECTOR_J503_D4      GPIO_PA6
#define HEADER_CONNECTOR_J503_D5      GPIO_PD27
#define HEADER_CONNECTOR_J503_D6      GPIO_PD11
#define HEADER_CONNECTOR_J503_D7      GPIO_PC19
#define HEADER_CONNECTOR_J503_D8      GPIO_PA2

// J504 HEADER
#define HEADER_CONNECTOR_J504_D1      GPIO_PD24
#define HEADER_CONNECTOR_J504_D2      GPIO_PA10
#define HEADER_CONNECTOR_J504_D3      GPIO_PA22
#define HEADER_CONNECTOR_J504_D4      GPIO_PC31
#define HEADER_CONNECTOR_J504_D5      GPIO_PB13
#define HEADER_CONNECTOR_J504_D6      GPIO_PD0
#define HEADER_CONNECTOR_J504_D7      GPIO_PB3
#define HEADER_CONNECTOR_J504_D8      GPIO_PB2

// J505 HEADER
#define HEADER_CONNECTOR_J505_D1      GPIO_PD28
#define HEADER_CONNECTOR_J505_D2      GPIO_PB0
#define HEADER_CONNECTOR_J505_D3      GPIO_PD18
#define HEADER_CONNECTOR_J505_D4      GPIO_PD19
#define HEADER_CONNECTOR_J505_D5      GPIO_PD15
#define HEADER_CONNECTOR_J505_D6      GPIO_PD16
#define HEADER_CONNECTOR_J505_D7      GPIO_PB0
#define HEADER_CONNECTOR_J505_D8      GPIO_PB1

// J506 HEADER
#define HEADER_CONNECTOR_J506_D1      GPIO_PD20
#define HEADER_CONNECTOR_J506_D2      // Pin not routed
#define HEADER_CONNECTOR_J506_D3      GPIO_PD22
#define HEADER_CONNECTOR_J506_D4      GPIO_PD21
#define HEADER_CONNECTOR_J506_D5      // Pin not routed
#define HEADER_CONNECTOR_J506_D6      // Pin not routed

// J507 HEADER
#define HEADER_CONNECTOR_J507_D1      // Pin not routed
#define HEADER_CONNECTOR_J507_D2      // Pin not routed
#define HEADER_CONNECTOR_J507_D3      GPIO_PA18
#define HEADER_CONNECTOR_J507_D4      GPIO_PB1
#define HEADER_CONNECTOR_J507_D5      GPIO_PB0
#define HEADER_CONNECTOR_J507_D6      GPIO_PD17
#define HEADER_CONNECTOR_J507_D7      GPIO_PD19
#define HEADER_CONNECTOR_J507_D8      GPIO_PD18
#define HEADER_CONNECTOR_J507_D9      GPIO_PA5
#define HEADER_CONNECTOR_J507_D10     // Pin not routed
#define HEADER_CONNECTOR_J507_D11     GPIO_PA29
#define HEADER_CONNECTOR_J507_D12     GPIO_PA1
#define HEADER_CONNECTOR_J507_D13     // Pin not routed
#define HEADER_CONNECTOR_J507_D14     GPIO_PA26
#define HEADER_CONNECTOR_J507_D15     // Pin not routed
#define HEADER_CONNECTOR_J507_D16     GPIO_PA12
#define HEADER_CONNECTOR_J507_D17     GPIO_PA13
#define HEADER_CONNECTOR_J507_D18     // Pin not routed
#define HEADER_CONNECTOR_J507_D19     GPIO_PB13
#define HEADER_CONNECTOR_J507_D20     GPIO_PB2
#define HEADER_CONNECTOR_J507_D21     GPIO_PB3
#define HEADER_CONNECTOR_J507_D22     GPIO_PA31
#define HEADER_CONNECTOR_J507_D23     // Pin not routed
#define HEADER_CONNECTOR_J507_D24     GPIO_PA23
#define HEADER_CONNECTOR_J507_D25     GPIO_PA25
#define HEADER_CONNECTOR_J507_D26     GPIO_PA24
#define HEADER_CONNECTOR_J507_D27     GPIO_PA21
#define HEADER_CONNECTOR_J507_D28     GPIO_PB4
#define HEADER_CONNECTOR_J507_D29     GPIO_PA30
#define HEADER_CONNECTOR_J507_D30     GPIO_PA28
#define HEADER_CONNECTOR_J507_D31     GPIO_PA18
#define HEADER_CONNECTOR_J507_D32     // Pin not routed
#define HEADER_CONNECTOR_J507_D33     GPIO_PC12
#define HEADER_CONNECTOR_J507_D34     GPIO_PC14
#define HEADER_CONNECTOR_J507_D35     // Pin not routed
#define HEADER_CONNECTOR_J507_D36     // Pin not routed

// LEDS
#define LED1    GPIO_PC8

// BUTTONS
#define BUTTON1 GPIO_PA11

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END