/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @brief Core specific defines and enums used for RISC-V chips.
 */

#ifndef _HAL_LL_CORE_DEFINES_H_
#define _HAL_LL_CORE_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include "assembly.h"

#define MSTATUS_MIE                      (0x00000008)
#define ECLIC_ADDR_BASE                  (0xD2000000)
#define CLIC_CFG_NLBITS_MASK             (0x1E)
#define CLIC_CFG_NLBITS_SHIFT            (1)
#define CLIC_INFO_CLICINTCTLBITS_MASK    (0x01E00000)
#define CLIC_INFO_CLICINTCTLBITS_SHIFT   (21)
#define MTVEC_CLIC_INTERRUPT_MODE        (0x00000003)
#define MTVEC_CLIC_INTERRUPT_MODE_MASK   (0xFFFFFFC0)
#define CLICINT_ATTR_VECTORED_INTERRUPT  (0x1)

#define ECLIC_INT_IP_OFFSET              (0x1000UL)
#define ECLIC_INT_IE_OFFSET              (0x1001UL)
#define ECLIC_INT_ATTR_OFFSET            (0x1002UL)
#define ECLIC_INT_CTL_OFFSET             (0x1003UL)

#define SET_ECLIC_CLICINT_IP(IRQn,val)   (*(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IP_OFFSET+IRQn*4)=val)
#define GET_ECLIC_CLICINT_IP(IRQn)       (*(volatile uint8_t*)ECLIC_ADDR_BASE+ECLIC_INT_IP_OFFSET+IRQn*4)

#define SET_ECLIC_CLICINT_IE(IRQn,val)   (*(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_IE_OFFSET+IRQn*4)=val)
#define GET_ECLIC_CLICINT_IE(IRQn)       (*(volatile uint8_t*)ECLIC_ADDR_BASE+ECLIC_INT_IE_OFFSET+IRQn*4)

#define SET_ECLIC_CLICINT_ATTR(IRQn,val) (*(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_ATTR_OFFSET+IRQn*4)=val)
#define GET_ECLIC_CLICINT_ATTR(IRQn)     (*(volatile uint8_t*)ECLIC_ADDR_BASE+ECLIC_INT_ATTR_OFFSET+IRQn*4)

#define SET_ECLIC_CLICINT_CTL(IRQn,val)  (*(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTL_OFFSET+IRQn*4)=val)
#define GET_ECLIC_CLICINT_CTL(IRQn)      (*(volatile uint8_t*)ECLIC_ADDR_BASE+ECLIC_INT_CTL_OFFSET+IRQn*4)

typedef struct {
    volatile uint8_t cfg;               // Global configuration register
    uint8_t _unused1[3];
    const uint32_t info;                // Global info register
    uint8_t _unused2[3];
    volatile uint8_t mth;               // Target threshold level register
} eclic;

#define __weak __attribute__((weak))

#define set_csr(reg, bit) ({ unsigned long __tmp; \
                             if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
                                 asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
                             else \
                                 asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
                             __tmp; })
#define clear_csr(reg, bit) ({ unsigned long __tmp; \
                               if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32) \
                                   asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
                               else \
                                   asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
                               __tmp; })

#define read_csr(reg) ({ unsigned long __tmp; \
                         asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
                         __tmp; })

#define write_csr(reg, val) ({ \
                               if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
                                   asm volatile ("csrw " #reg ", %0" :: "i"(val)); \
                               else \
                                   asm volatile ("csrw " #reg ", %0" :: "r"(val)); })

#if defined(gigadevice)
#if defined(__core_bumblebee__)
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

#endif
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_CORE_DEFINES_H_
// ------------------------------------------------------------------------- END
