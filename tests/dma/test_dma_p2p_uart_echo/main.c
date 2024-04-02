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
// Set proper module stream and channel for UART RX event for target MCU.
#define TEST_DMA_MODULE 1
#define TEST_DMA_STREAM 1
#define TEST_DMA_CHANNEL 5
#endif

// Set proper UART TX and RX register addresses for target MCU.
#define UART_RX_REG_ADDRESS UART_RX_ADDRESS_NOT_DEFINED
#define UART_TX_REG_ADDRESS UART_TX_ADDRESS_NOT_DEFINED

// ----------------------------------------------------------------- VARIABLES

static digital_out_t pin;

static uart_t uart;
static uart_config_t uart_cfg;

static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];

static dma_config_t dma_cfg;
static dma_t dma;
static dma_channel_t channels;

// ----------------------------------------------------------------- USER CODE

void test_fail();

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    digital_out_init( &pin, TEST_PIN_NAME );

    uart_configure_default( &uart_cfg );
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;
    uart_cfg.tx_pin = USB_UART_TX;
    uart_cfg.rx_pin = USB_UART_RX;
    uart_cfg.tx_ring_size = 128;
    uart_cfg.rx_ring_size = 128;
    uart_open( &uart, &uart_cfg );
    uart_set_baud(&uart, 115200);

    // Enable UART DMA RX for test to function.
    #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
    *(uint32_t *)0x40011414 |= 0x00000040;  // USART6_CR3bits.DMAR = 1;
    #endif

    // Set default configuration values first.
    dma_configure_default( &dma_cfg );

    dma_cfg.src_inc = true;
    dma_cfg.dst_inc = true;
    dma_cfg.data_align_source = DMA_DATA_ALIGN_BYTES_1;
    dma_cfg.data_align_destination = DMA_DATA_ALIGN_BYTES_1;
    dma_cfg.direction = DMA_DIRECTION_PERIPH_TO_PERIPH;
    dma_cfg.mode = DMA_MODE_CIRCULAR;
    dma_cfg.priority = DMA_PRIORITY_HIGH;

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
                            UART_RX_REG_ADDRESS,
                            UART_TX_REG_ADDRESS,
                            1,
                            DMA_SOURCE_MEMORY_REGION_RAM
                        ) ) {
        test_fail();
    }

    if ( DMA_SUCCESS != dma_transfer_start( &dma ) ) {
        test_fail();
    }

    while( 1 ) {

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
