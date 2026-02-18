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
 * @file  hal_ll_sci.c
 * @brief UART HAL LOW LEVEL layer implementation.
 */

#include <math.h>
#include "hal_ll_gpio.h"
#include "hal_ll_sci.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_sci_get_base_struct(_handle) ((hal_ll_sci_base_handle_t *)_handle)

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_CCR0_TE              (4)
#define HAL_LL_SCI_CCR0_TIE             (20)
#define HAL_LL_SCI_CCR0_TEIE            (21)

#define HAL_LL_SCI_CCR1_PE              (8)
#define HAL_LL_SCI_CCR1_PM              (9)
#define HAL_LL_SCI_CCR1_TINV            (12)
#define HAL_LL_SCI_CCR1_RINV            (13)

#define HAL_LL_CCR2_BRR_OFFSET          (8)
#define HAL_LL_CCR2_CKS_OFFSET          (20)

#define HAL_LL_SCI_CCR3_CPHA            (0)
#define HAL_LL_SCI_CCR3_CPOL            (1)
#define HAL_LL_SCI_CCR3_LSBF            (12)
#define HAL_LL_SCI_CCR3_SINV            (13)
#define HAL_LL_SCI_CCR3_FM              (20)

#define HAL_LL_SCI_CSR_ORER             (24)
#define HAL_LL_SCI_CSR_TDRE             (29)
#define HAL_LL_SCI_CSR_TEND             (30)
#define HAL_LL_SCI_CSR_RDRF             (31)

#define HAL_LL_SCI_ICR_IICINTM          (8)
#define HAL_LL_SCI_ICR_IICCSC           (9)
#define HAL_LL_SCI_ICR_IICACKT          (13)

#define HAL_LL_SCI_ISR_IICACKR          (0)
#define HAL_LL_SCI_ISR_IICSTIF          (3)

#define HAL_LL_SCI_CFCLR_ORERC          (24)

#define HAL_LL_SCI_ICFCLR_IICSTIFC      (3)

/*!< @brief Macros defining bit masks. */
#define HAL_LL_SCI_CCR0_READ_MASK       (0x300011)

#define HAL_LL_SCI_CCR3_MOD_SPI_MASK    (0x30000)
#define HAL_LL_SCI_CCR3_MOD_IIC_MASK    (0x40000)
#define HAL_LL_SCI_CCR3_CKE_MASK        (0x3000000)

#define HAL_LL_SCI_ICR_START_MASK       (0x510000)
#define HAL_LL_SCI_ICR_STOP_MASK        (0x540000)
#define HAL_LL_SCI_ICR_IICSDAS_MASK     (0x300000)
#define HAL_LL_SCI_ICR_IICSCLS_MASK     (0xC00000)
#define HAL_LL_SCI_CFCLR_MASK           (0x9D070010)

/*!< @brief I2C register structure */
typedef struct {
    uint32_t rdr;        /* Receive Data Register (RDR / RDR_BY overlay) */
    uint32_t tdr;        /* Transmit Data Register (TDR / TDR_BY overlay) */
    uint32_t ccr0;
    uint32_t ccr1;
    uint32_t ccr2;
    uint32_t ccr3;
    uint32_t ccr4;
    uint8_t  cesr;
    uint8_t  _unused;
    uint16_t _unused1;
    uint32_t icr;
    uint32_t fcr;
    uint32_t _unused2;
    uint32_t mcr;
    uint32_t dcr;
    uint32_t xcr0;
    uint32_t xcr1;
    uint32_t xcr2;
    uint32_t _unused3[2];
    uint32_t csr;
    uint32_t isr;
    uint32_t frsr;
    uint32_t ftsr;
    uint32_t msr;
    uint32_t xsr0;
    uint32_t xsr1;
    uint32_t _unused4;
    uint32_t cfclr;
    uint32_t icfclr;
    uint32_t ffclr;
    uint32_t mfclr;
    uint32_t xfclr;
} hal_ll_sci_base_handle_t;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_SCI_SUCCESS = 0,
    HAL_LL_SCI_WRONG_PINS,
    HAL_LL_SCI_MODULE_ERROR,

    HAL_LL_SCI_ERROR = (-1)
} hal_ll_sci_err_t;

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
static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets SCI pin alternate function state to work in I2C Master mode.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if SCI is to work in I2C Master mode.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_sci_i2c_alternate_functions_set_state( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state );

/**
  * @brief  Sets SCI pin alternate function state to work in SPI Master mode.
  *
  * Sets adequate value for alternate function settings.
  * This function must be called if SCI is to work in SPI Master mode.
  * Based on value of hal_ll_state, alternate functions can be
  * set or cleared.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  *
  * @return  None
  */
