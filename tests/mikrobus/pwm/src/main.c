// ------------------------------------------------------------------ INCLUDES

#include "mikrobus_pwm.h"

// -------------------------------------------------------------------- MACROS

// NOTE If set to true, test is done on a single pin.
//      If set to false, test is done on all mikroBUS pins
//      defined in 'board.h'.
#define SINGLE_MIKROBUS true

#if SINGLE_MIKROBUS
    // TODO define PWM test pin.
    // NOTE MIKROBUS_x_PWM where 'x' is mikroBUS number.
    #define TEST_PIN_PWM_TIM HAL_PIN_NC
    #define TEST_PIN_COUNT 1
    pin_name_t test_pins[TEST_PIN_COUNT] = {TEST_PIN_PWM_TIM};
#else
    #define TEST_PIN_COUNT MIKROBUS_COUNT
    pin_name_t *test_pins = test_pins_mikrobus;
#endif

// TODO Define frequency used in test.
#define TEST_PWM_FREQUENCY 5000

// TODO PWM step.
#define PWM_STEP 0.05

// TODO Wait time defined in ms.
#define WAIT_TIME 100

// ----------------------------------------------------------------- VARIABLES

static float duty_cycle = 0.0;

static pwm_t pwm;
static pwm_config_t pwm_cfg;

// ----------------------------------------------------------------- USER CODE

void main() {
    uint8_t cnt = 0;

    while (1) {
        for ( cnt = 0; cnt < TEST_PIN_COUNT; cnt++ ) {
            // STEP 1: Initialize and configure PWM pin.
            // ---------------------------------------------------------------
            pwm_configure_default( &pwm_cfg );
            // NOTE 'cnt' represents mikroBUS number
            //      i.e 0 is mikroBUS1, 1 is mikroBUS2...
            pwm_cfg.pin = test_pins[cnt];
            pwm_cfg.freq_hz = TEST_PWM_FREQUENCY;

            if( ACQUIRE_FAIL == pwm_open( &pwm, &pwm_cfg ) ) {
                while(1);
            }

            if ( PWM_SUCCESS != pwm_set_freq( &pwm, pwm_cfg.freq_hz ) ) {
                while(1);
            }

            if ( PWM_SUCCESS != pwm_start( &pwm ) ) {
                while(1);
            }
            // ---------------------------------------------------------------

            // STEP 2: Toggle duty cycle from max to min.
            // ---------------------------------------------------------------
            for ( duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= PWM_STEP ) {
                if ( PWM_SUCCESS != pwm_set_duty( &pwm, duty_cycle ) ) {
                    while(1);
                } 

                Delay_ms(WAIT_TIME);
            }

            // STEP 3: Close the module and prepare for next mikroBUS.
            // ---------------------------------------------------------------
            pwm_close( &pwm );
            // ---------------------------------------------------------------
        }
    }

}

// ----------------------------------------------------------------------- END
