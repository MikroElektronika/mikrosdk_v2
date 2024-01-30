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
#include "interrupts.h"
// Note: Added for MikroE implementation.
// MikroE interrupt source uses NVIC -> (IRQx + 16).
#define NVIC_EnableIRQ(_x)  interrupt_enable(_x + 16)
#define NVIC_DisableIRQ(_x) interrupt_disable(_x + 16)
#ifdef MPU_CESR_VLD_MASK
    #define disable_MPU()       ( MPU->CESR &= ~MPU_CESR_VLD_MASK )
#elif SYSMPU_CESR_VLD_MASK
    #define disable_MPU()       ( SYSMPU->CESR &= ~SYSMPU_CESR_VLD_MASK )
#else
     #define disable_MPU()
#endif

static inline void usb_hw_init(void) {
    // Disable MPU.
    disable_MPU();
    // Enable global interrupts
    interrupts_enable();
    /**
    * @brief USB needs 48 MHz clock to function. Use NECTO's setups to configure clock or do it manualy here.
    * @note
    * If you set USB_CLKIN as clock source it is necessary to set alternate function for that pin, usually PTA5 or PTE26.
    * @b Example code for MK64FN1MOVDC12
    * @code
    *   #define PORTE_PCR_AF7 0x00000700
    *   // Port E Clock enable.
    *   SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    *   // PTE26 (H6) USB_CLKIN alternate function enable.
    *   PORTE->PCR[26] |= PORTE_PCR_AF7;
    * @endcode
    */
    // Enable USB Clock gate control.
    SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
