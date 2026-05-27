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

/*!< @brief Macros used for calculating actual baud rate value and error value. */

/*!< @brief Macro used for picking the divisors for the source clock.
 * if is_base_16 == true:
 *     Skip this calculation for divisors that are not achievable with 16 base clk cycles per bit.
 * if is_base_16 == false:
 *     Skip this calculation for divisors that are only achievable without 16 base clk cycles per bit.
 */
#define hal_ll_sci_brr_assert_divisors(is_base_16, i)   \
                                    (is_base_16  ^ (g_async_baud[i].abcs | g_async_baud[i].abcse))

/*!< @brief Macro used for calculating BRR register value.
 * BRR = (PCLKA / (div_coefficient * baud)) - 1
 */
#define hal_ll_sci_brr_calculate(baud, pclka, i) (pclka / (g_div_coefficient[i] * baud))

/*!< @brief Macro used for calculating the baud rate error.
 * error[%] = {(PCLKA / (baud * div_coefficient * (BRR + 1)) - 1} x 100
 * Promoting to 64 bits for calculation, but the final value can never be more than 32 bits, as
 * described below, so this cast is safe.
 *    1. Larger frequencies yield larger bit errors (absolute value). As the frequency grows,
 *       the current_error approaches -100000, so:
 *       0 >= current_error >= -100000
 *    2. current_error is between -100000 and 0. This entire range fits in an int32_t type, so the cast
 *       to (int32_t) is safe.
 */
#define hal_ll_sci_brr_get_error(brr, pclka, baud, i) \
    (int32_t)(((((int64_t)pclka) * HAL_LL_SCI_BRR_ERROR_REFERENCE) / \
    (g_div_coefficient[i] * baud * (brr + 1))) - HAL_LL_SCI_BRR_ERROR_REFERENCE)

/*!< @brief Macro used for getting the real baudrate.
 * baud = PCLKA / ((BRR + 1) * div_coefficient)
 */
#define hal_ll_sci_get_baud_rate(pclka, brr, i) (pclka / ((brr + 1) * g_div_coefficient[i]))

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_CCR0_RE              (0)
#define HAL_LL_SCI_CCR0_TE              (4)
#define HAL_LL_SCI_CCR0_RIE             (16)
#define HAL_LL_SCI_CCR0_TIE             (20)
#define HAL_LL_SCI_CCR0_TEIE            (21)

#define HAL_LL_SCI_CCR1_PE              (8)
#define HAL_LL_SCI_CCR1_PM              (9)
#define HAL_LL_SCI_CCR1_TINV            (12)
#define HAL_LL_SCI_CCR1_RINV            (13)

#define HAL_LL_SCI_CCR2_BGDM            (4)
#define HAL_LL_SCI_CCR2_ABCS            (5)
#define HAL_LL_SCI_CCR2_ABSCE           (6)
#define HAL_LL_SCI_CCR2_ABSCE2          (7)
#define HAL_LL_SCI_CCR2_BRR_OFFSET      (8)
#define HAL_LL_SCI_CCR2_CKS_OFFSET      (20)

#define HAL_LL_SCI_CCR3_CPHA            (0)
#define HAL_LL_SCI_CCR3_CPOL            (1)
#define HAL_LL_SCI_CCR3_CHR             (8)
#define HAL_LL_SCI_CCR3_LSBF            (12)
#define HAL_LL_SCI_CCR3_SINV            (13)
#define HAL_LL_SCI_CCR3_STP             (14)
#define HAL_LL_SCI_CCR3_FM              (20)
#define HAL_LL_SCI_CCR3_CKE             (24)

#define HAL_LL_SCI_CSR_ORER             (24)
#define HAL_LL_SCI_CSR_PER              (27)
#define HAL_LL_SCI_CSR_FER              (28)
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

#define HAL_LL_SCI_CCR2_BPS_CONFIG_BITS_MASK    (0xf0)
#define HAL_LL_SCI_CCR2_BRR_MASK                (0xff00)
#define HAL_LL_SCI_CCR2_CKS_MASK                (0x300000)

