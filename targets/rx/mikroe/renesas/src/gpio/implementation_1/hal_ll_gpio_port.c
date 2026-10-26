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
 * @brief GPIO HAL LOW LEVEL ported layer implementation — RX26T.
 */

#include "hal_ll_gpio_port.h"

#define hal_ll_gpio_port_get_pin_index(__index)  ( ( uint8_t )( __index ) & 0x07U )
#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index ) >> 3 )

#define GPIO_ALT_FUNC_MASK (0xFF00)

#define RX26T_PORT_BASE   ( 0x0008C000UL )

static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    #ifdef __PORT_0_CN
    GPIO_PORT0_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_1_CN
    GPIO_PORT1_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_2_CN
    GPIO_PORT2_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_3_CN
    GPIO_PORT3_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_4_CN
    GPIO_PORT4_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_5_CN
    GPIO_PORT5_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_6_CN
    GPIO_PORT6_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_7_CN
    GPIO_PORT7_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_8_CN
    GPIO_PORT8_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_9_CN
    GPIO_PORT9_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_A_CN
    GPIO_PORTA_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_B_CN
    GPIO_PORTB_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_D_CN
    GPIO_PORTD_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_E_CN
    GPIO_PORTE_BASE,
    #else
    0,
    #endif
    #ifdef __PORT_N_CN
    GPIO_PORTN_BASE,
    #else
    0,
    #endif
};

#define HAL_LL_GPIO_PDR_OFFSET   ( 0x00UL )
#define HAL_LL_GPIO_PODR_OFFSET  ( 0x20UL )
#define HAL_LL_GPIO_PIDR_OFFSET  ( 0x40UL )
#define HAL_LL_GPIO_PMR_OFFSET   ( 0x60UL )
#define HAL_LL_GPIO_ODR_OFFSET   ( 0x80UL )
#define HAL_LL_GPIO_PCR_OFFSET   ( 0xC0UL )
#define HAL_LL_GPIO_DSCR_OFFSET  ( 0xE0UL )

#define HAL_LL_MPC_PWPR_OFFSET       ( 0x11FUL )
#define HAL_LL_MPC_PFS_BASE_OFFSET   ( 0x140UL )
#define HAL_LL_MPC_PFS_PORT_STRIDE   ( 0x08UL )
#define HAL_LL_MPC_PWPR_PFSWE_BIT    ( 6U )
#define HAL_LL_MPC_PWPR_B0WI_BIT     ( 7U )
#define HAL_LL_MPC_PFS_ISEL_BIT      ( 6U )
#define HAL_LL_MPC_PFS_ASEL_BIT      ( 7U )
#define HAL_LL_MPC_PFS_PSEL_MASK     ( 0x3FU )

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
  * @brief  Configure alternate function for pin
  * @param  module_pin    - pin name with alternate function in the upper byte
  *         module_config - pin settings
  *         state         - true/false
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

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_port_index( ( uint8_t )( name & GPIO_PIN_NAME_MASK ) );
}

uint16_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name ) {
    return ( uint16_t )( 1UL << hal_ll_gpio_pin_index( name ) );
}

uint32_t hal_ll_gpio_port_base( hal_ll_port_name_t name ) {
    return hal_ll_gpio_get_base_addr( ( uint8_t )name );
}

void hal_ll_gpio_analog_input( uint32_t *port, uint16_t pin_mask ) {
    volatile uint8_t *pdr = ( volatile uint8_t * )( ( uint32_t )port + HAL_LL_GPIO_PDR_OFFSET );
    volatile uint8_t *pmr = ( volatile uint8_t * )( ( uint32_t )port + HAL_LL_GPIO_PMR_OFFSET );
    volatile uint8_t *pwpr = ( volatile uint8_t * )( RX26T_PORT_BASE + HAL_LL_MPC_PWPR_OFFSET );
    uint32_t real_id = ( uint32_t )port - RX26T_PORT_BASE;
    uint32_t pfs_base = RX26T_PORT_BASE + HAL_LL_MPC_PFS_BASE_OFFSET + ( real_id * HAL_LL_MPC_PFS_PORT_STRIDE );
    uint8_t pin;

    if ( 0 == ( uint32_t )port ) {
        return;
    }

    /* PMR/PDR both 0 before ASEL goes high (R01UH0979 21.3.3). */
    *pmr &= ( uint8_t )~pin_mask;
    *pdr &= ( uint8_t )~pin_mask;

    *pwpr &= ( uint8_t )~( 1U << HAL_LL_MPC_PWPR_B0WI_BIT );
    *pwpr |= ( uint8_t )( 1U << HAL_LL_MPC_PWPR_PFSWE_BIT );

    for ( pin = 0; pin < 8; pin++ ) {
        if ( 0 != ( pin_mask & ( 1U << pin ) ) ) {
            volatile uint8_t *pfs = ( volatile uint8_t * )( pfs_base + pin );
            *pfs |= ( uint8_t )( 1U << HAL_LL_MPC_PFS_ASEL_BIT );
        }
    }

    *pwpr &= ( uint8_t )~( 1U << HAL_LL_MPC_PWPR_PFSWE_BIT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_DIGITAL_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state ) {
    uint8_t index = 0;

    while ( GPIO_MODULE_STRUCT_END != ( int32_t )module->pins[ index ] ) {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );
        index++;
    }
}

