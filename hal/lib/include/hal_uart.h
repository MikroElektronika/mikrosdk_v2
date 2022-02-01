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
 * @file  hal_uart.h
 * @brief API for UART HAL level.
 */

#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"
#include "ring.h"

/**
 * @details The context for storing  HAL level object handlers.
 * Contains specific hardware module handle and
 * said module init state.
 * @warning User is not to change these values or
 * unexpected behaviour may occur.
 */
typedef struct
{
    handle_t *hal_uart_handle; /*!< UART HAL level handle */
    handle_t *drv_uart_handle; /*!< UART DRV level handle */
    bool init_state;           /*!< UART HAL object init state */
} hal_uart_handle_register_t;

/**
 * @details Return values.
 */
typedef enum
{
    HAL_UART_SUCCESS = 0,  /*!< Success. */
    HAL_UART_WRONG_PINS,   /*!< Wrong pins selected. */
    HAL_UART_MODULE_ERROR, /*!< Object wasn't closed. */

    HAL_UART_ERROR = (-1)  /*!< Error. */
} hal_uart_err_t;

/**
 * @brief Predefined enum values for interrupt request type.
 */
typedef enum
{
    HAL_UART_IRQ_RX, /*!< RX INT. */
    HAL_UART_IRQ_TX  /*!< TX INT. */
} hal_uart_irq_t;

/**
 * @brief Predefined enum values for data bit selection.
 */
typedef enum
{
    HAL_UART_DATA_BITS_7 = 0,   /*!< 7 data bits. */
    HAL_UART_DATA_BITS_8,       /*!< 8 data bits. */
    HAL_UART_DATA_BITS_9,       /*!< 9 data bits. */

    HAL_UART_DATA_BITS_DEFAULT = HAL_UART_DATA_BITS_8 /*!< Default (8 data bits). */
} hal_uart_data_bits_t;

/**
 * @brief Predefined enum values for parity selection.
 */
typedef enum
{
    HAL_UART_PARITY_NONE = 0, /*!< No parity. */
    HAL_UART_PARITY_EVEN,     /*!< Even parity. */
    HAL_UART_PARITY_ODD,      /*!< Odd parity. */

    HAL_UART_PARITY_DEFAULT = HAL_UART_PARITY_NONE /*!< Default (no parity). */
} hal_uart_parity_t;

/**
 * @brief Predefined enum values for stop bit selection.
 */
typedef enum
{
    HAL_UART_STOP_BITS_HALF = 0,       /*!< Half stop bit. */
    HAL_UART_STOP_BITS_ONE,            /*!< One stop bit. */
    HAL_UART_STOP_BITS_ONE_AND_A_HALF, /*!< One and a half stop bit. */
    HAL_UART_STOP_BITS_TWO,            /*!< Two stop bits. */

    HAL_UART_STOP_BITS_DEFAULT = HAL_UART_STOP_BITS_ONE /*!< Default (one stop bit). */
} hal_uart_stop_bits_t;

/**
 * @brief UART HAL init configuration structure, consisted of the following fields :
 * @details User needs to specifiy values herein.
 * @note Take into consideration that any value can be changed explicitly by the user.
 *
 * @b Example
 * @code
 *   // UART HAL config structure.
 *   static hal_uart_config_t hal_uart_cfg;
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t hal_uart_rx_buffer[128];
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t hal_uart_tx_buffer[128];
 *
 *   // Fill structure with default values.
 *   hal_uart_configure_default( &hal_uart_cfg );
 *
 *   // Specify desired UART RX pin.
 *   hal_uart_cfg.rx_pin = MIKROBUS_1_RX;
 *
 *   // Specify desired UART TX pin.
 *   hal_uart_cfg.tx_pin = MIKROBUS_1_TX;
 *
 *   // Declare buffer size.
 *   hal_uart_cfg.tx_ring_size = sizeof( hal_uart_tx_buffer );
 *
 *   // Declare buffer size.
 *   hal_uart_cfg.rx_ring_size = sizeof( hal_uart_rx_buffer );
 * @endcode
 */
typedef struct
{
    hal_pin_name_t tx_pin; /*!< Tx pin. */
    hal_pin_name_t rx_pin; /*!< Rx pin. */

    uint32_t baud;                  /*!< Baud rate. */
    hal_uart_data_bits_t data_bits; /*!< Data bits. See #hal_uart_data_bits_t for valid values.*/
    hal_uart_parity_t parity;       /*!< Parity bits. See #hal_uart_parity_t for valid values.*/
    hal_uart_stop_bits_t stop_bits; /*!< Stop bits. See #hal_uart_stop_bits_t for valid values.*/

    ring_buf8_t tx_buf; /*!< Tx buffer. */
    ring_buf8_t rx_buf; /*!< Rx buffer. */

    size_t tx_ring_size; /*!< Tx ring size. */
    size_t rx_ring_size; /*!< Rx ring size. */
} hal_uart_config_t;

