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
        for (int i=0; i < 8; i++) 
            GLCD_Write(&glcd, 0, i, 0xFF); // Write a pattern to the GLCD

        Delay_ms(1000); // Wait for a second
        GLCD_Clear(&glcd); // Clear the GLCD
        
        for (int i=0; i < 8; i++) 
            GLCD_Write(&glcd, i, 0, 0xFF); // Write a pattern to the GLCD

        Delay_ms(1000); // Wait for a second
        GLCD_Clear(&glcd); // Clear the GLCD
        
    }
    return 0;
}