/*
 * Copyright (c) 2019, Emil Renner Berthing
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
#ifndef RISCV_BITS_H
#define RISCV_BITS_H

#define ROUNDUP(a, b) ((((a)-1)/(b)+1)*(b))
#define ROUNDDOWN(a, b) ((a)/(b)*(b))

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef CLAMP
#define CLAMP(a, lo, hi) MIN(MAX(a, lo), hi)
#endif
#ifndef STR
#define STR(x) XSTR(x)
#define XSTR(x) #x
#endif

#ifdef __ASSEMBLER__

#if __riscv_xlen == 64
# define SLL32    sllw
# define STORE    sd
# define LOAD     ld
# define LWU      lwu
# define REGBYTES     8
# define LOG_REGBYTES 3
#elif __riscv_xlen == 32
# define SLL32    sll
# define STORE    sw
# define LOAD     lw
# define LWU      lw
# define REGBYTES     4
# define LOG_REGBYTES 2
#else
#error "Unsupported __riscv_xlen"
#endif

#else /* C */

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define ARRAY_END(x) (&(x)[ARRAY_SIZE(x)])

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

#if __has_attribute(__naked__)
#define __naked __attribute__((__naked__))
#endif

#if __has_attribute(__interrupt__)
#define __interrupt __attribute__((__interrupt__))
#endif

#if __has_attribute(__noreturn__)
#define __noreturn __attribute__((__noreturn__))
#else
#define __noreturn
#endif

static inline void
wait_for_interrupt(void)
{
    __asm__ __volatile__ ("wfi");
}

static inline void
nop(void)
{
    __asm__ __volatile__ ("nop");
}

#endif
#endif
