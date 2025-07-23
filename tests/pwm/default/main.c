// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_pwm.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

#define TEST_PIN_PWM_TIM GPIO_P302 // TODO define pin used in test

#define TEST_PWM_FREQUENCY 5000 // TODO define frequency used in last test

#define CUSTOM_ARRAY false

// TODO Define test pins according to hardware
// Feel free to add additional pins if needed
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

//TODO Set wait time between set_duty and stop signal.
// Take this time to check pwm_duty on oscilloscope.
#define wait_test_time    Delay_ms( 1500 )

// ----------------------------------------------------------------- VARIABLES
static pwm_t pwm;  // PWM driver context structure.
static pwm_config_t pwm_cfg;  // PWM driver context structure.

static digital_out_t test_pin;

#if !CUSTOM_ARRAY
// Array with default test values
uint32_t freq_array[] =
{
    500, 2500, 5000,
    10000, 20000, 28000,
    70000, 126000, 480000,
    590000, 691000, 759000,
    828000, 903000, 1000000
};
#else
// TODO - define custom frequency array if needed
uint32_t freq_array[] =
{

};
#endif

// ----------------------------------------------------------------- USER CODE

static inline void run_test_1( uint32_t freq ) {
    if ( PWM_SUCCESS != pwm_set_freq( &pwm, freq ) ) {
        signal_error( TEST_PIN_2 );
    }

    if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.9 ) ) {
        signal_error( TEST_PIN_4 );
    }

    if ( PWM_SUCCESS != pwm_start( &pwm ) ) {
        signal_error( TEST_PIN_3 );
    }

    wait_test_time;

    if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.1 ) ) {
        signal_error( TEST_PIN_4 );
    }

    wait_test_time;
}

static inline void run_test_2( uint32_t freq ) {
    if ( PWM_SUCCESS != pwm_set_freq( &pwm, freq ) ) {
        signal_error( TEST_PIN_2 );
    }

    if ( PWM_SUCCESS != pwm_start( &pwm ) ) {
        signal_error( TEST_PIN_3 );
    }

    if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.9 ) ) {
        signal_error( TEST_PIN_4 );
    }

    wait_test_time;

    if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.1 ) ) {
        signal_error( TEST_PIN_4 );
    }

    wait_test_time;
}

static inline void run_test_3( void ) {
    int counter = 10;

    while(counter--) {
        if ( PWM_SUCCESS != pwm_stop( &pwm ) ) {
            signal_error( TEST_PIN_3 );
        }
        wait_test_time;

        if ( PWM_SUCCESS != pwm_start( &pwm ) ) {
            signal_error( TEST_PIN_3 );
        }
        wait_test_time;
    }
}
#include "mcu.h"
#define PCLK        60000000UL  // Example Peripheral Clock
#define FREQ_HZ     1000.0f     // Desired PWM frequency
#define DUTY        0.5f        // 50% duty cycle

