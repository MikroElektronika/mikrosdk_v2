/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief I2C module base addresses */
#ifdef I2C_MODULE_1
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = 0x40005400;
#endif
#ifdef I2C_MODULE_2
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE_ADDR = 0x40005800;
#endif
#ifdef I2C_MODULE_3
static const hal_ll_base_addr_t HAL_LL_I2C3_BASE_ADDR = 0x40005C00;
#endif
#ifdef I2C_MODULE_4
#if defined(STM32F7xx)
static const hal_ll_base_addr_t HAL_LL_I2C4_BASE_ADDR = 0x40006000;
#elif defined(STM32H7xx)
static const hal_ll_base_addr_t HAL_LL_I2C4_BASE_ADDR = 0x58001C00;
#elif defined(STM32L4xx)
static const hal_ll_base_addr_t HAL_LL_I2C4_BASE_ADDR = 0x40008400;
#endif
#endif

/*!< @brief I2C module alternate functions */
#ifdef I2C_MODULE_1
static const uint8_t HAL_LL_I2C1_GPIO_AF1 = 1;
static const uint8_t HAL_LL_I2C1_GPIO_AF3 = 3;
static const uint8_t HAL_LL_I2C1_GPIO_AF4 = 4;
static const uint8_t HAL_LL_I2C1_GPIO_AF5 = 5;
static const uint8_t HAL_LL_I2C1_GPIO_AF6 = 6;
#endif
#ifdef I2C_MODULE_2
static const uint8_t HAL_LL_I2C2_GPIO_AF1 = 1;
static const uint8_t HAL_LL_I2C2_GPIO_AF4 = 4;
static const uint8_t HAL_LL_I2C2_GPIO_AF5 = 5;
static const uint8_t HAL_LL_I2C2_GPIO_AF6 = 6;
#endif
#ifdef I2C_MODULE_3
static const uint8_t HAL_LL_I2C3_GPIO_AF3 = 3;
static const uint8_t HAL_LL_I2C3_GPIO_AF4 = 4;
static const uint8_t HAL_LL_I2C3_GPIO_AF7 = 7;
static const uint8_t HAL_LL_I2C3_GPIO_AF8 = 8;
static const uint8_t HAL_LL_I2C3_GPIO_AF9 = 9;
#endif
#ifdef I2C_MODULE_4
static const uint8_t HAL_LL_I2C4_GPIO_AF3 = 3;
static const uint8_t HAL_LL_I2C4_GPIO_AF4 = 4;
static const uint8_t HAL_LL_I2C4_GPIO_AF6 = 6;
static const uint8_t HAL_LL_I2C4_GPIO_AF11 = 11;
#endif

