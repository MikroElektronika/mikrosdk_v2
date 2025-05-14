// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "board.h"
#include "log.h"
#include "sprint.h"
#include "drv_digital_out.h"
#include "delays.h"
#include <stdio.h>
#ifdef __XC8__
#include "string.h"
#endif

// ----------------------------------------------------------------- MACROS

#define TEST_LED_F HAL_PIN_NC // TODO: Define a pin, i.e. GPIO_PD0
#define TEST_LED_L HAL_PIN_NC // TODO: Define a pin, i.e. GPIO_PD1
#define TEST_LED_I HAL_PIN_NC // TODO: Define a pin, i.e. GPIO_PD2

// ----------------------------------------------------------------- VARIABLES

// Logger instance
static log_t logger;
static log_cfg_t log_cfg;

// Failure counters for different tests
uint8_t fail_count_f = 0;
uint8_t fail_count_l = 0;
uint8_t fail_count_i = 0;
uint8_t match = 0;

// LED instances for status indication
digital_out_t ledf, ledl, ledi;

// Test variables
char buffer[256];
int ret;

// ----------------------------------------------------------------- STATIC FUNCTION DECLARATIONS

/**
 * @brief Compares the result of sprintf_me formatting.
 *
 * @param buf The formatted string.
 * @param expected The expected string.
 * @param ret The return value from the formatting function.
 */
static void CHECK_RESULTF( char *buf, char *expected, char* ret );

/**
 * @brief Compares the result of sprintl_me formatting.
 *
 * @param buf The formatted string.
 * @param expected The expected string.
 * @param ret The return value from the formatting function.
 */
static void CHECK_RESULTL( char *buf, char *expected, char* ret );

/**
 * @brief Compares the result of sprinti_me formatting.
 *
 * @param buf The formatted string.
 * @param expected The expected string.
 * @param ret The return value from the formatting function.
 */
static void CHECK_RESULTI( char *buf, char *expected, char* ret );

/**
 * @brief Perform sprintf tests with different formats and check results.
 */
static void perform_sprintf_tests( void );

/**
 * @brief Perform sprintl tests with different formats and check results.
 */
static void perform_sprintl_tests( void );

/**
 * @brief Perform sprinti tests with different formats and check results.
 */
static void perform_sprinti_tests( void );

/**
 * @brief Initialize LEDs for indicating test results.
 */
static void initialize_leds( void );

/**
 * @brief Update LED status based on failure counts.
 */
static void update_led_status( void );

// ----------------------------------------------------------------- MAIN FUNCTION

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize logger
    LOG_MAP_USB_UART(log_cfg);
    log_init( &logger, &log_cfg );

    // Perform sprintf tests
    log_printf( &logger, "\nSPRINTF TESTS:\n" );
    perform_sprintf_tests();
    Delay_ms( 500 );

    // Perform sprintl tests
    log_printf( &logger, "\nSPRINTL TESTS:\n" );
    perform_sprintl_tests();
    Delay_ms( 500 );

    // Perform sprinti tests
    log_printf( &logger, "\nSPRINTI TESTS:\n" );
    perform_sprinti_tests();
    Delay_ms( 500 );

    // Summary of failures
    log_printf( &logger, "sprintf_me failures: %d\n", ( uint16_t )fail_count_f );
    log_printf( &logger, "sprintl_me failures: %d\n", ( uint16_t )fail_count_l );
    log_printf( &logger, "sprinti_me failures: %d\n", ( uint16_t )fail_count_i );

    // Initialize LEDs and update their status based on test results
    initialize_leds();
    update_led_status();

    return 0;
}

// ----------------------------------------------------------------- STATIC FUNCTIONS

static void CHECK_RESULTF( char *buf, char *expected, char* ret ) {
    match = ( strcmp( buf, expected ) == 0 );
    if ( !match ) {
        fail_count_f++;
        log_printf( &logger, "sprintf: \"%s\" | Return: %d | Match: %s\n", buf, ret, match ? "true" : "false" );
    }
}

static void CHECK_RESULTL( char *buf, char *expected, char* ret ) {
    match = ( strcmp( buf, expected ) == 0 );
    if ( !match ) {
        fail_count_l++;
        log_printf( &logger, "sprintl: \"%s\" | Return: %d | Match: %s\n", buf, ret, match ? "true" : "false" );
    }
}

