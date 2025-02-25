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

#define BOARD_NAME "MPLAB STARTER KIT FOR PIC32MX1XX/2XX"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN1_D1       PB9
#define HEADER_CONNECTOR_CN1_D2       PC6
#define HEADER_CONNECTOR_CN1_D3       PC7
#define HEADER_CONNECTOR_CN1_D4       PC8
#define HEADER_CONNECTOR_CN1_D5       PC9
#define HEADER_CONNECTOR_CN1_D8       PB10
#define HEADER_CONNECTOR_CN1_D9       PB11
#define HEADER_CONNECTOR_CN1_D11      PB13
#define HEADER_CONNECTOR_CN1_D12      PA10
#define HEADER_CONNECTOR_CN1_D13      PA7
#define HEADER_CONNECTOR_CN1_D14      PB14
#define HEADER_CONNECTOR_CN1_D15      PB15
#define HEADER_CONNECTOR_CN1_D19      PA0
#define HEADER_CONNECTOR_CN1_D20      PA1
#define HEADER_CONNECTOR_CN1_D21      PB0
#define HEADER_CONNECTOR_CN1_D22      PB1
#define HEADER_CONNECTOR_CN1_D23      PB2
#define HEADER_CONNECTOR_CN1_D24      PB3
#define HEADER_CONNECTOR_CN1_D25      PC0
#define HEADER_CONNECTOR_CN1_D26      PC1
#define HEADER_CONNECTOR_CN1_D27      PC2
#define HEADER_CONNECTOR_CN1_D30      PA2
#define HEADER_CONNECTOR_CN1_D31      PA3
#define HEADER_CONNECTOR_CN1_D32      PA8
#define HEADER_CONNECTOR_CN1_D33      PB4
#define HEADER_CONNECTOR_CN1_D34      PA4
#define HEADER_CONNECTOR_CN1_D35      PA9
#define HEADER_CONNECTOR_CN1_D36      PC3
#define HEADER_CONNECTOR_CN1_D37      PC4
#define HEADER_CONNECTOR_CN1_D38      PC5
#define HEADER_CONNECTOR_CN1_D41      PB5
#define HEADER_CONNECTOR_CN1_D43      PB7
#define HEADER_CONNECTOR_CN1_D44      PB8

// LCD
#define LCD_RST     PC5
#define LCD_DB0     PD0
#define LCD_DB1     PD1
#define LCD_DB2     PD2
#define LCD_DB3     PD3
#define LCD_DB4     PD4
#define LCD_DB5     PD5
#define LCD_DB6     PD6
#define LCD_DB7     PD7
#define LCD_RD      PB3
#define LCD_WR      PB13
#define LCD_D_C     RB5

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
