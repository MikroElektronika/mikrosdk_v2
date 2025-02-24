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
** The above copyPIM notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYPIM HOLDERS BE LIABLE FOR ANY CLAIM,
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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (6)
#define BOARD_REV_MINOR (3)

#define BOARD_NAME "Explorer 16-32"

#include "pim_socket.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1 1
#define MIKROBUS_1_AN PIM_PIN_025
#define MIKROBUS_1_RST PIM_PIN_095
#define MIKROBUS_1_CS PIM_PIN_014
#define MIKROBUS_1_SCK PIM_PIN_010
#define MIKROBUS_1_MISO PIM_PIN_011
#define MIKROBUS_1_MOSI PIM_PIN_012
#define MIKROBUS_1_PWM PIM_PIN_072
#define MIKROBUS_1_RX PIM_PIN_052
#define MIKROBUS_1_INT PIM_PIN_067
#define MIKROBUS_1_TX PIM_PIN_051
#define MIKROBUS_1_SCL PIM_PIN_057
#define MIKROBUS_1_SDA PIM_PIN_056

#define MIKROBUS_2 2
#define MIKROBUS_2_AN PIM_PIN_024
#define MIKROBUS_2_RST PIM_PIN_019
#define MIKROBUS_2_CS PIM_PIN_023
#define MIKROBUS_2_SCK PIM_PIN_055
#define MIKROBUS_2_MISO PIM_PIN_054
#define MIKROBUS_2_MOSI PIM_PIN_053
#define MIKROBUS_2_PWM PIM_PIN_078
#define MIKROBUS_2_RX PIM_PIN_049
#define MIKROBUS_2_INT PIM_PIN_018
#define MIKROBUS_2_TX PIM_PIN_050
#define MIKROBUS_2_SCL PIM_PIN_057
#define MIKROBUS_2_SDA PIM_PIN_056

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
