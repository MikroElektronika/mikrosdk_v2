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
 * @file  trace.c
 * @brief Firmware trace implementation.
 *
 * @details Record format and debugger contract: docs/design/firmware_trace_v1.md in the NECTO
 * Studio repository. The names of __traceBuffer, __traceLen, __traceDropped and
 * traceBuffFullBreak are read by the debugger and must not change.
 */

#include "trace.h"
#include "drv_trace.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "drv_uart.h"
#include "core_header.h"
#include <stdbool.h>
#include <string.h>

#if !DRV_TRACE_ENABLED
#error "The firmware trace needs a toolchain with weak symbols."
#endif

#define TRACE_FORMAT_VERSION (1)
#define TRACE_MAX_LANES (32)
// The UART driver hands uart_println() text over in a buffer of this size (drv_uart.c).
#define TRACE_MAX_DATA (16)
#define TRACE_MAX_NAME (16)
#define TRACE_MAX_RECORD (52)
#define TRACE_LANE_NONE (0xFF)
#define TRACE_LEVEL_UNKNOWN (0xFF)

// Sizes of the records written after a loss: META and DROPPED.
#define TRACE_META_SIZE (13)
#define TRACE_DROPPED_SIZE (10)

// META, DROPPED, the largest LANE_DEF and the largest event must fit after a flush.
#define TRACE_MIN_BUFF_SIZE (128)

// A pin written this many times in a row, each write within TRACE_BURST_GAP_US of the one
// before, is in a burst (a display strobe, a bit-banged bus): its writes are counted, not
// recorded, until a pause longer than the gap. One BURST record then stands for all of them.
#define TRACE_BURST_WRITES (16)
#define TRACE_BURST_GAP_US (20)

typedef enum
{
    TRACE_RECORD_META = 0x01,
    TRACE_RECORD_LANE_DEF = 0x02,
    TRACE_RECORD_LEVEL = 0x10,
    TRACE_RECORD_BURST = 0x11,
    TRACE_RECORD_I2C = 0x20,
    TRACE_RECORD_SPI = 0x21,
    TRACE_RECORD_UART_TX = 0x22,
    TRACE_RECORD_UART_RX = 0x23,
    TRACE_RECORD_VALUE = 0x30,
    TRACE_RECORD_DROPPED = 0x3F
} trace_record_type_t;

typedef enum
{
    TRACE_LANE_GPIO_OUT = 1,
    TRACE_LANE_GPIO_IN = 2,
    TRACE_LANE_I2C = 3,
    TRACE_LANE_SPI = 4,
    TRACE_LANE_UART = 5,
    TRACE_LANE_VALUE = 6
} trace_lane_kind_t;

typedef struct
{
    const void *key;    // driver object, or the name of a value
    const char *name;
    pin_name_t pins[ 3 ];
    uint8_t pin_count;
    uint8_t kind;
    bool defined;       // LANE_DEF written since the last loss
    uint8_t level;      // last level written or read
    // Burst detection, for pins (TRACE_BURST_WRITES).
    bool written;           // last_write is valid
    bool bursting;
    uint8_t fast_writes;    // writes in a row within the gap
    uint32_t last_write;
    uint32_t burst_start;
    uint32_t burst_changes;
} trace_lane_t;

typedef struct
{
    uint8_t data[ TRACE_MAX_RECORD ];
    uint8_t len;
} trace_record_t;

// Tells the drivers that their hooks are here (drv_trace.h).
const volatile uint8_t drv_trace_present = 1;

// Read by the debugger, see the file comment.
// Weak: an application with TRACE_BUFFER( size ) replaces both. The size is read at run time
// (volatile), never folded into the code, so that the replacement takes effect.
__attribute__((weak)) volatile uint8_t __traceBuffer[ TRACE_BUFF_SIZE ];
__attribute__((weak)) const volatile uint16_t __traceBufferSize = TRACE_BUFF_SIZE;
volatile uint16_t __traceLen = 0;
volatile uint32_t __traceDropped = 0;

