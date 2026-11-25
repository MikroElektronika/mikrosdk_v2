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
 * @note Used for SAME70, SAMS70, SAMV70 and SAMV71 MCUs (USBHS - samx7x driver).
 * @note USB clock: UTMI PLL (480 MHz) from the 12 MHz main crystal oscillator
 * (USB clock setting). USB_48M (full speed) = UPLLCK / 10.
 */

#ifndef _USB_HW_H_
#define _USB_HW_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu.h"

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
 * @brief PMC registers (same layout as MikroE SAM HAL, hal_ll_pmc.h).
 */
#define USB_HW_PMC_SCER         (*(volatile uint32_t *)0x400E0600UL)
#define USB_HW_CKGR_UCKR        (*(volatile uint32_t *)0x400E061CUL)
#define USB_HW_CKGR_MOR         (*(volatile uint32_t *)0x400E0620UL)
#define USB_HW_PMC_USB          (*(volatile uint32_t *)0x400E0638UL)
#define USB_HW_PMC_SR           (*(volatile uint32_t *)0x400E0668UL)
#define USB_HW_PMC_PCER1        (*(volatile uint32_t *)0x400E0700UL)

#define USB_HW_PMC_SCER_USBCLK      (1UL << 5)
#define USB_HW_CKGR_UCKR_UPLLEN     (1UL << 16)
#define USB_HW_CKGR_UCKR_UPLLCOUNT  (0xFUL << 20)  // Maximum UTMI PLL start-up time.
#define USB_HW_CKGR_MOR_MOSCSEL     (1UL << 24)
#define USB_HW_PMC_USB_USBS_UPLL    (1UL << 0)
#define USB_HW_PMC_USB_USBDIV_10    (9UL << 8)     // USB_48M = 480 MHz / 10.
#define USB_HW_PMC_SR_LOCKU         (1UL << 6)

/**
 * @brief Initializes USB.
 * @details UTMI PLL is normally started by the core (USB clock setting).
 * If it isn't running, it is started here - only when the main crystal
 * oscillator is selected, as UTMI PLL can't run from the RC oscillator.
 * Enables the USB_48M clock and the USBHS peripheral clock.
 * USB D+/D- are dedicated pins, so no pin setup is needed.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    if (!(USB_HW_PMC_SR & USB_HW_PMC_SR_LOCKU)) {
        if (!(USB_HW_CKGR_MOR & USB_HW_CKGR_MOR_MOSCSEL)) {
            return; // No main crystal oscillator - select USB clock setting for the MCU.
        }
        USB_HW_CKGR_UCKR = USB_HW_CKGR_UCKR_UPLLCOUNT | USB_HW_CKGR_UCKR_UPLLEN;
        while (!(USB_HW_PMC_SR & USB_HW_PMC_SR_LOCKU));
    }

    // USB_48M clock (used in full speed mode).
    USB_HW_PMC_USB = USB_HW_PMC_USB_USBS_UPLL | USB_HW_PMC_USB_USBDIV_10;
    USB_HW_PMC_SCER = USB_HW_PMC_SCER_USBCLK;

    // USBHS peripheral clock.
    USB_HW_PMC_PCER1 = 1UL << (ID_USBHS - 32);
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
