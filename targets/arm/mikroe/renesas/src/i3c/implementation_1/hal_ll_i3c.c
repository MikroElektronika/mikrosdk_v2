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

#include <math.h>
#include "hal_ll_bit_control.h"
#include "hal_ll_gpio.h"
#include "hal_ll_i3c.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS
#define I3C_REG(base, offset)  (*(volatile uint32_t *)((base) + (offset)))

#define HAL_LL_I3C_ACKCTL_REG_OFFSET     (0x0A0UL)
#define HAL_LL_I3C_BCST_REG_OFFSET       (0x210UL)
#define HAL_LL_I3C_BCTL_REG_OFFSET       (0x014UL)
#define HAL_LL_I3C_BFCTL_REG_OFFSET      (0x060UL)
#define HAL_LL_I3C_BFRECDT_REG_OFFSET    (0x07CUL)
#define HAL_LL_I3C_BIE_REG_OFFSET        (0x1D8UL)
#define HAL_LL_I3C_BST_REG_OFFSET        (0x1D0UL)
#define HAL_LL_I3C_BSTE_REG_OFFSET       (0x1D4UL)
#define HAL_LL_I3C_CNDCTL_REG_OFFSET     (0x140UL)
#define HAL_LL_I3C_EXTBR_REG_OFFSET      (0x078UL)
#define HAL_LL_I3C_INCTL_REG_OFFSET      (0x08CUL)
#define HAL_LL_I3C_NTDTBP0_REG_OFFSET    (0x158UL)
#define HAL_LL_I3C_NTIE_REG_OFFSET       (0x1E8UL)
#define HAL_LL_I3C_NTST_REG_OFFSET       (0x1E0UL)
#define HAL_LL_I3C_NTSTE_REG_OFFSET      (0x1E4UL)
#define HAL_LL_I3C_OUTCTL_REG_OFFSET     (0x088UL)
#define HAL_LL_I3C_PRTS_REG_OFFSET       (0x000UL)
#define HAL_LL_I3C_REFCKCTL_REG_OFFSET   (0x070UL)
#define HAL_LL_I3C_RSTCTL_REG_OFFSET     (0x020UL)
#define HAL_LL_I3C_SCSTRCTL_REG_OFFSET   (0x0A4UL)
#define HAL_LL_I3C_SDATBAS0_REG_OFFSET   (0x2B0UL)
#define HAL_LL_I3C_STDBR_REG_OFFSET      (0x074UL)
#define HAL_LL_I3C_SVCTL_REG_OFFSET      (0x064UL)
#define HAL_LL_I3C_TMOCTL_REG_OFFSET     (0x090UL)

/*!< @brief Macros defining bit location. */
#define HAL_LL_I3C_ACKCTL_ACKT        (1)
#define HAL_LL_I3C_ACKCTL_ACKTWP      (2)
#define HAL_LL_I3C_BCST_BFREF         (0)
#define HAL_LL_I3C_BCTL_BUSE          (31)
#define HAL_LL_I3C_BFCTL_MALE         (0)
#define HAL_LL_I3C_BFCTL_SCSYNE       (8)
#define HAL_LL_I3C_BST_STCNDDF        (0)
#define HAL_LL_I3C_BST_SPCNDDF        (1)
#define HAL_LL_I3C_BST_NACKDF         (4)
#define HAL_LL_I3C_BST_TENDF          (8)
#define HAL_LL_I3C_CNDCTL_STCND       (0)
#define HAL_LL_I3C_CNDCTL_SRCND       (1)
#define HAL_LL_I3C_CNDCTL_SPCND       (2)
#define HAL_LL_I3C_INCTL_DNFE         (4)
#define HAL_LL_I3C_NTST_TDBEF0        (0)
#define HAL_LL_I3C_NTST_RDBEF0        (1)
#define HAL_LL_I3C_PRTS_PRTMD         (0)
#define HAL_LL_I3C_RSTCTL_RI3CRST     (0)
#define HAL_LL_I3C_RSTCTL_INTLRST     (16)
#define HAL_LL_I3C_SCSTRLCTL_RWE      (1)
#define HAL_LL_I3C_TMOCTL_TOLCTL      (4)
#define HAL_LL_I3C_TMOCTL_TOHCTL      (5)

