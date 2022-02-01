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
 * @file  drv_uart.h
 * @brief API for UART driver.
 */

#ifndef _DRV_UART_H_
#define _DRV_UART_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_name.h"
#include "hal_uart.h"
#include "ring.h"

/**
 * @details Return values.
 */
typedef enum
{
    UART_SUCCESS = 0,  /*!< Success. */
    UART_ERROR = (-1)  /*!< Error. */
} uart_err_t;

/**
 * @details Predefined enum values for data bit selection.
 */
typedef enum
{
    UART_DATA_BITS_7 = 0,   /*!< 7 data bits. */
    UART_DATA_BITS_8,       /*!< 8 data bits. */
    UART_DATA_BITS_9,       /*!< 9 data bits. */

    UART_DATA_BITS_DEFAULT = UART_DATA_BITS_8 /*!< Default (8 data bits). */
} uart_data_bits_t;

/**
 * @details Predefined enum values for parity selection.
 */
typedef enum
{
    UART_PARITY_NONE = 0, /*!< No parity. */
    UART_PARITY_EVEN,     /*!< Even parity. */
    UART_PARITY_ODD,      /*!< Odd parity. */

    UART_PARITY_DEFAULT = UART_PARITY_NONE /*!< Default (no parity). */
} uart_parity_t;

/**
 * @details Predefined enum values for stop bit selection.
 */
typedef enum
{
    UART_STOP_BITS_HALF = 0,       /*!< Half stop bit. */
    UART_STOP_BITS_ONE,            /*!< One stop bit. */
    UART_STOP_BITS_ONE_AND_A_HALF, /*!< One and a half stop bit. */
    UART_STOP_BITS_TWO,            /*!< Two stop bits. */

    UART_STOP_BITS_DEFAULT = UART_STOP_BITS_ONE /*!< Default (one stop bit). */
} uart_stop_bits_t;

/**
 * @brief UART init configuration structure, consisted of the following fields :
 * @details User needs to specify values herein.
 * @note Take into consideration that any value can be changed
 * explicitly by the user.
 * @warning The following example includes pins mapping.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // UART driver configuration structure.
 *   static uart_config_t uart_cfg;
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t uart_rx_buffer[128];
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t uart_tx_buffer[128];
 *
 *   // Fill structure with default values.
 *   uart_configure_default(&uart_cfg);
 *
 *   // Specify desired UART RX pin.
 *   uart_cfg.rx_pin = MIKROBUS_1_RX;
 *
 *   // Specify desired UART TX pin.
 *   uart_cfg.tx_pin = MIKROBUS_1_TX;
 *
 *   // Declare buffer size.
 *   uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
 *
 *   // Declare buffer size.
 *   uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );
 * @endcode
 */
typedef struct
{
    pin_name_t tx_pin; /*!< Tx pin. */
    pin_name_t rx_pin; /*!< Rx pin. */

    uint32_t baud;              /*!< Baud rate. */
    uart_data_bits_t data_bits; /*!< Data bits. */
    uart_parity_t parity;       /*!< Parity bits. */
    uart_stop_bits_t stop_bits; /*!< Stop bits. */

    ring_buf8_t tx_buf; /*!< Tx buffer. */
    ring_buf8_t rx_buf; /*!< Rx buffer. */

    size_t tx_ring_size; /*!< Tx ring size. */
    size_t rx_ring_size; /*!< Rx ring size. */
} uart_config_t;

/**
 * @brief UART driver context structure, consisted of the following fields :
 * @details UART driver context structure, used by every other function later on.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 * @endcode
 */
