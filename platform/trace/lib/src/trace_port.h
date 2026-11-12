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
 * @file  trace_port.h
 * @brief Architecture port of the firmware trace: interrupt lock and cycle counter.
 *
 * @details Everything in trace.c that depends on the core is here. A port provides:
 *
 * - trace_port_lock() / trace_port_unlock( state ): mask the interrupts and restore the state
 *   from before, so that a hook called inside a critical section of the application does not
 *   enable them. The hooks run in interrupts too (UART callbacks).
 * - TRACE_PORT_HAS_COUNTER: 1 when the core has a free-running counter, then also
 *   trace_port_counter_start() (enables it, true when it really counts),
 *   trace_port_counter() (the current count) and TRACE_PORT_COUNTER_HZ (its rate, 0 when the
 *   clock is unknown). Without a counter the trace counts records: order, no timing.
 *
 * The counter is read as 32 bits and may wrap; the automatic flush keeps the wrap visible to
 * the debugger as long as the flush interval is shorter than the wrap period.
 *
 * Ported: Cortex-M (ARM), RISC-V, PIC32 (MIPS32) with GCC, Clang and XC32; Cortex-M and PIC32
 * with mikroC, which has its own assembler syntax and none of the GCC attributes. Not yet:
 * dsPIC/PIC24 (XC16), PIC 8-bit (XC8), see the stubs at the end. platform/CMakeLists.txt
 * builds the trace only for the ported architectures.
 */

#ifndef _TRACE_PORT_H_
#define _TRACE_PORT_H_

#include <stdbool.h>
#include <stdint.h>

// The core header of ARM and RISC-V holds only defines (FOSC_KHZ_VALUE). The one of PIC32
// (and of dsPIC and PIC 8-bit) also holds the #pragma config of the device, which belongs to
// preinit.c alone: included here as well, the configuration words are defined twice and the
// link fails.
#if defined(__arm__) || defined(__thumb__) || defined(__riscv)
#include "core_header.h"
#endif

// Core clock in Hz, 0 when the setup does not give it. ARM and RISC-V core headers define
// FOSC_KHZ_VALUE; the PIC32 core library defines OSC_KHZ on the command line.
#if defined(FOSC_KHZ_VALUE)
#define TRACE_PORT_FOSC_HZ ( (uint32_t)( FOSC_KHZ_VALUE ) * 1000UL )
#elif defined(OSC_KHZ)
#define TRACE_PORT_FOSC_HZ ( (uint32_t)( OSC_KHZ ) * 1000UL )
#else
#define TRACE_PORT_FOSC_HZ ( 0UL )
#endif

// ======================================================================== mikroC: Cortex-M
#if defined(__MIKROC_AI_FOR_ARM__)

// The core clock, set by the system library at startup: the rate of the DWT cycle counter.
unsigned long Get_Fosc_kHz( void );

// mikroC's assembler names special registers by number only (16: PRIMASK) and reaches C
// variables only when they are global, so the state goes through this one. The functions are
// not inline: the compiler does not know which registers the assembly uses.
volatile uint32_t trace_port_primask;

