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
 * @file  trace.h
 * @brief Firmware trace: driver activity recorded for the NECTO Studio timeline.
 *
 * @details Linking this library replaces the empty trace hooks of the drivers (drv_trace.h).
 * I2C transfers and GPIO pin changes are then written as binary records to a RAM buffer.
 * When the buffer is full, the firmware stops in #traceBuffFullBreak; the debugger reads the
 * buffer, empties it and lets the firmware continue. Without a debugger the records are
 * dropped and counted.
 *
 * Applications built with flattened drivers (FLATTEN_ME_LEVEL_HIGH) also need the
 * MIKROSDK_TRACE compile definition, for the GPIO macros.
 */

#ifndef _TRACE_H_
#define _TRACE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/*!
 * @addtogroup platform Platform
 * @{
 */

/*!
 * @addtogroup trace Firmware Trace
 * @brief Firmware trace library.
 * @{
 */

/**
 * @brief Default trace buffer size in bytes.
 */
#define TRACE_BUFF_SIZE 512U

/**
 * @brief Gives the trace a buffer of another size.
 * @details Each full buffer stops the program once while the debugger reads it, so a larger
 * buffer means fewer stops, at the cost of RAM. Use once, at file scope in the application:
 * @code
 * TRACE_BUFFER( 4096 );
 * @endcode
 * Sizes below 128 bytes leave the trace off.
 */
#define TRACE_BUFFER( size ) \
    volatile uint8_t __traceBuffer[ size ]; \
    const volatile uint16_t __traceBufferSize = ( size )

/**
 * @brief Default automatic flush interval, in milliseconds of program time.
 */
#define TRACE_FLUSH_INTERVAL_MS 500U

/**
 * @brief Start recording.
 * @details Call early in main. Transfers before the call are not recorded; the pins of
 * drivers initialized before it are still known.
 */
void trace_init( void );

/**
 * @brief Hand the recorded data to the debugger now.
 * @details Records otherwise wait for the automatic flush (#trace_set_flush_interval), a full
 * buffer, or a stop of the program. Each call stops the program while the debugger reads
 * the buffer: calling it in a fast loop slows the program down a lot.
 */
void trace_flush( void );

/**
 * @brief Hand the records to the debugger at least this often.
 * @details Counted in program time: the time base stops while the debugger holds the program.
 * Each flush stops the program for as long as the debugger needs to read the buffer (about
 * 0.3 s over CODEGRIP), so a short interval makes the timeline more live and the program
 * slower. 0 flushes only when the buffer is full. Has no effect without a timer. Call it
 * after #trace_init, which sets the default.
 * @param[in] ms Interval in milliseconds, #TRACE_FLUSH_INTERVAL_MS by default.
 */
void trace_set_flush_interval( uint32_t ms );

/**
 * @brief Record a named value.
 * @param[in] name Value name: a string literal, it is kept as a pointer.
 * @param[in] value Value.
 */
void trace_value( const char *name, float value );

/**
 * @brief Time base of the trace, in ticks.
 * @details Cortex-M3 and newer: the DWT cycle counter. Other cores: a record counter, which
 * keeps the order but not the timing. Weak: an application can supply its own free-running
 * timer together with #trace_tick_hz.
 */
uint32_t trace_ticks( void );

/**
 * @brief Frequency of #trace_ticks, 0 when it counts records and not time.
 */
uint32_t trace_tick_hz( void );

/**
 * @brief The debugger breaks here to read the buffer.
 */
void traceBuffFullBreak( void );

/*! @} */ // trace
/*! @} */ // platform

#ifdef __cplusplus
}
#endif

#endif // _TRACE_H_
// ------------------------------------------------------------------------- END
