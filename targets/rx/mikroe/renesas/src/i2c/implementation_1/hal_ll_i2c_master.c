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
#include "hal_ll_per.h"
#include "delays.h"
#include <stdbool.h>
#include "mcu.h"
/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting the 2nd SFR area (IICCTLn0/1, IICWLn/H, SVAn) */
#define hal_ll_i2c_get_ctrl_struct(_handle) ((hal_ll_i2c_ctrl_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base
/*!< @brief Helper macro for getting bit rate configuration values */
#define hal_ll_i2c_get_brh_brl(bus_speed, bitrate, constant) ((float)bus_speed / (float)bitrate - (2.0 * (float)constant))
#define hal_ll_i2c_get_real_bitrate(bus_speed, brhl, constant) ((float)bus_speed / (float)(brhl + 2 * constant))
#define hal_ll_i2c_get_bitrate_error(real_bitrate, bitrate) (((float)real_bitrate - (float)bitrate)/(float)bitrate)

// No open-drain/peripheral-pin bit exists here; DIGITAL_INPUT leaves the pin off the plain GPIO output driver.
#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_DIGITAL_OUTPUT)

/*!< @brief ICBRL and ICBRH setting helper macros */
#define HAL_LL_I2C_BRL_BRH_MAX          (31)
#define HAL_LL_I2C_BRL_BRH_MASK         (0x1F)
#define HAL_LL_I2C_DIV_TIME_NS          (1000000UL)
#define HAL_LL_I2C_BITRATE_ERROR_MAX    (0.1)

/*!< @brief IICCTLn0 bit positions (start/stop trigger, ACK/clock-stretch control) */
#define HAL_LL_I2C_IICCTL0_IICE         (7)
#define HAL_LL_I2C_IICCTL0_LREL         (6)
#define HAL_LL_I2C_IICCTL0_WREL         (5)
#define HAL_LL_I2C_IICCTL0_SPIE         (4)
#define HAL_LL_I2C_IICCTL0_WTIM         (3)
#define HAL_LL_I2C_IICCTL0_ACKE         (2)
#define HAL_LL_I2C_IICCTL0_STT          (1)
#define HAL_LL_I2C_IICCTL0_SPT          (0)

/*!< @brief IICSn bit positions (read-only status) */
#define HAL_LL_I2C_IICS_MSTS            (7)
#define HAL_LL_I2C_IICS_ALD             (6)
#define HAL_LL_I2C_IICS_EXC             (5)
#define HAL_LL_I2C_IICS_COI             (4)
#define HAL_LL_I2C_IICS_TRC             (3)
#define HAL_LL_I2C_IICS_ACKD            (2)
#define HAL_LL_I2C_IICS_STD             (1)
#define HAL_LL_I2C_IICS_SPD             (0)

/*!< @brief IICFn bit positions */
#define HAL_LL_I2C_IICF_STCF            (7)
#define HAL_LL_I2C_IICF_IICBSY          (6)
#define HAL_LL_I2C_IICF_STCEN           (1)
#define HAL_LL_I2C_IICF_IICRSV          (0)

/*!< @brief IICCTLn1 bit positions */
#define HAL_LL_I2C_IICCTL1_WUP          (7)
#define HAL_LL_I2C_IICCTL1_SVADIS       (6)
#define HAL_LL_I2C_IICCTL1_CLD          (5)
#define HAL_LL_I2C_IICCTL1_DAD          (4)
#define HAL_LL_I2C_IICCTL1_SMC          (3)
#define HAL_LL_I2C_IICCTL1_DFC          (2)
#define HAL_LL_I2C_IICCTL1_PRS          (0)

// PRR0 (reset control) isn't exposed in hal_ll_per.h; reset value already leaves it released.

/*!< @brief fMCK must not exceed this before PRSn (IICCTLn1) must divide it by 2 */
#define HAL_LL_I2C_FMCK_MAX_HZ          (20000000UL)

// Board/clock-tree dependent - not derivable from the register documentation alone.
#define HAL_LL_I2C_MCU_CLOCK_HZ         (32000000UL) /* TODO: replace with real fCLK source */
#define HAL_LL_I2C_RISE_FALL_TIME_S     (0.0000003)  /* TODO: calibrate, currently 300 ns placeholder */

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K    (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K    (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M      (1000000UL)
#define HAL_LL_I2C_MASTER_SPEED_3M2     (3200000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT   (10000)

/*!< @brief I2C register structure - 1st SFR area (IICAn/IICSn/IICFn, e.g. FFF50H/FFF54H) */
typedef struct {
    uint8_t iica;   /*!< IICAn - shift register (address+R/W, or data), R/W */
    uint8_t iics;   /*!< IICSn - status register, read-only */
    uint8_t iicf;   /*!< IICFn - flag register */
} hal_ll_i2c_base_handle_t;

// I2C register structure - 2nd SFR area (IICCTLn0/1, IICWLn/IICWHn, SVAn), not contiguous with hal_ll_i2c_base_handle_t.
typedef struct {
    uint8_t iicctl0; /*!< IICCTLn0 - start/stop trigger, ACK/clock-stretch control */
    uint8_t iicctl1; /*!< IICCTLn1 - speed mode, digital filter, clock divider */
    uint8_t iicwl;   /*!< IICWLn  - SCL low-level width setting */
    uint8_t iicwh;   /*!< IICWHn  - SCL high-level width setting */
    uint8_t sva;     /*!< SVAn    - own slave address (unused in pure-master role) */
} hal_ll_i2c_ctrl_handle_t;

// MODULE-0-ONLY offset (0xFFF50 -> 0xF0230): the two blocks don't share a per-module stride, so module 1 needs its own value recomputed against 0xF0238.
#define HAL_LL_I2C0_CTRL_BASE_ADDR (HAL_LL_I2C0_BASE_ADDR - 0xFD20UL)

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_base_addr_t base;      /*!< -> hal_ll_i2c_base_handle_t (IICAn/IICSn/IICFn) */
    hal_ll_base_addr_t ctrl_base; /*!< -> hal_ll_i2c_ctrl_handle_t (IICCTLn0/1, IICWLn/H, SVAn) */
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
    {HAL_LL_I2C0_BASE_ADDR, HAL_LL_I2C0_CTRL_BASE_ADDR, hal_ll_i2c_module_num( I2C_MODULE_0 ),
     {{HAL_LL_PIN_NC, 0}, {HAL_LL_PIN_NC, 0}},
     HAL_LL_I2C_MASTER_SPEED_100K , 0, HAL_LL_I2C_DEFAULT_PASS_COUNT},
    #endif

    {HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR,
     {{HAL_LL_PIN_NC, 0}, {HAL_LL_PIN_NC, 0}}, 0, 0, 0}
};

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Enable or disable the I2C hardware module.
  *
  * Controls the clock and power state of the specified I2C hardware module
  * by enabling or disabling it, depending on the provided state parameter.
  *
  * @param[in]  *map        - Object specific context handler.
  * @param[in]  hal_ll_state - Desired state of the module (true to enable, false to disable).
  * @return None
  */
static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state );

