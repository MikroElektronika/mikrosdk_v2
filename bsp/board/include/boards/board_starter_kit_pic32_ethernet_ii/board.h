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

#define BOARD_NAME "PIC32 ETHERNET STARTER KIT II"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       // Pin not routed
#define HEADER_CONNECTOR_CN1_D2       // Pin not routed
#define HEADER_CONNECTOR_CN1_D3       PG14
#define HEADER_CONNECTOR_CN1_D4       PA6
#define HEADER_CONNECTOR_CN1_D5       PG12
#define HEADER_CONNECTOR_CN1_D6       PA7
#define HEADER_CONNECTOR_CN1_D7       PE7
#define HEADER_CONNECTOR_CN1_D8       PG13
#define HEADER_CONNECTOR_CN1_D9       PE6
#define HEADER_CONNECTOR_CN1_D10      PG0
#define HEADER_CONNECTOR_CN1_D11      // Pin not routed
#define HEADER_CONNECTOR_CN1_D12      // Pin not routed
#define HEADER_CONNECTOR_CN1_D13      PE5
#define HEADER_CONNECTOR_CN1_D14      PG1
#define HEADER_CONNECTOR_CN1_D15      PE4
#define HEADER_CONNECTOR_CN1_D16      PF1
#define HEADER_CONNECTOR_CN1_D17      PE3
#define HEADER_CONNECTOR_CN1_D18      PF0
#define HEADER_CONNECTOR_CN1_D19      PE2
#define HEADER_CONNECTOR_CN1_D20      PD12
#define HEADER_CONNECTOR_CN1_D21      PE1
#define HEADER_CONNECTOR_CN1_D22      PD13
#define HEADER_CONNECTOR_CN1_D23      PE0
#define HEADER_CONNECTOR_CN1_D24      PD6
#define HEADER_CONNECTOR_CN1_D25      PD5
#define HEADER_CONNECTOR_CN1_D26      PD7
#define HEADER_CONNECTOR_CN1_D28      PD4
#define HEADER_CONNECTOR_CN1_D29      PD10
#define HEADER_CONNECTOR_CN1_D30      PC13
#define HEADER_CONNECTOR_CN1_D31      PC14
#define HEADER_CONNECTOR_CN1_D32      PC14
#define HEADER_CONNECTOR_CN1_D33      // Pin not routed
#define HEADER_CONNECTOR_CN1_D34      // Pin not routed
#define HEADER_CONNECTOR_CN1_D35      PC1
#define HEADER_CONNECTOR_CN1_D36      PB15
#define HEADER_CONNECTOR_CN1_D37      PC2
#define HEADER_CONNECTOR_CN1_D38      PD4
#define HEADER_CONNECTOR_CN1_D39      PC3
#define HEADER_CONNECTOR_CN1_D40      PD3
#define HEADER_CONNECTOR_CN1_D41      PC4
#define HEADER_CONNECTOR_CN1_D42      PD2
#define HEADER_CONNECTOR_CN1_D43      // Pin not routed
#define HEADER_CONNECTOR_CN1_D44      PD1
#define HEADER_CONNECTOR_CN1_D45      PG6
#define HEADER_CONNECTOR_CN1_D46      PD0
#define HEADER_CONNECTOR_CN1_D47      PG7
#define HEADER_CONNECTOR_CN1_D48      PD12
#define HEADER_CONNECTOR_CN1_D49      // Pin not routed
#define HEADER_CONNECTOR_CN1_D50      // Pin not routed
#define HEADER_CONNECTOR_CN1_D51      // Pin not routed
#define HEADER_CONNECTOR_CN1_D52      PD10
#define HEADER_CONNECTOR_CN1_D53      // Pin not routed
#define HEADER_CONNECTOR_CN1_D54      PD9
#define HEADER_CONNECTOR_CN1_D55      // Pin not routed
#define HEADER_CONNECTOR_CN1_D56      // Pin not routed
#define HEADER_CONNECTOR_CN1_D57      // Pin not routed
#define HEADER_CONNECTOR_CN1_D58      // Pin not routed
#define HEADER_CONNECTOR_CN1_D59      // Pin not routed
#define HEADER_CONNECTOR_CN1_D60      // Pin not routed
#define HEADER_CONNECTOR_CN1_D61      // Pin not routed
#define HEADER_CONNECTOR_CN1_D62      PB5
#define HEADER_CONNECTOR_CN1_D63      PB5
#define HEADER_CONNECTOR_CN1_D64      PB4
#define HEADER_CONNECTOR_CN1_D65      PB4
#define HEADER_CONNECTOR_CN1_D66      PB3
#define HEADER_CONNECTOR_CN1_D67      PB3
#define HEADER_CONNECTOR_CN1_D68      PB2
#define HEADER_CONNECTOR_CN1_D69      PB2
#define HEADER_CONNECTOR_CN1_D70      PB1
#define HEADER_CONNECTOR_CN1_D71      PB8
#define HEADER_CONNECTOR_CN1_D72      PB0
#define HEADER_CONNECTOR_CN1_D73      PB9
#define HEADER_CONNECTOR_CN1_D74      PA3
#define HEADER_CONNECTOR_CN1_D76      PA2
#define HEADER_CONNECTOR_CN1_D77      // Pin not routed
#define HEADER_CONNECTOR_CN1_D78      // Pin not routed
#define HEADER_CONNECTOR_CN1_D79      // Pin not routed
#define HEADER_CONNECTOR_CN1_D80      // Pin not routed
#define HEADER_CONNECTOR_CN1_D81      // Pin not routed
#define HEADER_CONNECTOR_CN1_D82      // Pin not routed
#define HEADER_CONNECTOR_CN1_D83      // Pin not routed
#define HEADER_CONNECTOR_CN1_D84      PA14
#define HEADER_CONNECTOR_CN1_D85      // Pin not routed
#define HEADER_CONNECTOR_CN1_D86      // Pin not routed
#define HEADER_CONNECTOR_CN1_D87      PD0
#define HEADER_CONNECTOR_CN1_D88      PF2
#define HEADER_CONNECTOR_CN1_D89      // Pin not routed
#define HEADER_CONNECTOR_CN1_D90      PF8
#define HEADER_CONNECTOR_CN1_D91      PD10
#define HEADER_CONNECTOR_CN1_D92      // Pin not routed
#define HEADER_CONNECTOR_CN1_D93      PC4
#define HEADER_CONNECTOR_CN1_D95      PD0
#define HEADER_CONNECTOR_CN1_D96      // Pin not routed
#define HEADER_CONNECTOR_CN1_D97      PB2
#define HEADER_CONNECTOR_CN1_D98      // Pin not routed
#define HEADER_CONNECTOR_CN1_D99      // Pin not routed
#define HEADER_CONNECTOR_CN1_D100     // Pin not routed
#define HEADER_CONNECTOR_CN1_D101     PB10
#define HEADER_CONNECTOR_CN1_D102     PB10
#define HEADER_CONNECTOR_CN1_D103     PB11
#define HEADER_CONNECTOR_CN1_D104     // Pin not routed
#define HEADER_CONNECTOR_CN1_D105     PB12
#define HEADER_CONNECTOR_CN1_D106     PF13
#define HEADER_CONNECTOR_CN1_D107     PB13
#define HEADER_CONNECTOR_CN1_D108     PF12
#define HEADER_CONNECTOR_CN1_D109     PF4
#define HEADER_CONNECTOR_CN1_D110     PF4
#define HEADER_CONNECTOR_CN1_D111     PF5
#define HEADER_CONNECTOR_CN1_D112     PF5
#define HEADER_CONNECTOR_CN1_D113     PA9
#define HEADER_CONNECTOR_CN1_D114     PA9
#define HEADER_CONNECTOR_CN1_D115     PA10
#define HEADER_CONNECTOR_CN1_D116     PA10
#define HEADER_CONNECTOR_CN1_D117     PG6
#define HEADER_CONNECTOR_CN1_D118     PA5
#define HEADER_CONNECTOR_CN1_D119     PG7
#define HEADER_CONNECTOR_CN1_D120     PA4
#define HEADER_CONNECTOR_CN1_D121     // Pin not routed
#define HEADER_CONNECTOR_CN1_D122     // Pin not routed
#define HEADER_CONNECTOR_CN1_D123     // Pin not routed
#define HEADER_CONNECTOR_CN1_D124     PA1
#define HEADER_CONNECTOR_CN1_D125     // Pin not routed
#define HEADER_CONNECTOR_CN1_D126     PA0
#define HEADER_CONNECTOR_CN1_D127     PB14
#define HEADER_CONNECTOR_CN1_D128     PB6
#define HEADER_CONNECTOR_CN1_D129     PB15
#define HEADER_CONNECTOR_CN1_D130     // Pin not routed
#define HEADER_CONNECTOR_CN1_D131     PB7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
