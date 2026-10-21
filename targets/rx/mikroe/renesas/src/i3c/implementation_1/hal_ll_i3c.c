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
 * @file  hal_ll_i3c.c
 * @brief I3C HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_bit_control.h"
#include "hal_ll_gpio.h"
#include "hal_ll_i3c.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS
#define I3C_REG(base, offset)  (*(volatile uint32_t *)((base) + (offset)))

/*!< @brief RI3C register offsets (RX26T Group manual sec. 35.2, RI3C0 base 000E C000h). */
#define HAL_LL_I3C_ICMR_REG_OFFSET       (0x000UL)
#define HAL_LL_I3C_ICCR_REG_OFFSET       (0x014UL)
#define HAL_LL_I3C_ICCAR_REG_OFFSET      (0x018UL)
#define HAL_LL_I3C_ICRCR_REG_OFFSET      (0x020UL)
#define HAL_LL_I3C_ICSBR_REG_OFFSET      (0x074UL)
#define HAL_LL_I3C_ICEBR_REG_OFFSET      (0x078UL)
#define HAL_LL_I3C_ICBFTR_REG_OFFSET     (0x07CUL)
#define HAL_LL_I3C_ICBATR_REG_OFFSET     (0x080UL)
#define HAL_LL_I3C_ICBITR_REG_OFFSET     (0x084UL)
#define HAL_LL_I3C_ICCQR_REG_OFFSET      (0x150UL)
#define HAL_LL_I3C_ICRQR_REG_OFFSET      (0x154UL)
#define HAL_LL_I3C_ICDR_REG_OFFSET       (0x158UL)
#define HAL_LL_I3C_ICQBTCR_REG_OFFSET    (0x190UL)
#define HAL_LL_I3C_ICDBTCR_REG_OFFSET    (0x194UL)
#define HAL_LL_I3C_ICBSR_REG_OFFSET      (0x210UL)
#define HAL_LL_I3C_ICTDATR0_REG_OFFSET   (0x224UL)
#define HAL_LL_I3C_ICQBSR_REG_OFFSET     (0x394UL)
#define HAL_LL_I3C_ICDBSR_REG_OFFSET     (0x398UL)

/*!< @brief Macros defining bit location. */
#define HAL_LL_I3C_ICMR_OMS           (0)
#define HAL_LL_I3C_ICCR_RESUME        (30)
#define HAL_LL_I3C_ICCR_ICE           (31)
#define HAL_LL_I3C_ICCAR_DAV          (31)
#define HAL_LL_I3C_ICCAR_DADR         (16)
#define HAL_LL_I3C_ICRCR_MRST         (0)
#define HAL_LL_I3C_ICBSR_BFREE        (0)
#define HAL_LL_I3C_ICTDATR_TYPE       (31)
#define HAL_LL_I3C_ICQBTCR_IDSS       (16)
#define HAL_LL_I3C_BR_ODDBL           (31)
#define HAL_LL_I3C_BR_PPHW            (24)
#define HAL_LL_I3C_BR_PPLW            (16)
#define HAL_LL_I3C_BR_ODHW            (8)

/*!< @brief Masks for the queue/buffer status registers. */
#define HAL_LL_I3C_ICQBSR_CQFL_MASK   (0x000000FFUL)
#define HAL_LL_I3C_ICQBSR_RQFL_MASK   (0x0000FF00UL)
#define HAL_LL_I3C_ICDBSR_TBFL_MASK   (0x000000FFUL)
#define HAL_LL_I3C_ICDBSR_RBFL_MASK   (0x0000FF00UL)
#define HAL_LL_I3C_ICTDATR_SADR_MASK  (0x7FUL)

/*!< @brief Bit-rate register limits. */
#define HAL_LL_I3C_BR_OD_MAX          (0xFFUL)
#define HAL_LL_I3C_BR_PP_DEFAULT      (0x3FUL)
#define HAL_LL_I3C_ICBFTR_MAX         (0x1FEUL)
#define HAL_LL_I3C_ICBITR_MASK        (0x3FFFFUL)

