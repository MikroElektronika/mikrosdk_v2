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

#define BOARD_NAME "Chameleon 16-Bit Development Kit"

#include "dip_socket.h"

// Mapping
#define HEADER_CONNECTOR_J4_D0  MCU_CONNECTOR_4
#define HEADER_CONNECTOR_J4_D1  MCU_CONNECTOR_5
#define HEADER_CONNECTOR_J4_D2  MCU_CONNECTOR_6
#define HEADER_CONNECTOR_J4_D3  MCU_CONNECTOR_7
#define HEADER_CONNECTOR_J4_D4  MCU_CONNECTOR_11
#define HEADER_CONNECTOR_J4_D5  MCU_CONNECTOR_14
#define HEADER_CONNECTOR_J4_D6  MCU_CONNECTOR_15
#define HEADER_CONNECTOR_J4_D7  MCU_CONNECTOR_16

#define HEADER_CONNECTOR_J5_D8  MCU_CONNECTOR_18
#define HEADER_CONNECTOR_J5_D9  MCU_CONNECTOR_12
#define HEADER_CONNECTOR_J5_D10 MCU_CONNECTOR_21
#define HEADER_CONNECTOR_J5_D11 MCU_CONNECTOR_22
#define HEADER_CONNECTOR_J5_D12 MCU_CONNECTOR_23
#define HEADER_CONNECTOR_J5_D13 MCU_CONNECTOR_24

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