static trace_lane_t trace_lanes[ TRACE_MAX_LANES ];
static uint8_t trace_lane_count = 0;
static uint16_t trace_records = 0;    // records in the buffer, counted when they are lost
static uint32_t trace_lost = 0;       // lost records not reported yet
static uint32_t trace_hz = 0;
static uint32_t trace_sequence = 0;
static bool trace_started = false;
static bool trace_resync = false;    // META (and DROPPED) needed before the next record
static uint32_t trace_flush_ticks = 0;    // automatic flush interval, 0: only when full
static uint32_t trace_last_flush = 0;
static uint32_t trace_burst_gap = 0;      // TRACE_BURST_GAP_US in ticks, 0: no bursts
static uint8_t trace_bursts = 0;          // lanes in a burst

// --------------------------------------------------------------- Time base

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_8M_MAIN__)
#define TRACE_HAS_CYCCNT 1
#define TRACE_DEMCR (*(volatile uint32_t *)0xE000EDFCUL)
#define TRACE_DEMCR_TRCENA (1UL << 24)
#define TRACE_DWT_CTRL (*(volatile uint32_t *)0xE0001000UL)
#define TRACE_DWT_CTRL_CYCCNTENA (1UL << 0)
#define TRACE_DWT_CYCCNT (*(volatile uint32_t *)0xE0001004UL)
// Cortex-M7 keeps the DWT locked until this key is written; other cores have no such register.
#define TRACE_DWT_LAR (*(volatile uint32_t *)0xE0001FB0UL)
#define TRACE_DWT_LAR_KEY (0xC5ACCE55UL)

static bool trace_cyccnt_running = false;

static void trace_cyccnt_start( void )
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
    trace_cyccnt_running = ( TRACE_DWT_CYCCNT != first );
}
#else
#define TRACE_HAS_CYCCNT 0
#endif

__attribute__((weak)) uint32_t trace_tick_hz( void )
{
    #if TRACE_HAS_CYCCNT && defined(FOSC_KHZ_VALUE)
    if ( trace_cyccnt_running )
    {
        return (uint32_t)FOSC_KHZ_VALUE * 1000UL;
    }
    #endif
    return 0;
}

__attribute__((weak)) uint32_t trace_ticks( void )
{
    #if TRACE_HAS_CYCCNT
    if ( trace_cyccnt_running )
    {
        return TRACE_DWT_CYCCNT;
    }
    #endif
    return trace_sequence++;
}

// --------------------------------------------------------------- Locking

// Hooks run in interrupts too (UART callbacks). The previous state is restored, so that a
// hook called inside a critical section of the application does not enable interrupts.
static inline uint32_t trace_lock( void )
{
    uint32_t primask;
    __asm volatile ( "mrs %0, primask\n\tcpsid i" : "=r" ( primask ) :: "memory" );
    return primask;
}

static inline void trace_unlock( uint32_t primask )
{
    __asm volatile ( "msr primask, %0" :: "r" ( primask ) : "memory" );
}

// --------------------------------------------------------------- Records

static void record_u8( trace_record_t *record, uint8_t value )
{
    record->data[ record->len++ ] = value;
}

static void record_u16( trace_record_t *record, uint16_t value )
{
    record_u8( record, (uint8_t)value );
    record_u8( record, (uint8_t)( value >> 8 ) );
}

static void record_u32( trace_record_t *record, uint32_t value )
{
    record_u16( record, (uint16_t)value );
    record_u16( record, (uint16_t)( value >> 16 ) );
}

static void record_bytes( trace_record_t *record, const uint8_t *bytes, uint8_t count )
{
    if ( !count )
    {
        return;
    }
    memcpy( &record->data[ record->len ], bytes, count );
    record->len += count;
}

static void record_header( trace_record_t *record, uint8_t type, uint8_t lane, uint32_t ticks )
{
    record->len = 0;
    record_u8( record, type );
    record_u8( record, lane );
    record_u32( record, ticks );
}

static uint16_t clamp_u16( size_t value )
{
    return ( value > 0xFFFFU ) ? 0xFFFFU : (uint16_t)value;
}

static uint8_t kept_bytes( const uint8_t *buffer, size_t len )
{
    if ( !buffer )
    {
        return 0;
    }
    return ( len > TRACE_MAX_DATA ) ? TRACE_MAX_DATA : (uint8_t)len;
}

