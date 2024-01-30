/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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

#include "hal_target.h"
#include "shield.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (00)

#define BOARD_NAME "Mikromedia for Tiva"

/// Mapping
#define TFT_RST  PA3
#define TFT_CS   PG3
#define TFT_RS   PK3
#define TFT_RD   PA6
#define TFT_WR   PA7
#define TFT_BLED PD1
#define TFT_TE   HAL_PIN_NC
#define TFT_D0   PF0
#define TFT_D1   PF1
#define TFT_D2   PF2
#define TFT_D3   PF3
#define TFT_D4   PF4
#define TFT_D5   PF5
#define TFT_D6   PF6
#define TFT_D7   PF7
#define TFT_D8   HAL_PIN_NC
#define TFT_D9   HAL_PIN_NC
#define TFT_D10  HAL_PIN_NC
#define TFT_D11  HAL_PIN_NC
#define TFT_D12  HAL_PIN_NC
#define TFT_D13  HAL_PIN_NC
#define TFT_D14  HAL_PIN_NC
#define TFT_D15  HAL_PIN_NC

#define TFT_BPWM TFT_BLED

#define TFT_8BIT_DATA_PORT_CH0 PORT_F
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 PORT_F
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define TP_MIKROE_XL PE5
#define TP_MIKROE_XR PC5
#define TP_MIKROE_YU PC4
#define TP_MIKROE_YD PD4

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 340
#define TP_MIKROE_CALIBRATION_XMAX 3600
#define TP_MIKROE_CALIBRATION_YMIN 240
#define TP_MIKROE_CALIBRATION_YMAX 3700

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (200)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (3800)

#define USB_SW_ID PB0
#define USB_VBUS PB1
#define USB_N PJ0
#define USB_P PJ1
#define USB_PSW HAL_PIN_NC

#define SD_CS PK0
#define SD_MOSI PA5
#define SD_SCK PA2
#define SD_MISO PA4
#define SD_CD PK1

#define FLASH_CS PK2
#define FLASH_MISO PA4
#define FLASH_SCK PA2
#define FLASH_MOSI PA5

#define MP3_SCLK PA2
#define MP3_SIN PA5
#define MP3_SOUT PA4
#define MP3_CS PG6
#define MP3_RST PE6
#define MP3_DREQ PE7
#define MP3_DCS PG7

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA PB3
#define ACCEL_SCL PB2
#define ACCEL_INT HAL_PIN_NC

#define BUZZER HAL_PIN_NC

#define IR_TX HAL_PIN_NC

#define LED_R HAL_PIN_NC
#define LED_G HAL_PIN_NC
#define LED_B HAL_PIN_NC

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX HAL_PIN_NC
#define CAN_TX HAL_PIN_NC

#define POWER_BAT_SENSE PE4
#define POWER_STATUS PB4
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define HEADER_CONNECTOR_HDR1_PIN1 HAL_PIN_NC  // VCC SYS
#define HEADER_CONNECTOR_HDR1_PIN2 HAL_PIN_NC  // VDD
#define HEADER_CONNECTOR_HDR1_PIN3 PD5
#define HEADER_CONNECTOR_HDR1_PIN4 PD6
#define HEADER_CONNECTOR_HDR1_PIN5 PD7
#define HEADER_CONNECTOR_HDR1_PIN6 PE3
#define HEADER_CONNECTOR_HDR1_PIN7 PE2
#define HEADER_CONNECTOR_HDR1_PIN8 PE1
#define HEADER_CONNECTOR_HDR1_PIN9 PE0
#define HEADER_CONNECTOR_HDR1_PIN10 PH0
#define HEADER_CONNECTOR_HDR1_PIN11 PH1
#define HEADER_CONNECTOR_HDR1_PIN12 PH2
#define HEADER_CONNECTOR_HDR1_PIN13 PH3
#define HEADER_CONNECTOR_HDR1_PIN14 PJ2
#define HEADER_CONNECTOR_HDR1_PIN15 PG0
#define HEADER_CONNECTOR_HDR1_PIN16 PG1
#define HEADER_CONNECTOR_HDR1_PIN17 PC7
#define HEADER_CONNECTOR_HDR1_PIN18 PD0
#define HEADER_CONNECTOR_HDR1_PIN19 PD2
#define HEADER_CONNECTOR_HDR1_PIN20 PD3
#define HEADER_CONNECTOR_HDR1_PIN21 PC6
#define HEADER_CONNECTOR_HDR1_PIN22 PA2
#define HEADER_CONNECTOR_HDR1_PIN23 PA4
#define HEADER_CONNECTOR_HDR1_PIN24 PA5
#define HEADER_CONNECTOR_HDR1_PIN25 HAL_PIN_NC  // VCC 3V3
#define HEADER_CONNECTOR_HDR1_PIN26 HAL_PIN_NC  // VDD

#define HEADER_CONNECTOR_HDR2_PIN27 HAL_PIN_NC  // RST
#define HEADER_CONNECTOR_HDR2_PIN28 HAL_PIN_NC  // VDD
#define HEADER_CONNECTOR_HDR2_PIN29 HAL_PIN_NC  // PHONE JACK L
#define HEADER_CONNECTOR_HDR2_PIN30 HAL_PIN_NC  // PHONE JACK R
#define HEADER_CONNECTOR_HDR2_PIN31 PH4
#define HEADER_CONNECTOR_HDR2_PIN32 PH5
#define HEADER_CONNECTOR_HDR2_PIN33 PH6
#define HEADER_CONNECTOR_HDR2_PIN34 PH7
#define HEADER_CONNECTOR_HDR2_PIN35 PC0
#define HEADER_CONNECTOR_HDR2_PIN36 PC1
#define HEADER_CONNECTOR_HDR2_PIN37 PC3
#define HEADER_CONNECTOR_HDR2_PIN38 PC2
#define HEADER_CONNECTOR_HDR2_PIN39 PB5
#define HEADER_CONNECTOR_HDR2_PIN40 PG5
#define HEADER_CONNECTOR_HDR2_PIN41 PG4
#define HEADER_CONNECTOR_HDR2_PIN42 PG2
#define HEADER_CONNECTOR_HDR2_PIN43 PF0
#define HEADER_CONNECTOR_HDR2_PIN44 PF1
#define HEADER_CONNECTOR_HDR2_PIN45 PF2
#define HEADER_CONNECTOR_HDR2_PIN46 PF3
#define HEADER_CONNECTOR_HDR2_PIN47 PA0
#define HEADER_CONNECTOR_HDR2_PIN48 PA1
#define HEADER_CONNECTOR_HDR2_PIN49 PB2
#define HEADER_CONNECTOR_HDR2_PIN50 PB3
#define HEADER_CONNECTOR_HDR2_PIN51 HAL_PIN_NC  // VCC 3V3
#define HEADER_CONNECTOR_HDR2_PIN52 HAL_PIN_NC  // VDD

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
