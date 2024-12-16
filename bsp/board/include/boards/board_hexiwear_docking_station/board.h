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

#define BOARD_NAME "Hexiwear Docking Station"

#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN GPIO_PB2
#define MIKROBUS_1_RST GPIO_PB11
#define MIKROBUS_1_CS GPIO_PC4
#define MIKROBUS_1_SCK GPIO_PC5
#define MIKROBUS_1_MISO GPIO_PC7
#define MIKROBUS_1_MOSI GPIO_PC6
#define MIKROBUS_1_PWM GPIO_PA10
#define MIKROBUS_1_INT GPIO_PB13
#define MIKROBUS_1_RX GPIO_PD2
#define MIKROBUS_1_TX GPIO_PD3
#define MIKROBUS_1_SCL GPIO_PD8
#define MIKROBUS_1_SDA GPIO_PD9

#define MIKROBUS_2 2
#define MIKROBUS_2_AN GPIO_PB3
#define MIKROBUS_2_RST GPIO_PB19
#define MIKROBUS_2_CS GPIO_PC3
#define MIKROBUS_2_SCK GPIO_PC5
#define MIKROBUS_2_MISO GPIO_PC7
#define MIKROBUS_2_MOSI GPIO_PC6
#define MIKROBUS_2_PWM GPIO_PA11
#define MIKROBUS_2_INT GPIO_PB8
#define MIKROBUS_2_RX GPIO_PC16
#define MIKROBUS_2_TX GPIO_PC17
#define MIKROBUS_2_SCL GPIO_PD8
#define MIKROBUS_2_SDA GPIO_PD9

#define MIKROBUS_3 3
#define MIKROBUS_3_AN GPIO_PB6
#define MIKROBUS_3_RST GPIO_PB10
#define MIKROBUS_3_CS GPIO_PC2
#define MIKROBUS_3_SCK GPIO_PC5
#define MIKROBUS_3_MISO GPIO_PC7
#define MIKROBUS_3_MOSI GPIO_PC6
#define MIKROBUS_3_PWM GPIO_PA4
#define MIKROBUS_3_INT GPIO_PB7
#define MIKROBUS_3_RX GPIO_PC16
#define MIKROBUS_3_TX GPIO_PC17
#define MIKROBUS_3_SCL GPIO_PD8
#define MIKROBUS_3_SDA GPIO_PD9

// SD card connections
#define SDHC_DAT0 GPIO_PE1
#define SDHC_DAT1 GPIO_PE0
#define SDHC_DAT2 GPIO_PE5
#define SDHC_DAT3 GPIO_PE4
#define SDHC_CLK GPIO_PE2
#define SDHC_CMD GPIO_PE3
#define SDHC_CD HAL_PIN_NC

// Buttons
#define BUTTON_T1 GPIO_PA12
#define BUTTON_T2 GPIO_PA13
#define BUTTON_T3 GPIO_PA14

// No TFT connector on board
#define TFT_8BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_8BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH0 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH0_MASK 0x0000

#define TFT_16BIT_DATA_PORT_CH1 HAL_PORT_NC
#define TFT_16BIT_DATA_PORT_CH1_MASK 0x0000

#define USB_UART_TX HAL_PIN_NC
#define USB_UART_RX HAL_PIN_NC

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
