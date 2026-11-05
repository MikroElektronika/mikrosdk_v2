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
    #ifdef I2C0_SCL_PB01_AF15
    {GPIO_PB01, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 15},
    #endif
    #ifdef I3C0_SCL_PB01_AF50
    {GPIO_PB01, HAL_LL_I3C0_BASE_ADDR, hal_ll_i2c_module_num( I3C_MODULE_0 ), 50},
    #endif
    #ifdef SCI11_SCL_P903_AF45
    {GPIO_P903, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SCL_PA01_AF45
    {GPIO_PA01, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SCL_PB06_AF45
    {GPIO_PB06, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SCL_PD05_AF45
    {GPIO_PD05, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI12_SCL_P000_AF12
    {GPIO_P000, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SCL_P202_AF12
    {GPIO_P202, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SCL_P800_AF12
    {GPIO_P800, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SCL_PB04_AF12
    {GPIO_PB04, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SCL_PB06_AF12
    {GPIO_PB06, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SCL_PD06_AF12
    {GPIO_PD06, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI1_SCL_PD05_AF10
    {GPIO_PD05, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 10},
    #endif
    #ifdef SCI5_SCL_P307_AF10
    {GPIO_P307, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SCL_P901_AF10
    {GPIO_P901, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SCL_PB06_AF10
    {GPIO_PB06, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SCL_PE00_AF10
    {GPIO_PE00, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI6_SCL_P800_AF10
    {GPIO_P800, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SCL_P905_AF10
    {GPIO_P905, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SCL_PA05_AF10
    {GPIO_PA05, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SCL_PB01_AF10
    {GPIO_PB01, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI8_SCL_P200_AF45
    {GPIO_P200, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCL_P202_AF44
    {GPIO_P202, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_SCL_P905_AF45
    {GPIO_P905, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCL_PA05_AF45
    {GPIO_PA05, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCL_PD01_AF45
    {GPIO_PD01, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI9_SCL_P000_AF44
    {GPIO_P000, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SCL_PA02_AF45
    {GPIO_PA02, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 45},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< I2C SDA Pins. */
static const hal_ll_i2c_pin_map_t hal_ll_i2c_sda_map[] = {
    #ifdef I2C0_SDA_PB02_AF15
    {GPIO_PB02, HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ), 15},
    #endif
    #ifdef I3C0_SDA_PB02_AF50
    {GPIO_PB02, HAL_LL_I3C0_BASE_ADDR, hal_ll_i2c_module_num( I3C_MODULE_0 ), 50},
    #endif
    #ifdef SCI11_SDA_P902_AF45
    {GPIO_P902, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SDA_PA00_AF45
    {GPIO_PA00, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SDA_PB05_AF45
    {GPIO_PB05, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SDA_PD03_AF45
    {GPIO_PD03, HAL_LL_SCI11_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI12_SDA_P001_AF12
    {GPIO_P001, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SDA_P201_AF12
    {GPIO_P201, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SDA_P203_AF12
    {GPIO_P203, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SDA_P801_AF12
    {GPIO_P801, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SDA_PB03_AF12
    {GPIO_PB03, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SDA_PB05_AF12
    {GPIO_PB05, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SDA_PD04_AF12
    {GPIO_PD04, HAL_LL_SCI12_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI1_SDA_PD03_AF10
    {GPIO_PD03, HAL_LL_SCI1_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_1 ), 10},
    #endif
    #ifdef SCI5_SDA_P306_AF10
    {GPIO_P306, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SDA_P900_AF10
    {GPIO_P900, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SDA_PB05_AF10
    {GPIO_PB05, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SDA_PD07_AF10
    {GPIO_PD07, HAL_LL_SCI5_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI6_SDA_P801_AF10
    {GPIO_P801, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SDA_PB00_AF10
    {GPIO_PB00, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SDA_PB02_AF10
    {GPIO_PB02, HAL_LL_SCI6_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI8_SDA_P201_AF44
    {GPIO_P201, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_SDA_P203_AF44
    {GPIO_P203, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_SDA_PA04_AF45
    {GPIO_PA04, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SDA_PB00_AF44
    {GPIO_PB00, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_SDA_PD00_AF45
    {GPIO_PD00, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SDA_PD07_AF45
    {GPIO_PD07, HAL_LL_SCI8_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI9_SDA_P001_AF44
    {GPIO_P001, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SDA_P100_AF44
    {GPIO_P100, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SDA_P903_AF44
    {GPIO_P903, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SDA_P904_AF44
    {GPIO_P904, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SDA_PA01_AF44
    {GPIO_PA01, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SDA_PA03_AF44
    {GPIO_PA03, HAL_LL_SCI9_BASE_ADDR, hal_ll_i2c_module_num( SCI_MODULE_9 ), 44},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_PIN_MAP_H_
// ------------------------------------------------------------------------- END
