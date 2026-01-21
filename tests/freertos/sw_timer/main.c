/**
 * @file main.c
 * @brief Main source file for the STM32F429ZI application.
 *
 * This is a basic project template providing a minimal structure
 * for initializing the MCU and writing embedded application logic.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "board.h"
#include "drv_digital_out.h"
#include "drv_digital_in.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h" 
#include "event_groups.h"

 #define DIODE_1 HAL_PIN_NC
 #define DIODE_2 HAL_PIN_NC
 #define BUTTON HAL_PIN_NC

#define mainBUTTON_TASK_PRIO        ( 1 )

typedef enum{
    LD_1,
    LD_2,
    LED_UNDEFF
}led_t;

static digital_out_t output_pin1;
static digital_out_t output_pin2;
static digital_in_t input_pin;

/*This variable will be used to store which diode is currently active*/
led_t LED;

/*This timer will be used to toggle active diode*/
TimerHandle_t xDiodeTimer;

/**
 * @brief Button task function
 *
 * This task checks if button is pressed switches between two diodes
 * deciding which will be the active one.
 * 
 */
static void prvButtonTaskFunction( void *pvParameters )
{
    uint16_t i;

    uint8_t     previousButtonState = 1;
    uint8_t     currentButtonState  = 1;
    for ( ;; )
    {
        /*Read button state*/
        currentButtonState = digital_in_read( &input_pin );
        /*Detected button signal edge*/
        if( previousButtonState != currentButtonState){
            /* soft debaunce */
            for(i = 0; i < 1000; i++);
            /*read button state again to verify rising edge of button signal*/
            currentButtonState = digital_in_read( &input_pin );
            previousButtonState = currentButtonState;
            if(currentButtonState == 0){
                /* it is important to stop timer before changing diode state
                * because prvDiodeTimerCallback function also access global
                * variable. In order to prevent mutual exclusion
                * we stop timer */
                xTimerStop(xDiodeTimer, portMAX_DELAY);
                /* Change active diode */
                LED = LED == LD_1 ? LD_2 : LD_1;
                xTimerStart(xDiodeTimer,portMAX_DELAY);
            }
        }
    }
}

/**
 * @brief Diode timer callback function
 *
 * This function toggles active diode each time when timer expires.
 * 
 */
void prvDiodeTimerCallback(TimerHandle_t xTimer){
    if(LED == LD_1){
        digital_out_toggle(&output_pin1);
    }else if(LED == LD_2){
        digital_out_toggle(&output_pin2);
    }
}

int main(void)
{
    /* Do not remove this line — it ensures correct MCU initialization. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    /* init buttons and LEDs */
    digital_out_init( &output_pin1, DIODE_1 );
    digital_out_init( &output_pin2, DIODE_2 );
    digital_in_init( &input_pin, BUTTON );
    
    /* Create button task */
    if(xTaskCreate( prvButtonTaskFunction,
                 "BUTTON TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainBUTTON_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1); 
    
    /* Create timer */
    xDiodeTimer         = xTimerCreate("Diode timer",
                                       pdMS_TO_TICKS(500),
                                       pdTRUE,
                                       NULL,
                                       prvDiodeTimerCallback);
    
    /* Set initial active diode */
    LED = LD_1;

    /* Start timer */
    if( xTimerStart( xDiodeTimer, 0 ) != pdPASS )
    {
        while( 1 );
    }

    /* start scheduler */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     line will never be reached.  If the following line does execute, then
     there was most likely insufficient FreeRTOS heap memory available for the idle and/or
     timer tasks to be created. */
    for( ;; ) {
    }

    return 0;
}
