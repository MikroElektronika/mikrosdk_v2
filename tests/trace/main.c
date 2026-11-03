// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "trace.h"
#include "board.h"
#include "delays.h"
// -------------------------------------------------------------------- MACROS

// TODO Define a free pin. Its writes are the traced events.
#define TEST_PIN_TRACE HAL_PIN_NC

// TODO Define test pins according to hardware.
// The pin of the first failed check goes high, see ReadMe.txt.
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_SUCCESS HAL_PIN_NC

// Number of fast writes for the burst check (TEST_PIN_6).
// Without bursts these would need far more than TRACE_BUFF_SIZE bytes.
#define BURST_WRITES 1000

// Record types and sizes of the trace format (trace.c).
#define RECORD_META     0x01
#define RECORD_LANE_DEF 0x02
#define RECORD_LEVEL    0x10
#define RECORD_BURST    0x11
#define RECORD_VALUE    0x30
#define RECORD_DROPPED  0x3F

#define META_SIZE         13
#define GPIO_LANE_DEF_SIZE 13
#define LEVEL_SIZE         7
#define LEVEL_OFFSET       6

#define signal_error(pin)        digital_out_init( &test_pin, pin ); \
                                 digital_out_high( &test_pin ); \
                                 while(1)

#define signal_success(port,pin) digital_out_init( &port, pin ); \
                                 digital_out_write( &port, 1 )
// ----------------------------------------------------------------- VARIABLES

// Trace buffer and counters, read by the debugger (trace.c).
extern volatile uint8_t __traceBuffer[];
extern volatile uint16_t __traceLen;
extern volatile uint32_t __traceDropped;

static digital_out_t test_pin, trace_pin, success_pin;

static uint32_t dropped;
static uint16_t len;
static uint16_t i;
// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initializing a pin records nothing yet.
    if ( DIGITAL_OUT_SUCCESS != digital_out_init( &trace_pin, TEST_PIN_TRACE ) ) {
        signal_error( TEST_PIN_1 );
    }
    if ( 0 != __traceLen ) {
        signal_error( TEST_PIN_1 );
    }

    // The first write starts the trace: META, the lane definition of the pin, its level.
    digital_out_high( &trace_pin );
    if ( ( META_SIZE + GPIO_LANE_DEF_SIZE + LEVEL_SIZE ) != __traceLen ) {
        signal_error( TEST_PIN_2 );
    }
    if ( ( RECORD_META != __traceBuffer[ 0 ] ) ||
         ( RECORD_LANE_DEF != __traceBuffer[ META_SIZE ] ) ||
         ( RECORD_LEVEL != __traceBuffer[ META_SIZE + GPIO_LANE_DEF_SIZE ] ) ||
         ( 1 != __traceBuffer[ META_SIZE + GPIO_LANE_DEF_SIZE + LEVEL_OFFSET ] ) ) {
        signal_error( TEST_PIN_2 );
    }

    // A named value: its lane definition, then the value.
    len = __traceLen;
    trace_value( "value", 1.5 );
    if ( ( RECORD_LANE_DEF != __traceBuffer[ len ] ) ||
         ( RECORD_VALUE != __traceBuffer[ __traceLen - 10 ] ) ) {
        signal_error( TEST_PIN_3 );
    }

    // Flush. Without a debugger reading the trace the records are counted as dropped.
    trace_flush();
    if ( 0 != __traceLen ) {
        signal_error( TEST_PIN_4 );
    }

    // After a loss the trace starts over with META and DROPPED; otherwise only the event.
    digital_out_low( &trace_pin );
    if ( __traceDropped ) {
        if ( ( RECORD_META != __traceBuffer[ 0 ] ) ||
             ( RECORD_DROPPED != __traceBuffer[ META_SIZE ] ) ) {
            signal_error( TEST_PIN_5 );
        }
    } else if ( RECORD_LEVEL != __traceBuffer[ 0 ] ) {
        signal_error( TEST_PIN_5 );
    }

    // Bursts need a time base. Fast writes are counted, not recorded: the buffer never fills.
    // TODO On slow cores a write through the driver can take longer than the burst gap
    // (20 us): then no burst starts and this check fails.
    if ( trace_tick_hz() ) {
        dropped = __traceDropped;
        for ( i = 0; i < BURST_WRITES; i++ ) {
            digital_out_toggle( &trace_pin );
        }
        if ( dropped != __traceDropped ) {
            signal_error( TEST_PIN_6 );
        }

        // The next event after a pause ends the burst: BURST comes before it.
        len = __traceLen;
        Delay_ms( 1 );
        trace_value( "value", 2.5 );
        if ( RECORD_BURST != __traceBuffer[ len ] ) {
            signal_error( TEST_PIN_6 );
        }
    }

    signal_success( success_pin, TEST_PIN_SUCCESS );

    while ( 1 );

    return 0;
}

// ----------------------------------------------------------------------- END
