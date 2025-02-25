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
    {GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SCL_RF3
    {GPIO_PF3, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SCL_RG2
    {GPIO_PG2, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C1_RB8_SCL1_ALT
    {GPIO_PB8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RC5_SCL1
    {GPIO_PC5, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB4_SCL2
    {GPIO_PB4, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RB6_SCL2_ALT
    {GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG7_SCL1_ALT
    {GPIO_PG7, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RB6_SCL1
    {GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB15_SCL2
    {GPIO_PB15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RB3_SCL2_ALT
    {GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RC8_SCL1_ALT
    {GPIO_PC8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RD10_SCL1_ALT
    {GPIO_PD10, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RF5_SCL2
    {GPIO_PF5, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RA2_SCL2_ALT
    {GPIO_PA2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG2_SCL1
    {GPIO_PG2, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SCL_RB6_ALT
    {GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SCL_RB8
    {GPIO_PB8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SCL_RG2
    {GPIO_PG2, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_SCL_RF5
    {GPIO_PF5, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_SCL_RA2
    {GPIO_PA2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C_SCL_RB6
    {GPIO_PB6, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C2_SCL_RA14
    {GPIO_PA14, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RB8_SCL1
    {GPIO_PB8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB3_SCL2
    {GPIO_PB3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C3_RE6_SCL3
    {GPIO_PE6, hal_ll_i2c_module_num(I2C_MODULE_3)},
    #endif
    #ifdef I2C2_RA2_SCL2
    {GPIO_PA2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RD10_SCL1
    {GPIO_PD10, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RA14_SCL1
    {GPIO_PA14, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RA14_SCL2
    {GPIO_PA14, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RA1_SCL1
    {GPIO_PA1, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCL
};

/*!< @brief I2C SDA pins */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    //------------ BEGIN SDA
    #ifdef I2C_SDA_RB5
    {GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SDA_RF2
    {GPIO_PF2, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C_SDA_RG3
    {GPIO_PG3, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C1_RB9_SDA1_ALT
    {GPIO_PB9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RC4_SDA1
    {GPIO_PC4, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RA8_SDA2
    {GPIO_PA8, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RB5_SDA2_ALT
    {GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG8_SDA1_ALT
    {GPIO_PG8, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RB7_SDA1
    {GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB8_SDA2
    {GPIO_PB8, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RC7_SDA1_ALT
    {GPIO_PC7, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RC15_SDA2_ALT
    {GPIO_PC15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RD9_SDA1_ALT
    {GPIO_PD9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RF4_SDA2
    {GPIO_PF4, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_RA3_SDA2_ALT
    {GPIO_PA3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RG3_SDA1
    {GPIO_PG3, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RB5_SDA1
    {GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SDA_RB5_ALT
    {GPIO_PB5, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SDA_RB9
    {GPIO_PB9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_SDA_RG3
    {GPIO_PG3, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_SDA_RF4
    {GPIO_PF4, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C2_SDA_RA3
    {GPIO_PA3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C_SDA_RB7
    {GPIO_PB7, hal_ll_i2c_module_num(I2C_MODULE)},
    #endif
    #ifdef I2C2_SDA_RA15
    {GPIO_PA15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RB9_SDA1
    {GPIO_PB9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RB2_SDA2
    {GPIO_PB2, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C3_RE7_SDA3
    {GPIO_PE7, hal_ll_i2c_module_num(I2C_MODULE_3)},
    #endif
    #ifdef I2C2_RA3_SDA2
    {GPIO_PA3, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RD9_SDA1
    {GPIO_PD9, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C1_RA15_SDA1
    {GPIO_PA15, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    #ifdef I2C2_RA15_SDA2
    {GPIO_PA15, hal_ll_i2c_module_num(I2C_MODULE_2)},
    #endif
    #ifdef I2C1_RA0_SDA1
    {GPIO_PA0, hal_ll_i2c_module_num(I2C_MODULE_1)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SDA
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
