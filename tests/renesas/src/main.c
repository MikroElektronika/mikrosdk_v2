// TODO
// Test is done by checking board hardware status / LED's.
// TODO
// Make sure to test different pins.
// Also, make sure to use higher nibble pins.
// For example, if port is 16-bit, make sure
// to use GPIO_PB8-GPIO_PB15.
// If port is 32-bit, make sure to use pins from
// GPIO_PB16-GPIO_PB31. -- NXP specific( 32-bit ports )
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

// #include "cmsis_gcc.h"

// __attribute__((section(".ofs_section")))
// const uint32_t __ofs0 = 0xFF1FFF03;

// __attribute__((section(".ofs_section")))
// const uint32_t __ofs1 = 0xFFFFFFC7;

// __attribute__((section(".bsc_section")))
// const uint32_t __bsc = 0xFFFFFFF0;   // Boot swap disabled

// -------------------------------------------------------------------- MACROS

// ----------------------------------------------------------------- VARIABLES

// ----------------------------------------------------------------- USER CODE
// Simple delay function
void delay(void)
{
    for (volatile uint32_t i = 0; i < 1000000; i++)
    {
        asm("nop");
    }
}
void clock_init(void)
{
    // CLOCK
    R_SYSTEM->PRCR     = 0xA501;          // Enable clock register writes
    R_SYSTEM->MOSCCR_b.MOSTP   = 1;            // Stop XTAL
    R_SYSTEM->MOMCR_b.MODRV1    = 0;            // 10-20 MHz
    R_SYSTEM->MOMCR_b.MOSEL    = 0;            // External clock input
    R_SYSTEM->MOSCWTCR_b.MSTS = 9;            // XTAL wait time
    R_SYSTEM->MOSCCR_b.MOSTP   = 0;            // Start XTAL
    while (!(R_SYSTEM->OSCSF_b.MOSCSF));    // Wait for XTAL
    R_SYSTEM->SCKSCR_b.CKSEL = 3;
    R_SYSTEM->PRCR     = 0xA500;          // Disable clock register writes
    // CLOCK
}

// Initialize LED pin (P302)
void port_init_r7(void)
{
    // Configure P302 as GPIO output
    R_PFS->PORT[3].PIN[2].PmnPFS = 0x00000000; // GPIO mode

    R_PORT3->PDR_b.PDR2 = 1; // Direction: output

    R_PORT3->PODR_b.PODR2 = 0; // Initial state: low
}


#define DEFINED_CYCLES (10000)
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize system clock
    // clock_init();
    // Initialize GPIO port
    port_init_r7();

    // R_SYSTEM->CKOCR = 0;
    R_SYSTEM->CKOCR_b.CKOSEL = 3; // Main
    R_SYSTEM->CKOCR_b.CKODIV = 1;
    R_SYSTEM->CKOCR_b.CKOEN = 1;

    // R_PFS->PORT[2].PIN[5].PmnPFS = 0;
    R_PFS->PORT[2].PIN[5].PmnPFS_b.PMR = 1; // peripheral
    R_PFS->PORT[2].PIN[5].PmnPFS_b.PDR = 1; // output
    R_PFS->PORT[2].PIN[5].PmnPFS_b.PSEL = 9; // clkout
    R_PFS->PORT[2].PIN[5].PmnPFS_b.NCODR = 0; // CMOS
    R_PFS->PORT[2].PIN[5].PmnPFS_b.DSCR = 1; // middle drive


    // // // Main loop
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
