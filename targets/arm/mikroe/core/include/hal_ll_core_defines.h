/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file  hal_ll_core_defines.h
 * @brief Core specific defines and enums used for ARM chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

#if defined(__MIKROC_AI_FOR_ARM__)
#define MIKROC_IV(x) iv x
#else
#define MIKROC_IV(x)
#endif

#define __weak __attribute__((weak))

#if defined(stm32)
#if defined(__cortex_m0__)
#if defined(STM32F0xx) || defined(STM32L0xx) || defined(STM32G0xx)
    typedef enum
    {
        HAL_LL_IVT_PRIORITY_LEVEL_0 = 0,
        HAL_LL_IVT_PRIORITY_LEVEL_1,
        HAL_LL_IVT_PRIORITY_LEVEL_2,
        HAL_LL_IVT_PRIORITY_LEVEL_3
    } hal_ll_core_irq_priority_levels;

    #define hal_ll_core_enable_int_asm asm CPSIE I
    #define hal_ll_core_disable_int_asm asm CPSID I
    #define hal_ll_core_irq(irq_val) (irq_val-16)

    #define HAL_LL_CORE_IRQ_MASK 0x1F
    #define HAL_LL_CORE_LOW_NIBBLE 0x03UL
    #define HAL_LL_CORE_HIGH_NIBBLE 0xF0UL
    #define HAL_LL_CORE_IVT_INT_SYS_TICK 15
    #define HAL_LL_CORE_IVT_TICKINT_BIT 1
    #define HAL_LL_CORE_SCB_SHCRS (( uint32_t * )0xE000ED24)
    #define HAL_LL_CORE_STK_CTRL (( uint32_t * )0xE000E010)
    #define HAL_LL_CORE_NVIC_ISER (( uint32_t * )0xE000E100)
    #define HAL_LL_CORE_NVIC_ICER (( uint32_t * )0xE000E180)
    #define HAL_LL_CORE_NVIC_IPR_0 (( uint32_t * )0xE000E400)
    #define HAL_LL_CORE_NVIC_SCB_SHPR2 (( uint32_t * )0xE000ED1C)
    #define HAL_LL_CORE_NVIC_SCB_SHPR3 (( uint32_t * )0xE000ED20)
#endif
#endif

#if defined(__cortex_m3__)
#if defined(STM32F1xx) || defined(STM32L1xx) || defined(STM32F2xx)
    typedef enum
    {
        HAL_LL_IVT_PRIORITY_LEVEL_0 = 0,
        HAL_LL_IVT_PRIORITY_LEVEL_1,
        HAL_LL_IVT_PRIORITY_LEVEL_2,
        HAL_LL_IVT_PRIORITY_LEVEL_3
    } hal_ll_core_irq_priority_levels;

    #define hal_ll_core_enable_int_asm asm CPSIE I
    #define hal_ll_core_disable_int_asm asm CPSID I
    #define hal_ll_core_irq(irq_val) (irq_val-16)

    #define HAL_LL_CORE_IRQ_MASK 0x1F
    #define HAL_LL_CORE_LOW_NIBBLE 0x03UL
    #define HAL_LL_CORE_HIGH_NIBBLE 0xF0UL
    #define HAL_LL_CORE_IVT_INT_MEM_MANAGE 4
    #define HAL_LL_CORE_IVT_INT_BUS_FAULT 5
    #define HAL_LL_CORE_IVT_INT_USAGE_FAULT 6
    #define HAL_LL_CORE_IVT_INT_SYS_TICK 15
    #define HAL_LL_CORE_IVT_TICKINT_BIT 1
    #define HAL_LL_CORE_IVT_MEMFAULTENA_BIT 16
    #define HAL_LL_CORE_IVT_BUSFAULTENA_BIT 17
    #define HAL_LL_CORE_IVT_USGFAULTENA_BIT 18
    #define HAL_LL_CORE_SCB_SHCRS (( uint32_t * )0xE000ED24)
    #define HAL_LL_CORE_STK_CTRL (( uint32_t * )0xE000E010)
    #define HAL_LL_CORE_NVIC_ISER_0 (( uint32_t * )0xE000E100)
    #define HAL_LL_CORE_NVIC_ISER_1 (( uint32_t * )0xE000E104)
    #define HAL_LL_CORE_NVIC_ISER_2 (( uint32_t * )0xE000E108)
    #define HAL_LL_CORE_NVIC_ICER_0 (( uint32_t * )0xE000E180)
    #define HAL_LL_CORE_NVIC_ICER_1 (( uint32_t * )0xE000E184)
    #define HAL_LL_CORE_NVIC_ICER_2 (( uint32_t * )0xE000E188)
    #define HAL_LL_CORE_NVIC_IPR_0 (( uint32_t * )0xE000E400)
    #define HAL_LL_CORE_NVIC_SCB_SHPR1 (( uint32_t * )0xE000ED18)
    #define HAL_LL_CORE_NVIC_SCB_SHPR2 (( uint32_t * )0xE000ED1C)
    #define HAL_LL_CORE_NVIC_SCB_SHPR3 (( uint32_t * )0xE000ED20)
