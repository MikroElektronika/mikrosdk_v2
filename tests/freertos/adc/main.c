// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_port.h"
#include "drv_analog_in.h"
#include "board.h"
#include "drv_uart.h"
#include "conversions.h"
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

// TODO define pin if MIKROBUS_1_AN doesn't exist 
#define TEST_PIN_ADC_AN HAL_PIN_NC

// TODO Define result output
#define ANALOG_IN_UART_TEST 1 // Display result via UART defined pins

#define TEST_PIN_UART_TX HAL_PIN_NC // TODO define pin if displaying result via UART 
#define TEST_PIN_UART_RX HAL_PIN_NC // TODO define pin if displaying result via UART 

static uart_t uart;  // UART driver context structure.
static uart_config_t uart_cfg;  // UART driver context structure.

static uint8_t uart_rx_buffer[256];
static uint8_t uart_tx_buffer[256];

// TODO Define values used in test
#define TEST_VREF_VALUE 3.3f
#define TEST_RESOLUTION_VALUE ANALOG_IN_RESOLUTION_12_BIT

// TODO Define test pins according to hardware
// Feel free to add additional ones if required
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)

#define mainADC_SAMPLER_TASK            ( 3 )
#define mainADC_CONSUMER_TASK           ( 2 )

/* queue lenght */
#define mainADC_QUEUE_LENGTH   16

// ----------------------------------------------------------------- VARIABLES

static analog_in_t analog_in;  // Analog input driver context structure.ucture.
static analog_in_config_t  analog_in_cfg;  // ADC init configuration structure.
static digital_out_t test_pin;
float read_voltage_value;
uint16_t analog_in_read_value;

static uint8_t analog_in_read_buffer[32];

/* Queue for adc samples - uint16_t */
static QueueHandle_t      xAdcQueue;

/**
 * @brief ADC sampler task function
 *
 * This task takes ADC samples and sends the raw values to a queue.
 * 
 */
static void prvAdcSamplerTask( void *pvParameters )
{
    ( void ) pvParameters;

    for( ;; )
    {
        if ( ADC_ERROR == analog_in_read( &analog_in, &analog_in_read_value ) ) {
            signal_error( HAL_PIN_NC );
        }

        /* optional, to check value while debugging */
        if ( ADC_ERROR == analog_in_read_voltage( &analog_in, &read_voltage_value ) ) {
            signal_error( HAL_PIN_NC );
        }

        /* send sampled value to the queue */
        xQueueSendToBack( xAdcQueue, &analog_in_read_value, portMAX_DELAY );

        /* delay itself for 100ms */
        vTaskDelay( pdMS_TO_TICKS( 100 ) );
    }
}

/**
 * @brief ADC consumer task function
 *
 * This task receives ADC samples from a queue and sends the values via UART.
 * 
 */
static void prvAdcConsumerTask( void *pvParameters )
{
    ( void ) pvParameters;
    uint16_t value;

    for( ;; )
    {
        if( xQueueReceive( xAdcQueue, &value, portMAX_DELAY ) == pdTRUE )
        {
            /* cenvert to string and send via uart */
            uint16_to_str( value, analog_in_read_buffer );
            uart_println( &uart, analog_in_read_buffer );
        }
    }
}

void application_init()
{
    uart_configure_default(&uart_cfg);
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    uart_cfg.rx_pin = TEST_PIN_UART_RX;  // UART RX pin.
    uart_cfg.tx_pin = TEST_PIN_UART_TX;  // UART TX pin.

    uart_cfg.tx_ring_size = sizeof(uart_tx_buffer);
    uart_cfg.rx_ring_size = sizeof(uart_rx_buffer);

    uart_open( &uart, &uart_cfg );
    uart_set_baud( &uart, 115200 );  // Set baud rate.
    uart_println( &uart, "Hello!!!" );  // Write out data.

    // Default config
    analog_in_configure_default( &analog_in_cfg );

    /* Set AN pin. */
    analog_in_cfg.input_pin = TEST_PIN_ADC_AN;  
    
    /* Set ADC resolution. */
    analog_in_cfg.resolution = TEST_RESOLUTION_VALUE;  

    analog_in_cfg.vref_input = ANALOG_IN_VREF_EXTERNAL;

    analog_in_cfg.vref_value = TEST_VREF_VALUE;

    if( ACQUIRE_FAIL == analog_in_open( &analog_in, &analog_in_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    /* Set ADC resolution */
    if ( ADC_ERROR == analog_in_set_resolution( &analog_in, TEST_RESOLUTION_VALUE ) ) {
        signal_error( TEST_PIN_2 );
    }

    if ( ADC_ERROR == analog_in_set_vref_input( &analog_in, ANALOG_IN_VREF_EXTERNAL) ) {
        signal_error( TEST_PIN_3 );
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &analog_in, TEST_VREF_VALUE ) ) {
        signal_error( TEST_PIN_3 );
    }
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();

   /* create tasks */
    if( xTaskCreate( prvAdcSamplerTask,
                     "ADC_SAMPLER",
                     configMINIMAL_STACK_SIZE,
                     NULL,
                     mainADC_SAMPLER_TASK,
                     NULL ) != pdPASS ) while(1);

    if( xTaskCreate( prvAdcConsumerTask,
                     "ADC_CONS",
                     configMINIMAL_STACK_SIZE,
                     NULL,
                     mainADC_CONSUMER_TASK,
                     NULL ) != pdPASS ) while(1);
    
    /* Create Queue */
    xAdcQueue = xQueueCreate( mainADC_QUEUE_LENGTH, sizeof( uint16_t ) );
    if( xAdcQueue == NULL ) while(1);

    /* Start scheduler */
    vTaskStartScheduler();
    
    /* If all is well, the scheduler will now be running, and the following
     line will never be reached.  If the following line does execute, then
     there was most likely insufficient FreeRTOS heap memory available for the idle and/or
     timer tasks to be created. */
    for( ;; ){

    }

    analog_in_close( &analog_in );

    return 0;
}

// ----------------------------------------------------------------------- END
