/*
 * Host unit test of platform/systime, compiled with SYSTIME_TEST_COUNTER: the
 * cycle counter is fake_counter, advanced by the test. Checks that the
 * milliseconds always equal (cycles since start) / (cycles per ms), across
 * counter wraps and for steps up to almost a full counter period.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "systime.h"

static uint32_t fake_counter;
uint32_t systime_test_counter( void ) { return fake_counter; }

static int failures;
#define CHECK( name, cond ) do { if ( cond ) printf( "OK %s\n", name ); \
        else { failures++; printf( "FAIL %s (line %d)\n", name, __LINE__ ); } } while ( 0 )

int main( void )
{
    const uint64_t per_ms = SYSTIME_TEST_TICKS_PER_MS;

    fake_counter = 0xFFFFF000u;             /* start just before a wrap */
    CHECK( "first-call-starts-at-zero", 0 == systime_ms() );
    systime_init();                         /* a later init does not restart */
    fake_counter += ( uint32_t )( 5 * per_ms );
    CHECK( "init-is-idempotent", 5 == systime_ms() );

    uint64_t total = 5 * per_ms;
    uint32_t seed = 7;
    bool exact = true;
    for ( uint32_t i = 0; i < 3000000u && exact; i++ )
    {
        seed = seed * 1664525u + 1013904223u;
        uint32_t step;
        switch ( i % 1000 )
        {
            case 0:   step = 0xFFFFFFFFu; break;            /* almost a full period */
            case 1:   step = ( uint32_t )per_ms - 1u; break;
            case 2:   step = 0; break;
            default:  step = seed % ( 3u * ( uint32_t )per_ms ); break;
        }
        fake_counter += step;
        total += step;
        exact = ( systime_ms() == ( uint32_t )( total / per_ms ) );
    }
    CHECK( "exact-across-wraps", exact );
    printf( "   %llu cycles, %llu counter wraps\n", ( unsigned long long )total, ( unsigned long long )( total >> 32 ) );

    printf( "RESULT %s (%d failed)\n", failures ? "FAIL" : "PASS", failures );
    return failures ? 1 : 0;
}
