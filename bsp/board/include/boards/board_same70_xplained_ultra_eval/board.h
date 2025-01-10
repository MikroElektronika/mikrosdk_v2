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

#define BOARD_NAME "SAM E70 XPLAINED ULTRA EVALUATION KIT"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1                   1
#define MIKROBUS_1_AN                GPIO_PC31
#define MIKROBUS_1_RST               GPIO_PD11
#define MIKROBUS_1_CS                GPIO_PA5
#define MIKROBUS_1_SCK               GPIO_PD22
#define MIKROBUS_1_MISO              GPIO_PD20
#define MIKROBUS_1_MOSI              GPIO_PD21
#define MIKROBUS_1_PWM               GPIO_PA0
#define MIKROBUS_1_INT               GPIO_PD28
#define MIKROBUS_1_RX                GPIO_PB0
#define MIKROBUS_1_TX                GPIO_PB1
#define MIKROBUS_1_SCL               GPIO_PA4
#define MIKROBUS_1_SDA               GPIO_PA3

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

// J501 HEADER
#define HEADER_CONNECTOR_J501_D1      GPIO_PD26
#define HEADER_CONNECTOR_J501_D2      GPIO_PC31
#define HEADER_CONNECTOR_J501_D3      GPIO_PD30
#define HEADER_CONNECTOR_J501_D4      GPIO_PA19
#define HEADER_CONNECTOR_J501_D5      GPIO_PC13
#define HEADER_CONNECTOR_J501_D6      GPIO_PC30
#define HEADER_CONNECTOR_J501_D7      GPIO_PA17
#define HEADER_CONNECTOR_J501_D8      GPIO_PC12

// J502 HEADER
#define HEADER_CONNECTOR_J502_D1      GPIO_PD24
#define HEADER_CONNECTOR_J502_D2      GPIO_PA10
#define HEADER_CONNECTOR_J502_D3      GPIO_PA22
#define HEADER_CONNECTOR_J502_D4      GPIO_PC31
#define HEADER_CONNECTOR_J502_D5      GPIO_PB13
#define HEADER_CONNECTOR_J502_D6      GPIO_PD0
#define HEADER_CONNECTOR_J502_D7      GPIO_PB3
#define HEADER_CONNECTOR_J502_D8      GPIO_PB2

// J503 HEADER
#define HEADER_CONNECTOR_J503_D1      GPIO_PD20
#define HEADER_CONNECTOR_J503_D2      // Pin not routed
#define HEADER_CONNECTOR_J503_D3      GPIO_PD22
#define HEADER_CONNECTOR_J503_D4      GPIO_PD21
#define HEADER_CONNECTOR_J503_D5      // Pin not routed
#define HEADER_CONNECTOR_J503_D6      // Pin not routed

// J504 HEADER
#define HEADER_CONNECTOR_J504_D1      // Pin not routed
#define HEADER_CONNECTOR_J504_D2
#define HEADER_CONNECTOR_J504_D3      GPIO_PA18
#define HEADER_CONNECTOR_J504_D4      GPIO_PB1
#define HEADER_CONNECTOR_J504_D5      GPIO_PB0
#define HEADER_CONNECTOR_J504_D6      GPIO_PD17
#define HEADER_CONNECTOR_J504_D7      GPIO_PD19
#define HEADER_CONNECTOR_J504_D8      GPIO_PD18
#define HEADER_CONNECTOR_J504_D9      GPIO_PA5
#define HEADER_CONNECTOR_J504_D10     // Pin not routed
#define HEADER_CONNECTOR_J504_D11     GPIO_PA29
#define HEADER_CONNECTOR_J504_D12     GPIO_PA1
#define HEADER_CONNECTOR_J504_D13     // Pin not routed
#define HEADER_CONNECTOR_J504_D14     GPIO_PA26
#define HEADER_CONNECTOR_J504_D15     // Pin not routed
#define HEADER_CONNECTOR_J504_D16     GPIO_PA12
#define HEADER_CONNECTOR_J504_D17     GPIO_PA13
#define HEADER_CONNECTOR_J504_D18     // Pin not routed
#define HEADER_CONNECTOR_J504_D19     GPIO_PB13
#define HEADER_CONNECTOR_J504_D20     GPIO_PB2
#define HEADER_CONNECTOR_J504_D21     GPIO_PB3
#define HEADER_CONNECTOR_J504_D22     GPIO_PA31
#define HEADER_CONNECTOR_J504_D23     // Pin not routed
#define HEADER_CONNECTOR_J504_D24     GPIO_PA23
#define HEADER_CONNECTOR_J504_D25     GPIO_PA25
#define HEADER_CONNECTOR_J504_D26     GPIO_PA24
#define HEADER_CONNECTOR_J504_D27     GPIO_PA21
#define HEADER_CONNECTOR_J504_D28     GPIO_PB4
#define HEADER_CONNECTOR_J504_D29     GPIO_PA30
#define HEADER_CONNECTOR_J504_D30     GPIO_PA28
#define HEADER_CONNECTOR_J504_D31     GPIO_PA18
#define HEADER_CONNECTOR_J504_D32     // Pin not routed
#define HEADER_CONNECTOR_J504_D33     GPIO_PC12
#define HEADER_CONNECTOR_J504_D34     GPIO_PC14
#define HEADER_CONNECTOR_J504_D35     // Pin not routed
#define HEADER_CONNECTOR_J504_D36     // Pin not routed

