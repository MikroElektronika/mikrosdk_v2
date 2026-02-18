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

#include <math.h>
#include "hal_ll_gpio.h"
#include "hal_ll_sci.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_sci_get_base_struct(_handle) ((hal_ll_sci_base_handle_t *)_handle)

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_SCR_TEIE         (2)
#define HAL_LL_SCI_SCR_RE           (4)
#define HAL_LL_SCI_SCR_TE           (5)
#define HAL_LL_SCI_SCR_TIE          (7)

#define HAL_LL_SCI_SEMR_BRME        (2)
#define HAL_LL_SCI_SEMR_NFEN        (5)

#define HAL_LL_SCI_SSR_TEND         (2)
#define HAL_LL_SCI_SSR_ORER         (5)
#define HAL_LL_SCI_SSR_RDRF         (6)
#define HAL_LL_SCI_SSR_TDRE         (7)

#define HAL_LL_SCI_SCMR_SMIF        (0)
#define HAL_LL_SCI_SCMR_SINV        (2)
#define HAL_LL_SCI_SCMR_SDIR        (3)

#define HAL_LL_SCI_SPTR_RXDMON      (0)
#define HAL_LL_SCI_SPTR_SPB2DT      (1)
#define HAL_LL_SCI_SPTR_SPB2IO      (2)
#define HAL_LL_SCI_SPTR_RINV        (4)
#define HAL_LL_SCI_SPTR_TINV        (5)
#define HAL_LL_SCI_SPTR_ASEN        (6)
#define HAL_LL_SCI_SPTR_ATEN        (7)

#define HAL_LL_SCI_SIMR1_IICM       (0)

#define HAL_LL_SCI_SIMR2_IICINTM    (0)
#define HAL_LL_SCI_SIMR2_IICCSC     (1)
#define HAL_LL_SCI_SIMR2_IICACKT    (5)

#define HAL_LL_SCI_SIMR3_IICSTIF    (3)

#define HAL_LL_SCI_SISR_IICACKR     (0)

#define HAL_LL_SCI_FCR_FM           (0)

#define HAL_LL_SCI_SMR_CM           (7)

#define HAL_LL_SCI_SPMR_CKPOL       (6)
#define HAL_LL_SCI_SPMR_CKPH        (7)

/*!< @brief Macros defining bit masks. */
#define HAL_LL_SCI_SCR_MASK_TE_RE_RIE_TIE  (0xF0)
#define HAL_LL_SCI_SCR_MASK_TE_RE_TIE      (0xB0)
#define HAL_LL_SCI_SCR_MASK_TE_RE_RIE      (0x70)
#define HAL_LL_SCI_SCR_MASK_TE_RE          (0xA0)
#define HAL_LL_SCI_SCR_READ_MASK           (0xB4)
#define HAL_LL_SCI_SIMR3_IICSDAS_MASK      (0x30)
#define HAL_LL_SCI_SIMR3_IICSCLS_MASK      (0xC0)
#define HAL_LL_SCI_SIMR3_START_MASK        (0x51)
#define HAL_LL_SCI_SIMR3_STOP_MASK         (0x54)

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
    while( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    // Trigger the start condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
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
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
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
                        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
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
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF | \
                    HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

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
    write_reg( &hal_ll_hw_reg->scr, 0 );
    set_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_READ_MASK );

    // Trigger the start condition.
    write_reg( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_START_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
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
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
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
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    clear_reg_bits( &hal_ll_hw_reg->simr3, HAL_LL_SCI_SIMR3_IICSTIF | \
                    HAL_LL_SCI_SIMR3_IICSDAS_MASK | HAL_LL_SCI_SIMR3_IICSCLS_MASK );

    return HAL_LL_SCI_SUCCESS;
}

void hal_ll_sci_spi_write_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                      uint8_t *write_data_buffer,
                                      size_t write_data_length ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    while ( 0 < write_data_length-- ) {
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

        // Wait until transmit buffer is empty.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ));

        // Send byte from write buffer.
        write_reg( &hal_ll_hw_reg->tdr, ( uint8_t )( *write_data_buffer++ ) );

        // Wait until transmit is complete.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ));

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ));

        // Dummy read
        volatile uint8_t temp = read_reg( &hal_ll_hw_reg->rdr );
    }
}

void hal_ll_sci_spi_read_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                     uint8_t *read_data_buffer, size_t read_data_length,
                                     uint8_t dummy_data ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    while ( 0 < read_data_length-- ) {
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ));

        // Send dummy data
        write_reg( &hal_ll_hw_reg->tdr, dummy_data );

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ));

        // Read received byte and store if read buffer is provided
        *read_data_buffer++ = read_reg( &hal_ll_hw_reg->rdr );
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ));
}

