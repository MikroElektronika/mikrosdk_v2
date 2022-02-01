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
 * @file  hal_spi_master.h
 * @brief API for SPI Master HAL layer.
 */

#ifndef _HAL_SPI_MASTER_H_
#define _HAL_SPI_MASTER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"
#include "hal_ll_spi_master.h"
#include "hal_gpio.h"

/**
 * @brief SPI Master level handle.
 * @details The context for storing  HAL level object handler.
 * Contains specific hardware module handle and
 * said module init state.
 * @warning User is not to change these values or
 * unexpected behaviour may occur.
 */
typedef struct
{
    handle_t *hal_spi_master_handle; /*!< SPI Master HAL level handle */
    handle_t *drv_spi_master_handle; /*!< SPI Master DRV level handle */
    bool init_state; /*!< SPI Master HAL object init state */
} hal_spi_master_handle_register_t;

/**
 * @details Enum containing predefined module mode values.
 */
typedef enum
{
    HAL_SPI_MASTER_MODE_0 = 0,  /*!< SPI MODE 0 */
    HAL_SPI_MASTER_MODE_1,      /*!< SPI MODE 1 */
    HAL_SPI_MASTER_MODE_2,      /*!< SPI MODE 2 */
    HAL_SPI_MASTER_MODE_3,      /*!< SPI MODE 3 */

    HAL_SPI_MASTER_MODE_DEFAULT = HAL_SPI_MASTER_MODE_0 /*!< Default SPI mode - MODE 0 */
} hal_spi_master_mode_t;

/**
 * @details Enum containing predefined chip select polarity values.
 */
typedef enum
{
    HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW = 0, /*!< CS active low. */
    HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH,    /*!< CS active high. */
    HAL_SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY = HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW /*!< CS active low. */
} hal_spi_master_chip_select_polarity_t;

/**
 * @brief HAL SPI Master init configuration structure, consisted of the following fields :
 * @details User needs to specifiy values herein.
 * @note Take into consideration that any value can be changed explicitly by the user.
 *
 * @b Example
 * @code
 *   // SPI Master configuration structure.
 *   static hal_spi_master_config_t hal_spi_master_cfg;
 *
 *   // Populate structure to default init values.
 *   hal_spi_master_configure_default(&hal_spi_master_cfg);
 *
 *   // Specify desired SPI Serial Clock pin.
 *   hal_spi_master_cfg.sck = MIKROBUS_1_SCK;
 *
 *   // Specify desired SPI Master-In Slave-Out pin.
 *   hal_spi_master_cfg.miso = MIKROBUS_1_MISO;
 *
 *   // Specify desired SPI Master-Out Slave-In pin.
 *   hal_spi_master_cfg.mosi = MIKROBUS_1_MOSI;
 *
 *   // Specify desired SPI transfer rate.
 *   hal_spi_master_cfg.speed = 100000;
 *
 *   // Specify desired SPI Mode.
 *   hal_spi_master_cfg.mode = SPI_MASTER_MODE_0;
 * @endcode
 */
typedef struct
{
    uint8_t default_write_data; /*!< SPI Master default write data. */
    hal_pin_name_t sck; /*!< SCK pin name. */
    hal_pin_name_t miso; /*!< MISO pin name. */
    hal_pin_name_t mosi; /*!< MOSI pin name. */
    uint32_t speed; /*!< SPI transfer rate.*/
    hal_spi_master_mode_t mode; /*!< SPI mode. See #hal_spi_master_mode_t for valid values.*/
} hal_spi_master_config_t;

/**
 * @brief SPI master HAL context structure, consisted of the following fields :
 * @details SPI master HAL context structure for storing driver internal state.
 * The contents of the context structure are used by the module and must
 * not be altered. Reading or writing data directly from a control
 * structure by user should be avoided.
 *
 * @b Example
 * @code
 *   // HAL SPI Master context structure.
 *   static hal_spi_master_t hal_spi_master;
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< HAL SPI Master handle. */
    hal_spi_master_config_t config; /*!< HAL SPI configuration structure. */
} hal_spi_master_t;

/**
 * @details Enum containing predefined module return values.
 */
typedef enum {
    HAL_SPI_MASTER_SUCCESS = 0,    /*!< Success. */
    HAL_SPI_MASTER_WRONG_PINS,     /*!< Wrong pins selected. */
    HAL_SPI_MASTER_MODULE_ERROR,   /*!< Object wasn't closed. */
    HAL_SPI_MASTER_ERROR = ( -1 )  /*!< Error. */
} hal_spi_master_err_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/*!
 * @addtogroup halspimastergroup SPI Master HAL
 * @brief SPI Master Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating SPI Master HAL module.
 * @{
 */

