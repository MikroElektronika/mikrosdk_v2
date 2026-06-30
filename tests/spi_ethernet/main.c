#include "spi_ethernet.h"
#include "spi_ethernet_enc28j60.h"
#include "drv_spi_master.h"
#include "drv_digital_out.h"
#include "drv_uart.h"
#include "board.h"
#include <string.h>
#include <stdint.h>

#define MY_IP_0 172
#define MY_IP_1 20
#define MY_IP_2 22
#define MY_IP_3 200

#define MIKROBUS2_SCK   GPIO_PA5
#define MIKROBUS2_MISO  GPIO_PA6
#define MIKROBUS2_MOSI  GPIO_PB5
#define MIKROBUS2_CS    GPIO_PB2
#define MIKROBUS2_RST   GPIO_PE12

extern spi_ethernet_driver_t enc28j60_driver;

static spi_ethernet_t eth;
static spi_master_t   spi;
static uart_t         uart;
static uart_config_t  uart_cfg;
static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];

static uint8_t my_mac[6] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };

void mb1_print(const char *str) {
    while (*str) { uart_write(&uart, (uint8_t *)str, 1); str++; }
}

void mb1_print_hex(uint8_t val) {
    const char hex[] = "0123456789ABCDEF";
    char buf[5] = "0x";
    buf[2] = hex[val >> 4]; buf[3] = hex[val & 0x0F]; buf[4] = '\0';
    mb1_print(buf);
}

int main(void)
{
    /* ---------- UART ---------- */
    uart_configure_default(&uart_cfg);
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;
    uart_cfg.tx_pin = USB_UART_TX;
    uart_cfg.rx_pin = USB_UART_RX;
    uart_cfg.tx_ring_size = sizeof(uart_tx_buffer);
    uart_cfg.rx_ring_size = sizeof(uart_rx_buffer);
    uart_open(&uart, &uart_cfg);
    uart_set_baud(&uart, 115200);
    uart_set_parity(&uart, UART_PARITY_DEFAULT);
    uart_set_stop_bits(&uart, UART_STOP_BITS_DEFAULT);
    uart_set_data_bits(&uart, UART_DATA_BITS_DEFAULT);
    Delay_ms(100);
    mb1_print("=== ENC28J60 INIT TEST ===\r\n");

    /* ---------- SPI ---------- */
    mb1_print("SPI INIT...");
    spi_master_config_t spi_cfg;
    spi_master_configure_default(&spi_cfg);
    spi_cfg.sck   = MIKROBUS2_SCK;
    spi_cfg.miso  = MIKROBUS2_MISO;
    spi_cfg.mosi  = MIKROBUS2_MOSI;
    spi_cfg.speed = 1000000;
    spi_cfg.mode  = SPI_MASTER_MODE_0;
    spi_master_open(&spi, &spi_cfg);
    spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);
    mb1_print(" OK\r\n");

    /* ---------- CS / RST ---------- */
    digital_out_init(&eth.cs, MIKROBUS2_CS);
    digital_out_init(&eth.reset, MIKROBUS2_RST);
    digital_out_high(&eth.cs);

    /* ---------- Contexte eth ---------- */
    eth.spi = &spi;
    memcpy(eth.mac, my_mac, 6);
    uint8_t ip[4] = { MY_IP_0, MY_IP_1, MY_IP_2, MY_IP_3 };
    memcpy(eth.ip, ip, 4);
    eth.fullDuplex = 0;

    mb1_print("ENC28J60 INIT (reset + bank config)...\r\n");
    spi_ethernet_init(&eth, &enc28j60_driver);

    uint8_t rev = enc28j60_get_rev();
    mb1_print("EREVID = ");
    mb1_print_hex(rev);
    mb1_print("\r\n");

    while (1) { Delay_ms(1000); }
    return 0;
}