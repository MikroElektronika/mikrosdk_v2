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
 * @note This register(@ref GPIO_PORTx_AMSEL_R) and bits are only
 * valid for GPIO signals that share analog function through a unified I/O pad.
 */
#define analog_function_enable(_reg,_pin) (_reg |= 1U << _pin)

/**
 * @brief Enable alternate functionality.
 * @details Enables alternate functionality for provided @ref _pin.
 * The associated pin functions as a peripheral signal and is
 * controlled by the alternate hardware function.
 */
#define alternate_function_enable(_pin) (GPIO_PORTB_AHB_AFSEL_R |= 1U << _pin)

/**
 * @brief Pin numbers.
 */
#define GPIO_PORTB_PIN0 (0)
#define GPIO_PORTB_PIN1 (1)
#define GPIO_PORTL_PIN6 (6)
#define GPIO_PORTL_PIN7 (7)
#define USB_DP_PIN GPIO_PORTL_PIN6
#define USB_DN_PIN GPIO_PORTL_PIN7
#define USB_ID_PIN GPIO_PORTB_PIN0
#define USB_VBUS_PIN GPIO_PORTB_PIN1

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock to USB0ID/USB0VBUS pins.
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    // Enable clock to DP/DM pins.
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;
    // Set pins as analog.
    // The analog functions of the pins are enabled, the isolation is
    // disabled, and the pins are capable of analog functions.
    analog_function_enable(GPIO_PORTB_AHB_AMSEL_R,GPIO_PORTB_PIN0);
    analog_function_enable(GPIO_PORTB_AHB_AMSEL_R,GPIO_PORTB_PIN1);
    // Set pins alternate function.
    // The associated pin functions as a peripheral signal and is
    // controlled by the alternate hardware function.
    alternate_function_enable(GPIO_PORTB_PIN0);
    alternate_function_enable(GPIO_PORTB_PIN1);
    // Set pins as analog.
    // The analog functions of the pins are enabled, the isolation is
    // disabled, and the pins are capable of analog functions.
    analog_function_enable(GPIO_PORTL_AMSEL_R,USB_DN_PIN);
    analog_function_enable(GPIO_PORTL_AMSEL_R,USB_DP_PIN);
    // Enable general USB clock.
    SYSCTL_RCGCUSB_R |= SYSCTL_RCGCUSB_R0;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
