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
#include "hal_ll_cg.h"

#define hal_ll_gpio_port_get_pin_index(__index) ( ( uint8_t )__index & 0xF )

#define hal_ll_gpio_port_get_port_index(__index) ( ( uint8_t )( __index & 0xF0 ) >> 4 )

#ifdef GPIO_PORT_A
#define GPIO_PORT0_BASE  (0x400E0000UL)
#endif
#ifdef GPIO_PORT_B
#define GPIO_PORT1_BASE  (0x400E0100UL)
#endif
#ifdef GPIO_PORT_C
#define GPIO_PORT2_BASE  (0x400E0200UL)
#endif
#ifdef GPIO_PORT_D
#define GPIO_PORT3_BASE  (0x400E0300UL)
#endif
#ifdef GPIO_PORT_E
#define GPIO_PORT4_BASE  (0x400E0400UL)
#endif
#ifdef GPIO_PORT_F
#define GPIO_PORT5_BASE  (0x400E0500UL)
#endif
#ifdef GPIO_PORT_G
#define GPIO_PORT6_BASE  (0x400E0600UL)
#endif
#ifdef GPIO_PORT_H
#define GPIO_PORT7_BASE  (0x400E0700UL)
#endif
#ifdef GPIO_PORT_J
#define GPIO_PORT8_BASE  (0x400E0800UL)
#endif
#ifdef GPIO_PORT_K
#define GPIO_PORT9_BASE  (0x400E0900UL)
#endif
#ifdef GPIO_PORT_L
#define GPIO_PORT10_BASE (0x400E0A00UL)
#endif
#ifdef GPIO_PORT_M
#define GPIO_PORT11_BASE (0x400E0B00UL)
#endif
#ifdef GPIO_PORT_N
#define GPIO_PORT12_BASE (0x400E0C00UL)
#endif
#ifdef GPIO_PORT_U
#define GPIO_PORT13_BASE (0x400E1000UL)
#endif
#ifdef GPIO_PORT_V
#define GPIO_PORT14_BASE (0x400E1100UL)
#endif

#define PWPR_REGISTER_BASE (* ( volatile uint8_t * )0x40040D03UL)
#define PFS_REGISTER_ADDR (0x40040800UL)
#define PFS_PSEL_MASK (0x1F000000UL)

/*!< @brief GPIO PORT array */
static const uint32_t hal_ll_gpio_port_base_arr[] =
{
    #ifdef GPIO_PORT0_BASE
    GPIO_PORT0_BASE,
    #endif
    #ifdef GPIO_PORT1_BASE
    GPIO_PORT1_BASE,
    #endif
    #ifdef GPIO_PORT2_BASE
    GPIO_PORT2_BASE,
    #endif
    #ifdef GPIO_PORT3_BASE
    GPIO_PORT3_BASE,
    #endif
    #ifdef GPIO_PORT4_BASE
    GPIO_PORT4_BASE,
    #endif
    #ifdef GPIO_PORT5_BASE
    GPIO_PORT5_BASE,
    #endif
    #ifdef GPIO_PORT6_BASE
    GPIO_PORT6_BASE,
    #endif
    #ifdef GPIO_PORT7_BASE
    GPIO_PORT7_BASE,
    #endif
    #ifdef GPIO_PORT8_BASE
    GPIO_PORT8_BASE,
    #endif
    #ifdef GPIO_PORT9_BASE
    GPIO_PORT9_BASE,
    #endif
    #ifdef GPIO_PORT10_BASE
    GPIO_PORT10_BASE,
    #endif
    #ifdef GPIO_PORT11_BASE
    GPIO_PORT11_BASE,
    #endif
    #ifdef GPIO_PORT12_BASE
    GPIO_PORT12_BASE,
    #endif
    #ifdef GPIO_PORT13_BASE
    GPIO_PORT13_BASE,
    #endif
    #ifdef GPIO_PORT14_BASE
    GPIO_PORT14_BASE
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
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( uint32_t port, uint32_t* port_pcr_base_addr );

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
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_INPUT );
}

void hal_ll_gpio_digital_input( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_INPUT );
}

void hal_ll_gpio_digital_output( uint32_t *port, uint16_t pin_mask ) {
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_OUTPUT_PP );
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

static uint32_t hal_ll_gpio_get_port_number(uint32_t base_addr)
{
    for (int i = 0; i < sizeof(hal_ll_gpio_port_base_arr) / sizeof(hal_ll_gpio_port_base_arr[0]); i++) {
        if (hal_ll_gpio_port_base_arr[i] == base_addr) {
            return i; // Port number.
        }
    }
    return -1; // Not found.
}

