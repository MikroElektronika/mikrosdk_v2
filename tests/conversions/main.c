// ------------------------------------------------------------------ INCLUDES

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// Define USE_LOGGER to 1 to enable logging of test results to the MikroE std_out logger.
// Define USE_LOGGER to 0 to disable logging (necessary in some cases to avoid memory issues).
#define USE_LOGGER 0

#if USE_LOGGER
#include "log.h"
#endif
#include "conversions.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// ----------------------------------------------------------------- VARIABLES
// NOTE: In case this test doesn't built because of a memory issue, reduce the number of function calls
//       in functions named `test_<name>` to reduce the memory footprint of the test.

// Set at least one of these to 1 to select a test group,
#define TEST_GROUP_HEX                       (1)
#define TEST_GROUP_TO_STR                    (0)
#define TEST_GROUP_BCD_TRIM                  (0)
#define TEST_GROUP_FLOAT                     (0)
#define TEST_GROUP_STR_TO_INT                (0)
#define TEST_GROUP_HEX_PARSE                 (0)

// Or set this macro to 1 to run all tests.
#define TEST_GROUP_FULL                      (0)

#define MAX_FAILED_TESTS 8

static uint16_t pass_count = 0;
static uint16_t fail_count = 0;
static uint16_t failed_lines[ MAX_FAILED_TESTS ];
static char buf[32];

// ----------------------------------------------------------------- HELPERS

static void record_result( bool did_pass, uint16_t line ) {
    if ( true == did_pass ) {
        pass_count++;
        #if USE_LOGGER
        printf_me( "[PASS] line %d\n", line );
        #endif
        return;
    }
    if ( fail_count < MAX_FAILED_TESTS ) {
        failed_lines[ fail_count ] = line;
        #if USE_LOGGER
        printf_me( "[FAIL] line %d\n", line );
        #endif
    }
    fail_count++;
}

#define CHECK_STR( got, expected ) \
    record_result( ( 0 == strcmp( ( got ), ( expected ) ) ), ( uint16_t )__LINE__ )

#define CHECK_U8( got, expected ) \
    record_result( ( ( expected ) == ( got ) ), ( uint16_t )__LINE__ )

#define CHECK_I8( got, expected ) \
    record_result( ( ( expected ) == ( got ) ), ( uint16_t )__LINE__ )

#define CHECK_U16( got, expected ) \
    record_result( ( ( expected ) == ( got ) ), ( uint16_t )__LINE__ )

#define CHECK_I16( got, expected ) \
    record_result( ( ( expected ) == ( got ) ), ( uint16_t )__LINE__ )

#define CHECK_U32( got, expected ) \
    record_result( ( ( expected ) == ( got ) ), ( uint16_t )__LINE__ )

#define CHECK_I32( got, expected ) \
    record_result( ( ( expected ) == ( got ) ), ( uint16_t )__LINE__ )

// float comparison: allow 0.5% relative error or 1e-5 absolute
static bool float_eq( float a, float b ) {
    float diff = a - b;
    if ( 0.0f > diff ) diff = -diff;
    float ref  = 0.0f > b ? -b : b;
    if ( 1e-5f > ref ) ref = 1e-5f;
    return ( 0.005f > ( diff / ref ) );
}

#define CHECK_F( got, expected ) \
    record_result( float_eq( ( got ), ( expected ) ), ( uint16_t )__LINE__ )

// ----------------------------------------------------------------- TEST GROUPS

static void test_uint8_to_hex( void ) {
    uint8_to_hex( 0x00, buf ); CHECK_STR( buf, "00" );
    uint8_to_hex( 0xFF, buf ); CHECK_STR( buf, "FF" );
    uint8_to_hex( 0xAB, buf ); CHECK_STR( buf, "AB" );
    uint8_to_hex( 0x0F, buf ); CHECK_STR( buf, "0F" );
}

