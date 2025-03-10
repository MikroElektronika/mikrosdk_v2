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
#define BOARD_REV_MINOR (02)

#define BOARD_NAME "Mikromedia 3 for STM32F4 Resistive - FPI"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PC2
#define MIKROBUS_1_RST GPIO_PC3
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

#define TFT_RST GPIO_PE14
#define TFT_CS GPIO_PE13
#define TFT_D_C GPIO_PE15
#define TFT_RD GPIO_PE12
#define TFT_WR GPIO_PE11
#define TFT_TE GPIO_PD4
#define TFT_D0 GPIO_PE0
#define TFT_D1 GPIO_PE1
#define TFT_D2 GPIO_PE2
#define TFT_D3 GPIO_PE3
#define TFT_D4 GPIO_PE4
#define TFT_D5 GPIO_PE5
#define TFT_D6 GPIO_PE6
#define TFT_D7 GPIO_PE7

#define LCD_TFT_8BIT_CH0 GPIO_PORT_E
#define TFT_8BIT_DATA_PORT_CH0 LCD_TFT_8BIT_CH0
#define LCD_TFT_8BIT_CH0_MASK 0x00FF
#define TFT_8BIT_DATA_PORT_CH0_MASK LCD_TFT_8BIT_CH0_MASK

#define LCD_TFT_16BIT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0 LCD_TFT_16BIT_CH0
#define LCD_TFT_16BIT_CH0_MASK 0x0000
#define TFT_16BIT_DATA_PORT_CH0_MASK LCD_TFT_16BIT_CH0_MASK

#define LCD_TFT_16BIT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1 LCD_TFT_16BIT_CH1
#define LCD_TFT_16BIT_CH1_MASK 0x0000
#define TFT_16BIT_DATA_PORT_CH1_MASK LCD_TFT_16BIT_CH1_MASK

#define CTP_SDA GPIO_PB7
#define CTP_SCL GPIO_PB6
#define CTP_INT GPIO_PH1

#define USB_SW_ID GPIO_PA10
#define USB_VBUS GPIO_PA9
#define USB_N GPIO_PA11
#define USB_P GPIO_PA12
#define USB_PSW GPIO_PD6

#define SDIO_DAT0 GPIO_PC8
#define SDIO_DAT1 GPIO_PC9
#define SDIO_DAT2 GPIO_PC10
#define SDIO_DAT3 GPIO_PC11
#define SDIO_CLK GPIO_PC12
#define SDIO_CMD GPIO_PD2
#define SDIO_CD GPIO_PD3

#define FLASH_CS GPIO_PE8
#define FLASH_MISO GPIO_PB14
#define FLASH_SCK GPIO_PB13
#define FLASH_MOSI GPIO_PB15

#define MP3_SCLK GPIO_PA5
#define MP3_SIN GPIO_PA6
#define MP3_SOUT GPIO_PA7
#define MP3_CS GPIO_PD11
#define MP3_RST GPIO_PD8
#define MP3_DREQ GPIO_PD9
#define MP3_DCS GPIO_PD10

#define ALS_SDA GPIO_PB7
#define ALS_SCL GPIO_PB6

#define ACCEL_SDA GPIO_PB7
#define ACCEL_SCL GPIO_PB6
#define ACCEL_INT1 GPIO_PB9
#define ACCEL_INT2 GPIO_PB8

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
