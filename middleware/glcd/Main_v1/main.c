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

    point one_point[] = { {64, 32} };
    point two_points[] = { {10, 10}, {100, 50} };
    point three_points[] = { {20, 20}, {60, 20}, {20, 40} }; // devrait former un rectangle
    point four_points[] = { {30, 30}, {80, 30}, {80, 50}, {30, 50} }; // rectangle parfait

    segment triangle[3] = {
        { { {20, 20}, {60, 20} }, 2 },
        { { {60, 20}, {40, 50} }, 2 },
        { { {40, 50}, {20, 20} }, 2 }
    };

    point pts[] = { {20, 20}, {60, 20}, {100, 20}, {20, 40}};  
    rect rects[] = { { 10, 10, 1, false, false}, { 10, 10, 2, false, false }, 
                     { 10, 10, 3, false, false }, { 10, 10, 4, false, false }
    };

    circle c[] = { { { 64, 32 }, 10, 1, false }, 
                   { { 64, 32 }, 20, 1, false }, 
                   { { 64, 32 }, 30, 1, false },
                   { { 64, 32 }, 40, 1, false }
    };
    
    ellipse e = { {{64, 32}, {120, 32}}, 20, 1, false };

    while (1) 
    {
        // GLCD_Draw_Rect(&glcd, &pts, 4, &rects, 4);
        // GLCD_Draw_Circle(&glcd, c, 4, DEFAULT_MODE);
        GLCD_Draw_Ellipse(&glcd, &e, 1, DEFAULT_MODE);
    }
    return 0;
}