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
#include "delays.h"

// -------------------------------------------------------------------- MACROS

#define TEST_PWM_FREQUENCY 5000

#ifndef PD3
    #define PD3 HAL_PIN_NC
#endif
#ifndef PD4
    #define PD4 HAL_PIN_NC
#endif
#ifndef PD5
    #define PD5 HAL_PIN_NC
#endif
#ifndef PD6
    #define PD6 HAL_PIN_NC
#endif
#ifndef PD7
    #define PD7 HAL_PIN_NC
#endif

// TODO Define test pins according to hardware
// Feel free to add additional pins if needed
#define TEST_PIN_1 PD3
#define TEST_PIN_2 PD4
#define TEST_PIN_3 PD5
#define TEST_PIN_4 PD6
#define TEST_PIN_5 PD7

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

// ----------------------------------------------------------------- VARIABLES

// PWM driver context structures.
static pwm_t pwm1;
static pwm_t pwm2;
static pwm_t pwm3;
static pwm_t pwm4;

// PWM driver configuration structure.
// We only need 1 as all 4 pins are on the same timer module.
static pwm_config_t pwm_cfg;

// Test pin context structure.
static digital_out_t test_pin;

#ifndef PD12
    #define PD12 HAL_PIN_NC
#endif
#ifndef PD13
    #define PD13 HAL_PIN_NC
#endif
#ifndef PD14
    #define PD14 HAL_PIN_NC
#endif
#ifndef PD15
    #define PD15 HAL_PIN_NC
#endif

// TODO - Define variables for test here.
#define PWMS  {&pwm1, &pwm2, &pwm3, &pwm4}
#define DUTYS {0.1, 0.3, 0.5, 0.7}
#define PINS  {PD12, PD13, PD14, PD15}

// TODO - Set to 1 for continuous loop.
#define LED_WAVE 1

// ----------------------------------------------------------------- USER CODE

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    pwm_t *pwm_arrays[] = PWMS;
    pin_name_t pin_array[] = PINS;
    float duty_array[] = DUTYS;

    uint8_t counter = 0;

    // Default config
    pwm_configure_default( &pwm_cfg );

    // Initialize each pin signal once.
    for (counter = 0; counter < (sizeof(pin_array) / sizeof(pin_name_t)); counter++) {
        pwm_cfg.pin = pin_array[counter];
        if( ACQUIRE_FAIL == pwm_open( pwm_arrays[counter], &pwm_cfg ) ) {
            signal_error( TEST_PIN_1 );
        }
    }

    // Then just initialize the frequency.
    // This can be done only once, as all 4 objects will operate
    // on the same module.
    if ( PWM_SUCCESS != pwm_set_freq( pwm_arrays[0], TEST_PWM_FREQUENCY ) ) {
        signal_error( TEST_PIN_2 );
    }

    // Then start all channel signals.
    for (counter = 0; counter < (sizeof(pin_array) / sizeof(pin_name_t)); counter++) {
        if ( PWM_SUCCESS != pwm_start( pwm_arrays[counter] ) ) {
            signal_error( TEST_PIN_3 );
        }
    }

    // Now simply set duty values for separate channels.
    #if LED_WAVE
    while(1) {
    #endif
        for (counter = 0; counter < (sizeof(pin_array) / sizeof(pin_name_t)); counter++) {
            if (duty_array[counter] > 1.0) {
                duty_array[counter] = 0.0;
            }
            if ( PWM_SUCCESS != pwm_set_duty( pwm_arrays[counter], duty_array[counter] ) ) {
                signal_error( TEST_PIN_4 );
            }
            duty_array[counter] += 0.1;
            // Short timeout so we can see the change on the LEDs.
            Delay_ms(15);
        }
    #if LED_WAVE
    };
    #endif

    // It will get here only if LED_WAVE is 0.
    signal_end( TEST_PIN_5 );

    // It will never get here.
    return 0;
}

// ----------------------------------------------------------------------- END
