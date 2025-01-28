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

#define BOARD_NAME "Arduino Nano"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_J1_1  GPIO_PD1
#define HEADER_CONNECTOR_J1_2  GPIO_PD0
#define HEADER_CONNECTOR_J1_3  // Pin not routed
#define HEADER_CONNECTOR_J1_4  // Pin not routed
#define HEADER_CONNECTOR_J1_5  GPIO_PD2
#define HEADER_CONNECTOR_J1_6  GPIO_PD3
#define HEADER_CONNECTOR_J1_7  GPIO_PD4
#define HEADER_CONNECTOR_J1_8  GPIO_PD5
#define HEADER_CONNECTOR_J1_9  GPIO_PD6
#define HEADER_CONNECTOR_J1_10 GPIO_PD7
#define HEADER_CONNECTOR_J1_11 GPIO_PB0
#define HEADER_CONNECTOR_J1_12 GPIO_PB1
#define HEADER_CONNECTOR_J1_13 GPIO_PB2
#define HEADER_CONNECTOR_J1_14 GPIO_PB3
#define HEADER_CONNECTOR_J1_15 GPIO_PB4

#define HEADER_CONNECTOR_J2_1  // Pin not routed
#define HEADER_CONNECTOR_J2_2  // Pin not routed
#define HEADER_CONNECTOR_J2_3  // Pin not routed
#define HEADER_CONNECTOR_J2_4  // Pin not routed
#define HEADER_CONNECTOR_J2_5  // Pin not routed
#define HEADER_CONNECTOR_J2_6  // Pin not routed
#define HEADER_CONNECTOR_J2_7  GPIO_PC5
#define HEADER_CONNECTOR_J2_8  GPIO_PC4
#define HEADER_CONNECTOR_J2_9  GPIO_PC3
#define HEADER_CONNECTOR_J2_10 GPIO_PC2
#define HEADER_CONNECTOR_J2_11 GPIO_PC1
#define HEADER_CONNECTOR_J2_12 GPIO_PC0
#define HEADER_CONNECTOR_J2_13 // Pin not routed
#define HEADER_CONNECTOR_J2_14 // Pin not routed
#define HEADER_CONNECTOR_J2_15 GPIO_PB5

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
