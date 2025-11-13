/**
 * @file main.c
 * @brief Main source file for the secondary core (Core 1) of the dual-core application.
 *
 * This file represents the entry point for Core 1 in a dual-core MCU setup.
 * Core 1 typically executes secondary or parallel processing tasks,
 * while Core 0 manages system initialization and inter-core coordination.
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

    while (1)
    {
    }

    return 0;
}
