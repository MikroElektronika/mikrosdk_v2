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
#include "hal_ll_core.h"
#include "delays.h"
#include "mcu.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_sci_get_base_struct(_handle) ((volatile hal_ll_sci_base_handle_t *)_handle)

/*!< @brief Macros defining bit location. */
#define HAL_LL_SCI_SCR_TEIE         (2)
#define HAL_LL_SCI_SCR_RE           (4)
#define HAL_LL_SCI_SCR_TE           (5)
#define HAL_LL_SCI_SCR_RIE          (6)
#define HAL_LL_SCI_SCR_TIE          (7)

#define HAL_LL_SCI_SEMR_ABCSE       (3)

#define HAL_LL_SCI_SSR_TEND         (2)
#define HAL_LL_SCI_SSR_PER          (3)
#define HAL_LL_SCI_SSR_FER          (4)
#define HAL_LL_SCI_SSR_ORER         (5)
#define HAL_LL_SCI_SSR_RDRF         (6)
#define HAL_LL_SCI_SSR_TDRE         (7)

#define HAL_LL_SCI_SCMR_SMIF        (0)
#define HAL_LL_SCI_SCMR_SINV        (2)
#define HAL_LL_SCI_SCMR_SDIR        (3)
#define HAL_LL_SCI_SCMR_CHR1        (4)

#define HAL_LL_SCI_SIMR1_IICM       (0)
#define HAL_LL_SCI_SIMR1_IICDL      (3)

#define HAL_LL_SCI_SIMR2_IICINTM    (0)
#define HAL_LL_SCI_SIMR2_IICCSC     (1)
#define HAL_LL_SCI_SIMR2_IICACKT    (5)

#define HAL_LL_SCI_SIMR3_IICSTIF    (3)

#define HAL_LL_SCI_SISR_IICACKR     (0)

#define HAL_LL_SCI_SMR_STOP         (3)
#define HAL_LL_SCI_SMR_PM           (4)
#define HAL_LL_SCI_SMR_PE           (5)
#define HAL_LL_SCI_SMR_CHR          (6)
#define HAL_LL_SCI_SMR_CM           (7)

#define HAL_LL_SCI_SPMR_CKPOL       (6)
#define HAL_LL_SCI_SPMR_CKPH        (7)

/*!< @brief Macros defining register bit values. */
#define HAL_LL_SCI_CLOCK_EXTERNAL           (0x3)
#define HAL_LL_SCI_SMR_CKS_MASK             (0x03)
#define HAL_LL_SCI_SSR_ERROR_MASK           (0x38)

/*!< @brief Macros defining bit masks. */
#define HAL_LL_SCI_SCR_IRQ_MASK             ((1 << HAL_LL_SCI_SCR_RIE) | (1 << HAL_LL_SCI_SCR_TIE))
#define HAL_LL_SCI_SIMR3_START_MASK         (0x51)
#define HAL_LL_SCI_SIMR3_RESTART_MASK       (0x52)
#define HAL_LL_SCI_SIMR3_STOP_MASK          (0x54)
#define HAL_LL_SCI_SIMR3_RELEASE_MASK       (0xF0)

/*!< @brief SSCL/SSDA pin config -- open-drain with pull-up, as required by simple I2C mode */
#define HAL_LL_SCI_I2C_AF_CONFIG            ( GPIO_CFG_PORT_PULL_UP_ENABLE |\
                                              GPIO_CFG_DIGITAL_OUTPUT |\
                                              GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE )

/*!< @brief SCR enable mask for TIE, TE, RE and TEIE */
#define HAL_LL_SCI_SCR_ENABLE_MASK          (0xB4)

/*!< @brief SCR enable mask for TE and RE (set together in clock synchronous mode) */
#define HAL_LL_SCI_SCR_TE_RE_MASK           (0x30)

/*!< @brief Macros used for interrupt handling -- ICU.IRn is located at ICU base + vector number. */
#define HAL_LL_ICU_IR_BASE                  (0x00087000UL)
#define hal_ll_icu_ir(_vector)              (( volatile uint8_t * )( HAL_LL_ICU_IR_BASE + ( _vector )))

/*!< @brief Macros used for bit rate and SSDA delay calculations */
#define HAL_LL_SCI_SCL_STEP_BASE            (4UL)
#define HAL_LL_SCI_SCL_OVERHEAD_CYCLES      (15UL)
#define HAL_LL_SCI_BRR_COUNT_MAX            (256UL)
#define HAL_LL_SCI_UART_BRR_MAX_VALUE       (255)
#define HAL_LL_SCI_CKS_COUNT                (4)
#define HAL_LL_SCI_SCL_FALL_TIME_NS         (300UL)
#define HAL_LL_SCI_IICDL_MAX                (31UL)
#define HAL_LL_SCI_DUMMY_BYTE               (0xFF)
#define HAL_LL_SCI_SPI_STEP_BASE            (4UL)


/*!< @brief RSCI (RSCI8, RSCI9, RSCI11) macros defining bit location (RX26T Group manual sec. 33.2). */
#define HAL_LL_RSCI_SCR0_RE             (0)
#define HAL_LL_RSCI_SCR0_TE             (4)
#define HAL_LL_RSCI_SCR0_RIE            (16)
#define HAL_LL_RSCI_SCR0_TIE            (20)

#define HAL_LL_RSCI_SCR1_SPB2DT         (4)
#define HAL_LL_RSCI_SCR1_PE             (8)
#define HAL_LL_RSCI_SCR1_PM             (9)
#define HAL_LL_RSCI_SCR1_NFCS           (24)
#define HAL_LL_RSCI_SCR1_NFEN           (28)

#define HAL_LL_RSCI_SCR2_BGDM           (4)
#define HAL_LL_RSCI_SCR2_ABCS           (5)
#define HAL_LL_RSCI_SCR2_BRR            (8)
#define HAL_LL_RSCI_SCR2_BRME           (16)
#define HAL_LL_RSCI_SCR2_CKS            (20)
#define HAL_LL_RSCI_SCR2_MDDR           (24)

#define HAL_LL_RSCI_SCR3_CPHA           (0)
#define HAL_LL_RSCI_SCR3_CPOL           (1)
#define HAL_LL_RSCI_SCR3_SYNDIS         (7)
#define HAL_LL_RSCI_SCR3_CHR            (8)
#define HAL_LL_RSCI_SCR3_DDIR           (12)
#define HAL_LL_RSCI_SCR3_STOP           (14)
#define HAL_LL_RSCI_SCR3_MOD            (16)

#define HAL_LL_RSCI_SSR_ORER            (24)
#define HAL_LL_RSCI_SSR_TDRE            (29)

#define HAL_LL_RSCI_SSCR_ORERC          (24)
#define HAL_LL_RSCI_SSCR_APERC          (27)
#define HAL_LL_RSCI_SSCR_AFERC          (28)

#define HAL_LL_RSCI_SIMR_IICDL          (0)
#define HAL_LL_RSCI_SIMR_IICINTM        (8)
#define HAL_LL_RSCI_SIMR_IICCSC         (9)
#define HAL_LL_RSCI_SIMR_IICACKT        (13)

#define HAL_LL_RSCI_SSR_TEND            (30)
#define HAL_LL_RSCI_SSR_RDRF            (31)

#define HAL_LL_RSCI_SISR_IICACKR        (0)
#define HAL_LL_RSCI_SISR_IICSTIF        (3)

#define HAL_LL_RSCI_SISCR_IICSTIFC      (3)

/*!< @brief RSCI register bit values. */
#define HAL_LL_RSCI_SCR3_MOD_ASYNC      (0x0UL)
#define HAL_LL_RSCI_SCR3_MOD_SIMPLE_SPI (0x3UL)
#define HAL_LL_RSCI_SCR3_MOD_SIMPLE_I2C (0x4UL)
#define HAL_LL_RSCI_SCR3_CHR_9_BIT      (0x0UL)
#define HAL_LL_RSCI_SCR3_CHR_8_BIT      (0x2UL)
#define HAL_LL_RSCI_SCR3_CHR_7_BIT      (0x3UL)
#define HAL_LL_RSCI_SCR1_NFCS_DIV_1     (0x1UL)
#define HAL_LL_RSCI_SCR2_MDDR_DEFAULT   (0xFFUL)
#define HAL_LL_RSCI_SCR2_MDDR_MIN       (128UL)
#define HAL_LL_RSCI_SCR2_MDDR_DIVISOR   (256UL)
#define HAL_LL_RSCI_SCR2_BCP_DEFAULT    (0x4UL)