static uint32_t trace_port_lock( void )
{
    asm {
        MRS     R0, #16
        CPSID   I
        MOVW    R1, #lo_addr(_trace_port_primask+0)
        MOVT    R1, #hi_addr(_trace_port_primask+0)
        STR     R0, [R1, #0]
    }
    // Read with the interrupts masked: no other lock can change it now.
    return trace_port_primask;
}

static void trace_port_unlock( uint32_t primask )
{
    trace_port_primask = primask;
    asm {
        MOVW    R1, #lo_addr(_trace_port_primask+0)
        MOVT    R1, #hi_addr(_trace_port_primask+0)
        LDR     R0, [R1, #0]
        MSR     #16, R0
    }
}

// DWT cycle counter: Cortex-M3 and newer (core defines of MikroSDK.HalLowLevelCore). Cortex-M0
// has none, and its debug registers fault when written.
#if defined(__cortex_m3__) || defined(__cortex_m4__) || defined(__cortex_m7__) || defined(__cortex_m33__)
#define TRACE_PORT_HAS_COUNTER 1
#define TRACE_PORT_COUNTER_HZ ( (uint32_t)Get_Fosc_kHz() * 1000UL )

#define TRACE_DEMCR (*(volatile uint32_t *)0xE000EDFCUL)
#define TRACE_DEMCR_TRCENA (1UL << 24)
#define TRACE_DWT_CTRL (*(volatile uint32_t *)0xE0001000UL)
#define TRACE_DWT_CTRL_CYCCNTENA (1UL << 0)
#define TRACE_DWT_CYCCNT (*(volatile uint32_t *)0xE0001004UL)
#define TRACE_DWT_LAR (*(volatile uint32_t *)0xE0001FB0UL)
#define TRACE_DWT_LAR_KEY (0xC5ACCE55UL)

static uint32_t trace_port_counter( void )
{
    return TRACE_DWT_CYCCNT;
}

static bool trace_port_counter_start( void )
{
    uint32_t first;
    TRACE_DEMCR |= TRACE_DEMCR_TRCENA;
    #ifdef __cortex_m7__
    TRACE_DWT_LAR = TRACE_DWT_LAR_KEY;
    #endif
    TRACE_DWT_CYCCNT = 0;
    TRACE_DWT_CTRL |= TRACE_DWT_CTRL_CYCCNTENA;

    first = TRACE_DWT_CYCCNT;
    asm {
        NOP
        NOP
        NOP
        NOP
    }
    return TRACE_DWT_CYCCNT != first;
}
#else
#define TRACE_PORT_HAS_COUNTER 0
#endif

// ======================================================================== mikroC: PIC32
#elif defined(__MIKROC_AI_FOR_PIC32__)

// The system clock: CP0 Count runs at half of it.
unsigned long Get_Fosc_kHz( void );

// CP0_GET is a compiler built-in. It takes the name of a constant and looks up <name>_SELECT
// next to it; given a plain number, the compiler stops without a message.
static const unsigned long TRACE_CP0_COUNT = 9;
static const unsigned long TRACE_CP0_COUNT_SELECT = 0;
static const unsigned long TRACE_CP0_STATUS = 12;
static const unsigned long TRACE_CP0_STATUS_SELECT = 0;
#define TRACE_STATUS_IE (1UL)

static uint32_t trace_port_lock( void )
{
    uint32_t status = CP0_GET( TRACE_CP0_STATUS );
    asm {
        DI
        EHB
    }
    return status;
}

static void trace_port_unlock( uint32_t status )
{
    if ( status & TRACE_STATUS_IE )
    {
        asm {
            EI
            EHB
        }
    }
}

#define TRACE_PORT_HAS_COUNTER 1
#define TRACE_PORT_COUNTER_HZ ( (uint32_t)Get_Fosc_kHz() * 500UL )

static uint32_t trace_port_counter( void )
{
    return CP0_GET( TRACE_CP0_COUNT );
}

static bool trace_port_counter_start( void )
{
    uint32_t first = trace_port_counter();
    asm {
        NOP
        NOP
        NOP
        NOP
    }
    return trace_port_counter() != first;
}

// ======================================================================== ARM Cortex-M
#elif defined(__arm__) || defined(__thumb__)

static inline uint32_t trace_port_lock( void )
{
    uint32_t primask;
    __asm volatile ( "mrs %0, primask\n\tcpsid i" : "=r" ( primask ) :: "memory" );
    return primask;
}

static inline void trace_port_unlock( uint32_t primask )
{
    __asm volatile ( "msr primask, %0" :: "r" ( primask ) : "memory" );
}

// DWT cycle counter: Cortex-M3 and newer, optional in the architecture. Cortex-M0/M0+ have none.
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_8M_MAIN__)
#define TRACE_PORT_HAS_COUNTER 1
#define TRACE_PORT_COUNTER_HZ TRACE_PORT_FOSC_HZ

#define TRACE_DEMCR (*(volatile uint32_t *)0xE000EDFCUL)
#define TRACE_DEMCR_TRCENA (1UL << 24)
#define TRACE_DWT_CTRL (*(volatile uint32_t *)0xE0001000UL)
#define TRACE_DWT_CTRL_CYCCNTENA (1UL << 0)
#define TRACE_DWT_CYCCNT (*(volatile uint32_t *)0xE0001004UL)
// Cortex-M7 keeps the DWT locked until this key is written; other cores have no such register.
#define TRACE_DWT_LAR (*(volatile uint32_t *)0xE0001FB0UL)
#define TRACE_DWT_LAR_KEY (0xC5ACCE55UL)

static inline uint32_t trace_port_counter( void )
{
    return TRACE_DWT_CYCCNT;
}

static inline bool trace_port_counter_start( void )
{
    TRACE_DEMCR |= TRACE_DEMCR_TRCENA;
    #ifdef __cortex_m7__
    TRACE_DWT_LAR = TRACE_DWT_LAR_KEY;
    #endif
    TRACE_DWT_CYCCNT = 0;
    TRACE_DWT_CTRL |= TRACE_DWT_CTRL_CYCCNTENA;

    // The counter is optional in the architecture: check that it really counts.
    uint32_t first = TRACE_DWT_CYCCNT;
    __asm volatile ( "nop\n\tnop\n\tnop\n\tnop" );
    return TRACE_DWT_CYCCNT != first;
}
#else
#define TRACE_PORT_HAS_COUNTER 0
#endif

// ======================================================================== RISC-V
#elif defined(__riscv)

// Machine mode: mstatus.MIE (bit 3) gates every interrupt, the ECLIC ones too.
#define TRACE_MSTATUS_MIE (8UL)

static inline uint32_t trace_port_lock( void )
{
    unsigned long mstatus;
    __asm volatile ( "csrrci %0, mstatus, 8" : "=r" ( mstatus ) :: "memory" );
    return (uint32_t)mstatus;
}

static inline void trace_port_unlock( uint32_t mstatus )
{
    unsigned long mie = mstatus & TRACE_MSTATUS_MIE;
    __asm volatile ( "csrs mstatus, %0" :: "r" ( mie ) : "memory" );
}

// mcycle, at the core clock. Only its low 32 bits are read: the trace time base is 32 bits.
#define TRACE_PORT_HAS_COUNTER 1
#define TRACE_PORT_COUNTER_HZ TRACE_PORT_FOSC_HZ

static inline uint32_t trace_port_counter( void )
{
    unsigned long cycles;
    __asm volatile ( "csrr %0, mcycle" : "=r" ( cycles ) );
    return (uint32_t)cycles;
}

static inline bool trace_port_counter_start( void )
{
    // mcycle runs from reset on the supported cores (GD32VF103). mcountinhibit can stop it, but
    // that CSR is not on every core and writing a missing CSR traps: only check that it counts.
    uint32_t first = trace_port_counter();
    __asm volatile ( "nop\n\tnop\n\tnop\n\tnop" );
    return trace_port_counter() != first;
}

// ======================================================================== PIC32 (MIPS32)
#elif defined(__mips__) || defined(__XC32)

// Status.IE, bit 0. di/ei are MIPS32 release 2, which every PIC32 core is.
#define TRACE_STATUS_IE (1UL)

static inline uint32_t trace_port_lock( void )
{
    uint32_t status;
    __asm volatile ( "di %0\n\tehb" : "=r" ( status ) :: "memory" );
    return status;
}

static inline void trace_port_unlock( uint32_t status )
{
    if ( status & TRACE_STATUS_IE )
    {
        __asm volatile ( "ei\n\tehb" ::: "memory" );
    }
}

// CP0 Count (register 9, select 0) counts every other core clock.
#define TRACE_PORT_HAS_COUNTER 1
#define TRACE_PORT_COUNTER_HZ ( TRACE_PORT_FOSC_HZ / 2UL )

static inline uint32_t trace_port_counter( void )
{
    uint32_t count;
    __asm volatile ( "mfc0 %0, $9, 0" : "=r" ( count ) );
    return count;
}

static inline bool trace_port_counter_start( void )
{
    // Count runs from reset unless Cause.DC stops it, which no startup code sets.
    uint32_t first = trace_port_counter();
    __asm volatile ( "nop\n\tnop\n\tnop\n\tnop" );
    return trace_port_counter() != first;
}

// ======================================================================== dsPIC / PIC24 (XC16)
#elif defined(__XC16__) || defined(__XC16)

// Not ported yet: platform/CMakeLists.txt does not build the trace for pic_16bit. To port:
// - Lock: save SR and raise the CPU priority to 7 (SET_AND_SAVE_CPU_IPL / RESTORE_CPU_IPL from
//   xc.h). __builtin_disi() is not enough: it leaves priority 7 on and times out.
// - Counter: the core has no cycle counter. Give the trace a 32-bit timer pair (TMR2/TMR3)
//   running from the instruction clock, FOSC / 2, and set TRACE_PORT_COUNTER_HZ to its rate.
//   Or leave TRACE_PORT_HAS_COUNTER at 0: record order only, no bursts, no automatic flush.
// - RAM: the lanes alone take close to 2 KB with TRACE_MAX_LANES 32; parts with 8 KB need fewer lanes
//   and a smaller TRACE_BUFF_SIZE.
#error "Firmware trace: the dsPIC/PIC24 port is not written yet, see trace_port.h."

// ======================================================================== PIC 8-bit (XC8)
#elif defined(__XC8) || defined(__XC8__)

// Not ported yet, and not reachable: drv_trace.h compiles no hooks for XC8, so trace.c stops
// at its DRV_TRACE_ENABLED check before this file. A port needs more than this header:
// - The hooks: the drivers rely on weak symbols to switch the trace on at link time. XC8
//   needs a compile-time switch (MIKROSDK_TRACE) around every hook call instead.
// - The XC8 compiled stack: a function called from both main and an interrupt is duplicated
//   or rejected, and the UART callbacks call the hooks from interrupts.
// - Lock: save INTCON.GIE (and GIEH/GIEL with priorities), clear it, restore it.
// - Counter: none; a 16-bit timer at most. Smaller records (16-bit ticks), fewer lanes and no
//   burst state would fit 1 to 4 KB of RAM.
#error "Firmware trace: the PIC 8-bit port is not written yet, see trace_port.h."

#else
#error "Firmware trace: no port for this architecture, see trace_port.h."
#endif

#endif // _TRACE_PORT_H_
// ------------------------------------------------------------------------- END
