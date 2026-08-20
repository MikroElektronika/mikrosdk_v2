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
 * @file  hal_ll_gpio_port.c
 * @brief GPIO HAL LOW LEVEL ported layer implementation.
 */

#include "hal_ll_gpio_port.h"

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index & 0xF )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index & 0xF0 ) >> 4 )

#define GPIO_ALT_FUNC_MASK (0xFF00)

/* -------------------------------------------------------------------- */
/* RL78/L23 register layout                                              */
/*                                                                        */
/* P and PM sit exactly 0x20 apart for every port that has both, and      */
/* PU/PIM/POM/PDIDIS sit at fixed 0x10/0x20/0x280 offsets from PU for      */
/* every port that has them -- but the two groups live in different SFR   */
/* banks (P/PM near 0xFFF00, PU/PIM/POM/PDIDIS near 0xF0000), so they're   */
/* two separate offset-anchored handles, not one:                         */
/*                                                                        */
/*   hal_ll_gpio_base_handle_t : P (0x00) .. PM (0x20)                    */
/*   hal_ll_gpio_cfg_handle_t  : PU (0x00), PIM (0x10), POM (0x20),        */
/*                               PDIDIS (0x280)                           */
/*                                                                        */
/* GPIO_PORTx_BASE must resolve to that port's P register address, and    */
/* GPIO_PORTx_CFG_BASE to that port's PU register address (R01UH1082      */
/* Table 4-2). Port 13 has neither PM nor PU/PIM (only P130/POM13/         */
/* PDIDIS13), so it isn't modelled through these structs at all.          */
/*                                                                        */
/* PMCAxx/PMCTxx/PMCExx (analog / capacitance / ELCL function-class       */
/* registers) aren't at a fixed offset from anything -- they exist for    */
/* a handful of ports each, at addresses with no arithmetic relation to   */
/* P/PM/PU -- so they stay as individually looked-up registers below.     */
/* -------------------------------------------------------------------- */

// typedef struct {
//     volatile uint8_t p;                  /* 0x00: output latch / pin read */
//     uint8_t           reserved0[ 0x1F ];
//     volatile uint8_t pm;                 /* 0x20: direction, 0 = out, 1 = in */
// } hal_ll_gpio_base_handle_t;

typedef struct {
    volatile uint8_t pu;                 /* 0x000: pull-up enable */
    uint8_t           reserved0[ 0x0F ];
    volatile uint8_t pim;                /* 0x010: input buffer, 0 = CMOS, 1 = TTL */
    uint8_t           reserved1[ 0x0F ];
    volatile uint8_t pom;                /* 0x020: output mode, 0 = push-pull, 1 = open-drain */
    uint8_t           reserved2[ 0x25F ];
    volatile uint8_t pdidis;             /* 0x280: 1 = input buffer disabled */
} hal_ll_gpio_cfg_handle_t;

/* PMCAxx only exists for ports 1, 2 and 4 (R01UH1082 4.3.7); every other
 * port has no analog/digital mux, so GPIO_CFG_ANALOG_INPUT is simply not
 * valid there and this reads back 0. Indexed identically to
 * hal_ll_gpio_port_base_arr / hal_ll_gpio_cfg_base_arr below. */
static const hal_ll_base_addr_t hal_ll_gpio_analog_ctrl_arr[] = {
    0,          /* port 0  */
    0xF0061UL,  /* port 1  -> PMCA1 */
    0xF0062UL,  /* port 2  -> PMCA2 */
    0,          /* port 3  */
    0xF0064UL,  /* port 4  -> PMCA4 */
    0,          /* port 5  */
    0,          /* port 6  */
    0,          /* port 7  */
    0,          /* port 8  */
    0,          /* port 9  */
    0,          /* port 10 (not present on this device) */
    0,          /* port 11 (not present on this device) */
    0,          /* port 12 */
    0,          /* port 13 */
    0,          /* port 14 */
};

/* -------------------------------------------------------------------- */
/* Raw-address register helpers -- for PMCAxx/PIORx/etc, which are not   */
/* reachable through either offset-anchored struct above.                */
/* -------------------------------------------------------------------- */

// #define hal_ll_reg8( addr ) ( *( volatile uint8_t * )( addr ) )

// static inline void hal_ll_set_reg_bits( hal_ll_base_addr_t addr, uint8_t mask ) {
//     if ( 0 != addr ) {
//         hal_ll_reg8( addr ) |= mask;
//     }
// }

