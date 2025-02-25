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

#define BOARD_NAME "SAM V71 XPLAINED ULTRA EVALUATION KIT"

#include "mikrobus.h"

// Mapping
// EXTENSION HEADER EXT1 J602
#define HEADER_CONNECTOR_EXT1_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT1_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT1_D3      GPIO_PC31
#define HEADER_CONNECTOR_EXT1_D4      GPIO_PA19
#define HEADER_CONNECTOR_EXT1_D5      GPIO_PB3
#define HEADER_CONNECTOR_EXT1_D6      GPIO_PB2
#define HEADER_CONNECTOR_EXT1_D7      GPIO_PA0
#define HEADER_CONNECTOR_EXT1_D8      GPIO_PC30
#define HEADER_CONNECTOR_EXT1_D9      GPIO_PD28
#define HEADER_CONNECTOR_EXT1_D10     GPIO_PA05
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
#define HEADER_CONNECTOR_EXT2_D15     GPIO_PD27
#define HEADER_CONNECTOR_EXT2_D16     GPIO_PD21
#define HEADER_CONNECTOR_EXT2_D17     GPIO_PD20
#define HEADER_CONNECTOR_EXT2_D18     GPIO_PD22
#define HEADER_CONNECTOR_EXT2_D19     // Pin not routed
#define HEADER_CONNECTOR_EXT2_D20     // Pin not routed

// EXTENSION CONNECTOR EXT4 - LCD
#define HEADER_CONNECTOR_EXT4_D1      // Pin not routed
#define HEADER_CONNECTOR_EXT4_D2      // Pin not routed
#define HEADER_CONNECTOR_EXT4_D3      GPIO_PC0
#define HEADER_CONNECTOR_EXT4_D4      GPIO_PC1
#define HEADER_CONNECTOR_EXT4_D5      GPIO_PC2
#define HEADER_CONNECTOR_EXT4_D6      GPIO_PC3
#define HEADER_CONNECTOR_EXT4_D7      // Pin not routed
#define HEADER_CONNECTOR_EXT4_D8      GPIO_PC4
#define HEADER_CONNECTOR_EXT4_D9      GPIO_PC5
#define HEADER_CONNECTOR_EXT4_D10     GPIO_PC6
#define HEADER_CONNECTOR_EXT4_D11     GPIO_PC7
#define HEADER_CONNECTOR_EXT4_D12     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D13     GPIO_PE0
#define HEADER_CONNECTOR_EXT4_D14     GPIO_PE1
#define HEADER_CONNECTOR_EXT4_D15     GPIO_PE2
#define HEADER_CONNECTOR_EXT4_D16     GPIO_PE3
#define HEADER_CONNECTOR_EXT4_D17     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D18     GPIO_PE4
#define HEADER_CONNECTOR_EXT4_D19     GPIO_PE5
#define HEADER_CONNECTOR_EXT4_D20     GPIO_PA15
#define HEADER_CONNECTOR_EXT4_D21     GPIO_PA16
#define HEADER_CONNECTOR_EXT4_D22     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D23     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D24     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D25     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D26     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D27     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D28     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D29     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D30     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D31     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D32     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D33     GPIO_PC30
#define HEADER_CONNECTOR_EXT4_D34     GPIO_PD19
#define HEADER_CONNECTOR_EXT4_D35     GPIO_PC8
#define HEADER_CONNECTOR_EXT4_D36     GPIO_PC11
#define HEADER_CONNECTOR_EXT4_D37     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D38     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D39     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D40     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D41     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D42     GPIO_PA3
#define HEADER_CONNECTOR_EXT4_D43     GPIO_PA4
#define HEADER_CONNECTOR_EXT4_D44     GPIO_PD28
#define HEADER_CONNECTOR_EXT4_D45     GPIO_PA2
#define HEADER_CONNECTOR_EXT4_D46     GPIO_PC9
#define HEADER_CONNECTOR_EXT4_D47     GPIO_PC13
#define HEADER_CONNECTOR_EXT4_D48     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D49     // Pin not routed
#define HEADER_CONNECTOR_EXT4_D50     // Pin not routed

// DIGITAL HIGH HEADER J500
#define HEADER_CONNECTOR_J500_D1      GPIO_PA5
#define HEADER_CONNECTOR_J500_D2      GPIO_PC9
#define HEADER_CONNECTOR_J500_D3      GPIO_PD25
#define HEADER_CONNECTOR_J500_D4      GPIO_PD21
#define HEADER_CONNECTOR_J500_D5      GPIO_PD20
#define HEADER_CONNECTOR_J500_D6      GPIO_PD22
#define HEADER_CONNECTOR_J500_D7      // Pin not routed
#define HEADER_CONNECTOR_J500_D8      // Pin not routed
#define HEADER_CONNECTOR_J500_D9      GPIO_PA3
#define HEADER_CONNECTOR_J500_D10     GPIO_PA4

