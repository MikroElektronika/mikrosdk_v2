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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Mikromedia 4 for STM32F2 Resistive - FPI"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PC2
#define MIKROBUS_1_RST GPIO_PD11
#define MIKROBUS_1_CS GPIO_PB5
#define MIKROBUS_1_SCK GPIO_PA5
#define MIKROBUS_1_MISO GPIO_PA6
#define MIKROBUS_1_MOSI GPIO_PA7
#define MIKROBUS_1_PWM GPIO_PD15
#define MIKROBUS_1_INT GPIO_PD7
#define MIKROBUS_1_RX GPIO_PA3
#define MIKROBUS_1_TX GPIO_PD5
#define MIKROBUS_1_SCL GPIO_PB10
#define MIKROBUS_1_SDA GPIO_PB11

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PC1
#define MIKROBUS_2_RST GPIO_PD12
#define MIKROBUS_2_CS GPIO_PC0
#define MIKROBUS_2_SCK GPIO_PA5
#define MIKROBUS_2_MISO GPIO_PA6
#define MIKROBUS_2_MOSI GPIO_PA7
#define MIKROBUS_2_PWM GPIO_PD14
#define MIKROBUS_2_INT GPIO_PD1
#define MIKROBUS_2_RX GPIO_PC7
#define MIKROBUS_2_TX GPIO_PC6
#define MIKROBUS_2_SCL GPIO_PB10
#define MIKROBUS_2_SDA GPIO_PB11

#define TFT_RST GPIO_PA0
#define TFT_CS GPIO_PA1
#define TFT_D_C GPIO_PA4
#define TFT_RD GPIO_PC4
#define TFT_WR GPIO_PC5
#define TFT_TE GPIO_PD4
#define TFT_GPIO GPIO_PB0
#define TFT_D0 GPIO_PE0
#define TFT_D1 GPIO_PE1
#define TFT_D2 GPIO_PE2
#define TFT_D3 GPIO_PE3
#define TFT_D4 GPIO_PE4
#define TFT_D5 GPIO_PE5
#define TFT_D6 GPIO_PE6
#define TFT_D7 GPIO_PE7
#define TFT_D8 GPIO_PE8
#define TFT_D9 GPIO_PE9
#define TFT_D10 GPIO_PE10
#define TFT_D11 GPIO_PE11
#define TFT_D12 GPIO_PE12
#define TFT_D13 GPIO_PE13
#define TFT_D14 GPIO_PE14
#define TFT_D15 GPIO_PE15

#define LCD_TFT_8BIT_CH0 GPIO_PORT_E
#define TFT_8BIT_DATA_PORT_CH0 LCD_TFT_8BIT_CH0
#define LCD_TFT_8BIT_CH0_MASK 0x00FF
#define TFT_8BIT_DATA_PORT_CH0_MASK LCD_TFT_8BIT_CH0_MASK

#define LCD_TFT_16BIT_CH0 GPIO_PORT_E
#define TFT_16BIT_DATA_PORT_CH0 LCD_TFT_16BIT_CH0
#define LCD_TFT_16BIT_CH0_MASK 0xFFFF
#define TFT_16BIT_DATA_PORT_CH0_MASK LCD_TFT_16BIT_CH0_MASK

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1 LCD_TFT_16BIT_CH1
#define LCD_TFT_16BIT_CH1_MASK 0x0000
#define TFT_16BIT_DATA_PORT_CH1_MASK LCD_TFT_16BIT_CH1_MASK

#define CTP_SDA GPIO_PB7
#define CTP_SCL GPIO_PB6
#define CTP_INT GPIO_PA2
#define CTP_WAKE GPIO_PB2

#define NRF_CE GPIO_PD13
#define NRF_CS GPIO_PB4
#define NRF_SCK GPIO_PB13
#define NRF_SDI GPIO_PB15
#define NRF_SDO GPIO_PB14
#define NRF_INT GPIO_PD0

#define USB_SW_ID GPIO_PA10
#define USB_VBUS GPIO_PA9
#define USB_N GPIO_PA11
#define USB_P GPIO_PA12
#define USB_PSW GPIO_PD6

#define SD_CLK GPIO_PC12
#define SD_CMD GPIO_PD2
#define SD_CD GPIO_PD3

#define FLASH_CS GPIO_PC13
#define FLASH_MISO GPIO_PB14
#define FLASH_SCK GPIO_PB13
#define FLASH_MOSI GPIO_PB15

#define MP3_SCLK GPIO_PB13
#define MP3_SIN GPIO_PB15
#define MP3_SOUT GPIO_PB14
#define MP3_CS GPIO_PB3
#define MP3_RST GPIO_PD8
#define MP3_DREQ GPIO_PD9
#define MP3_DCS GPIO_PD10

#define ALS_SDA GPIO_PB7
#define ALS_SCL GPIO_PB6

#define ACCEL_SDA GPIO_PB7
#define ACCEL_SCL GPIO_PB6
#define ACCEL_INT2 GPIO_PA8
#define ACCEL_INT1 GPIO_PB9

#define BUZZER GPIO_PB8

#define POWER_BAT_SENSE GPIO_PC3
#define POWER_STATUS GPIO_PB1
#define POWER_DC_DETECT GPIO_PB12

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