/*!< @brief Pin function structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    uint8_t af;
} hal_ll_i2c_pin_map_t;

/*!< @brief I2C SCL pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] =
{
    //------------ BEGIN SCL
    #ifdef I2C_MODULE_1
    #ifdef I2C1_SCL_PA11_AF5
    {PA11, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PA15_AF4
    {PA15, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PA4_AF3
    {PA4, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF3},
    #endif
    #ifdef I2C1_SCL_PA9_AF1
    {PA9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SCL_PA9_AF3
    {PA9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF3},
    #endif
    #ifdef I2C1_SCL_PA9_AF4
    {PA9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PA9_AF5
    {PA9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PA9_AF6
    {PA9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF6},
    #endif
    #ifdef I2C1_SCL_PB10_AF4
    {PB10, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PB10_AF5
    {PB10, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PB13_AF5
    {PB13, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PB6_AF1
    {PB6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SCL_PB6_AF3
    {PB6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF3},
    #endif
    #ifdef I2C1_SCL_PB6_AF4
    {PB6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PB6_AF5
    {PB6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PB6_AF6
    {PB6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF6},
    #endif
    #ifdef I2C1_SCL_PB8_AF1
    {PB8, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SCL_PB8_AF3
    {PB8, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF3},
    #endif
    #ifdef I2C1_SCL_PB8_AF4
    {PB8, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PB8_AF5
    {PB8, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PB8_AF6
    {PB8, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF6},
    #endif
    #ifdef I2C1_SCL_PF1_AF4
    {PF1, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PF1_AF5
    {PF1, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PF6_AF4
    {PF6, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PG14_AF4
    {PG14, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SCL_PA11_AF5
    {PA11, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF5},
    #endif
    #ifdef I2C2_SCL_PA11_AF6
    {PA11, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF6},
    #endif
    #ifdef I2C2_SCL_PA9_AF4
    {PA9, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SCL_PB10_AF1
    {PB10, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF1},
    #endif
    #ifdef I2C2_SCL_PB10_AF4
    {PB10, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SCL_PB10_AF5
    {PB10, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF5},
    #endif
    #ifdef I2C2_SCL_PB10_AF6
    {PB10, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF6},
    #endif
    #ifdef I2C2_SCL_PB13_AF1
    {PB13, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF1},
    #endif
    #ifdef I2C2_SCL_PB13_AF4
    {PB13, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SCL_PB13_AF5
    {PB13, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF5},
    #endif
    #ifdef I2C2_SCL_PB13_AF6
    {PB13, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF6},
    #endif
    #ifdef I2C2_SCL_PF1_AF4
    {PF1, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SCL_PF6_AF1
    {PF6, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF1},
    #endif
    #ifdef I2C2_SCL_PF6_AF4
    {PF6, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SCL_PH4_AF4
    {PH4, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #endif

    #ifdef I2C_MODULE_3
    #ifdef I2C3_SCL_PA7_AF4
    {PA7, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SCL_PA8_AF3
    {PA8, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF3},
    #endif
    #ifdef I2C3_SCL_PA8_AF4
    {PA8, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SCL_PA8_AF7
    {PA8, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF7},
    #endif
    #ifdef I2C3_SCL_PC0_AF4
    {PC0, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SCL_PC0_AF7
    {PC0, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF7},
    #endif
    #ifdef I2C3_SCL_PG7_AF4
    {PG7, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SCL_PH7_AF4
    {PH7, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #endif

    #ifdef I2C_MODULE_4
    #ifdef I2C4_SCL_PD12_AF11
    {PD12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF11},
    #endif
    #ifdef I2C4_SCL_PD12_AF3
    {PD12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF3},
    #endif
    #ifdef I2C4_SCL_PD12_AF4
    {PD12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF4},
    #endif
    #ifdef I2C4_SCL_PD12_AF6
    {PD12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF6},
    #endif
    #ifdef I2C4_SCL_PF14_AF11
    {PF14, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF11},
    #endif
    #ifdef I2C4_SCL_PF14_AF3
    {PF14, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF3},
    #endif
    #ifdef I2C4_SCL_PF14_AF4
    {PF14, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF4},
    #endif
    #ifdef I2C4_SCL_PF14_AF6
    {PF14, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF6},
    #endif
    #ifdef I2C4_SCL_PH11_AF11
    {PH11, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF11},
    #endif
    #ifdef I2C4_SCL_PH11_AF4
    {PH11, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF4},
    #endif
    #ifdef I2C4_SCL_PH11_AF6
    {PH11, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF6},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] =
{
    //------------ BEGIN SDA
    #ifdef I2C_MODULE_1
    #ifdef I2C1_SDA_PA10_AF1
    {PA10, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SDA_PA10_AF4
    {PA10, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PA10_AF6
    {PA10, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF6},
    #endif
    #ifdef I2C1_SDA_PA12_AF4
    {PA12, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PA13_AF1
    {PA13, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SDA_PA14_AF4
    {PA14, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PB11_AF4
    {PB11, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PB14_AF4
    {PB14, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PB7_AF1
    {PB7, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SDA_PB7_AF4
    {PB7, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PB7_AF6
    {PB7, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF6},
    #endif
    #ifdef I2C1_SDA_PB9_AF1
    {PB9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF1},
    #endif
    #ifdef I2C1_SDA_PB9_AF4
    {PB9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PB9_AF6
    {PB9, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF6},
    #endif
    #ifdef I2C1_SDA_PF0_AF4
    {PF0, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PF7_AF4
    {PF7, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_1), HAL_LL_I2C1_GPIO_AF4},
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C1_SDA_PG13_AF4
    {PG13, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PA10_AF4
    {PA10, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PA12_AF5
    {PA12, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF5},
    #endif
    #ifdef I2C2_SDA_PA12_AF6
    {PA12, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF6},
    #endif
    #ifdef I2C2_SDA_PB11_AF1
    {PB11, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF1},
    #endif
    #ifdef I2C2_SDA_PB11_AF4
    {PB11, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PB11_AF5
    {PB11, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF5},
    #endif
    #ifdef I2C2_SDA_PB11_AF6
    {PB11, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF6},
    #endif
    #ifdef I2C2_SDA_PB14_AF1
    {PB14, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF1},
    #endif
    #ifdef I2C2_SDA_PB14_AF4
    {PB14, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PB14_AF5
    {PB14, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF5},
    #endif
    #ifdef I2C2_SDA_PB14_AF6
    {PB14, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF6},
    #endif
    #ifdef I2C2_SDA_PB3_AF4
    {PB3, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PC12_AF4
    {PC12, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PF0_AF4
    {PF0, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PF7_AF1
    {PF7, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF1},
    #endif
    #ifdef I2C2_SDA_PF7_AF4
    {PF7, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #ifdef I2C2_SDA_PH5_AF4
    {PH5, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_2), HAL_LL_I2C2_GPIO_AF4},
    #endif
    #endif

    #ifdef I2C_MODULE_3
    #ifdef I2C3_SDA_PB4_AF4
    {PB4, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SDA_PB4_AF7
    {PB4, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF7},
    #endif
    #ifdef I2C3_SDA_PB4_AF9
    {PB4, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF9},
    #endif
    #ifdef I2C3_SDA_PB5_AF8
    {PB5, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF8},
    #endif
    #ifdef I2C3_SDA_PC1_AF4
    {PC1, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SDA_PC1_AF7
    {PC1, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF7},
    #endif
    #ifdef I2C3_SDA_PC9_AF4
    {PC9, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SDA_PC9_AF7
    {PC9, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF7},
    #endif
    #ifdef I2C3_SDA_PC9_AF8
    {PC9, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF8},
    #endif
    #ifdef I2C3_SDA_PC9_AF9
    {PC9, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF9},
    #endif
    #ifdef I2C3_SDA_PG8_AF4
    {PG8, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #ifdef I2C3_SDA_PH8_AF4
    {PH8, HAL_LL_I2C3_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_3), HAL_LL_I2C3_GPIO_AF4},
    #endif
    #endif

    #ifdef I2C_MODULE_4
    #ifdef I2C4_SDA_PD13_AF11
    {PD13, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF11},
    #endif
    #ifdef I2C4_SDA_PD13_AF3
    {PD13, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF3},
    #endif
    #ifdef I2C4_SDA_PD13_AF4
    {PD13, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF4},
    #endif
    #ifdef I2C4_SDA_PD13_AF6
    {PD13, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF6},
    #endif
    #ifdef I2C4_SDA_PF15_AF11
    {PF15, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF11},
    #endif
    #ifdef I2C4_SDA_PF15_AF3
    {PF15, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF3},
    #endif
    #ifdef I2C4_SDA_PF15_AF4
    {PF15, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF4},
    #endif
    #ifdef I2C4_SDA_PF15_AF6
    {PF15, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF6},
    #endif
    #ifdef I2C4_SDA_PH12_AF11
    {PH12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF11},
    #endif
    #ifdef I2C4_SDA_PH12_AF4
    {PH12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF4},
    #endif
    #ifdef I2C4_SDA_PH12_AF6
    {PH12, HAL_LL_I2C4_BASE_ADDR, hal_ll_i2c_module_num(I2C_MODULE_4), HAL_LL_I2C4_GPIO_AF6},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
