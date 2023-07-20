/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2023 MikroElektronika d.o.o.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for SAML Touch Click driver.
 *
 * \addtogroup samltouch SAML Touch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SAMLTOUCH_H
#define SAMLTOUCH_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */
#define SAMLTOUCH_START_FRAME  0x55
#define SAMLTOUCH_END_FRAME  0xAA
/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define SAMLTOUCH_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SAMLTOUCH_RETVAL  uint8_t

#define SAMLTOUCH_OK           0x00
#define SAMLTOUCH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 1000
#define DRV_TX_BUFFER_SIZE 80
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint8_t button1;
    uint8_t button2;
    uint8_t sw_state;
    uint8_t sw_pos;

} samltouch_state_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} samltouch_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;
    pin_name_t tx_pin;

    // static variable

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.
    uart_stop_bits_t  stop_bit;      // Stop bits.

} samltouch_cfg_t;

/**
 * @brief Error type
 */
typedef uint8_t samltouch_error_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void samltouch_cfg_setup ( samltouch_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param samltouch Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SAMLTOUCH_RETVAL samltouch_init ( samltouch_t *ctx, samltouch_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void samltouch_generic_write ( samltouch_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 *
 * @return Number of reads data.
 */
int32_t samltouch_generic_read ( samltouch_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 *
 * @param data_in      pointer to response buffer
 * @param state    pointer to the structure.
 *
 * @description The function parses the response it receives -
 * restores the state of the button 1, button 2, the slider status and the slider position.
 */
void samltouch_parser ( char *data_in, samltouch_state_t *state );

#ifdef __cplusplus
}
#endif
#endif  // _SAMLTOUCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------- END
