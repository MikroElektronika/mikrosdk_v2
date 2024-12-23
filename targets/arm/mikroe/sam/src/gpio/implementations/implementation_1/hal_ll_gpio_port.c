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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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
#include "hal_ll_pmc.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**< @brief Utility macro for geting pin name based on port and bit for that pin on that port. */
#define HAL_LL_GET_PIN(port_name, pin_index) ( ( hal_ll_pin_name_t ) ( ( port_name << 0x04 ) + pin_index ) )

// -------------------------------------------------------------- PRIVATE TYPES

/**
 *  Defines used in source
 */
 // GPIO Register addresses and offsets
#ifdef __PORT_A_CN
#define HAL_LL_GPIOA_BASE_ADDR 0x400E0E00UL
#define HAL_LL_PMC_ID_PIOA_BIT 0x0A
#endif
#ifdef __PORT_B_CN
#define HAL_LL_GPIOB_BASE_ADDR 0x400E1000UL
#define HAL_LL_PMC_ID_PIOB_BIT 0x0B
#endif
#ifdef __PORT_C_CN
#define HAL_LL_GPIOC_BASE_ADDR 0x400E1200UL
#define HAL_LL_PMC_ID_PIOC_BIT 0x0C
#endif
#ifdef __PORT_D_CN
#define HAL_LL_GPIOD_BASE_ADDR 0x400E1400UL
#define HAL_LL_PMC_ID_PIOD_BIT 0x10
#endif
#ifdef __PORT_E_CN
#define HAL_LL_GPIOE_BASE_ADDR 0x400E1600UL
#define HAL_LL_PMC_ID_PIOE_BIT 0x11
#endif


#define HAL_LL_PERIPHERAL_A 0
#define HAL_LL_PERIPHERAL_B 1
#define HAL_LL_PERIPHERAL_C 2
#define HAL_LL_PERIPHERAL_D 3
// EOF GPIO Register addresses and offsets


/*!< @brief GPIO PORT array */
static const hal_ll_base_addr_t _hal_ll_gpio_port_base [ PORT_COUNT ] =
{
    #ifdef __PORT_A_CN
    HAL_LL_GPIOA_BASE_ADDR,
    #endif
    #ifdef __PORT_B_CN
    HAL_LL_GPIOB_BASE_ADDR,
    #endif
    #ifdef __PORT_C_CN
    HAL_LL_GPIOC_BASE_ADDR,
    #endif
    #ifdef __PORT_D_CN
    HAL_LL_GPIOD_BASE_ADDR,
    #endif
    #ifdef __PORT_E_CN
    HAL_LL_GPIOE_BASE_ADDR
    #endif
};

// ----------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
  * @brief  Configure single port pins
  *
  * @param[in] port     - port base address
  * @param[in] pin_mask - desired pin
  * @param[in] config   - pin settings
  * @return none
  */
static void hal_ll_gpio_config( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask, uint8_t config );

/**
  * @brief  Configure pin that has analog function.
  *
  * @param[in] pin - Desired pin.
  * @param[in] is_digital - Pin configuration( true = digital, false = analog ).
  * @return none
  */
static void hal_ll_gpio_port_configure_analog_pin( hal_ll_pin_name_t pin, bool is_digital );

/**
  * @brief  Configure port pins.
  *
  * @param[in]  port - Port base address.
  * @param[in]  pin - Desired single pin.
  * @param[in]  config - Pin settings.
  * @return     none
  */
static void hal_ll_gpio_port_config( hal_ll_gpio_base_t *port, hal_ll_pin_name_t pin, uint32_t config );

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void hal_ll_gpio_config_pin_alternate_enable( uint8_t module_pin, uint8_t module_config, bool state );

// ------------------------------------------------ PUBLIC FUNCTION DEFFINITIONS

static uint8_t hal_ll_gpio_pin_index( hal_ll_pin_name_t name )
{
    return ( hal_ll_port_name_t )name % PORT_SIZE;
}

uint8_t hal_ll_gpio_port_index( hal_ll_pin_name_t name )
{
    return ( hal_ll_port_name_t )name / PORT_SIZE;
}

hal_ll_gpio_mask_t hal_ll_gpio_pin_mask( hal_ll_pin_name_t name )
{
    return ( ( hal_ll_gpio_mask_t )0x01 << hal_ll_gpio_pin_index( name ) );
}

hal_ll_base_addr_t hal_ll_gpio_port_base( hal_ll_port_name_t name )
{
    return _hal_ll_gpio_port_base[ name ];
}

void hal_ll_gpio_analog_input( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask )
{
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_ANALOG );
}

void hal_ll_gpio_digital_input( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask )
{
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_INPUT );
}