/*!< @brief Command Descriptor fields (manual sec. 35.3.1). */
#define HAL_LL_I3C_CMD_ATTR_REGULAR   (0UL)
#define HAL_LL_I3C_CMD_ATTR_IMMEDIATE (1UL)
#define HAL_LL_I3C_CMD_TID            (3)
#define HAL_LL_I3C_CMD_BYTE_CNT       (23)
#define HAL_LL_I3C_CMD_MODE           (26)
#define HAL_LL_I3C_CMD_RNW            (29)
#define HAL_LL_I3C_CMD_ROC            (30)
#define HAL_LL_I3C_CMD_TOC            (31)
#define HAL_LL_I3C_CMD_DATA_LENGTH    (16)
#define HAL_LL_I3C_CMD_MODE_I2C_FM    (0UL) /* ICSBR register setting */
#define HAL_LL_I3C_CMD_MODE_I2C_FMP   (1UL) /* ICEBR register setting */
#define HAL_LL_I3C_CMD_IMMEDIATE_MAX  (4)

/*!< @brief Response Descriptor fields (manual sec. 35.3.2). */
#define HAL_LL_I3C_RESP_TID           (24)
#define HAL_LL_I3C_RESP_TID_MASK      (0xFUL)
#define HAL_LL_I3C_RESP_ERR_MASK      (0xF0000000UL)

/*!< @brief Transaction IDs used to match responses with commands. */
#define HAL_LL_I3C_TID_WRITE          (1UL)
#define HAL_LL_I3C_TID_READ           (2UL)

/*!< @brief Transmit data buffer is 2 stages of 4 bytes (manual table 35.5). */
#define HAL_LL_I3C_TX_BUFFER_SIZE     (8)

/*!< @brief Dynamic address RI3C self-assigns as the Active Controller. */
#define HAL_LL_I3C_OWN_DYNAMIC_ADDRESS (0x08UL)

#define HAL_LL_I3C_AF_CONFIG (GPIO_CFG_PORT_PULL_UP_ENABLE |\
                              GPIO_CFG_DIGITAL_OUTPUT |\
                              GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE)

// RI3C is clocked from PCLKA -- matches the PCLKA value assumed by hal_ll_spi_master.c.
#define HAL_LL_I3C_MCU_CLOCK_HZ         (120000000UL) /* TODO: verify against the actual board clock config */

#define HAL_LL_I3C_MASTER_SPEED_100K    (100000UL)
#define HAL_LL_I3C_MASTER_SPEED_400K    (400000UL)

/* I2C spec minimums (ns) per mode from the official I2C specification and user manual
 * https://www.nxp.com/docs/en/user-guide/UM10204.pdf
 */
typedef struct {
    uint32_t th;
    uint32_t tl;
    uint32_t tr;
    uint32_t tf;
} i2c_spec_t;

static const i2c_spec_t i2c_nxp_specifications[] = {
    { 4000, 4700, 1000, 300  },  /* Sm  <= 100 kbps */
    { 600,  1300, 300,  300  },  /* Fm  <= 400 kbps */
    { 260,  500,  120,  120  },  /* Fm+ <= 1000 kbps */
};

