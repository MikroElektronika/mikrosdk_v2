// ------------------------------------------------------------------ INCLUDES

#include "drv_digital_out.h"
#include "drv_pwm.h"
#include "board.h"

// -------------------------------------------------------------------- MACROS

#define TEST_PIN_PWM_TIM HAL_PIN_NC // TODO define pin used in test

#define TEST_PWM_FREQUENCY 5000 // TODO define frequency used in test

// TODO Define test pins according to hardware
// Feel free to add additional pins if needed
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

//TODO Set wait time between set_duty and stop signal.
// Take this time to check pwm_duty on oscilloscope.
#define wait_test_time    Delay_ms( 10000 )

// ----------------------------------------------------------------- VARIABLES
static pwm_t pwm;  // PWM driver context structure.
static pwm_config_t pwm_cfg;  // PWM driver context structure.

static digital_out_t test_pin;
// ----------------------------------------------------------------- USER CODE
int main( void ) {
    // Default config
    pwm_configure_default( &pwm_cfg );

    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher then 7. For example, for porta, pins
    // PA8, PA9, PA10 etc.
    pwm_cfg.pin = TEST_PIN_PWM_TIM;

    // TODO Test different freq for PWM.
    // Using oscilloscope test all possible freq.
    // Test the lowest possible frequency
    // Test a frequency that is less than the lowest possible,
    // and see if the freq is set to the lowest possible
    pwm_cfg.freq_hz = TEST_PWM_FREQUENCY;

    if( ACQUIRE_FAIL == pwm_open( &pwm, &pwm_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    // Set PWM freq.
    // TODO Test different freq values.
    if ( PWM_SUCCESS != pwm_set_freq( &pwm, pwm_cfg.freq_hz ) ) {
        signal_error( TEST_PIN_2 );
    }

    // Start PWM
    if ( PWM_SUCCESS != pwm_start( &pwm ) ) {
        signal_error( TEST_PIN_3 );
    }

    while( 1 )
    {
        // TODO
        // Test different percentages for duty from 0% to 100%
        // 0,0.1,0.2..0.5....1
        // Using an oscilloscope check if the set duty is correct.
        if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.5 ) ) {
            signal_error( TEST_PIN_4 );
        } else {
            wait_test_time;
            break;
        }
    }

    // Check if pwm is stoped.
    if ( PWM_SUCCESS != pwm_stop( &pwm ) ) {
        signal_error( TEST_PIN_5 );
    }

    // Close PWM module.
    // TODO Test by debugging and stepping into.
    // Make sure to confirm that everything is
    // disabled/dealocated etc.
    pwm_close( &pwm );
    signal_end( TEST_PIN_6 );

    return 0;
}

// ----------------------------------------------------------------------- END
