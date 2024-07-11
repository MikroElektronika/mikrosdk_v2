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
 * @brief SPI Master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_rcu.h"
#include "hal_ll_spi_master.h"
#include "hal_ll_spi_master_pin_map.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = {(handle_t *)NULL, (handle_t *)NULL, false};

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address ((hal_ll_spi_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle) ((hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                              (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base

/*!< @brief Control Register 0 (SPI_CTL0) constants. */
#define HAL_LL_SPI_MASTER_SSI_1 (8)
#define HAL_LL_SPI_MASTER_ENABLE (6)
#define HAL_LL_SPI_MASTER_CLK_PHASE (0)
#define HAL_LL_SPI_MASTER_SELECTION (2)
#define HAL_LL_SPI_MASTER_SSM_ENABLE (9)
#define HAL_LL_SPI_MASTER_CLK_POLARITY (1)

/*!< @brief Control Register 1 (SPI_CTL1) constants. */
#define HAL_LL_SPI_MASTER_SSOE_BIT (2)

/*!< @brief Status Register (SPI_STAT) constants. */
#define HAL_LL_SPI_MASTER_RXNE (0)

/*!< @brief Helper macros for enabling clocks for SPI modules (APB2 and APB1 registers). */
#define HAL_LL_SPI0_MASTER_ENABLE (12)
#define HAL_LL_SPI1_MASTER_ENABLE (14)
#define HAL_LL_SPI2_MASTER_ENABLE (15)

/*!< @brief Helper macro for retrieving SPI baud rate. */
#define hal_ll_spi_master_get_speed(_fosc,_speed) (_speed >= _fosc/2)? (0):\
                                                  ((_speed <= _fosc/2)  && (_speed > _fosc/4))?  (0):\
                                                  ((_speed <= _fosc/4)  && (_speed > _fosc/8))?  (0x0008UL):\
                                                  ((_speed <= _fosc/8)  && (_speed > _fosc/16))? (0x0010UL):\
                                                  ((_speed <= _fosc/16) && (_speed > _fosc/32))? (0x0018UL):\
                                                  ((_speed <= _fosc/32) && (_speed > _fosc/64))? (0x0020UL):\
                                                  ((_speed <= _fosc/64) && (_speed > _fosc/128))?(0x0028UL):\
                                                  ((_speed <= _fosc/128)&& (_speed > _fosc/256))?(0x0030UL):(0x0038UL)

/*!< @brief Helper macro for retrieving actual hardware SPI baud rate. */
#define hal_ll_spi_master_get_actual_speed(_fosc,_divider) (_divider == 0)?(_fosc/2):\
                                                           (_divider == 0x0008UL)?(_fosc/4):\
                                                           (_divider == 0x0010UL)?(_fosc/8):\
                                                           (_divider == 0x0018UL)?(_fosc/16):\
                                                           (_divider == 0x0020UL)?(_fosc/32):\
                                                           (_divider == 0x0028UL)?(_fosc/64):\
                                                           (_divider == 0x0030UL)?(_fosc/128):\
                                                           (_divider == 0x0038UL)?(_fosc/256):(_fosc/256)

/*!< @brief Default SPI Master bit-rate if no speed is set. */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief SPI register structure. */
typedef struct {
    hal_ll_base_addr_t spi_ctl0; /* Control Register 0. */
    hal_ll_base_addr_t spi_ctl1; /* Control Register 1. */
    hal_ll_base_addr_t spi_stat; /* Status Register. */
    hal_ll_base_addr_t spi_data; /* Data Register. */
    hal_ll_base_addr_t spi_crcpoly; /* CRC Polynomial Register. */
    hal_ll_base_addr_t spi_rcrc; /* Rx CRC Register. */
    hal_ll_base_addr_t spi_tcrc; /* Tx CRC Register. */
    hal_ll_base_addr_t spi_i2sctl; /* I2S Control Register. */
    hal_ll_base_addr_t spi_i2spsc; /* I2S Clock Prescaler Register. */
} hal_ll_spi_master_base_handle_t;

/*!< @brief SPI hardware specific structure. */
typedef struct {
    hal_ll_base_addr_t base;
    uint8_t module_index;
    hal_ll_spi_master_pins_t pins;
    uint8_t  dummy_data;
    uint32_t speed;
    uint32_t hw_actual_speed;
    hal_ll_spi_master_mode_t mode;
} hal_ll_spi_master_hw_specifics_map_t;

/*!< @brief SPI hardware specific module values. */
typedef struct {
    hal_ll_pin_name_t pin_sck;
    hal_ll_pin_name_t pin_miso;
    hal_ll_pin_name_t pin_mosi;
} hal_ll_spi_pin_id;

/*!< @brief SPI hardware specific error values. */
typedef enum {
    HAL_LL_SPI_MASTER_SUCCESS = 0,
    HAL_LL_SPI_MASTER_WRONG_PINS,
    HAL_LL_SPI_MASTER_MODULE_ERROR,

    HAL_LL_SPI_MASTER_ERROR = (-1)
} hal_ll_spi_master_err_t;

// ------------------------------------------------------------------ VARIABLES
/*!< @brief SPI hardware specific info. */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[] = {
    #ifdef SPI_MODULE_0
    { HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    #ifdef SPI_MODULE_1
    { HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    #ifdef SPI_MODULE_2
    { HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT },
    #endif

    {HAL_LL_MODULE_ERROR, (uint8_t)HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0, 0}
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
  * index numbers have to be the same for all pins.
  *
  * @param[in] sck - SCK pre-defined pin name.
  * @param[in] miso - MISO pre-defined pin name.
  * @param[in] mosi - MOSI pre-defined pin name.
  * @param[out] *index_list - Index list address.
  * @param[out] *handle_map - SPI HAL low level handle register.
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map );

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
  * @brief  Enable clock for SPI Master module on hardware level.
  *
  * Initializes SPI Master module clock on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Hardware specifics map information.
  * @param[in]  hal_ll_state - True(enable clock)/False(disable clock).
  * @param[in]  *clock_value - SPI Master baud rate value taken from a specific peripheral clock bus.
  * @return None
  */
static void hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state, uint32_t *clock_value);

/**
  * @brief  Sets SPI Master pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if SPI is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  * @return None
  */
static void hal_ll_spi_master_alternate_functions_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
  * @brief  Full SPI Master module initialization procedure.
  *
  * Initializes SPI Master module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  * @return None
  */
static void hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map);

/**
  * @brief  Perform a read on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  *hal_ll_hw_reg - Hardware register list for user-defined SPI pins.
  * @param[in]  *read_data_buffer - Pointer to data buffer.
  * @param[in]  read_data_length - Number of data to be read.
  * @param[in]  dummy_data - Data required for read procedure.
  * @return None
  */
static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data);

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  *hal_ll_hw_reg - Hardware register list for user-defined SPI pins.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return None
  */
static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buffer, size_t write_data_length);

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
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * SPI SCK, MISO and MOSI pins.
 *
 * @param[in]  module_index SPI HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCK, MISO and MOSI map index values and module number
 * @return None
 */
static void hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_pin_id *index_list);


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id) {

    hal_ll_spi_pin_id index_list[SPI_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check user-defined pins.
    if ((pin_check_result = hal_ll_spi_master_check_pins(sck, miso, mosi, &index_list, handle_map)) == HAL_LL_PIN_NC) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };
    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not have to take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ((hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.sck.pin_name != sck) ||
        (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.miso.pin_name != miso) ||
        (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.mosi.pin_name != mosi) ) {

        hal_ll_spi_master_alternate_functions_set_state(&hal_ll_spi_master_hw_specifics_map[pin_check_result], false);

        hal_ll_spi_master_map_pins(pin_check_result, &index_list);

        hal_ll_spi_master_alternate_functions_set_state(&hal_ll_spi_master_hw_specifics_map[pin_check_result], true);

        handle_map[pin_check_result].init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;

    // Return the same info about module one level up ( into the HAL level ).
    handle_map[pin_check_result].hal_ll_spi_master_handle = (handle_t*)&hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle;

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

    if(hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
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

    if ( HAL_LL_MODULE_ERROR == hal_ll_spi_master_hw_specifics_map_local->base ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

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

    if ( HAL_LL_MODULE_ERROR == hal_ll_spi_master_hw_specifics_map_local->base ) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    // Insert user-defined mode into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close(handle_t* handle) {
    uint32_t dummy;
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle != NULL) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_local, true, &dummy);
        hal_ll_spi_master_alternate_functions_set_state(hal_ll_spi_master_hw_specifics_map_local, false);
        hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_local, false, &dummy);

        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
uint8_t hal_ll_spi_master_transfer_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t data_buffer) {
    // Write user-defined data ( 'hal_ll_spi_master_read_bare_metal' procedure will send dummy data ).
    *((volatile uint8_t *)&hal_ll_hw_reg->spi_data) = (uint8_t)data_buffer;

    // "Receive buffer not empty" flag is needed in order to read 8 bits of data from SPI bus.
    while ( !( check_reg_bit( &( hal_ll_hw_reg->spi_stat ), HAL_LL_SPI_MASTER_RXNE ) ) );

    // Return read data.
    return *( (volatile uint8_t *)&hal_ll_hw_reg->spi_data );
}

