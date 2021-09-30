/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

#include "hal_ll_spi_master.h"
#include "hal_ll_spi_master_pin_map.h"
#include "hal_ll_rcc.h"

/*!< @brief Local handle list */
static volatile hal_ll_spi_master_handle_register_t hal_ll_module_state[SPI_MODULE_COUNT] = {(handle_t *)NULL, (handle_t *)NULL, false};

// Defines constant value arrays for the baud rate pre-scalar and scalar divider values
static const uint32_t baudrate_prescaler[] = { 2, 3, 5, 7 };
static const uint32_t baudrate_scaler[] = { 2, 4, 6, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768 };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_spi_master_get_module_state_address            ((hal_ll_spi_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_spi_master_get_handle                          (hal_ll_spi_master_handle_register_t *)hal_ll_spi_master_get_module_state_address->hal_ll_spi_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_spi_master_get_base_struct(_handle)            ((hal_ll_spi_master_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_spi_master_get_base_from_hal_handle            ((hal_ll_spi_master_hw_specifics_map_t *)((hal_ll_spi_master_handle_register_t *)\
                                                              (((hal_ll_spi_master_handle_register_t *)(handle))->hal_ll_spi_master_handle))->hal_ll_spi_master_handle)->base

/*!< Enable constants. */
#define HAL_LL_SPI0_MASTER_ENABLE               12
#define HAL_LL_SPI1_MASTER_ENABLE               13
#define HAL_LL_SPI2_MASTER_ENABLE               12

#define MIN_DIFF                                0xFFFFFFFFUL

/*!< @brief Default SPI Master bit-rate if no speed is set */
#define HAL_LL_SPI_MASTER_SPEED_100K            100000

/*!< @brief Macros used for module pin checking */
#define HAL_LL_SPI_SCK_PIN                      0
#define HAL_LL_SPI_MISO_PIN                     1
#define HAL_LL_SPI_MOSI_PIN                     2
#define HAL_LL_SPI_MODULE_PIN_COUNT             3

#define SPI_MASTER_CFG_CMD_CTCNT_CLEAR          0x04000000

#define SPI_MASTER_CTAR_BR_MASK                 0xF
#define SPI_MASTER_CTAR_BR_3BITS_MASK           0x7
#define SPI_MASTER_CTAR_BR_SHIFT                0
#define SPI_MASTER_CTAR_PBR_MASK                0x30000UL
#define SPI_MASTER_CTAR_PBR_SHIFT               16
#define SPI_MASTER_CTAR_DBR_MASK                0x80000000UL
#define SPI_MASTER_CTAR_DBR_SHIFT               31
#define SPI_MASTER_CTAR_DEFAULT                 0x78000000UL

#define SPI_MASTER_MCR_CLR_RXF_MASK             0x400UL
#define SPI_MASTER_MCR_CLR_TXF_MASK             0x800UL

#define SPI_MASTER_MCR_HALT_SHIFT               0
#define SPI_MASTER_MCR_CLR_RXF_SHIFT            10
#define SPI_MASTER_MCR_CLR_TXF_SHIFT            11
#define SPI_MASTER_MCR_DIS_RXF_SHIFT            12
#define SPI_MASTER_MCR_DIS_TXF_SHIFT            13
#define SPI_MASTER_MCR_MDIS_SHIFT               14
#define SPI_MASTER_MCR_MSTR_SHIFT               31

#define SPI_MASTER_SR_RFDF_MASK                 0x20000UL
#define SPI_MASTER_SR_RFOF_MASK                 0x80000UL
#define SPI_MASTER_SR_TFFF_MASK                 0x2000000UL
#define SPI_MASTER_SR_TFUF_MASK                 0x8000000UL
#define SPI_MASTER_SR_EOQF_MASK                 0x10000000UL
#define SPI_MASTER_SR_TCF_MASK                  0x80000000UL
#define SPI_MASTER_SR_TCF_SHIFT                 31
#define SPI_MASTER_SR_RFDF_SHIFT                17

#define SPI_MASTER_CTAR0_LSBFE_SHIFT            24
#define SPI_MASTER_CTAR0_FMSZ_4BIT_SHIFT        30
#define SPI_MASTER_CTAR0_FMSZ_3BITS_MASK        0x38000000UL

#define SPI_MASTER_RSER_TCF_RE_BIT              31
#define SPI_MASTER_RSER_TCF_RE_MASK             (1UL << SPI_MASTER_RSER_TCF_RE_BIT)
#define SPI_MASTER_RSER_EOQF_RE_BIT             28
#define SPI_MASTER_RSER_EOQF_RE_MASK            (1UL << SPI_MASTER_RSER_EOQF_RE_BIT)
#define SPI_MASTER_RSER_TFUF_RE_BIT             27
#define SPI_MASTER_RSER_TFUF_RE_MASK            (1UL << SPI_MASTER_RSER_TFUF_RE_BIT)
#define SPI_MASTER_RSER_TFFF_RE_BIT             25
#define SPI_MASTER_RSER_TFFF_RE_MASK            (1UL << SPI_MASTER_RSER_TFFF_RE_BIT)
#define SPI_MASTER_RSER_TFFF_DIRS_BIT           24
#define SPI_MASTER_RSER_TFFF_DIRS_MASK          (1UL << SPI_MASTER_RSER_TFFF_DIRS_BIT)
#define SPI_MASTER_RSER_RFOF_RE_BIT             19
#define SPI_MASTER_RSER_RFOF_RE_MASK            (1UL << SPI_MASTER_RSER_RFOF_RE_BIT)
#define SPI_MASTER_RSER_RFDF_RE_BIT             17
#define SPI_MASTER_RSER_RFDF_RE_MASK            (1UL << SPI_MASTER_RSER_RFDF_RE_BIT)
#define SPI_MASTER_RSER_RFDF_DIRS_BIT           16
#define SPI_MASTER_RSER_RFDF_DIRS_MASK          (1UL << SPI_MASTER_RSER_RFDF_DIRS_BIT)
#define SPI_MASTER_RSER_FULL_MASK               (SPI_MASTER_RSER_TCF_RE_MASK | \
                                                 SPI_MASTER_RSER_EOQF_RE_MASK | \
                                                 SPI_MASTER_RSER_TFUF_RE_MASK | \
                                                 SPI_MASTER_RSER_TFFF_RE_MASK | \
                                                 SPI_MASTER_RSER_TFFF_DIRS_MASK | \
                                                 SPI_MASTER_RSER_RFOF_RE_MASK | \
                                                 SPI_MASTER_RSER_RFDF_RE_MASK | \
                                                 SPI_MASTER_RSER_RFDF_DIRS_MASK)

#define SPI_MASTER_TCR_TCNT_MASK                0x0000FFFFUL

#define HAL_LL_SPI_MASTER_CLK_POLARITY          26
#define HAL_LL_SPI_MASTER_CLK_PHASE             25

// -------------------------------------------------------------- PRIVATE TYPES
typedef struct {
    uint32_t mcr;                               /**< Module Configuration Register, offset: 0x0 */
    uint32_t __unused1;
    uint32_t tcr;                               /**< Transfer Count Register, offset: 0x8 */
    uint32_t ctar0;                             /**< Clock and Transfer Attributes Register (In Master Mode), array offset: 0xC */
    uint32_t ctar1;                             /**< Clock and Transfer Attributes Register (In Master Mode), array offset: 0x10 */
    uint32_t __unused2[ 6 ];
    uint32_t sr;                                /**< Status Register, offset: 0x2C */
    uint32_t rser;                              /**< DMA/Interrupt Request Select and Enable Register, offset: 0x30 */
    uint32_t pushr;                             /**< PUSH TX FIFO Register In Master Mode, offset: 0x34 */
    uint32_t popr;                              /**< POP RX FIFO Register, offset: 0x38 */
    /* Commented out for memory optimization;
     * Uncomment if needed.
     */
    // uint32_t txfr0;                          /**< Transmit FIFO Registers, offset: 0x3C */
    // uint32_t txfr1;                          /**< Transmit FIFO Registers, offset: 0x40 */
    // uint32_t txfr2;                          /**< Transmit FIFO Registers, offset: 0x44 */
    // uint32_t txfr3;                          /**< Transmit FIFO Registers, offset: 0x48 */
    // uint32_t __unused3[12];
    // uint32_t rxfr0;                          /**< Receive FIFO Registers, offset: 0x7C */
    // uint32_t rxfr1;                          /**< Receive FIFO Registers, offset: 0x80 */
    // uint32_t rxfr2;                          /**< Receive FIFO Registers, offset: 0x84 */
    // uint32_t rxfr3;                          /**< Receive FIFO Registers, offset: 0x88 */
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
typedef struct
{
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

// ------------------------------------------------------------------ VARIABLES
/*!< @brief SPI Master hardware specific info */
static hal_ll_spi_master_hw_specifics_map_t hal_ll_spi_master_hw_specifics_map[SPI_MODULE_COUNT + 1] = {
    #ifdef SPI_MODULE_0
    {HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif
    #ifdef SPI_MODULE_1
    {HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif
    #ifdef SPI_MODULE_2
    {HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, HAL_LL_SPI_MASTER_SPEED_100K, 0, HAL_LL_SPI_MASTER_MODE_DEFAULT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, {HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0, HAL_LL_PIN_NC, 0}, 0, 0, 0, 0}
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
  * @param[in]  sck  - SCK pre-defined pin name.
  * @param[in]  miso - MISO pre-defined pin name.
  * @param[in]  mosi - MOSI pre-defined pin name.
  * @param[in]  *index_list - Index list address
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t _hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map);

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
  */
static void _hal_ll_spi_master_alternate_functions_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * SPI SCK, MISO and MOSI pins.
 *
 * @param[in]  module_index SPI HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCK, MISO and MOSI map index values
 *
 * @return  None
 */
static void _hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_pin_id *index_list);

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
static hal_ll_spi_master_hw_specifics_map_t *_hal_ll_get_specifics(handle_t handle);

/**
  * @brief  Set CTAR register.
  *
  * Calculate Baud Rate Prescaler, Baud Rate Scaler, Double Baud Rate
  *
  * @param[in]  *map - Object specific context handler.
  */
static void _hal_ll_spi_master_get_speed(hal_ll_spi_master_hw_specifics_map_t *map);

/**
  * @brief  Perform a write on the SPI Master bus.
  *
  * Initializes SPI Master module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  map - Object specific context handler.
  * @param[in]  *write_data_buffer - Pointer to data buffer.
  * @param[in]  write_data_length - Number of data to be written.
  * @return hal_ll_err_t Module specific error values.
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */
static void _hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *write_data_buffer, size_t write_data_length);

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
  */
static void _hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data);

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
static void _hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state);

/**
  * @brief  Initialize hardware SPI module.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined error values.
  * Take into consideration that this is hardware specific.
  */

static void _hal_ll_spi_master_hw_init(hal_ll_spi_master_hw_specifics_map_t *map);

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

static void _hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_spi_master_register_handle(hal_ll_pin_name_t sck, hal_ll_pin_name_t miso, hal_ll_pin_name_t mosi, hal_ll_spi_master_handle_register_t *handle_map, uint8_t *hal_module_id) {
    hal_ll_spi_pin_id index_list[SPI_MODULE_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    uint16_t pin_check_result;

    // Check user-defined pins.
    if ((pin_check_result = _hal_ll_spi_master_check_pins(sck, miso, mosi, &index_list, handle_map)) == HAL_LL_PIN_NC) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    // If user has come with the same SPI hardware module, and with the same pair of the pins, the pin mapping procedure
    // will not have to take a place; otherwise, clear af-s, map new pins, set af-s, and set init state to false.
    if ((hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.sck.pin_name != sck) ||
        (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.miso.pin_name != miso) ||
        (hal_ll_spi_master_hw_specifics_map[pin_check_result].pins.mosi.pin_name != mosi) ) {

        _hal_ll_spi_master_alternate_functions_set_state(&hal_ll_spi_master_hw_specifics_map[pin_check_result], false);

        _hal_ll_spi_master_map_pins(pin_check_result, &index_list);

        _hal_ll_spi_master_alternate_functions_set_state(&hal_ll_spi_master_hw_specifics_map[pin_check_result], true);

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
    hal_ll_spi_pin_id index_list[HAL_LL_SPI_MODULE_PIN_COUNT] = {HAL_LL_PIN_NC,HAL_LL_PIN_NC,HAL_LL_PIN_NC};
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);
    uint8_t pin_check_result;

    if ((pin_check_result = _hal_ll_spi_master_check_pins(hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_name,
                                                          hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_name,
                                                          hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_name,
                                                          &index_list,
                                                          (void *)0)) == HAL_LL_PIN_NC) {
        return HAL_LL_SPI_MASTER_WRONG_PINS;
    };

    _hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    hal_ll_module_state[pin_check_result].hal_ll_spi_master_handle = (handle_t *)&hal_ll_spi_master_hw_specifics_map[pin_check_result].base;
    hal_ll_module_state[pin_check_result].init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_set_default_write_data(handle_t *handle, uint8_t dummy_data) {
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(hal_ll_spi_master_hw_specifics_map_local->base != HAL_LL_MODULE_ERROR) {
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = dummy_data;
    }
}

hal_ll_err_t hal_ll_spi_master_write(handle_t *handle, uint8_t *write_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    // Check for module error.
    if(low_level_handle->hal_ll_spi_master_handle == NULL) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    _hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_read(handle_t *handle, uint8_t *read_data_buffer, size_t length_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle == NULL) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    _hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_spi_master_write_then_read(handle_t *handle, uint8_t *write_data_buffer, size_t length_write_data, uint8_t *read_data_buffer, size_t length_read_data) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle == NULL) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    _hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_local, write_data_buffer, length_write_data);

    _hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_local, read_data_buffer, length_read_data, hal_ll_spi_master_hw_specifics_map_local->dummy_data);

    return HAL_LL_SPI_MASTER_SUCCESS;
}

uint32_t hal_ll_spi_master_set_speed(handle_t *handle, uint32_t speed) {
   // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle == NULL) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    // Insert user-defined baud rate into local map.
    hal_ll_spi_master_hw_specifics_map_local->speed = speed;

    // Init once again, but with updated SPI Master baud rate value.
    _hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    // Return value of the SPI Master baud rate value.
    return hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed;
}

hal_ll_err_t hal_ll_spi_master_set_mode(handle_t *handle, hal_ll_spi_master_mode_t mode) {
    // Get low level HAL handle.
    low_level_handle = hal_ll_spi_master_get_handle;
    // Get appropriate hw specifics map.
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle == NULL) {
        return HAL_LL_SPI_MASTER_MODULE_ERROR;
    }

    low_level_handle->init_ll_state = false;

    // Insert user-defined mode into local map.
    hal_ll_spi_master_hw_specifics_map_local->mode = mode;

    // Init once again, but with updated SPI Master mode value.
    _hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_local);

    low_level_handle->init_ll_state = true;

    return HAL_LL_SPI_MASTER_SUCCESS;
}

