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
#include "mcu.h"

// -------------------------------------------------------------------- MACROS
// TODO
#define TEST_CLOCK        true
#define CLOCK_TEST_PORT   HAL_PORT_NC

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

static uint8_t port_counter = port_count_size;  // Defined in memake file.
// ----------------------------------------------------------------- USER CODE
// Simple delay function
void delay(void)
{
    for (volatile uint32_t i = 0; i < 1000000; i++)
    {
        __asm("nop");
    }
}
void clock_init(void)
{
    // CHATGPT - NOT GOOD
    // // Start HOCO
    // R_SYSTEM->HOCOCR_b.HCSTP = 0;

    // // Wait for HOCO to stabilize
    // while (!(R_SYSTEM->OSCSF & R_SYSTEM_OSCSF_HOCOSF_Msk))
    // {
    //     // Wait
    // }

    // // Set clock dividers to divide by 1 (default)
    // R_SYSTEM->SCKDIVCR = 0x00000000;

    // // Select HOCO as system clock
    // R_SYSTEM->SCKSCR = 0x01; // HOCO

    // // Stop unused oscillators
    // R_SYSTEM->MOCOCR_b.MCSTP = 1; // Stop MOCO
    // R_SYSTEM->LOCOCR_b.LCSTP = 1; // Stop LOCO

    // // Stop PLL (optional)
    // R_SYSTEM->PLLCR_b.PLLSTP = 1;

    // My try - NOT GOOD
    // R_SYSTEM->SCKSCR = 5; // Set PLL as source clock
    // R_SYSTEM->MOMCR = 1 << 6; // Set Main Clock Oscillator as External clock input
    // while (!(R_SYSTEM->OSCSF & R_SYSTEM_OSCSF_MOSCSF_Msk))
    // {
    //     // Wait
    // }
    // // NOTE: MOMCR REGISTER MUST BE SET BEFORE THIS
    // R_SYSTEM->MOSCCR = 0; // Main clock oscillator is operating.
    // R_SYSTEM->PLLCCR2 = (R_SYSTEM_PLLCCR2_PLLMUL_Msk & (8 << R_SYSTEM_PLLCCR2_PLLMUL_Pos)) | 
    //                     (R_SYSTEM_PLLCCR2_PLODIV_Msk & (2 << R_SYSTEM_PLLCCR2_PLODIV_Pos));

    // R_SYSTEM->PLLCR = 0;
    // // Wait for PLL to stabilize
    // while (!(R_SYSTEM->OSCSF & R_SYSTEM_OSCSF_PLLSF_Msk))
    // {
    //     // Wait
    // }
    // R_SYSTEM->SCKDIVCR |= (1 << R_SYSTEM_SCKDIVCR_PCKB_Pos);

    // From soneone's github
    R_SYSTEM->PRCR     = 0xA501;          // Enable writing to the clock registers
    R_SYSTEM->MOSCCR   = 0x01;            // Make sure XTAL is stopped
    R_SYSTEM->MOMCR    = 0x00;            // MODRV1 = 0 (10 MHz to 20 MHz); MOSEL = 0 (Resonator)
    R_SYSTEM->MOSCWTCR = 0x07;            // Set stability timeout period 
    R_SYSTEM->MOSCCR   = 0x00;            // Enable XTAL
        asm volatile("dsb");                // Data bus Synchronization instruction
    char enable_ok = R_SYSTEM->MOSCCR;    // Check bit 
    Delay_ms(100);                         // wait for XTAL to stabilise  
    R_SYSTEM->PLLCR    = 0x01;            // Disable PLL
    R_SYSTEM->PLLCCR2  = 0x07;            // Setup PLLCCR2_PLLMUL_4_0 PLL PLL Frequency Multiplication to 8x
    R_SYSTEM->PLLCCR2 |= 0x40;            // Setup PLLCCR2_PLODIV_1_0 PLL Output Frequency Division to /2
    R_SYSTEM->PLLCR    = 0x00;            // Enable PLL
    Delay_us(1000);            // wait for PLL to stabilise
    if(R_SYSTEM->OSCSF == 0b0101001)      // Check for stabile XTAL, before allowing switch
    {
        R_SYSTEM->SCKSCR   = 0x05;          // Select PLL as the system clock
        // Serial.println("System clock changed to XTAL with PLL"); 
    }
    else
    {
        // Serial.println("XTAL or PLL not stable, remain on HOCO clock"); 
    }
    R_SYSTEM->PRCR     = 0xA500;          // Disable writing to the clock registers
}

// Initialize LED pin (P302)
void port_init_r7(void)
{
    // Configure P302 as GPIO output
    R_PFS->PORT[3].PIN[2].PmnPFS = 0x00000000; // GPIO mode

    R_PORT3->PDR_b.PDR2 = 1; // Direction: output
    R_PORT3->PODR_b.PODR2 = 0; // Initial state: low
}

int main( void ) {
    // Initialize system clock
    // clock_init();

    // // Initialize GPIO port
    // port_init_r7();

    // // Main loop
    // while (1)
    // {
    //     // LED ON
    //     R_PORT3->PODR_b.PODR2 = 1;
    //     Delay_1ms();

    //     // LED OFF
    //     R_PORT3->PODR_b.PODR2 = 0;
    //     Delay_1ms();
    // }

    while(1);
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    volatile pin_name_t fetch_pin = hal_gpio_fetch_pin(LED);
    volatile port_name_t fetch_port = hal_gpio_fetch_port(LED);

    #if TEST_CLOCK
    CLOCK_TEST( CLOCK_TEST_PORT );
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