#define HAL_LL_I3C_PS_PER_SECOND (1000000000000ULL)

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_I3C_SUCCESS = 0,
    HAL_LL_I3C_WRONG_PINS,
    HAL_LL_I3C_MODULE_ERROR,

    HAL_LL_I3C_ERROR = (-1)
} hal_ll_i3c_err_t;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Initialize I3C module in I2C Master mode on hardware level.
  *
  * Initializes I3C module in I2C Master mode on hardware level,
  * based on beforehand set configuration and module handler.
  * Also used to recover the module, as any transfer error halts RI3C.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i3c_i2c_hw_init( hal_ll_i3c_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets I3C pin alternate function state to work in I2C Master mode.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if I3C is to work in I2C Master mode.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_i3c_i2c_alternate_functions_set_state( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state );

/**
  * @brief  Set I3C speed registers based on clock and requested bit rate.
  *
  * Calculates and sets the open-drain SCL high/low widths in ICSBR
  * (Fm and below) or ICEBR (Fm+), and the bus condition timings,
  * based on the PCLKA clock and desired speed.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_i3c_i2c_calculate_speed( hal_ll_i3c_i2c_hw_specifics_map_t *map );

/**
  * @brief  Get MODE field of the Command Descriptor for the current speed.
  *
  * @param[in]  *map - Object specific context handler.
  * @return uint32_t MODE field value, shifted into place.
  */
static uint32_t hal_ll_i3c_i2c_get_mode( hal_ll_i3c_i2c_hw_specifics_map_t *map );

/**
  * @brief  Pack up to 4 bytes into one little-endian 32-bit word.
  *
  * @param[in]      *data_buf - Data buffer.
  * @param[in,out]  *index    - Current buffer index, advanced by the packed byte count.
  * @param[in]      len       - Buffer length.
  * @return uint32_t Packed word.
  */
static uint32_t hal_ll_i3c_i2c_pack_word( uint8_t *data_buf, size_t *index, size_t len );

/**
  * @brief  Write a Command Descriptor to the command queue.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  command_low  - Lower 32 bits of the Command Descriptor.
  * @param[in]  command_high - Upper 32 bits of the Command Descriptor.
  * @return hal_ll_err_t HAL_LL_I3C_SUCCESS or HAL_LL_I3C_ERROR on timeout.
  */
static hal_ll_err_t hal_ll_i3c_i2c_write_command( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                  uint32_t command_low,
                                                  uint32_t command_high );

/**
  * @brief  Wait for the Response Descriptor of the given transaction.
  *
  * Pops Response Descriptors until the one with matching TID is found.
  * On any error status or timeout the module is re-initialized.
  *
  * @param[in]  *map  - Object specific context handler.
  * @param[in]  tid   - Transaction ID to wait for.
  * @param[in]  error - Error value to return on failure.
  * @return hal_ll_err_t HAL_LL_I3C_SUCCESS or error.
  */
static hal_ll_err_t hal_ll_i3c_i2c_wait_response( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                  uint32_t tid,
                                                  hal_ll_err_t error );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i3c_i2c_write_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_i3c_i2c_end_mode_t mode ) {
    uint16_t time_counter = map->timeout;
    uint32_t command = ( HAL_LL_I3C_TID_WRITE << HAL_LL_I3C_CMD_TID ) |
                       ( 1UL << HAL_LL_I3C_CMD_ROC ) |
                       hal_ll_i3c_i2c_get_mode( map );
    uint32_t data_word;
    size_t index = 0;

    // Keep the bus with a repeated START condition when a read follows.
    if ( HAL_LL_I3C_I2C_WRITE_THEN_READ != mode )
        command |= ( 1UL << HAL_LL_I3C_CMD_TOC );

    // Bus free detection flag
    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICBSR_REG_OFFSET ), HAL_LL_I3C_ICBSR_BFREE )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
            }
        }
    }

    // Set slave address as a legacy I2C device in DAT entry 0
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICTDATR0_REG_OFFSET ),
               ( 1UL << HAL_LL_I3C_ICTDATR_TYPE ) | ( map->address & HAL_LL_I3C_ICTDATR_SADR_MASK ) );

    if ( HAL_LL_I3C_CMD_IMMEDIATE_MAX >= len_write_data ) {
        // Short writes carry the data inside the Command Descriptor itself.
        command |= HAL_LL_I3C_CMD_ATTR_IMMEDIATE | ( len_write_data << HAL_LL_I3C_CMD_BYTE_CNT );
        data_word = hal_ll_i3c_i2c_pack_word( write_data_buf, &index, len_write_data );

        if ( HAL_LL_I3C_SUCCESS != hal_ll_i3c_i2c_write_command( map, command, data_word )) {
            hal_ll_i3c_i2c_hw_init( map );
            return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
        }
    } else {
        // Transmission starts once 2 stages of the transmit buffer are filled, so fill it beforehand.
        while (( index < len_write_data ) && ( HAL_LL_I3C_TX_BUFFER_SIZE > index ))
            write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICDR_REG_OFFSET ),
                       hal_ll_i3c_i2c_pack_word( write_data_buf, &index, len_write_data ));

        if ( HAL_LL_I3C_SUCCESS != hal_ll_i3c_i2c_write_command( map, command | HAL_LL_I3C_CMD_ATTR_REGULAR,
                                                                  len_write_data << HAL_LL_I3C_CMD_DATA_LENGTH )) {
            hal_ll_i3c_i2c_hw_init( map );
            return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
        }

        // Feed the rest of the data; SCL is stalled while the transmit buffer is empty.
        time_counter = map->timeout;
        while ( index < len_write_data ) {
            // RI3C halts on any transfer error (e.g. NACK), error is read from the response.
            if ( check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICCR_REG_OFFSET ), HAL_LL_I3C_ICCR_RESUME ))
                break;

            if ( read_reg( &I3C_REG( map->base, HAL_LL_I3C_ICDBSR_REG_OFFSET )) & HAL_LL_I3C_ICDBSR_TBFL_MASK ) {
                write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICDR_REG_OFFSET ),
                           hal_ll_i3c_i2c_pack_word( write_data_buf, &index, len_write_data ));
                time_counter = map->timeout;
            } else if( map->timeout ) {
                if( !time_counter-- ) {
                    hal_ll_i3c_i2c_hw_init( map );
                    return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
                }
            }
        }
    }

    // On a repeated START the response is collected together with the read one.
    if (( HAL_LL_I3C_I2C_WRITE_THEN_READ == mode ) &&
        !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICCR_REG_OFFSET ), HAL_LL_I3C_ICCR_RESUME ))
        return HAL_LL_I3C_SUCCESS;

    return hal_ll_i3c_i2c_wait_response( map, HAL_LL_I3C_TID_WRITE, HAL_LL_I3C_I2C_TIMEOUT_WRITE );
}

