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

#ifdef I2C_MODULE_0
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = 0x40053000UL;
#endif
#ifdef I2C_MODULE_1
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = 0x40053100UL;
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
    #ifdef I2C0_SCL_P408_AF7
    {GPIO_P408, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C1_SCL_P100_AF7
    {GPIO_P100, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C0_SCL_P204_AF7
    {GPIO_P204, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C0_SCL_P400_AF7
    {GPIO_P400, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C1_SCL_P205_AF7
    {GPIO_P205, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< I2C SDA Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    #ifdef I2C0_SDA_P407_AF7
    {GPIO_P407, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C1_SDA_P101_AF7
    {GPIO_P101, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C0_SDA_P401_AF7
    {GPIO_P401, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C1_SDA_P206_AF7
    {GPIO_P206, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