/*!< @brief RSCI bit masks. */
#define HAL_LL_RSCI_SIMR_START_MASK     (0x00510000UL)
#define HAL_LL_RSCI_SIMR_RESTART_MASK   (0x00520000UL)
#define HAL_LL_RSCI_SIMR_STOP_MASK      (0x00540000UL)
#define HAL_LL_RSCI_SIMR_RELEASE_MASK   (0x00F00000UL)
#define HAL_LL_RSCI_SIMR_SERIAL_MASK    (0x00000000UL)
#define HAL_LL_RSCI_SIMR_CONFIG_MASK    (0x0000FFFFUL)
#define HAL_LL_RSCI_SCR0_TE_RE_MASK     ((1UL << HAL_LL_RSCI_SCR0_TE) | (1UL << HAL_LL_RSCI_SCR0_RE))
#define HAL_LL_RSCI_SCR0_IRQ_MASK       ((1UL << HAL_LL_RSCI_SCR0_RIE) | (1UL << HAL_LL_RSCI_SCR0_TIE))
#define HAL_LL_RSCI_TDR_RESERVED_MASK   (0xFFFFFF00UL)
#define HAL_LL_RSCI_RDR_DATA_MASK       (0xFFUL)
#define HAL_LL_RSCI_SSCR_ERROR_MASK     ((1UL << HAL_LL_RSCI_SSCR_ORERC) | (1UL << HAL_LL_RSCI_SSCR_APERC) |\
                                         (1UL << HAL_LL_RSCI_SSCR_AFERC))
/*!< @brief SSCR: RDRFC, AFERC, APERC, MFFC, ORERC, DFERC, DPERC, DCMFC and ERSC (Figure 33.85 step 7). */
#define HAL_LL_RSCI_SSCR_CLEAR_MASK     (0x9D070010UL)

/*!< @brief Macros used for RSCI simple I2C bit rate calculation. */
// Bit rate = PCLK / ( 64 * 2^(2n-1) * ( N + 1 )) = PCLK / ( 32 * 4^n * ( N + 1 )) (Table 33.10).
#define HAL_LL_RSCI_I2C_STEP_BASE       (32UL)
// CKS other than PCLK/1 is prohibited for RSCI8 and RSCI9 (Table 33.12).
#define HAL_LL_RSCI_CKS_MAX_RSCI8_9     (0)
#define HAL_LL_RSCI_CKS_MAX_RSCI11      (3)

/*!< @brief Macros used for RSCI clock synchronous (simple SPI) bit rate calculation. */
// Bit rate = PCLK / ( 4 * 4^n * ( N + 1 )), halved divisor with BGDM = 1 (Table 33.10).
#define HAL_LL_RSCI_SPI_STEP_BASE       (4UL)
#define HAL_LL_RSCI_SPI_STEP_BASE_BGDM  (2UL)

/*!< @brief Macros used for RSCI asynchronous bit rate calculation. */
// Bit rate = PCLK / ( F/2 * 4^n * ( N + 1 )), F = 64, 32 or 16 depending on BGDM/ABCS (Table 33.10).
#define HAL_LL_RSCI_UART_STEP_COUNT     (3)

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

/*!< @brief RSCI register structure (RSCI8, RSCI9, RSCI11, RX26T Group manual sec. 33.2) */
typedef struct {
    uint32_t rdr;           // 0x00
    uint32_t tdr;           // 0x04
    uint32_t scr0;          // 0x08
    uint32_t scr1;          // 0x0C
    uint32_t scr2;          // 0x10
    uint32_t scr3;          // 0x14
    uint32_t scr4;          // 0x18
    uint32_t reserved0;     // 0x1C (HBSCR at 0x1E)
    uint32_t simr;          // 0x20
    uint32_t fcr;           // 0x24
    uint32_t reserved1[8];  // 0x28 - 0x44
    uint32_t ssr;           // 0x48
    uint32_t sisr;          // 0x4C
    uint32_t reserved2[6];  // 0x50 - 0x64
    uint32_t sscr;          // 0x68
    uint32_t siscr;         // 0x6C
} hal_ll_rsci_base_handle_t;

/*!< @brief Helper macro for getting RSCI module specific control register structure */
#define hal_ll_rsci_get_base_struct(_handle) ((volatile hal_ll_rsci_base_handle_t *)_handle)

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
  * @brief  Sets SCI pin alternate function state to work in SPI Master mode.
  *
  * Sets PSEL value for SCK, SMISO and SMOSI pins.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  hal_ll_state - Init/De-init
  * @return None
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
  * @brief  Calculate and set SCI bit rate.
  *
  * I2C Master mode: picks the CKS/BRR pair with the smallest bit rate error
  * and sets the SSDA output delay.
  * SPI Master mode: picks the smallest CKS for which BRR fits, never exceeding
  * the desired bit rate.
  *
  * @param[in]  base - SCI module base address.
  * @param[in]  speed - Desired bit rate.
  * @param[in]  sci_mode - SCI operating mode.
  * @return None
  */
static void hal_ll_sci_calculate_speed( uint32_t base, uint32_t speed, hal_ll_sci_mode_t sci_mode );

/**
  * @brief  Checks whether the module is an RSCI channel.
  *
  * RSCI8, RSCI9 and RSCI11 have a different register layout than SCI1/5/6/12.
  *
  * @param[in]  base - SCI module base address.
  * @return true if module is an RSCI channel, false otherwise.
  */
static bool hal_ll_sci_is_rsci( uint32_t base );

/**
  * @brief  Returns the source clock of the SCI module.
  *
  * RSCI8, RSCI9 and RSCI11 are clocked from PCLKA, SCI1/5/6/12 from PCLKB.
  *
  * @param[in]  base - SCI module base address.
  * @return Source clock frequency in Hz.
  */
static uint32_t hal_ll_sci_get_source_clock( uint32_t base );

/**
  * @brief  Returns the highest allowed SCR2.CKS value for the RSCI channel.
  *
  * CKS other than PCLK/1 is prohibited for RSCI8 and RSCI9 (Table 33.12).
  *
  * @param[in]  base - RSCI module base address.
  * @return Highest allowed CKS value.
  */
static uint32_t hal_ll_rsci_cks_max( uint32_t base );

/**
  * @brief  Returns the ICU interrupt request flag of the module TXI interrupt.
  *
  * @param[in]  module_index - SCI module index.
  * @return Pointer to ICU.IRn of the TXI interrupt, NULL if unknown.
  */
static volatile uint8_t *hal_ll_sci_txi_ir( uint8_t module_index );

/**
  * @brief  Initialize RSCI module in asynchronous (UART) mode on hardware level.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_rsci_uart_hw_init( hal_ll_sci_uart_hw_specifics_map_t *map );

/**
  * @brief  Calculate and set RSCI bit rate for asynchronous mode.
  *
  * Picks the CKS/BGDM/ABCS/BRR combination with the smallest bit rate error.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_rsci_uart_set_baud_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map );

/**
  * @brief  Initialize RSCI module in simple SPI Master mode on hardware level.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_rsci_spi_hw_init( hal_ll_sci_spi_hw_specifics_map_t *map );

/**
  * @brief  Perform a full duplex transfer on the RSCI bus configured in simple SPI Master mode.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buffer - Data to send, dummy data is sent if NULL.
  * @param[in]  *read_data_buffer - Received data storage, discarded if NULL.
  * @param[in]  data_length - Number of bytes to transfer.
  * @param[in]  dummy_data - Byte sent when there is no write buffer.
  * @return None
  */
static void hal_ll_rsci_spi_transfer_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                                 uint8_t *write_data_buffer,
                                                 uint8_t *read_data_buffer,
                                                 size_t data_length,
                                                 uint8_t dummy_data );

/**
  * @brief  Initialize RSCI module in simple I2C Master mode on hardware level.
  *
  * @param[in]  *map - Object specific context handler.
  * @return None
  */
static void hal_ll_rsci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map );

/**
  * @brief  Calculate and set RSCI bit rate for simple I2C Master mode.
  *
  * Picks the smallest CKS for which BRR fits, never exceeding the desired bit rate.
  *
  * @param[in]  *map - Object specific context handler.
  * @return uint32_t SSDA output delay (SIMR.IICDL) value matching the selected clock.
  */
static uint32_t hal_ll_rsci_i2c_calculate_speed( hal_ll_sci_i2c_hw_specifics_map_t *map );

/**
  * @brief  Waits for an RSCI register bit to reach the desired state.
  *
  * @param[in]  *reg - Register to poll.
  * @param[in]  bit - Bit position.
  * @param[in]  state - Desired bit state.
  * @param[in]  timeout - Timeout count, 0 waits forever.
  * @return true if the bit reached the state, false on timeout.
  */
static bool hal_ll_rsci_wait_bit( volatile uint32_t *reg, uint8_t bit, bool state, uint16_t timeout );

/**
  * @brief  Generates a start, restart or stop condition on the RSCI bus.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  condition_mask - SIMR condition request mask.
  * @param[in]  output_mask - SIMR SSCL/SSDA output select mask applied once the condition is generated.
  * @return true if the condition has been generated, false on timeout.
  */
static bool hal_ll_rsci_i2c_condition( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                       uint32_t condition_mask, uint32_t output_mask );

/**
  * @brief  Perform a write on the RSCI bus configured in simple I2C Master mode.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *write_data_buf - Pointer to data buffer.
  * @param[in]  len_write_data - Number of data to be written.
  * @param[in]  mode - End mode.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_rsci_i2c_write_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                      uint8_t *write_data_buf,
                                                      size_t len_write_data,
                                                      hal_ll_sci_i2c_end_mode_t mode );

/**
  * @brief  Perform a read on the RSCI bus configured in simple I2C Master mode.
  *
  * @param[in]  *map - Object specific context handler.
  * @param[in]  *read_data_buf - Pointer to data buffer.
  * @param[in]  len_read_data - Number of data to be read.
  * @param[in]  mode - End mode.
  * @return hal_ll_err_t Module specific values.
  */
