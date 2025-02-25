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

#define BOARD_NAME "dsPICDEM 2 Development Board"

#include "dip_socket.h"

// Mapping
#define HEADER_CONNECTOR_H8_D1      // Pin not pouted
#define HEADER_CONNECTOR_H8_D2      CONNECTOR_RB0_1
#define HEADER_CONNECTOR_H8_D3      CONNECTOR_RB1_1
#define HEADER_CONNECTOR_H8_D4      CONNECTOR_RB2_1
#define HEADER_CONNECTOR_H8_D5      CONNECTOR_RB3_1
#define HEADER_CONNECTOR_H8_D6      CONNECTOR_RB4_1
#define HEADER_CONNECTOR_H8_D7      CONNECTOR_RB5_1
#define HEADER_CONNECTOR_H8_D8      CONNECTOR_RB6_1
#define HEADER_CONNECTOR_H8_D9      CONNECTOR_RB7_1
#define HEADER_CONNECTOR_H8_D10     CONNECTOR_RB8_1
#define HEADER_CONNECTOR_H8_D11     // Pin not pouted
#define HEADER_CONNECTOR_H8_D12     // Pin not pouted
#define HEADER_CONNECTOR_H8_D13     // Pin not pouted
#define HEADER_CONNECTOR_H8_D14     // Pin not pouted
#define HEADER_CONNECTOR_H8_D15     CONNECTOR_RC13_1
#define HEADER_CONNECTOR_H8_D16     CONNECTOR_RC14_1
#define HEADER_CONNECTOR_H8_D17     CONNECTOR_RA11_1
#define HEADER_CONNECTOR_H8_D18     CONNECTOR_RD9_1
#define HEADER_CONNECTOR_H8_D19     CONNECTOR_RD3_1
#define HEADER_CONNECTOR_H8_D20     // Pin not pouted
#define HEADER_CONNECTOR_H8_D21     // Pin not pouted
#define HEADER_CONNECTOR_H8_D22     CONNECTOR_RD2_1
#define HEADER_CONNECTOR_H8_D23     CONNECTOR_RD8_1
#define HEADER_CONNECTOR_H8_D24     CONNECTOR_RF6_1
#define HEADER_CONNECTOR_H8_D25     CONNECTOR_RF3_1
#define HEADER_CONNECTOR_H8_D26     CONNECTOR_RF2_1
#define HEADER_CONNECTOR_H8_D27     CONNECTOR_RF5_1
#define HEADER_CONNECTOR_H8_D28     CONNECTOR_RF4_1
#define HEADER_CONNECTOR_H8_D29     CONNECTOR_RF1_1
#define HEADER_CONNECTOR_H8_D30     CONNECTOR_RF0_1
#define HEADER_CONNECTOR_H8_D31     // Pin not pouted
#define HEADER_CONNECTOR_H8_D32     // Pin not pouted
#define HEADER_CONNECTOR_H8_D33     CONNECTOR_RD1_1
#define HEADER_CONNECTOR_H8_D34     CONNECTOR_RD0_1
#define HEADER_CONNECTOR_H8_D35     CONNECTOR_RB12_1
#define HEADER_CONNECTOR_H8_D36     CONNECTOR_RB11_1
#define HEADER_CONNECTOR_H8_D37     CONNECTOR_RB10_1
#define HEADER_CONNECTOR_H8_D38     CONNECTOR_RB9_1
#define HEADER_CONNECTOR_H8_D39     // Pin not pouted
#define HEADER_CONNECTOR_H8_D40     // Pin not pouted

#define HEADER_CONNECTOR_H9_D1      // Pin not pouted
#define HEADER_CONNECTOR_H9_D2      CONNECTOR_RB0_2
#define HEADER_CONNECTOR_H9_D3      CONNECTOR_RB1_2
#define HEADER_CONNECTOR_H9_D4      CONNECTOR_RB2_2
#define HEADER_CONNECTOR_H9_D5      CONNECTOR_RB3_2
#define HEADER_CONNECTOR_H9_D6      CONNECTOR_RB4_2
#define HEADER_CONNECTOR_H9_D7      CONNECTOR_RB5_2
#define HEADER_CONNECTOR_H9_D8      CONNECTOR_RB6_2
#define HEADER_CONNECTOR_H9_D9      CONNECTOR_RB7_2
#define HEADER_CONNECTOR_H9_D10     CONNECTOR_RB8_2
#define HEADER_CONNECTOR_H9_D11     // Pin not pouted
#define HEADER_CONNECTOR_H9_D12     // Pin not pouted
#define HEADER_CONNECTOR_H9_D13     // Pin not pouted
#define HEADER_CONNECTOR_H9_D14     // Pin not pouted
#define HEADER_CONNECTOR_H9_D15     CONNECTOR_RC13_2
#define HEADER_CONNECTOR_H9_D16     CONNECTOR_RC14_2
#define HEADER_CONNECTOR_H9_D17     CONNECTOR_RE8_2
#define HEADER_CONNECTOR_H9_D18     CONNECTOR_RD1_2
#define HEADER_CONNECTOR_H9_D19     CONNECTOR_RD3_2
#define HEADER_CONNECTOR_H9_D20     // Pin not pouted
#define HEADER_CONNECTOR_H9_D21     // Pin not pouted
#define HEADER_CONNECTOR_H9_D22     CONNECTOR_RD2_2
#define HEADER_CONNECTOR_H9_D23     CONNECTOR_RD0_2
#define HEADER_CONNECTOR_H9_D24     CONNECTOR_RF6_2
#define HEADER_CONNECTOR_H9_D25     CONNECTOR_RF3_2
#define HEADER_CONNECTOR_H9_D26     CONNECTOR_RF2_2
#define HEADER_CONNECTOR_H9_D27     CONNECTOR_RF5_2
#define HEADER_CONNECTOR_H9_D28     CONNECTOR_RF4_2
#define HEADER_CONNECTOR_H9_D29     CONNECTOR_RF1_2
#define HEADER_CONNECTOR_H9_D30     CONNECTOR_RF0_2
#define HEADER_CONNECTOR_H9_D31     // Pin not pouted
#define HEADER_CONNECTOR_H9_D32     // Pin not pouted
#define HEADER_CONNECTOR_H9_D33     CONNECTOR_RE5_2
#define HEADER_CONNECTOR_H9_D34     CONNECTOR_RE4_2
#define HEADER_CONNECTOR_H9_D35     CONNECTOR_RE3_2
#define HEADER_CONNECTOR_H9_D36     CONNECTOR_RE2_2
#define HEADER_CONNECTOR_H9_D37     CONNECTOR_RE1_2
#define HEADER_CONNECTOR_H9_D38     CONNECTOR_RE0_2
#define HEADER_CONNECTOR_H9_D39     // Pin not pouted
#define HEADER_CONNECTOR_H9_D40     // Pin not pouted

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
