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

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h" 
#include "event_groups.h"

// -------------------------------------------------------------------- MACROS

#define TEST_PIN_PWM_TIM GPIO_PB5 // TODO define pin used in test  MIKROBUS_4_PWM

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

#define PWM_HOLD_TIME_MS   500u

#define mainPWM_DUTY10_TASK           ( 2 )
#define mainPWM_DUTY90_TASK           ( 2 )
// ----------------------------------------------------------------- VARIABLES
static pwm_t pwm;  // PWM driver context structure.
static pwm_config_t pwm_cfg;  // PWM driver context structure.

static digital_out_t test_pin;

/* LEDs for visual representation */
static digital_out_t led_10;
static digital_out_t led_90;

/* handlers for FreeRTOS objects */
static SemaphoreHandle_t xPwmMutex;     // ?titi PWM drajver
static SemaphoreHandle_t xDuty10Sem;    // 10%-task start
static SemaphoreHandle_t xDuty90Sem;    // 90%-task start

// ----------------------------------------------------------------- USER CODE

static void application_init( void )
{
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin = TEST_PIN_PWM_TIM;

    if ( ACQUIRE_FAIL == pwm_open( &pwm, &pwm_cfg ) )
    {
        signal_error( TEST_PIN_1 );
    }

    if ( PWM_SUCCESS != pwm_set_freq( &pwm, TEST_PWM_FREQUENCY ) )
    {
        signal_error( TEST_PIN_2 );
    }

    if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.10f ) )
    {
        signal_error( TEST_PIN_3 );
    }

    if ( PWM_SUCCESS != pwm_start( &pwm ) )
    {
        signal_error( TEST_PIN_4 );
    }

    digital_out_init( &led_10, GPIO_PB0 );   
    digital_out_init( &led_90, GPIO_PB1 );  
}

/**
 * @brief PWM Duty10 task function
 *
 * This task sets PWM duty cycle to 10% and holds it for a defined time.
 * 
 */
static void vPwmDuty10Task( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait unitl its time to change Duty */
        xSemaphoreTake( xDuty10Sem, portMAX_DELAY );
        
        /* take PWM mutex */
        xSemaphoreTake( xPwmMutex, portMAX_DELAY );

        if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.10f ) )
        {
            signal_error( TEST_PIN_5 );
        }
        
        /* give PWM mutex */
        xSemaphoreGive( xPwmMutex );

        /* LED indication which Duty is on*/
        digital_out_high( &led_10 );
        digital_out_low(  &led_90 );

        /* hold 10% Duty for a certain period of time */
        vTaskDelay( pdMS_TO_TICKS( PWM_HOLD_TIME_MS ) );

        /* signal Duty90 task to change duty */
        xSemaphoreGive( xDuty90Sem );
    }
}

/**
 * @brief PWM Duty90 task function
 *
 * This task sets PWM duty cycle to 90% and holds it for a defined time.
 * 
 */
static void vPwmDuty90Task( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait unitl its time to change Duty */
        xSemaphoreTake( xDuty90Sem, portMAX_DELAY );
        
        /* take PWM mutex */
        xSemaphoreTake( xPwmMutex, portMAX_DELAY );

        if ( PWM_SUCCESS != pwm_set_duty( &pwm, 0.90f ) )
        {
            signal_error( TEST_PIN_5 );
        }

        /* give PWM mutex */
        xSemaphoreGive( xPwmMutex );

        /* LED indication which Duty is on*/
        digital_out_low(  &led_10 );
        digital_out_high( &led_90 );

        /* hold 90% Duty for a certain period of time */
        vTaskDelay( pdMS_TO_TICKS( PWM_HOLD_TIME_MS ) );

        /* signal Duty10 task to change duty */
        xSemaphoreGive( xDuty10Sem );
    }
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();

    /* create semaphores */
    xPwmMutex   = xSemaphoreCreateMutex();
    xDuty10Sem  = xSemaphoreCreateBinary();
    xDuty90Sem  = xSemaphoreCreateBinary();

     /* 10% Duty task will be the first one to get CPU time */
    xSemaphoreGive( xDuty10Sem );

    /* tasks creation */
    if( xTaskCreate( vPwmDuty10Task,
                     "PWM10",
                     configMINIMAL_STACK_SIZE + 128,
                     NULL,
                     mainPWM_DUTY10_TASK,
                     NULL ) != pdPASS ) while(1);

    if( xTaskCreate( vPwmDuty90Task,
                     "PWM90",
                     configMINIMAL_STACK_SIZE + 128,
                     NULL,
                     mainPWM_DUTY90_TASK,
                     NULL ) != pdPASS ) while(1);
    
    /* start scheduler */  
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     line will never be reached.  If the following line does execute, then
     there was most likely insufficient FreeRTOS heap memory available for the idle and/or
     timer tasks to be created. */
    for( ;; )
    {

    }

    pwm_close( &pwm );

    return 0;
}
// ----------------------------------------------------------------------- END
