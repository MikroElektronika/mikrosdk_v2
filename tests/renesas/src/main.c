// ------------------------------------------------------------------ INCLUDES
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "mcu.h"
#define PWPR_REGISTER_BASE (* ( volatile uint8_t * )0x40040D03UL)

void uart_init(void)
{
    // 1. Enable SCI0 in the Module Stop Register
    R_SYSTEM->PRCR = 0xa502;
    R_MSTP->MSTPCRB_b.MSTPB31 = 0; // Enable SCI0 (MSTPB31 = 0)
    R_SYSTEM->PRCR = 0xa500;

    // 2. Configure P411 as TXD0 and P410 as RXD0 via IOPORT
    // TXD0 (P411) = Peripheral function: 0x0A
    // RXD0 (P410) = Peripheral function: 0x0A

    // Clear the B0WI bit in the PWPR register. This enables writing to the PFSWE bit in the PWPR register.
    PWPR_REGISTER_BASE &= ~0x80; // Clear B0WI bit
    // Set 1 to the PFSWE bit in the PWPR register. This enables writing to the PmnPFS register.
    PWPR_REGISTER_BASE |= 0x40; // Set PFSWE bit

    // Write PFS registers directly (PFS write-protected by default)
    // ra_gpio_config(pin, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_LOW_POWER, af);
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PMR = 0; // TXD0
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PDR = 1; // TXD0
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PSEL = 0x04; // TXD0
    R_PFS->PORT[4].PIN[11].PmnPFS_b.PMR = 1; // TXD0

    // ra_gpio_config(pin, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_LOW_POWER, af);
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PMR = 0; // RXD0
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PCR = 1; // RXD0
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PSEL = 0x04; // RXD0
    R_PFS->PORT[4].PIN[10].PmnPFS_b.PMR = 1; // RXD0

    // Clear the PFSWE bit in the PWPR register. This disables writing to the PmnPFS register.
    PWPR_REGISTER_BASE &= ~0x40; // Set PFSWE bit
    // Set 1 to the B0WI bit in the PWPR register. This disables writing to the PFSWE bit in the PWPR register
    PWPR_REGISTER_BASE |= 0x80; // Set B0WI bit

    // 3. Initialize SCI1 registers

    // Disable TE and RE
    R_SCI0->SCR = 0x00;
    while (R_SCI0->SCR != 0);

    R_SCI0->SMR = 0x00;
    R_SCI0->SCMR = 0xF3;
    R_SCI0->SEMR = 0xC0;

    // R_SCI0->FCR_b.FM = 1;
    // R_SCI0->FCR_b.TFRST = 1;
    // R_SCI0->FCR_b.RFRST = 1;
    // R_SCI0->FCR_b.TTRG = 0;
    // R_SCI0->FCR_b.RTRG = 0;
    // R_SCI0->FCR_b.RSTRG = 0;

    R_SCI0->SCR_b.CKE = 0x00;
    R_SCI0->SMR_b.CKS = 0x00;
    R_SCI0->BRR = 106;
    
    // Async, 8N1, PCLK/1
    


    // R_SCI0->FCR_b.TFRST = 0;
    // R_SCI0->FCR_b.RFRST = 0;


    // Delay at least 1 bit time (~8.6 us at 115200 baud)
    // for (volatile int i = 0; i < 1000; ++i) { __asm__("nop"); }

    // Enable transmit and receive
    R_SCI0->SCR_b.RE = 0x01;
    R_SCI0->SCR_b.TE = 0x01;
}

void uart_send_char(char c)
{
    // Wait until there is space in the transmit FIFO (TDFE = 1)
    while (!(R_SCI0->SSR_b.TDRE));
    R_SCI0->TDR = c;

    // Clear TDFE by writing 0
    R_SCI0->SSR_b.TDRE = 0;
}

char uart_receive_char(void)
{
    // Wait until there is data in the receive FIFO (RDF = 1)
    while (!(R_SCI0->SSR_b.RDRF));
    char c = R_SCI0->RDR;

    // Clear RDF by writing 0
    R_SCI0->SSR_b.RDRF = 0;

    return c;
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    uart_init();

    uart_send_char('H');
    uart_send_char('i');
    uart_send_char('\r');
    uart_send_char('\n');

    while (1)
    {
        char c = uart_receive_char();
        uart_send_char(c); // Echo received char
    }

    return 0;
}

// ----------------------------------------------------------------------- END
