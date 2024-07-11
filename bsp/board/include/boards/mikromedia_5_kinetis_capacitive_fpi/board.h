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
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia 5 for Kinetis Capacitive - FPI"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PB4
#define MIKROBUS_1_RST PE12
#define MIKROBUS_1_CS PE26
#define MIKROBUS_1_SCK PB21
#define MIKROBUS_1_MISO PB23
#define MIKROBUS_1_MOSI PB22
#define MIKROBUS_1_PWM PE6
#define MIKROBUS_1_INT PC16
#define MIKROBUS_1_RX PA15
#define MIKROBUS_1_TX PA14
#define MIKROBUS_1_SCL PC10
#define MIKROBUS_1_SDA PC11

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PB5
#define MIKROBUS_2_RST PA4
#define MIKROBUS_2_CS PA5
#define MIKROBUS_2_SCK PB21
#define MIKROBUS_2_MISO PB23
#define MIKROBUS_2_MOSI PB22
#define MIKROBUS_2_PWM PE7
#define MIKROBUS_2_INT PC17
#define MIKROBUS_2_RX PC3
#define MIKROBUS_2_TX PC4
#define MIKROBUS_2_SCL PC10
#define MIKROBUS_2_SDA PC11

#define MIKROBUS_3 3
#define MIKROBUS_3_AN PB6
#define MIKROBUS_3_RST PA7
#define MIKROBUS_3_CS PA8
#define MIKROBUS_3_SCK PB21
#define MIKROBUS_3_MISO PB23
#define MIKROBUS_3_MOSI PB22
#define MIKROBUS_3_PWM PE11
#define MIKROBUS_3_INT PC18
#define MIKROBUS_3_RX PC14
#define MIKROBUS_3_TX PC15
#define MIKROBUS_3_SCL PA12
#define MIKROBUS_3_SDA PA13

#define TFT_RST PB19
#define TFT_CS PB20
#define TFT_D_C PC2
#define TFT_RD PC8
#define TFT_WR PC9
#define TFT_TE PC0
#define TFT_GPIO PC1
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 PD0
#define TFT_D1 PD1
#define TFT_D2 PD2
#define TFT_D3 PD3
#define TFT_D4 PD4
#define TFT_D5 PD5
#define TFT_D6 PD6
#define TFT_D7 PD7
#define TFT_D8 PD8
#define TFT_D9 PD9
#define TFT_D10 PD10
#define TFT_D11 PD11
#define TFT_D12 PD12
#define TFT_D13 PD13
#define TFT_D14 PD14
#define TFT_D15 PD15

#define TFT_8BIT_DATA_PORT_CH0 PORT_D
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 PORT_D
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 PORT_D
#define TFT_16BIT_DATA_PORT_CH1_MASK 0xFF00

#define CTP_SDA PB3
#define CTP_SCL PB2
#define CTP_INT PB18
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST PB10

#define WIFI_RST PA28
#define WIFI_NHIB PA29
#define WIFI_SCK PB11
#define WIFI_MOSI PB16
#define WIFI_MISO PB17
#define WIFI_HOSTINT PB0
#define WIFI_CS PB1

#define NRF_CE PA25
#define NRF_CS PA26
#define NRF_SCK PC5
#define NRF_SDI PC6
#define NRF_SDO PC7
#define NRF_INT PA27

#define ETH_RXER HAL_PIN_NC
#define ETH_TXD0 HAL_PIN_NC
#define ETH_TDD1 HAL_PIN_NC
#define ETH_RXD0 HAL_PIN_NC
#define ETH_RXD1 HAL_PIN_NC
#define ETH_TXEN HAL_PIN_NC
#define ETH_CRS_DV HAL_PIN_NC
#define ETH_MDIO HAL_PIN_NC
#define ETH_RST HAL_PIN_NC
#define ETH_CLKO HAL_PIN_NC
#define ETH_MDC HAL_PIN_NC
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID PE10
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW PE9

#define SDIO_DAT0 PE1
#define SDIO_DAT1 PE0
#define SDIO_DAT2 PE5
#define SDIO_DAT3 PE4
#define SDIO_CLK PE2
#define SDIO_CMD PE3
#define SDIO_CD PA9

#define FLASH_CS PC19
#define FLASH_MISO PB17
#define FLASH_SCK PB11
#define FLASH_MOSI PB16

#define MP3_SCLK PC5
#define MP3_SIN PC6
#define MP3_SOUT PC7
#define MP3_CS PA6
#define MP3_RST PA10
#define MP3_DREQ PA11
#define MP3_DCS PA24

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA PB3
#define ACCEL_SCL PB2
#define ACCEL_INT2 PA17
#define ACCEL_INT1 PA16

#define BUZZER PE8

#define IR_TX HAL_PIN_NC

#define LED_RGB_SCL HAL_PIN_NC
#define LED_RGB_SDA HAL_PIN_NC

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX HAL_PIN_NC
#define CAN_TX HAL_PIN_NC

#define POWER_BAT_SENSE PB7
#define POWER_STATUS PE27
#define POWER_DC_DETECT PE28

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
