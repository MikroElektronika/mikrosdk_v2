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

#define BOARD_NAME "Graphics PIC24FJ256DA210 Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       GPIO_PG8
#define HEADER_CONNECTOR_CN1_D2       GPIO_PD0
#define HEADER_CONNECTOR_CN1_D3       GPIO_PD8
#define HEADER_CONNECTOR_CN1_D4       GPIO_PF3
#define HEADER_CONNECTOR_CN1_D5       GPIO_PB0
#define HEADER_CONNECTOR_CN1_D6       // Pin not routed
#define HEADER_CONNECTOR_CN1_D7       GPIO_PB1
#define HEADER_CONNECTOR_CN1_D8       // Pin not routed
#define HEADER_CONNECTOR_CN1_D9       // Pin not routed
#define HEADER_CONNECTOR_CN1_D10      // Pin not routed
#define HEADER_CONNECTOR_CN1_D11      // Pin not routed
#define HEADER_CONNECTOR_CN1_D12      GPIO_PG6
#define HEADER_CONNECTOR_CN1_D13      GPIO_PB5
#define HEADER_CONNECTOR_CN1_D14      // Pin not routed
#define HEADER_CONNECTOR_CN1_D15      // Pin not routed
#define HEADER_CONNECTOR_CN1_D16      // Pin not routed
#define HEADER_CONNECTOR_CN1_D17      GPIO_PA15
#define HEADER_CONNECTOR_CN1_D18      GPIO_PE8
#define HEADER_CONNECTOR_CN1_D19      GPIO_PG6
#define HEADER_CONNECTOR_CN1_D20      GPIO_PC13
#define HEADER_CONNECTOR_CN1_D21      // Pin not routed
#define HEADER_CONNECTOR_CN1_D22      // Pin not routed
#define HEADER_CONNECTOR_CN1_D23      // Pin not routed
#define HEADER_CONNECTOR_CN1_D24      // Pin not routed
#define HEADER_CONNECTOR_CN1_D25      // Pin not routed
#define HEADER_CONNECTOR_CN1_D26      // Pin not routed
#define HEADER_CONNECTOR_CN1_D27      GPIO_PG0
#define HEADER_CONNECTOR_CN1_D28      GPIO_PF0
#define HEADER_CONNECTOR_CN1_D29      GPIO_PG1
#define HEADER_CONNECTOR_CN1_D30      GPIO_PF1
#define HEADER_CONNECTOR_CN1_D31      // Pin not routed
#define HEADER_CONNECTOR_CN1_D32      // Pin not routed
#define HEADER_CONNECTOR_CN1_D33      GPIO_PG9
#define HEADER_CONNECTOR_CN1_D34      GPIO_PF4
#define HEADER_CONNECTOR_CN1_D35      GPIO_PF12
#define HEADER_CONNECTOR_CN1_D36      GPIO_PF5
#define HEADER_CONNECTOR_CN1_D37      GPIO_PA3
#define HEADER_CONNECTOR_CN1_D38      // Pin not routed
#define HEADER_CONNECTOR_CN1_D39      GPIO_PA4
#define HEADER_CONNECTOR_CN1_D40      // Pin not routed
#define HEADER_CONNECTOR_CN1_D41      // Pin not routed
#define HEADER_CONNECTOR_CN1_D42      // Pin not routed
#define HEADER_CONNECTOR_CN1_D43      // Pin not routed
#define HEADER_CONNECTOR_CN1_D44      // Pin not routed
#define HEADER_CONNECTOR_CN1_D45      GPIO_PA9
#define HEADER_CONNECTOR_CN1_D46      GPIO_PA10
#define HEADER_CONNECTOR_CN1_D47      // Pin not routed
#define HEADER_CONNECTOR_CN1_D48      // Pin not routed
#define HEADER_CONNECTOR_CN1_D49      GPIO_PA15
#define HEADER_CONNECTOR_CN1_D50      GPIO_PA14
#define HEADER_CONNECTOR_CN1_D51      GPIO_PG6
#define HEADER_CONNECTOR_CN1_D52      // Pin not routed
#define HEADER_CONNECTOR_CN1_D53      // Pin not routed
#define HEADER_CONNECTOR_CN1_D54      // Pin not routed
#define HEADER_CONNECTOR_CN1_D55      // Pin not routed
#define HEADER_CONNECTOR_CN1_D56      // Pin not routed
#define HEADER_CONNECTOR_CN1_D57      // Pin not routed
#define HEADER_CONNECTOR_CN1_D58      // Pin not routed
#define HEADER_CONNECTOR_CN1_D59      // Pin not routed
#define HEADER_CONNECTOR_CN1_D60      // Pin not routed
#define HEADER_CONNECTOR_CN1_D61      // Pin not routed
#define HEADER_CONNECTOR_CN1_D62      // Pin not routed
#define HEADER_CONNECTOR_CN1_D63      // Pin not routed
#define HEADER_CONNECTOR_CN1_D64      // Pin not routed
#define HEADER_CONNECTOR_CN1_D65      // Pin not routed
#define HEADER_CONNECTOR_CN1_D66      // Pin not routed
#define HEADER_CONNECTOR_CN1_D67      // Pin not routed
#define HEADER_CONNECTOR_CN1_D68      GPIO_PG14
#define HEADER_CONNECTOR_CN1_D69      // Pin not routed
#define HEADER_CONNECTOR_CN1_D70      // Pin not routed
#define HEADER_CONNECTOR_CN1_D71      // Pin not routed
#define HEADER_CONNECTOR_CN1_D72      GPIO_PG8
#define HEADER_CONNECTOR_CN1_D73      // Pin not routed
#define HEADER_CONNECTOR_CN1_D74      GPIO_PA7
#define HEADER_CONNECTOR_CN1_D75      // Pin not routed
#define HEADER_CONNECTOR_CN1_D76      // Pin not routed
#define HEADER_CONNECTOR_CN1_D77      // Pin not routed
#define HEADER_CONNECTOR_CN1_D78      // Pin not routed
#define HEADER_CONNECTOR_CN1_D79      GPIO_PB10
#define HEADER_CONNECTOR_CN1_D80      GPIO_PB11
#define HEADER_CONNECTOR_CN1_D81      GPIO_PB12
#define HEADER_CONNECTOR_CN1_D82      GPIO_PB13
#define HEADER_CONNECTOR_CN1_D83      GPIO_PB14
#define HEADER_CONNECTOR_CN1_D84      GPIO_PB15
#define HEADER_CONNECTOR_CN1_D85      GPIO_PE9
#define HEADER_CONNECTOR_CN1_D86      // Pin not routed
#define HEADER_CONNECTOR_CN1_D87      // Pin not routed
#define HEADER_CONNECTOR_CN1_D88      // Pin not routed
#define HEADER_CONNECTOR_CN1_D89      // Pin not routed
#define HEADER_CONNECTOR_CN1_D90      // Pin not routed
#define HEADER_CONNECTOR_CN1_D91      // Pin not routed
#define HEADER_CONNECTOR_CN1_D92      // Pin not routed
#define HEADER_CONNECTOR_CN1_D93      GPIO_PA15
#define HEADER_CONNECTOR_CN1_D94      // Pin not routed
#define HEADER_CONNECTOR_CN1_D95      // Pin not routed
#define HEADER_CONNECTOR_CN1_D96      GPIO_PD3
#define HEADER_CONNECTOR_CN1_D97      GPIO_PD4
#define HEADER_CONNECTOR_CN1_D98      GPIO_PD5
#define HEADER_CONNECTOR_CN1_D99      GPIO_PD6
#define HEADER_CONNECTOR_CN1_D100     GPIO_PD7
#define HEADER_CONNECTOR_CN1_D101     GPIO_PC13
#define HEADER_CONNECTOR_CN1_D102     // Pin not routed
#define HEADER_CONNECTOR_CN1_D103     GPIO_PD10
#define HEADER_CONNECTOR_CN1_D104     GPIO_PD11
#define HEADER_CONNECTOR_CN1_D105     GPIO_PD12
#define HEADER_CONNECTOR_CN1_D106     GPIO_PD13
#define HEADER_CONNECTOR_CN1_D107     // Pin not routed
#define HEADER_CONNECTOR_CN1_D108     // Pin not routed
#define HEADER_CONNECTOR_CN1_D109     GPIO_PE0
#define HEADER_CONNECTOR_CN1_D110     GPIO_PE1
#define HEADER_CONNECTOR_CN1_D111     GPIO_PE2
#define HEADER_CONNECTOR_CN1_D112     GPIO_PE3
#define HEADER_CONNECTOR_CN1_D113     GPIO_PE4
#define HEADER_CONNECTOR_CN1_D114     GPIO_PE5
#define HEADER_CONNECTOR_CN1_D115     GPIO_PE6
#define HEADER_CONNECTOR_CN1_D116     GPIO_PE7
#define HEADER_CONNECTOR_CN1_D117     // Pin not routed
#define HEADER_CONNECTOR_CN1_D118     // Pin not routed
#define HEADER_CONNECTOR_CN1_D119     // Pin not routed
#define HEADER_CONNECTOR_CN1_D120     // Pin not routed