static hal_ll_err_t hal_ll_rsci_i2c_read_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                     uint8_t *read_data_buf,
                                                     size_t len_read_data,
                                                     hal_ll_sci_i2c_end_mode_t mode );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS

void hal_ll_sci_uart_irq_enable( hal_ll_sci_uart_hw_specifics_map_t *map, hal_ll_sci_uart_irq_t irq ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    volatile hal_ll_rsci_base_handle_t *hal_ll_rsci_reg = hal_ll_rsci_get_base_struct( map->base );
    volatile uint8_t *txi_ir = hal_ll_sci_txi_ir( map->module_index );
    bool is_rsci = hal_ll_sci_is_rsci( map->base );

    switch ( irq ) {
        case HAL_LL_SCI_UART_IRQ_RX:
            if ( is_rsci )
                set_reg_bit( &hal_ll_rsci_reg->scr0, HAL_LL_RSCI_SCR0_RIE );
            else
                set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );
            break;
        case HAL_LL_SCI_UART_IRQ_TX:
            if ( is_rsci ) {
                uint32_t scr0_val;

                while ( !check_reg_bit( &hal_ll_rsci_reg->ssr, HAL_LL_RSCI_SSR_TEND ) ) {
                    // Brief window so a pending RXI is served while waiting.
                    hal_ll_core_enable_interrupts();
                    __asm__ volatile ( "nop" );
                    hal_ll_core_disable_interrupts();
                }

                // TE and TIE have to be set simultaneously for the TXI request to be generated.
                scr0_val = read_reg( &hal_ll_rsci_reg->scr0 );
                scr0_val &= ~( ( 1UL << HAL_LL_RSCI_SCR0_TIE ) | ( 1UL << HAL_LL_RSCI_SCR0_TE ) );
                write_reg( &hal_ll_rsci_reg->scr0, scr0_val );
                if ( txi_ir )
                    write_reg( txi_ir, 0 );
                write_reg( &hal_ll_rsci_reg->scr0, scr0_val | ( 1UL << HAL_LL_RSCI_SCR0_TIE ) | ( 1UL << HAL_LL_RSCI_SCR0_TE ) );
            } else {
                uint8_t scr_val;

                while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ) ) {
                    // Brief window so a pending RXI is served while waiting.
                    hal_ll_core_enable_interrupts();
                    __asm__ volatile ( "nop" );
                    hal_ll_core_disable_interrupts();
                }

                scr_val = read_reg( &hal_ll_hw_reg->scr );
                scr_val &= ( uint8_t )~( ( 1 << HAL_LL_SCI_SCR_TIE ) | ( 1 << HAL_LL_SCI_SCR_TE ) );
                write_reg( &hal_ll_hw_reg->scr, scr_val );
                if ( txi_ir )
                    write_reg( txi_ir, 0 );
                write_reg( &hal_ll_hw_reg->scr, scr_val | ( 1 << HAL_LL_SCI_SCR_TIE ) | ( 1 << HAL_LL_SCI_SCR_TE ) );
            }
            break;

        default:
            break;
    }
}

void hal_ll_sci_uart_irq_disable( hal_ll_sci_uart_hw_specifics_map_t *map, hal_ll_sci_uart_irq_t irq ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    volatile hal_ll_rsci_base_handle_t *hal_ll_rsci_reg = hal_ll_rsci_get_base_struct( map->base );
    bool is_rsci = hal_ll_sci_is_rsci( map->base );

    switch ( irq ) {
        case HAL_LL_SCI_UART_IRQ_RX:
            if ( is_rsci )
                clear_reg_bit( &hal_ll_rsci_reg->scr0, HAL_LL_RSCI_SCR0_RIE );
            else
                clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RIE );
            break;
        case HAL_LL_SCI_UART_IRQ_TX:
            if ( is_rsci )
                clear_reg_bit( &hal_ll_rsci_reg->scr0, HAL_LL_RSCI_SCR0_TIE );
            else
                clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TIE );
            break;

        default:
            break;
    }
}

void hal_ll_sci_uart_write( hal_ll_sci_uart_hw_specifics_map_t *map, uint8_t wr_data ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        volatile hal_ll_rsci_base_handle_t *hal_ll_rsci_reg = hal_ll_rsci_get_base_struct( map->base );

        while ( !check_reg_bit( &hal_ll_rsci_reg->ssr, HAL_LL_RSCI_SSR_TDRE ) );

        write_reg( &hal_ll_rsci_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | wr_data );
        return;
    }

    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ) );

    write_reg( &hal_ll_hw_reg->tdr, wr_data );
}

void hal_ll_sci_uart_write_polling( hal_ll_sci_uart_hw_specifics_map_t *map, uint8_t wr_data ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    volatile hal_ll_rsci_base_handle_t *hal_ll_rsci_reg = hal_ll_rsci_get_base_struct( map->base );
    bool is_rsci = hal_ll_sci_is_rsci( map->base );
    uint32_t time_counter = map->timeout_polling_write;

    // The wait can last a full frame, so scale the timeout for baud rates below 115200.
    if ( map->baud_rate.baud && ( map->baud_rate.baud < 115200UL ) ) {
        time_counter *= ( 115200UL / map->baud_rate.baud );
    }

    // Wait until the TDR register is empty.
    while ( is_rsci ? !check_reg_bit( &hal_ll_rsci_reg->ssr, HAL_LL_RSCI_SSR_TDRE ) :
                      !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ) ) {
        if ( !time_counter-- ) {
            return;
        }
    }

    if ( is_rsci )
        write_reg( &hal_ll_rsci_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | wr_data );
    else
        write_reg( &hal_ll_hw_reg->tdr, wr_data );
}

uint8_t hal_ll_sci_uart_read( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) )
        return ( uint8_t )( read_reg( &hal_ll_rsci_get_base_struct( map->base )->rdr ) & HAL_LL_RSCI_RDR_DATA_MASK );

    return read_reg( &hal_ll_hw_reg->rdr );
}

uint8_t hal_ll_sci_uart_read_polling( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    uint8_t rx_data;

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        volatile hal_ll_rsci_base_handle_t *hal_ll_rsci_reg = hal_ll_rsci_get_base_struct( map->base );

        while ( !check_reg_bit( &hal_ll_rsci_reg->ssr, HAL_LL_RSCI_SSR_RDRF ) ) {
            // An overrun error blocks further reception until cleared.
            if ( check_reg_bit( &hal_ll_rsci_reg->ssr, HAL_LL_RSCI_SSR_ORER ) ) {
                write_reg( &hal_ll_rsci_reg->sscr, 1UL << HAL_LL_RSCI_SSCR_ORERC );
            }
        }

        rx_data = ( uint8_t )( read_reg( &hal_ll_rsci_reg->rdr ) & HAL_LL_RSCI_RDR_DATA_MASK );
        hal_ll_sci_uart_clear_errors( map->base );

        return rx_data;
    }

    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ) ) {
        // An overrun error blocks further reception until cleared.
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ) ) {
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );
        }
    }

    rx_data = read_reg( &hal_ll_hw_reg->rdr );
    hal_ll_sci_uart_clear_errors( map->base );

    return rx_data;
}

void hal_ll_sci_uart_clear_regs( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        // TE = RE = 0 and interrupts disabled, so the mode/format registers can be rewritten.
        clear_reg( &hal_ll_rsci_get_base_struct( map->base )->scr0 );
        return;
    }

    clear_reg( &hal_ll_hw_reg->scr );
    clear_reg( &hal_ll_hw_reg->smr );
}

void hal_ll_sci_uart_clear_errors( uint32_t base ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    if ( hal_ll_sci_is_rsci( base ) ) {
        // RSCI status flags are read-only, they are cleared through SSCR.
        write_reg( &hal_ll_rsci_get_base_struct( base )->sscr, HAL_LL_RSCI_SSCR_ERROR_MASK );
        return;
    }

    uint8_t ssr = read_reg( &hal_ll_hw_reg->ssr );

    write_reg( &hal_ll_hw_reg->ssr, ( uint8_t )( 0xC0 | ( HAL_LL_SCI_SSR_ERROR_MASK & ~ssr ) ) );
}

hal_ll_err_t hal_ll_sci_i2c_write_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                              uint8_t *write_data_buf,
                                              size_t len_write_data,
                                              hal_ll_sci_i2c_end_mode_t mode ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_read;

    if ( hal_ll_sci_is_rsci( map->base ) )
        return hal_ll_rsci_i2c_write_bare_metal( map, write_data_buf, len_write_data, mode );

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
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint16_t time_counter = map->timeout;
    uint8_t dummy_byte = HAL_LL_SCI_DUMMY_BYTE;
    uint8_t dummy_read = 0;

    if ( hal_ll_sci_is_rsci( map->base ) )
        return hal_ll_rsci_i2c_read_bare_metal( map, read_data_buf, len_read_data, mode );

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

