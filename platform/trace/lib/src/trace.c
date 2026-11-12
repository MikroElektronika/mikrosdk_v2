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
 * Studio repository. The names of __traceBuffer, __traceLen, __traceDropped, __traceFaults and
 * traceBuffFullBreak are read or written by the debugger and must not change.
 */

#include "trace.h"
#include "drv_trace.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "drv_uart.h"
#include "trace_port.h"
#include <stdbool.h>
#include <string.h>

#if !DRV_TRACE_ENABLED
#error "The firmware trace needs a toolchain with weak symbols."
#endif

// ------------------------------------------------------------- PRIVATE MACROS

// 2: ONE_WIRE records and lanes. 3: TRACE_RECORD_INJECTED. 4: BUS_BURST records. 5: the
// bus rate at the end of LANE_DEF.
#define TRACE_FORMAT_VERSION (5)
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

// The same for a bus: this many transfers in a row, each starting within TRACE_BUS_BURST_GAP_US
// of the one before (a display filled pixel by pixel), and the transfers after them are counted,
// not recorded, until a pause: one BUS_BURST record stands for them.
#define TRACE_BUS_BURST_TRANSFERS (16)
#define TRACE_BUS_BURST_GAP_US (100)

// Chip select pins seen by spi_master_select_device(). Their lanes are keyed by the entries,
// as other lanes are by their driver object.
#define TRACE_MAX_CS (8)

// Faults the debugger can inject at once.
#define TRACE_MAX_FAULTS (8)

// -------------------------------------------------------------- PRIVATE TYPES

typedef enum
{
    TRACE_RECORD_META = 0x01,
    TRACE_RECORD_LANE_DEF = 0x02,
    TRACE_RECORD_LEVEL = 0x10,
    TRACE_RECORD_BURST = 0x11,
    TRACE_RECORD_BUS_BURST = 0x12,
    TRACE_RECORD_I2C = 0x20,
    TRACE_RECORD_SPI = 0x21,
    TRACE_RECORD_UART_TX = 0x22,
    TRACE_RECORD_UART_RX = 0x23,
    TRACE_RECORD_ONE_WIRE = 0x24,
    TRACE_RECORD_VALUE = 0x30,
    TRACE_RECORD_DROPPED = 0x3F,
    // Set in the type of an event that an injected fault changed.
    TRACE_RECORD_INJECTED = 0x80
} trace_record_type_t;

// Faults the debugger injects; the values are part of the debugger contract.
typedef enum
{
    TRACE_FAULT_NONE = 0,
    TRACE_FAULT_I2C_NO_ANSWER = 1,      // pin: SCL; address: the device that stops answering
    TRACE_FAULT_SPI_MISO = 2,           // pin: SCK; value: the byte every read gives
    TRACE_FAULT_GPIO_IN = 3,            // pin: the input; value: the level it is held at
    TRACE_FAULT_ADC = 4,                // pin: the input; value: the raw count, a float
    TRACE_FAULT_ADC_VOLTAGE = 5,        // pin: the input; value: the volts, a float
    TRACE_FAULT_ONE_WIRE_NO_DEVICE = 6  // pin: the data pin
} trace_fault_kind_t;

// One entry of __traceFaults, 12 bytes, little-endian on the targets.
typedef struct
{
    uint8_t kind;    // trace_fault_kind_t
    uint8_t address;
    uint16_t reserved;
    uint32_t pin;    // pin_name_t
    uint32_t value;
} trace_fault_t;

typedef enum
{
    TRACE_LANE_GPIO_OUT = 1,
    TRACE_LANE_GPIO_IN = 2,
    TRACE_LANE_I2C = 3,
    TRACE_LANE_SPI = 4,
    TRACE_LANE_UART = 5,
    TRACE_LANE_VALUE = 6,
    TRACE_LANE_ONE_WIRE = 7
} trace_lane_kind_t;

typedef struct
{
    const void *key;    // driver object, or the name of a value
    const char *name;
    pin_name_t pins[ 4 ];    // SPI: SCK, MISO, MOSI and the chip select, once known
    uint8_t pin_count;
    uint8_t kind;
    uint32_t rate;      // a bus's bit rate in Hz (I2C, SPI clock, UART baud), 0 when unknown
    bool defined;       // LANE_DEF written since the last loss
    uint8_t level;      // last level written or read
    uint8_t injected;   // TRACE_RECORD_INJECTED when a fault gave that level
    // Burst detection, for pins (TRACE_BURST_WRITES).
    bool written;           // last_write is valid
    bool bursting;
    uint8_t fast_writes;    // writes in a row within the gap
    uint32_t last_write;
    uint32_t burst_start;
    uint32_t burst_changes;    // level changes; transfers, on a bus
    // A bus's burst: when its last transfer ended, the bytes and the failures.
    uint32_t burst_end;
    uint32_t burst_written;
    uint32_t burst_read;
    uint16_t burst_failed;
} trace_lane_t;

