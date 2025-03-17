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

#define BOARD_NAME "32-bit Multimedia Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_HDR1_D1     // Pin not routed
#define HEADER_CONNECTOR_HDR1_D2     // Pin not routed
#define HEADER_CONNECTOR_HDR1_D3     PE0
#define HEADER_CONNECTOR_HDR1_D4     PE1
#define HEADER_CONNECTOR_HDR1_D5     PE2
#define HEADER_CONNECTOR_HDR1_D6     PE3
#define HEADER_CONNECTOR_HDR1_D7     PE4
#define HEADER_CONNECTOR_HDR1_D8     PE5
#define HEADER_CONNECTOR_HDR1_D9     PE6
#define HEADER_CONNECTOR_HDR1_D10    PE7
#define HEADER_CONNECTOR_HDR1_D11    PG0
#define HEADER_CONNECTOR_HDR1_D12    PG1
#define HEADER_CONNECTOR_HDR1_D13    PF1
#define HEADER_CONNECTOR_HDR1_D14    PF0
#define HEADER_CONNECTOR_HDR1_D15    PD12
#define HEADER_CONNECTOR_HDR1_D16    PD13
#define HEADER_CONNECTOR_HDR1_D17    PD6
#define HEADER_CONNECTOR_HDR1_D18    PD7
#define HEADER_CONNECTOR_HDR1_D19    PD5
#define HEADER_CONNECTOR_HDR1_D20    PD4
#define HEADER_CONNECTOR_HDR1_D21    PB3
#define HEADER_CONNECTOR_HDR1_D22    PB2
#define HEADER_CONNECTOR_HDR1_D23    PB1
#define HEADER_CONNECTOR_HDR1_D24    PB0
#define HEADER_CONNECTOR_HDR1_D25    PA10
#define HEADER_CONNECTOR_HDR1_D26    PA9
#define HEADER_CONNECTOR_HDR1_D27    PB4
#define HEADER_CONNECTOR_HDR1_D28    PB5
#define HEADER_CONNECTOR_HDR1_D29    // Pin not routed
#define HEADER_CONNECTOR_HDR1_D30    // Pin not routed

#define HEADER_CONNECTOR_HDR2_D1     // Pin not routed
#define HEADER_CONNECTOR_HDR2_D2     // Pin not routed
#define HEADER_CONNECTOR_HDR2_D3     PB9
#define HEADER_CONNECTOR_HDR2_D4     PB14
#define HEADER_CONNECTOR_HDR2_D5     PB3
#define HEADER_CONNECTOR_HDR2_D6     PD11
#define HEADER_CONNECTOR_HDR2_D7     PE9
#define HEADER_CONNECTOR_HDR2_D8     PG12
#define HEADER_CONNECTOR_HDR2_D9     PG13
#define HEADER_CONNECTOR_HDR2_D10    PG14
#define HEADER_CONNECTOR_HDR2_D11    PG15
#define HEADER_CONNECTOR_HDR2_D12    PF2
#define HEADER_CONNECTOR_HDR2_D13    PF8
#define HEADER_CONNECTOR_HDR2_D14    PD14
#define HEADER_CONNECTOR_HDR2_D15    PD15
#define HEADER_CONNECTOR_HDR2_D16    PF4
#define HEADER_CONNECTOR_HDR2_D17    PF5
#define HEADER_CONNECTOR_HDR2_D18    // Pin not routed
#define HEADER_CONNECTOR_HDR2_D19    PA14
#define HEADER_CONNECTOR_HDR2_D20    PA15
#define HEADER_CONNECTOR_HDR2_D21    PA2
#define HEADER_CONNECTOR_HDR2_D22    PA3
#define HEADER_CONNECTOR_HDR2_D23    PC4
#define HEADER_CONNECTOR_HDR2_D24    PD0
#define HEADER_CONNECTOR_HDR2_D25    PD10
#define HEADER_CONNECTOR_HDR2_D26    PG7
#define HEADER_CONNECTOR_HDR2_D27    PG8
#define HEADER_CONNECTOR_HDR2_D28    PG6
#define HEADER_CONNECTOR_HDR2_D29    // Pin not routed
#define HEADER_CONNECTOR_HDR2_D30    // Pin not routed

// TFT
#define TFT_LED_A1  // Pin not routed
#define TFT_LED_A2  // Pin not routed
#define TFT_LED_A3  // Pin not routed
#define TFT_LED_A4  // Pin not routed
#define TFT_IM0     // Pin not routed
#define TFT_IM1     // Pin not routed
#define TFT_IM2     // Pin not routed
#define TFT_IM3     // Pin not routed
#define TFT_RESET   RB15
#define TFT_VSYNC   // Pin not routed
#define TFT_HSYNC   // Pin not routed
#define TFT_DOTCLK  // Pin not routed
#define TFT_ENABLE  // Pin not routed
#define TFT_DB17    PD7
#define TFT_DB16    PD6
#define TFT_DB15    PD13
#define TFT_DB14    PD12
#define TFT_DB13    RF0
#define TFT_DB12    RF1
#define TFT_DB11    RG1
#define TFT_DB10    RG0
#define TFT_DB9     // Pin not routed
#define TFT_DB8     RE7
#define TFT_DB7     RE6
#define TFT_DB6     RE5
#define TFT_DB5     RE4
#define TFT_DB4     RE3
#define TFT_DB3     RE2
#define TFT_DB2     RE1
#define TFT_DB1     RE0
#define TFT_DB0     // Pin not routed
#define TFT_SDO     // Pin not routed
#define TFT_SDI     // Pin not routed
#define TFT_RD      RD5
#define TFT_WR_SCL  RD4
#define TFT_RS      RB15
#define TFT_CS      RF12
#define TFT_FMARK   // Pin not routed
#define TFT_VCC_IO  // Pin not routed
#define TFT_VCC     // Pin not routed
#define TFT_VCC_I   // Pin not routed
#define TFT_GND     // Pin not routed
#define TFT_XR      RB11
#define TFT_YD      RB10
#define TFT_XL      RB13
#define TFT_YU      RB12

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
