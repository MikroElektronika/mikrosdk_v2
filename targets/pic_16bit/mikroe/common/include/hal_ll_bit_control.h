/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_bit_control.h
 * @brief Macros used for bitwise register manipulation.
 */

#ifndef _HAL_LL_BIT_CONTROL_H_
#define _HAL_LL_BIT_CONTROL_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/*!< @brief Mask used for register clearing */
#define HAL_LL_CLEAR 0x00U

/*!< @brief Macro */
#define selected_reg(__reg) (*(uint16_t *)__reg)

/*!< @brief Low nibble macros */
#define HAL_LL_NIBBLE_LOW_8BIT (0xF)
#define HAL_LL_NIBBLE_LOW_16BIT (0xFFU)
#define HAL_LL_NIBBLE_LOW_32BIT (0xFFFFUL)

/*!< @brief High nibble macros */
#define HAL_LL_NIBBLE_HIGH_8BIT (0xF0) //0b11110000
#define HAL_LL_NIBBLE_HIGH_16BIT (0xFF00U)
#define HAL_LL_NIBBLE_HIGH_32BIT (0xFFFF0000UL)

/**
 * @brief Sets one bit in a register.
 *
 * @param[in] reg  - register address.
 * @param[in] _bit - bit number (0-7).
 */
#define set_reg_bit(reg,_bit) (selected_reg(reg) |= ((1U)<<(_bit)))

/**
 * @brief Sets bits specified by bit_mask
 *        in the specified register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 */
#define set_reg_bits(reg,bit_mask) (selected_reg(reg) |= (bit_mask))

/**
 * @brief Clears one bit in a register.
 *
 * @param[in] reg  - register address.
 * @param[in] _bit - bit number (0-7).
 */
#define clear_reg_bit(reg,_bit) (selected_reg(reg) &= ~((1U)<<(_bit)))

/**
 * @brief Clears bits specified by bit_mask
 *        in the specified register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 */
#define clear_reg_bits(reg,bit_mask) (selected_reg(reg) &= ~(bit_mask))

/**
 * @brief Returns value of one bit
 *        in a register.
 *
 * @param[in] reg  - register address.
 * @param[in] _bit - bit number (0-7).
 * @return Register(reg) bit value.
 */
#define check_reg_bit(reg,_bit) (selected_reg(reg) & ((1U)<<(_bit)))

/**
 * @brief Writes specified value to
 *        specified register.
 *
 * @param[in] reg  - register address.
 * @param[in] _val - Value to be written.
 */
#define write_reg(reg,_val) (selected_reg(reg) = (_val))

/**
 * @brief Returns value stored
 *        in a register.
 *
 * @param[in] reg  - register address.
 *
 * @return Register(reg) value.
 */
#define read_reg(reg) (selected_reg(reg))

/**
 * @brief Returns value of specified bit
 *        mask from a register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 *
 * @return Register(reg) bits value.
 */
#define read_reg_bits(reg,bit_mask) (selected_reg(reg) & (bit_mask))

/**
 * @brief Clears all bits in a register.
 *
 * @param[in] reg  - register address
 */
#define clear_reg(reg) write_reg(reg, HAL_LL_CLEAR)

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_BIT_CONTROL_H_
// ------------------------------------------------------------------------- END
