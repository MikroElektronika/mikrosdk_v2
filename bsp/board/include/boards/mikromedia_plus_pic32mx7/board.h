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

// Hardware revision number
#define BOARD_REV_MAJOR (1)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Mikromedia Plus for PIC32MX7"

/// Mapping
#define TFT_RST GPIO_PC1
#define TFT_CS GPIO_PF12
#define TFT_D_C GPIO_PB15
#define TFT_RD GPIO_PD5
#define TFT_WR GPIO_PD4
#define TFT_TE HAL_PIN_NC
#define TFT_BPWM HAL_PIN_NC
#define TFT_D0 GPIO_PE0
#define TFT_D1 GPIO_PE1
#define TFT_D2 GPIO_PE2
#define TFT_D3 GPIO_PE3
#define TFT_D4 GPIO_PE4
#define TFT_D5 GPIO_PE5
#define TFT_D6 GPIO_PE6
#define TFT_D7 GPIO_PE7
#define TFT_D8 GPIO_PG0 // PMP pin
#define TFT_D9 GPIO_PG1 // PMP pin
#define TFT_D10 GPIO_PF1 // PMP pin
#define TFT_D11 GPIO_PF0 // PMP pin
#define TFT_D12 GPIO_PD12 // PMP pin
#define TFT_D13 GPIO_PD13 // PMP pin
#define TFT_D14 GPIO_PD2 // PMP pin
#define TFT_D15 GPIO_PD3 // PMP pin

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

#define CTP_SDA GPIO_PA3
#define CTP_SCL GPIO_PA2
#define CTP_INT GPIO_PA14
#define CTP_WAKE HAL_PIN_NC
#define CTP_RST HAL_PIN_NC

#define NRF_CE GPIO_PB14
#define NRF_CS GPIO_PA4
#define NRF_SCK GPIO_PD10
#define NRF_SDI GPIO_PD0
#define NRF_SDO GPIO_PC4
#define NRF_INT GPIO_PB3

#define ETH_RXER GPIO_PG15
#define ETH_TXD0 GPIO_PD14
#define ETH_TDD1 GPIO_PD15
#define ETH_RXD0 GPIO_PE8
#define ETH_RXD1 GPIO_PE9
#define ETH_TXEN GPIO_PA15
#define ETH_CRS_DV GPIO_PG8
#define ETH_MDIO GPIO_PD8
#define ETH_RST GPIO_PA0
#define ETH_CLKO GPIO_PG9
#define ETH_MDC GPIO_PD11
#define ETH_INT HAL_PIN_NC

#define USB_SW_ID GPIO_PF3
#define USB_VBUS HAL_PIN_NC
#define USB_N GPIO_PG3
#define USB_P GPIO_PG2
#define USB_PSW GPIO_PB5

#define SD_CS GPIO_PA6
#define SD_MOSI GPIO_PD0
#define SD_SCK GPIO_PD10
#define SD_MISO GPIO_PC4
#define SD_CD GPIO_PA7

#define FLASH_CS GPIO_PA9
#define FLASH_MISO GPIO_PD0
#define FLASH_SCK GPIO_PD10
#define FLASH_MOSI GPIO_PC4

#define MP3_SCLK GPIO_PD10
#define MP3_SIN GPIO_PC4
#define MP3_SOUT GPIO_PD0
#define MP3_CS GPIO_PA5
#define MP3_RST GPIO_PG12
#define MP3_DREQ GPIO_PG14
#define MP3_DCS GPIO_PG13

#define ALS_SDA HAL_PIN_NC
#define ALS_SCL HAL_PIN_NC

#define ACCEL_SDA GPIO_PA3
#define ACCEL_SCL GPIO_PA2
#define ACCEL_INT GPIO_PG6

#define BUZZER GPIO_PF13

#define IR_TX GPIO_PG7

#define LED_R GPIO_PD1
#define LED_G GPIO_PD2
#define LED_B GPIO_PD3

#define TEMP_SENS GPIO_PB9

#define CAN_RX GPIO_PC2
#define CAN_TX GPIO_PC3

#define POWER_BAT_SENSE GPIO_PB10
#define POWER_STATUS GPIO_PB13
#define POWER_DC_DETECT HAL_PIN_NC

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