static void hal_ll_spi_master_write_bare_metal( hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buffer, size_t write_data_length ) {
    size_t transfer_counter = 0;

    // Write the first data to be transmitted into the SPI_DR register.
    for(transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++) {
        // If we are good to go ( if the tx buffer value has been shifted to the shift register ), write the data.
        hal_ll_spi_master_transfer_bare_metal( hal_ll_hw_reg, write_data_buffer[transfer_counter]);
    }
}

static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data) {
    size_t transfer_counter = 0;

    // Read the first data to be transmitted into the SPI_DR register.
    for(transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++) {
        // If we are good to go ( if the value from shift register has been shifted to the rx register ), read the data.
        read_data_buffer[transfer_counter] = hal_ll_spi_master_transfer_bare_metal(hal_ll_hw_reg, dummy_data);
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

static void hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_pin_id *index_list) {
    // if every single pin is OK, insert them into this new map, and use this map in all low level functions.
    hal_ll_spi_master_hw_specifics_map[module_index].pins.sck.pin_name  = _spi_sck_map[index_list[module_index].pin_sck].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.miso.pin_name = _spi_miso_map[index_list[module_index].pin_miso].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.mosi.pin_name = _spi_mosi_map[index_list[module_index].pin_mosi].pin;

    // SCK, MISO and MOSI pins could have different alternate function settings, hence save all the AF-s.
    hal_ll_spi_master_hw_specifics_map[module_index].pins.sck.pin_af   = _spi_sck_map[index_list[module_index].pin_sck].af;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.miso.pin_af  = _spi_miso_map[index_list[module_index].pin_miso].af;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.mosi.pin_af  = _spi_mosi_map[index_list[module_index].pin_mosi].af;
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof( hal_ll_spi_master_handle_register_t));

    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof( hal_ll_spi_master_handle_register_t));

    while (hal_ll_module_count--) {
        if (hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state, uint32_t *clock_value) {
    rcu_clocks_t hal_ll_spi_clock_structure;

    system_rcu_get_clocks(&hal_ll_spi_clock_structure);

    switch (map->module_index) {
        #if defined (SPI_MODULE_0)
        case (hal_ll_spi_master_module_num(SPI_MODULE_0)):
            if( hal_ll_state ) {
                set_reg_bit( RCU_APB2EN, HAL_LL_SPI0_MASTER_ENABLE );
            } else {
                clear_reg_bit( RCU_APB2EN, HAL_LL_SPI0_MASTER_ENABLE );
            }
            *clock_value = hal_ll_spi_clock_structure.rcu_clocks_apb2;
            break;
        #endif
        #if defined (SPI_MODULE_1)
        case (hal_ll_spi_master_module_num(SPI_MODULE_1)):
            if( hal_ll_state ) {
                set_reg_bit( RCU_APB1EN, HAL_LL_SPI1_MASTER_ENABLE );
            } else {
                clear_reg_bit( RCU_APB1EN, HAL_LL_SPI1_MASTER_ENABLE );
            }
            *clock_value = hal_ll_spi_clock_structure.rcu_clocks_apb1;
            break;
        #endif
        #if defined (SPI_MODULE_2)
        case (hal_ll_spi_master_module_num(SPI_MODULE_2)):
            if( hal_ll_state ) {
                set_reg_bit( RCU_APB1EN, HAL_LL_SPI2_MASTER_ENABLE );
            } else {
                clear_reg_bit( RCU_APB1EN, HAL_LL_SPI2_MASTER_ENABLE );
            }
            *clock_value = hal_ll_spi_clock_structure.rcu_clocks_apb1;
            break;
        #endif
    }
}

static void hal_ll_spi_master_alternate_functions_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    module_struct module;
    uint32_t spi_config;

    if((map->pins.sck.pin_name != HAL_LL_PIN_NC) && (map->pins.miso.pin_name != HAL_LL_PIN_NC) && (map->pins.miso.pin_name != HAL_LL_PIN_NC)) {
        module.pins[0] = VALUE(map->pins.sck.pin_name, map->pins.sck.pin_af);
        module.pins[1] = VALUE(map->pins.miso.pin_name, map->pins.miso.pin_af);
        module.pins[2] = VALUE(map->pins.mosi.pin_name, map->pins.mosi.pin_af);
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        spi_config = GPIO_CTL_CFG_OUTPUT_AFIO_PP | GPIO_CTL_MODE_OUTPUT_SPEED_M50;

        module.configs[0] = spi_config;
        module.configs[1] = spi_config;
        module.configs[2] = spi_config;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        module.gpio_remap = map->pins.sck.pin_af;

        hal_ll_gpio_module_struct_init(&module, hal_ll_state);
    }
}

