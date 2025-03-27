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

#include "mikrobus.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Mikromedia 3 for PIC32MZ Resistive - FPI"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PA0
#define MIKROBUS_1_RST GPIO_PF0
#define MIKROBUS_1_CS GPIO_PB15
#define MIKROBUS_1_SCK GPIO_PB14
#define MIKROBUS_1_MISO GPIO_PD14
#define MIKROBUS_1_MOSI GPIO_PD15
#define MIKROBUS_1_PWM GPIO_PB5
#define MIKROBUS_1_INT GPIO_PD0
#define MIKROBUS_1_RX GPIO_PE8
#define MIKROBUS_1_TX GPIO_PE9
#define MIKROBUS_1_SCL GPIO_PA2
#define MIKROBUS_1_SDA GPIO_PA3

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PB4
#define MIKROBUS_2_RST GPIO_PF2
#define MIKROBUS_2_CS GPIO_PB9
#define MIKROBUS_2_SCK GPIO_PF13
#define MIKROBUS_2_MISO GPIO_PB10
#define MIKROBUS_2_MOSI GPIO_PB3
#define MIKROBUS_2_PWM GPIO_PB1
#define MIKROBUS_2_INT GPIO_PD4
#define MIKROBUS_2_RX GPIO_PB0
#define MIKROBUS_2_TX GPIO_PB2
#define MIKROBUS_2_SCL GPIO_PF5
#define MIKROBUS_2_SDA GPIO_PF4

#define TFT_RST GPIO_PG14
#define TFT_CS GPIO_PG12
#define TFT_D_C GPIO_PG13
#define TFT_RD GPIO_PC4
#define TFT_WR GPIO_PC3
#define TFT_TE GPIO_PD13
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 GPIO_PE0
#define TFT_D1 GPIO_PE1
#define TFT_D2 GPIO_PE2
#define TFT_D3 GPIO_PE3
#define TFT_D4 GPIO_PE4
#define TFT_D5 GPIO_PE5
#define TFT_D6 GPIO_PE6
#define TFT_D7 GPIO_PE7
#define TFT_D8 HAL_PIN_NC
#define TFT_D9 HAL_PIN_NC
#define TFT_D10 HAL_PIN_NC
#define TFT_D11 HAL_PIN_NC
#define TFT_D12 HAL_PIN_NC
#define TFT_D13 HAL_PIN_NC
#define TFT_D14 HAL_PIN_NC
#define TFT_D15 HAL_PIN_NC

#define LCD_TFT_8BIT_CH0 GPIO_PORT_E
#define TFT_8BIT_DATA_PORT_CH0 LCD_TFT_8BIT_CH0
#define LCD_TFT_8BIT_CH0_MASK 0x00FF
#define TFT_8BIT_DATA_PORT_CH0_MASK LCD_TFT_8BIT_CH0_MASK

#define LCD_TFT_16BIT_CH0 GPIO_PORT_E
#define TFT_16BIT_DATA_PORT_CH0 LCD_TFT_16BIT_CH0
#define LCD_TFT_16BIT_CH0_MASK 0x00FF
#define TFT_16BIT_DATA_PORT_CH0_MASK LCD_TFT_16BIT_CH0_MASK

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1 LCD_TFT_16BIT_CH1
#define LCD_TFT_16BIT_CH1_MASK 0x0000
#define TFT_16BIT_DATA_PORT_CH1_MASK LCD_TFT_16BIT_CH1_MASK

#define CTP_SDA GPIO_PA15
#define CTP_SCL GPIO_PA14
#define CTP_INT GPIO_PF1
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define NRF_CE HAL_PIN_NC
#define NRF_CS HAL_PIN_NC
#define NRF_SCK HAL_PIN_NC
#define NRF_SDI HAL_PIN_NC
#define NRF_SDO HAL_PIN_NC
#define NRF_INT HAL_PIN_NC

#define USB_SW_ID GPIO_PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW GPIO_PB13

#define SD_CS GPIO_PA4
#define SD_MOSI GPIO_PG8
#define SD_SCK GPIO_PG6
#define SD_MISO GPIO_PG7
#define SD_CD GPIO_PF8

#define FLASH_CS GPIO_PD9
#define FLASH_MISO GPIO_PG7
#define FLASH_SCK GPIO_PG6
#define FLASH_MOSI GPIO_PG8

#define MP3_SCLK GPIO_PD1
#define MP3_SIN GPIO_PD3
#define MP3_SOUT GPIO_PD2
#define MP3_CS GPIO_PG1
#define MP3_RST GPIO_PG0
#define MP3_DREQ GPIO_PA6
#define MP3_DCS GPIO_PA7

#define ACCEL_SDA GPIO_PA15
#define ACCEL_SCL GPIO_PA14
#define ACCEL_INT2 GPIO_PD11
#define ACCEL_INT1 GPIO_PD10

#define BUZZER HAL_PIN_NC

#define POWER_BAT_SENSE GPIO_PA5
#define POWER_STATUS GPIO_PB11
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
