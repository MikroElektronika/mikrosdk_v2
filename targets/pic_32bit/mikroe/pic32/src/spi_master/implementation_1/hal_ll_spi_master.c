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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  hal_ll_spi_master.c
 * @brief SPI master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_spi_master.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pps.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_slrcon_map.h"
#include "math.h"
#include "delays.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address              ((hal_ll_spi_master_handle_register_t *)handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle                            (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle)              ((hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle              ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                                (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base

/*!< @brief Macros used for register manipulation */
#define HAL_LL_SPI_RECEIVE_BUFFER_FULL_STATUS_BIT               0
#define HAL_LL_SPI_MASTER_MODE_ENABLE_BIT                       5
#define HAL_LL_SPI_CLOCK_POLARITY_SELECT_BIT                    6
#define HAL_LL_SPI_CLOCK_EDGE_SELECT_BIT                        8
#define HAL_LL_SPI_MASTER_DATA_SAMPLE_MIDDLE                    9
#define HAL_LL_SPI_MODE_16_BIT                                  10
#define HAL_LL_SPI_MODE_32_BIT                                  11
#define HAL_LL_SPI_PERIPHERAL_ON_BIT                            15

#define HAL_LL_SPI_RECEIVE_OVERFLOW_FLAG_BIT                    6

#define HAL_LL_SPI_PBDIV_FIRST_BIT                              19
#define HAL_LL_SPI_PBDIV_MASK_MX                                0x03
#define HAL_LL_SPI_PBDIV_MASK_MZ                                0x7F

#define HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK             5

#define port_mask                                               0xF0
#define pin_mask                                                0x0F

#define HAL_LL_SPI_MASTER_CURRENT_FOSC_DIV                      hal_ll_spi_master_divisor_calculate()
#define _fosc                                                   (Get_Fosc_kHz()*1000)

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K                            100000

/*!< @brief Macros used for SPI baud rate divider upper limit */
#if defined (SPI_BAUD_REG_9_AND_13_BIT_RESOLUTION_MZ)
#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK             0x01FF
#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_13_BIT_MASK      0x1FFF
#endif
#if defined (SPI_BAUD_REG_9_BIT_RESOLUTION)
#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK             0x01FF
#endif
#if defined (SPI_BAUD_REG_13_BIT_RESOLUTION)
#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK             0x1FFF
#endif


// -------------------------------------------------------------- PRIVATE TYPES

/*!< @brief SPI register structure. */
typedef struct {
    hal_ll_base_addr_t spicon_reg_addr;
    hal_ll_base_addr_t __unused_1[ 3 ];
    hal_ll_base_addr_t spistat_reg_addr;
    hal_ll_base_addr_t __unused_2[ 3 ];
    hal_ll_base_addr_t spibuf_reg_addr;
    hal_ll_base_addr_t __unused_3[ 3 ];
    hal_ll_base_addr_t spibrg_reg_addr;
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI Master hardware specific structure */
typedef struct {
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t  dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
} hal_ll_spi_master_hw_specifics_map_t;

/*!< @brief SPI hw specific module values */
typedef struct {
    uint16_t pin_sck;
    uint16_t pin_miso;
    uint16_t pin_mosi;
} hal_ll_spi_master_pin_id;

/*!< @brief SPI Master hw specific error values */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief SPI Master hardware specific info */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[ SPI_MODULE_COUNT + 1 ] = {

    #ifdef SPI_MODULE
    { HAL_LL_SPI1CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE_1), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_2
    { HAL_LL_SPI2CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE_2), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_3
    { HAL_LL_SPI3CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE_3), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_4
    { HAL_LL_SPI4CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE_4), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_5
    { HAL_LL_SPI5CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE_5), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif
    #ifdef SPI_MODULE_6
    { HAL_LL_SPI6CON_ADDRESS, hal_ll_spi_master_module_num(SPI_MODULE_6), { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    { HAL_LL_MODULE_ERROR, NULL, { HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC }, NULL, HAL_LL_SPI_MASTER_SPEED_100K, NULL, HAL_LL_SPI_MASTER_MODE_DEFAULT }
 };

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static volatile hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_master_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Peripheral Bus Clock Configuration.
  *
  * Divisor for baud rate generator depends on clock source (SYSCLK and PBCLK)
  *
  * @return calculated divisor value.
  *
  * Returns one of possible divisors values.
  * Formula is different for MZ and MX family of the MCU.
  */
static uint16_t hal_ll_spi_master_divisor_calculate(void);

/**
  * @brief  Check if pins are adequate.
  *
  * Checks SCK, MISO and MOSI pins the user has passed with pre-defined
  * pins in SCK, MISO and MOSI maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  sck - SCK pre-defined pin name.
  * @param[in]  miso - MISO pre-defined pin name.
  * @param[in]  mosi - MOSI pre-defined pin name.
  * @param[in]  *index_list - Index list.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map);

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_spi_master_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_spi_master_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle);

/**
 * @brief  Set PPS state.
 *
 * Sets adequate RPnR and [pin_name]R register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  hal_ll_state - init or deinit
 *
 * @return  hal_ll_pps_err_t PPS specific value.
 * HAL_LL_PPS_SUCCESS  -- OK
 * HAL_LL_PPS_DIRECTION_ERROR -- Direction not set
 * HAL_LL_PPS_PIN_ERROR -- Wrong pin
 * HAL_LL_PPS_MODULE_ERROR -- General error
 *
 * @note PIC specific.
 */
static hal_ll_pps_err_t hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
  * @brief  Enable clock for SPI module on hardware level.
  *
  * Initializes SPI module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return None
  */
static void hal_ll_spi_master_peripheral_module_disable(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
  * @brief  Full SPI Master module initialization procedure.
  *
  * Initializes SPI Master module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map);

/**
  * @brief  Initialize SPI module on hardware level.
  *
  * Initializes SPI module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *map - Object specific context handler.
  * @return none
  *
  */
static void hal_ll_spi_master_hw_init(hal_ll_spi_master_hw_specifics_map_t *map);

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * SPI SCK, MISO and MOSI pins.
 *
 * @param[in]  module_index SPI HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCK, MISO and MOSI map index values
 *                          and module number
 *
 * @return  None
 */
static void hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_master_pin_id *index_list);

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  hal_ll_hw_reg - SPI master base structure.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data);

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  hal_ll_hw_reg - SPI master base structure.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buffer, size_t write_data_length);

