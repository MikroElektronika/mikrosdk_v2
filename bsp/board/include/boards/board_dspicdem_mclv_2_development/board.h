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

#define BOARD_NAME "dsPICDEM MCLV-2 Development Board"

#include "pim_socket.h"

// Mapping
#define CONNECTOR_DBG_LED2          PIM_PIN_001
#define CONNECTOR_PWM1H3            PIM_PIN_003
#define CONNECTOR_MCLR              PIM_PIN_013
#define CONNECTOR_FAULT             PIM_PIN_018
#define CONNECTOR_TX                PIM_PIN_019
#define CONNECTOR_PIM_V_M3          PIM_PIN_020
#define CONNECTOR_PIM_V_M2          PIM_PIN_021
#define CONNECTOR_PIM_V_M1          PIM_PIN_022
#define CONNECTOR_PIM_IMOTOR_SUM    PIM_PIN_023
#define CONNECTOR_PIM_IMOTOR2       PIM_PIN_024
#define CONNECTOR_PIM_IMOTOR1       PIM_PIN_025
#define CONNECTOR_PGC               PIM_PIN_026
#define CONNECTOR_PGD               PIM_PIN_027
#define CONNECTOR_VREF              PIM_PIN_028
#define CONNECTOR_PIM_REC_NEUTR     PIM_PIN_029
#define CONNECTOR_AVDD              PIM_PIN_030
#define CONNECTOR_AVSS              PIM_PIN_031
#define CONNECTOR_PIM_POT           PIM_PIN_032
#define CONNECTOR_PIM_GEN2          PIM_PIN_034
#define CONNECTOR_PIM_VBUS          PIM_PIN_035
#define CONNECTOR_PIM_MONITOR_1     PIM_PIN_041
#define CONNECTOR_PIM_MONITOR_2     PIM_PIN_042
#define CONNECTOR_PIM_MONITOR_3     PIM_PIN_043
#define CONNECTOR_HALLB             PIM_PIN_047
#define CONNECTOR_HALLC             PIM_PIN_048
#define CONNECTOR_RX                PIM_PIN_049
#define CONNECTOR_USB_TX            PIM_PIN_051
#define CONNECTOR_USB_RX            PIM_PIN_052
#define CONNECTOR_PIM_FLT_OUT2      PIM_PIN_058
#define CONNECTOR_PIM_FLT_OUT1      PIM_PIN_059
#define CONNECTOR_DBG_LED1          PIM_PIN_060
#define CONNECTOR_HOME              PIM_PIN_061
#define CONNECTOR_OSC1              PIM_PIN_063
#define CONNECTOR_OSC2              PIM_PIN_064
#define CONNECTOR_PIM_IBUSP         PIM_PIN_066
#define CONNECTOR_PIM_IBUSM         PIM_PIN_067
#define CONNECTOR_LIN_CS            PIM_PIN_068
#define CONNECTOR_LIN_FAULT         PIM_PIN_069
#define CONNECTOR_PIM_IBP           PIM_PIN_073
#define CONNECTOR_PIM_IAP           PIM_PIN_074
#define CONNECTOR_CAN_TX            PIM_PIN_077
#define CONNECTOR_CAN_RX            PIM_PIN_078
#define CONNECTOR_HALLA             PIM_PIN_080
#define CONNECTOR_PIM_GEN1          PIM_PIN_082
#define CONNECTOR_PWM1L1            PIM_PIN_093
#define CONNECTOR_PWM1H1            PIM_PIN_094
#define CONNECTOR_PWM1L2            PIM_PIN_098
#define CONNECTOR_PWM1H2            PIM_PIN_099
#define CONNECTOR_PWM1L3            PIM_PIN_100

#define BUTTON_1    PIM_PIN_083
#define BUTTON_2    PIM_PIN_084

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
