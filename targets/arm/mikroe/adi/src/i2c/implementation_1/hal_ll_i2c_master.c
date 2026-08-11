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
 * @file  hal_ll_i2c_master.c
 * @brief I2C master HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"
#include "hal_ll_i2c_pin_map.h"
#include "hal_ll_pclkdis.h"
#include "delays.h"
#include <stdbool.h>

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = {0};

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base
/*!< @brief Helper macro for getting bit rate configuration values */
#define hal_ll_i2c_get_bitrate_error(real_bitrate, bitrate) (((float)real_bitrate - (float)bitrate)/(float)bitrate)

#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_PORT_PULL_UP_ENABLE |\
                              GPIO_CFG_DIGITAL_OUTPUT |\
                              GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE |\
                              GPIO_CFG_PERIPHERAL_PIN)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K    (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K    (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M      (1000000UL)
#define HAL_LL_I2C_MASTER_SPEED_3M2     (3200000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT   (10000)

/*!< @brief CTRL register bits */
#define HAL_LL_I2C_CTRL_EN                  (0)
#define HAL_LL_I2C_CTRL_MST_MODE            (1)
#define HAL_LL_I2C_CTRL_HS_EN               (15)

/*!< @brief STATUS register bits */
#define HAL_LL_I2C_STATUS_BUSY              (0)
#define HAL_LL_I2C_STATUS_RX_EMPTY          (1)
#define HAL_LL_I2C_STATUS_TX_EMPTY          (3)
#define HAL_LL_I2C_STATUS_TX_FULL           (4)

/*!< @brief INTFL0 register bits */
#define HAL_LL_I2C_INTFL0_DONE_BIT          (0)
#define HAL_LL_I2C_INTFL0_ARB_ERR_BIT       (8)
#define HAL_LL_I2C_INTFL0_TO_ERR_BIT        (9)

/*!< @brief MSTCTRL register bits */
#define HAL_LL_I2C_MSTCTRL_START            (0)
#define HAL_LL_I2C_MSTCTRL_RESTART          (1)
#define HAL_LL_I2C_MSTCTRL_STOP             (2)

/*!< @brief INTFL0 register masks */
#define HAL_LL_I2C_INTFL0_DONE              (0x1)
#define HAL_LL_I2C_INTFL0_RX_THD            (0x10)
#define HAL_LL_I2C_INTFL0_STOP              (0x40)
#define HAL_LL_I2C_INTFL0_ARB_ERR           (0x100)
#define HAL_LL_I2C_INTFL0_TO_ERR            (0x200)
#define HAL_LL_I2C_INTFL0_ERROR_MASK        (0xFF00)
#define HAL_LL_I2C_INTFL0_CLEAR_MASK        (0xFFFFFF)

/*!< @brief INTFL1 register masks */
#define HAL_LL_I2C_INTFL1_ERROR_MASK        (0x3)
#define HAL_LL_I2C_INTFL1_CLEAR_MASK        (0x7)

/*!< @brief RXCTRL0 register fields */
#define HAL_LL_I2C_RXCTRL0_FLUSH            (7)
#define HAL_LL_I2C_RXCTRL0_THD_VALUE        (0x600)

/*!< @brief RXCTRL1 register fields */
#define HAL_LL_I2C_RXCTRL1_COUNT_MASK       (0xFF)
#define HAL_LL_I2C_RXCTRL1_MAX_COUNT        (256)

/*!< @brief TXCTRL0 register fields */
#define HAL_LL_I2C_TXCTRL0_FLUSH            (7)
#define HAL_LL_I2C_TXCTRL0_THD_VALUE        (0x200)

/*!< @brief FIFO register fields */
#define HAL_LL_I2C_FIFO_ADDR_POS            (1)
#define HAL_LL_I2C_FIFO_ADDR_READ           (1)

/*!< @brief CLKLO and CLKHI register field masks */
#define HAL_LL_I2C_CLKLO_COUNT_MASK         (0x1FF)
#define HAL_LL_I2C_CLKHI_COUNT_MASK         (0x1FF)

/*!< @brief MSTCTRL register masks */
#define HAL_LL_I2C_MSTCTRL_RESTART_MASK     (0x2)
#define HAL_LL_I2C_MSTCTRL_STOP_MASK        (0x4)

/*!< @brief MAX32690 I2C peripheral input clock */
#define HAL_LL_I2C_PERIPHERAL_CLOCK     (((uint32_t)FOSC_KHZ_VALUE * 1000UL) / 2UL)

/*!< @brief I2C register structure */
typedef struct {
    uint32_t ctrl;                 /**< <tt>\b 0x00:</tt> I2C CTRL Register */
    uint32_t status;               /**< <tt>\b 0x04:</tt> I2C STATUS Register */
    uint32_t intfl0;               /**< <tt>\b 0x08:</tt> I2C INTFL0 Register */
    uint32_t inten0;               /**< <tt>\b 0x0C:</tt> I2C INTEN0 Register */
    uint32_t intfl1;               /**< <tt>\b 0x10:</tt> I2C INTFL1 Register */
    uint32_t inten1;               /**< <tt>\b 0x14:</tt> I2C INTEN1 Register */
    uint32_t fifolen;              /**< <tt>\b 0x18:</tt> I2C FIFOLEN Register */
    uint32_t rxctrl0;              /**< <tt>\b 0x1C:</tt> I2C RXCTRL0 Register */
    uint32_t rxctrl1;              /**< <tt>\b 0x20:</tt> I2C RXCTRL1 Register */
    uint32_t txctrl0;              /**< <tt>\b 0x24:</tt> I2C TXCTRL0 Register */
    uint32_t txctrl1;              /**< <tt>\b 0x28:</tt> I2C TXCTRL1 Register */
    uint32_t fifo;                 /**< <tt>\b 0x2C:</tt> I2C FIFO Register */
    uint32_t mstctrl;              /**< <tt>\b 0x30:</tt> I2C MSTCTRL Register */
    uint32_t clklo;                /**< <tt>\b 0x34:</tt> I2C CLKLO Register */
    uint32_t clkhi;                /**< <tt>\b 0x38:</tt> I2C CLKHI Register */
    uint32_t hsclk;                /**< <tt>\b 0x3C:</tt> I2C HSCLK Register */
    uint32_t timeout;              /**< <tt>\b 0x40:</tt> I2C TIMEOUT Register */
    uint32_t __unused0;
    uint32_t dma;                  /**< <tt>\b 0x48:</tt> I2C DMA Register */
    uint32_t slave_multi[4];   /**< <tt>\b 0x4C:</tt> I2C SLAVE_MULTI Register */
} hal_ll_i2c_base_handle_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific module values */
typedef struct {
    uint32_t pin_scl;
    uint32_t pin_sda;
} hal_ll_i2c_pin_id;

/*!< @brief I2C end mode selection values */
typedef enum {
    HAL_LL_I2C_MASTER_END_MODE_RESTART = 0,
    HAL_LL_I2C_MASTER_END_MODE_STOP,
    HAL_LL_I2C_MASTER_WRITE_THEN_READ
} hal_ll_i2c_master_end_mode_t;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_I2C_MASTER_SUCCESS = 0,
    HAL_LL_I2C_MASTER_WRONG_PINS,
    HAL_LL_I2C_MASTER_MODULE_ERROR,

    HAL_LL_I2C_MASTER_ERROR = (-1)
} hal_ll_i2c_master_err_t;

/*!< @brief I2C timeout error values */
typedef enum {
    HAL_LL_I2C_MASTER_TIMEOUT_START = 1300,
    HAL_LL_I2C_MASTER_TIMEOUT_STOP,
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_INIT,
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE
} hal_ll_i2c_master_timeout_t;

/*!< @brief Enum containing predefined module standard speed values */
typedef enum {
    HAL_LL_I2C_MASTER_SPEED_STANDARD = 0,
    HAL_LL_I2C_MASTER_SPEED_FULL,
    HAL_LL_I2C_MASTER_SPEED_FAST
} hal_ll_i2c_master_speed_t;

// ------------------------------------------------------------------ VARIABLES
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] = {
    #ifdef I2C_MODULE_0
    {HAL_LL_I2C0_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
     HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_1
    {HAL_LL_I2C1_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_1 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
     HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif
    #ifdef I2C_MODULE_2
    {HAL_LL_I2C2_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_2 ),
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0},
     HAL_LL_I2C_MASTER_SPEED_100K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
     {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Enable or disable the I2C hardware module.
 *
 * Controls the peripheral clock state for the selected I2C instance.
 *
 * @param[in] *map         Object-specific context handler.
 * @param[in] hal_ll_state Desired module state: true to enable, false to disable.
 *
 * @return None.
 */
static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
 * @brief Initialize the I2C module on hardware level.
 *
 * Resets the master configuration registers, configures FIFO thresholds,
 * flushes both FIFOs, and places the peripheral in master mode.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return None.
 */
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Perform the complete I2C module initialization procedure.
 *
 * Enables the peripheral clock, initializes the I2C hardware, and applies
 * the configured bus speed.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return None.
 */
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Set I2C pin alternate-function state.
 *
 * Configures or releases SCL and SDA using the alternate-function values
 * selected from the I2C pin maps.
 *
 * @param[in] *map         Object-specific context handler.
 * @param[in] hal_ll_state Desired pin state: true to configure, false to release.
 *
 * @return None.
 */
static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

/**
 * @brief Get the local hardware-specific map.
 *
 * Matches the supplied handle against the registered I2C base addresses.
 *
 * @param[in] handle Object-specific context handler.
 *
 * @return Pointer to the matching hardware-specific map entry, or the
 *         sentinel error entry when no match is found.
 */
static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
 * @brief Check whether the selected SCL and SDA pins form a valid I2C pair.
 *
 * The function searches the pin maps for SCL/SDA entries that belong to the
 * same hardware module and records the matching map indexes.
 *
 * @param[in]  scl         SCL pin name.
 * @param[in]  sda         SDA pin name.
 * @param[out] *index_list Array receiving SCL/SDA map indexes for the module.
 * @param[in]  *handle_map I2C handle table used to determine module ownership.
 *
 * @return Matching module-map index, or HAL_LL_PIN_NC if the pair is invalid.
 */
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map );

/**
 * @brief Map the selected SCL and SDA pins to an I2C module.
 *
 * Copies pin names and alternate-function values from the pin maps into the
 * hardware-specific module map.
 *
 * @param[in] module_index I2C hardware-map index.
 * @param[in] *index_list  Array containing SCL and SDA pin-map indexes.
 *
 * @return None.
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list );

/**
 * @brief Wait until the I2C bus becomes idle.
 *
 * Polls STATUS.BUSY and also checks hardware error flags while waiting.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on success, otherwise a module-specific
 *         timeout or hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Get the supported I2C bit rate closest to the requested value.
 *
 * @param[in] bit_rate Requested I2C bit rate.
 *
 * @return One of the supported 100 kHz, 400 kHz, or 1 MHz values.
 */
static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate );

/**
 * @brief Configure CLKLO and CLKHI for the selected I2C speed.
 *
 * Calculates the low/high SCL clock counts from the MAX32690 I2C peripheral
 * input clock. High-speed mode is kept disabled because this HAL exposes
 * Standard, Fast, and Fast-mode Plus operation.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return None.
 */
static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Perform an I2C master read transaction.
 *
 * Supports standalone reads and the read phase of write-then-read transfers,
 * including receive transactions longer than the RXCTRL1 count field.
 *
 * @param[in]  *map           Object-specific context handler.
 * @param[out] *read_data_buf Destination data buffer.
 * @param[in]  len_read_data  Number of bytes to read.
 * @param[in]  mode           Transaction end mode.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on success, otherwise a module-specific
 *         timeout or hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode );

