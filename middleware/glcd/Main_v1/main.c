/**
 * @file main.c
 * @brief Main function for Main_v1 application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "glcd_lib_v1.h"
static glcd_t glcd;

int main(void)
{
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    GLCD_Init(&glcd);              // Initialisation du GLCD
    GLCD_Display(&glcd, on);

    while (1)
    {
        /*
        // Main loop code can be added here
        // For example, you can update the GLCD display or handle user input
        GLCD_Write(&glcd, 0, 0, 0xFF); // Write data to the GLCD
        Delay_ms(1000); // Delay for 1 second
        GLCD_Write(&glcd, 0, 1, 0xAA); // Write another data to the GLCD
        Delay_ms(1000); // Delay for 1 second
        */
    }
    return 0;
}
