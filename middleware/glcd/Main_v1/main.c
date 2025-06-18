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

    point p = { 12, 27 }; // Initialize a point at (0, 0)

    while (1) 
    {
        for (uint8_t i=0; i<8; i++)
        {
            GLCD_Draw_Dot(&glcd, &p, 2, true); // Draw a dot at the point
            Delay_ms(1000);
        }
        p.x = 12;
        GLCD_Clear(&glcd); // Clear the GLCD
    }
    return 0;
}