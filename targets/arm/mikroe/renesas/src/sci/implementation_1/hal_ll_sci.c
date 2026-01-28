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
 * @file  hal_ll_uart.c
 * @brief UART HAL LOW LEVEL layer implementation.
 */

#include <math.h>
#include "hal_ll_gpio.h"
#include "hal_ll_sci.h"
#include "hal_ll_i2c_pin_map.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

/*!< @brief Local handle list */
static volatile hal_ll_i2c_master_handle_register_t hal_ll_module_state[I2C_MODULE_COUNT] = { (handle_t *)NULL, (handle_t *)NULL, false };

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting hal_ll_module_state address */
#define hal_ll_i2c_get_module_state_address ((hal_ll_i2c_master_handle_register_t *)*handle)
/*!< @brief Helper macro for getting module specific control register structure base address // first register address */
#define hal_ll_i2c_get_handle (hal_ll_i2c_master_handle_register_t *)hal_ll_i2c_get_module_state_address->hal_ll_i2c_master_handle
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_i2c_get_base_struct(_handle) ((hal_ll_sci_base_handle_t *)_handle)
/*!< @brief Helper macro for getting module specific base address directly from HAL layer handle */
#define hal_ll_i2c_get_base_from_hal_handle ((hal_ll_i2c_sci_hw_specifics_map_t *)((hal_ll_i2c_master_handle_register_t *)\
                                            (((hal_ll_i2c_master_handle_register_t *)(handle))->hal_ll_i2c_master_handle))->hal_ll_i2c_master_handle)->base

#define HAL_LL_I2C_AF_CONFIG (GPIO_CFG_PORT_PULL_UP_ENABLE |\
                              GPIO_CFG_DIGITAL_OUTPUT |\
                              GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE |\
                              GPIO_CFG_PERIPHERAL_PIN)

/*!< @brief Default I2C bit-rate if no speed is set */
#define HAL_LL_I2C_MASTER_SPEED_100K                (100000UL)
#define HAL_LL_I2C_MASTER_SPEED_400K                (400000UL)
#define HAL_LL_I2C_MASTER_SPEED_1M                  (1000000UL)
#define HAL_LL_I2C_MASTER_SPEED_3M2                 (3200000UL)

#define HAL_LL_I2C_DEFAULT_PASS_COUNT               (10000)

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_SCR_TEIE         2
#define HAL_LL_SCI_SCR_RE           4
#define HAL_LL_SCI_SCR_TE           5
#define HAL_LL_SCI_SCR_TIE          7

#define HAL_LL_SCI_SEMR_NFEN        5

#define HAL_LL_SCI_SSR_TEND         2
#define HAL_LL_SCI_SSR_RDRF         6
#define HAL_LL_SCI_SSR_TDRE         7

#define HAL_LL_SCI_SCMR_SMIF        0
#define HAL_LL_SCI_SCMR_SINV        2
#define HAL_LL_SCI_SCMR_SDIR        3

#define HAL_LL_SCI_SPTR_RXDMON      0
#define HAL_LL_SCI_SPTR_SPB2DT      1
#define HAL_LL_SCI_SPTR_SPB2IO      2
#define HAL_LL_SCI_SPTR_RINV        4
#define HAL_LL_SCI_SPTR_TINV        5
#define HAL_LL_SCI_SPTR_ASEN        6
#define HAL_LL_SCI_SPTR_ATEN        7

#define HAL_LL_SCI_SIMR1_IICM       0

#define HAL_LL_SCI_SIMR2_IICINTM    0
#define HAL_LL_SCI_SIMR2_IICCSC     1
#define HAL_LL_SCI_SIMR2_IICACKT    5

#define HAL_LL_SCI_SIMR3_IICSTIF    3

#define HAL_LL_SCI_SISR_IICACKR     0

