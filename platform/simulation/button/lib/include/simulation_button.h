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
 * @file  simulation_button.h
 * @brief mikroSDK button simulation library.
 */

#ifndef _SIMULATION_BUTTON_H_
#define _SIMULATION_BUTTON_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include "drv_digital_out.h"
#include "delays.h"

/*!
 * @addtogroup platform Platform
 * @{
 */

/*!
 * @addtogroup sim_button Button simulation.
 * @brief Button simulation library.
 * @{
 */

typedef struct
{
    digital_out_t pin;
    bool init_state;
} sim_button_t;

/**
 * @brief Initializes the button simulation module.
 *
 * Configures the pin used to simulate a button.
 *
 * @param[in] sim_button_t *button Pointer to the button simulation object.
 * @param[in] pin_name_t pin_name Pin name (GPIO_PA0, GPIO_PA1, ...).
 *
 * @return void None.
 */
void sim_button_init( sim_button_t *button, pin_name_t pin_name );

/**
 * @brief Presses and holds the button.
 *
 * Switches the button to the "on" ("pressed") state and holds it.
 *
 * @param[in] sim_button_t *button Pointer to the button simulation object.
 *
 * @return void None.
 */
void sim_button_press_and_hold( sim_button_t *button );

/**
 * @brief Press the button for a specified number of milliseconds.
 *
 * Keep the button pressed for the given duration in milliseconds.
 *
 * @param[in] sim_button_t *button Pointer to the button simulation object.
 * @param[in] uint32_t delay_milliseconds The duration for which the button stays pressed.
 *
 * @return void None.
 */
void sim_button_press_ms( sim_button_t *button, uint32_t delay_milliseconds );

/**
 * @brief Toggles the state of the button.
 *
 * Changes the button's state between pressed and released.
 *
 * @param[in] sim_button_t *button Pointer to the button simulation object.
 *
 * @return void None.
 */
void sim_button_toggle( sim_button_t *button );

/**
 * @brief Checks the state of the button.
 *
 * Returns whether the button is pressed or released.
 *
 * @param[in] sim_button_t *button Pointer to the button simulation object.
 *
 * @return bool The state of the button (pressed or released).
 */
bool sim_button_is_pressed( sim_button_t *button );

/**
 * @brief Releases the button.
 *
 * Sets the button pin to input, releasing it.
 *
 * @param[in] sim_button_t *button Pointer to the button simulation object.
 *
 * @return void None.
 */
void sim_button_release( sim_button_t *button );

/*TODO*/

/*! @} */ // sim_button
/*! @} */ // platform

#ifdef __cplusplus
}
#endif

/*! @} */

#endif // _SIMULATION_BUTTON_H_
// ------------------------------------------------------------------------- END
