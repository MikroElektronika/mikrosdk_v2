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
/*

  This file is part of mikroSDK.

  Copyright (c) ${COPYRIGHT_YEAR}, MikroElektronika - www.mikroe.com

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
    uint8_t module_index;
} hal_ll_i2c_pin_map_t;

/*!< @brief I2C SCL pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] = {
    //------------ BEGIN SCL
    #ifdef I2C_MODULE
    #endif

    #ifdef I2C_MODULE_1
    #ifdef I2C1_SCL_RB8
    { GPIO_PB8, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RG2
    { GPIO_PG2, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RD10
    { GPIO_PD10, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RA14
    { GPIO_PA14, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SCL_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RF5
    { GPIO_PF5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RA2
    { GPIO_PA2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #endif

    #ifdef I2C_MODULE_3
    #ifdef I2C3_SCL_RD3
    { GPIO_PD3, hal_ll_i2c_module_num(I2C_MODULE_3) },
    #endif
    #ifdef I2C3_SCL_RF8
    { GPIO_PF8, hal_ll_i2c_module_num(I2C_MODULE_3) },
    #endif
    #endif

    #ifdef I2C_MODULE_4
    #ifdef I2C4_SCL_RG8
    { GPIO_PG8, hal_ll_i2c_module_num(I2C_MODULE_4) },
    #endif
    #endif

    #ifdef I2C_MODULE_5
    #ifdef I2C5_SCL_RF5
    { GPIO_PF5, hal_ll_i2c_module_num(I2C_MODULE_5) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    //------------ BEGIN SDA
    #ifdef I2C_MODULE
    #endif

    #ifdef I2C_MODULE_1
    #ifdef I2C1_SDA_RB9
    { GPIO_PB9, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RG3
    { GPIO_PG3, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RD9
    { GPIO_PD9, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RA15
    { GPIO_PA15, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SDA_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RF4
    { GPIO_PF4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RA3
    { GPIO_PA3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #endif

    #ifdef I2C_MODULE_3
    #ifdef I2C3_SDA_RD2
    { GPIO_PD2, hal_ll_i2c_module_num(I2C_MODULE_3) },
    #endif
    #ifdef I2C3_SDA_RF2
    { GPIO_PF2, hal_ll_i2c_module_num(I2C_MODULE_3) },
    #endif
    #endif

    #ifdef I2C_MODULE_4
    #ifdef I2C4_SDA_RG7
    { GPIO_PG7, hal_ll_i2c_module_num(I2C_MODULE_4) },
    #endif
    #endif

    #ifdef I2C_MODULE_5
    #ifdef I2C5_SDA_RF4
    { GPIO_PF4, hal_ll_i2c_module_num(I2C_MODULE_5) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ---------------------------------------------------------------------- END
