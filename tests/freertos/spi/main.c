// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_spi_master.h"
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
#define SINGLE_SRAM_CLICK_TEST

#define TEST_PIN_SPI_CS1   MIKROBUS_4_CS // TODO Define Chip Select pin.
#define TEST_PIN_SPI_SCK1  MIKROBUS_4_SCK // TODO Define SCK pin.
#define TEST_PIN_SPI_MISO1 MIKROBUS_4_MISO // TODO Define MISO pin.
#define TEST_PIN_SPI_MOSI1 MIKROBUS_4_MOSI // TODO Define MOSI pin.

#define TEST_PIN_SIGNAL_SUCCESS1 GPIO_PB0 // TODO Define signal pin (write-then-read, SRAM click 1).
#define TEST_PIN_SIGNAL_SUCCESS3 GPIO_PB1 // TODO Define signal pin (transfer, SRAM click 1).

// TODO Define test pins according to hardware.
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

#define signal_error(pin)   digital_out_init( &test_pin, pin ); \
                            digital_out_high( &test_pin ); \
                            while(1)

#define signal_success(port,pin)    digital_out_init( &port, pin ); \
                                    digital_out_write( &port, 1 )

// SRAM Click specific macros.
#define DATA_LENGTH                         150
#define SRAM_CLICK_WRITE_CMD                2
#define SRAM_CLICK_READ_CMD                 3
#define SRAM_CLICK_WRITE_DATA_LENGTH        5
#define SRAM_CLICK_WRITE_READ_DATA_LENGTH   4
#define SRAM_CLICK_DEFAULT_WRITE_DATA       0

#define SRAM_CLICK_1_SPEED                  100000

#define mainSPI_WRITER_TASK           ( 3 )
#define mainSPI_READER_TASK           ( 2 )
#define mainSPI_CHECKER_TASK          ( 1 )
#define mainSPI_TRANSFER_TASK         ( 2 )
// ----------------------------------------------------------------- VARIABLES
// Instances of structs necessary for SPI Master testing.
static digital_out_t test_pin;

static digital_out_t result_pin_sram_click_1;

static spi_master_t sram_click_1;
static spi_master_config_t sram_click_1_config;

static digital_out_t output_pin;
static digital_out_t output_pin2;

// SRAM Click specific variables.
// Array for data to be written - SRAM Click 1.
static uint8_t write_data_buffer_sram_click_1[DATA_LENGTH];

// Array for data to be read - SRAM Click 1.
static uint8_t read_data_buffer_sram_click_1[DATA_LENGTH];

/* FreeRTOS sync primitiva */
static SemaphoreHandle_t xWriteDoneSem;   // writer -> reader
static SemaphoreHandle_t xReadDoneSem;    // reader -> checker
static SemaphoreHandle_t xCheckDoneSem;   // checker -> writer (nova tura)
static SemaphoreHandle_t xBuffersMutex;   // ?titi oba buffera
static SemaphoreHandle_t xSpiMutex;   // ?titi oba buffera
static SemaphoreHandle_t xStartTransferSem; // checker -> transfer
static SemaphoreHandle_t xTransferDoneSem;  // transfer -> checker
// ----------------------------------------------------------------- USER CODE

// SRAM Click 1 Write procedure.
void sram_click_1_write(uint32_t address, uint8_t data_to_be_written) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[SRAM_CLICK_WRITE_DATA_LENGTH] = {0};

    // Fill in necessary data in order for SRAM Click to be working correctly.
    local_array[0] = SRAM_CLICK_WRITE_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;
    local_array[4] = data_to_be_written;
    
    // take spi mutex
    xSemaphoreTake( xSpiMutex, portMAX_DELAY );

    // Select SRAM Click 1.
    spi_master_select_device(TEST_PIN_SPI_CS1);

    // Write data to SRAM Click 1.
    spi_master_write(&sram_click_1, &local_array, SRAM_CLICK_WRITE_DATA_LENGTH);

    // Deselect SRAM Click 1.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);
    
    // give spi mutex
    xSemaphoreGive( xSpiMutex );
}

