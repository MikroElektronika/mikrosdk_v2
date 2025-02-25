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

#define BOARD_NAME "dsPICDEM 80-Pin Starter Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_P2_1   GPIO_PG15
#define HEADER_CONNECTOR_P2_2   GPIO_PC1
#define HEADER_CONNECTOR_P2_3   GPIO_PC2
#define HEADER_CONNECTOR_P2_4   GPIO_PC3
#define HEADER_CONNECTOR_P2_5   GPIO_PC4
#define HEADER_CONNECTOR_P2_6   GPIO_PC6
#define HEADER_CONNECTOR_P2_7   GPIO_PG7
#define HEADER_CONNECTOR_P2_8   GPIO_PG8
#define HEADER_CONNECTOR_P2_9   // Pin not routed
#define HEADER_CONNECTOR_P2_10  GPIO_PG9
#define HEADER_CONNECTOR_P2_11  // Pin not routed
#define HEADER_CONNECTOR_P2_12  // Pin not routed
#define HEADER_CONNECTOR_P2_13  GPIO_PA12
#define HEADER_CONNECTOR_P2_14  GPIO_PA13
#define HEADER_CONNECTOR_P2_15  GPIO_PB5
#define HEADER_CONNECTOR_P2_16  GPIO_PB4
#define HEADER_CONNECTOR_P2_17  GPIO_PB3
#define HEADER_CONNECTOR_P2_18  GPIO_PB2
#define HEADER_CONNECTOR_P2_19  GPIO_PB1
#define HEADER_CONNECTOR_P2_20  GPIO_PB0
#define HEADER_CONNECTOR_P2_21  GPIO_PB6
#define HEADER_CONNECTOR_P2_22  GPIO_PB7
#define HEADER_CONNECTOR_P2_23  GPIO_PA9
#define HEADER_CONNECTOR_P2_24  GPIO_PA10
#define HEADER_CONNECTOR_P2_25  // Pin not routed
#define HEADER_CONNECTOR_P2_26  // Pin not routed
#define HEADER_CONNECTOR_P2_27  GPIO_PB8
#define HEADER_CONNECTOR_P2_28  GPIO_PB9
#define HEADER_CONNECTOR_P2_29  GPIO_PB10
#define HEADER_CONNECTOR_P2_30  GPIO_PB11
#define HEADER_CONNECTOR_P2_31  // Pin not routed
#define HEADER_CONNECTOR_P2_32  // Pin not routed
#define HEADER_CONNECTOR_P2_33  GPIO_PB12
#define HEADER_CONNECTOR_P2_34  GPIO_PB13
#define HEADER_CONNECTOR_P2_35  GPIO_PB14
#define HEADER_CONNECTOR_P2_36  GPIO_PB15
#define HEADER_CONNECTOR_P2_37  GPIO_PD14
#define HEADER_CONNECTOR_P2_38  GPIO_PD15
#define HEADER_CONNECTOR_P2_39  GPIO_PF4
#define HEADER_CONNECTOR_P2_40  GPIO_PF5
#define HEADER_CONNECTOR_P2_41  GPIO_PF3
#define HEADER_CONNECTOR_P2_42  GPIO_PF2
#define HEADER_CONNECTOR_P2_43  GPIO_PF8
#define HEADER_CONNECTOR_P2_44  GPIO_PF7
#define HEADER_CONNECTOR_P2_45  GPIO_PF6
#define HEADER_CONNECTOR_P2_46  GPIO_PG3
#define HEADER_CONNECTOR_P2_47  GPIO_PG2
#define HEADER_CONNECTOR_P2_48  // Pin not routed
#define HEADER_CONNECTOR_P2_49  // Pin not routed
#define HEADER_CONNECTOR_P2_50  // Pin not routed
#define HEADER_CONNECTOR_P2_51  // Pin not routed
#define HEADER_CONNECTOR_P2_52  GPIO_PA14
#define HEADER_CONNECTOR_P2_53  GPIO_PA15
#define HEADER_CONNECTOR_P2_54  GPIO_PD8
#define HEADER_CONNECTOR_P2_55  GPIO_PD9
#define HEADER_CONNECTOR_P2_56  GPIO_PD10
#define HEADER_CONNECTOR_P2_57  GPIO_PD11
#define HEADER_CONNECTOR_P2_58  GPIO_PD0
#define HEADER_CONNECTOR_P2_59  GPIO_PC13
#define HEADER_CONNECTOR_P2_60  GPIO_PC14
#define HEADER_CONNECTOR_P2_61  GPIO_PD1
#define HEADER_CONNECTOR_P2_62  GPIO_PD2
#define HEADER_CONNECTOR_P2_63  GPIO_PD3
#define HEADER_CONNECTOR_P2_64  GPIO_PD12
#define HEADER_CONNECTOR_P2_65  GPIO_PD13
#define HEADER_CONNECTOR_P2_66  GPIO_PD4
#define HEADER_CONNECTOR_P2_67  GPIO_PD5
#define HEADER_CONNECTOR_P2_68  GPIO_PD6
#define HEADER_CONNECTOR_P2_69  GPIO_PD7
#define HEADER_CONNECTOR_P2_70  // Pin not routed
#define HEADER_CONNECTOR_P2_71  // Pin not routed
#define HEADER_CONNECTOR_P2_72  GPIO_PF0
#define HEADER_CONNECTOR_P2_73  GPIO_PF1
#define HEADER_CONNECTOR_P2_74  GPIO_PG1
#define HEADER_CONNECTOR_P2_75  GPIO_PG0
#define HEADER_CONNECTOR_P2_76  GPIO_PA6
#define HEADER_CONNECTOR_P2_77  GPIO_PA7
#define HEADER_CONNECTOR_P2_78  GPIO_PG14
#define HEADER_CONNECTOR_P2_79  GPIO_PG12
#define HEADER_CONNECTOR_P2_80  GPIO_PG13

#define LED_2       GPIO_PD4
#define LED_3       GPIO_PD5
#define LED_4       GPIO_PD6
#define LED_5       GPIO_PD7

#define BUTTON_1    GPIO_PA12
#define BUTTON_2    GPIO_PA13

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
