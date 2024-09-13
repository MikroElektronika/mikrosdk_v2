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

#define BOARD_NAME "Nucleo-G071RB"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN2_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D2 	PA11
#define HEADER_CONNECTOR_CN2_D3 	PA12
#define HEADER_CONNECTOR_CN2_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN2_D5 	// Pin not routed

#define HEADER_CONNECTOR_CN5_D1 	PA9
#define HEADER_CONNECTOR_CN5_D2 	PC7
#define HEADER_CONNECTOR_CN5_D3 	PB0
#define HEADER_CONNECTOR_CN5_D4 	PA7
#define HEADER_CONNECTOR_CN5_D5 	PA6
#define HEADER_CONNECTOR_CN5_D6 	PA5
#define HEADER_CONNECTOR_CN5_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN5_D9 	PB9
#define HEADER_CONNECTOR_CN5_D10	PB8

#define HEADER_CONNECTOR_CN6_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN6_D8 	// Pin not routed

#define HEADER_CONNECTOR_CN8_D1 	PA0
#define HEADER_CONNECTOR_CN8_D2 	PA1
#define HEADER_CONNECTOR_CN8_D3 	PA4
#define HEADER_CONNECTOR_CN8_D4 	PB1
#define HEADER_CONNECTOR_CN8_D5 	PB9
#define HEADER_CONNECTOR_CN8_D6 	PB8

#define HEADER_CONNECTOR_CN9_D1 	PC5
#define HEADER_CONNECTOR_CN9_D2 	PC4
#define HEADER_CONNECTOR_CN9_D3 	PA10
#define HEADER_CONNECTOR_CN9_D4 	PB3
#define HEADER_CONNECTOR_CN9_D5 	PB5
#define HEADER_CONNECTOR_CN9_D6 	PB4
#define HEADER_CONNECTOR_CN9_D7 	PB14
#define HEADER_CONNECTOR_CN9_D8 	PA8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
