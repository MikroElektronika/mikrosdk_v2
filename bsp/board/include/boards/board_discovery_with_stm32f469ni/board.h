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

#define BOARD_NAME "STM32F469NI_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN5_D1 	PG10
#define HEADER_CONNECTOR_CN5_D2 	PA7
#define HEADER_CONNECTOR_CN5_D3 	PH6
#define HEADER_CONNECTOR_CN5_D4 	PB15
#define HEADER_CONNECTOR_CN5_D5 	PB14
#define HEADER_CONNECTOR_CN5_D6 	PD3
#define HEADER_CONNECTOR_CN5_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D9 	PB9
#define HEADER_CONNECTOR_CN5_D10	PB8

#define HEADER_CONNECTOR_CN7_D1 	PG9
#define HEADER_CONNECTOR_CN7_D2 	PG14
#define HEADER_CONNECTOR_CN7_D3 	PG13
#define HEADER_CONNECTOR_CN7_D4 	PA1
#define HEADER_CONNECTOR_CN7_D5 	PG12
#define HEADER_CONNECTOR_CN7_D6 	PA2
#define HEADER_CONNECTOR_CN7_D7 	PA6
#define HEADER_CONNECTOR_CN7_D8 	PG11

#define HEADER_CONNECTOR_CN8_D1 	PB1
#define HEADER_CONNECTOR_CN8_D2 	PC2
#define HEADER_CONNECTOR_CN8_D3 	PC3
#define HEADER_CONNECTOR_CN8_D4 	PC4
#define HEADER_CONNECTOR_CN8_D5 	PB9
#define HEADER_CONNECTOR_CN8_D6 	PA4

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