static void test_int8_to_hex( void ) {
    int8_to_hex(  0,   buf ); CHECK_STR( buf, "00" );
    int8_to_hex( -1,   buf ); CHECK_STR( buf, "FF" );
    int8_to_hex(  127, buf ); CHECK_STR( buf, "7F" );
    int8_to_hex( -128, buf ); CHECK_STR( buf, "80" );
}

static void test_uint16_to_hex( void ) {
    uint16_to_hex( 0x0000, buf ); CHECK_STR( buf, "0000" );
    uint16_to_hex( 0xFFFF, buf ); CHECK_STR( buf, "FFFF" );
    uint16_to_hex( 0x1234, buf ); CHECK_STR( buf, "1234" );
    uint16_to_hex( 0xABCD, buf ); CHECK_STR( buf, "ABCD" );
}

static void test_uint32_to_hex( void ) {
    uint32_to_hex( 0x00000000UL, buf ); CHECK_STR( buf, "00000000" );
    uint32_to_hex( 0xFFFFFFFFUL, buf ); CHECK_STR( buf, "FFFFFFFF" );
    uint32_to_hex( 0x12345678UL, buf ); CHECK_STR( buf, "12345678" );
    uint32_to_hex( 0xDEADBEEFUL, buf ); CHECK_STR( buf, "DEADBEEF" );
}

static void test_int32_to_hex( void ) {
    int32_to_hex(  0,          buf ); CHECK_STR( buf, "00000000" );
    int32_to_hex( -1,          buf ); CHECK_STR( buf, "FFFFFFFF" );
    int32_to_hex(  2147483647, buf ); CHECK_STR( buf, "7FFFFFFF" );
}

static void test_uint8_to_str( void ) {
    uint8_to_str( 0,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "0"   );
    uint8_to_str( 255, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "255" );
    uint8_to_str( 42,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "42"  );
}

static void test_uint8_to_str_with_zeros( void ) {
    uint8_to_str_with_zeros( 0,   buf ); CHECK_STR( buf, "000" );
    uint8_to_str_with_zeros( 255, buf ); CHECK_STR( buf, "255" );
    uint8_to_str_with_zeros( 7,   buf ); CHECK_STR( buf, "007" );
}

static void test_int8_to_str( void ) {
    int8_to_str(  0,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "0"    );
    int8_to_str(  127, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "127"  );
    int8_to_str( -1,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "-1"   );
    int8_to_str( -128, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "-128" );
}

static void test_int8_to_str_with_zeros( void ) {
    int8_to_str_with_zeros(  0,   buf ); CHECK_STR( buf, "0000"  );
    int8_to_str_with_zeros(  127, buf ); CHECK_STR( buf, "0127"  );
    int8_to_str_with_zeros( -1,   buf ); CHECK_STR( buf, "-001"  );
    int8_to_str_with_zeros( -128, buf ); CHECK_STR( buf, "-128"  );
}

static void test_uint16_to_str( void ) {
    uint16_to_str( 0,     buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "0"     );
    uint16_to_str( 65535, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "65535" );
    uint16_to_str( 1000,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "1000"  );
}

static void test_uint16_to_str_with_zeros( void ) {
    uint16_to_str_with_zeros( 0,     buf ); CHECK_STR( buf, "00000" );
    uint16_to_str_with_zeros( 65535, buf ); CHECK_STR( buf, "65535" );
    uint16_to_str_with_zeros( 42,    buf ); CHECK_STR( buf, "00042" );
}

static void test_int16_to_str( void ) {
    int16_to_str(  0,      buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "0"      );
    int16_to_str(  32767,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "32767"  );
    int16_to_str( -1,      buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "-1"     );
    int16_to_str( -32768,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "-32768" );
}

static void test_int16_to_str_with_zeros( void ) {
    int16_to_str_with_zeros(  0,     buf ); CHECK_STR( buf, "000000"  );
    int16_to_str_with_zeros(  32767, buf ); CHECK_STR( buf, "032767"  );
    int16_to_str_with_zeros( -1,     buf ); CHECK_STR( buf, "-00001"  );
    int16_to_str_with_zeros( -32768, buf ); CHECK_STR( buf, "-32768"  );
}