#define HAL_LL_I3C_BSTE_START_ENABLE           (1 << 0)
#define HAL_LL_I3C_BSTE_STOP_ENABLE            (1 << 1)
#define HAL_LL_I3C_BSTE_NACK_ENABLE            (1 << 4)
#define HAL_LL_I3C_BSTE_TRANSMIT_END_ENABLE    (1 << 8)
#define HAL_LL_I3C_BSTE_MASK                   (HAL_LL_I3C_BSTE_START_ENABLE | HAL_LL_I3C_BSTE_STOP_ENABLE | \
                                                HAL_LL_I3C_BSTE_NACK_ENABLE | HAL_LL_I3C_BSTE_TRANSMIT_END_ENABLE)

#define HAL_LL_I3C_NTST_TDBEF0_MASK            (1 << 0)
#define HAL_LL_I3C_NTST_RDBEF0_MASK            (1 << 1)
#define HAL_LL_I3C_NTSTE_MASK                  (HAL_LL_I3C_NTST_TDBEF0_MASK | HAL_LL_I3C_NTST_RDBEF0_MASK)

#define HAL_LL_I3C_BIE_START_DETECT_ENABLE     (1 << 0)
#define HAL_LL_I3C_BIE_STOP_DETECT_ENABLE      (1 << 1)
#define HAL_LL_I3C_BIE_MASK                    (HAL_LL_I3C_BIE_START_DETECT_ENABLE | HAL_LL_I3C_BIE_STOP_DETECT_ENABLE)

#define HAL_LL_I3C_NTIE_TDBEIE0_ENABLE         (1 << 0)
#define HAL_LL_I3C_NTIE_RDBFIE0_ENABLE         (1 << 1)
#define HAL_LL_I3C_NTIE_MASK                   (HAL_LL_I3C_NTIE_TDBEIE0_ENABLE | HAL_LL_I3C_NTIE_RDBFIE0_ENABLE)

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
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  *
  * Returns one of pre-defined values.
  * Take into consideration that this is hardware specific.
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
  * Calculates and sets the I3C bit rate by configuring the SPBR register,
  * based on the PCLK clock and desired speed.
  *
  * @param[in]  base     Base address for the module in use.
  * @param[in]  speed    Requested bitrate value.
  * @param[in]  i3c_mode I3C mode in use.
  * @return None
  */
static void hal_ll_i3c_i2c_calculate_speed( hal_ll_i3c_i2c_hw_specifics_map_t *map );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS
hal_ll_err_t hal_ll_i3c_i2c_write_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_i3c_i2c_end_mode_t mode ) {
    uint16_t time_counter = map->timeout;

    // Bus free detection flag
    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BCST_REG_OFFSET ), HAL_LL_I3C_BCST_BFREF ));
    // Issue Start condition
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_STCND );

    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_NTST_REG_OFFSET ), HAL_LL_I3C_NTST_TDBEF0 )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
            }
        }
    }

    // Set slave address and write bit
    I3C_REG( map->base, HAL_LL_I3C_NTDTBP0_REG_OFFSET ) = map->address << 1;

    for (uint32_t i = 0; i < len_write_data; i++) {
        while( check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_NACKDF )) {
            if( map->timeout ) {
                if( !time_counter-- ) {
                    // Stop condition
                    clear_reg_bits( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), ( 1U << HAL_LL_I3C_BST_SPCNDDF ) | ( 1U << HAL_LL_I3C_BST_NACKDF ) );
                    return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
                }
            }
        }
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_NTST_REG_OFFSET ), HAL_LL_I3C_NTST_TDBEF0 ));

        I3C_REG( map->base, HAL_LL_I3C_NTDTBP0_REG_OFFSET ) = write_data_buf[i];
    }

    time_counter = map->timeout;
    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_TENDF )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                // Stop condition
                clear_reg_bits( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), ( 1U << HAL_LL_I3C_BST_SPCNDDF ) | ( 1U << HAL_LL_I3C_BST_NACKDF ) );
                return HAL_LL_I3C_I2C_TIMEOUT_WRITE;
            }
        }
    }

    if ( mode == HAL_LL_I3C_I2C_WRITE_THEN_READ ) {
        // Wait for STCNDDF then clear it before issuing repeated START
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_STCNDDF ));
        clear_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_STCNDDF );
        // Issue Repeated START condition
        set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_SRCND );
        // Wait for SRCND to clear — Sr has been issued
        while ( check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_SRCND ));
        // Wait for STCNDDF — hardware is ready for address byte
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_STCNDDF ));
        return HAL_LL_I3C_SUCCESS;
    }

    // Clear Stop condition flag
    clear_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_SPCNDDF );
    // Issue Stop condition
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_SPCND );

    // Wait for Stop condition to be sent
    time_counter = map->timeout;
    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_SPCNDDF )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                return HAL_LL_I3C_I2C_TIMEOUT_STOP;
            }
        }
    }

    // Clear Stop condition and NACK detection flags
    clear_reg_bits( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), ( 1U << HAL_LL_I3C_BST_SPCNDDF ) | ( 1U << HAL_LL_I3C_BST_NACKDF ) );

    return HAL_LL_I3C_SUCCESS;
}

