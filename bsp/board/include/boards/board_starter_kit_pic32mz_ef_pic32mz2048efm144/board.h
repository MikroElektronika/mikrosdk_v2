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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.4/new_hw/2025-06-17.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "PIC32MZ EF STARTER KIT with PIC32MZ2048EFM144"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       PF12
#define HEADER_CONNECTOR_CN1_D2       PA1
#define HEADER_CONNECTOR_CN1_D3       PF13
#define HEADER_CONNECTOR_CN1_D4       PA0
#define HEADER_CONNECTOR_CN1_D5       PB0
#define HEADER_CONNECTOR_CN1_D6       PB7
#define HEADER_CONNECTOR_CN1_D7       PB1
#define HEADER_CONNECTOR_CN1_D8       PB6
#define HEADER_CONNECTOR_CN1_D9       // Pin not routed
#define HEADER_CONNECTOR_CN1_D10      // Pin not routed
#define HEADER_CONNECTOR_CN1_D11      // Pin not routed
#define HEADER_CONNECTOR_CN1_D12      // Pin not routed
#define HEADER_CONNECTOR_CN1_D13      // Pin not routed
#define HEADER_CONNECTOR_CN1_D14      PD0
#define HEADER_CONNECTOR_CN1_D15      PC13
#define HEADER_CONNECTOR_CN1_D16      PG13
#define HEADER_CONNECTOR_CN1_D17      PC14
#define HEADER_CONNECTOR_CN1_D18      PG12
#define HEADER_CONNECTOR_CN1_D19      PD4
#define HEADER_CONNECTOR_CN1_D20      PG14
#define HEADER_CONNECTOR_CN1_D21      PD5
#define HEADER_CONNECTOR_CN1_D22      PA7
#define HEADER_CONNECTOR_CN1_D23      PG15
#define HEADER_CONNECTOR_CN1_D24      PA6
#define HEADER_CONNECTOR_CN1_D25      PJ15
#define HEADER_CONNECTOR_CN1_D26      // Pin not routed
#define HEADER_CONNECTOR_CN1_D27      PK1
#define HEADER_CONNECTOR_CN1_D28      // Pin not routed
#define HEADER_CONNECTOR_CN1_D29      PG9
#define HEADER_CONNECTOR_CN1_D30      // Pin not routed
#define HEADER_CONNECTOR_CN1_D31      PK2
#define HEADER_CONNECTOR_CN1_D32      // Pin not routed
#define HEADER_CONNECTOR_CN1_D33      PH7
#define HEADER_CONNECTOR_CN1_D34      // Pin not routed
#define HEADER_CONNECTOR_CN1_D35      PA5
#define HEADER_CONNECTOR_CN1_D36      // Pin not routed
#define HEADER_CONNECTOR_CN1_D37      PC1
#define HEADER_CONNECTOR_CN1_D38      // Pin not routed
#define HEADER_CONNECTOR_CN1_D39      // Pin not routed
#define HEADER_CONNECTOR_CN1_D40      // Pin not routed
#define HEADER_CONNECTOR_CN1_D41      // Pin not routed
#define HEADER_CONNECTOR_CN1_D42      // Pin not routed
#define HEADER_CONNECTOR_CN1_D43      PB9
#define HEADER_CONNECTOR_CN1_D44      // Pin not routed
#define HEADER_CONNECTOR_CN1_D45      PF5
#define HEADER_CONNECTOR_CN1_D46      // Pin not routed
#define HEADER_CONNECTOR_CN1_D47      PF4
#define HEADER_CONNECTOR_CN1_D48      // Pin not routed
#define HEADER_CONNECTOR_CN1_D49      PB8
#define HEADER_CONNECTOR_CN1_D50      // Pin not routed
#define HEADER_CONNECTOR_CN1_D51      PB12
#define HEADER_CONNECTOR_CN1_D52      // Pin not routed
#define HEADER_CONNECTOR_CN1_D53      PC2
#define HEADER_CONNECTOR_CN1_D54      // Pin not routed
#define HEADER_CONNECTOR_CN1_D55      PJ13
#define HEADER_CONNECTOR_CN1_D56      // Pin not routed
#define HEADER_CONNECTOR_CN1_D57      PA4
#define HEADER_CONNECTOR_CN1_D58      // Pin not routed
#define HEADER_CONNECTOR_CN1_D59      PD9
#define HEADER_CONNECTOR_CN1_D60      // Pin not routed
#define HEADER_CONNECTOR_CN1_D61      PK0
#define HEADER_CONNECTOR_CN1_D62      PH2
#define HEADER_CONNECTOR_CN1_D63      PK3
#define HEADER_CONNECTOR_CN1_D64      PH3
#define HEADER_CONNECTOR_CN1_D65      PK4
#define HEADER_CONNECTOR_CN1_D66      // Pin not routed
#define HEADER_CONNECTOR_CN1_D67      PK5
#define HEADER_CONNECTOR_CN1_D68      PC3
#define HEADER_CONNECTOR_CN1_D69      // Pin not routed
#define HEADER_CONNECTOR_CN1_D70      // Pin not routed
#define HEADER_CONNECTOR_CN1_D71      // Pin not routed
#define HEADER_CONNECTOR_CN1_D72      // Pin not routed
#define HEADER_CONNECTOR_CN1_D73      PK6
#define HEADER_CONNECTOR_CN1_D74      PJ4
#define HEADER_CONNECTOR_CN1_D75      PK7
#define HEADER_CONNECTOR_CN1_D76      PJ5
#define HEADER_CONNECTOR_CN1_D77      PJ3
#define HEADER_CONNECTOR_CN1_D78      PJ6
#define HEADER_CONNECTOR_CN1_D79      PH15
#define HEADER_CONNECTOR_CN1_D80      PJ7
#define HEADER_CONNECTOR_CN1_D81      PJ12
#define HEADER_CONNECTOR_CN1_D82      PA3
#define HEADER_CONNECTOR_CN1_D83      PJ10
#define HEADER_CONNECTOR_CN1_D84      PH11
#define HEADER_CONNECTOR_CN1_D85      PH14
#define HEADER_CONNECTOR_CN1_D86      PJ2
#define HEADER_CONNECTOR_CN1_D87      PG6
#define HEADER_CONNECTOR_CN1_D88      PB14
#define HEADER_CONNECTOR_CN1_D89      PG7
#define HEADER_CONNECTOR_CN1_D90      PB15
#define HEADER_CONNECTOR_CN1_D91      PG8
#define HEADER_CONNECTOR_CN1_D92      PH6
#define HEADER_CONNECTOR_CN1_D93      PE8
#define HEADER_CONNECTOR_CN1_D94      PD14
#define HEADER_CONNECTOR_CN1_D95      PE9
#define HEADER_CONNECTOR_CN1_D96      PD15
#define HEADER_CONNECTOR_CN1_D97      // Pin not routed
#define HEADER_CONNECTOR_CN1_D98      // Pin not routed
#define HEADER_CONNECTOR_CN1_D99      // Pin not routed
#define HEADER_CONNECTOR_CN1_D100     // Pin not routed
#define HEADER_CONNECTOR_CN1_D101     PB5
#define HEADER_CONNECTOR_CN1_D102     PF3
#define HEADER_CONNECTOR_CN1_D103     PB4
#define HEADER_CONNECTOR_CN1_D104     PF2
#define HEADER_CONNECTOR_CN1_D105     PB3
#define HEADER_CONNECTOR_CN1_D106     PF8
#define HEADER_CONNECTOR_CN1_D107     PB2
#define HEADER_CONNECTOR_CN1_D108     PH9
#define HEADER_CONNECTOR_CN1_D109     PA9
#define HEADER_CONNECTOR_CN1_D110     PH10
#define HEADER_CONNECTOR_CN1_D111     PA10
#define HEADER_CONNECTOR_CN1_D112     PA2
#define HEADER_CONNECTOR_CN1_D113     PH0
#define HEADER_CONNECTOR_CN1_D114     PD10
#define HEADER_CONNECTOR_CN1_D115     PH1
#define HEADER_CONNECTOR_CN1_D116     PH12
#define HEADER_CONNECTOR_CN1_D117     PB10
#define HEADER_CONNECTOR_CN1_D118     PD1
#define HEADER_CONNECTOR_CN1_D119     PB11
#define HEADER_CONNECTOR_CN1_D120     PJ0
#define HEADER_CONNECTOR_CN1_D121     PB12
#define HEADER_CONNECTOR_CN1_D122     PD7
#define HEADER_CONNECTOR_CN1_D123     PB13
#define HEADER_CONNECTOR_CN1_D124     PA14
#define HEADER_CONNECTOR_CN1_D125     // Pin not routed
#define HEADER_CONNECTOR_CN1_D126     PA15
#define HEADER_CONNECTOR_CN1_D127     // Pin not routed
#define HEADER_CONNECTOR_CN1_D128     // Pin not routed
#define HEADER_CONNECTOR_CN1_D129     // Pin not routed
#define HEADER_CONNECTOR_CN1_D130     // Pin not routed
#define HEADER_CONNECTOR_CN1_D131     PD3
#define HEADER_CONNECTOR_CN1_D132     PE4
#define HEADER_CONNECTOR_CN1_D133     PD3
#define HEADER_CONNECTOR_CN1_D134     PE3
#define HEADER_CONNECTOR_CN1_D135     PD3
#define HEADER_CONNECTOR_CN1_D136     PE2
#define HEADER_CONNECTOR_CN1_D137     PF0
#define HEADER_CONNECTOR_CN1_D138     PE1
#define HEADER_CONNECTOR_CN1_D139     PD12
#define HEADER_CONNECTOR_CN1_D140     PE0
#define HEADER_CONNECTOR_CN1_D141     PD13
#define HEADER_CONNECTOR_CN1_D142     PE4
#define HEADER_CONNECTOR_CN1_D143     PD2
#define HEADER_CONNECTOR_CN1_D144     PE4
#define HEADER_CONNECTOR_CN1_D145     PD3
#define HEADER_CONNECTOR_CN1_D146     PE4
#define HEADER_CONNECTOR_CN1_D147     PF1
#define HEADER_CONNECTOR_CN1_D148     PF1
#define HEADER_CONNECTOR_CN1_D149     PF1
#define HEADER_CONNECTOR_CN1_D150     PG1
#define HEADER_CONNECTOR_CN1_D151     PE5
#define HEADER_CONNECTOR_CN1_D152     PG0
#define HEADER_CONNECTOR_CN1_D153     PE6
#define HEADER_CONNECTOR_CN1_D154     PE7
#define HEADER_CONNECTOR_CN1_D155     PC4
#define HEADER_CONNECTOR_CN1_D156     // Pin not routed
#define HEADER_CONNECTOR_CN1_D157     // Pin not routed
#define HEADER_CONNECTOR_CN1_D158     // Pin not routed
#define HEADER_CONNECTOR_CN1_D159     // Pin not routed
#define HEADER_CONNECTOR_CN1_D160     // Pin not routed
#define HEADER_CONNECTOR_CN1_D161     // Pin not routed
#define HEADER_CONNECTOR_CN1_D162     // Pin not routed
#define HEADER_CONNECTOR_CN1_D163     PB14
#define HEADER_CONNECTOR_CN1_D165     PB5
#define HEADER_CONNECTOR_CN1_D166     PG8
#define HEADER_CONNECTOR_CN1_D167     PG6
#define HEADER_CONNECTOR_CN1_D168     PD7