static void hal_ll_sci_spi_alternate_functions_set_state( hal_ll_sci_spi_hw_specifics_map_t *map,
                                                          bool hal_ll_state );

/**
  * @brief  Initialize SCI module in SPI Master mode on hardware level.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_sci_spi_hw_init( hal_ll_sci_spi_hw_specifics_map_t *map );

/**
  * @brief  Set SCI speed registers based on clock and requested bit rate.
  *
  * Calculates and sets the SCI bit rate by configuring the SPBR register,
  * based on the PCLK clock and desired speed.
  *
  * @param[in]  base     Base address for the module in use.
  * @param[in]  speed    Requested bitrate value.
  * @param[in]  sci_mode SCI mode in use.
  * @return None
  */
static void hal_ll_sci_calculate_speed( uint32_t base, uint32_t speed, hal_ll_sci_mode_t sci_mode );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS

hal_ll_err_t hal_ll_sci_i2c_write_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_sci_i2c_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    // Wait for all previous transmissions to be ended.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    // Trigger the start condition.
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_START_MASK );

    // Wait for completion of start condition.
    while( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear condition status flag and revert I2C into default state.
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSCLS_MASK );

    // Send the slave address and write command.
    write_reg( &hal_ll_hw_reg->tdr, map->address << 1 );

    // Wait for the slave address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    // Check for ACK signal.
    if ( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICACKR ) ) {
        for( uint8_t i = 0; i < len_write_data; i++ ) {
            write_reg( &hal_ll_hw_reg->tdr, write_data_buf[i] );

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
                }
            }
        }
    }

    // Trigger the stop condition.
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_STOP_MASK );

    // Wait for completion of stop condition.
    while( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear condition status flag and revert I2C into default state.
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSCLS_MASK );

    return HAL_LL_SCI_SUCCESS;
}

hal_ll_err_t hal_ll_sci_i2c_read_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                             uint8_t *read_data_buf,
                                             size_t len_read_data,
                                             hal_ll_sci_i2c_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = 0xFF;
    uint8_t dummy_read = 0;

    // Configure I2C Master to be in Receiver mode.
    write_reg( &hal_ll_hw_reg->ccr0, 0 );
    set_reg_bits( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_READ_MASK );

    // Trigger the start condition.
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_START_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK |\
                                            HAL_LL_SCI_ICR_IICSCLS_MASK );

    // Send the slave address and write command.
    write_reg( &hal_ll_hw_reg->tdr, ( map->address << 1 ) | 1 );

    // Wait for the address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Check if address has been acknowledged.
    if ( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICACKR ) ) {
        // Clear ACK flag.
        clear_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICACKT );

        // Read all the dummy data from Receive Buffer.
        dummy_read = read_reg( &hal_ll_hw_reg->rdr );

        for( uint8_t i = 0; i < len_read_data - 1; i++ ) {
            // Wait for Receive Buffer to be empty.
            time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_READ;
                }
            }

            // Send 0xFF to trigger clock line and trace incoming data byte.
            write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

            // Wait for data to be written into Receive Buffer.
            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_READ;
                }
            }

            // Read received data.
            read_data_buf[i] = read_reg( &hal_ll_hw_reg->rdr );
        }

        // Enable NACK transmission prior to the reception of the last byte.
        set_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICACKT );

        // Wait for Receive Buffer to be empty.
        time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_READ;
                }
            }

        // Send 0xFF to trigger clock line and trace incoming data byte.
        write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

        // Wait for data to be written into Receive Buffer.
        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_SCI_I2C_TIMEOUT_READ;
            }
        }

        // Read received data.
        read_data_buf[len_read_data - 1] = read_reg( &hal_ll_hw_reg->rdr );
    }

    // Clear ACK flag and revert I2C into default state.
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK |\
                                            HAL_LL_SCI_ICR_IICSCLS_MASK );

    // Trigger the stop condition.
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_STOP_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    set_reg_bit(  &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK |\
                                            HAL_LL_SCI_ICR_IICSCLS_MASK );

    return HAL_LL_SCI_SUCCESS;
}

void hal_ll_sci_spi_write_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                      uint8_t *write_data_buffer,
                                      size_t write_data_length ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    while ( 0 < write_data_length-- ) {
        if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->cfclr, HAL_LL_SCI_CFCLR_ORERC );

        // Wait until transmit buffer is empty.
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE ));

        // Send byte from write buffer.
        write_reg( &hal_ll_hw_reg->tdr, ( uint8_t )( *write_data_buffer++ ) );

        // Wait until transmit is complete.
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND ));

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF ));

        // Dummy read
        volatile uint8_t temp = read_reg( &hal_ll_hw_reg->rdr );
    }
}

