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

#define BOARD_NAME "STM32F769NI_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN9_D1 	PJ4
#define HEADER_CONNECTOR_CN9_D2 	PH6
#define HEADER_CONNECTOR_CN9_D3 	PA11
#define HEADER_CONNECTOR_CN9_D4 	PB15
#define HEADER_CONNECTOR_CN9_D5 	PB14
#define HEADER_CONNECTOR_CN9_D6 	PA12
#define HEADER_CONNECTOR_CN9_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D9 	PB9
#define HEADER_CONNECTOR_CN9_D10	PB8

#define HEADER_CONNECTOR_CN11_D1	PA12
#define HEADER_CONNECTOR_CN11_D2	PB14
#define HEADER_CONNECTOR_CN11_D3	PB15
#define HEADER_CONNECTOR_CN11_D4	PA11
#define HEADER_CONNECTOR_CN11_D5	PH6
#define HEADER_CONNECTOR_CN11_D6	PJ4
#define HEADER_CONNECTOR_CN11_D7	PJ4
#define HEADER_CONNECTOR_CN11_D8	PJ3

#define HEADER_CONNECTOR_CN13_D1	PC7
#define HEADER_CONNECTOR_CN13_D2	PC6
#define HEADER_CONNECTOR_CN13_D3	PJ1
#define HEADER_CONNECTOR_CN13_D4	PF6
#define HEADER_CONNECTOR_CN13_D5	PJ0
#define HEADER_CONNECTOR_CN13_D6	PC8
#define HEADER_CONNECTOR_CN13_D7	PF7
#define HEADER_CONNECTOR_CN13_D8	PJ3

#define HEADER_CONNECTOR_CN14_D1	PA6
#define HEADER_CONNECTOR_CN14_D2	PA4
#define HEADER_CONNECTOR_CN14_D3	PC2
#define HEADER_CONNECTOR_CN14_D4	PF10
#define HEADER_CONNECTOR_CN14_D5	PF8
#define HEADER_CONNECTOR_CN14_D6	PB8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
