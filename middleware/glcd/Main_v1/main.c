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
        GLCD_Draw_Dot(&glcd, &p); // Draw a dot at the point
        Delay_ms(5000);

        GLCD_Clear(&glcd);              // Clear the GLCD
        point p2 = { 0, 0 };
        for (uint8_t i=0; i<64; i++)
        {
            p2.x = i+4; p2.y = i;
            GLCD_Draw_Dot(&glcd, &p2); // Draw a dot at the point
            Delay_ms(100);
        }
        
        GLCD_Clear(&glcd);              // Clear the GLCD
    }
    return 0;
}