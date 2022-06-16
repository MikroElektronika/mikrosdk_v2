/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  hal_ll_gpio.h
 * @brief This file contains all the functions prototypes for the GPIO library.
 */

#ifndef _HAL_LL_GPIO_H_
#define _HAL_LL_GPIO_H_

#include "hal_ll_gpio_port.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Function configures pin.
 *
 * Configures pin to digital output or digital input.
 * Sets only the pin defined by pin mask in
 * hal_ll_gpio_pin_t structure.
 *
 * @param *pin Pin object context.
 *             Configured during this functions process.
 * @param name Pin name -- PA0, PA1...
 * @param direction Pin direction.
 * HAL_LL_GPIO_DIGITAL_INPUT
 * HAL_LL_GPIO_DIGITAL_OUTPUT
 *
 * @return None.
 */
void hal_ll_gpio_configure_pin(hal_ll_gpio_pin_t *pin, hal_ll_pin_name_t name, hal_ll_gpio_direction_t direction);

/**
 * @brief Read pin input.
 *
 * Checks pin data input register value and
 * returns logical state.
 *
 * @param *pin Pin object context.
 *             Configured during hal_ll_gpio_configure_pin.
 *
 * @return uint8_t Pin logical state.
 * 1/true -- pin high state -- 1.8V or more detected
 * 0/false -- pin low state -- 1.8V or less detected
 */
uint8_t hal_ll_gpio_read_pin_input(hal_ll_gpio_pin_t *pin);

/**
 * @brief Read pin output.
 *
 * Checks pin data output register value and
 * returns logical state.
 *
 * @param *pin Pin object context.
 *             Configured during hal_ll_gpio_configure_pin.
 *
 * @return uint8_t Pin logical state.
 * 1/true -- pin high state -- 1.8V or more detected
 * 0/false -- pin low state -- 1.8V or less detected
 */
uint8_t hal_ll_gpio_read_pin_output(hal_ll_gpio_pin_t *pin);

/**
 * @brief Writes pin output state.
 *
 * Sets single pin logical state.
 *
 * @param *pin Pin object context.
 *             Configured during hal_ll_gpio_configure_pin.
 * @param value Pin logical state.
 * 1/true -- sets pin high state -- over 1.8V
 * 0/false -- sets pin low state -- less than 1.8V
 *
 * @return None
 */
void hal_ll_gpio_write_pin_output(hal_ll_gpio_pin_t *pin, uint8_t value);

/**
 * @brief Toggles pin logical state.
 *
 * Checks current state of pin
 * and toggles it.
 *
 * @param *pin Pin object context.
 *             Configured during hal_ll_gpio_configure_pin.
 *
 * @return None
 */
void hal_ll_gpio_toggle_pin_output(hal_ll_gpio_pin_t *pin);

/**
 * @brief Sets pin logical state.
 *
 * Sets pin logical state to high.
 *
 * @param *pin Pin object context.
 *             Configured during hal_ll_gpio_configure_pin.
 *
 * @return None
 */
void hal_ll_gpio_set_pin_output(hal_ll_gpio_pin_t *pin);

/**
 * @brief Sets pin logical state.
 *
 * Sets pin logical state to low.
 *
 * @param *pin Pin object context.
 *             Configured during hal_ll_gpio_configure_pin.
 *
 * @return None
 */
void hal_ll_gpio_clear_pin_output(hal_ll_gpio_pin_t *pin);

/**
 * @brief Configures port.
 *
 * Configures port according to specified
 * direction. Takes into consideration only
 * pins defined by mask.
 *
 * @param *port Port object context.
 *              Configured during this functions process.
 * @param name Port name.
 * @param mask Port pin mask.
 * @param direction Port pin direction.
 * HAL_LL_GPIO_DIGITAL_INPUT
 * HAL_LL_GPIO_DIGITAL_OUTPUT
 *
 * @return None
 */
void hal_ll_gpio_configure_port(hal_ll_gpio_port_t *port, hal_ll_port_name_t name, hal_ll_gpio_mask_t mask, hal_ll_gpio_direction_t direction);

/**
 * @brief Read port input value.
 *
 * Checks port data input register value and
 * returns it.
 *
 * @param *port Port object context.
 *              Configured during hal_ll_gpio_configure_port.
 *
 * @return hal_ll_port_size_t Port input data register value.
 */
hal_ll_port_size_t hal_ll_gpio_read_port_input(hal_ll_gpio_port_t *port);

/**
 * @brief Read port output value.
 *
 * Checks port data output register value and
 * returns it.
 *
 * @param *port Port object context.
 *              Configured during hal_ll_gpio_configure_port.
 * @return hal_ll_port_size_t Port output data register value.
 */
hal_ll_port_size_t hal_ll_gpio_read_port_output(hal_ll_gpio_port_t *port);

/**
 * @brief Set port state.
 *
 * Sets port output state.
 * Will take into consideration only
 * port pins defined by mask in
 * port object context.
 *
 * @param *port Port object context.
 *              Configured during hal_ll_gpio_configure_port.
 *
 * @return None
 */
void hal_ll_gpio_write_port_output(hal_ll_gpio_port_t *port, hal_ll_port_size_t value);

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_GPIO_H_
// ------------------------------------------------------------------------- END
