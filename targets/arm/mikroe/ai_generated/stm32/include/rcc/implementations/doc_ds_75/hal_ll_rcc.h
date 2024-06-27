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
 * @file  hal_ll_rcc.h
 * @brief Reset and Clock control defines necessary for HAL.
 */

#ifndef _HAL_LL_RCC_H_
#define _HAL_LL_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/**
 *  Core register addresses used in source
 */
#define _RCC_BASE (0x40021000UL)
#define _RCC_CR ((uint32_t *)(_RCC_BASE + 0x0))
#define _RCC_ICSCR ((uint32_t *)(_RCC_BASE + 0x4))
#define _RCC_CFGR ((uint32_t *)(_RCC_BASE + 0x8))
#define _RCC_PLLCFGR ((uint32_t *)(_RCC_BASE + 0xC))
#define _RCC_CIER ((uint32_t *)(_RCC_BASE + 0x18))
#define _RCC_CIFR ((uint32_t *)(_RCC_BASE + 0x1C))
#define _RCC_CICR ((uint32_t *)(_RCC_BASE + 0x20))
#define _RCC_IOPRSTR ((uint32_t *)(_RCC_BASE + 0x24))
#define _RCC_AHBRSTR ((uint32_t *)(_RCC_BASE + 0x28))
#define _RCC_APBRSTR1 ((uint32_t *)(_RCC_BASE + 0x2C))
#define _RCC_APBRSTR2 ((uint32_t *)(_RCC_BASE + 0x30))
#define _RCC_IOPENR ((uint32_t *)(_RCC_BASE + 0x34))
#define _RCC_AHBENR ((uint32_t *)(_RCC_BASE + 0x38))
#define _RCC_APBENR1 ((uint32_t *)(_RCC_BASE + 0x3C))
#define _RCC_APBENR2 ((uint32_t *)(_RCC_BASE + 0x40))
#define _RCC_IOPSMENR ((uint32_t *)(_RCC_BASE + 0x44))
#define _RCC_AHBSMENR ((uint32_t *)(_RCC_BASE + 0x48))
#define _RCC_APBSMENR1 ((uint32_t *)(_RCC_BASE + 0x4C))
#define _RCC_APBSMENR2 ((uint32_t *)(_RCC_BASE + 0x50))
#define _RCC_CCIPR ((uint32_t *)(_RCC_BASE + 0x54))
#define _RCC_BDCR ((uint32_t *)(_RCC_BASE + 0x5C))
#define _RCC_CSR ((uint32_t *)(_RCC_BASE + 0x60))

/**
 *  RCC Structs used in source
 */
typedef struct rcc_clocks
{
  uint32_t sysclk; // SYSCLK clock frequency  in Hz
  uint32_t hclk;   // HCLK   clock frequency  in Hz
  uint32_t pclk;   // PCLK   clock frequency  in Hz
  uint32_t tpclk;  // TPCLK  clock frequency  in Hz
} rcc_clocks_t;

/**
 * @brief Gets clock values.
 *
 * @param rcc_clocks_t[OUT] RCC clocks structure.
 *
 * @return *rcc_clocks_t Structure containing clock values.
 */
void RCC_GetClocksFrequency(rcc_clocks_t *RCC_Clocks);

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_RCC_H_
// ------------------------------------------------------------------------- END
