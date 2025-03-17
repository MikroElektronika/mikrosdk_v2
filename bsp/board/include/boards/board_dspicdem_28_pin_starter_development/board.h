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

#define BOARD_NAME "dsPICDEM 28-Pin Starter Development Board"

#include "dip_socket.h"

// Mapping
#define HEADER_CONNECTOR_U1_D1      MCU_CONNECTOR_1
#define HEADER_CONNECTOR_U1_D2      MCU_CONNECTOR_2
#define HEADER_CONNECTOR_U1_D3      MCU_CONNECTOR_3
#define HEADER_CONNECTOR_U1_D4      MCU_CONNECTOR_4
#define HEADER_CONNECTOR_U1_D5      MCU_CONNECTOR_5
#define HEADER_CONNECTOR_U1_D6      MCU_CONNECTOR_6
#define HEADER_CONNECTOR_U1_D7      MCU_CONNECTOR_7
#define HEADER_CONNECTOR_U1_D8      MCU_CONNECTOR_8
#define HEADER_CONNECTOR_U1_D9      MCU_CONNECTOR_9
#define HEADER_CONNECTOR_U1_D10     MCU_CONNECTOR_10
#define HEADER_CONNECTOR_U1_D11     MCU_CONNECTOR_11
#define HEADER_CONNECTOR_U1_D12     MCU_CONNECTOR_12
#define HEADER_CONNECTOR_U1_D13     MCU_CONNECTOR_13
#define HEADER_CONNECTOR_U1_D14     MCU_CONNECTOR_14
#define HEADER_CONNECTOR_U1_D15     MCU_CONNECTOR_15
#define HEADER_CONNECTOR_U1_D16     MCU_CONNECTOR_16
#define HEADER_CONNECTOR_U1_D17     MCU_CONNECTOR_17
#define HEADER_CONNECTOR_U1_D18     MCU_CONNECTOR_18
#define HEADER_CONNECTOR_U1_D19     MCU_CONNECTOR_19
#define HEADER_CONNECTOR_U1_D20     MCU_CONNECTOR_20
#define HEADER_CONNECTOR_U1_D21     MCU_CONNECTOR_21
#define HEADER_CONNECTOR_U1_D22     MCU_CONNECTOR_22
#define HEADER_CONNECTOR_U1_D23     MCU_CONNECTOR_23
#define HEADER_CONNECTOR_U1_D24     MCU_CONNECTOR_24
#define HEADER_CONNECTOR_U1_D25     MCU_CONNECTOR_25
#define HEADER_CONNECTOR_U1_D26     MCU_CONNECTOR_26
#define HEADER_CONNECTOR_U1_D27     MCU_CONNECTOR_27
#define HEADER_CONNECTOR_U1_D28     MCU_CONNECTOR_28

#define HEADER_CONNECTOR_U2_D1      MCU_CONNECTOR_1
#define HEADER_CONNECTOR_U2_D2      MCU_CONNECTOR_2
#define HEADER_CONNECTOR_U2_D3      MCU_CONNECTOR_3
#define HEADER_CONNECTOR_U2_D4      MCU_CONNECTOR_4
#define HEADER_CONNECTOR_U2_D5      MCU_CONNECTOR_5
#define HEADER_CONNECTOR_U2_D6      MCU_CONNECTOR_6
#define HEADER_CONNECTOR_U2_D7      MCU_CONNECTOR_7
#define HEADER_CONNECTOR_U2_D8      MCU_CONNECTOR_8
#define HEADER_CONNECTOR_U2_D9      MCU_CONNECTOR_9
#define HEADER_CONNECTOR_U2_D10     MCU_CONNECTOR_10
#define HEADER_CONNECTOR_U2_D11     MCU_CONNECTOR_11
#define HEADER_CONNECTOR_U2_D12     MCU_CONNECTOR_12
#define HEADER_CONNECTOR_U2_D13     MCU_CONNECTOR_13
#define HEADER_CONNECTOR_U2_D14     MCU_CONNECTOR_14
#define HEADER_CONNECTOR_U2_D15     MCU_CONNECTOR_15
#define HEADER_CONNECTOR_U2_D16     MCU_CONNECTOR_16
#define HEADER_CONNECTOR_U2_D17     MCU_CONNECTOR_17
#define HEADER_CONNECTOR_U2_D18     MCU_CONNECTOR_18
#define HEADER_CONNECTOR_U2_D19     MCU_CONNECTOR_19
#define HEADER_CONNECTOR_U2_D20     MCU_CONNECTOR_20
#define HEADER_CONNECTOR_U2_D21     MCU_CONNECTOR_21
#define HEADER_CONNECTOR_U2_D22     MCU_CONNECTOR_22
#define HEADER_CONNECTOR_U2_D23     MCU_CONNECTOR_23
#define HEADER_CONNECTOR_U2_D24     MCU_CONNECTOR_24
#define HEADER_CONNECTOR_U2_D25     MCU_CONNECTOR_25
#define HEADER_CONNECTOR_U2_D26     MCU_CONNECTOR_26
#define HEADER_CONNECTOR_U2_D27     MCU_CONNECTOR_27
#define HEADER_CONNECTOR_U2_D28     MCU_CONNECTOR_28

#define HEADER_CONNECTOR_J4_D1      MCU_CONNECTOR_1
#define HEADER_CONNECTOR_J4_D2      MCU_CONNECTOR_26
#define HEADER_CONNECTOR_J4_D3      MCU_CONNECTOR_2
#define HEADER_CONNECTOR_J4_D4      MCU_CONNECTOR_25
#define HEADER_CONNECTOR_J4_D5      MCU_CONNECTOR_3
#define HEADER_CONNECTOR_J4_D6      MCU_CONNECTOR_24
#define HEADER_CONNECTOR_J4_D7      MCU_CONNECTOR_4
#define HEADER_CONNECTOR_J4_D8      MCU_CONNECTOR_23
#define HEADER_CONNECTOR_J4_D9      MCU_CONNECTOR_5
#define HEADER_CONNECTOR_J4_D10     MCU_CONNECTOR_22
#define HEADER_CONNECTOR_J4_D11     MCU_CONNECTOR_6
#define HEADER_CONNECTOR_J4_D12     MCU_CONNECTOR_21// Pin not routed
#define HEADER_CONNECTOR_J4_D13     MCU_CONNECTOR_7
#define HEADER_CONNECTOR_J4_D14     MCU_CONNECTOR_18
#define HEADER_CONNECTOR_J4_D15     MCU_CONNECTOR_11
#define HEADER_CONNECTOR_J4_D16     MCU_CONNECTOR_17
#define HEADER_CONNECTOR_J4_D17     MCU_CONNECTOR_12
#define HEADER_CONNECTOR_J4_D18     MCU_CONNECTOR_16
#define HEADER_CONNECTOR_J4_D19     MCU_CONNECTOR_14
#define HEADER_CONNECTOR_J4_D20     MCU_CONNECTOR_15
#define HEADER_CONNECTOR_J4_D21     // Pin not routed
#define HEADER_CONNECTOR_J4_D22     // Pin not routed
#define HEADER_CONNECTOR_J4_D23     // Pin not routed
#define HEADER_CONNECTOR_J4_D24     // Pin not routed
#define HEADER_CONNECTOR_J4_D25     // Pin not routed
#define HEADER_CONNECTOR_J4_D26     // Pin not routed
#define HEADER_CONNECTOR_J4_D27     // Pin not routed
#define HEADER_CONNECTOR_J4_D28     // Pin not routed

#define LED_1   MCU_CONNECTOR_15

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
