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
 * @file  hal_ll_gpio.c
 * @brief GPIO HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_gpio_port.h"

/*!< @brief Marker stored in pin->base for virtual I2C-expander pins.
 *   0xF is never a valid real hardware base address (real bases live in
 *   MCU peripheral memory, e.g. 0x4008xxxx), so it can be told apart from
 *   any genuine hal_ll_gpio_port_base() result. */
#define HAL_LL_GPIO_EXPANDER_BASE_MARKER ((hal_ll_gpio_base_t) HAL_LL_GPIO_EXPANDER_PORT_INDEX)

/*!< @brief Weak, do-nothing defaults for the I2C GPIO-expander hooks.
 *   Boards that route some of their pins through an on-board I2C GPIO
 *   expander (e.g. Clicker 2 for TMPM4L4A / PCA9538A) provide real,
 *   non-weak implementations of these four functions in their own
 *   hal_ll_gpio_port.c. Boards that don't need this feature simply link
 *   these harmless defaults - nothing else in the SDK needs to change. */
__attribute__((weak)) uint8_t hal_ll_gpio_expander_pin_check( hal_ll_pin_name_t name ) {
    (void)name;
    return 0;
}

__attribute__((weak)) void hal_ll_gpio_expander_configure_pin( uint8_t bit, hal_ll_gpio_direction_t direction ) {
    (void)bit;
    (void)direction;
}

__attribute__((weak)) uint8_t hal_ll_gpio_expander_read_pin( uint8_t bit ) {
    (void)bit;
    return 0;
}

__attribute__((weak)) void hal_ll_gpio_expander_write_pin( uint8_t bit, uint8_t value ) {
    (void)bit;
    (void)value;
}

/*******************************************************************************
 *
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction) {
    if ( hal_ll_gpio_expander_pin_check( name ) ) {
        // Virtual pin routed through an I2C GPIO expander. We don't have a
        // real register address, so pin->base gets the sentinel marker and
        // pin->mask carries the raw expander bit index (0-7) instead of a
        // bitmask - both are only ever interpreted by the *_pin_input/
        // *_pin_output functions below, never dereferenced as a pointer.
        pin->base = HAL_LL_GPIO_EXPANDER_BASE_MARKER;
        pin->mask = (hal_ll_gpio_mask_t) ( name & 0x0F );
        hal_ll_gpio_expander_configure_pin( (uint8_t) pin->mask, direction );
        return;
    }

    pin->base = (hal_ll_gpio_base_t)hal_ll_gpio_port_base(hal_ll_gpio_port_index(name));
    pin->mask = hal_ll_gpio_pin_mask(name);

    if ( HAL_LL_GPIO_DIGITAL_INPUT == direction )
        hal_ll_gpio_digital_input(&pin->base, pin->mask);
    else
        hal_ll_gpio_digital_output(&pin->base, pin->mask);
}

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin) {
    uint8_t gpio_data_value;

    if ( HAL_LL_GPIO_EXPANDER_BASE_MARKER == pin->base )
        return hal_ll_gpio_expander_read_pin( (uint8_t) pin->mask );

    gpio_data_value = ((hal_ll_gpio_base_handle_t *)(pin->base))->data;
    return (gpio_data_value & pin->mask) ? 0x01 : 0x00;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin) {
    uint8_t gpio_data_value;

    if ( HAL_LL_GPIO_EXPANDER_BASE_MARKER == pin->base )
        return hal_ll_gpio_expander_read_pin( (uint8_t) pin->mask );

    gpio_data_value = ((hal_ll_gpio_base_handle_t *)(pin->base))->data;
    return (gpio_data_value & pin->mask) ? 0x01 : 0x00;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value) {
    if ( HAL_LL_GPIO_EXPANDER_BASE_MARKER == pin->base ) {
        hal_ll_gpio_expander_write_pin( (uint8_t) pin->mask, value );
        return;
    }

    if (value)
        ((hal_ll_gpio_base_handle_t *)(pin->base))->data |= pin->mask;
    else
        ((hal_ll_gpio_base_handle_t *)(pin->base))->data &= ~pin->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin) {
    uint8_t gpio_data_value = hal_ll_gpio_read_pin_output(pin);
    hal_ll_gpio_write_pin_output(pin, !gpio_data_value);
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin) {
    if ( HAL_LL_GPIO_EXPANDER_BASE_MARKER == pin->base ) {
        hal_ll_gpio_expander_write_pin( (uint8_t) pin->mask, 1 );
        return;
    }

    ((hal_ll_gpio_base_handle_t *)(pin->base))->data |= pin->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin) {
    if ( HAL_LL_GPIO_EXPANDER_BASE_MARKER == pin->base ) {
        hal_ll_gpio_expander_write_pin( (uint8_t) pin->mask, 0 );
        return;
    }

    ((hal_ll_gpio_base_handle_t *)(pin->base))->data &= ~pin->mask;
}
#endif

/*******************************************************************************
 *
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name,
                                hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction) {
    port->base = hal_ll_gpio_port_base(name);
    port->mask = mask;

    if ( HAL_LL_GPIO_DIGITAL_INPUT == direction )
        hal_ll_gpio_digital_input(&port->base, port->mask);
    else
        hal_ll_gpio_digital_output(&port->base, port->mask);
}

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port) {
    return ((hal_ll_gpio_base_handle_t *)(port->base))->data & port->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port) {
    return ((hal_ll_gpio_base_handle_t *)(port->base))->data & port->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value) {
    hal_ll_gpio_base_handle_t *base_reg = (hal_ll_gpio_base_handle_t *)port->base;
    base_reg->data = (base_reg->data & ~port->mask) | (port->mask & value);
}
#endif

// ------------------------------------------------------------------------- END
