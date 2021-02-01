/****************************************************************************
**
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The mikroElektronika Company.
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
extern "C"{
#endif

// Hardware revision number
#define BOARD_REV_MAJOR (2)
#define BOARD_REV_MINOR (0)

#define BOARD_NAME "Curiosity HPC"

#include "dip_socket.h"
#include "mikrobus.h"

/// Mapping
#define MIKROBUS_1      1
#define MIKROBUS_1_AN   MIKROBUS_1_AN_DIP
#define MIKROBUS_1_RST  MIKROBUS_1_RST_DIP
#define MIKROBUS_1_CS   MIKROBUS_1_CS_DIP
#define MIKROBUS_1_SCK  MIKROBUS_1_SCK_DIP
#define MIKROBUS_1_MISO MIKROBUS_1_MISO_DIP
#define MIKROBUS_1_MOSI MIKROBUS_1_MOSI_DIP
#define MIKROBUS_1_PWM  MIKROBUS_1_PWM_DIP
#define MIKROBUS_1_INT  MIKROBUS_1_INT_DIP
#define MIKROBUS_1_RX   MIKROBUS_1_RX_DIP
#define MIKROBUS_1_TX   MIKROBUS_1_TX_DIP
#define MIKROBUS_1_SCL  MIKROBUS_1_SCL_DIP
#define MIKROBUS_1_SDA  MIKROBUS_1_SDA_DIP

#define MIKROBUS_2      2
#define MIKROBUS_2_AN   MIKROBUS_2_AN_DIP
#define MIKROBUS_2_RST  MIKROBUS_2_RST_DIP
#define MIKROBUS_2_CS   MIKROBUS_2_CS_DIP
#define MIKROBUS_2_SCK  MIKROBUS_2_SCK_DIP
#define MIKROBUS_2_MISO MIKROBUS_2_MISO_DIP
#define MIKROBUS_2_MOSI MIKROBUS_2_MOSI_DIP
#define MIKROBUS_2_PWM  MIKROBUS_2_PWM_DIP
#define MIKROBUS_2_INT  MIKROBUS_2_INT_DIP
#define MIKROBUS_2_RX   MIKROBUS_2_RX_DIP
#define MIKROBUS_2_TX   MIKROBUS_2_TX_DIP
#define MIKROBUS_2_SCL  MIKROBUS_2_SCL_DIP
#define MIKROBUS_2_SDA  MIKROBUS_2_SDA_DIP

#define BOARD_CURIOSITY_HPC_D2   PA4
#define BOARD_CURIOSITY_HPC_D3   PA5
#define BOARD_CURIOSITY_HPC_D4   PA6
#define BOARD_CURIOSITY_HPC_D5   PA7

#define BOARD_CURIOSITY_HPC_S1   PB4
#define BOARD_CURIOSITY_HPC_S2   PC5

#define BOARD_CURIOSITY_HPC_POT1 PA0

#define USB_UART_TX     MIKROBUS_2_RX_DIP
#define USB_UART_RX     MIKROBUS_2_TX_DIP

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