void hal_ll_sci_spi_write_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                      uint8_t *write_data_buffer,
                                      size_t write_data_length ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        hal_ll_rsci_spi_transfer_bare_metal( map, write_data_buffer, NULL, write_data_length, HAL_LL_SCI_DUMMY_BYTE );
        return;
    }

    while ( 0 < write_data_length-- ) {
        // An overrun error blocks both reception and transmission in clock synchronous mode.
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

        // Wait until transmit buffer is empty.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ));

        // Send byte from write buffer.
        write_reg( &hal_ll_hw_reg->tdr, ( uint8_t )( *write_data_buffer++ ) );

        // Wait until receive is complete.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ));

        // Dummy read to free the receive buffer.
        volatile uint8_t temp = read_reg( &hal_ll_hw_reg->rdr );
        ( void )temp;
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ));
}

void hal_ll_sci_spi_read_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                     uint8_t *read_data_buffer, size_t read_data_length,
                                     uint8_t dummy_data ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        hal_ll_rsci_spi_transfer_bare_metal( map, NULL, read_data_buffer, read_data_length, dummy_data );
        return;
    }

    while ( 0 < read_data_length-- ) {
        // An overrun error blocks both reception and transmission in clock synchronous mode.
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

        // Wait until transmit buffer is empty.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ));

        // Send dummy data to generate the clock.
        write_reg( &hal_ll_hw_reg->tdr, dummy_data );

        // Wait until receive is complete.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ));

        // Read received byte.
        *read_data_buffer++ = read_reg( &hal_ll_hw_reg->rdr );
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ));
}

void hal_ll_sci_spi_transfer_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                         uint8_t *write_data_buffer,
                                         uint8_t *read_data_buffer,
                                         size_t data_length ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        hal_ll_rsci_spi_transfer_bare_metal( map, write_data_buffer, read_data_buffer, data_length, HAL_LL_SCI_DUMMY_BYTE );
        return;
    }

    while ( 0 < data_length-- ) {
        // An overrun error blocks both reception and transmission in clock synchronous mode.
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
            clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

        // Wait until transmit buffer is empty.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TDRE ));

        // Send byte from write buffer, or dummy byte if there is none.
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : HAL_LL_SCI_DUMMY_BYTE;
        write_reg( &hal_ll_hw_reg->tdr, tx_data );

        // Wait until receive is complete.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_RDRF ));

        // Read received byte and store it if read buffer is provided.
        uint8_t rx_data = read_reg( &hal_ll_hw_reg->rdr );

        if ( read_data_buffer ) {
            *read_data_buffer++ = rx_data;
        }
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_TEND ));
}

void hal_ll_sci_module_enable( uint8_t module_index, bool hal_ll_state ) {
    volatile uint16_t *prcr = ( uint16_t * )HAL_LL_MSTPCR_PRCR_ADDR;
    write_reg( prcr, HAL_LL_MSTPCR_PRCR_UNLOCK_VAL );

    switch ( module_index ) {
        #ifdef SCI_MODULE_1
        case ( hal_ll_sci_module_num( SCI_MODULE_1 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB30_POS ));
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
        #ifdef SCI_MODULE_8
        case ( hal_ll_sci_module_num( SCI_MODULE_8 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRC, MSTPCRC_MSTPC27_POS )) : ( clear_reg_bit( _MSTPCRC, MSTPCRC_MSTPC27_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_9
        case ( hal_ll_sci_module_num( SCI_MODULE_9 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRC, MSTPCRC_MSTPC26_POS )) : ( clear_reg_bit( _MSTPCRC, MSTPCRC_MSTPC26_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_11
        case ( hal_ll_sci_module_num( SCI_MODULE_11 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRC, MSTPCRC_MSTPC24_POS )) : ( clear_reg_bit( _MSTPCRC, MSTPCRC_MSTPC24_POS ));
            break;
        #endif
        #ifdef SCI_MODULE_12
        case ( hal_ll_sci_module_num( SCI_MODULE_12 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB4_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB4_POS ));
            break;
        #endif

        default:
            break;
    }

    write_reg( prcr, HAL_LL_MSTPCR_PRCR_LOCK_VAL );
}

void hal_ll_sci_i2c_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    // Enable SCI peripheral
    hal_ll_sci_module_enable( map->module_index, true );

    hal_ll_sci_i2c_alternate_functions_set_state( map, true );

    if ( hal_ll_sci_is_rsci( map->base ) )
        hal_ll_rsci_i2c_hw_init( map );
    else
        hal_ll_sci_i2c_hw_init( map );
}

void hal_ll_sci_spi_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {
    // Enable SCI peripheral
    hal_ll_sci_module_enable( map->module_index, true );

    hal_ll_sci_spi_alternate_functions_set_state( map, true );

    if ( hal_ll_sci_is_rsci( map->base ) )
        hal_ll_rsci_spi_hw_init( map );
    else
        hal_ll_sci_spi_hw_init( map );
}

void hal_ll_sci_uart_hw_init( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    if ( hal_ll_sci_is_rsci( map->base ) ) {
        hal_ll_rsci_uart_hw_init( map );
        return;
    }

    uint8_t irq_bits = read_reg( &hal_ll_hw_reg->scr ) & HAL_LL_SCI_SCR_IRQ_MASK;

    // SCR/SMR must be re-initialized (with TE = RE = 0) before any mode/format change.
    hal_ll_sci_uart_clear_regs( map );

    hal_ll_sci_uart_set_data_bits_bare_metal( map );

    hal_ll_sci_uart_set_parity_bare_metal( map );

    hal_ll_sci_uart_set_stop_bits_bare_metal( map );

    hal_ll_sci_uart_set_baud_bare_metal( map );

    // Clear any receive error flags left over from a previous session -- ORER blocks further reception until cleared.
    clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );
    clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_FER );
    clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_PER );

    hal_ll_sci_uart_set_transmitter( map->base, HAL_LL_SCI_ENABLE );

    hal_ll_sci_uart_set_receiver( map->base, HAL_LL_SCI_ENABLE );

    hal_ll_sci_uart_set_module( map->base, HAL_LL_SCI_ENABLE );

    set_reg_bits( &hal_ll_hw_reg->scr, irq_bits );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_sci_i2c_alternate_functions_set_state( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                          bool hal_ll_state ) {
    module_struct module;

    if( (map->pins.pin_scl.pin_name != HAL_LL_PIN_NC) && (map->pins.pin_sda.pin_name != HAL_LL_PIN_NC) ) {
        module.pins[0] = VALUE( map->pins.pin_scl.pin_name, map->pins.pin_scl.pin_af );
        module.pins[1] = VALUE( map->pins.pin_sda.pin_name, map->pins.pin_sda.pin_af );
        module.pins[2] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = HAL_LL_SCI_I2C_AF_CONFIG;
        module.configs[1] = HAL_LL_SCI_I2C_AF_CONFIG;
        module.configs[2] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_sci_spi_alternate_functions_set_state( hal_ll_sci_spi_hw_specifics_map_t *map,
                                                          bool hal_ll_state ) {
    module_struct module;

    if (( map->pins.sck.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.miso.pin_name != HAL_LL_PIN_NC ) &&
        ( map->pins.mosi.pin_name != HAL_LL_PIN_NC )) {
        module.pins[0] = VALUE( map->pins.sck.pin_name, map->pins.sck.pin_af );
        module.pins[1] = VALUE( map->pins.miso.pin_name, map->pins.miso.pin_af );
        module.pins[2] = VALUE( map->pins.mosi.pin_name, map->pins.mosi.pin_af );
        module.pins[3] = GPIO_MODULE_STRUCT_END;

        module.configs[0] = GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[1] = GPIO_CFG_DIGITAL_INPUT;
        module.configs[2] = GPIO_CFG_DIGITAL_OUTPUT;
        module.configs[3] = GPIO_MODULE_STRUCT_END;

        hal_ll_gpio_module_struct_init( &module, hal_ll_state );
    }
}

static void hal_ll_sci_calculate_speed( uint32_t base, uint32_t speed, hal_ll_sci_mode_t sci_mode ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );
    uint32_t source_clock = hal_ll_sci_get_source_clock( base );
    uint32_t best_error = 0xFFFFFFFFUL;
    uint8_t best_cks = 0;
    uint8_t best_brr = 0;

    if ( HAL_LL_SCI_SPI_MODE == sci_mode ) {
        uint32_t divisor = HAL_LL_SCI_BRR_COUNT_MAX;
        uint8_t cks;

        // Bit rate = PCLK / ( 8 * 2^(2n-1) * ( N + 1 )) (Table 32.10); round the divisor up so the rate never exceeds the requested one.
        for ( cks = 0; cks < HAL_LL_SCI_CKS_COUNT; cks++ ) {
            uint32_t step = ( HAL_LL_SCI_SPI_STEP_BASE << ( 2 * cks )) * speed;

            divisor = ( source_clock + step - 1 ) / step;

            if ( HAL_LL_SCI_BRR_COUNT_MAX >= divisor ) {
                break;
            }
        }

        // Requested bit rate is below the minimum achievable, so use the slowest setting.
        if ( HAL_LL_SCI_CKS_COUNT == cks ) {
            cks = HAL_LL_SCI_CKS_COUNT - 1;
            divisor = HAL_LL_SCI_BRR_COUNT_MAX;
        }

        clear_reg_bits( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CKS_MASK );
        set_reg_bits( &hal_ll_hw_reg->smr, cks );

        write_reg( &hal_ll_hw_reg->brr, ( uint8_t )( divisor - 1 ));

        return;
    }

    // SCL period in cycles: 8 * ( N + 1 ) * 2^(2n-1) + 15 (Table 32.12).
    for ( uint8_t cks = 0; cks < HAL_LL_SCI_CKS_COUNT; cks++ ) {
        uint32_t step = HAL_LL_SCI_SCL_STEP_BASE << ( 2 * cks );
        uint32_t cycles = source_clock / speed;

        if ( cycles <= HAL_LL_SCI_SCL_OVERHEAD_CYCLES ) {
            continue;
        }

        uint32_t brr_plus_one = ( cycles - HAL_LL_SCI_SCL_OVERHEAD_CYCLES + step / 2 ) / step;

        if (( 0 == brr_plus_one ) || ( brr_plus_one > HAL_LL_SCI_BRR_COUNT_MAX )) {
            continue;
        }

        uint32_t real_speed = source_clock / ( step * brr_plus_one + HAL_LL_SCI_SCL_OVERHEAD_CYCLES );
        uint32_t error = ( real_speed > speed ) ? ( real_speed - speed ) : ( speed - real_speed );

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
    uint32_t baud_clock = source_clock >> ( 2 * best_cks );
    uint32_t iicdl = ((( baud_clock / 1000UL ) * HAL_LL_SCI_SCL_FALL_TIME_NS + 999999UL ) / 1000000UL ) + 1;

    if ( iicdl > HAL_LL_SCI_IICDL_MAX ) {
        iicdl = HAL_LL_SCI_IICDL_MAX;
    }

    write_reg( &hal_ll_hw_reg->simr1, ( uint8_t )( iicdl << HAL_LL_SCI_SIMR1_IICDL ));
}

static void hal_ll_sci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

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

static void hal_ll_sci_spi_hw_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint32_t source_clock = hal_ll_sci_get_source_clock( map->base );
    uint8_t cks;

    // Clear Serial Control Register before configuring SCI in SPI master mode (internal clock, SCKn as output).
    clear_reg( &hal_ll_hw_reg->scr );

    // Simple I2C mode off, no SSDA output delay.
    clear_reg( &hal_ll_hw_reg->simr1 );

    // Master mode, SSn# pin function and CTS disabled (single master).
    clear_reg( &hal_ll_hw_reg->spmr );

    // Choose whether transmit occurs on the transition from ACTIVE to IDLE (1), or vice versa (0).
    if (( HAL_LL_SCI_SPI_MODE_0 == map->mode ) || ( HAL_LL_SCI_SPI_MODE_2 == map->mode )) {
        set_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPH );
    } else {
        clear_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPH );
    }

    // Choose whether idle state for the clock is high level (1) or low level (0).
    if (( HAL_LL_SCI_SPI_MODE_0 == map->mode ) || ( HAL_LL_SCI_SPI_MODE_3 == map->mode )) {
        clear_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPOL );
    } else {
        set_reg_bit( &hal_ll_hw_reg->spmr, HAL_LL_SCI_SPMR_CKPOL );
    }

    // Set Simple SPI mode as Communication Mode.
    clear_reg( &hal_ll_hw_reg->smr );
    set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CM );

    // Set the format for transmission as Simple SPI, don't invert data, transfer MSB first.
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SMIF );
    clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SINV );
    set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_SDIR );

    // Asynchronous mode settings, noise filter and bit rate modulation are not used.
    clear_reg( &hal_ll_hw_reg->semr );

    // Don't invert TXD/RXD signals.
    clear_reg( &hal_ll_hw_reg->sptr );

    // Set the desired bit rate.
    hal_ll_sci_calculate_speed( map->base, map->speed, HAL_LL_SCI_SPI_MODE );

    cks = read_reg( &hal_ll_hw_reg->smr ) & HAL_LL_SCI_SMR_CKS_MASK;
    map->hw_actual_speed = source_clock /
                           (( HAL_LL_SCI_SPI_STEP_BASE << ( 2 * cks )) * ( read_reg( &hal_ll_hw_reg->brr ) + 1UL ));

    // Clear any receive error flags -- ORER blocks transmission in clock synchronous mode.
    if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER ))
        clear_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_SCI_SSR_ORER );

    // Enable transmitter and receiver at the same time.
    write_reg( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE_RE_MASK );
}

