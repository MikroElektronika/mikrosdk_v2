// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_uart.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

// TODO If set to 1, will work simultaneously with two objects
#define TEST_TWO_MODULES 0

#define TEST_PIN_UART_TX HAL_PIN_NC // TODO define UART TX pin
#define TEST_PIN_UART_RX HAL_PIN_NC // TODO define UART RX pin

#if TEST_TWO_MODULES
#define TEST_PIN_UART_TX2 HAL_PIN_NC // TODO define UART TX pin
#define TEST_PIN_UART_RX2 HAL_PIN_NC // TODO define UART RX pin
#endif

// TODO Define test pins according to hardware
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC
#define TEST_PIN_9  HAL_PIN_NC
#define TEST_PIN_10 HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

// Macro used for defining number of reads
// `false` means infinte -- echo example
// `true` means one read followed by module closing
#define close_selector false
// ----------------------------------------------------------------- VARIABLES
static uart_t uart;  // UART driver context structure.
static uart_config_t uart_cfg;  // UART driver context structure.

// Be careful to have big enough buffers.
// TODO Test different buffer sizes.
static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];
static uint8_t buffer[32];

#if TEST_TWO_MODULES
// TODO Test two different modules at the same time.
// Add second object initialization in order to test.
static uart_t uart2;  // UART driver context structure.
static uart_config_t uart_cfg2;  // UART driver context structure.
static uint8_t uart_rx_buffer2[128];
static uint8_t uart_tx_buffer2[128];
static uint8_t buffer2[32];
#endif

static int32_t read_size = 0;