hal_ll_err_t hal_ll_i3c_i2c_read_bare_metal( hal_ll_i3c_i2c_hw_specifics_map_t *map,
                                             uint8_t *read_data_buf,
                                             size_t len_read_data,
                                             hal_ll_i3c_i2c_end_mode_t mode ) {
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = 0xFF;
    uint8_t dummy_read = 0;

    if ( mode != HAL_LL_I3C_I2C_WRITE_THEN_READ ) {
        // Bus free detection flag — skipped when coming from a Repeated START
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BCST_REG_OFFSET ), HAL_LL_I3C_BCST_BFREF )) {
            if( map->timeout ) {
                if( !time_counter-- ) {
                    return HAL_LL_I3C_I2C_TIMEOUT_READ;
                }
            }
        }
        // Issue Start condition — skipped when coming from a Repeated START (already issued at end of write)
        set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_STCND );
    }

    // Set slave address and read bit
    I3C_REG( map->base, HAL_LL_I3C_NTDTBP0_REG_OFFSET ) = ( map->address << 1 ) | 1;

    time_counter = map->timeout;
    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_NTST_REG_OFFSET ), HAL_LL_I3C_NTST_RDBEF0 )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                return HAL_LL_I3C_I2C_TIMEOUT_READ;
            }
        }
    }
    time_counter = map->timeout;
    if (I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ) & ( 1U << HAL_LL_I3C_BST_NACKDF )) {
        // Slave did not ACK — issue Stop and abort
        set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_SPCND );
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_SPCNDDF )) {
            if( map->timeout ) {
                if( !time_counter-- ) {
                    I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ) &= ~((1U << HAL_LL_I3C_BST_SPCNDDF) | (1U << HAL_LL_I3C_BST_NACKDF));
                    return HAL_LL_I3C_I2C_TIMEOUT_READ;
                }
            }
        }

        return -1;
    }

    // Dummy read to kick off first SCL output
    (void)I3C_REG( map->base, HAL_LL_I3C_NTDTBP0_REG_OFFSET );

    for (uint32_t i = 0; i < len_read_data; i++)
    {
        // Hold SCL before second-to-last byte to ensure NACK can be set in time
        if (i == len_read_data - 2)
            set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_SCSTRCTL_REG_OFFSET ), HAL_LL_I3C_SCSTRLCTL_RWE );

        // Send NACK for last byte to signal end of transfer to slave
        if (i == len_read_data - 1)
            set_reg_bits( &I3C_REG( map->base, HAL_LL_I3C_ACKCTL_REG_OFFSET ), (1U << HAL_LL_I3C_ACKCTL_ACKTWP) | (1U << HAL_LL_I3C_ACKCTL_ACKT) );

        time_counter = map->timeout;
        while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_NTST_REG_OFFSET ), HAL_LL_I3C_NTST_RDBEF0 )) {
            if( map->timeout ) {
                if( !time_counter-- ) {
                    return HAL_LL_I3C_I2C_TIMEOUT_READ;
                }
            }
        }

        // Issue Stop before reading last byte — releases SCL hold and triggers Stop after 9th cycle
        if (i == len_read_data - 1)
            set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_CNDCTL_REG_OFFSET ), HAL_LL_I3C_CNDCTL_SPCND );

        read_data_buf[i] = I3C_REG( map->base, HAL_LL_I3C_NTDTBP0_REG_OFFSET );
    }

    // Wait for Stop condition to be detected
    time_counter = map->timeout;
    while ( !check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), HAL_LL_I3C_BST_SPCNDDF )) {
        if( map->timeout ) {
            if( !time_counter-- ) {
                return HAL_LL_I3C_I2C_TIMEOUT_READ;
            }
        }
    }
    // Clear Stop condition and NACK detection flags
    clear_reg_bits( &I3C_REG( map->base, HAL_LL_I3C_BST_REG_OFFSET ), (1U << HAL_LL_I3C_BST_NACKDF) | (1U << HAL_LL_I3C_BST_SPCNDDF) );

    // Reset ACK control for next transfer
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_ACKCTL_REG_OFFSET ), HAL_LL_I3C_ACKCTL_ACKTWP );

    return HAL_LL_I3C_SUCCESS;
}

