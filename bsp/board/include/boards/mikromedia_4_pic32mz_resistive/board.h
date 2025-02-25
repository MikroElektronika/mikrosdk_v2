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
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Mikromedia 4 for PIC32MZ Resistive"

/// Mapping
#define TFT_RST GPIO_PH9
#define TFT_CS GPIO_PH10
#define TFT_D_C GPIO_PH11
#define TFT_RD GPIO_PA7
#define TFT_WR GPIO_PA6
#define TFT_TE GPIO_PA4
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 GPIO_PE0
#define TFT_D1 GPIO_PE1
#define TFT_D2 GPIO_PE2
#define TFT_D3 GPIO_PE3
#define TFT_D4 GPIO_PE4
#define TFT_D5 GPIO_PE5
#define TFT_D6 GPIO_PE6
#define TFT_D7 GPIO_PE7
#define TFT_D8 GPIO_PG0 // PMP pin
#define TFT_D9 GPIO_PG1 // PMP pin
#define TFT_D10 GPIO_PF1 // PMP pin
#define TFT_D11 GPIO_PF0 // PMP pin
#define TFT_D12 GPIO_PD12 // PMP pin
#define TFT_D13 GPIO_PD13 // PMP pin
#define TFT_D14 GPIO_PD2 // PMP pin
#define TFT_D15 GPIO_PD3 // PMP pin

#define TFT_8BIT_DATA_PORT_CH0 GPIO_PORT_E
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 GPIO_PORT_E
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA GPIO_PA15
#define CTP_SCL GPIO_PA14
#define CTP_INT GPIO_PB15
#define CTP_WAKE GPIO_PH14
#define CTP_RST HAL_PIN_NC

#define NRF_CE GPIO_PH0
#define NRF_CS GPIO_PH1
#define NRF_SCK GPIO_PB14
#define NRF_SDI GPIO_PC1
#define NRF_SDO GPIO_PD10
#define NRF_INT GPIO_PD5

#define ETH_RXER GPIO_PH4
#define ETH_TXD0 GPIO_PJ8
#define ETH_TDD1 GPIO_PJ9
#define ETH_RXD0 GPIO_PH8
#define ETH_RXD1 GPIO_PH5
#define ETH_TXEN GPIO_PD6
#define ETH_CRS_DV GPIO_PH13
#define ETH_MDIO GPIO_PJ1
#define ETH_RST GPIO_PH3
#define ETH_CLKO GPIO_PJ11
#define ETH_MDC GPIO_PD11
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID GPIO_PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW GPIO_PJ3

#define SD_CS GPIO_PG14
#define SD_MOSI GPIO_PG10
#define SD_SCK GPIO_PF13
#define SD_MISO GPIO_PB5
#define SD_CD GPIO_PG12

#define FLASH_CS GPIO_PH2
#define FLASH_MISO GPIO_PB5
#define FLASH_SCK GPIO_PF13
#define FLASH_MOSI GPIO_PB10

#define MP3_SCLK GPIO_PB14
#define MP3_SIN GPIO_PC1
#define MP3_SOUT GPIO_PD10
#define MP3_CS GPIO_PK0
#define MP3_RST GPIO_PJ13
#define MP3_DREQ GPIO_PJ14
#define MP3_DCS GPIO_PJ15

#define ALS_SDA GPIO_PA15
#define ALS_SCL GPIO_PA14

#define ACCEL_SDA GPIO_PA15
#define ACCEL_SCL GPIO_PA14
#define ACCEL_INT2 GPIO_PD9
#define ACCEL_INT1 GPIO_PD7

#define BUZZER GPIO_PK2

#define IR_TX GPIO_PJ6

#define LED_R GPIO_PB2
#define LED_G GPIO_PB1
#define LED_B GPIO_PB0

#define TEMP_SENS GPIO_PG15

#define CAN_RX GPIO_PD15
#define CAN_TX GPIO_PD14

#define POWER_BAT_SENSE GPIO_PA5
#define POWER_STATUS GPIO_PJ12
#define POWER_DC_DETECT GPIO_PJ10

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define SHIELD_CONNECTOR_J1_PIN3 GPIO_PA0
#define SHIELD_CONNECTOR_J1_PIN4 GPIO_PB11
#define SHIELD_CONNECTOR_J1_PIN5 GPIO_PA1
#define SHIELD_CONNECTOR_J1_PIN6 GPIO_PB12
#define SHIELD_CONNECTOR_J1_PIN7 GPIO_PB13
#define SHIELD_CONNECTOR_J1_PIN8 GPIO_PH6
#define SHIELD_CONNECTOR_J1_PIN9 GPIO_PK4
#define SHIELD_CONNECTOR_J1_PIN10 GPIO_PK5
#define SHIELD_CONNECTOR_J1_PIN11 GPIO_PB4
#define SHIELD_CONNECTOR_J1_PIN12 GPIO_PG6
#define SHIELD_CONNECTOR_J1_PIN13 GPIO_PG7
#define SHIELD_CONNECTOR_J1_PIN14 GPIO_PG8
#define SHIELD_CONNECTOR_J1_PIN15 GPIO_PD15
#define SHIELD_CONNECTOR_J1_PIN16 GPIO_PD14
#define SHIELD_CONNECTOR_J1_PIN17 GPIO_PK1
#define SHIELD_CONNECTOR_J1_PIN18 GPIO_PD1
#define SHIELD_CONNECTOR_J1_PIN19 GPIO_PF4
#define SHIELD_CONNECTOR_J1_PIN20 GPIO_PF5

#define SHIELD_CONNECTOR_J2_PIN7 GPIO_PF12
#define SHIELD_CONNECTOR_J2_PIN8 GPIO_PC2
#define SHIELD_CONNECTOR_J2_PIN9 GPIO_PB8
#define SHIELD_CONNECTOR_J2_PIN10 GPIO_PB3
#define SHIELD_CONNECTOR_J2_PIN11 GPIO_PB9
#define SHIELD_CONNECTOR_J2_PIN12 HAL_PIN_NC
#define SHIELD_CONNECTOR_J2_PIN13 GPIO_PC3
#define SHIELD_CONNECTOR_J2_PIN14 GPIO_PC4
#define SHIELD_CONNECTOR_J2_PIN15 GPIO_PC14
#define SHIELD_CONNECTOR_J2_PIN16 GPIO_PG9
#define SHIELD_CONNECTOR_J2_PIN17 GPIO_PA2
#define SHIELD_CONNECTOR_J2_PIN18 GPIO_PA3
#define SHIELD_CONNECTOR_J2_PIN19 GPIO_PD4
#define SHIELD_CONNECTOR_J2_PIN20 GPIO_PD0
#define SHIELD_CONNECTOR_J2_PIN21 GPIO_PE8
#define SHIELD_CONNECTOR_J2_PIN22 GPIO_PE9
#define SHIELD_CONNECTOR_J2_PIN23 GPIO_PF8
#define SHIELD_CONNECTOR_J2_PIN24 GPIO_PF2

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