/*!< @brief Macros defining bit masks. */
#define HAL_LL_SCI_SCR_READ_MASK            0xB4
#define HAL_LL_SCI_SIMR3_IICSDAS_MASK       0x30
#define HAL_LL_SCI_SIMR3_IICSCLS_MASK       0xC0
#define HAL_LL_SCI_SIMR3_START_MASK         0x51
#define HAL_LL_SCI_SIMR3_STOP_MASK          0x54

/*!< @brief Baud rate divisor information structure. */
static const uint16_t g_div_coefficient[] = {
    32U, 128U, 512U, 2048U
};

/*!< @brief I2C register structure */
typedef struct {
    uint8_t smr;        // Serial Mode Register.
    uint8_t brr;        // Bit Rate Register.
    uint8_t scr;        // Serial Control Register.
    uint8_t tdr;        // Transmit Data Register.
    uint8_t ssr;        // Serial Status Register.
    uint8_t rdr;        // Receive Data Register.
    uint8_t scmr;       // Smart Card Mode Register.
    uint8_t semr;       // Serial Extended Mode Register.
    uint8_t snfr;       // Noise Filter Setting Register.
    uint8_t simr1;      // I2C Mode Register 1.
    uint8_t simr2;      // I2C Mode Register 2.
    uint8_t simr3;      // I2C Mode Register 3.
    uint8_t sisr;       // I2C Status Register
    uint8_t spmr;       // SPI Mode Register
    uint16_t tdrhl;     // Transmit 9-bit Data Register.
    uint16_t rdrhl;     // Receive 9-bit Data Register.
    uint8_t mddr;       // Modulation Duty Register.
    uint8_t dccr;       // Data Compare Match Control Register.
    uint16_t fcr;       // FIFO Control Register.
    uint16_t fdr;       // FIFO Data Count Register.
    uint16_t lsr;       // Line Status Register.
    uint16_t cdr;       // Compare Match Data Register.
    uint8_t sptr;       // Serial Port Register.

} hal_ll_sci_base_handle_t;

// ------------------------------------------------------------------ VARIABLES

extern hal_ll_i2c_sci_hw_specifics_map_t hal_ll_i2c_hw_specifics_map[ I2C_MODULE_COUNT + SCI_MODULE_COUNT + 1 ];

/*!< @brief Global handle variables used in functions */
static volatile hal_ll_i2c_master_handle_register_t *low_level_handle;
static volatile hal_ll_i2c_sci_hw_specifics_map_t *hal_ll_i2c_hw_specifics_map_local;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize SCI module in I2C Master mode on hardware level.
  *
  * Initializes SCI module in I2C Master mode on hardware level,
  * based on beforehand set configuration and module handler.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
  */
static void hal_ll_i2c_sci_hw_init( hal_ll_i2c_sci_hw_specifics_map_t *map );

/**
  * @brief  Sets I2C_SCI pin alternate function state.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I2C_SCI is to work.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i2c_sci_alternate_functions_set_state( hal_ll_i2c_sci_hw_specifics_map_t *map,
                                                             bool hal_ll_state );

/**
  * @brief  Get local hardware specific map.
  *
  * Checks handle value and returns address of adequate
  * hal_ll_i2c_hw_specifics_map array index.
  *
  * @param[in]  handle - Object specific context handler.
  * @return hal_ll_i2c_sci_hw_specifics_map_t Map address.
  *
  * Returns pre-defined map index address based on handle value,
  * if handle is adequate.
  */
static hal_ll_i2c_sci_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle );

/**
  * @brief  Set I2C_SCI speed registers based on clock and bit rate.
  *
  * Sets ICMR1, ICBRL, and ICBRH values based on the PCLKB clock
  * and desired I2C speed (100kHz, 400kHz, or 1MHz).
  *
  * @param[in]  *map - I2C_SCI hardware context.
  */