// J505 HEADER
#define HEADER_CONNECTOR_J505_D1      GPIO_PA17
#define HEADER_CONNECTOR_J505_D2      GPIO_PC9
#define HEADER_CONNECTOR_J505_D3      GPIO_PD25
#define HEADER_CONNECTOR_J505_D4      GPIO_PD21
#define HEADER_CONNECTOR_J505_D5      GPIO_PD20
#define HEADER_CONNECTOR_J505_D6      GPIO_PD22
#define HEADER_CONNECTOR_J505_D7      // Pin not routed
#define HEADER_CONNECTOR_J505_D8      // Pin not routed
#define HEADER_CONNECTOR_J505_D9      GPIO_PA3
#define HEADER_CONNECTOR_J505_D10     GPIO_PA4

// J506 HEADER
#define HEADER_CONNECTOR_J506_D1      GPIO_PD28
#define HEADER_CONNECTOR_J506_D2      GPIO_PD30
#define HEADER_CONNECTOR_J506_D3      GPIO_PA5
#define HEADER_CONNECTOR_J506_D4      GPIO_PA6
#define HEADER_CONNECTOR_J506_D5      GPIO_PD27
#define HEADER_CONNECTOR_J506_D6      GPIO_PD11
#define HEADER_CONNECTOR_J506_D7      GPIO_PC19
#define HEADER_CONNECTOR_J506_D8      GPIO_PA2

// J507 HEADER
#define HEADER_CONNECTOR_J507_D1      GPIO_PD28
#define HEADER_CONNECTOR_J507_D2      GPIO_PD27
#define HEADER_CONNECTOR_J507_D3      GPIO_PD18
#define HEADER_CONNECTOR_J507_D4      GPIO_PD19
#define HEADER_CONNECTOR_J507_D5      GPIO_PD15
#define HEADER_CONNECTOR_J507_D6      GPIO_PD16
#define HEADER_CONNECTOR_J507_D7      GPIO_PB0
#define HEADER_CONNECTOR_J507_D8      GPIO_PB1

// ARM JTAG HEADER J600
#define HEADER_CONNECTOR_J600_D1      // Pin not routed
#define HEADER_CONNECTOR_J600_D2      // Pin not routed
#define HEADER_CONNECTOR_J600_D3      // Pin not routed
#define HEADER_CONNECTOR_J600_D4      // Pin not routed
#define HEADER_CONNECTOR_J600_D5      NC/// Pin not routed
#define HEADER_CONNECTOR_J600_D6      // Pin not routed
#define HEADER_CONNECTOR_J600_D7      GPIO_PB6
#define HEADER_CONNECTOR_J600_D8      // Pin not routed
#define HEADER_CONNECTOR_J600_D9      GPIO_PB7
#define HEADER_CONNECTOR_J600_D10     // Pin not routed
#define HEADER_CONNECTOR_J600_D11     // Pin not routed
#define HEADER_CONNECTOR_J600_D12     // Pin not routed
#define HEADER_CONNECTOR_J600_D13     GPIO_PB5
#define HEADER_CONNECTOR_J600_D14     // Pin not routed
#define HEADER_CONNECTOR_J600_D15     // Pin not routed
#define HEADER_CONNECTOR_J600_D16     // Pin not routed
#define HEADER_CONNECTOR_J600_D17     // Pin not routed
#define HEADER_CONNECTOR_J600_D18     // Pin not routed
#define HEADER_CONNECTOR_J600_D19     // Pin not routed
#define HEADER_CONNECTOR_J600_D20     // Pin not routed

