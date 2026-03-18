// TODO
// Test is done by checking board hardware status / LED's.
// TODO
// Make sure to test different pins.
// Also, make sure to use higher nibble pins.
// For example, if port is 16-bit, make sure
// to use GPIO_PB8-GPIO_PB15.
// If port is 32-bit, make sure to use pins from
// GPIO_PB16-GPIO_PB31. -- NXP specific( 32-bit ports )
// ------------------------------------------------------------------ INCLUDES
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_port.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS
// TODO
#define TEST_CLOCK        true
#define CLOCK_TEST_PORT   2

#define TEST_FLATTENER    false

#define FULL_TEST         true

#if FULL_TEST
#define PIN_TEST          true
#define PORT_TEST         true
#define BUTTON_TEST       true
#else
#define PIN_TEST          false
#define PORT_TEST         false
#define BUTTON_TEST       false
#endif
// TODO
// Define port used for signaling errors.
#define PORT_SIGNAL_ERROR HAL_PORT_NC // Example: GPIO_PORT_C
#define signal_error port_init( &test_port, PORT_SIGNAL_ERROR, \
                                PORT_MASK, PIN_DIRECTION_DIGITAL_OUTPUT ); \
                     while(1) { \
                     port_write( &test_port, PORT_MASK ); \
                     Delay_100ms(); \
                     port_write( &test_port, ~PORT_MASK ); \
                     }

#define CLOCK_TEST(x) port_init( &test_port, x, 0xFF, PIN_DIRECTION_DIGITAL_OUTPUT ); \
                      while(1) { \
                          port_write( &test_port, 0xFF ); \
                          Delay_1sec(); \
                          port_write( &test_port, 0x00 ); \
                          Delay_1sec(); \
                      }

// TODO
// Define port used for testing.
#define PORT_NAME HAL_PORT_NC // Example: GPIO_PORT_B
#define PORT_MASK (port_size_t)0xFFFFFFFF
#define PORT_READ_VALUE 0xAA
#define SINGLE_LED_DELAY 300  // Delay LED single shift test.
// TODO
// Define pins used for testing digital in/out.
#define LED HAL_PIN_NC        // Example: GPIO_PA0
#define BUTTON HAL_PIN_NC     // Example: GPIO_PB0
// ----------------------------------------------------------------- VARIABLES
static port_t test_port;          // PORT driver context structure.
static digital_in_t input_pin;    // Digital input driver context structure.
static digital_out_t output_pin;  // Digital output driver context structure.
#define port_count_size 4 // RUCNO DODATO
static uint8_t port_counter = port_count_size;  // Defined in memake file.
// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    


    volatile pin_name_t fetch_pin = hal_gpio_fetch_pin(LED);
    volatile port_name_t fetch_port = hal_gpio_fetch_port(LED);

   

    /*#if TEST_CLOCK
    CLOCK_TEST( CLOCK_TEST_PORT );
    #endif*/

    

    #if TEST_FLATTENER
    digital_out_init( &output_pin, LED );
    while(1) {
        digital_out_toggle( &output_pin );
    }
    #endif
    
    #if PORT_TEST
    // ------------------------------------------------------------------ PORT
    // TODO
    // Test out different ports using different masks.
    // Output on LED's should be as expected based on defined port/mask.
    TRISD = 0x00;
    LATD = 0xFF;
    ANSELD = 0x00;
    Delay_1sec();
    TRISD = 0x00;
    LATD = 0x00;
    ANSELD = 0x00;

    int a;
    port_init( &test_port, 2, 255, PIN_DIRECTION_DIGITAL_OUTPUT );

    // TODO
    // Make sure to use a full port ( all LED's connected )
    // All LED's should turn on.
    
    port_write( &test_port, 255 );
    Delay_1sec();
    // All LED's should turn off.
    port_write( &test_port, 0 );
    Delay_1sec();
    // All LED's should turn on.
    port_write( &test_port, 255 );
    Delay_1sec();
    // All LED's should turn off.
    port_write( &test_port, 0 );
    Delay_1sec();
    CLRWDT();
    
    
    // TODO
    // This is a sanity check using pin shifting
    // Make sure to define the delay value in order
    // to see all LED's change.
    port_counter = 255;
    while ( port_counter > 0 ) {
        port_write( &test_port, port_counter );
        Delay_ms(10);
        CLRWDT();
        port_counter -= 1;
    }
    
    for ( uint8_t i = 0; i < port_count_size; i++ ) {
        port_write( &test_port, 1ul << i );
        Delay_ms(10);
        CLRWDT();
    }


    // TODO
    // Test read on different ports.
    
    /*if ( PORT_READ_VALUE != port_read( &test_port ) ) {
        signal_error
    }
    port_write( &test_port, PORT_READ_VALUE );*/
    CLRWDT();
    Delay_1sec();
    CLRWDT();
    #endif
    // -------------------------------------------------------------- EOF PORT
    // -------------------------------------------------------- DIGITAL_IN_OUT
    volatile uint8_t value;
    #if PIN_TEST

    
    // Initializes digital output driver context structure and individual GPIO
    // pin as digital output.
    digital_out_init( &output_pin, 4 );
    
    // TODO
    // Check if defined pin is being toggled.
    uint8_t i = 60;
    
    while ( i > 40 ) {
        digital_out_high( &output_pin );
        
        Delay_100ms();
        digital_out_low ( &output_pin );
        
        Delay_100ms();
        i -= 1;
        CLRWDT();
    }
    


    while ( i > 20 ) {
        digital_out_toggle( &output_pin );
        Delay_100ms();
        i -= 1;
        CLRWDT();
    }

    while ( i-- ) {
        digital_out_write( &output_pin, true );
        Delay_100ms();
        digital_out_write( &output_pin, false );
        Delay_100ms();
        CLRWDT();
    }
    
    #endif
    #if BUTTON_TEST
    
    // Initializes digital input driver context structure and individual GPIO
    // pin as digital input.
     digital_in_init( &input_pin, 3 );
    // Initializes digital output driver context structure and individual GPIO
    // pin as digital output.
    digital_out_init( &output_pin, 4 );

    while(1) {
        // TODO
        // Set button press level for PORT high.
        // Pull down pin.
        // By pressing adequate pin button, same
        // value should be set to defined LED pin.
        int a = 0;
        
        value = digital_in_read( &input_pin );    // Read digital input value.
        /*if(value > 250){
            digital_out_write( &output_pin, true );
        }
        else{
            digital_out_write( &output_pin, false );
        }*/
        digital_out_write( &output_pin, value );
        //digital_out_write( &output_pin, value );  // Write read value.
        CLRWDT();
    }
    #endif
    // -----------------------------------------------------EOF DIGITAL_IN_OUT
    
    while(1){CLRWDT();};

    return 0;
}

// ----------------------------------------------------------------------- END
