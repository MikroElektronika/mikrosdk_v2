// ------------------------------------------------------------------ INCLUDES

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "board.h"
#include "log.h"
#include "conversions.h"
#include "delays.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// ----------------------------------------------------------------- VARIABLES

static log_t logger;
static log_cfg_t log_cfg;

static uint16_t pass_count = 0;
static uint16_t fail_count = 0;
static char buf[32];

// ----------------------------------------------------------------- HELPERS

static void CHECK_STR( const char *fn, const char *got, const char *expected ) {
    if ( strcmp( got, expected ) == 0 ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got \"%s\", expected \"%s\"\n", fn, got, expected );
    }
}

static void CHECK_U8( const char *fn, uint8_t got, uint8_t expected ) {
    if ( got == expected ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got %u, expected %u\n", fn, ( uint16_t )got, ( uint16_t )expected );
    }
}

static void CHECK_I8( const char *fn, int8_t got, int8_t expected ) {
    if ( got == expected ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got %d, expected %d\n", fn, ( int16_t )got, ( int16_t )expected );
    }
}

static void CHECK_U16( const char *fn, uint16_t got, uint16_t expected ) {
    if ( got == expected ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got %u, expected %u\n", fn, got, expected );
    }
}

static void CHECK_I16( const char *fn, int16_t got, int16_t expected ) {
    if ( got == expected ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got %d, expected %d\n", fn, got, expected );
    }
}

static void CHECK_U32( const char *fn, uint32_t got, uint32_t expected ) {
    if ( got == expected ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got %lu, expected %lu\n", fn, got, expected );
    }
}

static void CHECK_I32( const char *fn, int32_t got, int32_t expected ) {
    if ( got == expected ) {
        pass_count++;
    } else {
        fail_count++;
        log_printf( &logger, "FAIL  %s: got %ld, expected %ld\n", fn, got, expected );
    }
}

// float comparison: allow 0.5% relative error or 1e-5 absolute
static bool float_eq( float a, float b ) {
    float diff = a - b;
    if ( diff < 0 ) diff = -diff;
    float ref  = b < 0 ? -b : b;
    if ( ref < 1e-5f ) ref = 1e-5f;
    return ( diff / ref ) < 0.005f;
}

static void CHECK_F( const char *fn, float got, float expected ) {
    if ( float_eq( got, expected ) ) {
        pass_count++;
    } else {
        fail_count++;
        // log_printf on embedded typically can't do %f, print via float_to_str
        char g[20], e[20];
        float_to_str( got,      g );
        float_to_str( expected, e );
        log_printf( &logger, "FAIL  %s: got %s, expected %s\n", fn, g, e );
    }
}

// ----------------------------------------------------------------- TEST GROUPS

static void test_uint8_to_hex( void ) {
    log_printf( &logger, "\n-- uint8_to_hex --\n" );
    uint8_to_hex( 0x00, buf ); CHECK_STR( "uint8_to_hex(0x00)",  buf, "00" );
    uint8_to_hex( 0xFF, buf ); CHECK_STR( "uint8_to_hex(0xFF)",  buf, "FF" );
    uint8_to_hex( 0xAB, buf ); CHECK_STR( "uint8_to_hex(0xAB)",  buf, "AB" );
    uint8_to_hex( 0x0F, buf ); CHECK_STR( "uint8_to_hex(0x0F)",  buf, "0F" );
}

static void test_int8_to_hex( void ) {
    log_printf( &logger, "\n-- int8_to_hex --\n" );
    int8_to_hex(  0,   buf ); CHECK_STR( "int8_to_hex(0)",    buf, "00" );
    int8_to_hex( -1,   buf ); CHECK_STR( "int8_to_hex(-1)",   buf, "FF" );
    int8_to_hex(  127, buf ); CHECK_STR( "int8_to_hex(127)",  buf, "7F" );
    int8_to_hex( -128, buf ); CHECK_STR( "int8_to_hex(-128)", buf, "80" );
}

static void test_uint16_to_hex( void ) {
    log_printf( &logger, "\n-- uint16_to_hex --\n" );
    uint16_to_hex( 0x0000, buf ); CHECK_STR( "uint16_to_hex(0x0000)", buf, "0000" );
    uint16_to_hex( 0xFFFF, buf ); CHECK_STR( "uint16_to_hex(0xFFFF)", buf, "FFFF" );
    uint16_to_hex( 0x1234, buf ); CHECK_STR( "uint16_to_hex(0x1234)", buf, "1234" );
    uint16_to_hex( 0xABCD, buf ); CHECK_STR( "uint16_to_hex(0xABCD)", buf, "ABCD" );
}

