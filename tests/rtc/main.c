// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_rtc.h"
#include "log.h"
#include "board.h"
#include "drv_digital_out.h"
#include "drv_port.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

// TODO Define test pins for the additional test information.  // Example: GPIO_PB0
#define TEST_PIN_SIGNAL_SYSTEM_RESET HAL_PIN_NC

// TODO Define test port for visualizing the seconds counting while RTC is stopped.  // Example: GPIO_PORT_B.
#define TEST_PORT_SIGNAL_RTC_STOP HAL_PORT_NC

// TODO Define test pins according to hardware.
// Feel free to add additional pins if needed.
#define TEST_PIN_1 HAL_PIN_NC
#define TEST_PIN_2 HAL_PIN_NC
#define TEST_PIN_3 HAL_PIN_NC
#define TEST_PIN_4 HAL_PIN_NC
#define TEST_PIN_5 HAL_PIN_NC
#define TEST_PIN_6 HAL_PIN_NC
#define TEST_PIN_7 HAL_PIN_NC
#define TEST_PIN_8 HAL_PIN_NC
#define TEST_PIN_9 HAL_PIN_NC
#define TEST_PIN_10 HAL_PIN_NC

// TODO Define test port for visualizing the seconds counting.  // Example: GPIO_PORT_B.
#define PORT_RTC_SECONDS_COUNTING HAL_PORT_NC // TODO Define signal port, for example: GPIO_PORT_B.

#define signal_error(pin) digital_out_init(&test_pin, pin); \
                          digital_out_high(&test_pin); \
                          while(1)

#define signal_success(pin) digital_out_init(&test_pin, pin); \
                            digital_out_high(&test_pin)

#define wait_test_time Delay_ms(2000)
#define wait_second    Delay_ms(1000)

#define MASK     0xFFFF
#define SET_PORT uint8_t turn = time.second % 8;\
                 if(!turn) {value = 255;}\
                 else {\
                 while (turn) {\
                 value = value << 1;\
                 value++;\
                 turn--;}}

#define TIME_VALIDATION_FAIL  (time.hour >= 24 || time.minute >= 60 || time.second >= 60)
#define RESET_PORT            (value = 0)

// TODO Define the time values for the set time test.
#define set_time_value time.second = 32; \
                       time.minute = 52; \
                       time.hour = 12;

// TODO Define the default time values.
#define time_default_value time.second = 00; \
                           time.minute = 20; \
                           time.hour = 4;

// TODO Select the test.
#define RTC_START           1
#define FIRST_INIT          1
#define SYSTEM_RESET_TEST   0
#define SET_TIME_TEST       1
#define RTC_STOP_TEST       0
#define RTC_RESET_TEST      0

// ------------------------------------------------------------------ VARIABLES

