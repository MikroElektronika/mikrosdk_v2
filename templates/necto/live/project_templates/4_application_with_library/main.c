/**
 * @file main.c
 * @brief Main source file for the ${PROJECT_NAME} application.
 *
 * This is a basic template for a standalone embedded application.
 * It provides a minimal structure for user code and MCU initialization.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

/**
 * @brief Application entry point.
 *
 * Initializes the MCU and starts the main execution loop.
 * Do not remove the preinit() call — it ensures proper clock configuration.
 */
int main(void)
{
    /* Do not remove this line — it ensures correct MCU initialization. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Add your application initialization code here.

    while (1)
    {
        // Place your program logic here.
    }

    return 0;
}
