/****************************************************************************
**
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file  hal_ll_spi_master.c
 * @brief SPI master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_spi_master.h"
#include "hal_ll_gpio_port.h"
#include "hal_ll_pps.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_slrcon_map.h"
#include "assembly.h"

#ifdef __XC8__
#if FSR_APPROACH
#include "mcu.h"
#endif
#endif

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = {(handle_t *)NULL, (handle_t *)NULL, false};

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address              ((hal_ll_spi_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle                            (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle)              ((const hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle              ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                                (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base

/*!< @brief Macros used for register manipulation */
#define HAL_LL_SPI_MASTER_CLK_POLARITY                      4
#define HAL_LL_SPI_MASTER_CLK_PHASE                         6
#define HAL_LL_SPI_MASTER_DATA_SAMPLE_MIDDLE                7

#define HAL_LL_SPI_MASTER_SSPSTAT_BF                        0
#define HAL_LL_SPI_MASTER_SSPCON1_SSPEN                     5
#define HAL_LL_SPI_MASTER_SSPSTAT_CKE                       6
#define HAL_LL_SPI_MASTER_SSPSTAT_SMP                       7

#define _fosc                                               (Get_Fosc_kHz()*1000)

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K 100000

/*!< @brief SPI Master Speed implementation 1 */
#if defined (HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_1)

#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_64          64
#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_16          16
#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_4           4

#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK         2
#define HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK      1
#define HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK         0
#define hal_ll_spi_master_get_prescaler(_divider)           ( ( _divider == 0 )?(HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_4):\
                                                            ( ( _divider == 1 )?(HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_16):(HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_64) ) )
#define hal_ll_spi_master_speed_equation(_divider)          ( _fosc / hal_ll_spi_master_get_prescaler(_divider) )
#define HAL_LL_SPI_MASTER_MEAN_SPEED_1                      ( ( ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK) ) +\
                                                            ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK) ) ) / 2 )
#define HAL_LL_SPI_MASTER_MEAN_SPEED_2                      ( ( ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK) ) +\
                                                            ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK) ) ) / 2 )
#define HAL_LL_SPI_MASTER_MEDIUM_SPEED                      ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK) )
#define hal_ll_spi_master_prescaler_equation                ( ( ( map->speed < HAL_LL_SPI_MASTER_MEAN_SPEED_1 ) && ( map->speed >= speed_minimum ) )?(2):\
                                                            ( ( ( map->speed >= HAL_LL_SPI_MASTER_MEAN_SPEED_1 ) && ( map->speed <= HAL_LL_SPI_MASTER_MEDIUM_SPEED ) )?(1):\
                                                            ( ( ( map->speed > HAL_LL_SPI_MASTER_MEDIUM_SPEED) && ( map->speed < HAL_LL_SPI_MASTER_MEAN_SPEED_2) )?(1):\
                                                            ( ( ( map->speed >= HAL_LL_SPI_MASTER_MEAN_SPEED_2) && ( map->speed <= speed_maximum ) )?(0):(2) ) ) ) )
//EOF SPI Master Speed implementation 1.

/*!< @brief SPI Master Speed implementation 2 */
#elif defined (HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_2)

#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_64          64
#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_16          16
#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_8           8
#define HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_4           4

#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK         2
#define HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK      1
#define HAL_LL_SPI_MASTER_HIGH_SPEED_RESOLUTION_MASK        10
#define HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK         0
#define hal_ll_spi_master_get_prescaler(_divider)           ( ( _divider == HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK )?( HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_4 ):\
                                                            ( ( _divider == HAL_LL_SPI_MASTER_HIGH_SPEED_RESOLUTION_MASK )?( HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_8 ):\
                                                            ( ( _divider == HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK )?( HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_16 ):\
                                                            ( HAL_LL_SPI_MASTER_SPEED_PRESCALER_VALUE_64 ) ) ) )
#define hal_ll_spi_master_speed_equation(_divider)          (_fosc / hal_ll_spi_master_get_prescaler(_divider) )
#define HAL_LL_SPI_MASTER_MEAN_SPEED_1                      ( ( ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK) ) + \
                                                            ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK) ) ) / 2 )
#define HAL_LL_SPI_MASTER_MEAN_SPEED_2                      ( ( ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK) ) + \
                                                            ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_HIGH_SPEED_RESOLUTION_MASK) ) ) / 2 )
#define HAL_LL_SPI_MASTER_MEAN_SPEED_3                      ( ( ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_HIGH_SPEED_RESOLUTION_MASK) ) + \
                                                            ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK) ) ) / 2 )
#define HAL_LL_SPI_MASTER_MEDIUM_SPEED                      ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_MEDIUM_SPEED_RESOLUTION_MASK) )
#define HAL_LL_SPI_MASTER_HIGH_SPEED                        ( hal_ll_spi_master_speed_equation(HAL_LL_SPI_MASTER_HIGH_SPEED_RESOLUTION_MASK) )
#define hal_ll_spi_master_prescaler_equation                ( ( ( map->speed < HAL_LL_SPI_MASTER_MEAN_SPEED_1) && ( map->speed >= speed_minimum ) )?(2):\
                                                            ( ( ( map->speed >= HAL_LL_SPI_MASTER_MEAN_SPEED_1 ) && ( map->speed <= HAL_LL_SPI_MASTER_MEDIUM_SPEED ) )?(1):\
                                                            ( ( ( map->speed < HAL_LL_SPI_MASTER_MEAN_SPEED_2 ) && ( map->speed >= HAL_LL_SPI_MASTER_MEDIUM_SPEED ) )?(1):\
                                                            ( ( ( map->speed >= HAL_LL_SPI_MASTER_MEAN_SPEED_2 ) && ( map->speed <= HAL_LL_SPI_MASTER_HIGH_SPEED ) )?(10):\
                                                            ( ( ( map->speed < HAL_LL_SPI_MASTER_MEAN_SPEED_3 ) && ( map->speed >= HAL_LL_SPI_MASTER_HIGH_SPEED ) )?(10):\
                                                            ( ( ( map->speed >= HAL_LL_SPI_MASTER_MEAN_SPEED_3 ) && ( map->speed <= speed_maximum ) )?(0):(2) ) ) ) ) ) )
