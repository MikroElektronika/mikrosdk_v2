// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "glcd.h"
static glcd_t glcd;

int main(void)
{
    GLCD_Init(&glcd);
    GLCD_Display(&glcd, ON);
    GLCD_Clear(&glcd);

    GLCD_Write(&glcd, 1, 12, 0xFF);
    return 0;
}

// ----------------------------------------------------------------------- END
