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
 * @file  hal_ll_spi_master.c
 * @brief SPI master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_spi_master.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pps.h"
#include "hal_ll_slrcon_map.h"
#include "hal_ll_spi_master_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = {(handle_t *)NULL, (handle_t *)NULL, false};

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address ((hal_ll_spi_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle) ((const hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                   (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base

/*!< @brief Macros used for pin/port manipulation */
#define HAL_LL_SPI_MASTER_DEFAULT_BASE_ADDRESS                  0xFF

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K                            100000

/*!< @brief Macros defining MCU clock and SPI Master baud rate properties */
#define _fosc (Get_Fosc_kHz()*1000)
#define hal_ll_spi_master_speed_equation(_speed_resolution)     (_fosc / (2 * (_speed_resolution + 1)))
#define hal_ll_spi_master_prescaler_equation                    ((_fosc / (map->speed * 2)) - 1)
#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK             255
#define HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK             0

/*!< @brief Macros defining register addresses and masks */
#define HAL_LL_SPI_MASTER_SPI1CON0_BMODE                        0
#define HAL_LL_SPI_MASTER_SPI1CON0_MST                          1
#define HAL_LL_SPI_MASTER_SPI1CON0_EN                           7
#define HAL_LL_SPI_MASTER_SPI1CON1_SSP                          0x04
#define HAL_LL_SPI_MASTER_SPI1CON1_CKE                          0x40
#define HAL_LL_SPI_MASTER_SPI1CON2_BUSY                         7
#define HAL_LL_SPI_MASTER_SPI1CON2_RXR                          0
#define HAL_LL_SPI_MASTER_SPI1CON2_TXR                          1
#define HAL_LL_SPI_MASTER_SPI1INTE_SRMTIE                       0x80
#define HAL_LL_SPI_MASTER_SPI1INTE_TCZIE                        0x40
#define HAL_LL_SPI_MASTER_PIE2_SPI1IE                           0x40
#define HAL_LL_SPI_MASTER_SPI1TCNTL                             0
#define HAL_LL_SPI_MASTER_SPI1INTF_TCZIF                        6
#define HAL_LL_SPI_MASTER_SPI1INTF_SRMTIF                       7
#define HAL_LL_SPI_MASTER_CLK_POLARITY                          5
#define HAL_LL_SPI_MASTER_CLK_PHASE                             6
#define HAL_LL_SPI_MASTER_DATA_SAMPLE_MIDDLE                    7
#define HAL_LL_SPI_MASTER_MAX_FOSC_DIV                          2

// -------------------------------------------------------------- PRIVATE TYPES

/*!< @brief SPI register structure. */
typedef struct {
    hal_ll_base_addr_t hal_ll_spi1_clk_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_inte_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_intf_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_baud_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_twidth_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_status_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_con2_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_con1_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_con0_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_tcnth_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_tcntl_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_txb_reg_addr;
    hal_ll_base_addr_t hal_ll_spi1_rxb_reg_addr;
    hal_ll_base_addr_t hal_ll_pie2_reg_addr;
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI Master hardware specific structure */
typedef struct {
    const hal_ll_spi_master_base_handle_t *base;
    uint8_t module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
} hal_ll_spi_master_hw_specifics_map_t;

/*!< @brief SPI hw specific module values */
typedef struct {
    uint16_t pin_sck;
    uint16_t pin_miso;
    uint16_t pin_mosi;
} hal_ll_spi_pin_id;

/*!< @brief SPI Master hw specific error values */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

// ------------------------------------------------------------------ CONSTANTS
// SPI Master module registers array.
static const hal_ll_spi_master_base_handle_t hal_ll_spi_master_registers[SPI_MODULE_COUNT + 1] = {
    #ifdef SPI_MODULE
    {HAL_LL_SPI1CLK_ADDRESS,HAL_LL_SPI1INTE_ADDRESS,HAL_LL_SPI1INTF_ADDRESS,HAL_LL_SPI1BAUD_ADDRESS,HAL_LL_SPI1TWIDTH_ADDRESS,HAL_LL_SPI1STATUS_ADDRESS,HAL_LL_SPI1CON2_ADDRESS,HAL_LL_SPI1CON1_ADDRESS,HAL_LL_SPI1CON0_ADDRESS, HAL_LL_SPI1TCNTH_ADDRESS,HAL_LL_SPI1TCNTL_ADDRESS,HAL_LL_SPI1TXB_ADDRESS,HAL_LL_SPI1RXB_ADDRESS, HAL_LL_PIE2_ADDRESS},
    #endif

    #ifdef SPI_MODULE_1
    {HAL_LL_SPI1CLK_ADDRESS,HAL_LL_SPI1INTE_ADDRESS,HAL_LL_SPI1INTF_ADDRESS,HAL_LL_SPI1BAUD_ADDRESS,HAL_LL_SPI1TWIDTH_ADDRESS,HAL_LL_SPI1STATUS_ADDRESS,HAL_LL_SPI1CON2_ADDRESS,HAL_LL_SPI1CON1_ADDRESS,HAL_LL_SPI1CON0_ADDRESS, HAL_LL_SPI1TCNTH_ADDRESS,HAL_LL_SPI1TCNTL_ADDRESS,HAL_LL_SPI1TXB_ADDRESS,HAL_LL_SPI1RXB_ADDRESS, HAL_LL_PIE2_ADDRESS},
    #endif

    #ifdef SPI_MODULE_2
    {HAL_LL_SPI2CLK_ADDRESS,HAL_LL_SPI2INTE_ADDRESS,HAL_LL_SPI2INTF_ADDRESS,HAL_LL_SPI2BAUD_ADDRESS,HAL_LL_SPI2TWIDTH_ADDRESS,HAL_LL_SPI2STATUS_ADDRESS,HAL_LL_SPI2CON2_ADDRESS,HAL_LL_SPI2CON1_ADDRESS,HAL_LL_SPI2CON0_ADDRESS, HAL_LL_SPI2TCNTH_ADDRESS,HAL_LL_SPI2TCNTL_ADDRESS,HAL_LL_SPI2TXB_ADDRESS,HAL_LL_SPI2RXB_ADDRESS, HAL_LL_PIE2_ADDRESS},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR}
};

// ------------------------------------------------------------------ VARIABLES

/*!< @brief SPI Master hardware specific info */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[SPI_MODULE_COUNT + 1] = {
    #ifdef SPI_MODULE
    {&hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE)], hal_ll_spi_master_module_num(SPI_MODULE), {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    #ifdef SPI_MODULE_1
    {&hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_1)], hal_ll_spi_master_module_num(SPI_MODULE_1), {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    #ifdef SPI_MODULE_2
    {&hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_2)], hal_ll_spi_master_module_num(SPI_MODULE_2), {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    {&hal_ll_spi_master_registers[SPI_MODULE_COUNT], HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, NULL, NULL, NULL, NULL}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_spi_master_handle_register_t *low_level_handle;
static volatile hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_master_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
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
static hal_ll_pin_name_t hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map);

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
 * Sets adequate RPINRx and RPORx register
 * values for adequate functionality.
 * Also, sets TRISx register bit appropriately.
 *
 * @param[in]  *map - Object specific context handler.
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
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @return None
  */
static void hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
  * @brief  Initialize SPI module on hardware level.
  *
  * Initializes SPI module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_hw_init(hal_ll_spi_master_hw_specifics_map_t *map);

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
static void hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_pin_id *index_list);

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data);

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *write_data_buffer, size_t write_data_length);

/**
  * @brief  Perform a write then read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  *handle - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  length_write_data - Number of data to be written.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  length_read_data - Number of data to be read.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
hal_ll_err_t hal_ll_spi_master_write_then_read(handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data);

/**
  * @brief  Perform a transfer on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  data_buffer - User-specific data, or dummy data.
  * @return data Read data.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static uint8_t hal_ll_spi_master_transfer_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer);

/**
 * @brief  Set GPIO state.
 *
 * Sets adequate TRISx register
 * values for adequate functionality.
 *
 * @param[in] *map - Object specific context handler.
 * @param[in] hal_ll_state - init or deinit
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
 * @param pin - Object specific context handler.
 *
 * @return  none.
 *
 * @note PIC specific.
 */
static void hal_ll_spi_master_set_slew_rate(hal_ll_pin_name_t pin);

/**
 * @brief  Get SPI baud rate prescaler.
 *
 * Calculate Baud Rate Prescaler value.
 *
 * @param[in] *map - Object specific context handler.
 *
 * @return Prescaler value with the range from 255 (lowest speed possible) up to 0 (highest speed possible).
 *
 * @note PIC specific.
 */
static uint8_t hal_ll_spi_master_set_speed_prescaler(hal_ll_spi_master_hw_specifics_map_t *map);

/**
 * @brief  Get SPI baud rate.
 *
 * Get SPI speed which is available on hardware.
 *
 * @param[in] divider - Baud Rate Prescaler value (from 0 to 255).
 *
 * @return Actual SPI speed.
 *
 * @note PIC specific.
 */
static uint32_t hal_ll_spi_master_get_actual_speed(uint8_t divider);


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id) {

    hal_ll_spi_pin_id index_list[SPI_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint8_t pin_check_result;

    // Check user-defined pins.
    if ((pin_check_result = hal_ll_spi_master_check_pins(sck, miso, mosi, &index_list, handle_map)) == HAL_LL_PIN_NC) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    }

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ((hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.sck != sck) ||
        (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.miso != miso) ||
        (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.mosi != mosi)) {
        // Used only for chips which have SPI PPS pins.
        #if HAL_LL_SPI_PPS_ENABLED == true
        // Clear previous module pps
        hal_ll_pps_set_state(&hal_ll_spi_master_hw_specifics_map[pin_check_result], false);
        #endif

        // Map new pps.
        hal_ll_spi_master_map_pins(pin_check_result, &index_list);

        // Used only for chips which have SPI PPS pins.
        #if HAL_LL_SPI_PPS_ENABLED == true
        // Set mapped pps
        hal_ll_pps_set_state(&hal_ll_spi_master_hw_specifics_map[pin_check_result], true);
        #endif

        handle_map[pin_check_result]->init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;

    // Return the same info about module one level up (into the HAL level).
    handle_map[pin_check_result]->hal_ll_spi_master_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi(handle_t *handle) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_pin_id index_list[SPI_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);
    uint8_t pin_check_result;

    if ((pin_check_result = hal_ll_spi_master_check_pins(hal_ll_spi_master_hw_specifics_map_local->pins.sck,
                                                         hal_ll_spi_master_hw_specifics_map_local->pins.miso,
                                                         hal_ll_spi_master_hw_specifics_map_local->pins.mosi, &index_list, (void *)0 )) == HAL_LL_PIN_NC) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data(handle_t *handle, uint8_t dummy_data) {
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
}

hal_ll_err_t hal_ll_spi_master_write( handle_t *handle, uint8_t *write_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read( handle_t *handle, uint8_t *read_data_buffer, size_t length_data)
{
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read(handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data)
{
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_write_data);

    hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_read_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

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

    if(low_level_handle->hal_ll_spi_master_handle != NULL) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle  = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_local, false);
        hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_local, false);
        hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_local, false);

        hal_ll_spi_master_hw_specifics_map_local->pins.sck = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_spi_master_transfer_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer) {
   const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);

    // Wait for data exchange is not in progress.
    while ((check_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con2_reg_addr , HAL_LL_SPI_MASTER_SPI1CON2_BUSY)));

    // TXFIFO data is not required for a transfer.
    clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con2_reg_addr, HAL_LL_SPI_MASTER_SPI1CON2_TXR);

    // Received data is not stored in the FIFO.
    clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con2_reg_addr, HAL_LL_SPI_MASTER_SPI1CON2_RXR);

    // Spi Master Transfer counter counts 1 byte.
    set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_tcntl_reg_addr, HAL_LL_SPI_MASTER_SPI1TCNTL);

    // Set Transmit mode.
    set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con2_reg_addr, HAL_LL_SPI_MASTER_SPI1CON2_TXR);

    // Set Receive mode.
    set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con2_reg_addr, HAL_LL_SPI_MASTER_SPI1CON2_RXR);

    // Write user-defined data ('hal_ll_spi_master_read_bare_metal' procedure will send dummy data).
    *((volatile uint8_t *)hal_ll_hw_reg->hal_ll_spi1_txb_reg_addr) = (uint8_t)data_buffer;

    // Wait for transfer counter to be decremented to zero.
    while (!(check_reg_bit(hal_ll_hw_reg->hal_ll_spi1_intf_reg_addr , HAL_LL_SPI_MASTER_SPI1INTF_TCZIF)));

    // Wait for data exchange to be completed.
    while (!(check_reg_bit(hal_ll_hw_reg->hal_ll_spi1_intf_reg_addr , HAL_LL_SPI_MASTER_SPI1INTF_SRMTIF)));

    // Clear interrupt flag to be: no interrupt pending.
    clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_intf_reg_addr, HAL_LL_SPI_MASTER_SPI1INTF_TCZIF);

    // Clear interrupt flag to be: no data transfers have occurred.
    clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_intf_reg_addr, HAL_LL_SPI_MASTER_SPI1INTF_SRMTIF);

    // Return read data.
    return *((volatile uint8_t *)hal_ll_hw_reg->hal_ll_spi1_rxb_reg_addr);
}