/**
 * @brief UART HAL context structure, consisted of the following fields :
 * @details UART HAL context structure, used by every other function later on.
 *
 * @b Example
 * @code
 *   // UART HAL context structure.
 *   static hal_uart_t hal_uart;
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< UART HAL handle. */

    hal_uart_config_t config; /*!< UART HAL configuration structure. */

    uint8_t *tx_ring_buffer; /*!< Pointer to Tx ring buffer. */
    uint8_t *rx_ring_buffer; /*!< Pointer to Rx ring buffer. */

    bool is_tx_irq_enabled; /*!< Tx interrupt enabled. */
    bool is_rx_irq_enabled; /*!< Rx interrupt enabled. */

    bool is_blocking; /*!< Is blocking. */
} hal_uart_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/*!
 * @addtogroup haluartgroup UART HAL
 * @brief UART Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating UART HAL module.
 * @{
 */

/**
 * @brief Configure UART configuration structure with default values.
 * @details Configures structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config UART HAL layer configuration structure.
 * See #hal_uart_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * Tx pin              | HAL_PIN_NC (invalid pin)  |
 * Rx pin              | HAL_PIN_NC (invalid pin)  |
 * Baud rate           | 115200                    |
 * Data bits           | 8 data bits               |
 * Parity              | no parity                 |
 * Stop bits           | 1 stop bit                |
 * Tx buffer           | cleared                   |
 * Rx buffer           | cleared                   |
 * Tx ring buffer size | zero                      |
 * Rx ring buffer size | zero                      |
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // UART HAL config structure.
 *   static hal_uart_config_t hal_uart_cfg;
 *
 *   // Fill structure with default values.
 *   hal_uart_configure_default( &hal_uart_cfg );
 * @endcode
 */
void hal_uart_configure_default( hal_uart_config_t *config );

/**
 * @brief Open the UART HAL layer object on selected pins.
 * @details Function opens the UART HAL layer object on selected pins and allocates memory needed for UART module,
 * pins and ring buffers for specified object.
 * Also, initializes interrupts on the global level.
 * @param[in,out] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] hal_obj_open_state UART state, is it open or not.
 * @return The function can return one of the values defined in the #hal_uart_err_t
 * enum list.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // UART HAL context structure.
 *   static hal_uart_t hal_uart;
 *
 *   // UART HAL config structure.
 *   static hal_uart_config_t hal_uart_cfg;
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t hal_uart_rx_buffer[128];
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t hal_uart_tx_buffer[128];
 *
 *   // Fill structure with default values.
 *   uart_configure_default( &hal_uart_cfg );
 *
 *   // Specify desired UART RX pin.
 *   hal_uart_cfg.rx_pin = MIKROBUS_1_RX;
 *
 *   // Specify desired UART TX pin.
 *   hal_uart_cfg.tx_pin = MIKROBUS_1_TX;
 *
 *   // Declare buffer size.
 *   hal_uart_cfg.tx_ring_size = sizeof( hal_uart_tx_buffer );
 *
 *   // Declare buffer size.
 *   hal_uart_cfg.rx_ring_size = sizeof( hal_uart_rx_buffer );
 *
 *   // Initialize appropriate interrupt and allocate resources for UART module.
 *   if ( hal_uart_open( &hal_uart->handle, true ) == HAL_UART_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t hal_uart_open( handle_t *handle, bool hal_obj_open_state );

/**
 * @brief Set the UART baud rate.
 * @details Initializes module on the hardware level and sets
 * the baud rate to specified \p config->baud value.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] config UART HAL config structure.
 * See #hal_uart_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_uart_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 * @warning Take into consideration that if the difference
 * between desired baud rate and actual baud
 * rate the hw was initialized to is greater than
 * 1%, baud rate shall not be set.
 *
 * @b Example
 * @code
 *   // Set baud rate.
 *   hal_uart_set_baud( &hal_uart->handle, &hal_uart->config );
 * @endcode
 */
err_t hal_uart_set_baud( handle_t *handle, hal_uart_config_t *config );

/**
 * @brief Set the UART parity.
 * @details Sets parity on hardware level based on \p config->parity value.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] config UART HAL config structure.
 * @return The function can return one of the values defined by
 * #hal_uart_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   // Set data parity.
 *   hal_uart_set_parity( &hal_uart->handle, &hal_uart->parity );
 * @endcode
 */
err_t hal_uart_set_parity( handle_t *handle, hal_uart_config_t *config );

/**
 * @brief Set the number of UART stop bits.
 * @details Sets stop bits on hardware level based on \p config->stop_bits value.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] config UART HAL config structure.
 * @return The function can return one of the values defined by
 * #hal_uart_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   // Set stop bits.
 *   hal_uart_set_stop_bits( &hal_uart->handle, &hal_uart->stop_bits );
 * @endcode
 */
