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

#define BOARD_NAME "Mikromedia for dsPIC33EP"

/// Mapping
#define TFT_RST  PC1
#define TFT_CS   PC3
#define TFT_RS   PB15
#define TFT_RD   PD12
#define TFT_WR   PD13
#define TFT_BLED PD7
#define TFT_D0   PA0
#define TFT_D1   PA1
#define TFT_D2   PA2
#define TFT_D3   PA3
#define TFT_D4   PA4
#define TFT_D5   PA5
#define TFT_D6   PA6
#define TFT_D7   PA7
#define TFT_D8   PE0
#define TFT_D9   PE1
#define TFT_D10  PE2
#define TFT_D11  PE3
#define TFT_D12  PE4
#define TFT_D13  PE5
#define TFT_D14  PE6
#define TFT_D15  PE7

#define TFT_BPWM TFT_BLED

#define TFT_8BIT_DATA_PORT_CH0 PORT_A
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 PORT_A
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 PORT_E
#define TFT_16BIT_DATA_PORT_CH1_MASK 0xFF00

#define TP_MIKROE_XL PB13
#define TP_MIKROE_XR PB11
#define TP_MIKROE_YU PB12
#define TP_MIKROE_YD PB10

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 92
#define TP_MIKROE_CALIBRATION_XMAX 882
#define TP_MIKROE_CALIBRATION_YMIN 132
#define TP_MIKROE_CALIBRATION_YMAX 770

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (70)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (1000)

// not needed

#define USB_SW_ID HAL_PIN_NC
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW HAL_PIN_NC

#define SD_CS HAL_PIN_NC
#define SD_MOSI HAL_PIN_NC
#define SD_SCK HAL_PIN_NC
#define SD_MISO HAL_PIN_NC
#define SD_CD HAL_PIN_NC

#define FLASH_CS HAL_PIN_NC
#define FLASH_MISO HAL_PIN_NC
#define FLASH_SCK HAL_PIN_NC
#define FLASH_MOSI HAL_PIN_NC

#define MP3_SCLK HAL_PIN_NC
#define MP3_SIN HAL_PIN_NC
#define MP3_SOUT HAL_PIN_NC
#define MP3_CS HAL_PIN_NC
#define MP3_RST HAL_PIN_NC
#define MP3_DREQ HAL_PIN_NC
#define MP3_DCS HAL_PIN_NC

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA HAL_PIN_NC
#define ACCEL_SCL HAL_PIN_NC
#define ACCEL_INT HAL_PIN_NC

#define BUZZER HAL_PIN_NC

#define IR_TX HAL_PIN_NC

#define LED_R HAL_PIN_NC
#define LED_G HAL_PIN_NC
#define LED_B HAL_PIN_NC

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX HAL_PIN_NC
#define CAN_TX HAL_PIN_NC

#define POWER_BAT_SENSE HAL_PIN_NC
#define POWER_STATUS HAL_PIN_NC
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX PF3
#define USB_UART_RX PF2

#define HEADER_CONNECTOR_HDR1_PIN1 HAL_PIN_NC   // VCC SYS
#define HEADER_CONNECTOR_HDR1_PIN2 HAL_PIN_NC   // VDD
#define HEADER_CONNECTOR_HDR1_PIN3 PB0
#define HEADER_CONNECTOR_HDR1_PIN4 PB1
#define HEADER_CONNECTOR_HDR1_PIN5 PB2
#define HEADER_CONNECTOR_HDR1_PIN6 PB3
#define HEADER_CONNECTOR_HDR1_PIN7 PB4
#define HEADER_CONNECTOR_HDR1_PIN8 PB5
#define HEADER_CONNECTOR_HDR1_PIN9 PB9
#define HEADER_CONNECTOR_HDR1_PIN10 PD6
#define HEADER_CONNECTOR_HDR1_PIN11 PD7
#define HEADER_CONNECTOR_HDR1_PIN12 PD12
#define HEADER_CONNECTOR_HDR1_PIN13 PD13
#define HEADER_CONNECTOR_HDR1_PIN14 PA14
#define HEADER_CONNECTOR_HDR1_PIN15 PA15
#define HEADER_CONNECTOR_HDR1_PIN16 PD10
#define HEADER_CONNECTOR_HDR1_PIN17 PC4
#define HEADER_CONNECTOR_HDR1_PIN18 PD0
#define HEADER_CONNECTOR_HDR1_PIN19 PB14
#define HEADER_CONNECTOR_HDR1_PIN20 PG13
#define HEADER_CONNECTOR_HDR1_PIN21 PG14
#define HEADER_CONNECTOR_HDR1_PIN22 PG6
#define HEADER_CONNECTOR_HDR1_PIN23 PG7
#define HEADER_CONNECTOR_HDR1_PIN24 PG8
#define HEADER_CONNECTOR_HDR1_PIN25 HAL_PIN_NC   // VCC 3V3
#define HEADER_CONNECTOR_HDR1_PIN26 HAL_PIN_NC   // VDD