// --------------------------------------------------------------- Buffer

void __attribute__((noinline, used)) traceBuffFullBreak( void )
{
    __asm volatile ( "nop" );
}

static void trace_flush_locked( void )
{
    if ( 0 == __traceLen )
    {
        return;
    }

    traceBuffFullBreak();
    trace_last_flush = trace_ticks();

    if ( __traceLen )
    {
        // Nobody read the buffer: no debugger, or one that does not know the trace.
        trace_lost += trace_records;
        __traceDropped += trace_records;
        __traceLen = 0;
        trace_resync = true;
        for ( uint8_t i = 0; i < trace_lane_count; i++ )
        {
            trace_lanes[ i ].defined = false;
        }
    }
    trace_records = 0;
}

static void trace_commit( const trace_record_t *record )
{
    uint16_t pos = __traceLen;
    memcpy( (uint8_t *)&__traceBuffer[ pos ], record->data, record->len );

    // The debugger may have emptied the buffer while the record was copied (a pause or a
    // breakpoint in between). The record then belongs at the start.
    if ( __traceLen != pos )
    {
        memmove( (uint8_t *)__traceBuffer, (uint8_t *)&__traceBuffer[ pos ], record->len );
        __traceLen = record->len;
        trace_records = 1;
    }
    else
    {
        __traceLen = pos + record->len;
        trace_records++;
    }
}

static uint8_t name_length( const char *name )
{
    uint8_t len = 0;
    while ( name && name[ len ] && ( len < TRACE_MAX_NAME ) )
    {
        len++;
    }
    return len;
}

static uint8_t lane_def_size( const trace_lane_t *lane )
{
    uint8_t name_len = name_length( lane->name );
    return 6 + 2 + 4 * lane->pin_count + 1 + name_len;
}

static void trace_write_lane_def( uint8_t id, trace_lane_t *lane )
{
    trace_record_t record;
    uint8_t name_len = name_length( lane->name );

    record_header( &record, TRACE_RECORD_LANE_DEF, id, 0 );
    record_u8( &record, lane->kind );
    record_u8( &record, lane->pin_count );
    for ( uint8_t i = 0; i < lane->pin_count; i++ )
    {
        record_u32( &record, (uint32_t)lane->pins[ i ] );
    }
    record_u8( &record, name_len );
    record_bytes( &record, (const uint8_t *)lane->name, name_len );
    trace_commit( &record );
    lane->defined = true;
}

static void trace_write_resync( void )
{
    trace_record_t record;

    record_header( &record, TRACE_RECORD_META, TRACE_LANE_NONE, 0 );
    record_u8( &record, TRACE_FORMAT_VERSION );
    record_u32( &record, trace_hz );
    record_u16( &record, __traceBufferSize );
    trace_commit( &record );

    if ( trace_lost )
    {
        record_header( &record, TRACE_RECORD_DROPPED, TRACE_LANE_NONE, 0 );
        record_u32( &record, trace_lost );
        trace_commit( &record );
        trace_lost = 0;
    }
    trace_resync = false;
}

// Writes an event record with what it depends on: META after a loss, the lane definition.
// Space for all of it is made first, so that a flush cannot separate them.
static void trace_write( uint8_t id, trace_lane_t *lane, const trace_record_t *event )
{
    for ( uint8_t attempt = 0; attempt < 2; attempt++ )
    {
        uint16_t needed = event->len;
        if ( trace_resync )
        {
            needed += TRACE_META_SIZE + ( trace_lost ? TRACE_DROPPED_SIZE : 0 );
        }
        if ( lane && !lane->defined )
        {
            needed += lane_def_size( lane );
        }
        if ( ( (uint32_t)__traceLen + needed ) <= __traceBufferSize )
        {
            break;
        }
        // A loss here sets trace_resync and clears the lane definitions: recompute.
        trace_flush_locked();
    }

    if ( trace_resync )
    {
        trace_write_resync();
    }
    if ( lane && !lane->defined )
    {
        trace_write_lane_def( id, lane );
    }
    trace_commit( event );
}

