// ------------------------------------------------------------------ INCLUDES

#include "mikrobus_uart.h"

// -------------------------------------------------------------------- MACROS

// NOTE If set to true, test is done on a single module.
//      If set to false, test is done on all mikroBUS pins
//      defined in 'board.h'.
#define SINGLE_MIKROBUS true

// TODO Define timeout if using multiple mikroBUSes.
// NOTE Use this time to place UART click on another mikroBUS.
#define change_bus_wait_time_seconds 10

#if SINGLE_MIKROBUS
    // TODO Define UART test pins.
    // NOTE MIKROBUS_x_TX where 'x' is mikroBUS number.
    // NOTE MIKROBUS_x_RX where 'x' is mikroBUS number.
    #define TEST_PIN_TX HAL_PIN_NC
    #define TEST_PIN_RX HAL_PIN_NC
    #define TEST_MODULE_COUNT 1
    pin_name_t test_pins[1][2] = {TEST_PIN_TX,TEST_PIN_RX};
#else
    #define TEST_MODULE_COUNT MIKROBUS_COUNT
    pin_name_t (*test_pins)[2] = test_pins_mikrobus;
#endif

// TODO Declare desired speed value.
// NOTE 115200 by default.
#define UART_BAUD 115200

// Declare error signal pins.
// NOTE Optional.
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC

// NOTE Do not edit these.
#define MIKROBUS_TX_PIN 0
#define MIKROBUS_RX_PIN 1

// ----------------------------------------------------------------- VARIABLES

static uart_t uart;
static uart_config_t uart_cfg;

static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];
static uint8_t buffer[32];

static int32_t size = 0;

static digital_out_t test_pin;

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

void main() {
    uint8_t cnt = 0;

    while(1) {
        for ( cnt = 0; cnt < TEST_MODULE_COUNT; cnt++ ) {
            // STEP 1: Initializes and configures UART module.
            // ---------------------------------------------------------------
            // Default config
            uart_configure_default( &uart_cfg );

            // Ring buffer mapping
            uart.tx_ring_buffer = uart_tx_buffer;
            uart.rx_ring_buffer = uart_rx_buffer;

            // NOTE 'cnt' represents mikroBUS number
            //      i.e 0 is mikroBUS1, 1 is mikroBUS2...
            uart_cfg.tx_pin = test_pins[cnt][MIKROBUS_TX_PIN];
            uart_cfg.rx_pin = test_pins[cnt][MIKROBUS_RX_PIN];

            uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
            uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );

            if( ACQUIRE_FAIL == uart_open( &uart, &uart_cfg ) ) {
                signal_error( TEST_PIN_1 );
            }

            // Set baud rate.
            if ( UART_SUCCESS != uart_set_baud( &uart, UART_BAUD ) ) {
                signal_error( TEST_PIN_2 );
            }
            // ---------------------------------------------------------------

            // STEP 2: Echo example.
            // ---------------------------------------------------------------
            // Write out data.
            if ( UART_ERROR == uart_println( &uart,
                                             format_mikrobus_message("Testing mikroBUS/",
                                                                     cnt) ) ) {
                signal_error( TEST_PIN_3 );
            }

            Delay_1sec();
            uart_clear( &uart );
            uart_set_blocking( &uart, true );

            size = uart_read( &uart, buffer, sizeof( buffer ) );  // Read data.
            if ( size > 0 )  // If anything was read.
            {
                size = uart_write( &uart, buffer, size );  // Write what you read.
            }
            // ---------------------------------------------------------------

            // STEP 3: Close the module and prepare for next mikroBUS.
            // ---------------------------------------------------------------
            Delay_1sec();

            if ( TEST_MODULE_COUNT > 1 ) {
                if ( UART_ERROR == uart_println( &uart,
                                                 format_mikrobus_message("Place Uart click in mikroBUS/",
                                                                         cnt+1) ) ) {
                    signal_error( TEST_PIN_4 );
                }
            }

            uart_clear( &uart );
            uart_close( &uart );
            Delay_ms(change_bus_wait_time_seconds*1000);
            // ---------------------------------------------------------------
        }
    }
}

// ----------------------------------------------------------------------- END