typedef struct
{
    uint8_t data[ TRACE_MAX_RECORD ];
    uint8_t len;
} trace_record_t;

// ------------------------------------------------------------------ VARIABLES

// Tells the drivers that their hooks are here (drv_trace.h).
const volatile uint8_t drv_trace_present = 1;

// Read by the debugger, see the file comment.
// Weak: an application with TRACE_BUFFER( size ) replaces both. The size is read at run time
// (volatile), never folded into the code, so that the replacement takes effect.
__attribute__((weak)) volatile uint8_t __traceBuffer[ TRACE_BUFF_SIZE ];
__attribute__((weak)) const volatile uint16_t __traceBufferSize = TRACE_BUFF_SIZE;
volatile uint16_t __traceLen = 0;
volatile uint32_t __traceDropped = 0;
// Written by the debugger while the program is stopped, the faults packed from the start: the
// first entry of kind TRACE_FAULT_NONE ends the list.
__attribute__((used)) volatile trace_fault_t __traceFaults[ TRACE_MAX_FAULTS ];

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
static uint32_t trace_bus_burst_gap = 0;  // TRACE_BUS_BURST_GAP_US in ticks
static uint8_t trace_bursts = 0;          // lanes in a burst

static pin_name_t trace_cs_pins[ TRACE_MAX_CS ];
static uint8_t trace_cs_count = 0;
static bool trace_cs_selected = false;
static pin_name_t trace_cs_pin;    // selected chip select, while trace_cs_selected

// Driver object whose call a fault just changed: its record is marked injected.
static const void *trace_injected = NULL;

