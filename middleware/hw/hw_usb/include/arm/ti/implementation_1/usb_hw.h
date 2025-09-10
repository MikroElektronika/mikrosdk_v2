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
#include <stdint.h>

typedef enum {
  USB0_IRQn = 42
} IRQn_Type;

// Note: Added for MikroE implementation.
// MikroE interrupt source uses NVIC -> (IRQx + 16).
#define NVIC_EnableIRQ(_x)      interrupt_enable(_x + 16)
#define NVIC_DisableIRQ(_x)     interrupt_disable(_x + 16)
#define NVIC_GetEnableIRQ       __NVIC_GetEnableIRQ
#define NVIC_ClearPendingIRQ    __NVIC_ClearPendingIRQ

typedef struct
{
    uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32_t RESERVED0[24U];
    uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32_t RESERVED1[24U];
    uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32_t RESERVED2[24U];
    uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
}  NVIC_Type;

#define NVIC ((NVIC_Type *) 0xE000E100UL )   /*!< NVIC configuration struct */

extern volatile uint32_t SystemCoreClock;

static inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}

static inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
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
 * @note This register(@ref GPIO_PORTx_AMSEL_R) and bits are only
 * valid for GPIO signals that share analog function through a unified I/O pad.
 */
#define analog_function_enable(_reg,_pin) (_reg |= 1U << _pin)

/**
 * @brief Enable alternate functionality.
 * @details Enables alternate functionality for provided @ref _pin.
 * The associated pin functions as a peripheral signal and is
 * controlled by the alternate hardware function.
 */
#define alternate_function_enable(_pin) (GPIO_PORTB_AHB_AFSEL_R |= 1U << _pin)

#define USB0_BASE 0x40050000UL

/**
 * @brief Pin numbers.
 */
#define GPIO_PORTB_PIN0 (0)
#define GPIO_PORTB_PIN1 (1)
#define GPIO_PORTL_PIN6 (6)
#define GPIO_PORTL_PIN7 (7)
#define USB_DP_PIN GPIO_PORTL_PIN6
#define USB_DN_PIN GPIO_PORTL_PIN7
#define USB_ID_PIN GPIO_PORTB_PIN0
#define USB_VBUS_PIN GPIO_PORTB_PIN1

extern volatile uint32_t SystemCoreClock;

/**
 * @brief MOSC value.
 * @details Set main oscillator value here.
 * @note Assumed mainosc is 25MHz.
 * @warning When the USB module uses the integrated USB PHY,
 * the MOSC must be the clock source, either with or without using the PLL,
 * and the system clock must be at least 30 MHz. In addition,
 * only integer divisors should be used to achieve the 60 MHz USB clock source.
 * Fractional divisors may increase jitter and compromise USB function.
 */
static const unsigned long assumed_mosc_value = 25;

static unsigned long get_vco_in_mhz(void){
    unsigned long result = 480;
    const unsigned long sysctl_rsclkcfg_pllsrc24_mask = (0xFUL << 24),
                        mfrac = (SYSCTL_PLLFREQ0_R >> 10) & 0x3FF,
                        mint = SYSCTL_PLLFREQ0_R & 0x3FF,
                        q = (SYSCTL_PLLFREQ1_R >> 8) & 0x1F,
                        n = SYSCTL_PLLFREQ1_R & 0x1F;

    if ( SYSCTL_RSCLKCFG_R & SYSCTL_RSCLKCFG_USEPLL ){
        if ( ( SYSCTL_RSCLKCFG_R & sysctl_rsclkcfg_pllsrc24_mask ) == 0 ) {
            result = ( 16 * ( mint + ( mfrac / 1024 ) ) ) / ( ( q + 1 ) * ( n + 1 ) );
        } else if ( ( SYSCTL_RSCLKCFG_R & sysctl_rsclkcfg_pllsrc24_mask ) == ( 3UL << 24 ) ) {
            /**
             * @note Assumed mainosc is 25MHz, in order to work for MikroE HW.
             * Change the value of @ref assumed_mosc_value to suite your HW if needed.
             */
            result = ( assumed_mosc_value * ( mint + ( mfrac / 1024 ) ) ) / ( ( q + 1 ) * ( n + 1 ) );
        }
    }

    return result;
}

static void usb_set_cc(void){
    unsigned long reg = USB0_CC_R,
                  clkdiv = (get_vco_in_mhz() / 60 - 1);

    reg &= ~(0xFUL | USB_CC_CSD);
    reg |= (clkdiv & 0xF) | USB_CC_CLKEN;

    USB0_CC_R = reg;
}

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @return None
 */
static inline void usb_hw_init(void) {
    // Enable clock to USB0ID/USB0VBUS pins.
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    // Enable clock to DP/DM pins.
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;
    // Set pins as analog.
    // The analog functions of the pins are enabled, the isolation is
    // disabled, and the pins are capable of analog functions.
    analog_function_enable(GPIO_PORTB_AHB_AMSEL_R,GPIO_PORTB_PIN0);
    analog_function_enable(GPIO_PORTB_AHB_AMSEL_R,GPIO_PORTB_PIN1);
    // Set pins alternate function.
    // The associated pin functions as a peripheral signal and is
    // controlled by the alternate hardware function.
    alternate_function_enable(GPIO_PORTB_PIN0);
    alternate_function_enable(GPIO_PORTB_PIN1);
    // Set pins as analog.
    // The analog functions of the pins are enabled, the isolation is
    // disabled, and the pins are capable of analog functions.
    analog_function_enable(GPIO_PORTL_AMSEL_R,USB_DN_PIN);
    analog_function_enable(GPIO_PORTL_AMSEL_R,USB_DP_PIN);
    // Enable general USB clock.
    SYSCTL_RCGCUSB_R |= SYSCTL_RCGCUSB_R0;
    // Calculate and set apprpriate USB clock values.
    usb_set_cc();
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
