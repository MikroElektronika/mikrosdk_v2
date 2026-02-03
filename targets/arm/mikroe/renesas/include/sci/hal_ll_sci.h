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
 * @file  hal_ll_SCI.h
 * @brief API for SCI sub-implementation of I2C and SPI modules.
 */

#ifndef _HAL_LL_SCI_H_
#define _HAL_LL_SCI_H_

#include "hal_ll_target.h"

/**
 * @brief I2C master low level pins config structure.
 *
 * The context structure for storing low level pin configuration
 * for both SCL and SDA pins.
 *
 */
typedef enum
{
    HAL_LL_SCI_I2C_MODE = 0,
    HAL_LL_SCI_SPI_MODE
} hal_ll_sci_mode_t;

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
} hal_ll_i2c_sci_pins_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_sci_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
    uint8_t is_sci_module;
} hal_ll_i2c_sci_hw_specifics_map_t;

/*!< @brief I2C end mode selection values */
typedef enum {
    HAL_LL_I2C_SCI_END_MODE_RESTART = 0,
    HAL_LL_I2C_SCI_END_MODE_STOP,
    HAL_LL_I2C_SCI_WRITE_THEN_READ
} hal_ll_i2c_sci_end_mode_t;

/*!< @brief I2C hw specific module values */
typedef struct {
    uint32_t pin_scl;
    uint32_t pin_sda;
} hal_ll_i2c_sci_pin_id;

/*!< @brief I2C timeout error values */
typedef enum {
    HAL_LL_I2C_SCI_TIMEOUT_START = 1300,
    HAL_LL_I2C_SCI_TIMEOUT_STOP,
    HAL_LL_I2C_SCI_TIMEOUT_WRITE,
    HAL_LL_I2C_SCI_TIMEOUT_READ,
    HAL_LL_I2C_SCI_ARBITRATION_LOST,
    HAL_LL_I2C_SCI_TIMEOUT_INIT,
    HAL_LL_I2C_SCI_TIMEOUT_WAIT_IDLE
} hal_ll_i2c_sci_timeout_t;

/**
 * @brief Enum containing predefined module mode values.
 *
 * Enum values:
 *
 * HAL_LL_SPI_SCI_MODE_0 -- CPO = 0, CPH = 0
 * HAL_LL_SPI_SCI_MODE_1 -- CPO = 0, CPH = 1
 * HAL_LL_SPI_SCI_MODE_2 -- CPO = 1, CPH = 0
 * HAL_LL_SPI_SCI_MODE_3 -- CPO = 1, CPH = 1
 */
typedef enum {
    HAL_LL_SPI_SCI_MODE_0 = 0,
    HAL_LL_SPI_SCI_MODE_1,
    HAL_LL_SPI_SCI_MODE_2,
    HAL_LL_SPI_SCI_MODE_3,

    HAL_LL_SPI_SCI_MODE_DEFAULT = HAL_LL_SPI_SCI_MODE_0
} hal_ll_spi_sci_mode_t;

/**
 * @brief SPI configuration pins structure.
 */
typedef struct {
    hal_ll_pin_af_t  sck;
    hal_ll_pin_af_t  miso;
    hal_ll_pin_af_t  mosi;
} hal_ll_spi_sci_pins_t;

/*!< @brief SPI Master hardware specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_spi_sci_pins_t pins;
    uint8_t dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_sci_mode_t mode;
    uint8_t is_sci_module;
} hal_ll_spi_sci_hw_specifics_map_t;

/*!< @brief SPI Master hardware specific module values. */
typedef struct {
    uint8_t pin_miso;
    uint8_t pin_mosi;
    uint8_t pin_sck;
} hal_ll_spi_sci_pin_id;

#ifdef __cplusplus
extern "C"{
#endif

/**
  * @brief  Full SCI module initialization in I2C Master mode procedure.
  *
  * Initializes SCI module in I2C Master mode on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
void hal_ll_i2c_sci_init( hal_ll_i2c_sci_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the SCI bus configured in I2C Master mode.
  *
  * Initializes SCI module in I2C Master mode on hardware level,
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
hal_ll_err_t hal_ll_i2c_sci_read_bare_metal( hal_ll_i2c_sci_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_sci_end_mode_t mode );

/**
  * @brief  Perform a write on the SCI bus configured in I2C Master mode.
  *
  * Initializes SCI module in I2C Master mode on hardware level,
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
hal_ll_err_t hal_ll_i2c_sci_write_bare_metal( hal_ll_i2c_sci_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_sci_end_mode_t mode );

/**
  * @brief  Enable or disable the SCI hardware module for I2C Master mode.
  *
  * Controls the clock and power state of the specified I2CSCI hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
void hal_ll_sci_module_enable( hal_ll_i2c_sci_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Full SCI module initialization procedure for SPI mode.
  *
  * Initializes SCI module in SPI Master mode on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None.
  */
void hal_ll_spi_sci_init( hal_ll_spi_sci_hw_specifics_map_t *map );

/**
  * @brief  Perform a write on the SCI bus configured in SPI Master mode.
  *
  * Initializes SCI module in SPI Master mode on hardware level, if not
  * initialized beforehand and continues to perform a write operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return None.
  */
void hal_ll_spi_sci_write_bare_metal( hal_ll_spi_sci_hw_specifics_map_t *map,
                                               uint8_t *read_data, size_t write_data_size );

/**
  * @brief  Perform a read on the on the SCI bus configured in SPI Master mode.
  *
  * Initializes SCI module in SPI Master mode on hardware level, if not
  * initialized beforehand and continues to perform a read operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  * @return None.
  */
void hal_ll_spi_sci_read_bare_metal( hal_ll_spi_sci_hw_specifics_map_t *map,
                                               uint8_t *read_data_buffer,
                                               size_t read_data_length,
                                               uint8_t dummy_data );

/**
  * @brief  Perform a simultaneous write and read on the SCI module configured in SPI Master mode.
  *
  * Function performs a full-duplex SPI transfer. Each written byte results in
  * a received byte which is optionally stored in the read buffer.
  * If the write buffer is NULL, the configured dummy byte will be transmitted.
  * If the read buffer is NULL, the received data will be discarded.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to write data buffer.
  *                                  If NULL, dummy data will be used.
  * @param[out] *read_data_buffer - Pointer to read data buffer.
  *                                 If NULL, received data will be discarded.
  * @param[in]  data_length - Number of bytes to be transferred.
  *
  * @note TX FIFO is flushed and re-enabled on each byte transfer to ensure proper behavior.
  *       This implementation uses polling and is blocking.
  */
void hal_ll_spi_sci_transfer_bare_metal( hal_ll_spi_sci_hw_specifics_map_t *map,
                                                   uint8_t *write_data_buffer,
                                                   uint8_t *read_data_buffer,
                                                   size_t data_length );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_I2C_MASTER_H_
// ------------------------------------------------------------------------- END