#if TRACE_PORT_HAS_COUNTER
static bool trace_counter_running = false;
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

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
    } else {
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
    return 6 + 2 + 4 * lane->pin_count + 1 + name_len + 4;
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
    record_u32( &record, lane->rate );
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

static bool trace_is_bus( const trace_lane_t *lane )
{
    return ( TRACE_LANE_I2C == lane->kind ) || ( TRACE_LANE_SPI == lane->kind ) ||
           ( TRACE_LANE_UART == lane->kind ) || ( TRACE_LANE_ONE_WIRE == lane->kind );
}

// Ends the burst of a lane. The record is stamped now, so that record times never go back
// (the debugger takes a step back as a wrap of the time base); it says how long ago the burst
// started and ended.
static void trace_write_burst( uint8_t id, trace_lane_t *lane, uint32_t now )
{
    trace_record_t record;

    if ( trace_is_bus( lane ) )
    {
        record_header( &record, TRACE_RECORD_BUS_BURST, id, now );
        record_u32( &record, lane->burst_end - lane->burst_start );
        record_u32( &record, now - lane->burst_end );
        record_u32( &record, lane->burst_changes );
        record_u32( &record, lane->burst_written );
        record_u32( &record, lane->burst_read );
        record_u16( &record, lane->burst_failed );
    } else {
        record_header( &record, TRACE_RECORD_BURST, id, now );
        record_u32( &record, lane->last_write - lane->burst_start );
        record_u32( &record, now - lane->last_write );
        record_u32( &record, lane->burst_changes );
        record_u8( &record, lane->level );
    }
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
        uint32_t gap = trace_is_bus( lane ) ? trace_bus_burst_gap : trace_burst_gap;
        if ( lane->bursting &&
             ( all || ( (int32_t)( now - lane->last_write ) > (int32_t)gap ) ) )
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

static void trace_set_flush_interval_locked( uint32_t ms )
{
    // Needs a time base; a record counter gives none.
    trace_flush_ticks = trace_hz ? (uint32_t)( ( (uint64_t)trace_hz * ms ) / 1000U ) : 0;
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

// The fault of this kind on this pin (and I2C address), or NULL.
static const volatile trace_fault_t *trace_fault( uint8_t kind, pin_name_t pin, uint8_t address )
{
    for ( uint8_t i = 0; ( i < TRACE_MAX_FAULTS ) && ( TRACE_FAULT_NONE != __traceFaults[ i ].kind ); i++ )
    {
        const volatile trace_fault_t *fault = &__traceFaults[ i ];
        if ( ( kind == fault->kind ) && ( (uint32_t)pin == fault->pin ) &&
             ( ( TRACE_FAULT_I2C_NO_ANSWER != kind ) || ( address == fault->address ) ) )
        {
            return fault;
        }
    }
    return NULL;
}

// TRACE_RECORD_INJECTED for the record of the call a fault changed, once; 0 otherwise.
static uint8_t trace_take_injected( const void *obj )
{
    if ( !trace_injected || ( trace_injected != obj ) )
    {
        return 0;
    }
    trace_injected = NULL;
    return TRACE_RECORD_INJECTED;
}

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

// Counts a transfer into the burst of its bus lane, starting or ending the burst, as
// trace_burst_write() does for pins. True when the transfer is counted and needs no record.
static bool trace_bus_burst( uint8_t id, trace_lane_t *lane, uint32_t start, uint32_t end,
                             size_t written, size_t read, err_t result )
{
    if ( !trace_bus_burst_gap )
    {
        return false;
    }

    bool fast = lane->written && ( ( start - lane->last_write ) <= trace_bus_burst_gap );
    if ( lane->bursting && !fast )
    {
        trace_write_burst( id, lane, start );
    }
    lane->written = true;
    lane->last_write = start;
    if ( !fast )
    {
        lane->fast_writes = 0;
        return false;
    }

    if ( lane->fast_writes < TRACE_BUS_BURST_TRANSFERS )
    {
        lane->fast_writes++;
    }
    if ( !lane->bursting )
    {
        if ( lane->fast_writes < TRACE_BUS_BURST_TRANSFERS )
        {
            return false;
        }
        lane->bursting = true;
        lane->burst_start = start;
        lane->burst_changes = 0;
        lane->burst_written = 0;
        lane->burst_read = 0;
        lane->burst_failed = 0;
        trace_bursts++;
    }
    lane->burst_changes++;
    lane->burst_written += (uint32_t)written;
    lane->burst_read += (uint32_t)read;
    if ( result && ( lane->burst_failed < 0xFFFFU ) )
    {
        lane->burst_failed++;
    }
    lane->burst_end = end;
    return true;
}

// injected: TRACE_RECORD_INJECTED when a fault gave the level. A level held by a fault and
// then let go is a change even when the level stays.
static void trace_level(const void *obj, uint8_t kind, uint8_t level, bool changes_only,
                         uint8_t injected )
{
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, kind, &id );
    uint32_t now = trace_ticks();
    level = level ? 1 : 0;
    if ( lane && changes_only && ( lane->level == level ) && ( lane->injected == injected ) )
    {
        trace_port_unlock( irq_state );
        return;
    }

    if ( lane && trace_burst_write( id, lane, level, now ) )
    {
        trace_auto_flush();
    } else {
        trace_record_t record;
        if ( lane )
        {
            lane->level = level;
            lane->injected = injected;
        }
        record_header( &record, TRACE_RECORD_LEVEL | injected, id, now );
        record_u8( &record, level );
        trace_emit( id, lane, &record );
    }
    trace_port_unlock( irq_state );
}

static void trace_emit_value( uint8_t id, trace_lane_t *lane, float value, uint8_t injected )
{
    uint32_t raw;
    trace_record_t record;

    memcpy( &raw, &value, sizeof( raw ) );
    record_header( &record, TRACE_RECORD_VALUE | injected, id, trace_ticks() );
    record_u32( &record, raw );
    trace_emit( id, lane, &record );
}

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

__attribute__((weak)) uint32_t trace_tick_hz( void )
{
    #if TRACE_PORT_HAS_COUNTER
    if ( trace_counter_running )
    {
        return TRACE_PORT_COUNTER_HZ;
    }
    #endif
    return 0;
}

__attribute__((weak)) uint32_t trace_ticks( void )
{
    #if TRACE_PORT_HAS_COUNTER
    if ( trace_counter_running )
    {
        return trace_port_counter();
    }
    #endif
    return trace_sequence++;
}

void __attribute__((noinline, used)) traceBuffFullBreak( void )
{
    __asm volatile ( "nop" );
}

void trace_set_flush_interval( uint32_t ms )
{
    uint32_t irq_state = trace_port_lock();
    trace_set_flush_interval_locked( ms );
    trace_port_unlock( irq_state );
}

void trace_init( void )
{
    if ( __traceBufferSize < TRACE_MIN_BUFF_SIZE )
    {
        return;
    }

    uint32_t irq_state = trace_port_lock();
    // Started already, by an earlier call or by the first recorded event: restarting would
    // reset the time base under the records already made.
    if ( trace_started )
    {
        trace_port_unlock( irq_state );
        return;
    }
    #if TRACE_PORT_HAS_COUNTER
    trace_counter_running = trace_port_counter_start();
    #endif
    trace_hz = trace_tick_hz();
    // Bursts need a time base too.
    trace_burst_gap = (uint32_t)( ( (uint64_t)trace_hz * TRACE_BURST_GAP_US ) / 1000000U );
    trace_bus_burst_gap = (uint32_t)( ( (uint64_t)trace_hz * TRACE_BUS_BURST_GAP_US ) / 1000000U );
    trace_set_flush_interval_locked( TRACE_FLUSH_INTERVAL_MS );
    trace_last_flush = trace_ticks();
    trace_started = true;
    trace_resync = true;
    trace_port_unlock( irq_state );
}

void trace_flush( void )
{
    uint32_t irq_state = trace_port_lock();
    trace_end_bursts( trace_ticks(), true );
    trace_flush_locked();
    trace_port_unlock( irq_state );
}

void trace_value( const char *name, float value )
{
    if ( !name || !trace_ensure_started() )
    {
        return;
    }

    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( name, TRACE_LANE_VALUE, &id );
    if ( lane )
    {
        lane->name = name;
        trace_emit_value( id, lane, value, 0 );
    }
    trace_port_unlock( irq_state );
}

uint32_t drv_trace_now( void )
{
    return trace_ensure_started() ? trace_ticks() : 0;
}

// A bus's rate, set at its configuration or changed later (i2c_master_set_speed(),
// uart_set_baud()): a new one defines the lane again.
static void trace_set_rate( trace_lane_t *lane, uint32_t rate )
{
    if ( lane && ( lane->rate != rate ) )
    {
        lane->rate = rate;
        lane->defined = false;
    }
}

// I2C speeds are given as i2c_master_speed_t (standard, full, fast) or, by some HALs, in Hz.
static uint32_t trace_i2c_rate( uint32_t speed )
{
    switch ( speed )
    {
        case 0:
            return 100000;
        case 1:
            return 400000;
        case 2:
            return 1000000;
        default:
            return speed;
    }
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
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_I2C, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = i2c->config.scl;
        lane->pins[ 1 ] = i2c->config.sda;
        lane->pin_count = 2;
    }
    trace_set_rate( lane, trace_i2c_rate( i2c->config.speed ) );

    // Transfers too fast to record each (a display filled pixel by pixel) are counted.
    if ( lane && trace_bus_burst( id, lane, start, start + duration, write_len, read_len, result ) )
    {
        (void)trace_take_injected( obj );
        trace_auto_flush();
        trace_port_unlock( irq_state );
        return;
    }

    trace_record_t record;
    record_header( &record, TRACE_RECORD_I2C | trace_take_injected( obj ), id, start );
    record_u8( &record, i2c->config.addr );
    record_transfer( &record, op, write_buf, write_len, read_buf, read_len, result, duration );
    trace_emit( id, lane, &record );
    trace_port_unlock( irq_state );
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
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_SPI, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = spi->config.sck;
        lane->pins[ 1 ] = spi->config.miso;
        lane->pins[ 2 ] = spi->config.mosi;
        lane->pin_count = 3;
    }
    trace_set_rate( lane, spi->config.speed );
    // The chip select tells the device, and so the mikroBUS socket, when several share the bus.
    // A driver object is one device in Click libraries: its first chip select stays.
    if ( lane && ( 3 == lane->pin_count ) && trace_cs_selected )
    {
        lane->pins[ 3 ] = trace_cs_pin;
        lane->pin_count = 4;
        lane->defined = false;
    }

    // Transfers too fast to record each (a display filled pixel by pixel) are counted.
    if ( lane && trace_bus_burst( id, lane, start, start + duration, write_len, read_len, result ) )
    {
        (void)trace_take_injected( obj );
        trace_auto_flush();
        trace_port_unlock( irq_state );
        return;
    }

    trace_record_t record;
    record_header( &record, TRACE_RECORD_SPI | trace_take_injected( obj ), id, start );
    record_transfer( &record, op, write_buf, write_len, read_buf, read_len, result, duration );
    trace_emit( id, lane, &record );
    trace_port_unlock( irq_state );
}