static void hal_ll_gpio_config( uint32_t *port, uint16_t pin_mask, uint32_t config ) {
    uint8_t  pin_num     = 0;
    uint16_t pin_pos     = 0;
    uint16_t current_pin = 0;
    uint32_t port_base   = 0;

    hal_ll_gpio_base_handle_t *gpio_ptr = (hal_ll_gpio_base_handle_t*) *port;

    hal_ll_gpio_clock_enable( *port, &port_base );

    for ( pin_num = 0; pin_num < 16; pin_num++ ) {
        pin_pos = 1U << pin_num;
        current_pin = pin_mask & pin_pos;

        if ( current_pin == pin_pos ) {
            if ( config & GPIO_CFG_PORT_DIRECTION_OUTPUT ) {
                // Configure as output
                gpio_ptr->CR |= current_pin;   // Enable Output
                gpio_ptr->IE &= ~current_pin;  // Disable Input 
                
                // Configure output type
                if ( config & (GPIO_CFG_OTYPE_OD << GPIO_CFG_OTYPE_POS) ) {
                    gpio_ptr->OD |= current_pin;  // Enable open drain
                } else {
                    gpio_ptr->OD &= ~current_pin; // Disable open drain
                }
                
                gpio_ptr->PUP &= ~current_pin;
                gpio_ptr->PDN &= ~current_pin;
                
            } else {
                // Configure as input
                gpio_ptr->CR &= ~current_pin;  // Disable Output
                gpio_ptr->IE |= current_pin;   // Enable Input
                gpio_ptr->OD &= ~current_pin;  // Disable open drain
                
                // Configure pull-up/down
                if ( config & (GPIO_CFG_PULL_UP << GPIO_CFG_PULL_UP_POS) ) {
                    gpio_ptr->PUP |= current_pin;  // Enable pull-up
                    gpio_ptr->PDN &= ~current_pin; // Disable pull-down
                } else if ( config & (GPIO_CFG_PULL_DOWN << GPIO_CFG_PULL_DOWN_POS) ) {
                    gpio_ptr->PUP &= ~current_pin; // Disable pull-up
                    gpio_ptr->PDN |= current_pin;  // Enable pull-down
                } else {
                    gpio_ptr->PUP &= ~current_pin; // Disable pull-up
                    gpio_ptr->PDN &= ~current_pin; // Disable pull-down
                }
            }
        }
    }
}

static void hal_ll_gpio_config_pin_alternate_enable( uint32_t module_pin, uint32_t module_config, bool state ) {
    uint8_t pin_index;
    hal_ll_pin_name_t pin_name;
    hal_ll_port_name_t port_name;
    hal_ll_gpio_base_handle_t *port_ptr;
    uint32_t *pfs_register;
    uint32_t pfs_offset;

    pin_name = module_pin & GPIO_PIN_NAME_MASK;
    pin_index = hal_ll_gpio_pin_index( pin_name );
    port_name = hal_ll_gpio_port_index( module_pin & 0xFF );
    port_ptr = ( hal_ll_gpio_base_handle_t* )hal_ll_gpio_port_base( port_name );

    hal_ll_gpio_config( (uint32_t *)&port_ptr, hal_ll_gpio_pin_mask( pin_name ), module_config );

    pfs_offset = (port_name * 16 + pin_index) * 4;
    pfs_register = (uint32_t *)(PFS_REGISTER_ADDR + pfs_offset);

    PWPR_REGISTER_BASE = 0x00;
    PWPR_REGISTER_BASE = 0x80;

    if ( true == state ) {
        uint32_t psel_value = (module_pin >> 24) & 0x1F;
        
        *pfs_register &= ~PFS_PSEL_MASK;
        *pfs_register |= (psel_value << 24);
        
        *pfs_register |= GPIO_CFG_ALT_FUNCTION;
    } else {
        *pfs_register &= ~PFS_PSEL_MASK;
        *pfs_register &= ~GPIO_CFG_ALT_FUNCTION;
    }

    PWPR_REGISTER_BASE = 0x00;
    PWPR_REGISTER_BASE = 0x80;
}

static void hal_ll_gpio_clock_enable( uint32_t port, uint32_t* port_pcr_base_addr )
{
    uint32_t port_index;
    uint32_t *sysma_addr = (uint32_t *)HAL_LL_CG_BASE_FSYSMENA_ADDR;

    port_index = hal_ll_gpio_get_port_number( port );

        switch(port_index){
        case 0:
            port_index = FSYSMENA_PORTA;
            break;
        case 1:
            port_index = FSYSMENA_PORTB;
            break;
        case 2:
            port_index = FSYSMENA_PORTC;
            break;
        case 3:
            port_index = FSYSMENA_PORTD;
            break;
        case 4:
            port_index = FSYSMENA_PORTE;
            break;
        case 5:
            port_index = FSYSMENA_PORTF;
            break;
        case 6:
            port_index = FSYSMENA_PORTG;
            break;
        case 7:
            port_index = FSYSMENA_PORTH;
            break;
        case 8:
            port_index = FSYSMENA_PORTJ;
            break;
        case 9 :
            port_index = FSYSMENA_PORTK;
            break;
        case 10:
            port_index = FSYSMENA_PORTL;
            break;
        case 11:
            port_index = FSYSMENA_PORTM;
            break;
        case 12:
            port_index = FSYSMENA_PORTN;
            break;
        case 13:
            port_index = FSYSMENA_PORTU;
            break;
        case 14:
            port_index = FSYSMENA_PORTV;
            break;
    }
    
    if ( port_index != (uint32_t)-1 ) {
        *sysma_addr = 0x00;
        *sysma_addr |= (1 << port_index);
    }
    
    if ( port_pcr_base_addr != NULL ) {
        *port_pcr_base_addr = 0;
    }
}

// ------------------------------------------------------------------------- END