static digital_out_t test_pin;
// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    // Choose UART mode: Set to `true` for
    // interrupt-driven UART, `false` for polling mode.
    uart.is_interrupt = false;

    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher than 7. For example, for porta, pins
    // GPIO_PA8, GPIO_PA9, GPIO_PA10 etc.
    uart_cfg.tx_pin = TEST_PIN_UART_TX;  // UART TX pin.
    uart_cfg.rx_pin = TEST_PIN_UART_RX;  // UART RX pin.

    uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );

    if( ACQUIRE_FAIL == uart_open( &uart, &uart_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    #if TEST_TWO_MODULES
    // Default config
    uart_configure_default( &uart_cfg2 );

    // Ring buffer mapping
    uart2.tx_ring_buffer = uart_tx_buffer2;
    uart2.rx_ring_buffer = uart_rx_buffer2;

    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher than 7. For example, for porta, pins
    // GPIO_PA8, GPIO_PA9, GPIO_PA10 etc.
    uart_cfg2.tx_pin = TEST_PIN_UART_TX2;  // UART TX pin.
    uart_cfg2.rx_pin = TEST_PIN_UART_RX2;  // UART RX pin.

    uart_cfg2.tx_ring_size = sizeof( uart_tx_buffer2 );
    uart_cfg2.rx_ring_size = sizeof( uart_rx_buffer2 );

    if( ACQUIRE_FAIL == uart_open( &uart2, &uart_cfg2 ) ) {
        signal_error( TEST_PIN_1 );
    }
    #endif

    //------------------------------------------------------------------------
    // UART settings
    //------------------------------------------------------------------------

    // Set baud rate.
    // TODO Test different baud rate values.
    if ( UART_SUCCESS != uart_set_baud( &uart, 115200 ) ) {
        signal_error( TEST_PIN_2 );
    }
    #if TEST_TWO_MODULES
    if ( UART_SUCCESS != uart_set_baud( &uart2, 115200 ) ) {
        signal_error( TEST_PIN_2 );
    }
    #endif

    // Set data parity. ( no parity )
    // TODO Test different parity values.
    // This test can be performed by checking
    // register for adequate values.
    if ( UART_SUCCESS != uart_set_parity( &uart, UART_PARITY_DEFAULT ) ) {
        signal_error( TEST_PIN_3 );
    };
    #if TEST_TWO_MODULES
    if ( UART_SUCCESS != uart_set_parity( &uart2, UART_PARITY_DEFAULT ) ) {
        signal_error( TEST_PIN_3 );
    };
    #endif

    // Set stop bits. ( one stop bit )
    // TODO Test different stop bit values.
    // This test can be performed by checking
    // register for adequate values.
    if ( UART_SUCCESS != uart_set_stop_bits( &uart, UART_STOP_BITS_DEFAULT ) ) {
        signal_error( TEST_PIN_4 );
    }
    #if TEST_TWO_MODULES
    if ( UART_SUCCESS != uart_set_stop_bits( &uart2, UART_STOP_BITS_DEFAULT ) ) {
        signal_error( TEST_PIN_4 );
    }
    #endif

    // Set data bits. ( 8-bit data )
    // TODO Test different bit per wr/rd values.
    // This test can be performed by checking
    // register for adequate values.
    if ( UART_SUCCESS != uart_set_data_bits( &uart, UART_DATA_BITS_DEFAULT ) ) {
        signal_error( TEST_PIN_5 );
    }
    #if TEST_TWO_MODULES
    if ( UART_SUCCESS != uart_set_data_bits( &uart2, UART_DATA_BITS_DEFAULT ) ) {
        signal_error( TEST_PIN_5 );
    }
    #endif
    Delay_100ms();

    //------------------------------------------------------------------------
    // EOF UART settings
    //------------------------------------------------------------------------

    // Write out data.
    if ( UART_ERROR == uart_print( &uart, "Hello!" ) ) {
        signal_error( TEST_PIN_6 );
    }
    #if TEST_TWO_MODULES
    if ( UART_ERROR == uart_print( &uart2, "Hello!" ) ) {
        signal_error( TEST_PIN_6 );
    }
    #endif
    // Delay needed because of `uart_clear` function, so all data is transmitted.
    Delay_100ms();

    // Write out data with new line.
    if ( UART_ERROR == uart_println( &uart, "This UART is on object 1!" ) ) {
        signal_error( TEST_PIN_7 );
    }
    #if TEST_TWO_MODULES
    if ( UART_ERROR == uart_println( &uart2, "This UART is on object 2!" ) ) {
        signal_error( TEST_PIN_7 );
    }
    #endif
    // Delay needed because of `uart_clear` function, so all data is transmitted.
    Delay_100ms();

    // Clear rx and tx buffers.
    uart_clear( &uart );
    #if TEST_TWO_MODULES
    uart_clear( &uart2 );
    #endif

    // Check if buffers have been cleared
    if ( uart.config.tx_buf.head ||
         uart.config.tx_buf.tail ||
         uart.config.tx_buf.size )
    {
        signal_error( TEST_PIN_8 );  // Same signal pin for both buffers.
    }
    if ( uart.config.rx_buf.head ||
         uart.config.rx_buf.tail ||
         uart.config.rx_buf.size )
    {
        signal_error( TEST_PIN_8 );  // Same signal pin for both buffers.
    }
    #if TEST_TWO_MODULES
    if ( uart2.config.tx_buf.head ||
         uart2.config.tx_buf.tail ||
         uart2.config.tx_buf.size )
    {
        signal_error( TEST_PIN_8 );  // Same signal pin for both buffers.
    }
    if ( uart2.config.rx_buf.head ||
         uart2.config.rx_buf.tail ||
         uart2.config.rx_buf.size )
    {
        signal_error( TEST_PIN_8 );  // Same signal pin for both buffers.
    }
    #endif

    // Set blocking mode.
    // TODO -- Test both --> true/false.
    uart_set_blocking( &uart, true );
    #if TEST_TWO_MODULES
    uart_set_blocking( &uart2, true );
    #endif

    // Wait for first read, or read indefinitely depending on `close_selector`.
    #if TEST_TWO_MODULES
    while(1) {
        size = uart_read( &uart, buffer, sizeof( buffer ) );  // Read data.

        if ( size > 0 )  // If anything was read.
        {
            size = uart_write( &uart2, buffer, size );  // Write what you read.
        }
    }
    #else
    while( ( close_selector == false )?( true ):( !read_size ) )
    {
        read_size = uart_read( &uart, buffer, sizeof( buffer ) );  // Read data.

        if ( read_size > 0 )  // If anything was read.
        {
            read_size = uart_write( &uart, buffer, read_size );  // Write what you read.
        }

        if ( uart.is_blocking && ( UART_ERROR == read_size ) ) {
            signal_error( TEST_PIN_9 );
        }
    }
    #endif

    // Close UART module.
    // TODO Test by debugging and stepping into.
    // Make sure to confirm that everything is
    // disabled/dealocated etc.
    uart_close( &uart );
    #if TEST_TWO_MODULES
    uart_close( &uart2 );
    #endif
    signal_end( TEST_PIN_10 );
    // If everything works as expected,
    // test UART module using click
    // packages that can be found in
    // the tests/clicks/uart folder

    return 0;
}

// ----------------------------------------------------------------------- END
