/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is GPIO_part of the mikroSDK GPIO_package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement GPIO_provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General GPIO_Public License Usage
**
** Alternatively, this file may be used for
** non-commercial GPIO_projects under the terms of the GNU Lesser
** General GPIO_Public License version 3 as GPIO_published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this GPIO_permission notice shall be
** included in all copies or substantial GPIO_portions of the Software.
**
** THE SOFTWARE IS GPIO_PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A GPIO_PARTICULAR GPIO_PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  board.h
 * @brief Main board GPIO_pin mapping.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "GigaDevice GD32VF103 Eval Board"

#include "hal_target.h"

// JTAG
#define JTAG_JNTRST    GPIO_PB4
#define JTAG_JTDI      GPIO_PA15
#define JTAG_JTMS      GPIO_PA13
#define JTAG_JTCK      GPIO_PA14
#define JTAG_JTDO      GPIO_PB3

// USB
#define USB_DM      GPIO_PA11
#define USB_DP      GPIO_PA12
#define USB_VBUS    GPIO_PA9

// I2C
#define I2C_SCL     GPIO_PB6
#define I2C_SDA     GPIO_PB7

// I2S
#define I2S0_WS     GPIO_PB12
#define I2S0_CK     GPIO_PB13
#define I2S0_SD     GPIO_PB15
#define I2S0_MCK    GPIO_PC6

// USART0
#define USART0_TX   GPIO_PA9
#define USART0_RX   GPIO_PA10

// USART1
#define USART1_TX   GPIO_PA2
#define USART1_RX   GPIO_PA3

// SPI
#define SPI0_SCK    GPIO_PA5
#define SPI0_MISO   GPIO_PA6
#define SPI0_MOSI   GPIO_PA7
#define SPI0_CS     GPIO_PE3

// CAN0
#define CAN0_RX     GPIO_PD0
#define CAN0_TX     GPIO_PD1

// CAN1
#define CAN1_RX     GPIO_PB5
#define CAN1_TX     GPIO_PB6

// LCD
#define LCD_D0     GPIO_PD14
#define LCD_D1     GPIO_PD15
#define LCD_D2     GPIO_PD0
#define LCD_D3     GPIO_PD1
#define LCD_D4     GPIO_PE7
#define LCD_D5     GPIO_PE8
#define LCD_D6     GPIO_PE9
#define LCD_D7     GPIO_PE10
#define LCD_D8     GPIO_PE11
#define LCD_D9     GPIO_PE12
#define LCD_D10    GPIO_PE13
#define LCD_D11    GPIO_PE14
#define LCD_D12    GPIO_PE15
#define LCD_D13    GPIO_PD8
#define LCD_D14    GPIO_PD9
#define LCD_D15    GPIO_PD10
#define LCD_A23    GPIO_PE2
#define LCD_NOE    GPIO_PD4
#define LCD_NWE    GPIO_PD5
#define LCD_NE0    GPIO_PD7

// ADC
#define ADC01_IN13  GPIO_PC3

// DAC
#define DAC_OUT0    GPIO_PA4
#define DAC_OUT1    GPIO_PA5

// LEDS
#define LED1    GPIO_PC0
#define LED2    GPIO_PC2
#define LED3    GPIO_PE0
#define LED4    GPIO_PE1

// BUTTONS
#define BUTTON_A    GPIO_PA0
#define BUTTON_B    GPIO_PC13
#define BUTTON_C    GPIO_PB14
#define BUTTON_D    GPIO_PC5
#define BUTTON_Cet  GPIO_PC4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END