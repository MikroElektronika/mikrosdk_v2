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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.6/new_hw/2025-07-28.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "PICDEM LCD 2 DEMONSTRATION BOARD"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_J3_D1  // Pin not routed
#define HEADER_CONNECTOR_J3_D2  GPIO_PA5
#define HEADER_CONNECTOR_J3_D3  // Pin not routed
#define HEADER_CONNECTOR_J3_D4  GPIO_PA4
#define HEADER_CONNECTOR_J3_D5  GPIO_PA7
#define HEADER_CONNECTOR_J3_D6  GPIO_PA3
#define HEADER_CONNECTOR_J3_D7  GPIO_PA6
#define HEADER_CONNECTOR_J3_D8  GPIO_PC5
#define HEADER_CONNECTOR_J3_D9  GPIO_PC7
#define HEADER_CONNECTOR_J3_D10 GPIO_PC4
#define HEADER_CONNECTOR_J3_D11 GPIO_PC6
#define HEADER_CONNECTOR_J3_D12 GPIO_PC3
#define HEADER_CONNECTOR_J3_D13 GPIO_PB7
#define HEADER_CONNECTOR_J3_D14 GPIO_PA0
#define HEADER_CONNECTOR_J3_D15 GPIO_PB6
#define HEADER_CONNECTOR_J3_D16 GPIO_PA1
#define HEADER_CONNECTOR_J3_D17 GPIO_PB5
#define HEADER_CONNECTOR_J3_D18 GPIO_PA2
#define HEADER_CONNECTOR_J3_D19 GPIO_PB4
#define HEADER_CONNECTOR_J3_D20 GPIO_PC0
#define HEADER_CONNECTOR_J3_D21 GPIO_PB3
#define HEADER_CONNECTOR_J3_D22 GPIO_PC1
#define HEADER_CONNECTOR_J3_D23 GPIO_PB2
#define HEADER_CONNECTOR_J3_D24 GPIO_PC2
#define HEADER_CONNECTOR_J3_D25 GPIO_PB1
#define HEADER_CONNECTOR_J3_D26 // Pin not routed
#define HEADER_CONNECTOR_J3_D27 GPIO_PB1
#define HEADER_CONNECTOR_J3_D28 // Pin not routed

#define HEADER_CONNECTOR_J8_D1  GPIO_PD1
#define HEADER_CONNECTOR_J8_D2  GPIO_PD0
#define HEADER_CONNECTOR_J8_D3  GPIO_PD3
#define HEADER_CONNECTOR_J8_D4  GPIO_PD2
#define HEADER_CONNECTOR_J8_D5  GPIO_PD5
#define HEADER_CONNECTOR_J8_D6  GPIO_PD4
#define HEADER_CONNECTOR_J8_D7  GPIO_PD7
#define HEADER_CONNECTOR_J8_D8  GPIO_PD6
#define HEADER_CONNECTOR_J8_D9  // Pin not routed
#define HEADER_CONNECTOR_J8_D10 // Pin not routed
#define HEADER_CONNECTOR_J8_D11 // Pin not routed
#define HEADER_CONNECTOR_J8_D12 // Pin not routed

#define HEADER_CONNECTOR_J7_D1  GPIO_PJ1
#define HEADER_CONNECTOR_J7_D2  GPIO_PJ0
#define HEADER_CONNECTOR_J7_D3  GPIO_PJ3
#define HEADER_CONNECTOR_J7_D4  GPIO_PJ2
#define HEADER_CONNECTOR_J7_D5  GPIO_PJ5
#define HEADER_CONNECTOR_J7_D6  GPIO_PJ4
#define HEADER_CONNECTOR_J7_D7  GPIO_PJ7
#define HEADER_CONNECTOR_J7_D8  GPIO_PJ6
#define HEADER_CONNECTOR_J7_D9  GPIO_PH1
#define HEADER_CONNECTOR_J7_D10 GPIO_PH0
#define HEADER_CONNECTOR_J7_D11 GPIO_PH3
#define HEADER_CONNECTOR_J7_D12 GPIO_PH2
#define HEADER_CONNECTOR_J7_D13 GPIO_PH5
#define HEADER_CONNECTOR_J7_D14 GPIO_PH4
#define HEADER_CONNECTOR_J7_D15 GPIO_PH7
#define HEADER_CONNECTOR_J7_D16 GPIO_PH6

#define HEADER_CONNECTOR_J4_D1  GPIO_PG1
#define HEADER_CONNECTOR_J4_D2  GPIO_PG0
#define HEADER_CONNECTOR_J4_D3  GPIO_PG3
#define HEADER_CONNECTOR_J4_D4  GPIO_PG2
#define HEADER_CONNECTOR_J4_D5  GPIO_PG5
#define HEADER_CONNECTOR_J4_D6  GPIO_PG4
#define HEADER_CONNECTOR_J4_D7  GPIO_PF1
#define HEADER_CONNECTOR_J4_D8  GPIO_PF0
#define HEADER_CONNECTOR_J4_D9  GPIO_PF3
#define HEADER_CONNECTOR_J4_D10 GPIO_PF2
#define HEADER_CONNECTOR_J4_D11 GPIO_PF5
#define HEADER_CONNECTOR_J4_D12 GPIO_PF4
#define HEADER_CONNECTOR_J4_D13 GPIO_PF7
#define HEADER_CONNECTOR_J4_D14 GPIO_PF6
#define HEADER_CONNECTOR_J4_D15 GPIO_PE5
#define HEADER_CONNECTOR_J4_D16 GPIO_PE4
#define HEADER_CONNECTOR_J4_D17 GPIO_PE7
#define HEADER_CONNECTOR_J4_D18 GPIO_PE6
#define HEADER_CONNECTOR_J4_D19 // Pin not routed
#define HEADER_CONNECTOR_J4_D20 // Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
