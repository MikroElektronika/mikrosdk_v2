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
#include "interrupts.h"
// Note: Added for MikroE implementation.
// MikroE interrupt source uses NVIC -> (IRQx + 16).
#define NVIC_EnableIRQ(_x)  interrupt_enable(_x + 16)
#define NVIC_DisableIRQ(_x) interrupt_disable(_x + 16)
#define power_set()         ( USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_PWRDWN )
#ifdef USB_OTG_GCCFG_VBUSASEN
#define vbus_enable()       ( USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBUSASEN )
#else
#define vbus_enable()       ( USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBDEN )
#endif

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
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock for GPIO_PORT_A.
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // Alternate function enable for pins GPIO_PA12 and GPIO_PA11.
    GPIOA->MODER |= GPIO_MODER_MODER11_1;
    GPIOA->MODER |= GPIO_MODER_MODER12_1;
    // Pins speed selection.
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR11_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR12_1;
    // Setting alternate function AF10 for pins A11, A12.
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH3_1;
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH3_3;
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH4_1;
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH4_3;

    // Alternate function enable for pin GPIO_PA10.
    GPIOA->MODER |= GPIO_MODER_MODER10_1;
    // Configure pin as Open drain.
    GPIOA->OTYPER |= GPIO_OTYPER_OT10_Msk;
    // Configure pin Pull up.
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;
    // Setting alternate function for pin.
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH2_1;
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH2_3;

    // USB_OTG_FS Clock enable.
    RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
    // System Clock Configuration Clock enable.
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
