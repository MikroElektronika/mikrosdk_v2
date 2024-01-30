/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_core_macros.h
 * @brief mikroSDK dsPIC core macros.
 */

#ifndef __HAL_LL_CORE_MACROS_H__
#define __HAL_LL_CORE_MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define UART1_INTERRUPT_CONTROL_BIT_TX (12)
#define UART1_INTERRUPT_CONTROL_BIT_RX (11)
#define UART1_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC0_REG_ADDRESS)
#define UART1_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC0_REG_ADDRESS)
#define UART1_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS0_REG_ADDRESS)
#define UART1_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS0_REG_ADDRESS)
#define UART2_INTERRUPT_CONTROL_BIT_TX (15)
#define UART2_INTERRUPT_CONTROL_BIT_RX (14)
#define UART2_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC1_REG_ADDRESS)
#define UART2_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC1_REG_ADDRESS)
#define UART2_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS1_REG_ADDRESS)
#define UART2_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS1_REG_ADDRESS)
#define UART3_INTERRUPT_CONTROL_BIT_TX (3)
#define UART3_INTERRUPT_CONTROL_BIT_RX (2)
#define UART3_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC5_REG_ADDRESS)
#define UART3_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC5_REG_ADDRESS)
#define UART3_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS5_REG_ADDRESS)
#define UART3_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS5_REG_ADDRESS)
#define UART4_INTERRUPT_CONTROL_BIT_TX (9)
#define UART4_INTERRUPT_CONTROL_BIT_RX (8)
#define UART4_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC5_REG_ADDRESS)
#define UART4_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC5_REG_ADDRESS)
#define UART4_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS5_REG_ADDRESS)
#define UART4_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS5_REG_ADDRESS)
#define UART5_INTERRUPT_CONTROL_BIT_TX (0)
#define UART5_INTERRUPT_CONTROL_BIT_RX (15)
#define UART5_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC7_REG_ADDRESS)
#define UART5_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC6_REG_ADDRESS)
#define UART5_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS7_REG_ADDRESS)
#define UART5_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS6_REG_ADDRESS)
#define UART6_INTERRUPT_CONTROL_BIT_TX (3)
#define UART6_INTERRUPT_CONTROL_BIT_RX (2)
#define UART6_INTERRUPT_CONTROL_REG_IEC_TX (HAL_LL_IEC7_REG_ADDRESS)
#define UART6_INTERRUPT_CONTROL_REG_IEC_RX (HAL_LL_IEC7_REG_ADDRESS)
#define UART6_INTERRUPT_CONTROL_REG_IFS_TX (HAL_LL_IFS7_REG_ADDRESS)
#define UART6_INTERRUPT_CONTROL_REG_IFS_RX (HAL_LL_IFS7_REG_ADDRESS)

#ifdef __cplusplus
}
#endif

#endif // __HAL_LL_CORE_MACROS_H__
