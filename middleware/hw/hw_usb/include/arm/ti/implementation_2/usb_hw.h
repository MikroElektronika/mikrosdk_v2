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
 * @brief USB0 interrupt request number.
 * This interrupt is triggered by USB0 controller events
 * such as data transfer completion or USB bus state changes.
 * @note The numeric value (44) is the hardware IRQ index used by the NVIC.
 */
typedef enum {
    USB0_IRQn = 44
} IRQn_Type;

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
 * @brief Base address for USB registers.
 */
#define USB0_BASE 0x40050000UL

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
 * @brief Enable analog functionality.
 * @details Enables analog functionality for provided @ref _pin.
 * The analog function of the pin is enabled, the isolation is
 * disabled, and the pin is capable of analog functions.
 * @note This register(@ref GPIO_PORTJ_AMSEL_R) and bits are only
 * valid for GPIO signals that share analog function through a unified I/O pad.
 */
#define analog_function_enable(_pin) (GPIO_PORTJ_AMSEL_R |= 1U << _pin)

/**
 * @brief Pin numbers.
 */
#define GPIO_PORTJ_PIN0 (0)
#define GPIO_PORTJ_PIN1 (1)

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock to J0 and J1 pins - DP/DM pins.
    SYSCTL_RCGC2_R |= SYSCTL_GPIOHBCTL_PORTJ;
    // Enable clock to B0 and B1 pins - USB0ID/USB0VBUS pins.
    SYSCTL_RCGC2_R |= SYSCTL_GPIOHBCTL_PORTB;
    // Make sure AHB (Advanced High-Performance Bus) is disabled
    // for previously selected pins.
    SYSCTL_GPIOHBCTL_R &= ~(SYSCTL_GPIOHBCTL_PORTJ | SYSCTL_GPIOHBCTL_PORTB);
    // The analog functions of the pins are enabled, the isolation is
    // disabled, and the pins are capable of analog functions.
    analog_function_enable(GPIO_PORTJ_PIN0);
    analog_function_enable(GPIO_PORTJ_PIN1);
    // Enable general USB clock.
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_USB0;
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
