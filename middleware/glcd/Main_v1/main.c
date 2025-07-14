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
    point p4 = {20, 10};
    
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
        GLCD_Write(&glcd, 1, 12, 0xFF);
    }
    return 0;
}