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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.15.0/new_hw/2025-08-15.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "FUBARINO SD DEVELOPMENT BOARD"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_J2_1   // Pin not routed
#define HEADER_CONNECTOR_J2_2   // Pin not routed
#define HEADER_CONNECTOR_J2_3   // Pin not routed
#define HEADER_CONNECTOR_J2_4   GPIO_PD8
#define HEADER_CONNECTOR_J2_5   GPIO_PD9
#define HEADER_CONNECTOR_J2_6   GPIO_PD10
#define HEADER_CONNECTOR_J2_7   GPIO_PD11
#define HEADER_CONNECTOR_J2_8   GPIO_PD0
#define HEADER_CONNECTOR_J2_9   GPIO_PC13
#define HEADER_CONNECTOR_J2_10  GPIO_PC14
#define HEADER_CONNECTOR_J2_11  GPIO_PD1
#define HEADER_CONNECTOR_J2_12  GPIO_PD2
#define HEADER_CONNECTOR_J2_13  GPIO_PD3
#define HEADER_CONNECTOR_J2_14  GPIO_PD4
#define HEADER_CONNECTOR_J2_15  GPIO_PD5
#define HEADER_CONNECTOR_J2_16  GPIO_PD6
#define HEADER_CONNECTOR_J2_17  GPIO_PD7
#define HEADER_CONNECTOR_J2_18  GPIO_PF0
#define HEADER_CONNECTOR_J2_19  GPIO_PF1
#define HEADER_CONNECTOR_J2_20  GPIO_PE0
#define HEADER_CONNECTOR_J2_21  GPIO_PE1
#define HEADER_CONNECTOR_J2_22  GPIO_PE2
#define HEADER_CONNECTOR_J2_23  GPIO_PE3
#define HEADER_CONNECTOR_J2_24  GPIO_PE4
#define HEADER_CONNECTOR_J2_25  GPIO_PE5
#define HEADER_CONNECTOR_J2_26  GPIO_PE6
#define HEADER_CONNECTOR_J2_27  GPIO_PE7
#define HEADER_CONNECTOR_J2_28  // Pin not routed

#define HEADER_CONNECTOR_J3_1   // Pin not routed
#define HEADER_CONNECTOR_J3_2   GPIO_PG6
#define HEADER_CONNECTOR_J3_3   GPIO_PG7
#define HEADER_CONNECTOR_J3_4   GPIO_PG8
#define HEADER_CONNECTOR_J3_5   GPIO_PG9
#define HEADER_CONNECTOR_J3_6   GPIO_PB4
#define HEADER_CONNECTOR_J3_7   GPIO_PB3
#define HEADER_CONNECTOR_J3_8   GPIO_PB2
#define HEADER_CONNECTOR_J3_9   GPIO_PB1
#define HEADER_CONNECTOR_J3_10  GPIO_PB0
#define HEADER_CONNECTOR_J3_11  // Pin not routed
#define HEADER_CONNECTOR_J3_12  // Pin not routed
#define HEADER_CONNECTOR_J3_13  // Pin not routed
#define HEADER_CONNECTOR_J3_14  GPIO_PB7
#define HEADER_CONNECTOR_J3_15  GPIO_PB6
#define HEADER_CONNECTOR_J3_16  GPIO_PB8
#define HEADER_CONNECTOR_J3_17  GPIO_PB9
#define HEADER_CONNECTOR_J3_18  GPIO_PB10
#define HEADER_CONNECTOR_J3_19  GPIO_PB11
#define HEADER_CONNECTOR_J3_20  GPIO_PB12
#define HEADER_CONNECTOR_J3_21  GPIO_PB13
#define HEADER_CONNECTOR_J3_22  GPIO_PB14
#define HEADER_CONNECTOR_J3_23  GPIO_PB15
#define HEADER_CONNECTOR_J3_24  GPIO_PF4
#define HEADER_CONNECTOR_J3_25  GPIO_PF5
#define HEADER_CONNECTOR_J3_26  // Pin not routed
#define HEADER_CONNECTOR_J3_27  // Pin not routed
#define HEADER_CONNECTOR_J3_28  // Pin not routed

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
