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

    point p2[] = { { 0, 0 }, { 64, 60 }, { 12, 60 }, { 112, 40 }, {12 , 32} };
    point p = {0, 0};
    point p3[] = { { 0, 0 }, { 64, 0 } };
    uint8_t p2size = sizeof(p2) / sizeof(p2[0]);
    while (1) 
    {
        GLCD_Draw_Rect_Giving_Size(&glcd, &p, 90, 30, 2, false, false);
    }
    return 0;
}