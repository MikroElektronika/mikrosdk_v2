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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_i2c_pin_map.h
 * @brief I2C HAL LOW LEVEL PIN MAP.
 */

#ifndef _HAL_LL_I2C_PIN_MAP_H_
#define _HAL_LL_I2C_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_i2c_module_num(_module_num) (_module_num - 1)

#ifdef I2C_MODULE_0
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = 0x40020000;
#endif
#ifdef I2C_MODULE_1
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = 0x40021000;
#endif
#ifdef I2C_MODULE_2
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE_ADDR = 0x40022000;
#endif
#ifdef I2C_MODULE_3
static const hal_ll_base_addr_t HAL_LL_I2C3_BASE_ADDR = 0x40023000;
#endif
#ifdef I2C_MODULE_4
static const hal_ll_base_addr_t HAL_LL_I2C4_BASE_ADDR = 0x400C0000;
#endif
#ifdef I2C_MODULE_5
static const hal_ll_base_addr_t HAL_LL_I2C5_BASE_ADDR = 0x400C1000;
#endif
#ifdef I2C_MODULE_6
static const hal_ll_base_addr_t HAL_LL_I2C6_BASE_ADDR = 0x400C2000;
#endif
#ifdef I2C_MODULE_7
static const hal_ll_base_addr_t HAL_LL_I2C7_BASE_ADDR = 0x400C3000;
#endif
#ifdef I2C_MODULE_8
static const hal_ll_base_addr_t HAL_LL_I2C8_BASE_ADDR = 0x400B8000;
#endif
#ifdef I2C_MODULE_9
static const hal_ll_base_addr_t HAL_LL_I2C9_BASE_ADDR = 0x400B9000;
#endif

