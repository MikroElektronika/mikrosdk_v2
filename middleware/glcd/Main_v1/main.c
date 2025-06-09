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

    GLCD_Init(&glcd);              // Initialisation du GLCD
    while (1)
    {
        GLCD_Display(&glcd, on); // Turn on the GLCD
        Delay_ms(1000); // Delay for 1 second
        GLCD_Display(&glcd, off); // Turn on the GLCD
        Delay_ms(1000); // Delay for 1 second
    }
    return 0;
}