static void test_uint32_to_hex( void ) {
    log_printf( &logger, "\n-- uint32_to_hex --\n" );
    uint32_to_hex( 0x00000000UL, buf ); CHECK_STR( "uint32_to_hex(0x00000000)", buf, "00000000" );
    uint32_to_hex( 0xFFFFFFFFUL, buf ); CHECK_STR( "uint32_to_hex(0xFFFFFFFF)", buf, "FFFFFFFF" );
    uint32_to_hex( 0x12345678UL, buf ); CHECK_STR( "uint32_to_hex(0x12345678)", buf, "12345678" );
    uint32_to_hex( 0xDEADBEEFUL, buf ); CHECK_STR( "uint32_to_hex(0xDEADBEEF)", buf, "DEADBEEF" );
}

static void test_int32_to_hex( void ) {
    log_printf( &logger, "\n-- int32_to_hex --\n" );
    int32_to_hex(  0,          buf ); CHECK_STR( "int32_to_hex(0)",          buf, "00000000" );
    int32_to_hex( -1,          buf ); CHECK_STR( "int32_to_hex(-1)",         buf, "FFFFFFFF" );
    int32_to_hex(  2147483647, buf ); CHECK_STR( "int32_to_hex(INT32_MAX)",  buf, "7FFFFFFF" );
}

