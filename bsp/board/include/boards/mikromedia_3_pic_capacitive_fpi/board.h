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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (02)

#include "mikrobus.h"

#define BOARD_NAME "Mikromedia 3 for PIC Capacitive FPI"

#define MIKROBUS_1 1
#define MIKROBUS_1_AN PH7
#define MIKROBUS_1_RST PH3
#define MIKROBUS_1_CS PG0
#define MIKROBUS_1_SCK PD7
#define MIKROBUS_1_MISO PD4
#define MIKROBUS_1_MOSI PB1
#define MIKROBUS_1_PWM PG4
#define MIKROBUS_1_INT PB0
#define MIKROBUS_1_RX PA0
#define MIKROBUS_1_TX PA1
#define MIKROBUS_1_SCL PD6
#define MIKROBUS_1_SDA PD5

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PH6
#define MIKROBUS_2_RST PE0
#define MIKROBUS_2_CS PF2
#define MIKROBUS_2_SCK PD7
#define MIKROBUS_2_MISO PD4
#define MIKROBUS_2_MOSI PB1
#define MIKROBUS_2_PWM PF6
#define MIKROBUS_2_INT PG1
#define MIKROBUS_2_RX PA4
#define MIKROBUS_2_TX PA5
#define MIKROBUS_2_SCL PD6
#define MIKROBUS_2_SDA PD5

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

#define POWER_BAT_SENSE PH2
#define POWER_STATUS PL6
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
