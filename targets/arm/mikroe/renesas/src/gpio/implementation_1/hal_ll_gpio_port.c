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

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index&0xF )//% PORT_SIZE )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )(__index&0xF0) >> 4 )

#define GPIO_PORT0_BASE  (0x40040000UL)
#define GPIO_PORT1_BASE  (0x40040020UL)
#define GPIO_PORT2_BASE  (0x40040040UL)
#define GPIO_PORT3_BASE  (0x40040060UL)
#define GPIO_PORT4_BASE  (0x40040080UL)
#define GPIO_PORT5_BASE  (0x400400A0UL)
#define GPIO_PORT6_BASE  (0x400400C0UL)
#define GPIO_PORT7_BASE  (0x400400E0UL)
#define GPIO_PORT8_BASE  (0x40040100UL)
#define GPIO_PORT9_BASE  (0x40040120UL)
// According to the documentation, this MCU has 10 ports,
// but in mcu.h there are 15 port addresses
// #define GPIO_PORT10_BASE (0x40040140UL)
// #define GPIO_PORT11_BASE (0x40040160UL)
// #define GPIO_PORT12_BASE (0x40040180UL)
// #define GPIO_PORT13_BASE (0x400401A0UL)
// #define GPIO_PORT14_BASE (0x400401C0UL)

#define PWPR_REGISTER_BASE (( volatile uint8_t * )0x40040D03UL)

/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    GPIO_PORT0_BASE,
    GPIO_PORT1_BASE,
    GPIO_PORT2_BASE,
    GPIO_PORT3_BASE,
    GPIO_PORT4_BASE,
    GPIO_PORT5_BASE,
    GPIO_PORT6_BASE,
    GPIO_PORT7_BASE,
    GPIO_PORT8_BASE,
    GPIO_PORT9_BASE//,
    // GPIO_PORT10_BASE,
    // GPIO_PORT11_BASE,
    // GPIO_PORT12_BASE,
    // GPIO_PORT13_BASE,
    // GPIO_PORT14_BASE
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

// /**
//   * @brief  Enable gpio port clock
//   * @param  port - port base address
//   * @return none
//   */
// static void _hal_ll_gpio_clock_enable( uint32_t *port ); // TODO Esma

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

// TODO Esma
static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name );

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

static void hal_ll_gpio_clock_enable( uint32_t port ) {
    // TODO Esma - PORTs don't have clock enabling feature.
}

uint32_t get_port_number(uint32_t base_addr)
{
    for (int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++) {
        if (hal_ll_gpio_port_base_arr[i] == base_addr) {
            return i; // port number
        }
    }
    return -1; // not found
}

#include "mcu.h"

#define PmnPFS ((hal_ll_gpio_pfs_t *)0x40040800UL) // Base address of PFS

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    uint32_t pin_index = ( pin_mask == 0xFFFF ) ? 0xFFFF : __builtin_ctz(pin_mask); // TODO Esma
    hal_ll_port_name_t port_index;
    port_index = get_port_number( *port );
    hal_ll_gpio_pfs_t *port_pfs_ptr = &PmnPFS->port[0].pin[0];
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *) *port;

    // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    // *PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    // *PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit
    R_PMISC->PWPR_b.B0WI = 0;
    R_PMISC->PWPR_b.PFSWE = 1;

    if ( pin_mask == 0xFFFF ) {
        if ( GPIO_CFG_DIGITAL_OUTPUT == config )
            port_ptr->pdr = pin_mask;
        else if ( GPIO_CFG_DIGITAL_INPUT == config )
            port_ptr->pdr = 0;
    } else {
        // Clear the Port Mode Control bit in the PMR for the target pin to select the general I/O port.
        port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pmr = 0;
        // Specify the input/output function for the pin through the PSEL[4:0] bit settings in the PmnPFS register.
        port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.psel = 0;
        // Set the PMR to 1 as required to switch to the selected input/output function for the pin.
        // TODO Esma zasto odmah stavljamo da nije GPIO nego peripheral?
        // port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pmr = 1;

        if( GPIO_CFG_ANALOG_INPUT == config ) {
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pmr = 0;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pdr = 0;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.asel = 1;
        } else if ( GPIO_CFG_DIGITAL_OUTPUT == config ) {
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pdr = 1;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.asel = 0;
        } else if ( GPIO_CFG_DIGITAL_INPUT == config ) {
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.pdr = 0;
            port_pfs_ptr->port[port_index].pin[pin_index].pmnpfs_b.asel = 0;
        }

        // // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
        // *PWPR_REGISTER_BASE &= ~0x40; // Set PFSWE bit
        // // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
        // *PWPR_REGISTER_BASE |= 0x80; // Set B0WI bit
        R_PMISC->PWPR_b.PFSWE = 0;
        R_PMISC->PWPR_b.B0WI = 1;
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    // hal_ll_gpio_base_handle_t *port_ptr;
    hal_ll_gpio_pfs_t *port_ptr;

    pin_name = module_pin & GPIO_PIN_NAME_MASK;

    pin_index = hal_ll_gpio_pin_index( pin_name );

    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );

    port_ptr = ( hal_ll_gpio_base_handle_t* )hal_ll_gpio_port_base( port_name );

    // port_pcr_array = ( hal_ll_gpio_pcr_base_handle_t* )( GPIO_PCR_BASE_VALUE + port_name * GPIO_PCR_OFFSET_VALUE );

    hal_ll_gpio_config( (uint32_t *)&port_ptr, hal_ll_gpio_pin_mask( pin_index ), module_config );

    if ( true == state ) {
        port_ptr->port[port_name].pin[pin_index].pmnpfs_b.psel |= module_pin & 0x1F000000;
    } else {
        port_ptr->port[port_name].pin[pin_index].pmnpfs_b.psel &= ~( module_pin & 0x1F000000 );
    }
}

// ------------------------------------------------------------------------- END
