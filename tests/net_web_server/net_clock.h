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
 * @file net_clock.h
 * @brief Millisecond counter for the network layer (net_config_t.now_ms),
 * without interrupts: the core's cycle counter, added up on every call.
 * @details Cortex-M3 and newer: DWT CYCCNT at the core clock. PIC32: CP0 Count
 * at half the core clock (same counters and clock macros as platform/trace).
 * The counter wraps after 2^32 cycles (about 25 s at 168 MHz), so now_ms must
 * be called at least that often: net_poll() does so. During long Delay_ms()
 * calls without net_poll() the clock would lose time.
 */

#ifndef _NET_CLOCK_H
#define _NET_CLOCK_H

#include <stdint.h>

#if defined( __arm__ ) || defined( __thumb__ )
#include "core_header.h"
#endif

// Core clock in kHz: ARM core headers define FOSC_KHZ_VALUE, the PIC32 core
// library defines OSC_KHZ on the command line.
#if defined( FOSC_KHZ_VALUE )
#define NET_CLOCK_CORE_KHZ ( ( uint32_t )( FOSC_KHZ_VALUE ) )
#elif defined( OSC_KHZ )
#define NET_CLOCK_CORE_KHZ ( ( uint32_t )( OSC_KHZ ) )
#else
#error "net_clock.h: the setup gives no core clock (FOSC_KHZ_VALUE / OSC_KHZ)"
#endif

#if defined( __arm__ ) || defined( __thumb__ )

#if !( defined( __ARM_ARCH_7M__ ) || defined( __ARM_ARCH_7EM__ ) || defined( __ARM_ARCH_8M_MAIN__ ) || \
       defined( __ARM_ARCH_8_1M_MAIN__ ) )
#error "net_clock.h: Cortex-M0/M0+/M23 have no cycle counter; provide now_ms from a timer"
#endif

#define NET_CLOCK_DEMCR     ( *( volatile uint32_t * )0xE000EDFCUL )
#define NET_CLOCK_DWT_CTRL  ( *( volatile uint32_t * )0xE0001000UL )
#define NET_CLOCK_DWT_CYCNT ( *( volatile uint32_t * )0xE0001004UL )
#define NET_CLOCK_DWT_LAR   ( *( volatile uint32_t * )0xE0001FB0UL )
#define NET_CLOCK_TICKS_PER_MS NET_CLOCK_CORE_KHZ

static inline uint32_t net_clock_counter( void )
{
    return NET_CLOCK_DWT_CYCNT;
}

static inline void net_clock_counter_start( void )
{
    NET_CLOCK_DEMCR |= ( 1UL << 24 );          // TRCENA
    #ifdef __cortex_m7__
    NET_CLOCK_DWT_LAR = 0xC5ACCE55UL;          // Cortex-M7 keeps the DWT locked until this key
    #endif
    NET_CLOCK_DWT_CTRL |= 1UL;                 // CYCCNTENA
}

#elif defined( __mips__ ) || defined( __XC32 )

#define NET_CLOCK_TICKS_PER_MS ( NET_CLOCK_CORE_KHZ / 2UL )   // CP0 Count: every other core clock

static inline uint32_t net_clock_counter( void )
{
    uint32_t count;
    __asm__ volatile ( "mfc0 %0, $9, 0" : "=r" ( count ) );
    return count;
}

static inline void net_clock_counter_start( void )
{
    // CP0 Count runs from reset.
}

#else
#error "net_clock.h: unsupported core"
#endif

static uint32_t net_clock_last;
static uint32_t net_clock_ticks;   // ticks not yet counted as a millisecond
static uint32_t net_clock_now;

/*! @brief Start the cycle counter. Call once before net_init(). */
static inline void net_clock_init( void )
{
    net_clock_counter_start();
    net_clock_last = net_clock_counter();
}

/*! @brief Milliseconds since net_clock_init(); use as net_config_t.now_ms. */
static uint32_t net_clock_ms( void )
{
    uint32_t now = net_clock_counter();
    net_clock_ticks += now - net_clock_last;   // unsigned: correct across a wrap
    net_clock_last = now;
    net_clock_now += net_clock_ticks / NET_CLOCK_TICKS_PER_MS;
    net_clock_ticks %= NET_CLOCK_TICKS_PER_MS;
    return net_clock_now;
}

#endif // _NET_CLOCK_H
// ------------------------------------------------------------------------- END
