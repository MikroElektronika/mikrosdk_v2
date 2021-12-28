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
#include "shield.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia 3 for Kinetis Capacitive"

/// Mapping
#define TFT_RST PC12
#define TFT_CS PC13
#define TFT_D_C PC14
#define TFT_RD PC15
#define TFT_WR PC16
#define TFT_TE PC17
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 PC0
#define TFT_D1 PC1
#define TFT_D2 PC2
#define TFT_D3 PC3
#define TFT_D4 PC4
#define TFT_D5 PC5
#define TFT_D6 PC6
#define TFT_D7 PC7
#define TFT_D8 HAL_PIN_NC
#define TFT_D9 HAL_PIN_NC
#define TFT_D10 HAL_PIN_NC
#define TFT_D11 HAL_PIN_NC
#define TFT_D12 HAL_PIN_NC
#define TFT_D13 HAL_PIN_NC
#define TFT_D14 HAL_PIN_NC
#define TFT_D15 HAL_PIN_NC

#define TFT_8BIT_DATA_PORT_CH0 PORT_C
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x00FF

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define CTP_SDA PB1
#define CTP_SCL PB0
#define CTP_INT PE26
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define USB_SW_ID PA29
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW PB13

#define SDIO_DAT0 PE1
#define SDIO_DAT1 PE0
#define SDIO_DAT2 PE5
#define SDIO_DAT3 PE4
#define SDIO_CLK PE2
#define SDIO_CMD PE3
#define SDIO_CD PE6

#define FLASH_CS PD10
#define FLASH_MISO PB17
#define FLASH_SCK PB11
#define FLASH_MOSI PB16

#define MP3_SCLK PD1
#define MP3_SIN PD2
#define MP3_SOUT PD3
#define MP3_CS PA14
#define MP3_RST PA15
#define MP3_DREQ PA16
#define MP3_DCS PA17

#define ALS_SDA PB1
#define ALS_SCL PB0

#define ACCEL_SDA PB1
#define ACCEL_SCL PB0
#define ACCEL_INT2 PC19
#define ACCEL_INT1 PC18

#define TEMP_SENS PE25

#define POWER_BAT_SENSE PE24
#define POWER_STATUS PB12
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define SHIELD_CONNECTOR_J1_PIN3 PB2
#define SHIELD_CONNECTOR_J1_PIN4 PB3
#define SHIELD_CONNECTOR_J1_PIN5 PB6
#define SHIELD_CONNECTOR_J1_PIN6 PB7
#define SHIELD_CONNECTOR_J1_PIN7 PC8
#define SHIELD_CONNECTOR_J1_PIN8 PC9
#define SHIELD_CONNECTOR_J1_PIN9 PB8
#define SHIELD_CONNECTOR_J1_PIN10 PB9
#define SHIELD_CONNECTOR_J1_PIN11 PB10
#define SHIELD_CONNECTOR_J1_PIN12 PB11
#define SHIELD_CONNECTOR_J1_PIN13 PB17
#define SHIELD_CONNECTOR_J1_PIN14 PB16
#define SHIELD_CONNECTOR_J1_PIN15 PA13
#define SHIELD_CONNECTOR_J1_PIN16 PA12
#define SHIELD_CONNECTOR_J1_PIN17 PD0
#define SHIELD_CONNECTOR_J1_PIN18 PD1
#define SHIELD_CONNECTOR_J1_PIN19 PD3
#define SHIELD_CONNECTOR_J1_PIN20 PD2
#define SHIELD_CONNECTOR_J1_PIN21 PD11
#define SHIELD_CONNECTOR_J1_PIN22 PD12
#define SHIELD_CONNECTOR_J1_PIN23 PD14
#define SHIELD_CONNECTOR_J1_PIN24 PD13

#define SHIELD_CONNECTOR_J2_PIN7 PA11
#define SHIELD_CONNECTOR_J2_PIN8 PB18
#define SHIELD_CONNECTOR_J2_PIN9 PB19
#define SHIELD_CONNECTOR_J2_PIN10 PD4
#define SHIELD_CONNECTOR_J2_PIN11 PD5
#define SHIELD_CONNECTOR_J2_PIN12 PA10
#define SHIELD_CONNECTOR_J2_PIN13 PB20
#define SHIELD_CONNECTOR_J2_PIN14 PB21
#define SHIELD_CONNECTOR_J2_PIN15 PB22
#define SHIELD_CONNECTOR_J2_PIN16 PB23
#define SHIELD_CONNECTOR_J2_PIN17 PC10
#define SHIELD_CONNECTOR_J2_PIN18 PC11
#define SHIELD_CONNECTOR_J2_PIN19 PD8
#define SHIELD_CONNECTOR_J2_PIN20 PD9
#define SHIELD_CONNECTOR_J2_PIN21 PD6
#define SHIELD_CONNECTOR_J2_PIN22 PD7
#define SHIELD_CONNECTOR_J2_PIN23 PB0
#define SHIELD_CONNECTOR_J2_PIN24 PB1

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