void hal_ll_i3c_module_enable( hal_ll_i3c_i2c_hw_specifics_map_t *map, bool hal_ll_state ) {
    switch ( map->module_index ) {
        #ifdef I3C_MODULE_0
        case ( hal_ll_i3c_module_num( I3C_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB4_POS )) :
                                        ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB4_POS ));
            break;
        #endif

        default:
            break;
    }
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

        module.configs[0] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[1] = GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_i3c_i2c_calculate_speed( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    system_clocks_t system_clocks;
    uint8_t irefcks, double_period = 0;
    uint32_t high_cycles, low_cycles;
    uint64_t clock_period_ps;
    SYSTEM_GetClocksFrequency( &system_clocks );

    const i2c_spec_t *i2c_specs = ( map->speed <= 100000 ) ? &i2c_nxp_specifications[0] :
                                  ( map->speed <= 400000 ) ? &i2c_nxp_specifications[1] :
                                                             &i2c_nxp_specifications[2];

    uint32_t tbuf_ns = ( map->speed <= 100000 ) ? 4700 :
                       ( map->speed <= 400000 ) ? 1300 :
                                                  500;

    #if (defined(R7FA4E2) || defined(R7FA4L1) || defined(R7FA4T1) || \
         defined(R7FA6E2) || defined(R7FA6T3) || defined(R7FA8D1) || \
         defined(R7FA8M1) || defined(R7FA8T1))
    uint32_t i3c_clock          = system_clocks.i3cck;
    uint32_t pclk_clock         = system_clocks.pclka;
    #else
    uint32_t i3c_clock          = system_clocks.pclkd;
    uint32_t pclk_clock         = system_clocks.pclkb;
    #endif

    // Find appropriate divider for PCLK,
    for ( irefcks = 0; irefcks <= 7; irefcks++ ) {
        uint8_t clock_divider       = 1U << irefcks;
        uint64_t target_period_ps   = HAL_LL_I3C_PS_PER_SECOND / map->speed;
        uint64_t budget_ps          = target_period_ps - ( ( uint64_t )( i2c_specs->tr + i2c_specs->tf ) * 1000ULL );

        clock_period_ps    = HAL_LL_I3C_PS_PER_SECOND / ( pclk_clock / clock_divider );

        high_cycles = ( uint32_t )( ( ( uint64_t )i2c_specs->th * 1000ULL + clock_period_ps - 1 ) / clock_period_ps );
        low_cycles  = ( uint32_t )( ( ( uint64_t )i2c_specs->tl * 1000ULL + clock_period_ps - 1 ) / clock_period_ps );

        if ( ( high_cycles + low_cycles ) * clock_period_ps <= budget_ps )
            low_cycles += ( uint32_t )( ( budget_ps - ( high_cycles + low_cycles ) * clock_period_ps ) / clock_period_ps );

        if ( high_cycles > 0xFF || low_cycles > 0xFF ) {
            high_cycles = ( high_cycles + 1 ) / 2;
            low_cycles = ( low_cycles + 1 ) / 2;
            double_period = 1;
        }

        if ( high_cycles <= 0xFF && low_cycles <= 0xFF )
            break;
    }

    I3C_REG( map->base, HAL_LL_I3C_REFCKCTL_REG_OFFSET ) = irefcks;
    I3C_REG( map->base, HAL_LL_I3C_STDBR_REG_OFFSET )    = ( ( uint32_t )double_period << 31 ) |
                                    ( ( high_cycles & 0xFF ) << 8 ) |
                                    ( low_cycles & 0xFF );
    I3C_REG( map->base, HAL_LL_I3C_BFRECDT_REG_OFFSET )  = ( tbuf_ns * 1000ULL + clock_period_ps - 1 ) / clock_period_ps;

    return;
}

