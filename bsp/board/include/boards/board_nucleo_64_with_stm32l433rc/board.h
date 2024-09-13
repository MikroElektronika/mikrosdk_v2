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

#define BOARD_NAME "Nucleo-L433RC"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D2 	PA11
#define HEADER_CONNECTOR_CN1_D3 	PA12
#define HEADER_CONNECTOR_CN1_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN1_D5 	// Pin not routed

#define HEADER_CONNECTOR_CN3_D1 	PA0
#define HEADER_CONNECTOR_CN3_D2 	PA5
#define HEADER_CONNECTOR_CN3_D3 	PA12
#define HEADER_CONNECTOR_CN3_D4 	PA14
#define HEADER_CONNECTOR_CN3_D5 	PB0
#define HEADER_CONNECTOR_CN3_D6 	PA10

#define HEADER_CONNECTOR_CN7_D1 	PB6
#define HEADER_CONNECTOR_CN7_D2 	PA8
#define HEADER_CONNECTOR_CN7_D3 	PA11
#define HEADER_CONNECTOR_CN7_D4 	PB15
#define HEADER_CONNECTOR_CN7_D5 	PB14
#define HEADER_CONNECTOR_CN7_D6 	PB13
#define HEADER_CONNECTOR_CN7_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN7_D9 	PB7
#define HEADER_CONNECTOR_CN7_D10	PB8

#define HEADER_CONNECTOR_CN8_D1 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D2 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D3 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D4 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D5 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D6 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN8_D8 	// Pin not routed

#define HEADER_CONNECTOR_CN9_D1 	PA3
#define HEADER_CONNECTOR_CN9_D2 	PA2
#define HEADER_CONNECTOR_CN9_D3 	PA12
#define HEADER_CONNECTOR_CN9_D4 	PB3
#define HEADER_CONNECTOR_CN9_D5 	PB5
#define HEADER_CONNECTOR_CN9_D6 	PA15
#define HEADER_CONNECTOR_CN9_D7 	PB10
#define HEADER_CONNECTOR_CN9_D8 	PC7

#define HEADER_CONNECTOR_CN10_D1	PA0
#define HEADER_CONNECTOR_CN10_D2	PA1
#define HEADER_CONNECTOR_CN10_D3	PC3
#define HEADER_CONNECTOR_CN10_D4	PC2
#define HEADER_CONNECTOR_CN10_D5	PC1
#define HEADER_CONNECTOR_CN10_D6	PC0

#define HEADER_CONNECTOR_CN11_D1	// Pin not routed
#define HEADER_CONNECTOR_CN11_D2	// Pin not routed
#define HEADER_CONNECTOR_CN11_D3	// Pin not routed
#define HEADER_CONNECTOR_CN11_D4	PA5
#define HEADER_CONNECTOR_CN11_D5	PA4
#define HEADER_CONNECTOR_CN11_D6	PA7
#define HEADER_CONNECTOR_CN11_D7	PA6
#define HEADER_CONNECTOR_CN11_D8	// Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