/**
 * @brief Perform an I2C master write transaction.
 *
 * Supports standalone writes and the write phase of write-then-read transfers.
 *
 * @param[in] *map            Object-specific context handler.
 * @param[in] *write_data_buf Source data buffer.
 * @param[in] len_write_data  Number of bytes to write.
 * @param[in] mode            Transaction end mode.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on success, otherwise a module-specific
 *         timeout or hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode );

/**
 * @brief Clear all pending I2C interrupt flags.
 *
 * INTFL0 and INTFL1 are write-one-to-clear registers, so all implemented flag
 * bits are cleared by writing their respective masks.
 *
 * @param[in] *hal_ll_hw_reg I2C register block.
 *
 * @return None.
 */
static void hal_ll_i2c_master_clear_flags( hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
 * @brief Clear the master configuration registers used by this implementation.
 *
 * Centralizes the register reset state used during initialization. Interrupt
 * flags are cleared separately through their write-one-to-clear semantics.
 *
 * @param[in] *hal_ll_hw_reg I2C register block.
 *
 * @return None.
 */
static void hal_ll_i2c_master_clear_registers( hal_ll_i2c_base_handle_t *hal_ll_hw_reg );

/**
 * @brief Flush the I2C transmit and receive FIFOs.
 *
 * Requests TXCTRL0.FLUSH and RXCTRL0.FLUSH and waits until hardware clears
 * both bits.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on success, or
 *         HAL_LL_I2C_MASTER_TIMEOUT_INIT if the flush does not complete.
 */
static hal_ll_err_t hal_ll_i2c_master_flush_fifos( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Abort the active I2C master transaction.
 *
 * Requests a STOP condition, waits for the request to complete when possible,
 * and clears all pending interrupt flags.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return None.
 */
static void hal_ll_i2c_master_abort( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Check the current hardware error flags.
 *
 * Converts MAX32690 interrupt error flags into mikroSDK HAL error values and
 * clears the error flags that were consumed.
 *
 * @param[in] *hal_ll_hw_reg I2C register block.
 * @param[in] timeout_error  HAL timeout value to return for INTFL0.TO_ERR.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS if no error is pending, otherwise the
 *         corresponding HAL error.
 */
static hal_ll_err_t hal_ll_i2c_master_check_error( hal_ll_i2c_base_handle_t *hal_ll_hw_reg,
                                                   hal_ll_err_t timeout_error );

/**
 * @brief Wait until the current master operation reports completion.
 *
 * Polls INTFL0.DONE while checking error flags and the configured software
 * timeout.
 *
 * @param[in] *map          Object-specific context handler.
 * @param[in] timeout_error HAL timeout value returned if waiting expires.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on completion, otherwise a timeout or
 *         hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_wait_done( hal_ll_i2c_hw_specifics_map_t *map,
                                                 hal_ll_err_t timeout_error );

/**
 * @brief Wait until selected MSTCTRL request bits are cleared by hardware.
 *
 * @param[in] *map          Object-specific context handler.
 * @param[in] mask          MSTCTRL request-bit mask to monitor.
 * @param[in] timeout_error HAL timeout value returned if waiting expires.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on completion, otherwise a timeout or
 *         hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_wait_mstctrl_clear( hal_ll_i2c_hw_specifics_map_t *map,
                                                          uint32_t mask,
                                                          hal_ll_err_t timeout_error );

/**
 * @brief Prepare the I2C master for a new transaction.
 *
 * Waits for an idle bus, disables I2C interrupts, clears pending flags, and
 * flushes both FIFOs.
 *
 * @param[in] *map Object-specific context handler.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on success, otherwise a timeout or
 *         hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_prepare_transaction( hal_ll_i2c_hw_specifics_map_t *map );

/**
 * @brief Finish the active I2C master transaction.
 *
 * Generates STOP or RESTART according to the requested end mode and waits for
 * the MAX32690 master state machine to report completion.
 *
 * @param[in] *map Object-specific context handler.
 * @param[in] mode Transaction end mode.
 *
 * @return HAL_LL_I2C_MASTER_SUCCESS on success, otherwise a timeout or
 *         hardware error.
 */
static hal_ll_err_t hal_ll_i2c_master_finish_transaction( hal_ll_i2c_hw_specifics_map_t *map,
                                                          hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl,
                                                hal_ll_pin_name_t sda,
                                                hal_ll_i2c_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
    hal_ll_i2c_pin_id index_list[I2C_MODULE_COUNT] = {0};
    uint16_t pin_check_result;

    for ( uint8_t module = 0; module < I2C_MODULE_COUNT; module++ ) {
        index_list[module].pin_scl = HAL_LL_PIN_NC;
        index_list[module].pin_sda = HAL_LL_PIN_NC;
    }

    // Check if pins are valid
    if (( pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, index_list, handle_map )) == HAL_LL_PIN_NC ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if (( hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_scl.pin_name != scl ) ||
        ( hal_ll_i2c_hw_specifics_map[pin_check_result].pins.pin_sda.pin_name != sda ))
    {
        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], false );

        hal_ll_i2c_master_map_pins( pin_check_result, index_list );

        hal_ll_i2c_master_alternate_functions_set_state( &hal_ll_i2c_hw_specifics_map[ pin_check_result ], true );

        handle_map[pin_check_result].init_ll_state = false;
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle =
            (handle_t *)&hal_ll_i2c_hw_specifics_map[pin_check_result].base;

    handle_map[pin_check_result].hal_ll_i2c_master_handle =
            (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_master_handle_register_t *hal_handle = (hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle =
            ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;

    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    low_level_handle->init_ll_state = false;
    hal_ll_i2c_hw_specifics_map_local->speed = hal_ll_i2c_get_speed( speed );

    hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local );

    low_level_handle->init_ll_state = true;

    return hal_ll_i2c_hw_specifics_map_local->speed;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_i2c_hw_specifics_map_local->base ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( HAL_LL_MODULE_ERROR != hal_ll_i2c_hw_specifics_map_local->base ) {
        hal_ll_i2c_hw_specifics_map_local->address = addr;
    }
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                              read_data_buf,
                                              len_read_data,
                                              HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                               write_data_buf,
                                               len_write_data,
                                               HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle,
                                                uint8_t *write_data_buf,
                                                size_t len_write_data,
                                                uint8_t *read_data_buf,
                                                size_t len_read_data ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    hal_ll_err_t status = hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                                write_data_buf,
                                                                len_write_data,
                                                                HAL_LL_I2C_MASTER_WRITE_THEN_READ );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    status = hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local,
                                                read_data_buf,
                                                len_read_data,
                                                HAL_LL_I2C_MASTER_WRITE_THEN_READ );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    if( NULL != low_level_handle->hal_ll_i2c_master_handle ) {
        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_100K;

        hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_local, false );
        hal_ll_i2c_master_clear_registers( hal_ll_i2c_get_base_struct( hal_ll_i2c_hw_specifics_map_local->base ) );
        hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_local, false );

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_name = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl.pin_af = 0;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda.pin_af = 0;
    }
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_err_t status;

    if ( ( NULL == write_data_buf ) && len_write_data ) {
        return HAL_LL_I2C_MASTER_ERROR;
    }

    /* A combined zero-length write is simply a pure read. */
    if ( ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) && ( 0 == len_write_data ) ) {
        return HAL_LL_I2C_MASTER_SUCCESS;
    }

    status = hal_ll_i2c_master_prepare_transaction( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    /* MAX32690 expects the 7-bit address plus R/W bit in the data FIFO. */
    hal_ll_hw_reg->fifo = ( uint32_t )map->address << HAL_LL_I2C_FIFO_ADDR_POS;
    set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_START );

    for ( size_t transfer_counter = 0; transfer_counter < len_write_data; transfer_counter++ ) {
        uint16_t time_counter = map->timeout;

        while ( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_I2C_STATUS_TX_FULL )) {
            status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );
            if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
                hal_ll_i2c_master_abort( map );
                return status;
            }

            if ( map->timeout && !time_counter-- ) {
                hal_ll_i2c_master_abort( map );
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }

        hal_ll_hw_reg->fifo = write_data_buf[ transfer_counter ];
    }

    /* Ensure every byte has left the TX FIFO before issuing STOP/RESTART. */
    {
        uint16_t time_counter = map->timeout;
        while ( !( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_I2C_STATUS_TX_EMPTY ))) {
            status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );
            if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
                hal_ll_i2c_master_abort( map );
                return status;
            }

            if ( map->timeout && !time_counter-- ) {
                hal_ll_i2c_master_abort( map );
                return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
            }
        }
    }

    status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, HAL_LL_I2C_MASTER_TIMEOUT_WRITE );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        hal_ll_i2c_master_abort( map );
        return status;
    }

    /* The read half of write-then-read generates the repeated START. */
    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) {
        write_reg( &hal_ll_hw_reg->intfl0, HAL_LL_I2C_INTFL0_DONE | HAL_LL_I2C_INTFL0_RX_THD );
        return HAL_LL_I2C_MASTER_SUCCESS;
    }

    return hal_ll_i2c_master_finish_transaction( map, mode );
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_err_t status;
    size_t transfer_counter = 0;
    size_t chunk_remaining;

    if ( ( NULL == read_data_buf ) && len_read_data ) {
        return HAL_LL_I2C_MASTER_ERROR;
    }

    if ( 0 == len_read_data ) {
        /* A zero-length read after a write still has to release the bus. */
        if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode &&
             ( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_I2C_STATUS_BUSY ))) {
            return hal_ll_i2c_master_finish_transaction( map, HAL_LL_I2C_MASTER_END_MODE_STOP );
        }
        return HAL_LL_I2C_MASTER_SUCCESS;
    }

    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ != mode ) {
        status = hal_ll_i2c_master_prepare_transaction( map );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    } else {
        /* Keep the write transaction active; only clear flags relevant to RX. */
        write_reg( &hal_ll_hw_reg->intfl0, HAL_LL_I2C_INTFL0_DONE | HAL_LL_I2C_INTFL0_RX_THD );
    }

    chunk_remaining = ( len_read_data > HAL_LL_I2C_RXCTRL1_MAX_COUNT ) ?
                      HAL_LL_I2C_RXCTRL1_MAX_COUNT : len_read_data;
    hal_ll_hw_reg->rxctrl1 = ( HAL_LL_I2C_RXCTRL1_MAX_COUNT == chunk_remaining ) ?
                             0UL : ( ( uint32_t )chunk_remaining & HAL_LL_I2C_RXCTRL1_COUNT_MASK );

    /* START automatically becomes RESTART while an earlier master transaction is active. */
    if ( check_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_START )) {
        set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_RESTART );
        status = hal_ll_i2c_master_wait_mstctrl_clear( map,
                                                       HAL_LL_I2C_MSTCTRL_RESTART_MASK,
                                                       HAL_LL_I2C_MASTER_TIMEOUT_START );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            hal_ll_i2c_master_abort( map );
            return status;
        }
    } else {
        set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_START );
    }

    hal_ll_hw_reg->fifo = (( uint32_t )map->address << HAL_LL_I2C_FIFO_ADDR_POS ) |
                            HAL_LL_I2C_FIFO_ADDR_READ;

    /* For a combined transfer DONE marks completion of the write phase/restart handoff. */
    if ( HAL_LL_I2C_MASTER_WRITE_THEN_READ == mode ) {
        status = hal_ll_i2c_master_wait_done( map, HAL_LL_I2C_MASTER_TIMEOUT_READ );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            hal_ll_i2c_master_abort( map );
            return status;
        }
        write_reg( &hal_ll_hw_reg->intfl0, HAL_LL_I2C_INTFL0_DONE );
    }

    while ( transfer_counter < len_read_data ) {
        uint16_t time_counter = map->timeout;

        while ( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_I2C_STATUS_RX_EMPTY )) {
            status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, HAL_LL_I2C_MASTER_TIMEOUT_READ );
            if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
                hal_ll_i2c_master_abort( map );
                return status;
            }

            /* A 256-byte chunk is complete when DONE is set and the FIFO is empty. */
            if (( read_reg( &hal_ll_hw_reg->intfl0 ) & HAL_LL_I2C_INTFL0_DONE ) &&
                 ( transfer_counter < len_read_data ) && !chunk_remaining ) {
                break;
            }

            if ( map->timeout && !time_counter-- ) {
                hal_ll_i2c_master_abort( map );
                return HAL_LL_I2C_MASTER_TIMEOUT_READ;
            }
        }

        if ( !( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_I2C_STATUS_RX_EMPTY ))) {
            read_data_buf[ transfer_counter++ ] = ( uint8_t )hal_ll_hw_reg->fifo;
            if ( chunk_remaining ) {
                chunk_remaining--;
            }
        }

        if ( ( 0 == chunk_remaining ) && ( transfer_counter < len_read_data ) ) {
            status = hal_ll_i2c_master_wait_done( map, HAL_LL_I2C_MASTER_TIMEOUT_READ );
            if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
                hal_ll_i2c_master_abort( map );
                return status;
            }

            size_t bytes_left = len_read_data - transfer_counter;
            chunk_remaining = ( bytes_left > HAL_LL_I2C_RXCTRL1_MAX_COUNT ) ?
                              HAL_LL_I2C_RXCTRL1_MAX_COUNT : bytes_left;

            hal_ll_hw_reg->rxctrl1 = ( HAL_LL_I2C_RXCTRL1_MAX_COUNT == chunk_remaining ) ?
                                     0UL : ( ( uint32_t )chunk_remaining & HAL_LL_I2C_RXCTRL1_COUNT_MASK );
            set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_RESTART );
            write_reg( &hal_ll_hw_reg->intfl0, HAL_LL_I2C_INTFL0_DONE );

            /* For subsequent 256-byte chunks ADI queues the next read address
             * immediately after requesting RESTART. */
            hal_ll_hw_reg->fifo = (( uint32_t )map->address << HAL_LL_I2C_FIFO_ADDR_POS ) |
                                    HAL_LL_I2C_FIFO_ADDR_READ;
        }
    }

    status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, HAL_LL_I2C_MASTER_TIMEOUT_READ );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        hal_ll_i2c_master_abort( map );
        return status;
    }

    return hal_ll_i2c_master_finish_transaction( map, mode );
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_I2C_AF_CONFIG;
        module.configs[1] = HAL_LL_I2C_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
    // Map new pins
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_name =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].pin;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_name =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].pin;
    // SCL and SDA could have different alternate function settings,
    // hence save both AF values
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_scl.pin_af =
                        hal_ll_i2c_scl_map[ index_list[module_index].pin_scl ].af;
    hal_ll_i2c_hw_specifics_map[module_index].pins.pin_sda.pin_af =
                        hal_ll_i2c_sda_map[ index_list[module_index].pin_sda ].af;
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_STANDARD ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FULL ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_FAST ) {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        }
    } else {
        if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_100K ) {
            return HAL_LL_I2C_MASTER_SPEED_100K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_400K ) {
            return HAL_LL_I2C_MASTER_SPEED_400K;
        } else if ( bit_rate <= HAL_LL_I2C_MASTER_SPEED_1M ) {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        } else {
            return HAL_LL_I2C_MASTER_SPEED_1M;
        }
    }
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) /
                                        (sizeof( hal_ll_i2c_master_handle_register_t ));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) /
                                        (sizeof( hal_ll_i2c_master_handle_register_t));

    while( hal_ll_module_count-- ) {
        if ( hal_ll_i2c_get_base_from_hal_handle ==
                 hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map ) {
    static const uint16_t scl_map_size =
            ( sizeof( hal_ll_i2c_scl_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    static const uint16_t sda_map_size =
            ( sizeof( hal_ll_i2c_sda_map ) / sizeof( hal_ll_i2c_pin_map_t ) );
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t scl_index;
    uint16_t sda_index;

    if ( (HAL_LL_PIN_NC == scl) || (HAL_LL_PIN_NC == sda) ) {
        return HAL_LL_PIN_NC;
    }

    for ( scl_index = 0; scl_index < scl_map_size; scl_index++ ) {
        if ( hal_ll_i2c_scl_map[ scl_index ].pin == scl ) {
            for ( sda_index = 0; sda_index < sda_map_size; sda_index++ ) {
                if ( hal_ll_i2c_sda_map[ sda_index ].pin == sda ) {
                    if ( hal_ll_i2c_scl_map[ scl_index ].module_index ==
                                hal_ll_i2c_sda_map[ sda_index ].module_index ) {
                        // Get module number
                        hal_ll_module_id = hal_ll_i2c_scl_map[ scl_index ].module_index;

                        // Map module number to map index
                        for ( uint8_t map_member = 0; map_member < I2C_MODULE_COUNT + 1; map_member++  ) {
                            if ( hal_ll_i2c_hw_specifics_map[map_member].module_index ==  hal_ll_module_id ) {
                                hal_ll_module_id = map_member;
                                break;
                            }
                        }

                        // Map pin names
                        index_list[hal_ll_module_id].pin_scl = scl_index;
                        index_list[hal_ll_module_id].pin_sda = sda_index;

                        // Check if module is taken
                        if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_i2c_master_handle ) {
                            return hal_ll_module_id;
                        } else if ( I2C_MODULE_COUNT == ++index_counter ) {
                            return --index_counter;
                        }
                    }
                }
            }
        }
    }

    if ( index_counter ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_i2c_master_clear_flags( hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    /* INTFL0/INTFL1 use write-one-to-clear semantics. */
    hal_ll_hw_reg->intfl0 = HAL_LL_I2C_INTFL0_CLEAR_MASK;
    hal_ll_hw_reg->intfl1 = HAL_LL_I2C_INTFL1_CLEAR_MASK;
}

static void hal_ll_i2c_master_clear_registers( hal_ll_i2c_base_handle_t *hal_ll_hw_reg ) {
    /*
     * Keep the complete master configuration clear state in one place.
     * STATUS, FIFOLEN and FIFO are status/data registers. Clock timing
     * registers are configured separately by hal_ll_i2c_calculate_speed().
     * Slave-only registers are intentionally left untouched by this master HAL.
     */
    hal_ll_hw_reg->ctrl = 0;
    hal_ll_hw_reg->inten0 = 0;
    hal_ll_hw_reg->inten1 = 0;
    hal_ll_hw_reg->rxctrl0 = 0;
    hal_ll_hw_reg->rxctrl1 = 0;
    hal_ll_hw_reg->txctrl0 = 0;
    hal_ll_hw_reg->txctrl1 = 0;
    hal_ll_hw_reg->mstctrl = 0;
    hal_ll_hw_reg->timeout = 0;
    hal_ll_hw_reg->dma = 0;

    hal_ll_i2c_master_clear_flags( hal_ll_hw_reg );
}

static hal_ll_err_t hal_ll_i2c_master_flush_fifos( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    /* Hardware clears both FLUSH request bits when the operation completes. */
    set_reg_bit( &hal_ll_hw_reg->txctrl0, HAL_LL_I2C_TXCTRL0_FLUSH );
    set_reg_bit( &hal_ll_hw_reg->rxctrl0, HAL_LL_I2C_RXCTRL0_FLUSH );

    while (( check_reg_bit( &hal_ll_hw_reg->txctrl0, HAL_LL_I2C_TXCTRL0_FLUSH )) ||
           ( check_reg_bit( &hal_ll_hw_reg->rxctrl0, HAL_LL_I2C_RXCTRL0_FLUSH ))) {
        if ( map->timeout && !time_counter-- ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_INIT;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_check_error( hal_ll_i2c_base_handle_t *hal_ll_hw_reg,
                                                   hal_ll_err_t timeout_error ) {
    uint32_t intfl0 = hal_ll_hw_reg->intfl0;
    uint32_t intfl1 = hal_ll_hw_reg->intfl1;

    if ( intfl0 & HAL_LL_I2C_INTFL0_ARB_ERR ) {
        hal_ll_hw_reg->intfl0 = HAL_LL_I2C_INTFL0_ARB_ERR;
        return HAL_LL_I2C_MASTER_ARBITRATION_LOST;
    }

    if ( intfl0 & HAL_LL_I2C_INTFL0_TO_ERR ) {
        hal_ll_hw_reg->intfl0 = HAL_LL_I2C_INTFL0_TO_ERR;
        return timeout_error;
    }

    if ( intfl0 & HAL_LL_I2C_INTFL0_ERROR_MASK ) {
        hal_ll_hw_reg->intfl0 = intfl0 & HAL_LL_I2C_INTFL0_ERROR_MASK;
        return HAL_LL_I2C_MASTER_ERROR;
    }

    if ( intfl1 & HAL_LL_I2C_INTFL1_ERROR_MASK ) {
        hal_ll_hw_reg->intfl1 = intfl1 & HAL_LL_I2C_INTFL1_ERROR_MASK;
        return HAL_LL_I2C_MASTER_ERROR;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_master_abort( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_STOP );
    while ( check_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_STOP )) {
        if ( map->timeout && !time_counter-- ) {
            break;
        }
    }

    hal_ll_i2c_master_clear_flags( hal_ll_hw_reg );
}

static hal_ll_err_t hal_ll_i2c_master_wait_mstctrl_clear( hal_ll_i2c_hw_specifics_map_t *map,
                                                          uint32_t mask,
                                                          hal_ll_err_t timeout_error ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( hal_ll_hw_reg->mstctrl & mask ) {
        hal_ll_err_t status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, timeout_error );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }

        if ( map->timeout && !time_counter-- ) {
            return timeout_error;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_wait_done( hal_ll_i2c_hw_specifics_map_t *map,
                                                 hal_ll_err_t timeout_error ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( !(( read_reg( &hal_ll_hw_reg->intfl0 ) & HAL_LL_I2C_INTFL0_DONE ))) {
        hal_ll_err_t status = hal_ll_i2c_master_check_error( hal_ll_hw_reg, timeout_error );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }

        if ( map->timeout && !time_counter-- ) {
            return timeout_error;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_prepare_transaction( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_err_t status;

    /* A fresh transaction must not disturb another master operation. */
    status = hal_ll_i2c_master_wait_for_idle( map );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    /* This HAL uses polling, so keep peripheral interrupts disabled. */
    hal_ll_hw_reg->inten0 = 0;
    hal_ll_hw_reg->inten1 = 0;

    /* Remove stale completion/error state and stale FIFO data. */
    hal_ll_i2c_master_clear_flags( hal_ll_hw_reg );
    return hal_ll_i2c_master_flush_fifos( map );
}

static hal_ll_err_t hal_ll_i2c_master_finish_transaction( hal_ll_i2c_hw_specifics_map_t *map,
                                                          hal_ll_i2c_master_end_mode_t mode ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    hal_ll_err_t status;

    if ( HAL_LL_I2C_MASTER_END_MODE_RESTART == mode ) {
        set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_RESTART );
    } else {
        set_reg_bit( &hal_ll_hw_reg->mstctrl, HAL_LL_I2C_MSTCTRL_STOP );
        status = hal_ll_i2c_master_wait_mstctrl_clear( map,
                                                       HAL_LL_I2C_MSTCTRL_STOP_MASK,
                                                       HAL_LL_I2C_MASTER_TIMEOUT_STOP );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }
    }

    status = hal_ll_i2c_master_wait_done( map,
                                          ( HAL_LL_I2C_MASTER_END_MODE_RESTART == mode ) ?
                                          HAL_LL_I2C_MASTER_TIMEOUT_START : HAL_LL_I2C_MASTER_TIMEOUT_STOP );
    if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
        return status;
    }

    status = hal_ll_i2c_master_check_error( hal_ll_hw_reg,
                                            ( HAL_LL_I2C_MASTER_END_MODE_RESTART == mode ) ?
                                            HAL_LL_I2C_MASTER_TIMEOUT_START : HAL_LL_I2C_MASTER_TIMEOUT_STOP );

    write_reg( &hal_ll_hw_reg->intfl0, HAL_LL_I2C_INTFL0_DONE | HAL_LL_I2C_INTFL0_STOP );
    return status;
}

static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    while ( check_reg_bit( &hal_ll_hw_reg->status, HAL_LL_I2C_STATUS_BUSY )) {
        hal_ll_err_t status = hal_ll_i2c_master_check_error( hal_ll_hw_reg,
                                                             HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE );
        if ( HAL_LL_I2C_MASTER_SUCCESS != status ) {
            return status;
        }

        if ( map->timeout && !time_counter-- ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint32_t ticks_total;
    uint32_t high_ticks;
    uint32_t low_ticks;

    clear_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_I2C_CTRL_HS_EN );

    ticks_total = HAL_LL_I2C_PERIPHERAL_CLOCK / map->speed;
    if ( ticks_total < 4UL ) {
        ticks_total = 4UL;
    }

    high_ticks = ( ticks_total >> 1 ) - 1UL;
    low_ticks = ( ticks_total >> 1 ) - 1UL;

    if ( ticks_total & 1UL ) {
        high_ticks++;
    }

    if ( high_ticks > HAL_LL_I2C_CLKHI_COUNT_MASK ) {
        high_ticks = HAL_LL_I2C_CLKHI_COUNT_MASK;
    }
    if ( low_ticks > HAL_LL_I2C_CLKLO_COUNT_MASK ) {
        low_ticks = HAL_LL_I2C_CLKLO_COUNT_MASK;
    }

    write_reg( &hal_ll_hw_reg->clklo, low_ticks & HAL_LL_I2C_CLKLO_COUNT_MASK );
    write_reg( &hal_ll_hw_reg->clkhi, high_ticks & HAL_LL_I2C_CLKHI_COUNT_MASK );
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    /* Start from a known master configuration state. */
    hal_ll_i2c_master_clear_registers( hal_ll_hw_reg );

    /* Enable the block before FIFO configuration, preserving the original sequence. */
    set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_I2C_CTRL_EN );

    /* Configure polling-friendly FIFO thresholds. */
    write_reg( &hal_ll_hw_reg->txctrl0, HAL_LL_I2C_TXCTRL0_THD_VALUE );
    write_reg( &hal_ll_hw_reg->rxctrl0, HAL_LL_I2C_RXCTRL0_THD_VALUE );

    /*
     * Preserve the previous behavior: initialization continues even if the
     * software FIFO-flush timeout expires.
     */
    ( void )hal_ll_i2c_master_flush_fifos( map );

    /* All transactions in this driver use master mode. */
    set_reg_bit( &hal_ll_hw_reg->ctrl, HAL_LL_I2C_CTRL_MST_MODE );
}

static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef I2C_MODULE_0
        case hal_ll_i2c_module_num( I2C_MODULE_0 ):
            if ( hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_13 );
            } else {
                set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_13 );
            }
            break;
        #endif

        #ifdef I2C_MODULE_1
        case hal_ll_i2c_module_num( I2C_MODULE_1 ):
            if ( hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_28 );
            } else {
                set_reg_bit( _GCR_PCLKDIS0_, GCR_PCLKDIS0_28 );
            }
            break;
        #endif

        #ifdef I2C_MODULE_2
        case hal_ll_i2c_module_num( I2C_MODULE_2 ):
            if ( hal_ll_state ) {
                clear_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS1_24 );
            } else {
                set_reg_bit( _GCR_PCLKDIS1_, GCR_PCLKDIS1_24 );
            }
            break;
        #endif

        default:
            break;
    }
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    /* Enable I2C peripheral clock before touching its registers. */
    hal_ll_i2c_master_module_enable( map, true );

    hal_ll_i2c_hw_init( map );

    hal_ll_i2c_calculate_speed( map );
}

// ------------------------------------------------------------------------- END
