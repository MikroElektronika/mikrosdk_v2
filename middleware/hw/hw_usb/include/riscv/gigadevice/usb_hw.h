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
#include <stdbool.h>
#include "interrupts.h"

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

// TODO - VBUS pin sense disables or not.
// Define it here.
#define VBUS_SENSE_OFF false

#define pointer_byte(_reg) (*(volatile uint8_t *)(uint32_t)(_reg))
#define pointer_word(_reg) (*(volatile uint16_t *)(uint32_t)(_reg))
#define pointer_dword(_reg) (*(volatile uint32_t *)(uint32_t)(_reg))

#define HXTAL_STARTUP_TIMEOUT ((uint16_t)0xFFFF)

#define BITS(start, end) ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))

// AHB prescaler selection.
#define CFG0_AHBPSC(regval) (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_AHB_CKSYS_DIV1 CFG0_AHBPSC(0)
#define RCU_AHB_CKSYS_DIV2 CFG0_AHBPSC(8)
#define RCU_AHB_CKSYS_DIV4 CFG0_AHBPSC(9)
#define RCU_AHB_CKSYS_DIV8 CFG0_AHBPSC(10)
#define RCU_AHB_CKSYS_DIV16 CFG0_AHBPSC(11)
#define RCU_AHB_CKSYS_DIV64 CFG0_AHBPSC(12)
#define RCU_AHB_CKSYS_DIV128 CFG0_AHBPSC(13)
#define RCU_AHB_CKSYS_DIV256 CFG0_AHBPSC(14)
#define RCU_AHB_CKSYS_DIV512 CFG0_AHBPSC(15)

// APB1 prescaler selection.
#define CFG0_APB1PSC(regval) (BITS(8,10) & ((uint32_t)(regval) << 8))
#define RCU_APB1_CKAHB_DIV1 CFG0_APB1PSC(0)
#define RCU_APB1_CKAHB_DIV2 CFG0_APB1PSC(4)
#define RCU_APB1_CKAHB_DIV4 CFG0_APB1PSC(5)
#define RCU_APB1_CKAHB_DIV8 CFG0_APB1PSC(6)
#define RCU_APB1_CKAHB_DIV16 CFG0_APB1PSC(7)

// APB2 prescaler selection.
#define CFG0_APB2PSC(regval) (BITS(11,13) & ((uint32_t)(regval) << 11))
#define RCU_APB2_CKAHB_DIV1 CFG0_APB2PSC(0)
#define RCU_APB2_CKAHB_DIV2 CFG0_APB2PSC(4)
#define RCU_APB2_CKAHB_DIV4 CFG0_APB2PSC(5)
#define RCU_APB2_CKAHB_DIV8 CFG0_APB2PSC(6)
#define RCU_APB2_CKAHB_DIV16 CFG0_APB2PSC(7)

// RCU_CFG0 register bit define system clock source select.
#define CFG0_SCS(regval) (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_CKSYSSRC_IRC8M CFG0_SCS(0)
#define RCU_CKSYSSRC_HXTAL CFG0_SCS(1)
#define RCU_CKSYSSRC_PLL CFG0_SCS(2)

// System clock source select status.
#define CFG0_SCSS(regval) (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_SCSS_IRC8M CFG0_SCSS(0)
#define RCU_SCSS_HXTAL CFG0_SCSS(1)
#define RCU_SCSS_PLL CFG0_SCSS(2)

// PLL clock source selection.
#define RCU_PLLSRC_IRC8M_DIV2 ((uint32_t)0x00000000U)
#define RCU_PLLSRC_HXTAL RCU_CFG0_PLLSEL

// PLL clock multiplication factor.
#define PLLMF_4 RCU_CFG0_PLLMF_4