static void hal_ll_i3c_i2c_hw_init( hal_ll_i3c_i2c_hw_specifics_map_t *map ) {
    // Disable I3C bus operation
    clear_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BCTL_REG_OFFSET ), HAL_LL_I3C_BCTL_BUSE );
    // Reset I3C module
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_RSTCTL_REG_OFFSET ), HAL_LL_I3C_RSTCTL_RI3CRST );

    while ( check_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_RSTCTL_REG_OFFSET ), HAL_LL_I3C_RSTCTL_RI3CRST ) ) {
        // Wait for software reset to complete
    }

    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_RSTCTL_REG_OFFSET ), HAL_LL_I3C_RSTCTL_INTLRST );
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_PRTS_REG_OFFSET ), HAL_LL_I3C_PRTS_PRTMD );
    clear_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_RSTCTL_REG_OFFSET ), HAL_LL_I3C_RSTCTL_INTLRST );

    // Set slave address length to 7-bit
    clear_reg( &I3C_REG( map->base, HAL_LL_I3C_SDATBAS0_REG_OFFSET ) );

    // Set bitrate
    hal_ll_i3c_i2c_calculate_speed( map );

    // Set output control register
    clear_reg( &I3C_REG( map->base, HAL_LL_I3C_OUTCTL_REG_OFFSET ) );
    // Set input control register
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_INCTL_REG_OFFSET ), HAL_LL_I3C_INCTL_DNFE );
    // Set timeout control register
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_TMOCTL_REG_OFFSET ), HAL_LL_I3C_TMOCTL_TOLCTL );
    // Set timeout control register
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_TMOCTL_REG_OFFSET ), HAL_LL_I3C_TMOCTL_TOHCTL );
    // Set acknowledge control register
    clear_reg( &I3C_REG( map->base, HAL_LL_I3C_ACKCTL_REG_OFFSET ) );
    // Set slave communication start control register
    clear_reg( &I3C_REG( map->base, HAL_LL_I3C_SCSTRCTL_REG_OFFSET ) );

    // Enable master arbitration-lost detection
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BFCTL_REG_OFFSET ), HAL_LL_I3C_BFCTL_MALE);
    // Enable SCL synchronous circuit
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BFCTL_REG_OFFSET ), HAL_LL_I3C_BFCTL_SCSYNE);

    // Enable functionality for start/stop detection, NACK detection and transmit end detection
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_BSTE_REG_OFFSET ), HAL_LL_I3C_BSTE_MASK );
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_NTSTE_REG_OFFSET ), HAL_LL_I3C_NTSTE_MASK );
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_BIE_REG_OFFSET ), HAL_LL_I3C_BIE_MASK );
    write_reg( &I3C_REG( map->base, HAL_LL_I3C_NTIE_REG_OFFSET ), HAL_LL_I3C_NTIE_MASK );

    // Start I3C bus operation
    set_reg_bit( &I3C_REG( map->base, HAL_LL_I3C_BCTL_REG_OFFSET ), HAL_LL_I3C_BCTL_BUSE );
}

// ------------------------------------------------------------------------- END
