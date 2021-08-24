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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Mikromedia 3 for STM32F2 Capacitive - FPI"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PC2
#define MIKROBUS_1_RST PC3
#define MIKROBUS_1_CS PB5
#define MIKROBUS_1_SCK PA5
#define MIKROBUS_1_MISO PA6
#define MIKROBUS_1_MOSI PA7
#define MIKROBUS_1_PWM PD15
#define MIKROBUS_1_INT PD7
#define MIKROBUS_1_RX PA3
#define MIKROBUS_1_TX PD5
#define MIKROBUS_1_SCL PB10
#define MIKROBUS_1_SDA PB11

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PC1
#define MIKROBUS_2_RST PD12
#define MIKROBUS_2_CS PC0
#define MIKROBUS_2_SCK PA5
#define MIKROBUS_2_MISO PA6
#define MIKROBUS_2_MOSI PA7
#define MIKROBUS_2_PWM PD14
#define MIKROBUS_2_INT PD1
#define MIKROBUS_2_RX PC7
#define MIKROBUS_2_TX PC6
#define MIKROBUS_2_SCL PB10
#define MIKROBUS_2_SDA PB11

#define TFT_RST PE14
#define TFT_CS PE13
#define TFT_D_C PE15
#define TFT_RD PE12
#define TFT_WR PE11
#define TFT_TE PD4
#define TFT_D0 PE0
#define TFT_D1 PE1
#define TFT_D2 PE2
#define TFT_D3 PE3
#define TFT_D4 PE4
#define TFT_D5 PE5
#define TFT_D6 PE6
#define TFT_D7 PE7

#define TFT_8BIT_DATA_PORT_CH0 PORT_E
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PB7
#define CTP_SCL PB6
#define CTP_INT PH1

#define USB_SW_ID PA10
#define USB_VBUS PA9
#define USB_N PA11
#define USB_P PA12
#define USB_PSW PD6

#define SDIO_DAT0 PC8
#define SDIO_DAT1 PC9
#define SDIO_DAT2 PC10
#define SDIO_DAT3 PC11
#define SDIO_CLK PC12
#define SDIO_CMD PD2
#define SDIO_CD PD3

#define FLASH_CS PE8
#define FLASH_MISO PB14
#define FLASH_SCK PB13
#define FLASH_MOSI PB15

#define MP3_SCLK PA5
#define MP3_SIN PA6
#define MP3_SOUT PA7
#define MP3_CS PD11
#define MP3_RST PD8
#define MP3_DREQ PD9
#define MP3_DCS PD10

#define ALS_SDA PB7
#define ALS_SCL PB6

#define ACCEL_SDA PB7
#define ACCEL_SCL PB6
#define ACCEL_INT1 PB9
#define ACCEL_INT2 PB8

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
