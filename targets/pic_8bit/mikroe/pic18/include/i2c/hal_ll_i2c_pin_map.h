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
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t module_index;
} hal_ll_i2c_pin_map_t;

/*!< @brief I2C SCL pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] =
{
    //------------ BEGIN SCL
    #ifdef I2C_MODULE
    #ifdef I2C_SCL_RB1
    { GPIO_PB1, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB4
    { GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC3
    { GPIO_PC3, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB0
    { GPIO_PB0, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB5
    { GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB6
    { GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RB7
    { GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC0
    { GPIO_PC0, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC1
    { GPIO_PC1, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC2
    { GPIO_PC2, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC4
    { GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC5
    { GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC6
    { GPIO_PC6, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RC7
    { GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD0
    { GPIO_PD0, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD1
    { GPIO_PD1, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD2
    { GPIO_PD2, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD3
    { GPIO_PD3, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD4
    { GPIO_PD4, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD5
    { GPIO_PD5, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD6
    { GPIO_PD6, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SCL_RD7
    { GPIO_PD7, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #endif

    #ifdef I2C_MODULE_1
    #ifdef I2C1_SCL_RC3
    { GPIO_PC3, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB0
    { GPIO_PB0, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB1
    { GPIO_PB1, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB4
    { GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB5
    { GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB6
    { GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RB7
    { GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC0
    { GPIO_PC0, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC1
    { GPIO_PC1, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC2
    { GPIO_PC2, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC4
    { GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC5
    { GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC6
    { GPIO_PC6, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SCL_RC7
    { GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SCL_RB0
    { GPIO_PB0, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB1
    { GPIO_PB1, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB4
    { GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB5
    { GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB6
    { GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RB7
    { GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC0
    { GPIO_PC0, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC1
    { GPIO_PC1, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC2
    { GPIO_PC2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC3
    { GPIO_PC3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC4
    { GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC5
    { GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC6
    { GPIO_PC6, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RC7
    { GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD0
    { GPIO_PD0, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD1
    { GPIO_PD1, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD2
    { GPIO_PD2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD3
    { GPIO_PD3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD4
    { GPIO_PD4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD5
    { GPIO_PD5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD6
    { GPIO_PD6, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SCL_RD7
    { GPIO_PD7, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] =
{
    //------------ BEGIN SDA
    #ifdef I2C_MODULE
    #ifdef I2C_SDA_RB0
    { GPIO_PB0, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB5
    { GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC4
    { GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB1
    { GPIO_PB1, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB4
    { GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB6
    { GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RB7
    { GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC0
    { GPIO_PC0, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC1
    { GPIO_PC1, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC2
    { GPIO_PC2, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC3
    { GPIO_PC3, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC5
    { GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC6
    { GPIO_PC6, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #ifdef I2C_SDA_RC7
    { GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE) },
    #endif
    #endif

    #ifdef I2C_MODULE_1
    #ifdef I2C1_SDA_RC4
    { GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB0
    { GPIO_PB0, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB1
    { GPIO_PB1, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB4
    { GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB5
    { GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB6
    { GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RB7
    { GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC0
    { GPIO_PC0, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC1
    { GPIO_PC1, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC2
    { GPIO_PC2, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC3
    { GPIO_PC3, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC5
    { GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC6
    { GPIO_PC6, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #ifdef I2C1_SDA_RC7
    { GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE_1) },
    #endif
    #endif

    #ifdef I2C_MODULE_2
    #ifdef I2C2_SDA_RB0
    { GPIO_PB0, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB1
    { GPIO_PB1, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB2
    { GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB3
    { GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB4
    { GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB5
    { GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB6
    { GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RB7
    { GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC0
    { GPIO_PC0, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC1
    { GPIO_PC1, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC2
    { GPIO_PC2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC3
    { GPIO_PC3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC4
    { GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC5
    { GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC6
    { GPIO_PC6, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RC7
    { GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD1
    { GPIO_PD1, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD0
    { GPIO_PD0, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD2
    { GPIO_PD2, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD3
    { GPIO_PD3, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD4
    { GPIO_PD4, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD5
    { GPIO_PD5, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD6
    { GPIO_PD6, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #ifdef I2C2_SDA_RD7
    { GPIO_PD7, hal_ll_i2c_module_num(I2C_MODULE_2) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