/**
  * @brief  Perform a transfer on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  hal_ll_hw_reg - SPI master base structure.
  * @param[in]  data_buffer - User-specific data, or dummy data.
  * @return data Read data.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static uint8_t hal_ll_spi_master_transfer_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t data_buffer);

/**
 * @brief  Set GPIO state.
 *
 * Sets adequate TRISx register
 * values for adequate functionality.
 *
 * @param map - Object specific context handler.
 * @param hal_ll_state - init or deinit
 *
 * @return  none.
 *
 * @note PIC specific.
 */
static void hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
 * @brief  Set Slew rate.
 *
 * Sets adequate Slew rate for used pins.
 *
 * @param pin - SDK defined pin number.
 *
 * @return  none.
 *
 * @note PIC32 specific.
 */
static void hal_ll_spi_master_set_slew_rate(hal_ll_pin_name_t pin);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id) {

    hal_ll_spi_master_pin_id index_list[SPI_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check user-defined pins.
    if ((pin_check_result = hal_ll_spi_master_check_pins(sck, miso, mosi, &index_list, handle_map)) == HAL_LL_PIN_NC) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    }

    if ((hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.sck != sck) ||
         (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.miso != miso) ||
         (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.mosi != mosi)) {
        // Used only for chips which have SPI PPS pins.
        #if HAL_LL_SPI_PPS_ENABLED == true
        // Clear previous module pps
        hal_ll_pps_set_state(&hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false);
        #endif

        // Map new pps.
        hal_ll_spi_master_map_pins(pin_check_result, &index_list);

        // Used only for chips which have SPI PPS pins.
        #if HAL_LL_SPI_PPS_ENABLED == true
        // Clear previous module pps
        hal_ll_pps_set_state(&hal_ll_spi_master_hw_specifics_map[ pin_check_result ], true);
        #endif

        handle_map[pin_check_result].init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;

    // Return the same info about module one level up (into the HAL level).
    handle_map[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi(handle_t *handle) {
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);
    hal_ll_spi_master_handle_register_t *hal_handle = (hal_ll_spi_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_spi_master_hw_specifics_map_local->module_index;

    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data(handle_t *handle, uint8_t dummy_data) {
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
}

hal_ll_err_t hal_ll_spi_master_write(handle_t *handle, uint8_t *write_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local->base, write_data_buffer, length_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read(handle_t *handle, uint8_t *read_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local->base, read_data_buffer, length_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read(handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local->base, write_data_buffer, length_write_data);

    hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local->base, read_data_buffer, length_read_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed(handle_t *handle, uint32_t speed) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->speed = speed;

    // Init once again, but with updated SPI Master baud rate value.
    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master baud rate value.
    return hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed;
}

hal_ll_err_t hal_ll_spi_master_set_mode(handle_t *handle, hal_ll_spi_master_mode_t mode) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master mode that is going to be used.
    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close(handle_t* handle) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if (low_level_handle->hal_ll_spi_master_handle != NULL) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle  = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
        hal_ll_spi_master_peripheral_module_disable(hal_ll_spi_master_hw_specifics_map_local, true);
        #endif
        #if HAL_LL_SPI_PPS_ENABLED == true
        hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_local, false);
        #endif
        hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_local, false);
        #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
        hal_ll_spi_master_peripheral_module_disable(hal_ll_spi_master_hw_specifics_map_local, false);
        #endif

        hal_ll_spi_master_hw_specifics_map_local->pins.sck = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t hal_ll_spi_master_divisor_calculate(void){
    volatile uint8_t pbdiv = 0;

    #if defined(PIC32MZxx)

    pbdiv = read_reg(HAL_LL_PB2DIV_ADDRESS);
    pbdiv &= HAL_LL_SPI_PBDIV_MASK_MZ;

    return pbdiv + 1;

    #else

    // Separating 19 and 20 bit of OSCCON register ( by shifting right for 19 bits )
    pbdiv = read_reg(HAL_LL_OSCCON_ADDRESS) >> HAL_LL_SPI_PBDIV_FIRST_BIT; //
    pbdiv &= HAL_LL_SPI_PBDIV_MASK_MX;

    // Divisor represent the power raised to the base number, where base is equal 2 and power is value of pbdiv register
    return pow(2, pbdiv);
    #endif
}

static uint8_t hal_ll_spi_master_transfer_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t data_buffer) {
    // Write user-defined data ( 'hal_ll_spi_master_read_bare_metal' procedure will send dummy data ).
    *((volatile uint8_t *)&hal_ll_hw_reg->spibuf_reg_addr) = (uint8_t)data_buffer;    // 8-bit data
    // Wait for receive buffer not empty status. (For debug mode replace while loop with Delay_ms(1))
    while (!(check_reg_bit(&(hal_ll_hw_reg->spistat_reg_addr), HAL_LL_SPI_RECEIVE_BUFFER_FULL_STATUS_BIT)));
    // Return read data.
    return *((volatile uint8_t *)&hal_ll_hw_reg->spibuf_reg_addr);                // 8-bit data
}

static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buffer, size_t write_data_length) {
    volatile size_t transfer_counter = 0;

    // Write the first data to be transmitted into the SPI_DR register.
    for (transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++) {
        // If we are good to go ( if the tx buffer value has been shifted to the shift register ), write the data.
        hal_ll_spi_master_transfer_bare_metal(hal_ll_hw_reg, write_data_buffer[transfer_counter]);
    }
}

static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data) {
    volatile size_t transfer_counter = 0;

    // Read the first data to be transmitted into the SPI_DR register.
    for (transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++) {
        // If we are good to go ( if the value from shift register has been shifted to the rx register ), read the data.
        read_data_buffer[transfer_counter] = hal_ll_spi_master_transfer_bare_metal(hal_ll_hw_reg, dummy_data);
    }
}

