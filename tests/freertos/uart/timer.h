#include "mcu.h"

#define TIMER_SYSTICK_HANDLER() void __attribute__((interrupt(IPL1AUTO), vector(_TIMER_1_VECTOR))) _TIMER_1_HANDLER(void)

int init_1ms_timer() {
    uint16_t prescaler_list[4] = { 256, 64, 8, 1 };
    uint16_t prescaler;
    int8_t index = -1;
    uint16_t remnant;
    uint32_t count = 0;
    #if defined(PIC32MZ)
    uint8_t pbclk_div = PB3DIVbits.PBDIV + 1;
    #elif defined(PIC32MX)
    uint8_t pbclk_div = (uint8_t)1 << OSCCONbits.PBDIV;
    #endif
    uint32_t timer_clock = OSC_KHZ / pbclk_div;
    uint8_t prescaler_index;
    uint32_t period;

    // Configure Timer1 for periodic 1ms interrupts.
    do {
        ++index;
        prescaler = prescaler_list[index];
        remnant = timer_clock % prescaler;
        count = timer_clock / prescaler;
    }
    while ( ( 0 != remnant ) && ( count <= 65535 ) );

    if ( count > 65535 ) {
        if ( 0 < index ) {
            --index;
            prescaler = prescaler_list[index];
            count = timer_clock / prescaler;
        } else {
            return (0);
        }
    } else {
        prescaler_index = (uint8_t)(3 - index);     // Set prescaler to 1:64.
        period = count - 1;
    }

    T1CONbits.TON = 0;                  // Disable Timer1 during configuration.
    T1CONbits.TCS = 0;                  // Select internal peripheral clock.
    T1CONbits.TCKPS = prescaler_index;  // Set the prescaler for 1ms interrupt.
    T1CONbits.TGATE = 0;                // Disable gated time accumulation.

    TMR1 = 0;                           // Clear Timer value.
    PR1 = period;                       // Set Period value for 1ms interrupt.

    // Clear Timer1 interrupt flag.
    IFS0bits.T1IF = 0;

    // Set Timer1 interrupt priority to 1.
    IPC1bits.T1IP = 1;

    // Enable Multi-Vector interrupts.
    INTCONbits.MVEC = 1;

    // Enable Timer1 interrupt.
    IEC0bits.T1IE = 1;

    // Start the Timer1.
    T1CONbits.TON = 1;

    return (1);
}
