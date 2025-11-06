/**
 * @file main.c
 * @brief Main source file for the ${PROJECT_NAME} application.
 *
 * This is a basic project template providing a minimal structure
 * for initializing the MCU and writing embedded application logic.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif


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
