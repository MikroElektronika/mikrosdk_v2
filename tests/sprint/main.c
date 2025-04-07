// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

// #include "mcu.h"
#include "board.h"
#include "log.h"
#include "sprint.h"
#include "delays.h"
#include <stdio.h>
#ifdef __XC8__
#include "string.h"
#endif
// -------------------------------------------------------------------- MACROS
#define TEST_PIN HAL_PIN_NC
#define END_PIN HAL_PIN_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

// ----------------------------------------------------------------- VARIABLES

// TODO Esma
static log_t logger;

int sprinti_me(char *str, const char *format, ...);
int sprintl_me(char *str, const char *format, ...);
int sprintf_me(char *str, const char *format, ...);

void test_sprinti(void) {
    char buffer[64];
    int ret;

    log_printf(&logger,"=== Testing sprinti_me ===\n");

    ret = sprinti_me(buffer, "Test int: %d", -123);
    log_printf(&logger,"sprinti: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprinti_me(buffer, "Test unsigned: %u", 456u);
    log_printf(&logger,"sprinti: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprinti_me(buffer, "Test char: %c", 'A');
    log_printf(&logger,"sprinti: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprinti_me(buffer, "Test string: %s", "hello");
    log_printf(&logger,"sprinti: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprinti_me(buffer, "Mix: %d %u %c %s", -1, 2u, 'B', "end");
    log_printf(&logger,"sprinti: \"%s\" | Return: %d\n", buffer, ret);

    log_printf(&logger,"\n");
}

void test_sprintl(void) {
    char buffer[64];
    int ret;

    log_printf(&logger,"=== Testing sprintl_me ===\n");

    ret = sprintl_me(buffer, "Test long: %ld", -123456789L);
    log_printf(&logger,"sprintl: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintl_me(buffer, "Test unsigned long: %ul", 987654321UL);
    log_printf(&logger,"sprintl: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintl_me(buffer, "Test char: %c", 'C');
    log_printf(&logger,"sprintl: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintl_me(buffer, "Test string: %s", "world");
    log_printf(&logger,"sprintl: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintl_me(buffer, "Mix: %ld %ul %c %s", -999999L, 888888UL, 'D', "done");
    log_printf(&logger,"sprintl: \"%s\" | Return: %d\n", buffer, ret);

    log_printf(&logger,"\n");
}

void test_sprintf(void) {
    char buffer[64];
    int ret;

    log_printf(&logger,"=== Testing sprintf_me ===\n");

    // Integer
    ret = sprintf_me(buffer, "Signed int: %d", -1234);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Unsigned int: %u", 5678u);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Long
    ret = sprintf_me(buffer, "Signed long: %ld", -1234567890L);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Unsigned long: %ul", 1234567890UL);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Hexadecimal
    ret = sprintf_me(buffer, "Hex lowercase: %x", 0xDEAD);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Hex uppercase: %X", 0xBEEF);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Octal
    ret = sprintf_me(buffer, "Octal: %o", 0755);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Character
    ret = sprintf_me(buffer, "Character: %c", 'Z');
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // String
    ret = sprintf_me(buffer, "String: %s", "test string");
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Pointer (address)
    int x = 42;
    ret = sprintf_me(buffer, "Pointer: %p", (void*)&x);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Floating point numbers
    ret = sprintf_me(buffer, "Float: %.2f", 3.14159f);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Float negative: %.3f", -2.71828f);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Float zero: %.1f", 0.0f);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Float large: %.1f", 1234567.89f);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Scientific notation
    ret = sprintf_me(buffer, "Scientific: %.3e", 12345.6789);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    ret = sprintf_me(buffer, "Scientific negative: %.2E", -0.00123);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    // Mixed test
    ret = sprintf_me(buffer, "Mix: %d %u %ld %ul %x %X %o %c %s %.2f",
                  -1, 2u, -300000L, 400000UL, 0x1A2B, 0x3C4D, 0755, 'A', "mix", 6.2831);
    log_printf(&logger,"sprintf: \"%s\" | Return: %d\n", buffer, ret);

    log_printf(&logger,"\n");
}

int main(void) {
    // test_sprinti();
    // test_sprintl();
    // test_sprintf();

    char buffer[256];
    int ret;

    log_cfg_t log_cfg;  /**< Logger config object. */
    // LOG_MAP_USB_UART( log_cfg );
    // log_cfg.rx_pin = USB_UART_RX;
    // log_cfg.tx_pin = USB_UART_TX;
    // log_cfg.baud = 9600;
    // log_cfg.is_interrupt = false;
    log_init( &logger, &log_cfg );

    // Test sprintf (everything)
    ret = sprintf_me(buffer, "Test string: %s", "hello");
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Signed decimal: %d", -12345);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Unsigned decimal: %u", 12345);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Hexadecimal (lowercase): %x", 255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Hexadecimal (uppercase): %X", 255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Octal: %o", 255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Character: %c", 'A');
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Float: %f", 123.456);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Float with precision: %.2f", 123.456);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Long integer: %ld", 1234567890L);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Unsigned long: %lu", 1234567890UL);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Long hexadecimal: %lx", 255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Long octal: %lo", 255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Short integer: %hd", (short)-32768);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Unsigned short: %hu", (unsigned short)65535);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Short hexadecimal: %hx", (short)255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintf_me(buffer, "Short octal: %ho", (short)255);
    log_printf(&logger, "sprintf: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    // Test sprintl (everything except float)
    ret = sprintl_me(buffer, "Test string: %s", "hello");
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Signed decimal: %d", -12345);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Unsigned decimal: %u", 12345);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Hexadecimal (lowercase): %x", 255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Hexadecimal (uppercase): %X", 255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Octal: %o", 255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Character: %c", 'A');
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Long integer: %ld", 1234567890L);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Unsigned long: %lu", 1234567890UL);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Long hexadecimal: %lx", 255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Long octal: %lo", 255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Short integer: %hd", (short)-32768);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Unsigned short: %hu", (unsigned short)65535);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Short hexadecimal: %hx", (short)255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprintl_me(buffer, "Short octal: %ho", (short)255);
    log_printf(&logger, "sprintl: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    // Test sprinti (only integer types, no long, no float)
    ret = sprinti_me(buffer, "Test string: %s", "hello");
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Signed decimal: %d", -12345);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Unsigned decimal: %u", 12345);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Hexadecimal (lowercase): %x", 255);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Hexadecimal (uppercase): %X", 255);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Octal: %o", 255);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Character: %c", 'A');
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Short integer: %hd", (short)-32768);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Unsigned short: %hu", (unsigned short)65535);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Short hexadecimal: %hx", (short)255);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    ret = sprinti_me(buffer, "Short octal: %ho", (short)255);
    log_printf(&logger, "sprinti: \"%s\" | Return: %d\n", buffer, ret);
    Delay_ms(500);

    return 0;
}