static log_t logger;
static rtc_time_t time;
static digital_out_t test_pin;
static port_t port;
static port_t port_rtc_stop;
static uint8_t mask;
static uint8_t value = 0;
static uint32_t check_value;
static uint32_t check_value_minute;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init()
{
    log_cfg_t log_cfg;
    /**
     * Logger initialization.
     * Default baud rate: 115200.
     * Default log level: LOG_LEVEL_DEBUG.
     * @note If USB_UART_RX and USB_UART_TX
     * are defined as HAL_PIN_NC, you will
     * need to define them manually for log to work.
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    Delay_100ms();
    rtc_init();

    #if RTC_START
    // RTC initialization.
    #if FIRST_INIT
    time_default_value;
    if ( RTC_ERROR == rtc_set_time( &time ) ) {
        signal_error( TEST_PIN_1 );
    }
    #endif
    if ( RTC_ERROR == rtc_start() ) {
        signal_error( TEST_PIN_2 );
    }
    #endif
    if ( RTC_ERROR == rtc_get_time( &time ) ) {
            signal_error( TEST_PIN_3 );
    }
    check_value_minute = time.minute;
    port_init( &port, PORT_RTC_SECONDS_COUNTING, MASK, GPIO_DIGITAL_OUTPUT );
    port_init( &port_rtc_stop, TEST_PORT_SIGNAL_RTC_STOP, MASK, GPIO_DIGITAL_OUTPUT );
}

void application_task()
{
    bool first_pass = true;
    while ( 1 ) {
        if ( RTC_ERROR == rtc_get_time( &time ) ) {
            signal_error( TEST_PIN_4 );
        }
        if ( time.second != check_value ) {
            // Set the value for the LEDs on the chosen port.
            SET_PORT;
            // LEDs will show the seconds counting.
            port_write( &port, value );
            log_printf( &logger, "%dh : %dm : %ds\n", time.hour, time.minute, time.second );
            // Reset the value for the LEDs on the chosen port.
            RESET_PORT;
        }

        check_value = time.second;

        #if RTC_STOP_TEST
        // RTC will stop for 8 seconds, time shouldn't change for this period.
        if ( time.minute != check_value_minute ) {
            log_printf( &logger, "\nRTC will stop for 8 seconds.\n");
            log_printf( &logger, "TEST_PORT_SIGNAL_RTC_STOP will change every second during this time to prove that test is still working.\n");
            log_printf( &logger, "RTC will be stopped in a minute again.\n\n");
            check_value_minute = time.minute;
            if ( RTC_ERROR == rtc_stop() ) {
                signal_error( TEST_PIN_5 );
            }
            for ( uint8_t i = 0; i < 8; i++ ) {
                if ( RTC_ERROR == rtc_get_time( &time ) ) {
                    signal_error( TEST_PIN_6 );
                }
                log_printf( &logger, "%dh: %dm: %ds\n", time.hour, time.minute, time.second );
                port_write( &port_rtc_stop, 1<<i );
                Delay_1sec();
            }
            port_write( &port_rtc_stop, RESET_PORT );
            log_printf( &logger, "\nRTC starts counting again now.\n\n");
            if ( RTC_ERROR == rtc_start() ) {
                signal_error( TEST_PIN_7 );
            }
        }
        #endif

        #if SET_TIME_TEST
        // RTC will set the time to values define in set_time_value.
        if ( first_pass) {
            set_time_value;
            first_pass = false;
            // Checking if time values are valid.
            if ( TIME_VALIDATION_FAIL ) {
                log_printf( &logger, "\nYou are trying to set invalid time. Maximum values are 23h: 59m: 59s.");
            }
            if ( RTC_ERROR == rtc_set_time( &time ) ) {
                signal_error( TEST_PIN_8 );
            }
            if ( RTC_ERROR == rtc_get_time( &time ) ) {
                signal_error( TEST_PIN_9 );
            }
            log_printf( &logger, "\nSetting time - %dh: %dm: %ds\n", time.hour, time.minute, time.second );
        }
        #endif

        #if SYSTEM_RESET_TEST
        // MCU will be reset by software every 8 seconds.
        if ( time.minute != check_value_minute ) {
            // When system reset occurs TEST_PIN_SIGNAL_SYSTEM_RESET should turn off.
            // NOTE: For MCUs that don't have system reset feature on HW level, watchdog was used.
            log_printf( &logger, "\n.\n");
            log_printf( &logger, "TEST_PIN_SIGNAL_SYSTEM_RESET should turn off if SW reset occurs.\n\n");
            #if FIRST_INIT
            log_printf( &logger, "Time will be set to initial values.\n\n");
            #else
            log_printf( &logger, "Time will count from the last stored value.\n\n");
            #endif
            signal_success( TEST_PIN_SIGNAL_SYSTEM_RESET );
            wait_test_time;
            rtc_system_reset();
        }
        #endif

        #if RTC_RESET_TEST
        // RTC will be set to 0h: 0m: 0s every minute.
        if ( time.minute != check_value_minute ) {
            log_printf( &logger, "\nTime will be set to 0h 0m 0s.\n");
            log_printf( &logger, "Time will be reset in a minute again.\n\n");
            if ( RTC_ERROR == rtc_reset() ) {
                signal_error( TEST_PIN_10 );
            }
            Delay_100ms();
            check_value_minute = 0;
        }
        #endif
    }
}

int main( void )
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();

    application_task();

    return 0;
}