//EOF SPI Master Speed implementation 2.

/*!< @brief SPI Master Speed implementation 3 */
#elif defined (HAL_LL_SPI_MASTER_SPEED_IMPLEMENTATION_3)
/*!< @brief Macros used for module speed (baud rate) manipulation */
#define HAL_LL_SPI_MASTER_MIN_SPEED_RESOLUTION_MASK         255
#define HAL_LL_SPI_MASTER_MAX_SPEED_RESOLUTION_MASK         0
#define HAL_LL_SPI_MASTER_BAUD_RATE_RELOAD_REGISTER         0xA

#define hal_ll_spi_master_speed_equation(_divider)          ( _fosc / (4 * (_divider + 1) ) )
#define hal_ll_spi_master_prescaler_equation                ( ( _fosc / (map->speed * 4) ) - 1 )
#else  //EOF SPI Master Speed implementation 3.
#   error "Selected chip is not supported. Check regex for supported chips: mikrosdk-2.0\targets\pic_8bit\mikroe\pic18\src\spi_master\CMakeLists.txt."
#endif

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief SPI register structure. */
typedef struct {
    hal_ll_base_addr_t sspcon1_reg_addr;
    hal_ll_base_addr_t sspstat_reg_addr;
    hal_ll_base_addr_t sspbuf_reg_addr;
    hal_ll_base_addr_t sspadd_reg_addr;
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
static const hal_ll_spi_master_base_handle_t hal_ll_spi_master_registers[ SPI_MODULE_COUNT + 1 ] = {
    #ifdef SPI_MODULE
    {HAL_LL_SSPCON1_SPI_MASTER_MODULE_1, HAL_LL_SSPSTAT_SPI_MASTER_MODULE_1, HAL_LL_SSPBUF_SPI_MASTER_MODULE_1, HAL_LL_SSP1ADD_ADDRESS},
    #endif

    #ifdef SPI_MODULE_1
    {HAL_LL_SSPCON1_SPI_MASTER_MODULE_1, HAL_LL_SSPSTAT_SPI_MASTER_MODULE_1, HAL_LL_SSPBUF_SPI_MASTER_MODULE_1, HAL_LL_SSP1ADD_ADDRESS},
    #endif

    #ifdef SPI_MODULE_2
    {HAL_LL_SSPCON1_SPI_MASTER_MODULE_2, HAL_LL_SSPSTAT_SPI_MASTER_MODULE_2, HAL_LL_SSPBUF_SPI_MASTER_MODULE_2, HAL_LL_SSP2ADD_ADDRESS},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR}
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief SPI Master hardware specific info */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[ SPI_MODULE_COUNT + 1 ] = {
 /*   #ifdef SPI_MODULE
    {&hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE)], hal_ll_spi_master_module_num(SPI_MODULE), {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    #ifdef SPI_MODULE_1
    {&hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_1)], hal_ll_spi_master_module_num(SPI_MODULE_1), {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    #ifdef SPI_MODULE_2
    {&hal_ll_spi_master_registers[hal_ll_spi_master_module_num(SPI_MODULE_2)], hal_ll_spi_master_module_num(SPI_MODULE_2), {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    {&hal_ll_spi_master_registers[SPI_MODULE_COUNT], HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}, NULL, NULL, NULL}
*/
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
static hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_get_specifics(handle_t handle);

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
static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t * __generic_ptr write_data_buffer, size_t write_data_length);

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
static uint8_t hal_ll_spi_master_transfer_byte_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer);

/**
  * @brief  Perform a simultaneous write and read on the SPI Master bus.
  *
  * Function performs a full-duplex SPI transfer. Each written byte results in
  * a received byte which is optionally stored in the read buffer.
  * If the write buffer is NULL, the configured dummy byte will be transmitted.
  * If the read buffer is NULL, the received data will be discarded.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to write data buffer.
  *                                  If NULL, dummy data will be used.
  * @param[out] *read_data_buffer - Pointer to read data buffer.
  *                                 If NULL, received data will be discarded.
  * @param[in]  data_length - Number of bytes to be transferred.
  *
  * @note TX FIFO is flushed and re-enabled on each byte transfer to ensure proper behavior.
  *       This implementation uses polling and is blocking.
  */
static void hal_ll_spi_master_transfer_bare_metal ( hal_ll_spi_master_hw_specifics_map_t *map,
                                                    uint8_t *write_data_buffer,
                                                    uint8_t *read_data_buffer,
                                                    size_t data_length );

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
 * Calculate Baud Rate Reload register value.
 *
 * @param[in] map - Object specific context handler.
 *
 * @return Prescaler value with the range from 255 (lowest speed possible) up to 1 (highest speed possible).
 *
 * @note PIC specific.
 */
static uint8_t hal_ll_spi_master_set_speed_prescaler(hal_ll_spi_master_hw_specifics_map_t *map);

