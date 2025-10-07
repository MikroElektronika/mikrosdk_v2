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

/**
 * @brief Enable an interrupt for the given IRQ number.
 * @param _x IRQ number (without +16 offset).
 * @note MikroE interrupt source uses NVIC -> (IRQx + 16).
 */
#define NVIC_EnableIRQ(_x)      interrupt_enable(_x + 16)

/**
 * @brief Disable an interrupt for the given IRQ number.
 * @param _x IRQ number (without +16 offset).
 * @note MikroE interrupt source uses NVIC -> (IRQx + 16).
 */
#define NVIC_DisableIRQ(_x)     interrupt_disable(_x + 16)

/**
 * @brief Get interrupt enable state.
 * @param IRQn IRQ number.
 * @return 1 if enabled, 0 if disabled.
 * @note Wrapper for internal function __NVIC_GetEnableIRQ().
 */
#define NVIC_GetEnableIRQ       __NVIC_GetEnableIRQ

/**
 * @brief Clear the pending flag for the given interrupt.
 * @param IRQn IRQ number.
 * @note Wrapper for internal function __NVIC_ClearPendingIRQ().
 */
#define NVIC_ClearPendingIRQ    __NVIC_ClearPendingIRQ

/**
 * @brief Disable the Memory Protection Unit (MPU) if present.
 * @note Some MCUs have different register names (MPU vs SYSMPU).
 *       This macro disables the MPU by clearing the VLD (valid) bit in CESR,
 *       effectively disabling memory protection.
 *       If no MPU is present, this macro does nothing.
 */
#ifdef MPU_CESR_VLD_MASK
    #define disable_MPU()       ( MPU->CESR &= ~MPU_CESR_VLD_MASK )
#elif SYSMPU_CESR_VLD_MASK
    #define disable_MPU()       ( SYSMPU->CESR &= ~SYSMPU_CESR_VLD_MASK )
#else
     #define disable_MPU()
#endif

/**
 * @brief NVIC register map structure.
 * This structure represents the memory-mapped NVIC
 * (Nested Vectored Interrupt Controller) registers inside the Cortex-M core.
 * Registers:
 * - ISER: Interrupt Set-Enable Registers (enable specific IRQs)
 * - ICER: Interrupt Clear-Enable Registers (disable specific IRQs)
 * - ISPR: Interrupt Set-Pending Registers (force pending state)
 * - ICPR: Interrupt Clear-Pending Registers (clear pending state)
 */
typedef struct
{
    uint32_t ISER[8U];
    uint32_t RESERVED0[24U];
    uint32_t ICER[8U];
    uint32_t RESERVED1[24U];
    uint32_t ISPR[8U];
    uint32_t RESERVED2[24U];
    uint32_t ICPR[8U];
} NVIC_Type;

/**
 * @brief Pointer to NVIC configuration registers.
 */
#define NVIC ( ( NVIC_Type *) 0xE000E100UL )

/**
 * @brief System core clock frequency in Hz.
 * @note This variable is updated whenever the system clock changes
 *       and is used for timing-related calculations
 *       (e.g., delays or SysTick configuration).
 */
extern volatile uint32_t SystemCoreClock;


/**
 * @brief Get the enable state of a specific interrupt.
 * Checks if the interrupt is currently enabled in the NVIC.
 * @param IRQn Interrupt number.
 * @return 1 if the interrupt is enabled, 0 otherwise.
 * @note
 * - If IRQn >= 0: Reads the appropriate ISER bitfield to see if set.
 * - If IRQn < 0: Returns 0 (system exceptions are not handled here).
 */
static inline uint32_t __NVIC_GetEnableIRQ( IRQn_Type IRQn ) {
    if ( ( int32_t )( IRQn ) >= 0 )
    {
        return ( ( uint32_t )( ( ( NVIC->ISER[ ( ( ( uint32_t )IRQn ) >> 5UL ) ] & \
                ( 1UL << ( ( ( uint32_t )IRQn ) & 0x1FUL ) ) ) != 0UL ) ? 1UL : 0UL ) );
    }
    else
    {
        return ( 0U );
    }
}

/**
 * @brief Clear the pending flag for a specific interrupt.
 * Clears the pending state of an interrupt to prevent unwanted re-triggering.
 * @param IRQn Interrupt number.
 * @note
 * - If IRQn >= 0: Writes to the correct ICPR bitfield to clear the pending state.
 * - If IRQn < 0: Does nothing (system exceptions are not handled here).
 */
static inline void __NVIC_ClearPendingIRQ( IRQn_Type IRQn ) {
    if ( ( int32_t )( IRQn ) >= 0 )
    {
        NVIC->ICPR[ ( ( ( uint32_t )IRQn ) >> 5UL ) ] = \
            ( uint32_t )( 1UL << ( ( ( uint32_t )IRQn ) & 0x1FUL ) );
    }
}

static inline void usb_hw_init( void ) {
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
