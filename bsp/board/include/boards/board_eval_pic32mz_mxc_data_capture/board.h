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
 *       https://github.com/MikroElektronika/mikrosdk_v2/blob/master/changelog/v2.14.4/new_hw/2025-06-16.md
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "PIC32MZ MXS Data Capture Board"

#include "mikrobus.h"

// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   PB9
#define MIKROBUS_1_RST  PD11
#define MIKROBUS_1_CS   PB15
#define MIKROBUS_1_SCK  PB14
#define MIKROBUS_1_MISO PB10
#define MIKROBUS_1_MOSI PF0
#define MIKROBUS_1_PWM  PD2
#define MIKROBUS_1_INT  PD0
#define MIKROBUS_1_RX   PC14
#define MIKROBUS_1_TX   PC13
#define MIKROBUS_1_SCL  PD10
#define MIKROBUS_1_SDA  PD9

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   PB8
#define MIKROBUS_2_RST  PB4
#define MIKROBUS_2_CS   PB2
#define MIKROBUS_2_SCK  PG6
#define MIKROBUS_2_MISO PB3
#define MIKROBUS_2_MOSI PB5
#define MIKROBUS_2_PWM  PE5
#define MIKROBUS_2_INT  PG9
#define MIKROBUS_2_RX   PB7
#define MIKROBUS_2_TX   PB6
#define MIKROBUS_2_SCL  PG8
#define MIKROBUS_2_SDA  PG7

// QSPI
#define QSPI_AN16   PE6
#define QSPI_CS1    PD5
#define QSPI_CS0    PD4
#define QSPI_D2     PE2
#define QSPI_D3     PE3
#define QSPI_D1     PE1
#define QSPI_D0     PE0
#define QSPI_CLK    PF1

// PAC1944
#define PAC1944_SCL PF5
#define PAC1944_SDA PF6

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