hal_ll_err_t hal_ll_i3c_i2c_read_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                             uint8_t *read_data_buf,
                                             size_t len_read_data,
                                             hal_ll_i3c_i2c_end_mode_t mode ) {
    uint16_t time_counter = map->timeout;
    uint32_t command = HAL_LL_I3C_CMD_ATTR_REGULAR |
                       ( HAL_LL_I3C_TID_READ << HAL_LL_I3C_CMD_TID ) |
                       ( 1UL << HAL_LL_I3C_CMD_RNW ) |
                       ( 1UL << HAL_LL_I3C_CMD_ROC ) |
                       ( 1UL << HAL_LL_I3C_CMD_TOC ) |
                       hal_ll_i3c_i2c_get_mode( map );
    uint32_t data_word;
    size_t index = 0;

    if ( mode != HAL_LL_I3C_I2C_WRITE_THEN_READ ) {
        // Bus free detection flag -- skipped when coming from a Repeated START
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICBSR_REG_OFFSET ), HAL_LL_I3C_ICBSR_BFREE )) {
            if( map->timeout ) {
                if( !time_counter-- ) {
                    return HAL_LL_I3C_I2C_TIMEOUT_READ;
                }
            }
        }

        // Set slave address as a legacy I2C device in DAT entry 0 -- already set by the preceding write otherwise
        write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICTDATR0_REG_OFFSET ),
                   ( 1UL << HAL_LL_I3C_ICTDATR_TYPE ) | ( map->address & HAL_LL_I3C_ICTDATR_SADR_MASK ) );
    }

    if ( HAL_LL_I3C_SUCCESS != hal_ll_i3c_i2c_write_command( map, command,
                                                              len_read_data << HAL_LL_I3C_CMD_DATA_LENGTH )) {
        hal_ll_i3c_i2c_hw_init( map );
        return HAL_LL_I3C_I2C_TIMEOUT_READ;
    }

    // Receive data; SCL is stalled while the receive buffer is full. NACK on the last byte is automatic.
    time_counter = map->timeout;
    while ( index < len_read_data ) {
        if ( read_reg( &I3C_REG( map->base, HAL_LL_I3C_ICDBSR_REG_OFFSET )) & HAL_LL_I3C_ICDBSR_RBFL_MASK ) {
            data_word = read_reg( &I3C_REG( map->base, HAL_LL_I3C_ICDR_REG_OFFSET ));
            for ( uint8_t shift = 0; ( shift < 32 ) && ( index < len_read_data ); shift += 8 )
                read_data_buf[index++] = ( uint8_t )( data_word >> shift );
            time_counter = map->timeout;
        } else if ( check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICCR_REG_OFFSET ), HAL_LL_I3C_ICCR_RESUME )) {
            // RI3C halts on any transfer error (e.g. NACK), error is read from the response.
            break;
        } else if( map->timeout ) {
            if( !time_counter-- ) {
                hal_ll_i3c_i2c_hw_init( map );
                return HAL_LL_I3C_I2C_TIMEOUT_READ;
            }
        }
    }

    // Also collects the response of a preceding write with Repeated START, if still pending.
    return hal_ll_i3c_i2c_wait_response( map, HAL_LL_I3C_TID_READ, HAL_LL_I3C_I2C_TIMEOUT_READ );
}

