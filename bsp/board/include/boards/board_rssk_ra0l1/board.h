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

#define BOARD_NAME "Capacitive Touch Evaluation System for RA0L1"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D2      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D3      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D4      GPIO_P206
#define HEADER_CONNECTOR_CN1_D5      GPIO_P915
#define HEADER_CONNECTOR_CN1_D6      GPIO_P201
#define HEADER_CONNECTOR_CN1_D7      GPIO_P914
#define HEADER_CONNECTOR_CN1_D8      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D9      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D10     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D11     GPIO_P913
#define HEADER_CONNECTOR_CN1_D12     GPIO_P407
#define HEADER_CONNECTOR_CN1_D13     GPIO_P408
#define HEADER_CONNECTOR_CN1_D14     GPIO_P409
#define HEADER_CONNECTOR_CN1_D15     // Pin not routed.
#define HEADER_CONNECTOR_CN1_D16     // Pin not routed.

#define HEADER_CONNECTOR_CN2_D1      GPIO_P302
#define HEADER_CONNECTOR_CN2_D2      GPIO_P301
#define HEADER_CONNECTOR_CN2_D3      GPIO_P109
#define HEADER_CONNECTOR_CN2_D4      GPIO_P110
#define HEADER_CONNECTOR_CN2_D5      GPIO_P111
#define HEADER_CONNECTOR_CN2_D6      GPIO_P106
#define HEADER_CONNECTOR_CN2_D7      GPIO_P105
#define HEADER_CONNECTOR_CN2_D8      GPIO_P104
#define HEADER_CONNECTOR_CN2_D9      GPIO_P103
#define HEADER_CONNECTOR_CN2_D10     GPIO_P102
#define HEADER_CONNECTOR_CN2_D11     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D12     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D13     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D14     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D15     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D16     GPIO_P101
#define HEADER_CONNECTOR_CN2_D17     GPIO_P100
#define HEADER_CONNECTOR_CN2_D18     GPIO_P500
#define HEADER_CONNECTOR_CN2_D19     GPIO_P015
#define HEADER_CONNECTOR_CN2_D20     GPIO_P014
#define HEADER_CONNECTOR_CN2_D21     GPIO_P013
#define HEADER_CONNECTOR_CN2_D22     GPIO_P012
#define HEADER_CONNECTOR_CN2_D23     GPIO_P009
#define HEADER_CONNECTOR_CN2_D24     GPIO_P008
#define HEADER_CONNECTOR_CN2_D25     GPIO_P011
#define HEADER_CONNECTOR_CN2_D26     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D27     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D28     GPIO_P010
#define HEADER_CONNECTOR_CN2_D29     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D30     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D31     GPIO_P002
#define HEADER_CONNECTOR_CN2_D32     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D33     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D34     GPIO_P001
#define HEADER_CONNECTOR_CN2_D35     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D36     GPIO_P000
#define HEADER_CONNECTOR_CN2_D37     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D38     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D39     // Pin not routed.
#define HEADER_CONNECTOR_CN2_D40     // Pin not routed.

#define BUTTON2    GPIO_P215
#define BUTTON3    GPIO_P214

#define LED2       GPIO_P400
#define LED3       GPIO_P401

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