// Ends the burst of a lane. The record is stamped now, so that record times never go back
// (the debugger takes a step back as a wrap of the time base); it says how long ago the burst
// started and ended.
static void trace_write_burst( uint8_t id, trace_lane_t *lane, uint32_t now )
{
    trace_record_t record;

    record_header( &record, TRACE_RECORD_BURST, id, now );
    record_u32( &record, lane->last_write - lane->burst_start );
    record_u32( &record, now - lane->last_write );
    record_u32( &record, lane->burst_changes );
    record_u8( &record, lane->level );
    trace_write( id, lane, &record );
    lane->bursting = false;
    trace_bursts--;
}

// Ends the bursts that paused for longer than the gap by now, or all of them.
static void trace_end_bursts( uint32_t now, bool all )
{
    for ( uint8_t i = 0; trace_bursts && ( i < trace_lane_count ); i++ )
    {
        trace_lane_t *lane = &trace_lanes[ i ];
        // Signed: an event stamped at its start (a transfer) can be older than the last write.
        if ( lane->bursting &&
             ( all || ( (int32_t)( now - lane->last_write ) > (int32_t)trace_burst_gap ) ) )
        {
            trace_write_burst( i, lane, now );
        }
    }
}

// Records reach the debugger at least every interval of program time, not only when the
// buffer is full: the timeline stays live, and the time base never wraps unseen.
static void trace_auto_flush( void )
{
    if ( !trace_flush_ticks )
    {
        return;
    }
    uint32_t now = trace_ticks();
    if ( ( now - trace_last_flush ) >= trace_flush_ticks )
    {
        // A burst still going on is cut here, so that the timeline shows it.
        trace_end_bursts( now, true );
        trace_flush_locked();
    }
}

static uint32_t record_ticks( const trace_record_t *record )
{
    return (uint32_t)record->data[ 2 ] | ( (uint32_t)record->data[ 3 ] << 8 ) |
           ( (uint32_t)record->data[ 4 ] << 16 ) | ( (uint32_t)record->data[ 5 ] << 24 );
}

static void trace_emit( uint8_t id, trace_lane_t *lane, const trace_record_t *event )
{
    // A burst that ended goes first: the timeline then shows it before this event.
    if ( trace_bursts )
    {
        trace_end_bursts( record_ticks( event ), false );
    }
    trace_write( id, lane, event );
    trace_auto_flush();
}

// --------------------------------------------------------------- Lanes

static trace_lane_t *trace_lane( const void *key, uint8_t kind, uint8_t *id )
{
    for ( uint8_t i = 0; i < trace_lane_count; i++ )
    {
        if ( trace_lanes[ i ].key == key )
        {
            *id = i;
            return &trace_lanes[ i ];
        }
    }

    if ( trace_lane_count >= TRACE_MAX_LANES )
    {
        *id = TRACE_LANE_NONE;
        return NULL;
    }

    trace_lane_t *lane = &trace_lanes[ trace_lane_count ];
    memset( lane, 0, sizeof( *lane ) );
    lane->key = key;
    lane->kind = kind;
    lane->level = TRACE_LEVEL_UNKNOWN;
    *id = trace_lane_count++;
    return lane;
}

// --------------------------------------------------------------- Public API

static void trace_set_flush_interval_locked( uint32_t ms )
{
    // Needs a time base; a record counter gives none.
    trace_flush_ticks = trace_hz ? (uint32_t)( ( (uint64_t)trace_hz * ms ) / 1000U ) : 0;
}

void trace_set_flush_interval( uint32_t ms )
{
    uint32_t primask = trace_lock();
    trace_set_flush_interval_locked( ms );
    trace_unlock( primask );
}

void trace_init( void )
{
    if ( __traceBufferSize < TRACE_MIN_BUFF_SIZE )
    {
        return;
    }

    uint32_t primask = trace_lock();
    // Started already, by an earlier call or by the first recorded event: restarting would
    // reset the time base under the records already made.
    if ( trace_started )
    {
        trace_unlock( primask );
        return;
    }
    #if TRACE_HAS_CYCCNT
    trace_cyccnt_start();
    #endif
    trace_hz = trace_tick_hz();
    // Bursts need a time base too.
    trace_burst_gap = (uint32_t)( ( (uint64_t)trace_hz * TRACE_BURST_GAP_US ) / 1000000U );
    trace_set_flush_interval_locked( TRACE_FLUSH_INTERVAL_MS );
    trace_last_flush = trace_ticks();
    trace_started = true;
    trace_resync = true;
    trace_unlock( primask );
}

