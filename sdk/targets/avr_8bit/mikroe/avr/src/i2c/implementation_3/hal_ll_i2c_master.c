/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_i2c_master.c
 * @brief I2C master HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_i2c_master.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address (( hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) (( hal_ll_i2c_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

/*!< @brief Helper macro for getting adequate module index number. */
#define hal_ll_i2c_module_num(_module_num) (_module_num - 1)

/*!< @brief Default pass count value upon reset. */
#define HAL_LL_I2C_DEFAULT_PASS_COUNT (10000)

/*!< @brief Default I2C bit-rate if no speed is set. */
#define HAL_LL_I2C_MASTER_SPEED_50K (50000UL)

/*!< @brief Helper macro for getting adequate slave address bit count. */
#define HAL_LL_I2C_MASTER_BIT_COUNTER (0x80)

/*!< @brief Helper macro for getting adequate slave address byte size. */
#define HAL_LL_I2C_MASTER_SLAVE_ADDRESS_BYTE (1)

/*!< @brief Helper macros for getting adequate software I2C timings. */
void software_i2c_timing_value_a( void ) {
    Delay_1us(); Delay_1us();
}

void software_i2c_timing_value_b( void ) {
    Delay_1us(); Delay_1us();
    Delay_1us(); Delay_1us();
}

void software_i2c_timing_value_c( void ) {
    Delay_1us(); Delay_1us();
    Delay_1us(); Delay_1us();
    Delay_1us(); Delay_1us();
    Delay_1us(); Delay_1us();
}

// -------------------------------------------------------------- PRIVATE TYPES
/*!< @brief I2C register structure */
typedef struct {
    hal_ll_base_addr_t port_reg_addr;
    hal_ll_base_addr_t ddr_reg_addr;
    hal_ll_base_addr_t pin_reg_addr;
} hal_ll_i2c_base_handle_t;

/*!< @brief Software I2C hw specific pointers to functions. */
typedef struct {
    hal_ll_err_t ( *mapped_function_software_i2c_signal_write )( hal_ll_i2c_base_handle_t *, uint8_t *write_data_buf, size_t len_write_data );
    hal_ll_err_t ( *mapped_function_software_i2c_signal_read )( hal_ll_i2c_base_handle_t *, uint8_t *read_data_buf, size_t len_read_data );
} hal_ll_software_i2c_functions;

/*!< @brief Context structure for storing pin mask for both SCL and SDA. */
typedef struct {
    hal_ll_pin_name_t pin_mask_scl;
    hal_ll_pin_name_t pin_mask_sda;
} hal_ll_i2c_pins_mask_t;

/*!< @brief I2C hw specific structure */
typedef struct {
    hal_ll_i2c_base_handle_t *base;
    hal_ll_pin_name_t module_index;
    hal_ll_i2c_pins_t pins;
    hal_ll_i2c_pins_mask_t pins_mask;
    uint32_t speed;
    uint8_t address;
    uint16_t timeout;
    hal_ll_software_i2c_functions mapped_functions;
} hal_ll_i2c_hw_specifics_map_t;

/*!< @brief I2C hw specific module values */
typedef struct {
    hal_ll_pin_name_t pin_scl;
    hal_ll_pin_name_t pin_sda;
} hal_ll_i2c_pin_id;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_I2C_MASTER_SUCCESS = 0,
    HAL_LL_I2C_MASTER_WRONG_PINS,
    HAL_LL_I2C_MASTER_MODULE_ERROR,

    HAL_LL_I2C_MASTER_ERROR = (-1)
} hal_ll_i2c_master_err_t;

/*!< @brief I2C end mode selection values */
typedef enum {
    HAL_LL_I2C_MASTER_END_MODE_RESTART = 0,
    HAL_LL_I2C_MASTER_END_MODE_STOP,
    HAL_LL_I2C_MASTER_WRITE_THEN_READ
} hal_ll_i2c_master_end_mode_t;

/*!< @brief I2C timeout error values */
typedef enum {
    HAL_LL_I2C_MASTER_TIMEOUT_START = 1300,
    HAL_LL_I2C_MASTER_TIMEOUT_WRITE,
    HAL_LL_I2C_MASTER_TIMEOUT_READ,
    HAL_LL_I2C_MASTER_ARBITRATION_LOST,
    HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE,
    HAL_LL_I2C_MASTER_WRITE_COLLISION
} hal_ll_i2c_master_timeout_t;

// ------------------------------------------------------------------ CONSTANTS
/*!< @brief I2C registers array */
static  hal_ll_i2c_base_handle_t hal_ll_i2c_hw_regs[ I2C_MODULE_COUNT + 1 ] = {
    #ifdef __PORT_A_CN
    { PORTA_REG_ADDRESS, DDRA_REG_ADDRESS, PINA_REG_ADDRESS },
    #endif
    #ifdef __PORT_B_CN
    { PORTB_REG_ADDRESS, DDRB_REG_ADDRESS, PINB_REG_ADDRESS },
    #endif
    #ifdef __PORT_C_CN
    { PORTC_REG_ADDRESS, DDRC_REG_ADDRESS, PINC_REG_ADDRESS },
    #endif
    #ifdef __PORT_D_CN
    { PORTD_REG_ADDRESS, DDRD_REG_ADDRESS, PIND_REG_ADDRESS },
    #endif
    #ifdef __PORT_E_CN
    { PORTE_REG_ADDRESS, DDRE_REG_ADDRESS, PINE_REG_ADDRESS },
    #endif
    #ifdef __PORT_F_CN
    { PORTF_REG_ADDRESS, DDRF_REG_ADDRESS, PINF_REG_ADDRESS },
    #endif
    #ifdef __PORT_G_CN
    { PORTG_REG_ADDRESS, DDRG_REG_ADDRESS, PING_REG_ADDRESS },
    #endif
    #ifdef __PORT_H_CN
    { PORTH_REG_ADDRESS, DDRH_REG_ADDRESS, PINH_REG_ADDRESS },
    #endif
    #ifdef __PORT_J_CN
    { PORTJ_REG_ADDRESS, DDRJ_REG_ADDRESS, PINJ_REG_ADDRESS },
    #endif
    #ifdef __PORT_K_CN
    { PORTK_REG_ADDRESS, DDRK_REG_ADDRESS, PINK_REG_ADDRESS },
    #endif
    #ifdef __PORT_L_CN
    { PORTL_REG_ADDRESS, DDRL_REG_ADDRESS, PINL_REG_ADDRESS },
    #endif
    #ifdef __PORT_R_CN
    { PORTR_REG_ADDRESS, DDRR_REG_ADDRESS, PINR_REG_ADDRESS },
    #endif
    { HAL_LL_PORT_NC, HAL_LL_PORT_NC, HAL_LL_PORT_NC }
};

// ------------------------------------------------------------------ VARIABLES
/*!< @brief I2C hardware specific info */
static hal_ll_i2c_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + 1 ] = {
    #ifdef __PORT_A_CN
    { &hal_ll_i2c_hw_regs[ PORT_A ], hal_ll_i2c_module_num( PORT_A + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_B_CN
    { &hal_ll_i2c_hw_regs[ PORT_B ], hal_ll_i2c_module_num( PORT_B + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_C_CN
    { &hal_ll_i2c_hw_regs[ PORT_C ], hal_ll_i2c_module_num( PORT_C + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_D_CN
    { &hal_ll_i2c_hw_regs[ PORT_D ], hal_ll_i2c_module_num( PORT_D + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_E_CN
    { &hal_ll_i2c_hw_regs[ PORT_E ], hal_ll_i2c_module_num( PORT_E + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_F_CN
    { &hal_ll_i2c_hw_regs[ PORT_F ], hal_ll_i2c_module_num( PORT_F + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_G_CN
    { &hal_ll_i2c_hw_regs[ PORT_G ], hal_ll_i2c_module_num( PORT_G + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_H_CN
    { &hal_ll_i2c_hw_regs[ PORT_H ], hal_ll_i2c_module_num( PORT_H + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_J_CN
    { &hal_ll_i2c_hw_regs[ PORT_J ], hal_ll_i2c_module_num( PORT_J + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_K_CN
    { &hal_ll_i2c_hw_regs[ PORT_K ], hal_ll_i2c_module_num( PORT_K + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_L_CN
    { &hal_ll_i2c_hw_regs[ PORT_L ], hal_ll_i2c_module_num( PORT_L + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif
    #ifdef __PORT_R_CN
    { &hal_ll_i2c_hw_regs[ PORT_R ], hal_ll_i2c_module_num( PORT_R + 1 ), { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0, HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL },
    #endif

    { HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, { HAL_LL_PIN_NC, HAL_LL_PIN_NC }, HAL_LL_I2C_MASTER_SPEED_50K, 0,
    HAL_LL_I2C_DEFAULT_PASS_COUNT, NULL }
};
/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief Check if pins are adequate.
  *
  * Checks scl and sda pins the user has passed with pre-defined
  * pins in scl and sda maps. Take into consideration that module
  * index numbers have to be the same for both pins.
  *
  * @param[in] scl - SCL pre-defined pin name.
  * @param[in] sda - SDA pre-defined pin name.
  * @param[in] *handle_map - Local handle list.
  *
  * @return hal_ll_pin_name_t Module index based on pins.
  *
  * Returns pre-defined module index from pin maps, if pins
  * are adequate.
  */
static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map );

/**
  * @brief Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_i2c_hw_specifics_map array index.
  *
  * @param[in] handle - Object specific context handler.
  *
  * @return hal_ll_i2c_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
 * @brief Maps new-found module specific values.
 *
 * Maps pin names and alternate function values for
 * I2C SCL and SDA pins.
 *
 * @param[in] module_index I2C HW module index -- 0,1,2...
 * @param[in] scl Clock pin.
 * @param[in] sda Data pin.
 *
 * @return  None
 */
static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_pin_name_t scl, hal_ll_pin_name_t sda );

/**
  * @brief Full software I2C module initialization procedure.
  *
  * Initializes I2C module on hardware level, based on beforehand
  * set configuration and module handler.
  *
  * @param[in] *map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief Map adequate function addresses.
  *
  * Function maps adequate function addresses.
  *
  * @param[in] hal_ll_module_id - Module index.
  *
  * @return none
  *
  */
static inline void map_pointer_functions( uint8_t hal_ll_module_id );

/**
  * @brief Software I2C "write bytes" function.
  *
  * Function starts generating how many bytes there are on SDA pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of software I2C module.
  * @param[in] *write_data_buf - Pointer to data buffer.
  * @param[in] len_write_data - Number of data to be written.
  *
  * @return hal_ll_err_t Module specific values.
  *
  */
static inline hal_ll_err_t ptr_function_software_i2c_signal_write_bytes( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buf, size_t len_write_data );

/**
  * @brief Software I2C "read bytes" function.
  *
  * Function starts reading how many bytes there are on SDA pin.
  *
  * @param[in] *hal_ll_hw_reg - Set of registers used for proper usage of software I2C module.
  * @param[in] *read_data_buf - Pointer to data buffer.
  * @param[in] len_read_data - Number of data to be read.
  *
  * @return hal_ll_err_t Module specific values.
  *
  */
static inline hal_ll_err_t ptr_function_software_i2c_signal_read_bytes( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buf, size_t len_read_data );

/**
  * @brief Generates start signal on I2C bus.
  *
  * Generates a start signal on the I2C bus.
  *
  * @param[in] *map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief Generates stop signal on I2C bus.
  *
  * Generates a stop signal on the I2C bus.
  *
  * @param[in] *map - Object specific context handler.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map );

/**
  * @brief Perform a read on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a read operation on the bus.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] *read_data_buf - Pointer to data buffer.
  * @param[in] len_read_data - Number of data to be read.
  * @param[in] mode - I2C end mode selection value.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode );

/**
  * @brief Perform a write on the I2C bus.
  *
  * Initializes I2C module on hardware level, if not initialized beforehand
  * and continues to perform a write operation on the bus.
  *
  * @param[in] *map - Object specific context handler.
  * @param[in] *write_data_buf - Pointer to data buffer.
  * @param[in] len_write_data - Number of data to be written.
  * @param[in] mode - I2C end mode selection value.
  *
  * @return hal_ll_err_t Module specific values.
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i2c_master_register_handle( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map, uint8_t *hal_module_id ) {
    hal_ll_i2c_pin_id index_list[ I2C_MODULE_COUNT ] = { HAL_LL_PIN_NC, HAL_LL_PIN_NC };
    uint8_t pin_check_result;

    if ( HAL_LL_PIN_NC == ( pin_check_result = hal_ll_i2c_master_check_pins( scl, sda, handle_map ) ) ) {
        return HAL_LL_I2C_MASTER_WRONG_PINS;
    };

    if ( ( hal_ll_i2c_hw_specifics_map[ pin_check_result ].pins.pin_scl != scl ) ||
         ( hal_ll_i2c_hw_specifics_map[ pin_check_result ].pins.pin_sda != sda ) ) {
        // Map new pins.
        hal_ll_i2c_master_map_pins( pin_check_result, scl, sda );

        // Set HAL initialization state to false.
        handle_map[ pin_check_result ]->init_ll_state = false;

        // Initialize HAL Low Level software I2C module.
        if ( HAL_LL_I2C_MASTER_SUCCESS != ( hal_ll_i2c_init( &hal_ll_i2c_hw_specifics_map[ pin_check_result ] ) ) ) {
            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
        }
    }

    *hal_module_id = pin_check_result;

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;

    handle_map[ pin_check_result ]->hal_ll_i2c_master_handle = ( handle_t * )&hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_module_configure_i2c( handle_t *handle ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );
    hal_ll_i2c_master_handle_register_t *hal_handle = (hal_ll_i2c_master_handle_register_t *)*handle;
    uint8_t pin_check_result = hal_ll_i2c_hw_specifics_map_local->module_index;

    if ( HAL_LL_I2C_MASTER_SUCCESS != ( hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_local ) ) ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
    }

    hal_ll_module_state[ pin_check_result ].hal_ll_i2c_master_handle = (handle_t * )&hal_ll_i2c_hw_specifics_map[ pin_check_result ].base;
    hal_ll_module_state[ pin_check_result ].init_ll_state = true;
    hal_handle->init_ll_state = true;

    return HAL_LL_I2C_MASTER_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_master_set_speed( handle_t *handle, uint32_t speed ) {
    /* NOTE 1:
     * Speed selection currently not applicable for software I2C implementation,
     * it is dependable of MCU clock frequency itself.
     *
     * NOTE 2:
     * Realistic software I2C speeds (after testing Mikroe's Click Boards with this implementation):
     * ~50kHz @16MHz;
     * ~25kHz @8MHz. */
    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_set_timeout( handle_t *handle, uint16_t timeout ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( hal_ll_i2c_hw_specifics_map_local->module_index != HAL_LL_MODULE_ERROR ) {
        hal_ll_i2c_hw_specifics_map_local->timeout = timeout;
    }
}

void hal_ll_i2c_master_set_slave_address( handle_t *handle, uint8_t addr ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    hal_ll_i2c_hw_specifics_map_local->address = addr;
}

hal_ll_err_t hal_ll_i2c_master_read( handle_t *handle, uint8_t *read_data_buf, size_t len_read_data ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics(hal_ll_i2c_get_module_state_address);

    return hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    return hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_END_MODE_STOP );
}

hal_ll_err_t hal_ll_i2c_master_write_then_read( handle_t *handle, uint8_t *write_data_buf, size_t len_write_data, uint8_t *read_data_buf, size_t len_read_data ) {
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_local, write_data_buf, len_write_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != HAL_LL_I2C_MASTER_SUCCESS ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_WRITE;
    }

    /**
     * @note Wait for drivers to set-up
     * correctly.
     **/
    #ifdef __TFT_RESISTIVE_TSC2003__
    Delay_22us();
    #endif

    if( hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_local, read_data_buf, len_read_data, HAL_LL_I2C_MASTER_WRITE_THEN_READ ) != HAL_LL_I2C_MASTER_SUCCESS ) {
        return HAL_LL_I2C_MASTER_TIMEOUT_READ;
    }

    return HAL_LL_I2C_MASTER_SUCCESS;
}

void hal_ll_i2c_master_close( handle_t *handle ) {
    low_level_handle = hal_ll_i2c_get_handle;
    hal_ll_i2c_hw_specifics_map_local = hal_ll_get_specifics( hal_ll_i2c_get_module_state_address );

    if( low_level_handle->hal_ll_i2c_master_handle != NULL ) {
        low_level_handle->hal_ll_i2c_master_handle = NULL;
        low_level_handle->hal_drv_i2c_master_handle = NULL;
        low_level_handle->init_ll_state = false;

        hal_ll_i2c_hw_specifics_map_local->address = 0;
        hal_ll_i2c_hw_specifics_map_local->timeout = HAL_LL_I2C_DEFAULT_PASS_COUNT;
        hal_ll_i2c_hw_specifics_map_local->speed = HAL_LL_I2C_MASTER_SPEED_50K;

        hal_ll_i2c_hw_specifics_map_local->pins.pin_scl = HAL_LL_PIN_NC;
        hal_ll_i2c_hw_specifics_map_local->pins.pin_sda = HAL_LL_PIN_NC;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static hal_ll_err_t hal_ll_i2c_master_read_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *read_data_buf, size_t len_read_data, hal_ll_i2c_master_end_mode_t mode ) {
    uint8_t ptr_slave_address = ( ( hal_ll_i2c_hw_specifics_map_local->address << 1 ) | 1 );
    uint16_t time_counter = map->timeout;

    // Apply start signal only if READ functionality is used (skip if WRITE then READ is used instead).
    if( HAL_LL_I2C_MASTER_WRITE_THEN_READ != mode ) {
        hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_local );
    }

    // Map write and read functions.
    map_pointer_functions( hal_ll_i2c_hw_specifics_map_local->module_index );

    // Send slave address and a "Read" bit (via function pointer).
    ( hal_ll_i2c_hw_specifics_map_local->mapped_functions.mapped_function_software_i2c_signal_write )
    ( hal_ll_i2c_hw_specifics_map_local->base, &ptr_slave_address, HAL_LL_I2C_MASTER_SLAVE_ADDRESS_BYTE );

    // Read byte(s) of data (via function pointer).
    ( hal_ll_i2c_hw_specifics_map_local->mapped_functions.mapped_function_software_i2c_signal_read )
    ( hal_ll_i2c_hw_specifics_map_local->base, read_data_buf, len_read_data );

    // Stop signal.
    hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_local );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_write_bare_metal( hal_ll_i2c_hw_specifics_map_t *map, uint8_t *write_data_buf, size_t len_write_data, hal_ll_i2c_master_end_mode_t mode ) {
    uint8_t ptr_slave_address = hal_ll_i2c_hw_specifics_map_local->address << 1;

    /*!< @brief Start signal. */
    hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_local );

    // Map write function.
    map_pointer_functions( hal_ll_i2c_hw_specifics_map_local->module_index );

    /*!< @brief Send slave address and a "Write" bit (via function pointer). */
    ( hal_ll_i2c_hw_specifics_map_local->mapped_functions.mapped_function_software_i2c_signal_write )
    ( hal_ll_i2c_hw_specifics_map_local->base, &ptr_slave_address, HAL_LL_I2C_MASTER_SLAVE_ADDRESS_BYTE );

    /*!< @brief Write byte(s) of data (via function pointer). */
    ( hal_ll_i2c_hw_specifics_map_local->mapped_functions.mapped_function_software_i2c_signal_write )
    ( hal_ll_i2c_hw_specifics_map_local->base, write_data_buf, len_write_data );

    /*!< @brief Generate stop (or a restart) signal. */
    if( HAL_LL_I2C_MASTER_END_MODE_STOP == mode ) {
        hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_local );
    } else {
        /**
         * @note When R/W = 0, the input sample acquisition period starts
         * on the falling edge of SCL once the C0 bit of the command
         * byte has been latched, and ends when a Stop or
         * repeated Start condition has been issued.
         **/
        #ifdef __TFT_RESISTIVE_TSC2003__
        Delay_1ms();
        #endif
        hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_local );
    }
    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_start( hal_ll_i2c_hw_specifics_map_t *map ) {
    // Get appropriate PORT, PIN and DDR registers.
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // Set SDA direction to be input.
    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_sda );

    // Stabilization time.
    software_i2c_timing_value_a();

    // Set SCL direction to be input.
    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_scl );

    // Stabilization time.
    software_i2c_timing_value_a();

    // Set SDA direction to be output.
    set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_sda );

    // Stabilization time.
    software_i2c_timing_value_a();

    // Set SCL direction to be output.
    set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_scl );

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_err_t hal_ll_i2c_master_stop( hal_ll_i2c_hw_specifics_map_t *map ) {
    uint16_t time_counter = map->timeout;

    // Get appropriate PORT, PIN and DDR registers.
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // Set SDA direction to be output.
    set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_sda );

    // Stabilization time.
    software_i2c_timing_value_a();

    // Set SCL direction to be input.
    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_scl );

    // Wait until SCL pin is unblocked.
    while ( !( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, map->pins_mask.pin_mask_scl ) ) ) {
        // User-defined timeout.
        if ( time_counter ) {
            if ( !time_counter-- ) {
                return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
            }
        }
    }

    // Stabilization time.
    software_i2c_timing_value_c();

    // Set SDA direction to be input.
    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_sda );

    // Stabilization time.
    software_i2c_timing_value_a();

    return HAL_LL_I2C_MASTER_SUCCESS;
}

static hal_ll_pin_name_t hal_ll_i2c_master_check_pins( hal_ll_pin_name_t scl, hal_ll_pin_name_t sda, hal_ll_i2c_master_handle_register_t *handle_map ) {
    uint8_t hal_ll_module_id = 0;

    // Check if pins are valid.
    if ( ( HAL_LL_PIN_NC == scl ) || ( HAL_LL_PIN_NC == sda ) ) {
        return HAL_LL_PIN_NC;
    }

    // Check if both SCL and SDA pins are on the same port.
    if ( ( hal_ll_gpio_port_index( scl ) ) == ( hal_ll_gpio_port_index( sda ) ) ) {
        // Get module number.
        hal_ll_module_id = hal_ll_gpio_port_index( scl );
    }

    // Check if module is taken.
    if ( NULL == handle_map[ hal_ll_module_id ].hal_drv_i2c_master_handle ) {
        return hal_ll_module_id;
    } else {
        return HAL_LL_PIN_NC;
    }
}

static hal_ll_i2c_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
    uint8_t hal_ll_module_count = sizeof( hal_ll_module_state ) / ( sizeof( hal_ll_i2c_master_handle_register_t ) );
    static uint8_t hal_ll_module_error = hal_ll_module_count;

    while( hal_ll_module_count-- ) {
        if ( hal_ll_i2c_get_base_from_hal_handle == hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ].base ) {
            return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_count ];
        }
    }

    return &hal_ll_i2c_hw_specifics_map[ hal_ll_module_error ];
}

static void hal_ll_i2c_master_map_pins( uint8_t module_index, hal_ll_pin_name_t scl, hal_ll_pin_name_t sda ) {
    // Map new pins.
    hal_ll_i2c_hw_specifics_map[ module_index ].pins.pin_scl = scl;
    hal_ll_i2c_hw_specifics_map[ module_index ].pins.pin_sda = sda;

    // Map new pin's masks.
    hal_ll_i2c_hw_specifics_map[ module_index ].pins_mask.pin_mask_scl = ( uint8_t )scl % PORT_SIZE;
    hal_ll_i2c_hw_specifics_map[ module_index ].pins_mask.pin_mask_sda = ( uint8_t )sda % PORT_SIZE;
}

static hal_ll_err_t hal_ll_i2c_init( hal_ll_i2c_hw_specifics_map_t *map ) {
    uint16_t time_counter = map->timeout;

    // Get appropriate PORT, PIN and DDR registers.
    hal_ll_i2c_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // Set SDA direction to be input.
    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_sda );

    // Set SCL direction to be input.
    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, map->pins_mask.pin_mask_scl );

    // Clear output on SDA pin.
    clear_reg_bit( hal_ll_hw_reg->port_reg_addr, map->pins_mask.pin_mask_sda );

    // Clear output on SCL pin.
    clear_reg_bit( hal_ll_hw_reg->port_reg_addr, map->pins_mask.pin_mask_scl );

    // Wait until SCL pin is unblocked.
    while ( !( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, map->pins_mask.pin_mask_scl ) ) ) {
        // User-defined timeout.
        if ( time_counter ) {
            if ( !time_counter-- ) {
                return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
            }
        }
    }
    return HAL_LL_I2C_MASTER_SUCCESS;
}

// ---------------------------------------------------- STATIC POINTER FUNCTIONS
static inline void map_pointer_functions( uint8_t hal_ll_module_id ) {
    hal_ll_i2c_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_software_i2c_signal_write = &ptr_function_software_i2c_signal_write_bytes;
    hal_ll_i2c_hw_specifics_map[ hal_ll_module_id ]->mapped_functions.mapped_function_software_i2c_signal_read = &ptr_function_software_i2c_signal_read_bytes;
}

static inline hal_ll_err_t ptr_function_software_i2c_signal_write_bytes( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint8_t *write_data_buf, size_t len_write_data ) {
    uint16_t time_counter = hal_ll_i2c_hw_specifics_map_local->timeout;
    size_t byte_counter = 0;
    uint16_t bit_counter;

    while ( ( byte_counter < len_write_data ) ) {
        bit_counter = HAL_LL_I2C_MASTER_BIT_COUNTER;
            while ( bit_counter ) {
                // Stabilization time.
                software_i2c_timing_value_b();

                // Set SCL direction to be output.
                set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

                // Stabilization time.
                software_i2c_timing_value_a();

                if ( write_data_buf[ byte_counter ] & bit_counter ){
                    // Set SDA direction to be input.
                    clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );
                } else {
                    // Set SDA direction to be output.
                    set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );
                }
                // Stabilization time.
                software_i2c_timing_value_a();

                // Set SCL direction to be input.
                clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

                // Wait until SCL pin is unblocked.
                while ( !( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl ) ) ) {
                    // User-defined timeout.
                    if ( time_counter ) {
                        if ( !time_counter-- ) {
                            return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
                        }
                    }
                }

                bit_counter >>= 1;
            }
            ++byte_counter;

        // Stabilization time.
        software_i2c_timing_value_a();

        // Set SCL direction to be output.
        set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

        // Stabilization time.
        software_i2c_timing_value_a();

        // Set SDA direction to be input.
        clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );

        // Stabilization time.
        software_i2c_timing_value_b();

        // Set SCL direction to be input.
        clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

        // Wait until SCL pin is unblocked.
        while ( !( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl ) ) ) {
            // User-defined timeout.
            if ( time_counter ) {
                if ( !time_counter-- ) {
                    return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
                }
            }
        }

        // Stabilization time.
        software_i2c_timing_value_a();

        if ( ( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda ) ) ) {
            return HAL_LL_I2C_MASTER_WRITE_COLLISION;
        }

        // Stabilization time.
        software_i2c_timing_value_c();

        // Set SCL direction to be output.
        set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

        // Set SDA direction to be output.
        set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );
    }
    return HAL_LL_I2C_MASTER_SUCCESS;
}

