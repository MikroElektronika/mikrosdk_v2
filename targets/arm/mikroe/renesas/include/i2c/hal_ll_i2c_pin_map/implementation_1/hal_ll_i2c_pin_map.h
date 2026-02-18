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

/*!< @brief I2C pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    uint8_t af;
} hal_ll_i2c_pin_map_t;

/*!< I2C SCL Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_scl_map[] = {
    #ifdef I2C0_SCL_P204_AF7
    {GPIO_P204, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C0_SCL_P400_AF7
    {GPIO_P400, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C0_SCL_P408_AF7
    {GPIO_P408, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C1_SCL_P100_AF7
    {GPIO_P100, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C1_SCL_P205_AF7
    {GPIO_P205, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C2_SCL_P512_AF7
    {GPIO_P512, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), 7},
    #endif
    #ifdef I2C1_SCL_P512_AF7
    {GPIO_P512, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C0_SCL_P100_AF7
    {GPIO_P100, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C2_SCL_P410_AF7
    {GPIO_P410, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), 7},
    #endif
    #ifdef I2C2_SCL_P415_AF7
    {GPIO_P415, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), 7},
    #endif
    #ifdef I2C0_SCL_P410_AF7
    {GPIO_P410, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef SCI0_SCL_P100_AF4
    {GPIO_P100, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCL_P104_AF4
    {GPIO_P104, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCL_P206_AF4
    {GPIO_P206, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCL_P410_AF4
    {GPIO_P410, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SCL_P212_AF5
    {GPIO_P212, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SCL_P402_AF5
    {GPIO_P402, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SCL_P502_AF5
    {GPIO_P502, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCL_P301_AF4
    {GPIO_P301, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI9_SCL_P110_AF5
    {GPIO_P110, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SCL_P408_AF5
    {GPIO_P408, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI1_SCL_P708_AF5
    {GPIO_P708, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI9_SCL_P202_AF5
    {GPIO_P202, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SCL_P601_AF5
    {GPIO_P601, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI2_SCL_P113_AF4
    {GPIO_P113, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_SCL_P309_AF5
    {GPIO_P309, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_SCL_P408_AF5
    {GPIO_P408, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_SCL_P706_AF5
    {GPIO_P706, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_SCL_P206_AF4
    {GPIO_P206, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_SCL_P315_AF4
    {GPIO_P315, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_SCL_P511_AF4
    {GPIO_P511, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI5_SCL_P502_AF5
    {GPIO_P502, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI5_SCL_P513_AF5
    {GPIO_P513, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI6_SCL_P304_AF4
    {GPIO_P304, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI6_SCL_P505_AF4
    {GPIO_P505, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI7_SCL_P402_AF5
    {GPIO_P402, HAL_LL_SCI7_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI7_SCL_P614_AF5
    {GPIO_P614, HAL_LL_SCI7_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI8_SCL_P104_AF4
    {GPIO_P104, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI8_SCL_P607_AF4
    {GPIO_P607, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI0_SCL_P113_AF4
    {GPIO_P113, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCL_P610_AF4
    {GPIO_P610, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SCL_P401_AF5
    {GPIO_P401, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCL_P802_AF4
    {GPIO_P802, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI4_SCL_P414_AF4
    {GPIO_P414, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_SCL_P101_AF5
    {GPIO_P101, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SCL_P208_AF5
    {GPIO_P208, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI0_SCL_P602_AF4
    {GPIO_P602, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI2_SCL_P700_AF4
    {GPIO_P700, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI1_SCL_P706_AF5
    {GPIO_P706, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCL_PA02_AF4
    {GPIO_PA02, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_SCL_P901_AF5
    {GPIO_P901, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_SCL_P715_AF4
    {GPIO_P715, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_SCL_PA15_AF5
    {GPIO_PA15, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< I2C SDA Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    #ifdef I2C0_SDA_P401_AF7
    {GPIO_P401, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C0_SDA_P407_AF7
    {GPIO_P407, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C1_SDA_P101_AF7
    {GPIO_P101, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C1_SDA_P206_AF7
    {GPIO_P206, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C2_SDA_P511_AF7
    {GPIO_P511, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), 7},
    #endif
    #ifdef I2C1_SDA_P511_AF7
    {GPIO_P511, HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ), 7},
    #endif
    #ifdef I2C0_SDA_P101_AF7
    {GPIO_P101, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef I2C2_SDA_P409_AF7
    {GPIO_P409, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), 7},
    #endif
    #ifdef I2C2_SDA_P414_AF7
    {GPIO_P414, HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ), 7},
    #endif
    #ifdef I2C0_SDA_P409_AF7
    {GPIO_P409, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 7},
    #endif
    #ifdef SCI0_SDA_P101_AF4
    {GPIO_P101, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SDA_P205_AF4
    {GPIO_P205, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SDA_P411_AF4
    {GPIO_P411, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SDA_P213_AF5
    {GPIO_P213, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SDA_P401_AF5
    {GPIO_P401, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SDA_P501_AF5
    {GPIO_P501, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SDA_P102_AF4
    {GPIO_P102, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_SDA_P112_AF4
    {GPIO_P112, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_SDA_P302_AF4
    {GPIO_P302, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI9_SDA_P109_AF5
    {GPIO_P109, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SDA_P409_AF5
    {GPIO_P409, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SDA_P203_AF5
    {GPIO_P203, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SDA_P602_AF5
    {GPIO_P602, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI3_SDA_P310_AF5
    {GPIO_P310, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_SDA_P409_AF5
    {GPIO_P409, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_SDA_P707_AF5
    {GPIO_P707, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_SDA_P205_AF4
    {GPIO_P205, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_SDA_P512_AF4
    {GPIO_P512, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_SDA_P900_AF4
    {GPIO_P900, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI5_SDA_P501_AF5
    {GPIO_P501, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI5_SDA_P805_AF5
    {GPIO_P805, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI6_SDA_P305_AF4
    {GPIO_P305, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI6_SDA_P506_AF4
    {GPIO_P506, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI7_SDA_P401_AF5
    {GPIO_P401, HAL_LL_SCI7_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI7_SDA_P613_AF5
    {GPIO_P613, HAL_LL_SCI7_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI8_SDA_P105_AF4
    {GPIO_P105, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI8_SDA_PA00_AF4
    {GPIO_PA00, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI1_SDA_P709_AF5
    {GPIO_P709, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI4_SDA_P207_AF4
    {GPIO_P207, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI0_SDA_P112_AF4
    {GPIO_P112, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SDA_P609_AF4
    {GPIO_P609, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SDA_P400_AF5
    {GPIO_P400, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SDA_P406_AF4
    {GPIO_P406, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_SDA_P801_AF4
    {GPIO_P801, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI4_SDA_P415_AF4
    {GPIO_P415, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_SDA_P102_AF5
    {GPIO_P102, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SDA_P209_AF5
    {GPIO_P209, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI0_SDA_P603_AF4
    {GPIO_P603, HAL_LL_SCI0_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SDA_P707_AF5
    {GPIO_P707, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SDA_PA03_AF4
    {GPIO_PA03, HAL_LL_SCI2_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_SDA_P900_AF5
    {GPIO_P900, HAL_LL_SCI3_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_SDA_P714_AF4
    {GPIO_P714, HAL_LL_SCI4_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_SDA_PA14_AF5
    {GPIO_PA14, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