void hal_ll_i3c_module_enable( hal_ll_i3c_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    volatile uint16_t *prcr = ( uint16_t * )HAL_LL_MSTPCR_PRCR_ADDR;
    write_reg( prcr, HAL_LL_MSTPCR_PRCR_UNLOCK_VAL );

    #ifdef I3C_MODULE_0
    if ( hal_ll_i3c_module_num( I3C_MODULE_0 ) == map->module_index ) {
        hal_ll_state ? clear_reg_bit( _MSTPCRD, MSTPCRD_MSTPD5_POS ) : set_reg_bit( _MSTPCRD, MSTPCRD_MSTPD5_POS );
    }
    #endif

    write_reg( prcr, HAL_LL_MSTPCR_PRCR_LOCK_VAL );
}

void hal_ll_i3c_i2c_init( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    // Enable I3C peripheral
    hal_ll_i3c_module_enable( map, true );

    hal_ll_i3c_i2c_alternate_functions_set_state( map, true );

    hal_ll_i3c_i2c_hw_init( map );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_i3c_i2c_alternate_functions_set_state( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_I3C_AF_CONFIG;
        module.configs[1] = HAL_LL_I3C_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static uint32_t hal_ll_i3c_i2c_get_mode( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    return (( map->speed <= HAL_LL_I3C_MASTER_SPEED_400K ) ? HAL_LL_I3C_CMD_MODE_I2C_FM :
                                                             HAL_LL_I3C_CMD_MODE_I2C_FMP ) << HAL_LL_I3C_CMD_MODE;
}

static uint32_t hal_ll_i3c_i2c_pack_word( uint8_t *data_buf, size_t *index, size_t len ) {
    uint32_t data_word = 0;

    // First byte goes out first, i.e. from the least significant byte.
    for ( uint8_t shift = 0; ( shift < 32 ) && ( *index < len ); shift += 8 )
        data_word |= ( uint32_t )data_buf[( *index )++] << shift;

    return data_word;
}

static hal_ll_err_t hal_ll_i3c_i2c_write_command( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                  uint32_t command_low,
                                                  uint32_t command_high ) {
    uint16_t time_counter = map->timeout;

    // Wait for a free command queue entry
    while ( !( read_reg( &I3C_REG( map->base, HAL_LL_I3C_ICQBSR_REG_OFFSET )) & HAL_LL_I3C_ICQBSR_CQFL_MASK )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                return HAL_LL_I3C_ERROR;
            }
        }
    }

    // Lower 32 bits first, the transfer is issued once the upper 32 bits are written.
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICCQR_REG_OFFSET ), command_low );
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICCQR_REG_OFFSET ), command_high );

    return HAL_LL_I3C_SUCCESS;
}