static void hal_ll_sci_uart_set_stop_bits_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( map->stop_bit ) {
        case HAL_LL_SCI_UART_STOP_BITS_ONE:
        default:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_STOP );
            break;
        case HAL_LL_SCI_UART_STOP_BITS_TWO:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_STOP );
            break;
    }
}

static void hal_ll_sci_uart_set_data_bits_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    // 8/7 bit selection needs SCMR.CHR1 = 1 (SCMR.CHR1/SMR.CHR combination);
    // 9 bit needs SCMR.CHR1 = 0 regardless of SMR.CHR.
    switch ( map->data_bit )
    {
        case HAL_LL_SCI_UART_DATA_BITS_7:
            set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_CHR1 );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CHR );
            break;
        case HAL_LL_SCI_UART_DATA_BITS_8:
        default:
            set_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_CHR1 );
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CHR );
            break;
        case HAL_LL_SCI_UART_DATA_BITS_9:
            clear_reg_bit( &hal_ll_hw_reg->scmr, HAL_LL_SCI_SCMR_CHR1 );
            break;
    }
}

static void hal_ll_sci_uart_set_parity_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );

    switch ( map->parity )
    {
        case HAL_LL_SCI_UART_PARITY_NONE:
        default:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PE );
            break;
        case HAL_LL_SCI_UART_PARITY_EVEN:
            clear_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PM );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PE );
            break;
        case HAL_LL_SCI_UART_PARITY_ODD:
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PM );
            set_reg_bit( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_PE );
            break;
    }
}

static void hal_ll_sci_uart_set_module( uint32_t base, hal_ll_sci_state_t module_state ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    switch ( module_state )
    {
        case HAL_LL_SCI_DISABLE:
            set_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_CLOCK_EXTERNAL );
            break;

        case HAL_LL_SCI_ENABLE:
            clear_reg_bits( &hal_ll_hw_reg->scr, HAL_LL_SCI_CLOCK_EXTERNAL );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_transmitter( uint32_t base, hal_ll_sci_state_t module_state ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    switch ( module_state )
    {
        case HAL_LL_SCI_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
            break;

        case HAL_LL_SCI_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_TE );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_receiver( uint32_t base, hal_ll_sci_state_t module_state ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( base );

    switch ( module_state )
    {
        case HAL_LL_SCI_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RE );
            break;

        case HAL_LL_SCI_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->scr, HAL_LL_SCI_SCR_RE );
            break;

        default:
            break;
    }
}

static void hal_ll_sci_uart_set_baud_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_sci_base_handle_t *hal_ll_hw_reg = hal_ll_sci_get_base_struct( map->base );
    uint32_t source_clock = hal_ll_sci_get_source_clock( map->base );
    uint32_t brr_value;
    uint8_t n;

    set_reg_bit( &hal_ll_hw_reg->semr, HAL_LL_SCI_SEMR_ABCSE );

    for ( n = 0; n <= HAL_LL_SCI_SMR_CKS_MASK; n++ ) {
        brr_value = ( source_clock / ( 6UL * ( 1UL << ( 2 * n ) ) * map->baud_rate.baud ) ) - 1;

        if ( HAL_LL_SCI_UART_BRR_MAX_VALUE >= brr_value ) {
            break;
        }
    }

    clear_reg_bits( &hal_ll_hw_reg->smr, HAL_LL_SCI_SMR_CKS_MASK );
    set_reg_bits( &hal_ll_hw_reg->smr, n );

    write_reg( &hal_ll_hw_reg->brr, brr_value );

    map->baud_rate.real_baud = source_clock / ( 6UL * ( 1UL << ( 2 * n ) ) * ( brr_value + 1 ) );
}

static bool hal_ll_sci_is_rsci( uint32_t base ) {
    ( void )base;

    #ifdef SCI_MODULE_8
    if ( HAL_LL_SCI8_BASE_ADDR == base )
        return true;
    #endif
    #ifdef SCI_MODULE_9
    if ( HAL_LL_SCI9_BASE_ADDR == base )
        return true;
    #endif
    #ifdef SCI_MODULE_11
    if ( HAL_LL_SCI11_BASE_ADDR == base )
        return true;
    #endif

    return false;
}

static uint32_t hal_ll_sci_get_source_clock( uint32_t base ) {
    system_clocks_t system_clocks;

    SYSTEM_GetClocksFrequency( &system_clocks );

    return hal_ll_sci_is_rsci( base ) ? system_clocks.pclka : system_clocks.pclkb;
}

static uint32_t hal_ll_rsci_cks_max( uint32_t base ) {
    ( void )base;

    #ifdef SCI_MODULE_11
    if ( HAL_LL_SCI11_BASE_ADDR == base )
        return HAL_LL_RSCI_CKS_MAX_RSCI11;
    #endif

    return HAL_LL_RSCI_CKS_MAX_RSCI8_9;
}

