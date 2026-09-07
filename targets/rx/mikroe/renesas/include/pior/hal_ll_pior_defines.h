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

/*!< @brief PIOR register block base address (R01UH1082EJ0110, 4.3.10).
 * PIOR0..PIOR13 are byte-wide registers at consecutive offsets from this
 * base - hal_ll_pior_set_field() computes the exact register/bit/width
 * per entry in hal_ll_pior_connection_defs.h. */
#define HAL_LL_PIOR_BASE ( 0xF04E0UL )

/*!< @brief Writes a value into one field of a PIOR register. Moved here
 * from hal_ll_gpio_port.c - it's used exclusively by the PIOR module now
 * (GPIO no longer touches PIOR at all), and being static there made it
 * invisible to this file's translation unit. */
static inline void hal_ll_pior_set_field( uint8_t pior_index, uint8_t shift, uint8_t width, uint8_t value ) {
    uint32_t reg  = HAL_LL_PIOR_BASE + pior_index;
    uint8_t  mask = ( uint8_t ) ( ( ( 1U << width ) - 1U ) << shift );

    clear_reg_bits( ( uint8_t * ) reg, mask );
    set_reg_bits( ( uint8_t * ) reg, ( uint8_t ) ( ( value << shift ) & mask ) );
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
