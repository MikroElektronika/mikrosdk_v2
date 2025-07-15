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
    GLCD_Display(&glcd, ON);
    GLCD_Clear(&glcd);

    point p[] = { { 0, 0 }, { 64, 60 }, { 12, 60 }, { 112, 40 }, {12 , 32} };
    point p4 = {20, 20};

    point one_point[] = { {64, 32} };
    point two_points[] = { {10, 10}, {100, 50} };
    point three_points[] = { {20, 20}, {60, 20}, {20, 40} }; // devrait former un rectangle
    point four_points[] = { {30, 30}, {80, 30}, {80, 50}, {30, 50} }; // rectangle parfait

    segment triangle[3] = {
        { { {20, 20}, {60, 20} }, 2 },
        { { {60, 20}, {40, 50} }, 2 },
        { { {40, 50}, {20, 20} }, 2 }
    };

    rect rect1 = { 80, 10, 2, true, false};

    while (1) 
    {
        GLCD_Draw_Rect(&glcd, &p4, 1, &rect1, 1, 2);
    }
    return 0;
}