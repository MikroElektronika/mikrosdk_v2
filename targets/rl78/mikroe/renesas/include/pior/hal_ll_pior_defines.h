/*!
 * @file  hal_ll_pior_defines.h
 * @brief Supporting macros and enums for HAL LOW LEVEL PIOR (peripheral I/O
 *        redirection) implementation. Shared across all RL78 parts - the
 *        actual per-pin routing table lives in hal_ll_pior_connection_defs.h,
 *        one file per chip, same split as the PIC32 PPS files.
 */

#ifndef _HAL_LL_PIOR_DEFINES_H_
#define _HAL_LL_PIOR_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "mcu_definitions.h"

/*!< @brief Enum defining PIOR module (channel) index.
 * Meaning depends on hal_ll_pior_functionality_t: e.g. for
 * HAL_LL_PIOR_FUNCTIONALITY_SPI_SCK, index 5 means SAU channel "21"
 * (unit 2, sub-channel 1) - see hal_ll_pior_connection_defs.h per pin. */
typedef enum
{
    HAL_LL_PIOR_MODULE_INDEX_0 = 0,
    HAL_LL_PIOR_MODULE_INDEX_1,
    HAL_LL_PIOR_MODULE_INDEX_2,
    HAL_LL_PIOR_MODULE_INDEX_3,
    HAL_LL_PIOR_MODULE_INDEX_4,
    HAL_LL_PIOR_MODULE_INDEX_5,
    HAL_LL_PIOR_MODULE_INDEX_6,
    HAL_LL_PIOR_MODULE_INDEX_7
} hal_ll_pior_module_index_t;

/*!< @brief Enum defining PIOR functionalities.
 * Unlike PIC32 (separate SPI_MISO/SPI_MOSI functionalities because input
 * and output go through entirely different register sets), RL78 routes
 * both directions of a channel through the same PIOR field - the split
 * here follows the manual's own signal names (SCK/SI/SO, TxD/RxD, SCL/SDA,
 * TI/TO) rather than an input-vs-output register distinction. */
typedef enum
{
    HAL_LL_PIOR_FUNCTIONALITY_UART_TX = 0,
    HAL_LL_PIOR_FUNCTIONALITY_UART_RX,
    HAL_LL_PIOR_FUNCTIONALITY_SPI_SCK,
    HAL_LL_PIOR_FUNCTIONALITY_SPI_MISO,
    HAL_LL_PIOR_FUNCTIONALITY_SPI_MOSI,
    HAL_LL_PIOR_FUNCTIONALITY_I2C_SCL,
    HAL_LL_PIOR_FUNCTIONALITY_I2C_SDA,
    HAL_LL_PIOR_FUNCTIONALITY_TIMER_IC,   // TIn - input capture
    HAL_LL_PIOR_FUNCTIONALITY_TIMER_OC,   // TOn - output compare

    HAL_LL_PIOR_FUNCTIONALITY_NONE = 0xFF
} hal_ll_pior_functionality_t;

/*!< @brief Enum defining PIOR return values */
typedef enum
{
    HAL_LL_PIOR_SUCCESS = 0,
    HAL_LL_PIOR_DIRECTION_ERROR,
    HAL_LL_PIOR_PIN_ERROR,
    HAL_LL_PIOR_MODULE_ERROR
} hal_ll_pior_err_t;

/*!< @brief PIORn register address.
 * Where the PIOR registers sit differs between RL78 groups, every chip
 * provides hal_ll_pior_reg_addr() in its mcu_reg_addresses.h. */
#ifndef hal_ll_pior_reg_addr
#error "hal_ll_pior_reg_addr() is not defined for this MCU."
#endif

/*!< @brief Writes the bits selected by mask in PIORn.
 * @param pior_index PIOR register number (n in PIORn).
 * @param mask       Bits that route the peripheral.
 * @param value      Register value for those bits, already in position.
 */
static inline void hal_ll_pior_write( uint8_t pior_index, uint8_t mask, uint8_t value ) {
    volatile uint8_t *reg = ( volatile uint8_t * ) hal_ll_pior_reg_addr( pior_index );

    if ( !mask ) {
        return;
    }

    // PIORx only supports 8-bit access, a single write also avoids
    // briefly routing the function to the value 0 pin.
    *reg = ( uint8_t ) ( ( *reg & ( uint8_t ) ~mask ) | ( value & mask ) );
}

/*!< @brief Spreads a pin map AF value over the routing bits of a module.
 * Bit i of af goes to the i-th lowest set bit of mask. For a contiguous
 * mask this is af shifted to the mask position. Some modules are routed
 * by bits that are not next to each other, e.g. one UART on RL78/G24 uses
 * PIOR0 bits 1 and 6, so AF 1 sets bit 1 and AF 2 sets bit 6.
 * @param mask Bits that route the module.
 * @param af   Pin map AF value.
 * @return Register value for the mask bits.
 */
static inline uint8_t hal_ll_pior_af_to_value( uint8_t mask, uint8_t af ) {
    uint8_t value = 0;
    uint8_t bit;

    for ( bit = 0; bit < 8; bit++ ) {
        if ( mask & ( 1U << bit ) ) {
            if ( af & 1U ) {
                value |= ( uint8_t ) ( 1U << bit );
            }
            af >>= 1;
        }
    }

    return value;
}

/*!< @brief Routes a module to the pins selected by a pin map AF value. */
static inline void hal_ll_pior_route( uint8_t pior_index, uint8_t mask, uint8_t af ) {
    hal_ll_pior_write( pior_index, mask, hal_ll_pior_af_to_value( mask, af ) );
}

/*!< @brief Used in low level source, same shape as the PIC32 pps_defines
 * helpers so callers reading both feel the same. */
#define reg_addr_ptr( reg_addr )        *( uint8_t * )reg_addr
#define write_reg_ptr( reg_addr,val )   reg_addr_ptr( reg_addr ) = val
#define clear_reg_ptr( reg_addr,mask )  reg_addr_ptr( reg_addr ) &= ~mask
#define set_reg_ptr( reg_addr,mask )    reg_addr_ptr( reg_addr ) |= mask

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIOR_DEFINES_H_
