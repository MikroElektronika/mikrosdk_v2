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
 * @details Sets clock, interrupt, etc.
 * @note Used for RA4M2, RA4M3, RA4E1, RA6E1, RA6M4 and RA6M5 MCUs (USBFS device - renesas rusb2 driver).
 * @note UCLK = PLL2 (240 MHz, from HOCO) / 5. PLL2 is started here if it is stopped; if it already runs it has to be set to 240 MHz.
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
 * USB clock and interrupt.
 * @{
 */

/**
 * @brief Number of ICU event link slots (IELSRn / IRQn) on these MCUs.
 */
#define USB_HW_RA_ICU_SLOT_COUNT    (96U)

/**
 * @brief ICU slot (IRQn) used for the USBFS interrupt.
 * @note The last ICU slot is used, because MikroE HAL modules use the lowest slots.
 */
#define USB_HW_RA_IRQ_SLOT          (95U)

/**
 * @brief IELSRn value of the USBFS_INT interrupt on these MCUs.
 */
#define USB_HW_RA_USBFS_INT_EVENT   (0x06DUL)

/**
 * @brief Register write protection (PRCR) keys.
 * @note Unlocks PRC0 (clock generation) and PRC1 (low power modes / MSTP).
 */
#define USB_HW_RA_PRCR_UNLOCK       (0xA503U)
#define USB_HW_RA_PRCR_LOCK         (0xA500U)

/**
 * @brief ICU IELSRn.IR (interrupt request) flag mask.
 */
#define USB_HW_RA_IELSR_IR_MSK      (1UL << 16)

/**
 * @brief Clears the ICU interrupt request flag of the USBFS interrupt.
 * @details Renesas RA ICU doesn't clear the IR flag automatically,
 * so it is cleared at the start of the generated USB ISR.
 */
#define USB_HW_ISR_PROLOGUE()       (R_ICU->IELSR[USB_HW_RA_IRQ_SLOT] &= ~USB_HW_RA_IELSR_IR_MSK)

/**
 * @brief USB interrupt service routine.
 * @note Generated in usb_isr_routines.c.
 */
extern void USBFS_INT_IRQHandler(void);

/**
 * @brief USBCKCR bits and values (same encoding as Renesas FSP).
 */
#define USB_HW_RA_USBCKCR_USBCKSREQ (0x40U)
#define USB_HW_RA_USBCKCR_USBCKSRDY (0x80U)
#define USB_HW_RA_USBCKSEL_PLL2       (6U)    // USBCKCR.USBCKSEL - PLL2.
#define USB_HW_RA_USBCKDIV_5          (6U)    // USBCKDIVCR.USBCKDIV - divide by 5.

/**
 * @brief PLL2 settings.
 * @note PLL2CCR: PLL2MUL[13:8] = (2 * multiplier) - 1, PL2SRCSEL[4] = 1 (HOCO), PL2IDIV[1:0] = 0 (/1).
 */
#define USB_HW_RA_PLL2CCR_HOCO_X12    (0x1710U) // 20 MHz HOCO x 12 = 240 MHz.
#define USB_HW_RA_PLL2CCR_HOCO_X15    (0x1D10U) // 16 MHz HOCO x 15 = 240 MHz.
#define USB_HW_RA_HOCO_16MHZ          (0U)      // HOCOCR2.HCFRQ0 value for 16 MHz.
#define USB_HW_RA_HOCO_20MHZ          (2U)      // HOCOCR2.HCFRQ0 value for 20 MHz.
#define USB_HW_RA_HOCOCR2_HCFRQ0_MSK  (0x3U)
#define USB_HW_RA_PLL2CR_PLL2STP      (0x1U)
#define USB_HW_RA_OSCSF_PLL2SF        (0x40U)

/**
 * @brief Selects the USB clock source and divider.
 * @details Sequence from "USBCKCR : USB Clock Control Register"
 * description in the CGC chapter of the hardware manual.
 * @param source USBCKCR.USBCKSEL value.
 * @param divider USBCKDIVCR.USBCKDIV value.
 * @return None
 * @note PRCR has to be unlocked.
 */
static inline void usb_hw_select_usb_clock(uint8_t source, uint8_t divider) {
    // Request to change the USB clock and wait for the clock to be stopped.
    R_SYSTEM->USBCKCR |= USB_HW_RA_USBCKCR_USBCKSREQ;
    while (!(R_SYSTEM->USBCKCR & USB_HW_RA_USBCKCR_USBCKSRDY));

    R_SYSTEM->USBCKDIVCR = divider;

    // Select the USB clock without enabling it, then enable it.
    R_SYSTEM->USBCKCR = source | USB_HW_RA_USBCKCR_USBCKSREQ;
    R_SYSTEM->USBCKCR = source;

    // Wait for the USB clock to be started.
    while (R_SYSTEM->USBCKCR & USB_HW_RA_USBCKCR_USBCKSRDY);
}

/**
 * @brief Sets the 48 MHz USB clock.
 * @details PLL2 is set to 240 MHz from HOCO (16 or 20 MHz),
 * and UCLK = PLL2 / 5 = 48 MHz.
 * @param None
 * @return None
 */
static inline void usb_hw_clock_init(void) {
    R_SYSTEM->PRCR = USB_HW_RA_PRCR_UNLOCK;

    if ((R_SYSTEM->PLL2CR & USB_HW_RA_PLL2CR_PLL2STP)) {
        if (USB_HW_RA_HOCO_20MHZ == (R_SYSTEM->HOCOCR2 & USB_HW_RA_HOCOCR2_HCFRQ0_MSK)) {
            R_SYSTEM->PLL2CCR = USB_HW_RA_PLL2CCR_HOCO_X12;
        } else if (USB_HW_RA_HOCO_16MHZ == (R_SYSTEM->HOCOCR2 & USB_HW_RA_HOCOCR2_HCFRQ0_MSK)) {
            R_SYSTEM->PLL2CCR = USB_HW_RA_PLL2CCR_HOCO_X15;
        }
        R_SYSTEM->PLL2CR = 0U;
        // Wait for PLL2 to stabilize.
        while (!(R_SYSTEM->OSCSF & USB_HW_RA_OSCSF_PLL2SF));
    }

    usb_hw_select_usb_clock(USB_HW_RA_USBCKSEL_PLL2, USB_HW_RA_USBCKDIV_5);

    R_SYSTEM->PRCR = USB_HW_RA_PRCR_LOCK;
}

/**
 * @brief Links the USBFS interrupt to the CPU.
 * @details Renesas RA routes peripheral events to the NVIC through the ICU.
 * The vector table is copied to RAM, the USB ISR is placed in the selected
 * ICU slot and the USBFS_INT event is linked to that slot.
 * Existing vectors (e.g. the UART ones placed in flash by the HAL) are kept.
 * @param None
 * @return None
 */
static inline void usb_hw_link_interrupt(void) {
    // Cortex-M exceptions (16) + ICU slots. VTOR requires the table to be
    // aligned to the next power of two of its size.
    static uint32_t usb_hw_ram_vectors[16U + USB_HW_RA_ICU_SLOT_COUNT] __attribute__((aligned(512)));
    const uint32_t *current_vectors = (const uint32_t *)SCB->VTOR;

    if (current_vectors != usb_hw_ram_vectors) {
        for (uint32_t i = 0U; i < (16U + USB_HW_RA_ICU_SLOT_COUNT); i++) {
            usb_hw_ram_vectors[i] = current_vectors[i];
        }
    }
    usb_hw_ram_vectors[16U + USB_HW_RA_IRQ_SLOT] = (uint32_t)USBFS_INT_IRQHandler;

    #if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
    // Make sure the table is in RAM before the core fetches vectors from it.
    SCB_CleanDCache_by_Addr(usb_hw_ram_vectors, sizeof(usb_hw_ram_vectors));
    #endif

    __DSB();
    SCB->VTOR = (uint32_t)usb_hw_ram_vectors;
    __DSB();
    __ISB();

    // Link USBFS_INT event to the selected slot. NVIC is enabled by TinyUSB.
    R_ICU->IELSR[USB_HW_RA_IRQ_SLOT] = USB_HW_RA_USBFS_INT_EVENT;
}

/**
 * @brief Initializes USB.
 * @details Sets the 48 MHz USB clock (UCLK) and links the USBFS interrupt.
 * USB_DP/USB_DM are dedicated pins, so no pin setup is needed.
 * VBUS pin is not required - the device connects right after init.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    usb_hw_clock_init();
    usb_hw_link_interrupt();
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