void drv_trace_uart( const void *obj, uint8_t is_tx, const uint8_t *buf, size_t len, uint32_t start )
{
    if ( !trace_ensure_started() )
    {
        return;
    }

    uint32_t duration = trace_ticks() - start;
    const uart_t *uart = (const uart_t *)obj;
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_UART, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = uart->config.tx_pin;
        lane->pins[ 1 ] = uart->config.rx_pin;
        lane->pin_count = 2;
    }
    trace_set_rate( lane, uart->config.baud );

    // Transfers too fast to record each (a display filled pixel by pixel) are counted.
    if ( lane && trace_bus_burst( id, lane, start, start + duration, is_tx ? len : 0, is_tx ? 0 : len, 0 ) )
    {
        (void)trace_take_injected( obj );
        trace_auto_flush();
        trace_port_unlock( irq_state );
        return;
    }

    uint8_t kept = kept_bytes( buf, len );
    trace_record_t record;
    record_header( &record, is_tx ? TRACE_RECORD_UART_TX : TRACE_RECORD_UART_RX, id, start );
    record_u32( &record, duration );
    record_u16( &record, clamp_u16( len ) );
    record_u8( &record, kept );
    record_bytes( &record, buf, kept );
    trace_emit( id, lane, &record );
    trace_port_unlock( irq_state );
}

