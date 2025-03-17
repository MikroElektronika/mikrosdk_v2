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

#define BOARD_NAME "MPLab Starter Kit For PIC24H MCUs"

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
#define DISPLAY_CONNECTOR_DC1_D11     GPIO_PB15
#define DISPLAY_CONNECTOR_DC1_D12     GPIO_PA1
#define DISPLAY_CONNECTOR_DC1_D13     GPIO_PC7
#define DISPLAY_CONNECTOR_DC1_D14     GPIO_PB14
#define DISPLAY_CONNECTOR_DC1_D15     GPIO_PB13
#define DISPLAY_CONNECTOR_DC1_D16     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D17     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D18     GPIO_PB12
#define DISPLAY_CONNECTOR_DC1_D19     GPIO_PB11
#define DISPLAY_CONNECTOR_DC1_D20     GPIO_PB10
#define DISPLAY_CONNECTOR_DC1_D21     GPIO_PB9
#define DISPLAY_CONNECTOR_DC1_D22     GPIO_PB8
#define DISPLAY_CONNECTOR_DC1_D23     GPIO_PB7
#define DISPLAY_CONNECTOR_DC1_D24     GPIO_PB6
#define DISPLAY_CONNECTOR_DC1_D25     GPIO_PB5
#define DISPLAY_CONNECTOR_DC1_D26     // Pin not routed
#define DISPLAY_CONNECTOR_DC1_D27     // Pin not routed


// BUTTONS
#define BUTTON1     GPIO_PC2
#define BUTTON2     GPIO_PA8

// ACCELEROMETER
#define ACCEL_X     GPIO_PB2
#define ACCEL_Y     GPIO_PB3
#define ACCEL_Z     GPIO_PC0

// SPEAKER
#define AUDIO_OUT   GPIO_PB4

// SENSOR
#define SENSOR_IN   GPIO_PC1


#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END