/**
 * @brief  Get SPI baud rate.
 *
 * Get SPI speed which is available on hardware.
 *
 * @param[in] divider - Baud Rate Reload register value (from 1 to 255).
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
    if ((pin_check_result = hal_ll_spi_master_check_pins(sck, miso, mosi, index_list, handle_map)) == HAL_LL_PIN_NC) {
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
        hal_ll_pps_set_state(&hal_ll_spi_master_hw_specifics_map[ pin_check_result ], false);
        #endif

        // Map new pps.
        hal_ll_spi_master_map_pins(pin_check_result, index_list);

        // Used only for chips which have SPI PPS pins.
        #if HAL_LL_SPI_PPS_ENABLED == true
        // Set mapped pps
        hal_ll_pps_set_state(&hal_ll_spi_master_hw_specifics_map[ pin_check_result ], true);
        #endif

        handle_map[pin_check_result].init_ll_state = false;
    }

    // Return id of the SPI module that is going to be used.
    *hal_module_id = pin_check_result;

    // Insert current module into hal_ll_module_state map.
    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[ pin_check_result ].base;

    // Return the same info about module one level up (into the HAL level).
    //handle_map[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle;

     *hal_module_id = pin_check_result;

    {
        hal_ll_spi_master_handle_register_t *handle_entry;
        volatile hal_ll_spi_master_handle_register_t *module_state_entry;
        hal_ll_spi_master_hw_specifics_map_t *hw_entry;

        handle_entry = &handle_map[ pin_check_result ];
        module_state_entry = &hal_ll_module_state[ pin_check_result ];
        hw_entry = &hal_ll_spi_master_hw_specifics_map[ pin_check_result ];

        module_state_entry->hal_ll_spi_master_handle = ( handle_t *)&hw_entry->base;

        handle_entry->hal_ll_spi_master_handle = ( handle_t *)&module_state_entry->hal_ll_spi_master_handle;
    }

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_spi(handle_t *handle) {
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);
    hal_ll_spi_master_handle_register_t *hal_handle = (hal_ll_spi_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_spi_master_hw_specifics_map_local->module_index;

    hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data(handle_t *handle, uint8_t dummy_data) {
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
}

hal_ll_err_t hal_ll_spi_master_write(handle_t *handle, uint8_t * __generic_ptr write_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read(handle_t *handle, uint8_t *read_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read(handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

    hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_write_data);

    hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_read_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_transfer(handle_t *handle,
                                        uint8_t *write_data_buffer,
                                        uint8_t *read_data_buffer,
                                        size_t data_length) {
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

    if (NULL == low_level_handle->hal_ll_spi_master_handle) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    if (!hal_ll_spi_master_hw_specifics_map_local || !data_length) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    hal_ll_spi_master_transfer_bare_metal(hal_ll_spi_master_hw_specifics_map_local,
                                          write_data_buffer,
                                          read_data_buffer,
                                          data_length);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed(handle_t *handle, uint32_t speed) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

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
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

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
    /*low_level_handle = hal_ll_spi_master_get_handle;

    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = hal_ll_spi_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle != NULL) {
        low_level_handle->hal_ll_spi_master_handle  = NULL;
        low_level_handle->hal_drv_spi_master_handle  = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_local, true);
        hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_local, false);
        hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_local, false);
        hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_local, false);

        hal_ll_spi_master_hw_specifics_map_local->pins.sck = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi = HAL_LL_PIN_NC;
    }*/
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static uint8_t hal_ll_spi_master_transfer_byte_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t data_buffer) {
    switch (map->module_index + 1) {
        #ifdef SPI_MODULE
        //#ifdef HAL_LL_PMD_SPI1_ADDRESS
        case SPI_MODULE:
            
            break;
        #endif
        //#endif

        #ifdef SPI_MODULE_1
        case SPI_MODULE_1:
            SSP1BUF = data_buffer;
            while(!SSP1STATbits.BF);
            return SSP1BUF;
        break;
        #endif

        #ifdef SPI_MODULE_2
        case SPI_MODULE_2:
            SSP2BUF = data_buffer;
            while(!SSP2STATbits.BF);
            return SSP2BUF;
        break;
        #endif
    }

    
}

static void hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t * __generic_ptr write_data_buffer, size_t write_data_length) {
    size_t transfer_counter = 0;
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);

    // Write the first data to be transmitted into the SPI_DR register.
    for(transfer_counter = 0; transfer_counter < write_data_length; transfer_counter++) {
        // If we are good to go ( if the tx buffer value has been shifted to the shift register ), write the data.
        hal_ll_spi_master_transfer_byte_bare_metal(map, write_data_buffer[transfer_counter]);
    }
}

static void hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data) {
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);
    volatile size_t transfer_counter = 0;

    // Read the first data to be transmitted into the SPI_DR register.
    for(transfer_counter = 0; transfer_counter < read_data_length; transfer_counter++) {
        // If we are good to go (if the value from shift register has been shifted to the rx register), read the data.
        read_data_buffer[ transfer_counter ] = hal_ll_spi_master_transfer_byte_bare_metal(map, dummy_data);
    }
}

