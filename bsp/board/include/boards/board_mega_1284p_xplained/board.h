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

#define BOARD_NAME "MEGA-1284P XPLAINED"

#include "hal_target.h"

// Mapping
#define TWI_SDA     GPIO_PC1
#define TWI_SCL     GPIO_PC0
#define USART_RXD0  GPIO_PD0
#define USART_TXD0  GPIO_PD1
#define USART_RXD1  GPIO_PD2
#define USART_TXD1  GPIO_PD3
#define SPI_SS      GPIO_PB4
#define SPI_SS1     GPIO_PD4
#define SPI_MOSI    GPIO_PB5
#define SPI_MISO    GPIO_PB6
#define SPI_SCK     GPIO_PB7

#define ADC0    GPIO_PA0
#define ADC1    GPIO_PA1
#define ADC2    GPIO_PA2
#define ADC3    GPIO_PA3
#define ADC4    GPIO_PA4
#define ADC5    GPIO_PA5
#define ADC6    GPIO_PA6
#define ADC7    GPIO_PA7

#define GPIO0    GPIO_PB0
#define GPIO1    GPIO_PB1
#define GPIO2    GPIO_PB2
#define GPIO3    GPIO_PB3
#define GPIO4    GPIO_PD4
#define GPIO5    GPIO_PD5
#define GPIO6    GPIO_PC4
#define GPIO7    GPIO_PC5

#define QTB0_SNSK0  GPIO_PD7
#define QTB0_SNS0   GPIO_PD6

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
