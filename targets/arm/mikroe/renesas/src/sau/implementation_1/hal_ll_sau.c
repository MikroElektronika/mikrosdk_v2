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
 * @file  hal_ll_sau.c
 * @brief sau HAL LOW LEVEL layer implementation.
 */

#include <math.h>
#include "hal_ll_gpio.h"
#include "hal_ll_sau.h"
#include "hal_ll_mstpcr.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS

/*!< @brief Helper macro for getting module specific control register structure */
#define hal_ll_sau_get_base_struct(_handle) ((hal_ll_sau_base_handle_t *)_handle)

/*!< @brief Macros defining bit location. */
#define HAL_LL_SAU_SMR_MD0 0
#define HAL_LL_SAU_SMR_CCS 14
#define HAL_LL_SAU_SMR_CKS 14

#define HAL_LL_SAU_SCR_DIR 7
#define HAL_LL_SAU_SCR_EOC 10

#define HAL_LL_SAU_SDR_STCLK_BIT_START 9

/*!< @brief Macros defining bit masks. */
#define HAL_LL_SAU_SMR_MD1_MASK_UART 0x6

#define HAL_LL_SAU_SCR_DLS_MASK_9BITS 0x1
#define HAL_LL_SAU_SCR_DLS_MASK_7BITS 0x2
#define HAL_LL_SAU_SCR_DLS_MASK_8BITS 0x3
#define HAL_LL_SAU_SCR_DLS_MASK 0x3
#define HAL_LL_SAU_SCR_SLC_MASK_1STOP 0x10
#define HAL_LL_SAU_SCR_SLC_MASK_2STOP 0x20
#define HAL_LL_SAU_SCR_SLC_MASK 0x30
#define HAL_LL_SAU_SCR_PTC_MASK 0x300
#define HAL_LL_SAU_SCR_PTC_MASK_EVEN 0x200
#define HAL_LL_SAU_SCR_PTC_MASK_ODD 0x300
#define HAL_LL_SAU_SCR_TRXE_MASK_UART 0x8000

/*!< @brief SAU register structure */
typedef struct {
    uint16_t sdr[4];         /*!< (@ 0x00000000) Serial Data Register                            */
    uint16_t _unused1[124];
    uint16_t ssr[4];         /*!< (@ 0x00000100) Serial Status Register                          */
    uint16_t sir[4];         /*!< (@ 0x00000108) Serial Flag Clear Trigger Register              */
    uint16_t smr[4];         /*!< (@ 0x00000110) Serial Mode Register                            */
    uint16_t scr[4];         /*!< (@ 0x00000118) Serial Communication Operation Setting Register */
    uint16_t se;             /*!< (@ 0x00000120) Serial Channel Enable Status                    */
    uint16_t ss;             /*!< (@ 0x00000122) Serial Channel Start Register                   */
    uint16_t st;             /*!< (@ 0x00000124) Serial Channel Stop Register                    */
    uint16_t sps;            /*!< (@ 0x00000126) Serial Clock Select Register                    */
    uint16_t so;             /*!< (@ 0x00000128) Serial Output Register                          */
    uint16_t soe;            /*!< (@ 0x0000012A) Serial Output Enable Register                   */
    uint16_t _unused2[4];
    uint16_t sol;            /*!< (@ 0x00000134) Serial Output Level Register                    */
} hal_ll_sau_base_handle_t;

/*!< @brief I2C hw specific error values */
typedef enum {
    HAL_LL_SAU_SUCCESS = 0,
    HAL_LL_SAU_WRONG_PINS,
    HAL_LL_SAU_MODULE_ERROR,

    HAL_LL_SAU_ERROR = (-1)
} hal_ll_sau_err_t;

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
static void hal_ll_sau_uart_set_stop_bits_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map );

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
static void hal_ll_sau_uart_set_data_bits_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map );

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
static void hal_ll_sau_uart_set_parity_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map );

/**
 * @brief  Sets module clock value.
 *
 * Enables/disables specific SAU_UART module
 * clock gate.
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  pin_state - true(enable clock) / false(disable clock)
 *
 * @return void None.
 */
static void hal_ll_sau_uart_set_module( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_state_t pin_state );

/**
 * @brief  Sets module TX line state.
 *
 * Enables/disables specific SAU_UART module
 * TX pin state
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  pin_state - true(enable transmitter pin) / false(disable transmitter pin)
 *
 * @return void None.
 */
static void hal_ll_sau_uart_set_transmitter( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_state_t pin_state );

/**
 * @brief  Sets module RX line state.
 *
 * Enables/disables specific SAU_UART module
 * RX pin state
 *
 * @param[in]  map - Object specific context handler.
 * @param[in]  pin_state - true(enable receive pin) / false(disable receive pin)
 *
 * @return void None.
 */
static void hal_ll_sau_uart_set_receiver( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_state_t pin_state );

/**
 * @brief  Sets SAU_UART module baudrate.
 *
 * Sets desired baud rate for SAU module configured in UART mode.
 *
 * @param[in]  map - Object specific context handler.
 *
 * @return void None.
 */
static void hal_ll_sau_uart_set_baud_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map );

// ----------------------------------------------- PUBLIC FUNCTION DEFINITIONS

void hal_ll_sau_uart_irq_enable( hal_ll_base_addr_t base, hal_ll_sau_uart_irq_t irq ) {

}

void hal_ll_sau_uart_irq_disable( hal_ll_base_addr_t base, hal_ll_sau_uart_irq_t irq ) {

}

void hal_ll_sau_uart_write( hal_ll_base_addr_t base, uint8_t wr_data) {

}