static hal_ll_pin_name_t hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin, hal_ll_pin_name_t mosi_pin, hal_ll_spi_master_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map ) {
    static const hal_ll_pin_name_t depth_sck_pin_map  = (sizeof(_spi_sck_map)) / (sizeof(hal_ll_spi_master_pin_map_t));
    static const hal_ll_pin_name_t depth_miso_pin_map = (sizeof(_spi_miso_map)) / (sizeof(hal_ll_spi_master_pin_map_t));
    static const hal_ll_pin_name_t depth_mosi_pin_map = (sizeof(_spi_mosi_map)) / (sizeof(hal_ll_spi_master_pin_map_t));
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t miso_index;
    uint16_t mosi_index;
    uint16_t sck_index;

    if ( (HAL_LL_PIN_NC == sck_pin) || (HAL_LL_PIN_NC == miso_pin) || (HAL_LL_PIN_NC == mosi_pin) ) {
        return HAL_LL_PIN_NC;
    }

    // Check pins from the specific pin maps with the user defined pins.
    for (sck_index = 0; sck_index < depth_sck_pin_map; sck_index++) {
        if (_spi_sck_map[sck_index].pin == sck_pin) {
            for (miso_index = 0; miso_index < depth_miso_pin_map; miso_index++) {
                if (_spi_miso_map[miso_index].pin == miso_pin) {
                    if (hal_ll_spi_master_hw_specifics_map[_spi_sck_map[sck_index].module_index].base ==
                        hal_ll_spi_master_hw_specifics_map[_spi_miso_map[miso_index].module_index].base) {
                        for (mosi_index = 0; mosi_index < depth_mosi_pin_map; mosi_index++) {
                            if (_spi_mosi_map[mosi_index].pin ==  mosi_pin) {
                                if (hal_ll_spi_master_hw_specifics_map[_spi_sck_map[sck_index].module_index].base ==
                                    hal_ll_spi_master_hw_specifics_map[_spi_mosi_map[mosi_index].module_index].base) {

                                    // Get module number
                                    hal_ll_module_id = _spi_sck_map[ sck_index ].module_index;

                                    // Map pin names
                                    index_list[hal_ll_module_id].pin_sck = sck_index;
                                    index_list[hal_ll_module_id].pin_miso = miso_index;
                                    index_list[hal_ll_module_id].pin_mosi = mosi_index;

                                    // Check if module is taken
                                    if ( NULL == handle_map[hal_ll_module_id].hal_drv_spi_master_handle ) {
                                        return hal_ll_module_id;
                                    } else if ( SPI_MODULE_COUNT == ++index_counter ) {
                                        return --index_counter;
                                    }

                                }
                            }
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

static void hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_master_pin_id *index_list) {
    hal_ll_spi_master_hw_specifics_map[module_index].pins.sck  = _spi_sck_map[index_list[module_index].pin_sck].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.miso = _spi_miso_map[index_list[module_index].pin_miso].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.mosi = _spi_mosi_map[index_list[module_index].pin_mosi].pin;
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_spi_master_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_spi_master_handle_register_t));

    hal_ll_spi_master_handle_register_t *local_handle = (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_base_from_hal_handle;

    while (hal_ll_module_count--) {
        if ((hal_ll_base_addr_t)local_handle->hal_ll_spi_master_handle == hal_ll_spi_master_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_set_slew_rate(hal_ll_pin_name_t pin) {
    uint8_t index;
    uint8_t map_size = sizeof(slew_rate_map) / sizeof(hal_ll_slew_rate_t);

    for (index = 0; index < map_size; index++) {
        if (slew_rate_map[index].pin == pin) {
            clear_reg_bit(slew_rate_map[index].srconx_address[0], slew_rate_map[index].srconx_address_bit);
            clear_reg_bit(slew_rate_map[index].srconx_address[1], slew_rate_map[index].srconx_address_bit);
            break;
        }
    }
}

static void hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    hal_ll_gpio_pin_t pin;

    if (hal_ll_state) {
        hal_ll_gpio_configure_pin(&pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_OUTPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_OUTPUT);

        #ifdef PIC32MZxx
        hal_ll_spi_master_set_slew_rate(map->pins.sck);
        hal_ll_spi_master_set_slew_rate(map->pins.miso);
        hal_ll_spi_master_set_slew_rate(map->pins.mosi);
        #endif
    } else {
        hal_ll_gpio_configure_pin(&pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_INPUT);
    }
}

static void hal_ll_spi_master_peripheral_module_disable(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    switch (map->module_index + 1) {
        #ifdef HAL_LL_PMD5_ADDRESS
            #ifdef SPI_MODULE
            case SPI_MODULE:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI1MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI1MD_ENABLE_BIT);
                }
                break;
            #endif
            #ifdef SPI_MODULE_1
            case SPI_MODULE_1:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI1MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI1MD_ENABLE_BIT);
                }
                break;
            #endif
            #ifdef SPI_MODULE_2
            case SPI_MODULE_2:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI2MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI2MD_ENABLE_BIT);
                }
                break;
            #endif
            #ifdef SPI_MODULE_3
            case SPI_MODULE_3:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI3MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI3MD_ENABLE_BIT);
                }
                break;
            #endif
            #ifdef SPI_MODULE_4
            case SPI_MODULE_4:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI4MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI4MD_ENABLE_BIT);
                }
                break;
            #endif
            #ifdef SPI_MODULE_5
            case SPI_MODULE_5:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI5MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI5MD_ENABLE_BIT);
                }
                break;
            #endif
            #ifdef SPI_MODULE_6
            case SPI_MODULE_6:
                if (hal_ll_state) {
                    clear_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI6MD_ENABLE_BIT);
                } else {
                    set_reg_bit(HAL_LL_PMD5_ADDRESS, HAL_LL_SPI6MD_ENABLE_BIT);
                }
                break;
            #endif
        #endif

            default:
                break;
    }
}