// ANALOG LOW HEADER J502
#define HEADER_CONNECTOR_J502_D1      GPIO_PD26
#define HEADER_CONNECTOR_J502_D2      GPIO_PC31
#define HEADER_CONNECTOR_J502_D3      GPIO_PA19
#define HEADER_CONNECTOR_J502_D4      GPIO_PD30
#define HEADER_CONNECTOR_J502_D5      GPIO_PC13
#define HEADER_CONNECTOR_J502_D6      GPIO_PE0
#define HEADER_CONNECTOR_J502_D7      GPIO_PE3
#define HEADER_CONNECTOR_J502_D8      GPIO_PE4

// DIGITAL LOW HEADER J503
#define HEADER_CONNECTOR_J503_D1      GPIO_PD28
#define HEADER_CONNECTOR_J503_D2      GPIO_PD30
#define HEADER_CONNECTOR_J503_D3      GPIO_PA0
#define HEADER_CONNECTOR_J503_D4      GPIO_PA6
#define HEADER_CONNECTOR_J503_D5      GPIO_PD27
#define HEADER_CONNECTOR_J503_D6      GPIO_PD11
#define HEADER_CONNECTOR_J503_D7      GPIO_PC19
#define HEADER_CONNECTOR_J503_D8      GPIO_PA2

// ANALOG HIGH HEADER J504
#define HEADER_CONNECTOR_J504_D1      GPIO_PD24
#define HEADER_CONNECTOR_J504_D2      GPIO_PA10
#define HEADER_CONNECTOR_J504_D3      GPIO_PA22
#define HEADER_CONNECTOR_J504_D4      GPIO_PE5
#define HEADER_CONNECTOR_J504_D5      GPIO_PB13
#define HEADER_CONNECTOR_J504_D6      GPIO_PD0
#define HEADER_CONNECTOR_J504_D7      GPIO_PB3
#define HEADER_CONNECTOR_J504_D8      GPIO_PB2

// COMMUNICATION HEADER J505
#define HEADER_CONNECTOR_J505_D1      GPIO_PD28
#define HEADER_CONNECTOR_J505_D2      GPIO_PD27
#define HEADER_CONNECTOR_J505_D3      GPIO_PD18
#define HEADER_CONNECTOR_J505_D4      GPIO_PD19
#define HEADER_CONNECTOR_J505_D5      GPIO_PD15
#define HEADER_CONNECTOR_J505_D6      GPIO_PD16
#define HEADER_CONNECTOR_J505_D7      GPIO_PB0
#define HEADER_CONNECTOR_J505_D8      GPIO_PB1

// SPI HEADER J506
#define HEADER_CONNECTOR_J506_D1      GPIO_PD20
#define HEADER_CONNECTOR_J506_D2      // Pin not routed
#define HEADER_CONNECTOR_J506_D3      GPIO_PD22
#define HEADER_CONNECTOR_J506_D4      GPIO_PD21
#define HEADER_CONNECTOR_J506_D5      // Pin not routed
#define HEADER_CONNECTOR_J506_D6      // Pin not routed

// DIGITAL EXTRA HEADER J507
#define HEADER_CONNECTOR_J507_D1      // Pin not routed
#define HEADER_CONNECTOR_J507_D2      // Pin not routed
#define HEADER_CONNECTOR_J507_D3      GPIO_PA18
#define HEADER_CONNECTOR_J507_D4      GPIO_PB1
#define HEADER_CONNECTOR_J507_D5      GPIO_PB0
#define HEADER_CONNECTOR_J507_D6      // Pin not routed
#define HEADER_CONNECTOR_J507_D7      GPIO_PD19
#define HEADER_CONNECTOR_J507_D8      GPIO_PD18
#define HEADER_CONNECTOR_J507_D9      // Pin not routed
#define HEADER_CONNECTOR_J507_D10     // Pin not routed
#define HEADER_CONNECTOR_J507_D11     // Pin not routed
#define HEADER_CONNECTOR_J507_D12     // Pin not routed
#define HEADER_CONNECTOR_J507_D13     // Pin not routed
#define HEADER_CONNECTOR_J507_D14     // Pin not routed
#define HEADER_CONNECTOR_J507_D15     // Pin not routed
#define HEADER_CONNECTOR_J507_D16     // Pin not routed
#define HEADER_CONNECTOR_J507_D17     // Pin not routed
#define HEADER_CONNECTOR_J507_D18     // Pin not routed
#define HEADER_CONNECTOR_J507_D19     // Pin not routed
#define HEADER_CONNECTOR_J507_D20     GPIO_PB2
#define HEADER_CONNECTOR_J507_D21     GPIO_PB3
#define HEADER_CONNECTOR_J507_D22     // Pin not routed
#define HEADER_CONNECTOR_J507_D23     // Pin not routed
#define HEADER_CONNECTOR_J507_D24     // Pin not routed
#define HEADER_CONNECTOR_J507_D25     GPIO_PA25
#define HEADER_CONNECTOR_J507_D26     GPIO_PA24
#define HEADER_CONNECTOR_J507_D27     GPIO_PA21
#define HEADER_CONNECTOR_J507_D28     GPIO_PB4
#define HEADER_CONNECTOR_J507_D29     // Pin not routed
#define HEADER_CONNECTOR_J507_D30     // Pin not routed
#define HEADER_CONNECTOR_J507_D31     // Pin not routed
#define HEADER_CONNECTOR_J507_D32     // Pin not routed
#define HEADER_CONNECTOR_J507_D33     GPIO_PC12
#define HEADER_CONNECTOR_J507_D34     GPIO_PC14
#define HEADER_CONNECTOR_J507_D35     // Pin not routed
#define HEADER_CONNECTOR_J507_D36     // Pin not routed

