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

    GLCD_Init(&glcd);
    GLCD_Display(&glcd, ON);
    GLCD_Clear(&glcd);

    /* --------------- Variable definition for the becoming tests --------------- */
    point tab[] = { { 10, 10 }, { 20, 20 }, { 30, 30 }, { 40, 40 }, { 50, 50 } };
    uint8_t size = sizeof(tab) / sizeof(tab[0]);

    segment s[] = { { { { 10, 10 }, { 50, 50 } }, 2 }, { { { 20, 20 }, { 60, 60 } }, 2 }, { { { 30, 30 }, { 70, 70 } }, 2 } };
    uint8_t s_size = sizeof(s) / sizeof(s[0]);

    circle c[] = { { { 64, 32 }, 20, 2, false }, { { 64, 32 }, 40, 2, false } };
    uint8_t c_size = sizeof(c) / sizeof(c[0]);

    ellipse e = { { { 64, 32 }, { 100, 32 } }, 40, 2, false };
    
    /* --------------- Drawing tests --------------- */
    while (1) 
    {
        // Draw dots
        // GLCD_Draw_Dots(&glcd, tab, size, 2);
        // Delay_ms(1000); // Delay to visualize dots
        // GLCD_Clear(&glcd); // Clear the GLCD before next drawing

        // Draw lines
        // GLCD_Draw_Line(&glcd, s, s_size, DIAGONAL);
        // Delay_ms(1000);
        // GLCD_Clear(&glcd);

        // Draw circles
        GLCD_Draw_Circle(&glcd, c, c_size, DEFAULT);
        // Delay_ms(1000);
        // GLCD_Clear(&glcd);

        // Draw ellipses
        // GLCD_Draw_Ellipse(&glcd, &e, 1, DEFAULT);
        // Delay_ms(1000);
        // GLCD_Clear(&glcd);

    }
    return 0;
}