// EXTENSION HEADER EXT1 J602
#define HEADER_CONNECTOR_J602_D1      // Pin not routed
#define HEADER_CONNECTOR_J602_D2      // Pin not routed
#define HEADER_CONNECTOR_J602_D3      GPIO_PC31
#define HEADER_CONNECTOR_J602_D4      GPIO_PA19
#define HEADER_CONNECTOR_J602_D5      GPIO_PB3
#define HEADER_CONNECTOR_J602_D6      GPIO_PB2
#define HEADER_CONNECTOR_J602_D7      GPIO_PA0
#define HEADER_CONNECTOR_J602_D8      GPIO_PC30
#define HEADER_CONNECTOR_J602_D9      GPIO_PD28
#define HEADER_CONNECTOR_J602_D10     GPIO_PC17
#define HEADER_CONNECTOR_J602_D11     GPIO_PA3
#define HEADER_CONNECTOR_J602_D12     GPIO_PA4
#define HEADER_CONNECTOR_J602_D13     GPIO_PB0
#define HEADER_CONNECTOR_J602_D14     GPIO_PB1
#define HEADER_CONNECTOR_J602_D15     GPIO_PD25
#define HEADER_CONNECTOR_J602_D16     GPIO_PD21
#define HEADER_CONNECTOR_J602_D17     GPIO_PD20
#define HEADER_CONNECTOR_J602_D18     GPIO_PD22
#define HEADER_CONNECTOR_J602_D19     // Pin not routed
#define HEADER_CONNECTOR_J602_D20     // Pin not routed

// TRACE (CORESIGHT 20) HEADER J603
#define HEADER_CONNECTOR_J603_D1     // Pin not routed
#define HEADER_CONNECTOR_J603_D2     GPIO_PB6
#define HEADER_CONNECTOR_J603_D3     // Pin not routed
#define HEADER_CONNECTOR_J603_D4     GPIO_PB7
#define HEADER_CONNECTOR_J603_D5     // Pin not routed
#define HEADER_CONNECTOR_J603_D6     GPIO_PB5
#define HEADER_CONNECTOR_J603_D8     // Pin not routed
#define HEADER_CONNECTOR_J603_D9     // Pin not routed
#define HEADER_CONNECTOR_J603_D10    // Pin not routed
#define HEADER_CONNECTOR_J603_D11     // Pin not routed
#define HEADER_CONNECTOR_J603_D12    GPIO_PD8
#define HEADER_CONNECTOR_J603_D13    // Pin not routed
#define HEADER_CONNECTOR_J603_D14    GPIO_PD4
#define HEADER_CONNECTOR_J603_D15    // Pin not routed
#define HEADER_CONNECTOR_J603_D16    GPIO_PD5
#define HEADER_CONNECTOR_J603_D17    // Pin not routed
#define HEADER_CONNECTOR_J603_D18    GPIO_PD6
#define HEADER_CONNECTOR_J603_D19    // Pin not routed
#define HEADER_CONNECTOR_J603_D20    GPIO_PD7

// EXTENSION HEADER EXT2  J604
#define HEADER_CONNECTOR_J604_D1      // Pin not routed
#define HEADER_CONNECTOR_J604_D2      // Pin not routed
#define HEADER_CONNECTOR_J604_D3      GPIO_PD30
#define HEADER_CONNECTOR_J604_D4      GPIO_PC13
#define HEADER_CONNECTOR_J604_D5      GPIO_PA6
#define HEADER_CONNECTOR_J604_D6      GPIO_PD11
#define HEADER_CONNECTOR_J604_D7      GPIO_PC19
#define HEADER_CONNECTOR_J604_D8      GPIO_PD26
#define HEADER_CONNECTOR_J604_D9      GPIO_PA2
#define HEADER_CONNECTOR_J604_D10     GPIO_PA24
#define HEADER_CONNECTOR_J604_D11     GPIO_PA3
#define HEADER_CONNECTOR_J604_D12     GPIO_PA4
#define HEADER_CONNECTOR_J604_D13     GPIO_PA21
#define HEADER_CONNECTOR_J604_D14     GPIO_PB4
#define HEADER_CONNECTOR_J604_D15     GPIO_PD27
#define HEADER_CONNECTOR_J604_D16     GPIO_PD21
#define HEADER_CONNECTOR_J604_D17     GPIO_PD20
#define HEADER_CONNECTOR_J604_D18     GPIO_PD22
#define HEADER_CONNECTOR_J604_D19     // Pin not routed
#define HEADER_CONNECTOR_J604_D20     // Pin not routed

