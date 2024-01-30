/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  usb_hw.h
 * @brief Initializes USB HW module.
 * @details Sets clock, pins, etc.
 */

#ifndef _USB_HW_H_
#define _USB_HW_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu.h"
#include <stdint.h>

/*!
 * @addtogroup middleware Middleware
 * @{
 */

/*!
 * @addtogroup usb MikroE USB HW implementation.
 * @brief MikroE USB HW init library.
 *
 * @details This library initializes HW specific
 * USB pins/clock etc.
 * @{
 */

/**
 * @brief Enable analog functionality.
 * @details Enables analog functionality for provided @ref _pin.
 * The analog function of the pin is enabled, the isolation is
 * disabled, and the pin is capable of analog functions.
 * @note This register(@ref GPIO_PORTJ_AMSEL_R) and bits are only 
 * valid for GPIO signals that share analog function through a unified I/O pad.
 */
#define analog_function_enable(_pin) (GPIO_PORTJ_AMSEL_R |= 1U << _pin)

/**
 * @brief Pin numbers.
 */
#define GPIO_PORTJ_PIN0 (0)
#define GPIO_PORTJ_PIN1 (1)

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock to J0 and J1 pins - DP/DM pins.
    SYSCTL_RCGC2_R |= SYSCTL_GPIOHBCTL_PORTJ;
    // Enable clock to B0 and B1 pins - USB0ID/USB0VBUS pins.
    SYSCTL_RCGC2_R |= SYSCTL_GPIOHBCTL_PORTB;
    // Make sure AHB (Advanced High-Performance Bus) is disabled
    // for previously selected pins.
    SYSCTL_GPIOHBCTL_R &= ~(SYSCTL_GPIOHBCTL_PORTJ | SYSCTL_GPIOHBCTL_PORTB);
    // The analog functions of the pins are enabled, the isolation is
    // disabled, and the pins are capable of analog functions.
    analog_function_enable(GPIO_PORTJ_PIN0);
    analog_function_enable(GPIO_PORTJ_PIN1);
    // Enable general USB clock.
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_USB0;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