void hal_ll_sau_uart_write_polling( hal_ll_sau_uart_hw_specifics_map_t *map, uint8_t wr_data) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    write_reg( &hal_ll_hw_reg->sdr[ map->sau_channel], wr_data );
}

uint8_t hal_ll_sau_uart_read( hal_ll_base_addr_t base ) {

}

uint8_t hal_ll_sau_uart_read_polling( hal_ll_base_addr_t base ) {

}

void hal_ll_sau_set_clock( hal_ll_pin_name_t module_index, bool hal_ll_state ) {
    switch ( module_index ) {
        #ifdef SAU_UART_MODULE_0
        case ( hal_ll_sau_module_num( SAU_UART_MODULE_0 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB6_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB6_POS ));
            break;
        #endif
        #ifdef SAU_UART_MODULE_1
        case ( hal_ll_sau_module_num( SAU_UART_MODULE_1 )):
            ( hal_ll_state == false ) ? ( set_reg_bit( _MSTPCRB, MSTPCRB_MSTPB7_POS )) : ( clear_reg_bit( _MSTPCRB, MSTPCRB_MSTPB7_POS ));
            break;
        #endif
    }
}

void hal_ll_sau_uart_clear_regs( hal_ll_sau_uart_hw_specifics_map_t *map ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    clear_reg( &hal_ll_hw_reg->smr[ map->sau_channel ] );
    clear_reg( &hal_ll_hw_reg->scr[ map->sau_channel ] );
    clear_reg( &hal_ll_hw_reg->sol );
    clear_reg( &hal_ll_hw_reg->soe );
    clear_reg( &hal_ll_hw_reg->ss );
}

void hal_ll_sau_uart_hw_init( hal_ll_sau_uart_hw_specifics_map_t *map ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    hal_ll_sau_uart_clear_regs( map );

    // Configure SAU to be in UART mode.
    set_reg_bits( &hal_ll_hw_reg->smr[map->sau_channel], HAL_LL_SAU_SMR_MD1_MASK_UART );

    hal_ll_sau_uart_set_data_bits_bare_metal( map );

    hal_ll_sau_uart_set_parity_bare_metal( map );

    hal_ll_sau_uart_set_stop_bits_bare_metal( map );

    hal_ll_sau_uart_set_baud_bare_metal( map );

    hal_ll_sau_uart_set_module( map, HAL_LL_SAU_ENABLE );

    hal_ll_sau_uart_set_transmitter( map, HAL_LL_SAU_ENABLE );

    hal_ll_sau_uart_set_receiver( map, HAL_LL_SAU_ENABLE );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_sau_uart_set_baud_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );


}

static void hal_ll_sau_uart_set_stop_bits_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    clear_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_SLC_MASK );
    switch ( map->stop_bit ) {
        case HAL_LL_SAU_UART_STOP_BITS_ONE:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_SLC_MASK_1STOP );
            break;
        case HAL_LL_SAU_UART_STOP_BITS_TWO:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_SLC_MASK_2STOP );
            break;

        default:
            break;
    }
}

static void hal_ll_sau_uart_set_data_bits_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    clear_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_DLS_MASK );
    switch ( map->data_bit ) {
        case HAL_LL_SAU_UART_DATA_BITS_7:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_DLS_MASK_7BITS );
            break;
        case HAL_LL_SAU_UART_DATA_BITS_8:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_DLS_MASK_8BITS );
            break;
        case HAL_LL_SAU_UART_DATA_BITS_9:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_DLS_MASK_9BITS );
            break;

        default:
            break;
    }
}

static void hal_ll_sau_uart_set_parity_bare_metal( hal_ll_sau_uart_hw_specifics_map_t *map ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    switch ( map->parity )
    {
        clear_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_PTC_MASK );
        case HAL_LL_SAU_UART_PARITY_NONE:
            clear_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_PTC_MASK );
            break;
        case HAL_LL_SAU_UART_PARITY_EVEN:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_PTC_MASK_EVEN );
            break;
        case HAL_LL_SAU_UART_PARITY_ODD:
            set_reg_bits( &hal_ll_hw_reg->scr[ map->sau_channel ], HAL_LL_SAU_SCR_PTC_MASK_ODD );
            break;

        default:
            break;
    }
}

static void hal_ll_sau_uart_set_module( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_state_t pin_state ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    switch ( pin_state )
    {
        case HAL_LL_SAU_DISABLE:
            set_reg_bit( &hal_ll_hw_reg->st, map->sau_channel );
            clear_reg_bit( &hal_ll_hw_reg->se, map->sau_channel );
            break;

        case HAL_LL_SAU_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->ss, map->sau_channel );
            set_reg_bit( &hal_ll_hw_reg->se, map->sau_channel );
            break;

        default:
            break;
    }
}

static void hal_ll_sau_uart_set_transmitter( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_state_t pin_state ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    switch ( pin_state )
    {
        case HAL_LL_SAU_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->soe, map->sau_channel );
            break;

        case HAL_LL_SAU_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->soe, map->sau_channel );
            break;

        default:
            break;
    }
}

static void hal_ll_sau_uart_set_receiver( hal_ll_sau_uart_hw_specifics_map_t *map, hal_ll_sau_state_t pin_state ) {
    hal_ll_sau_base_handle_t *hal_ll_hw_reg = hal_ll_sau_get_base_struct( map->base );

    switch ( pin_state )
    {
        case HAL_LL_SAU_DISABLE:
            clear_reg_bit( &hal_ll_hw_reg->soe, map->sau_channel );
            break;

        case HAL_LL_SAU_ENABLE:
            set_reg_bit( &hal_ll_hw_reg->soe, map->sau_channel );
            break;

        default:
            break;
    }
}

// ------------------------------------------------------------------------- END