#define HAL_LL_SCI_CCR3_CHR_7BITS               (0x3 << HAL_LL_SCI_CCR3_CHR)
#define HAL_LL_SCI_CCR3_CHR_8BITS               (0x2 << HAL_LL_SCI_CCR3_CHR)
#define HAL_LL_SCI_CCR3_CHR_9BITS               (0x1 << HAL_LL_SCI_CCR3_CHR)

#define HAL_LL_SCI_CCR3_MOD_SPI_MASK            (0x30000)
#define HAL_LL_SCI_CCR3_MOD_IIC_MASK            (0x40000)
#define HAL_LL_SCI_CCR3_CKE_MASK                (0x3000000)

#define HAL_LL_SCI_ICR_START_MASK               (0x510000)
#define HAL_LL_SCI_ICR_RESTART_MASK             (0x520000)
#define HAL_LL_SCI_ICR_STOP_MASK                (0x540000)
#define HAL_LL_SCI_ICR_IICSDAS_MASK             (0x300000)
#define HAL_LL_SCI_ICR_IICSCLS_MASK             (0xC00000)
#define HAL_LL_SCI_CFCLR_MASK                   (0x9D070010)

/*!< @brief Macros defining register bit values. */
#define HAL_LL_SCI_CLOCK_EXTERNAL               ( 0x3 << HAL_LL_SCI_CCR3_CKE )
#define HAL_LL_SCI_CCR2_CONFIGURE(bgdm, abcs, abcse, abcse2 ) \
                                    (bgdm << HAL_LL_SCI_CCR2_BGDM) | \
                                    (abcs << HAL_LL_SCI_CCR2_ABCS) | \
                                    (abcse << HAL_LL_SCI_CCR2_ABSCE) | \
                                    (abcse2 << HAL_LL_SCI_CCR2_ABSCE2)

/*!< @brief Macros used for baudrate calculations. */
#define HAL_LL_SCI_NUM_DIVISORS         14
#define HAL_LL_SCI_BRR_MAX              256
#define HAL_LL_SCI_BRR_ERROR_ACCEPTABLE 1000UL
#define HAL_LL_SCI_BRR_ERROR_REFERENCE  100000UL

/* @brief Macros used for interrupt handling. */
#define HAL_LL_SCI_TXI_ENABLE_MASK          ( 0x100010 )

/*!< @brief Structure used for baudrate calculations. */
typedef struct st_baud_setting_const_t {
    uint8_t bgdm;   /**< BGDM value to get divisor */
    uint8_t abcs;   /**< ABCS value to get divisor */
    uint8_t abcse;  /**< ABCSE value to get divisor */
    uint8_t abcse2;  /**< ABCSE value to get divisor */
    uint8_t cks;    /**< CKS  value to get divisor (CKS = N) */
} baud_setting_const_t;

/*!< @brief Baud rate bit divisor information structure. */
static const baud_setting_const_t g_async_baud[ HAL_LL_SCI_NUM_DIVISORS ] = {
    {0U, 0U, 0U, 1U, 0U},                  /* BGDM, ABCS, ABCSE, ABCSE2, n */
    {0U, 0U, 1U, 0U, 0U},
    {1U, 1U, 0U, 0U, 0U},
    {1U, 0U, 0U, 0U, 0U},
    {0U, 0U, 1U, 0U, 1U},
    {0U, 0U, 0U, 0U, 0U},
    {1U, 0U, 0U, 0U, 1U},
    {0U, 0U, 1U, 0U, 2U},
    {0U, 0U, 0U, 0U, 1U},
    {1U, 0U, 0U, 0U, 2U},
    {0U, 0U, 1U, 0U, 3U},
    {0U, 0U, 0U, 0U, 2U},
    {1U, 0U, 0U, 0U, 3U},
    {0U, 0U, 0U, 0U, 3U}
};