void hal_ll_spi_master_close(handle_t* handle) {
    uint32_t dummy;
    low_level_handle = hal_ll_spi_master_get_handle;
    hal_ll_spi_master_hw_specifics_map_local = _hal_ll_get_specifics(hal_ll_spi_master_get_module_state_address);

    if(low_level_handle->hal_ll_spi_master_handle != NULL) {
        low_level_handle->hal_ll_spi_master_handle = NULL;
        low_level_handle->hal_drv_spi_master_handle = NULL;

        low_level_handle->init_ll_state = false;

        hal_ll_spi_master_hw_specifics_map_local->mode = HAL_LL_SPI_MASTER_MODE_DEFAULT;
        hal_ll_spi_master_hw_specifics_map_local->speed = HAL_LL_SPI_MASTER_SPEED_100K;
        hal_ll_spi_master_hw_specifics_map_local->dummy_data = 0;
        hal_ll_spi_master_hw_specifics_map_local->hw_actual_speed = 0;

        _hal_ll_spi_master_alternate_functions_set_state(hal_ll_spi_master_hw_specifics_map_local, false);
        _hal_ll_spi_master_set_clock(hal_ll_spi_master_hw_specifics_map_local, false);

        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_name = HAL_LL_PIN_NC;
        hal_ll_spi_master_hw_specifics_map_local->pins.sck.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.miso.pin_af = 0;
        hal_ll_spi_master_hw_specifics_map_local->pins.mosi.pin_af = 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_pin_name_t _hal_ll_spi_master_check_pins(hal_ll_pin_name_t sck_pin, hal_ll_pin_name_t miso_pin, hal_ll_pin_name_t mosi_pin, hal_ll_spi_pin_id *index_list, hal_ll_spi_master_handle_register_t *handle_map) {
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

static void _hal_ll_spi_master_alternate_functions_set_state(hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state) {
    module_struct module;
    uint32_t spi_config;

    if((map->pins.sck.pin_name != HAL_LL_PIN_NC) && (map->pins.miso.pin_name != HAL_LL_PIN_NC) && (map->pins.miso.pin_name != HAL_LL_PIN_NC)) {
        module.pins[0] = VALUE(map->pins.sck.pin_name, map->pins.sck.pin_af);
        module.pins[1] = VALUE(map->pins.miso.pin_name, map->pins.miso.pin_af);
        module.pins[2] = VALUE(map->pins.mosi.pin_name, map->pins.mosi.pin_af);
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        spi_config = GPIO_CFG_MODE_ALT_FUNCTION;

        module.configs[0] = spi_config;
        module.configs[1] = spi_config;
        module.configs[2] = spi_config;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init(&module, hal_ll_state);
    }
}

static void _hal_ll_spi_master_map_pins(uint8_t module_index, hal_ll_spi_pin_id *index_list) {

    // if every single pin is OK, insert them into this new map, and use this map in all low level functions.
    hal_ll_spi_master_hw_specifics_map[module_index]->pins.sck.pin_name  = _spi_sck_map[index_list[module_index]->pin_sck].pin;
    hal_ll_spi_master_hw_specifics_map[module_index]->pins.miso.pin_name = _spi_miso_map[index_list[module_index]->pin_miso].pin;
    hal_ll_spi_master_hw_specifics_map[module_index]->pins.mosi.pin_name = _spi_mosi_map[index_list[module_index]->pin_mosi].pin;

    // SCK, MISO and MOSI pins could have different alternate function settings, hence save all the AF-s.
    hal_ll_spi_master_hw_specifics_map[module_index]->pins.sck.pin_af   = _spi_sck_map[index_list[module_index]->pin_sck].af;
    hal_ll_spi_master_hw_specifics_map[module_index]->pins.miso.pin_af  = _spi_miso_map[index_list[module_index]->pin_miso].af;
    hal_ll_spi_master_hw_specifics_map[module_index]->pins.mosi.pin_af  = _spi_mosi_map[index_list[module_index]->pin_mosi].af;

}

static hal_ll_spi_master_hw_specifics_map_t *_hal_ll_get_specifics(handle_t handle) {
    uint8_t hal_ll_module_count = sizeof(hal_ll_module_state) / (sizeof( hal_ll_spi_master_handle_register_t));

    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while (hal_ll_module_count--) {
        if (hal_ll_spi_master_get_base_from_hal_handle == hal_ll_spi_master_hw_specifics_map[hal_ll_module_count].base) {
            return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_count];
        }
    }

    return &hal_ll_spi_master_hw_specifics_map[hal_ll_module_error];
}

static void _hal_ll_spi_master_get_speed(hal_ll_spi_master_hw_specifics_map_t *map){
    SIM_ClocksTypeDef sim_clocks;
    uint32_t prescaler, best_prescaler;
    uint32_t scaler, best_scaler;
    uint32_t dbr, best_dbr;
    uint32_t real_baudrate, best_baudrate;
    uint32_t diff, min_diff;
    uint32_t baudrate_prescaler_size, baudrate_scaler_size;

    uint32_t baudrate = map->speed;

    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;

    // Get clocks - source clock for dspi is bus clock.
    SIM_GetClocksFrequency(&sim_clocks);

    // Find combination of prescaler and scaler resulting in baudrate closest to the requested value.
    min_diff = MIN_DIFF;
    best_prescaler = 0;
    best_scaler = 0;
    best_dbr = 1;
    best_baudrate = 0;

    baudrate_prescaler_size = sizeof(baudrate_prescaler)/sizeof(uint32_t);
    baudrate_scaler_size = sizeof(baudrate_scaler)/sizeof(uint32_t);

    // In all for loops, if min_diff = 0, the exit for loop.
    for (prescaler = 0; min_diff && (prescaler < baudrate_prescaler_size); prescaler++)
    {
        for (scaler = 0; min_diff && (scaler < baudrate_scaler_size); scaler++)
        {
            for (dbr = 1; min_diff && (dbr < 3); dbr++)
            {
                #ifdef HAL_LL_RCC_CLOCK_OUTPUT
                real_baudrate = (sim_clocks.fast_peripheral_frequency * dbr) /
                                (baudrate_prescaler[prescaler] * (baudrate_scaler[scaler]));
                #else
                real_baudrate = (sim_clocks.busclock_frequency * dbr) /
                                (baudrate_prescaler[prescaler] * (baudrate_scaler[scaler]));
                #endif
                // EOF TODO
                if (baudrate >= real_baudrate)
                {
                    diff = baudrate-real_baudrate;
                    if (min_diff > diff)
                    {
                        min_diff = diff;
                        best_prescaler = prescaler;
                        best_scaler = scaler;
                        best_baudrate = real_baudrate;
                        best_dbr = dbr;
                    }
                }
            }
        }
    }

    // Write the best dbr, prescalar, and baud rate scalar to the CTAR.
    hal_ll_hw_reg->ctar0 &= ~((uint32_t)(SPI_MASTER_CTAR_DBR_MASK | SPI_MASTER_CTAR_PBR_MASK | SPI_MASTER_CTAR_BR_MASK));
    hal_ll_hw_reg->ctar0 |= (best_dbr - 1) << SPI_MASTER_CTAR_DBR_SHIFT;
    hal_ll_hw_reg->ctar0 |= (best_prescaler << SPI_MASTER_CTAR_PBR_SHIFT) & SPI_MASTER_CTAR_PBR_MASK;
    hal_ll_hw_reg->ctar0 |= (best_scaler << SPI_MASTER_CTAR_BR_SHIFT) & SPI_MASTER_CTAR_BR_MASK;

    map->hw_actual_speed = best_baudrate;
}

static void _hal_ll_spi_master_write_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *write_data_buffer, size_t write_data_length){

    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;
    size_t loop_counter = 0;

    /* Clear all interrupts. */
    hal_ll_hw_reg->rser &= ~(SPI_MASTER_RSER_FULL_MASK);

    for (loop_counter = 0; loop_counter < write_data_length; loop_counter++ ){

        /* Flush TXFIFO. */
        hal_ll_hw_reg->mcr |= ( 1UL << SPI_MASTER_MCR_DIS_TXF_SHIFT );

        hal_ll_hw_reg->sr = 1UL << SPI_MASTER_SR_TCF_SHIFT;

        hal_ll_hw_reg->pushr = SPI_MASTER_CFG_CMD_CTCNT_CLEAR |  ((uint32_t) write_data_buffer[loop_counter]);

        while((hal_ll_hw_reg->sr & SPI_MASTER_SR_TCF_MASK) == 0)
        {
        }

        hal_ll_hw_reg->mcr &= ~( 1UL << SPI_MASTER_MCR_DIS_TXF_SHIFT );
    }

}

static void _hal_ll_spi_master_read_bare_metal(hal_ll_spi_master_hw_specifics_map_t *map, uint8_t *read_data_buffer, size_t read_data_length, uint8_t dummy_data){

    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;
    size_t i = 0;

    /* Clear all interrupts. */
    hal_ll_hw_reg->rser &= ~(SPI_MASTER_RSER_FULL_MASK);

    for( i=0; i < read_data_length; i++ ) {
        set_reg_bit(&hal_ll_hw_reg->mcr, SPI_MASTER_MCR_HALT_SHIFT);

        hal_ll_hw_reg->mcr = ( hal_ll_hw_reg->mcr  & ( ~( SPI_MASTER_MCR_CLR_RXF_MASK | SPI_MASTER_MCR_CLR_TXF_MASK ) ) ) |
                             ( 1UL << SPI_MASTER_MCR_CLR_RXF_SHIFT ) | ( 1UL << SPI_MASTER_MCR_CLR_TXF_SHIFT );

        /* Flush RXFIFO. */
        hal_ll_hw_reg->mcr |= ( 1UL << SPI_MASTER_MCR_DIS_RXF_SHIFT );

        clear_reg_bit( &hal_ll_hw_reg->mcr,SPI_MASTER_MCR_HALT_SHIFT );

        hal_ll_hw_reg->sr = SPI_MASTER_SR_TCF_MASK | SPI_MASTER_SR_EOQF_MASK | SPI_MASTER_SR_TFUF_MASK |
                            SPI_MASTER_SR_TFFF_MASK | SPI_MASTER_SR_RFOF_MASK | SPI_MASTER_SR_RFDF_MASK;

        /* Set to 0 always, because one byte is transferred. */
        hal_ll_hw_reg->tcr &= SPI_MASTER_TCR_TCNT_MASK;

        hal_ll_hw_reg->mcr &= ~( 1UL << SPI_MASTER_MCR_DIS_RXF_SHIFT );
        clear_reg_bit( &hal_ll_hw_reg->mcr,SPI_MASTER_MCR_HALT_SHIFT );

        _hal_ll_spi_master_write_bare_metal( map, &dummy_data, sizeof( dummy_data ) );

        // Wait for RFDF to be set.
        while((hal_ll_hw_reg->sr & SPI_MASTER_SR_RFDF_MASK) == 0);

        read_data_buffer[ i ] = (uint8_t)hal_ll_hw_reg->popr;

        hal_ll_hw_reg->sr = 1UL << SPI_MASTER_SR_RFDF_SHIFT;
    }
}

static void _hal_ll_spi_master_set_clock( hal_ll_spi_master_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #if defined( SPI_MODULE_0 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_0 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC6, HAL_LL_SPI0_MASTER_ENABLE );
            } else {
                clear_reg_bit( _SIM_SCGC6, HAL_LL_SPI0_MASTER_ENABLE );
            }
            break;
        #endif
        #if defined( SPI_MODULE_1 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_1 ) ):
            if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC6, HAL_LL_SPI1_MASTER_ENABLE );
            } else {
                clear_reg_bit( _SIM_SCGC6, HAL_LL_SPI1_MASTER_ENABLE );
            }
            break;
        #endif
        #if defined( SPI_MODULE_2 )
        case ( hal_ll_spi_master_module_num( SPI_MODULE_2 ) ):
             if( hal_ll_state ) {
                set_reg_bit( _SIM_SCGC3, HAL_LL_SPI2_MASTER_ENABLE );
            } else {
                clear_reg_bit( _SIM_SCGC3, HAL_LL_SPI2_MASTER_ENABLE );
            }
            break;
        #endif
    }
}