void hal_ll_gpio_digital_output( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask )
{
    hal_ll_gpio_config( port, pin_mask, GPIO_CFG_MODE_OUTPUT );
}

void hal_ll_gpio_module_struct_init( module_struct const *module, bool state )
{
    int8_t index = 0;

    while ( module->pins[ index ] != GPIO_MODULE_STRUCT_END )
    {
        hal_ll_gpio_config_pin_alternate_enable( module->pins[ index ], module->configs[ index ], state );

        index++;
    }
}

/**
  * @brief  Enable gpio port clock
  * @param  port - port base address
  * @return none
  */
static void hal_ll_gpio_clock_enable( hal_ll_gpio_base_t *port )
{
    hal_ll_gpio_mask_t pos = 0;

    switch ( ( hal_ll_base_addr_t )port )
    {
        #ifdef __PORT_A_CN
        case HAL_LL_GPIOA_BASE_ADDR: pos = HAL_LL_PMC_ID_PIOA_BIT;   break;
        #endif
        #ifdef __PORT_B_CN
        case HAL_LL_GPIOB_BASE_ADDR: pos = HAL_LL_PMC_ID_PIOB_BIT;   break;
        #endif
        #ifdef __PORT_C_CN
        case HAL_LL_GPIOC_BASE_ADDR: pos = HAL_LL_PMC_ID_PIOC_BIT;   break;
        #endif
        #ifdef __PORT_D_CN
        case HAL_LL_GPIOD_BASE_ADDR: pos = HAL_LL_PMC_ID_PIOD_BIT;   break;
        #endif
        #ifdef __PORT_E_CN
        case HAL_LL_GPIOE_BASE_ADDR: pos = HAL_LL_PMC_ID_PIOE_BIT;   break;
        #endif
    }

    set_reg_bit( _PMC_PCER0, pos );
}

static void hal_ll_gpio_config( hal_ll_gpio_base_t *port, hal_ll_gpio_mask_t pin_mask, uint8_t config )
{
    uint8_t  pin_num     = 0;
    hal_ll_gpio_mask_t pin_pos     = 0;
    hal_ll_gpio_mask_t current_pin = 0;
    hal_ll_base_addr_t port_base   = 0;

    hal_ll_gpio_base_handle_t *port_ptr;

    port_ptr = ( hal_ll_gpio_base_handle_t *)port;

    hal_ll_gpio_clock_enable( port );

    // Check if it is a digital signal or alternate function
    if ( config != GPIO_CFG_MODE_ANALOG ) {
        if ( config == GPIO_CFG_MODE_INPUT ) {
            // Set gpio direction as input with filtering.
            port_ptr->pio.enable |= pin_mask;
            port_ptr->filter.enable |= pin_mask;
        } else {
            // Set gpio direction as output and enable Pull Up resistor.
            port_ptr->pio.enable |= pin_mask;
            port_ptr->output.enable |= pin_mask;
            port_ptr->pullup_off.disable |= pin_mask;
        }
    }
    else {
        // Set pin to analog.
        port_ptr->pio.disable = pin_mask;
    }
}

/**
  * @brief  Configure port pins alternate
  *         functions
  * @param  module_pin - desired pin
  *         config     - pin settings
  * @return none
  */
static void hal_ll_gpio_config_pin_alternate_enable( uint8_t module_pin, uint8_t module_config, bool state )
{
    hal_ll_pin_name_t pin_index;
    hal_ll_gpio_base_handle_t *port_ptr;

    // Get the port address.
    port_ptr = ( hal_ll_gpio_base_handle_t *)hal_ll_gpio_port_base( hal_ll_gpio_port_index ( module_pin ) );

    // Get the pin index.
    pin_index = hal_ll_gpio_pin_index( module_pin );

    // Disable PIO control over this pin.
    port_ptr->pio.disable |= 1 << pin_index;

    switch ( module_config ) {
        case HAL_LL_PERIPHERAL_A:
            clear_reg_bit( &port_ptr->abcdsr0, pin_index );
            clear_reg_bit( &port_ptr->abcdsr1, pin_index );
            break;
        case HAL_LL_PERIPHERAL_B:
            set_reg_bit( &port_ptr->abcdsr0, pin_index );
            clear_reg_bit( &port_ptr->abcdsr1, pin_index );
            break;
        case HAL_LL_PERIPHERAL_C:
            clear_reg_bit( &port_ptr->abcdsr0, pin_index );
            set_reg_bit( &port_ptr->abcdsr1, pin_index );
            break;
        case HAL_LL_PERIPHERAL_D:
            set_reg_bit( &port_ptr->abcdsr0, pin_index );
            set_reg_bit( &port_ptr->abcdsr1, pin_index );
            break;
    }
}
// ------------------------------------------------------------------------- END
