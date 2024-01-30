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
#define BOARD_REV_MINOR (10)

#define BOARD_NAME "Mikromedia for PIC32"

/// Mapping
#define TFT_RST  PC1
#define TFT_CS   PF12
#define TFT_RS   PB15
#define TFT_RD   PD5
#define TFT_WR   PD4
#define TFT_BLED PA9
#define TFT_D0   PE0
#define TFT_D1   PE1
#define TFT_D2   PE2
#define TFT_D3   PE3
#define TFT_D4   PE4
#define TFT_D5   PE5
#define TFT_D6   PE6
#define TFT_D7   PE7
#define TFT_D8   PG0  // PMD pin - not implemented in mikroSDK yet
#define TFT_D9   PG1  // PMD pin - not implemented in mikroSDK yet
#define TFT_D10  PF1  // PMD pin - not implemented in mikroSDK yet
#define TFT_D11  PF0  // PMD pin - not implemented in mikroSDK yet
#define TFT_D12  PD12 // PMD pin - not implemented in mikroSDK yet
#define TFT_D13  PD13 // PMD pin - not implemented in mikroSDK yet
#define TFT_D14  PD6  // PMD pin - not implemented in mikroSDK yet
#define TFT_D15  PD7  // PMD pin - not implemented in mikroSDK yet

#define TFT_BPWM TFT_BLED

#define TFT_8BIT_DATA_PORT_CH0 PORT_E
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 PORT_E
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define TP_MIKROE_XL PB11
#define TP_MIKROE_XR PB13
#define TP_MIKROE_YU PB12
#define TP_MIKROE_YD PB10

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 115
#define TP_MIKROE_CALIBRATION_XMAX 860
#define TP_MIKROE_CALIBRATION_YMIN 115
#define TP_MIKROE_CALIBRATION_YMAX 860

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (90)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (900)

#define USB_SW_ID HAL_PIN_NC
#define USB_VBUS HAL_PIN_NC
#define USB_N PG3
#define USB_P PG2
#define USB_PSW HAL_PIN_NC

#define SD_CS PG9
#define SD_MOSI PG8
#define SD_SCK PG6
#define SD_MISO PG7
#define SD_CD PF13

#define FLASH_CS PC2
#define FLASH_MISO PG7
#define FLASH_SCK PG6
#define FLASH_MOSI PG8

#define MP3_SCLK PG6
#define MP3_SIN PG7
#define MP3_SOUT PG8
#define MP3_CS PG15
#define MP3_RST PD9
#define MP3_DREQ PD8
#define MP3_DCS PB8

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA PA3
#define ACCEL_SCL PA2
#define ACCEL_INT HAL_PIN_NC

#define BUZZER HAL_PIN_NC

#define IR_TX HAL_PIN_NC

#define LED_R HAL_PIN_NC
#define LED_G HAL_PIN_NC
#define LED_B HAL_PIN_NC

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX HAL_PIN_NC
#define CAN_TX HAL_PIN_NC

#define POWER_BAT_SENSE PB9
#define POWER_STATUS PC3
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define HEADER_CONNECTOR_HDR1_PIN1 HAL_PIN_NC  // VCC SYS
#define HEADER_CONNECTOR_HDR1_PIN2 HAL_PIN_NC  // VDD
#define HEADER_CONNECTOR_HDR1_PIN3 PB0
#define HEADER_CONNECTOR_HDR1_PIN4 PB1
#define HEADER_CONNECTOR_HDR1_PIN5 PB2
#define HEADER_CONNECTOR_HDR1_PIN6 PB3
#define HEADER_CONNECTOR_HDR1_PIN7 PB4
#define HEADER_CONNECTOR_HDR1_PIN8 PB5
#define HEADER_CONNECTOR_HDR1_PIN9 PB14
#define HEADER_CONNECTOR_HDR1_PIN10 PE8
#define HEADER_CONNECTOR_HDR1_PIN11 PE9
#define HEADER_CONNECTOR_HDR1_PIN12 PA14
#define HEADER_CONNECTOR_HDR1_PIN13 PA15
#define HEADER_CONNECTOR_HDR1_PIN14 PA10
#define HEADER_CONNECTOR_HDR1_PIN15 PC4
#define HEADER_CONNECTOR_HDR1_PIN16 PB6
#define HEADER_CONNECTOR_HDR1_PIN17 PB7
#define HEADER_CONNECTOR_HDR1_PIN18 PF3
#define HEADER_CONNECTOR_HDR1_PIN19 PG12
#define HEADER_CONNECTOR_HDR1_PIN20 PG13
#define HEADER_CONNECTOR_HDR1_PIN21 PG14
#define HEADER_CONNECTOR_HDR1_PIN22 PG6
#define HEADER_CONNECTOR_HDR1_PIN23 PG7
#define HEADER_CONNECTOR_HDR1_PIN24 PG8
#define HEADER_CONNECTOR_HDR1_PIN25 HAL_PIN_NC  // VCC 3V3
#define HEADER_CONNECTOR_HDR1_PIN26 HAL_PIN_NC  // VDD

#define HEADER_CONNECTOR_HDR2_PIN27 HAL_PIN_NC  // RST
#define HEADER_CONNECTOR_HDR2_PIN28 HAL_PIN_NC  // VDD
#define HEADER_CONNECTOR_HDR2_PIN29 HAL_PIN_NC  // PHONE JACK L
#define HEADER_CONNECTOR_HDR2_PIN30 HAL_PIN_NC  // PHONE JACK R
#define HEADER_CONNECTOR_HDR2_PIN31 PD0
#define HEADER_CONNECTOR_HDR2_PIN32 PD1
#define HEADER_CONNECTOR_HDR2_PIN33 PD2
#define HEADER_CONNECTOR_HDR2_PIN34 PD3
#define HEADER_CONNECTOR_HDR2_PIN35 PA0
#define HEADER_CONNECTOR_HDR2_PIN36 PA1
#define HEADER_CONNECTOR_HDR2_PIN37 PA4
#define HEADER_CONNECTOR_HDR2_PIN38 PA5
#define HEADER_CONNECTOR_HDR2_PIN39 PA6
#define HEADER_CONNECTOR_HDR2_PIN40 PA7
#define HEADER_CONNECTOR_HDR2_PIN41 PD10
#define HEADER_CONNECTOR_HDR2_PIN42 PD11
#define HEADER_CONNECTOR_HDR2_PIN43 PD14
#define HEADER_CONNECTOR_HDR2_PIN44 PD15
#define HEADER_CONNECTOR_HDR2_PIN45 PF4
#define HEADER_CONNECTOR_HDR2_PIN46 PF5
#define HEADER_CONNECTOR_HDR2_PIN47 PF2
#define HEADER_CONNECTOR_HDR2_PIN48 PF8
#define HEADER_CONNECTOR_HDR2_PIN49 PA2
#define HEADER_CONNECTOR_HDR2_PIN50 PA3
#define HEADER_CONNECTOR_HDR2_PIN51 HAL_PIN_NC  // VCC 3V3
#define HEADER_CONNECTOR_HDR2_PIN52 HAL_PIN_NC  // VDD

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