#define CFG0_PLLMF(regval) (BITS(18,21) & ((uint32_t)(regval) << 18))
#define RCU_PLL_MUL2 CFG0_PLLMF(0)
#define RCU_PLL_MUL3 CFG0_PLLMF(1)
#define RCU_PLL_MUL4 CFG0_PLLMF(2)
#define RCU_PLL_MUL5 CFG0_PLLMF(3)
#define RCU_PLL_MUL6 CFG0_PLLMF(4)
#define RCU_PLL_MUL7 CFG0_PLLMF(5)
#define RCU_PLL_MUL8 CFG0_PLLMF(6)
#define RCU_PLL_MUL9 CFG0_PLLMF(7)
#define RCU_PLL_MUL10 CFG0_PLLMF(8)
#define RCU_PLL_MUL11 CFG0_PLLMF(9)
#define RCU_PLL_MUL12 CFG0_PLLMF(10)
#define RCU_PLL_MUL13 CFG0_PLLMF(11)
#define RCU_PLL_MUL14 CFG0_PLLMF(12)
#define RCU_PLL_MUL6_5 CFG0_PLLMF(13)
#define RCU_PLL_MUL16 CFG0_PLLMF(14)
#define RCU_PLL_MUL17 (PLLMF_4 | CFG0_PLLMF(0))
#define RCU_PLL_MUL18 (PLLMF_4 | CFG0_PLLMF(1))
#define RCU_PLL_MUL19 (PLLMF_4 | CFG0_PLLMF(2))
#define RCU_PLL_MUL20 (PLLMF_4 | CFG0_PLLMF(3))
#define RCU_PLL_MUL21 (PLLMF_4 | CFG0_PLLMF(4))
#define RCU_PLL_MUL22 (PLLMF_4 | CFG0_PLLMF(5))
#define RCU_PLL_MUL23 (PLLMF_4 | CFG0_PLLMF(6))
#define RCU_PLL_MUL24 (PLLMF_4 | CFG0_PLLMF(7))
#define RCU_PLL_MUL25 (PLLMF_4 | CFG0_PLLMF(8))
#define RCU_PLL_MUL26 (PLLMF_4 | CFG0_PLLMF(9))
#define RCU_PLL_MUL27 (PLLMF_4 | CFG0_PLLMF(10))
#define RCU_PLL_MUL28 (PLLMF_4 | CFG0_PLLMF(11))
#define RCU_PLL_MUL29 (PLLMF_4 | CFG0_PLLMF(12))
#define RCU_PLL_MUL30 (PLLMF_4 | CFG0_PLLMF(13))
#define RCU_PLL_MUL31 (PLLMF_4 | CFG0_PLLMF(14))
#define RCU_PLL_MUL32 (PLLMF_4 | CFG0_PLLMF(15))

// PREDV0 input clock source selection.
#define RCU_PREDV0SRC_HXTAL ((uint32_t)0x00000000U)
#define RCU_PREDV0SRC_CKPLL1 RCU_CFG1_PREDV0SEL

// PLL1 clock multiplication factor.
#define CFG1_PLL1MF(regval) (BITS(8,11) & ((uint32_t)(regval) << 8))
#define RCU_PLL1_MUL8 CFG1_PLL1MF(6)
#define RCU_PLL1_MUL9 CFG1_PLL1MF(7)
#define RCU_PLL1_MUL10 CFG1_PLL1MF(8)
#define RCU_PLL1_MUL11 CFG1_PLL1MF(9)
#define RCU_PLL1_MUL12 CFG1_PLL1MF(10)
#define RCU_PLL1_MUL13 CFG1_PLL1MF(11)
#define RCU_PLL1_MUL14 CFG1_PLL1MF(12)
#define RCU_PLL1_MUL15 CFG1_PLL1MF(13)
#define RCU_PLL1_MUL16 CFG1_PLL1MF(14)
#define RCU_PLL1_MUL20 CFG1_PLL1MF(15)

// PREDV0 division factor.
#define CFG1_PREDV0(regval) (BITS(0,3) & ((uint32_t)(regval) << 0))
#define RCU_PREDV0_DIV1 CFG1_PREDV0(0)
#define RCU_PREDV0_DIV2 CFG1_PREDV0(1)
#define RCU_PREDV0_DIV3 CFG1_PREDV0(2)
#define RCU_PREDV0_DIV4 CFG1_PREDV0(3)
#define RCU_PREDV0_DIV5 CFG1_PREDV0(4)
#define RCU_PREDV0_DIV6 CFG1_PREDV0(5)
#define RCU_PREDV0_DIV7 CFG1_PREDV0(6)
#define RCU_PREDV0_DIV8 CFG1_PREDV0(7)
#define RCU_PREDV0_DIV9 CFG1_PREDV0(8)
#define RCU_PREDV0_DIV10 CFG1_PREDV0(9)
#define RCU_PREDV0_DIV11 CFG1_PREDV0(10)
#define RCU_PREDV0_DIV12 CFG1_PREDV0(11)
#define RCU_PREDV0_DIV13 CFG1_PREDV0(12)
#define RCU_PREDV0_DIV14 CFG1_PREDV0(13)
#define RCU_PREDV0_DIV15 CFG1_PREDV0(14)
#define RCU_PREDV0_DIV16 CFG1_PREDV0(15)