void hal_ll_sci_spi_read_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                     uint8_t *read_data_buffer, size_t read_data_length,
                                     uint8_t dummy_data ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    while ( 0 < read_data_length-- ) {
        if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->cfclr, HAL_LL_SCI_CFCLR_ORERC );

        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE ));

        // Send dummy data
        write_reg( &hal_ll_hw_reg->tdr, dummy_data );

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF ));

        // Read received byte and store if read buffer is provided
        *read_data_buffer++ = read_reg( &hal_ll_hw_reg->rdr );
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND ));
}

void hal_ll_sci_spi_transfer_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                         uint8_t *write_data_buffer,
                                         uint8_t *read_data_buffer,
                                         size_t data_length ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    while ( 0 < data_length-- ) {
        if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->cfclr, HAL_LL_SCI_CFCLR_ORERC );

        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE ));

        // Send byte from write buffer or dummy if NULL
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : 0xFF;
        write_reg( &hal_ll_hw_reg->tdr, tx_data );

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF ));

        // Read received byte and store if read buffer is provided
        uint8_t rx_data = read_reg( &hal_ll_hw_reg->rdr );
        if ( read_data_buffer ) {
            *read_data_buffer++ = rx_data;
        }
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND ));
}

void hal_ll_sci_module_enable( hal_ll_sci_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    if ( hal_ll_state )
        clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS - map->module_index );
    else
        set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS - map->module_index );
}

void hal_ll_sci_i2c_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    // Enable SCI peripheral
    hal_ll_sci_module_enable( map, true );

    hal_ll_sci_i2c_alternate_functions_set_state( map, true );

    hal_ll_sci_i2c_hw_init( map );
}

