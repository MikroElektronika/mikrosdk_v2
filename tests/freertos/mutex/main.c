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

#define mainBUTTON_TASK_PRIO        ( 1 )
#define mainLED_TASK_PRIO           ( 2 )

typedef enum{
    BUTTON_SW3,
    BUTTON_SW4,
    BUTTON_UNDEF
}button_t;

static digital_in_t input_pin1;
static digital_in_t input_pin2;
static digital_out_t output_pin1;
static digital_out_t output_pin2;

/*This semaphore whill be used to signal "Button press" event*/
xSemaphoreHandle    xEvent_ButtonPressed;

/*This mutex will be used to guard access to shared resource - prvPressedButton variable*/
xSemaphoreHandle    xMutex_GuardButton;

/*This variable will be used to store which button press event is detected*/
button_t            prvPressedButton;   

/**
 * @brief Button task function
 *
 * This task checks if one of two buttons are pressed 
 * and signals the event with binary semaphore.
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
        /*Detected button 1 signal edge*/
        if( previousButton_1State != currentButton_1State){
            /* soft debaunce */
            for(i = 0; i < 1000; i++);
            /*read button state again to verify rising edge of button signal*/
            currentButton_1State = digital_in_read( &input_pin1 );
            previousButton_1State = currentButton_1State;
            if(currentButton_1State == 0){
                /* take mutex */
                xSemaphoreTake(xMutex_GuardButton, portMAX_DELAY);
                /* Write which button press event is detected */
                prvPressedButton    = BUTTON_SW3;
                /* Give mutex */
                xSemaphoreGive(xMutex_GuardButton);
                /* Signal the event */
                xSemaphoreGive(xEvent_ButtonPressed);
                continue;
            }
        }
        /*Detected button 2 signal edge*/
        if( previousButton_2State != currentButton_2State){
            /* soft debaunce */
            for(i = 0; i < 1000; i++);
            /*read button state again to verify rising edge of button signal*/
            currentButton_2State = digital_in_read( &input_pin2 );
            previousButton_2State = currentButton_2State;
            if(currentButton_2State == 0){
                /* take mutex */
                xSemaphoreTake(xMutex_GuardButton, portMAX_DELAY);
                /* Write which button press event is detected */
                prvPressedButton    = BUTTON_SW4;
                /* Give mutex */
                xSemaphoreGive(xMutex_GuardButton);
                /* Signal the event */
                xSemaphoreGive(xEvent_ButtonPressed);
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
    uint16_t i;
    button_t    pressedButton; /*This variable will be used to temporally store global variable value */
    for ( ;; )
    {
        /*Wait on event*/
        xSemaphoreTake(xEvent_ButtonPressed, portMAX_DELAY);
        /* Global variable is shared resource. To access it, first try to
         * take mutex */
        xSemaphoreTake(xMutex_GuardButton, portMAX_DELAY);
        /* Read which button press event is detect */
        pressedButton    = prvPressedButton;
        /* Give mutex */
        xSemaphoreGive(xMutex_GuardButton);
        switch(pressedButton){
        case BUTTON_SW3:
            digital_out_toggle( &output_pin1 );
            break;
        case BUTTON_SW4:
            digital_out_toggle( &output_pin2 );
            break;
        case BUTTON_UNDEF:
            //TODO: Implement error detection
            break;
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
    if(xTaskCreate( prvButtonTaskFunction,
                 "BUTTON TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainBUTTON_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);

     if(xTaskCreate( prvLEDTaskFunction,
                 "LED TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainLED_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);
    
    /* Create binary semaphore */
    xEvent_ButtonPressed = xSemaphoreCreateBinary();

    /* Create mutex */
    xMutex_GuardButton   = xSemaphoreCreateMutex();

    /* Initialize shared variable */
    prvPressedButton     = BUTTON_UNDEF;
    
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
