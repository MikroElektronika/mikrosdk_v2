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

#include "hal_target.h"
#include "shield.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Mikromedia 4 for PIC32MZ Resistive"

/// Mapping
#define TFT_RST PH9
#define TFT_CS PH10
#define TFT_D_C PH11
#define TFT_RD PA7
#define TFT_WR PA6
#define TFT_TE PA4
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

#define CTP_SDA PA15
#define CTP_SCL PA14
#define CTP_INT PB15
#define CTP_WAKE PH14
#define CTP_RST HAL_PIN_NC

#define NRF_CE PH0
#define NRF_CS PH1
#define NRF_SCK PB14
#define NRF_SDI PC1
#define NRF_SDO PD10
#define NRF_INT PD5

#define ETH_RXER PH4
#define ETH_TXD0 PJ8
#define ETH_TDD1 PJ9
#define ETH_RXD0 PH8
#define ETH_RXD1 PH5
#define ETH_TXEN PD6
#define ETH_CRS_DV PH13
#define ETH_MDIO PJ1
#define ETH_RST PH3
#define ETH_CLKO PJ11
#define ETH_MDC PD11
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW PJ3

#define SD_CS PG14
#define SD_MOSI PG10
#define SD_SCK PF13
#define SD_MISO PB5
#define SD_CD PG12

#define FLASH_CS PH2
#define FLASH_MISO PB5
#define FLASH_SCK PF13
#define FLASH_MOSI PB10

#define MP3_SCLK PB14
#define MP3_SIN PC1
#define MP3_SOUT PD10
#define MP3_CS PK0
#define MP3_RST PJ13
#define MP3_DREQ PJ14
#define MP3_DCS PJ15

#define ALS_SDA PA15
#define ALS_SCL PA14

#define ACCEL_SDA PA15
#define ACCEL_SCL PA14
#define ACCEL_INT2 PD9
#define ACCEL_INT1 PD7

#define BUZZER PK2

#define IR_TX PJ6

#define LED_R PB2
#define LED_G PB1
#define LED_B PB0

#define TEMP_SENS PG15

#define CAN_RX PD15
#define CAN_TX PD14

#define POWER_BAT_SENSE PA5
#define POWER_STATUS PJ12
#define POWER_DC_DETECT PJ10

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define SHIELD_CONNECTOR_J1_PIN3 PA0
#define SHIELD_CONNECTOR_J1_PIN4 PB11
#define SHIELD_CONNECTOR_J1_PIN5 PA1
#define SHIELD_CONNECTOR_J1_PIN6 PB12
#define SHIELD_CONNECTOR_J1_PIN7 PB13
#define SHIELD_CONNECTOR_J1_PIN8 PH6
#define SHIELD_CONNECTOR_J1_PIN9 PK4
#define SHIELD_CONNECTOR_J1_PIN10 PK5
#define SHIELD_CONNECTOR_J1_PIN11 PB4
#define SHIELD_CONNECTOR_J1_PIN12 PG6
#define SHIELD_CONNECTOR_J1_PIN13 PG7
#define SHIELD_CONNECTOR_J1_PIN14 PG8
#define SHIELD_CONNECTOR_J1_PIN15 PD15
#define SHIELD_CONNECTOR_J1_PIN16 PD14
#define SHIELD_CONNECTOR_J1_PIN17 PK1
#define SHIELD_CONNECTOR_J1_PIN18 PD1
#define SHIELD_CONNECTOR_J1_PIN19 PF4
#define SHIELD_CONNECTOR_J1_PIN20 PF5

#define SHIELD_CONNECTOR_J2_PIN7 PF12
#define SHIELD_CONNECTOR_J2_PIN8 PC2
#define SHIELD_CONNECTOR_J2_PIN9 PB8
#define SHIELD_CONNECTOR_J2_PIN10 PB3
#define SHIELD_CONNECTOR_J2_PIN11 PB9
#define SHIELD_CONNECTOR_J2_PIN12 HAL_PIN_NC
#define SHIELD_CONNECTOR_J2_PIN13 PC3
#define SHIELD_CONNECTOR_J2_PIN14 PC4
#define SHIELD_CONNECTOR_J2_PIN15 PC14
#define SHIELD_CONNECTOR_J2_PIN16 PG9
#define SHIELD_CONNECTOR_J2_PIN17 PA2
#define SHIELD_CONNECTOR_J2_PIN18 PA3
#define SHIELD_CONNECTOR_J2_PIN19 PD4
#define SHIELD_CONNECTOR_J2_PIN20 PD0
#define SHIELD_CONNECTOR_J2_PIN21 PE8
#define SHIELD_CONNECTOR_J2_PIN22 PE9
#define SHIELD_CONNECTOR_J2_PIN23 PF8
#define SHIELD_CONNECTOR_J2_PIN24 PF2

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