static void hal_ll_spi_master_transfer_bare_metal ( hal_ll_spi_master_hw_specifics_map_t *map,
                                                    uint8_t *write_data_buffer,
                                                    uint8_t *read_data_buffer,
                                                    size_t data_length ) {
    const hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = hal_ll_spi_master_get_base_struct(map->base);

    for (size_t i = 0; i < data_length; i++) {
        uint8_t tx_data = write_data_buffer ? write_data_buffer[i] : map->dummy_data;
        uint8_t rx_data = hal_ll_spi_master_transfer_byte_bare_metal(map, tx_data);

        if (read_data_buffer) {
            read_data_buffer[i] = rx_data;
        }
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
                                    if (NULL == handle_map[hal_ll_module_id].hal_drv_spi_master_handle) {
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
    hal_ll_spi_master_hw_specifics_map[module_index].pins.sck  = _spi_sck_map[index_list[module_index].pin_sck].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.miso = _spi_miso_map[index_list[module_index].pin_miso].pin;
    hal_ll_spi_master_hw_specifics_map[module_index].pins.mosi = _spi_mosi_map[index_list[module_index].pin_mosi].pin;
}

static hal_ll_spi_master_hw_specifics_map_t *hal_ll_spi_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof(hal_ll_spi_master_handle_register_t));
    static uint8_t hal_ll_module_error = sizeof(hal_ll_module_state) / (sizeof(hal_ll_spi_master_handle_register_t));

    #ifdef __XC8__
    #define REGISTER_HANDLE hal_ll_spi_master_handle
    #define REGISTER_HANDLE_TYPE hal_ll_spi_master_handle_register_t
    memory_width tmp_addr = 0;
    #if !(FSR_APPROACH)
    // On 8-bit PIC microcontrollers, pointers are often only 8 bits wide by default,
    // meaning they can only access addresses within a single memory page.
    // Circumvent this issue by concatenating the address to one 16-bit wide variable.
    memory_width *tmp_ptr, tmp_values[NUMBER_OF_BYTES] = {0};
    REGISTER_HANDLE_TYPE *handle_register = (REGISTER_HANDLE_TYPE *)handle;
    memory_width current_addr = &handle_register->REGISTER_HANDLE;

    for (uint8_t i = 0; i < NUMBER_OF_BYTES; i++) {
        current_addr += i;
        tmp_values[i] = read_reg(current_addr);
    }

    current_addr = 0;
    for (uint8_t i=0; i<NUMBER_OF_BYTES; i++) {
        current_addr = current_addr | (tmp_values[i] << (8*i));
    }
    #else
    /**
     * @brief Alternate approach with indirect register access.
     */
    memory_width *tmp_ptr, current_addr = 0;
    REGISTER_HANDLE_TYPE *handle_register = (REGISTER_HANDLE_TYPE *)handle;
    FSR0 = &handle_register->REGISTER_HANDLE;
    for (uint8_t i=0; i<NUMBER_OF_BYTES; i++) {
        current_addr = current_addr | (read_reg(FSR0++) << (8*i));
    }
    #endif
    tmp_ptr = current_addr;
    current_addr = *tmp_ptr;
    #endif

  while (hal_ll_module_count--) {
        #ifdef __XC8__
        tmp_addr = &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        if (current_addr == tmp_addr) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
        #else
        if (hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
        #endif
    }

    // If NOK, return pointer to the last row of this map ( point to null pointer ).
    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void hal_ll_spi_master_set_slew_rate(hal_ll_pin_name_t pin) {
    
    uint8_t port = pin >> 4;
    uint8_t pin_num = pin & 0x0F;

    /*switch(port){  // Setting SDO because it can be any GPIO pin
                case 0:
                    switch(pin){
                        case 0:
                            SLRCONAbits.SLRCONA0 = 0;
                        break;
                        case 1:
                            TRISAbits.TRISA1 = 0;
                        break;
                        case 2:
                            TRISAbits.TRISA2 = 0;
                        break;
                        case 3:
                            TRISAbits.TRISA3 = 0;
                        break;
                        case 4:
                            TRISAbits.TRISA4 = 0;
                        break;
                        case 5:
                            TRISAbits.TRISA5 = 0;
                        break;
                        case 6:
                            TRISAbits.TRISA6 = 0;
                        break;
                        case 7:
                            TRISAbits.TRISA7 = 0;
                        break;
                    }
                break;

                case 1:
                    switch(pin){
                        case 0:
                            TRISBbits.TRISB0 = 0;
                        break;
                        case 1:
                            TRISBbits.TRISB1 = 0;
                        break;
                        case 2:
                            TRISBbits.TRISB2 = 0;
                        break;
                        case 3:
                            TRISBbits.TRISB3 = 0;
                        break;
                        case 4:
                            TRISBbits.TRISB4 = 0;
                        break;
                        case 5:
                            TRISBbits.TRISB5 = 0;
                        break;
                        case 6:
                            TRISBbits.TRISB6 = 0;
                        break;
                        case 7:
                            TRISBbits.TRISB7 = 0;
                        break;
                    }
                break;

                case 2:
                    switch(pin){
                        case 0:
                            TRISCbits.TRISC0 = 0;
                        break;
                        case 1:
                            TRISCbits.TRISC1 = 0;
                        break;
                        case 2:
                            TRISCbits.TRISC2 = 0;
                        break;
                        case 3:
                            TRISCbits.TRISC3 = 0;
                        break;
                        case 4:
                            TRISCbits.TRISC4 = 0;
                        break;
                        case 5:
                            TRISCbits.TRISC5 = 0;
                        break;
                        case 6:
                            TRISCbits.TRISC6 = 0;
                        break;
                        case 7:
                            TRISCbits.TRISC7 = 0;
                        break;
                    }
                break;
                case 3:
                    switch(pin){
                        case 0:
                            TRISDbits.TRISD0 = 0;
                        break;
                        case 1:
                            TRISDbits.TRISD1 = 0;
                        break;
                        case 2:
                            TRISDbits.TRISD2 = 0;
                        break;
                        case 3:
                            TRISDbits.TRISD3 = 0;
                        break;
                        case 4:
                            TRISDbits.TRISD4 = 0;
                        break;
                        case 5:
                            TRISDbits.TRISD5 = 0;
                        break;
                        case 6:
                            TRISDbits.TRISD6 = 0;
                        break;
                        case 7:
                            TRISDbits.TRISD7 = 0;
                        break;
                    }
                break;
            }*/
    
    /*uint8_t index;
    uint8_t map_size = sizeof(slew_rate_map) / sizeof(hal_ll_slew_rate_t);

    for (index = 0; index < map_size; index++) {
        if (slew_rate_map[index].pin == pin) {
            clear_reg_bit(slew_rate_map[index].slrcon_address, slew_rate_map[index].slrcon_address_bit);
            break;
        }
    }*/
}

static void hal_ll_spi_master_configure_pins(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    hal_ll_gpio_pin_t pin;

    if (hal_ll_state) {
        hal_ll_gpio_configure_pin(&pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_OUTPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_OUTPUT);

        // Set slew rate.
        hal_ll_spi_master_set_slew_rate(map->pins.sck);
        hal_ll_spi_master_set_slew_rate(map->pins.miso);
        hal_ll_spi_master_set_slew_rate(map->pins.mosi);

    } else {
        hal_ll_gpio_configure_pin(&pin, map->pins.miso, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.mosi, HAL_LL_GPIO_DIGITAL_INPUT);
        hal_ll_gpio_configure_pin(&pin, map->pins.sck, HAL_LL_GPIO_DIGITAL_INPUT);
    }
}

static hal_ll_pps_err_t hal_ll_pps_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    
    uint8_t port = map->pins.mosi >> 4;
    uint8_t pin = map->pins.mosi & 0x0F;

    switch (map->module_index + 1) {
        #ifdef SPI_MODULE
        //#ifdef HAL_LL_PMD_SPI1_ADDRESS
        case SPI_MODULE:
            
            break;
        #endif
        //#endif

        #ifdef SPI_MODULE_1
        case SPI_MODULE_1:

            

            PPSLOCK = 0x55;  // PPS lock sequence
            PPSLOCK = 0xAA;    
            PPSLOCKbits.PPSLOCKED = 0;
        
            switch(port){  // Setting SDO because it can be any GPIO pin
                case 0:
                    switch(pin){
                        case 0:
                            RA0PPS = 0x1C;
                        break;
                        case 1:
                            RA1PPS = 0x1C;
                        break;
                        case 2:
                            RA2PPS = 0x1C;
                        break;
                        case 3:
                            RA3PPS = 0x1C;
                        break;
                        case 4:
                            RA4PPS = 0x1C;
                        break;
                        case 5:
                            RA5PPS = 0x1C;
                        break;
                        case 6:
                            RA6PPS = 0x1C;
                        break;
                        case 7:
                            RA7PPS = 0x1C;
                        break;
                    }
                break;

                case 1:
                    switch(pin){
                        case 0:
                            RB0PPS = 0x1C;
                        break;
                        case 1:
                            RB1PPS = 0x1C;
                        break;
                        case 2:
                            RB2PPS = 0x1C;
                        break;
                        case 3:
                            RB3PPS = 0x1C;
                        break;
                        case 4:
                            RB4PPS = 0x1C;
                        break;
                        case 5:
                            RB5PPS = 0x1C;
                        break;
                        case 6:
                            RB6PPS = 0x1C;
                        break;
                        case 7:
                            RB7PPS = 0x1C;
                        break;
                    }
                break;

                case 2:
                    switch(pin){
                        case 0:
                            RC0PPS = 0x1C;
                        break;
                        case 1:
                            RC1PPS = 0x1C;
                        break;
                        case 2:
                            RC2PPS = 0x1C;
                        break;
                        case 3:
                            RC3PPS = 0x1C;
                        break;
                        case 4:
                            RC4PPS = 0x1C;
                        break;
                        case 5:
                            RC5PPS = 0x1C;
                        break;
                        case 6:
                            RC6PPS = 0x1C;
                        break;
                        case 7:
                            RC7PPS = 0x1C;
                        break;
                    }
                break;
                case 3:
                    switch(pin){
                        case 0:
                            RD0PPS = 0x1C;
                        break;
                        case 1:
                            RD1PPS = 0x1C;
                        break;
                        case 2:
                            RD2PPS = 0x1C;
                        break;
                        case 3:
                            RD3PPS = 0x1C;
                        break;
                        case 4:
                            RD4PPS = 0x1C;
                        break;
                        case 5:
                            RD5PPS = 0x1C;
                        break;
                        case 6:
                            RD6PPS = 0x1C;
                        break;
                        case 7:
                            RD7PPS = 0x1C;
                        break;
                    }
                break;
            }

            RC3PPS = 0x1B; // RC3 SCL1
            SSP1DATPPS = 0x14;//(((map->pins.mosi >> 4) * 8) + (map->pins.mosi & 0x0F));
            
            
            PPSLOCK = 0x55;
            PPSLOCK = 0xAA;
            PPSLOCKbits.PPSLOCKED = 1;   
        break;
        #endif

        #ifdef SPI_MODULE_2
        case SPI_MODULE_2:
            PPSLOCK = 0x55;  // PPS lock sequence
            PPSLOCK = 0xAA;    
            PPSLOCKbits.PPSLOCKED = 0;
        
            switch(port){
                case 0:
                    switch(pin){
                        case 0:
                            RA0PPS = 0x1E;
                        break;
                        case 1:
                            RA1PPS = 0x1E;
                        break;
                        case 2:
                            RA2PPS = 0x1E;
                        break;
                        case 3:
                            RA3PPS = 0x1E;
                        break;
                        case 4:
                            RA4PPS = 0x1E;
                        break;
                        case 5:
                            RA5PPS = 0x1E;
                        break;
                        case 6:
                            RA6PPS = 0x1E;
                        break;
                        case 7:
                            RA7PPS = 0x1E;
                        break;
                    }
                break;

                case 1:
                    switch(pin){
                        case 0:
                            RB0PPS = 0x1E;
                        break;
                        case 1:
                            RB1PPS = 0x1E;
                        break;
                        case 2:
                            RB2PPS = 0x1E;
                        break;
                        case 3:
                            RB3PPS = 0x1E;
                        break;
                        case 4:
                            RB4PPS = 0x1E;
                        break;
                        case 5:
                            RB5PPS = 0x1E;
                        break;
                        case 6:
                            RB6PPS = 0x1E;
                        break;
                        case 7:
                            RB7PPS = 0x1E;
                        break;
                    }
                break;

                case 2:
                    switch(pin){
                        case 0:
                            RC0PPS = 0x1E;
                        break;
                        case 1:
                            RC1PPS = 0x1E;
                        break;
                        case 2:
                            RC2PPS = 0x1E;
                        break;
                        case 3:
                            RC3PPS = 0x1E;
                        break;
                        case 4:
                            RC4PPS = 0x1E;
                        break;
                        case 5:
                            RC5PPS = 0x1E;
                        break;
                        case 6:
                            RC6PPS = 0x1E;
                        break;
                        case 7:
                            RC7PPS = 0x1E;
                        break;
                    }
                break;
                case 3:
                    switch(pin){
                        case 0:
                            RD0PPS = 0x1E;
                        break;
                        case 1:
                            RD1PPS = 0x1E;
                        break;
                        case 2:
                            RD2PPS = 0x1E;
                        break;
                        case 3:
                            RD3PPS = 0x1E;
                        break;
                        case 4:
                            RD4PPS = 0x1E;
                        break;
                        case 5:
                            RD5PPS = 0x1E;
                        break;
                        case 6:
                            RD6PPS = 0x1E;
                        break;
                        case 7:
                            RD7PPS = 0x1E;
                        break;
                    }
                break;
            }

            RB1PPS = 0x1D; // RB1 SCL2
            SSP2DATPPS = 0x0A;//(((map->pins.mosi >> 4) * 8) + (map->pins.mosi & 0x0F));
            
            
            PPSLOCK = 0x55;
            PPSLOCK = 0xAA;
            PPSLOCKbits.PPSLOCKED = 1; 
        break;
        #endif
       // #endif
    }

    

    return HAL_LL_PPS_SUCCESS;
}

static void hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    switch (map->module_index + 1) {
        #ifdef SPI_MODULE
        #ifdef HAL_LL_PMD_SPI1_ADDRESS
        case SPI_MODULE:
            if(hal_ll_state) {
                //clear_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
                
            } else {
                
                //set_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            }
            break;
        #endif
        #endif

        #ifdef SPI_MODULE_1
        #ifdef HAL_LL_PMD_SPI1_ADDRESS
        case SPI_MODULE_1:
            if(hal_ll_state) {
                PMD3bits.MSSP1MD = 0;
                //clear_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            } else {
                PMD3bits.MSSP1MD = 1;
                //set_reg_bit(HAL_LL_PMD_SPI1_ADDRESS, HAL_LL_SSP1_MODULE_BIT);
            }
            break;
        #endif
        #endif

        #ifdef SPI_MODULE_2
        #ifdef HAL_LL_PMD_SPI2_ADDRESS
        case SPI_MODULE_2:
            if(hal_ll_state) {
                PMD3bits.MSSP2MD = 0;
                //clear_reg_bit(HAL_LL_PMD_SPI2_ADDRESS, HAL_LL_SSP2_MODULE_BIT);
            } else {
                PMD3bits.MSSP2MD = 1;
                //set_reg_bit(HAL_LL_PMD_SPI2_ADDRESS, HAL_LL_SSP2_MODULE_BIT);
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
    
     OSCCON1 = (0 << _OSCCON1_NDIV_POSN)   // NDIV 1
        | (6 << _OSCCON1_NOSC_POSN);  // NOSC HFINTOSC
    OSCCON3 = (0 << _OSCCON3_SOSCPWR_POSN)   // SOSCPWR Low power
        | (0 << _OSCCON3_CSWHOLD_POSN);  // CSWHOLD may proceed
    OSCEN = (0 << _OSCEN_EXTOEN_POSN)   // EXTOEN disabled
        | (0 << _OSCEN_HFOEN_POSN)   // HFOEN disabled
        | (0 << _OSCEN_MFOEN_POSN)   // MFOEN disabled
        | (0 << _OSCEN_LFOEN_POSN)   // LFOEN disabled
        | (0 << _OSCEN_ADOEN_POSN)   // ADOEN disabled
        | (0 << _OSCEN_PLLEN_POSN);  // PLLEN disabled
    OSCFRQ = (6 << _OSCFRQ_FRQ_POSN);  // FRQ 32_MHz
    OSCTUNE = (0 << _OSCTUNE_TUN_POSN);  // TUN 0x0
    ACTCON = (0 << _ACTCON_ACTEN_POSN)   // ACTEN disabled
        | (0 << _ACTCON_ACTUD_POSN)   // ACTUD enabled
        | (0 << _ACTCON_ACTLOCK_POSN)   // ACTLOCK Not locked
        | (0 << _ACTCON_ACTORS_POSN);  // ACTORS In range

    uint8_t port = map->pins.mosi >> 4;
    uint8_t pin = map->pins.mosi & 0x0F;

    /*TRISCbits.TRISC3 = 0;   //SCL1
    TRISCbits.TRISC4 = 1;  //SDI1
    TRISEbits.TRISE0 = 0;  //SS1
    TRISCbits.TRISC5 = 0; //SDO1
    
    ANSELCbits.ANSELC3 = 0;
    ANSELCbits.ANSELC4 = 0;
    ANSELEbits.ANSELE0 = 0;
    ANSELCbits.ANSELC5 = 0;
    
    LATEbits.LATE0 = 1;  

    PPSLOCK = 0x55;  // PPS lock sequence
    PPSLOCK = 0xAA;    
    PPSLOCKbits.PPSLOCKED = 0;
   
    RC3PPS = 0x1B; // RC3 SCL1
    RC5PPS = 0x1C;  // RC5 SDO1
    SSP1DATPPS = 0x14; // RC4 = SDI1
    
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 1;  

    SSP1ADD = 0x4F; // 100kHz
    SSP1MSK = 0x00;
    SSP1STATbits.SMP = 1; 
    SSP1STATbits.CKE = 1;
    SSP1CON1bits.CKP = 0;
    
    SSP1CON1bits.SSPM = 0b0000;
    SSP1CON1bits.SSPEN = 1; // enable*/
    
    switch (map->module_index + 1) {
        #ifdef SPI_MODULE
        //#ifdef HAL_LL_PMD_SPI1_ADDRESS
        case SPI_MODULE:
            
            break;
        #endif
        //#endif

        #ifdef SPI_MODULE_1
        //#ifdef HAL_LL_PMD_SPI1_ADDRESS
        case SPI_MODULE_1:
            TRISCbits.TRISC3 = 0;   //SCL1
            TRISCbits.TRISC4 = 1;  //SDI1
            TRISEbits.TRISE0 = 0;  //SS1
            ANSELEbits.ANSELE0 = 0;
            
            switch(port){  // Setting SDO because it can be any GPIO pin
                case 0:
                    switch(pin){
                        case 0:
                            TRISAbits.TRISA0 = 0;
                            ANSELAbits.ANSELA0 = 0;
                        break;
                        case 1:
                            TRISAbits.TRISA1 = 0;
                            ANSELAbits.ANSELA1 = 0;
                        break;
                        case 2:
                            TRISAbits.TRISA2 = 0;
                            ANSELAbits.ANSELA2 = 0;
                        break;
                        case 3:
                            TRISAbits.TRISA3 = 0;
                            ANSELAbits.ANSELA3 = 0;
                        break;
                        case 4:
                            TRISAbits.TRISA4 = 0;
                            ANSELAbits.ANSELA4 = 0;
                        break;
                        case 5:
                            TRISAbits.TRISA5 = 0;
                            ANSELAbits.ANSELA5 = 0;
                        break;
                        case 6:
                            TRISAbits.TRISA6 = 0;
                            //ANSELAbits.ANSELA6 = 0;
                        break;
                        case 7:
                            TRISAbits.TRISA7 = 0;
                            //ANSELAbits.ANSELA7 = 0;
                        break;
                    }
                break;

                case 1:
                    switch(pin){
                        case 0:
                            TRISBbits.TRISB0 = 0;
                            ANSELBbits.ANSELB0 = 0;
                        break;
                        case 1:
                            TRISBbits.TRISB1 = 0;
                            ANSELBbits.ANSELB1 = 0;
                        break;
                        case 2:
                            TRISBbits.TRISB2 = 0;
                            ANSELBbits.ANSELB2 = 0;
                        break;
                        case 3:
                            TRISBbits.TRISB3 = 0;
                            ANSELBbits.ANSELB3 = 0;
                        break;
                        case 4:
                            TRISBbits.TRISB4 = 0;
                            ANSELBbits.ANSELB4 = 0;
                        break;
                        case 5:
                            TRISBbits.TRISB5 = 0;
                            ANSELBbits.ANSELB5 = 0;
                        break;
                        case 6:
                            TRISBbits.TRISB6 = 0;
                            ANSELBbits.ANSELB6 = 0;
                        break;
                        case 7:
                            TRISBbits.TRISB7 = 0;
                            ANSELBbits.ANSELB7 = 0;
                        break;
                    }
                break;

                case 2:
                    switch(pin){
                        case 0:
                            TRISCbits.TRISC0 = 0;
                            ANSELCbits.ANSELC0 = 0;
                        break;
                        case 1:
                            TRISCbits.TRISC1 = 0;
                            ANSELCbits.ANSELC1 = 0;
                        break;
                        case 2:
                            TRISCbits.TRISC2 = 0;
                            ANSELCbits.ANSELC2 = 0;
                        break;
                        case 3:
                            TRISCbits.TRISC3 = 0;
                            ANSELCbits.ANSELC3 = 0;
                        break;
                        case 4:
                            TRISCbits.TRISC4 = 0;
                            ANSELCbits.ANSELC4 = 0;
                        break;
                        case 5:
                            TRISCbits.TRISC5 = 0;
                            ANSELCbits.ANSELC5 = 0;
                        break;
                        case 6:
                            TRISCbits.TRISC6 = 0;
                            ANSELCbits.ANSELC6 = 0;
                        break;
                        case 7:
                            TRISCbits.TRISC7 = 0;
                            ANSELCbits.ANSELC7 = 0;
                        break;
                    }
                break;
                case 3:
                    switch(pin){
                        case 0:
                            TRISDbits.TRISD0 = 0;
                            ANSELDbits.ANSELD0 = 0;
                        break;
                        case 1:
                            TRISDbits.TRISD1 = 0;
                            ANSELDbits.ANSELD1 = 0;
                        break;
                        case 2:
                            TRISDbits.TRISD2 = 0;
                            ANSELDbits.ANSELD2 = 0;
                        break;
                        case 3:
                            TRISDbits.TRISD3 = 0;
                            ANSELDbits.ANSELD3 = 0;
                        break;
                        case 4:
                            TRISDbits.TRISD4 = 0;
                            ANSELDbits.ANSELD4 = 0;
                        break;
                        case 5:
                            TRISDbits.TRISD5 = 0;
                            ANSELDbits.ANSELD5 = 0;
                        break;
                        case 6:
                            TRISDbits.TRISD6 = 0;
                            ANSELDbits.ANSELD6 = 0;
                        break;
                        case 7:
                            TRISDbits.TRISD7 = 0;
                            ANSELDbits.ANSELD7 = 0;
                        break;
                    }
                break;
            }
            //TRISCbits.TRISC5 = 0; //SDO1
            ANSELCbits.ANSELC3 = 0;
            ANSELCbits.ANSELC4 = 0;
            ANSELEbits.ANSELE0 = 0;
            ANSELCbits.ANSELC5 = 0;

            //SSP1ADD = map->speed;
            SSP1MSK = 0x00;

            uint32_t freq = Get_Fosc_kHz();
            freq = 32000; // HARDCODE
            
            switch(map->speed){
                case 100000:
                    if(freq == 32000)
                        SSP1ADD = 0x4F; // 100kHz
                    else if(freq == 16000)
                        SSP1ADD = 0x27;
                    else if(freq == 4000){
                        SSP1ADD = 0x09;
                    }
                break;
                case 400000:
                    if(freq == 32000)
                        SSP1ADD = 0x13; // 400kHz
                    else if(freq == 16000)
                        SSP1ADD = 0x09;

                break;
            }

            switch(map->mode){
                case 0:
                    SSP1STATbits.CKE = 1;
                    SSP1CON1bits.CKP = 0;
                break;

                case 1:
                    SSP1CON1bits.CKP = 0;
                    SSP1STATbits.CKE = 0;
                break;

                case 2:
                    SSP1CON1bits.CKP = 1;
                    SSP1STATbits.CKE = 1;
                break;

                case 3:
                    SSP1CON1bits.CKP = 1;
                    SSP1STATbits.CKE = 0;
                break;
            }
            SSP1STATbits.SMP = 1; 
            
            SSP1CON1bits.SSPM = 0b0000;
            SSP1CON1bits.SSPEN = 1; // enable
            break;
        #endif
       // #endif

        #ifdef SPI_MODULE_2
       // #ifdef HAL_LL_PMD_SPI2_ADDRESS
        case SPI_MODULE_2:
            
            TRISB2 = 1;
            TRISB1 = 0;


            switch(port){  // Setting SDO because it can be any GPIO pin
                case 0:
                    switch(pin){
                        case 0:
                            TRISAbits.TRISA0 = 0;
                        break;
                        case 1:
                            TRISAbits.TRISA1 = 0;
                        break;
                        case 2:
                            TRISAbits.TRISA2 = 0;
                        break;
                        case 3:
                            TRISAbits.TRISA3 = 0;
                        break;
                        case 4:
                            TRISAbits.TRISA4 = 0;
                        break;
                        case 5:
                            TRISAbits.TRISA5 = 0;
                        break;
                        case 6:
                            TRISAbits.TRISA6 = 0;
                        break;
                        case 7:
                            TRISAbits.TRISA7 = 0;
                        break;
                    }
                break;

                case 1:
                    switch(pin){
                        case 0:
                            TRISBbits.TRISB0 = 0;
                        break;
                        case 1:
                            TRISBbits.TRISB1 = 0;
                        break;
                        case 2:
                            TRISBbits.TRISB2 = 0;
                        break;
                        case 3:
                            TRISBbits.TRISB3 = 0;
                        break;
                        case 4:
                            TRISBbits.TRISB4 = 0;
                        break;
                        case 5:
                            TRISBbits.TRISB5 = 0;
                        break;
                        case 6:
                            TRISBbits.TRISB6 = 0;
                        break;
                        case 7:
                            TRISBbits.TRISB7 = 0;
                        break;
                    }
                break;

                case 2:
                    switch(pin){
                        case 0:
                            TRISCbits.TRISC0 = 0;
                        break;
                        case 1:
                            TRISCbits.TRISC1 = 0;
                        break;
                        case 2:
                            TRISCbits.TRISC2 = 0;
                        break;
                        case 3:
                            TRISCbits.TRISC3 = 0;
                        break;
                        case 4:
                            TRISCbits.TRISC4 = 0;
                        break;
                        case 5:
                            TRISCbits.TRISC5 = 0;
                        break;
                        case 6:
                            TRISCbits.TRISC6 = 0;
                        break;
                        case 7:
                            TRISCbits.TRISC7 = 0;
                        break;
                    }
                break;
                case 3:
                    switch(pin){
                        case 0:
                            TRISDbits.TRISD0 = 0;
                        break;
                        case 1:
                            TRISDbits.TRISD1 = 0;
                        break;
                        case 2:
                            TRISDbits.TRISD2 = 0;
                        break;
                        case 3:
                            TRISDbits.TRISD3 = 0;
                        break;
                        case 4:
                            TRISDbits.TRISD4 = 0;
                        break;
                        case 5:
                            TRISDbits.TRISD5 = 0;
                        break;
                        case 6:
                            TRISDbits.TRISD6 = 0;
                        break;
                        case 7:
                            TRISDbits.TRISD7 = 0;
                        break;
                    }
                break;
            }

            
            SSP2MSK = 0x00;
            freq = Get_Fosc_kHz();
            freq = 32000; // HARDCODE
            
            switch(map->speed){
                case 100000:
                    if(freq == 32000)
                        SSP2ADD = 0x4F; // 100kHz
                    else if(freq == 16000)
                        SSP2ADD = 0x27;
                    else if(freq == 4000){
                        SSP2ADD = 0x09;
                    }
                break;
                case 400000:
                    if(freq == 32000)
                        SSP2ADD = 0x13; // 400kHz
                    else if(freq == 16000)
                        SSP2ADD = 0x09;

                break;
            }
            SSP2STATbits.SMP = 1; 
            switch(map->mode){
                case 0:
                    SSP2STATbits.CKE = 1;
                    SSP2CON1bits.CKP = 0;
                break;

                case 1:
                    SSP2CON1bits.CKP = 0;
                    SSP2STATbits.CKE = 0;
                break;

                case 2:
                    SSP2CON1bits.CKP = 1;
                    SSP2STATbits.CKE = 1;
                break;

                case 3:
                    SSP2CON1bits.CKP = 1;
                    SSP2STATbits.CKE = 0;
                break;
            }
            
            SSP2CON1bits.SSPM = 0b0000;
            SSP2CON1bits.SSPEN = 1; // enable


            break;
        #endif
       // #endif
    }
    
    
    
    


}

static void hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map) {

   
    hal_ll_spi_master_hw_init(map);
}
// ------------------------------------------------------------------------- END