static void CHECK_RESULTI( char *buf, char *expected, char* ret ) {
    match = ( strcmp( buf, expected ) == 0 );
    if ( !match ) {
        fail_count_i++;
        log_printf( &logger, "sprinti: \"%s\" | Return: %d | Match: %s\n", buf, ret, match ? "true" : "false" );
    }
}

static void perform_sprintf_tests( void ) {
    ret = sprintf_me( buffer, "Test string: %s", "hello" );
    CHECK_RESULTF( buffer, "Test string: hello", ret );

    ret = sprintf_me( buffer, "Signed decimal: %d", -12345 );
    CHECK_RESULTF( buffer, "Signed decimal: -12345", ret );

    ret = sprintf_me( buffer, "Unsigned decimal: %u", 12345 );
    CHECK_RESULTF( buffer, "Unsigned decimal: 12345", ret );

    ret = sprintf_me( buffer, "Hexadecimal (lowercase): %x", 255 );
    CHECK_RESULTF( buffer, "Hexadecimal (lowercase): ff", ret );

    ret = sprintf_me( buffer, "Hexadecimal (uppercase): %X", 255 );
    CHECK_RESULTF( buffer, "Hexadecimal (uppercase): FF", ret );

    ret = sprintf_me( buffer, "Octal: %o", 255 );
    CHECK_RESULTF( buffer, "Octal: 377", ret );

    ret = sprintf_me( buffer, "Character: %c", 'A' );
    CHECK_RESULTF( buffer, "Character: A", ret );

    ret = sprintf_me( buffer, "Float: %f", 123.456 );
    CHECK_RESULTF( buffer, "Float: 123.456000", ret );

    ret = sprintf_me( buffer, "Float with precision: %.2f", 123.456 );
    CHECK_RESULTF( buffer, "Float with precision: 123.46", ret );

    ret = sprintf_me( buffer, "Long integer: %ld", ( unsigned long )1234567890L );
    CHECK_RESULTF( buffer, "Long integer: 1234567890", ret );

    ret = sprintf_me( buffer, "Unsigned long: %lu", ( unsigned long )1234567890UL );
    CHECK_RESULTF( buffer, "Unsigned long: 1234567890", ret );

    ret = sprintf_me( buffer, "Long hexadecimal: %lx", ( unsigned long )255 );
    CHECK_RESULTF( buffer, "Long hexadecimal: ff", ret );

    ret = sprintf_me( buffer, "Long octal: %lo", ( unsigned long )255 );
    CHECK_RESULTF( buffer, "Long octal: 377", ret );

    ret = sprintf_me( buffer, "Short integer: %hd", -32768 );
    CHECK_RESULTF( buffer, "Short integer: -32768", ret );

    ret = sprintf_me( buffer, "Unsigned short: %hu", 65535 );
    CHECK_RESULTF( buffer, "Unsigned short: 65535", ret );

    ret = sprintf_me( buffer, "Short hexadecimal: %hx", 255 );
    CHECK_RESULTF( buffer, "Short hexadecimal: ff", ret );

    ret = sprintf_me( buffer, "Short octal: %ho", 255 );
    CHECK_RESULTF( buffer, "Short octal: 377", ret );
}