err_t hal_uart_set_stop_bits( handle_t *handle, hal_uart_config_t *config );

/**
 * @brief Set the number of UART data bits.
 * @details Sets data bits on hardware level based on \p config->data_bits value.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] config UART HAL config structure.
 * @return The function can return one of the values defined by
 * #hal_uart_err_t, which is size dependant on the architecture.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   // Set data bits.
 *   hal_uart_set_data_bits( &hal_uart->handle, &hal_uart->data_bits );
 * @endcode
 */
err_t hal_uart_set_data_bits( handle_t *handle, hal_uart_config_t *config );

/**
 * @brief Set UART HAL in blocking/non-blocking mode.
 * @details Sets the UART HAL to work in blocking/non-blocking mode.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] blocking \p true for blocking mode, \p false for non-blocking mode.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Set transmit/receive mode to be blocking/non-blocking.
 *   hal_uart_set_blocking( &hal_uart->handle, true );
 * @endcode
 */
void hal_uart_set_blocking( handle_t *handle, bool blocking );

/**
 * @brief Write data to UART.
 * @details Writes at most \p size bytes of data from \p buffer to the device.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] buffer Array containing data to be written.
 * @param[in] size Number of bytes to be written.
 * @return Returns the number of bytes that were actually written,
 * or -1 if an error occurred or no data written.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   static size_t size;
 *
 *   // Write size number of data from buffer.
 *   size = hal_uart_write( &hal_uart->handle, hal_uart_tx_buffer, size );
 * @endcode
 */
size_t hal_uart_write( handle_t *handle, uint8_t *buffer, size_t size );

/**
 * @brief Print the string to UART.
 * @details Print the string pointed to by text.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] text Pointer to text array.
 * @return Returns the number of bytes that were actually written,
 * or -1 if an error occurred or no data written.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example :
 * @code
 *   static size_t size;
 *
 *   // Print out "Hello!".
 *   size = hal_uart_print( &hal_uart->handle, "Hello!" );  // Print out "Hello!".
 * @endcode
 */
size_t hal_uart_print( handle_t *handle, char *text );

/**
 * @brief Print the string to UART and append new line.
 * @details Print the string pointed to by text and append new line at the end.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[in] text Pointer to text array.
 * @return Returns the number of bytes that were actually written,
 * or -1 if an error occurred or no data written.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   static size_t size;
 *
 *   // Print out "Hello!" and append new line.
 *   size = hal_uart_print_ln( &hal_uart, "Hello!" );
 * @endcode
 */
size_t hal_uart_println( handle_t *handle, char *text );

/**
 * @brief Read data from UART.
 * @details Reads at most \p size bytes of data from the device into \p buffer.
 * @param[in] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @param[out] buffer Array to place read data in.
 * @param[in] size Number of bytes to be written.
 * @return Returns the number of bytes that were actually read,
 * or -1 if an error occurred or no data read.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #hal_uart_open definition for detailed explanation.
 *
 * @b Example
 * @code
 *   static size_t size;
 *
 *   // Read data.
 *   size = hal_uart_read( &hal_uart->handle, hal_uart_rx_buffer, sizeof( buffer ) );
 * @endcode
 */
size_t hal_uart_read( handle_t *handle, uint8_t *buffer, size_t size );

/**
 * @brief Check number of data available to read.
 * @details Check number of data available to read.
 * @param[in] hal_obj UART HAL object.
 * See #hal_uart_t structure definition for detailed explanation.
 * @return Returns the number of bytes that are available for reading.
 *
 * @b Example
 * @code
 *   if ( hal_uart_bytes_available( &hal_uart ) )
 *   {
 *       // If it enters here, data is available for reading.
 *   }
 * @endcode
 */
size_t hal_uart_bytes_available( hal_uart_t *hal_obj );

/**
 * @brief Discard all characters from UART buffers.
 * @details Discards all characters from the output and input buffer.
 * @param[in] hal_obj UART HAL object.
 * See #hal_uart_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Clear rx and tx buffers.
 *   hal_uart_clear( &hal_uart );
 * @endcode
 */
void hal_uart_clear( hal_uart_t *hal_obj );

/**
 * @brief Close UART HAL layer object.
 * @details Closes UART HAL layer object,
 * disables all interrupts, resets pin AF to default values,
 * clears all buffers used by object and disables module
 * clock for lower power consumption.
 * @param[in,out] handle UART handle.
 * See #hal_uart_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // Close the UART HAL module object handler.
 *   hal_uart_close( &hal_uart->handle );
 * @endcode
 */
err_t hal_uart_close( handle_t *handle );

/*! @} */ // haluartgroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_UART_H_
// ------------------------------------------------------------------------- END
