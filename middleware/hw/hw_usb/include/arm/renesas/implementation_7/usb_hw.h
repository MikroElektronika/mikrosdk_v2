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
 * @note Used for RA2A1 MCUs (USBFS device - renesas rusb2 driver).
 * @note UCLK = HOCO (48 MHz, default setting). UCKSEL.UCKSELC is set when HOCO is the system clock.
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
#define USB_HW_RA_ICU_SLOT_COUNT    (32U)

/**
 * @brief ICU slot (IRQn) used for the USBFS interrupt.
 * @note Slot 30 is not used by MikroE HAL modules on these MCUs.
 */
#define USB_HW_RA_IRQ_SLOT          (30U)

/**
 * @brief IELSRn value of the USBFS_INT interrupt on these MCUs.
 */
#define USB_HW_RA_USBFS_INT_EVENT   (0x025UL)

/**
 * @brief USBFS on these MCUs only has pipes 0, 4, 5, 6 and 7.
 * @note Used by TinyUSB rusb2 driver - no isochronous endpoints,
 * 2 bulk and 2 interrupt pipes.
 */
#define USB_HW_RA_PIPE04567

/**
 * @brief Data pipes use the CFIFO port (no D0FIFO/D1FIFO on these MCUs),
 * same as Renesas FSP USB driver without DMA.
 * @note Used by TinyUSB rusb2 driver.
 */
#define USB_HW_RA_CFIFO_ONLY

/**
 * @brief UCKSEL register settings.
 */
#define USB_HW_RA_SCKSCR_CKSEL_MSK    (0x7U)
#define USB_HW_RA_SCKSCR_CKSEL_HOCO   (0x0U)
#define USB_HW_RA_UCKSEL_UCKSELC      (0x0001U)

/**
 * @brief Selects HOCO as USB clock when HOCO is the system clock.
 * @details Called by TinyUSB after the USB module is enabled (USBE = 1).
 * Same as Renesas FSP hw_usb_pmodule_init().
 */
#define USB_HW_PHY_INIT() do { \
    if (USB_HW_RA_SCKSCR_CKSEL_HOCO == (R_SYSTEM->SCKSCR & USB_HW_RA_SCKSCR_CKSEL_MSK)) { \
        R_USB_FS0->UCKSEL |= USB_HW_RA_UCKSEL_UCKSELC; \
    } \
} while (0)

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
 * @brief Sets the 48 MHz USB clock.
 * @details USB is clocked from 48 MHz HOCO - see USB_HW_PHY_INIT().
 * @param None
 * @return None
 */
static inline void usb_hw_clock_init(void) {
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
