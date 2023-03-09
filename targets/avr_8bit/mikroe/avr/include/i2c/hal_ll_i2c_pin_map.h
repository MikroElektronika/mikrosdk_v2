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
/*

  This file is part of mikroSDK.

  Copyright (c) 2023, MikroElektonika - www.mikroe.com

  All rights reserved.

-------------------------------------------------------------------------- */
/*!
 * @file  hal_ll_i2c_pin_map.h
 * @brief I2C HAL LOW LEVEL PIN MAPS.
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

/*!< @brief Pin function structure */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
} hal_ll_i2c_pin_map_t;

/*!< @brief I2C SCL pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] = {
    //------------ BEGIN SCL
    #ifdef TWI0_SCL_PD0
    {PD0, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI0_SCL_PC0
    {PC0, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI0_SCL_PC5
    {PC5, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI0_SCL0_PC0
    {PC0, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI1_SCL1_PE6
    {PE6, HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_1)},
    #endif
    #ifdef TWI1_SCL_PE1
    {PE1, HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_1)},
    #endif
    #ifdef TWIC_SCL_PC1
    {PC1, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_C)},
    #endif
    #ifdef TWID_SCL_PD1
    {PD1, HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_D)},
    #endif
    #ifdef TWIE_SCL_PE1
    {PE1, HAL_LL_I2C2_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_E)},
    #endif
    #ifdef TWIF_SCL_PF1
    {PF1, HAL_LL_I2C3_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_F)},
    #endif
    #ifdef TWIC_SCL_PD1
    {PD1, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_C)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    //------------ BEGIN SDA
    #ifdef TWI0_SDA_PD1
    {PD1, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI0_SDA_PC1
    {PC1, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI0_SDA_PC4
    {PC4, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI0_SDA0_PC1
    {PC1, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_0)},
    #endif
    #ifdef TWI1_SDA1_PE5
    {PE5, HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_1)},
    #endif
    #ifdef TWI1_SDA_PE0
    {PE0, HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_1)},
    #endif
    #ifdef TWIC_SDA_PC0
    {PC0, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_C)},
    #endif
    #ifdef TWID_SDA_PD0
    {PD0, HAL_LL_I2C1_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_D)},
    #endif
    #ifdef TWIE_SDA_PE0
    {PE0, HAL_LL_I2C2_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_E)},
    #endif
    #ifdef TWIF_SDA_PF0
    {PF0, HAL_LL_I2C3_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_F)},
    #endif
    #ifdef TWIC_SDA_PD0
    {PD0, HAL_LL_I2C0_BASE_ADDRESS, hal_ll_i2c_module_num(TWI_MODULE_C)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ---------------------------------------------------------------------- END
