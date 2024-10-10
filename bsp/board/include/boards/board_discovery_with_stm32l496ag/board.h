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

#define BOARD_NAME "STM32L496AG_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN10_D1 	PG15
#define HEADER_CONNECTOR_CN10_D2 	PH13
#define HEADER_CONNECTOR_CN10_D3 	PA15
#define HEADER_CONNECTOR_CN10_D4 	PB5
#define HEADER_CONNECTOR_CN10_D5 	PB4
#define HEADER_CONNECTOR_CN10_D6 	PA5
#define HEADER_CONNECTOR_CN10_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN10_D9 	PB7
#define HEADER_CONNECTOR_CN10_D10	PB8

#define HEADER_CONNECTOR_CN11_D1 	PG8
#define HEADER_CONNECTOR_CN11_D2 	PG7
#define HEADER_CONNECTOR_CN11_D3 	PG13
#define HEADER_CONNECTOR_CN11_D4 	PH15
#define HEADER_CONNECTOR_CN11_D5 	PI11
#define HEADER_CONNECTOR_CN11_D6 	PB9
#define HEADER_CONNECTOR_CN11_D7 	PI6
#define HEADER_CONNECTOR_CN11_D8 	PG6

#define HEADER_CONNECTOR_CN15_D1 	PA5
#define HEADER_CONNECTOR_CN15_D2 	PB4
#define HEADER_CONNECTOR_CN15_D3 	PB5
#define HEADER_CONNECTOR_CN15_D4 	PA15
#define HEADER_CONNECTOR_CN15_D5 	PH13
#define HEADER_CONNECTOR_CN15_D6 	PG15
#define HEADER_CONNECTOR_CN15_D7 	PG15
#define HEADER_CONNECTOR_CN15_D8 	PG6

#define HEADER_CONNECTOR_CN16_D1 	PC4
#define HEADER_CONNECTOR_CN16_D2 	PC1
#define HEADER_CONNECTOR_CN16_D3 	PC3
#define HEADER_CONNECTOR_CN16_D4 	PF10
#define HEADER_CONNECTOR_CN16_D5 	PA1
#define HEADER_CONNECTOR_CN16_D6 	PB8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
