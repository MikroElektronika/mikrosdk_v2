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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.3/new_hw/2025-05-12.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "STM32F723IE_DISCOVERY"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN11_D1 	GPIO_PE4
#define HEADER_CONNECTOR_CN11_D2 	GPIO_PH6
#define HEADER_CONNECTOR_CN11_D3 	GPIO_PA1
#define HEADER_CONNECTOR_CN11_D4 	GPIO_PB5
#define HEADER_CONNECTOR_CN11_D5 	GPIO_PA4
#define HEADER_CONNECTOR_CN11_D6 	GPIO_PA5
#define HEADER_CONNECTOR_CN11_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN11_D9 	GPIO_PH5
#define HEADER_CONNECTOR_CN11_D10 	GPIO_PH4

#define HEADER_CONNECTOR_CN13_D1 	GPIO_PA3
#define HEADER_CONNECTOR_CN13_D2 	GPIO_PA2
#define HEADER_CONNECTOR_CN13_D3 	GPIO_PC5
#define HEADER_CONNECTOR_CN13_D4 	GPIO_PE5
#define HEADER_CONNECTOR_CN13_D5 	GPIO_PH3
#define HEADER_CONNECTOR_CN13_D6 	GPIO_PB0
#define HEADER_CONNECTOR_CN13_D7 	GPIO_PE6
#define HEADER_CONNECTOR_CN13_D8 	GPIO_PE3

#define HEADER_CONNECTOR_CN15_D1 	GPIO_PA6
#define HEADER_CONNECTOR_CN15_D2 	GPIO_PA4
#define HEADER_CONNECTOR_CN15_D3 	GPIO_PC4
#define HEADER_CONNECTOR_CN15_D4 	GPIO_PF10
#define HEADER_CONNECTOR_CN15_D5 	GPIO_PC0
#define HEADER_CONNECTOR_CN15_D6 	GPIO_PC1

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
