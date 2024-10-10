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

#include "mikrobus.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Mikromedia 3 for PIC32MZ Resistive - FPI"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PA0
#define MIKROBUS_1_RST PF0
#define MIKROBUS_1_CS PB15
#define MIKROBUS_1_SCK PB14
#define MIKROBUS_1_MISO PD14
#define MIKROBUS_1_MOSI PD15
#define MIKROBUS_1_PWM PB5
#define MIKROBUS_1_INT PD0
#define MIKROBUS_1_RX PE8
#define MIKROBUS_1_TX PE9
#define MIKROBUS_1_SCL PA2
#define MIKROBUS_1_SDA PA3

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PB4
#define MIKROBUS_2_RST PF2
#define MIKROBUS_2_CS PB9
#define MIKROBUS_2_SCK PF13
#define MIKROBUS_2_MISO PB10
#define MIKROBUS_2_MOSI PB3
#define MIKROBUS_2_PWM PB1
#define MIKROBUS_2_INT PD4
#define MIKROBUS_2_RX PB0
#define MIKROBUS_2_TX PB2
#define MIKROBUS_2_SCL PF5
#define MIKROBUS_2_SDA PF4

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

#define TFT_16BIT_DATA_PORT_CH0 PORT_E
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PA15
#define CTP_SCL PA14
#define CTP_INT PF1
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define NRF_CE HAL_PIN_NC
#define NRF_CS HAL_PIN_NC
#define NRF_SCK HAL_PIN_NC
#define NRF_SDI HAL_PIN_NC
#define NRF_SDO HAL_PIN_NC
#define NRF_INT HAL_PIN_NC

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

#define ACCEL_SDA PA15
#define ACCEL_SCL PA14
#define ACCEL_INT2 PD11
#define ACCEL_INT1 PD10

#define BUZZER HAL_PIN_NC

#define POWER_BAT_SENSE PA5
#define POWER_STATUS PB11
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
