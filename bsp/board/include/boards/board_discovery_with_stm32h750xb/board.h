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

#define BOARD_NAME "STM32H750XB_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1 	GPIO_PE3
#define HEADER_CONNECTOR_CN2_D2 	GPIO_PH15
#define HEADER_CONNECTOR_CN2_D3 	GPIO_PB4
#define HEADER_CONNECTOR_CN2_D4 	GPIO_PB15
#define HEADER_CONNECTOR_CN2_D5 	GPIO_PI2
#define HEADER_CONNECTOR_CN2_D6 	GPIO_PD3
#define HEADER_CONNECTOR_CN2_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D9 	GPIO_PD13
#define HEADER_CONNECTOR_CN2_D10	GPIO_PD12

#define HEADER_CONNECTOR_CN3_D1 	GPIO_PD3
#define HEADER_CONNECTOR_CN3_D2 	GPIO_PI2
#define HEADER_CONNECTOR_CN3_D3 	GPIO_PB15
#define HEADER_CONNECTOR_CN3_D4 	GPIO_PB4
#define HEADER_CONNECTOR_CN3_D5 	GPIO_PH15
#define HEADER_CONNECTOR_CN3_D6 	GPIO_PE3
#define HEADER_CONNECTOR_CN3_D7 	GPIO_PE3
#define HEADER_CONNECTOR_CN3_D8 	GPIO_PI8

#define HEADER_CONNECTOR_CN6_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D5 	GPIO_PK1
#define HEADER_CONNECTOR_CN6_D6 	GPIO_PA8
#define HEADER_CONNECTOR_CN6_D7 	GPIO_PE6
#define HEADER_CONNECTOR_CN6_D8 	GPIO_PI8

#define HEADER_CONNECTOR_CN7_D1 	GPIO_PC3
#define HEADER_CONNECTOR_CN7_D2 	GPIO_PC2
#define HEADER_CONNECTOR_CN7_D3 	GPIO_PA1
#define HEADER_CONNECTOR_CN7_D4 	GPIO_PA0

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
