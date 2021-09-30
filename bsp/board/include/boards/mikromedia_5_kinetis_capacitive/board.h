/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia 5 for Kinetis Capacitive"

/// Mapping
#define TFT_RST PB19
#define TFT_CS PB20
#define TFT_D_C PB21
#define TFT_RD PB22
#define TFT_WR PB23
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
#define CTP_RST PB19

#define NRF_CE PA25
#define NRF_CS PA26
#define NRF_SCK PC5
#define NRF_SDI PC6
#define NRF_SDO PC7
#define NRF_INT PA27

#define ETH_RXER PA5
#define ETH_TXD0 PA16
#define ETH_TDD1 PA17
#define ETH_RXD0 PA13
#define ETH_RXD1 PA12
#define ETH_TXEN PA15
#define ETH_CRS_DV PA14
#define ETH_MDIO PA7
#define ETH_RST PA9
#define ETH_CLKO PE26
#define ETH_MDC PA8
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID PE10
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW PE9

#define SD_CS PB8
#define SD_MOSI PE1
#define SD_SCK PE2
#define SD_MISO PE3
#define SD_CD PB9

#define FLASH_CS PB17
#define FLASH_MISO PC7
#define FLASH_SCK PC5
#define FLASH_MOSI PC6

#define MP3_SCLK PC5
#define MP3_SIN PC6
#define MP3_SOUT PC7
#define MP3_CS PA6
#define MP3_RST PA10
#define MP3_DREQ PA11
#define MP3_DCS PA24

#define ALS_SDA PB3
#define ALS_SCL PB2

#define ACCEL_SDA PB3
#define ACCEL_SCL PB2
#define ACCEL_INT2 PB11
#define ACCEL_INT1 PB10

#define BUZZER PE8

#define IR_TX PA4

#define LED_RGB_SCL PB0
#define LED_RGB_SDA PB1

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX PE25
#define CAN_TX PE24

#define POWER_BAT_SENSE HAL_PIN_NC
#define POWER_STATUS PE27
#define POWER_DC_DETECT PE28

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