// PREDV1 division factor.
#define CFG1_PREDV1(regval) (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_PREDV1_DIV1 CFG1_PREDV1(0)
#define RCU_PREDV1_DIV2 CFG1_PREDV1(1)
#define RCU_PREDV1_DIV3 CFG1_PREDV1(2)
#define RCU_PREDV1_DIV4 CFG1_PREDV1(3)
#define RCU_PREDV1_DIV5 CFG1_PREDV1(4)
#define RCU_PREDV1_DIV6 CFG1_PREDV1(5)
#define RCU_PREDV1_DIV7 CFG1_PREDV1(6)
#define RCU_PREDV1_DIV8 CFG1_PREDV1(7)
#define RCU_PREDV1_DIV9 CFG1_PREDV1(8)
#define RCU_PREDV1_DIV10 CFG1_PREDV1(9)
#define RCU_PREDV1_DIV11 CFG1_PREDV1(10)
#define RCU_PREDV1_DIV12 CFG1_PREDV1(11)
#define RCU_PREDV1_DIV13 CFG1_PREDV1(12)
#define RCU_PREDV1_DIV14 CFG1_PREDV1(13)
#define RCU_PREDV1_DIV15 CFG1_PREDV1(14)
#define RCU_PREDV1_DIV16 CFG1_PREDV1(15)

// RCU_CFG0 bits.
#define _RCU_CFG0_PLLMF BITS(18,21)
#define _RCU_CFG1_PLL1MF BITS(8,11)
#define _RCU_CFG1_PREDV0 BITS(0,3)
#define _RCU_CFG1_PREDV1 BITS(4,7)
#define _RCU_CFG0_SCS BITS(0,1)

static inline void system_rcu_clock_reset( void ) {
    pointer_dword(RCU_BASE+RCU_CTL) |= RCU_CTL_IRC8MEN;

    // Wait for IRC8M to stabilize.
    while( !(pointer_dword(RCU_BASE+RCU_CTL) & RCU_CTL_IRC8MSTB ) );

    /**
     * Reset SCS, AHBPSC, APB1PSC, ADCPSC, CKOUT0SEL bits,
     * PLLSEL, PREDV0_LSB, PLLMF, USBFSPSC bits.
     * @note Effectively selecting IRC8M as clock source.
     */
    pointer_dword(RCU_BASE+RCU_CFG0) &= ~(RCU_CFG0_SCS_Msk | RCU_CFG0_AHBPSC_Msk |
                                          RCU_CFG0_APB1PSC_Msk | RCU_CFG0_APB2PSC_Msk |
                                          RCU_CFG0_ADCPSC_Msk | RCU_CFG0_CKOUT0SEL_Msk |
                                          RCU_CFG0_PLLSEL | RCU_CFG0_PREDV0_LSB |
                                          RCU_CFG0_PLLMF_Msk | RCU_CFG0_USBFSPSC_Msk);

    // Reset HXTALEN, CKMEN, PLLEN bits.
    pointer_dword(RCU_BASE+RCU_CTL) &= ~(RCU_CTL_HXTALEN |
                                         RCU_CTL_CKMEN |
                                         RCU_CTL_PLLEN);

    /**
     * Reset HXTALBPS bit.
     * @note HXTAL @b MUST be disabled first.
     */
    while( ( pointer_dword(RCU_BASE+RCU_CTL) & RCU_CTL_HXTALEN ) );
    pointer_dword(RCU_BASE+RCU_CTL) &= ~(RCU_CTL_HXTALBPS);

    // Reset PLLSEL, PREDV0_LSB, PLLMF, USBFSPSC bits.
    pointer_dword(RCU_BASE+RCU_CFG0) &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PREDV0_LSB |
                                          RCU_CFG0_PLLMF_Msk | RCU_CFG0_USBFSPSC_Msk);

    /**
     * Reset PREDV0, PREDV1, PLL1MF, PLL2MF,
     * PREDV0_SEL, I2S1SEL and I2S2SEL bits.
     */
    pointer_dword(RCU_BASE+RCU_CFG1) &= ~(0x7FFFFul);

    // Reset HXTALEN, CKMEN, PLLEN, PLL1EN and PLL2EN bits.
    pointer_dword(RCU_BASE+RCU_CTL) &= ~(RCU_CTL_PLLEN | RCU_CTL_PLL1EN |
                                         RCU_CTL_PLL2EN | RCU_CTL_CKMEN |
                                         RCU_CTL_HXTALEN);

    /**
     * Disable all interrupts and clear flags.
     * @note This register is the same for all GD32VF103 chips.
     */
    pointer_dword(RCU_BASE+RCU_INT) |= 0x00FF0000ul;
}