static void hal_ll_i2c_sci_calculate_speed( hal_ll_i2c_sci_hw_specifics_map_t *map );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_i2c_sci_write_bare_metal( hal_ll_i2c_sci_hw_specifics_map_t *map,
                                                        uint8_t *write_data_buf,
                                                        size_t len_write_data,
                                                        hal_ll_i2c_sci_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    // Wait for all previous transmissions to be ended.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_WRITE;
        }
    }

    // Trigger the start condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_READ;
        }
    }

    // Clear ACK flag I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | \
                    HAL_LL_SCI_SIMR3_IICSCLS_MASK | HAL_LL_SCI_SIMR3_IICSTIF );

    // Send the slave address and write command.
    write_reg( &hal_ll_hw_reg->tdr, map->address << 1 );

    // Wait for the slave address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_WRITE;
        }
    }

    // Check if for ACK signal.
    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_SCI_SISR_IICACKR ) ) {
        for( uint8_t i = 0; i < len_write_data; i++ ) {
            write_reg( &hal_ll_hw_reg->tdr, write_data_buf[i] );

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_SCI_TIMEOUT_WRITE;
                }
            }
        }
    }

    // Trigger the stop condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF | \
                    HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    return HAL_LL_I2C_SCI_SUCCESS;
}

hal_ll_err_t hal_ll_i2c_sci_read_bare_metal( hal_ll_i2c_sci_hw_specifics_map_t *map,
                                                       uint8_t *read_data_buf,
                                                       size_t len_read_data,
                                                       hal_ll_i2c_sci_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = 0xFF;
    uint8_t dummy_read = 0;

    // Configure I2C Master to be in Receiver mode.
    write_reg( &hal_ll_hw_reg->scr, 0 );
    set_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_READ_MASK );

    // Trigger the start condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_READ;
        }
    }

    // Clear ACK flag I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK | \
                    HAL_LL_SCI_SIMR3_IICSCLS_MASK | HAL_LL_SCI_SIMR3_IICSTIF );

    // Send the slave address and write command.
    write_reg( &hal_ll_hw_reg->tdr, ( map->address << 1 ) | 1 );

    // Wait for the address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_READ;
        }
    }

    // Check if address has been acknowledged.
    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_SCI_SISR_IICACKR ) ) {
        // Clear ACK flag.
        clear_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

        // Read all the dummy data from Receive Buffer.
        dummy_read = read_reg( &hal_ll_hw_reg->rdr );

        for( uint8_t i = 0; i < len_read_data - 1; i++ ) {
            // Wait for Receive Buffer to be empty.
            time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_SCI_TIMEOUT_READ;
                }
            }

            // Send 0xFF to trigger clock line and trace incoming data byte.
            write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

            // Wait for data to be written into Receive Buffer.
            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_SCI_TIMEOUT_READ;
                }
            }

            // Read received data.
            read_data_buf[i] = read_reg( &hal_ll_hw_reg->rdr );
        }

        // Enable NACK transmission prior to the reception of the last byte.
        set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

        // Wait for Receive Buffer to be empty.
        time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_I2C_SCI_TIMEOUT_READ;
                }
            }

        // Send 0xFF to trigger clock line and trace incoming data byte.
        write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

        // Wait for data to be written into Receive Buffer.
        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_I2C_SCI_TIMEOUT_READ;
            }
        }

        // Read received data.
        read_data_buf[len_read_data - 1] = read_reg( &hal_ll_hw_reg->rdr );
    }

    // Clear ACK flag and revert I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF | \
                    HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    // Trigger the stop condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_I2C_SCI_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF | \
                    HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    return HAL_LL_I2C_SCI_SUCCESS;
}

void hal_ll_i2c_sci_module_enable( hal_ll_i2c_sci_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef I2C_SCI_MODULE_0
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_1
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_1 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_2
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_2 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_3
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_3 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_4
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_4 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_5
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_5 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_6
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_6 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_7
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_7 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_8
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_8 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS ));
            break;
        #endif
        #ifdef I2C_SCI_MODULE_9
        case ( hal_ll_i2c_module_num( I2C_SCI_MODULE_9 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS ));
            break;
        #endif

        default:
            break;
    }
}

