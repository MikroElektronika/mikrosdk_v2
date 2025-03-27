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

#define BOARD_NAME "PIC32 Audio Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1               PD0
#define HEADER_CONNECTOR_CN1_D2               PC13
#define HEADER_CONNECTOR_CN1_D3               PC14
#define HEADER_CONNECTOR_CN1_S1               PD3
#define HEADER_CONNECTOR_CN1_S2               PD2
#define HEADER_CONNECTOR_CN1_S3               PD1
#define HEADER_CONNECTOR_CN1_S4               PD12
#define HEADER_CONNECTOR_CN1_MCLR             // Pin not routed
#define HEADER_CONNECTOR_CN1_SELECT           PE9
#define HEADER_CONNECTOR_CN1_ACC              PB4
#define HEADER_CONNECTOR_CN1_OVERCURRENT      PB0
#define HEADER_CONNECTOR_CN1_PGC              PB6
#define HEADER_CONNECTOR_CN1_PGD              PB7
#define HEADER_CONNECTOR_CN1_RXD              PF13
#define HEADER_CONNECTOR_CN1_TXD              PF12
#define HEADER_CONNECTOR_CN1_VBUS             // Pin not routed
#define HEADER_CONNECTOR_CN1_D_NEG            PG3
#define HEADER_CONNECTOR_CN1_D_POS            PG2
#define HEADER_CONNECTOR_CN1_VCAP             // Pin not routed
#define HEADER_CONNECTOR_CN1_ACC_PWR          PE8
#define HEADER_CONNECTOR_CN1_ACC_ID_SEL0      PB3
#define HEADER_CONNECTOR_CN1_ACC_ID_SEL1      PB2
#define HEADER_CONNECTOR_CN1_SDA              PF2
#define HEADER_CONNECTOR_CN1_SCL              PF8
#define HEADER_CONNECTOR_CN1_SCL2             PA2
#define HEADER_CONNECTOR_CN1_SDA2             PA3
#define HEADER_CONNECTOR_CN1_C_RESET          PD14
#define HEADER_CONNECTOR_CN1_IPOD_DETECT      PD15

// LCD
#define LCD_DB5     PE5
#define LCD_DB6     PE6
#define LCD_DB7     PE7
#define LCD_RESET   PC1
#define LCD_D_C     PB15
#define LCD_CS      PD11
#define LCD_WR      PD4
#define LCD_RD      PD5
#define LCD_DB0     PE0
#define LCD_DB1     PE1
#define LCD_DB2     PE2
#define LCD_DB3     PE3
#define LCD_DB4     PE4

// CODEC
#define CODEC_BCLK      PG6
#define CODEC_ADCDAT    PG7
#define CODEC_DACDAT    PG8
#define CODEC_DACLRC    PG9

// USB
#define USB_OVERCURRENT PB1
#define USB_VBUSON      PB5

// COMM
#define USB_UART_RX PF4
#define USB_UART_TX PF5

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
