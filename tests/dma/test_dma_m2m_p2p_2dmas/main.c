// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "dma_test.h"
#include "drv_digital_out.h"
#include "drv_uart.h"
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
// Set proper module stream and channel for UART RX and DMA reload events for target MCU.
#define TEST_DMA_MODULE_1 1
#define TEST_DMA_MODULE_2 1
#define TEST_DMA_STREAM_1 3
#define TEST_DMA_STREAM_2 1
#define TEST_DMA_CHANNEL_1 3
#define TEST_DMA_CHANNEL_2 5
#endif

// Set proper UART TX and RX register addresses for target MCU.
#define UART_TX_REG_ADDRESS UART_TX_ADDRESS_NOT_DEFINED
#define UART_RX_REG_ADDRESS UART_RX_ADDRESS_NOT_DEFINED

// ----------------------------------------------------------------- VARIABLES

static uart_t uart;
static uart_config_t uart_cfg;

static uint8_t uart_rx_buffer[ 128 ];
static uint8_t uart_tx_buffer[ 128 ];

static dma_config_t dma1_cfg, dma2_cfg;
static dma_t dma1, dma2;
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

#ifdef PIC32xx
static uint32_t __attribute__((coherent)) buffer_dst_ram[ BUFFER_SIZE ];
#else
static uint32_t buffer_dst_ram[ BUFFER_SIZE ];
#endif

// ----------------------------------------------------------------- USER CODE

void test_fail();

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Configure UART.
    uart_configure_default( &uart_cfg );
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;
    uart_cfg.tx_pin = USB_UART_TX;
    uart_cfg.rx_pin = USB_UART_RX;
    uart_cfg.tx_ring_size = 128;
    uart_cfg.rx_ring_size = 128;
    uart_open(&uart, &uart_cfg);
    uart_set_baud( &uart, 115200 );

    // Enable UART DMA RX for test to function.
    #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
    *(uint32_t *)0x40011414 |= 0x00000040;  // USART6_CR3bits.DMAR = 1;
    #endif

    digital_out_init( &pin, TEST_PIN_NAME );
    digital_out_low( &pin );
    Delay_1sec();
    Delay_1sec();

    // Set default configuration values for DMA1.
    dma_configure_default(&dma1_cfg);
    // Then set memory addresses to be incremented for both source and destination.
    dma1_cfg.src_inc = true;
    dma1_cfg.dst_inc = true;
    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels(&channels);
    if ( !channels[ TEST_DMA_MODULE_1 ][ TEST_DMA_STREAM_1 ][ TEST_DMA_CHANNEL_1 ] ) {
        dma1_cfg.module = TEST_DMA_MODULE_1;
        dma1_cfg.stream = TEST_DMA_STREAM_1;
        dma1_cfg.channel = TEST_DMA_CHANNEL_1;
    } else {
        test_fail();
    }
    #endif

    // Set default configuration values for DMA2.
    dma_configure_default( &dma2_cfg );
    // Then set memory addresses to be incremented for both source and destination.
    dma2_cfg.src_inc = true;
    dma2_cfg.dst_inc = true;
    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels( &channels );
    if ( !channels[ TEST_DMA_MODULE_2 ][ TEST_DMA_STREAM_2 ][ TEST_DMA_CHANNEL_2 ] ) {
        dma2_cfg.module = TEST_DMA_MODULE_2;
        dma2_cfg.stream = TEST_DMA_STREAM_2;
        dma2_cfg.channel = TEST_DMA_CHANNEL_2;
    } else {
        test_fail();
    }
    #endif

    // Open DMA1.
    if ( DMA_SUCCESS != dma_open( &dma1, &dma1_cfg ) ) {
        test_fail();
    }
    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels( &channels );
    if ( !channels[ TEST_DMA_MODULE_1 ][ TEST_DMA_STREAM_1 ][ TEST_DMA_CHANNEL_1 ] ) {
        test_fail();
    }
    #endif

    // Open DMA2.
    if ( DMA_SUCCESS != dma_open( &dma2, &dma2_cfg ) ) {
        test_fail();
    }
    #ifndef TEST_AUTOMATIC_ALLOCATION
    dma_get_channels( &channels );
    if ( !channels[ TEST_DMA_MODULE_2 ][ TEST_DMA_STREAM_2 ][ TEST_DMA_CHANNEL_2 ] ) {
       test_fail();
    }
    #endif

    // Test randomized access to two different dma modules.
    // Set DMA2 priority to high.
    if ( DMA_SUCCESS != dma_set_priority( &dma2, DMA_PRIORITY_VERY_HIGH ) ) {
        test_fail();
    }
    // Set transfer config for DMA1.
    if ( DMA_SUCCESS != dma_set_transfer_config(
                            &dma1,
                            (uint32_t)&buffer_src_flash,
                            (uint32_t)&buffer_dst_ram,
                            sizeof(buffer_src_flash),
                            DMA_SOURCE_MEMORY_REGION_PFM
                        ) ) {
        test_fail();
    }


    // Set direction to be P2P for DMA2.
    if ( DMA_SUCCESS != dma_set_direction( &dma2, DMA_DIRECTION_PERIPH_TO_PERIPH ) ) {
        test_fail();
    }
    // Set DMA1 priority to low.
    if ( DMA_SUCCESS != dma_set_priority( &dma1, DMA_PRIORITY_LOW ) ) {
        test_fail();
    }
    // Set circular mode for DMA2.
    if ( DMA_SUCCESS != dma_set_mode( &dma2, DMA_MODE_CIRCULAR ) ) {
        test_fail();
    }
    // Set transfer config for DMA2.
    if ( DMA_SUCCESS != dma_set_transfer_config(
                            &dma2,
                            UART_RX_REG_ADDRESS,
                            UART_TX_REG_ADDRESS,
                            1,
                            DMA_SOURCE_MEMORY_REGION_RAM
                        ) ) {
        test_fail();
    }
    // Set circular mode for DMA1.
    if ( DMA_SUCCESS != dma_set_mode( &dma1, DMA_MODE_CIRCULAR ) ) {
    test_fail();
    }

    digital_out_high( &pin );

    // Start transmissions.
    if ( DMA_SUCCESS != dma_transfer_start( &dma1 ) ) {
        test_fail();
    }
    if ( DMA_SUCCESS != dma_transfer_start( &dma2 ) ) {
        test_fail();
    }

    check_result = memcmp(buffer_src_flash, buffer_dst_ram, sizeof(buffer_src_flash));

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
