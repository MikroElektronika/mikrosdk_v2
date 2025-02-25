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
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "MINI-32 BOARD"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       PB7
#define HEADER_CONNECTOR_CN1_D2       PB6
#define HEADER_CONNECTOR_CN1_D3       PD3
#define HEADER_CONNECTOR_CN1_D4       PD2
#define HEADER_CONNECTOR_CN1_D5       PD1
#define HEADER_CONNECTOR_CN1_D6       PD10
#define HEADER_CONNECTOR_CN1_D7       PD9
#define HEADER_CONNECTOR_CN1_D8       PD8
#define HEADER_CONNECTOR_CN1_D11      PE7
#define HEADER_CONNECTOR_CN1_D12      PE6
#define HEADER_CONNECTOR_CN1_D13      PE5
#define HEADER_CONNECTOR_CN1_D14      PE4
#define HEADER_CONNECTOR_CN1_D15      PF4
#define HEADER_CONNECTOR_CN1_D16      PF5
#define HEADER_CONNECTOR_CN1_D17      PG8
#define HEADER_CONNECTOR_CN1_D18      PG7
#define HEADER_CONNECTOR_CN1_D19      PE3
#define HEADER_CONNECTOR_CN1_D20      PE2

#define HEADER_CONNECTOR_CN2_D2       PB5
#define HEADER_CONNECTOR_CN2_D3       PB4
#define HEADER_CONNECTOR_CN2_D4       PB1
#define HEADER_CONNECTOR_CN2_D5       PB0
#define HEADER_CONNECTOR_CN2_D6       PD11
#define HEADER_CONNECTOR_CN2_D7       PB9
#define HEADER_CONNECTOR_CN2_D8       PD5
#define HEADER_CONNECTOR_CN2_D9       PD4
#define HEADER_CONNECTOR_CN2_D10      PB8
#define HEADER_CONNECTOR_CN2_D13      PF1
#define HEADER_CONNECTOR_CN2_D14      PF0
#define HEADER_CONNECTOR_CN2_D15      PB14
#define HEADER_CONNECTOR_CN2_D16      PB15
#define HEADER_CONNECTOR_CN2_D17      PD0
#define HEADER_CONNECTOR_CN2_D18      PG6
#define HEADER_CONNECTOR_CN2_D19      PE0
#define HEADER_CONNECTOR_CN2_D20      PE1

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
