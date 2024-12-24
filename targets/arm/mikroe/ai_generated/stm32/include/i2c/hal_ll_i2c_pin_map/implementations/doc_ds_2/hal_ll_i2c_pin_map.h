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

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_i2c_module_num(_module_num) (_module_num - 1)

/*!< @brief Pin function structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    uint8_t af;
} hal_ll_i2c_pin_map_t;

#ifdef I2C_MODULE_1
#define I2C1_BASE_ADDRESS (0x40005400UL)
#define I2C1_BASE_ADDR I2C1_BASE_ADDRESS
#define HAL_LL_I2C1_BASE_ADDR I2C1_BASE_ADDRESS
#define HAL_LL_I2C1_BASE_ADDRESS I2C1_BASE_ADDRESS
#endif

/*!< @brief I2C SCL pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] =
{
    #ifdef I2C1_SCL_PB6_AF6
    {GPIO_PB6, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    #ifdef I2C1_SCL_PB7_AF14
    {GPIO_PB7, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 14},
    #endif
    #ifdef I2C1_SCL_PB8_AF6
    {GPIO_PB8, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    #ifdef I2C1_SCL_PA9_AF6
    {GPIO_PA9, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] =
{
    #ifdef I2C1_SDA_PB7_AF6
    {GPIO_PB7, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    #ifdef I2C1_SDA_PC14_AF14
    {GPIO_PC14, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 14},
    #endif
    #ifdef I2C1_SDA_PA10_AF6
    {GPIO_PA10, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    #ifdef I2C1_SDA_PB9_AF6
    {GPIO_PB9, I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(I2C_MODULE_1), 6},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