static volatile uint8_t *hal_ll_sci_txi_ir( uint8_t module_index ) {
    switch ( module_index ) {
        #ifdef SCI_MODULE_1
        case ( hal_ll_sci_module_num( SCI_MODULE_1 )):
            return hal_ll_icu_ir( SCI1_TXI_VECTOR );
        #endif
        #ifdef SCI_MODULE_5
        case ( hal_ll_sci_module_num( SCI_MODULE_5 )):
            return hal_ll_icu_ir( SCI5_TXI_VECTOR );
        #endif
        #ifdef SCI_MODULE_6
        case ( hal_ll_sci_module_num( SCI_MODULE_6 )):
            return hal_ll_icu_ir( SCI6_TXI_VECTOR );
        #endif
        #ifdef SCI_MODULE_8
        case ( hal_ll_sci_module_num( SCI_MODULE_8 )):
            return hal_ll_icu_ir( SCI8_TXI_VECTOR );
        #endif
        #ifdef SCI_MODULE_9
        case ( hal_ll_sci_module_num( SCI_MODULE_9 )):
            return hal_ll_icu_ir( SCI9_TXI_VECTOR );
        #endif
        #ifdef SCI_MODULE_11
        case ( hal_ll_sci_module_num( SCI_MODULE_11 )):
            return hal_ll_icu_ir( SCI11_TXI_VECTOR );
        #endif
        #ifdef SCI_MODULE_12
        case ( hal_ll_sci_module_num( SCI_MODULE_12 )):
            return hal_ll_icu_ir( SCI12_TXI_VECTOR );
        #endif

        default:
            return NULL;
    }
}

static bool hal_ll_rsci_wait_bit( volatile uint32_t *reg, uint8_t bit, bool state, uint16_t timeout ) {
    uint16_t time_counter = timeout;

    while( ( 0 != check_reg_bit( reg, bit )) != state ) {
        if( timeout ) {
            if( !time_counter-- )
                return false;
        }
    }

    return true;
}

static bool hal_ll_rsci_i2c_condition( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                       uint32_t condition_mask, uint32_t output_mask ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );

    // A condition may only be requested while IICSTIF is 0.
    write_reg( &hal_ll_hw_reg->siscr, 1UL << HAL_LL_RSCI_SISCR_IICSTIFC );

    // Request the condition together with SSCL/SSDA output select set to 01b, keeping the mode bits.
    write_reg( &hal_ll_hw_reg->simr,
               ( read_reg( &hal_ll_hw_reg->simr ) & HAL_LL_RSCI_SIMR_CONFIG_MASK ) | condition_mask );

    // Wait for the condition to be generated.
    if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->sisr, HAL_LL_RSCI_SISR_IICSTIF, true, map->timeout ))
        return false;

    // Clear flag and switch SSCL/SSDA outputs to the requested state.
    write_reg( &hal_ll_hw_reg->siscr, 1UL << HAL_LL_RSCI_SISCR_IICSTIFC );
    write_reg( &hal_ll_hw_reg->simr,
               ( read_reg( &hal_ll_hw_reg->simr ) & HAL_LL_RSCI_SIMR_CONFIG_MASK ) | output_mask );

    return true;
}

static uint32_t hal_ll_rsci_i2c_calculate_speed( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    uint32_t source_clock = hal_ll_sci_get_source_clock( map->base );
    uint32_t cks_max = hal_ll_rsci_cks_max( map->base );
    uint32_t divisor = HAL_LL_SCI_BRR_COUNT_MAX;
    uint32_t cks;

    // Round the divisor up so the rate never exceeds the requested one.
    for ( cks = 0; cks <= cks_max; cks++ ) {
        uint32_t step = ( HAL_LL_RSCI_I2C_STEP_BASE << ( 2 * cks )) * map->speed;

        divisor = ( source_clock + step - 1 ) / step;

        if ( HAL_LL_SCI_BRR_COUNT_MAX >= divisor ) {
            break;
        }
    }

    // Requested bit rate is below the minimum achievable, so use the slowest setting.
    if ( cks > cks_max ) {
        cks = cks_max;
        divisor = HAL_LL_SCI_BRR_COUNT_MAX;
    }

    // Bit rate modulation disabled, MDDR and BCP left at their initial values.
    write_reg( &hal_ll_hw_reg->scr2, ( HAL_LL_RSCI_SCR2_MDDR_DEFAULT << HAL_LL_RSCI_SCR2_MDDR ) |
                                     ( cks << HAL_LL_RSCI_SCR2_CKS ) |
                                     (( divisor - 1 ) << HAL_LL_RSCI_SCR2_BRR ) |
                                     HAL_LL_RSCI_SCR2_BCP_DEFAULT );

    // SSDA output delay has to exceed the SSCL fall time, and be within 1 to 31 in simple I2C mode.
    uint32_t baud_clock = source_clock >> ( 2 * cks );
    uint32_t iicdl = ((( baud_clock / 1000UL ) * HAL_LL_SCI_SCL_FALL_TIME_NS + 999999UL ) / 1000000UL ) + 1;

    if ( iicdl > HAL_LL_SCI_IICDL_MAX ) {
        iicdl = HAL_LL_SCI_IICDL_MAX;
    }

    return iicdl;
}

static void hal_ll_rsci_i2c_hw_init( hal_ll_sci_i2c_hw_specifics_map_t *map ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    uint32_t iicdl;

    // [1] Disable transmitter, receiver and interrupts before changing the operating mode.
    clear_reg( &hal_ll_hw_reg->scr0 );

    // [4] Bit rate first, since the SSDA output delay depends on the selected clock.
    iicdl = hal_ll_rsci_i2c_calculate_speed( map );

    // [2] Release SSCL/SSDA (high-impedance), ACK/NACK reception, clock synchronization,
    //     transmission/reception interrupt mode and SSDA output delay.
    write_reg( &hal_ll_hw_reg->simr, HAL_LL_RSCI_SIMR_RELEASE_MASK |
                                     ( 1UL << HAL_LL_RSCI_SIMR_IICACKT ) |
                                     ( 1UL << HAL_LL_RSCI_SIMR_IICCSC ) |
                                     ( 1UL << HAL_LL_RSCI_SIMR_IICINTM ) |
                                     ( iicdl << HAL_LL_RSCI_SIMR_IICDL ));

    // [3] Simple I2C mode, CKE = 00b, MSB first, no data inversion, FIFO off.
    //     SYNDIS must be 1, CPOL/CPHA must be 1 outside clock synchronous/simple SPI mode.
    write_reg( &hal_ll_hw_reg->scr3, ( HAL_LL_RSCI_SCR3_MOD_SIMPLE_I2C << HAL_LL_RSCI_SCR3_MOD ) |
                                     ( HAL_LL_RSCI_SCR3_CHR_8_BIT << HAL_LL_RSCI_SCR3_CHR ) |
                                     ( 1UL << HAL_LL_RSCI_SCR3_SYNDIS ) |
                                     ( 1UL << HAL_LL_RSCI_SCR3_CPOL ) |
                                     ( 1UL << HAL_LL_RSCI_SCR3_CPHA ));

    // [5] Noise filter on SSCL/SSDA (NFCS = 000b is prohibited in simple I2C mode), no CTS/RTS, no inversion.
    write_reg( &hal_ll_hw_reg->scr1, ( 1UL << HAL_LL_RSCI_SCR1_NFEN ) |
                                     ( HAL_LL_RSCI_SCR1_NFCS_DIV_1 << HAL_LL_RSCI_SCR1_NFCS ) |
                                     ( 1UL << HAL_LL_RSCI_SCR1_SPB2DT ));

    // Data match and timing adjustment functions are not used.
    clear_reg( &hal_ll_hw_reg->scr4 );

    // [7] Clear status flags.
    write_reg( &hal_ll_hw_reg->sscr, HAL_LL_RSCI_SSCR_CLEAR_MASK );
    write_reg( &hal_ll_hw_reg->siscr, 1UL << HAL_LL_RSCI_SISCR_IICSTIFC );

    // [8] Enable transmitter and receiver at the same time, interrupts are not used (polling).
    write_reg( &hal_ll_hw_reg->scr0, HAL_LL_RSCI_SCR0_TE_RE_MASK );
}

static hal_ll_err_t hal_ll_rsci_i2c_write_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                      uint8_t *write_data_buf,
                                                      size_t len_write_data,
                                                      hal_ll_sci_i2c_end_mode_t mode ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    volatile uint8_t dummy_read;

    // Wait for all previous transmissions to be ended.
    if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TEND, true, map->timeout ))
        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;

    // Generate the start condition and switch SSCL/SSDA to serial output.
    if ( !hal_ll_rsci_i2c_condition( map, HAL_LL_RSCI_SIMR_START_MASK, HAL_LL_RSCI_SIMR_SERIAL_MASK ))
        return HAL_LL_SCI_I2C_TIMEOUT_START;

    // Send the slave address and write command.
    write_reg( &hal_ll_hw_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | ( uint8_t )( map->address << 1 ));

    // In simple I2C mode the frame (including ACK) is complete once TEND is set.
    if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TEND, true, map->timeout ))
        return HAL_LL_SCI_I2C_TIMEOUT_WRITE;

    if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_RDRF ))
        dummy_read = ( uint8_t )read_reg( &hal_ll_hw_reg->rdr );

    // Check for ACK signal.
    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_RSCI_SISR_IICACKR ) ) {
        for( size_t i = 0; i < len_write_data; i++ ) {
            write_reg( &hal_ll_hw_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | write_data_buf[i] );

            if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TEND, true, map->timeout ))
                return HAL_LL_SCI_I2C_TIMEOUT_WRITE;

            if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_RDRF ))
                dummy_read = ( uint8_t )read_reg( &hal_ll_hw_reg->rdr );
        }
    }

    // If there is no need in RESTART condition - issue a STOP condition and release SSCL and SSDA pins.
    if ( HAL_LL_SCI_I2C_WRITE_THEN_READ != mode ) {
        if ( !hal_ll_rsci_i2c_condition( map, HAL_LL_RSCI_SIMR_STOP_MASK, HAL_LL_RSCI_SIMR_RELEASE_MASK ))
            return HAL_LL_SCI_I2C_TIMEOUT_STOP;
    }

    return 0;
}

