/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "EasyPIC v7 for dsPIC30"

#include "dip_socket.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN MIKROBUS_1_DIP_AN
#define MIKROBUS_1_RST MIKROBUS_1_DIP_RST
#define MIKROBUS_1_CS MIKROBUS_1_DIP_CS
#define MIKROBUS_1_SCK MIKROBUS_1_DIP_SCK
#define MIKROBUS_1_MISO MIKROBUS_1_DIP_MISO
#define MIKROBUS_1_MOSI MIKROBUS_1_DIP_MOSI
#define MIKROBUS_1_PWM MIKROBUS_1_DIP_PWM
#define MIKROBUS_1_INT MIKROBUS_1_DIP_INT
#define MIKROBUS_1_RX MIKROBUS_1_DIP_RX
#define MIKROBUS_1_TX MIKROBUS_1_DIP_TX
#define MIKROBUS_1_SCL MIKROBUS_1_DIP_SCL
#define MIKROBUS_1_SDA MIKROBUS_1_DIP_SDA

#define MIKROBUS_2 2
#define MIKROBUS_2_AN MIKROBUS_2_DIP_AN
#define MIKROBUS_2_RST MIKROBUS_2_DIP_RST
#define MIKROBUS_2_CS MIKROBUS_2_DIP_CS
#define MIKROBUS_2_SCK MIKROBUS_2_DIP_SCK
#define MIKROBUS_2_MISO MIKROBUS_2_DIP_MISO
#define MIKROBUS_2_MOSI MIKROBUS_2_DIP_MOSI
#define MIKROBUS_2_PWM MIKROBUS_2_DIP_PWM
#define MIKROBUS_2_INT MIKROBUS_2_DIP_INT
#define MIKROBUS_2_RX MIKROBUS_2_DIP_RX
#define MIKROBUS_2_TX MIKROBUS_2_DIP_TX
#define MIKROBUS_2_SCL MIKROBUS_2_DIP_SCL
#define MIKROBUS_2_SDA MIKROBUS_2_DIP_SDA

#define USB_UART_TX USB_UART_DIP_TX
#define USB_UART_RX USB_UART_DIP_RX

#define TFT_CS1  PB4
#define TFT_CS2  PB5
#define TFT_RS   PF0
#define TFT_R_W  PF1
#define TFT_E    PF4
#define TFT_D0   PB0
#define TFT_D1   PB1
#define TFT_D2   PB2
#define TFT_D3   PB3
#define TFT_D4   PD0
#define TFT_D5   PD1
#define TFT_D6   PD2
#define TFT_D7   PD3
#define TFT_RST  PF5
#define TFT_BPWM PB10

#define TFT_RD TFT_CS1
#define TFT_WR TFT_CS2
#define TFT_CS TFT_E

#define TP_MIKROE_XL PB7
#define TP_MIKROE_XR PC13
#define TP_MIKROE_YU PC14
#define TP_MIKROE_YD PB8

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 120
#define TP_MIKROE_CALIBRATION_XMAX 910
#define TP_MIKROE_CALIBRATION_YMIN 78
#define TP_MIKROE_CALIBRATION_YMAX 945

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (70)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (1000)

#define TFT_8BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_8BIT_DATA_PORT_CH0_MASK 0xFF

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