void drv_trace_gpio_init( const void *obj, pin_name_t pin, uint8_t is_output )
{
    // Kept before trace_init too: drivers are often initialized first.
    uint32_t irq_state = trace_port_lock();
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
        lane->injected = 0;
        lane->defined = false;
        lane->written = false;
        lane->fast_writes = 0;
    }
    trace_port_unlock( irq_state );
}

void drv_trace_gpio_out( const void *obj, uint8_t level )
{
    if ( trace_ensure_started() )
    {
        trace_level( obj, TRACE_LANE_GPIO_OUT, level, false, 0 );
    }
}

uint8_t drv_trace_gpio_in( const void *obj, uint8_t level )
{
    if ( !trace_ensure_started() )
    {
        return level;
    }

    // A fault holding the pin gives its level instead of the one read.
    uint8_t injected = 0;
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_GPIO_IN, &id );
    const volatile trace_fault_t *fault =
        ( lane && lane->pin_count ) ? trace_fault( TRACE_FAULT_GPIO_IN, lane->pins[ 0 ], 0 ) : NULL;
    if ( fault )
    {
        level = fault->value ? 1 : 0;
        injected = TRACE_RECORD_INJECTED;
    }
    trace_port_unlock( irq_state );

    // Polling loops read the same level again and again: only changes are recorded.
    trace_level( obj, TRACE_LANE_GPIO_IN, level, true, injected );
    return level;
}

void drv_trace_spi_cs( pin_name_t chip_select, uint8_t selected, uint8_t level )
{
    if ( ( HAL_PIN_NC == chip_select ) || !trace_ensure_started() )
    {
        return;
    }

    uint32_t irq_state = trace_port_lock();
    if ( selected )
    {
        trace_cs_pin = chip_select;
        trace_cs_selected = true;
    }
    else if ( trace_cs_selected && ( trace_cs_pin == chip_select ) )
    {
        trace_cs_selected = false;
    }

    const void *key = NULL;
    for ( uint8_t i = 0; i < trace_cs_count; i++ )
    {
        if ( trace_cs_pins[ i ] == chip_select )
        {
            key = &trace_cs_pins[ i ];
        }
    }
    if ( !key && ( trace_cs_count < TRACE_MAX_CS ) )
    {
        trace_cs_pins[ trace_cs_count ] = chip_select;
        key = &trace_cs_pins[ trace_cs_count++ ];
    }

    uint8_t id;
    trace_lane_t *lane = key ? trace_lane( key, TRACE_LANE_GPIO_OUT, &id ) : NULL;
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = chip_select;
        lane->pin_count = 1;
    }
    trace_port_unlock( irq_state );

    if ( lane )
    {
        trace_level( key, TRACE_LANE_GPIO_OUT, level, false, 0 );
    }
}

