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

#define BOARD_NAME "Freedom Development Platform for Kinetis K66, K65, and K26 MCUs"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN3_D1       GPIO_PA27
#define HEADER_CONNECTOR_CN3_D2       // Pin not routed
#define HEADER_CONNECTOR_CN3_D3       GPIO_PA26
#define HEADER_CONNECTOR_CN3_D4       // Pin not routed
#define HEADER_CONNECTOR_CN3_D5       GPIO_PA4
#define HEADER_CONNECTOR_CN3_D6       // Pin not routed
#define HEADER_CONNECTOR_CN3_D7       GPIO_PA6
#define HEADER_CONNECTOR_CN3_D8       // Pin not routed
#define HEADER_CONNECTOR_CN3_D9       GPIO_PA7
#define HEADER_CONNECTOR_CN3_D10      // Pin not routed
#define HEADER_CONNECTOR_CN3_D11      GPIO_PA8
#define HEADER_CONNECTOR_CN3_D12      // Pin not routed
#define HEADER_CONNECTOR_CN3_D13      GPIO_PA9
#define HEADER_CONNECTOR_CN3_D14      // Pin not routed
#define HEADER_CONNECTOR_CN3_D15      GPIO_PA1
#define HEADER_CONNECTOR_CN3_D16      // Pin not routed

#define HEADER_CONNECTOR_CN4_D1       // Pin not routed
#define HEADER_CONNECTOR_CN4_D2       GPIO_PB7
#define HEADER_CONNECTOR_CN4_D3       // Pin not routed
#define HEADER_CONNECTOR_CN4_D4       GPIO_PB6
#define HEADER_CONNECTOR_CN4_D5       // Pin not routed
#define HEADER_CONNECTOR_CN4_D6       GPIO_PB5
#define HEADER_CONNECTOR_CN4_D7       // Pin not routed
#define HEADER_CONNECTOR_CN4_D8       GPIO_PB4
#define HEADER_CONNECTOR_CN4_D9       GPIO_PB23
#define HEADER_CONNECTOR_CN4_D10      GPIO_PB3
#define HEADER_CONNECTOR_CN4_D11      // Pin not routed
#define HEADER_CONNECTOR_CN4_D12      GPIO_PB2

#define HEADER_CONNECTOR_CN2_D1       // Pin not routed
#define HEADER_CONNECTOR_CN2_D2       GPIO_PB18
#define HEADER_CONNECTOR_CN2_D3       // Pin not routed
#define HEADER_CONNECTOR_CN2_D4       GPIO_PB19
#define HEADER_CONNECTOR_CN2_D5       // Pin not routed
#define HEADER_CONNECTOR_CN2_D6       GPIO_PD0
#define HEADER_CONNECTOR_CN2_D7       GPIO_PB10
#define HEADER_CONNECTOR_CN2_D8       GPIO_PD2
#define HEADER_CONNECTOR_CN2_D9       GPIO_PB11
#define HEADER_CONNECTOR_CN2_D10      GPIO_PD3
#define HEADER_CONNECTOR_CN2_D11      GPIO_PC0
#define HEADER_CONNECTOR_CN2_D12      GPIO_PD1
#define HEADER_CONNECTOR_CN2_D13      GPIO_PE24
#define HEADER_CONNECTOR_CN2_D14      // Pin not routed
#define HEADER_CONNECTOR_CN2_D15      GPIO_PE25
#define HEADER_CONNECTOR_CN2_D16      // Pin not routed
#define HEADER_CONNECTOR_CN2_D17      GPIO_PD13
#define HEADER_CONNECTOR_CN2_D18      GPIO_PC11
#define HEADER_CONNECTOR_CN2_D19      GPIO_PD12
#define HEADER_CONNECTOR_CN2_D20      GPIO_PC10

#define HEADER_CONNECTOR_CN1_D1       GPIO_PE12
#define HEADER_CONNECTOR_CN1_D2       GPIO_PC3
#define HEADER_CONNECTOR_CN1_D3       GPIO_PE11
#define HEADER_CONNECTOR_CN1_D4       GPIO_PC4
#define HEADER_CONNECTOR_CN1_D5       GPIO_PC1
#define HEADER_CONNECTOR_CN1_D6       GPIO_PC16
#define HEADER_CONNECTOR_CN1_D7       GPIO_PC6
#define HEADER_CONNECTOR_CN1_D8       GPIO_PC8
#define HEADER_CONNECTOR_CN1_D9       GPIO_PE9
#define HEADER_CONNECTOR_CN1_D10      GPIO_PC12
#define HEADER_CONNECTOR_CN1_D11      GPIO_PC11
#define HEADER_CONNECTOR_CN1_D12      GPIO_PC5
#define HEADER_CONNECTOR_CN1_D13      GPIO_PE8
#define HEADER_CONNECTOR_CN1_D14      GPIO_PC2
#define HEADER_CONNECTOR_CN1_D15      GPIO_PE7
#define HEADER_CONNECTOR_CN1_D16      GPIO_PA25

// LEDS
#define LED1     GPIO_PC9         // RED
#define LED2     GPIO_PE6         // GREEN
#define LED3     GPIO_PA11        // BLUE

// BUTTONS
#define BUTTON2  GPIO_PD11
#define BUTTON3  GPIO_PA10

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
