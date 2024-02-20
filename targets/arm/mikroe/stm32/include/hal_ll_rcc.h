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
#if defined(STM32F03x) || defined(STM32F04x) || defined(STM32F05x) || \
    defined(STM32F07x) || defined(STM32F09x)
    #define _RCC_AHBENR   ( uint32_t * )0x40021014
    #define _RCC_APB2ENR  ( uint32_t * )0x40021018
    #define _RCC_APB1ENR  ( uint32_t * )0x4002101C
    #define _RCC_CR2      ( uint32_t * )0x40021034
#endif

#if defined(STM32G0xx)
    #define _RCC_IOPENR   ( uint32_t * )0x40021034
    #define _RCC_AHBENR   ( uint32_t * )0x40021038
    #define _RCC_APB1ENR  ( uint32_t * )0x4002103C
    #define _RCC_APB2ENR  ( uint32_t * )0x40021040
    #define _RCC_CCIPR    ( uint32_t * )0x40021054
#endif

#if defined(STM32L01x) || defined(STM32L02x) || defined(STM32L03x) || \
    defined(STM32L04x) || defined(STM32L05x) || defined(STM32L06x) || \
    defined(STM32L07x) || defined(STM32L08x)
    #define _RCC_IOPENR   ( uint32_t * )0x4002102C
    #define _RCC_AHBENR   ( uint32_t * )0x40021030
    #define _RCC_APB2ENR  ( uint32_t * )0x40021034
    #define _RCC_APB1ENR  ( uint32_t * )0x40021038
    #define _RCC_CCIPR    ( uint32_t * )0x4002104C
    #define _RCC_CR       ( uint32_t *)0x40021000
#endif

#if defined (STM32F1xx)
    #define _RCC_AHBENR   ( uint32_t * )0x40021014
    #define _RCC_APB1ENR  ( uint32_t * )0x4002101C
    #define _RCC_APB2ENR  ( uint32_t * )0x40021018
    #define _AFIO_MAPR    ( uint32_t * )0x40010004
    #define _AFIO_MAPR2   ( uint32_t * )0x4001001C
#endif

#if defined(STM32L1xx)
    #define _RCC_APB1ENR  ( uint32_t * )0x40023824
    #define _RCC_APB2ENR  ( uint32_t * )0x40023820
    #define _RCC_AHBENR   ( uint32_t * )0x4002381C
#endif

#if defined(STM32F2xx)
    #define _RCC_APB1ENR  ( uint32_t * )0x40023840
    #define _RCC_APB2ENR  ( uint32_t * )0x40023844
    #define _RCC_AHB1ENR  ( uint32_t * )0x40023830
#endif

#if defined(STM32F3xx)
    #define _RCC_AHBENR   ( uint32_t * )0x40021014
    #define _RCC_APB1ENR  ( uint32_t * )0x4002101C
    #define _RCC_APB2ENR  ( uint32_t * )0x40021018
#endif

#if defined (STM32F4xx)
    #define _RCC_AHB1ENR  ( uint32_t * )0x40023830
    #define _RCC_APB1ENR  ( uint32_t * )0x40023840
    #define _RCC_APB2ENR  ( uint32_t * )0x40023844
#endif

#if defined(STM32L4xx)
    #define _RCC_AHB1ENR   ( uint32_t * )0x40021048
    #define _RCC_APB1ENR1  ( uint32_t * )0x40021058
    #define _RCC_APB1ENR2  ( uint32_t * )0x4002105C
    #define _RCC_APB2ENR   ( uint32_t * )0x40021060
    #define _RCC_AHB2ENR   ( uint32_t * )0x4002104C
    #define _RCC_CCIPR     ( uint32_t * )0x40021088
    #define _RCC_CCIPR2    ( uint32_t * )0x4002109C
#endif

#if defined(STM32F7xx)
    #define _RCC_AHB1ENR   ( uint32_t * )0x40023830
    #define _RCC_APB1ENR   ( uint32_t * )0x40023840
    #define _RCC_APB2ENR   ( uint32_t * )0x40023844
    #define _RCC_DCKCFGR2  ( uint32_t * )0x40023890
#endif

#if defined(STM32H7xx)
    #define _RCC_AHB1ENR   ( uint32_t * )0x580244D8
    #define _RCC_APB1LENR  ( uint32_t * )0x580244E8
    #define _RCC_APB2ENR   ( uint32_t * )0x580244F0
    #define _RCC_AHB4ENR   ( uint32_t * )0x580244E0
    #define _RCC_APB4ENR   ( uint32_t * )0x580244F4
    #define _RCC_D1CCIPR   ( uint32_t * )0x5802444C
    #define _RCC_D2CCIP2R  ( uint32_t * )0x58024454
    #define _RCC_D2CCIP1R  ( uint32_t * )0x58024450
    #define _RCC_D3CCIPR   ( uint32_t * )0x58024458
#endif

/**
 *  RCC Structs used in source
 */
#if defined(STM32H7xx)
typedef struct
{
  uint32_t sysclk; // SYSCLK clock frequency  in Hz
  uint32_t hclk;   // HCLK   clock frequency  in Hz
  uint32_t pclk1;  // PCLK1  clock frequency  in Hz
  uint32_t pclk2;  // PCLK2  clock frequency  in Hz
  uint32_t pclk3;  // PCLK1  clock frequency  in Hz
  uint32_t pclk4;  // PCLK1  clock frequency  in Hz
  uint32_t adcclk; // ADCCLK clock frequency  in Hz
} rcc_clocks_t;
#elif defined(STM32F7xx) || defined(STM32F4xx) || \
      defined(STM32L4xx) || defined(STM32F3xx) || defined(STM32F2xx) || \
      defined(STM32F1xx) || defined(STM32L1xx)
typedef struct
{
  uint32_t sysclk; // SYSCLK clock frequency  in Hz
  uint32_t hclk;   // HCLK   clock frequency  in Hz
  uint32_t pclk1;  // PCLK1  clock frequency  in Hz
  uint32_t pclk2;  // PCLK2  clock frequency  in Hz
  uint32_t adcclk; // ADCCLK clock frequency  in Hz
} rcc_clocks_t;
#elif defined(STM32L0xx)
typedef struct
{
  uint32_t sysclk; // SYSCLK clock frequency  in Hz
  uint32_t hclk;   // HCLK   clock frequency  in Hz
  uint32_t pclk1;  // PCLK1  clock frequency  in Hz
  uint32_t pclk2;  // PCLK2  clock frequency  in Hz
} rcc_clocks_t;
#elif defined(STM32G0xx)
typedef struct
{
  uint32_t sysclk; // SYSCLK clock frequency  in Hz
  uint32_t hclk;   // HCLK   clock frequency  in Hz
  uint32_t pclk;   // PCLK   clock frequency  in Hz
  uint32_t tpclk;  // TPCLK  clock frequency  in Hz
} rcc_clocks_t;
#else
typedef struct
{
  uint32_t sysclk; // SYSCLK clock frequency  in Hz
  uint32_t hclk;   // HCLK   clock frequency  in Hz
  uint32_t pclk;   // PCLK   clock frequency  in Hz
  uint32_t adcclk; // ADCCLK clock frequency  in Hz
} rcc_clocks_t;
#endif

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
