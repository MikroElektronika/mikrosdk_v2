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
 * @file  hal_ll_pmc.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_PMC_H_
#define _HAL_LL_PMC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 *  Core register addresses used in source
 */
#define _PMC_BASE       (0x400E0600UL) /* PMC Base Address */
#define _PMC_SCER       ((uint32_t *)(_PMC_BASE + 0x00))   /* System Clock Enable Register */
#define _PMC_SCDR       ((uint32_t *)(_PMC_BASE + 0x04))   /* System Clock Disable Register */
#define _PMC_SCSR       ((uint32_t *)(_PMC_BASE + 0x08))   /* System Clock Status Register */
#define _PMC_PCER0      ((uint32_t *)(_PMC_BASE + 0x10))   /* Peripheral Clock Enable Register 0 */
#define _PMC_PCDR0      ((uint32_t *)(_PMC_BASE + 0x14))   /* Peripheral Clock Disable Register 0 */
#define _PMC_PCSR0      ((uint32_t *)(_PMC_BASE + 0x18))   /* Peripheral Clock Status Register 0 */
#define _CKGR_UCKR      ((uint32_t *)(_PMC_BASE + 0x1C))   /* UTMI Clock Register */
#define _CKGR_MOR       ((uint32_t *)(_PMC_BASE + 0x20))   /* Main Oscillator Register */
#define _CKGR_MCFR      ((uint32_t *)(_PMC_BASE + 0x24))   /* Main Clock Frequency Register */
#define _CKGR_PLLAR     ((uint32_t *)(_PMC_BASE + 0x28))   /* PLLA Register */
#define _PMC_MCKR       ((uint32_t *)(_PMC_BASE + 0x30))   /* Master Clock Register */
#define _PMC_USB        ((uint32_t *)(_PMC_BASE + 0x38))   /* USB Clock Register */
#define _PMC_PCK0       ((uint32_t *)(_PMC_BASE + 0x40))   /* Programmable Clock Register 0 */
#define _PMC_PCK1       ((uint32_t *)(_PMC_BASE + 0x44))   /* Programmable Clock Register 1 */
#define _PMC_PCK2       ((uint32_t *)(_PMC_BASE + 0x48))   /* Programmable Clock Register 2 */
#define _PMC_PCK3       ((uint32_t *)(_PMC_BASE + 0x4C))   /* Programmable Clock Register 3 */
#define _PMC_PCK4       ((uint32_t *)(_PMC_BASE + 0x50))   /* Programmable Clock Register 4 */
#define _PMC_PCK5       ((uint32_t *)(_PMC_BASE + 0x54))   /* Programmable Clock Register 5 */
#define _PMC_PCK6       ((uint32_t *)(_PMC_BASE + 0x58))   /* Programmable Clock Register 6 */
#define _PMC_PCK7       ((uint32_t *)(_PMC_BASE + 0x5C))   /* Programmable Clock Register 7 */
#define _PMC_IER        ((uint32_t *)(_PMC_BASE + 0x60))   /* Interrupt Enable Register */
#define _PMC_IDR        ((uint32_t *)(_PMC_BASE + 0x64))   /* Interrupt Disable Register */
#define _PMC_SR         ((uint32_t *)(_PMC_BASE + 0x68))   /* Status Register */
#define _PMC_IMR        ((uint32_t *)(_PMC_BASE + 0x6C))   /* Interrupt Mask Register */
#define _PMC_FSMR       ((uint32_t *)(_PMC_BASE + 0x70))   /* Fast Startup Mode Register */
#define _PMC_FSPR       ((uint32_t *)(_PMC_BASE + 0x74))   /* Fast Startup Polarity Register */
#define _PMC_FOCR       ((uint32_t *)(_PMC_BASE + 0x78))   /* Fault Output Clear Register */
#define _PMC_WPMR       ((uint32_t *)(_PMC_BASE + 0xE4))   /* Write Protection Mode Register */
#define _PMC_WPSR       ((uint32_t *)(_PMC_BASE + 0xE8))   /* Write Protection Status Register */
#define _PMC_PCER1      ((uint32_t *)(_PMC_BASE + 0x100))  /* Peripheral Clock Enable Register 1 */
#define _PMC_PCDR1      ((uint32_t *)(_PMC_BASE + 0x104))  /* Peripheral Clock Disable Register 1 */
#define _PMC_PCSR1      ((uint32_t *)(_PMC_BASE + 0x108))  /* Peripheral Clock Status Register 1 */
#define _PMC_PCR        ((uint32_t *)(_PMC_BASE + 0x10C))  /* Peripheral Control Register */
#define _PMC_OCR        ((uint32_t *)(_PMC_BASE + 0x110))  /* Oscillator Calibration Register */
#define _PMC_SLPWK_ER0  ((uint32_t *)(_PMC_BASE + 0x114))  /* SleepWalking Enable Register 0 */
#define _PMC_SLPWK_DR0  ((uint32_t *)(_PMC_BASE + 0x118))  /* SleepWalking Disable Register 0 */
#define _PMC_SLPWK_SR0  ((uint32_t *)(_PMC_BASE + 0x11C))  /* SleepWalking Status Register 0 */
#define _PMC_SLPWK_ASR0 ((uint32_t *)(_PMC_BASE + 0x120))  /* SleepWalking Activity Status Register 0 */
#define _PMC_PMMR       ((uint32_t *)(_PMC_BASE + 0x130))  /* PLL Maximum Multiplier Value Register */
#define _PMC_SLPWK_ER1  ((uint32_t *)(_PMC_BASE + 0x134))  /* SleepWalking Enable Register 1 */
#define _PMC_SLPWK_DR1  ((uint32_t *)(_PMC_BASE + 0x138))  /* SleepWalking Disable Register 1 */
#define _PMC_SLPWK_SR1  ((uint32_t *)(_PMC_BASE + 0x13C))  /* SleepWalking Status Register 1 */
#define _PMC_SLPWK_ASR1 ((uint32_t *)(_PMC_BASE + 0x140))  /* SleepWalking Activity Status Register 1 */
#define _PMC_SLPWK_AIPR ((uint32_t *)(_PMC_BASE + 0x144))  /* SleepWalking Activity In Progress Register */

/**
 *  RCC Structs used in source
 */
typedef struct pmc_clocks
{
    uint32_t mck;     // Master clock frequency in Hz
    uint32_t pck[8];  // Peripheral clock frequency in Hz
} pmc_clocks_t;

/**
 * @brief Gets clock values.
 *
 * @param pmc_clocks_t[OUT] RCC clocks structure.
 *
 * @return *pmc_clocks_t Structure containing clock values.
 */
void RCC_GetClocksFrequency(pmc_clocks_t *PMC_Clocks);

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PMC_H_
// ------------------------------------------------------------------------- END
