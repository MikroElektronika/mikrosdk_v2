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
 * @file  hal_ll_sau_uart.h
 * @brief API for SAU sub-implementation of UART module.
 */

#ifndef _HAL_LL_SAU_UART_H_
#define _HAL_LL_SAU_UART_H_

/**
 * @brief Interrupt request type enum.
 */
typedef enum
{
    HAL_LL_SAU_UART_IRQ_RX, /**< RX INT   */
    HAL_LL_SAU_UART_IRQ_TX  /**< TX INT   */
} hal_ll_sau_uart_irq_t;

/*!< @brief SAU module state selection. */
typedef enum {
    HAL_LL_SAU_DISABLE = 0,
    HAL_LL_SAU_ENABLE
} hal_ll_sau_state_t;

/**
 * @brief Predefined enum values for parity selection.
 */
typedef enum
{
    HAL_LL_SAU_UART_PARITY_NONE = 0,
    HAL_LL_SAU_UART_PARITY_EVEN,
    HAL_LL_SAU_UART_PARITY_ODD,

    HAL_LL_SAU_UART_PARITY_DEFAULT = HAL_LL_SAU_UART_PARITY_NONE
} hal_ll_sau_uart_parity_t;

/**
 * @brief Predefined enum values for stop bit selection.
 */
typedef enum
{
    HAL_LL_SAU_UART_STOP_BITS_HALF = 0,
    HAL_LL_SAU_UART_STOP_BITS_ONE,
    HAL_LL_SAU_UART_STOP_BITS_ONE_AND_A_HALF,
    HAL_LL_SAU_UART_STOP_BITS_TWO,

    HAL_LL_SAU_UART_STOP_BITS_DEFAULT = HAL_LL_SAU_UART_STOP_BITS_ONE
} hal_ll_sau_uart_stop_bits_t;

/**
 * @brief Predefined enum values for data bit selection.
 */
typedef enum
{
    HAL_LL_SAU_UART_DATA_BITS_5 = -2,
    HAL_LL_SAU_UART_DATA_BITS_6,
    HAL_LL_SAU_UART_DATA_BITS_7,
    HAL_LL_SAU_UART_DATA_BITS_8,
    HAL_LL_SAU_UART_DATA_BITS_9,

    HAL_LL_SAU_UART_DATA_BITS_DEFAULT = HAL_LL_SAU_UART_DATA_BITS_8
} hal_ll_sau_uart_data_bits_t;

/**
 * @brief SAU_UART low level pins config structure.
 *
 * The context structure for storing low level pin configuration
 * for both TX and RX pins.
 *
 */
typedef struct
{
    hal_ll_pin_af_t tx_pin;
    hal_ll_pin_af_t rx_pin;
} hal_ll_sau_uart_pins_t;

/*!< @brief SAU_UART baud rate structure. */
typedef struct {
    uint32_t baud;
    uint32_t real_baud;
} hal_ll_sau_uart_baud_t;

/*!< @brief SAU_UART hw specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_sau_uart_pins_t pins;
    hal_ll_sau_uart_baud_t baud_rate;
    hal_ll_sau_uart_parity_t parity;
    hal_ll_sau_uart_stop_bits_t stop_bit;
    hal_ll_sau_uart_data_bits_t data_bit;
    uint32_t timeout_polling_write;
    uint8_t sau_tx_channel;
    uint8_t sau_rx_channel;
    bool is_sau_module;
} hal_ll_sau_uart_hw_specifics_map_t;

/**
 * @brief  Enables module specific interrupt.
 *
 * Enables module specific interrupt and registers
 * interrupt on hardware level and enables it.
 *
 * @param[in] map - Object specific context handler.
 * @param[in] irq Chip interrupt IRQ value.
 *
 * @return void None.
 */
void hal_ll_sau_uart_irq_enable( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_uart_irq_t irq );

/**
 * @brief  Disables module specific interrupt.
 *
 * Disables module specific interrupt.
 *
 * @param[in] map - Object specific context handler.
 * @param[in] irq Chip interrupt IRQ value.
 *
 * @return void None.
 */
void hal_ll_sau_uart_irq_disable( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_uart_irq_t irq );

/**
 * @brief  Performs read operation.
 *
 * Reads one byte on a hardware level.
 *
 * @param[in] map - Object specific context handler.
 *
 * @return uint8_t Data read from hw register.
 */
uint8_t hal_ll_sau_uart_read( hal_ll_sau_uart_hw_specifics_map_t *map );

/**
 * @brief  Performs read operation in polling mode.
 *
 * Reads one byte on a hardware level.
 *
 * @param[in] map - Object specific context handler.
 *
 * @return uint8_t Data read from hw register.
 */
uint8_t hal_ll_sau_uart_read_polling( hal_ll_sau_uart_hw_specifics_map_t *map );

/**
 * @brief  Performs write operation.
 *
 * Accesses hardware data registers and
 * writes data directly to it.
 *
 * @param[in] map - Object specific context handler.
 * @param[in] wr_data Data to be written.
 *
 * @return void None.
 */
void hal_ll_sau_uart_write( hal_ll_sau_uart_hw_specifics_map_t *map, uint8_t wr_data);

/**
 * @brief  Performs write operation in polling mode.
 *
 * Accesses hardware data registers and
 * writes data directly to it.
 *
 * @param[in] map - Object specific context handler.
 * @param[in] wr_data Data to be written.
 *
 * @return void None.
 */
void hal_ll_sau_uart_write_polling( hal_ll_sau_uart_hw_specifics_map_t *map, uint8_t wr_data);

/**
 * @brief  Initialize SAU module in UART mode on the hardware level.
 *
 * Performs SAU module initialization in UART mode on
 * the hardware level.
 *
 * Procedure:
 * 1. Clears control registers
 * 2. Sets data bit value
 * 3. Sets parity value
 * 4. Sets stop bit value
 * 5. Sets baud rate value
 * 6. Enables transmit pin
 * 7. Enables receive pin
 * 8. Enables clock gate for specific module
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
void hal_ll_sau_uart_hw_init( hal_ll_sau_uart_hw_specifics_map_t *map );

/**
  * @brief  Clears SAU_UART registers.
  *
  * Clears SAU_UART module configuration
  * registers, effectively disabling the module itself.
  * Take into consideration that any IRQ bits
  * are not cleared.
  *
  * @param[in] map - Object specific context handler.
  *
  * @return void None.
  */
void hal_ll_sau_uart_clear_regs( hal_ll_sau_uart_hw_specifics_map_t *map );

#endif // _HAL_LL_SAU_UART_H_
// ------------------------------------------------------------------------- END
