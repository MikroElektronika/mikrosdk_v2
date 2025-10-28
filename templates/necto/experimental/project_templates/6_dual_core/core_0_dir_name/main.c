/**
 * @file main.c
 * @brief Main source file for the primary core (Core 0) of the dual-core application.
 *
 * This file represents the entry point for Core 0 in a dual-core MCU setup.
 * Core 0 is typically responsible for system initialization, inter-core communication,
 * and control logic, while Core 1 executes secondary or compute-specific tasks.
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
    
    // Add Core 0-specific initialization and task management here.

    while (1)
    {
    }

    return 0;
}