void hal_ll_sci_spi_transfer_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                         uint8_t *write_data_buffer,
                                         uint8_t *read_data_buffer,
                                         size_t data_length ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    while ( 0 < data_length-- ) {
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

        // Wait until transmit buffer is empty
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ));

        // Send byte from write buffer or dummy if NULL
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : 0xFF;
        write_reg( &hal_ll_hw_reg->tdr, tx_data );

        // Wait until receive is complete
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ));

        // Read received byte and store if read buffer is provided
        uint8_t rx_data = read_reg( &hal_ll_hw_reg->rdr );
        if ( read_data_buffer ) {
            *read_data_buffer++ = rx_data;
        }
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ));
}

void hal_ll_sci_module_enable( hal_ll_sci_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef SCI_MODULE_0
        case ( hal_ll_sci_module_num( SCI_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_1
        case ( hal_ll_sci_module_num( SCI_MODULE_1 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_2
        case ( hal_ll_sci_module_num( SCI_MODULE_2 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB29_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_3
        case ( hal_ll_sci_module_num( SCI_MODULE_3 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB28_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_4
        case ( hal_ll_sci_module_num( SCI_MODULE_4 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB27_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_5
        case ( hal_ll_sci_module_num( SCI_MODULE_5 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB26_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_6
        case ( hal_ll_sci_module_num( SCI_MODULE_6 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB25_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_7
        case ( hal_ll_sci_module_num( SCI_MODULE_7 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB24_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_8
        case ( hal_ll_sci_module_num( SCI_MODULE_8 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB23_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_9
        case ( hal_ll_sci_module_num( SCI_MODULE_9 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB22_POS ));
            break;
        #endif

        default:
            break;
    }
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
     * BRR = ( PCLK / ( bit_rate * 64 * 2^(2n-1) )) - 1
     * Where n is CKS value in [0..3], so divider constant in
     * this equation can be 32, 128, 512 and 2048.
     */
    for ( uint8_t cks_value = 0; cks_value < 4; cks_value++ ) {
        uint16_t brr_value = ( source_clock / ( speed * g_div_coefficient[cks_value] )) - 1;

        // Check the closest rounded versions of BRR value.
        for ( uint8_t i = 0; i < 3; i++ ) {
            if (( brr_value + i ) < 0 || ( brr_value + i ) > 0xFF )
                continue;

            double real_bps = source_clock / ( g_div_coefficient[cks_value] * ( (double)( brr_value + i ) + 1.0 ) );
            double error = ( real_bps - speed ) / speed * 100.0;

            if ( fabs( error ) < fabs( best_error ) ) {
                best_cks = cks_value;
                best_brr = brr_value + i - 1;
                best_error = error;
            }
        }
    }

    // Set PCLK dividers for SCI.
    set_reg_bits( &hal_ll_hw_reg->smr, best_cks );

    // Set the bit rate register with the found value.
    write_reg( &hal_ll_hw_reg->brr, best_brr );

    // Disable bit rate modulation function.
    clear_reg_bit( &hal_ll_hw_reg->semr, HAL_LL_SCI_SEMR_BRME );
}

static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

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
    hal_ll_sci_calculate_speed( map->base, map->speed, HAL_LL_SCI_I2C_MODE );

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

static void hal_ll_sci_spi_hw_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // Clear Serial Control Register before configuring SCI in SPI master mode.
    clear_reg( &hal_ll_hw_reg->scr );

    // Clear SPI mode register for initial settings for SCI in SPI master mode.
    clear_reg( &hal_ll_hw_reg->spmr );

    // Clear FIFO Mode Select bit for non-FIFO implementation.
    clear_reg_bit( &hal_ll_hw_reg->fcr, HAL_LL_SCI_FCR_FM );

    // Enable Simple SPI mode.
    clear_reg_bit( &hal_ll_hw_reg->simr1, HAL_LL_SCI_SIMR1_IICM );

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0).
    if ( HAL_LL_SCI_SPI_MODE_0 == map->mode || HAL_LL_SCI_SPI_MODE_2 == map->mode ) {
        set_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPH );
    } else {
        clear_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPH );
    }

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if ( HAL_LL_SCI_SPI_MODE_2 >= map->mode ) {
        clear_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPOL );
    } else {
        set_reg_bit(&( hal_ll_hw_reg->spmr), HAL_LL_SCI_SPMR_CKPOL );
    }

    // Set Simple SPI mode as Communication Mode.
    set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CM );

    // Set the format for transmission as Simple SPI.
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SMIF );

    // Don't invert received and transmitted data.
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SINV );

    // Transfer MSB first.
    set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SDIR );

    // Set the initial value for Serial Port Register.
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_RINV );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_TINV );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_SPB2IO );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_ASEN );
    clear_reg_bit( &hal_ll_hw_reg->sptr, HAL_LL_SCI_SPTR_ATEN );

    // Set the desired bit rate.
    hal_ll_sci_calculate_speed( map->base, map->speed, HAL_LL_SCI_SPI_MODE );

    // Set TE, RE and TIE bit simultaneously
    set_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_MASK_TE_RE_RIE_TIE );
}

// ------------------------------------------------------------------------- END
