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

#define BOARD_NAME "STM32G431CB_DISCOVERY"

#include "hal_target.h"

// Mapping
#define MOTOR_CONNECTOR_D1      // Pin not routed
#define MOTOR_CONNECTOR_D2      GPIO_PC13
#define MOTOR_CONNECTOR_D3      GPIO_PC14
#define MOTOR_CONNECTOR_D4      GPIO_PC15
#define MOTOR_CONNECTOR_D5      GPIO_PF0
#define MOTOR_CONNECTOR_D6      GPIO_PF1
#define MOTOR_CONNECTOR_D7      GPIO_PG10
#define MOTOR_CONNECTOR_D8      GPIO_PA0
#define MOTOR_CONNECTOR_D9      GPIO_PA1
#define MOTOR_CONNECTOR_D10     GPIO_PA2
#define MOTOR_CONNECTOR_D11     GPIO_PA3
#define MOTOR_CONNECTOR_D12     GPIO_PA4
#define MOTOR_CONNECTOR_D13     GPIO_PA5
#define MOTOR_CONNECTOR_D14     GPIO_PA6
#define MOTOR_CONNECTOR_D15     GPIO_PA7
#define MOTOR_CONNECTOR_D16     GPIO_PC4
#define MOTOR_CONNECTOR_D17     GPIO_PB0
#define MOTOR_CONNECTOR_D18     GPIO_PB1
#define MOTOR_CONNECTOR_D19     GPIO_PB2
#define MOTOR_CONNECTOR_D20     // Pin not routed
#define MOTOR_CONNECTOR_D21     // Pin not routed
#define MOTOR_CONNECTOR_D22     GPIO_PB10
#define MOTOR_CONNECTOR_D23     // Pin not routed
#define MOTOR_CONNECTOR_D24     GPIO_PB11
#define MOTOR_CONNECTOR_D25     GPIO_PB12
#define MOTOR_CONNECTOR_D26     GPIO_PB13
#define MOTOR_CONNECTOR_D27     GPIO_PB14
#define MOTOR_CONNECTOR_D28     GPIO_PB15
#define MOTOR_CONNECTOR_D29     GPIO_PC6
#define MOTOR_CONNECTOR_D30     GPIO_PA8
#define MOTOR_CONNECTOR_D31     GPIO_PA9
#define MOTOR_CONNECTOR_D32     GPIO_PA10
#define MOTOR_CONNECTOR_D33     GPIO_PA11
#define MOTOR_CONNECTOR_D34     GPIO_PA12
#define MOTOR_CONNECTOR_D35     // Pin not routed
#define MOTOR_CONNECTOR_D36     GPIO_PA13
#define MOTOR_CONNECTOR_D37     GPIO_PA14
#define MOTOR_CONNECTOR_D38     GPIO_PA15
#define MOTOR_CONNECTOR_D39     GPIO_PC10
#define MOTOR_CONNECTOR_D40     GPIO_PC11
#define MOTOR_CONNECTOR_D41     GPIO_PB3
#define MOTOR_CONNECTOR_D42     GPIO_PB4
#define MOTOR_CONNECTOR_D43     GPIO_PB5
#define MOTOR_CONNECTOR_D44     GPIO_PB6
#define MOTOR_CONNECTOR_D45     GPIO_PB7
#define MOTOR_CONNECTOR_D46     GPIO_PB8
#define MOTOR_CONNECTOR_D47     GPIO_PB9


#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
