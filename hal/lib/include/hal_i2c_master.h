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
 * @file  hal_i2c_master.h
 * @brief API for I2C master HAL layer.
 */

#ifndef _HAL_I2C_MASTER_H_
#define _HAL_I2C_MASTER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

/**
 * @details The context for storing  HAL level object handlers.
 * Contains specific hardware module handle and
 * said module init state.
 * @warning User is not to change these values or
 * unexpected behaviour may occur.
 */
typedef struct
{
    handle_t *hal_i2c_master_handle; /*!< I2C Master HAL level handle */
    handle_t *drv_i2c_master_handle; /*!< I2C Master DRV level handle */
    bool init_state;                 /*!< I2C Master HAL object init state */
} hal_i2c_master_handle_register_t;

/**
 * @details Return values.
 */
typedef enum
{
    HAL_I2C_MASTER_SUCCESS = 0,  /*!< Success. */
    HAL_I2C_MASTER_WRONG_PINS,   /*!< Wrong pins selected. */
    HAL_I2C_MASTER_MODULE_ERROR, /*!< Object wasn't closed. */

    HAL_I2C_MASTER_ERROR = (-1)  /*!< Error. */
} hal_i2c_master_err_t;

/**
 * @details Predefined enum values for timeout occurrences.
 */
typedef enum
{
    HAL_I2C_MASTER_TIMEOUT_START = 1300, /*!< Start signal generation failed. */
    HAL_I2C_MASTER_TIMEOUT_STOP,         /*!< Stop signal generation failed. */
    HAL_I2C_MASTER_TIMEOUT_WRITE,        /*!< I2C bus write failed. */
    HAL_I2C_MASTER_TIMEOUT_READ,         /*!< I2C bus read failed. */
    HAL_I2C_MASTER_ARBITRATION_LOST,     /*!< I2C Master arbitration lost. */
    HAL_I2C_MASTER_TIMEOUT_INIT          /*!< I2C HW initialization failed. */
} hal_i2c_master_timeout_t;

/**
 * @details Predefined enum values for I2C transmission rates.
 */
typedef enum
{
    HAL_I2C_MASTER_SPEED_STANDARD = 0, /*!< Speed set at 100K. */
    HAL_I2C_MASTER_SPEED_FULL,         /*!< Speed set at 400K. */
    HAL_I2C_MASTER_SPEED_FAST          /*!< Speed set at 1M. */
} hal_i2c_master_speed_t;

/**
 * @brief  I2C Master HAL init configuration structure, consisted of the following fields :
 * @details User needs to specify values herein.
 * @note Take into consideration that any value can be changed explicitly by the user.
 * @warning The following example includes pins mapping.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // I2C master HAL driver configuration structure.
 *   static hal_i2c_master_config_t hal_i2c_master_cfg;
 *
 *   // Fill structure with default values.
 *   hal_i2c_master_configure_default(&hal_i2c_master_cfg);
 *
 *   // Specify desired scl pin.
 *   hal_i2c_master_cfg.scl = MIKROBUS_1_SCL;
 *
 *   // Specify desired sda pin.
 *   hal_i2c_master_cfg.sda = MIKROBUS_1_SDA;
 * @endcode
 */
typedef struct
{
    uint8_t addr; /*!< Slave address. */

    hal_pin_name_t sda; /*!< SDA pin. */
    hal_pin_name_t scl; /*!< SCL pin.  */

    uint32_t speed; /*!< I2C transmission rate. See #hal_i2c_master_speed_t for valid values. */
    uint16_t timeout_pass_count; /*!< I2C timeout value ( number of retries for each operation ). See #hal_i2c_master_timeout_t for valid values. */
} hal_i2c_master_config_t;

/**
 * @brief I2C Master HAL context structure, consisted of the following fields :
 * @details I2C Master HAL context structure, used by every other function later on.
 * @note The contents of the context structure are used by the module
 * and must not be altered. Reading or writing data directly from
 * a control structure by user should be avoided.
 *
 * @b Example
 * @code
 *   // I2C master HAL driver context structure.
 *   static hal_i2c_master_t hal_i2c_master;
 * @endcode
 */
typedef struct
{
    handle_t handle;                /*!<  I2C Master HAL handle. */
    hal_i2c_master_config_t config; /*!<  I2C Master HAL configuration structure. */
} hal_i2c_master_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/*!
 * @addtogroup hali2cgroup I2C Master HAL
 * @brief I2C Master Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating I2C Master HAL module.
 * @{
 */

/**
 * @brief Configure I2C Master HAL configuration structure.
 * @details Configures configuration structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config I2C Master HAL driver configuration structure.
 * See #hal_i2c_master_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * Address             | 0                         |
 * SCL pin             | 0xFFFFFFFF (invalid pin)  |
 * SDA pin             | 0xFFFFFFFF (invalid pin)  |
 * Speed               | 100K                      |
 * Timeout value       | 10000 retries             |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // I2C Master HAL config structure.
 *   static hal_i2c_master_config_t hal_i2c_master_cfg;
 *
 *   // Fill structure with default values.
 *   hal_i2c_master_configure_default( &hal_i2c_master_cfg );
 * @endcode
 */
void hal_i2c_master_configure_default( hal_i2c_master_config_t *config );