static hal_ll_pps_err_t hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if ((map->pins.miso != HAL_LL_PIN_NC) && (map->pins.mosi != HAL_LL_PIN_NC)) {

        hal_ll_status = hal_ll_pps_map((map->pins.miso & port_mask) >> 4, map->pins.miso & pin_mask, HAL_LL_GPIO_DIGITAL_INPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, map->module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }

        hal_ll_status = hal_ll_pps_map((map->pins.mosi & port_mask) >> 4, map->pins.mosi & pin_mask, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                        HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, map->module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }
    } else {
        return HAL_LL_PPS_SUCCESS;
    }
}

static void hal_ll_spi_master_hw_init(hal_ll_spi_master_hw_specifics_map_t *map) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);
    uint16_t divisor = 0;
    uint32_t baud_rate_gen = 0;

    clear_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_PERIPHERAL_ON_BIT);

    hal_ll_hw_reg->spicon_reg_addr  = 0;
    hal_ll_hw_reg->spistat_reg_addr = 0;

    // Configure SPI baud rate.
    divisor = hal_ll_spi_master_divisor_calculate();
    baud_rate_gen = ((_fosc / divisor)/(2*(map->speed))) - 1;

    // If calculated prescaler value is less then or equal to prescaler value that has been proved to be the minimal eligible,
    // set baud rate prescaler value to generate max SPI speed available on actual hardware device.
    if (baud_rate_gen <= HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK) {

        baud_rate_gen = HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK;    // Most MX and MZ chips do not work with a BRG value below 5.

    // If calculated prescaler value is greater then or equal to prescaler value that has been proved to be the maximal eligible,
    // set baud rate prescaler value to generate min SPI speed available on actual hardware device.
    } else if (baud_rate_gen >= HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK) {

        #if defined (PIC32MZxx)
        // PIC32MZxx MCUs which utilize SPI module 0 have 13 bit speed resolution.
        if (hal_ll_spi_master_module_num(SPI_MODULE_1) == map->module_index) {
            baud_rate_gen = HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_13_BIT_MASK; // Upper SPIxBRG limit.
        }else {
        // All other SPI modules utilize 9 bit speed resolution.
            baud_rate_gen = HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK;        // Upper SPIxBRG limit.
        }
        #else
        baud_rate_gen = HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK;            // Upper SPIxBRG limit.
        #endif
    };


    // Check BRG register. According to the datasheet (page 328) register uses 9 (or 13 bits for SPI1BRG - MZ family)
    // of the total amount of bits, but it has been experimentally concluded that a larger number may be written.
    hal_ll_hw_reg->spibrg_reg_addr  = baud_rate_gen;  // Best performance in between 5 and 14289.

    // Enable Master Mode.
    set_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_MASTER_MODE_ENABLE_BIT);

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if (map->mode <= HAL_LL_SPI_MASTER_MODE_1) {
       clear_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_CLOCK_POLARITY_SELECT_BIT);
    } else {
       set_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_CLOCK_POLARITY_SELECT_BIT);
    }

    // Input data is sampled at the middle od data output.
    clear_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_MASTER_DATA_SAMPLE_MIDDLE);

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE ( 1 ), or vice versa ( 0 ).
    if (map->mode == HAL_LL_SPI_MASTER_MODE_0 || map->mode == HAL_LL_SPI_MASTER_MODE_2) {
        set_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_CLOCK_EDGE_SELECT_BIT);
    } else {
        clear_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_CLOCK_EDGE_SELECT_BIT);
    }

    // Communication Select bits set to ZERO so that MCU communicate with 8-bit mode
    clear_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_MODE_16_BIT);
    clear_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_MODE_32_BIT);

    //SPI module is enabled
    set_reg_bit(&(hal_ll_hw_reg->spicon_reg_addr), HAL_LL_SPI_PERIPHERAL_ON_BIT);
}

static void hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map) {
    #ifdef HAL_LL_PERIPHERAL_MODULE_DISABLE
    hal_ll_spi_master_peripheral_module_disable(map, true);
    #endif

    // Configure pins which are going to be used for SPI communication.
    hal_ll_spi_master_configure_pins(map, true);

    // Used only for chips which have SPI PPS pins.
    #if HAL_LL_SPI_PPS_ENABLED == true
    // Set pps functions for mapped pins.
    hal_ll_pps_set_state(map, true);
    #endif

    // Finally, write user-defined settings into hardware registers.
    hal_ll_spi_master_hw_init(map);
}
// ------------------------------------------------------------------------- END
