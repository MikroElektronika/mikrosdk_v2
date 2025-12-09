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
#include "drv_uart.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h" 
#include "event_groups.h"

#define mainUART_TASK_PRIO                 ( 1 )
#define mainLED_TASK_PRIO                  ( 2 )
#define mainPROCESSING_TASK_PRIO           ( 3 )

#define TEST_PIN_UART_RX GPIO_PB7
#define TEST_PIN_UART_TX GPIO_PB6 
#define LED GPIO_PB0

static digital_out_t output_pin;

static uart_t uart;             
static uart_config_t uart_cfg;  

static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];
static uint8_t buffer[32];

typedef enum{
    DIODE_COMMAND_ON,
    DIODE_COMMAND_OFF,
    DIODE_COMMAND_UNDEF
}diode_command_t;

/* queue lenght */
#define mainCHAR_QUEUE_LENGTH   5

/* Semaphore handle */
xSemaphoreHandle    xEvent_DiodeCommand;

/* MUTEX handle */
xSemaphoreHandle    xGuard_ControlMsg;

/* Queue handle */
xQueueHandle        xCharQueue;

/* This variable will be used to store command for diode control */
diode_command_t     prvDIODE_COMMAND;

/**
 * @brief Character processing task function
 *
 * This task reads characters from the queue and based on character value
 * sends adequate command to "Diode Control" task.
 * 
 */
static void prvCharProcessingTaskFunction( void *pvParameters )
{
    char        recChar =   0;
    diode_command_t commandToSend = DIODE_COMMAND_UNDEF;
    for ( ;; )
    {
        /*Read char from the queue*/
        xQueueReceive(xCharQueue, &recChar, portMAX_DELAY);
        /* Determine which character is received and based on character value
         * determine which command will be sent to "Diode Control" task */
        switch(recChar){
            case 'e':
                commandToSend   = DIODE_COMMAND_ON;
                break;
            case 'd':
                commandToSend   = DIODE_COMMAND_OFF;
                break;
            default:
                commandToSend   = DIODE_COMMAND_UNDEF;
                break;
        }
        if(commandToSend != DIODE_COMMAND_UNDEF){
            /* take mutex */
            xSemaphoreTake(xGuard_ControlMsg, portMAX_DELAY);
            /* Write command to shared variable */
            prvDIODE_COMMAND = commandToSend;
            /* Give mutex */
            xSemaphoreGive(xGuard_ControlMsg);
            /* Signal the event */
            xSemaphoreGive(xEvent_DiodeCommand);
        }
    }
}

/**
 * @brief Diode control task function
 *
 * This task processes commands received from "Character Processing" task
 * and controls diode state accordingly.
 * 
 */
static void prvDiodeControlTaskFunction( void *pvParameters )
{
    diode_command_t commandToProcess = DIODE_COMMAND_UNDEF;
    for ( ;; )
    {
        /* Wait on event*/
        xSemaphoreTake(xEvent_DiodeCommand, portMAX_DELAY);
        /* take mutex */
        xSemaphoreTake(xGuard_ControlMsg, portMAX_DELAY);
        /* Read shared variable*/
        commandToProcess = prvDIODE_COMMAND;
        /* Give mutex */
        xSemaphoreGive(xGuard_ControlMsg);
        switch(commandToProcess){
        case DIODE_COMMAND_OFF:
            digital_out_low(&output_pin);
            break;
        case DIODE_COMMAND_ON:
            digital_out_high(&output_pin);
            break;
        case DIODE_COMMAND_UNDEF:
            break;
        }
    }
}

/**
 * @brief UART task function
 *
 * This task reads characters from UART and based on character value
 * sends that charachter to "Character Processing" task via queue.
 * 
 */
static void prvUartTaskFunction( void *pvParameters )
{
    for ( ;; )
    {   
        /* Read data from UART */
        int32_t size = uart_read( &uart, buffer, sizeof( buffer ) );

        /* check if anything was read */
        if( size > 0 )
        {
            for( int32_t i = 0; i < size; i++ )
            {
                char c = buffer[ i ];

                switch( c )
                {
                    case 'e':
                    xQueueSendToBack( xCharQueue, &c, portMAX_DELAY );
                        break;
                    case 'd':
                        xQueueSendToBack( xCharQueue, &c, portMAX_DELAY );
                        break;

                    default:
                        break;
                }
            }
        } 
    }
}

int main(void)
{
    /* Do not remove this line — it ensures correct MCU initialization. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    /* Initialize digital output */
    digital_out_init( &output_pin, LED);

    /* Default uart config */
    uart_configure_default( &uart_cfg );

    /* Ring buffer mapping */
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    /* Choose UART mode: Set to `true` for
     * interrupt-driven UART, `false` for polling mode.*/
    uart_cfg.is_interrupt = false;

    uart_cfg.tx_pin = TEST_PIN_UART_TX;  // UART TX pin.
    uart_cfg.rx_pin = TEST_PIN_UART_RX;  // UART RX pin.

    uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );

    if( ACQUIRE_FAIL == uart_open( &uart, &uart_cfg ) ) {
        //signal_error
    }

    if ( UART_SUCCESS != uart_set_baud( &uart, 115200 ) ) {
        //signal_error
    }
    
    /* Create tasks */
    if(xTaskCreate( prvCharProcessingTaskFunction,
                 "PROCESSING TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainPROCESSING_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);

     if(xTaskCreate( prvDiodeControlTaskFunction,
                 "LED TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainLED_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1);  
    
    if(xTaskCreate( prvUartTaskFunction,
                 "UART TASK",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainUART_TASK_PRIO,
                 NULL
               ) != pdPASS) while(1); 
    
    /* Create semaphores        */
    xEvent_DiodeCommand     =   xSemaphoreCreateBinary();
    /* Create MUTEX             */
    xGuard_ControlMsg       =   xSemaphoreCreateMutex();
    /* Create Queue             */
    xCharQueue              =   xQueueCreate(mainCHAR_QUEUE_LENGTH,sizeof(char));

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
