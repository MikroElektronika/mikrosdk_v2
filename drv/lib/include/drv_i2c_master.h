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
 * @file  drv_i2c_master.h
 * @brief API for I2C master driver.
 */

#ifndef _DRV_I2C_MASTER_H_
#define _DRV_I2C_MASTER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_i2c_master.h"

/**
 * @details Return values.
 */
typedef enum
{
    I2C_MASTER_SUCCESS = 0,  /*!< Success. */
    I2C_MASTER_ERROR = (-1)  /*!< Error. */
} i2c_master_err_t;

/**
 * @details Predefined enum values for module standard speed values.
 */
typedef enum
{
    I2C_MASTER_SPEED_STANDARD = 0, /*!< Speed set at 100K. */
    I2C_MASTER_SPEED_FULL,         /*!< Speed set at 400K. */
    I2C_MASTER_SPEED_FAST          /*!< Speed set at 1M. */
} i2c_master_speed_t;

/**
 * @brief I2C Master initialization configuration structure, consisted of the following fields :
 * @details User needs to specify values herein.
 * @note Take into consideration that any value can be changed explicitly by the user.
 * @warning The following example includes pins mapping.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // I2C master driver config structure.
 *   static i2c_master_config_t i2c_master_cfg;
 *
 *   // Fill structure with default values.
 *   i2c_master_configure_default(&i2c_master_cfg);
 *
 *   // Specify desired SCL pin.
 *   i2c_master_cfg.scl = MIKROBUS_1_SCL;
 *
 *   // Specify desired SDA pin.
 *   i2c_master_cfg.sda = MIKROBUS_1_SDA;
 * @endcode
 */
typedef struct
{
    uint8_t addr; /*!< Slave address. */

    pin_name_t sda; /*!< SDA pin. */
    pin_name_t scl; /*!< SCL pin.  */

    uint32_t speed; /*!< I2C transmission rate. */
    uint16_t timeout_pass_count; /*!< I2C timeout value ( number of retries for each operation ) */
} i2c_master_config_t;

