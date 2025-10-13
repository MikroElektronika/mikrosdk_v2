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

#ifdef I2C_MODULE_0
static const hal_ll_base_addr_t HAL_LL_I2C0_BASE_ADDR = 0x40080000UL;
#endif
#ifdef I2C_MODULE_1
static const hal_ll_base_addr_t HAL_LL_I2C1_BASE_ADDR = 0x40081000UL;
#endif
#ifdef I2C_MODULE_2
static const hal_ll_base_addr_t HAL_LL_I2C2_BASE_ADDR = 0x40082000UL;
#endif

/*!< I2C AF NUMBERS */
#define HAL_LL_I2C_GPIO_AF3    3
#define HAL_LL_I2C_GPIO_AF4    4
#define HAL_LL_I2C_GPIO_AF5    5
#define HAL_LL_I2C_GPIO_AF6    6
#define HAL_LL_I2C_GPIO_AF7    7
#define HAL_LL_I2C_GPIO_AF8    8
#define HAL_LL_I2C_GPIO_AF9    9

/*!< @brief I2C pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    uint8_t af;
} hal_ll_i2c_pin_map_t;

/*!< I2C SCL Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] = {
    
    #ifdef I2C_MODULE_0
    #ifdef I2C0_SCL_PC12_AF4
    {GPIO_PC12, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SCL_PD7_AF4
    {GPIO_PD7, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SCL_PE13_AF4
    {GPIO_PE13, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SCL_PF3_AF4
    {GPIO_PF3, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SCL_PB5_AF6
    {GPIO_PB5, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF6},
    #endif
    #ifdef I2C0_SCL_PA5_AF9
    {GPIO_PA5, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C0_SCL_PC1_AF9
    {GPIO_PC1, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF9},
    #endif
    #endif

    #ifdef I2C_MODULE_1
    #ifdef I2C1_SCL_PF0_AF3
    {GPIO_PF0, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF3},
    #endif
    #ifdef I2C1_SCL_PA12_AF4
    {GPIO_PA12, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PD5_AF4
    {GPIO_PD5, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C1_SCL_PG2_AF5
    {GPIO_PG2, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF5},
    #endif
    #ifdef I2C1_SCL_PB11_AF7
    {GPIO_PB11, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF7},
    #endif
    #ifdef I2C1_SCL_PA7_AF8
    {GPIO_PA7, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF8},
    #endif
    #ifdef I2C1_SCL_PE1_AF8
    {GPIO_PE1, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF8},
    #endif
    #ifdef I2C1_SCL_PA3_AF9
    {GPIO_PA3, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C1_SCL_PB1_AF9
    {GPIO_PB1, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C1_SCL_PC5_AF9
    {GPIO_PC5, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF9},
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SCL_PD9_AF3
    {GPIO_PD9, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF3},
    #endif
    #ifdef I2C2_SCL_PA14_AF6
    {GPIO_PA14, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF6},
    #endif
    #ifdef I2C2_SCL_PD1_AF6
    {GPIO_PD1, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF6},
    #endif
    #ifdef I2C2_SCL_PA11_AF7
    {GPIO_PA11, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF7},
    #endif
    #ifdef I2C2_SCL_PB13_AF8
    {GPIO_PB13, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF8},
    #endif
    #ifdef I2C2_SCL_PA1_AF9
    {GPIO_PA1, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C2_SCL_PH8_AF9
    {GPIO_PH8, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF9},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< I2C SDA Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    
    #ifdef I2C_MODULE_0
    #ifdef I2C0_SDA_PC8_AF4
    {GPIO_PC8, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SDA_PC11_AF4
    {GPIO_PC11, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SDA_PD6_AF4
    {GPIO_PD6, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SDA_PF2_AF4
    {GPIO_PF2, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C0_SDA_PB4_AF6
    {GPIO_PB4, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF6},
    #endif
    #ifdef I2C0_SDA_PA4_AF9
    {GPIO_PA4, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C0_SDA_0_AF9
    {GPIO_PC0, HAL_LL_I2C0_BASE_ADDR, I2C_MODULE_0, HAL_LL_I2C_GPIO_AF9},
    #endif
    #endif

    #ifdef I2C_MODULE_1
    #ifdef I2C1_SDA_PF1_AF3
    {GPIO_PF1, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF3},
    #endif
    #ifdef I2C1_SDA_PA13_AF4
    {GPIO_PA13, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PD4_AF4
    {GPIO_PD4, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF4},
    #endif
    #ifdef I2C1_SDA_PG3_AF5
    {GPIO_PG3, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF5},
    #endif
    #ifdef I2C1_SDA_PB10_AF7
    {GPIO_PB10, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF7},
    #endif
    #ifdef I2C1_SDA_PA6_AF8
    {GPIO_PA6, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF8},
    #endif
    #ifdef I2C1_SDA_PE0_AF8
    {GPIO_PE0, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF8},
    #endif
    #ifdef I2C1_SDA_PA2_AF9
    {GPIO_PA2, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C1_SDA_PB0_AF9
    {GPIO_PB0, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C1_SDA_PC4_AF9
    {GPIO_PC4, HAL_LL_I2C1_BASE_ADDR, I2C_MODULE_1, HAL_LL_I2C_GPIO_AF9},
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SDA_PD8_AF3
    {GPIO_PD8, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF3},
    #endif
    #ifdef I2C2_SDA_PA15_AF6
    {GPIO_PA15, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF6},
    #endif
    #ifdef I2C2_SDA_PD0_AF6
    {GPIO_PD0, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF6},
    #endif
    #ifdef I2C2_SDA_PA10_AF7
    {GPIO_PA10, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF7},
    #endif
    #ifdef I2C2_SDA_PB12_AF8
    {GPIO_PB12, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF8},
    #endif
    #ifdef I2C2_SDA_PA0_AF9
    {GPIO_PA0, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF9},
    #endif
    #ifdef I2C2_SDA_PH9_AF9
    {GPIO_PH9, HAL_LL_I2C2_BASE_ADDR, I2C_MODULE_2, HAL_LL_I2C_GPIO_AF9},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END