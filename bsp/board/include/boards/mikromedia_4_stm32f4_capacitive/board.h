/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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

#include "hal_target.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (03)

#define BOARD_NAME "Mikromedia 4 for STM32F4 Capacitive"

/// Mapping
#define TFT_RST PF14
#define TFT_CS PF13
#define TFT_D_C PF15
#define TFT_RD PF12
#define TFT_WR PF11
#define TFT_TE PD4
#define TFT_GPIO PG5
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 PE0
#define TFT_D1 PE1
#define TFT_D2 PE2
#define TFT_D3 PE3
#define TFT_D4 PE4
#define TFT_D5 PE5
#define TFT_D6 PE6
#define TFT_D7 PE7
#define TFT_D8 PE8
#define TFT_D9 PE9
#define TFT_D10 PE10
#define TFT_D11 PE11
#define TFT_D12 PE12
#define TFT_D13 PE13
#define TFT_D14 PE14
#define TFT_D15 PE15

#define TFT_8BIT_DATA_PORT_CH0 PORT_E
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 PORT_E
#define TFT_16BIT_DATA_PORT_CH0_MASK 0xFFFF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PB7
#define CTP_SCL PB6
#define CTP_INT PA0
#define CTP_WAKE PF6
#define CTP_RST HAL_PIN_NC

#define NRF_CE PG12
#define NRF_CS PG9
#define NRF_SCK PB13
#define NRF_SDI PB15
#define NRF_SDO PB14
#define NRF_INT PG10

#define ETH_RXER PB10
#define ETH_TXD0 PG13
#define ETH_TDD1 PG14
#define ETH_RXD0 PC4
#define ETH_RXD1 PC5
#define ETH_TXEN PG11
#define ETH_CRS_DV PA7
#define ETH_MDIO PA2
#define ETH_RST PG8
#define ETH_CLKO PA1
#define ETH_MDC PC1
#define ETH_INT PG6

#define USB_SW_ID PA10
#define USB_VBUS PA9
#define USB_N PA11
#define USB_P PA12
#define USB_PSW PD6

#define SD_CS PC11
#define SD_MOSI PD2
#define SD_SCK PC12
#define SD_MISO PC8
#define SD_CD PD3

#define FLASH_CS PB11
#define FLASH_MISO PB14
#define FLASH_SCK PB13
#define FLASH_MOSI PB15

#define MP3_SCLK PB13
#define MP3_SIN PB15
#define MP3_SOUT PB14
#define MP3_CS PD11
#define MP3_RST PD8
#define MP3_DREQ PD9
#define MP3_DCS PD10

#define ALS_SDA PB7
#define ALS_SCL PB6

#define ACCEL_SDA PB7
#define ACCEL_SCL PB6
#define ACCEL_INT2 PF2
#define ACCEL_INT1 PB9

#define BUZZER PB8

#define IR_TX PF10

#define LED_R PF7
#define LED_G PD14
#define LED_B PD15

#define TEMP_SENS PF4

#define CAN_RX PD0
#define CAN_TX PD1

#define POWER_BAT_SENSE PF5
#define POWER_STATUS PF3
#define POWER_DC_DETECT PG15

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