/*!< @brief Baud rate divisor information structure. */
static const uint16_t g_div_coefficient[ HAL_LL_SCI_NUM_DIVISORS ] = {
    4U, 6U, 8U, 16U, 24U, 32U, 64U, 96U, 128U, 256U, 384U, 512U, 1024U, 2048U,
};

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
 * @brief  Sets desired stop bits.
 *
 * Initializes module on hardware level
 * with specified stop bit value.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_stop_bits_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets desired data bits.
 *
 * Initializes module on hardware level
 * with specified data bit bit value.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_data_bits_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets desired parity.
 *
 * Initializes module on hardware level
 * with specified parity value.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_parity_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets module clock value.
 *
 * Enables/disables specific SCI_UART module
 * clock gate.
 *
 * @param[in]  base - SCI module base address.
 * @param[in]  module_state - true(enable clock) / false(disable clock)
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_module( uint32_t base, hal_ll_sci_state_t module_state );

/**
 * @brief  Sets module TX line state.
 *
 * Enables/disables specific SCI_UART module
 * TX pin state
 *
 * @param[in]  base - SCI module base address.
 * @param[in]  module_state - true(enable transmitter pin) / false(disable transmitter pin)
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_transmitter( uint32_t base, hal_ll_sci_state_t module_state );

/**
 * @brief  Sets module RX line state.
 *
 * Enables/disables specific SCI_UART module
 * RX pin state
 *
 * @param[in]  base - SCI module base address.
 * @param[in]  module_state - true(enable receive pin) / false(disable receive pin)
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_receiver( uint32_t base, hal_ll_sci_state_t module_state );

/**
 * @brief  Sets Sci_UART module baudrate.
 *
 * Sets desired baud rate for SCI module configured in UART mode.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_sci_uart_set_baud_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map );

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

void hal_ll_sci_uart_irq_enable( hal_ll_sci_uart_hw_specifics_map_t *map, hal_ll_sci_uart_irq_t irq ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( irq ) {
        case HAL_LL_SCI_UART_IRQ_RX:
            set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_RIE );
            break;
        case HAL_LL_SCI_UART_IRQ_TX:
            /*
            * Note: In Hardware Manual for RA8M1 in 32.1.5 TIE bit (Transmit Interrupt Enable)
            * paragraph it is said: "At the beginning of transmission, set 1 to CCR0.TE and
            * CCR0.TIE simultaneously. The SCIn_TXI interrupt request is then generated.
            *
            * In order to set TE bit in SCI SCR register we need first to clear it as it was set during
            * the initialization process.
            */
            clear_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TE );
            set_reg_bits( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_TXI_ENABLE_MASK );
            break;

        default:
            break;

    }
}

void hal_ll_sci_uart_irq_disable( hal_ll_sci_uart_hw_specifics_map_t *map, hal_ll_sci_uart_irq_t irq ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( irq ) {
        case HAL_LL_SCI_UART_IRQ_RX:
            clear_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_RIE );
            break;
        case HAL_LL_SCI_UART_IRQ_TX:
            clear_reg_bits( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_TXI_ENABLE_MASK );
            break;

        default:
            break;
    }
}

void hal_ll_sci_uart_write( hal_ll_sci_uart_hw_specifics_map_t *map, uint8_t wr_data ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    hal_ll_hw_reg->tdr = wr_data;

    // Wait until transmit data register is empty.
    while ( !( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE )));

    // Wait for transmission to end.
    while ( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND ));
}

void hal_ll_sci_uart_write_polling( hal_ll_sci_uart_hw_specifics_map_t *map, uint8_t wr_data ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint32_t time_counter = map->timeout_polling_write;

    // Wait until transmit data register is empty.
    while ( !( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE ))) {
        // Timeout check.
        if( !time_counter-- ) {
            return;
        }
    }

    hal_ll_hw_reg->tdr = wr_data;
}

uint8_t hal_ll_sci_uart_read( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    uint8_t rd_data;

    /*
     * If irq_handler is called by ERI ISR (Error Receive Interrupt)
     * we need to handle overrun error properly. We need to disable reception
     * and read the RDR data not to lose it before clearing the overrun error flag.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER ) )
        clear_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_RE );

    rd_data = hal_ll_hw_reg->rdr;

    /*
     * If irq_handler is called by the overrun error we need
     * to enable reception after reading the data from RDR.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER ) ) {
        set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_RE );
        clear_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER );
        while ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_ORER ) );
    }

    /*
     * If irq_handler is called by the framing error we need
     * to clear the error flag to disable the ERI interrupt.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_FER )) {
        clear_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_FER );
        while ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_FER ));
    }

    /*
     * If irq_handler is called by the parity error we need
     * to clear the error flag to disable the ERI interrupt.
     */
    if ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_PER )) {
        clear_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_PER );
        while ( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_PER ));
    }

    return rd_data;
}

