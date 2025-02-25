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

#define BOARD_NAME "Digilent Cerebot 32MX7 Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       PB2
#define HEADER_CONNECTOR_CN1_D2       PB3
#define HEADER_CONNECTOR_CN1_D3       PB4
#define HEADER_CONNECTOR_CN1_D4       PB6
#define HEADER_CONNECTOR_CN1_D7       PB7
#define HEADER_CONNECTOR_CN1_D8       PB8
#define HEADER_CONNECTOR_CN1_D9       PB9
#define HEADER_CONNECTOR_CN1_D10      PB10

#define HEADER_CONNECTOR_CN2_D1       PE0
#define HEADER_CONNECTOR_CN2_D2       PE1
#define HEADER_CONNECTOR_CN2_D3       PE2
#define HEADER_CONNECTOR_CN2_D4       PE3
#define HEADER_CONNECTOR_CN2_D7       PE4
#define HEADER_CONNECTOR_CN2_D8       PE5
#define HEADER_CONNECTOR_CN2_D9       PE6
#define HEADER_CONNECTOR_CN2_D10      PE7

#define HEADER_CONNECTOR_CN3_D1       PC1
#define HEADER_CONNECTOR_CN3_D2       PG0
#define HEADER_CONNECTOR_CN3_D3       PG1
#define HEADER_CONNECTOR_CN3_D4       PD7
#define HEADER_CONNECTOR_CN3_D7       PB15
#define HEADER_CONNECTOR_CN3_D8       PD5
#define HEADER_CONNECTOR_CN3_D9       PD4
#define HEADER_CONNECTOR_CN3_D10      PB14

#define HEADER_CONNECTOR_CN4_D1       PD9
#define HEADER_CONNECTOR_CN4_D2       PD0
#define HEADER_CONNECTOR_CN4_D3       PC4
#define HEADER_CONNECTOR_CN4_D4       PD10
#define HEADER_CONNECTOR_CN4_D7       PD1
#define HEADER_CONNECTOR_CN4_D8       PD2
#define HEADER_CONNECTOR_CN4_D9       PD3
#define HEADER_CONNECTOR_CN4_D10      PD12

#define HEADER_CONNECTOR_CN5_D1       PD14
#define HEADER_CONNECTOR_CN5_D2       PF8
#define HEADER_CONNECTOR_CN5_D3       PF2
#define HEADER_CONNECTOR_CN5_D4       PD15
#define HEADER_CONNECTOR_CN5_D7       PA6
#define HEADER_CONNECTOR_CN5_D8       PA7
#define HEADER_CONNECTOR_CN5_D9       PA9
#define HEADER_CONNECTOR_CN5_D10      PA10

#define HEADER_CONNECTOR_CN6_D1       PF12
#define HEADER_CONNECTOR_CN6_D2       PF5
#define HEADER_CONNECTOR_CN6_D3       PF4
#define HEADER_CONNECTOR_CN6_D4       PF13
#define HEADER_CONNECTOR_CN6_D7       PA0
#define HEADER_CONNECTOR_CN6_D8       PA1
#define HEADER_CONNECTOR_CN6_D9       PA4
#define HEADER_CONNECTOR_CN6_D10      PA5

// I2C
#define I2C_SCL1    PA14
#define I2C_SDA1    PA15
#define I2C_SCL2    PA2
#define I2C_SDA2    PA3

// USB
#define USB_VBUSON      PB5
#define USB_OVCURRENT   PE8
#define USB_USBID       PF3
#define USB_DP          PG2
#define USB_DM          PG3

// ETHERNET
#define ETH_RXER    PB11
#define ETH_RXD0    PB12
#define ETH_RXD1    PB13
#define ETH_TXEN    PD6
#define ETH_MDIO    PD8
#define ETH_MDC     PD11
#define ETH_RST     PE9
#define ETH_TXD1    PF0
#define ETH_TXD0    PF1
#define ETH_CRS_DV  PG8
#define ETH_CLK     PG9

// CAN
#define CAN2_TX PC2
#define CAN2_RX PC3
#define CAN1_RX PF12
#define CAN1_TX PF13

// OSCILLATOR
#define OSC_OSC1    PC12
#define OSC_SOSCI   PC13
#define OSC_SOSCO   PC14
#define OSC_OSC2    PC15

// BUTTONS
#define BUTTON_1    PG6
#define BUTTON_2    PG7
#define BUTTON_3    PD13

// LEDS
#define LED_1   PG12
#define LED_2   PG13
#define LED_3   PG14
#define LED_4   PG15



#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
