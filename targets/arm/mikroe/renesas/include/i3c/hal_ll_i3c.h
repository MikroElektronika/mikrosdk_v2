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
 * @file  hal_ll_i3c.h
 * @brief API for I3C sub-implementation of I2C module.
 */

#ifndef _HAL_LL_I3C_H_
#define _HAL_LL_I3C_H_

#include "hal_ll_target.h"
#include <stdbool.h>

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_i3c_module_num(_module_num) (_module_num - 1)

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief I3C low level pins config structure (I2C Master mode).
 *
 * The context structure for storing low level pin configuration
 * for both SCL and SDA pins.
 *
 */
typedef struct
{
    hal_ll_pin_af_t pin_scl;
    hal_ll_pin_af_t pin_sda;
} hal_ll_i3c_i2c_pins_t;

/*!< @brief i3c hw specific structure (I2C Master mode) */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_i3c_i2c_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
    bool is_i3c_module;
} hal_ll_i3c_i2c_hw_specifics_map_t;

/*!< @brief I3C end mode selection values (I2C Master mode) */
typedef enum {
    HAL_LL_I3C_I2C_END_MODE_RESTART = 0,
    HAL_LL_I3C_I2C_END_MODE_STOP,
    HAL_LL_I3C_I2C_WRITE_THEN_READ
} hal_ll_i3c_i2c_end_mode_t;

/*!< @brief i3c timeout error values (I2C Master mode) */
typedef enum {
    HAL_LL_I3C_I2C_TIMEOUT_START = 1300,
    HAL_LL_I3C_I2C_TIMEOUT_STOP,
    HAL_LL_I3C_I2C_TIMEOUT_WRITE,
    HAL_LL_I3C_I2C_TIMEOUT_READ,
    HAL_LL_I3C_I2C_ARBITRATION_LOST,
    HAL_LL_I3C_I2C_TIMEOUT_INIT,
    HAL_LL_I3C_I2C_TIMEOUT_WAIT_IDLE
} hal_ll_i3c_i2c_timeout_t;

/**
  * @brief  Full I3C module initialization in I2C Master mode procedure.
  *
  * Initializes I3C module in I2C Master mode on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
void hal_ll_i3c_i2c_init( hal_ll_i3c_i2c_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the I3C bus configured in I2C Master mode.
  *
  * Initializes I3C module in I2C Master mode on hardware level,
  * if not initialized beforehand and continues to perform a read operation
  * on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *readDatabuf - Pointer to data buffer.
  * @param[in]  lenReadData - Number of data to be read.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
hal_ll_err_t hal_ll_i3c_i2c_read_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                             uint8_t *read_data_buf,
                                             size_t len_read_data,
                                             hal_ll_i3c_i2c_end_mode_t mode );

/**
  * @brief  Perform a write on the I3C bus configured in I2C Master mode.
  *
  * Initializes I3C module in I2C Master mode on hardware level,
  * if not initialized beforehand and continues to perform a write operation
  * on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *writeDatabuf - Pointer to data buffer.
  * @param[in]  lenWriteData - Number of data to be written.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
hal_ll_err_t hal_ll_i3c_i2c_write_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_i3c_i2c_end_mode_t mode );

/**
  * @brief  Enable or disable the I3C hardware module for I2C Master mode.
  *
  * Controls the clock and power state of the specified I3C hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map         - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
void hal_ll_i3c_module_enable( hal_ll_i3c_i2c_hw_specifics_map_t *map, bool hal_ll_state );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I3C_H_
// ------------------------------------------------------------------------- END