// The first recorded event starts the trace: linking the library is all an application needs.
static bool trace_ensure_started( void )
{
    if ( !trace_started )
    {
        trace_init();
    }
    return trace_started;
}

void trace_flush( void )
{
    uint32_t primask = trace_lock();
    trace_end_bursts( trace_ticks(), true );
    trace_flush_locked();
    trace_unlock( primask );
}

void trace_value( const char *name, float value )
{
    if ( !name || !trace_ensure_started() )
    {
        return;
    }

    uint32_t primask = trace_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( name, TRACE_LANE_VALUE, &id );
    if ( lane )
    {
        uint32_t raw;
        trace_record_t record;

        lane->name = name;
        memcpy( &raw, &value, sizeof( raw ) );
        record_header( &record, TRACE_RECORD_VALUE, id, trace_ticks() );
        record_u32( &record, raw );
        trace_emit( id, lane, &record );
    }
    trace_unlock( primask );
}

// --------------------------------------------------------------- Driver hooks

// SPI and I2C records share their tail: op, result, duration, lengths, kept bytes.
static void record_transfer( trace_record_t *record, uint8_t op, const uint8_t *write_buf,
                             size_t write_len, const uint8_t *read_buf, size_t read_len,
                             err_t result, uint32_t duration )
{
    // Data read by a failed transfer is not valid.
    uint8_t write_kept = kept_bytes( write_buf, write_len );
    uint8_t read_kept = result ? 0 : kept_bytes( read_buf, read_len );

    record_u8( record, op );
    record_u8( record, result ? 1 : 0 );
    record_u32( record, duration );
    record_u16( record, clamp_u16( write_len ) );
    record_u16( record, clamp_u16( read_len ) );
    record_u8( record, write_kept );
    record_u8( record, read_kept );
    record_bytes( record, write_buf, write_kept );
    record_bytes( record, read_buf, read_kept );
}


uint32_t drv_trace_now( void )
{
    return trace_ensure_started() ? trace_ticks() : 0;
}

void drv_trace_i2c( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                    const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start )
{
    if ( !trace_ensure_started() )
    {
        return;
    }

    // The hook runs right after the transfer: now is its end.
    uint32_t duration = trace_ticks() - start;
    const i2c_master_t *i2c = (const i2c_master_t *)obj;
    uint32_t primask = trace_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_I2C, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = i2c->config.scl;
        lane->pins[ 1 ] = i2c->config.sda;
        lane->pin_count = 2;
    }

    trace_record_t record;
    record_header( &record, TRACE_RECORD_I2C, id, start );
    record_u8( &record, i2c->config.addr );
    record_transfer( &record, op, write_buf, write_len, read_buf, read_len, result, duration );
    trace_emit( id, lane, &record );
    trace_unlock( primask );
}

void drv_trace_spi( const void *obj, uint8_t op, const uint8_t *write_buf, size_t write_len,
                    const uint8_t *read_buf, size_t read_len, err_t result, uint32_t start )
{
    if ( !trace_ensure_started() )
    {
        return;
    }

    uint32_t duration = trace_ticks() - start;
    const spi_master_t *spi = (const spi_master_t *)obj;
    uint32_t primask = trace_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_SPI, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = spi->config.sck;
        lane->pins[ 1 ] = spi->config.miso;
        lane->pins[ 2 ] = spi->config.mosi;
        lane->pin_count = 3;
    }

    trace_record_t record;
    record_header( &record, TRACE_RECORD_SPI, id, start );
    record_transfer( &record, op, write_buf, write_len, read_buf, read_len, result, duration );
    trace_emit( id, lane, &record );
    trace_unlock( primask );
}

