// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "drv_digital_in.h"
#include "board.h"
#include "delays.h"
#ifdef __XC8__
#include "string.h"
#endif

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h" 
#include "event_groups.h"
// -------------------------------------------------------------------- MACROS

#define TEST_PIN_I2C_SCL HAL_PIN_NC // TODO define I2C SCL pin 
#define TEST_PIN_I2C_SDA HAL_PIN_NC // TODO define I2C SDA pin  

// TODO
// Define an existing pin to check the accuracy of write and read functions
#define TEST_PIN_FIRST_PASS HAL_PIN_NC

// TODO
// Set array size.
// This is the number of bytes which shall be sent/read.
// Tako into consideration that the max size is 1 byte( 255 )
#define ARRAY_LENGTH 150

// TODO
// Used for single read check
#define TEST_READ 71

// TODO Set correct slave address for EEPROM click.
#define I2C_MASTER_SLAVE_ADDRESS 0x50

// TODO Define test pins according to hardware
// Feel free to add additional pins if needed
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin)        digital_out_init( &test_pin, pin ); \
                                 digital_out_high( &test_pin ); \
                                 while(1)

#define signal_success(port,pin) digital_out_init( &port, pin ); \
                                 digital_out_write( &port, 1 )

#define signal_end(pin)          signal_error(pin)

#define mainI2C_WRITER_TASK           ( 3 )
#define mainI2C_READER_TASK           ( 2 )
#define mainI2C_CHECKER_TASK          ( 1 )
// ----------------------------------------------------------------- VARIABLES

static digital_out_t test_pin, scl_pin;
static digital_in_t sda_pin;

static i2c_master_t i2c_master;
static i2c_master_config_t i2c_master_cfg;

static digital_out_t output_pin_first_pass;

static uint8_t write_buffer[ARRAY_LENGTH];
static uint8_t read_buffer[ARRAY_LENGTH];

static volatile uint8_t check_value = 0;
static uint8_t i;


/* handles for FreeRTOS objects */
static SemaphoreHandle_t xWriteDoneSem;   
static SemaphoreHandle_t xReadDoneSem;    
static SemaphoreHandle_t xCycleDoneSem;   
static SemaphoreHandle_t xBuffersMutex;   
static SemaphoreHandle_t xI2CMutex;      

// ----------------------------------------------------------------- USER CODE
void EEPROM_24C02_WrSingle(uint8_t wAddr, uint8_t wData) {
    uint8_t wr_dat[2];

    wr_dat[0] = wAddr;
    wr_dat[1] = wData;
    
    /* since I2C is a shared resource and not thred safe,its accsess needs to be atomic */
    xSemaphoreTake( xI2CMutex, portMAX_DELAY );

    if ( I2C_MASTER_ERROR == i2c_master_write(&i2c_master, &wr_dat, 2) ) {
        signal_error( TEST_PIN_5 );
    }
    
    /* give mutex */
    xSemaphoreGive( xI2CMutex );
}

uint8_t EEPROM_24C02_RdSingle(uint8_t rAddr) {
    uint8_t rd_dat[1];
    uint8_t wr_dat[1];

    wr_dat[0] = rAddr;
    
    /* take mutex */
    xSemaphoreTake( xI2CMutex, portMAX_DELAY );

    if ( I2C_MASTER_ERROR == i2c_master_write(&i2c_master, &wr_dat, 1) ) {
        signal_error( TEST_PIN_7 );
    }

    if ( I2C_MASTER_ERROR == i2c_master_read(&i2c_master, &rd_dat, 1) ) {
        signal_error( TEST_PIN_8 );
    }
    
    /* give mutex */
    xSemaphoreGive( xI2CMutex );

    return rd_dat[0];
}

