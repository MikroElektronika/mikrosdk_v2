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

#define BOARD_NAME "PICKit PIC18 j-series 64/80-Pin Demo Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_P1_D1       // Pin not routed
#define HEADER_CONNECTOR_P1_D2       // Pin not routed
#define HEADER_CONNECTOR_P1_D3       // Pin not routed
#define HEADER_CONNECTOR_P1_D4       GPIO_PB7
#define HEADER_CONNECTOR_P1_D5       GPIO_PB6
#define HEADER_CONNECTOR_P1_D6       // Pin not routed

// LEDS
#define LED1        GPIO_PD0
#define LED2        GPIO_PD1
#define LED3        GPIO_PD2
#define LED4        GPIO_PD3
#define LED5        GPIO_PD4
#define LED6        GPIO_PD5
#define LED7        GPIO_PD6
#define LED8        GPIO_PD7

// BUTTON
#define BUTTON      GPIO_PB0

// POTENTIOMETER
#define POT1        GPIO_PA0

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
