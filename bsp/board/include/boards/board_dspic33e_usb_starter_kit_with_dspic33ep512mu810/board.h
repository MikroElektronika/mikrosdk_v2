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

#define BOARD_NAME "dsPIC33E USB Starter Kit With dsPIC33EP512MU810"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       GPIO_PG15
#define HEADER_CONNECTOR_CN1_D2       // Pin not routed
#define HEADER_CONNECTOR_CN1_D3       GPIO_PG14
#define HEADER_CONNECTOR_CN1_D4       GPIO_PA6
#define HEADER_CONNECTOR_CN1_D5       GPIO_PG12
#define HEADER_CONNECTOR_CN1_D6       GPIO_PA7
#define HEADER_CONNECTOR_CN1_D8       GPIO_PG13
#define HEADER_CONNECTOR_CN1_D9       GPIO_PE6
#define HEADER_CONNECTOR_CN1_D10      GPIO_PG10
#define HEADER_CONNECTOR_CN1_D11      // Pin not routed
#define HEADER_CONNECTOR_CN1_D12      // Pin not routed
#define HEADER_CONNECTOR_CN1_D13      GPIO_PE5
#define HEADER_CONNECTOR_CN1_D14      GPIO_PG1
#define HEADER_CONNECTOR_CN1_D17      GPIO_PE3
#define HEADER_CONNECTOR_CN1_D18      GPIO_PF0
#define HEADER_CONNECTOR_CN1_D19      GPIO_PE2
#define HEADER_CONNECTOR_CN1_D20      GPIO_PD12
#define HEADER_CONNECTOR_CN1_D21      GPIO_PE1
#define HEADER_CONNECTOR_CN1_D22      GPIO_PD13
#define HEADER_CONNECTOR_CN1_D23      GPIO_PE0
#define HEADER_CONNECTOR_CN1_D24      GPIO_PD6
#define HEADER_CONNECTOR_CN1_D25      GPIO_PD5
#define HEADER_CONNECTOR_CN1_D26      GPIO_PD7
#define HEADER_CONNECTOR_CN1_D27      GPIO_PD11
#define HEADER_CONNECTOR_CN1_D28      GPIO_PD4
#define HEADER_CONNECTOR_CN1_D29      GPIO_PD10
#define HEADER_CONNECTOR_CN1_D30      GPIO_PC13
#define HEADER_CONNECTOR_CN1_D31      GPIO_PC14
#define HEADER_CONNECTOR_CN1_D32      GPIO_PC14
#define HEADER_CONNECTOR_CN1_D33      // Pin not routed
#define HEADER_CONNECTOR_CN1_D34      // Pin not routed
#define HEADER_CONNECTOR_CN1_D35      GPIO_PC1
#define HEADER_CONNECTOR_CN1_D36      GPIO_PA0
#define HEADER_CONNECTOR_CN1_D37      GPIO_PC2
#define HEADER_CONNECTOR_CN1_D38      GPIO_PD4
#define HEADER_CONNECTOR_CN1_D39      GPIO_PC3
#define HEADER_CONNECTOR_CN1_D40      GPIO_PD3
#define HEADER_CONNECTOR_CN1_D41      GPIO_PC4
#define HEADER_CONNECTOR_CN1_D42      GPIO_PD2
#define HEADER_CONNECTOR_CN1_D43      // Pin not routed
#define HEADER_CONNECTOR_CN1_D44      GPIO_PD1
#define HEADER_CONNECTOR_CN1_D45      GPIO_PG6
#define HEADER_CONNECTOR_CN1_D46      GPIO_PD0
#define HEADER_CONNECTOR_CN1_D47      GPIO_PG7
#define HEADER_CONNECTOR_CN1_D48      GPIO_PD12
#define HEADER_CONNECTOR_CN1_D49      GPIO_PG8
#define HEADER_CONNECTOR_CN1_D50      GPIO_PD11
#define HEADER_CONNECTOR_CN1_D51      GPIO_PG9
#define HEADER_CONNECTOR_CN1_D52      GPIO_PD10
#define HEADER_CONNECTOR_CN1_D53      // Pin not routed
#define HEADER_CONNECTOR_CN1_D54      GPIO_PD9
#define HEADER_CONNECTOR_CN1_D55      // Pin not routed
#define HEADER_CONNECTOR_CN1_D56      // Pin not routed
#define HEADER_CONNECTOR_CN1_D57      // Pin not routed
#define HEADER_CONNECTOR_CN1_D58      GPIO_PD8
#define HEADER_CONNECTOR_CN1_D62      GPIO_PB5
#define HEADER_CONNECTOR_CN1_D63      GPIO_PB5
#define HEADER_CONNECTOR_CN1_D64      GPIO_PB4
#define HEADER_CONNECTOR_CN1_D65      GPIO_PB4
#define HEADER_CONNECTOR_CN1_D66      GPIO_PB3
#define HEADER_CONNECTOR_CN1_D67      GPIO_PB3
#define HEADER_CONNECTOR_CN1_D68      GPIO_PB2
#define HEADER_CONNECTOR_CN1_D69      GPIO_PB2
#define HEADER_CONNECTOR_CN1_D70      GPIO_PB1
#define HEADER_CONNECTOR_CN1_D71      GPIO_PB8
#define HEADER_CONNECTOR_CN1_D72      GPIO_PB0
#define HEADER_CONNECTOR_CN1_D73      GPIO_PB9
#define HEADER_CONNECTOR_CN1_D74      GPIO_PA3
#define HEADER_CONNECTOR_CN1_D75      // Pin not routed
#define HEADER_CONNECTOR_CN1_D76      GPIO_PA2
#define HEADER_CONNECTOR_CN1_D77      // Pin not routed
#define HEADER_CONNECTOR_CN1_D78      // Pin not routed
#define HEADER_CONNECTOR_CN1_D79      GPIO_PA15
#define HEADER_CONNECTOR_CN1_D80      // Pin not routed
#define HEADER_CONNECTOR_CN1_D81      GPIO_PA14
#define HEADER_CONNECTOR_CN1_D82      // Pin not routed
#define HEADER_CONNECTOR_CN1_D83      GPIO_PE9
#define HEADER_CONNECTOR_CN1_D84      GPIO_PA14
#define HEADER_CONNECTOR_CN1_D85      GPIO_PE8
#define HEADER_CONNECTOR_CN1_D86      GPIO_PA15
#define HEADER_CONNECTOR_CN1_D87      GPIO_PD0
#define HEADER_CONNECTOR_CN1_D88      GPIO_PF2
#define HEADER_CONNECTOR_CN1_D90      GPIO_PF8
#define HEADER_CONNECTOR_CN1_D91      GPIO_PD10
#define HEADER_CONNECTOR_CN1_D92      // Pin not routed
#define HEADER_CONNECTOR_CN1_D93      GPIO_PC4
#define HEADER_CONNECTOR_CN1_D94      GPIO_PD14
#define HEADER_CONNECTOR_CN1_D95      GPIO_PD0
#define HEADER_CONNECTOR_CN1_D96      // Pin not routed
#define HEADER_CONNECTOR_CN1_D97      GPIO_PB2
#define HEADER_CONNECTOR_CN1_D98      // Pin not routed
#define HEADER_CONNECTOR_CN1_D99      // Pin not routed
#define HEADER_CONNECTOR_CN1_D100     // Pin not routed
#define HEADER_CONNECTOR_CN1_D101     GPIO_PA13
#define HEADER_CONNECTOR_CN1_D102     GPIO_PA13
#define HEADER_CONNECTOR_CN1_D103     GPIO_PB11
#define HEADER_CONNECTOR_CN1_D105     GPIO_PB12
#define HEADER_CONNECTOR_CN1_D106     GPIO_PF13
#define HEADER_CONNECTOR_CN1_D107     GPIO_PB13
#define HEADER_CONNECTOR_CN1_D108     GPIO_PF12
#define HEADER_CONNECTOR_CN1_D109     GPIO_PF4
#define HEADER_CONNECTOR_CN1_D110     GPIO_PF4
#define HEADER_CONNECTOR_CN1_D111     GPIO_PF5
#define HEADER_CONNECTOR_CN1_D112     GPIO_PF5
#define HEADER_CONNECTOR_CN1_D113     GPIO_PA9
#define HEADER_CONNECTOR_CN1_D114     GPIO_PA9
#define HEADER_CONNECTOR_CN1_D115     GPIO_PA10
#define HEADER_CONNECTOR_CN1_D116     GPIO_PA10
#define HEADER_CONNECTOR_CN1_D117     GPIO_PG6
#define HEADER_CONNECTOR_CN1_D118     GPIO_PA5
#define HEADER_CONNECTOR_CN1_D119     GPIO_PG7
#define HEADER_CONNECTOR_CN1_D120     GPIO_PA4
#define HEADER_CONNECTOR_CN1_D121     // Pin not routed
#define HEADER_CONNECTOR_CN1_D122     // Pin not routed
#define HEADER_CONNECTOR_CN1_D123     GPIO_PG8
#define HEADER_CONNECTOR_CN1_D124     GPIO_PA1
#define HEADER_CONNECTOR_CN1_D125     GPIO_PG9
#define HEADER_CONNECTOR_CN1_D126     GPIO_PA0
#define HEADER_CONNECTOR_CN1_D127     GPIO_PB14
#define HEADER_CONNECTOR_CN1_D128     // Pin not routed
#define HEADER_CONNECTOR_CN1_D129     GPIO_PA0
#define HEADER_CONNECTOR_CN1_D130     // Pin not routed
#define HEADER_CONNECTOR_CN1_D131     // Pin not routed
#define HEADER_CONNECTOR_CN1_D132     // Pin not routed

// LEDS
#define LED1    GPIO_PD0
#define LED2    GPIO_PD1
#define LED3    GPIO_PD2

// BUTTONS
#define BUTTON1 GPIO_PD6
#define BUTTON2 GPIO_PD7
#define BUTTON3 GPIO_PD13

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END