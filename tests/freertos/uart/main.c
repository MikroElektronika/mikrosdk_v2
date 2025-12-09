// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_uart.h"
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

#define TEST_PIN_UART_TX MIKROBUS_1_TX // TODO define UART TX pin
#define TEST_PIN_UART_RX MIKROBUS_1_RX // TODO define UART RX pin

// TODO Define test pins according to hardware
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC
#define TEST_PIN_9  HAL_PIN_NC
#define TEST_PIN_10 HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

#define mainUART_RX_TASK            ( 2 )
#define mainUART_TX_TASK            ( 3 )
// ----------------------------------------------------------------- VARIABLES
static uart_t uart;  // UART driver context structure.
static uart_config_t uart_cfg;  // UART driver context structure.

// Be careful to have big enough buffers.
// TODO Test different buffer sizes.
static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];
static uint8_t buffer[32];

static int32_t read_size = 0;

static digital_out_t test_pin;

/* FreeRTOS objects handlers */
static QueueHandle_t     xRxQueue   = NULL;  
static SemaphoreHandle_t xUartMutex = NULL; 

void application_init(){
   // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    // Choose UART mode: Set to `true` for
    // interrupt-driven UART, `false` for polling mode.
    uart_cfg.is_interrupt = false;

    uart_cfg.tx_pin = TEST_PIN_UART_TX;  // UART TX pin.
    uart_cfg.rx_pin = TEST_PIN_UART_RX;  // UART RX pin.

    uart_cfg.tx_ring_size = sizeof( uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( uart_rx_buffer );

    if( ACQUIRE_FAIL == uart_open( &uart, &uart_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    // Set baud rate.
    if ( UART_SUCCESS != uart_set_baud( &uart, 115200 ) ) {
        signal_error( TEST_PIN_2 );
    }

    // Set data parity. ( no parity )
    if ( UART_SUCCESS != uart_set_parity( &uart, UART_PARITY_DEFAULT ) ) {
        signal_error( TEST_PIN_3 );
    };

    // Set stop bits. ( one stop bit )
    if ( UART_SUCCESS != uart_set_stop_bits( &uart, UART_STOP_BITS_DEFAULT ) ) {
        signal_error( TEST_PIN_4 );
    }

    // Set data bits. ( 8-bit data )
    if ( UART_SUCCESS != uart_set_data_bits( &uart, UART_DATA_BITS_DEFAULT ) ) {
        signal_error( TEST_PIN_5 );
    }

     Delay_100ms();

    // Write out data.
    if ( UART_ERROR == uart_print( &uart, "Hello!" ) ) {
        signal_error( TEST_PIN_6 );
    }

    // Delay needed because of `uart_clear` function, so all data is transmitted.
    Delay_100ms();

    // Write out data with new line.
    if ( UART_ERROR == uart_println( &uart, "This UART is on object 1!" ) ) {
        signal_error( TEST_PIN_7 );
    }
   
    // Delay needed because of `uart_clear` function, so all data is transmitted.
    Delay_100ms();

    // Clear rx and tx buffers.
    uart_clear( &uart );
    
    // Set blocking mode.
    uart_set_blocking( &uart, true );
}

/**
 * @brief UART RX task function
 *
 * This task reads data from UART and puts received bytes into a queue.
 */
static void vUartRxTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* take uart mutex */
        xSemaphoreTake( xUartMutex, portMAX_DELAY );
    
        read_size = uart_read( &uart, buffer, sizeof( buffer ) );

        /* give uart mutex */
        xSemaphoreGive( xUartMutex );
         
        /* check if anything was read */
        if( read_size > 0 )
        {
            /* send recieved bytes to queue */
            for( int32_t i = 0; i < read_size; i++ )
            {
                uint8_t ch = buffer[i];
                xQueueSend( xRxQueue, &ch, portMAX_DELAY );
            }
        }
        else
        {
            if( uart.is_blocking && ( read_size == UART_ERROR ) )
            {
                signal_error( TEST_PIN_9 );
            }
        }
    
    }
}

/**
 * @brief UART TX task function
 *
 * This task reads bytes from a queue and sends them back via UART (echo).
 */
static void vUartTxTask( void *pvParameters )
{
    (void) pvParameters;
    uint8_t ch;

    for( ;; )
    {    
        /* wait for data in queue */
        if( xQueueReceive( xRxQueue, &ch, portMAX_DELAY ) == pdTRUE )
        {   
            /* take uart mutex */
            xSemaphoreTake( xUartMutex, portMAX_DELAY );

            int32_t written = uart_write( &uart, &ch, 1 );

            /* give uart mutex */
            xSemaphoreGive( xUartMutex );
        }
    }
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init();

    /* create semaphore */
    xUartMutex = xSemaphoreCreateMutex();

    /* create queue */
    xRxQueue = xQueueCreate( 128, sizeof( uint8_t ) );

    /* create tasks */
    if( xTaskCreate( vUartRxTask,
                     "UART_RX",
                     configMINIMAL_STACK_SIZE + 200,
                     NULL,
                     mainUART_RX_TASK,
                     NULL ) != pdPASS ) while(1);

    if( xTaskCreate( vUartTxTask,
                     "UART_TX",
                     configMINIMAL_STACK_SIZE + 200,
                     NULL,
                     mainUART_TX_TASK,
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

    uart_close( &uart );

    return 0;
}
// ----------------------------------------------------------------------- END