static uint8_t clock_48m_hxtal(bool hse_25) {
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;

    (void)system_rcu_clock_reset();

    // Enable HXTAL.
    *(uint32_t volatile *)(RCU_BASE+RCU_CTL) |= RCU_CTL_HXTALEN;

    // @ait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT.
    do{
        timeout++;
        stab_flag = (*(uint32_t volatile *)(RCU_BASE+RCU_CTL) & RCU_CTL_HXTALSTB);
    }while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    // If it fails.
    if(0U == (*(uint32_t volatile *)(RCU_BASE+RCU_CTL) & RCU_CTL_HXTALSTB)){
        return 1;
    }

    // Continue if HXTAL is stable.

    // AHB = SYSCLK.
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) |= RCU_AHB_CKSYS_DIV1;
    // APB2 = AHB/1.
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) |= RCU_APB2_CKAHB_DIV1;
    // APB1 = AHB/2.
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) |= RCU_APB1_CKAHB_DIV2;

    // CK_PLL = (CK_PREDIV0) * 12 = 48 MHz.
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) &= ~(_RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_4);
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL12);

    // HSE 25MHz
    if(hse_25){
        // CK_PREDIV0 = (CK_HXTAL)/5 *8 /10 = 4 MHz.
        *(uint32_t volatile *)(RCU_BASE+RCU_CFG1) &= ~(RCU_CFG1_PREDV0SEL | _RCU_CFG1_PLL1MF | _RCU_CFG1_PREDV1 | _RCU_CFG1_PREDV0);
        *(uint32_t volatile *)(RCU_BASE+RCU_CFG1) |= (RCU_PREDV0SRC_CKPLL1 | RCU_PLL1_MUL8 | RCU_PREDV1_DIV5 | RCU_PREDV0_DIV10);

        // Enable PLL1.
        *(uint32_t volatile *)(RCU_BASE+RCU_CTL) |= RCU_CTL_PLL1EN;
        // Wait till PLL1 is ready.
        while((*(uint32_t volatile *)(RCU_BASE+RCU_CTL) & RCU_CTL_PLL1STB) == 0){
        }
    // HSE 8MHz
    } else {
        *(uint32_t volatile *)(RCU_BASE+RCU_CFG1) &= ~(RCU_CFG1_PREDV0SEL | _RCU_CFG1_PREDV1 | _RCU_CFG1_PLL1MF | _RCU_CFG1_PREDV0);
        *(uint32_t volatile *)(RCU_BASE+RCU_CFG1) |= (RCU_PREDV0SRC_HXTAL | RCU_PREDV0_DIV2 );
    }

    // Enable PLL.
    *(uint32_t volatile *)(RCU_BASE+RCU_CTL) |= RCU_CTL_PLLEN;

    // Wait until PLL is stable.
    while(0U == (*(uint32_t volatile *)(RCU_BASE+RCU_CTL) & RCU_CTL_PLLSTB)){
    }

    // Select PLL as system clock.
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) &= ~_RCU_CFG0_SCS;
    *(uint32_t volatile *)(RCU_BASE+RCU_CFG0) |= RCU_CKSYSSRC_PLL;

    // Wait until PLL is selected as system clock.
    while(0U == (*(uint32_t volatile *)(RCU_BASE+RCU_CFG0) & RCU_SCSS_PLL)){
    }

    return 0;
}