#define HEADER_CONNECTOR_CN2_D1       // Pin not routed
#define HEADER_CONNECTOR_CN2_D2       // Pin not routed
#define HEADER_CONNECTOR_CN2_D3       PA3
#define HEADER_CONNECTOR_CN2_D4       // Pin not routed
#define HEADER_CONNECTOR_CN2_D5       PA2
#define HEADER_CONNECTOR_CN2_D6       // Pin not routed
#define HEADER_CONNECTOR_CN2_D7       PA14
#define HEADER_CONNECTOR_CN2_D8       PG6
#define HEADER_CONNECTOR_CN2_D9       // Pin not routed
#define HEADER_CONNECTOR_CN2_D10      PB14
#define HEADER_CONNECTOR_CN2_D11      PD0
#define HEADER_CONNECTOR_CN2_D12      PF2
#define HEADER_CONNECTOR_CN2_D13      PJ13
#define HEADER_CONNECTOR_CN2_D14      // Pin not routed
#define HEADER_CONNECTOR_CN2_D15      PB3
#define HEADER_CONNECTOR_CN2_D16      PK1
#define HEADER_CONNECTOR_CN2_D17      // Pin not routed
#define HEADER_CONNECTOR_CN2_D18      PK2
#define HEADER_CONNECTOR_CN2_D19      PF5
#define HEADER_CONNECTOR_CN2_D20      // Pin not routed
#define HEADER_CONNECTOR_CN2_D21      PF4
#define HEADER_CONNECTOR_CN2_D22      PK3
#define HEADER_CONNECTOR_CN2_D23      PD1
#define HEADER_CONNECTOR_CN2_D24      PJ5
#define HEADER_CONNECTOR_CN2_D25      // Pin not routed
#define HEADER_CONNECTOR_CN2_D26      PJ7
#define HEADER_CONNECTOR_CN2_D27      // Pin not routed
#define HEADER_CONNECTOR_CN2_D28      // Pin not routed
#define HEADER_CONNECTOR_CN2_D29      PH7
#define HEADER_CONNECTOR_CN2_D30      // Pin not routed
#define HEADER_CONNECTOR_CN2_D31      PH9
#define HEADER_CONNECTOR_CN2_D32      PH11
#define HEADER_CONNECTOR_CN2_D33      PK4
#define HEADER_CONNECTOR_CN2_D34      // Pin not routed
#define HEADER_CONNECTOR_CN2_D35      PK5
#define HEADER_CONNECTOR_CN2_D36      PK6
#define HEADER_CONNECTOR_CN2_D37      PD10
#define HEADER_CONNECTOR_CN2_D38      PH15
#define HEADER_CONNECTOR_CN2_D39      // Pin not routed
#define HEADER_CONNECTOR_CN2_D40      PJ3

// LEDS
#define LED1    PH0
#define LED2    PH1
#define LED3    PH2

// BUTTONS
#define BUTTON1 PB12
#define BUTTON2 PB13
#define BUTTON3 PB14

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
