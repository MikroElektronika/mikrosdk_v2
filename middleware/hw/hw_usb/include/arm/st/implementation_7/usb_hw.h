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

// Clock value in Hz provided externally.
extern volatile uint32_t SystemCoreClock;

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // System Clock Configuration Clock enable.
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    // Enable access to the backup domain.
    PWR->CR1 |= PWR_CR1_DBP;
    // Modify LSE drive capability. (lower driving capability)
    RCC->BDCR &= ~RCC_BDCR_LSEDRV_Msk;
    // Enable clock for PORT_A.
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    /**
     * @brief Pin settings.
     * @details Setting following options for pins:
     * @arg PA9: Input, No pull
     * @arg PA11: Alternate Function Push Pull, No pull, Very High Speed, AF10 (OTG_FS)
     * @arg PA12: Alternate Function Push Pull, No pull, Very High Speed, AF10 (OTG_FS)
     */
    GPIOA->PUPDR = 0x64000000UL;
    GPIOA->OSPEEDR = 0xFC00000UL;
    GPIOA->OTYPER = 0UL;
    GPIOA->AFR[1] = 0xAA000UL;
    GPIOA->MODER = 0xAAB3FFFFUL;
    // Enable VDDUSB.
    if (!(RCC->APB1ENR1 & RCC_APB1ENR1_PWREN)) {
        RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
        PWR->CR2 |= PWR_CR2_USV;
        RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
    } else {
        PWR->CR2 |= PWR_CR2_USV;
    }
    #ifdef RCC_CRRCR_HSI48ON
    // Turn HSI48 on. Only for  L496/L4A6 devices.
    RCC->CRRCR |= RCC_CRRCR_HSI48ON;
    // Wait for HSI48 to stabilize.
    while(!(RCC->CRRCR & RCC_CRRCR_HSI48RDY));
    // Select HSI48 as USB clock source.
    RCC->CCIPR &= ~RCC_CCIPR_CLK48SEL;
    #endif
    // USB_OTG_FS Clock enable.
    RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
