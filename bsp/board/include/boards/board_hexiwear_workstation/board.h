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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Hexiwear Workstation"

#include "mikrobus.h"

/// Mapping
#define PIN_GROUP_0 true
#define PIN_G00 PC2
#define PIN_G01 PB6
#define PIN_G02 PB10
#define PIN_G03 PA4
#define PIN_G04 PB7
#define PIN_G05 PE2
#define PIN_G06 PE3
#define PIN_G07 PE1

#define PIN_GROUP_1 true
#define PIN_G10 PE0
#define PIN_G11 PE5
#define PIN_G12 PE4
#define PIN_G13 PD3
#define PIN_G14 PD2
#define PIN_G15 PC17
#define PIN_G16 PC16
#define PIN_G17 PA17

#define PIN_GROUP_2 true
#define PIN_G20 PA15
#define PIN_G21 PA16
#define PIN_G22 PA14
#define PIN_G23 PA12
#define PIN_G24 PA13
#define PIN_G25 PA5
#define PIN_G26 PC5
#define PIN_G27 PC7

#define PIN_GROUP_3 true
#define PIN_G30 PC6
#define PIN_G31 PB17
#define PIN_G32 PB16
#define PIN_G33 PD8
#define PIN_G34 PD9
#define PIN_G35 PC4
#define PIN_G36 PB2
#define PIN_G37 PB11

#define PIN_GROUP_4 true
#define PIN_G40 PA10
#define PIN_G41 PB13
#define PIN_G42 PC3
#define PIN_G43 PB3
#define PIN_G44 PB19
#define PIN_G45 PA11
#define PIN_G46 PB8

#define MIKROBUS_1 1
#define MIKROBUS_1_AN PIN_G36
#define MIKROBUS_1_RST PIN_G37
#define MIKROBUS_1_CS PIN_G35
#define MIKROBUS_1_SCK PIN_G26
#define MIKROBUS_1_MISO PIN_G27
#define MIKROBUS_1_MOSI PIN_G30
#define MIKROBUS_1_PWM PIN_G40
#define MIKROBUS_1_INT PIN_G41
#define MIKROBUS_1_RX PIN_G14
#define MIKROBUS_1_TX PIN_G13
#define MIKROBUS_1_SCL PIN_G33
#define MIKROBUS_1_SDA PIN_G34

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PIN_G43
#define MIKROBUS_2_RST PIN_G44
#define MIKROBUS_2_CS PIN_G42
#define MIKROBUS_2_SCK PIN_G26
#define MIKROBUS_2_MISO PIN_G27
#define MIKROBUS_2_MOSI PIN_G30
#define MIKROBUS_2_PWM PIN_G45
#define MIKROBUS_2_INT PIN_G46
#define MIKROBUS_2_RX PIN_G14
#define MIKROBUS_2_TX PIN_G13
#define MIKROBUS_2_SCL PIN_G33
#define MIKROBUS_2_SDA PIN_G34

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PIN_G01
#define MIKROBUS_3_RST PIN_G02
#define MIKROBUS_3_CS PIN_G00
#define MIKROBUS_3_SCK PIN_G26
#define MIKROBUS_3_MISO PIN_G27
#define MIKROBUS_3_MOSI PIN_G30
#define MIKROBUS_3_PWM PIN_G03
#define MIKROBUS_3_INT PIN_G04
#define MIKROBUS_3_RX PIN_G16
#define MIKROBUS_3_TX PIN_G15
#define MIKROBUS_3_SCL PIN_G23
#define MIKROBUS_3_SDA PIN_G24

#define MIKROBUS_4 4
#define MIKROBUS_4_AN PIN_G17
#define MIKROBUS_4_RST PIN_G21
#define MIKROBUS_4_CS PIN_G22
#define MIKROBUS_4_SCK PIN_G26
#define MIKROBUS_4_MISO PIN_G27
#define MIKROBUS_4_MOSI PIN_G30
#define MIKROBUS_4_PWM PIN_G25
#define MIKROBUS_4_INT PIN_G20
#define MIKROBUS_4_RX PIN_G16
#define MIKROBUS_4_TX PIN_G15
#define MIKROBUS_4_SCL PIN_G23
#define MIKROBUS_4_SDA PIN_G24

