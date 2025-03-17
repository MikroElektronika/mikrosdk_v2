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

#define BOARD_NAME "STM32L496AG_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN6_D1  	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2  	GPIO_PH7
#define HEADER_CONNECTOR_CN6_D3  	GPIO_PD10
#define HEADER_CONNECTOR_CN6_D4  	GPIO_PD9
#define HEADER_CONNECTOR_CN6_D5  	GPIO_PD8
#define HEADER_CONNECTOR_CN6_D6  	GPIO_PE15
#define HEADER_CONNECTOR_CN6_D7  	GPIO_PE14
#define HEADER_CONNECTOR_CN6_D8  	GPIO_PE13
#define HEADER_CONNECTOR_CN6_D9  	GPIO_PE12
#define HEADER_CONNECTOR_CN6_D10 	GPIO_PE11
#define HEADER_CONNECTOR_CN6_D11 	GPIO_PE10
#define HEADER_CONNECTOR_CN6_D12 	GPIO_PE9
#define HEADER_CONNECTOR_CN6_D13 	GPIO_PE8
#define HEADER_CONNECTOR_CN6_D14 	GPIO_PE7
#define HEADER_CONNECTOR_CN6_D15 	GPIO_PD1
#define HEADER_CONNECTOR_CN6_D16 	GPIO_PD0
#define HEADER_CONNECTOR_CN6_D17 	GPIO_PD15
#define HEADER_CONNECTOR_CN6_D18 	GPIO_PD14
#define HEADER_CONNECTOR_CN6_D19 	GPIO_PD4
#define HEADER_CONNECTOR_CN6_D20 	GPIO_PD5
#define HEADER_CONNECTOR_CN6_D21 	GPIO_PD13
#define HEADER_CONNECTOR_CN6_D22 	GPIO_PD7
#define HEADER_CONNECTOR_CN6_D23 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D24 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D25 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D26 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D27 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D28 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D29 	// Pin not routed

#define HEADER_CONNECTOR_CN10_D1 	GPIO_PG15
#define HEADER_CONNECTOR_CN10_D2 	GPIO_PH13
#define HEADER_CONNECTOR_CN10_D3 	GPIO_PA15
#define HEADER_CONNECTOR_CN10_D4 	GPIO_PB5
#define HEADER_CONNECTOR_CN10_D5 	GPIO_PB4
#define HEADER_CONNECTOR_CN10_D6 	GPIO_PA5
#define HEADER_CONNECTOR_CN10_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D9 	GPIO_PB7
#define HEADER_CONNECTOR_CN10_D10	GPIO_PB8

#define HEADER_CONNECTOR_CN11_D1 	GPIO_PG8
#define HEADER_CONNECTOR_CN11_D2 	GPIO_PG7
#define HEADER_CONNECTOR_CN11_D3 	GPIO_PG13
#define HEADER_CONNECTOR_CN11_D4 	GPIO_PH15
#define HEADER_CONNECTOR_CN11_D5 	GPIO_PI11
#define HEADER_CONNECTOR_CN11_D6 	GPIO_PB9
#define HEADER_CONNECTOR_CN11_D7 	GPIO_PI6
#define HEADER_CONNECTOR_CN11_D8 	GPIO_PG6

#define HEADER_CONNECTOR_CN15_D1 	GPIO_PA5
#define HEADER_CONNECTOR_CN15_D2 	GPIO_PB4
#define HEADER_CONNECTOR_CN15_D3 	GPIO_PB5
#define HEADER_CONNECTOR_CN15_D4 	GPIO_PA15
#define HEADER_CONNECTOR_CN15_D5 	GPIO_PH13
#define HEADER_CONNECTOR_CN15_D6 	GPIO_PG15
#define HEADER_CONNECTOR_CN15_D7 	GPIO_PG15
#define HEADER_CONNECTOR_CN15_D8 	GPIO_PG6

#define HEADER_CONNECTOR_CN16_D1 	GPIO_PC4
#define HEADER_CONNECTOR_CN16_D2 	GPIO_PC1
#define HEADER_CONNECTOR_CN16_D3 	GPIO_PC3
#define HEADER_CONNECTOR_CN16_D4 	GPIO_PF10
#define HEADER_CONNECTOR_CN16_D5 	GPIO_PA1
#define HEADER_CONNECTOR_CN16_D6 	GPIO_PB8


#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
