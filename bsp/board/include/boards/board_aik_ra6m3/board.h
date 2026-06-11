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

#define BOARD_NAME "AI Kit Development Platform with RA6M3"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_PMOD1_D1      GPIO_P207
#define HEADER_CONNECTOR_PMOD1_D2      GPIO_P203
#define HEADER_CONNECTOR_PMOD1_D3      GPIO_P202
#define HEADER_CONNECTOR_PMOD1_D4      GPIO_P204
#define HEADER_CONNECTOR_PMOD1_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD1_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD1_D7      GPIO_P000
#define HEADER_CONNECTOR_PMOD1_D8      GPIO_P209
#define HEADER_CONNECTOR_PMOD1_D9      GPIO_P210
#define HEADER_CONNECTOR_PMOD1_D10     GPIO_P313
#define HEADER_CONNECTOR_PMOD1_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD1_D12     // Pin not routed.

#define HEADER_CONNECTOR_PMOD2_D1      GPIO_PB01
#define HEADER_CONNECTOR_PMOD2_D2      GPIO_P707
#define HEADER_CONNECTOR_PMOD2_D3      GPIO_P706
#define HEADER_CONNECTOR_PMOD2_D4      GPIO_PB00
#define HEADER_CONNECTOR_PMOD2_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD2_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD2_D7      GPIO_P804
#define HEADER_CONNECTOR_PMOD2_D8      GPIO_P414
#define HEADER_CONNECTOR_PMOD2_D9      GPIO_P500
#define HEADER_CONNECTOR_PMOD2_D10     GPIO_P507
#define HEADER_CONNECTOR_PMOD2_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD2_D12     // Pin not routed.

#define HEADER_CONNECTOR_PMOD3_D1      GPIO_P606
#define HEADER_CONNECTOR_PMOD3_D2      GPIO_PA00
#define HEADER_CONNECTOR_PMOD3_D3      GPIO_P607
#define HEADER_CONNECTOR_PMOD3_D4      GPIO_PA01
#define HEADER_CONNECTOR_PMOD3_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD3_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD3_D7      GPIO_P002
#define HEADER_CONNECTOR_PMOD3_D8      GPIO_P508
#define HEADER_CONNECTOR_PMOD3_D9      GPIO_P513
#define HEADER_CONNECTOR_PMOD3_D10     GPIO_P600
#define HEADER_CONNECTOR_PMOD3_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD3_D12     // Pin not routed.

#define HEADER_CONNECTOR_PMOD4_D1      GPIO_P504
#define HEADER_CONNECTOR_PMOD4_D2      GPIO_P501
#define HEADER_CONNECTOR_PMOD4_D3      GPIO_P502
#define HEADER_CONNECTOR_PMOD4_D4      GPIO_P503
#define HEADER_CONNECTOR_PMOD4_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD4_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD4_D7      GPIO_P004
#define HEADER_CONNECTOR_PMOD4_D8      GPIO_P615
#define HEADER_CONNECTOR_PMOD4_D9      GPIO_P802
#define HEADER_CONNECTOR_PMOD4_D10     GPIO_P803
#define HEADER_CONNECTOR_PMOD4_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD4_D12     // Pin not routed.

#define HEADER_CONNECTOR_PMOD5_D1      GPIO_P806
#define HEADER_CONNECTOR_PMOD5_D2      GPIO_P900
#define HEADER_CONNECTOR_PMOD5_D3      GPIO_P315
#define HEADER_CONNECTOR_PMOD5_D4      GPIO_P901
#define HEADER_CONNECTOR_PMOD5_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D7      // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D8      // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D9      // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D10     // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD5_D12     // Pin not routed.

#define HEADER_CONNECTOR_PMOD6_D1      GPIO_P006
#define HEADER_CONNECTOR_PMOD6_D2      GPIO_P905
#define HEADER_CONNECTOR_PMOD6_D3      GPIO_P400
#define HEADER_CONNECTOR_PMOD6_D4      GPIO_P401
#define HEADER_CONNECTOR_PMOD6_D5      // Pin not routed.
#define HEADER_CONNECTOR_PMOD6_D6      // Pin not routed.
#define HEADER_CONNECTOR_PMOD6_D7      GPIO_PA08
#define HEADER_CONNECTOR_PMOD6_D8      GPIO_PA09
#define HEADER_CONNECTOR_PMOD6_D9      GPIO_PA10
#define HEADER_CONNECTOR_PMOD6_D10     GPIO_P805
#define HEADER_CONNECTOR_PMOD6_D11     // Pin not routed.
#define HEADER_CONNECTOR_PMOD6_D12     // Pin not routed.

#define BUTTON1    GPIO_P007
#define BUTTON2    GPIO_P003

#define LED1       GPIO_P908
#define LED2       GPIO_P907
#define LED3       GPIO_P906

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
