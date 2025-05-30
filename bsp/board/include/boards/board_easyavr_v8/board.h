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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "EasyAVR v8"

#include "dip_socket.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   MIKROBUS_1_DIP_AN
#define MIKROBUS_1_RST  MIKROBUS_1_DIP_RST
#define MIKROBUS_1_CS   MIKROBUS_1_DIP_CS
#define MIKROBUS_1_SCK  MIKROBUS_1_DIP_SCK
#define MIKROBUS_1_MISO MIKROBUS_1_DIP_MISO
#define MIKROBUS_1_MOSI MIKROBUS_1_DIP_MOSI
#define MIKROBUS_1_PWM  MIKROBUS_1_DIP_PWM
#define MIKROBUS_1_INT  MIKROBUS_1_DIP_INT
#define MIKROBUS_1_RX   MIKROBUS_1_DIP_RX
#define MIKROBUS_1_TX   MIKROBUS_1_DIP_TX
#define MIKROBUS_1_SCL  MIKROBUS_1_DIP_SCL
#define MIKROBUS_1_SDA  MIKROBUS_1_DIP_SDA

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   MIKROBUS_2_DIP_AN
#define MIKROBUS_2_RST  MIKROBUS_2_DIP_RST
#define MIKROBUS_2_CS   MIKROBUS_2_DIP_CS
#define MIKROBUS_2_SCK  MIKROBUS_2_DIP_SCK
#define MIKROBUS_2_MISO MIKROBUS_2_DIP_MISO
#define MIKROBUS_2_MOSI MIKROBUS_2_DIP_MOSI
#define MIKROBUS_2_PWM  MIKROBUS_2_DIP_PWM
#define MIKROBUS_2_INT  MIKROBUS_2_DIP_INT
#define MIKROBUS_2_RX   MIKROBUS_2_DIP_RX
#define MIKROBUS_2_TX   MIKROBUS_2_DIP_TX
#define MIKROBUS_2_SCL  MIKROBUS_2_DIP_SCL
#define MIKROBUS_2_SDA  MIKROBUS_2_DIP_SDA

#define MIKROBUS_3      3
#define MIKROBUS_3_AN   MIKROBUS_3_DIP_AN
#define MIKROBUS_3_RST  MIKROBUS_3_DIP_RST
#define MIKROBUS_3_CS   MIKROBUS_3_DIP_CS
#define MIKROBUS_3_SCK  MIKROBUS_3_DIP_SCK
#define MIKROBUS_3_MISO MIKROBUS_3_DIP_MISO
#define MIKROBUS_3_MOSI MIKROBUS_3_DIP_MOSI
#define MIKROBUS_3_PWM  MIKROBUS_3_DIP_PWM
#define MIKROBUS_3_INT  MIKROBUS_3_DIP_INT
#define MIKROBUS_3_RX   MIKROBUS_3_DIP_RX
#define MIKROBUS_3_TX   MIKROBUS_3_DIP_TX
#define MIKROBUS_3_SCL  MIKROBUS_3_DIP_SCL
#define MIKROBUS_3_SDA  MIKROBUS_3_DIP_SDA

#define MIKROBUS_4      4
#define MIKROBUS_4_AN   MIKROBUS_4_DIP_AN
#define MIKROBUS_4_RST  MIKROBUS_4_DIP_RST
#define MIKROBUS_4_CS   MIKROBUS_4_DIP_CS
#define MIKROBUS_4_SCK  MIKROBUS_4_DIP_SCK
#define MIKROBUS_4_MISO MIKROBUS_4_DIP_MISO
#define MIKROBUS_4_MOSI MIKROBUS_4_DIP_MOSI
#define MIKROBUS_4_PWM  MIKROBUS_4_DIP_PWM
#define MIKROBUS_4_INT  MIKROBUS_4_DIP_INT
#define MIKROBUS_4_RX   MIKROBUS_4_DIP_RX
#define MIKROBUS_4_TX   MIKROBUS_4_DIP_TX
#define MIKROBUS_4_SCL  MIKROBUS_4_DIP_SCL
#define MIKROBUS_4_SDA  MIKROBUS_4_DIP_SDA

#define MIKROBUS_5      5
#define MIKROBUS_5_AN   MIKROBUS_5_DIP_AN
#define MIKROBUS_5_RST  MIKROBUS_5_DIP_RST
#define MIKROBUS_5_CS   MIKROBUS_5_DIP_CS
#define MIKROBUS_5_SCK  MIKROBUS_5_DIP_SCK
#define MIKROBUS_5_MISO MIKROBUS_5_DIP_MISO
#define MIKROBUS_5_MOSI MIKROBUS_5_DIP_MOSI
#define MIKROBUS_5_PWM  MIKROBUS_5_DIP_PWM
#define MIKROBUS_5_INT  MIKROBUS_5_DIP_INT
#define MIKROBUS_5_RX   MIKROBUS_5_DIP_RX
#define MIKROBUS_5_TX   MIKROBUS_5_DIP_TX
#define MIKROBUS_5_SCL  MIKROBUS_5_DIP_SCL
#define MIKROBUS_5_SDA  MIKROBUS_5_DIP_SDA

#define USB_UART_TX     USB_UART_DIP_TX
#define USB_UART_RX     USB_UART_DIP_RX

#define LCD_CS1  GPIO_PB0
#define LCD_CS2  GPIO_PB1
#define LCD_RS   GPIO_PA2
#define LCD_E    GPIO_PD6
#define LCD_D4   GPIO_PC4
#define LCD_D5   GPIO_PC5
#define LCD_D6   GPIO_PC6
#define LCD_D7   GPIO_PC7
#define LCD_BPWM GPIO_PD5

#define TFT_CS1  GPIO_PB0
#define TFT_CS2  GPIO_PB1
#define TFT_RS   GPIO_PA2
#define TFT_R_W  GPIO_PA3
#define TFT_E    GPIO_PD6
#define TFT_D0   GPIO_PC0
#define TFT_D1   GPIO_PC1
#define TFT_D2   GPIO_PC2
#define TFT_D3   GPIO_PC3
#define TFT_D4   GPIO_PC4
#define TFT_D5   GPIO_PC5
#define TFT_D6   GPIO_PC6
#define TFT_D7   GPIO_PC7
#define TFT_RST  GPIO_PD7
#define TFT_BPWM GPIO_PD5

#define TFT_RD TFT_CS1
#define TFT_WR TFT_CS2
#define TFT_CS TFT_E

#define TP_MIKROE_XL GPIO_PA1
#define TP_MIKROE_XR GPIO_PA2
#define TP_MIKROE_YU GPIO_PA3
#define TP_MIKROE_YD GPIO_PA0

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 120
#define TP_MIKROE_CALIBRATION_XMAX 910
#define TP_MIKROE_CALIBRATION_YMIN 78
#define TP_MIKROE_CALIBRATION_YMAX 945

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (70)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (1000)

#define TFT_8BIT_DATA_PORT_CH0 GPIO_PORT_C
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
