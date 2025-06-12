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

/*******************************************************************************
 *
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction) {
    pin->base = (hal_ll_gpio_base_t)hal_ll_gpio_port_base(hal_ll_gpio_port_index(name));
    pin->mask = hal_ll_gpio_pin_mask(name);

    if ( direction == HAL_LL_GPIO_DIGITAL_INPUT)
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

    gpio_data_value = ((hal_ll_gpio_base_handle_t *)(pin->base))->pidr;
    return (gpio_data_value & pin->mask) ? 0x01 : 0x00;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin) {
    uint8_t gpio_data_value;

    gpio_data_value = ((hal_ll_gpio_base_handle_t *)(pin->base))->podr;
    return (gpio_data_value & pin->mask) ? 0x01 : 0x00;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value) {
    if (value)
        ((hal_ll_gpio_base_handle_t *)(pin->base))->podr |= pin->mask;
    else
        ((hal_ll_gpio_base_handle_t *)(pin->base))->podr &= ~pin->mask;
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
    ((hal_ll_gpio_base_handle_t *)(pin->base))->podr |= pin->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin) {
    ((hal_ll_gpio_base_handle_t *)(pin->base))->podr &= ~pin->mask;
}
#endif

/*******************************************************************************
 *
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction) {
    port->base = hal_ll_gpio_port_base(name);
    port->mask = mask;

    if (direction == HAL_LL_GPIO_DIGITAL_INPUT)
        hal_ll_gpio_digital_input(&port->base, port->mask);
    else
        hal_ll_gpio_digital_output(&port->base, port->mask);
}

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port) {
    uint8_t gpio_data_value;
    return ((hal_ll_gpio_base_handle_t *)(port->base))->pidr & port->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port) {
    uint8_t gpio_data_value;
    return ((hal_ll_gpio_base_handle_t *)(port->base))->podr & port->mask;
}
#endif

/*******************************************************************************
 *
 */
#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_LOW)
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value) {
    hal_ll_gpio_base_handle_t *base_reg = (hal_ll_gpio_base_handle_t *)port->base;
    base_reg->podr = (uint32_t)(port->mask & value);
}
#endif

// ------------------------------------------------------------------------- END