static uint32_t hal_ll_spi_master_hw_init(hal_ll_spi_master_hw_specifics_map_t *map, uint32_t clock_value) {
    uint32_t temp_speed;

    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;

    // Reset all the settings in control register.
    hal_ll_hw_reg->spi_ctl0 = 0;

    // Populate appropriate register values to get appropriate data transfer baud rate prescalers.
    temp_speed = hal_ll_spi_master_get_speed(clock_value, map->speed);
    hal_ll_hw_reg->spi_ctl0 = temp_speed;

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if (map->mode <= HAL_LL_SPI_MASTER_MODE_1) {
        clear_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_CLK_POLARITY);
    } else {
        set_reg_bit(&( hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_CLK_POLARITY);
    }

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0).
    if (map->mode == HAL_LL_SPI_MASTER_MODE_0 || map->mode == HAL_LL_SPI_MASTER_MODE_2) {
        clear_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_CLK_PHASE);
    } else {
        set_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_CLK_PHASE);
    }

    // Set default values for SPI Master configuration.
    set_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_SSM_ENABLE);
    set_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_SSI_1);
    set_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_SELECTION);

    // Set Slave Select Output Enable bit.
    set_reg_bit(&(hal_ll_hw_reg->spi_ctl1), HAL_LL_SPI_MASTER_SSOE_BIT);

    // Enable SPI peripheral.
    set_reg_bit(&(hal_ll_hw_reg->spi_ctl0), HAL_LL_SPI_MASTER_ENABLE);

    return (hal_ll_spi_master_get_actual_speed(clock_value, temp_speed));
}

static void hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map) {
    uint32_t clock_value;

    // Enable specific clock module.
    hal_ll_spi_master_set_clock (map, true, &clock_value);

    // Enable specific alternate functions.
    hal_ll_spi_master_alternate_functions_set_state(map, true);

    // Finally, write user-defined settings into hardware registers.
    hal_ll_spi_master_hw_init(map, clock_value);
}
// ------------------------------------------------------------------------- END