void hal_ll_i2c_sci_init( hal_ll_i2c_sci_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // Enable I2C peripheral
    hal_ll_i2c_sci_module_enable( map, true );

    hal_ll_i2c_sci_alternate_functions_set_state( map, true );

    hal_ll_i2c_sci_hw_init( map );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_i2c_sci_alternate_functions_set_state( hal_ll_i2c_sci_hw_specifics_map_t *map,
                                                             bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[1] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static hal_ll_i2c_sci_hw_specifics_map_t *hal_ll_get_specifics( handle_t handle ) {
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

static void hal_ll_i2c_sci_calculate_speed( hal_ll_i2c_sci_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    uint8_t best_n = -1;
    uint8_t best_N = 0;
    double best_error = 100.0;

    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );

    uint32_t i2c_source_clock = system_clocks.pclka;

    for ( uint8_t i = 0; i < 4; i++ ) {
        double raw_N = ( i2c_source_clock / ( g_div_coefficient[i] * map->speed ) ) - 1;

        uint8_t candidates_N [5];
        uint8_t candidates_count;

        uint8_t raw_N_floor = (uint8_t) floor( raw_N );
        uint8_t raw_N_ceil  = (uint8_t) ceil( raw_N );
        uint8_t raw_N_round = (uint8_t) floor( raw_N + 0.5 );

        candidates_N[candidates_count++] = raw_N_floor;

        if ( raw_N_ceil != raw_N_floor )
            candidates_N[candidates_count++] = raw_N_ceil;

        if ( raw_N_round != raw_N_floor && raw_N_round != raw_N_ceil )
            candidates_N[candidates_count++] = raw_N_round;

        candidates_N[candidates_count++] = raw_N_floor > 1 ? raw_N_floor - 1 : 1;
        candidates_N[candidates_count++] = raw_N_floor + 1;

        for ( uint8_t j = 0; j < candidates_count; j++ ) {
            uint8_t candidate_N = candidates_N[j];

            if ( candidate_N < 0 || candidate_N > 255 )
                continue;

            double real_bps = i2c_source_clock / ( g_div_coefficient[i] * ( (double)candidate_N + 1.0 ) );
            double error = ( real_bps - map->speed ) / map->speed * 100.0;

            if ( fabs( error ) < fabs( best_error ) ) {
                best_n = i;
                best_N = candidate_N;
                best_error = error;
            }
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->smr, 0x3 );
    write_reg( &hal_ll_hw_reg->brr, best_N );
    clear_reg_bit( &hal_ll_hw_reg->semr, 2 );
}

static void hal_ll_i2c_sci_hw_init( hal_ll_i2c_sci_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_i2c_get_base_struct( map->base );

    // Clear Serial Control Register before configuring SCI in I2C master mode.
    clear_reg( &hal_ll_hw_reg->scr );

    // Set the SIMR3.IICSDAS and SIMR3.IICSCLS bits set to 11b to drive the SCLn and SDAn pins to high-impedance state.
    set_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSDAS_MASK );
    set_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    // Clear Serial Mode Register before configuring SCI in I2C master mode.
    clear_reg( &hal_ll_hw_reg->smr );

    // Set the format for transmission.
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SMIF );
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SINV );
    set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SDIR );

    // Set the initial value for Serial Port Register.
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_RINV );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_TINV );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_SPB2IO );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_ASEN );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_ATEN );

    // Calculate I2C speed.
    hal_ll_i2c_sci_calculate_speed( map );

    // Disable Noise Filtering.
    clear_reg_bit( &hal_ll_hw_reg->semr, HAL_LL_SCI_SEMR_NFEN );

    // Configure IIC Mode registers.
    set_reg_bit( &hal_ll_hw_reg->simr1, HAL_LL_SCI_SIMR1_IICM );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICINTM );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICCSC );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

    // Set initial state for I2C to work as transmitter.
    set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
    set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TIE );
    set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TEIE );
}

// ------------------------------------------------------------------------- END