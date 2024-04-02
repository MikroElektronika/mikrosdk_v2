// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "drv_dma.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

// #define TEST_AUTOMATIC_ALLOCATION

#ifndef PB0
#define TEST_PIN_NAME HAL_PIN_NC
#else
#define TEST_PIN_NAME PB0
#endif

#define BUFFER_SIZE 32

#ifndef TEST_AUTOMATIC_ALLOCATION
#define TEST_DMA_MODULE 1
#define TEST_DMA_STREAM 1
#define TEST_DMA_CHANNEL 3
#endif

// ----------------------------------------------------------------- VARIABLES

static dma_config_t dma_cfg;
static dma_t dma;
static dma_channel_t channels;

static digital_out_t pin;

int check_result = 0xFF;
static const uint32_t buffer_src_flash[ BUFFER_SIZE ]= {
    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
};

static uint32_t buffer_dst_ram[ BUFFER_SIZE ];

// ----------------------------------------------------------------- USER CODE

void test_fail();

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    digital_out_init( &pin, TEST_PIN_NAME );
    digital_out_low( &pin );
    Delay_1sec();
    Delay_1sec();

    // Set default configuration values first.
    dma_configure_default( &dma_cfg );

    // Now set data alignment to WORD(32-bit) because
    // arrays are word size.
    dma_cfg.data_align_source = DMA_DATA_ALIGN_BYTES_4;
    dma_cfg.data_align_destination = DMA_DATA_ALIGN_BYTES_4;

    // Then set memory addresses to be incremented
    // for both memory and peripheral.
    dma_cfg.src_inc = true;
    dma_cfg.dst_inc = true;

    #ifndef TEST_AUTOMATIC_ALLOCATION
    // NOTE - on stm32f2/f4 and f7 MCUs only DMA2 can
    // work in M2M mode.
    dma_get_channels( &channels );
    if ( !channels[ TEST_DMA_MODULE ][ TEST_DMA_STREAM ][ TEST_DMA_CHANNEL ] ) {
        dma_cfg.module = TEST_DMA_MODULE;
        dma_cfg.stream = TEST_DMA_STREAM;
        dma_cfg.channel = TEST_DMA_CHANNEL;
    } else {
        test_fail();
    }
    #endif

    // Test closing and opening effect on registers.
    if ( DMA_SUCCESS != dma_open( &dma, &dma_cfg ) ) {
        test_fail();
    }

    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels( &channels );
    if ( !channels[ TEST_DMA_MODULE ][ TEST_DMA_STREAM ][ TEST_DMA_CHANNEL ] ) {
        test_fail();
    }
    #endif

    if ( DMA_SUCCESS != dma_set_transfer_config(
                            &dma,
                            (uint32_t)&buffer_src_flash,
                            (uint32_t)&buffer_dst_ram,
                            sizeof( buffer_src_flash ),
                            DMA_SOURCE_MEMORY_REGION_PFM
                        ) ) {
        test_fail();
    }

    digital_out_high( &pin );

    // Start transmission.
    if ( DMA_SUCCESS != dma_transfer_start( &dma ) ) {
        test_fail();
    }

    check_result = memcmp( buffer_src_flash, buffer_dst_ram, sizeof( buffer_src_flash ) );

    while( 1 ) {
        if ( !check_result ) {
            digital_out_toggle( &pin );
            Delay_100ms();
        }
    }

    return 0;
}

void test_fail() {
    while( 1 ) {
        digital_out_toggle( &pin );
        Delay_1sec();
    }
}

// ----------------------------------------------------------------------- END
