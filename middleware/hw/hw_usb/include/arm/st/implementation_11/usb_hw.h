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
 * @note Used for STM32G0B1/STM32G0C1 MCUs (USB DRD FS - stm32_fsdev driver).
 */

#ifndef _USB_HW_H_
#define _USB_HW_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu.h"
#include "interrupts.h"

/**
 * @brief Enable an interrupt for the given IRQ number.
 * @param _x IRQ number (without +16 offset).
 * @note MikroE interrupt source uses NVIC -> (IRQx + 16).
 */
#define NVIC_EnableIRQ(_x)  interrupt_enable(_x + 16)

/**
 * @brief Disable an interrupt for the given IRQ number.
 * @param _x IRQ number (without +16 offset).
 * @note MikroE interrupt source uses NVIC -> (IRQx + 16).
 */
#define NVIC_DisableIRQ(_x) interrupt_disable(_x + 16)

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
 * USB DP/DM (PA12/PA11) are connected to the USB peripheral
 * automatically once it is enabled, so no GPIO setup is needed.
 * USB is clocked from the internal HSI48 oscillator, trimmed by
 * the CRS from the USB SOF packets, so it doesn't depend on the
 * user PLL configuration.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock for GPIO_PORT_A.
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    // System Clock Configuration Clock enable.
    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;

    // Enable PWR clock.
    RCC->APBENR1 |= RCC_APBENR1_PWREN;
    #ifdef PWR_CR2_USV
    // VDDUSB supply valid - remove USB isolation.
    PWR->CR2 |= PWR_CR2_USV;
    #endif

    // Turn HSI48 on.
    RCC->CR |= RCC_CR_HSI48ON;
    // Wait for HSI48 to stabilize.
    while(!(RCC->CR & RCC_CR_HSI48RDY));
    // Select HSI48 as USB clock source (USBSEL = 00).
    RCC->CCIPR2 &= ~RCC_CCIPR2_USBSEL;

    // Enable CRS clock and automatic HSI48 trimming.
    // Default CRS sync source is USB SOF.
    RCC->APBENR1 |= RCC_APBENR1_CRSEN;
    CRS->CR |= CRS_CR_AUTOTRIMEN | CRS_CR_CEN;

    // USB FS Clock enable.
    RCC->APBENR1 |= RCC_APBENR1_USBEN;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