static void test_uint32_to_str( void ) {
    uint32_to_str( 0UL,         buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "0"          );
    uint32_to_str( 4294967295UL,buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "4294967295" );
    uint32_to_str( 1000000UL,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "1000000"    );
}

static void test_uint32_to_str_with_zeros( void ) {
    uint32_to_str_with_zeros( 0UL,          buf ); CHECK_STR( buf, "0000000000" );
    uint32_to_str_with_zeros( 4294967295UL, buf ); CHECK_STR( buf, "4294967295" );
    uint32_to_str_with_zeros( 42UL,         buf ); CHECK_STR( buf, "0000000042" );
}

static void test_int32_to_str( void ) {
    int32_to_str(  0,           buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "0"           );
    int32_to_str(  2147483647L, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "2147483647"  );
    int32_to_str( -1L,          buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "-1"          );
    int32_to_str( -2147483647L, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "-2147483647" );
}

static void test_int32_to_str_with_zeros( void ) {
    int32_to_str_with_zeros(  0,           buf ); CHECK_STR( buf, "00000000000"  );
    int32_to_str_with_zeros(  2147483647L, buf ); CHECK_STR( buf, "02147483647"  );
    int32_to_str_with_zeros( -1L,          buf ); CHECK_STR( buf, "-0000000001"  );
    int32_to_str_with_zeros( -2147483647L, buf ); CHECK_STR( buf, "-2147483647"  );
}

static void test_dec_bcd( void ) {
    CHECK_U8( dec_to_bcd( 0 ),   0x00 );
    CHECK_U8( dec_to_bcd( 9 ),   0x09 );
    CHECK_U8( dec_to_bcd( 10 ),  0x10 );
    CHECK_U8( dec_to_bcd( 99 ),  0x99 );
    CHECK_U8( bcd_to_dec( 0x00 ), 0  );
    CHECK_U8( bcd_to_dec( 0x09 ), 9  );
    CHECK_U8( bcd_to_dec( 0x10 ), 10 );
    CHECK_U8( bcd_to_dec( 0x99 ), 99 );
}

static void test_dec_bcd16( void ) {
    CHECK_U16( dec_to_bcd16( 0 ),    0x0000 );
    CHECK_U16( dec_to_bcd16( 1234 ), 0x1234 );
    CHECK_U16( dec_to_bcd16( 9999 ), 0x9999 );
    CHECK_U16( bcd_to_dec16( 0x0000 ), 0    );
    CHECK_U16( bcd_to_dec16( 0x1234 ), 1234 );
    CHECK_U16( bcd_to_dec16( 0x9999 ), 9999 );
}

static void test_trim( void ) {
    strcpy( buf, "hello   " ); r_trim( buf ); CHECK_STR( buf, "hello"   );
    strcpy( buf, "   hello" ); l_trim( buf ); CHECK_STR( buf, "hello"   );
    strcpy( buf, "  hi  "  ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "hi" );
    strcpy( buf, "none"    ); r_trim( buf ); l_trim( buf ); CHECK_STR( buf, "none" );
}

static void test_float_to_str( void ) {
    float_to_str( 0.0f,      buf ); CHECK_STR( buf, "0"       );
    float_to_str( 1.0f,      buf ); CHECK_STR( buf, "1"       );
    float_to_str( -1.0f,     buf ); CHECK_STR( buf, "-1"      );
    float_to_str( 3.14f,     buf ); CHECK_STR( buf, "3.14"    );
    float_to_str( -3.14f,    buf ); CHECK_STR( buf, "-3.14"   );
    float_to_str( 123456.0f, buf ); CHECK_STR( buf, "123456"  );
    float_to_str( 1234567.0f,buf ); CHECK_STR( buf, "1234567" );
    float_to_str( 0.001f,    buf ); CHECK_STR( buf, "1e-3"    );
}

