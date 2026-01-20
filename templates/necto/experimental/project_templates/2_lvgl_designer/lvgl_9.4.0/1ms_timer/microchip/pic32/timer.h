#include <mcu.h>

#define PRESCALER_1 0
#define PRESCALER_8 1
#define PRESCALER_64 2
#define PRESCALER_256 3

#define PRESCALER_VALUE_1 1
#define PRESCALER_VALUE_8 8
#define PRESCALER_VALUE_64 64
#define PRESCALER_VALUE_256 256

#ifdef PIC32TIMER
    #define _prescale_formula(_presc)  ((CLOCK*1000UL)/(_presc*2))
#else
    #define _prescale_formula(_presc)  ((CLOCK*1000UL)/(_presc))
#endif

#define _prescale_values()                  (_prescale_formula(1)<UINT16_MAX)?PRESCALER_1:\
                                            (_prescale_formula(8)<UINT16_MAX)?PRESCALER_8:\
                                            (_prescale_formula(64)<UINT16_MAX)?PRESCALER_64:\
                                            PRESCALER_256

#define _clock_values(_presc)               (_presc == PRESCALER_1)?_prescale_formula(PRESCALER_VALUE_1):\
                                            (_presc == PRESCALER_8)?_prescale_formula(PRESCALER_VALUE_8):\
                                            (_presc == PRESCALER_64)?_prescale_formula(PRESCALER_VALUE_64):\
                                            _prescale_formula(PRESCALER_VALUE_256)

static inline void timerInit() {
    // Configure Timer1 for 1ms interrupt
    uint8_t presc;
    presc = _prescale_values();
    T1CONbits.TON = 0;          // Disable Timer1 during configuration.
    T1CONbits.TCS = 0;          // Select internal peripheral clock.
    T1CONbits.TCKPS = presc;    // Set prescaler.
    T1CONbits.TGATE = 0;        // Disable gated time accumulation.
    TMR1 = 0;                   // Clear Timer1 value.
    PR1 = _clock_values(presc); // For a 1ms interrupt (Clock KHz / presc ).

    // Clear Timer1 interrupt flag.
    IFS0bits.T1IF = 0;

    // Set Interrupt priority.
    IPC1bits.T1IP = 7;

    INTCONbits.MVEC = 1; // Enable Multi Vecotr Interrupts.
    __builtin_enable_interrupts();  // Enable global interrupts.

    // Enable Timer1 interrupt.
    IEC0bits.T1IE = 1;

    T1CONbits.TON = 1;
}
