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
 * @file  hal_ll_uart.h
 * @brief API for UART HAL LOW LEVEL layer.
 */

#ifndef _HAL_LL_UART_H_
#define _HAL_LL_UART_H_

#include "hal_ll_target.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Interrupt request type enum.
 */
typedef enum
{
    HAL_LL_UART_IRQ_RX, /**< RX INT   */
    HAL_LL_UART_IRQ_TX  /**< TX INT   */
} hal_ll_uart_irq_t;

/**
 * @brief Pointer to interrupt handler function.
 */
typedef void ( *hal_ll_uart_isr_t )( handle_t handle, hal_ll_uart_irq_t event );

/**
 * @brief Predefined enum values for parity selection.
 */
typedef enum
{
    HAL_LL_UART_PARITY_NONE = 0,
    HAL_LL_UART_PARITY_EVEN,
    HAL_LL_UART_PARITY_ODD,

    HAL_LL_UART_PARITY_DEFAULT = HAL_LL_UART_PARITY_NONE
} hal_ll_uart_parity_t;

/**
 * @brief Predefined enum values for stop bit selection.
 */
typedef enum
{
    HAL_LL_UART_STOP_BITS_HALF = 0,
    HAL_LL_UART_STOP_BITS_ONE,
    HAL_LL_UART_STOP_BITS_ONE_AND_A_HALF,
    HAL_LL_UART_STOP_BITS_TWO,

    HAL_LL_UART_STOP_BITS_DEFAULT = HAL_LL_UART_STOP_BITS_ONE
} hal_ll_uart_stop_bits_t;

/**
 * @brief Predefined enum values for data bit selection.
 */
typedef enum
{
    HAL_LL_UART_DATA_BITS_7 = 0,
    HAL_LL_UART_DATA_BITS_8,
    HAL_LL_UART_DATA_BITS_9,

    HAL_LL_UART_DATA_BITS_DEFAULT = HAL_LL_UART_DATA_BITS_8
} hal_ll_uart_data_bits_t;

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
    hal_ll_pin_af_t tx_pin;
    hal_ll_pin_af_t rx_pin;
} hal_ll_uart_pins_t;

/**
 * @brief I2C master low level handle.
 *
 * The context for storing low level object handler.
 * User is not to change these values or unexpected behaviour
 * may occur.
 */
typedef struct
{
    handle_t *hal_ll_uart_handle;
    handle_t *hal_drv_uart_handle;
    bool init_ll_state;
} hal_ll_uart_handle_register_t;

/**
 * @brief  Registers handler for future use.
 *
 * Registers low level and hal level handlers
 * for use with appropriate functions.
 *
 * @param[in] tx_pin UART TX pin.
 * @param[in] rx_pin UART RX pin.
 * @param[in] *handle_map HAL layer local handle map.
 * @param[in] *hal_module_id HAL layer module number.

 * @return hal_ll_err_t Module specific error.
 *
 * Returns one of pre-defined values.
 * Take into consideration that this is hardware specific.
 */
hal_ll_err_t hal_ll_uart_register_handle( hal_ll_pin_name_t tx_pin, hal_ll_pin_name_t rx_pin, hal_ll_uart_handle_register_t *handle_map, uint8_t *hal_module_id );

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
hal_ll_err_t hal_ll_module_configure_uart( handle_t *handle );

/**
 * @brief  Registers interrupt handlers for future use.
 *
 * Registers low level interrupt handlers
 * for use with appropriate functions.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] handler Predefined pointer function.
 * @param[in] obj HAL context handle address.

 * @return None.
 */
void hal_ll_uart_register_irq_handler( handle_t *handle, hal_ll_uart_isr_t handler, handle_t obj );

/**
 * @brief  Sets desired baud rate.
 *
 * Initializes module with specified baud rate value.
 * Take into consideration that if the difference
 * between desired baud rate and actual baud
 * rate the hw was initialized to is greater than
 * 1%, baud rate shall not be set.
 * If this occurs, return value shall be
 * the error percentage.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] baud Desired baud rate value in Bits/s.
 *
 * @return Actual baud rate value the hw module was initialized to,
 *              or module specific error value if init failed.
 */
hal_ll_err_t hal_ll_uart_set_baud( handle_t *handle, uint32_t baud );

/**
 * @brief  Sets desired parity.
 *
 * Initializes module with specified parity value.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] parity One of pre-defined values.
 *
 * @return Re-init module state. If neccessary.
 */
hal_ll_err_t hal_ll_uart_set_parity( handle_t *handle, hal_ll_uart_parity_t parity );

/**
 * @brief  Sets desired stop bits.
 *
 * Initializes module with specified stop bits value.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] stop_bit One of pre-defined values.
 *
 * @return Re-init module state. If neccessary.
 */
hal_ll_err_t hal_ll_uart_set_stop_bits( handle_t *handle, hal_ll_uart_stop_bits_t stop_bit );

/**
 * @brief  Sets desired data bits.
 *
 * Initializes module with specified data bits value.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] data_bit One of pre-defined values.
 *
 * @return Re-init module state. If neccessary.
 */
hal_ll_err_t hal_ll_uart_set_data_bits( handle_t *handle, hal_ll_uart_data_bits_t data_bit );

/**
 * @brief  Enables module specific interrupt.
 *
 * Enables module specific interrupt and registers
 * interrupt on hardware level and enables it.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] irq Chip interrupt IRQ value.
 *
 * @return void None.
 */
void hal_ll_uart_irq_enable( handle_t *handle, hal_ll_uart_irq_t irq );

/**
 * @brief  Disables module specific interrupt.
 *
 * Disables module specific interrupt.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] irq Chip interrupt IRQ value.
 *
 * @return void None.
 */
void hal_ll_uart_irq_disable( handle_t *handle, hal_ll_uart_irq_t irq );

/**
 * @brief  Performs read operation.
 *
 * Reads one byte on a hardware level.
 *
 * @param[in] handle HAL context object handle.
 *
 * @return uint16_t Data read from hw register.
 */
uint16_t hal_ll_uart_read( handle_t *handle );

/**
 * @brief  Performs write operation.
 *
 * Accesses hardware data registers and
 * writes data directly to it.
 *
 * @param[in] handle HAL context object handle.
 * @param[in] wr_data Data to be written.
 *
 * @return void None.
 */
void hal_ll_uart_write( handle_t *handle, uint16_t wr_data);

/**
 * @brief  Closes UART HAL and HAL_LOW_LEVEL context object.
 *
 * De-allocates hardware resources for specific driver object and
 * de-initializes the module on a hardware level.
 *
 * @param[in] *handle HAL context object handle.
 *
 * @return void None.
 */
void hal_ll_uart_close( handle_t *handle );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_UART_H_
// ------------------------------------------------------------------------- END
