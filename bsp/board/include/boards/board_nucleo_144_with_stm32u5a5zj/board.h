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
extern "C"
{
#endif

#define BOARD_NAME "Nucleo 144 with STM32U5A5ZJ MCU"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define ARDUINO_CONNECTOR_A0        GPIO_PA3
#define ARDUINO_CONNECTOR_A1        GPIO_PA2
#define ARDUINO_CONNECTOR_A2        GPIO_PC3
#define ARDUINO_CONNECTOR_A3        GPIO_PB0
#define ARDUINO_CONNECTOR_A4        GPIO_PC1
#define ARDUINO_CONNECTOR_A5        GPIO_PC0
#define ARDUINO_CONNECTOR_D0        GPIO_PG8
#define ARDUINO_CONNECTOR_D1        GPIO_PG7
#define ARDUINO_CONNECTOR_D2        GPIO_PF15
#define ARDUINO_CONNECTOR_D3        GPIO_PE13
#define ARDUINO_CONNECTOR_D4        GPIO_PF14
#define ARDUINO_CONNECTOR_D5        GPIO_PE11
#define ARDUINO_CONNECTOR_D6        GPIO_PE9
#define ARDUINO_CONNECTOR_D7        GPIO_PF13
#define ARDUINO_CONNECTOR_D8        GPIO_PF12
#define ARDUINO_CONNECTOR_D9        GPIO_PD15
#define ARDUINO_CONNECTOR_D10       GPIO_PD14
#define ARDUINO_CONNECTOR_D11       GPIO_PA7
#define ARDUINO_CONNECTOR_D12       GPIO_PA6
#define ARDUINO_CONNECTOR_D13       GPIO_PA5
#define ARDUINO_CONNECTOR_SCL       GPIO_PB8
#define ARDUINO_CONNECTOR_SDA       GPIO_PB9

#define HEADER_CONNECTOR_CN11_D1      GPIO_PC10
#define HEADER_CONNECTOR_CN11_D2      GPIO_PC11
#define HEADER_CONNECTOR_CN11_D3      GPIO_PC12
#define HEADER_CONNECTOR_CN11_D4      GPIO_PD2
#define HEADER_CONNECTOR_CN11_D13     GPIO_PA13  // Shared with SWD (ST-LINK)
#define HEADER_CONNECTOR_CN11_D15     GPIO_PA14  // Shared with SWD (ST-LINK)
#define HEADER_CONNECTOR_CN11_D31     // Pin not routed (PH1, SB49 not documented as ON by default)
#define HEADER_CONNECTOR_CN11_D32     GPIO_PA4
#define HEADER_CONNECTOR_CN11_D36     GPIO_PC1
#define HEADER_CONNECTOR_CN11_D38     GPIO_PC0
#define HEADER_CONNECTOR_CN11_D41     GPIO_PD5
#define HEADER_CONNECTOR_CN11_D43     GPIO_PD6
#define HEADER_CONNECTOR_CN11_D51     GPIO_PF1
#define HEADER_CONNECTOR_CN11_D53     GPIO_PF0
#define HEADER_CONNECTOR_CN11_D66     GPIO_PG10

#define HEADER_CONNECTOR_CN12_D1      GPIO_PC9
#define HEADER_CONNECTOR_CN12_D2      GPIO_PC8
#define HEADER_CONNECTOR_CN12_D4      GPIO_PC6
#define HEADER_CONNECTOR_CN12_D16     // Pin not routed (NC on MB1549)
#define HEADER_CONNECTOR_CN12_D19     GPIO_PC7  // Shared with user LED LD1
#define HEADER_CONNECTOR_CN12_D21     GPIO_PA9  // Shared with ST-LINK VCP USART1_TX (default)
#define HEADER_CONNECTOR_CN12_D27     GPIO_PB4
#define HEADER_CONNECTOR_CN12_D29     GPIO_PB5  // Shared with UCPD_DBn (SB46 ON)
#define HEADER_CONNECTOR_CN12_D31     GPIO_PB3
#define HEADER_CONNECTOR_CN12_D33     GPIO_PA10  // Shared with ST-LINK VCP USART1_RX (default)
#define HEADER_CONNECTOR_CN12_D35     GPIO_PA2
#define HEADER_CONNECTOR_CN12_D37     GPIO_PA3
#define HEADER_CONNECTOR_CN12_D56     GPIO_PE11
#define HEADER_CONNECTOR_CN12_D57     GPIO_PF13
#define HEADER_CONNECTOR_CN12_D65     GPIO_PD10
#define HEADER_CONNECTOR_CN12_D66     GPIO_PG8
#define HEADER_CONNECTOR_CN12_D69     GPIO_PG4
#define HEADER_CONNECTOR_CN12_D70     GPIO_PG6

#define BUTTON1    GPIO_PC13

#define LED1       GPIO_PC7
#define LED2       GPIO_PB7
#define LED3       GPIO_PG2

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