/**
 * @brief Configure SPI Master configuration structure with default values.
 * @details Configures structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config SPI Master HAL layer configuration settings.
 * See #hal_spi_master_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function                 | Default value                |
 * -------------------------|------------------------------|
 * SPI SCK pin              | HAL_PIN_NC (invalid pin)     |
 * SPI MISO pin             | HAL_PIN_NC (invalid pin)     |
 * SPI MOSI pin             | HAL_PIN_NC (invalid pin)     |
 * SPI Speed                | 100KHz                       |
 * SPI mode                 | 0                            |
 * SPI default write data   | 0                            |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // HAL SPI configuration structure.
 *   hal_spi_master_config_t hal_spi_master_config;
 *
 *   // Populate structure to default init values.
 *   hal_spi_master_configure_default( &hal_spi_master_config );
 * @endcode
 */
void hal_spi_master_configure_default( hal_spi_master_config_t *config );

/**
 * @brief Open the SPI Master HAL object on selected pins.
 * @details Opens the SPI Master HAL object on selected pins.
 * Allocates memory and pin for specified object.
 * @param[in] handle SPI Master HAL object.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[in] hal_obj_open_state SPI Master configuration structure.
 * See #hal_spi_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 * @note This function needs to be called before other HAL functions.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   hal_spi_master_t hal_spi_master;
 *
 *   // HAL SPI configuration structure.
 *   hal_spi_master_config_t  hal_spi_master_config;
 *
 *   // Populate structure to default init values.
 *   hal_spi_master_configure_default( &hal_spi_master_config );
 *
 *   // Specify desired SPI Serial Clock pin.
 *   hal_spi_master_config.sck = MIKROBUS_1_SCK;
 *
 *   // Specify desired SPI Master-In Slave-Out pin.
 *   hal_spi_master_config.miso = MIKROBUS_1_MISO;
 *
 *   // Specify desired SPI Master-Out Slave-In pin.
 *   hal_spi_master_config.mosi = MIKROBUS_1_MOSI;
 *
 *   // Specify desired SPI transfer rate.
 *   hal_spi_master_config.speed = 100000;
 *
 *   // Specify desired SPI Mode.
 *   hal_spi_master_config.mode = SPI_MASTER_MODE_0;
 *
 *   // Specify SPI default write (dummy) data.
 *   hal_spi_master_config.default_write_data = 0x00;
 *
 *   // Allocate resources for SPI module.
 *   hal_spi_master_open( &hal_spi_master, &hal_spi_master_config );
 * @endcode
 */
err_t hal_spi_master_open( handle_t *handle, bool hal_obj_open_state );

/**
 * @brief Select SPI Slave device.
 * @details Sets digital output individual slave pin to logic 0.
 * @param[in] chip_select Device-specific chip select pin.
 * @return Nothing.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Select desired device.
 *   hal_spi_master_select_device( PA1 );
 * @endcode
 */
void hal_spi_master_select_device( hal_pin_name_t chip_select );

/**
 * @brief Deselect SPI Slave device.
 * @details Sets digital output individual slave pin to logic 1.
 * @param[in] chip_select Device-specific chip select pin.
 * @return Nothing.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Deselect desired device.
 *   hal_spi_master_deselect_device( PA1 );
 * @endcode
 */
void hal_spi_master_deselect_device( hal_pin_name_t chip_select );

/**
 * @brief Set desired chip select polarity.
 * @details Sets SPI Master chip select polarity either to active low or
 * active high. Chip select polarity shall be active low by default.
 * @param[in] polarity Desired chip select polarity mode.
 * See #hal_spi_master_chip_select_polarity_t for valid values.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Specify desired chip-select polarity.
 *   hal_spi_master_set_chip_select_polarity( HAL_SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW );
 * @endcode
 */
void hal_spi_master_set_chip_select_polarity( hal_spi_master_chip_select_polarity_t polarity );

/**
 * @brief Set SPI Master default ( dummy ) write data.
 * @details Default write data is sent by driver when the data transmit buffer is shorter than data receive buffer.
 * @param[in] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[in] config HAL SPI Master config structure.
 * See #hal_spi_master_config_t structure definition for detailed explanation.
 * @return Nothing.
 * @pre Before calling this function,
 * the user is expected to call #hal_spi_master_open function.
 *
 * @b Example
 * @code
 *   // Specify desired default write (dummy) data.
 *   hal_spi_master_set_default_write_data( &handle, 0x00 );
 * @endcode
 */
void hal_spi_master_set_default_write_data( handle_t *handle,
                                            hal_spi_master_config_t *config );

/**
 * @brief Set desired SPI communication speed.
 * @details Sets SPI Master module speed to passed value if possible.
 * If not possible, returns error. Make sure to check for return value.
 * Initializes SPI module on hardware level.
 * @param[in] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[in] config HAL SPI Master config structure.
 * See #hal_spi_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_spi_master_open function.
 *
 * @b Example
 * @code
 *   // Specify desired SPI transfer rate.
 *   hal_spi_master_set_speed( &handle, 100000 );
 * @endcode
 */
err_t hal_spi_master_set_speed( handle_t *handle, hal_spi_master_config_t *config );

