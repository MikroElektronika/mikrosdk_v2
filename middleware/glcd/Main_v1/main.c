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
    point p4 = {20, 25};
    
    point foci[3] = {
        { 0, 30 }, // F1
        { 30, 30 }, // F2
        { 50, 20 }  // (a, b)
    };

    point one_point[] = { {64, 32} };
    point two_points[] = { {10, 10}, {100, 50} };
    point three_points[] = { {20, 20}, {60, 20}, {20, 40} }; // devrait former un rectangle
    point four_points[] = { {30, 30}, {80, 30}, {80, 50}, {30, 50} }; // rectangle parfait

    
    uint8_t psize = sizeof(p) / sizeof(p[0]);
    uint8_t p2size = sizeof(p2) / sizeof(p2[0]);
    uint8_t p3size = sizeof(p3) / sizeof(p3[0]);

    while (1) 
    {
        GLCD_Draw_Rect_Giving_Size(&glcd, &p4, 80, 20, 2, true, false);
        /*
        GLCD_Draw_Circle(&glcd, &p4, 2, 20, DEFAULT_MODE, false);
        GLCD_Draw_Dots(&glcd, p5, 2, 2);

        GLCD_Draw_Rect_Giving_Points(&glcd, one_point, 1, 2, false, false);
        Delay_ms(1000);
        GLCD_Clear(&glcd);

        GLCD_Draw_Rect_Giving_Points(&glcd, two_points, 2, 2, false, false);
        Delay_ms(1000);
        GLCD_Clear(&glcd);

        GLCD_Draw_Rect_Giving_Points(&glcd, three_points, 3, 2, false, false);
        Delay_ms(1000);
        GLCD_Clear(&glcd);

        GLCD_Draw_Rect_Giving_Points(&glcd, four_points, 4, 2, false, false);
        Delay_ms(1000);
        GLCD_Clear();
        
        //GLCD_Draw_Ellipse(&glcd, foci, 2, DEFAULT_MODE, false);

        GLCD_Write(&glcd, 2, 45, 0xAA);  // Page 2, colonne 45
        uint8_t val = GLCD_Read_LL(&glcd, 2, 45);
        */
    }
    return 0;
}