/**
  * @brief  Initialize I2C module on hardware level.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Full I2C module initialization procedure.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler. Sets adequate pin alternate functions.
  * Initializes module clock.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets I2C pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I2C is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_i2c_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_i2c_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Check if pins are adequate.
  *
  * Checks scl and sda pins the user has passed with pre-defined
  * pins in scl and sda maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in]  scl - SCL pre-defined pin name.
  * @param[in]  sda - SDA pre-defined pin name.
  * @param[in]  *index_list - Index list address
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map );

/**
 * @brief  Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * I2C SCL and SDA pins.
 *
 * @param[in]  module_index I2C HW module index -- 0,1,2...
 * @param[in]  *index_list  Array with SCL and SDA map index values
 *
 * @return  None
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list );

/**
  * @brief  Waits until device is free to operate.
  *
  * Polls I2C busy bit value and waits until device has finished any
  * on-going operation.
  *
  * @param[in]  *map - Object specific context handler.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) ;

/**
  * @brief  Get adequate I2C bit-rate value.
  *
  * Returns one of pre-defined bit-rate values,
  * or the closest bit-rate based on bit_rate
  * value passed to the function.
  *
  * @param[in]  bit_rate - I2C bit rate.
  * @return uint32_t Adequate bit-rate value.
  *
  * Returns adequate value to be latter written into bare metal register address.
  * Take into consideration that this returns a predefined value.
  *
  * HAL_LL_I2C_MASTER_SPEED_100K -- 100Kbit/s
  * HAL_LL_I2C_MASTER_SPEED_400K -- 400Kbit/s
  * HAL_LL_I2C_MASTER_SPEED_1M -- 1Mbit/s
  * HAL_LL_I2C_MASTER_SPEED_3M2 -- 3.2Mbit/s
  */
static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate );

/**
  * @brief  Set I2C speed registers based on clock and bit rate.
  *
  * Sets ICMR1, ICBRL, and ICBRH values based on the PCLKB clock
  * and desired I2C speed (100kHz, 400kHz, or 1MHz).
  *
  * @param[in]  *map - I2C hardware context.
  */
static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief  Perform a read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *readDatabuf - Pointer to data buffer.
  * @param[in]  lenReadData - Number of data to be read.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode );

/**
  * @brief  Perform a write on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *writeDatabuf - Pointer to data buffer.
  * @param[in]  lenWriteData - Number of data to be written.
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl,
                                                hal_ll_pin_name_t sda,
                                                hal_ll_i2c_master_handle_register_t *handle_map,
                                                uint8_t *hal_module_id ) {
    return 0;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    return 0;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    return 0;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    return 0;
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    return 0;
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle,
                                                uint8_t *write_data_buf,
                                                size_t len_write_data,
                                                uint8_t *read_data_buf,
                                                size_t len_read_data ) {
    return 0;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
// No status bit flags "clock stretch active" independent of ACK/NACK (needs the interrupt-controller's INTIICAn flag, not provided); NACK/no-reply is only caught via timeout below, not immediately.
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_master_end_mode_t mode ) {
    return 0;
}

static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_master_end_mode_t mode ) {
    return 0;
}

static void hal_ll_i2c_master_alternate_functions_set_state( hal_ll_i2c_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_i2c_pin_id *index_list ) {
}

static uint32_t hal_ll_i2c_get_speed( uint32_t bit_rate ) {
    return 0;
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    return 0;
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl,
                                                       hal_ll_pin_name_t sda,
                                                       hal_ll_i2c_pin_id *index_list,
                                                       hal_ll_i2c_master_handle_register_t *handle_map ) {
    return 0;
}

static hal_ll_err_t hal_ll_i2c_master_wait_for_idle( hal_ll_i2c_hw_specifics_map_t *map ) {
    return 0;
}

static void hal_ll_i2c_calculate_speed( hal_ll_i2c_hw_specifics_map_t *map ) {
}

static void hal_ll_i2c_hw_init( hal_ll_i2c_hw_specifics_map_t *map ) {
}

static void hal_ll_i2c_master_module_enable( hal_ll_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
}

static void hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
}

// ------------------------------------------------------------------------- END