static void test_uint8_to_str( void ) {
    log_printf( &logger, "\n-- uint8_to_str --\n" );
    // right-justified in 3 chars + NUL, leading spaces
    uint8_to_str( 0,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint8_to_str(0)",   buf, "0"   );
    uint8_to_str( 255, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint8_to_str(255)", buf, "255" );
    uint8_to_str( 42,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint8_to_str(42)",  buf, "42"  );
}

static void test_uint8_to_str_with_zeros( void ) {
    log_printf( &logger, "\n-- uint8_to_str_with_zeros --\n" );
    uint8_to_str_with_zeros( 0,   buf ); CHECK_STR( "uint8_to_str_with_zeros(0)",   buf, "000" );
    uint8_to_str_with_zeros( 255, buf ); CHECK_STR( "uint8_to_str_with_zeros(255)", buf, "255" );
    uint8_to_str_with_zeros( 7,   buf ); CHECK_STR( "uint8_to_str_with_zeros(7)",   buf, "007" );
}

static void test_int8_to_str( void ) {
    log_printf( &logger, "\n-- int8_to_str --\n" );
    int8_to_str(  0,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int8_to_str(0)",    buf, "0"    );
    int8_to_str(  127, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int8_to_str(127)",  buf, "127"  );
    int8_to_str( -1,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int8_to_str(-1)",   buf, "-1"   );
    int8_to_str( -128, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int8_to_str(-128)", buf, "-128" );
}

static void test_int8_to_str_with_zeros( void ) {
    log_printf( &logger, "\n-- int8_to_str_with_zeros --\n" );
    int8_to_str_with_zeros(  0,   buf ); CHECK_STR( "int8_to_str_with_zeros(0)",    buf, "0000"  );
    int8_to_str_with_zeros(  127, buf ); CHECK_STR( "int8_to_str_with_zeros(127)",  buf, "0127"  );
    int8_to_str_with_zeros( -1,   buf ); CHECK_STR( "int8_to_str_with_zeros(-1)",   buf, "-001"  );
    int8_to_str_with_zeros( -128, buf ); CHECK_STR( "int8_to_str_with_zeros(-128)", buf, "-128"  );
}

static void test_uint16_to_str( void ) {
    log_printf( &logger, "\n-- uint16_to_str --\n" );
    uint16_to_str( 0,     buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint16_to_str(0)",     buf, "0"     );
    uint16_to_str( 65535, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint16_to_str(65535)", buf, "65535" );
    uint16_to_str( 1000,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint16_to_str(1000)",  buf, "1000"  );
}

static void test_uint16_to_str_with_zeros( void ) {
    log_printf( &logger, "\n-- uint16_to_str_with_zeros --\n" );
    uint16_to_str_with_zeros( 0,     buf ); CHECK_STR( "uint16_to_str_with_zeros(0)",     buf, "00000" );
    uint16_to_str_with_zeros( 65535, buf ); CHECK_STR( "uint16_to_str_with_zeros(65535)", buf, "65535" );
    uint16_to_str_with_zeros( 42,    buf ); CHECK_STR( "uint16_to_str_with_zeros(42)",    buf, "00042" );
}

static void test_int16_to_str( void ) {
    log_printf( &logger, "\n-- int16_to_str --\n" );
    int16_to_str(  0,      buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int16_to_str(0)",      buf, "0"      );
    int16_to_str(  32767,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int16_to_str(32767)",  buf, "32767"  );
    int16_to_str( -1,      buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int16_to_str(-1)",     buf, "-1"     );
    int16_to_str( -32768,  buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int16_to_str(-32768)", buf, "-32768" );
}

static void test_int16_to_str_with_zeros( void ) {
    log_printf( &logger, "\n-- int16_to_str_with_zeros --\n" );
    int16_to_str_with_zeros(  0,     buf ); CHECK_STR( "int16_to_str_with_zeros(0)",      buf, "000000"  );
    int16_to_str_with_zeros(  32767, buf ); CHECK_STR( "int16_to_str_with_zeros(32767)",  buf, "032767"  );
    int16_to_str_with_zeros( -1,     buf ); CHECK_STR( "int16_to_str_with_zeros(-1)",     buf, "-00001"  );
    int16_to_str_with_zeros( -32768, buf ); CHECK_STR( "int16_to_str_with_zeros(-32768)", buf, "-32768"  );
}

static void test_uint32_to_str( void ) {
    log_printf( &logger, "\n-- uint32_to_str --\n" );
    uint32_to_str( 0UL,         buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint32_to_str(0)",          buf, "0"          );
    uint32_to_str( 4294967295UL,buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint32_to_str(UINT32_MAX)", buf, "4294967295" );
    uint32_to_str( 1000000UL,   buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "uint32_to_str(1000000)",   buf, "1000000"    );
}

static void test_uint32_to_str_with_zeros( void ) {
    log_printf( &logger, "\n-- uint32_to_str_with_zeros --\n" );
    uint32_to_str_with_zeros( 0UL,          buf ); CHECK_STR( "uint32_to_str_with_zeros(0)",          buf, "0000000000" );
    uint32_to_str_with_zeros( 4294967295UL, buf ); CHECK_STR( "uint32_to_str_with_zeros(UINT32_MAX)", buf, "4294967295" );
    uint32_to_str_with_zeros( 42UL,         buf ); CHECK_STR( "uint32_to_str_with_zeros(42)",         buf, "0000000042" );
}

static void test_int32_to_str( void ) {
    log_printf( &logger, "\n-- int32_to_str --\n" );
    int32_to_str(  0,           buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int32_to_str(0)",           buf, "0"           );
    int32_to_str(  2147483647L, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int32_to_str(INT32_MAX)",   buf, "2147483647"  );
    int32_to_str( -1L,          buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int32_to_str(-1)",          buf, "-1"          );
    int32_to_str( -2147483647L, buf ); r_trim( buf ); l_trim( buf ); CHECK_STR( "int32_to_str(-2147483647)", buf, "-2147483647" );
}

static void test_int32_to_str_with_zeros( void ) {
    log_printf( &logger, "\n-- int32_to_str_with_zeros --\n" );
    int32_to_str_with_zeros(  0,           buf ); CHECK_STR( "int32_to_str_with_zeros(0)",          buf, "00000000000"  );
    int32_to_str_with_zeros(  2147483647L, buf ); CHECK_STR( "int32_to_str_with_zeros(INT32_MAX)",  buf, "02147483647"  );
    int32_to_str_with_zeros( -1L,          buf ); CHECK_STR( "int32_to_str_with_zeros(-1)",         buf, "-0000000001"  );
    int32_to_str_with_zeros( -2147483647L, buf ); CHECK_STR( "int32_to_str_with_zeros(-INT32_MAX)", buf, "-2147483647"  );
}

static void test_dec_bcd( void ) {
    log_printf( &logger, "\n-- dec_to_bcd / bcd_to_dec --\n" );
    CHECK_U8( "dec_to_bcd(0)",   dec_to_bcd( 0 ),   0x00 );
    CHECK_U8( "dec_to_bcd(9)",   dec_to_bcd( 9 ),   0x09 );
    CHECK_U8( "dec_to_bcd(10)",  dec_to_bcd( 10 ),  0x10 );
    CHECK_U8( "dec_to_bcd(99)",  dec_to_bcd( 99 ),  0x99 );
    CHECK_U8( "bcd_to_dec(0x00)", bcd_to_dec( 0x00 ), 0  );
    CHECK_U8( "bcd_to_dec(0x09)", bcd_to_dec( 0x09 ), 9  );
    CHECK_U8( "bcd_to_dec(0x10)", bcd_to_dec( 0x10 ), 10 );
    CHECK_U8( "bcd_to_dec(0x99)", bcd_to_dec( 0x99 ), 99 );
}

static void test_dec_bcd16( void ) {
    log_printf( &logger, "\n-- dec_to_bcd16 / bcd_to_dec16 --\n" );
    CHECK_U16( "dec_to_bcd16(0)",    dec_to_bcd16( 0 ),    0x0000 );
    CHECK_U16( "dec_to_bcd16(1234)", dec_to_bcd16( 1234 ), 0x1234 );
    CHECK_U16( "dec_to_bcd16(9999)", dec_to_bcd16( 9999 ), 0x9999 );
    CHECK_U16( "bcd_to_dec16(0x0000)", bcd_to_dec16( 0x0000 ), 0    );
    CHECK_U16( "bcd_to_dec16(0x1234)", bcd_to_dec16( 0x1234 ), 1234 );
    CHECK_U16( "bcd_to_dec16(0x9999)", bcd_to_dec16( 0x9999 ), 9999 );
}

static void test_trim( void ) {
    log_printf( &logger, "\n-- r_trim / l_trim --\n" );
    strcpy( buf, "hello   " ); r_trim( buf ); CHECK_STR( "r_trim trailing",  buf, "hello"   );
    strcpy( buf, "   hello" ); l_trim( buf ); CHECK_STR( "l_trim leading",   buf, "hello"   );
    strcpy( buf, "  hi  "  ); r_trim( buf ); l_trim( buf ); CHECK_STR( "trim both", buf, "hi" );
    strcpy( buf, "none"    ); r_trim( buf ); l_trim( buf ); CHECK_STR( "trim none",  buf, "none" );
}

static void test_float_to_str( void ) {
    log_printf( &logger, "\n-- float_to_str --\n" );
    float_to_str( 0.0f,      buf ); CHECK_STR( "float_to_str(0)",       buf, "0"       );
    float_to_str( 1.0f,      buf ); CHECK_STR( "float_to_str(1)",       buf, "1"       );
    float_to_str( -1.0f,     buf ); CHECK_STR( "float_to_str(-1)",      buf, "-1"      );
    float_to_str( 3.14f,     buf ); CHECK_STR( "float_to_str(3.14)",    buf, "3.14"    );
    float_to_str( -3.14f,    buf ); CHECK_STR( "float_to_str(-3.14)",   buf, "-3.14"   );
    float_to_str( 123456.0f, buf ); CHECK_STR( "float_to_str(123456)",  buf, "123456"  );
    float_to_str( 1234567.0f,buf ); CHECK_STR( "float_to_str(1234567)", buf, "1234567" );
    float_to_str( 0.001f,    buf ); CHECK_STR( "float_to_str(0.001)",   buf, "1e-3"    );
}

static void test_float_to_str_prec( void ) {
    log_printf( &logger, "\n-- float_to_str_prec --\n" );
    float_to_str_prec( 12.435468f,  buf, sizeof(buf), 2 ); CHECK_STR( "prec(12.435468,2)",  buf, "12.44"    );
    float_to_str_prec( 12.435468f,  buf, sizeof(buf), 4 ); CHECK_STR( "prec(12.435468,4)",  buf, "12.4355"  );
    float_to_str_prec( 0.0f,        buf, sizeof(buf), 3 ); CHECK_STR( "prec(0,3)",          buf, "0.000"    );
    float_to_str_prec( 1.0f,        buf, sizeof(buf), 0 ); CHECK_STR( "prec(1,0)",          buf, "1"        );
    float_to_str_prec( -3.14159f,   buf, sizeof(buf), 4 ); CHECK_STR( "prec(-3.14159,4)",   buf, "-3.1416"  );
    float_to_str_prec( 100.0f,      buf, sizeof(buf), 2 ); CHECK_STR( "prec(100,2)",        buf, "100.00"   );
    float_to_str_prec( 0.001f,      buf, sizeof(buf), 5 ); CHECK_STR( "prec(0.001,5)",      buf, "0.00100"  );
    float_to_str_prec( 999999.9f,   buf, sizeof(buf), 1 ); CHECK_STR( "prec(999999.9,1)",   buf, "999999.9");
}

static void test_str_to_uint8( void ) {
    log_printf( &logger, "\n-- str_to_uint8 --\n" );
    CHECK_U8( "str_to_uint8(\"0\")",   str_to_uint8( "0"   ), 0   );
    CHECK_U8( "str_to_uint8(\"255\")", str_to_uint8( "255" ), 255 );
    CHECK_U8( "str_to_uint8(\"042\")", str_to_uint8( "042" ), 42  );
    CHECK_U8( "str_to_uint8(\"bad\")", str_to_uint8( "bad" ), 0   );
}

static void test_str_to_int8( void ) {
    log_printf( &logger, "\n-- str_to_int8 --\n" );
    CHECK_I8( "str_to_int8(\"0\")",    str_to_int8( "0"    ),  0   );
    CHECK_I8( "str_to_int8(\"127\")",  str_to_int8( "127"  ),  127 );
    CHECK_I8( "str_to_int8(\"-1\")",   str_to_int8( "-1"   ), -1   );
    CHECK_I8( "str_to_int8(\"-128\")", str_to_int8( "-128" ), -128 );
}

static void test_str_to_uint16( void ) {
    log_printf( &logger, "\n-- str_to_uint16 --\n" );
    CHECK_U16( "str_to_uint16(\"0\")",     str_to_uint16( "0"     ), 0     );
    CHECK_U16( "str_to_uint16(\"65535\")", str_to_uint16( "65535" ), 65535 );
    CHECK_U16( "str_to_uint16(\"1000\")",  str_to_uint16( "1000"  ), 1000  );
    CHECK_U16( "str_to_uint16(\"bad\")",   str_to_uint16( "bad"   ), 0     );
}

static void test_str_to_int16( void ) {
    log_printf( &logger, "\n-- str_to_int16 --\n" );
    CHECK_I16( "str_to_int16(\"0\")",      str_to_int16( "0"      ),  0     );
    CHECK_I16( "str_to_int16(\"32767\")",  str_to_int16( "32767"  ),  32767 );
    CHECK_I16( "str_to_int16(\"-1\")",     str_to_int16( "-1"     ), -1     );
    CHECK_I16( "str_to_int16(\"-32767\")", str_to_int16( "-32767" ), -32767 );
}

static void test_str_to_uint32( void ) {
    log_printf( &logger, "\n-- str_to_uint32 --\n" );
    CHECK_U32( "str_to_uint32(\"0\")",          str_to_uint32( "0"          ), 0UL          );
    CHECK_U32( "str_to_uint32(\"4294967295\")",  str_to_uint32( "4294967295" ), 4294967295UL );
    CHECK_U32( "str_to_uint32(\"1000000\")",     str_to_uint32( "1000000"   ), 1000000UL    );
    CHECK_U32( "str_to_uint32(\"bad\")",         str_to_uint32( "bad"       ), 0UL          );
}

static void test_str_to_int32( void ) {
    log_printf( &logger, "\n-- str_to_int32 --\n" );
    CHECK_I32( "str_to_int32(\"0\")",           str_to_int32( "0"           ),  0L          );
    CHECK_I32( "str_to_int32(\"2147483647\")",   str_to_int32( "2147483647"  ),  2147483647L );
    CHECK_I32( "str_to_int32(\"-1\")",           str_to_int32( "-1"          ), -1L          );
    CHECK_I32( "str_to_int32(\"-2147483647\")",  str_to_int32( "-2147483647" ), -2147483647L );
}

static void test_str_to_float( void ) {
    log_printf( &logger, "\n-- str_to_float --\n" );
    CHECK_F( "str_to_float(\"0.0\")",    str_to_float( "0.0"    ),  0.0f    );
    CHECK_F( "str_to_float(\"1.0\")",    str_to_float( "1.0"    ),  1.0f    );
    CHECK_F( "str_to_float(\"-1.5\")",   str_to_float( "-1.5"   ), -1.5f    );
    CHECK_F( "str_to_float(\"3.14\")",   str_to_float( "3.14"   ),  3.14f   );
    CHECK_F( "str_to_float(\"123.456\")",str_to_float( "123.456"),  123.456f );
}

static void test_hex_to_uint8( void ) {
    log_printf( &logger, "\n-- hex_to_uint8 --\n" );
    CHECK_U8( "hex_to_uint8(\"00\")", hex_to_uint8( "00" ), 0x00 );
    CHECK_U8( "hex_to_uint8(\"FF\")", hex_to_uint8( "FF" ), 0xFF );
    CHECK_U8( "hex_to_uint8(\"ff\")", hex_to_uint8( "ff" ), 0xFF );
    CHECK_U8( "hex_to_uint8(\"AB\")", hex_to_uint8( "AB" ), 0xAB );
    CHECK_U8( "hex_to_uint8(\"0F\")", hex_to_uint8( "0F" ), 0x0F );
}

static void test_hex_to_uint16( void ) {
    log_printf( &logger, "\n-- hex_to_uint16 --\n" );
    CHECK_U16( "hex_to_uint16(\"0000\")", hex_to_uint16( "0000" ), 0x0000 );
    CHECK_U16( "hex_to_uint16(\"FFFF\")", hex_to_uint16( "FFFF" ), 0xFFFF );
    CHECK_U16( "hex_to_uint16(\"1234\")", hex_to_uint16( "1234" ), 0x1234 );
    CHECK_U16( "hex_to_uint16(\"abcd\")", hex_to_uint16( "abcd" ), 0xABCD );
}

static void test_hex_to_uint32( void ) {
    log_printf( &logger, "\n-- hex_to_uint32 --\n" );
    CHECK_U32( "hex_to_uint32(\"00000000\")", hex_to_uint32( "00000000" ), 0x00000000UL );
    CHECK_U32( "hex_to_uint32(\"FFFFFFFF\")", hex_to_uint32( "FFFFFFFF" ), 0xFFFFFFFFUL );
    CHECK_U32( "hex_to_uint32(\"12345678\")", hex_to_uint32( "12345678" ), 0x12345678UL );
    CHECK_U32( "hex_to_uint32(\"DEADBEEF\")", hex_to_uint32( "DEADBEEF" ), 0xDEADBEEFUL );
}

static void test_hex_to_int( void ) {
    log_printf( &logger, "\n-- hex_to_int8/16/32 --\n" );
    CHECK_I8(  "hex_to_int8(\"FF\")",       hex_to_int8( "FF" ),         -1          );
    CHECK_I8(  "hex_to_int8(\"7F\")",       hex_to_int8( "7F" ),          127        );
    CHECK_I8(  "hex_to_int8(\"80\")",       hex_to_int8( "80" ),         -128        );
    CHECK_I16( "hex_to_int16(\"FFFF\")",    hex_to_int16( "FFFF" ),      -1          );
    CHECK_I16( "hex_to_int16(\"7FFF\")",    hex_to_int16( "7FFF" ),       32767      );
    CHECK_I32( "hex_to_int32(\"FFFFFFFF\")",hex_to_int32( "FFFFFFFF" ),  -1L         );
    CHECK_I32( "hex_to_int32(\"7FFFFFFF\")",hex_to_int32( "7FFFFFFF" ),   2147483647L );
}

// ----------------------------------------------------------------- MAIN

int main( void ) {
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );

    log_printf( &logger, "\n=== CONVERSIONS TEST ===\n" );

    test_uint8_to_hex();
    test_int8_to_hex();
    test_uint16_to_hex();
    test_uint32_to_hex();
    test_int32_to_hex();

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

    test_dec_bcd();
    test_dec_bcd16();
    test_trim();
    test_float_to_str();
    test_float_to_str_prec();

    test_str_to_uint8();
    test_str_to_int8();
    test_str_to_uint16();
    test_str_to_int16();
    test_str_to_uint32();
    test_str_to_int32();
    test_str_to_float();

    test_hex_to_uint8();
    test_hex_to_uint16();
    test_hex_to_uint32();
    test_hex_to_int();

    log_printf( &logger, "\n=== DONE: %u passed, %u failed ===\n", pass_count, fail_count );

    return 0;
}
