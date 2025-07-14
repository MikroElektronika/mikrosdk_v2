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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.5/new_hw/2025-07-16.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "LED LIGHT CUBE"

#include "hal_target.h"

// Mapping
#define MCU_CONNECTOR_PIC_RST   GPIO_PA0
#define MCU_CONNECTOR_POT       GPIO_PA1
#define MCU_CONNECTOR_PGD       GPIO_PB0
#define MCU_CONNECTOR_PGC       GPIO_PB1
#define MCU_CONNECTOR_PWMCLK    GPIO_PB2
#define MCU_CONNECTOR_WAKE      GPIO_PB3
#define MCU_CONNECTOR_X1        GPIO_PA2
#define MCU_CONNECTOR_X2        GPIO_PA3
#define MCU_CONNECTOR_PIC_TX    GPIO_PB4
#define MCU_CONNECTOR_PIC_RX    GPIO_PA4
#define MCU_CONNECTOR_PIC_CTS   GPIO_PB5
#define MCU_CONNECTOR_MODE      GPIO_PB7
#define MCU_CONNECTOR_LE        GPIO_PB8
#define MCU_CONNECTOR_PIC_RTS   GPIO_PB9
#define MCU_CONNECTOR_DP        GPIO_PB10
#define MCU_CONNECTOR_DM        GPIO_PB11
#define MCU_CONNECTOR_SDO       GPIO_PB13
#define MCU_CONNECTOR_CLK       GPIO_PB14
#define MCU_CONNECTOR_LIGHT     GPIO_PB15

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
