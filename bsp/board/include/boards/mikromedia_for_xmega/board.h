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

#include "hal_target.h"
#include "shield.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (00)

#define BOARD_NAME "Mikromedia for XMEGA"

/// Mapping
#define TFT_RST  GPIO_PJ1
#define TFT_CS   GPIO_PJ5
#define TFT_RS   GPIO_PJ4
#define TFT_RD   GPIO_PJ2
#define TFT_WR   GPIO_PJ3
#define TFT_BLED GPIO_PC4
#define TFT_D0   GPIO_PK0
#define TFT_D1   GPIO_PK1
#define TFT_D2   GPIO_PK2
#define TFT_D3   GPIO_PK3
#define TFT_D4   GPIO_PK4
#define TFT_D5   GPIO_PK5
#define TFT_D6   GPIO_PK6
#define TFT_D7   GPIO_PK7
#define TFT_D8   HAL_PIN_NC
#define TFT_D9   HAL_PIN_NC
#define TFT_D10  HAL_PIN_NC
#define TFT_D11  HAL_PIN_NC
#define TFT_D12  HAL_PIN_NC
#define TFT_D13  HAL_PIN_NC
#define TFT_D14  HAL_PIN_NC
#define TFT_D15  HAL_PIN_NC

#define TFT_BPWM TFT_BLED

#define TFT_8BIT_DATA_PORT_CH0 GPIO_PORT_K
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 GPIO_PORT_K
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define TP_MIKROE_XL GPIO_PA2
#define TP_MIKROE_XR GPIO_PQ2
#define TP_MIKROE_YU GPIO_PQ3
#define TP_MIKROE_YD GPIO_PA1

// Default TP_MIKROE touch panel calibration values.
#define TP_MIKROE_CALIBRATION_XMIN 738
#define TP_MIKROE_CALIBRATION_XMAX 3820
#define TP_MIKROE_CALIBRATION_YMIN 604
#define TP_MIKROE_CALIBRATION_YMAX 3955

#define TP_MIKROE_PRESSURE_THRESHOLD_LOWER (300)
#define TP_MIKROE_PRESSURE_THRESHOLD_UPPER (3800)

#define USB_SW_ID HAL_PIN_NC
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW HAL_PIN_NC

#define SD_CS GPIO_PF5
#define SD_MOSI GPIO_PC5
#define SD_SCK GPIO_PC7
#define SD_MISO GPIO_PC6
#define SD_CD GPIO_PF4

#define FLASH_CS GPIO_PB7
#define FLASH_MISO GPIO_PC6
#define FLASH_SCK GPIO_PC7
#define FLASH_MOSI GPIO_PC5

#define MP3_SCLK GPIO_PC7
#define MP3_SIN GPIO_PC6
#define MP3_SOUT GPIO_PC5
#define MP3_CS GPIO_PH6
#define MP3_RST GPIO_PH5
#define MP3_DREQ GPIO_PE5
#define MP3_DCS GPIO_PH4

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA GPIO_PD0
#define ACCEL_SCL GPIO_PD1
#define ACCEL_INT HAL_PIN_NC

#define BUZZER HAL_PIN_NC

#define IR_TX HAL_PIN_NC

#define LED_R HAL_PIN_NC
#define LED_G HAL_PIN_NC
#define LED_B HAL_PIN_NC

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX HAL_PIN_NC
#define CAN_TX HAL_PIN_NC

