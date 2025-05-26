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
    GLCD_Display(&glcd, on);            // Allume l'affichage
    //GLCD_Clear(&glcd);            // Vide l'écran
    //GLCD_Fill_Screen( &glcd, 0xFF );
    while (1)
    {
        for (uint8_t i=0; i<PAGE_SIZE; i++)
        {
            for (uint8_t j=0; j<ROW_SIZE; j++)
            {
                GLCD_Write( &glcd, i, j, 0xFF );
            }
        }
    }

    return 0;
}
