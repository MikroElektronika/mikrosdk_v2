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

// Hardware revision number
#define MCU_CARD_REV_MAJOR (2)
#define MCU_CARD_REV_MINOR (0)

#include "hal_target.h"
#include "shield.h"

// Left connector
#define LEFT_CN_PIN_001 GPIO_PC7
#define LEFT_CN_PIN_002 GPIO_PD4
#define LEFT_CN_PIN_003 GPIO_PD5
#define LEFT_CN_PIN_004 GPIO_PD6
#define LEFT_CN_PIN_005 GPIO_PD7
#define LEFT_CN_PIN_008 GPIO_PB0
#define LEFT_CN_PIN_009 GPIO_PB1
#define LEFT_CN_PIN_010 GPIO_PB2

// Down connector
#define DOWN_CN_PIN_011 GPIO_PB3
#define DOWN_CN_PIN_012 GPIO_PB4
#define DOWN_CN_PIN_013 GPIO_PB5
#define DOWN_CN_PIN_014 GPIO_PB6 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_015 GPIO_PB7 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_016 GPIO_PE3 // Pin not routed to mikroBUS
#define DOWN_CN_PIN_017 GPIO_PA0
#define DOWN_CN_PIN_018 GPIO_PA1
#define DOWN_CN_PIN_019 GPIO_PA2
#define DOWN_CN_PIN_020 GPIO_PA3

// Right connector
#define RIGHT_CN_PIN_021 GPIO_PA4
#define RIGHT_CN_PIN_022 GPIO_PA5
#define RIGHT_CN_PIN_023 GPIO_PE0 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_024 GPIO_PE1 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_025 GPIO_PE2 // Pin not routed to mikroBUS
#define RIGHT_CN_PIN_028 GPIO_PA7
#define RIGHT_CN_PIN_029 GPIO_PA6
#define RIGHT_CN_PIN_030 GPIO_PC0 // Pin not routed to mikroBUS

// Up connector
#define UP_CN_PIN_031 GPIO_PC1 // Pin not routed to mikroBUS
#define UP_CN_PIN_032 GPIO_PC2
#define UP_CN_PIN_033 GPIO_PC3
#define UP_CN_PIN_034 GPIO_PD0 // Pin not routed to mikroBUS
#define UP_CN_PIN_035 GPIO_PD1 // Pin not routed to mikroBUS
#define UP_CN_PIN_036 GPIO_PD2 // Pin not routed to mikroBUS
#define UP_CN_PIN_037 GPIO_PD3 // Pin not routed to mikroBUS
#define UP_CN_PIN_038 GPIO_PC4
#define UP_CN_PIN_039 GPIO_PC5
#define UP_CN_PIN_040 GPIO_PC6

// Header connector
#define HEADER_CONNECTOR_HC1_PIN7  UP_CN_PIN_032
#define HEADER_CONNECTOR_HC1_PIN8  UP_CN_PIN_033
#define HEADER_CONNECTOR_HC1_PIN9  LEFT_CN_PIN_010
#define HEADER_CONNECTOR_HC1_PIN10 LEFT_CN_PIN_009
#define HEADER_CONNECTOR_HC1_PIN11 UP_CN_PIN_038
#define HEADER_CONNECTOR_HC1_PIN12 UP_CN_PIN_039
#define HEADER_CONNECTOR_HC1_PIN13 UP_CN_PIN_040
#define HEADER_CONNECTOR_HC1_PIN14 LEFT_CN_PIN_002
#define HEADER_CONNECTOR_HC1_PIN16 LEFT_CN_PIN_008
#define HEADER_CONNECTOR_HC1_PIN17 DOWN_CN_PIN_011
#define HEADER_CONNECTOR_HC1_PIN18 DOWN_CN_PIN_012
#define HEADER_CONNECTOR_HC1_PIN19 LEFT_CN_PIN_001

#define HEADER_CONNECTOR_HC2_PIN7  RIGHT_CN_PIN_028
#define HEADER_CONNECTOR_HC2_PIN8  RIGHT_CN_PIN_029
#define HEADER_CONNECTOR_HC2_PIN9  RIGHT_CN_PIN_022
#define HEADER_CONNECTOR_HC2_PIN10 RIGHT_CN_PIN_021
#define HEADER_CONNECTOR_HC2_PIN11 DOWN_CN_PIN_020
#define HEADER_CONNECTOR_HC2_PIN12 DOWN_CN_PIN_019
#define HEADER_CONNECTOR_HC2_PIN13 DOWN_CN_PIN_018
#define HEADER_CONNECTOR_HC2_PIN14 DOWN_CN_PIN_017
#define HEADER_CONNECTOR_HC2_PIN16 LEFT_CN_PIN_005
#define HEADER_CONNECTOR_HC2_PIN17 LEFT_CN_PIN_004
#define HEADER_CONNECTOR_HC2_PIN18 LEFT_CN_PIN_003
#define HEADER_CONNECTOR_HC2_PIN19 DOWN_CN_PIN_013

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
