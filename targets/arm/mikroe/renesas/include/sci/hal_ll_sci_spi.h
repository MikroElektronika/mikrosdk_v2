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
 * @file  hal_ll_sci_spi.h
 * @brief API for SCI sub-implementation of SPI module.
 */

#ifndef _HAL_LL_SCI_SPI_H_
#define _HAL_LL_SCI_SPI_H_

/**
 * @brief SCI SPI mode selection values.
 *
 * Enum values:
 *
 * HAL_LL_SCI_SPI_MODE_0 -- CPO = 0, CPH = 0
 * HAL_LL_SCI_SPI_MODE_1 -- CPO = 0, CPH = 1
 * HAL_LL_SCI_SPI_MODE_2 -- CPO = 1, CPH = 0
 * HAL_LL_SCI_SPI_MODE_3 -- CPO = 1, CPH = 1
 */
typedef enum {
    HAL_LL_SCI_SPI_MODE_0 = 0,
    HAL_LL_SCI_SPI_MODE_1,
    HAL_LL_SCI_SPI_MODE_2,
    HAL_LL_SCI_SPI_MODE_3,

    HAL_LL_SCI_SPI_MODE_DEFAULT = HAL_LL_SCI_SPI_MODE_0
} hal_ll_sci_spi_mode_t;

/**
 * @brief SCI configuration pins structure (SPI Master mode).
 */
typedef struct {
    hal_ll_pin_af_t  sck;
    hal_ll_pin_af_t  miso;
    hal_ll_pin_af_t  mosi;
} hal_ll_sci_spi_pins_t;

/*!< @brief SCI hardware specific structure (SPI Master mode). */
typedef struct {
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_sci_spi_pins_t pins;
    uint8_t dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_sci_spi_mode_t mode;
    bool is_sci_module;
} hal_ll_sci_spi_hw_specifics_map_t;

/*!< @brief SCI hardware specific module values (SPI Master mode). */
typedef struct {
    uint8_t pin_miso;
    uint8_t pin_mosi;
    uint8_t pin_sck;
} hal_ll_sci_spi_pin_id;

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
void hal_ll_sci_spi_init( hal_ll_sci_spi_hw_specifics_map_t *map );

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
void hal_ll_sci_spi_write_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                      uint8_t *write_data_buffer, size_t write_data_size );

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
void hal_ll_sci_spi_read_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
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
void hal_ll_sci_spi_transfer_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                         uint8_t *write_data_buffer,
                                         uint8_t *read_data_buffer,
                                         size_t data_length );

#endif // _HAL_LL_SCI_SPI_H_
// ------------------------------------------------------------------------- END