static void _hal_ll_spi_master_hw_init( hal_ll_spi_master_hw_specifics_map_t *map ) {
    hal_ll_spi_master_base_handle_t *hal_ll_hw_reg = (hal_ll_spi_master_base_handle_t *)map->base;

    // First, make sure the module is enabled to allow writes to certain registers.
    clear_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_MDIS_SHIFT);

    // Halt all transfers.
    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_HALT_SHIFT);

    hal_ll_hw_reg->sr = SPI_MASTER_SR_TCF_MASK | SPI_MASTER_SR_EOQF_MASK | SPI_MASTER_SR_TFUF_MASK | SPI_MASTER_SR_TFFF_MASK | SPI_MASTER_SR_RFOF_MASK | SPI_MASTER_SR_RFDF_MASK;

    hal_ll_hw_reg->tcr = 0;
    hal_ll_hw_reg->ctar0 = SPI_MASTER_CTAR_DEFAULT;
    hal_ll_hw_reg->ctar1 = SPI_MASTER_CTAR_DEFAULT;
    hal_ll_hw_reg->rser = 0;
    hal_ll_hw_reg->pushr = 0;

    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_CLR_RXF_SHIFT);
    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_CLR_TXF_SHIFT);

    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_MDIS_SHIFT);
    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_HALT_SHIFT);

    // Set master mode.
    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_MSTR_SHIFT);

    // Disable FIFO.
    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_DIS_RXF_SHIFT);
    set_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_DIS_TXF_SHIFT);

    // Enable spi module.
    clear_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_MDIS_SHIFT);

    hal_ll_hw_reg->ctar0 |= SPI_MASTER_CTAR_BR_3BITS_MASK;

    // Set polarity mode.
    // Choose whether idle state for the clock is high level (1) or low level (0).
    if (map->mode <= HAL_LL_SPI_MASTER_MODE_1) {
        clear_reg_bit(&(hal_ll_hw_reg->ctar0), HAL_LL_SPI_MASTER_CLK_POLARITY);
    } else {
        set_reg_bit(&( hal_ll_hw_reg->ctar0), HAL_LL_SPI_MASTER_CLK_POLARITY);
    }

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0).
    if (map->mode == HAL_LL_SPI_MASTER_MODE_0 || map->mode == HAL_LL_SPI_MASTER_MODE_2) {
        clear_reg_bit(&(hal_ll_hw_reg->ctar0), HAL_LL_SPI_MASTER_CLK_PHASE);
    } else {
        set_reg_bit(&(hal_ll_hw_reg->ctar0), HAL_LL_SPI_MASTER_CLK_PHASE);
    }

    // Set msb/lsb bit to transfer.
    clear_reg_bit(&(hal_ll_hw_reg->ctar0),SPI_MASTER_CTAR0_LSBFE_SHIFT);

    clear_reg_bit(&(hal_ll_hw_reg->ctar0),SPI_MASTER_CTAR0_FMSZ_4BIT_SHIFT);

    hal_ll_hw_reg->ctar0 |= SPI_MASTER_CTAR0_FMSZ_3BITS_MASK;

    _hal_ll_spi_master_get_speed(map);

    // Start transfer.
    clear_reg_bit(&(hal_ll_hw_reg->mcr),SPI_MASTER_MCR_HALT_SHIFT);
}

static void _hal_ll_spi_master_init(hal_ll_spi_master_hw_specifics_map_t *map) {
    // Enable specific alternate functions.
    _hal_ll_spi_master_alternate_functions_set_state(map, true);

    // Enable specific clock module.
    _hal_ll_spi_master_set_clock (map, true);

    // Finally, write user-defined settings into hardware registers.
    _hal_ll_spi_master_hw_init(map);
}
// ------------------------------------------------------------------------- END
