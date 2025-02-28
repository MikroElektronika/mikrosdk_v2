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

#define BOARD_NAME "CHIPKIT LENNY DEVELOPMENT BOARD"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_0  GPIO_PC8
#define HEADER_CONNECTOR_1  GPIO_PC9
#define HEADER_CONNECTOR_2  GPIO_PB7
#define HEADER_CONNECTOR_3  GPIO_PC4
#define HEADER_CONNECTOR_4  GPIO_PC6
#define HEADER_CONNECTOR_5  GPIO_PB5
#define HEADER_CONNECTOR_6  GPIO_PC7
#define HEADER_CONNECTOR_7  GPIO_PA3
#define HEADER_CONNECTOR_8  GPIO_PC5
#define HEADER_CONNECTOR_9  GPIO_PC3
#define HEADER_CONNECTOR_10 GPIO_PC1
#define HEADER_CONNECTOR_11 GPIO_PB13
#define HEADER_CONNECTOR_12 GPIO_PB1
#define HEADER_CONNECTOR_13 GPIO_PB14
#define HEADER_CONNECTOR_14 GPIO_PA1
#define HEADER_CONNECTOR_15 GPIO_PB0
#define HEADER_CONNECTOR_16 GPIO_PC0
#define HEADER_CONNECTOR_17 GPIO_PC2
#define HEADER_CONNECTOR_18 GPIO_PB2
#define HEADER_CONNECTOR_19 GPIO_PB3
#define HEADER_CONNECTOR_20 // Pin not routed
#define HEADER_CONNECTOR_21 // Pin not routed
#define HEADER_CONNECTOR_22 // Pin not routed
#define HEADER_CONNECTOR_23 // Pin not routed
#define HEADER_CONNECTOR_24 // Pin not routed
#define HEADER_CONNECTOR_25 GPIO_PA4
#define HEADER_CONNECTOR_26 GPIO_PB15
#define HEADER_CONNECTOR_27 GPIO_PA9
#define HEADER_CONNECTOR_28 GPIO_PB9
#define HEADER_CONNECTOR_29 GPIO_PB8

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
