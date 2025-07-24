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
#define TEST_CLOCK        false
#define CLOCK_TEST_PORT   PORT_4

#define TEST_FLATTENER    false

#define FULL_TEST         true

#if FULL_TEST
#define PIN_TEST          true
#define PORT_TEST         true
#define BUTTON_TEST       true
#else
#define PIN_TEST          false
#define PORT_TEST         false
#define BUTTON_TEST       true
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

static uint8_t port_counter = port_count_size;  // Defined in CMakeLists.txt file.

#define PWPR_REGISTER_BASE (*( volatile uint8_t * )0x40040D03UL)
#include "mcu.h"

// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif


    // // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    // // PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // R_PMISC->PWPR_b.B0WI = 0;
    // // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    // // PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit
    // R_PMISC->PWPR_b.PFSWE = 1;

    // // R_PFS->PORT[0].PIN[0].PmnPFS_b.PDR = 1;
    // // R_PFS->PORT[0].PIN[0].PmnPFS_b.PMR = 0;
    // // R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR = 1;

    // R_PFS->PORT[0].PIN[0].PmnPFS = 0x00000000; // GPIO mode
    // R_PORT0->PDR_b.PDR0 = 1; // Direction: output
    // R_PORT0->PODR_b.PODR0 = 0; // Initial state: low
    // R_PORT0->PODR |= 1;
    // while(1);

    // // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
    // R_PMISC->PWPR_b.PFSWE = 0;
    // // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
    // R_PMISC->PWPR_b.B0WI = 1;

    volatile pin_name_t fetch_pin = hal_gpio_fetch_pin(LED);
    volatile port_name_t fetch_port = hal_gpio_fetch_port(LED);

    #if TEST_CLOCK
    // CLOCK_TEST( CLOCK_TEST_PORT );
    port_init( &test_port, CLOCK_TEST_PORT, 0xFFFF, PIN_DIRECTION_DIGITAL_OUTPUT ); \
                      while(1) { \
                          port_write( &test_port, 0xFFFF ); \
                          Delay_1sec(); \
                          port_write( &test_port, 0x00 ); \
                          Delay_1sec(); \
                      }
    #endif

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
    port_init( &test_port, PORT_NAME, PORT_MASK, PIN_DIRECTION_DIGITAL_OUTPUT );

    // TODO
    // Make sure to use a full port ( all LED's connected )
    // All LED's should turn on.
    port_write( &test_port, PORT_MASK );
    Delay_1sec();
    // All LED's should turn off.
    port_write( &test_port, ~PORT_MASK );
    Delay_1sec();
    // All LED's should turn on.
    port_write( &test_port, PORT_MASK );
    Delay_1sec();
    // All LED's should turn off.
    port_write( &test_port, ~PORT_MASK );
    Delay_1sec();

    // TODO
    // This is a sanity check using pin shifting
    // Make sure to define the delay value in order
    // to see all LED's change.
    while ( --port_counter ) {
        port_write( &test_port, 1ul << port_counter );
        Delay_ms(SINGLE_LED_DELAY);
    }
    for ( uint8_t i = 0; i < port_count_size; i++ ) {
        port_write( &test_port, 1ul << i );
        Delay_ms(SINGLE_LED_DELAY);
    }

    // TODO
    // Test read on different ports.
    port_write( &test_port, PORT_READ_VALUE );
    if ( PORT_READ_VALUE != port_read( &test_port ) ) {
        signal_error
    }
    Delay_1sec();
    #endif
    // -------------------------------------------------------------- EOF PORT
    // -------------------------------------------------------- DIGITAL_IN_OUT
    volatile uint8_t value;
    #if PIN_TEST
    // Initializes digital output driver context structure and individual GPIO
    // pin as digital output.
    digital_out_init( &output_pin, LED );

    // TODO
    // Check if defined pin is being toggled.
    uint8_t i = 60;
    while ( i-- > 40 ) {
        digital_out_high( &output_pin );
        Delay_100ms();
        digital_out_low ( &output_pin );
        Delay_100ms();
    }

    while ( i-- > 20 ) {
        digital_out_toggle( &output_pin );
        Delay_100ms();
    }

    while ( i-- ) {
        digital_out_write( &output_pin, true );
        Delay_100ms();
        digital_out_write( &output_pin, false );
        Delay_100ms();
    }
    #endif
    #if BUTTON_TEST
    // Initializes digital input driver context structure and individual GPIO
    // pin as digital input.
    digital_in_init( &input_pin, BUTTON );
    // Initializes digital output driver context structure and individual GPIO
    // pin as digital output.
    digital_out_init( &output_pin, LED );

    while(1) {
        // TODO
        // Set button press level for PORT high.
        // Pull down pin.
        // By pressing adequate pin button, same
        // value should be set to defined LED pin.
        value = digital_in_read( &input_pin );    // Read digital input value.
        digital_out_write( &output_pin, value );  // Write read value.
    }
    #endif
    // -----------------------------------------------------EOF DIGITAL_IN_OUT
    while(1);

    return 0;
}

// ----------------------------------------------------------------------- END
