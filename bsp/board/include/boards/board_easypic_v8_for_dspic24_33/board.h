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

#define BOARD_NAME "EasyPIC v8 for PIC24/dsPIC33"

#include "dip_socket.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN HAL_PIN_NC
#define MIKROBUS_1_RST HAL_PIN_NC
#define MIKROBUS_1_CS HAL_PIN_NC
#define MIKROBUS_1_SCK HAL_PIN_NC
#define MIKROBUS_1_MISO HAL_PIN_NC
#define MIKROBUS_1_MOSI HAL_PIN_NC
#define MIKROBUS_1_PWM HAL_PIN_NC
#define MIKROBUS_1_INT HAL_PIN_NC
#define MIKROBUS_1_RX HAL_PIN_NC
#define MIKROBUS_1_TX HAL_PIN_NC
#define MIKROBUS_1_SCL HAL_PIN_NC
#define MIKROBUS_1_SDA HAL_PIN_NC

#define MIKROBUS_2 2
#define MIKROBUS_2_AN HAL_PIN_NC
#define MIKROBUS_2_RST HAL_PIN_NC
#define MIKROBUS_2_CS HAL_PIN_NC
#define MIKROBUS_2_SCK HAL_PIN_NC
#define MIKROBUS_2_MISO HAL_PIN_NC
#define MIKROBUS_2_MOSI HAL_PIN_NC
#define MIKROBUS_2_PWM HAL_PIN_NC
#define MIKROBUS_2_INT HAL_PIN_NC
#define MIKROBUS_2_RX HAL_PIN_NC
#define MIKROBUS_2_TX HAL_PIN_NC
#define MIKROBUS_2_SCL HAL_PIN_NC
#define MIKROBUS_2_SDA HAL_PIN_NC

#define MIKROBUS_3 3
#define MIKROBUS_3_AN HAL_PIN_NC
#define MIKROBUS_3_RST HAL_PIN_NC
#define MIKROBUS_3_CS HAL_PIN_NC
#define MIKROBUS_3_SCK HAL_PIN_NC
#define MIKROBUS_3_MISO HAL_PIN_NC
#define MIKROBUS_3_MOSI HAL_PIN_NC
#define MIKROBUS_3_PWM HAL_PIN_NC
#define MIKROBUS_3_INT HAL_PIN_NC
#define MIKROBUS_3_RX HAL_PIN_NC
#define MIKROBUS_3_TX HAL_PIN_NC
#define MIKROBUS_3_SCL HAL_PIN_NC
#define MIKROBUS_3_SDA HAL_PIN_NC

#define MIKROBUS_4 4
#define MIKROBUS_4_AN HAL_PIN_NC
#define MIKROBUS_4_RST HAL_PIN_NC
#define MIKROBUS_4_CS HAL_PIN_NC
#define MIKROBUS_4_SCK HAL_PIN_NC
#define MIKROBUS_4_MISO HAL_PIN_NC
#define MIKROBUS_4_MOSI HAL_PIN_NC
#define MIKROBUS_4_PWM HAL_PIN_NC
#define MIKROBUS_4_INT HAL_PIN_NC
#define MIKROBUS_4_RX HAL_PIN_NC
#define MIKROBUS_4_TX HAL_PIN_NC
#define MIKROBUS_4_SCL HAL_PIN_NC
#define MIKROBUS_4_SDA HAL_PIN_NC

#define MIKROBUS_5 5
#define MIKROBUS_5_AN HAL_PIN_NC
#define MIKROBUS_5_RST HAL_PIN_NC
#define MIKROBUS_5_CS HAL_PIN_NC
#define MIKROBUS_5_SCK HAL_PIN_NC
#define MIKROBUS_5_MISO HAL_PIN_NC
#define MIKROBUS_5_MOSI HAL_PIN_NC
#define MIKROBUS_5_PWM HAL_PIN_NC
#define MIKROBUS_5_INT HAL_PIN_NC
#define MIKROBUS_5_RX HAL_PIN_NC
#define MIKROBUS_5_TX HAL_PIN_NC
#define MIKROBUS_5_SCL HAL_PIN_NC
#define MIKROBUS_5_SDA HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define TFT_CS1  HAL_PIN_NC
#define TFT_CS2  HAL_PIN_NC
#define TFT_RS   HAL_PIN_NC
#define TFT_R_W  HAL_PIN_NC
#define TFT_E    HAL_PIN_NC
#define TFT_D0   HAL_PIN_NC
#define TFT_D1   HAL_PIN_NC
#define TFT_D2   HAL_PIN_NC
#define TFT_D3   HAL_PIN_NC
#define TFT_D4   HAL_PIN_NC
#define TFT_D5   HAL_PIN_NC
#define TFT_D6   HAL_PIN_NC
#define TFT_D7   HAL_PIN_NC
#define TFT_RST  HAL_PIN_NC
#define TFT_BPWM HAL_PIN_NC

#define TFT_RD TFT_CS1
#define TFT_WR TFT_CS2
#define TFT_CS TFT_E

#define TP_MIKROE_XL HAL_PIN_NC
#define TP_MIKROE_XR HAL_PIN_NC
#define TP_MIKROE_YU HAL_PIN_NC
#define TP_MIKROE_YD HAL_PIN_NC

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 120
#define TP_MIKROE_CALIBRATION_XMAX 910
#define TP_MIKROE_CALIBRATION_YMIN 78
#define TP_MIKROE_CALIBRATION_YMAX 945

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (70)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (1000)

#define TFT_8BIT_DATA_PORT_CH0 PORT_B
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