// GPIO mode values set.
#define GPIO_MODE_SET(n,mode) ((uint32_t)((uint32_t)(mode) << (4U * (n))))
#define GPIO_MODE_MASK(n) (0xFU << (4U * (n)))

// GPIO mode definitions.
#define GPIO_MODE_AIN ((uint8_t)0x00U)
#define GPIO_MODE_IN_FLOATING ((uint8_t)0x04U)
#define GPIO_MODE_IPD ((uint8_t)0x28U)
#define GPIO_MODE_IPU ((uint8_t)0x48U)
#define GPIO_MODE_OUT_OD ((uint8_t)0x14U)
#define GPIO_MODE_OUT_PP ((uint8_t)0x10U)
#define GPIO_MODE_AF_OD ((uint8_t)0x1CU)
#define GPIO_MODE_AF_PP ((uint8_t)0x18U)

// GPIO output max speed value.
#define GPIO_OSPEED_10MHZ ((uint8_t)0x01U)
#define GPIO_OSPEED_2MHZ ((uint8_t)0x02U)
#define GPIO_OSPEED_50MHZ ((uint8_t)0x03U)

// GPIO pin definitions.
#define GPIO_PIN_0 BIT(0)
#define GPIO_PIN_1 BIT(1)
#define GPIO_PIN_2 BIT(2)
#define GPIO_PIN_3 BIT(3)
#define GPIO_PIN_4 BIT(4)
#define GPIO_PIN_5 BIT(5)
#define GPIO_PIN_6 BIT(6)
#define GPIO_PIN_7 BIT(7)
#define GPIO_PIN_8 BIT(8)
#define GPIO_PIN_9 BIT(9)
#define GPIO_PIN_10 BIT(10)
#define GPIO_PIN_11 BIT(11)
#define GPIO_PIN_12 BIT(12)
#define GPIO_PIN_13 BIT(13)
#define GPIO_PIN_14 BIT(14)
#define GPIO_PIN_15 BIT(15)
#define GPIO_PIN_ALL BITS(0, 15)

#define BIT(x) ((uint32_t)((uint32_t)0x01U<<(x)))

static void gpio_init_ctlx(
                            uint32_t gpio_periph, uint32_t mode[2],
                            uint32_t speed, uint32_t pin
                          )
{
    uint32_t offset, reg = 0U;

    offset = GPIO_CTL0;
    if (pin > GPIO_PIN_7)
        offset = GPIO_CTL1;

    for (uint8_t i = 0U; i < 8U; i++) {
        if ((1U << i) & pin) {
            reg = *(uint32_t volatile *)(gpio_periph+offset);

            // Clear the specified pin mode bits.
            reg &= ~GPIO_MODE_MASK(i);
            // Set the specified pin mode bits.
            reg |= GPIO_MODE_SET(i, mode[1]);

            // Set IPD or IPU.
            if (GPIO_MODE_IPD == mode[0]) {
                // Reset the corresponding OCTL bit.
                *(uint32_t volatile *)(gpio_periph+GPIO_BC) = (uint32_t) ((1U << i) & pin);
            } else {
                // Set the corresponding OCTL bit.
                if (GPIO_MODE_IPU == mode[0]) {
                    *(uint32_t volatile *)(gpio_periph+GPIO_BOP) = (uint32_t) ((1U << i) & pin);
                }
            }
            // Set GPIO_CTLx register.
            *(uint32_t volatile *)(gpio_periph+offset) = reg;
        }
    }
}

static void gpio_init(
                        uint32_t gpio_periph, uint32_t mode,
                        uint32_t speed, uint32_t pin
                     )
{
    uint16_t i;
    uint32_t temp_mode[2] = {mode, 0U};
    uint32_t reg = 0U;

    // GPIO mode configuration.
    temp_mode[1] = (uint32_t) (mode & ((uint32_t) 0x0FU));

    // GPIO speed configuration.
    if (((uint32_t) 0x00U) != ((uint32_t) mode & ((uint32_t) 0x10U))) {
        // Output mode max speed:10MHz,2MHz,50MHz.
        temp_mode[1] |= (uint32_t) speed;
    }

    // Configure the port pin.
    gpio_init_ctlx(gpio_periph, temp_mode, speed, pin);
}

