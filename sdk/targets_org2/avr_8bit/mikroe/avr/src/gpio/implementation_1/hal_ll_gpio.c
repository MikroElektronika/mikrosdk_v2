/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file hal_ll_port_gpio.c
 * @brief Low level HAL GPIO source file.
 */

#include "hal_ll_gpio_port.h"

/*******************************************************************************
 *
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction) {
    // Get pin base.
    pin->base = (hal_ll_gpio_base_t)hal_ll_gpio_port_base_map( hal_ll_gpio_port_index ( name ) );

    // Get pin mask.
    pin->mask = hal_ll_gpio_port_pin_mask( name );

    if ( HAL_LL_GPIO_DIGITAL_INPUT == direction ) {
        hal_ll_gpio_port_digital_input( pin->base, name );
    } else if ( HAL_LL_GPIO_DIGITAL_OUTPUT == direction ) {
        hal_ll_gpio_port_digital_output( pin->base, name );
    } else {
        hal_ll_gpio_port_analog_input( pin->base, name );
    }
}

/*******************************************************************************
 *
 */
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)pin->base;

    /**
    * @brief A "NOP" instruction is included because of the fact
    * a single signal transition on the pin will be delayed between
    * ½ and 1½ system clock period depending upon the time of assertion.
    */
    asm {nop};
    return ( ( *(uint8_t *)port_ptr->pin_reg_addr ) & pin->mask ) ? 0x01: 0x00;
}

/*******************************************************************************
 *
 */
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)pin->base;

    /**
    * @brief A "NOP" instruction is included because of the fact
    * a single signal transition on the pin will be delayed between
    * ½ and 1½ system clock period depending upon the time of assertion.
    */
    asm {nop};
    return ( ( *(uint8_t *)port_ptr->port_reg_addr ) & pin->mask ) ? 0x01: 0x00;
}

/*******************************************************************************
 *
 */
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t*)pin->base;

    if (value) {
        *(uint8_t *)port_ptr->port_reg_addr |= pin->mask;
    } else {
        *(uint8_t *)port_ptr->port_reg_addr &= ~pin->mask;
    }
}

/*******************************************************************************
 *
 */
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin) {
    uint8_t value = hal_ll_gpio_read_pin_output( pin );
    hal_ll_gpio_write_pin_output( pin, !value );
}

/*******************************************************************************
 *
 */
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t*)pin->base;

    *(uint8_t *)port_ptr->port_reg_addr |= pin->mask;
}

/*******************************************************************************
 *
 */
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t*)pin->base;

    *(uint8_t *)port_ptr->port_reg_addr &= ( ~( pin->mask ) );
}

/*******************************************************************************
 *
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction) {
    if( PORT_COUNT <= name ) {
        port->base = NULL;
        port->mask = HAL_LL_PIN_NC;
    } else {
        // Get port base.
        port->base = (hal_ll_gpio_base_t)hal_ll_gpio_port_base_map( name );

        // Get mask of desired pin/s.
        port->mask = mask;
    }

    // Check if digital input functionality is needed.
    if ( HAL_LL_GPIO_DIGITAL_INPUT == direction ) {
        hal_ll_gpio_port_digital_configure_port(port, name, true);
    // Otherwise, digital output functionality is needed.
    } else {
        hal_ll_gpio_port_digital_configure_port(port, name, false);
    }
}

/*******************************************************************************
 *
 */
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t*)port->base;

    return  ( *( uint8_t *)port_ptr->pin_reg_addr ) & port->mask;
}

/*******************************************************************************
 *
 */
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port) {
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t*)port->base;

    return  ( *( uint8_t *)port_ptr->port_reg_addr ) & port->mask;
}
/*******************************************************************************
 *
 */
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value) {
    // Get appropriate PORT, DDR and PIN register.
    hal_ll_gpio_base_handle_t *port_ptr = (hal_ll_gpio_base_handle_t *)port->base;

    // Write user-defined value on port.
    *(uint8_t *)port_ptr->port_reg_addr = value & port->mask;
}
// ------------------------------------------------------------------------- END