static inline hal_ll_err_t ptr_function_software_i2c_signal_read_bytes( hal_ll_i2c_base_handle_t *hal_ll_hw_reg, uint8_t *read_data_buf, size_t len_read_data ) {
    uint16_t time_counter = hal_ll_i2c_hw_specifics_map_local->timeout;
    size_t byte_counter = 0;
    uint16_t bit_counter;

    while ( ( byte_counter < len_read_data ) ) {
        bit_counter = HAL_LL_I2C_MASTER_BIT_COUNTER;
        while ( bit_counter ) {
            // Stabilization time.
            software_i2c_timing_value_a();

            // Set SDA direction to be input.
            clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );

            // Stabilization time.
            software_i2c_timing_value_a();

            // Set SCL direction to be input.
            clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

            // Wait until SCL pin is unblocked.
            while ( !( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl ) ) ) {
                // User-defined timeout.
                if ( time_counter ) {
                    if ( !time_counter-- ) {
                        return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
                    }
                }
            }

            // Sample the data.
            if ( ( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda ) ) ) {
                read_data_buf[ byte_counter ] |= bit_counter;
            } else {
                read_data_buf[ byte_counter ] &= ~bit_counter;
            };

            // Stabilization time.
            software_i2c_timing_value_a();

            // Set SCL direction to be output.
            set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

            bit_counter >>= 1;
        }
        ++byte_counter;

        // Set SDA direction to be input.
        clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );

        // Stabilization time.
        software_i2c_timing_value_a();

        // Ack.
        if ( byte_counter < len_read_data ) {
            // Set SDA direction to be output.
            set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );
        } else {
            // Set SDA direction to be input.
            clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );
        }

        // Stabilization time.
        software_i2c_timing_value_a();

        // Set SCL direction to be input.
        clear_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

        // Wait until SCL pin is unblocked.
        while ( !( check_reg_bit( hal_ll_hw_reg->pin_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl ) ) ) {
            // User-defined timeout.
            if ( time_counter ) {
                if ( !time_counter-- ) {
                    return HAL_LL_I2C_MASTER_TIMEOUT_WAIT_IDLE;
                }
            }
        }

        // Stabilization time.
        software_i2c_timing_value_a();

        // Set SCL direction to be output.
        set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_scl );

        // Stabilization time.
        software_i2c_timing_value_a();

        // Set SDA direction to be output.
        set_reg_bit( hal_ll_hw_reg->ddr_reg_addr, hal_ll_i2c_hw_specifics_map_local->pins_mask.pin_mask_sda );
    }
    return HAL_LL_I2C_MASTER_SUCCESS;
}
// ------------------------------------------------------------------------- END