/*!< @brief I2C pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    uint8_t af;
} hal_ll_i2c_pin_map_t;

/*!< I2C SCL Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] = {
    #ifdef I2C0_SCL_PB2_AF3
    {PB2, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_0), 3},
    #endif
    #ifdef I2C1_SCL_PA6_AF3
    {PA6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 3},
    #endif
    #ifdef I2C1_SCL_PG4_AF3
    {PG4, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 3},
    #endif
    #ifdef I2C2_SCL_PE4_AF3
    {PE4, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 3},
    #endif
    #ifdef I2C3_SCL_PD0_AF3
    {PD0, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 3},
    #endif
    #ifdef I2C3_SCL_PG0_AF3
    {PG0, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 3},
    #endif
    #ifdef I2C4_SCL_PG2_AF3
    {PG2, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 3},
    #endif
    #ifdef I2C5_SCL_PB6_AF3
    {PB6, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 3},
    #endif
    #ifdef I2C2_SCL_PF6_AF3
    {PF6, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 3},
    #endif
    #ifdef I2C5_SCL_PG6_AF3
    {PG6, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 3},
    #endif
    #ifdef I2C0_SCL_PB2_AF2
    {PB2, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C1_SCL_PG0_AF2
    {PG0, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C2_SCL_PG2_AF2
    {PG2, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SCL_PL1_AF2
    {PL1, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SCL_PN5_AF3
    {PN5, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 3},
    #endif
    #ifdef I2C2_SCL_PP5_AF2
    {PP5, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C3_SCL_PG4_AF2
    {PG4, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C3_SCL_PK4_AF2
    {PK4, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C4_SCL_PG6_AF2
    {PG6, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 2},
    #endif
    #ifdef I2C4_SCL_PK6_AF2
    {PK6, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 2},
    #endif
    #ifdef I2C5_SCL_PB0_AF2
    {PB0, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 2},
    #endif
    #ifdef I2C5_SCL_PB4_AF2
    {PB4, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 2},
    #endif
    #ifdef I2C6_SCL_PA6_AF2
    {PA6, HAL_LL_I2C6_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_6), 2},
    #endif
    #ifdef I2C7_SCL_PA4_AF2
    {PA4, HAL_LL_I2C7_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_7), 2},
    #endif
    #ifdef I2C7_SCL_PD0_AF2
    {PD0, HAL_LL_I2C7_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_7), 2},
    #endif
    #ifdef I2C8_SCL_PA2_AF2
    {PA2, HAL_LL_I2C8_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_8), 2},
    #endif
    #ifdef I2C8_SCL_PD2_AF2
    {PD2, HAL_LL_I2C8_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_8), 2},
    #endif
    #ifdef I2C9_SCL_PA0_AF2
    {PA0, HAL_LL_I2C9_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_9), 2},
    #endif
    #ifdef I2C1_SCL_PR0_AF2
    {PR0, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C2_SCL_PR2_AF2
    {PR2, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C3_SCL_PR4_AF2
    {PR4, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C4_SCL_PR6_AF2
    {PR6, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 2},
    #endif
    #ifdef I2C6_SCL_PB6_AF2
    {PB6, HAL_LL_I2C6_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_6), 2},
    #endif
    #ifdef I2C9_SCL_PE6_AF2
    {PE6, HAL_LL_I2C9_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_9), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< I2C SDA Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    #ifdef I2C0_SDA_PB3_AF3
    {PB3, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_0), 3},
    #endif
    #ifdef I2C1_SDA_PA7_AF3
    {PA7, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 3},
    #endif
    #ifdef I2C1_SDA_PG5_AF3
    {PG5, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 3},
    #endif
    #ifdef I2C2_SDA_PE5_AF3
    {PE5, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 3},
    #endif
    #ifdef I2C3_SDA_PD1_AF3
    {PD1, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 3},
    #endif
    #ifdef I2C3_SDA_PG1_AF3
    {PG1, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 3},
    #endif
    #ifdef I2C4_SDA_PG3_AF3
    {PG3, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 3},
    #endif
    #ifdef I2C5_SDA_PB7_AF3
    {PB7, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 3},
    #endif
    #ifdef I2C2_SDA_PF7_AF3
    {PF7, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 3},
    #endif
    #ifdef I2C5_SDA_PG7_AF3
    {PG7, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 3},
    #endif
    #ifdef I2C0_SDA_PB3_AF2
    {PB3, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C1_SDA_PG1_AF2
    {PG1, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C2_SDA_PG3_AF2
    {PG3, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SDA_PL0_AF2
    {PL0, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SDA_PN4_AF3
    {PN4, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 3},
    #endif
    #ifdef I2C3_SDA_PG5_AF2
    {PG5, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C3_SDA_PK5_AF2
    {PK5, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C4_SDA_PG7_AF2
    {PG7, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 2},
    #endif
    #ifdef I2C4_SDA_PK7_AF2
    {PK7, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 2},
    #endif
    #ifdef I2C5_SDA_PB1_AF2
    {PB1, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 2},
    #endif
    #ifdef I2C5_SDA_PB5_AF2
    {PB5, HAL_LL_I2C5_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_5), 2},
    #endif
    #ifdef I2C6_SDA_PA7_AF2
    {PA7, HAL_LL_I2C6_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_6), 2},
    #endif
    #ifdef I2C7_SDA_PA5_AF2
    {PA5, HAL_LL_I2C7_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_7), 2},
    #endif
    #ifdef I2C7_SDA_PD1_AF2
    {PD1, HAL_LL_I2C7_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_7), 2},
    #endif
    #ifdef I2C8_SDA_PA3_AF2
    {PA3, HAL_LL_I2C8_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_8), 2},
    #endif
    #ifdef I2C8_SDA_PD3_AF2
    {PD3, HAL_LL_I2C8_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_8), 2},
    #endif
    #ifdef I2C9_SDA_PA1_AF2
    {PA1, HAL_LL_I2C9_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_9), 2},
    #endif
    #ifdef I2C1_SDA_PR1_AF2
    {PR1, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C2_SDA_PP6_AF2
    {PP6, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SDA_PR3_AF2
    {PR3, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C3_SDA_PR5_AF2
    {PR5, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C4_SDA_PR7_AF2
    {PR7, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), 2},
    #endif
    #ifdef I2C6_SDA_PB7_AF2
    {PB7, HAL_LL_I2C6_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_6), 2},
    #endif
    #ifdef I2C9_SDA_PE7_AF2
    {PE7, HAL_LL_I2C9_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_9), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