void application_init()
{
    // Initializes i2c master configuration structure to default values.
    i2c_master_configure_default( &i2c_master_cfg );

    i2c_master_cfg.scl = TEST_PIN_I2C_SCL;
    i2c_master_cfg.sda = TEST_PIN_I2C_SDA;

    digital_out_init( &scl_pin, TEST_PIN_I2C_SCL );
    digital_in_init( &sda_pin, TEST_PIN_I2C_SDA);
    digital_out_high( &scl_pin );
    while ( digital_in_read( &sda_pin ) == 0)
    {
        digital_out_low(&scl_pin);
        Delay_ms(1);
        digital_out_high(&scl_pin);
        Delay_ms(1);
    }

    if( ACQUIRE_FAIL == i2c_master_open( &i2c_master, &i2c_master_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    // Set i2c timeout.
    if ( I2C_MASTER_SUCCESS != i2c_master_set_timeout( &i2c_master, 10000 ) ) {
        signal_error( TEST_PIN_2 );
    }

    // I2C master set speed.
    if ( I2C_MASTER_SUCCESS != i2c_master_set_speed(&i2c_master,
                                                    I2C_MASTER_SPEED_FULL) ) {
        signal_error( TEST_PIN_3 );
    }

    // I2C master set slave address.
    // TODO It is necessary to set the correct slave address for eeprom click.
    if ( I2C_MASTER_SUCCESS != i2c_master_set_slave_address(&i2c_master,
                                                            I2C_MASTER_SLAVE_ADDRESS) ) {
        signal_error( TEST_PIN_4 );
    }
}

/**
 * @brief I2C writer task function
 *
 * This task writes data to EEPROM click.
 * 
 */
static void vI2CWriterTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait for previous cycle to be done  */
        xSemaphoreTake( xCycleDoneSem, portMAX_DELAY );
        
        /* take mutex */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );
        
        /* write data to EEPROM */
        for( uint8_t addr = 0; addr < ARRAY_LENGTH; addr++ )
        {
            uint8_t value = addr;

            EEPROM_24C02_WrSingle( addr, value );
            write_buffer[addr] = value;

            /* EEPROM 24C02 REQUIRES approximately 5ms for intern write cycle */
            vTaskDelay( pdMS_TO_TICKS( 10 ) );
        }

        xSemaphoreGive( xBuffersMutex );

        /* signal reader task to start reading from EEPROM */
        xSemaphoreGive( xWriteDoneSem );
    }
}

/**
 * @brief I2C reader task function
 *
 * This task reads data from EEPROM click.
 * 
 */
static void vI2CReaderTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {   
        /* wait for writing to SRAM to be done */
        xSemaphoreTake( xWriteDoneSem, portMAX_DELAY );
        
        /* take mutex for buffer guard */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );

        uint8_t startAddr = 0;
        
        /* take mutex for i2c guard */
        xSemaphoreTake( xI2CMutex, portMAX_DELAY );
        if ( I2C_MASTER_ERROR ==
             i2c_master_write_then_read( &i2c_master,
                                         &startAddr,
                                         1,
                                         read_buffer,
                                         ARRAY_LENGTH ) )
        {
            signal_error( TEST_PIN_6 );
        }

        /* give mutex */
        xSemaphoreGive( xI2CMutex );
        
        /* give mutex */
        xSemaphoreGive( xBuffersMutex );

        /* signal to checker task that read data is ready to be checked */
        xSemaphoreGive( xReadDoneSem );
    }
}

/**
 * @brief I2C check task function
 *
 * This task compares written and read data.
 * 
 */
static void vI2CCheckTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait for read data to be ready for checking */
        xSemaphoreTake( xReadDoneSem, portMAX_DELAY );

        /* take mutex */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );

        int cmp = memcmp( write_buffer, read_buffer, ARRAY_LENGTH );

        /* give mutex */
        xSemaphoreGive( xBuffersMutex );

        if( !cmp ){
            digital_out_toggle( &output_pin_first_pass );  
        }else{
            signal_error( TEST_PIN_1 );
        }
        
        /* signal writer tasks that the cycle is done */
        xSemaphoreGive( xCycleDoneSem );
    }
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();

    /* LEDs for visual results */
    digital_out_init( &output_pin_first_pass,  TEST_PIN_FIRST_PASS );

    /* smaphores creation */
    xBuffersMutex   = xSemaphoreCreateMutex();
    xI2CMutex       = xSemaphoreCreateMutex();
    xWriteDoneSem   = xSemaphoreCreateBinary();
    xReadDoneSem    = xSemaphoreCreateBinary();
    xCycleDoneSem   = xSemaphoreCreateBinary();

    /* this is so the writer tasks doesnt get blocked at the beginning */
    xSemaphoreGive( xCycleDoneSem );

    /* Create tasks */
    if( xTaskCreate( vI2CWriterTask,
                     "I2C_WR",
                     configMINIMAL_STACK_SIZE + 200 ,
                     NULL,
                     mainI2C_WRITER_TASK,
                     NULL ) != pdPASS ) while(1);

    if( xTaskCreate( vI2CReaderTask,
                     "I2C_RD",
                     configMINIMAL_STACK_SIZE + 200 ,
                     NULL,
                     mainI2C_READER_TASK,
                     NULL ) != pdPASS ) while(1);

    if( xTaskCreate( vI2CCheckTask,
                     "I2C_CHK",
                     configMINIMAL_STACK_SIZE + 200 ,
                     NULL,
                     mainI2C_CHECKER_TASK,
                     NULL ) != pdPASS ) while(1);
    
    /* Start scheduler */
    vTaskStartScheduler();
    
    /* If all is well, the scheduler will now be running, and the following
     line will never be reached.  If the following line does execute, then
     there was most likely insufficient FreeRTOS heap memory available for the idle and/or
     timer tasks to be created. */
    for( ;; )
    {

    }

    return 0;
}

// ----------------------------------------------------------------------- END