#endif
#endif

#if defined(__cortex_m4__)
#if defined(STM32F3xx) || defined(STM32F4xx) || defined(STM32L4xx)
    typedef enum
    {
        HAL_LL_IVT_PRIORITY_LEVEL_0 = 0,
        HAL_LL_IVT_PRIORITY_LEVEL_1,
        HAL_LL_IVT_PRIORITY_LEVEL_2,
        HAL_LL_IVT_PRIORITY_LEVEL_3,
        HAL_LL_IVT_PRIORITY_LEVEL_4,
        HAL_LL_IVT_PRIORITY_LEVEL_5,
        HAL_LL_IVT_PRIORITY_LEVEL_6,
        HAL_LL_IVT_PRIORITY_LEVEL_7,
        HAL_LL_IVT_PRIORITY_LEVEL_8,
        HAL_LL_IVT_PRIORITY_LEVEL_9,
        HAL_LL_IVT_PRIORITY_LEVEL_10,
        HAL_LL_IVT_PRIORITY_LEVEL_11,
        HAL_LL_IVT_PRIORITY_LEVEL_12,
        HAL_LL_IVT_PRIORITY_LEVEL_13,
        HAL_LL_IVT_PRIORITY_LEVEL_14,
        HAL_LL_IVT_PRIORITY_LEVEL_15
    } hal_ll_core_irq_priority_levels;

    #define hal_ll_core_enable_int_asm asm CPSIE I
    #define hal_ll_core_disable_int_asm asm CPSID I
    #define hal_ll_core_irq(irq_val) (( irq_val - 16 ))

    #define HAL_LL_CORE_IRQ_MASK 0x1F
    #define HAL_LL_CORE_LOW_NIBBLE 0xFUL
    #define HAL_LL_CORE_HIGH_NIBBLE 0xF0UL
    #define HAL_LL_CORE_IVT_INT_MEM_MANAGE 4
    #define HAL_LL_CORE_IVT_INT_BUS_FAULT 5
    #define HAL_LL_CORE_IVT_INT_USAGE_FAULT 6
    #define HAL_LL_CORE_IVT_INT_SYS_TICK 15
    #define HAL_LL_CORE_IVT_TICKINT_BIT 1
    #define HAL_LL_CORE_IVT_MEMFAULTENA_BIT 16
    #define HAL_LL_CORE_IVT_BUSFAULTENA_BIT 17
    #define HAL_LL_CORE_IVT_USGFAULTENA_BIT 18
    #define HAL_LL_CORE_SCB_SHCRS (( uint32_t * )0xE000ED24)
    #define HAL_LL_CORE_STK_CTRL (( uint32_t * )0xE000E010)
    #define HAL_LL_CORE_NVIC_ISER_0 (( uint32_t * )0xE000E100)
    #define HAL_LL_CORE_NVIC_ISER_1 (( uint32_t * )0xE000E104)
    #define HAL_LL_CORE_NVIC_ISER_2 (( uint32_t * )0xE000E108)
    #define HAL_LL_CORE_NVIC_ICER_0 (( uint32_t * )0xE000E180)
    #define HAL_LL_CORE_NVIC_ICER_1 (( uint32_t * )0xE000E184)
    #define HAL_LL_CORE_NVIC_ICER_2 (( uint32_t * )0xE000E188)
    #define HAL_LL_CORE_NVIC_IPR_0 (( uint32_t * )0xE000E400)
    #define HAL_LL_CORE_NVIC_SCB_SHPR1 (( uint32_t * )0xE000ED18)
    #define HAL_LL_CORE_NVIC_SCB_SHPR2 (( uint32_t * )0xE000ED1C)
    #define HAL_LL_CORE_NVIC_SCB_SHPR3 (( uint32_t * )0xE000ED20)
