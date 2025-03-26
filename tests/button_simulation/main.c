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

// ----------------------------------------------------------------- VARIABLES

static sim_button_t my_button;
static log_t logger;

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize the simulated button
    sim_button_init( &my_button, BUTTON );
    log_printf( &logger, "Button initialized on pin %d\n", BUTTON );

    // Simulate pressing the button for 500ms
    sim_button_press_ms( &my_button, 500 );
    log_printf( &logger, "Button pressed for 500ms\n", BUTTON );

    // Check if the button is currently pressed
    if ( sim_button_is_pressed( &my_button ) ) {
        log_printf( &logger, "Button is currently pressed\n", BUTTON );
    } else {
        log_printf( &logger, "Button is not pressed\n", BUTTON );
    }

    // Simulate a press-and-hold action
    sim_button_press_and_hold( &my_button );
    log_printf( &logger, "Button is held down\n", BUTTON );

    // Release the button
    sim_button_release( &my_button );
    log_printf( &logger, "Button released\n", BUTTON );

    // Toggle the button state
    sim_button_toggle( &my_button );
    log_printf( &logger, "Button state toggled\n", BUTTON );

    return 0;
}

// ----------------------------------------------------------------------- END