static void test_float_to_str_prec( void ) {
    float_to_str_prec( 12.435468f,  buf, sizeof(buf), 2 ); CHECK_STR( buf, "12.44"    );
    float_to_str_prec( 12.435468f,  buf, sizeof(buf), 4 ); CHECK_STR( buf, "12.4355"  );
    float_to_str_prec( 0.0f,        buf, sizeof(buf), 3 ); CHECK_STR( buf, "0.000"    );
    float_to_str_prec( 1.0f,        buf, sizeof(buf), 0 ); CHECK_STR( buf, "1"        );
    float_to_str_prec( -3.14159f,   buf, sizeof(buf), 4 ); CHECK_STR( buf, "-3.1416"  );
    float_to_str_prec( 100.0f,      buf, sizeof(buf), 2 ); CHECK_STR( buf, "100.00"   );
    float_to_str_prec( 0.001f,      buf, sizeof(buf), 5 ); CHECK_STR( buf, "0.00100"  );
    float_to_str_prec( 999999.9f,   buf, sizeof(buf), 1 ); CHECK_STR( buf, "999999.9");
}

static void test_str_to_uint8( void ) {
    CHECK_U8( str_to_uint8( "0"   ), 0   );
    CHECK_U8( str_to_uint8( "255" ), 255 );
    CHECK_U8( str_to_uint8( "042" ), 42  );
    CHECK_U8( str_to_uint8( "bad" ), 0   );
}

static void test_str_to_int8( void ) {
    CHECK_I8( str_to_int8( "0"    ),  0   );
    CHECK_I8( str_to_int8( "127"  ),  127 );
    CHECK_I8( str_to_int8( "-1"   ), -1   );
    CHECK_I8( str_to_int8( "-128" ), -128 );
}

static void test_str_to_uint16( void ) {
    CHECK_U16( str_to_uint16( "0"     ), 0     );
    CHECK_U16( str_to_uint16( "65535" ), 65535 );
    CHECK_U16( str_to_uint16( "1000"  ), 1000  );
    CHECK_U16( str_to_uint16( "bad"   ), 0     );
}

static void test_str_to_int16( void ) {
    CHECK_I16( str_to_int16( "0"      ),  0     );
    CHECK_I16( str_to_int16( "32767"  ),  32767 );
    CHECK_I16( str_to_int16( "-1"     ), -1     );
    CHECK_I16( str_to_int16( "-32767" ), -32767 );
}

static void test_str_to_uint32( void ) {
    CHECK_U32( str_to_uint32( "0"          ), 0UL          );
    CHECK_U32( str_to_uint32( "4294967295" ), 4294967295UL );
    CHECK_U32( str_to_uint32( "1000000"   ), 1000000UL    );
    CHECK_U32( str_to_uint32( "bad"       ), 0UL          );
}

static void test_str_to_int32( void ) {
    CHECK_I32( str_to_int32( "0"           ),  0L          );
    CHECK_I32( str_to_int32( "2147483647"  ),  2147483647L );
    CHECK_I32( str_to_int32( "-1"          ), -1L          );
    CHECK_I32( str_to_int32( "-2147483647" ), -2147483647L );
}

static void test_str_to_float( void ) {
    CHECK_F( str_to_float( "0.0"    ),  0.0f    );
    CHECK_F( str_to_float( "1.0"    ),  1.0f    );
    CHECK_F( str_to_float( "-1.5"   ), -1.5f    );
    CHECK_F( str_to_float( "3.14"   ),  3.14f   );
    CHECK_F( str_to_float( "123.456"),  123.456f );
}

