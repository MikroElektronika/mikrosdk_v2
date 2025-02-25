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

#define BOARD_NAME "ATMEGA328P XPLAINED MINI"

#include "hal_target.h"

// Mapping
// DIGITAL I/O HIGH BYTE HEADER
#define HEADER_CONNECTOR_DIGI_HIGH_D1      GPIO_PB0
#define HEADER_CONNECTOR_DIGI_HIGH_D2      GPIO_PB1
#define HEADER_CONNECTOR_DIGI_HIGH_D3      GPIO_PB2
#define HEADER_CONNECTOR_DIGI_HIGH_D4      GPIO_PB3
#define HEADER_CONNECTOR_DIGI_HIGH_D5      GPIO_PB4
#define HEADER_CONNECTOR_DIGI_HIGH_D6      GPIO_PB5
#define HEADER_CONNECTOR_DIGI_HIGH_D7      // Pin not routed
#define HEADER_CONNECTOR_DIGI_HIGH_D8      // Pin not routed
#define HEADER_CONNECTOR_DIGI_HIGH_D9      GPIO_PC4
#define HEADER_CONNECTOR_DIGI_HIGH_D10     GPIO_PC5

// DIGITAL I/0 LOW BYTE HEADER
#define HEADER_CONNECTOR_DIGI_LOW_D1       GPIO_PD0
#define HEADER_CONNECTOR_DIGI_LOW_D2       GPIO_PD1
#define HEADER_CONNECTOR_DIGI_LOW_D3       GPIO_PD2
#define HEADER_CONNECTOR_DIGI_LOW_D4       GPIO_PD3
#define HEADER_CONNECTOR_DIGI_LOW_D5       GPIO_PD4
#define HEADER_CONNECTOR_DIGI_LOW_D6       GPIO_PD5
#define HEADER_CONNECTOR_DIGI_LOW_D7       GPIO_PD6
#define HEADER_CONNECTOR_DIGI_LOW_D8       GPIO_PD7

// ANALOG HEADER
#define HEADER_CONNECTOR_ANALOG_D1    GPIO_PC0
#define HEADER_CONNECTOR_ANALOG_D2    GPIO_PC1
#define HEADER_CONNECTOR_ANALOG_D3    GPIO_PC2
#define HEADER_CONNECTOR_ANALOG_D4    GPIO_PC3
#define HEADER_CONNECTOR_ANALOG_D5    GPIO_PC4
#define HEADER_CONNECTOR_ANALOG_D6    GPIO_PC5

// ISP HEADER
#define HEADER_CONNECTOR_ISP_D1       GPIO_PB4
#define HEADER_CONNECTOR_ISP_D2       // Pin not routed
#define HEADER_CONNECTOR_ISP_D3       GPIO_PB5
#define HEADER_CONNECTOR_ISP_D4       GPIO_PB3
#define HEADER_CONNECTOR_ISP_D5       GPIO_PC6
#define HEADER_CONNECTOR_ISP_D6       // Pin not routed

// USART HEADER
#define HEADER_CONNECTOR_USART_D1     GPIO_PD0 // RX
#define HEADER_CONNECTOR_USART_D2     GPIO_PD1 // TX

// ADDITIONAL I/O
#define GRID_POSITION_H5              GPIO_PA6
#define GRID_POSITION_G5              GPIO_PA7

// LEDS
#define LED1    GPIO_PB5

// BUTTONS
#define BUTTON1 GPIO_PB7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END