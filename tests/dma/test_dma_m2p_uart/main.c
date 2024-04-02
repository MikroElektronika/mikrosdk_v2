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
// Set proper module stream and channel for UART TX event for target MCU.
#define TEST_DMA_MODULE 1
#define TEST_DMA_STREAM 7
#define TEST_DMA_CHANNEL 5
#endif

// Set proper UART TX register addresses for target MCU.
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

static const char buffer_src_flash[]= "MikroE DMA!\r\n!!!!";

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
    uart_set_baud( &uart, 115200 );

    // Enable UART DMA TX for test to function.
    /* Note: Depending on the architecture other MCUs might also require,
     *       enabling option to send request to DMA from the peripheral side.
     */
    #if defined(TM4C129)
    *(uint32_t *)0x40012048UL |= 0x2UL; // UART6DMACTL |= UARTDMACTL_RXDMAE;
    #endif
    #if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
    *(uint32_t *)0x40011414 |= 0x00000080;  // USART6_CR3bits.DMAT = 1;
    #endif

    // Set default configuration values first.
    dma_configure_default( &dma_cfg );
    dma_cfg.src_inc = true;
    dma_cfg.dst_inc = true;
    dma_cfg.dst_inc = false;
    dma_cfg.data_align_source = DMA_DATA_ALIGN_BYTES_1;
    dma_cfg.data_align_destination = DMA_DATA_ALIGN_BYTES_1;
    dma_cfg.burst_size_source = DMA_BURST_SIZE_INCREMENT_1;
    dma_cfg.burst_size_destination = DMA_BURST_SIZE_INCREMENT_1;
    dma_cfg.direction = DMA_DIRECTION_MEMORY_TO_PERIPH;
    dma_cfg.mode = DMA_MODE_NORMAL;
    dma_cfg.priority = DMA_PRIORITY_HIGH;

    #ifndef TEST_AUTOMATIC_ALLOCATION
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
                            (uint32_t)&buffer_src_flash,
                            UART_TX_REG_ADDRESS,
                            13,
                            DMA_SOURCE_MEMORY_REGION_PFM
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
    while(1) {
        digital_out_toggle( &pin );
        Delay_1sec();
    }
}

// ----------------------------------------------------------------------- END
