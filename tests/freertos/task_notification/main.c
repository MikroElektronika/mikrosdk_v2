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

#define LED1 GPIO_PB0 
#define LED2 GPIO_PB1
#define BUTTON1 GPIO_PB2
#define BUTTON2 GPIO_PB3

static digital_out_t output_pin1;
static digital_out_t output_pin2;
static digital_in_t input_pin1;
static digital_in_t input_pin2;

#define mainNOTIFICATION_LED1        0x01    /* toggle led 1 mask */
#define mainNOTIFICATION_LED2        0x02    /* toggle led 2 mask */

/* Task handles */
TaskHandle_t        xLEDTaskHandle;
TaskHandle_t        xButtonTaskHandle;

/**
 * @brief Button task function
 *
 * This task checks if one of two buttons are pressed 
 * and signals the event with task notifications.
 * 
 */
static void prvButtonTaskFunction( void *pvParameters )
{
    uint16_t i;
    
    uint8_t     previousButton_1State = 1;
    uint8_t     currentButton_1State  = 1;

    uint8_t     previousButton_2State = 1;
    uint8_t     currentButton_2State  = 1;
    for ( ;; )
    {
        /*Read button states*/
        currentButton_1State = digital_in_read( &input_pin1 );
        currentButton_2State = digital_in_read( &input_pin2 );
        /*Detected button signal edge*/
        if( previousButton_1State != currentButton_1State){
            /* soft debaunce */
            for(i = 0; i < 1000; i++);
            /*read button state again to verify rising edge of button signal*/
            currentButton_1State = digital_in_read( &input_pin1 );
            previousButton_1State = currentButton_1State;
            if(currentButton_1State == 0){
                /* notify task by wrtiting to its notification value */
                xTaskNotify(xLEDTaskHandle, mainNOTIFICATION_LED1, eSetBits);
                continue;
            }
        }
        if( previousButton_2State != currentButton_2State){
            /* soft debaunce */
            for(i = 0; i < 1000; i++);
            /*read button state again to verify rising edge of button signal*/
            currentButton_2State = digital_in_read( &input_pin2 );
            previousButton_2State = currentButton_2State;
            if(currentButton_2State == 0){
                /* notify task by wrtiting to its notification value */
                xTaskNotify(xLEDTaskHandle, mainNOTIFICATION_LED2, eSetBits);
                continue;
            }
        } 
    }  
}

/**
 * @brief LED task function
 *
 * This task toggles adequate LED on each button press event.
 * 
 */
static void prvLEDTaskFunction( void *pvParameters )
{
    uint32_t    notifyValue;

    for ( ;; )
    {
       /* Waits for notification value */
       xTaskNotifyWait(0xffffffff, 0xffffffff, &notifyValue, portMAX_DELAY);
       /* Check which button was pressed and toggle adequate LED */
       if((notifyValue & mainNOTIFICATION_LED1) != 0){
           digital_out_toggle(&output_pin1);
       }
       if((notifyValue & mainNOTIFICATION_LED2) != 0){
           digital_out_toggle(&output_pin2);
       }
    }
}


int main(void)
{
    /* Do not remove this line — it ensures correct MCU initialization. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    /* init buttons and LEDs */
    digital_out_init( &output_pin1, LED1 );
    digital_out_init( &output_pin2, LED2 );
    digital_in_init( &input_pin1, BUTTON1 );
    digital_in_init( &input_pin2, BUTTON2 );

    /* Create tasks */
    xTaskCreate( prvButtonTaskFunction,
                 "Button Task",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 5,
                 NULL
               );
    xTaskCreate( prvLEDTaskFunction,
                 "Diode Task",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 6,
                 &xLEDTaskHandle
               );

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