// Specifically defined in schematic
#define HEADER_CONNECTOR_HDR2_PIN1    // RST
#define HEADER_CONNECTOR_HDR2_PIN2    // VDD
#define HEADER_CONNECTOR_HDR2_PIN3    // PHONE JACK L
#define HEADER_CONNECTOR_HDR2_PIN4    // PHONE JACK R
#define HEADER_CONNECTOR_HDR2_PIN5 PF2
#define HEADER_CONNECTOR_HDR2_PIN6 PF4
#define HEADER_CONNECTOR_HDR2_PIN7 PF5
#define HEADER_CONNECTOR_HDR2_PIN8 PF8
#define HEADER_CONNECTOR_HDR2_PIN9 PF13
#define HEADER_CONNECTOR_HDR2_PIN10 PA0
#define HEADER_CONNECTOR_HDR2_PIN11 PA1
#define HEADER_CONNECTOR_HDR2_PIN12 PE8
#define HEADER_CONNECTOR_HDR2_PIN13 PE9
#define HEADER_CONNECTOR_HDR2_PIN14 PD8
#define HEADER_CONNECTOR_HDR2_PIN15 PD9
#define HEADER_CONNECTOR_HDR2_PIN16 PD11
#define HEADER_CONNECTOR_HDR2_PIN17 PG0
#define HEADER_CONNECTOR_HDR2_PIN18 PG1
#define HEADER_CONNECTOR_HDR2_PIN19 PF0
#define HEADER_CONNECTOR_HDR2_PIN20 PF1
#define HEADER_CONNECTOR_HDR2_PIN21 PD3
#define HEADER_CONNECTOR_HDR2_PIN22 PD1
#define HEADER_CONNECTOR_HDR2_PIN23 PA2
#define HEADER_CONNECTOR_HDR2_PIN24 PA3
#define HEADER_CONNECTOR_HDR2_PIN25 HAL_PIN_NC   // VCC 3V3
#define HEADER_CONNECTOR_HDR2_PIN26 HAL_PIN_NC   // VDD

#define HEADER_CONNECTOR_HDR2_PIN27    // RST
#define HEADER_CONNECTOR_HDR2_PIN28 HAL_PIN_NC   // VDD
#define HEADER_CONNECTOR_HDR2_PIN29    // PHONE JACK L
#define HEADER_CONNECTOR_HDR2_PIN30    // PHONE JACK R
#define HEADER_CONNECTOR_HDR2_PIN31 PD0
#define HEADER_CONNECTOR_HDR2_PIN32 PD1
#define HEADER_CONNECTOR_HDR2_PIN33 PD2
#define HEADER_CONNECTOR_HDR2_PIN34 PD3
#define HEADER_CONNECTOR_HDR2_PIN35 PD4
#define HEADER_CONNECTOR_HDR2_PIN36 PD5
#define HEADER_CONNECTOR_HDR2_PIN37 PD8
#define HEADER_CONNECTOR_HDR2_PIN38 PD9
#define HEADER_CONNECTOR_HDR2_PIN39 PD14
#define HEADER_CONNECTOR_HDR2_PIN40 PD15
#define HEADER_CONNECTOR_HDR2_PIN41 PD6
#define HEADER_CONNECTOR_HDR2_PIN42 PC2
#define HEADER_CONNECTOR_HDR2_PIN43 PF12
#define HEADER_CONNECTOR_HDR2_PIN44 PF13
#define HEADER_CONNECTOR_HDR2_PIN45 PF0
#define HEADER_CONNECTOR_HDR2_PIN46 PF1
#define HEADER_CONNECTOR_HDR2_PIN47 PF2
#define HEADER_CONNECTOR_HDR2_PIN48 PF3
#define HEADER_CONNECTOR_HDR2_PIN49 PG2
#define HEADER_CONNECTOR_HDR2_PIN50 PG3
#define HEADER_CONNECTOR_HDR2_PIN51 HAL_PIN_NC   // VCC 3V3
#define HEADER_CONNECTOR_HDR2_PIN52 HAL_PIN_NC   // VDD

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
