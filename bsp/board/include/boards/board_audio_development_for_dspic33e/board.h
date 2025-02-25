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

#define BOARD_NAME "Audio Development Board For dsPIC33E"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       PB2
#define HEADER_CONNECTOR_CN1_D2       PF12
#define HEADER_CONNECTOR_CN1_D4       PF13
#define HEADER_CONNECTOR_CN1_D6       PA2
#define HEADER_CONNECTOR_CN1_D8       PA3
#define HEADER_CONNECTOR_CN1_D9       // Pin not routed
#define HEADER_CONNECTOR_CN1_D10      // Pin not routed
#define HEADER_CONNECTOR_CN1_D11      PB0
#define HEADER_CONNECTOR_CN1_D13      PB3
#define HEADER_CONNECTOR_CN1_D14      PB4
#define HEADER_CONNECTOR_CN1_D17      PE9
#define HEADER_CONNECTOR_CN1_D18      PE8
#define HEADER_CONNECTOR_CN1_D19      PD14
#define HEADER_CONNECTOR_CN1_D20      PD15
#define HEADER_CONNECTOR_CN1_D21      // Pin not routed
#define HEADER_CONNECTOR_CN1_D22      // Pin not routed
#define HEADER_CONNECTOR_CN1_D25      // Pin not routed
#define HEADER_CONNECTOR_CN1_D26      // Pin not routed
#define HEADER_CONNECTOR_CN1_D27      PG2
#define HEADER_CONNECTOR_CN1_D29      PG3
#define HEADER_CONNECTOR_CN1_D41      // Pin not routed
#define HEADER_CONNECTOR_CN1_D42      // Pin not routed
#define HEADER_CONNECTOR_CN1_D47      // Pin not routed
#define HEADER_CONNECTOR_CN1_D48      // Pin not routed
#define HEADER_CONNECTOR_CN1_D53      // Pin not routed
#define HEADER_CONNECTOR_CN1_D54      // Pin not routed
#define HEADER_CONNECTOR_CN1_D57      // Pin not routed
#define HEADER_CONNECTOR_CN1_D58      // Pin not routed
#define HEADER_CONNECTOR_CN1_D65      // Pin not routed
#define HEADER_CONNECTOR_CN1_D107     // Pin not routed
#define HEADER_CONNECTOR_CN1_D108     // Pin not routed
#define HEADER_CONNECTOR_CN1_D119     // Pin not routed
#define HEADER_CONNECTOR_CN1_D120     // Pin not routed

// LCD
#define LCD_RST     PC1
#define LCD_DB0     PE0
#define LCD_DB1     PE1
#define LCD_DB2     PE2
#define LCD_DB3     PE3
#define LCD_DB4     PE4
#define LCD_DB5     PE5
#define LCD_DB6     PE6
#define LCD_DB7     PE7
#define LCD_RD      PD5
#define LCD_WR      PD4
#define LCD_D_C     PB15
#define LCD_CS      PD11

// LEDS
#define LED1        PD0
#define LED2        PC13
#define LED3        PC14

// BUTTONS
#define BUTTON1     PD3
#define BUTTON2     PD2
#define BUTTON3     PD1
#define BUTTON4     PD12

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END