#define POWER_BAT_SENSE GPIO_PA3
#define POWER_STATUS GPIO_PJ6
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define HEADER_CONNECTOR_HDR1_PIN1 HAL_PIN_NC  // VCC SYS
#define HEADER_CONNECTOR_HDR1_PIN2 HAL_PIN_NC  // VDD
#define HEADER_CONNECTOR_HDR1_PIN3 GPIO_PB1
#define HEADER_CONNECTOR_HDR1_PIN4 GPIO_PB2
#define HEADER_CONNECTOR_HDR1_PIN5 GPIO_PB3
#define HEADER_CONNECTOR_HDR1_PIN6 GPIO_PA4
#define HEADER_CONNECTOR_HDR1_PIN7 GPIO_PA5
#define HEADER_CONNECTOR_HDR1_PIN8 GPIO_PA6
#define HEADER_CONNECTOR_HDR1_PIN9 GPIO_PA7
#define HEADER_CONNECTOR_HDR1_PIN10 GPIO_PH0
#define HEADER_CONNECTOR_HDR1_PIN11 GPIO_PH1
#define HEADER_CONNECTOR_HDR1_PIN12 GPIO_PB5
#define HEADER_CONNECTOR_HDR1_PIN13 GPIO_PB6
#define HEADER_CONNECTOR_HDR1_PIN14 GPIO_PE1
#define HEADER_CONNECTOR_HDR1_PIN15 GPIO_PE0
#define HEADER_CONNECTOR_HDR1_PIN16 GPIO_PD7
#define HEADER_CONNECTOR_HDR1_PIN17 GPIO_PD6
#define HEADER_CONNECTOR_HDR1_PIN18 GPIO_PD5
#define HEADER_CONNECTOR_HDR1_PIN19 GPIO_PH7
#define HEADER_CONNECTOR_HDR1_PIN20 GPIO_PJ0
#define HEADER_CONNECTOR_HDR1_PIN21 GPIO_PD4
#define HEADER_CONNECTOR_HDR1_PIN22 GPIO_PC7
#define HEADER_CONNECTOR_HDR1_PIN23 GPIO_PC6
#define HEADER_CONNECTOR_HDR1_PIN24 GPIO_PC5
#define HEADER_CONNECTOR_HDR1_PIN25 HAL_PIN_NC  // VCC 3V3
#define HEADER_CONNECTOR_HDR1_PIN26 HAL_PIN_NC  // VDD

#define HEADER_CONNECTOR_HDR2_PIN27 HAL_PIN_NC  // RST
#define HEADER_CONNECTOR_HDR2_PIN28 HAL_PIN_NC  // VDD
#define HEADER_CONNECTOR_HDR2_PIN29 HAL_PIN_NC  // PHONE JACK L
#define HEADER_CONNECTOR_HDR2_PIN30 HAL_PIN_NC  // PHONE JACK R
#define HEADER_CONNECTOR_HDR2_PIN31 GPIO_PC0
#define HEADER_CONNECTOR_HDR2_PIN32 GPIO_PC1
#define HEADER_CONNECTOR_HDR2_PIN33 GPIO_PC2
#define HEADER_CONNECTOR_HDR2_PIN34 GPIO_PC3
#define HEADER_CONNECTOR_HDR2_PIN35 GPIO_PF0
#define HEADER_CONNECTOR_HDR2_PIN36 GPIO_PF1
#define HEADER_CONNECTOR_HDR2_PIN37 GPIO_PE4
#define HEADER_CONNECTOR_HDR2_PIN38 GPIO_PJ7
#define HEADER_CONNECTOR_HDR2_PIN39 GPIO_PR0
#define HEADER_CONNECTOR_HDR2_PIN40 GPIO_PR1
#define HEADER_CONNECTOR_HDR2_PIN41 GPIO_PE2
#define HEADER_CONNECTOR_HDR2_PIN42 GPIO_PE3
#define HEADER_CONNECTOR_HDR2_PIN43 GPIO_PE6
#define HEADER_CONNECTOR_HDR2_PIN44 GPIO_PE7
#define HEADER_CONNECTOR_HDR2_PIN45 GPIO_PF6
#define HEADER_CONNECTOR_HDR2_PIN46 GPIO_PF7
#define HEADER_CONNECTOR_HDR2_PIN47 GPIO_PD2
#define HEADER_CONNECTOR_HDR2_PIN48 GPIO_PD3
#define HEADER_CONNECTOR_HDR2_PIN49 GPIO_PD1
#define HEADER_CONNECTOR_HDR2_PIN50 GPIO_PD0
#define HEADER_CONNECTOR_HDR2_PIN51 HAL_PIN_NC  // VCC 3V3
#define HEADER_CONNECTOR_HDR2_PIN52 HAL_PIN_NC  // VDD

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
