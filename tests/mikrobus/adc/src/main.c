// ------------------------------------------------------------------ INCLUDES

#include "mikrobus_adc.h"

// -------------------------------------------------------------------- MACROS

// NOTE If set to true, test is done on a single pin.
//      If set to false, test is done on all mikroBUS pins
//      defined in 'board.h'.
#define SINGLE_MIKROBUS true

#if SINGLE_MIKROBUS
    // TODO define ADC test pin.
    // NOTE MIKROBUS_x_ADC where 'x' is mikroBUS number.
    #define TEST_PIN_ADC HAL_PIN_NC
    #define TEST_PIN_COUNT 1
    pin_name_t test_pins[TEST_PIN_COUNT] = {TEST_PIN_ADC};
#else
    #define TEST_PIN_COUNT MIKROBUS_COUNT
    pin_name_t *test_pins = test_pins_mikrobus;
#endif

// TODO Declare number of ADC reads.
#define READ_COUNT 50

// NOTE Example will use board UART pins if
//      existing.
#ifdef USB_UART_TX
    #define TEST_PIN_UART_TX USB_UART_TX
#else
    #define TEST_PIN_UART_TX HAL_PIN_NC // TODO
#endif

#ifdef USB_UART_RX
    #define TEST_PIN_UART_RX USB_UART_RX
#else
    #define TEST_PIN_UART_RX HAL_PIN_NC // TODO
#endif

// TODO Define values used in test.
#define TEST_VREF_VALUE 3.3f
#define TEST_RESOLUTION_VALUE ANALOG_IN_RESOLUTION_12_BIT

// NOTE Define max/min values for calibration.
// Optional. Set to 12bit by default.
#define READ_VALUE_MAX_CUSTOM false
#define READ_VALUE_MIN_CUSTOM false
// 16bit - <16383
// 14bit - <8191
// 12bit - <4095
// 10bit - <1023
// 8bit  - <255
// 6bit  - <127
#if READ_VALUE_MAX_CUSTOM == true
    #define READ_VALUE_MAX 0xFA0
#else
    #define READ_VALUE_MAX 0xFA0
#endif

#if READ_VALUE_MIN_CUSTOM == true
    #define READ_VALUE_MIN 0xA
#else
    #define READ_VALUE_MIN 0xA
#endif

// ----------------------------------------------------------------- VARIABLES

// ADC
static analog_in_t analog_in;
static analog_in_config_t  analog_in_cfg;

float read_voltage_value;
uint16_t analog_in_read_value;

static uint8_t analog_in_read_buffer[32];
// EOF ADC

// UART
static uart_t uart;
static uart_config_t uart_cfg;

static uint8_t uart_rx_buffer[256];
static uint8_t uart_tx_buffer[256];
// EOF UART

// ------------------------------------------------------ SUPPORTING FUNCTIONS

/*< @brief Formats messages. */
char *format_mikrobus_message( char *message, uint8_t module_id ) {
    uint8_t cnt = 0;
    char formatted_message[255];

    memset(formatted_message,0,sizeof(formatted_message));

    while ( message[cnt] != '/' ) {
        formatted_message[cnt] = message[cnt++];
    }

    formatted_message[cnt] = 49 + module_id;
    return formatted_message;
}

// ----------------------------------------------------------------- MAIN CODE

int main( void ) {
    uint8_t cnt = 0;
    uint8_t read_count = 0;

    // STEP 1: Initialize UART module.
    // -----------------------------------------------------------------------
    uart_configure_default(&uart_cfg);
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    uart_cfg.rx_pin = TEST_PIN_UART_RX;  // UART RX pin.
    uart_cfg.tx_pin = TEST_PIN_UART_TX;  // UART TX pin.

    uart_cfg.tx_ring_size = sizeof(uart_tx_buffer);
    uart_cfg.rx_ring_size = sizeof(uart_rx_buffer);

    if ( ACQUIRE_FAIL == uart_open( &uart, &uart_cfg ) ) {
        while(1);
    };

    uart_set_baud( &uart, 115200 );
    uart_println( &uart, "MikroBUS ADC test initiated!!!" );

    while (1) {
        for ( cnt = 0; cnt < TEST_PIN_COUNT; cnt++ ) {
            // Write out data.
            if ( UART_ERROR == uart_println( &uart,
                                             format_mikrobus_message("Testing mikroBUS/",
                                                                     cnt) ) ) {
                while(1);
            }

            read_count = READ_COUNT;
            analog_in_read_value = 0;
            // -----------------------------------------------------------------------

            // STEP 2: Initialize ADC module.
            // -----------------------------------------------------------------------
            analog_in_configure_default( &analog_in_cfg );
            // NOTE 'cnt' represents mikroBUS number
            //      i.e 0 is mikroBUS1, 1 is mikroBUS2...
            analog_in_cfg.input_pin = test_pins[cnt];
            analog_in_cfg.resolution = TEST_RESOLUTION_VALUE;
            analog_in_cfg.vref_input = ANALOG_IN_VREF_EXTERNAL;
            analog_in_cfg.vref_value = TEST_VREF_VALUE;

            if( ACQUIRE_FAIL == analog_in_open( &analog_in, &analog_in_cfg ) ) {
                while(1);
            }

            if ( ADC_ERROR == analog_in_set_resolution( &analog_in, TEST_RESOLUTION_VALUE ) ) {
                while(1);
            }

            if ( ADC_ERROR == analog_in_set_vref_input( &analog_in, ANALOG_IN_VREF_EXTERNAL) ) {
                while(1);
            }

            if ( ADC_ERROR == analog_in_set_vref_value( &analog_in, TEST_VREF_VALUE ) ) {
                while(1);
            }

            // Wait for potentiometer to be connected first.
            // Check max value first
            while( analog_in_read_value < READ_VALUE_MAX ) {
                analog_in_read( &analog_in, &analog_in_read_value );
                Delay_10ms();
            }

            // Check min value second.
            while( analog_in_read_value > READ_VALUE_MIN ) {
                analog_in_read( &analog_in, &analog_in_read_value );
                Delay_10ms();
            }

            // -----------------------------------------------------------------------

            // STEP 3: Read analog input and send via UART.
            // -----------------------------------------------------------------------
            while(read_count--) {
                if ( ADC_ERROR == analog_in_read( &analog_in, &analog_in_read_value ) ) {
                    while(1);
                }

                // Convert read value to string.
                uint16_to_str(analog_in_read_value, &analog_in_read_buffer);

                // Print RAW value to UART terminal.
                uart_print( &uart ,"RAW VALUE:" );
                uart_println( &uart, analog_in_read_buffer );

                Delay_100ms();
            }
            // -----------------------------------------------------------------------

            // STEP 4: Close the module and prepare for next mikroBUS.
            // -----------------------------------------------------------------------
            analog_in_close(&analog_in);

            if ( TEST_PIN_COUNT > 1 ) {
                if ( UART_ERROR == uart_println( &uart,
                                                 format_mikrobus_message("Place Uart click in mikroBUS/",
                                                                         cnt+1) ) ) {
                }
            }
            // -----------------------------------------------------------------------
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