// ETHERNET PHY HEADER J800
#define HEADER_CONNECTOR_J800_D1     GPIO_PA02
#define HEADER_CONNECTOR_J800_D2     GPIO_PD28
#define HEADER_CONNECTOR_J800_D3     GPIO_PD6
#define HEADER_CONNECTOR_J800_D4     GPIO_PD5
#define HEADER_CONNECTOR_J800_D5     GPIO_PD7
#define HEADER_CONNECTOR_J800_D6     GPIO_PD4
#define HEADER_CONNECTOR_J800_D7     GPIO_PD8
#define HEADER_CONNECTOR_J800_D8     GPIO_PD9
#define HEADER_CONNECTOR_J800_D9     GPIO_PA29
#define HEADER_CONNECTOR_J800_D10    GPIO_PC10
#define HEADER_CONNECTOR_J800_D11    GPIO_PA19
#define HEADER_CONNECTOR_J800_D12    // Pin not routed

// ETHERNET PHY HEADER J802
#define HEADER_CONNECTOR_J802_D1     GPIO_PD01
#define HEADER_CONNECTOR_J802_D2     GPIO_PD02
#define HEADER_CONNECTOR_J802_D3     GPIO_PD03
#define HEADER_CONNECTOR_J802_D4     GPIO_PD21
#define HEADER_CONNECTOR_J802_D5     GPIO_PD20
#define HEADER_CONNECTOR_J802_D6     // Pin not routed
#define HEADER_CONNECTOR_J802_D7     // Pin not routed
#define HEADER_CONNECTOR_J802_D8     GPIO_PD0
#define HEADER_CONNECTOR_J802_D9     // Pin not routed
#define HEADER_CONNECTOR_J802_D10    // Pin not routed
#define HEADER_CONNECTOR_J802_D11    GPIO_PC19
#define HEADER_CONNECTOR_J802_D12    GPIO_PD22

// X32 HEADER J902
#define HEADER_CONNECTOR_J902_D1     // Pin not routed
#define HEADER_CONNECTOR_J902_D2     // Pin not routed
#define HEADER_CONNECTOR_J902_D3     GPIO_PB0
#define HEADER_CONNECTOR_J902_D4     GPIO_PB2
#define HEADER_CONNECTOR_J902_D5     GPIO_PB1
#define HEADER_CONNECTOR_J902_D6     GPIO_PB3
#define HEADER_CONNECTOR_J902_D7     GPIO_PA4
#define HEADER_CONNECTOR_J902_D8     GPIO_PD11
#define HEADER_CONNECTOR_J902_D9     GPIO_PA3
#define HEADER_CONNECTOR_J902_D10    GPIO_PD24
#define HEADER_CONNECTOR_J902_D11    GPIO_PA10
#define HEADER_CONNECTOR_J902_D12    GPIO_PB1
#define HEADER_CONNECTOR_J902_D13    GPIO_PD26
#define HEADER_CONNECTOR_J902_D14    GPIO_PA18
#define HEADER_CONNECTOR_J902_D15    // Pin not routed
#define HEADER_CONNECTOR_J902_D16    // Pin not routed
#define HEADER_CONNECTOR_J902_D17    // Pin not routed
#define HEADER_CONNECTOR_J902_D18    // Pin not routed
#define HEADER_CONNECTOR_J902_D19    // Pin not routed
#define HEADER_CONNECTOR_J902_D20    // Pin not routed

// X32 HEADER J903
#define HEADER_CONNECTOR_J902_D1     GPIO_PE0
#define HEADER_CONNECTOR_J902_D2     GPIO_PD30
#define HEADER_CONNECTOR_J902_D3     GPIO_PA20
#define HEADER_CONNECTOR_J902_D4     // Pin not routed
#define HEADER_CONNECTOR_J902_D5     GPIO_PE2
#define HEADER_CONNECTOR_J902_D6     // Pin not routed
#define HEADER_CONNECTOR_J902_D7     GPIO_PE1
#define HEADER_CONNECTOR_J902_D8     // Pin not routed
#define HEADER_CONNECTOR_J902_D9     GPIO_PA19
#define HEADER_CONNECTOR_J902_D10    // Pin not routed
#define HEADER_CONNECTOR_J902_D11    // Pin not routed
#define HEADER_CONNECTOR_J902_D12    // Pin not routed

