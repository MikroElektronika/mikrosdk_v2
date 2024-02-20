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
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Mikromedia 3 for PIC Capacitive"

/// Mapping
#define TFT_RST PK1
#define TFT_CS PK2
#define TFT_D_C PK3
#define TFT_RD PK4
#define TFT_WR PK5
#define TFT_TE PK6
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 PJ0
#define TFT_D1 PJ1
#define TFT_D2 PJ2
#define TFT_D3 PJ3
#define TFT_D4 PJ4
#define TFT_D5 PJ5
#define TFT_D6 PJ6
#define TFT_D7 PJ7
#define TFT_D8 HAL_PIN_NC
#define TFT_D9 HAL_PIN_NC
#define TFT_D10 HAL_PIN_NC
#define TFT_D11 HAL_PIN_NC
#define TFT_D12 HAL_PIN_NC
#define TFT_D13 HAL_PIN_NC
#define TFT_D14 HAL_PIN_NC
#define TFT_D15 HAL_PIN_NC

#define TFT_8BIT_DATA_PORT_CH0 PORT_J
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PC4
#define CTP_SCL PC3
#define CTP_INT PE6
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define USB_SW_ID HAL_PIN_NC
#define USB_VBUS HAL_PIN_NC
#define USB_N PF3
#define USB_P PF4
#define USB_PSW HAL_PIN_NC

#define SD_CS PL5
#define SD_MOSI PC5
#define SD_SCK PC6
#define SD_MISO PE1
#define SD_CD PL4

#define FLASH_CS PL2
#define FLASH_MISO PE1
#define FLASH_SCK PC6
#define FLASH_MOSI PC5

#define MP3_SCLK PC6
#define MP3_SIN PE1
#define MP3_SOUT PC5
#define MP3_CS PG6
#define MP3_RST PD0
#define MP3_DREQ PL0
#define MP3_DCS PE7

#define ALS_SDA PC4
#define ALS_SCL PC3

#define ACCEL_SDA PC4
#define ACCEL_SCL PC3
#define ACCEL_INT2 PE3
#define ACCEL_INT1 PE2

#define TEMP_SENS PH3

#define POWER_BAT_SENSE PH2
#define POWER_STATUS PL6
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define SHIELD_CONNECTOR_J1_PIN3 PH7
#define SHIELD_CONNECTOR_J1_PIN4 PH6
#define SHIELD_CONNECTOR_J1_PIN5 PH5
#define SHIELD_CONNECTOR_J1_PIN6 PH4
#define SHIELD_CONNECTOR_J1_PIN7 PH0
#define SHIELD_CONNECTOR_J1_PIN8 PH1
#define SHIELD_CONNECTOR_J1_PIN9 PL7
#define SHIELD_CONNECTOR_J1_PIN10 PK0
#define SHIELD_CONNECTOR_J1_PIN11 PF2
#define SHIELD_CONNECTOR_J1_PIN12 PC6
#define SHIELD_CONNECTOR_J1_PIN13 PE1
#define SHIELD_CONNECTOR_J1_PIN14 PC5
#define SHIELD_CONNECTOR_J1_PIN15 PF5
#define SHIELD_CONNECTOR_J1_PIN16 PE0
#define SHIELD_CONNECTOR_J1_PIN17 PG0
#define SHIELD_CONNECTOR_J1_PIN18 PD7
#define SHIELD_CONNECTOR_J1_PIN19 PD4
#define SHIELD_CONNECTOR_J1_PIN20 PB1
#define SHIELD_CONNECTOR_J1_PIN21 PB2
#define SHIELD_CONNECTOR_J1_PIN22 PB3
#define SHIELD_CONNECTOR_J1_PIN23 PB4
#define SHIELD_CONNECTOR_J1_PIN24 PB5

#define SHIELD_CONNECTOR_J2_PIN7 PG4
#define SHIELD_CONNECTOR_J2_PIN8 PF6
#define SHIELD_CONNECTOR_J2_PIN9 PC7
#define SHIELD_CONNECTOR_J2_PIN10 PC2
#define SHIELD_CONNECTOR_J2_PIN11 PG3
#define SHIELD_CONNECTOR_J2_PIN12 PD2
#define SHIELD_CONNECTOR_J2_PIN13 PG1
#define SHIELD_CONNECTOR_J2_PIN14 PF7
#define SHIELD_CONNECTOR_J2_PIN15 PE5
#define SHIELD_CONNECTOR_J2_PIN16 PB0
#define SHIELD_CONNECTOR_J2_PIN17 PD6
#define SHIELD_CONNECTOR_J2_PIN18 PD5
#define SHIELD_CONNECTOR_J2_PIN19 PA4
#define SHIELD_CONNECTOR_J2_PIN20 PA5
#define SHIELD_CONNECTOR_J2_PIN21 PA0
#define SHIELD_CONNECTOR_J2_PIN22 PA1
#define SHIELD_CONNECTOR_J2_PIN23 PC3
#define SHIELD_CONNECTOR_J2_PIN24 PC4

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
