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

#define mainLED_TASK_PRIO           ( 1 )

static digital_out_t output_pin;

/**
 * @brief Blink task function
 *
 * This task toggles an output pin every 500 ms.
 * 
 */
static void vBlinkTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        digital_out_toggle(&output_pin);
        vTaskDelay( pdMS_TO_TICKS( 500 ) );  // 500 ms
    }
}

int main(void)
{
    /* Do not remove this line — it ensures correct MCU initialization. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    /* init digital output */
    digital_out_init( &output_pin, LED );
    
    /* Create blink task */
    if(xTaskCreate( vBlinkTask,
                 "BLINK",
                 256,
                 NULL,
                 mainLED_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);

    /* Start the scheduler */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     line will never be reached.  If the following line does execute, then
     there was most likely insufficient FreeRTOS heap memory available for the idle and/or
     timer tasks to be created. */
    for( ;; ) {
    }

    return 0;
}