/**
 * @brief I2C Master driver context structure, consisted of the following fields :
 * @details I2C Master driver context structure, used by every other function later on.
 * @note The contents of the context structure are used by the module
 * and must not be altered. Reading or writing data directly from
 * a control structure by user should be avoided.
 *
 * @b Example
 * @code
 *   // I2C Master driver context structure.
 *   static i2c_master_t i2c_master;
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< I2C Master handle. */
    i2c_master_config_t config; /*!< I2C configuration structure. */
} i2c_master_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup drvi2cgroup I2C Master Driver
 * @brief I2C Master Driver API Reference.
 * @details The I2C Master driver provides standard I2C Master functionality including setting the I2C speed and timeout.
 * @{
 */

/**
 * @brief Configure I2C Master configuration structure.
 * @details Configures I2C Master structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config I2C Master driver configuration structure.
 * See #i2c_master_config_t structure definition for detailed explanation.
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
 *   // I2C Master driver config structure.
 *   i2c_master_config_t i2c_master_cfg;
 *
 *   // Fill structure with default values.
 *   i2c_master_configure_default( &i2c_master_cfg );
 * @endcode
 */
void i2c_master_configure_default( i2c_master_config_t *config );

/**
 * @brief Open the I2C Master driver object.
 * @details Opens the I2C Master driver object on selected pins.
 * Allocates memory and pins for specified object.
 * @param[in,out] obj I2C Master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] config I2C Master driver configuration settings.
 * See #i2c_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that \p config structure has been adequately
 * populated beforehand.
 * See #i2c_master_configure_default definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // Specify desired SCL pin.
 *   i2c_master_cfg.scl = MIKROBUS_1_SCL;
 *
 *   // Specify desired SDA pin.
 *   i2c_master_cfg.sda = MIKROBUS_1_SDA;
 *
 *   // Allocate resources for I2C module.
 *   if ( i2c_master_open( &i2c_master, &i2c_master_cfg ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_open( i2c_master_t *obj, i2c_master_config_t *config );

/**
 * @brief Set I2C Master module speed.
 * @details Sets I2C Master module speed to \p speed value if possible.
 * @param[in] obj I2C Master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] speed Specified I2C transmission rate. See #i2c_master_speed_t for valid values.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #i2c_master_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // Set transmission rate.
 *   if ( i2c_master_set_speed( &i2c_master, I2C_MASTER_SPEED_STANDARD ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_set_speed( i2c_master_t *obj, uint32_t speed );

/**
 * @brief Set I2C Master timeout value.
 * @details Sets I2C Master module timeout interval to \p timeout_pass_count value.
 * This means that the module shall retry any given operation \p timeout_pass_count
 * number of times before exiting with adequate timeout value.
 * @param[in] obj I2C Master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] timeout_pass_count Specified I2C master timeout value.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #i2c_master_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // Set timeout value.
 *   if ( i2c_master_set_timeout( &i2c_master, 1000 ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_set_timeout( i2c_master_t *obj, uint16_t timeout_pass_count );

/**
 * @brief Set I2C Slave address.
 * @details Sets I2C address of the subordinate I2C device
 * to \p address which is targeted by read and write operations.
 * @param[in] obj I2C Master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] address Specified I2C slave address.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #i2c_master_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // Set slave address.
 *   if ( i2c_master_set_slave_address( &i2c_master, 0x50 ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_set_slave_address( i2c_master_t *obj, uint8_t address );

/**
 * @brief Write data to the I2C bus.
 * @details Function shall generate a START signal,
 * followed by \p len_write_data number of writes
 * from \p write_data_buf on the bus.
 * Ends with a STOP signal.
 * @param[in] obj I2C master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] *write_data_buf Data transmit buffer.
 * @param[in] len_write_data Number of bytes to write from data transmit buffer.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate I2C transmission rate.
 * See #i2c_master_open definition and #i2c_master_set_speed
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // I2C data buffer.
 *   uint8_t *write_buff;
 *
 *   if ( i2c_master_write( &i2c_master, &write_buff, sizeof( write_buff ) ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_write( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data );

/**
 * @brief Read data from the I2C bus.
 * @details Function shall generate a START signal,
 * followed by \p len_read_data number of reads
 * from the bus placing the data in \p read_data_buf .
 * Ends with a STOP signal.
 * @param[in] obj I2C master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[out] *read_data_buf Data receive buffer.
 * @param[in] len_read_data Number of bytes to read from bus.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate I2C transmission rate.
 * See #i2c_master_open definition and #i2c_master_set_speed
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // I2C data buffer.
 *   uint8_t *read_buff;
 *
 *   if ( i2c_master_read( &i2c_master, &read_buff, sizeof( read_buff ) ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_read( i2c_master_t *obj, uint8_t *read_data_buf, size_t len_read_data );

/**
 * @brief Write data to I2C bus followed by read.
 * @details Function performs a write operation followed by a
 * read operation on the bus. The operation consists of a
 * start signal followed by \p len_write_data number of write operations
 * ( data from \p write_data_buf ), a restart signal followed by
 * \p len_read_data number of read operations ( placed in \p read_data_buf ),
 * finishing the operation with a stop signal.
 * @param[in] obj I2C master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @param[in] *write_data_buf Data transmit buffer.
 * @param[in] len_write_data Number of bytes to write from data transmit buffer.
 * @param[out] *read_data_buf Data receive buffer.
 * @param[in] len_read_data Number of bytes to read from bus.
 * @return The function can return one of the values defined by
 * #i2c_master_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand, and
 * the module has been initialized to adequate I2C transmission rate.
 * See #i2c_master_open definition and #i2c_master_set_speed
 * for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // I2C data buffers.
 *   uint8_t *write_buff;
 *   uint8_t *read_buff;
 *
 *   if ( i2c_master_write_then_read( &i2c_master,  &write_buff, sizeof( write_buff ), &read_buff, sizeof( read_buff ) ) == I2C_MASTER_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t i2c_master_write_then_read( i2c_master_t *obj, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data );

/**
 * @brief Close I2C Master driver object.
 * @details De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level, resets pin AF to default values,
 * clears all buffers used by object and disables module
 * clock for lower power consumption.
 * @param[in,out] obj I2C Master driver object.
 * See #i2c_master_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // I2C driver context structure.
 *   static i2c_master_t i2c_master;
 *
 *   // Close the I2C Master module object handler.
 *   i2c_master_close( &i2c_master );
 * @endcode
 */
void i2c_master_close( i2c_master_t *obj );

/*! @} */ // drvi2cgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_I2C_MASTER_H_
// ------------------------------------------------------------------------- END