uint8_t hal_ll_sci_uart_read_polling( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // Wait until there is data in the receive data register.
    while ( !( check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_RDRF )));

    return hal_ll_hw_reg->rdr;
}

void hal_ll_sci_uart_clear_regs( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    clear_reg( &hal_ll_hw_reg->ccr0 );
    while ( read_reg( &hal_ll_hw_reg->ccr0 ));
}

hal_ll_err_t hal_ll_sci_i2c_write_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_sci_i2c_end_mode_t mode ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;

    // Wait for all previous transmissions to be ended.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    // Trigger the start condition.
    set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_START_MASK );

    // Wait for completion of start condition.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear condition status flag and revert I2C into default state.
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );

    // Wait for condition flag to be cleared.
    time_counter = map->timeout;
    while( check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK | HAL_LL_SCI_ICR_IICSCLS_MASK );

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
            while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
                }
            }

            time_counter = map->timeout;
            while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND )) {
                if( map->timeout ) {
                    if( !time_counter-- )
                        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
                }
            }
        }
    }

    // If there is no need in RESTART condition - issue a STOP condition.
    if ( HAL_LL_SCI_I2C_WRITE_THEN_READ != mode ) {
        // Trigger the STOP condition.
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

        // Wait for condition flag to be cleared.
        time_counter = map->timeout;
        while( check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
            if( map->timeout ) {
                if( !time_counter-- )
                    return HAL_LL_SCI_I2C_TIMEOUT_READ;
            }
        }
    }

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

    if ( HAL_LL_SCI_I2C_WRITE_THEN_READ != mode )
        // Trigger the START condition.
        set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_START_MASK );
    else
        // Issue a RESTART condition.
        set_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_RESTART_MASK );

    // Wait for ACK signal.
    while( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and revert I2C into default state.
    set_reg_bit( &hal_ll_hw_reg->icfclr, HAL_LL_SCI_ICFCLR_IICSTIFC );

    // Wait for condition flag to be cleared.
    time_counter = map->timeout;
    while( check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Clear ACK flag and set I2C to default state.
    clear_reg_bits( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICSDAS_MASK |\
                                            HAL_LL_SCI_ICR_IICSCLS_MASK );

    // Send the slave address and read command.
    write_reg( &hal_ll_hw_reg->tdr, ( map->address << 1 ) | 1 );

    // Wait for the address to be sent.
    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TDRE )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;
        }
    }

    time_counter = map->timeout;
    while( !check_reg_bit( &hal_ll_hw_reg->csr, HAL_LL_SCI_CSR_TEND )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Check if address has been acknowledged.
    if ( !check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICACKR ) ) {
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

    // Wait for condition flag to be cleared.
    time_counter = map->timeout;
    while( check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

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

    // Wait for condition flag to be cleared.
    time_counter = map->timeout;
    while( check_reg_bit( &hal_ll_hw_reg->isr, HAL_LL_SCI_ISR_IICSTIF )) {
        if( map->timeout ) {
            if( !time_counter-- )
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_READ_MASK );

    // Set initial state for I2C to work as transmitter.
    set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TE );
    set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TIE );
    set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TEIE );

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

void hal_ll_sci_module_enable( uint8_t module_index, bool hal_ll_state ) {
    if ( hal_ll_state )
        clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS - module_index );
    else
        set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB31_POS - module_index );
}

void hal_ll_sci_i2c_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    // Enable SCI peripheral
    hal_ll_sci_module_enable( map->module_index, true );

    hal_ll_sci_i2c_alternate_functions_set_state( map, true );

    hal_ll_sci_i2c_hw_init( map );
}

void hal_ll_sci_spi_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {

    hal_ll_sci_module_enable( map->module_index, true );

    hal_ll_sci_spi_alternate_functions_set_state( map, true );

    hal_ll_sci_spi_hw_init( map );
}

