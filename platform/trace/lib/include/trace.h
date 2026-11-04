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
 * I2C, SPI, UART and 1-Wire transfers, ADC reads and GPIO pin changes are then written as
 * binary records to a RAM buffer.
 * When the buffer is full, the firmware stops in #traceBuffFullBreak; the debugger reads the
 * buffer, empties it and lets the firmware continue. Without a debugger the records are
 * dropped and counted.
 *
 * A pin written very fast (a display strobe, a bit-banged bus) would fill the buffer with its
 * levels and stop the program over and over. After 16 writes in a row less than 20 us apart,
 * the writes of that pin are only counted until it pauses: the timeline shows one burst with
 * the number of level changes. A bus the same way: after 16 transfers in a row, each starting
 * less than 100 us after the one before (a display filled pixel by pixel), its transfers are
 * counted with their bytes until it pauses, and the timeline shows one burst. Both need a time
 * base (#trace_tick_hz).
 *
 * Fault injection: while debugging, NECTO Studio can make an I2C device stop answering, hold
 * an SPI bus's MISO at a byte, an input pin at a level or an analog input at a value, and take
 * the devices off a 1-Wire bus, to show how the application copes. The debugger writes the
 * faults while the program is stopped, at the latest when it next hands over the trace; the
 * drivers then fail or change the calls they apply to, and the timeline marks those calls.
 * Only calls through the drivers see the faults.
 *
 * Linking MikroSDK.Trace is all an application needs: the library is always linked in
 * (not only when something calls it), it starts with the first recorded event, and it defines
 * MIKROSDK_TRACE for the application, which flattened GPIO macros (FLATTEN_ME_LEVEL_HIGH) need.
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
 * @details Optional: the first recorded event starts the trace by itself, and linking
 * MikroSDK.Trace is all an application needs. Call it to start the time base at a known point;
 * later calls do nothing.
 *
 * @b Example
 * @code
 *   // Start the trace time base before the first driver is used.
 *   trace_init();
 * @endcode
 */
void trace_init( void );

/**
 * @brief Hand the recorded data to the debugger now.
 * @details Records otherwise wait for the automatic flush (#trace_set_flush_interval), a full
 * buffer, or a stop of the program. Each call stops the program while the debugger reads
 * the buffer: calling it in a fast loop slows the program down a lot.
 *
 * @b Example
 * @code
 *   // Show the records of one measurement right away.
 *   i2c_master_write_then_read( &i2c_master, &reg, 1, data_buf, 6 );
 *   trace_flush();
 * @endcode
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
 *
 * @b Example
 * @code
 *   trace_init();
 *   // Hand the records over every 2 seconds: fewer stops, a less live timeline.
 *   trace_set_flush_interval( 2000 );
 * @endcode
 */
void trace_set_flush_interval( uint32_t ms );

/**
 * @brief Record a named value.
 * @param[in] name Value name: a string literal, it is kept as a pointer.
 * @param[in] value Value.
 *
 * @b Example
 * @code
 *   // Show the measured temperature on the timeline.
 *   float temperature = 23.5;
 *   trace_value( "temperature", temperature );
 * @endcode
 */
void trace_value( const char *name, float value );

/**
 * @brief Time base of the trace, in ticks.
 * @details Cortex-M3 and newer: the DWT cycle counter. Other cores: a record counter, which
 * keeps the order but not the timing. Weak: an application can supply its own free-running
 * timer together with #trace_tick_hz.
 * @return Current time, in ticks.
 *
 * @b Example
 * @code
 *   // Application time base: a free-running 32-bit timer, here STM32 TIM2
 *   // already set up to count at 1 MHz.
 *   uint32_t trace_ticks( void )
 *   {
 *       return TIM2->CNT;
 *   }
 *
 *   uint32_t trace_tick_hz( void )
 *   {
 *       return 1000000;
 *   }
 * @endcode
 */
uint32_t trace_ticks( void );

/**
 * @brief Frequency of #trace_ticks.
 * @details Weak, see #trace_ticks.
 * @return Ticks per second, 0 when #trace_ticks counts records and not time.
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