#define PROTO_HEADER_G00 PC2
#define PROTO_HEADER_G01 PB6
#define PROTO_HEADER_G02 PB10
#define PROTO_HEADER_G03 PA4
#define PROTO_HEADER_G04 PB7
#define PROTO_HEADER_G05 PE2
#define PROTO_HEADER_G06 PE3
#define PROTO_HEADER_G07 PE1
#define PROTO_HEADER_G10 PE0
#define PROTO_HEADER_G11 PE5
#define PROTO_HEADER_G12 PE4
#define PROTO_HEADER_G13 PD3
#define PROTO_HEADER_G14 PD2
#define PROTO_HEADER_G15 PC17
#define PROTO_HEADER_G16 PC16
#define PROTO_HEADER_G17 PA17
#define PROTO_HEADER_G20 PA15
#define PROTO_HEADER_G21 PA16
#define PROTO_HEADER_G22 PA14
#define PROTO_HEADER_G23 PA12
#define PROTO_HEADER_G24 PA13
#define PROTO_HEADER_G25 PA5
#define PROTO_HEADER_G26 PC5
#define PROTO_HEADER_G27 PC7
#define PROTO_HEADER_G30 PC6
#define PROTO_HEADER_G31 PB17
#define PROTO_HEADER_G32 PB16
#define PROTO_HEADER_G33 PD8
#define PROTO_HEADER_G34 PD9
#define PROTO_HEADER_G35 PC4
#define PROTO_HEADER_G36 PB2
#define PROTO_HEADER_G37 PB11
#define PROTO_HEADER_G40 PA10
#define PROTO_HEADER_G41 PB13
#define PROTO_HEADER_G42 PC3
#define PROTO_HEADER_G43 PB3
#define PROTO_HEADER_G44 PB19
#define PROTO_HEADER_G45 PA11
#define PROTO_HEADER_G46 PB8

// Buttons
#define BUTTON_T1 PIN_G07
#define BUTTON_T2 PIN_G06
#define BUTTON_T3 PIN_G05
#define BUTTON_T4 PIN_G04
#define BUTTON_T5 PIN_G03
#define BUTTON_T6 PIN_G02
#define BUTTON_T7 PIN_G01
#define BUTTON_T8 PIN_G00

#define BUTTON_T9 PIN_G17
#define BUTTON_T10 PIN_G16
#define BUTTON_T11 PIN_G15
#define BUTTON_T12 PIN_G14
#define BUTTON_T13 PIN_G13
#define BUTTON_T14 PIN_G12
#define BUTTON_T15 PIN_G11
#define BUTTON_T16 PIN_G10

#define BUTTON_T19 PIN_G27
#define BUTTON_T20 PIN_G26
#define BUTTON_T21 PIN_G25
#define BUTTON_T22 PIN_G24
#define BUTTON_T23 PIN_G23
#define BUTTON_T24 PIN_G22
#define BUTTON_T25 PIN_G21
#define BUTTON_T26 PIN_G20

#define BUTTON_T27 PIN_G37
#define BUTTON_T28 PIN_G36
#define BUTTON_T29 PIN_G35
#define BUTTON_T30 PIN_G34
#define BUTTON_T31 PIN_G33
#define BUTTON_T32 PIN_G32
#define BUTTON_T33 PIN_G31
#define BUTTON_T34 PIN_G30

#define BUTTON_T35 PIN_G46
#define BUTTON_T36 PIN_G45
#define BUTTON_T37 PIN_G44
#define BUTTON_T38 PIN_G43
#define BUTTON_T39 PIN_G42
#define BUTTON_T40 PIN_G41
#define BUTTON_T41 PIN_G40
// EOF Buttons

// MP3 Connections
#define MP3_SCK PIN_G26
#define MP3_MISO PIN_G27
#define MP3_MOSI PIN_G30
#define MP3_CS PIN_G22
#define MP3_DCS PIN_G17
#define MP3_DREQ PIN_G20
#define MP3_RST PIN_G21
// EOF MP3 Connections

// SD Card Connections
#define SDHC_CLK PIN_G05
#define SDHC_CMD PIN_G06
#define SDHC_DAT0 PIN_G07
#define SDHC_DAT1 PIN_G10
#define SDHC_DAT2 PIN_G11
#define SDHC_DAT3 PIN_G12
// EOF SD Card Connections

// Analog input
#define ANALOG_INPUT_G01 PIN_G01
#define ANALOG_INPUT_G17 PIN_G17
#define ANALOG_INPUT_G36 PIN_G36
#define ANALOG_INPUT_G43 PIN_G43
// EOF Analog input

// DS1820
#define DS1820_G03 PIN_G03
#define DS1820_G45 PIN_G45
// EOF DS1820

// LM35
// Only on boards version 1.00
#if (BOARD_REV_MINOR == 00)
#define LM35_G01 PIN_G01
#define LM35_G43 PIN_G43
#endif
// EOF LM35

// Buzzer
#define BUZZER PG4
// EOF Buzzer

// No TFT connector on board
#define TFT_8BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

// USB Uart connections
#define USB_UART_RX PIN_G31
#define USB_UART_TX PIN_G32
// EOF USB Uart connections

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
