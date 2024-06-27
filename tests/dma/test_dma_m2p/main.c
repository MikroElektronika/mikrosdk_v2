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
#include "drv_dma.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

#ifndef PB0
#define TEST_PIN_NAME HAL_PIN_NC
#else
#define TEST_PIN_NAME PB0
#endif

#define BUFFER_SIZE 0x100 // 256 elements.

// TODO - define SPI data register address.
// TODO - define SPI test pins.
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
#define PERIPH_ADDRESS 0x4001300CUL  // SPI1_DR
#define TEST_PIN_SPI_SCK PA5
#define TEST_PIN_SPI_MISO PA6
#define TEST_PIN_SPI_MOSI PB5
#else
#define PERIPH_ADDRESS 0
#define TEST_PIN_SPI_SCK HAL_PIN_NC
#define TEST_PIN_SPI_MISO HAL_PIN_NC
#define TEST_PIN_SPI_MOSI HAL_PIN_NC
#endif

// Note that for SPI1_TX for STM32F4x
// only following will work:
// MODULE - 1 - DMA2
// STREAM - 3 or 5
// CHANNEL - 3
// According to table from ref manual page 308
// TODO - Set correct values for test to work.
#define TEST_DMA_MODULE 1
#define TEST_DMA_STREAM 3
#define TEST_DMA_CHANNEL 3

// ----------------------------------------------------------------- VARIABLES

static dma_t dma;
static dma_config_t dma_cfg;
static dma_channel_t channels;

static digital_out_t pin;

static spi_master_t spi;
static spi_master_config_t spi_cfg;

#ifdef PIC32xx
static uint8_t __attribute__((coherent)) buffer_src_flash[ BUFFER_SIZE ];
#else
static uint8_t buffer_src_flash[ BUFFER_SIZE ];
#endif

// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Fill buffer with designated number of elements.
    for ( int i = 0; i <= BUFFER_SIZE; i++ )
        buffer_src_flash[i] = i;

    // Set default properties for SPI.
    spi_master_configure_default(&spi_cfg);

    // Set pins for SPI module.
    spi_cfg.sck = TEST_PIN_SPI_SCK;
    spi_cfg.miso = TEST_PIN_SPI_MISO;
    spi_cfg.mosi = TEST_PIN_SPI_MOSI;

    // Configure SPI module.
    if (ACQUIRE_FAIL != spi_master_open(&spi, &spi_cfg)) {
        spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);
        spi_master_set_default_write_data(&spi, 0);
        spi_master_set_speed(&spi, 1000000);
        spi_master_set_mode(&spi, SPI_MASTER_MODE_DEFAULT);
        spi_master_select_device(PB0);
    }

    // TODO - Enable SPI DMA TX for test to function.
    #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
    // For STM32F4 SPI module 1, set bit 1 in register SPI_CR2 register.
    *(uint32_t *)0x40013004 |= 0x2;
    #endif

    // Initialize signal pin for DMA transfer.
    digital_out_init( &pin, TEST_PIN_NAME );

    // Set default configuration values first.
    dma_configure_default(&dma_cfg);

    // Now configure dma structure with new values.
    dma_cfg.data_align_source = DMA_DATA_ALIGN_BYTES_1;
    dma_cfg.data_align_destination = DMA_DATA_ALIGN_BYTES_1;
    dma_cfg.direction = DMA_DIRECTION_MEMORY_TO_PERIPH;
    dma_cfg.priority = DMA_PRIORITY_VERY_HIGH;
    dma_cfg.mode = DMA_MODE_NORMAL;

    // Then set memory addresses to be incremented
    // for memory only.
    dma_cfg.src_inc = true;

    // Check if desired Module-Stream-Channel is free.
    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels(&channels);
    if ( !channels[TEST_DMA_MODULE][TEST_DMA_STREAM][TEST_DMA_CHANNEL] ) {
        dma_cfg.module = TEST_DMA_MODULE;
        dma_cfg.stream = TEST_DMA_STREAM;
        dma_cfg.channel = TEST_DMA_CHANNEL;
    } else {
        while(1);
    }
    #endif

    // Open the object handler.
    dma_open(&dma, &dma_cfg);

    // Check if it has been allocated correctly.
    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels(&channels);
    if ( !channels[TEST_DMA_MODULE][TEST_DMA_STREAM][TEST_DMA_CHANNEL] ) {
        while(1);
    }
    #endif

    // Configure the new stream.
    dma_set_transfer_config(&dma,
                            (uint32_t)&buffer_src_flash,
                            (uint32_t)PERIPH_ADDRESS,
                            BUFFER_SIZE,
                            DMA_SOURCE_MEMORY_REGION_RAM
                           );

    // Start the stream.
    dma_transfer_start(&dma);

    // Infinite loop with data signaling.
    // Sanity check only - if no hard fault happened.
    while(1) {
        #ifndef __GNUC__
        digital_out_toggle( &pin );
        Delay_ms(1000);
        #endif
    }

    return 0;
}

// ----------------------------------------------------------------------- END
