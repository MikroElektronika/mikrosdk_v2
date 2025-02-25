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
 * @file  hal_ll_core_defines.h
 * @brief Core specific defines and enums used for dsPIC chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 * @brief Macro used to define interrupt vector
 * or address based on setting in CMakeLists.txt file.
 *
 * @note By default, mikroSDK uses the vector approach.
 * If you wish to switch to address approach, simply uncomment
 * line @b 13 in following file:
 *     - ../../avr/src/uart/CMakeLists.txt
 */
#define SET_ADDRESS_OR_VECTOR(MODULE, ADDRESS_OR_IVT) SET_ADDRESS_OR_VECTOR_IMPL(MODULE, ADDRESS_OR_IVT)
#define SET_ADDRESS_OR_VECTOR_IMPL(MODULE, ADDRESS_OR_IVT) MODULE##_##ADDRESS_OR_IVT

#if defined (__MIKROC_AI_FOR_AVR__) && defined (__MIKROSDK_AVR_IVT_ADDRESSES__)
#define MIKROC_IV(x) org x
#define ADDRESS_OR_VECTOR IVT_ADDRESS
#elif defined (__MIKROC_AI_FOR_AVR__) // Will be defined by IV approach by default
#define MIKROC_IV(x) iv x
#define ADDRESS_OR_VECTOR IVT
#else
#define MIKROC_IV(x)
#endif

#define __weak __attribute__((weak))

#define hal_ll_core_enable_int_asm asm SEI
#define hal_ll_core_disable_int_asm asm CLI

#ifdef __ATMEGA__
#define UART0_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART0_RX,ADDRESS_OR_VECTOR))
#define UART0_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART0_TX,ADDRESS_OR_VECTOR))
#define UART1_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART1_RX,ADDRESS_OR_VECTOR))
#define UART1_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART1_TX,ADDRESS_OR_VECTOR))
#define UART2_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART2_RX,ADDRESS_OR_VECTOR))
#define UART2_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART2_TX,ADDRESS_OR_VECTOR))
#define UART3_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART3_RX,ADDRESS_OR_VECTOR))
#define UART3_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USART3_TX,ADDRESS_OR_VECTOR))
#elif defined (__ATXMEGA__)
#define UARTC0_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTC0_RXC,ADDRESS_OR_VECTOR))
#define UARTC0_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTC0_TXC,ADDRESS_OR_VECTOR))
#define UARTC1_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTC1_RXC,ADDRESS_OR_VECTOR))
#define UARTC1_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTC1_TXC,ADDRESS_OR_VECTOR))
#define UARTD0_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTD0_RXC,ADDRESS_OR_VECTOR))
#define UARTD0_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTD0_TXC,ADDRESS_OR_VECTOR))
#define UARTD1_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTD1_RXC,ADDRESS_OR_VECTOR))
#define UARTD1_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTD1_TXC,ADDRESS_OR_VECTOR))
#define UARTE0_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTE0_RXC,ADDRESS_OR_VECTOR))
#define UARTE0_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTE0_TXC,ADDRESS_OR_VECTOR))
#define UARTE1_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTE1_RXC,ADDRESS_OR_VECTOR))
#define UARTE1_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTE1_TXC,ADDRESS_OR_VECTOR))
#define UARTF0_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTF0_RXC,ADDRESS_OR_VECTOR))
#define UARTF0_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTF0_TXC,ADDRESS_OR_VECTOR))
#define UARTF1_RX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTF1_RXC,ADDRESS_OR_VECTOR))
#define UARTF1_TX_INTERRUPT_ADDRESS_VECTOR (SET_ADDRESS_OR_VECTOR(HAL_LL_USARTF1_TXC,ADDRESS_OR_VECTOR))
#endif

// Interrupt vectors (program addresses).
#define HAL_LL_CORE_IRQ_NOT_SUPPORTED (0x0038)

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
