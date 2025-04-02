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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/{markdown_path}
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "Arduino Leonardo with Headers"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_JP1_D1     GPIO_PB4
#define HEADER_CONNECTOR_JP1_D2     GPIO_PB5
#define HEADER_CONNECTOR_JP1_D3     GPIO_PB6
#define HEADER_CONNECTOR_JP1_D4     GPIO_PB7
#define HEADER_CONNECTOR_JP1_D5     GPIO_PD6
#define HEADER_CONNECTOR_JP1_D6     GPIO_PC7
#define HEADER_CONNECTOR_JP1_D7     // Pin not routed
#define HEADER_CONNECTOR_JP1_D8     // Pin not routed
#define HEADER_CONNECTOR_JP1_D9     GPIO_PD1
#define HEADER_CONNECTOR_JP1_D10    GPIO_PD0

#define HEADER_CONNECTOR_J2_D1     GPIO_PD2
#define HEADER_CONNECTOR_J2_D2     GPIO_PD3
#define HEADER_CONNECTOR_J2_D3     GPIO_PD1
#define HEADER_CONNECTOR_J2_D4     GPIO_PD0
#define HEADER_CONNECTOR_J2_D5     GPIO_PD4
#define HEADER_CONNECTOR_J2_D6     GPIO_PC6
#define HEADER_CONNECTOR_J2_D7     GPIO_PD7
#define HEADER_CONNECTOR_J2_D8     GPIO_PE6

#define HEADER_CONNECTOR_J4_D1     GPIO_PF7
#define HEADER_CONNECTOR_J4_D2     GPIO_PF6
#define HEADER_CONNECTOR_J4_D3     GPIO_PF5
#define HEADER_CONNECTOR_J4_D4     GPIO_PF4
#define HEADER_CONNECTOR_J4_D5     GPIO_PF1
#define HEADER_CONNECTOR_J4_D6     GPIO_PF0

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