// PIC32 GFX CONNECTOR J1000
#define HEADER_CONNECTOR_J1000_D1    // Pin not routed
#define HEADER_CONNECTOR_J1000_D2    // Pin not routed
#define HEADER_CONNECTOR_J1000_D3    // Pin not routed
#define HEADER_CONNECTOR_J1000_D4    GPIO_PD28
#define HEADER_CONNECTOR_J1000_D5    // Pin not routed
#define HEADER_CONNECTOR_J1000_D6    GPIO_PA2
#define HEADER_CONNECTOR_J1000_D7    GPIO_PC11
#define HEADER_CONNECTOR_J1000_D8    GPIO_PD28
#define HEADER_CONNECTOR_J1000_D9    GPIO_PC30
#define HEADER_CONNECTOR_J1000_D10   GPIO_PA6
#define HEADER_CONNECTOR_J1000_D11   GPIO_PD19
#define HEADER_CONNECTOR_J1000_D12   // Pin not routed
#define HEADER_CONNECTOR_J1000_D13   GPIO_PC8
#define HEADER_CONNECTOR_J1000_D14   GPIO_PA3
#define HEADER_CONNECTOR_J1000_D15   GPIO_PC0
#define HEADER_CONNECTOR_J1000_D16   GPIO_PA4
#define HEADER_CONNECTOR_J1000_D17   GPIO_PC1
#define HEADER_CONNECTOR_J1000_D18   GPIO_PD22
#define HEADER_CONNECTOR_J1000_D19   GPIO_PC2
#define HEADER_CONNECTOR_J1000_D20   GPIO_PD21
#define HEADER_CONNECTOR_J1000_D21   GPIO_PC3
#define HEADER_CONNECTOR_J1000_D22   GPIO_PD20
#define HEADER_CONNECTOR_J1000_D23   GPIO_PC4
#define HEADER_CONNECTOR_J1000_D24   GPIO_PD25
#define HEADER_CONNECTOR_J1000_D25   GPIO_PC5
#define HEADER_CONNECTOR_J1000_D26   // Pin not routed
#define HEADER_CONNECTOR_J1000_D27   GPIO_PC6
#define HEADER_CONNECTOR_J1000_D28   // Pin not routed
#define HEADER_CONNECTOR_J1000_D29   GPIO_PC7
#define HEADER_CONNECTOR_J1000_D30   // Pin not routed
#define HEADER_CONNECTOR_J1000_D31   GPIO_PE0
#define HEADER_CONNECTOR_J1000_D32   // Pin not routed
#define HEADER_CONNECTOR_J1000_D33   GPIO_PE1
#define HEADER_CONNECTOR_J1000_D34   GPIO_PC9
#define HEADER_CONNECTOR_J1000_D35   GPIO_PE2
#define HEADER_CONNECTOR_J1000_D36   GPIO_PD19
#define HEADER_CONNECTOR_J1000_D37   GPIO_PE3
#define HEADER_CONNECTOR_J1000_D38   GPIO_PD11
#define HEADER_CONNECTOR_J1000_D39   GPIO_PE4
#define HEADER_CONNECTOR_J1000_D40   // Pin not routed
#define HEADER_CONNECTOR_J1000_D41   GPIO_PE5
#define HEADER_CONNECTOR_J1000_D42   // Pin not routed
#define HEADER_CONNECTOR_J1000_D43   GPIO_PA15
#define HEADER_CONNECTOR_J1000_D44   GPIO_PC13
#define HEADER_CONNECTOR_J1000_D45   GPIO_PA16
#define HEADER_CONNECTOR_J1000_D46   // Pin not routed
#define HEADER_CONNECTOR_J1000_D47   // Pin not routed
#define HEADER_CONNECTOR_J1000_D48   // Pin not routed
#define HEADER_CONNECTOR_J1000_D49   // Pin not routed
#define HEADER_CONNECTOR_J1000_D50   GPIO_PD30
#define HEADER_CONNECTOR_J1000_D51   // Pin not routed
#define HEADER_CONNECTOR_J1000_D52   GPIO_PA21
#define HEADER_CONNECTOR_J1000_D53   // Pin not routed
#define HEADER_CONNECTOR_J1000_D54   GPIO_PC31
#define HEADER_CONNECTOR_J1000_D55   // Pin not routed
#define HEADER_CONNECTOR_J1000_D56   GPIO_PC13
#define HEADER_CONNECTOR_J1000_D57   // Pin not routed
#define HEADER_CONNECTOR_J1000_D58   // Pin not routed
#define HEADER_CONNECTOR_J1000_D59   // Pin not routed
#define HEADER_CONNECTOR_J1000_D60   // Pin not routed
#define HEADER_CONNECTOR_J1000_D61   // Pin not routed
#define HEADER_CONNECTOR_J1000_D62   // Pin not routed
#define HEADER_CONNECTOR_J1000_D63   // Pin not routed
#define HEADER_CONNECTOR_J1000_D64   // Pin not routed
#define HEADER_CONNECTOR_J1000_D65   // Pin not routed
#define HEADER_CONNECTOR_J1000_D66   // Pin not routed
#define HEADER_CONNECTOR_J1000_D67   // Pin not routed

