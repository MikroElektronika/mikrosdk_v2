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
 * @note Used for MAX32690 MCU (USBHS - musb driver).
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
 * @brief Core clock value in Hz.
 * @note Defined in usb_isr_routines.c (used by TinyUSB musb driver).
 */
extern volatile uint32_t SystemCoreClock;

/**
 * @brief Initializes USB.
 * @details Same as Analog Devices MSDK / TinyUSB board init:
 * IPO enabled, 0.9 V LDO enabled, USB peripheral clock enabled
 * and USB peripheral reset.
 * USB D+/D- are dedicated pins, so no pin setup is needed.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Internal primary oscillator.
    if (!(MXC_GCR->clkctrl & MXC_F_GCR_CLKCTRL_IPO_RDY)) {
        MXC_GCR->clkctrl |= MXC_F_GCR_CLKCTRL_IPO_EN;
        while (!(MXC_GCR->clkctrl & MXC_F_GCR_CLKCTRL_IPO_RDY));
    }

    // 0.9 V LDO for USB PHY.
    MXC_MCR->ldoctrl |= MXC_F_MCR_LDOCTRL_0P9EN;

    // USB peripheral clock.
    MXC_GCR->pclkdis0 &= ~MXC_F_GCR_PCLKDIS0_USB;

    // Reset USB peripheral.
    MXC_GCR->rst0 |= MXC_F_GCR_RST0_USB;
    while (MXC_GCR->rst0 & MXC_F_GCR_RST0_USB);
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