// static inline void hal_ll_clear_reg_bits( hal_ll_base_addr_t addr, uint8_t mask ) {
//     if ( 0 != addr ) {
//         hal_ll_reg8( addr ) &= ( uint8_t ) ( ~mask );
//     }
// }

/* Peripheral I/O redirection registers (PIOR0..PIOR13), R01UH1082 4.3.10. */
#define HAL_LL_PIOR_BASE ( 0xF04E0UL )

static inline void hal_ll_pior_set_field( uint8_t pior_index, uint8_t shift, uint8_t width, uint8_t value ) {
    hal_ll_base_addr_t reg  = HAL_LL_PIOR_BASE + pior_index;
    uint8_t            mask = ( uint8_t ) ( ( ( 1U << width ) - 1U ) << shift );

    clear_reg_bits( &reg, mask );
    set_reg_bits( &reg, ( uint8_t ) ( ( value << shift ) & mask )); // TODO double check
}

/* One row per alternate-function selector value carried in a
 * module_struct pin entry's upper byte (GPIO_ALT_FUNC_MASK).
 *
 * pior_width == 0      -> this function is not redirectable, skip the
 *                          PIOR write entirely.
 * func_class_reg == 0   -> this pin has no PMCAxx/PMCTxx/PMCExx
 *                          function-class register, skip it.
 *
 * This table is necessarily per-pin (Table 4-6 of R01UH1082), so it
 * belongs in the MCU-specific pin map, not this generic port layer --
 * left as an extern here until it's populated there.
 */
typedef struct {
    uint8_t             pior_index;
    uint8_t             pior_shift;
    uint8_t             pior_width;
    uint8_t             pior_value;
    hal_ll_base_addr_t  func_class_reg;   /* PMCAxx / PMCTxx / PMCExx address, or 0 */
    uint8_t             func_class_bit;
    bool                open_drain;       /* true -> POMmn must be set for this function */
} hal_ll_gpio_af_t;

extern const hal_ll_gpio_af_t hal_ll_gpio_af_table[];

/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    #ifdef GPIO_PORT_0
    GPIO_PORT0_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_1
    GPIO_PORT1_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_2
    GPIO_PORT2_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_3
    GPIO_PORT3_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_4
    GPIO_PORT4_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_5
    GPIO_PORT5_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_6
    GPIO_PORT6_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_7
    GPIO_PORT7_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_8
    GPIO_PORT8_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_9
    GPIO_PORT9_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_10
    GPIO_PORT10_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_11
    GPIO_PORT11_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_12
    GPIO_PORT12_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_13
    GPIO_PORT13_BASE,
    #else
    0,
    #endif
    #ifdef GPIO_PORT_14
    GPIO_PORT14_BASE,
    #else
    0,
    #endif
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Configure port pins
  * @param  port     - port base address
  *         pin_mask - desired pin
  *         config   - pin settings
  * @return none
  */
static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state );

/**
  * @brief  Retrieve the index of the
  *         provided pin
  * @param  hal_ll_pin_name_t - pin
  * @return uint8_t - the index of the pin
  */
static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name );

/**
  * @brief  Fetch the port address based on the provided port index.
  * @param  uint8_t - the index of the port
  * @return uint32_t - base address of the port
  */
static uint32_t hal_ll_gpio_get_base_addr( uint8_t port_index );

/**
  * @brief  Fetch this port's config-bank base address
  *         (anchors PU/PIM/POM/PDIDIS, see hal_ll_gpio_cfg_handle_t).
  * @param  hal_ll_port_name_t - port
  * @return uint32_t - config-bank base address of the port
  */
static uint32_t hal_ll_gpio_port_cfg_base( hal_ll_port_name_t name );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    uint16_t ret;
    ret = hal_ll_gpio_port_get_port_index( name );
    return ret;
}

uint16_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name ) {
    uint16_t ret;
    ret = ( 1UL << hal_ll_gpio_pin_index( name ) );
    return ret;
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name ) {
    return hal_ll_gpio_port_base_arr[ name ];
}

void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_ANALOG_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
    int32_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END )
    {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( name );
}

static uint8_t hal_ll_gpio_get_port_number(uint32_t base_addr)
{
    for (int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++) {
        if (hal_ll_gpio_port_base_arr[i] == base_addr) {
            return i; // Port number.
        }
    }
    return 0xFF; // Not found.
}