// SERIAL EEPROM
#define EEPROM_WP                    GPIO_PC11
#define EEPROM_SDA                   GPIO_PA3
#define EEPROM_SCL                   GPIO_PA4

// MICROSD CARD
#define MICROSD_D0                   GPIO_PA30
#define MICROSD_D1                   GPIO_PA31
#define MICROSD_D2                   GPIO_PA26
#define MICROSD_D3                   GPIO_PA27
#define MICROSD_CLK                  GPIO_PA25
#define MICROSD_CMD                  GPIO_PA28
#define MICROSD_SWA                  GPIO_PC16

// SDRAM
#define SDRAM_A0                     GPIO_PC20
#define SDRAM_A1                     GPIO_PC21
#define SDRAM_A2                     GPIO_PC22
#define SDRAM_A3                     GPIO_PC23
#define SDRAM_A4                     GPIO_PC24
#define SDRAM_A5                     GPIO_PC25
#define SDRAM_A6                     GPIO_PC26
#define SDRAM_A7                     GPIO_PC27
#define SDRAM_A8                     GPIO_PC28
#define SDRAM_A9                     GPIO_PC29
#define SDRAM_A10                    GPIO_PD13
#define SDRAM_A11                    GPIO_PA20
#define SDRAM_CLK                    GPIO_PD23
#define SDRAM_CKE                    GPIO_PD14
#define SDRAM_CS                     GPIO_PD15
#define SDRAM_RAS                    GPIO_PD16
#define SDRAM_CAS                    GPIO_PD17
#define SDRAM_WE                     GPIO_PD29
#define SDRAM_LDQM                   GPIO_PC18
#define SDRAM_UDQM                   GPIO_PD15
#define SDRAM_DQ0                    GPIO_PC0
#define SDRAM_DQ1                    GPIO_PC1
#define SDRAM_DQ2                    GPIO_PC2
#define SDRAM_DQ3                    GPIO_PC3
#define SDRAM_DQ4                    GPIO_PC4
#define SDRAM_DQ5                    GPIO_PC5
#define SDRAM_DQ6                    GPIO_PC6
#define SDRAM_DQ7                    GPIO_PC7
#define SDRAM_DQ8                    GPIO_PE0
#define SDRAM_DQ9                    GPIO_PE1
#define SDRAM_DQ10                   GPIO_PE2
#define SDRAM_DQ11                   GPIO_PE3
#define SDRAM_DQ12                   GPIO_PE4
#define SDRAM_DQ13                   GPIO_PE5
#define SDRAM_DQ14                   GPIO_PA15
#define SDRAM_DQ15                   GPIO_PA16

// FLASH
#define FLASH_SI                     GPIO_PA13
#define FLASH_SO                     GPIO_PA12
#define FLASH_WP                     GPIO_PA17
#define FLASH_HOLD                   GPIO_PD31
#define FLASH_SCK                    GPIO_PA14
#define FLASH_CS                     GPIO_PA11

// LEDS
#define LED1    GPIO_PA5

// BUTTONS
#define BUTTON1 GPIO_PA11

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END