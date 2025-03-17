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

#define BOARD_NAME "Arduino Micro"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_J5_D1        GPIO_PB2
#define HEADER_CONNECTOR_J5_D2        GPIO_PB0
#define HEADER_CONNECTOR_J5_D3        GPIO_PD3
#define HEADER_CONNECTOR_J5_D4        GPIO_PD2
#define HEADER_CONNECTOR_J5_D5        // Pin not routed
#define HEADER_CONNECTOR_J5_D6        // Pin not routed
#define HEADER_CONNECTOR_J5_D7        GPIO_PD1
#define HEADER_CONNECTOR_J5_D8        GPIO_PD0
#define HEADER_CONNECTOR_J5_D9        GPIO_PD4
#define HEADER_CONNECTOR_J5_D10       GPIO_PC6
#define HEADER_CONNECTOR_J5_D11       GPIO_PD7
#define HEADER_CONNECTOR_J5_D12       GPIO_PE6
#define HEADER_CONNECTOR_J5_D13       GPIO_PB4
#define HEADER_CONNECTOR_J5_D14       GPIO_PB5
#define HEADER_CONNECTOR_J5_D15       GPIO_PB6
#define HEADER_CONNECTOR_J5_D16       GPIO_PB7
#define HEADER_CONNECTOR_J5_D17       GPIO_PD6

#define HEADER_CONNECTOR_J5_D1        GPIO_PB1
#define HEADER_CONNECTOR_J5_D2        GPIO_PB3
#define HEADER_CONNECTOR_J5_D3        // Pin not routed
#define HEADER_CONNECTOR_J5_D4        // Pin not routed
#define HEADER_CONNECTOR_J5_D5        // Pin not routed
#define HEADER_CONNECTOR_J5_D6        // Pin not routed
#define HEADER_CONNECTOR_J5_D7        // Pin not routed
#define HEADER_CONNECTOR_J5_D8        // Pin not routed
#define HEADER_CONNECTOR_J5_D9        GPIO_PF0
#define HEADER_CONNECTOR_J5_D10       GPIO_PF1
#define HEADER_CONNECTOR_J5_D11       GPIO_PF4
#define HEADER_CONNECTOR_J5_D12       GPIO_PF5
#define HEADER_CONNECTOR_J5_D13       GPIO_PF6
#define HEADER_CONNECTOR_J5_D14       GPIO_PF7
#define HEADER_CONNECTOR_J5_D15       // Pin not routed
#define HEADER_CONNECTOR_J5_D16       // Pin not routed
#define HEADER_CONNECTOR_J5_D17       GPIO_PC7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
