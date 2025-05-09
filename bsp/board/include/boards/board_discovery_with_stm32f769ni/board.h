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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.3/new_hw/2025-05-09.md
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
#define HEADER_CONNECTOR_CN9_D1 	GPIO_PJ4
#define HEADER_CONNECTOR_CN9_D2 	GPIO_PH6
#define HEADER_CONNECTOR_CN9_D3 	GPIO_PA11
#define HEADER_CONNECTOR_CN9_D4 	GPIO_PB15
#define HEADER_CONNECTOR_CN9_D5 	GPIO_PB14
#define HEADER_CONNECTOR_CN9_D6 	GPIO_PA12
#define HEADER_CONNECTOR_CN9_D7 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D8 	// Pin not routed
#define HEADER_CONNECTOR_CN9_D9 	GPIO_PB9
#define HEADER_CONNECTOR_CN9_D10	GPIO_PB8

#define HEADER_CONNECTOR_CN11_D1	GPIO_PA12
#define HEADER_CONNECTOR_CN11_D2	GPIO_PB14
#define HEADER_CONNECTOR_CN11_D3	GPIO_PB15
#define HEADER_CONNECTOR_CN11_D4	GPIO_PA11
#define HEADER_CONNECTOR_CN11_D5	GPIO_PH6
#define HEADER_CONNECTOR_CN11_D6	GPIO_PJ4
#define HEADER_CONNECTOR_CN11_D7	GPIO_PJ4
#define HEADER_CONNECTOR_CN11_D8	GPIO_PJ3

#define HEADER_CONNECTOR_CN13_D1	GPIO_PC7
#define HEADER_CONNECTOR_CN13_D2	GPIO_PC6
#define HEADER_CONNECTOR_CN13_D3	GPIO_PJ1
#define HEADER_CONNECTOR_CN13_D4	GPIO_PF6
#define HEADER_CONNECTOR_CN13_D5	GPIO_PJ0
#define HEADER_CONNECTOR_CN13_D6	GPIO_PC8
#define HEADER_CONNECTOR_CN13_D7	GPIO_PF7
#define HEADER_CONNECTOR_CN13_D8	GPIO_PJ3

#define HEADER_CONNECTOR_CN14_D1	GPIO_PA6
#define HEADER_CONNECTOR_CN14_D2	GPIO_PA4
#define HEADER_CONNECTOR_CN14_D3	GPIO_PC2
#define HEADER_CONNECTOR_CN14_D4	GPIO_PF10
#define HEADER_CONNECTOR_CN14_D5	GPIO_PF8
#define HEADER_CONNECTOR_CN14_D6	GPIO_PB8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