typedef struct
{
    handle_t handle; /*!< UART handle. */

    uart_config_t config; /*!< UART configuration structure. */

    uint8_t *tx_ring_buffer; /*!< Pointer to Tx ring buffer. */
    uint8_t *rx_ring_buffer; /*!< Pointer to Rx ring buffer. */

    bool is_tx_irq_enabled; /*!< Tx interrupt enabled. */
    bool is_rx_irq_enabled; /*!< Rx interrupt enabled. */

    bool is_blocking; /*!< Is blocking. */
} uart_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @{
 */

/*!
 * @addtogroup drvuartgroup UART Driver
 * @brief UART Driver API Reference.
 * @details UART DRV API layer header.
 * Contains all enums, structures and
 * function declarations available for
 * UART module.
 * @{
 */

/**
 * @brief Configure UART Driver configuration structure.
 * @details Configures #uart_config_t structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * Values need to be redefined by user.
 * @param[in,out] config configure UART driver configuration structure.
 * See #uart_config_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value             |
 * --------------------|---------------------------|
 * Tx pin              | 0xFFFFFFFF (invalid pin)  |
 * Rx pin              | 0xFFFFFFFF (invalid pin)  |
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
 *   // UART driver configuration structure.
 *   static uart_config_t uart_cfg;
 *
 *   // Fill structure with default values.
 *   uart_configure_default( &uart_cfg );
 * @endcode
 */
void uart_configure_default( uart_config_t *config );

/**
 * @brief Open the UART Driver object.
 * @details Opens the UART driver object on selected pins.
 * Allocates memory, pins and ring buffers for specified object.
 * Also, initializes interrupts on the global level.
 * @param[in,out] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] config configure UART driver configuration settings.
 * See #uart_config_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that \p configuration structure has been adequately
 * populated beforehand.
 * See #uart_configure_default definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // UART driver configuration structure.
 *   static uart_config_t uart_cfg;
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t uart_rx_buffer[128];
 *
 *   // Be careful to have large enough buffers.
 *   static uint8_t uart_tx_buffer[128];
 *
 *   // Fill structure with default values.
 *   uart_configure_default( &uart_cfg );
 *
 *   // Specify desired UART RX pin.
 *   uart_cfg.rx_pin = MIKROBUS_1_RX;
 *
 *   // Specify desired UART TX pin.
 *   uart_cfg.tx_pin = MIKROBUS_1_TX;
 *
 *   // Declare buffer size.
 *   uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
 *
 *   // Declare buffer size.
 *   uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );
 *
 *   // Initialize appropriate interrupt and allocate resources for UART module.
 *   if ( uart_open( &uart, &uart_cfg ) == UART_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t uart_open( uart_t *obj, uart_config_t *config );

/**
 * @brief Set the UART baud rate.
 * @details Sets the baud rate to specified \p baud value.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] baud Specified baud rate value.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #uart_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Set baud rate.
 *   if ( uart_set_baud( &uart, 115200 ) == UART_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t uart_set_baud( uart_t *obj, uint32_t baud );

/**
 * @brief Set the UART parity.
 * @details Sets parity scheme to be used by the UART driver.
 * @param[in,out] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] parity Parity.
 * See #uart_parity_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #uart_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Set data parity. ( no parity )
 *   if ( uart_set_parity( &uart, UART_PARITY_DEFAULT ) == UART_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t uart_set_parity( uart_t *obj, uart_parity_t parity );

/**
 * @brief Set the number of UART stop bits.
 * @details Sets the number of stop bits to be used by the UART driver.
 * @param[in,out] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] stop Stop bits.
 * See #uart_stop_bits_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #uart_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Set stop bits. ( one stop bit )
 *   if ( uart_set_stop_bits( &uart, UART_STOP_BITS_DEFAULT ) == UART_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t uart_set_stop_bits( uart_t *obj, uart_stop_bits_t stop );

/**
 * @brief Set the number of  UART data bits.
 * @details Sets the number of data bits to be used by the UART driver.
 * @param[in,out] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] bits Data bits.
 * See #uart_data_bits_t for valid values.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that adequate memory has been allocated beforehand.
 * See #uart_open definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Set data bits. ( 8-bit data )
 *   if ( uart_set_data_bits( &uart, UART_DATA_BITS_DEFAULT ) == UART_ERROR )
 *   {
 *       // Error handling strategy
 *   }
 * @endcode
 */
err_t uart_set_data_bits( uart_t *obj, uart_data_bits_t bits );

/**
 * @brief Set UART Driver in blocking/non-blocking mode.
 * @details Sets the UART driver to work in blocking/non-blocking mode.
 * @param[in,out] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] blocking \p true for blocking mode, \p false for non-blocking mode.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Set UART Driver in blocking mode.
 *   uart_set_blocking( &uart, true );
 * @endcode
 */
void uart_set_blocking( uart_t *obj, bool blocking );

/**
 * @brief Write data to UART.
 * @details Writes at most \p size bytes of data from \p buffer to the device.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] buffer Array containing data to be written.
 * @param[in] size Number of bytes to be written.
 * @return Returns the number of bytes that were actually written,
 * or -1 if an error occurred.
 * @pre Make sure that adequate memory has been allocated beforehand,
 * and the module was configured adequately ( bit-rate... ).
 * See #uart_open, #uart_set_baud, #uart_set_data_bits,
 * #uart_set_stop_bits and #uart_set_parity definition for detailed explanation.
 * @note Take into consideration that the function shall return (-1) if
 * no data was written, and appropriate error handling strategy is
 * recommended.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Data transmit buffer.
 *   uint8_t *uart_tx_buffer;
 *
 *   // Number of written bytes.
 *   static size_t size;
 *
 *   // Write size number of data from buffer.
 *   size = uart_write( &uart, uart_tx_buffer, size );
 * @endcode
 */
err_t uart_write( uart_t *obj, uint8_t *buffer, size_t size );

/**
 * @brief Print the string to UART.
 * @details Print the string pointed to by text.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] text Pointer to text array.
 * @return Returns the number of bytes that were actually written,
 * or -1 if an error occurred.
 * @pre Make sure that adequate memory has been allocated beforehand,
 * and the module was configured adequately ( bit-rate... ).
 * See #uart_open, #uart_set_baud, #uart_set_data_bits,
 * #uart_set_stop_bits and #uart_set_parity definition for detailed explanation.
 * @note Take into consideration that the function shall return (-1) if
 * no data was written, and appropriate error handling strategy is
 * recommended.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Number of written bytes.
 *   static size_t size;
 *
 *   // Print out "Hello!".
 *   size = uart_print( &uart, "Hello!" );
 * @endcode
 */
err_t uart_print( uart_t *obj, char *text );

/**
 * @brief Print the string to UART and append new line.
 * @details Print the string pointed to by text and append new line at the end.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[in] text Pointer to text array.
 * @return Returns the number of bytes that were actually written,
 * or -1 if an error occurred.
 * @pre Make sure that adequate memory has been allocated beforehand,
 * and the module was configured adequately ( bit-rate... ).
 * See #uart_open, #uart_set_baud, #uart_set_data_bits,
 * #uart_set_stop_bits and #uart_set_parity definition for detailed explanation.
 * @note Take into consideration that the function shall return (-1) if
 * no data was written, and appropriate error handling strategy is
 * recommended.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Number of written bytes.
 *   static size_t size;
 *
 *   // Print out "Hello!" and append new line.
 *   size = uart_print_ln( &uart, "Hello!" );
 * @endcode
 */
err_t uart_println( uart_t *obj, char *text );

/**
 * @brief Read data from UART.
 * @details Reads at most \p size bytes of data from the device into \p buffer.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @param[out] buffer Array to place read data in.
 * @param[in] size Number of bytes to be written.
 * @return Returns the number of bytes that were actually read,
 * or -1 if an error occurred.
 * @pre Make sure that adequate memory has been allocated beforehand,
 * and the module was configured adequately ( bit-rate... ).
 * See #uart_open, #uart_set_baud, #uart_set_data_bits,
 * #uart_set_stop_bits and #uart_set_parity definition for detailed explanation.
 * @note Take into consideration that the function shall return (-1) if
 * no data was read, and appropriate error handling strategy is
 * recommended.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Data receive buffer.
 *   uint8_t *uart_rx_buffer;
 *
 *   // Number of read bytes.
 *   static size_t size;
 *
 *   // Read data.
 *   size = uart_read( &uart, uart_rx_buffer, sizeof( buffer ) );
 * @endcode
 */
err_t uart_read( uart_t *obj, uint8_t *buffer, size_t size );

/**
 * @brief Check number of bytes available to read from UART.
 * @details Check number of bytes available to read from UART.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @return Returns the number of bytes that are available for reading.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   if ( uart_bytes_available( &uart ) )
 *   {
 *       // If it enters here, data is available for reading.
 *   }
 * @endcode
 */
size_t uart_bytes_available( uart_t *obj );

/**
 * @brief Discard all characters from UART buffers.
 * @details Discards all characters from the output and input buffer.
 * @param[in] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Clear rx and tx buffers.
 *   uart_clear( &uart );
 * @endcode
 */
void uart_clear( uart_t *obj );

/**
 * @brief Close UART Driver object.
 * @details Closes UART driver object,
 * disables all interrupts, resets pin AF to default values,
 * clears all buffers used by object and disables module
 * clock for lower power consumption.
 * @param[in,out] obj UART driver object.
 * See #uart_t structure definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *   // UART driver context structure.
 *   static uart_t uart;
 *
 *   // Close the UART module object handler.
 *   uart_close( &uart );
 * @endcode
 */
void uart_close( uart_t *obj );

/*! @} */ // drvuartgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _DRV_UART_H_
// ------------------------------------------------------------------------- END