void hal_ll_sci_spi_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {

    hal_ll_sci_module_enable( map, true );

    hal_ll_sci_spi_alternate_functions_set_state( map, true );

    hal_ll_sci_spi_hw_init( map );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_sci_i2c_alternate_functions_set_state( hal_ll_sci_i2c_hw_specifics_map_t *map,
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

static void hal_ll_sci_spi_alternate_functions_set_state( hal_ll_sci_spi_hw_specifics_map_t *map,
                                                          bool hal_ll_state ) {
    module_struct module;

    if((map->pins.sck.pin_name != HAL_LL_PIN_NC) &&
       (map->pins.miso.pin_name != HAL_LL_PIN_NC) &&
       (map->pins.miso.pin_name != HAL_LL_PIN_NC)) {

        module.pins[0] = VALUE(map->pins.sck.pin_name, map->pins.sck.pin_af);
        module.pins[1] = VALUE(map->pins.miso.pin_name, map->pins.miso.pin_af);
        module.pins[2] = VALUE(map->pins.mosi.pin_name, map->pins.mosi.pin_af);
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_PORT_PULL_UP_ENABLE | GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN;
        module.configs[1] = GPIO_CFG_DIGITAL_INPUT | GPIO_CFG_PERIPHERAL_PIN;
        module.configs[2] = GPIO_CFG_PORT_PULL_UP_ENABLE | GPIO_CFG_DIGITAL_OUTPUT | GPIO_CFG_PERIPHERAL_PIN;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        module.gpio_remap = map->pins.sck.pin_af;

        hal_ll_gpio_module_struct_init(&module, hal_ll_state);
    }
}

static void hal_ll_sci_calculate_speed( uint32_t base, uint32_t speed, hal_ll_sci_mode_t sci_mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    uint8_t best_cks = 0, best_brr = 0;
    double best_error = 100.0;

    system_clocks_t system_clocks;
    SYSTEM_GetClocksFrequency( &system_clocks );

    // Baud rate divisor information structure.
    uint16_t g_div_coefficient[4];

    if ( HAL_LL_SCI_I2C_MODE == sci_mode ) {
        g_div_coefficient[0] = 32U;
        g_div_coefficient[1] = 128U;
        g_div_coefficient[2] = 512U;
        g_div_coefficient[3] = 2048U;
    } else {
        g_div_coefficient[0] = 4U;
        g_div_coefficient[1] = 16U;
        g_div_coefficient[2] = 64U;
        g_div_coefficient[3] = 256U;
    }

    #if (defined(R7FA4M1) || defined(R7FA6M3) || defined(R7FA4M3) || defined(R7FA6M4) || defined(R7FA6M5))
    uint32_t source_clock = system_clocks.pclka;
    #elif defined(R7FA2E3)
    uint32_t source_clock = system_clocks.pclkb;
    #elif defined(R7FA8M1)
    uint32_t source_clock = system_clocks.sciclk;
    #endif

    /* Formula for I2C Master mode speed calculation of SCI module is:
     * BRR = ( TCLK / ( bit_rate * 64 * 2^(2n-1) )) - 1
     * Where n is CKS value in [0..3], so divider constant in
     * this equation can be 32, 128, 512 and 2048.
     */
    for ( uint8_t cks_value = 0; cks_value < 4; cks_value++ ) {
        // TCLK = SCICLK / ( 4 ^ CKS )
        source_clock = system_clocks.sciclk / ( 1 << (cks_value * 2));
        uint16_t brr_value = ( source_clock / ( speed * g_div_coefficient[cks_value] )) - 1;

        // Check the closest rounded versions of BRR value.
        for ( uint8_t i = 0; i < 3; i++ ) {
            if (( brr_value + i ) < 0 || ( brr_value + i ) > 0xFF )
                continue;

            double real_bps = source_clock / ( g_div_coefficient[cks_value] * ( (double)( brr_value + i ) + 1.0 ) );
            double error = ( real_bps - speed ) / speed * 100.0;

            if ( fabs( error ) < fabs( best_error ) ) {
                best_cks = cks_value;
                best_brr = brr_value + i - 2;
                best_error = error;
            }
        }
    }

    // Set PCLK dividers for SCI.
    set_reg_bits( &hal_ll_hw_reg->ccr2, best_cks << HAL_LL_CCR2_CKS_OFFSET );

    // Set the bit rate register with the found value.
    write_reg( &hal_ll_hw_reg->ccr2, best_brr << HAL_LL_CCR2_BRR_OFFSET );
}

static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // Clear Serial Control Register before configuring SCI in I2C master mode.
    clear_reg( &hal_ll_hw_reg->ccr0 );

    // Set the ICR.IICSDAS and ICR.IICSCLS bits set to 11b to drive the SCLn and SDAn pins to high-impedance state.
    clear_reg( &hal_ll_hw_reg->icr );
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK );
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSCLS_MASK );

    // Configure SCI to be in IIC mode.
    set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_MOD_IIC_MASK );
    clear_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CKE_MASK );

    // Configure IIC Mode registers.
    set_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICINTM );
    set_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICCSC );
    set_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICACKT );

    // Set the initial value for Serial Port Register.
    clear_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_TINV );
    clear_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_RINV );
    clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_LSBF );
    clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_SINV );

    // Calculate I2C speed.
    hal_ll_sci_calculate_speed( map->base, map->speed, HAL_LL_SCI_I2C_MODE );

    // Clear any pending flags.
    set_reg_bits( &hal_ll_hw_reg->cfclr, HAL_LL_SCI_CFCLR_MASK );
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );

    // Set initial state for I2C to work as transmitter.
    set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TE );
    set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TIE );
    set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TEIE );
}

static void hal_ll_sci_spi_hw_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // // Clear Serial Control Register before configuring SCI in SPI master mode.
    clear_reg( &hal_ll_hw_reg->ccr0 );

    // Clear FIFO Mode Select bit for non-FIFO implementation.
    clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_FM );

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0).
    if ( HAL_LL_SCI_SPI_MODE_0 == map->mode || HAL_LL_SCI_SPI_MODE_2 == map->mode ) {
        set_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CPHA );
    } else {
        clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CPHA );
    }

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if ( HAL_LL_SCI_SPI_MODE_2 >= map->mode ) {
        clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CPOL );
    } else {
        set_reg_bit(&( hal_ll_hw_reg->ccr3), HAL_LL_SCI_CCR3_CPOL );
    }

    // Set Simple SPI mode as Communication Mode.
    set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_MOD_SPI_MASK );

    // Set the desired bit rate.
    hal_ll_sci_calculate_speed( map->base, map->speed, HAL_LL_SCI_SPI_MODE );

    // Set the initial value for Serial Port Register.
    clear_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_TINV );
    clear_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_RINV );
    clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_SINV );

    // Transfer MSB first.
    clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_LSBF );

    // Clear any pending flags.
    set_reg_bits( &hal_ll_hw_reg->cfclr, HAL_LL_SCI_CFCLR_MASK );

    // Set TE, RE and TIE bit simultaneously
    set_reg_bits( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_READ_MASK );
}

// ------------------------------------------------------------------------- END
