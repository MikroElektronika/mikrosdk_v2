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

    point p2[] = { { 12, 25 }, { 64, 7}, { 25, 60 }, { 112, 40 }, {60 , 32} };
    uint8_t p2size = sizeof(p2) / sizeof(p2[0]);
    while (1) 
    {
        /*
        GLCD_Draw_Dots(&glcd, p2, p2size, 2);
        Delay_ms(1000);

        GLCD_Draw_Polygon(&glcd, p2, p2size, 4, false, false);
        Delay_ms(1000);
        */

        GLCD_Write_Char(&glcd, &p2[0], font[63]);
        Delay_ms(1000);
    }
    return 0;
}