#define PERIOD      ((uint32_t)(PCLK / FREQ_HZ))       // e.g. 60000
#define COMPARE     ((uint32_t)(PERIOD * DUTY) - 1)    // e.g. 29999

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    int counter = 0;

    // // PSEL 3
    // R_MSTP->MSTPCRD_b.MSTPD6 = 0;

    // R_GPT4->GTCR_b.CST = 0; // stop operation first
    // R_GPT4->GTCR_b.MD = 0x0; // PWM mode
    // R_GPT4->GTBER_b.PR = 1; // count up
    // R_GPT4->GTBER_b.PR = 1; // single buffer operation
    // // .... // freq settings
    // R_GPT4->GTCR = 0;              // Clear control register (stop, reset config)

    // R_GPT4->GTUDDTYC = 0x00;       // Saw-wave PWM mode (count up)
    // R_GPT4->GTIOR = 
    //     (0b01 << 2)  |             // GTIOCA output when counting up and match A (initial output = 1)
    //     (0b00 << 0)  |             // GTIOCA output when counting up and not matching (output = 0)
    //     (1 << 14);                 // Enable GTIOCA output

    // R_GPT4->GTCCR[0] = COMPARE;    // Set compare match A
    // R_GPT4->GTCCR[2] = COMPARE;    // Buffered A

    // R_GPT4->GTPR = PERIOD - 1;     // Set PWM period
    // R_GPT4->GTPBR = PERIOD - 1;    // Buffered period

    // R_GPT4->GTCR = (0b000 << 1);  // PCLK/1 as clock source (TPCS bits)

    // R_GPT4->GTCNT = 0;             // Clear counter
    // R_GPT4->GTCR |= (1 << 0);      // Start timer (CST = 1)
    // // .... // freq settings


    // R_GPT4->GTCNT = 0; // initial counter value

    // // A
    // R_GPT4->GTIOR_b.GTIOA = 0x9;               // Set GTIOC pin function (Initial low -> Low at GTCCRA/B compare match -> High at cycle end)
    // R_GPT4->GTIOR_b.OAE = 1;                   // Enable GTIOC pin output
    // R_GPT4->GTBER_b.CCRA = 1;                  // Set buffer operation for the duty
    // // uint32_t duty = 0; //  ????
    // // R_GPT4->GTCCR[0] = duty? duty - 1 : duty;  // Set compare match value
    // R_GPT4->GTCCR[2] = R_GPT4->GTCCR[0];

    // R_PFS->PORT[3].PIN[2].PmnPFS_b.PMR = 1;
    // R_PFS->PORT[3].PIN[2].PmnPFS_b.PMR = 1;
    // R_PFS->PORT[3].PIN[2].PmnPFS_b.PSEL = 3;

    // if (R_GPT4->GTPR && R_GPT4->GTCCR[0]) {
    //     R_GPT4->GTCR_b.CST = 1;
    // }
    // float duty = 0.0f;
    // float step = 0.01f;
    // uint32_t compare;

    // while (1) {
    //     // Calculate compare value from duty
    //     compare = (uint32_t)(duty * PERIOD);
    //     if (compare > 0) compare--;  // avoid overshoot

    //     R_GPT4->GTCCR[0] = compare;
    //     R_GPT4->GTCCR[2] = compare;

    //     // Update duty
    //     duty += step;
    //     if (duty >= 1.0f) {
    //         duty = 1.0f;
    //         step = -step;
    //     } else if (duty <= 0.0f) {
    //         duty = 0.0f;
    //         step = -step;
    //     }

    //     // Delay to control speed of fading (adjust as needed)
    //     for (volatile int i = 0; i < 30000; i++);
    // }
    
    // while(1);
    // Default config
    pwm_configure_default( &pwm_cfg );

    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher then 7. For example, for porta, pins
    // GPIO_PA8, GPIO_PA9, GPIO_PA10 etc.
    pwm_cfg.pin = TEST_PIN_PWM_TIM;

    if( ACQUIRE_FAIL == pwm_open( &pwm, &pwm_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    // Testing predefined cases for PWM
    // Test 1 - Change freq -> set duty -> start
    // for ( counter = 0; counter < (sizeof(freq_array) / sizeof(uint32_t)); counter++ ) {
    //     // Check if pwm is stoped.
    //     run_test_1( freq_array[ counter ] );
    //     wait_test_time;
    // }

    // // Test 2 - Change freq -> start -> set duty
    // for ( counter = 0; counter < (sizeof(freq_array) / sizeof(uint32_t)); counter++ ) {
    //     // Check if pwm is stoped.
    //     run_test_2( freq_array[ counter ] );
    //     wait_test_time;
    // }

    // // Test 3 - stop -> start and so on - simulate LED blinking
    // run_test_3();

    // TODO Test different freq for PWM.
    // Using oscilloscope test all possible freq.
    // Test the lowest possible frequency
    // Test a frequency that is less than the lowest possible,
    // and see if the freq is set to the lowest possible
    if ( PWM_SUCCESS != pwm_set_freq( &pwm, TEST_PWM_FREQUENCY ) ) {
        signal_error( TEST_PIN_2 );
    }

    if ( PWM_SUCCESS != pwm_start( &pwm ) ) {
        signal_error( TEST_PIN_3 );
    }

    // TODO
    // Test different percentages for duty from 0% to 100%
    // 0,0.1,0.2..0.5....1
    // Using an oscilloscope check if the set duty is correct.
    if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.5 ) ) {
        signal_error( TEST_PIN_4 );
    }

    // ADD begin
    float duty = 0.0f;
    float step = 0.01f;
    uint32_t compare;

    while (1) {
        // Calculate compare value from duty
        compare = (uint32_t)(duty * PERIOD);
        if (compare > 0) compare--;  // avoid overshoot

        R_GPT4->GTCCR[0] = compare;
        R_GPT4->GTCCR[2] = compare;

        // Update duty
        duty += step;
        if (duty >= 1.0f) {
            duty = 1.0f;
            step = -step;
        } else if (duty <= 0.0f) {
            duty = 0.0f;
            step = -step;
        }

        // Delay to control speed of fading (adjust as needed)
        for (volatile int i = 0; i < 30000; i++);
    }
    
    while(1);
    // ADD end

    wait_test_time;

    // Check if pwm is stoped.
    if ( PWM_SUCCESS != pwm_stop( &pwm ) ) {
        signal_error( TEST_PIN_5 );
    }

    // Close PWM module.
    // TODO Test by debugging and stepping into.
    // Make sure to confirm that everything is
    // disabled/dealocated etc.
    pwm_close( &pwm );

    return 0;
}

// ----------------------------------------------------------------------- END