// SRAM Click 1 Read procedure.
void sram_click_1_read(uint32_t address) {
    // Local array for storing appropriate data, which will be sent to SRAM Click.
    uint8_t local_array[4] = {0};

    // Fill in necessary data in order for SRAM Click to be working correctly.
    local_array[0] = SRAM_CLICK_READ_CMD;
    local_array[1] = address >> 16;
    local_array[2] = address >> 8;
    local_array[3] = address;
    
    // take spi mutex
    xSemaphoreTake( xSpiMutex, portMAX_DELAY );

    // Select SRAM Click 1.
    spi_master_select_device(TEST_PIN_SPI_CS1);

    // Write data to SRAM Click 1.
    spi_master_write_then_read(&sram_click_1, &local_array, SRAM_CLICK_WRITE_READ_DATA_LENGTH, &read_data_buffer_sram_click_1, DATA_LENGTH);

    // Deselect SRAM Click 1.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);
    
    // give spi mutex
    xSemaphoreGive( xSpiMutex );
}

void sram_click_1_transfer(uint32_t address) {
    // Prepare the 4-byte command header (read command + 24-bit address).
    uint8_t local_header[4] = {0};

    local_header[0] = SRAM_CLICK_READ_CMD;
    local_header[1] = address >> 16;
    local_header[2] = address >> 8;
    local_header[3] = address;

    // Clear the write and read buffers.
    memset(read_data_buffer_sram_click_1, 0, DATA_LENGTH);

    // Copy expected data to write buffer for full-duplex transfer.
    for (uint8_t i = 0; i < DATA_LENGTH; i++) {
        write_data_buffer_sram_click_1[i] = i;
    }
    
    // take spi mutex
    xSemaphoreTake( xSpiMutex, portMAX_DELAY );

    // Select SRAM Click 1.
    spi_master_select_device(TEST_PIN_SPI_CS1);

    // Send the command header first.
    spi_master_write(&sram_click_1, &local_header, sizeof(local_header));

    // Then transfer (write and read simultaneously).
    spi_master_transfer(&sram_click_1, write_data_buffer_sram_click_1,
                        read_data_buffer_sram_click_1, DATA_LENGTH);

    // Deselect SRAM Click 1.
    spi_master_deselect_device(TEST_PIN_SPI_CS1);

    // give spi mutex
    xSemaphoreGive( xSpiMutex );
}

void application_init() {
    // Set default properties for SRAM Click 1.
    spi_master_configure_default(&sram_click_1_config);

    // Set desired basic properties for SRAM Click 1 which is on mikroBUS1.
    sram_click_1_config.sck = TEST_PIN_SPI_SCK1;
    sram_click_1_config.miso = TEST_PIN_SPI_MISO1;
    sram_click_1_config.mosi = TEST_PIN_SPI_MOSI1;
    sram_click_1_config.speed = SRAM_CLICK_1_SPEED;
    sram_click_1_config.mode = SPI_MASTER_MODE_DEFAULT;
    sram_click_1_config.default_write_data = SRAM_CLICK_DEFAULT_WRITE_DATA;

    // Try to reserve memory for the SRAM Click 1.
    if (ACQUIRE_FAIL == spi_master_open(&sram_click_1, &sram_click_1_config)) {
        signal_error( TEST_PIN_1 );
    }

    // Set Chip Select polarity (SRAM Click requires active low).
    spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);

    // Set desired default write (dummy) data.
    spi_master_set_default_write_data(&sram_click_1, SRAM_CLICK_DEFAULT_WRITE_DATA);

    // Set desired baud rate (speed).
    spi_master_set_speed(&sram_click_1, SRAM_CLICK_1_SPEED);

    // Set desired mode (SRAM Click requires mode 0).
    spi_master_set_mode(&sram_click_1, SPI_MASTER_MODE_DEFAULT);
}

/**
 * @brief SPI write task function
 *
 * This task writes data to SRAM click.
 */
static void vSramWriterTask( void *pvParameters )
{
    (void) pvParameters;
    uint8_t i;

    for( ;; )
    {
        /* wait for the cycle to be done */
        xSemaphoreTake( xCheckDoneSem, portMAX_DELAY );
        
        /* take buffer mutex */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );

        for( i = 0; i < DATA_LENGTH; i++ )
        {
            uint8_t value = i;

            /* upis u SRAM */
            sram_click_1_write( i, value );

            /* zapamti ?ta o?ekujemo */
            write_data_buffer_sram_click_1[i] = value;
        }

        /* give buffer mutex */
        xSemaphoreGive( xBuffersMutex );

        /* signal to read task that writing to SRAM is done */
        xSemaphoreGive( xWriteDoneSem );
    }
}

/**
 * @brief SPI read task function
 *
 * This task reads data from SRAM click.
 */
