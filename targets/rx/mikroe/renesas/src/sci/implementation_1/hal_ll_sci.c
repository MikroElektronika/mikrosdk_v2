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
 * @brief SCI HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio.h"
#include "hal_ll_sci.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"
#include "mcu.h"

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_sci_get_base_struct(_handle) ((hal_ll_sci_base_handle_t *)_handle)

/*!< @brief SSR bit positions */
#define HAL_LL_SCI_SSR_TEND             (2)
#define HAL_LL_SCI_SSR_ORER             (5)
#define HAL_LL_SCI_SSR_RDRF             (6)

/*!< @brief SCMR bit positions */
#define HAL_LL_SCI_SCMR_SMIF            (0)
#define HAL_LL_SCI_SCMR_SINV            (2)
#define HAL_LL_SCI_SCMR_SDIR            (3)

/*!< @brief SIMR1, SIMR2, SIMR3 and SISR bit positions and masks */
#define HAL_LL_SCI_SIMR1_IICM           (0)
#define HAL_LL_SCI_SIMR1_IICDL          (3)
#define HAL_LL_SCI_SIMR2_IICINTM        (0)
#define HAL_LL_SCI_SIMR2_IICCSC         (1)
#define HAL_LL_SCI_SIMR2_IICACKT        (5)
#define HAL_LL_SCI_SIMR3_IICSTIF        (3)
#define HAL_LL_SCI_SIMR3_START_MASK     (0x51)
#define HAL_LL_SCI_SIMR3_RESTART_MASK   (0x52)
#define HAL_LL_SCI_SIMR3_STOP_MASK      (0x54)
#define HAL_LL_SCI_SIMR3_RELEASE_MASK   (0xF0)
#define HAL_LL_SCI_SISR_IICACKR         (0)

/*!< @brief SCR enable mask for TIE, TE, RE and TEIE */
#define HAL_LL_SCI_SCR_ENABLE_MASK      (0xB4)

/*!< @brief Macros used for bit rate and SSDA delay calculations */
#define HAL_LL_SCI_BRR_DIVISOR_BASE     (32UL)
#define HAL_LL_SCI_BRR_COUNT_MAX        (256UL)
#define HAL_LL_SCI_CKS_COUNT            (4)
#define HAL_LL_SCI_SCL_FALL_TIME_NS     (300UL)
#define HAL_LL_SCI_IICDL_MAX            (31UL)
#define HAL_LL_SCI_DUMMY_BYTE           (0xFF)

// Board/clock-tree dependent -- confirmed PCLKB = 60MHz for this board during hal_ll_uart.c bring-up
// (HOCO 20MHz -> PLLx12 -> ICLK/2 = 120MHz, PCLKB/4 = 60MHz). Re-confirm if the clock config changes.
#define HAL_LL_SCI_MCU_CLOCK_HZ         (60000000UL) /* TODO: verify against the actual board clock config */

/*!< @brief SCI register structure (SCI1, SCI5, SCI6, RX26T Group manual sec. 32.2) */
typedef struct {
    uint8_t smr;
    uint8_t brr;
    uint8_t scr;
    uint8_t tdr;
    uint8_t ssr;
    uint8_t rdr;
    uint8_t scmr;
    uint8_t semr;
    uint8_t snfr;
    uint8_t simr1;
    uint8_t simr2;
    uint8_t simr3;
    uint8_t sisr;
    uint8_t spmr;
    uint8_t reserved[14];
    uint8_t sptr;
} hal_ll_sci_base_handle_t;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
  * @brief  Initialize SCI module in I2C Master mode on hardware level.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map );

/**
  * @brief  Sets SCI pin alternate function state to work in I2C Master mode.
  *
  * Sets PSEL value for SSCL and SSDA pins and selects N-channel
  * open-drain output on the port side.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  * @return None
  */
static void hal_ll_sci_i2c_alternate_functions_set_state( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state );

/**
  * @brief  Calculate and set SCI bit rate for I2C Master mode.
  *
  * Picks the CKS/BRR pair with the smallest bit rate error and sets
  * the SSDA output delay.
  *
  * @param[in]  base - SCI module base address.
  * @param[in]  speed - Desired bit rate.
  * @param[in]  sci_mode - SCI operating mode.
  * @return None
  */