static hal_ll_err_t hal_ll_i3c_i2c_wait_response( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                                  uint32_t tid,
                                                  hal_ll_err_t error ) {
    uint16_t time_counter;
    uint32_t response;

    do {
        time_counter = map->timeout;
        while ( !( read_reg( &I3C_REG( map->base, HAL_LL_I3C_ICQBSR_REG_OFFSET )) & HAL_LL_I3C_ICQBSR_RQFL_MASK )) {
            if( map->timeout ) {
                if( !time_counter-- ) {
                    hal_ll_i3c_i2c_hw_init( map );
                    return error;
                }
            }
        }

        response = read_reg( &I3C_REG( map->base, HAL_LL_I3C_ICRQR_REG_OFFSET ));

        // Any error (address NACK, data NACK, ...) leaves RI3C halted -- reset it.
        if ( response & HAL_LL_I3C_RESP_ERR_MASK ) {
            hal_ll_i3c_i2c_hw_init( map );
            return error;
        }
    } while ( tid != (( response >> HAL_LL_I3C_RESP_TID ) & HAL_LL_I3C_RESP_TID_MASK ));

    return HAL_LL_I3C_SUCCESS;
}

static void hal_ll_i3c_i2c_calculate_speed( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    uint8_t double_period = 0;
    uint32_t high_cycles, low_cycles, bus_free_cycles;

    const i2c_spec_t *i2c_specs = ( map->speed <= 100000 ) ? &i2c_nxp_specifications[0] :
                                  ( map->speed <= 400000 ) ? &i2c_nxp_specifications[1] :
                                                             &i2c_nxp_specifications[2];

    uint32_t tbuf_ns = ( map->speed <= 100000 ) ? 4700 :
                       ( map->speed <= 400000 ) ? 1300 :
                                                  500;

    uint64_t clock_period_ps  = HAL_LL_I3C_PS_PER_SECOND / HAL_LL_I3C_MCU_CLOCK_HZ;
    uint64_t target_period_ps = HAL_LL_I3C_PS_PER_SECOND / map->speed;
    uint64_t budget_ps        = target_period_ps - ( ( uint64_t )( i2c_specs->tr + i2c_specs->tf ) * 1000ULL );

    // tLOW = ODLW / PCLKA, tHIGH = ODHW / PCLKA, rate = 1 / ( tLOW + tHIGH + tr + tf )
    high_cycles = ( uint32_t )( ( ( uint64_t )i2c_specs->th * 1000ULL + clock_period_ps - 1 ) / clock_period_ps );
    low_cycles  = ( uint32_t )( ( ( uint64_t )i2c_specs->tl * 1000ULL + clock_period_ps - 1 ) / clock_period_ps );

    if ( ( high_cycles + low_cycles ) * clock_period_ps <= budget_ps )
        low_cycles += ( uint32_t )( ( budget_ps - ( high_cycles + low_cycles ) * clock_period_ps ) / clock_period_ps );

    if ( map->speed <= HAL_LL_I3C_MASTER_SPEED_400K ) {
        // Only ICSBR can double the open-drain widths
        if ( high_cycles > HAL_LL_I3C_BR_OD_MAX || low_cycles > HAL_LL_I3C_BR_OD_MAX ) {
            high_cycles = ( high_cycles + 1 ) / 2;
            low_cycles = ( low_cycles + 1 ) / 2;
            double_period = 1;
        }
    }

    // Saturate to the register width (e.g. Sm tLOW can't be reached with PCLKA = 120MHz).
    if ( high_cycles > HAL_LL_I3C_BR_OD_MAX )
        high_cycles = HAL_LL_I3C_BR_OD_MAX;
    if ( low_cycles > HAL_LL_I3C_BR_OD_MAX )
        low_cycles = HAL_LL_I3C_BR_OD_MAX;

    // Push-pull widths are not used by legacy I2C transfers, keep their reset values.
    write_reg( &I3C_REG( map->base, ( map->speed <= HAL_LL_I3C_MASTER_SPEED_400K ) ?
                                    HAL_LL_I3C_ICSBR_REG_OFFSET : HAL_LL_I3C_ICEBR_REG_OFFSET ),
               ( ( uint32_t )double_period << HAL_LL_I3C_BR_ODDBL ) |
               ( HAL_LL_I3C_BR_PP_DEFAULT << HAL_LL_I3C_BR_PPHW ) |
               ( HAL_LL_I3C_BR_PP_DEFAULT << HAL_LL_I3C_BR_PPLW ) |
               ( high_cycles << HAL_LL_I3C_BR_ODHW ) |
               low_cycles );

    // Bus conditions must satisfy ICBFTR < ICBATR < ICBITR
    bus_free_cycles = ( uint32_t )( ( tbuf_ns * 1000ULL + clock_period_ps - 1 ) / clock_period_ps );
    if ( bus_free_cycles > HAL_LL_I3C_ICBFTR_MAX )
        bus_free_cycles = HAL_LL_I3C_ICBFTR_MAX;

    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICBFTR_REG_OFFSET ), bus_free_cycles );
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICBATR_REG_OFFSET ), bus_free_cycles + 1 );
    // Bus idle time of 1ms
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICBITR_REG_OFFSET ),
               ( HAL_LL_I3C_MCU_CLOCK_HZ / 1000UL ) & HAL_LL_I3C_ICBITR_MASK );
}

