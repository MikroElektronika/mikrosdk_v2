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
    GLCD_Clear(&glcd);
    while (1)
    {
        /*
        GLCD_Write( &glcd, 0x00, 0x00, 0x01 );  // Write data to GLCD at page 0, line 0
        Delay_ms(1000);                         // Wait for 1 second
        GLCD_Write( &glcd, 0x01, 0x01, 0x01 );  // Write data to GLCD at page 1, line 1
        Delay_ms(1000);                         // Wait for 1 second
        GLCD_Write( &glcd, 0x03, 0x03, 0x01 );  // Write data to GLCD at page 0, line 0
        Delay_ms(1000);                         // Wait for 1 second
        GLCD_Write( &glcd, 0x04, 0x04, 0x01 );  // Write data to GLCD at page 1, line 1
        */
    }
    return 0;
}
