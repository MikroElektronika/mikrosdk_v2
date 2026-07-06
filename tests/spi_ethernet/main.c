#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "spi_ethernet.h"
#include "spi_ethernet_enc28j60.h"
#include "drv_spi_master.h"
#include "drv_digital_out.h"
#include "drv_uart.h"
#include "board.h"
#include <string.h>
#include <stdint.h>

#define MIKROBUS2_SCK   GPIO_PA5
#define MIKROBUS2_MISO  GPIO_PA6
#define MIKROBUS2_MOSI  GPIO_PB5
#define MIKROBUS2_CS    GPIO_PB2
#define MIKROBUS2_RST   GPIO_PE12

extern spi_ethernet_driver_t enc28j60_driver;

// Lien direct vers le pin_name_t utilisé par le fichier .c modifié
extern pin_name_t enc28j60_cs_pin;

static spi_ethernet_t eth;
static spi_master_t   spi;
static uart_t         uart;
static uart_config_t  uart_cfg;
static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];

static const uint8_t local_mac[6] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
static const uint8_t local_ip[4]  = { 172, 20, 22, 200 };

void mb1_print(const char *str)
{
    while (*str)
    {
        uart_write(&uart, (uint8_t *)str, 1);
        str++;
    }
}

void mb1_print_hex(uint8_t val) {
    const char hex[] = "0123456789ABCDEF";
    char buf[5] = "0x";
    buf[2] = hex[val >> 4]; buf[3] = hex[val & 0x0F]; buf[4] = '\0';
    mb1_print(buf);
}

int main(void)
{
#ifdef PREINIT_SUPPORTED
    preinit();
#endif

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
    mb1_print("\r\n");
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

    /* ---------- GPIO ---------- */
    digital_out_init(&eth.cs, MIKROBUS2_CS);
    digital_out_init(&eth.reset, MIKROBUS2_RST);

    /* Enregistre la broche brute pour le driver .c avant de lancer l'init */
    enc28j60_cs_pin = MIKROBUS2_CS;

    spi_master_deselect_device(enc28j60_cs_pin);

    /* ---------- Ethernet context ---------- */
    eth.spi = &spi;
    memcpy(eth.mac, local_mac, 6);
    memcpy(eth.ip, local_ip, 4);
    eth.fullDuplex = 0;

    /* ---------- INIT ENC28J60 ---------- */
    mb1_print("ENC28J60 INIT...\r\n");

    spi_ethernet_init(&eth, &enc28j60_driver);

    /* ---------- Diagnostic SPI ---------- */
    uint8_t rev = enc28j60_get_rev();
    mb1_print("EREVID = ");
    mb1_print_hex(rev);

    if (rev == 0x00 || rev == 0xFF)
        mb1_print(" NOT CORRECT\r\n");
    else
        mb1_print("\r\n");

    /* ---------- Diagnostic PHY ID ---------- */
    uint8_t low, high;

    enc28j60_phy_read(PHHID1, &low, &high);
    mb1_print("PHHID1 = ");
    mb1_print_hex(high); mb1_print_hex(low);
    mb1_print(" (attendu 0x0083)\r\n");

    if (!(high == 0x00 && low == 0x83))
        mb1_print(" NOT CORRECT \r\n");

    /* ---------- Link status ---------- */
    mb1_print("PHSTAT2 = ");
    enc28j60_phy_read(PHSTAT2, &low, &high);
    mb1_print_hex(high);
    mb1_print_hex(low);

    mb1_print("\r\nWAIT LINK\r\n");
    if (enc28j60_get_link_status())
    {
        mb1_print(">>> LINK UP\r\n");
    } else {
        mb1_print(">>> LINK DOWN\r\n");
    }
    
    // Envoyer une trame test EtherType custom 0x88B5
    uint8_t tx_buf[60];
    memset(tx_buf, 0, sizeof(tx_buf));
    // Ethernet header : dest (broadcast), src (local_mac), EtherType
    memset(&tx_buf[0], 0xFF, 6);           // dst = broadcast
    memcpy(&tx_buf[6], local_mac, 6);      // src = notre MAC
    tx_buf[12] = 0x88; tx_buf[13] = 0xB5; // EtherType custom
    // Payload
    const char msg[] = "HELLO_FROM_MCU";
    memcpy(&tx_buf[14], msg, sizeof(msg)-1);

    mb1_print("TX TEST...");
    spi_ethernet_send(&eth, tx_buf, sizeof(tx_buf));
    mb1_print(" done\r\n");

    static uint8_t rx_buf[1518];

    while (1)
    {
        uint16_t rx_len = spi_ethernet_receive(&eth, rx_buf, sizeof(rx_buf));
        if (rx_len > 13)
        {
            uint16_t etype = ((uint16_t)rx_buf[12] << 8) | rx_buf[13];
            mb1_print("RX frame: EtherType=");
            mb1_print_hex((uint8_t)(etype >> 8));
            mb1_print_hex((uint8_t)(etype & 0xFF));
            mb1_print(" len=");
            mb1_print_hex((uint8_t)(rx_len >> 8));
            mb1_print_hex((uint8_t)(rx_len & 0xFF));
            mb1_print("\r\n");
        }
        Delay_ms(10);
    }
}