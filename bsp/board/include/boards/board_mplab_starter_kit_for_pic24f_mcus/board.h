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
 *
 * @note For board-specific changes and version history, refer to the changelogs:
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/{markdown_path}
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "MPLab Starter Kit For PIC24F MCUs"

#include "hal_target.h"

// OLED Display
#define DISPLAY_CONNECTOR_DC1_D1      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D2      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D3      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D4      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D5      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D6      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D7      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D8      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D9      // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D10     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D11     GPIO_PD11
#define DISPLAY_CONNECTOR_DC1_D12     GPIO_PD2
#define DISPLAY_CONNECTOR_DC1_D13     GPIO_PB15
#define DISPLAY_CONNECTOR_DC1_D14     GPIO_PD4
#define DISPLAY_CONNECTOR_DC1_D15     GPIO_PD5
#define DISPLAY_CONNECTOR_DC1_D16     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D17     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D18     GPIO_PE0
#define DISPLAY_CONNECTOR_DC1_D19     GPIO_PE1
#define DISPLAY_CONNECTOR_DC1_D20     GPIO_PE2
#define DISPLAY_CONNECTOR_DC1_D21     GPIO_PE3
#define DISPLAY_CONNECTOR_DC1_D22     GPIO_PE4
#define DISPLAY_CONNECTOR_DC1_D23     GPIO_PE5
#define DISPLAY_CONNECTOR_DC1_D24     GPIO_PE6
#define DISPLAY_CONNECTOR_DC1_D25     GPIO_PE7
#define DISPLAY_CONNECTOR_DC1_D26     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D27     // Pin not routed

// LEDS
#define LED1        GPIO_PF4     //RED
#define LED2        GPIO_PG8     //GREEN
#define LED3        GPIO_PG6     //BLUE

// CAPACITIVE ARROWS
#define TOUCH_PAD1  GPIO_PB8
#define TOUCH_PAD2  GPIO_PB9
#define TOUCH_PAD3  GPIO_PB10
#define TOUCH_PAD4  GPIO_PB11
#define TOUCH_PAD5  GPIO_PB12

// POTENTIOMETER
#define POT1        GPIO_PB0

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END