#endif
#endif

#if defined(__cortex_m7__)
#if defined(STM32F7xx) || defined(STM32H7xx)
    typedef enum
    {
        HAL_LL_IVT_PRIORITY_LEVEL_0 = 0,
        HAL_LL_IVT_PRIORITY_LEVEL_1,
        HAL_LL_IVT_PRIORITY_LEVEL_2,
        HAL_LL_IVT_PRIORITY_LEVEL_3,
        HAL_LL_IVT_PRIORITY_LEVEL_4,
        HAL_LL_IVT_PRIORITY_LEVEL_5,
        HAL_LL_IVT_PRIORITY_LEVEL_6,
        HAL_LL_IVT_PRIORITY_LEVEL_7,
        HAL_LL_IVT_PRIORITY_LEVEL_8,
        HAL_LL_IVT_PRIORITY_LEVEL_9,
        HAL_LL_IVT_PRIORITY_LEVEL_10,
        HAL_LL_IVT_PRIORITY_LEVEL_11,
        HAL_LL_IVT_PRIORITY_LEVEL_12,
        HAL_LL_IVT_PRIORITY_LEVEL_13,
        HAL_LL_IVT_PRIORITY_LEVEL_14,
        HAL_LL_IVT_PRIORITY_LEVEL_15
    } hal_ll_core_irq_priority_levels;

    #define hal_ll_core_enable_int_asm asm CPSIE I
    #define hal_ll_core_disable_int_asm asm CPSID I
    #define hal_ll_core_irq(irq_val) (irq_val-16)

    #define HAL_LL_CORE_IRQ_MASK 0x1F
    #define HAL_LL_CORE_LOW_NIBBLE 0xFUL
    #define HAL_LL_CORE_HIGH_NIBBLE 0xF0UL
    #define HAL_LL_CORE_IVT_INT_MEM_MANAGE 4
    #define HAL_LL_CORE_IVT_INT_BUS_FAULT 5
    #define HAL_LL_CORE_IVT_INT_USAGE_FAULT 6
    #define HAL_LL_CORE_IVT_INT_SYS_TICK 15
    #define HAL_LL_CORE_IVT_TICKINT_BIT 1
    #define HAL_LL_CORE_IVT_MEMFAULTENA_BIT 16
    #define HAL_LL_CORE_IVT_BUSFAULTENA_BIT 17
    #define HAL_LL_CORE_IVT_USGFAULTENA_BIT 18
    #define HAL_LL_CORE_SCB_SHCRS (( uint32_t * )0xE000ED24)
    #define HAL_LL_CORE_STK_CTRL (( uint32_t * )0xE000E010)
    #define HAL_LL_CORE_NVIC_ISER_0 (( uint32_t * )0xE000E100)
    #define HAL_LL_CORE_NVIC_ISER_1 (( uint32_t * )0xE000E104)
    #define HAL_LL_CORE_NVIC_ISER_2 (( uint32_t * )0xE000E108)
    #define HAL_LL_CORE_NVIC_ICER_0 (( uint32_t * )0xE000E180)
    #define HAL_LL_CORE_NVIC_ICER_1 (( uint32_t * )0xE000E184)
    #define HAL_LL_CORE_NVIC_ICER_2 (( uint32_t * )0xE000E188)
    #define HAL_LL_CORE_NVIC_IPR_0 (( uint32_t * )0xE000E400)
    #define HAL_LL_CORE_NVIC_SCB_SHPR1 (( uint32_t * )0xE000ED18)
    #define HAL_LL_CORE_NVIC_SCB_SHPR2 (( uint32_t * )0xE000ED1C)
    #define HAL_LL_CORE_NVIC_SCB_SHPR3 (( uint32_t * )0xE000ED20)
#endif
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
