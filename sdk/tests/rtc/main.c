// ------------------------------------------------------------------ INCLUDES

#include "drv_rtc.h"
#include "log.h"
#include "board.h"
#include "drv_digital_out.h"
#include "drv_port.h"

// -------------------------------------------------------------------- MACROS

#define TEST_PIN_SIGNAL_SUCCESS_1 HAL_PIN_NC // TODO Define signal pin, for example: MIKROBUS_5_AN.
#define TEST_PIN_SIGNAL_SUCCESS_2 HAL_PIN_NC // TODO Define signal pin, for example: MIKROBUS_5_PWM.

// TODO Define test pins according to hardware.  // Example: PB0
#define TEST_PIN_SIGNAL_SOFTWARE_RESET HAL_PIN_NC
#define TEST_PIN_SIGNAL_SET_TIME       HAL_PIN_NC
#define TEST_PIN_SIGNAL_RTC_STOP       HAL_PIN_NC
#define TEST_PIN_SIGNAL_RTC_RESET      HAL_PIN_NC

// TODO Define test pins according to hardware.
// Feel free to add additional pins if needed.
#define TEST_PIN_1 HAL_PIN_NC
#define TEST_PIN_2 HAL_PIN_NC
#define TEST_PIN_3 HAL_PIN_NC
#define TEST_PIN_4 HAL_PIN_NC
#define TEST_PIN_5 HAL_PIN_NC

// TODO Define port used for testing.
#define PORT_NAME HAL_PORT_NC // TODO Define signal port, for example: PORT_B.

#define signal_error(pin) digital_out_init(&test_pin, pin); \
                          digital_out_high(&test_pin); \
                          while(1)

#define signal_success(pin) digital_out_init(&test_pin, pin); \
                            digital_out_high(&test_pin)

#define signal_info(pin) digital_out_init(&test_pin, pin); \
                         digital_out_high(&test_pin);

#define wait_test_time      Delay_ms(500)
#define wait_long_test_time Delay_ms(5000)

#define MASK     0xFFFF
#define SET_PORT uint8_t turn = time.second % 8;\
                 if(!turn) {value = 255;}\
                 else {\
                 while (turn) {\
                 value = value << 1;\
                 value++;\
                 turn--;}}

#define EVERY_8_SECONDS  (time.second % 8 == 0 && time.second)
#define EVERY_10_SECONDS (time.second % 10 == 0 && time.second)
#define NOT_FIVE_MINUTE  time.minute != 5
#define RESET_PORT       value = 0

#define set_time_value time.second = 0; \
                       time.minute = 5; \
                       time.hour = 0; \
                       time.day_week = 1; \
                       time.day_month = 1; \
                       time.month = 1; \
                       time.year = 0

// TODO define the default time values.
#define time_default_value time.second = 0; \
                           time.minute = 1; \
                           time.hour = 0; \
                           time.day_week = 1; \
                           time.day_month = 1; \
                           time.month = 1; \
                           time.year = 0

// TODO select the test to do.
#define RTC_START           1
#define FIRST_INIT          1
#define SOFTWARE_RESET_TEST 0
#define SET_TIME_TEST       0
#define RTC_STOP_TEST       0
#define RTC_RESET_TEST      0

// ------------------------------------------------------------------ VARIABLES

static log_t logger;
static rtc_t time;
static digital_out_t test_pin;
static port_t port;
static uint8_t mask;
static uint8_t value = 0;
static uint32_t check_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init()
{
    port_init( &port, PORT_NAME, MASK, GPIO_DIGITAL_OUTPUT );
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
    if ( RTC_ERROR == rtc_configure_default( &time ) ) {
        signal_error( TEST_PIN_1 );
    }
    #endif
    if ( RTC_ERROR == rtc_start() ) {
        signal_error( TEST_PIN_2 );
    }
    #endif
}

void application_task()
{
    while ( 1 ) {
        if ( RTC_ERROR == rtc_get_time( &time ) ) {
            signal_error( TEST_PIN_3 );
        }
        if ( time.second != check_value ) {
            // Set the value for the leds on the chosen port.
            SET_PORT;
            // The leds will show the count of the rtc.
            port_write( &port, value );
            log_printf( &logger, "%dh : %dm : %ds\n", time.hour, time.minute, time.second );
            // Reset the value for the leds on the chosen port.
            RESET_PORT;
        }

        check_value = time.second;

        #if RTC_STOP_TEST
        // RTC will stop for 5 seconds, show that the time did not change and then restart.
        if ( RTC_SUCCESS == rtc_stop() ) {
            signal_info( TEST_PIN_SIGNAL_RTC_STOP );
            wait_long_test_time;
            log_printf( &logger, "%dh: %dm: %ds
", time.hour, time.minute, time.second );
            rtc_start();
        }
        #endif

        #if SET_TIME_TEST
        // RTC will set the time to 5 minutes when time.minute is not 5 minutes.
        if ( NOT_FIVE_MINUTE ) {
            set_time_value;
            if ( RTC_SUCCESS == rtc_set_time( &time ) ) {
                signal_info( TEST_PIN_SIGNAL_SOFTWARE_RESET );
            }
        }
        #endif

        #if SOFTWARE_RESET_TEST
        // Software will perform a software reset every 8 seconds.
        if ( EVERY_8_SECONDS ) {
            // If software reset is a success, TEST_PIN_SIGNAL_SOFTWARE_RESET should turn off.
            // TODO for MCUs that doesn't have software reset that can do that because of the HW
            // restrictions, WatchDog use is needed.
            signal_info( TEST_PIN_SIGNAL_SOFTWARE_RESET );
            wait_test_time;
            software_reset();
        }
        #endif

        #if RTC_RESET_TEST
        // RTC will restart to his default values every 10 seconds.
        if ( EVERY_10_SECONDS ) {
            signal_info( TEST_PIN_SIGNAL_RTC_RESET );
            rtc_reset();
        }
        #endif
    }
}

int main( void )
{
    application_init();

    application_task();

    return 0;
}
