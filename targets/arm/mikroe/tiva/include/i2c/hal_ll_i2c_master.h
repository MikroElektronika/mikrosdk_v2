/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  hal_ll_i2c_master.h
 * @brief API for I2C master HAL LOW LEVEL layer.
 */

#ifndef _HAL_LL_I2C_MASTER_H_
#define _HAL_LL_I2C_MASTER_H_

#include "hal_ll_target.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief I2C master low level pin config structure.
 *
 * The context structure for storing low level pin configuration.
 *
 */
typedef struct
{
    hal_ll_pin_name_t pin_name;
    uint32_t pin_af;
} hal_ll_pin_af_t;

/**
 * @brief I2C master low level pins config structure.
 *
 * The context structure for storing low level pin configuration
 * for both SCL and SDA pins.
 *
 */
typedef struct
{
    hal_ll_pin_af_t pin_scl;
    hal_ll_pin_af_t pin_sda;
} hal_ll_i2c_pins_t;

/**
 * @brief I2C master low level handle.
 *
 * The context for storing low level object handler.
 * User is not to change these values or unexpected behaviour
 * may occur.
 */
typedef struct
{
    handle_t *hal_ll_i2c_master_handle;
    handle_t *hal_drv_i2c_master_handle;
    bool init_ll_state;
} hal_ll_i2c_master_handle_register_t;

/**
 * @brief  Registers handler for future use.
 *
 * Registers low level and hal level handlers
 * for use with appropriate functions.
 *
 * @param[in] scl I2C SCL pin.
 * @param[in] sda I2C SDA pin.
 * @param[in] *handle_map HAL layer local handle map.
 * @param[in] *hal_module_id HAL layer module number.

 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map, uint8_t *hal_module_id );

/**
 * @brief  Configures specified module.
 *
 * Performs module configuration on the hardware
 * level. Enables module specific clock gate and
 * sets adequate alternate function values.
 *
 * @param[in]  *handle HAL context object handle.
 *
 * @return  hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle );

/**
 * @brief  Sets I2C slave address.
 *
 * Registers I2C slave address for specified
 * object.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] addr I2C slave address.
 *
 * @return void None.
 */
void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr );

/**
 * @brief  Sets I2C module speed.
 *
 * Sets specified speed for module.
 * Take into consideration that the module
 * will be re-initialized on the hardware level.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] speed Desired speed value.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns value of speed the module was
 * initialized to, or module specific error if
 * initialization failed.
 * When using from low level directly,
 * speed can be set to any desired value,
 * but take into consideration that not all values
 * will work, as this is chip specific.
 * Speed value is declared in kbit/s.
 */
hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed );

/**
 * @brief  Sets I2C timeout value.
 *
 * Registers I2C timeout value in number of retries.
 * Module shall retry any given operation
 * `timeout` number of times before aborting operation.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] timeout I2C timeout value.
 *
 * @return void None.
 */
void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout );

/**
 * @brief Executes low level data read on I2C bus.
 *
 * Function shall generate a START signal,
 * followed by lenReadData number of reads
 * on the bus. Ends with a STOP signal.
 *
 * @param handle I2C handle.
 * @param *readDatabuf Data buffer where read data
 *                     shall be placed.
 * @param lenReadData Number of bytes to read.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data );

/**
 * @brief Executes low level data write on I2C bus.
 *
 * Function shall generate a START signal,
 * followed by lenWriteData number of writes
 * on the bus. Ends with a STOP signal.
 *
 * @param handle I2C handle.
 * @param *WriteDatabuf Data buffer where data to
 *                      be written is located.
 * @param lenWriteData Number of bytes to send.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data );

/**
  * @brief  Perform a low level write followed by a low level read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a write operation followed by a
  * read operation on the bus.
  * The operation consists of a start signal followed by lenWriteData number
  * of write operations, a restart signal followed by lenReadData number
  * of read operations finishing with a stop signal.
  *
  * @param handle I2C handle.
  * @param[in]  *writeDatabuf - Pointer to write data buffer.
  * @param[in]  lenWriteData - Number of data to be written.
  * @param[in]  *readDatabuf - Pointer to read data buffer.
  * @param[in]  lenReadData - Number of data to be read.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data );

/**
 * @brief  Closes I2C master HAL and HAL_LOW_LEVEL context object.
 *
 * De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 *
 * @param[in] *handle HAL context object handle.
 *
 * @return void None.
 */
void hal_ll_i2c_master_close( handle_t *handle );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_MASTER_H_
// ------------------------------------------------------------------------- END