static void hal_ll_i3c_i2c_hw_init( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    // Disable I3C bus operation
    clear_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICCR_REG_OFFSET ), HAL_LL_I3C_ICCR_ICE );
    // Reset I3C module -- also releases it from the Halt state and flushes all queues and buffers
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICRCR_REG_OFFSET ), HAL_LL_I3C_ICRCR_MRST );

    while ( check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICRCR_REG_OFFSET ), HAL_LL_I3C_ICRCR_MRST ) ) {
        // Wait for module reset to complete
    }

    // Set operating mode
    clear_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICMR_REG_OFFSET ), HAL_LL_I3C_ICMR_OMS );

    // Self-assign a Dynamic Address so that RI3C acts as the Primary (Active) Controller
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICCAR_REG_OFFSET ),
               ( 1UL << HAL_LL_I3C_ICCAR_DAV ) | ( HAL_LL_I3C_OWN_DYNAMIC_ADDRESS << HAL_LL_I3C_ICCAR_DADR ) );

    // DAT entry 0 holds the slave as a legacy I2C device
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICTDATR0_REG_OFFSET ),
               ( 1UL << HAL_LL_I3C_ICTDATR_TYPE ) | ( map->address & HAL_LL_I3C_ICTDATR_SADR_MASK ) );

    // Set bitrate and bus condition timings
    hal_ll_i3c_i2c_calculate_speed( map );

    // Queue thresholds: command queue completely empty, one response entry, IBI data segment of 4 bytes
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_ICQBTCR_REG_OFFSET ), 1UL << HAL_LL_I3C_ICQBTCR_IDSS );
    // Data buffer thresholds: only 000b is allowed for all fields
    clear_reg( &I3C_REG( map->base, HAL_LL_I3C_ICDBTCR_REG_OFFSET ) );

    // Start I3C bus operation
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ICCR_REG_OFFSET ), HAL_LL_I3C_ICCR_ICE );
}

// ------------------------------------------------------------------------- END
