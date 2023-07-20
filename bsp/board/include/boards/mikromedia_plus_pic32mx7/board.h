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

#include "hal_target.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia Plus for PIC32MX7"

/// Mapping
#define TFT_RST PC1
#define TFT_CS PF12
#define TFT_D_C PB15
#define TFT_RD PD5
#define TFT_WR PD4
#define TFT_TE HAL_PIN_NC
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 PE0
#define TFT_D1 PE1
#define TFT_D2 PE2
#define TFT_D3 PE3
#define TFT_D4 PE4
#define TFT_D5 PE5
#define TFT_D6 PE6
#define TFT_D7 PE7
#define TFT_D8 PG0 // PMP pin
#define TFT_D9 PG1 // PMP pin
#define TFT_D10 PF1 // PMP pin
#define TFT_D11 PF0 // PMP pin
#define TFT_D12 PD12 // PMP pin
#define TFT_D13 PD13 // PMP pin
#define TFT_D14 PD2 // PMP pin
#define TFT_D15 PD3 // PMP pin

#define TFT_8BIT_DATA_PORT_CH0 PORT_E
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 PORT_E
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PA3
#define CTP_SCL PA2
#define CTP_INT PA14
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define NRF_CE PB14
#define NRF_CS PA4
#define NRF_SCK PD10
#define NRF_SDI PD0
#define NRF_SDO PC4
#define NRF_INT PB3

#define ETH_RXER PG15
#define ETH_TXD0 PD14
#define ETH_TDD1 PD15
#define ETH_RXD0 PE8
#define ETH_RXD1 PE9
#define ETH_TXEN PA15
#define ETH_CRS_DV PG8
#define ETH_MDIO PD8
#define ETH_RST PA0
#define ETH_CLKO PG9
#define ETH_MDC PD11
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N PG3
#define USB_P PG2
#define USB_PSW PB5

#define SD_CS PA6
#define SD_MOSI PD0
#define SD_SCK PD10
#define SD_MISO PC4
#define SD_CD PA7

#define FLASH_CS PA9
#define FLASH_MISO PD0
#define FLASH_SCK PD10
#define FLASH_MOSI PC4

#define MP3_SCLK PD10
#define MP3_SIN PC4
#define MP3_SOUT PD0
#define MP3_CS PA5
#define MP3_RST PG12
#define MP3_DREQ PG14
#define MP3_DCS PG13

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA PA3
#define ACCEL_SCL PA2
#define ACCEL_INT PG6

#define BUZZER PF13

#define IR_TX PG7

#define LED_R PD1
#define LED_G PD2
#define LED_B PD3

#define TEMP_SENS PB9

#define CAN_RX PC2
#define CAN_TX PC3

#define POWER_BAT_SENSE PB10
#define POWER_STATUS PB13
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