static inline uint32_t hal_ll_gpio_get_base_addr( uint8_t port_index )
{
    if ( PORT_COUNT > port_index ) {
        return hal_ll_gpio_port_base_arr[port_index];
    }
    return 0;
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    hal_ll_gpio_base_handle_t *port_ptr = ( hal_ll_gpio_base_handle_t * ) port;
    uint8_t mask = ( uint8_t ) pin_mask;
    uint8_t port_index;
    hal_ll_base_addr_t analog_reg;

    if ( NULL == port_ptr ) {
        return;
    }

    port_index = hal_ll_gpio_get_port_number( ( uint32_t ) port_ptr );
    analog_reg = ( PORT_COUNT > port_index ) ? hal_ll_gpio_analog_ctrl_arr[ port_index ] : 0;

    switch ( config ) {
        case GPIO_CFG_DIGITAL_INPUT:
            clear_reg_bits( &analog_reg, mask );
            port_ptr->pm |= mask;
            break;

        case GPIO_CFG_DIGITAL_OUTPUT:
            clear_reg_bits( &analog_reg, mask );
            port_ptr->pm &= ( uint8_t ) ( ~mask );
            break;

        case GPIO_CFG_ANALOG_INPUT:
            set_reg_bits( &analog_reg, mask );
            port_ptr->pm |= mask;
            break;

        default:
            break;
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_gpio_base_handle_t *port_ptr;
    hal_ll_gpio_cfg_handle_t *cfg_ptr;
    uint32_t port_addr;
    uint32_t cfg_addr;
    uint8_t alternate_function;

    pin_name = ( hal_ll_pin_name_t ) module_pin;
    pin_index = hal_ll_gpio_pin_index( pin_name );
    port_name = hal_ll_gpio_port_index( pin_name );
    uint32_t mask = ( uint32_t ) ( 1 << pin_index );

    port_addr = hal_ll_gpio_port_base( port_name );
    port_ptr = ( hal_ll_gpio_base_handle_t * ) port_addr;

    cfg_addr = hal_ll_gpio_port_cfg_base( port_name );
    cfg_ptr = ( hal_ll_gpio_cfg_handle_t * ) cfg_addr;

    alternate_function = ( ( module_pin & GPIO_ALT_FUNC_MASK ) >> GPIO_AF_OFFSET );

    const hal_ll_gpio_af_t *af = &hal_ll_gpio_af_table[ alternate_function ];

    if ( false == state ) {
        /* Hand the pin back to plain digital I/O. Direction/pull-up
         * are the caller's responsibility via hal_ll_gpio_digital_*;
         * this only undoes what enabling the alternate function did
         * that a plain GPIO_CFG_* call wouldn't touch. */
        clear_reg_bits( &af->func_class_reg, ( uint8_t ) ( 1U << af->func_class_bit ) );
        cfg_ptr->pom &= ( uint8_t ) ( ~mask );
        return;
    }

    /* 1. Route the peripheral signal to this physical pin -- only
     *    applies to functions RL78 actually lets you redirect. */
    if ( 0 != af->pior_width ) {
        hal_ll_pior_set_field( af->pior_index, af->pior_shift, af->pior_width, af->pior_value );
    }

    /* 2. Take the pin out of analog / capacitance-measurement / ELCL
     *    mode and into digital I/O, if it has such a register. */
    clear_reg_bits( &af->func_class_reg, ( uint8_t ) ( 1U << af->func_class_bit ) );

    /* 3. Electrical mode: N-ch open-drain (withstand VDD) for
     *    cross-voltage or shared-bus links, push-pull otherwise. */
    if ( true == af->open_drain ) {
        cfg_ptr->pom |= ( uint8_t ) mask;
    } else {
        cfg_ptr->pom &= ( uint8_t ) ( ~mask );
    }

    /* 4. Base electrical setup (direction / analog-out-of-the-way) is
     *    whatever this pin's module_struct configs[] entry says --
     *    same GPIO_CFG_* encoding hal_ll_gpio_config() consumes. */
    hal_ll_gpio_config( ( uint32_t * ) port_ptr, ( uint16_t ) mask, module_config );

    /* NOTE: per R01UH1082 Table 4-4/4-6, every *other* function
     * multiplexed on this pin must be forced to its documented idle
     * level (SAU/UARTA outputs -> 1, everything else -> 0) before the
     * peripheral is enabled, or the two outputs will contend on the
     * pad. That set of writes is peripheral-specific and belongs in
     * the calling module driver (UART/SPI/I2C/etc.), not here --
     * hal_ll_gpio_af_table only describes routing for the function
     * currently being enabled, not what its neighbors must idle at.
     */
}

// ------------------------------------------------------------------------- END
