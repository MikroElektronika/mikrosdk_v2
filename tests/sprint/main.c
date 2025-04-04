// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "mcu.h"
#include "log.h"
#include "sprint.h"
#include "delays.h"
#ifdef __XC8__
#include "string.h"
#endif
// -------------------------------------------------------------------- MACROS

#define TEST_PIN HAL_PIN_NC
#define END_PIN HAL_PIN_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

// ----------------------------------------------------------------- VARIABLES

// TODO Esma
log_t logger;

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    char buffer[100];
    int age = 30;
    char name[] = "John";

    // DMA1->HISR = 2;

    sprintf(buffer, "%s is %d years old.", name, age);
    log_printf(&logger, "%s\n", buffer);

    age = 27;
    name[] = "Esma";
    sprinti(buffer, "%s is %d years old.", name, age, streetnum, phonenum);
    log_printf(&logger, "%s\n", buffer);

    int age = 30;
    char name[] = "John";
    sprintl(buffer, "%s is %d years old.", name, age, streetnum, phonenum);
    log_printf(&logger, "%s\n", buffer);

    return 0;
}

// ----------------------------------------------------------------------- END