void drv_trace_adc( const void *obj, pin_name_t pin, uint8_t is_voltage, float value )
{
    if ( !trace_ensure_started() )
    {
        return;
    }

    // Raw counts and volts of one input are two lanes, so that a lane never mixes units. The
    // volts lane is keyed one byte into the driver object: no other object starts there.
    const void *key = is_voltage ? (const void *)( (const uint8_t *)obj + 1 ) : obj;
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( key, TRACE_LANE_VALUE, &id );
    if ( lane )
    {
        if ( !lane->pin_count )
        {
            lane->name = is_voltage ? "ADC V" : "ADC";
            lane->pins[ 0 ] = pin;
            lane->pin_count = 1;
        }
        trace_emit_value( id, lane, value, trace_take_injected( obj ) );
    }
    trace_port_unlock( irq_state );
}

void drv_trace_one_wire( const void *obj, pin_name_t pin, uint8_t op, const uint8_t *buf, size_t len,
                         err_t result, uint32_t start )
{
    if ( !trace_ensure_started() )
    {
        return;
    }

    uint32_t duration = trace_ticks() - start;
    uint32_t irq_state = trace_port_lock();
    uint8_t id;
    trace_lane_t *lane = trace_lane( obj, TRACE_LANE_ONE_WIRE, &id );
    if ( lane && !lane->pin_count )
    {
        lane->pins[ 0 ] = pin;
        lane->pin_count = 1;
    }

    // Data read by a failed operation is not valid; data written is kept.
    bool is_read = ( DRV_TRACE_ONE_WIRE_READ_ROM == op ) || ( DRV_TRACE_ONE_WIRE_SEARCH_FIRST == op ) ||
                   ( DRV_TRACE_ONE_WIRE_SEARCH_NEXT == op ) || ( DRV_TRACE_ONE_WIRE_READ == op );
    // Transfers too fast to record each (a display filled pixel by pixel) are counted.
    if ( lane && trace_bus_burst( id, lane, start, start + duration, is_read ? 0 : len, is_read ? len : 0, result ) )
    {
        (void)trace_take_injected( obj );
        trace_auto_flush();
        trace_port_unlock( irq_state );
        return;
    }

    uint8_t kept = ( result && is_read ) ? 0 : kept_bytes( buf, len );
    trace_record_t record;
    record_header( &record, TRACE_RECORD_ONE_WIRE | trace_take_injected( obj ), id, start );
    record_u8( &record, op );
    record_u8( &record, result ? 1 : 0 );
    record_u32( &record, duration );
    record_u16( &record, clamp_u16( len ) );
    record_u8( &record, kept );
    record_bytes( &record, buf, kept );
    trace_emit( id, lane, &record );
    trace_port_unlock( irq_state );
}

uint8_t drv_trace_fault_i2c( const void *obj )
{
    const i2c_master_t *i2c = (const i2c_master_t *)obj;
    if ( !trace_fault( TRACE_FAULT_I2C_NO_ANSWER, i2c->config.scl, i2c->config.addr ) )
    {
        return 0;
    }
    trace_injected = obj;
    return 1;
}

void drv_trace_fault_spi( const void *obj, uint8_t *read_buf, size_t read_len )
{
    // MISO is shared by the devices of the bus: the fault holds the bus, by its clock pin.
    const spi_master_t *spi = (const spi_master_t *)obj;
    const volatile trace_fault_t *fault = trace_fault( TRACE_FAULT_SPI_MISO, spi->config.sck, 0 );
    if ( fault && read_buf && read_len )
    {
        memset( read_buf, (uint8_t)fault->value, read_len );
        trace_injected = obj;
    }
}

uint8_t drv_trace_fault_adc( const void *obj, pin_name_t pin, uint8_t is_voltage, float *value )
{
    const volatile trace_fault_t *fault =
        trace_fault( is_voltage ? TRACE_FAULT_ADC_VOLTAGE : TRACE_FAULT_ADC, pin, 0 );
    if ( !fault )
    {
        return 0;
    }
    uint32_t raw = fault->value;
    memcpy( value, &raw, sizeof( raw ) );
    // A raw count is what a 16-bit read can give.
    if ( !is_voltage )
    {
        *value = ( *value < 0.0f ) ? 0.0f : ( ( *value > 65535.0f ) ? 65535.0f : *value );
    }
    trace_injected = obj;
    return 1;
}

uint8_t drv_trace_fault_one_wire( const void *obj, pin_name_t pin )
{
    if ( !trace_fault( TRACE_FAULT_ONE_WIRE_NO_DEVICE, pin, 0 ) )
    {
        return 0;
    }
    trace_injected = obj;
    return 1;
}

// ------------------------------------------------------------------------- END