static void hal_ll_sci_calculate_speed( uint32_t base, uint32_t speed, hal_ll_sci_mode_t sci_mode );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_sci_i2c_write_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_sci_i2c_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_read;

    // Wait for all previous transmissions to be ended.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    // Trigger the start condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    // Wait for the start condition to be generated.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_START;
        }
    }

    // Clear flag and set I2C into default state.
    write_reg( &hal_ll_hw_reg->simr3, 0 );

    // Send the slave address and write command.
    write_reg( &hal_ll_hw_reg->tdr, map->address << 1 );

    // Wait for the slave address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ))
        dummy_read = read_reg( &hal_ll_hw_reg->rdr );

    // Check if for ACK signal.
    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_SCI_SISR_IICACKR ) ) {
        for( size_t i = 0; i < len_write_data; i++ ) {
            write_reg( &hal_ll_hw_reg->tdr, write_data_buf[i] );

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
                }
            }

            if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ))
                dummy_read = read_reg( &hal_ll_hw_reg->rdr );
        }
    }

    // If there is no need in RESTART condition - issue a STOP condition.
    if ( HAL_LL_SCI_I2C_WRITE_THEN_READ != mode ) {
        // Trigger the STOP condition.
        write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

        // Wait for the stop condition to be generated.
        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_SCI_I2C_TIMEOUT_STOP;
            }
        }

        // Clear flag and release SSCL and SSDA pins.
        write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_RELEASE_MASK );
    }

    return 0;
}

hal_ll_err_t hal_ll_sci_i2c_read_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                             uint8_t *read_data_buf,
                                             size_t len_read_data,
                                             hal_ll_sci_i2c_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = HAL_LL_SCI_DUMMY_BYTE;
    uint8_t dummy_read = 0;

    if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ))
        dummy_read = read_reg( &hal_ll_hw_reg->rdr );

    if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
        clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

    if ( HAL_LL_SCI_I2C_WRITE_THEN_READ != mode )
        // Trigger the START condition.
        write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );
    else
        // Issue a RESTART condition.
        write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_RESTART_MASK );

    // Wait for the condition to be generated.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_START;
        }
    }

    // Clear flag and set I2C into default state.
    write_reg( &hal_ll_hw_reg->simr3, 0 );

    // Send the slave address and read command.
    write_reg( &hal_ll_hw_reg->tdr, ( map->address << 1 ) | 1 );

    // Wait for the address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Check if address has been acknowledged.
    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_SCI_SISR_IICACKR ) ) {
        // Enable ACK transmission.
        clear_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

        // Read all the dummy data from Receive Buffer.
        dummy_read = read_reg( &hal_ll_hw_reg->rdr );

        for( size_t i = 0; i < len_read_data - 1; i++ ) {
            // Wait for Receive Buffer to be empty.
            time_counter = map->timeout;
            while( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_READ;
                }
            }

            // Send 0xFF to trigger clock line and trace incoming data byte.
            write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

            // Wait for data to be written into Receive Buffer.
            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_READ;
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
                    return HAL_LL_SCI_I2C_TIMEOUT_READ;
            }
        }

        // Send 0xFF to trigger clock line and trace incoming data byte.
        write_reg( &hal_ll_hw_reg->tdr, dummy_byte );

        // Wait for data to be written into Receive Buffer.
        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_SCI_I2C_TIMEOUT_READ;
            }
        }

        // Read received data.
        read_data_buf[len_read_data - 1] = read_reg( &hal_ll_hw_reg->rdr );

        // Wait for the NACK bit of the last byte to be sent.
        time_counter = map->timeout;
        while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_SCI_I2C_TIMEOUT_READ;
            }
        }
    }

    // Trigger the stop condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_STOP_MASK );

    // Wait for the stop condition to be generated.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_STOP;
        }
    }

    // Clear flag and release SSCL and SSDA pins.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_RELEASE_MASK );

    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

    return 0;
}

void hal_ll_sci_i2c_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    // Enable SCI peripheral
    hal_ll_sci_module_enable( map->module_index, true );

    hal_ll_sci_i2c_alternate_functions_set_state( map, true );

    hal_ll_sci_i2c_hw_init( map );
}

void hal_ll_sci_module_enable( uint8_t module_index, bool hal_ll_state ) {
    volatile uint16_t *prcr = ( uint16_t * )HAL_LL_MSTPCR_PRCR_ADDR;
    write_reg( prcr, HAL_LL_MSTPCR_PRCR_UNLOCK_VAL );

    #ifdef SCI_MODULE_5
    if ( hal_ll_sci_module_num( SCI_MODULE_5 ) == module_index ) {
        hal_ll_state ? clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS ) : set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS );
    }
    #endif

    write_reg( prcr, HAL_LL_MSTPCR_PRCR_LOCK_VAL );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS
static void hal_ll_sci_i2c_alternate_functions_set_state( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = map->pins.pin_scl.pin_name;
        module.pins[1] = map->pins.pin_sda.pin_name;
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = map->pins.pin_scl.pin_af;
        module.configs[1] = map->pins.pin_sda.pin_af;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );

        // TODO: derive port and bit positions from the mapped SCL/SDA pins instead of fixed P90/P91
        if ( hal_ll_state ) {
            PORT9.ODR0.BYTE |= ( uint8_t )(( 1U << 0 ) | ( 1U << 2 ));
        } else {
            PORT9.ODR0.BYTE &= ( uint8_t )~(( 1U << 0 ) | ( 1U << 2 ));
        }
    }
}

static void hal_ll_sci_calculate_speed( uint32_t base, uint32_t speed, hal_ll_sci_mode_t sci_mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );
    uint32_t best_error = 0xFFFFFFFFUL;
    uint8_t best_cks = 0;
    uint8_t best_brr = 0;

    /* Formula for I2C Master mode speed calculation of SCI module is:
     * BRR = ( PCLK / ( bit_rate * 64 * 2^(2n-1) )) - 1
     * Where n is CKS value in [0..3], so divider constant in
     * this equation can be 32, 128, 512 and 2048.
     */
    for ( uint8_t cks = 0; cks < HAL_LL_SCI_CKS_COUNT; cks++ ) {
        uint32_t divisor = HAL_LL_SCI_BRR_DIVISOR_BASE << ( 2 * cks );
        uint32_t brr_plus_one = ( HAL_LL_SCI_MCU_CLOCK_HZ + ( divisor * speed ) / 2 ) /
                                ( divisor * speed );

        if (( 0 == brr_plus_one ) || ( brr_plus_one > HAL_LL_SCI_BRR_COUNT_MAX )) {
            continue;
        }

        uint32_t real_bitrate = HAL_LL_SCI_MCU_CLOCK_HZ / ( divisor * brr_plus_one );
        uint32_t error = ( real_bitrate > speed ) ? ( real_bitrate - speed ) :
                                                    ( speed - real_bitrate );

        if ( error < best_error ) {
            best_error = error;
            best_cks = cks;
            best_brr = ( uint8_t )( brr_plus_one - 1 );
        }
    }

    // Set PCLK dividers for SCI.
    set_reg_bits( &hal_ll_hw_reg->smr, best_cks );

    // Set the bit rate register with the found value.
    write_reg( &hal_ll_hw_reg->brr, best_brr );

    // SSDA output delay has to exceed the SSCL fall time.
    uint32_t baud_clock = HAL_LL_SCI_MCU_CLOCK_HZ >> ( 2 * best_cks );
    uint32_t iicdl = ((( baud_clock / 1000UL ) * HAL_LL_SCI_SCL_FALL_TIME_NS + 999999UL ) / 1000000UL ) + 1;

    if ( iicdl > HAL_LL_SCI_IICDL_MAX ) {
        iicdl = HAL_LL_SCI_IICDL_MAX;
    }

    write_reg( &hal_ll_hw_reg->simr1, ( uint8_t )( iicdl << HAL_LL_SCI_SIMR1_IICDL ));
}

static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // Clear Serial Control Register before configuring SCI in I2C master mode.
    clear_reg( &hal_ll_hw_reg->scr );

    // Set the SIMR3.IICSDAS and SIMR3.IICSCLS bits set to 11b to drive the SSCLn and SSDAn pins to high-impedance state.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_RELEASE_MASK );

    // Clear Serial Mode Register before configuring SCI in I2C master mode.
    clear_reg( &hal_ll_hw_reg->smr );

    // Set the format for transmission.
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SMIF );
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SINV );
    set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SDIR );

    // Set the initial value for Serial Port Register.
    clear_reg( &hal_ll_hw_reg->sptr );

    // Calculate I2C speed.
    hal_ll_sci_calculate_speed( map->base, map->speed, HAL_LL_SCI_I2C_MODE );

    // Disable Noise Filtering and bit rate modulation.
    clear_reg( &hal_ll_hw_reg->semr );

    // Configure IIC Mode registers.
    set_reg_bit( &hal_ll_hw_reg->simr1, HAL_LL_SCI_SIMR1_IICM );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICINTM );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICCSC );
    set_reg_bit( &hal_ll_hw_reg->simr2, HAL_LL_SCI_SIMR2_IICACKT );

    // Enable transmitter and receiver at the same time.
    write_reg( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_ENABLE_MASK );
}

// ------------------------------------------------------------------------- END
