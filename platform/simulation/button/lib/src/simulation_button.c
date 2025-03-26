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
 * @file  simulation_button.c
 * @brief mikroSDK button simulation library source file.
 */

#include "simulation_button.h"

// ------------------------------------------------------------------------- STATIC FUNCTIONS DECLARATION

/**
 * @brief Delays execution for a specified time.
 * @details Pauses the program for the given number of milliseconds using a busy-wait loop.
 * @param[in] delay_milliseconds The number of milliseconds to delay.
 */
static inline void delay_millisecond( uint32_t delay_milliseconds );

// ------------------------------------------------------------------------- PUBLIC FUNCTIONS

err_t sim_button_init(sim_button_t *button, pin_name_t pin_name ) {
    // Initialize the `button` pin as output
    if ( DIGITAL_OUT_SUCCESS != digital_out_init( &button->pin, pin_name ) )
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    button->init_state = true;
}

void sim_button_press_and_hold( sim_button_t *button ) {
    if( button->init_state )
        digital_out_high( &button->pin );
}

void sim_button_press_ms( sim_button_t *button, uint32_t delay_milliseconds ) {
    if( button->init_state ) {
        digital_out_high( &button->pin );
        // Keep the button pressed for the desired number of milliseconds.
        delay_millisecond( delay_milliseconds );
        sim_button_release( button );
    }
}

void sim_button_toggle( sim_button_t *button ) {
    if( button->init_state ) {
        if( digital_out_read( &button->pin ) ) {
            // If the button is pressed, release it
            digital_out_low( &button->pin );
        } else {
            // If the button is released, press it
            digital_out_high( &button->pin );
        }
    }
}

bool sim_button_is_pressed( sim_button_t *button ) {
    if( button->init_state )
        return (bool)digital_out_read( &button->pin );
    else
        return false;
}

void sim_button_release( sim_button_t *button ) {
    if( button->init_state )
        digital_out_low( &button->pin );
}

// ------------------------------------------------------------------------- STATIC FUNCTIONS

static inline void delay_millisecond( uint32_t delay_milliseconds ) {
    uint32_t milliseconds = delay_milliseconds;

    while( milliseconds-- ) {
        Delay_ms(1);
    }
}

// ------------------------------------------------------------------------- END
