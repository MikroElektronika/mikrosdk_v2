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

#include "mikrobus.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Mikromedia 4 for PIC32MZ Capacitive - FPI"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PA0
#define MIKROBUS_1_RST PH4
#define MIKROBUS_1_CS PK1
#define MIKROBUS_1_SCK PD1
#define MIKROBUS_1_MISO PD6
#define MIKROBUS_1_MOSI PD7
#define MIKROBUS_1_PWM PF12
#define MIKROBUS_1_INT PD9
#define MIKROBUS_1_RX PE8
#define MIKROBUS_1_TX PE9
#define MIKROBUS_1_SCL PA14
#define MIKROBUS_1_SDA PA15

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PB11
#define MIKROBUS_2_RST PH5
#define MIKROBUS_2_CS PK2
#define MIKROBUS_2_SCK PG6
#define MIKROBUS_2_MISO PG7
#define MIKROBUS_2_MOSI PG8
#define MIKROBUS_2_PWM PC2
#define MIKROBUS_2_INT PG9
#define MIKROBUS_2_RX PD4
#define MIKROBUS_2_TX PD0
#define MIKROBUS_2_SCL PA2
#define MIKROBUS_2_SDA PA3

#define TFT_RST PH9
#define TFT_CS PH10
#define TFT_D_C PH11
#define TFT_RD PC4
#define TFT_WR PC3
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

#define USB_SW_ID PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW PJ3

#define SD_CS PG14
#define SD_MOSI PB10
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

#define ACCEL_SDA PA15
#define ACCEL_SCL PA14
#define ACCEL_INT2 PF5
#define ACCEL_INT1 PF4

#define BUZZER PB2

#define POWER_BAT_SENSE PA5
#define POWER_STATUS PJ12
#define POWER_DC_DETECT PJ10

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
