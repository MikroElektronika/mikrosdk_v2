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
extern "C"
{
#endif

#define BOARD_NAME "STM32F746NG_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN4_D1 	PC7
#define HEADER_CONNECTOR_CN4_D2 	PC6
#define HEADER_CONNECTOR_CN4_D3 	PG6
#define HEADER_CONNECTOR_CN4_D4 	PB4
#define HEADER_CONNECTOR_CN4_D5 	PG7
#define HEADER_CONNECTOR_CN4_D6 	PI0
#define HEADER_CONNECTOR_CN4_D7 	PH6
#define HEADER_CONNECTOR_CN4_D8 	PI3

#define HEADER_CONNECTOR_CN5_D1 	PA0
#define HEADER_CONNECTOR_CN5_D2 	PF10
#define HEADER_CONNECTOR_CN5_D3 	PF9
#define HEADER_CONNECTOR_CN5_D4 	PF8
#define HEADER_CONNECTOR_CN5_D5 	PF7
#define HEADER_CONNECTOR_CN5_D6 	PB8

#define HEADER_CONNECTOR_CN6_D1 	PI1
#define HEADER_CONNECTOR_CN6_D2 	PB14
#define HEADER_CONNECTOR_CN6_D3 	PB15
#define HEADER_CONNECTOR_CN6_D4 	PA8
#define HEADER_CONNECTOR_CN6_D5 	PA15
#define HEADER_CONNECTOR_CN6_D6 	PI2
#define HEADER_CONNECTOR_CN6_D7 	PI2
#define HEADER_CONNECTOR_CN6_D8 	PI3

#define HEADER_CONNECTOR_CN7_D1 	PI2
#define HEADER_CONNECTOR_CN7_D2 	PA15
#define HEADER_CONNECTOR_CN7_D3 	PA8
#define HEADER_CONNECTOR_CN7_D4 	PB15
#define HEADER_CONNECTOR_CN7_D5 	PB14
#define HEADER_CONNECTOR_CN7_D6 	PI1
#define HEADER_CONNECTOR_CN7_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9 	PB9
#define HEADER_CONNECTOR_CN7_D10	PB8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
