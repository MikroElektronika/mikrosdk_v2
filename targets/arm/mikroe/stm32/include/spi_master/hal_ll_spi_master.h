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
 * @file  hal_ll_spi_master.h
 * @brief API for SPI master HAL LOW LEVEL layer.
 */

#ifndef _HAL_LL_SPI_MASTER_H_
#define _HAL_LL_SPI_MASTER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_target.h"
#include "hal_ll_gpio.h"

typedef struct
{
    hal_ll_pin_name_t pin_name;
    uint32_t pin_af;
} hal_ll_pin_af_t;

/**
 * @brief SPI configuration pins structure.
 */
typedef struct
{
    hal_ll_pin_af_t  sck;
    hal_ll_pin_af_t  miso;
    hal_ll_pin_af_t  mosi;
} hal_ll_spi_master_pins_t;

/**
 * @brief SPI master HAL low lever configuration structure.
 */
typedef struct
{
    uint8_t    default_write_data;
    hal_ll_pin_name_t sck;
    hal_ll_pin_name_t miso;
    hal_ll_pin_name_t mosi;
    uint32_t speed;
} hal_ll_spi_master_config_t;

/**
 * @brief Enum containing predefined module mode values.
 *
 * Enum values:
 *
 * HAL_LL_SPI_MASTER_MODE_0 -- CPOL = 0, CPHA = 0
 * HAL_LL_SPI_MASTER_MODE_1 -- CPOL = 0, CPHA = 1
 * HAL_LL_SPI_MASTER_MODE_2 -- CPOL = 1, CPHA = 0
 * HAL_LL_SPI_MASTER_MODE_3 -- CPOL = 1, CPHA = 1
 */
typedef enum
{
    HAL_LL_SPI_MASTER_MODE_0 = 0,
    HAL_LL_SPI_MASTER_MODE_1,
    HAL_LL_SPI_MASTER_MODE_2,
    HAL_LL_SPI_MASTER_MODE_3,

    HAL_LL_SPI_MASTER_MODE_DEFAULT = HAL_LL_SPI_MASTER_MODE_0
} hal_ll_spi_master_mode_t;

/**
 * @brief SPI master HAL low lever handle register.
 */
typedef struct
{
    handle_t *hal_ll_spi_master_handle;
    handle_t *hal_drv_spi_master_handle;
    bool init_ll_state;
} hal_ll_spi_master_handle_register_t;

/**
 * @brief  Registers handler for future use.
 *
 * Registers low level and hal level handlers
 * for use with appropriate functions.
 *
 * @param[in] *handle HAL context object handle.
 * @param[in] sck SPI sck pin.
 * @param[in] miso SPI miso pin.
 * @param[in] mosi SPI mosi pin.
 * @param[in] *handle_map HAL layer local handle map.
 * @param[in] *hal_module_id HAL layer module number.

 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined error values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_spi_master_register_handle( hal_ll_pin_name_t sck, hal_ll_pin_name_t miso,
                                                hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id );

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
hal_ll_err_t hal_ll_module_configure_spi( handle_t *handle );

/**
 * @brief Sets SPI Master configuration dummy data.
 * @param config[IN] SPI Master module configuration.
 * @param config[IN] user-defined dummy data.
 */
void hal_ll_spi_master_set_default_write_data( handle_t *handle, uint8_t dummy_data );

/**
 * @brief Sets SPI Master configuration dummy data.
 * @param config[IN] SPI Master module configuration.
 * @param config[IN] user-defined SPI Master baud rate value.
 */
uint32_t hal_ll_spi_master_set_speed( handle_t *handle, uint32_t speed );

/**
 * @brief Sets SPI Master configuration dummy data.
 * @param[in] *handle HAL context object handle.
 * @param[in] mode SPI Master de-facto mode selection.
 */
hal_ll_err_t hal_ll_spi_master_set_mode( handle_t *handle, hal_ll_spi_master_mode_t mode );

/**
 * @brief Executes low level data write on SPI bus.
 *
 * Function shall generate a START signal,
 * followed by write_data_buffer number of writes
 * on the bus.
 *
 * @param *handle HAL context object handle.
 * @param *write_data_buffer Data buffer where data to be written is located.
 * @param length_data Number of bytes to send.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data);

/**
 * @brief Executes low level data read on SPI bus.
 *
 * @param handle I2C handle.
 * @param *read_data_buffer Data buffer where read data shall be placed.
 * @param length_data Number of bytes to read.
 *
 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data);

/**
  * @brief  Perform a low level write followed by a low level read on the SPI bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation followed by a
  * read operation on the bus.
  *
  * @param[in]  *handle - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to write data buffer.
  * @param[in]  length_write_data - Number of data to be written.
  * @param[in]  *read_data_buffer - Pointer to read data buffer.
  * @param[in]  length_read_data - Number of data to be read.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
hal_ll_err_t hal_ll_spi_master_write_then_read( handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data );

/**
 * @brief  Closes SPI Master HAL and HAL_LOW_LEVEL context object.
 *
 * De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 *
 * @param[in] *handle HAL context object handle.
 *
 * @return void None.
 */
void hal_ll_spi_master_close( handle_t *handle );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_H_
// ------------------------------------------------------------------------- END