void hal_ll_sci_uart_hw_init( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_uart_clear_regs( map );

    hal_ll_sci_uart_set_data_bits_bare_metal( map );

    hal_ll_sci_uart_set_parity_bare_metal( map );

    hal_ll_sci_uart_set_stop_bits_bare_metal( map );

    hal_ll_sci_uart_set_baud_bare_metal( map );

    hal_ll_sci_uart_set_transmitter( map->base, HAL_LL_SCI_ENABLE );

    hal_ll_sci_uart_set_receiver( map->base, HAL_LL_SCI_ENABLE );

    hal_ll_sci_uart_set_module( map->base, HAL_LL_SCI_ENABLE );
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

    uint32_t source_clock = system_clocks.sciclk;

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
                if ( HAL_LL_SCI_I2C_MODE == sci_mode )
                    best_brr = brr_value + i;
                else
                    best_brr = brr_value + i - 2;
                best_error = error;
            }
        }
    }

    // Set PCLK dividers for SCI.
    set_reg_bits( &hal_ll_hw_reg->ccr2, best_cks << HAL_LL_SCI_CCR2_CKS_OFFSET );

    // Set the bit rate register with the found value.
    write_reg( &hal_ll_hw_reg->ccr2, best_brr << HAL_LL_SCI_CCR2_BRR_OFFSET );
}