static void test_hex_to_uint8( void ) {
    CHECK_U8( hex_to_uint8( "00" ), 0x00 );
    CHECK_U8( hex_to_uint8( "FF" ), 0xFF );
    CHECK_U8( hex_to_uint8( "ff" ), 0xFF );
    CHECK_U8( hex_to_uint8( "AB" ), 0xAB );
    CHECK_U8( hex_to_uint8( "0F" ), 0x0F );
}

static void test_hex_to_uint16( void ) {
    CHECK_U16( hex_to_uint16( "0000" ), 0x0000 );
    CHECK_U16( hex_to_uint16( "FFFF" ), 0xFFFF );
    CHECK_U16( hex_to_uint16( "1234" ), 0x1234 );
    CHECK_U16( hex_to_uint16( "abcd" ), 0xABCD );
}

static void test_hex_to_uint32( void ) {
    CHECK_U32( hex_to_uint32( "00000000" ), 0x00000000UL );
    CHECK_U32( hex_to_uint32( "FFFFFFFF" ), 0xFFFFFFFFUL );
    CHECK_U32( hex_to_uint32( "12345678" ), 0x12345678UL );
    CHECK_U32( hex_to_uint32( "DEADBEEF" ), 0xDEADBEEFUL );
}

static void test_hex_to_int( void ) {
    CHECK_I8( hex_to_int8( "FF" ),         -1          );
    CHECK_I8( hex_to_int8( "7F" ),          127        );
    CHECK_I8( hex_to_int8( "80" ),         -128        );
    CHECK_I16( hex_to_int16( "FFFF" ),      -1          );
    CHECK_I16( hex_to_int16( "7FFF" ),       32767      );
    CHECK_I32( hex_to_int32( "FFFFFFFF" ),  -1L         );
    CHECK_I32( hex_to_int32( "7FFFFFFF" ),   2147483647L );
}

// ----------------------------------------------------------------- MAIN

int main( void ) {
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    #if (TEST_GROUP_HEX || TEST_GROUP_FULL)
    test_uint8_to_hex();
    test_int8_to_hex();
    test_uint16_to_hex();
    test_uint32_to_hex();
    test_int32_to_hex();
    #endif

    #if (TEST_GROUP_TO_STR || TEST_GROUP_FULL)
    test_uint8_to_str();
    test_uint8_to_str_with_zeros();
    test_int8_to_str();
    test_int8_to_str_with_zeros();
    test_uint16_to_str();
    test_uint16_to_str_with_zeros();
    test_int16_to_str();
    test_int16_to_str_with_zeros();
    test_uint32_to_str();
    test_uint32_to_str_with_zeros();
    test_int32_to_str();
    test_int32_to_str_with_zeros();
    #endif

    #if (TEST_GROUP_BCD_TRIM || TEST_GROUP_FULL)
    test_dec_bcd();
    test_dec_bcd16();
    test_trim();
    #endif

    #if (TEST_GROUP_FLOAT || TEST_GROUP_FULL)
    test_float_to_str();
    test_float_to_str_prec();
    test_str_to_float();
    #endif

    #if (TEST_GROUP_STR_TO_INT || TEST_GROUP_FULL)
    test_str_to_uint8();
    test_str_to_int8();
    test_str_to_uint16();
    test_str_to_int16();
    test_str_to_uint32();
    test_str_to_int32();
    #endif

    #if (TEST_GROUP_HEX_PARSE || TEST_GROUP_FULL)
    test_hex_to_uint8();
    test_hex_to_uint16();
    test_hex_to_uint32();
    test_hex_to_int();
    #endif

    #if !( TEST_GROUP_HEX || TEST_GROUP_TO_STR || TEST_GROUP_BCD_TRIM || \
           TEST_GROUP_FLOAT || TEST_GROUP_STR_TO_INT || TEST_GROUP_HEX_PARSE || \
           TEST_GROUP_FULL )
    #error "Set at least one TEST_GROUP_* (or TEST_GROUP_FULL) to 1 to select which tests to build"
    #endif

    // Put a breakpoint here to inspect the results of the test.
    while ( 1 );

    return 0;
}
