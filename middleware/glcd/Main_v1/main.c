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

    GLCD_Init(&glcd);               // Initialisation du GLCD
    GLCD_Display(&glcd, on);        // Turn on the GLCD
    GLCD_Clear(&glcd);              // Clear the GLCD
    while (1)
    {
        GLCD_Write(&glcd, 0, 64, 0xAA); // Write a pattern to the GLCD at (0,0)
        Delay_ms(1000);          // Wait for 1 second
        GLCD_Clear(&glcd);          // Clear the GLCD

        GLCD_Write(&glcd, 0, 127, 0xAA);   // devrait allumer uniquement à droite
        Delay_ms(1000);          // Wait for 1 second
        GLCD_Clear(&glcd);          // Clear the GLCD
    }
    return 0;
}