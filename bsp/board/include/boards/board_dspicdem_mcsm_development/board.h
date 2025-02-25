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

#define BOARD_NAME "dsPICDEM MCSM Development Board"

#include "pim_socket.h"

// Mapping
#define PWM1H3      PIM_PIN_003
#define PWM2L1_1    PIM_PIN_004
#define PWM2H1_1    PIM_PIN_005
#define PWM2H1_2    PIM_PIN_018
#define PWM2L1_2    PIM_PIN_019
#define IMOTOTR2    PIM_PIN_024
#define IMOTOTR1    PIM_PIN_025
#define DC_REF      PIM_PIN_035
#define USB_RX_1    PIM_PIN_049
#define USB_TX_1    PIM_PIN_050
#define USB_RX_2    PIM_PIN_051
#define USB_TX_2    PIM_PIN_052
#define USB_VBUS    PIM_PIN_054
#define USB_D_M     PIM_PIN_056
#define USB_D_P     PIM_PIN_057
#define USB_TX_3    PIM_PIN_076
#define PWM2H1_3    PIM_PIN_077
#define PWM2L1_3    PIM_PIN_078
#define USB_TX_4    PIM_PIN_083
#define USB_RX_4    PIM_PIN_084
#define PWM1L1      PIM_PIN_093
#define PWM1H1      PIM_PIN_094
#define PWM1L2      PIM_PIN_098
#define PWM1H2      PIM_PIN_099
#define PWM1L3      PIM_PIN_100

#define POT     PIM_PIN_020

#define BUTTON_S1       PIM_PIN_070

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