// ------------------------------------------------ STATIC FUNCTION DEFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name ) {
    return hal_ll_gpio_port_get_pin_index( ( uint8_t )( name & GPIO_PIN_NAME_MASK ) );
}

static inline uint32_t hal_ll_gpio_get_base_addr( uint8_t port_index )
{
    if ( ( sizeof( hal_ll_gpio_port_base_arr ) / sizeof( hal_ll_gpio_port_base_arr[0] ) ) <= port_index ) {
        return 0;
    }

    return hal_ll_gpio_port_base_arr[ port_index ];
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    uint32_t real_id = ( uint32_t )port - RX26T_PORT_BASE;
    volatile uint8_t *pdr = ( volatile uint8_t * )( ( uint32_t )port + HAL_LL_GPIO_PDR_OFFSET );
    volatile uint8_t *pmr = ( volatile uint8_t * )( ( uint32_t )port + HAL_LL_GPIO_PMR_OFFSET );
    volatile uint8_t *pcr = ( volatile uint8_t * )( ( uint32_t )port + HAL_LL_GPIO_PCR_OFFSET );
    volatile uint8_t *dscr = ( volatile uint8_t * )( RX26T_PORT_BASE + HAL_LL_GPIO_DSCR_OFFSET + real_id );
    volatile uint8_t *odr = ( volatile uint8_t * )( RX26T_PORT_BASE + HAL_LL_GPIO_ODR_OFFSET + ( real_id * 2U ) );
    uint8_t pin;

    if ( 0 == ( uint32_t )port ) {
        return;
    }

    *pmr &= ( uint8_t )~pin_mask;

    if ( 0 != ( config & GPIO_CFG_DIGITAL_OUTPUT ) ) {
        *pdr |= ( uint8_t )pin_mask;
        *pcr &= ( uint8_t )~pin_mask;
    } else if ( 0 != ( config & GPIO_CFG_DIGITAL_INPUT ) ) {
        *pdr &= ( uint8_t )~pin_mask;
    }

    if ( 0 != ( config & GPIO_CFG_PORT_PULL_UP_ENABLE ) ) {
        *pcr |= ( uint8_t )pin_mask;
    }

    if ( ( 0 != ( config & GPIO_CFG_PORT_MIDDLE_DRIVE ) ) && ( ( real_id < 4U ) || ( real_id > 6U ) ) ) {
        *dscr |= ( uint8_t )pin_mask;
    }

    if ( 0 != ( config & GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE ) ) {
        for ( pin = 0; pin < 8; pin++ ) {
            if ( 0 != ( pin_mask & ( 1U << pin ) ) ) {
                *( odr + ( pin >> 2 ) ) |= ( uint8_t )( 1U << ( ( pin & 0x03U ) * 2U ) );
            }
        }
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    hal_ll_pin_name_t pin_name = ( hal_ll_pin_name_t )( module_pin & GPIO_PIN_NAME_MASK );
    uint8_t port_index = hal_ll_gpio_port_get_port_index( ( uint8_t )pin_name );
    uint32_t port_base = hal_ll_gpio_get_base_addr( port_index );
    uint8_t pin = hal_ll_gpio_pin_index( pin_name );
    uint8_t psel = ( uint8_t )( ( module_pin & GPIO_ALT_FUNC_MASK ) >> GPIO_AF_OFFSET );
    uint8_t pfs_value = 0x00U;
    uint32_t real_id;
    volatile uint8_t *pmr;
    volatile uint8_t *pwpr;
    volatile uint8_t *pfs;

    if ( 0 == port_base ) {
        return;
    }

    real_id = port_base - RX26T_PORT_BASE;
    pmr = ( volatile uint8_t * )( port_base + HAL_LL_GPIO_PMR_OFFSET );
    pwpr = ( volatile uint8_t * )( RX26T_PORT_BASE + HAL_LL_MPC_PWPR_OFFSET );
    pfs = ( volatile uint8_t * )( RX26T_PORT_BASE + HAL_LL_MPC_PFS_BASE_OFFSET +
                                  real_id * HAL_LL_MPC_PFS_PORT_STRIDE +
                                  pin );

    if ( true == state ) {
        pfs_value = ( uint8_t )( psel & HAL_LL_MPC_PFS_PSEL_MASK );

        if ( 0 != ( module_config & GPIO_CFG_IRQ_ENABLE ) ) {
            pfs_value |= ( uint8_t )( 1U << HAL_LL_MPC_PFS_ISEL_BIT );
        }
    }

    /* PMR must be 0 while PSEL is changed (R01UH0979 21.3.2 note 1). */
    *pmr &= ( uint8_t )~( 1U << pin );

    if ( true == state ) {
        hal_ll_gpio_config( ( uint32_t * )port_base, ( uint16_t )( 1U << pin ), module_config );
    }

    *pwpr &= ( uint8_t )~( 1U << HAL_LL_MPC_PWPR_B0WI_BIT );
    *pwpr |= ( uint8_t )( 1U << HAL_LL_MPC_PWPR_PFSWE_BIT );

    *pfs = pfs_value;

    *pwpr &= ( uint8_t )~( 1U << HAL_LL_MPC_PWPR_PFSWE_BIT );

    if ( true == state ) {
        *pmr |= ( uint8_t )( 1U << pin );
    }
}

// ------------------------------------------------------------------------- END
