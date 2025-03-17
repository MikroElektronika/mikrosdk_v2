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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia 4 for Kinetis Resistive - FPI"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PB2
#define MIKROBUS_1_RST GPIO_PE11
#define MIKROBUS_1_CS GPIO_PB10
#define MIKROBUS_1_SCK GPIO_PB11
#define MIKROBUS_1_MISO GPIO_PB17
#define MIKROBUS_1_MOSI GPIO_PB16
#define MIKROBUS_1_PWM GPIO_PE7
#define MIKROBUS_1_INT GPIO_PC5
#define MIKROBUS_1_RX GPIO_PC3
#define MIKROBUS_1_TX GPIO_PC4
#define MIKROBUS_1_SCL GPIO_PC10
#define MIKROBUS_1_SDA GPIO_PC11

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PB3
#define MIKROBUS_2_RST GPIO_PE12
#define MIKROBUS_2_CS GPIO_PA14
#define MIKROBUS_2_SCK GPIO_PA15
#define MIKROBUS_2_MISO GPIO_PA17
#define MIKROBUS_2_MOSI GPIO_PA16
#define MIKROBUS_2_PWM GPIO_PE8
#define MIKROBUS_2_INT GPIO_PC6
#define MIKROBUS_2_RX GPIO_PC14
#define MIKROBUS_2_TX GPIO_PC15
#define MIKROBUS_2_SCL GPIO_PA12
#define MIKROBUS_2_SDA GPIO_PA13

#define TFT_RST GPIO_PA25
#define TFT_CS GPIO_PA26
#define TFT_D_C GPIO_PA27
#define TFT_RD GPIO_PA28
#define TFT_WR GPIO_PA29
#define TFT_TE GPIO_PB8
#define TFT_GPIO GPIO_PB9
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 GPIO_PD0
#define TFT_D1 GPIO_PD1
#define TFT_D2 GPIO_PD2
#define TFT_D3 GPIO_PD3
#define TFT_D4 GPIO_PD4
#define TFT_D5 GPIO_PD5
#define TFT_D6 GPIO_PD6
#define TFT_D7 GPIO_PD7
#define TFT_D8 GPIO_PD8
#define TFT_D9 GPIO_PD9
#define TFT_D10 GPIO_PD10
#define TFT_D11 GPIO_PD11
#define TFT_D12 GPIO_PD12
#define TFT_D13 GPIO_PD13
#define TFT_D14 GPIO_PD14
#define TFT_D15 GPIO_PD15

#define LCD_TFT_8BIT_CH0 GPIO_PORT_D
#define TFT_8BIT_DATA_PORT_CH0 LCD_TFT_8BIT_CH0
#define LCD_TFT_8BIT_CH0_MASK 0x00FF
#define TFT_8BIT_DATA_PORT_CH0_MASK LCD_TFT_8BIT_CH0_MASK

#define LCD_TFT_16BIT_CH0 GPIO_PORT_D
#define TFT_16BIT_DATA_PORT_CH0 LCD_TFT_16BIT_CH0
#define LCD_TFT_16BIT_CH0_MASK 0x00FF
#define TFT_16BIT_DATA_PORT_CH0_MASK LCD_TFT_16BIT_CH0_MASK

#define LCD_TFT_16BIT_CH1 GPIO_PORT_D
#define TFT_16BIT_DATA_PORT_CH1 LCD_TFT_16BIT_CH1
#define LCD_TFT_16BIT_CH1_MASK 0xFF00
#define TFT_16BIT_DATA_PORT_CH1_MASK LCD_TFT_16BIT_CH1_MASK

#define CTP_SDA GPIO_PB1
#define CTP_SCL GPIO_PB0
#define CTP_INT GPIO_PB19
#define CTP_WAKE GPIO_PB18
#define CTP_RST HAL_PIN_NC

#define NRF_CE HAL_PIN_NC
#define NRF_CS HAL_PIN_NC
#define NRF_SCK HAL_PIN_NC
#define NRF_SDI HAL_PIN_NC
#define NRF_SDO HAL_PIN_NC
#define NRF_INT HAL_PIN_NC

#define ETH_RXER HAL_PIN_NC
#define ETH_TXD0 HAL_PIN_NC
#define ETH_TDD1 HAL_PIN_NC
#define ETH_RXD0 HAL_PIN_NC
#define ETH_RXD1 HAL_PIN_NC
#define ETH_TXEN HAL_PIN_NC
#define ETH_CRS_DV HAL_PIN_NC
#define ETH_MDIO HAL_PIN_NC
#define ETH_RST HAL_PIN_NC
#define ETH_CLKO HAL_PIN_NC
#define ETH_MDC HAL_PIN_NC
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID GPIO_PE10
#define USB_VBUS HAL_PIN_NC
#define USB_N HAL_PIN_NC
#define USB_P HAL_PIN_NC
#define USB_PSW GPIO_PE9

#define SDIO_DAT0 GPIO_PE1
#define SDIO_DAT1 GPIO_PE0
#define SDIO_DAT2 GPIO_PE5
#define SDIO_DAT3 GPIO_PE4
#define SDIO_CLK GPIO_PE2
#define SDIO_CMD GPIO_PE3
#define SDIO_CD GPIO_PE6

#define FLASH_CS GPIO_PA24
#define FLASH_MISO GPIO_PB23
#define FLASH_SCK GPIO_PB21
#define FLASH_MOSI GPIO_PB22

#define MP3_SCLK GPIO_PB21
#define MP3_SIN GPIO_PB22
#define MP3_SOUT GPIO_PB23
#define MP3_CS GPIO_PC9
#define MP3_RST GPIO_PC12
#define MP3_DREQ GPIO_PC13
#define MP3_DCS GPIO_PC16

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA GPIO_PB1
#define ACCEL_SCL GPIO_PB0
#define ACCEL_INT2 GPIO_PC18
#define ACCEL_INT1 GPIO_PC17

#define BUZZER GPIO_PA6

#define IR_TX HAL_PIN_NC

#define LED_RGB_SCL HAL_PIN_NC
#define LED_RGB_SDA HAL_PIN_NC

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX HAL_PIN_NC
#define CAN_TX HAL_PIN_NC

#define POWER_BAT_SENSE GPIO_PB7
#define POWER_STATUS GPIO_PE27
#define POWER_DC_DETECT GPIO_PE28

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