// MEDIALB CONNECTOR
#define HEADER_CONNECTOR_MLB_D1       // Pin not routed
#define HEADER_CONNECTOR_MLB_D2       GPIO_PB4
#define HEADER_CONNECTOR_MLB_D3       // Pin not routed
#define HEADER_CONNECTOR_MLB_D4       // Pin not routed
#define HEADER_CONNECTOR_MLB_D5       // Pin not routed
#define HEADER_CONNECTOR_MLB_D6       GPIO_PD10
#define HEADER_CONNECTOR_MLB_D7       // Pin not routed
#define HEADER_CONNECTOR_MLB_D8       // Pin not routed
#define HEADER_CONNECTOR_MLB_D9       // Pin not routed
#define HEADER_CONNECTOR_MLB_D10      GPIO_PB5
#define HEADER_CONNECTOR_MLB_D11      // Pin not routed
#define HEADER_CONNECTOR_MLB_D12      // Pin not routed
#define HEADER_CONNECTOR_MLB_D13      // Pin not routed
#define HEADER_CONNECTOR_MLB_D14      // Pin not routed
#define HEADER_CONNECTOR_MLB_D15      // Pin not routed
#define HEADER_CONNECTOR_MLB_D16      GPIO_PA2
#define HEADER_CONNECTOR_MLB_D17      // Pin not routed
#define HEADER_CONNECTOR_MLB_D18      // Pin not routed
#define HEADER_CONNECTOR_MLB_D19      // Pin not routed
#define HEADER_CONNECTOR_MLB_D20      // Pin not routed
#define HEADER_CONNECTOR_MLB_D21      // Pin not routed
#define HEADER_CONNECTOR_MLB_D22      // Pin not routed
#define HEADER_CONNECTOR_MLB_D23      // Pin not routed
#define HEADER_CONNECTOR_MLB_D24      // Pin not routed
#define HEADER_CONNECTOR_MLB_D25      GPIO_PA6
#define HEADER_CONNECTOR_MLB_D26      // Pin not routed
#define HEADER_CONNECTOR_MLB_D27      GPIO_PB3
#define HEADER_CONNECTOR_MLB_D28      // Pin not routed
#define HEADER_CONNECTOR_MLB_D29      // Pin not routed
#define HEADER_CONNECTOR_MLB_D30      // Pin not routed
#define HEADER_CONNECTOR_MLB_D31      // Pin not routed
#define HEADER_CONNECTOR_MLB_D32      // Pin not routed
#define HEADER_CONNECTOR_MLB_D33      GPIO_PA4
#define HEADER_CONNECTOR_MLB_D34      GPIO_PB2
#define HEADER_CONNECTOR_MLB_D35      GPIO_PA3
#define HEADER_CONNECTOR_MLB_D36      // Pin not routed
#define HEADER_CONNECTOR_MLB_D37      // Pin not routed
#define HEADER_CONNECTOR_MLB_D38      // Pin not routed
#define HEADER_CONNECTOR_MLB_D39      // Pin not routed
#define HEADER_CONNECTOR_MLB_D40      // Pin not routed

