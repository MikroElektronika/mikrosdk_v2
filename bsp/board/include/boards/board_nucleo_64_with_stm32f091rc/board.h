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

// Hardware revision number
#define BOARD_REV_MAJOR (C)
#define BOARD_REV_MINOR (03)

#define BOARD_NAME "Nucleo-F091RC"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1  PC10 // Pin not routed.
#define HEADER_CONNECTOR_CN1_D2  PC11 // Pin not routed.
#define HEADER_CONNECTOR_CN1_D3  PC12
#define HEADER_CONNECTOR_CN1_D4  PD2
#define HEADER_CONNECTOR_CN1_D5       // Pin not routed.
#define HEADER_CONNECTOR_CN1_D6       // Pin not routed.
#define HEADER_CONNECTOR_CN1_D7       // Pin not routed.
#define HEADER_CONNECTOR_CN1_D8       // Pin not routed.
#define HEADER_CONNECTOR_CN1_D9       // Pin not routed.
#define HEADER_CONNECTOR_CN1_D10      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D11      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D12      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D13 PA13 // Pin not routed.
#define HEADER_CONNECTOR_CN1_D14      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D15 PA14 // Pin not routed.
#define HEADER_CONNECTOR_CN1_D16      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D17 PA15
#define HEADER_CONNECTOR_CN1_D18      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D19      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D20      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D21 PB7  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D22      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D23 PC13 // Pin not routed.
#define HEADER_CONNECTOR_CN1_D24      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D25 PC14
#define HEADER_CONNECTOR_CN1_D26      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D27 PC15 // Pin not routed.
#define HEADER_CONNECTOR_CN1_D28 PA0  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D29 PF0  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D30 PA1  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D31 PF1  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D32 PA4  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D33      // Pin not routed.
#define HEADER_CONNECTOR_CN1_D34 PB0  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D35 PC2  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D36 PC1
#define HEADER_CONNECTOR_CN1_D37 PC3  // Pin not routed.
#define HEADER_CONNECTOR_CN1_D38 PC0

#define HEADER_CONNECTOR_CN2_D1  PC9
#define HEADER_CONNECTOR_CN2_D2  PC8
#define HEADER_CONNECTOR_CN2_D3  PB8
#define HEADER_CONNECTOR_CN2_D4  PC6
#define HEADER_CONNECTOR_CN2_D5  PB9
#define HEADER_CONNECTOR_CN2_D6  PC5  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D7       // Pin not routed.
#define HEADER_CONNECTOR_CN2_D8       // Pin not routed.
#define HEADER_CONNECTOR_CN2_D9       // Pin not routed.
#define HEADER_CONNECTOR_CN2_D10      // Pin not routed.
#define HEADER_CONNECTOR_CN2_D11 PA5  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D12 PA12 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D13 PA6  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D14 PA11 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D15 PA7  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D16 PB12
#define HEADER_CONNECTOR_CN2_D17 PB6
#define HEADER_CONNECTOR_CN2_D18 PB11 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D19 PC7  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D20      // Pin not routed.
#define HEADER_CONNECTOR_CN2_D21 PA9  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D22 PB2  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D23 PA8  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D24 PB1  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D25 PB10 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D26 PB15 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D27 PB4
#define HEADER_CONNECTOR_CN2_D28 PB14 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D29 PB5
#define HEADER_CONNECTOR_CN2_D30 PB13 // Pin not routed.
#define HEADER_CONNECTOR_CN2_D31 PB3
#define HEADER_CONNECTOR_CN2_D32      // Pin not routed.
#define HEADER_CONNECTOR_CN2_D33 PA10
#define HEADER_CONNECTOR_CN2_D34 PC4  // Pin not routed.
#define HEADER_CONNECTOR_CN2_D35 PA2
#define HEADER_CONNECTOR_CN2_D36      // Pin not routed.
#define HEADER_CONNECTOR_CN2_D37 PA3
#define HEADER_CONNECTOR_CN2_D38      // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
