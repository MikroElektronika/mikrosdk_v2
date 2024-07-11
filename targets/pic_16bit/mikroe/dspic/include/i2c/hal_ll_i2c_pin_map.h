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

/*!< @brief Pin function structure */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t module_index;
} hal_ll_i2c_pin_map_t;

/*!< @brief I2C SCL pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] = {
    //------------ BEGIN SCL
    #ifdef I2C_SCL_RB4
    {PB4, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SCL_RF3
    {PF3, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SCL_RG2
    {PG2, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C1_RB8_SCL1_ALT
    {PB8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RC5_SCL1
    {PC5, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB4_SCL2
    {PB4, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RB6_SCL2_ALT
    {PB6, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG7_SCL1_ALT
    {PG7, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RB6_SCL1
    {PB6, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB15_SCL2
    {PB15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RB3_SCL2_ALT
    {PB3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RC8_SCL1_ALT
    {PC8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RD10_SCL1_ALT
    {PD10, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RF5_SCL2
    {PF5, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RA2_SCL2_ALT
    {PA2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG2_SCL1
    {PG2, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SCL_RB6_ALT
    {PB6, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SCL_RB8
    {PB8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SCL_RG2
    {PG2, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_SCL_RF5
    {PF5, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_SCL_RA2
    {PA2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C_SCL_RB6
    {PB6, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C2_SCL_RA14
    {PA14, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RB8_SCL1
    {PB8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB3_SCL2
    {PB3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C3_RE6_SCL3
    {PE6, hal_ll_i2c_module_num(I2C_MODULE_3)},
    #endif
    #ifdef I2C2_RA2_SCL2
    {PA2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RD10_SCL1
    {PD10, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RA14_SCL1
    {PA14, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RA14_SCL2
    {PA14, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RA1_SCL1
    {PA1, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    //------------ BEGIN SDA
    #ifdef I2C_SDA_RB5
    {PB5, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SDA_RF2
    {PF2, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SDA_RG3
    {PG3, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C1_RB9_SDA1_ALT
    {PB9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RC4_SDA1
    {PC4, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RA8_SDA2
    {PA8, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RB5_SDA2_ALT
    {PB5, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG8_SDA1_ALT
    {PG8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RB7_SDA1
    {PB7, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB8_SDA2
    {PB8, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RC7_SDA1_ALT
    {PC7, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RC15_SDA2_ALT
    {PC15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RD9_SDA1_ALT
    {PD9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RF4_SDA2
    {PF4, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RA3_SDA2_ALT
    {PA3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG3_SDA1
    {PG3, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RB5_SDA1
    {PB5, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SDA_RB5_ALT
    {PB5, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SDA_RB9
    {PB9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SDA_RG3
    {PG3, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_SDA_RF4
    {PF4, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_SDA_RA3
    {PA3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C_SDA_RB7
    {PB7, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C2_SDA_RA15
    {PA15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RB9_SDA1
    {PB9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB2_SDA2
    {PB2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C3_RE7_SDA3
    {PE7, hal_ll_i2c_module_num(I2C_MODULE_3)},
    #endif
    #ifdef I2C2_RA3_SDA2
    {PA3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RD9_SDA1
    {PD9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RA15_SDA1
    {PA15, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RA15_SDA2
    {PA15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RA0_SDA1
    {PA0, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
