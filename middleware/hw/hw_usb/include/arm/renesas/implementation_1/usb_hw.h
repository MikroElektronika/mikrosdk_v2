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

/* ISR prototypes */
void usbfs_interrupt_handler(void);
// void usbfs_resume_handler(void);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#pragma GCC diagnostic ignored "-Wundef"
#pragma GCC diagnostic pop

#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

void g_common_init(void);

__STATIC_INLINE IRQn_Type R_FSP_CurrentIrqGet (void)
{
    xPSR_Type xpsr_value;
    xpsr_value.w = __get_xPSR();

    return (IRQn_Type) (xpsr_value.b.ISR - 16);
}

void R_BSP_IrqStatusClear (IRQn_Type irq)
{
    /* Clear the IR bit in the selected IELSR register. */
    R_ICU->IELSR_b[irq].IR = 0U;
}

typedef void (* fsp_vector_t )( void );

/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY         (0xA500U)

__attribute__((used)) __attribute__((section(".application_vectors"))) __attribute__((__used__))
const fsp_vector_t g_vector_table[4] = {
    [0] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
    [1] = usbfs_resume_handler,    /* USBFS RESUME (USBFS resume interrupt) */
};

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
    // Enable global interrupts in CPSR register since board with bootloader such as Arduino Uno R4
    // can transfer CPU control with CPSR.I bit set to 0 (disable IRQ)
    __enable_irq();

    /* Configure pins. */
    // R_IOPORT_Open(&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