#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

// Define clock source.
#define SEL_IRC8M ((uint16_t)0U)
#define SEL_HXTAL ((uint16_t)1U)
#define SEL_PLL ((uint16_t)2U)

// USBFS prescaler select.
#define CFG0_USBPSC(regval) (BITS(22,23) & ((uint32_t)(regval) << 22))
#define RCU_CKUSB_CKPLL_DIV1_5 CFG0_USBPSC(0)
#define RCU_CKUSB_CKPLL_DIV1 CFG0_USBPSC(1)
#define RCU_CKUSB_CKPLL_DIV2_5 CFG0_USBPSC(2)
#define RCU_CKUSB_CKPLL_DIV2 CFG0_USBPSC(3)
#define _RCU_CFG0_USBFSPSC BITS(22,23)

#define IRC8M_VALUE ((uint32_t)8000000)
#define MIKROE_HW_HXTAL ((uint32_t)25000000)

// Define value of high speed crystal oscillator (HXTAL) in Hz.
#if !defined  HXTAL_VALUE
    #ifdef MCU_CARD_FOR_RISC_V
        #define HXTAL_VALUE MIKROE_HW_HXTAL
    #else
        #define HXTAL_VALUE IRC8M_VALUE
    #endif
#endif

// Rcu clock frequency.
typedef enum {
    CK_SYS = 0,
    CK_AHB,
    CK_APB1,
    CK_APB2,
} rcu_clock_freq_enum;

/**
 * @brief      get the system clock, bus and peripheral clock frequency
 * @param[in]  clock: the clock frequency which to get
 *             only one parameter can be selected which is shown as below:
 * @arg        CK_SYS: system clock frequency
 * @arg        CK_AHB: AHB clock frequency
 * @arg        CK_APB1: APB1 clock frequency
 * @arg        CK_APB2: APB2 clock frequency
 * @param[out] none
 * @return     clock frequency of system, AHB, APB1, APB2
 */
static uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq;
    uint32_t pllsel, predv0sel, pllmf,ck_src, idx, clk_exp;
    uint32_t predv0, predv1, pll1mf;

    // Exponent of AHB, APB1 and APB2 clock divider.
    uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    sws = GET_BITS(pointer_dword(RCU_BASE+RCU_CFG0), 2, 3);
    switch(sws){
    // IRC8M is selected as CK_SYS.
    case SEL_IRC8M:
        cksys_freq = IRC8M_VALUE;
        break;
    // HXTAL is selected as CK_SYS.
    case SEL_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;
    // PLL is selected as CK_SYS.
    case SEL_PLL:
        // PLL clock source selection, HXTAL or IRC8M/2.
        pllsel = (pointer_dword(RCU_BASE+RCU_CFG0) & RCU_CFG0_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            // PLL clock source is HXTAL.
            ck_src = HXTAL_VALUE;

            predv0sel = (pointer_dword(RCU_BASE+RCU_CFG1) & RCU_CFG1_PREDV0SEL);
            // Source clock use PLL1.
            if(RCU_PREDV0SRC_CKPLL1 == predv0sel){
                predv1 = (uint32_t)((pointer_dword(RCU_BASE+RCU_CFG1) & _RCU_CFG1_PREDV1) >> 4) + 1U;
                pll1mf = (uint32_t)((pointer_dword(RCU_BASE+RCU_CFG1) & _RCU_CFG1_PLL1MF) >> 8) + 2U;
                if(17U == pll1mf){
                    pll1mf = 20U;
                }
                ck_src = (ck_src / predv1) * pll1mf;
            }
            predv0 = (pointer_dword(RCU_BASE+RCU_CFG1) & _RCU_CFG1_PREDV0) + 1U;
            ck_src /= predv0;
        }else{
            // PLL clock source is IRC8M/2.
            ck_src = IRC8M_VALUE/2U;
        }

        // PLL multiplication factor.
        pllmf = GET_BITS(pointer_dword(RCU_BASE+RCU_CFG0), 18, 21);
        if((pointer_dword(RCU_BASE+RCU_CFG0) & RCU_CFG0_PLLMF_4)){
            pllmf |= 0x10U;
        }
        if(pllmf < 15U){
            pllmf += 2U;
        }else{
            pllmf += 1U;
        }

        cksys_freq = ck_src * pllmf;

        if(15U == pllmf){
            // PLL source clock multiply by 6.5.
            cksys_freq = ck_src * 6U + ck_src / 2U;
        }

        break;

    // IRC8M is selected as CK_SYS.
    default:
        cksys_freq = IRC8M_VALUE;
        break;
    }

    // Calculate AHB clock frequency.
    idx = GET_BITS(pointer_dword(RCU_BASE+RCU_CFG0), 4, 7);
    clk_exp = ahb_exp[idx];
    ahb_freq = cksys_freq >> clk_exp;

    // Calculate APB1 clock frequency.
    idx = GET_BITS(pointer_dword(RCU_BASE+RCU_CFG0), 8, 10);
    clk_exp = apb1_exp[idx];
    apb1_freq = ahb_freq >> clk_exp;

    // Calculate APB2 clock frequency.
    idx = GET_BITS(pointer_dword(RCU_BASE+RCU_CFG0), 11, 13);
    clk_exp = apb2_exp[idx];
    apb2_freq = ahb_freq >> clk_exp;

    // Return the clock frequency.
    switch(clock){
        case CK_SYS:
            ck_freq = cksys_freq;
            break;
        case CK_AHB:
            ck_freq = ahb_freq;
            break;
        case CK_APB1:
            ck_freq = apb1_freq;
            break;
        case CK_APB2:
            ck_freq = apb2_freq;
            break;

        default:
            break;
    }

    return ck_freq;
}