static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *write_data_buffer, size_t write_data_length) {
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);

    uint16_t transfer_counter = NULL;

    // Write the first data to be transmitted into the SPI_DR register.
    for(transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++) {
        // If we are good to go (if the tx buffer value has been shifted to the shift register), write the data.
         hal_ll_spi_master_transfer_bare_metal(map, write_data_buffer[transfer_counter]);
    }
}

static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data) {
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);
    uint16_t transfer_counter = NULL;

    // Read the first data to be transmitted into the SPI_DR register.
    for(transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++) {
        // If we are good to go (if the value from shift register has been shifted to the rx register), read the data.
         read_data_buffer[transfer_counter] = hal_ll_spi_master_transfer_bare_metal(map, dummy_data);
    }
}

static hal_ll_pin_name_t hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin, hal_ll_pin_name_t mosi_pin, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map) {
    static const uint16_t sck_map_size  = (sizeof(_spi_sck_map)) / (sizeof(hal_ll_spi_master_pin_map_t));
    static const uint16_t miso_map_size = (sizeof(_spi_miso_map)) / (sizeof(hal_ll_spi_master_pin_map_t));
    static const uint16_t mosi_map_size = (sizeof(_spi_mosi_map)) / (sizeof(hal_ll_spi_master_pin_map_t));
    uint8_t hal_ll_module_id = 0;
    uint8_t index_counter = 0;
    uint16_t miso_index;
    uint16_t mosi_index;
    uint16_t sck_index;

    if ( (HAL_LL_PIN_NC == sck_pin) || (HAL_LL_PIN_NC == miso_pin) || (HAL_LL_PIN_NC == mosi_pin) ) {
        return HAL_LL_PIN_NC;
    }

    // Check pins from the specific pin maps with the user defined pins.
    for (sck_index = 0; sck_index < sck_map_size; sck_index++) {
        if (_spi_sck_map[sck_index].pin == sck_pin) {
            for (miso_index = 0; miso_index < miso_map_size; miso_index++) {
                if (_spi_miso_map[miso_index].pin == miso_pin) {
                    if (_spi_sck_map[sck_index].module_index ==_spi_miso_map[miso_index].module_index) {
                        for (mosi_index = 0; mosi_index < mosi_map_size; mosi_index++) {
                            if (_spi_mosi_map[mosi_index ].pin ==  mosi_pin) {
                                if (_spi_sck_map[sck_index].module_index ==_spi_mosi_map[mosi_index].module_index) {
                                    // Get module number
                                    hal_ll_module_id = _spi_sck_map[ sck_index ].module_index;

                                    // Map pin names
                                    index_list[hal_ll_module_id]->pin_sck = sck_index;
                                    index_list[hal_ll_module_id]->pin_miso = miso_index;
                                    index_list[hal_ll_module_id]->pin_mosi = mosi_index;

                                    // Check if module is taken
                                    if (NULL == handle_map[hal_ll_module_id]->hal_drv_spi_master_handle) {
                                        return hal_ll_module_id;
                                    } else if (SPI_MODULE_COUNT == ++index_counter) {
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

    if (index_counter) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static void hal_ll_spi_master_map_pins( uint8_t module_index, hal_ll_spi_pin_id *index_list ) {
    hal_ll_spi_master_hw_specifics_map[module_index].pins.sck  = _spi_sck_map[index_list[module_index]->pin_sck].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.miso = _spi_miso_map[index_list[module_index]->pin_miso].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.mosi = _spi_mosi_map[index_list[module_index]->pin_mosi].pin;
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_spi_master_handle_register_t));

    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while (hal_ll_module_count--) {
        if (hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[hal_ll_module_count ].base) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_set_slew_rate(hal_ll_pin_name_t pin) {
    uint8_t index;
    uint8_t map_size = sizeof(slew_rate_map) / sizeof(hal_ll_slew_rate_t);

    for (index = 0; index < map_size; index++) {
        if (slew_rate_map[index].pin == pin) {
            clear_reg_bit(slew_rate_map[index].slrcon_address, slew_rate_map[index].slrcon_address_bit);
            break;
        }
    }
}

static void hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    hal_ll_gpio_pin_t pin;

    if (hal_ll_state) {
        hal_ll_gpio_configure_pin(&pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_OUTPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_OUTPUT);

        // Set slew rate ( necessary for SPI baud rates greater then 4MHz ).
        hal_ll_spi_master_set_slew_rate(map->pins.sck);
        hal_ll_spi_master_set_slew_rate(map->pins.miso);
        hal_ll_spi_master_set_slew_rate(map->pins.mosi);
    } else
    {
        hal_ll_gpio_configure_pin(&pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_INPUT);
    }
}

static hal_ll_pps_err_t hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    hal_ll_pps_err_t hal_ll_status = HAL_LL_PPS_SUCCESS;

    if( (map->pins.sck != HAL_LL_PIN_NC) && (map->pins.miso != HAL_LL_PIN_NC) && (map->pins.mosi != HAL_LL_PIN_NC) ) {

        hal_ll_status = hal_ll_pps_map((map->pins.sck & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.sck & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, map->module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }

        hal_ll_status = hal_ll_pps_map((map->pins.miso & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.miso & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_INPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, map->module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }

        hal_ll_status = hal_ll_pps_map((map->pins.mosi & HAL_LL_NIBBLE_HIGH_8BIT) >> 4, map->pins.mosi & HAL_LL_NIBBLE_LOW_8BIT, HAL_LL_GPIO_DIGITAL_OUTPUT,
                                                HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, map->module_index, hal_ll_state);

        if (hal_ll_status != HAL_LL_PPS_SUCCESS) {
            return hal_ll_status;
        }
    } else {
        return HAL_LL_PPS_SUCCESS;
    }
}

static void hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {

    switch ((uint8_t)map->module_index + 1)
    {
        #if defined SPI_MODULE
        #if defined (HAL_LL_PMD_SPI1_ADDRESS)
        case (SPI_MODULE):
            if(hal_ll_state) {
                clear_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            } else {
                set_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            }
            break;
        #endif
        #endif
        #if defined SPI_MODULE_1
        #if defined (HAL_LL_PMD_SPI1_ADDRESS)
        case (SPI_MODULE_1):
            if(hal_ll_state) {
                clear_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            } else {
                set_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            }
            break;
        #endif
        #endif
        #if defined SPI_MODULE_2
        #if defined (HAL_LL_PMD_SPI2_ADDRESS)
        case (SPI_MODULE_2):
            if(hal_ll_state) {
                clear_reg_bit(HAL_LL_PMD_SPI2_ADDRESS, HAL_LL_SSP2_MODULE_BIT);
            } else {
                set_reg_bit(HAL_LL_PMD_SPI2_ADDRESS, HAL_LL_SSP2_MODULE_BIT);
            }
            break;
        #endif
        #endif
    }
}

static uint32_t hal_ll_spi_master_get_actual_speed(uint8_t divider) {

    return hal_ll_spi_master_speed_equation(divider);
}

static uint8_t hal_ll_spi_master_set_speed_prescaler(hal_ll_spi_master_hw_specifics_map_t *map) {

    // Prescaler value (starting from 0 -> highest SPI speed, up to 255 -> lowest SPI speed).
    uint8_t prescaler_val = 0;

    // Minimum bandwidth.
    uint32_t speed_minimum = hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK);

    // Maximum bandwidth.
    uint32_t speed_maximum = hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK);

    // If user-defined SPI speed is less then or equal to eligible hardware frequency, set SPI speed to be the minimal possible.
    if (map->speed <= speed_minimum) {

        return HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK;

      // If user-defined SPI speed is greater then or equal to eligible hardware frequency, set SPI speed to be the maximal possible.
    } else if (map->speed >= speed_maximum) {

        return HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK;

    // If user-defined SPI speed is in between, find as closest SPI speed prescaler as possible.
    } else {
        prescaler_val = hal_ll_spi_master_prescaler_equation;

        return prescaler_val;
    }
}

static void hal_ll_spi_master_hw_init(hal_ll_spi_master_hw_specifics_map_t *map) {

    // Get hardware register list for user-defined SPI pins.
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);

    // Prescaler value (starting from 0 -> highest SPI speed, up to 255 -> lowest SPI speed).
    uint8_t prescaler_val = 0;

    // Master Synchronous Serial Port Disable.
    clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con0_reg_addr, HAL_LL_SPI_MASTER_SPI1CON0_EN);

    // Bit-length mode select bit.
    set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con0_reg_addr, HAL_LL_SPI_MASTER_SPI1CON0_BMODE);

    // SPI module operates as the bus master.
    set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con0_reg_addr, HAL_LL_SPI_MASTER_SPI1CON0_MST);

    // Choose whether idle state for the clock is high level (1) or low level (0) - Polarity Control bit.
    if (map->mode <= HAL_LL_SPI_MASTER_MODE_1) {
        clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con1_reg_addr, HAL_LL_SPI_MASTER_CLK_POLARITY);
    } else  {
        set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con1_reg_addr, HAL_LL_SPI_MASTER_CLK_POLARITY);
    }

    // Choose whether input data is sampled at the end (1) or in the middle od data output.
    clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con1_reg_addr, HAL_LL_SPI_MASTER_DATA_SAMPLE_MIDDLE);

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0) - Clock Edge Select bit.
    if (map->mode == HAL_LL_SPI_MASTER_MODE_0 || map->mode == HAL_LL_SPI_MASTER_MODE_2) {
        set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con1_reg_addr, HAL_LL_SPI_MASTER_CLK_PHASE);
    } else {
        clear_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con1_reg_addr, HAL_LL_SPI_MASTER_CLK_PHASE);
    }

    // Clear SPI1CON2 register.
    *((uint8_t *)hal_ll_hw_reg->hal_ll_spi1_con2_reg_addr) = 0;

    // Set FOSC to be the main clock source for the SPI Master module.
    *((uint8_t *)hal_ll_hw_reg->hal_ll_spi1_clk_reg_addr) = 0;

    // Set SPI Master baud rate prescaler.
    prescaler_val = hal_ll_spi_master_set_speed_prescaler(map);

    // Set final SPI baud rate prescaler value.
    *((uint8_t *)hal_ll_hw_reg->hal_ll_spi1_baud_reg_addr) = prescaler_val;

    // Shift Register Empty Interrupt Enable.
    *((uint8_t *)hal_ll_hw_reg->hal_ll_spi1_inte_reg_addr) |= HAL_LL_SPI_MASTER_SPI1INTE_SRMTIE;

    // Shift Register Empty Interrupt Enable.
    *((uint8_t *)hal_ll_hw_reg->hal_ll_spi1_inte_reg_addr) |= HAL_LL_SPI_MASTER_SPI1INTE_TCZIE;

    // Master Synchronous Serial Port Enable.
    set_reg_bit(hal_ll_hw_reg->hal_ll_spi1_con0_reg_addr, HAL_LL_SPI_MASTER_SPI1CON0_EN);

    // Get actual SPI Master baud rate.
    map->hw_actual_speed = hal_ll_spi_master_get_actual_speed(prescaler_val);
}

static void hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map) {

    // Enable specific clock module.
    hal_ll_spi_master_set_clock (map, true);

    // Enable specific pin functions.
    hal_ll_spi_master_configure_pins(map, true);

    // Finally, write user-defined settings into hardware registers.
    hal_ll_spi_master_hw_init(map);
}
// ------------------------------------------------------------------------- END