// CAMERA CONNECTOR
#define HEADER_CONNECTOR_CAM_D1       // Pin not routed
#define HEADER_CONNECTOR_CAM_D2       // Pin not routed
#define HEADER_CONNECTOR_CAM_D3       // Pin not routed
#define HEADER_CONNECTOR_CAM_D4       // Pin not routed
#define HEADER_CONNECTOR_CAM_D5       GPIO_PB13
#define HEADER_CONNECTOR_CAM_D6       GPIO_PC19
#define HEADER_CONNECTOR_CAM_D7       GPIO_PA4
#define HEADER_CONNECTOR_CAM_D8       GPIO_PA3
#define HEADER_CONNECTOR_CAM_D9       // Pin not routed
#define HEADER_CONNECTOR_CAM_D10      GPIO_PA6
#define HEADER_CONNECTOR_CAM_D11      // Pin not routed
#define HEADER_CONNECTOR_CAM_D12      GPIO_PD25
#define HEADER_CONNECTOR_CAM_D13      // Pin not routed
#define HEADER_CONNECTOR_CAM_D14      GPIO_PD24
#define HEADER_CONNECTOR_CAM_D15      // Pin not routed
#define HEADER_CONNECTOR_CAM_D16      GPIO_PA24
#define HEADER_CONNECTOR_CAM_D17      // Pin not routed
#define HEADER_CONNECTOR_CAM_D18      GPIO_PD22
#define HEADER_CONNECTOR_CAM_D19      GPIO_PD21
#define HEADER_CONNECTOR_CAM_D20      GPIO_PB3
#define HEADER_CONNECTOR_CAM_D21      GPIO_PA9
#define HEADER_CONNECTOR_CAM_D22      GPIO_PA5
#define HEADER_CONNECTOR_CAM_D23      GPIO_PD11
#define HEADER_CONNECTOR_CAM_D24      GPIO_PD12
#define HEADER_CONNECTOR_CAM_D25      GPIO_PA27
#define HEADER_CONNECTOR_CAM_D26      GPIO_PD27
#define HEADER_CONNECTOR_CAM_D27      GPIO_PD28
#define HEADER_CONNECTOR_CAM_D28      GPIO_PD30
#define HEADER_CONNECTOR_CAM_D29      GPIO_PD31
#define HEADER_CONNECTOR_CAM_D30      // Pin not routed

// TRACE (CORESIGHT 20) HEADER
#define HEADER_CONNECTOR_CS20_D1      // Pin not routed
#define HEADER_CONNECTOR_CS20_D2      GPIO_PB6
#define HEADER_CONNECTOR_CS20_D3      // Pin not routed
#define HEADER_CONNECTOR_CS20_D4      GPIO_PB7
#define HEADER_CONNECTOR_CS20_D5      // Pin not routed
#define HEADER_CONNECTOR_CS20_D6      GPIO_PB5
#define HEADER_CONNECTOR_CS20_D7      // Pin not routed
#define HEADER_CONNECTOR_CS20_D8      // Pin not routed
#define HEADER_CONNECTOR_CS20_D9      // Pin not routed
#define HEADER_CONNECTOR_CS20_D10     // Pin not routed
#define HEADER_CONNECTOR_CS20_D11      // Pin not routed
#define HEADER_CONNECTOR_CS20_D12     GPIO_PD8
#define HEADER_CONNECTOR_CS20_D13     // Pin not routed
#define HEADER_CONNECTOR_CS20_D14     GPIO_PD4
#define HEADER_CONNECTOR_CS20_D15     // Pin not routed
#define HEADER_CONNECTOR_CS20_D16     GPIO_PD5
#define HEADER_CONNECTOR_CS20_D17     // Pin not routed
#define HEADER_CONNECTOR_CS20_D18     GPIO_PD6
#define HEADER_CONNECTOR_CS20_D19     // Pin not routed
#define HEADER_CONNECTOR_CS20_D20     GPIO_PD7

// CRYPTO FOOTPRINTS
#define CRYPTO_FOOTPRINTS_D1          // Pin not routed
#define CRYPTO_FOOTPRINTS_D2          // Pin not routed
#define CRYPTO_FOOTPRINTS_D3          // Pin not routed
#define CRYPTO_FOOTPRINTS_D4          // Pin not routed
#define CRYPTO_FOOTPRINTS_D5          GPIO_PA3
#define CRYPTO_FOOTPRINTS_D6          GPIO_PA4
#define CRYPTO_FOOTPRINTS_D7          // Pin not routed
#define CRYPTO_FOOTPRINTS_D8          // Pin not routed

// EXTERNAL 32.768KHZ CRYSTAL
#define OSC_KHZ32_XIN32               GPIO_PA7
#define OSC_KHZ32_XOUT32              GPIO_PA8

//EXTERNAL 12MHZ CRYSTAL
#define OSC_MHZ12_XIN                 GPIO_PB9
#define OSC_MHZ12_XOUT                GPIO_PB8

// LEDS
#define LED1        GPIO_PA23
#define LED2        GPIO_PC9

// BUTTONS
#define BUTTON1     GPIO_PA9
#define BUTTON2     GPIO_PB12

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END