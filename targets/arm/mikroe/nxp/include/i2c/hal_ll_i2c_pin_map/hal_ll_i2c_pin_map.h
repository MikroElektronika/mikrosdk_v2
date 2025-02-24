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

/*!< I2C module base addresses. */
#ifdef I2C_MODULE_0
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE = 0x40066000;
#endif

#ifdef I2C_MODULE_1
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE = 0x40067000;
#endif

#ifdef I2C_MODULE_2
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE = 0x400E6000;
#endif

#ifdef I2C_MODULE_3
static const hal_ll_base_addr_t HAL_LL_I2C3_BASE = 0x400E7000;
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
    #ifdef I2C0_SCL_PB0_AF2
    {GPIO_PB0, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C0_SCL_PB2_AF2
    {GPIO_PB2, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C1_SCL_PE1_AF6
    {GPIO_PE1, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    #ifdef I2C1_SCL_PC10_AF2
    {GPIO_PC10, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C0_SCL_PD2_AF7
    {GPIO_PD2, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 7},
    #endif
    #ifdef I2C0_SCL_PE24_AF5
    {GPIO_PE24, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 5},
    #endif
    #ifdef I2C2_SCL_PA12_AF5
    {GPIO_PA12, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 5},
    #endif
    #ifdef I2C2_SCL_PA14_AF5
    {GPIO_PA14, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 5},
    #endif
    #ifdef I2C0_SCL_PD8_AF2
    {GPIO_PD8, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C3_SCL_PE11_AF2
    {GPIO_PE11, HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C0_SCL_PE19_AF4
    {GPIO_PE19, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 4},
    #endif
    #ifdef I2C3_SCL_PA2_AF4
    {GPIO_PA2, HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), 4},
    #endif
    #ifdef I2C3_SCL_PC29_AF2
    {GPIO_PC29, HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C0_SCL_PA20_AF2
    {GPIO_PA20, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C2_SCL_PA11_AF2
    {GPIO_PA11, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SCL_PB10_AF4
    {GPIO_PB10, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 4},
    #endif
    #ifdef I2C2_SCL_PA6_AF2
    {GPIO_PA6, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C0_SCL_PC6_AF7
    {GPIO_PC6, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 7},
    #endif
    #ifdef I2C0_SCL_PC14_AF3
    {GPIO_PC14, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 3},
    #endif
    #ifdef I2C0_SCL_PA12_AF8
    {GPIO_PA12, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 8},
    #endif
    #ifdef I2C1_SCL_PA14_AF8
    {GPIO_PA14, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 8},
    #endif
    #ifdef I2C1_SCL_PC14_AF2
    {GPIO_PC14, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C1_SCL_PD8_AF2
    {GPIO_PD8, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< I2C SDA Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    #ifdef I2C0_SDA_PB1_AF2
    {GPIO_PB1, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C0_SDA_PB3_AF2
    {GPIO_PB3, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C1_SDA_PE0_AF6
    {GPIO_PE0, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    #ifdef I2C1_SDA_PC11_AF2
    {GPIO_PC11, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C0_SDA_PD3_AF7
    {GPIO_PD3, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 7},
    #endif
    #ifdef I2C0_SDA_PE25_AF5
    {GPIO_PE25, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 5},
    #endif
    #ifdef I2C2_SDA_PA13_AF5
    {GPIO_PA13, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 5},
    #endif
    #ifdef I2C2_SDA_PA11_AF5
    {GPIO_PA11, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 5},
    #endif
    #ifdef I2C0_SDA_PD9_AF2
    {GPIO_PD9, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C3_SDA_PE10_AF2
    {GPIO_PE10, HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C0_SDA_PE18_AF4
    {GPIO_PE18, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 4},
    #endif
    #ifdef I2C3_SDA_PA1_AF4
    {GPIO_PA1, HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), 4},
    #endif
    #ifdef I2C3_SDA_PC28_AF2
    {GPIO_PC28, HAL_LL_I2C3_BASE, hal_ll_i2c_module_num(I2C_MODULE_3), 2},
    #endif
    #ifdef I2C0_SDA_PA21_AF2
    {GPIO_PA21, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 2},
    #endif
    #ifdef I2C2_SDA_PA10_AF2
    {GPIO_PA10, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C2_SDA_PB11_AF4
    {GPIO_PB11, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 4},
    #endif
    #ifdef I2C2_SDA_PA7_AF2
    {GPIO_PA7, HAL_LL_I2C2_BASE, hal_ll_i2c_module_num(I2C_MODULE_2), 2},
    #endif
    #ifdef I2C0_SDA_PC7_AF7
    {GPIO_PC7, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 7},
    #endif
    #ifdef I2C0_SDA_PC15_AF3
    {GPIO_PC15, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 3},
    #endif
    #ifdef I2C1_SDA_PA13_AF8
    {GPIO_PA13, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 8},
    #endif
    #ifdef I2C1_SDA_PC15_AF2
    {GPIO_PC15, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif
    #ifdef I2C0_SDA_PA11_AF8
    {GPIO_PA11, HAL_LL_I2C0_BASE, hal_ll_i2c_module_num(I2C_MODULE_0), 8},
    #endif
    #ifdef I2C1_SDA_PD9_AF2
    {GPIO_PD9, HAL_LL_I2C1_BASE, hal_ll_i2c_module_num(I2C_MODULE_1), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