static hal_ll_err_t hal_ll_rsci_i2c_read_bare_metal( hal_ll_sci_i2c_hw_specifics_map_t *map,
                                                     uint8_t *read_data_buf,
                                                     size_t len_read_data,
                                                     hal_ll_sci_i2c_end_mode_t mode ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    volatile uint8_t dummy_read;
    uint32_t condition_mask;

    if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_RDRF ))
        dummy_read = ( uint8_t )read_reg( &hal_ll_hw_reg->rdr );

    // Issue a START condition, or a RESTART condition after a write without STOP.
    condition_mask = ( HAL_LL_SCI_I2C_WRITE_THEN_READ != mode ) ?
                     HAL_LL_RSCI_SIMR_START_MASK : HAL_LL_RSCI_SIMR_RESTART_MASK;

    if ( !hal_ll_rsci_i2c_condition( map, condition_mask, HAL_LL_RSCI_SIMR_SERIAL_MASK ))
        return HAL_LL_SCI_I2C_TIMEOUT_START;

    // Send the slave address and read command.
    write_reg( &hal_ll_hw_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | ( uint8_t )(( map->address << 1 ) | 1 ));

    // Wait for the address frame (including ACK) to be complete.
    if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TEND, true, map->timeout ))
        return HAL_LL_SCI_I2C_TIMEOUT_READ;

    // Check if address has been acknowledged.
    if ( !check_reg_bit( &hal_ll_hw_reg->sisr, HAL_LL_RSCI_SISR_IICACKR ) ) {
        // Discard the address byte shifted into the receive buffer.
        if( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_RDRF ))
            dummy_read = ( uint8_t )read_reg( &hal_ll_hw_reg->rdr );

        // Enable ACK transmission.
        clear_reg_bit( &hal_ll_hw_reg->simr, HAL_LL_RSCI_SIMR_IICACKT );

        for( size_t i = 0; i < len_read_data; i++ ) {
            // NACK is transmitted in response to the last byte.
            if ( ( len_read_data - 1 ) == i )
                set_reg_bit( &hal_ll_hw_reg->simr, HAL_LL_RSCI_SIMR_IICACKT );

            // Send 0xFF to trigger clock line and trace incoming data byte.
            write_reg( &hal_ll_hw_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | HAL_LL_SCI_DUMMY_BYTE );

            // Wait for data to be written into Receive Buffer.
            if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_RDRF, true, map->timeout ))
                return HAL_LL_SCI_I2C_TIMEOUT_READ;

            // Read received data.
            read_data_buf[i] = ( uint8_t )read_reg( &hal_ll_hw_reg->rdr );

            // Wait for the ACK/NACK bit to be sent.
            if ( !hal_ll_rsci_wait_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TEND, true, map->timeout ))
                return HAL_LL_SCI_I2C_TIMEOUT_READ;
        }
    }

    // Generate the stop condition and release SSCL and SSDA pins.
    if ( !hal_ll_rsci_i2c_condition( map, HAL_LL_RSCI_SIMR_STOP_MASK, HAL_LL_RSCI_SIMR_RELEASE_MASK ))
        return HAL_LL_SCI_I2C_TIMEOUT_STOP;

    // Default back to NACK transmission and ACK/NACK reception.
    set_reg_bit( &hal_ll_hw_reg->simr, HAL_LL_RSCI_SIMR_IICACKT );

    return 0;
}

static void hal_ll_rsci_uart_set_baud_bare_metal( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    uint32_t source_clock = hal_ll_sci_get_source_clock( map->base );
    // F/2 for F = 64 (BGDM = 0, ABCS = 0), 32 (BGDM = 1, ABCS = 0) and 16 (BGDM = 1, ABCS = 1).
    static const uint8_t step_base[ HAL_LL_RSCI_UART_STEP_COUNT ] = { 32, 16, 8 };
    static const uint8_t step_bgdm[ HAL_LL_RSCI_UART_STEP_COUNT ] = { 0, 1, 1 };
    static const uint8_t step_abcs[ HAL_LL_RSCI_UART_STEP_COUNT ] = { 0, 0, 1 };
    uint32_t cks_max = hal_ll_rsci_cks_max( map->base );
    uint32_t best_error = 0xFFFFFFFFUL;
    uint32_t best_cks = cks_max;
    uint32_t best_step = 0;
    uint32_t best_divisor = HAL_LL_SCI_BRR_COUNT_MAX;
    uint32_t best_speed = 0;
    uint32_t mddr = HAL_LL_RSCI_SCR2_MDDR_DEFAULT;
    uint32_t brme = 0;

    for ( uint32_t cks = 0; cks <= cks_max; cks++ ) {
        for ( uint8_t s = 0; s < HAL_LL_RSCI_UART_STEP_COUNT; s++ ) {
            uint32_t step_clock = source_clock / (( uint32_t )step_base[ s ] << ( 2 * cks ));
            uint32_t divisor = ( step_clock + map->baud_rate.baud / 2 ) / map->baud_rate.baud;

            if (( 0 == divisor ) || ( HAL_LL_SCI_BRR_COUNT_MAX < divisor )) {
                continue;
            }

            uint32_t real_speed = step_clock / divisor;
            uint32_t error = ( real_speed > map->baud_rate.baud ) ? ( real_speed - map->baud_rate.baud ) :
                                                                    ( map->baud_rate.baud - real_speed );

            // Strictly better only, so the higher oversampling wins on a tie.
            if ( error < best_error ) {
                best_error = error;
                best_cks = cks;
                best_step = s;
                best_divisor = divisor;
                best_speed = real_speed;
            }
        }
    }

    // Requested baud rate is below the minimum achievable with BRR alone (e.g. 9600 on RSCI8/RSCI9, where
    // CKS is fixed to PCLK/1) -- use the slowest setting and slow it further down with bit rate modulation:
    // B = PCLK / ( F/2 * 4^n * ( N + 1 )) * M / 256, 128 <= M <= 255 (Table 33.24).
    if ( 0xFFFFFFFFUL == best_error ) {
        uint32_t slowest_speed = ( source_clock /
                                 (( uint32_t )step_base[ best_step ] << ( 2 * best_cks ))) / best_divisor;

        mddr = ( map->baud_rate.baud * HAL_LL_RSCI_SCR2_MDDR_DIVISOR + slowest_speed / 2 ) / slowest_speed;

        if ( HAL_LL_RSCI_SCR2_MDDR_MIN > mddr ) {
            mddr = HAL_LL_RSCI_SCR2_MDDR_MIN;
        } else if ( HAL_LL_RSCI_SCR2_MDDR_DEFAULT < mddr ) {
            mddr = HAL_LL_RSCI_SCR2_MDDR_DEFAULT;
        }

        brme = 1;
        best_speed = ( slowest_speed * mddr ) / HAL_LL_RSCI_SCR2_MDDR_DIVISOR;
    }

    // BCP left at its initial value.
    write_reg( &hal_ll_hw_reg->scr2, ( mddr << HAL_LL_RSCI_SCR2_MDDR ) |
                                     ( best_cks << HAL_LL_RSCI_SCR2_CKS ) |
                                     ( brme << HAL_LL_RSCI_SCR2_BRME ) |
                                     (( best_divisor - 1 ) << HAL_LL_RSCI_SCR2_BRR ) |
                                     (( uint32_t )step_abcs[ best_step ] << HAL_LL_RSCI_SCR2_ABCS ) |
                                     (( uint32_t )step_bgdm[ best_step ] << HAL_LL_RSCI_SCR2_BGDM ) |
                                     HAL_LL_RSCI_SCR2_BCP_DEFAULT );

    map->baud_rate.real_baud = best_speed;
}

