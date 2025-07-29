/**
 * @file main.c
 * @brief Main function for dual_core_test application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

int main(void)
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    while (1)
    {
    }

    return 0;
}
