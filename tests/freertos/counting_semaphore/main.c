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

#define LED GPIO_PB0        
#define BUTTON GPIO_PB1

#define mainBUTTON_TASK_PRIO        ( 1 )
#define mainLED_TASK_PRIO           ( 2 )

static digital_in_t input_pin;
static digital_out_t output_pin;

/*This semaphore whill be used to signal "Button press" event*/
static xSemaphoreHandle xPressCountSem;

/**
 * @brief Button task function
 *
 * This task checks if button is pressed and signals the event with counting semaphore.
 * 
 */
static void prvButtonCountTask( void *pvParameters )
{
    (void) pvParameters;

    uint16_t i;
    uint8_t  previousButtonState = 1; 
    uint8_t  currentButtonState  = 1;

    for( ;; )
    {   
        /*Read button state*/
        currentButtonState = digital_in_read( &input_pin );
        /*Detected button signal edge*/
        if( previousButtonState != currentButtonState )
        {
            /* soft debaunce */
            for( i = 0; i < 1000; i++ );
            /*read button state again to verify rising edge of button signal*/
            currentButtonState  = digital_in_read( &input_pin );
            previousButtonState = currentButtonState;
            if( currentButtonState == 0 )
            {
                xSemaphoreGive( xPressCountSem );
            }
        }
    }
}

/**
 * @brief LED task function
 *
 * This task toggles LED on each 3 button press events.
 * 
 */
static void prvLEDCountTask( void *pvParameters )
{
    (void) pvParameters;
    uint8_t n = 0;

    for( ;; )
    {
        for( n = 0; n < 3; n++ )
        {
            xSemaphoreTake( xPressCountSem, portMAX_DELAY );
        }

        digital_out_toggle( &output_pin );
        n = 0;
    }
}

int main(void)
{
    /* Do not remove this line — it ensures correct MCU initialization. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    /* init button and LED */
    digital_out_init( &output_pin, LED );
    digital_in_init( &input_pin, BUTTON);
    
    /* Create tasks */
    if(xTaskCreate( prvButtonCountTask,
                 "BUTTON TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainBUTTON_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);

     if(xTaskCreate( prvLEDCountTask,
                 "LED TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainLED_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);

    /* Create counting semaphore */
    xPressCountSem = xSemaphoreCreateCounting( 3, 0 );
    
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