static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // Clear Serial Control Register before configuring SCI in I2C master mode.
    clear_reg( &hal_ll_hw_reg->ccr0 );

    // Set the ICR.IICSDAS and ICR.IICSCLS bits set to 11b to drive the SCLn and SDAn pins to high-impedance state.
    clear_reg( &hal_ll_hw_reg->icr );

    // Configure SCI to be in IIC mode.
    set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_MOD_IIC_MASK );
    clear_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CKE_MASK );

    // Configure IIC Mode registers.
    clear_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICINTM );
    clear_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICCSC );
    clear_reg_bit( &hal_ll_hw_reg->icr, HAL_LL_SCI_ICR_IICACKT );

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

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (0), or vice versa (1).
    if ( HAL_LL_SCI_SPI_MODE_0 == map->mode || HAL_LL_SCI_SPI_MODE_2 == map->mode ) {
        clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CPHA );
    } else {
        set_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CPHA );
    }

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if ( HAL_LL_SCI_SPI_MODE_0 == map->mode || HAL_LL_SCI_SPI_MODE_3 == map->mode ) {
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

static void hal_ll_sci_uart_set_stop_bits_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_SCI_UART_STOP_BITS_ONE:
            clear_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_STP );
            break;
        case HAL_LL_SCI_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_STP );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_data_bits_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( map->data_bit )
    {
        case HAL_LL_SCI_UART_DATA_BITS_7:
            set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CHR_7BITS );
            break;
        case HAL_LL_SCI_UART_DATA_BITS_8:
            set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CHR_8BITS );
            break;
        case HAL_LL_SCI_UART_DATA_BITS_9:
            set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CCR3_CHR_9BITS );

            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_parity_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( map->parity )
    {
        case HAL_LL_SCI_UART_PARITY_NONE:
            clear_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_PE );
            break;
        case HAL_LL_SCI_UART_PARITY_EVEN:
            set_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_PE );
            break;
        case HAL_LL_SCI_UART_PARITY_ODD:
            set_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_PE );
            set_reg_bit( &hal_ll_hw_reg->ccr1, HAL_LL_SCI_CCR1_PM );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_module( uint32_t base, hal_ll_sci_state_t module_state ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    switch ( module_state )
    {
        /* SCI module doesn't have any specific bitfield for enabling it, but
         * we disable UART work by switching source clock to external as this implementation
         * doesn't support the use of external clock for SCI module.
         */
        case HAL_LL_SCI_DISABLE:
            set_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CLOCK_EXTERNAL );
            break;

        case HAL_LL_SCI_ENABLE:
            clear_reg_bits( &hal_ll_hw_reg->ccr3, HAL_LL_SCI_CLOCK_EXTERNAL );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_transmitter( uint32_t base, hal_ll_sci_state_t module_state ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    switch ( module_state )
    {
        case HAL_LL_SCI_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TE );
            break;

        case HAL_LL_SCI_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_TE );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_receiver( uint32_t base, hal_ll_sci_state_t module_state ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    switch ( module_state )
    {
        case HAL_LL_SCI_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_RE );
            break;

        case HAL_LL_SCI_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->ccr0, HAL_LL_SCI_CCR0_RE );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_baud_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    /* Find the best BRR (bit rate register) value.
     *  In table g_async_baud, divisor values are stored for BGDM, ABCS, ABCSE and N values. Each set of divisors
     *  is tried, and the settings with the lowest bit rate error are stored. The formula to calculate BRR is as
     *  follows and it must be 255 or less:
     *  BRR = (PCLKA / (div_coefficient * baud)) - 1
     */
    uint32_t error = HAL_LL_SCI_BRR_ERROR_REFERENCE;
    uint32_t source_clock, temp_brr, divisor = 0U;
    uint8_t abcse2, abcse, abcs, bgdm, brr, cks;
    int32_t err_divisor, current_error;
    system_clocks_t system_clocks;
    uint16_t g_div_coefficient[ HAL_LL_SCI_NUM_DIVISORS ] = {
        4U, 6U, 8U, 16U, 24U, 32U, 64U, 96U, 128U, 256U, 384U, 512U, 1024U, 2048U,
    };

    SYSTEM_GetClocksFrequency( &system_clocks );

    source_clock = system_clocks.sciclk;

    for ( uint8_t select_16_base_clk_cycles = 0U;
          (( 1 >= select_16_base_clk_cycles ) && ( HAL_LL_SCI_BRR_ERROR_ACCEPTABLE < error ));
          select_16_base_clk_cycles++ )
    {
        for ( uint8_t i = 0U; HAL_LL_SCI_NUM_DIVISORS > i ; i++ )
        {
            if ( hal_ll_sci_brr_assert_divisors( select_16_base_clk_cycles, i ))
            {
                continue;
            }

            temp_brr = hal_ll_sci_brr_calculate( map->baud_rate.baud, source_clock, i );

            if (( HAL_LL_SCI_BRR_MAX ) >= temp_brr )
            {
                while ( temp_brr-- > 0U )
                {
                    current_error = hal_ll_sci_brr_get_error( temp_brr, source_clock, map->baud_rate.baud, i );

                    /* Take the absolute value of the bit rate error. */
                    if ( current_error < 0 )
                    {
                        current_error = -current_error;
                    }

                    /* If the absolute value of the bit rate error is less than the previous lowest absolute value of
                     *  bit rate error, then store these settings as the best value.
                     */
                    if ( current_error < error )
                    {
                        bgdm  = g_async_baud[i].bgdm;
                        abcs  = g_async_baud[i].abcs;
                        abcse = g_async_baud[i].abcse;
                        abcse2 = g_async_baud[i].abcse2;
                        cks = g_async_baud[i].cks;
                        brr = ( uint8_t ) temp_brr;
                        error = current_error;
                        map->baud_rate.real_baud = hal_ll_sci_get_baud_rate( source_clock, brr ,i );
                    }
                }
            }
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->ccr2, HAL_LL_SCI_CCR2_BPS_CONFIG_BITS_MASK );
    set_reg_bits( &hal_ll_hw_reg->ccr2, HAL_LL_SCI_CCR2_CONFIGURE( bgdm, abcs, abcse, abcse2 ));

    clear_reg_bits(  &hal_ll_hw_reg->ccr2, HAL_LL_SCI_CCR2_CKS_MASK );
    set_reg_bits( &hal_ll_hw_reg->ccr2, cks << HAL_LL_SCI_CCR2_CKS_OFFSET );

    clear_reg_bits( &hal_ll_hw_reg->ccr2, HAL_LL_SCI_CCR2_BRR_MASK );
    set_reg_bits( &hal_ll_hw_reg->ccr2, brr << HAL_LL_SCI_CCR2_BRR_OFFSET );
}

// ------------------------------------------------------------------------- END