static void vSramReaderTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait until data is written to SRAM */
        xSemaphoreTake( xWriteDoneSem, portMAX_DELAY );
        
        /* take buffer mutex */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );

        sram_click_1_read( 0 );
        
        /* give buffer mutex */
        xSemaphoreGive( xBuffersMutex );

        /* signal to checker task that read data is ready to be checked */
        xSemaphoreGive( xReadDoneSem );
    }
}

/**
 * @brief SPI check task function
 *
 * This task compares written and read data.
 */
static void vSramCheckTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait until read data is ready to be compared */
        xSemaphoreTake( xReadDoneSem, portMAX_DELAY );

        /* take buffer mutex */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );

        int cmp = memcmp( write_data_buffer_sram_click_1,
                          read_data_buffer_sram_click_1,
                          DATA_LENGTH );
        
        /* give buffer mutex */
        xSemaphoreGive( xBuffersMutex );

        if( cmp == 0 )
        {
            digital_out_toggle(&output_pin);
        }
        else
        {
            signal_error( TEST_PIN_1 );
        }

         /* notify that the full-duplex transfer can start */
        xSemaphoreGive( xStartTransferSem );

        /* wait untill transfer is done */
        xSemaphoreTake( xTransferDoneSem, portMAX_DELAY );
        
        /* take buffer mutex */
        xSemaphoreTake( xBuffersMutex, portMAX_DELAY );
        int cmp2 = memcmp( write_data_buffer_sram_click_1,
                           read_data_buffer_sram_click_1,
                           DATA_LENGTH );

        /* give buffer mutex */                   
        xSemaphoreGive( xBuffersMutex );

        if( cmp2 == 0 )
        {
            digital_out_toggle( &output_pin2 );    
        }
        else
        {
            signal_error( TEST_PIN_2 );
        }

        /* notify writer task that the cycle is done */
        xSemaphoreGive( xCheckDoneSem  );
    }
}

/**
 * @brief SPI transfer task function
 *
 * This task performs full-duplex transfer with SRAM click.
 */
static void vSramTransferTask( void *pvParameters )
{
    (void) pvParameters;

    for( ;; )
    {
        /* wait for signal that full-duplex transfer can begin */
        xSemaphoreTake( xStartTransferSem, portMAX_DELAY );

        sram_click_1_transfer( 0 );

        /* signal that full-duplex transfer is done */
        xSemaphoreGive( xTransferDoneSem );
    }
}

int main(void) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize necessary SPI protocol properties.
    application_init();
    
    // Initialize output pins for signaling success.
    digital_out_init( &output_pin, GPIO_PB0 );
    digital_out_init( &output_pin2, GPIO_PB1 );
    
    // create semaphores
    xBuffersMutex  = xSemaphoreCreateMutex();
    xSpiMutex      = xSemaphoreCreateMutex();
    xWriteDoneSem  = xSemaphoreCreateBinary();
    xReadDoneSem   = xSemaphoreCreateBinary();
    xCheckDoneSem  = xSemaphoreCreateBinary();
    xStartTransferSem = xSemaphoreCreateBinary();   
    xTransferDoneSem  = xSemaphoreCreateBinary();   

    /* allow writer tasks to get CPU time when scheduler starts */
    xSemaphoreGive( xCheckDoneSem );

    /* Create tasks */
    if(xTaskCreate( vSramWriterTask,
                 "WR",
                 configMINIMAL_STACK_SIZE+200,
                 NULL,
                 mainSPI_WRITER_TASK,
                 NULL
               ) != pdPASS) while(1);

     if(xTaskCreate( vSramReaderTask,
                 "RD",
                 configMINIMAL_STACK_SIZE+200,
                 NULL,
                 mainSPI_READER_TASK,
                 NULL
               ) != pdPASS) while(1);   

     if(xTaskCreate( vSramCheckTask,
                 "CHK",
                 configMINIMAL_STACK_SIZE+200,
                 NULL,
                 mainSPI_CHECKER_TASK,
                 NULL
               ) != pdPASS) while(1);       

     if(xTaskCreate( vSramTransferTask,
                 "TRF",
                 configMINIMAL_STACK_SIZE+200,
                 NULL,
                 mainSPI_TRANSFER_TASK,
                 NULL
               ) != pdPASS) while(1);       
    
    /* Start scheduler */
    vTaskStartScheduler();
    
    /* If all is well, the scheduler will now be running, and the following
     line will never be reached.  If the following line does execute, then
     there was most likely insufficient FreeRTOS heap memory available for the idle and/or
     timer tasks to be created. */
    for( ;; ){
        
    }

    return 0;
}

// ----------------------------------------------------------------------- END
