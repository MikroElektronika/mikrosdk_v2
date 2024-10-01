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

#define BOARD_NAME "Mikromedia 3 for PIC32MZ Resistive"

/// Mapping
#define TFT_RST PG14
#define TFT_CS PG12
#define TFT_D_C PG13
#define TFT_RD PC4
#define TFT_WR PC3
#define TFT_TE PD13
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 PE0
#define TFT_D1 PE1
#define TFT_D2 PE2
#define TFT_D3 PE3
#define TFT_D4 PE4
#define TFT_D5 PE5
#define TFT_D6 PE6
#define TFT_D7 PE7
#define TFT_D8 HAL_PIN_NC
#define TFT_D9 HAL_PIN_NC
#define TFT_D10 HAL_PIN_NC
#define TFT_D11 HAL_PIN_NC
#define TFT_D12 HAL_PIN_NC
#define TFT_D13 HAL_PIN_NC
#define TFT_D14 HAL_PIN_NC
#define TFT_D15 HAL_PIN_NC

#define TFT_8BIT_DATA_PORT_CH0 PORT_E
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PA15
#define CTP_SCL PA14
#define CTP_INT PF1
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define USB_SW_ID PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW PB13

#define SD_CS PA4
#define SD_MOSI PG8
#define SD_SCK PG6
#define SD_MISO PG7
#define SD_CD PF8

#define FLASH_CS PD9
#define FLASH_MISO PG7
#define FLASH_SCK PG6
#define FLASH_MOSI PG8

#define MP3_SCLK PD1
#define MP3_SIN PD3
#define MP3_SOUT PD2
#define MP3_CS PG1
#define MP3_RST PG0
#define MP3_DREQ PA6
#define MP3_DCS PA7

#define ALS_SDA PA15
#define ALS_SCL PA14

#define ACCEL_SDA PA15
#define ACCEL_SCL PA14
#define ACCEL_INT2 PD11
#define ACCEL_INT1 PD10

#define TEMP_SENS PG15

#define POWER_BAT_SENSE PA5
#define POWER_STATUS PB11
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define SHIELD_CONNECTOR_J1_PIN3 PA0
#define SHIELD_CONNECTOR_J1_PIN4 PB4
#define SHIELD_CONNECTOR_J1_PIN5 PA1
#define SHIELD_CONNECTOR_J1_PIN6 PF13
#define SHIELD_CONNECTOR_J1_PIN7 PF12
#define SHIELD_CONNECTOR_J1_PIN8 PB12
#define SHIELD_CONNECTOR_J1_PIN9 PB3
#define SHIELD_CONNECTOR_J1_PIN10 PB2
#define SHIELD_CONNECTOR_J1_PIN11 PG9
#define SHIELD_CONNECTOR_J1_PIN12 PG6
#define SHIELD_CONNECTOR_J1_PIN13 PG7
#define SHIELD_CONNECTOR_J1_PIN14 PG8
#define SHIELD_CONNECTOR_J1_PIN15 PB15
#define SHIELD_CONNECTOR_J1_PIN16 PC2
#define SHIELD_CONNECTOR_J1_PIN17 PD12
#define SHIELD_CONNECTOR_J1_PIN18 PD1
#define SHIELD_CONNECTOR_J1_PIN19 PD2
#define SHIELD_CONNECTOR_J1_PIN20 PD3
#define SHIELD_CONNECTOR_J1_PIN21 PC1
#define SHIELD_CONNECTOR_J1_PIN22 PB14
#define SHIELD_CONNECTOR_J1_PIN23 PD14
#define SHIELD_CONNECTOR_J1_PIN24 PD15

#define SHIELD_CONNECTOR_J2_PIN7 PB5
#define SHIELD_CONNECTOR_J2_PIN8 PB1
#define SHIELD_CONNECTOR_J2_PIN9 PB0
#define SHIELD_CONNECTOR_J2_PIN10 PB8
#define SHIELD_CONNECTOR_J2_PIN11 PB9
#define SHIELD_CONNECTOR_J2_PIN12 PB10
#define SHIELD_CONNECTOR_J2_PIN13 PD0
#define SHIELD_CONNECTOR_J2_PIN14 PD4
#define SHIELD_CONNECTOR_J2_PIN15 PD5
#define SHIELD_CONNECTOR_J2_PIN16 PF0
#define SHIELD_CONNECTOR_J2_PIN17 PA2
#define SHIELD_CONNECTOR_J2_PIN18 PA3
#define SHIELD_CONNECTOR_J2_PIN19 PF4
#define SHIELD_CONNECTOR_J2_PIN20 PF5
#define SHIELD_CONNECTOR_J2_PIN21 PE8
#define SHIELD_CONNECTOR_J2_PIN22 PE9
#define SHIELD_CONNECTOR_J2_PIN23 PA14
#define SHIELD_CONNECTOR_J2_PIN24 PA15

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