static void hal_ll_rsci_uart_hw_init( hal_ll_sci_uart_hw_specifics_map_t *map ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    uint32_t irq_bits = read_reg( &hal_ll_hw_reg->scr0 ) & HAL_LL_RSCI_SCR0_IRQ_MASK;
    uint32_t scr1 = ( 1UL << HAL_LL_RSCI_SCR1_SPB2DT );
    uint32_t scr3;

    // SCR1-SCR4 are writable only while TE = RE = 0.
    clear_reg( &hal_ll_hw_reg->scr0 );

    switch ( map->parity ) {
        case HAL_LL_SCI_UART_PARITY_EVEN:
            scr1 |= ( 1UL << HAL_LL_RSCI_SCR1_PE );
            break;
        case HAL_LL_SCI_UART_PARITY_ODD:
            scr1 |= ( 1UL << HAL_LL_RSCI_SCR1_PE ) | ( 1UL << HAL_LL_RSCI_SCR1_PM );
            break;
        case HAL_LL_SCI_UART_PARITY_NONE:
        default:
            break;
    }

    // No noise filter, CTS/RTS or signal inversion.
    write_reg( &hal_ll_hw_reg->scr1, scr1 );

    hal_ll_rsci_uart_set_baud_bare_metal( map );

    // Asynchronous mode, on-chip baud rate generator (CKE = 00b), LSB first, non-FIFO.
    // SYNDIS must be 1, CPOL/CPHA must be 1 outside clock synchronous/simple SPI mode.
    scr3 = ( HAL_LL_RSCI_SCR3_MOD_ASYNC << HAL_LL_RSCI_SCR3_MOD ) |
           ( 1UL << HAL_LL_RSCI_SCR3_DDIR ) |
           ( 1UL << HAL_LL_RSCI_SCR3_SYNDIS ) |
           ( 1UL << HAL_LL_RSCI_SCR3_CPOL ) |
           ( 1UL << HAL_LL_RSCI_SCR3_CPHA );

    switch ( map->data_bit ) {
        case HAL_LL_SCI_UART_DATA_BITS_7:
            scr3 |= ( HAL_LL_RSCI_SCR3_CHR_7_BIT << HAL_LL_RSCI_SCR3_CHR );
            break;
        case HAL_LL_SCI_UART_DATA_BITS_9:
            scr3 |= ( HAL_LL_RSCI_SCR3_CHR_9_BIT << HAL_LL_RSCI_SCR3_CHR );
            break;
        case HAL_LL_SCI_UART_DATA_BITS_8:
        default:
            scr3 |= ( HAL_LL_RSCI_SCR3_CHR_8_BIT << HAL_LL_RSCI_SCR3_CHR );
            break;
    }

    if ( HAL_LL_SCI_UART_STOP_BITS_TWO == map->stop_bit ) {
        scr3 |= ( 1UL << HAL_LL_RSCI_SCR3_STOP );
    }

    write_reg( &hal_ll_hw_reg->scr3, scr3 );

    // Data match and timing adjustment functions are not used.
    clear_reg( &hal_ll_hw_reg->scr4 );

    // Clear any receive error flags left over from a previous session -- ORER blocks further reception until cleared.
    write_reg( &hal_ll_hw_reg->sscr, HAL_LL_RSCI_SSCR_CLEAR_MASK );

    // Enable transmitter and receiver, restoring the interrupt enables (TE and TIE set together).
    write_reg( &hal_ll_hw_reg->scr0, HAL_LL_RSCI_SCR0_TE_RE_MASK | irq_bits );
}

static void hal_ll_rsci_spi_hw_init( hal_ll_sci_spi_hw_specifics_map_t *map ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );
    uint32_t source_clock = hal_ll_sci_get_source_clock( map->base );
    uint32_t cks_max = hal_ll_rsci_cks_max( map->base );
    uint32_t cks = 0;
    uint32_t bgdm = 0;
    uint32_t step_clock = 0;
    uint32_t divisor = HAL_LL_SCI_BRR_COUNT_MAX;
    uint32_t scr3;
    bool found = false;

    // Disable transmitter, receiver and interrupts, SSn# pin function disabled (single master).
    clear_reg( &hal_ll_hw_reg->scr0 );

    // No CTS/RTS, half-duplex, loopback or signal inversion.
    write_reg( &hal_ll_hw_reg->scr1, ( 1UL << HAL_LL_RSCI_SCR1_SPB2DT ));

    // Steps in increasing order: ( CKS, BGDM ) = ( 0, 1 ), ( 0, 0 ), ( 1, 1 ), ( 1, 0 ), ...
    // The first fit gives the finest resolution; round the divisor up so the rate never exceeds the requested one.
    for ( cks = 0; ( cks <= cks_max ) && !found; cks++ ) {
        for ( bgdm = 2; bgdm-- > 0; ) {
            uint32_t step = ( bgdm ? HAL_LL_RSCI_SPI_STEP_BASE_BGDM : HAL_LL_RSCI_SPI_STEP_BASE ) << ( 2 * cks );

            step_clock = source_clock / step;
            divisor = ( step_clock + map->speed - 1 ) / map->speed;

            if ( HAL_LL_SCI_BRR_COUNT_MAX >= divisor ) {
                found = true;
                break;
            }
        }
    }

    if ( found ) {
        // The outer loop incremented cks once more before exiting.
        cks--;
    } else {
        // Requested bit rate is below the minimum achievable, so use the slowest setting.
        cks = cks_max;
        bgdm = 0;
        step_clock = source_clock / ( HAL_LL_RSCI_SPI_STEP_BASE << ( 2 * cks ));
        divisor = HAL_LL_SCI_BRR_COUNT_MAX;
    }

    // Bit rate modulation must be disabled in simple SPI mode.
    write_reg( &hal_ll_hw_reg->scr2, ( HAL_LL_RSCI_SCR2_MDDR_DEFAULT << HAL_LL_RSCI_SCR2_MDDR ) |
                                     ( cks << HAL_LL_RSCI_SCR2_CKS ) |
                                     (( divisor - 1 ) << HAL_LL_RSCI_SCR2_BRR ) |
                                     ( bgdm << HAL_LL_RSCI_SCR2_BGDM ) |
                                     HAL_LL_RSCI_SCR2_BCP_DEFAULT );

    map->hw_actual_speed = step_clock / divisor;

    // Simple SPI mode, master (CKE = 00b, SCKn as clock output), MSB first, non-FIFO.
    scr3 = ( HAL_LL_RSCI_SCR3_MOD_SIMPLE_SPI << HAL_LL_RSCI_SCR3_MOD ) |
           ( HAL_LL_RSCI_SCR3_CHR_8_BIT << HAL_LL_RSCI_SCR3_CHR ) |
           ( 1UL << HAL_LL_RSCI_SCR3_SYNDIS );

    // Idle state of the clock: high (CPOL = 1) for modes 2 and 3.
    if (( HAL_LL_SCI_SPI_MODE_2 == map->mode ) || ( HAL_LL_SCI_SPI_MODE_3 == map->mode )) {
        scr3 |= ( 1UL << HAL_LL_RSCI_SCR3_CPOL );
    }

    // Data changes on the odd edge and is sampled on the even edge (CPHA = 1) for modes 1 and 3.
    if (( HAL_LL_SCI_SPI_MODE_1 == map->mode ) || ( HAL_LL_SCI_SPI_MODE_3 == map->mode )) {
        scr3 |= ( 1UL << HAL_LL_RSCI_SCR3_CPHA );
    }

    write_reg( &hal_ll_hw_reg->scr3, scr3 );

    // Data match and timing adjustment functions are not used.
    clear_reg( &hal_ll_hw_reg->scr4 );

    // Clear any receive error flags -- ORER stops reception in simple SPI mode.
    write_reg( &hal_ll_hw_reg->sscr, HAL_LL_RSCI_SSCR_CLEAR_MASK );

    // Enable transmitter and receiver at the same time (receive only is prohibited in master mode).
    write_reg( &hal_ll_hw_reg->scr0, HAL_LL_RSCI_SCR0_TE_RE_MASK );
}

static void hal_ll_rsci_spi_transfer_bare_metal( hal_ll_sci_spi_hw_specifics_map_t *map,
                                                 uint8_t *write_data_buffer,
                                                 uint8_t *read_data_buffer,
                                                 size_t data_length,
                                                 uint8_t dummy_data ) {
    volatile hal_ll_rsci_base_handle_t *hal_ll_hw_reg = hal_ll_rsci_get_base_struct( map->base );

    while ( 0 < data_length-- ) {
        // An overrun error stops reception in simple SPI mode.
        if ( check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_ORER ))
            write_reg( &hal_ll_hw_reg->sscr, 1UL << HAL_LL_RSCI_SSCR_ORERC );

        // Wait until transmit buffer is empty.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TDRE ));

        // Send byte from write buffer, or dummy byte if there is none.
        uint8_t tx_data = ( write_data_buffer ) ? *write_data_buffer++ : dummy_data;
        write_reg( &hal_ll_hw_reg->tdr, HAL_LL_RSCI_TDR_RESERVED_MASK | tx_data );

        // Wait until receive is complete.
        while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_RDRF ));

        // Read received byte (this also clears RDRF) and store it if read buffer is provided.
        uint8_t rx_data = ( uint8_t )( read_reg( &hal_ll_hw_reg->rdr ) & HAL_LL_RSCI_RDR_DATA_MASK );

        if ( read_data_buffer ) {
            *read_data_buffer++ = rx_data;
        }
    }

    // Wait until transmit is complete.
    while ( !check_reg_bit( &hal_ll_hw_reg->ssr, HAL_LL_RSCI_SSR_TEND ));
}

// ------------------------------------------------------------------------- END