static inline void rcu_usb_clock_config(uint32_t usb_psc)
{
    uint32_t reg;

    reg = pointer_dword(RCU_BASE+RCU_CFG0);

    // Configure the USBFS prescaler factor.
    reg &= ~_RCU_CFG0_USBFSPSC;
    pointer_dword(RCU_BASE+RCU_CFG0) = (reg | usb_psc);
}

static inline void usb_rcu_config(bool config_clock) {
    if (config_clock)
        // Initialize with external OSCILATTOR?
        (void)clock_48m_hxtal(HXTAL_VALUE == MIKROE_HW_HXTAL);

    static volatile uint32_t usbfs_prescaler = 0;
    volatile uint32_t system_clock = rcu_clock_freq_get(CK_SYS);

    if (system_clock == 48000000) {
        usbfs_prescaler = RCU_CKUSB_CKPLL_DIV1;
    } else if (system_clock == 72000000) {
        usbfs_prescaler = RCU_CKUSB_CKPLL_DIV1_5;
    } else if (system_clock == 96000000) {
        usbfs_prescaler = RCU_CKUSB_CKPLL_DIV2;
    } else {
        //  Reserved  //
        return;
    }

    rcu_usb_clock_config(usbfs_prescaler);
    pointer_dword(RCU_BASE+RCU_AHBEN) |= RCU_AHBEN_USBFSEN;
}

/**
 * @brief Initializes USB.
 * @details Sets appropriate clock settings.
 * Sets appropriate pins if necessary.
 * @param None
 * @note Needs to implemented by user for current MCU.
 * @return None
 */
static inline void usb_hw_init(void) {
    interrupts_disable();
    (void)usb_rcu_config(false);
    pointer_dword(RCU_BASE+RCU_APB2EN) |= RCU_APB2EN_PAEN; // PORTA clock.
    pointer_dword(RCU_BASE+RCU_APB2EN) |= RCU_APB2EN_AFEN; // AF clock.
    #if VBUS_SENSE_OFF
    gpio_init(GPIOA_BASE, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    pointer_dword(USBFS_BASE+USBFS_GCCFG) |= USBFS_GCCFG_VBUSIG;
    #endif
    pointer_dword(USBFS_BASE+USBFS_GCCFG) |= USBFS_GCCFG_VBUSBCEN | USBFS_GCCFG_PWRON;
    pointer_dword(RCU_BASE+RCU_APB1EN) |= RCU_APB1EN_PMUEN;
    interrupts_enable();
}

/*! @} */ // usb
/*! @} */ // middleware

#ifdef __cplusplus
}
#endif

#endif // _USB_HW_H_
// ------------------------------------------------------------------------- END