/**
 * @brief Open the I2C Master HAL object.
 * @details Opens the I2C Master HAL object on selected pins.
 * Allocates memory and pins for specified object.
 * @param[in,out] handle I2C Master HAL object.
 * See #hal_i2c_master_t structure definition for detailed explanation.
 * @param[in] hal_obj_open_state I2C state. Is it open or not.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C HAL context structure.
 *   static hal_i2c_master_t hal_i2c_master;
 *
 *   // Specify desired SCL pin.
 *   hal_i2c_master_cfg.scl = MIKROBUS_1_SCL;
 *
 *   // Specify desired SDA pin.
 *   hal_i2c_master_cfg.sda = MIKROBUS_1_SDA;
 *
 *   // Allocate resources for I2C module.
 *   if ( hal_i2c_master_open( &hal_i2c_master->handle, true ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t hal_i2c_master_open( handle_t *handle, bool hal_obj_open_state );

/**
 * @brief Set I2C master module speed.
 * @details Sets I2C module speed to \p config->speed value if possible.
 * @param[in] handle I2C handle.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] config I2C HAL configuration structure.
 * See #hal_i2c_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_i2c_master_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Set transmission rate.
 *   if ( hal_i2c_master_set_speed( &hal_i2c_master->handle, HAL_I2C_MASTER_SPEED_STANDARD ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t hal_i2c_master_set_speed( handle_t *handle, hal_i2c_master_config_t *config );

/**
 * @brief Set I2C master timeout value.
 * @details Sets I2C module timeout interval to \p config->timeout_pass_count value.
 * This means that the module shall retry any given operation \p config->timeout_pass_count
 * number of times before exiting with adequate timeout value.
 * @param[in] handle I2C handle.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] config I2C HAL configuration structure.
 * See #hal_i2c_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_i2c_master_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Set timeout value.
 *   if ( hal_i2c_master_set_timeout( &hal_i2c_master->handle, 1000 ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
void hal_i2c_master_set_timeout( handle_t *handle, hal_i2c_master_config_t *config );

/**
 * @brief Set I2C slave address.
 * @details Sets I2C Address of the subordinate I2C device
 * to \p config->address which is targeted by read and write operations.
 * @param[in] handle I2C handle.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] config I2C HAL configuration structure.
 * See #hal_i2c_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_i2c_master_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Set slave address.
 *   if ( hal_i2c_master_set_slave_address( &hal_i2c_master, 0x50 ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
void hal_i2c_master_set_slave_address( handle_t *handle, hal_i2c_master_config_t *config );

/**
 * @brief Write data to the I2C bus.
 * @details Function shall generate a START signal,
 * followed by \p len_write_data number of writes
 * from \p write_data_buf on the bus.
 * Ends with a STOP signal.
 * @param[in] handle I2C handle.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] *write_data_buf Data buffer.
 * @param[in] len_write_data Number of bytes to write from data buffer.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate I2C transmission rate.
 * See #hal_i2c_master_open definition and #hal_i2c_master_set_speed
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Set timeout value.
 *   if ( hal_i2c_master_write( &hal_i2c_master->handle, &write_buff, sizeof( write_buff ) ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t hal_i2c_master_write( handle_t handle, uint8_t *write_data_buf, size_t len_write_data );

/**
 * @brief Read data from the I2C bus.
 * @details Function shall generate a START signal,
 * followed by \p len_read_data number of reads
 * from the bus placing the data in \p read_data_buf .
 * Ends with a STOP signal.
 * @param[in] handle I2C handle.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[out] *read_data_buf Data buffer.
 * @param[in] len_read_data Number of bytes to read from bus.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate I2C transmission rate.
 * See #hal_i2c_master_open definition and #hal_i2c_master_set_speed
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Set timeout value.
 *   if ( hal_i2c_master_read( &hal_i2c_master, &read_buff, sizeof( read_buff ) ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t hal_i2c_master_read( handle_t handle, uint8_t *read_data_buf, size_t len_read_data );

/**
 * @brief Write data followed by read.
 * @details Function performs a write operation followed by a
 * read operation on the bus. The operation consists of a
 * start signal followed by \p len_write_data number of write operations
 * ( data from \p write_data_buf ), a restart signal followed by
 * \p len_read_data number of read operations ( placed in \p read_data_buf ),
 * finishing the operation with a stop signal.
 * @param[in] handle I2C handle.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] *write_data_buf Data buffer.
 * @param[in] len_write_data Number of bytes to write from data buffer.
 * @param[out] *read_data_buf Data buffer.
 * @param[in] len_read_data Number of bytes to read from bus.
 * @return The function can return one of the values defined by
 * #hal_i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate I2C transmission rate.
 * See #hal_i2c_master_open definition and #hal_i2c_master_set_speed
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Set timeout value.
 *   if ( hal_i2c_master_write_then_read( &hal_i2c_master->handle,  &write_buff, sizeof( write_buff ), &read_buff, sizeof( read_buff ) ) == HAL_I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t hal_i2c_master_write_then_read( handle_t handle, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data );

/**
 * @brief Closes I2C Master HAL object.
 * @details De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level, resets pin AF to default values,
 * clears all buffers used by object and disables module
 * clock for lower power consumption.
 * @param[in,out] handle I2C handle.
 * See #hal_i2c_master_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Close the I2C Master HAL module object handler.
 *   hal_i2c_master_close( &hal_i2c_master->handle );
 * @endcode
 */
err_t hal_i2c_master_close( handle_t *handle );

/*! @} */ // hali2cgroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_I2C_MASTER_H_
// ------------------------------------------------------------------------- END