// Display connector
#define DISPLAY_CONNECTOR_DC1_D1      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B1      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A2      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B2      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A3      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B3      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A4      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B4      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A5      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B5      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A6      GPIO_PA2
#define DISPLAY_CONNECTOR_DC1_B6      GPIO_PA1
#define DISPLAY_CONNECTOR_DC1_A7      GPIO_PC4
#define DISPLAY_CONNECTOR_DC1_B7      GPIO_PG7
#define DISPLAY_CONNECTOR_DC1_A8      GPIO_PC4
#define DISPLAY_CONNECTOR_DC1_B8      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A9      GPIO_PD8
#define DISPLAY_CONNECTOR_DC1_B9      GPIO_PB1
#define DISPLAY_CONNECTOR_DC1_A10     GPIO_PB0
#define DISPLAY_CONNECTOR_DC1_B10     GPIO_PA1
#define DISPLAY_CONNECTOR_DC1_A11     GPIO_PD0
#define DISPLAY_CONNECTOR_DC1_B11     GPIO_PD0
#define DISPLAY_CONNECTOR_DC1_A12     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B12     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A13     GPIO_PG15
#define DISPLAY_CONNECTOR_DC1_B13     GPIO_PA6
#define DISPLAY_CONNECTOR_DC1_A14     GPIO_PG12
#define DISPLAY_CONNECTOR_DC1_B14     GPIO_PG13
#define DISPLAY_CONNECTOR_DC1_A15     GPIO_PD15
#define DISPLAY_CONNECTOR_DC1_B15     GPIO_PD14
#define DISPLAY_CONNECTOR_DC1_A16     GPIO_PB9
#define DISPLAY_CONNECTOR_DC1_B16     GPIO_PD9
#define DISPLAY_CONNECTOR_DC1_A17     GPIO_PF8
#define DISPLAY_CONNECTOR_DC1_B17     GPIO_PC2
#define DISPLAY_CONNECTOR_DC1_A18     GPIO_PB4
#define DISPLAY_CONNECTOR_DC1_B18     GPIO_PF2
#define DISPLAY_CONNECTOR_DC1_A19     GPIO_PF13
#define DISPLAY_CONNECTOR_DC1_B19     GPIO_PB8
#define DISPLAY_CONNECTOR_DC1_A20     GPIO_PD2
#define DISPLAY_CONNECTOR_DC1_B20     GPIO_PD15
#define DISPLAY_CONNECTOR_DC1_A21     GPIO_PD1
#define DISPLAY_CONNECTOR_DC1_B21     GPIO_PB2
#define DISPLAY_CONNECTOR_DC1_A22     GPIO_PB3
#define DISPLAY_CONNECTOR_DC1_B22     GPIO_PC3
#define DISPLAY_CONNECTOR_DC1_A23     GPIO_PC1
#define DISPLAY_CONNECTOR_DC1_B23     GPIO_PB4
#define DISPLAY_CONNECTOR_DC1_A24     GPIO_PD15
#define DISPLAY_CONNECTOR_DC1_B24     GPIO_PD15
#define DISPLAY_CONNECTOR_DC1_A25     GPIO_PD9
#define DISPLAY_CONNECTOR_DC1_B25     GPIO_PD9
#define DISPLAY_CONNECTOR_DC1_A26     GPIO_PB4
#define DISPLAY_CONNECTOR_DC1_B26     GPIO_PB4
#define DISPLAY_CONNECTOR_DC1_A27     GPIO_PA5
#define DISPLAY_CONNECTOR_DC1_B27     GPIO_PA0
#define DISPLAY_CONNECTOR_DC1_A28     GPIO_PD8
#define DISPLAY_CONNECTOR_DC1_B28     GPIO_PB1
#define DISPLAY_CONNECTOR_DC1_A29     GPIO_PB0
#define DISPLAY_CONNECTOR_DC1_B29     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A30     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B30     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A31     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B31     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_A32     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_B32     // Pin not routed

// LEDS
#define LED1    GPIO_PG8
#define LED2    GPIO_PE9
#define LED3    GPIO_PB5
#define LED4    GPIO_PA7

// BUTTONS
#define BUTTON1  GPIO_PG8
#define BUTTON2  GPIO_PE9
#define BUTTON3  GPIO_PB5

// TOUCH PADS
#define TOUCH_PAD1  GPIO_PG8
#define TOUCH_PAD2  GPIO_PE9
#define TOUCH_PAD3  GPIO_PB5

// POTENTIOMETER
#define POT1       GPIO_PB5

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END