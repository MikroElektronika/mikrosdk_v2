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
 * @file  hal_ll_bit_control.h
 * @brief Macros used for bitwise register manipulation.
 */

#ifndef _HAL_LL_BIT_CONTROL_H_
#define _HAL_LL_BIT_CONTROL_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>

/*!< @brief Mask used for register clearing */
#define HAL_LL_CLEAR 0x00U

/*!< @brief Macro */
#define selected_reg(__reg) (*(uint8_t *)__reg)

/*!< @brief Low nibble macros */
#define HAL_LL_NIBBLE_LOW_8BIT (0xF)
#define HAL_LL_NIBBLE_LOW_16BIT (0xFFU)
#define HAL_LL_NIBBLE_LOW_32BIT (0xFFFFUL)

/*!< @brief High nibble macros */
#define HAL_LL_NIBBLE_HIGH_8BIT (0xF0)
#define HAL_LL_NIBBLE_HIGH_16BIT (0xFF00U)
#define HAL_LL_NIBBLE_HIGH_32BIT (0xFFFF0000UL)

/**
 * @brief Sets one bit in a register.
 *
 * @param[in] reg  - register address.
 * @param[in] _bit - bit number (0-7).
 */
#ifdef __XC8__
static inline void set_reg_bit(uint16_t reg, uint8_t bit) {
    uint8_t *addr;
    addr = reg;
    *addr = *addr | (1U)<<(bit);
}
#else
#define set_reg_bit(reg,_bit) (selected_reg(reg) |= ((1U)<<(_bit)))
#endif

/**
 * @brief Sets bits specified by bit_mask
 *        in the specified register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 */
#ifdef __XC8__
static inline void set_reg_bits(uint16_t reg, uint8_t bit_mask) {
    uint8_t *addr;
    addr = reg;
    *addr = *addr | bit_mask;
}
#else
#define set_reg_bits(reg,bit_mask) (selected_reg(reg) |= (bit_mask))
#endif

/**
 * @brief Clears one bit in a register.
 *
 * @param[in] reg  - register address.
 * @param[in] _bit - bit number (0-7).
 */
#ifdef __XC8__
static inline void clear_reg_bit(uint16_t reg, uint8_t bit) {
    uint8_t *addr;
    addr = reg;
    *addr = *addr & ~((1U)<<(bit));
}
#else
#define clear_reg_bit(reg,_bit) (selected_reg(reg) &= ~((1U)<<(_bit)))
#endif

/**
 * @brief Clears bits specified by bit_mask
 *        in the specified register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 */
#ifdef __XC8__
static inline void clear_reg_bits(uint16_t reg, uint8_t bit_mask) {
    uint8_t *addr;
    addr = reg;
    *addr = *addr & ~bit_mask;
}
#else
#define clear_reg_bits(reg,bit_mask) (selected_reg(reg) &= ~(bit_mask))
#endif

/**
 * @brief Returns value of one bit
 *        in a register.
 *
 * @param[in] reg  - register address.
 * @param[in] _bit - bit number (0-7).
 * @return Register(reg) bit value.
 */
#ifdef __XC8__
static inline bool check_reg_bit(uint16_t reg, uint8_t bit) {
    bool state;
    uint8_t *addr;
    addr = reg;
    state = *addr & ((1U)<<(bit));
    return state;
}
#else
#define check_reg_bit(reg,_bit) (selected_reg(reg) & ((1U)<<(_bit)))
#endif

/**
 * @brief Writes specified value to
 *        specified register.
 *
 * @param[in] reg  - register address.
 * @param[in] _val - Value to be written.
 */
#ifdef __XC8__
static void write_reg(uint16_t reg, uint8_t val) {
    uint8_t *addr;
    addr = reg;
    *addr = val;
}
#else
#define write_reg(reg,_val) (selected_reg(reg) = (_val))
#endif

/**
 * @brief Returns value stored
 *        in a register.
 *
 * @param[in] reg  - register address.
 *
 * @return Register(reg) value.
 */
#ifdef __XC8__
static inline uint8_t read_reg(uint16_t reg) {
    uint8_t state;
    uint8_t *addr;
    addr = reg;
    state = *addr;
    return state;
}
#else
#define read_reg(reg) (selected_reg(reg))
#endif

/**
 * @brief Returns value of specified bit
 *        mask from a register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 *
 * @return Register(reg) bits value.
 */
#ifdef __XC8__
static inline uint8_t read_reg_bits(uint16_t reg, uint8_t bit_mask) {
    uint8_t state;
    uint8_t *addr;
    addr = reg;
    state = *addr;
    state = state & bit_mask;
    return state;
}
#else
#define read_reg_bits(reg,bit_mask) (selected_reg(reg) & (bit_mask))
#endif

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