static void perform_sprintl_tests( void ) {
    ret = sprintl_me( buffer, "Test string: %s", "hello" );
    CHECK_RESULTL( buffer, "Test string: hello", ret );

    ret = sprintl_me( buffer, "Signed decimal: %d", -12345 );
    CHECK_RESULTL( buffer, "Signed decimal: -12345", ret );

    ret = sprintl_me( buffer, "Unsigned decimal: %u", 12345 );
    CHECK_RESULTL( buffer, "Unsigned decimal: 12345", ret );

    ret = sprintl_me( buffer, "Hexadecimal (lowercase): %x", 255 );
    CHECK_RESULTL( buffer, "Hexadecimal (lowercase): ff", ret );

    ret = sprintl_me( buffer, "Hexadecimal (uppercase): %X", 255 );
    CHECK_RESULTL( buffer, "Hexadecimal (uppercase): FF", ret );

    ret = sprintl_me( buffer, "Octal: %o", 255 );
    CHECK_RESULTL( buffer, "Octal: 377", ret );

    ret = sprintl_me( buffer, "Character: %c", 'A' );
    CHECK_RESULTL( buffer, "Character: A", ret );

    ret = sprintl_me( buffer, "Long integer: %ld", ( unsigned long )1234567890L );
    CHECK_RESULTL( buffer, "Long integer: 1234567890", ret );

    ret = sprintl_me( buffer, "Unsigned long: %lu", ( unsigned long )1234567890UL );
    CHECK_RESULTL( buffer, "Unsigned long: 1234567890", ret );

    ret = sprintl_me( buffer, "Long hexadecimal: %lx", ( unsigned long )255 );
    CHECK_RESULTL( buffer, "Long hexadecimal: ff", ret );

    ret = sprintl_me( buffer, "Long octal: %lo", ( unsigned long )255 );
    CHECK_RESULTL( buffer, "Long octal: 377", ret );

    ret = sprintl_me( buffer, "Short integer: %hd", -32768 );
    CHECK_RESULTL( buffer, "Short integer: -32768", ret );

    ret = sprintl_me( buffer, "Unsigned short: %hu", 65535 );
    CHECK_RESULTL( buffer, "Unsigned short: 65535", ret );

    ret = sprintl_me( buffer, "Short hexadecimal: %hx", 255 );
    CHECK_RESULTL( buffer, "Short hexadecimal: ff", ret );

    ret = sprintl_me( buffer, "Short octal: %ho", 255 );
    CHECK_RESULTL( buffer, "Short octal: 377", ret );
}

static void perform_sprinti_tests( void ) {
    ret = sprinti_me( buffer, "Test string: %s", "hello" );
    CHECK_RESULTI( buffer, "Test string: hello", ret );

    ret = sprinti_me( buffer, "Signed decimal: %d", -12345 );
    CHECK_RESULTI( buffer, "Signed decimal: -12345", ret );

    ret = sprinti_me( buffer, "Unsigned decimal: %u", 12345 );
    CHECK_RESULTI( buffer, "Unsigned decimal: 12345", ret );

    ret = sprinti_me( buffer, "Hexadecimal (lowercase): %x", 255 );
    CHECK_RESULTI( buffer, "Hexadecimal (lowercase): ff", ret );

    ret = sprinti_me( buffer, "Hexadecimal (uppercase): %X", 255 );
    CHECK_RESULTI( buffer, "Hexadecimal (uppercase): FF", ret );

    ret = sprinti_me( buffer, "Octal: %o", 255 );
    CHECK_RESULTI( buffer, "Octal: 377", ret );

    ret = sprinti_me( buffer, "Character: %c", 'A' );
    CHECK_RESULTI( buffer, "Character: A", ret );

    ret = sprinti_me( buffer, "Short integer: %hd", -32768 );
    CHECK_RESULTI( buffer, "Short integer: -32768", ret );

    ret = sprinti_me( buffer, "Unsigned short: %hu", 65535 );
    CHECK_RESULTI( buffer, "Unsigned short: 65535", ret );

    ret = sprinti_me( buffer, "Short hexadecimal: %hx", 255 );
    CHECK_RESULTI( buffer, "Short hexadecimal: ff", ret );

    ret = sprinti_me( buffer, "Short octal: %ho", 255 );
    CHECK_RESULTI( buffer, "Short octal: 377", ret );
}

static void initialize_leds( void ) {
    // Initialize the LEDs used for test result indication
    digital_out_init( &ledf, TEST_LED_F );
    digital_out_init( &ledl, TEST_LED_L );
    digital_out_init( &ledi, TEST_LED_I );
    digital_out_low( &ledf );
    digital_out_low( &ledl );
    digital_out_low( &ledi );
}

static void update_led_status( void ) {
    // Update LED status based on failure counts
    if( !fail_count_f ) {
        digital_out_high( &ledf );  // Indicate success for sprintf tests
    }
    if( !fail_count_l ) {
        digital_out_high( &ledl );  // Indicate success for sprintl tests
    }
    if( !fail_count_i ) {
        digital_out_high( &ledi );  // Indicate success for sprinti tests
    }
}
