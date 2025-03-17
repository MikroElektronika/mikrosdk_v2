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

#include "hal_target.h"
#include "shield.h"

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia 4 for Kinetis Resistive"

/// Mapping
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

#define NRF_CE GPIO_PC0
#define NRF_CS GPIO_PC1
#define NRF_SCK GPIO_PB21
#define NRF_SDI GPIO_PB22
#define NRF_SDO GPIO_PB23
#define NRF_INT GPIO_PC2

#define ETH_RXER GPIO_PA5
#define ETH_TXD0 GPIO_PA16
#define ETH_TDD1 GPIO_PA17
#define ETH_RXD0 GPIO_PA13
#define ETH_RXD1 GPIO_PA12
#define ETH_TXEN GPIO_PA15
#define ETH_CRS_DV GPIO_PA14
#define ETH_MDIO GPIO_PA7
#define ETH_RST GPIO_PA9
#define ETH_CLKO GPIO_PE26
#define ETH_MDC GPIO_PA8
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

#define ALS_SDA GPIO_PB1
#define ALS_SCL GPIO_PB0

#define ACCEL_SDA GPIO_PB1
#define ACCEL_SCL GPIO_PB0
#define ACCEL_INT2 GPIO_PC18
#define ACCEL_INT1 GPIO_PC17

#define BUZZER GPIO_PA6

#define IR_TX GPIO_PA4

#define LED_RGB_SCL GPIO_PB0
#define LED_RGB_SDA GPIO_PB1

#define TEMP_SENS HAL_PIN_NC

#define CAN_RX GPIO_PE25
#define CAN_TX GPIO_PE24

#define POWER_BAT_SENSE HAL_PIN_NC
#define POWER_STATUS GPIO_PE27
#define POWER_DC_DETECT GPIO_PE28

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#define SHIELD_CONNECTOR_J1_PIN3 GPIO_PB2
#define SHIELD_CONNECTOR_J1_PIN4 GPIO_PB3
#define SHIELD_CONNECTOR_J1_PIN5 GPIO_PB4
#define SHIELD_CONNECTOR_J1_PIN6 GPIO_PB5
#define SHIELD_CONNECTOR_J1_PIN7 GPIO_PB6
#define SHIELD_CONNECTOR_J1_PIN8 GPIO_PB7
#define SHIELD_CONNECTOR_J1_PIN9 GPIO_PC19
#define SHIELD_CONNECTOR_J1_PIN10 GPIO_PA2
#define SHIELD_CONNECTOR_J1_PIN11 GPIO_PB20
#define SHIELD_CONNECTOR_J1_PIN12 GPIO_PB21
#define SHIELD_CONNECTOR_J1_PIN13 GPIO_PB23
#define SHIELD_CONNECTOR_J1_PIN14 GPIO_PB22
#define SHIELD_CONNECTOR_J1_PIN15 GPIO_PE25
#define SHIELD_CONNECTOR_J1_PIN16 GPIO_PE24
#define SHIELD_CONNECTOR_J1_PIN17 GPIO_PB10
#define SHIELD_CONNECTOR_J1_PIN18 GPIO_PB11
#define SHIELD_CONNECTOR_J1_PIN19 GPIO_PB17
#define SHIELD_CONNECTOR_J1_PIN20 GPIO_PB16

#define SHIELD_CONNECTOR_J2_PIN7 GPIO_PE7
#define SHIELD_CONNECTOR_J2_PIN8 GPIO_PE8
#define SHIELD_CONNECTOR_J2_PIN9 GPIO_PE11
#define SHIELD_CONNECTOR_J2_PIN10 GPIO_PE12
#define SHIELD_CONNECTOR_J2_PIN11 GPIO_PA10
#define SHIELD_CONNECTOR_J2_PIN12 GPIO_PA11
#define SHIELD_CONNECTOR_J2_PIN13 GPIO_PC5
#define SHIELD_CONNECTOR_J2_PIN14 GPIO_PC6
#define SHIELD_CONNECTOR_J2_PIN15 GPIO_PC7
#define SHIELD_CONNECTOR_J2_PIN16 GPIO_PC8
#define SHIELD_CONNECTOR_J2_PIN17 GPIO_PC10
#define SHIELD_CONNECTOR_J2_PIN18 GPIO_PC11
#define SHIELD_CONNECTOR_J2_PIN19 GPIO_PC14
#define SHIELD_CONNECTOR_J2_PIN20 GPIO_PC15
#define SHIELD_CONNECTOR_J2_PIN21 GPIO_PC3
#define SHIELD_CONNECTOR_J2_PIN22 GPIO_PC4
#define SHIELD_CONNECTOR_J2_PIN23 GPIO_PB0
#define SHIELD_CONNECTOR_J2_PIN24 GPIO_PB1

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
