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
 * @brief MCU specific CAN module definitions for PIC32MX775F512L.
 */

#ifndef _CAN_DEFINITIONS_H_
#define _CAN_DEFINITIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

// CAN
#define CAN2_TX_RC2_ALT
#define CAN2_RX_RC3_ALT
#define CAN1_TX_RF13_ALT
#define CAN1_RX_RF12_ALT
#define CAN1_RX_RF0
#define CAN1_TX_RF1
#define CAN2_TX_RG1
#define CAN2_RX_RG0

#define CAN_MODULE_1 (1)
#define CAN_MODULE_2 (2)

#define CAN_MODULE_COUNT (2)

#define HAL_LL_C1CON_ADDRESS (0xBF88B000UL)
#define HAL_LL_CAN1_BASE_ADDRESS HAL_LL_C1CON_ADDRESS
#define HAL_LL_C2CON_ADDRESS (0xBF88C000UL)
#define HAL_LL_CAN2_BASE_ADDRESS HAL_LL_C2CON_ADDRESS
// EOF CAN

#ifdef __cplusplus
}
#endif

#endif // _CAN_DEFINITIONS_H_
// ------------------------------------------------------------------------- END
