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
#include "simulation_button.h"
#include "board.h"
#include "delays.h"
#ifdef __XC8__
#include "string.h"
#endif
// -------------------------------------------------------------------- MACROS

#define BUTTON HAL_PIN_NC // TODO define BUTTON pin

// ----------------------------------------------------------------- VARIABLES

static sim_button_t button_pin;

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // TODO

    return 0;
}

// ----------------------------------------------------------------------- END
