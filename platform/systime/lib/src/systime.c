/****************************************************************************
**
** Copyright ( C ) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
 * @file systime.c
 * @brief Millisecond time from the core's cycle counter (see systime.h).
 * @details Counters and clock macros as in platform/trace (trace_port.h).
 * SYSTIME_TEST_COUNTER replaces the counter by systime_test_counter() and its
 * rate by SYSTIME_TEST_TICKS_PER_MS, for host tests only.
 */

#include <stdbool.h>
#include "systime.h"

#if defined( SYSTIME_TEST_COUNTER )

uint32_t systime_test_counter( void );
#define SYSTIME_TICKS_PER_MS ( SYSTIME_TEST_TICKS_PER_MS )
static inline uint32_t systime_counter( void ) { return systime_test_counter(); }
static inline void systime_counter_start( void ) { }

#else

#if defined( __arm__ ) || defined( __thumb__ ) || defined( __riscv )
// ARM and RISC-V core headers define FOSC_KHZ_VALUE (the one of PIC32 also holds
// the #pragma config words, which belong to preinit.c alone).
#include "core_header.h"
#endif

// Core clock in kHz: FOSC_KHZ_VALUE (ARM, RISC-V core header) or OSC_KHZ (PIC32
// core library, on the command line).
#if defined( FOSC_KHZ_VALUE )
#define SYSTIME_CORE_KHZ ( ( uint32_t )( FOSC_KHZ_VALUE ) )
#elif defined( OSC_KHZ )
#define SYSTIME_CORE_KHZ ( ( uint32_t )( OSC_KHZ ) )
#else
#error "systime: the setup gives no core clock (FOSC_KHZ_VALUE / OSC_KHZ)"
#endif

#if defined( __arm__ ) || defined( __thumb__ )

#if !( defined( __ARM_ARCH_7M__ ) || defined( __ARM_ARCH_7EM__ ) || defined( __ARM_ARCH_8M_MAIN__ ) || \
       defined( __ARM_ARCH_8_1M_MAIN__ ) )
#error "systime: Cortex-M0/M0+/M23 have no cycle counter"
#endif

#define SYSTIME_DEMCR       ( *( volatile uint32_t * )0xE000EDFCUL )
#define SYSTIME_DWT_CTRL    ( *( volatile uint32_t * )0xE0001000UL )
#define SYSTIME_DWT_CYCCNT  ( *( volatile uint32_t * )0xE0001004UL )
#define SYSTIME_DWT_LAR     ( *( volatile uint32_t * )0xE0001FB0UL )
#define SYSTIME_TICKS_PER_MS SYSTIME_CORE_KHZ

static inline uint32_t systime_counter( void )
{
    return SYSTIME_DWT_CYCCNT;
}

static inline void systime_counter_start( void )
{
    SYSTIME_DEMCR |= ( 1UL << 24 );            // TRCENA
    #ifdef __cortex_m7__
    SYSTIME_DWT_LAR = 0xC5ACCE55UL;            // Cortex-M7 keeps the DWT locked until this key
    #endif
    SYSTIME_DWT_CTRL |= 1UL;                   // CYCCNTENA (left running if the trace started it)
}

#elif defined( __riscv )

#define SYSTIME_TICKS_PER_MS SYSTIME_CORE_KHZ

static inline uint32_t systime_counter( void )
{
    unsigned long cycles;
    __asm__ volatile ( "csrr %0, mcycle" : "=r" ( cycles ) );
    return ( uint32_t )cycles;
}

static inline void systime_counter_start( void )
{
    // mcycle runs from reset on the supported cores.
}

#elif defined( __mips__ ) || defined( __XC32 )

#define SYSTIME_TICKS_PER_MS ( SYSTIME_CORE_KHZ / 2UL )   // CP0 Count: every other core clock

static inline uint32_t systime_counter( void )
{
    uint32_t count;
    __asm__ volatile ( "mfc0 %0, $9, 0" : "=r" ( count ) );
    return count;
}

static inline void systime_counter_start( void )
{
    // CP0 Count runs from reset.
}

#else
#error "systime: unsupported core"
#endif

#endif // SYSTIME_TEST_COUNTER

static bool systime_started;
static uint32_t systime_last;     // counter at the previous call
static uint32_t systime_ticks;    // counted ticks not yet making a whole millisecond
static uint32_t systime_now;      // milliseconds

void systime_init( void )
{
    if ( !systime_started )
    {
        systime_counter_start();
        systime_last = systime_counter();
        systime_ticks = 0;
        systime_now = 0;
        systime_started = true;
    }
}

uint32_t systime_ms( void )
{
    if ( !systime_started )
    {
        systime_init();
    }
    uint32_t now = systime_counter();
    uint32_t elapsed = now - systime_last;      // unsigned: correct across a counter wrap
    systime_last = now;

    // Whole milliseconds first, so that the sum below cannot overflow.
    systime_now += elapsed / SYSTIME_TICKS_PER_MS;
    systime_ticks += elapsed % SYSTIME_TICKS_PER_MS;
    if ( systime_ticks >= SYSTIME_TICKS_PER_MS )
    {
        systime_ticks -= SYSTIME_TICKS_PER_MS;
        systime_now++;
    }
    return systime_now;
}

// ------------------------------------------------------------------------- END
