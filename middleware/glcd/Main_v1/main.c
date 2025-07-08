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

    point p[] = { { 0, 0 }, { 64, 60 }, { 12, 60 }, { 112, 40 }, {12 , 32} };
    point p2[] = { { 0, 0 }, { 64, 60 }, { 12, 60 }, { 112, 40 } };
    point p3[] = { { 0, 0 }, { 64, 60 }, { 12, 60 } };
    point p4 = {64, 25};
    point p5[2] = { {12, 12}, {50, 12} };
    
    uint8_t psize = sizeof(p) / sizeof(p[0]);
    uint8_t p2size = sizeof(p2) / sizeof(p2[0]);
    uint8_t p3size = sizeof(p3) / sizeof(p3[0]);
    float c = Module(p5[0], p5[1]);
    while (1) 
    {
        /*
        GLCD_Draw_Polygon(&glcd, p, psize, 2, false, false);
        Delay_ms(1000);

        GLCD_Draw_Polygon(&glcd, p, psize, 2, true, false);
        Delay_ms(1000);
        GLCD_Clear(&glcd);

        GLCD_Draw_Polygon(&glcd, p2, p2size, 2, false, false);
        Delay_ms(1000);

        GLCD_Draw_Polygon(&glcd, p2, p2size, 2, true, false);
        Delay_ms(1000);
        GLCD_Clear(&glcd);

        GLCD_Draw_Polygon(&glcd, p3, p3size, 2, false, false);
        Delay_ms(1000);

        GLCD_Draw_Polygon(&glcd, p3, p3size, 2, true, false);
        Delay_ms(1000);
        GLCD_Clear(&glcd);
        */

        //GLCD_Draw_Rect_Giving_Size(&glcd, &p4, 80, 20, 2, false, false);
        //GLCD_Draw_Circle(&glcd, &p4, 2, 20, DEFAULT_MODE, true);
        GLCD_Draw_Ellipse(&glcd, &p5, c+1, 2, DEFAULT_MODE, false);
    }
    return 0;
}