/**
 * @brief Set desired SPI communication mode.
 * @details Sets SPI Master module mode to passed value if possible.
 * If not possible, returns error. Make sure to check for return value.
 * Initializes SPI module on hardware level.
 * @param[in] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[in] config HAL SPI Master config structure.
 * See #hal_spi_master_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_spi_master_open function.
 *
 * @b Example
 * @code
 *   // Specify desired SPI mode.
 *   hal_spi_master_set_mode( &handle, HAL_SPI_MASTER_MODE_0 );
 * @endcode
 */
err_t hal_spi_master_set_mode( handle_t *handle, hal_spi_master_config_t *config );

/**
 * @brief Write byte to SPI bus.
 * @details Writes byte to SPI bus in blocking mode.
 * Received byte is discarded.
 * @param[in] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[in] write_data_buffer Value to send.
 * @param[in] write_data_length Number of bytes to write from data buffer.
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_spi_master_open function.
 * @warning The following example describes only how the function is used.
 * This is not a working example.
 *
 * @b Example
 * @code
 *   // Specify length of data to be written.
 *   #define DATA_LENGTH 150
 *
 *   // Specify data structure for data to be sent.
 *   uint8_t write_sequence[ DATA_LENGTH ];
 *
 *   // Specify i.e. 0th element to be sent.
 *   write_sequence[0] = 0x02;
 *
 *   // Specify i.e. 1st element to be sent.
 *   write_sequence[1] = 0x05;
 *
 *   // Write specified data on SPI bus.
 *   hal_spi_master_write( handle, &write_sequence, DATA_LENGTH );
 * @endcode
 */
err_t hal_spi_master_write( handle_t handle, uint8_t *write_data_buffer,
                                              size_t write_data_length );

/**
 * @brief Read byte from SPI bus.
 * @details Reads byte from SPI bus in blocking mode.
 * Transmitted byte is user-defined default (dummy) write data.
 * @param[in] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[out] read_data_buffer Read buffer.
 * @param[in] read_data_length Number of bytes to be read.
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_spi_master_open function.
 * @warning The following example describes only how the function is used.
 * This is not a working example.
 *
 * @b Example
 * @code
 *   // Specify length of data to be read.
 *   #define DATA_LENGTH 150
 *
 *   // Specify data structure for data to be read.
 *   uint8_t read_sequence[ DATA_LENGTH ];
 *
 *   // Read specified data on SPI bus.
 *   hal_spi_master_read( handle, &read_sequence, DATA_LENGTH );
 * @endcode
 */
err_t hal_spi_master_read( handle_t handle, uint8_t *read_data_buffer,
                                             size_t read_data_length );

/**
 * @brief Perform a sequence of SPI Master writes immediately followed by a SPI Master read.
 * @details Writes a sequence of bytes to SPI bus, followed by a corresponding read.
 * @param[in] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @param[in] write_data_buffer Value to send.
 * @param[in] length_write_data Number of bytes to write from data buffer.
 * @param[out] read_data_buffer Read buffer.
 * @param[in] length_read_data Number of bytes to be read.
 *
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #spi_master_open function.
 * Before calling this function.
 * @note If the transmitted data sequence is shorter than the received data sequence,
 * the remaining places in the data transmit buffer will be populated with user-defined data.
 * See #hal_spi_master_set_default_write_data function for more details.
 * @warning The following example describes only how the function is used.
 * This is not a working example.
 *
 * @b Example
 * @code
 *   // Specify length of data to be written and read.
 *   #define DATA_LENGTH 150
 *
 *   // Specify data structure for data to be sent.
 *   uint8_t write_sequence[ DATA_LENGTH ];
 *
 *   // Specify data structure for data to be read.
 *   uint8_t read_sequence[ DATA_LENGTH ];
 *
 *   // Specify i.e. 0th element to be sent.
 *   write_sequence[0] = 0x02;
 *
 *   // Specify i.e. 1st element to be sent.
 *   write_sequence[1] = 0x05;
 *
 *   // Write then read specified data on SPI bus.
 *   hal_spi_master_write_then_read( handle, &write_sequence,
 *                                           DATA_LENGTH,
 *                                           &read_sequence,
 *                                           DATA_LENGTH );
 * @endcode
 */
err_t hal_spi_master_write_then_read( handle_t handle, uint8_t *write_data_buffer,
                                                        size_t length_write_data,
                                                       uint8_t *read_data_buffer,
                                                        size_t length_read_data );

/**
 * @brief  Close SPI Master HAL context object.
 * @details Closes SPI Master HAL context object,
 * resets pin AF to default values and
 * clears all buffers used by object.
 * @param[in,out] handle SPI master handle.
 * See #hal_spi_master_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_spi_master_err_t, which is size dependant on the architecture.
 *
 * @b Example
 * @code
 *   // Close the SPI module object handler.
 *   hal_spi_master_close( &handle );
 * @endcode
 */
err_t hal_spi_master_close( handle_t *handle );

/*! @} */ // halspimastergroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_SPI_MASTER_H_
// ------------------------------------------------------------------------- END
