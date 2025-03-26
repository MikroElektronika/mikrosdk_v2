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
#include "simulation_button.h"
#include "delays.h"
#ifdef __XC8__
#include "string.h"
#endif
// -------------------------------------------------------------------- MACROS

#define BUTTON HAL_PIN_NC // TODO define BUTTON pin, i.e. GPIO_PB2

#define TEST_PIN HAL_PIN_NC
#define END_PIN HAL_PIN_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

// ----------------------------------------------------------------- VARIABLES

static sim_button_t button;
static log_t logger;

static digital_out_t test_pin;

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize the simulated button
    if ( SIM_BUTTON_SUCCESS != sim_button_init( &button, BUTTON ) ) {
        signal_error( TEST_PIN );
    }

    log_printf( &logger, "Button initialized on pin %d\n", BUTTON );

    // Simulate pressing the button for 500ms
    sim_button_press_ms( &button, 500 );
    log_printf( &logger, "Button pressed for 500ms\n", BUTTON );

    // Check if the button is currently pressed
    if ( sim_button_is_pressed( &button ) ) {
        log_printf( &logger, "Button is currently pressed\n", BUTTON );
    } else {
        log_printf( &logger, "Button is not pressed\n", BUTTON );
    }

    // Simulate a press-and-hold action
    sim_button_press_and_hold( &button );
    log_printf( &logger, "Button is held down\n", BUTTON );

    // Release the button
    sim_button_release( &button );
    log_printf( &logger, "Button released\n", BUTTON );

    // Toggle the button state
    sim_button_toggle( &button );
    log_printf( &logger, "Button state toggled\n", BUTTON );

    signal_end( END_PIN );

    return 0;
}

// ----------------------------------------------------------------------- END
