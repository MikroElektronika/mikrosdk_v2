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
 * @file  can_definitions.h
 * @brief MCU specific CAN module definitions for PIC32MX550F256L.
 */

#ifndef _CAN_DEFINITIONS_H_
#define _CAN_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

// CAN
#define CAN1_RX_RE5
#define CAN1_RX_RC4
#define CAN1_RX_RG7
#define CAN1_RX_RB3
#define CAN1_RX_RB1
#define CAN1_RX_RD15
#define CAN1_RX_RF5
#define CAN1_RX_RA15
#define CAN1_RX_RD11
#define CAN1_RX_RC13
#define CAN1_RX_RD3
#define CAN1_RX_RF0
#define CAN1_RX_RG0
#define CAN1_TX_RC1
#define CAN1_TX_RG8
#define CAN1_TX_RB5
#define CAN1_TX_RB9
#define CAN1_TX_RB10
#define CAN1_TX_RD14
#define CAN1_TX_RF4
#define CAN1_TX_RF2
#define CAN1_TX_RA14
#define CAN1_TX_RD10
#define CAN1_TX_RC14
#define CAN1_TX_RD2
#define CAN1_TX_RF1
#define CAN1_TX_RG1

#define CAN_MODULE_1 (1)

#define CAN_MODULE_COUNT (1)

#define HAL_LL_C1RXR_ADDRESS (0xBF80FAC8UL)
#define HAL_LL_C2RXR_ADDRESS (0xBF80FACCUL)
#define HAL_LL_C1CON_ADDRESS (0xBF88B000UL)
#define HAL_LL_CAN1_BASE_ADDRESS HAL_LL_C1CON_ADDRESS

#define HAL_LL_CAN_PPS_ENABLED true
// EOF CAN

#ifdef __cplusplus
}
#endif

#endif // _CAN_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
