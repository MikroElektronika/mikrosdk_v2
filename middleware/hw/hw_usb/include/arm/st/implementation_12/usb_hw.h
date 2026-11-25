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
 * @note Used for STM32H74x/STM32H75x MCUs (USB2 OTG FS - synopsys dwc2 driver).
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

/**
 * @def power_set
 * @brief Enable USB PHY power-down mode (power-on the USB transceiver).
 * This macro sets the **PWRDWN** bit in the `USB_OTG_FS->GCCFG` register,
 * which powers up the USB transceiver (PHY) and enables USB functionality.
 * @note
 * - This is required before enabling USB VBUS sensing or starting the USB peripheral.
 * - `USB_OTG_FS` refers to the USB2 Full-Speed OTG peripheral (USB2_OTG_FS) on STM32H7.
 */
#define power_set()         ( USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_PWRDWN )

/**
 * @def vbus_enable
 * @brief Enable VBUS sensing for USB OTG FS peripheral.
 * Configures the USB OTG FS core to sense the VBUS (USB power supply line)
 * depending on the MCU variant:
 * - If `USB_OTG_GCCFG_VBUSASEN` is defined, sets the **VBUSASEN** bit.
 * - Otherwise sets the **VBDEN** bit for VBUS detection.
 * @note
 * - This step is required for the USB peripheral to detect when a cable
 *   is plugged in and the host provides VBUS power.
 * - Macro selects the appropriate register bit depending on the silicon version.
 */
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
 * Sets PA11 (DM) and PA12 (DP) to AF10 (OTG_FS).
 * USB is clocked from the internal HSI48 oscillator, trimmed by
 * the CRS from the USB SOF packets, so it doesn't depend on the
 * user PLL configuration.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock for GPIO_PORT_A.
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
    // System Clock Configuration Clock enable.
    RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;

    // PA11 and PA12 - Alternate function mode.
    GPIOA->MODER &= ~(GPIO_MODER_MODE11_Msk | GPIO_MODER_MODE12_Msk);
    GPIOA->MODER |= (0x2UL << GPIO_MODER_MODE11_Pos) | (0x2UL << GPIO_MODER_MODE12_Pos);
    // PA11 and PA12 - Push pull, no pull.
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT11 | GPIO_OTYPER_OT12);
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD11_Msk | GPIO_PUPDR_PUPD12_Msk);
    // PA11 and PA12 - Very high speed.
    GPIOA->OSPEEDR |= (0x3UL << GPIO_OSPEEDR_OSPEED11_Pos) | (0x3UL << GPIO_OSPEEDR_OSPEED12_Pos);
    // PA11 and PA12 - AF10 (OTG_FS).
    GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL11_Msk | GPIO_AFRH_AFSEL12_Msk);
    GPIOA->AFR[1] |= (0xAUL << GPIO_AFRH_AFSEL11_Pos) | (0xAUL << GPIO_AFRH_AFSEL12_Pos);

    // Enable USB voltage level detector.
    PWR->CR3 |= PWR_CR3_USB33DEN;
    // Wait for USB regulator/VDD33USB to be ready.
    while(!(PWR->CR3 & PWR_CR3_USB33RDY));

    // Turn HSI48 on.
    RCC->CR |= RCC_CR_HSI48ON;
    // Wait for HSI48 to stabilize.
    while(!(RCC->CR & RCC_CR_HSI48RDY));
    // Select HSI48 as USB clock source (USBSEL = 11).
    RCC->D2CCIP2R |= RCC_D2CCIP2R_USBSEL_Msk;

    // Enable CRS clock and automatic HSI48 trimming.
    // Default CRS sync source is USB2 OTG FS SOF.
    RCC->APB1HENR |= RCC_APB1HENR_CRSEN;
    CRS->CR |= CRS_CR_AUTOTRIMEN | CRS_CR_CEN;

    // USB2_OTG_FS Clock enable.
    RCC->AHB1ENR |= RCC_AHB1ENR_USB2OTGFSEN;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
