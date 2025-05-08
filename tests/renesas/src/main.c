// ------------------------------------------------------------------ INCLUDES
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "delays.h"
#include "mcu.h"

// -------------------------------------------------------------------- MACROS

// ----------------------------------------------------------------- VARIABLES

// ----------------------------------------------------------------- USER CODE

// Initialize LED pin (P302)
void port_init(void)
{
    // Configure P302 as GPIO output
    R_PFS->PORT[3].PIN[2].PmnPFS = 0x00000000; // GPIO mode

    R_PORT3->PDR_b.PDR2 = 1; // Direction: output

    R_PORT3->PODR_b.PODR2 = 0; // Initial state: low
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize GPIO port
    port_init();

    R_PFS->PORT[2].PIN[5].PmnPFS = 0;
    R_PFS->PORT[2].PIN[5].PmnPFS_b.PMR = 1; // peripheral
    R_PFS->PORT[2].PIN[5].PmnPFS_b.PDR = 1; // output
    R_PFS->PORT[2].PIN[5].PmnPFS_b.PSEL = 9; // clkout
    R_PFS->PORT[2].PIN[5].PmnPFS_b.NCODR = 0; // CMOS
    R_PFS->PORT[2].PIN[5].PmnPFS_b.DSCR = 1; // middle drive

    // Main loop
    while (1)
    {
        R_PORT3->PODR |= (1 << 2);  // Set P302 high
        // for (volatile uint32_t i = 0; i < 10000; i++) __asm("NOP");
        Delay_ms(1000);

        R_PORT3->PODR &= ~(1 << 2); // Set P302 low
        // for (volatile uint32_t i = 0; i < 10000; i++) __asm("NOP");
        Delay_ms(1000);
    }

    return 0;
}

// ----------------------------------------------------------------------- END
