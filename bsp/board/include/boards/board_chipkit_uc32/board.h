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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.4/new_hw/2025-06-13.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "chipKIT UC32 Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN5_D1     PD10
#define HEADER_CONNECTOR_CN5_D2     PD5
#define HEADER_CONNECTOR_CN5_D3     PD3
#define HEADER_CONNECTOR_CN5_D4     PD11
#define HEADER_CONNECTOR_CN5_D5     PD4
#define HEADER_CONNECTOR_CN5_D6     PD6
#define HEADER_CONNECTOR_CN5_D7     PG8
#define HEADER_CONNECTOR_CN5_D8     PD7
#define HEADER_CONNECTOR_CN5_D9     PG7
#define HEADER_CONNECTOR_CN5_D10    PF6
#define HEADER_CONNECTOR_CN5_D11    PG6
#define HEADER_CONNECTOR_CN5_D12    PF4
#define HEADER_CONNECTOR_CN5_D13    // Pin not routed
#define HEADER_CONNECTOR_CN5_D14    PF5
#define HEADER_CONNECTOR_CN5_D15    PB0
#define HEADER_CONNECTOR_CN5_D16    PB1

#define HEADER_CONNECTOR_CN6_D1     PF2
#define HEADER_CONNECTOR_CN6_D2     PE0
#define HEADER_CONNECTOR_CN6_D3     PF3
#define HEADER_CONNECTOR_CN6_D4     PE1
#define HEADER_CONNECTOR_CN6_D5     PD8
#define HEADER_CONNECTOR_CN6_D6     PE2
#define HEADER_CONNECTOR_CN6_D7     PD0
#define HEADER_CONNECTOR_CN6_D8     PE3
#define HEADER_CONNECTOR_CN6_D9     PF1
#define HEADER_CONNECTOR_CN6_D10    PE4
#define HEADER_CONNECTOR_CN6_D11    PD1
#define HEADER_CONNECTOR_CN6_D12    PE5
#define HEADER_CONNECTOR_CN6_D13    PD2
#define HEADER_CONNECTOR_CN6_D14    PE6
#define HEADER_CONNECTOR_CN6_D15    PD9
#define HEADER_CONNECTOR_CN6_D16    PE7

#define HEADER_CONNECTOR_CN7_D1     PB2
#define HEADER_CONNECTOR_CN7_D2     PB3
#define HEADER_CONNECTOR_CN7_D3     PB4
#define HEADER_CONNECTOR_CN7_D4     PB5
#define HEADER_CONNECTOR_CN7_D5     PB8
#define HEADER_CONNECTOR_CN7_D6     PB9
#define HEADER_CONNECTOR_CN7_D7     PB10
#define HEADER_CONNECTOR_CN7_D8     PB11
#define HEADER_CONNECTOR_CN7_D9     PB12
#define HEADER_CONNECTOR_CN7_D10    PB13
#define HEADER_CONNECTOR_CN7_D11    PB14
#define HEADER_CONNECTOR_CN7_D12    PB15

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