void drv_trace_uart( const void *obj, uint8_t is_tx, const uint8_t *buf, size_t len, uint32_t start )
{
    if ( !trace_ensure_started() )
    {
        return;
    }

    uint32_t duration = trace_ticks() - start;
    const uart_t *uart = (const uart_t *)obj;
    uint32_t primask = trace_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_UART, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = uart->config.tx_pin;
        lane->pins[ 1 ] = uart->config.rx_pin;
        lane->pin_count = 2;
    }

    uint8_t kept = kept_bytes( buf, len );
    trace_record_t record;
    record_header( &record, is_tx ? TRACE_RECORD_UART_TX : TRACE_RECORD_UART_RX, id, start );
    record_u32( &record, duration );
    record_u16( &record, clamp_u16( len ) );
    record_u8( &record, kept );
    record_bytes( &record, buf, kept );
    trace_emit( id, lane, &record );
    trace_unlock( primask );
}

void drv_trace_gpio_init( const void *obj, pin_name_t pin, uint8_t is_output )
{
    // Kept before trace_init too: drivers are often initialized first.
    uint32_t primask = trace_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, is_output ? TRACE_LANE_GPIO_OUT : TRACE_LANE_GPIO_IN, &id );
    if ( lane )
    {
        // A driver object used again for another pin: its burst belongs to the old one.
        if ( lane->bursting )
        {
            trace_write_burst( id, lane, trace_ticks() );
        }
        lane->kind = is_output ? TRACE_LANE_GPIO_OUT : TRACE_LANE_GPIO_IN;
        lane->pins[ 0 ] = pin;
        lane->pin_count = 1;
        lane->level = TRACE_LEVEL_UNKNOWN;
        lane->defined = false;
        lane->written = false;
        lane->fast_writes = 0;
    }
    trace_unlock( primask );
}

// Counts a write into the burst of its lane, starting or ending the burst. True when the write
// is counted and needs no record of its own.
static bool trace_burst_write( uint8_t id, trace_lane_t *lane, uint8_t level, uint32_t now )
{
    if ( !trace_burst_gap )
    {
        return false;
    }

    bool fast = lane->written && ( ( now - lane->last_write ) <= trace_burst_gap );
    if ( lane->bursting && !fast )
    {
        trace_write_burst( id, lane, now );
    }
    lane->written = true;
    lane->last_write = now;
    if ( !fast )
    {
        lane->fast_writes = 0;
        return false;
    }

    if ( lane->fast_writes < TRACE_BURST_WRITES )
    {
        lane->fast_writes++;
    }
    if ( !lane->bursting )
    {
        if ( lane->fast_writes < TRACE_BURST_WRITES )
        {
            return false;
        }
        lane->bursting = true;
        lane->burst_start = now;
        lane->burst_changes = 0;
        trace_bursts++;
    }
    if ( lane->level != level )
    {
        lane->level = level;
        lane->burst_changes++;
    }
    return true;
}

static void trace_level( const void *obj, uint8_t kind, uint8_t level, bool changes_only )
{
    uint32_t primask = trace_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, kind, &id );
    uint32_t now = trace_ticks();
    level = level ? 1 : 0;
    if ( lane && changes_only && ( lane->level == level ) )
    {
        trace_unlock( primask );
        return;
    }

    if ( lane && trace_burst_write( id, lane, level, now ) )
    {
        trace_auto_flush();
    }
    else
    {
        trace_record_t record;
        if ( lane )
        {
            lane->level = level;
        }
        record_header( &record, TRACE_RECORD_LEVEL, id, now );
        record_u8( &record, level );
        trace_emit( id, lane, &record );
    }
    trace_unlock( primask );
}

void drv_trace_gpio_out( const void *obj, uint8_t level )
{
    if ( trace_ensure_started() )
    {
        trace_level( obj, TRACE_LANE_GPIO_OUT, level, false );
    }
}

uint8_t drv_trace_gpio_in( const void *obj, uint8_t level )
{
    // Polling loops read the same level again and again: only changes are recorded.
    if ( trace_ensure_started() )
    {
        trace_level( obj, TRACE_LANE_GPIO_IN, level, true );
    }
    return level;
}

// ------------------------------------------------------------------------- END
