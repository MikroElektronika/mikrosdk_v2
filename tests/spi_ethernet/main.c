// TODO
#if 0
/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "drv_digital_out.h"
#include "spi_ethernet.h"
#include "spi_ethernet_enc28j60.h"
#include "board.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS

// ----------------------------------------------------------------- VARIABLES

// ----------------------------------------------------------------- USER CODE

// ------------------------------------------------------------
// Main function.
// ------------------------------------------------------------
int main(void)
{
    // --- Init low-level stuff ---
    // spi_master_t spi;
    // spi_master_config_t spi_config;
    // // spi init blah blah
    // // Set default properties for SRAM Click 1.
    // spi_master_configure_default(&spi_config);

    // // Set desired basic properties for SRAM Click 1 which is on mikroBUS1.
    // spi_config.sck = MIKROBUS_1_SCK;
    // spi_config.miso = MIKROBUS_1_MISO;
    // spi_config.mosi = MIKROBUS_1_MOSI;
    // spi_config.speed = 100000;
    // spi_config.mode = SPI_MASTER_MODE_DEFAULT;
    // spi_config.default_write_data = 0;

    // // Try to reserve memory for the SRAM Click 1.
    // spi_master_open(&spi, &spi_config);

    // // spi_master_close(&spi);  //TODO This is the perfect place in code to test spi_master_close via debug!!!

    // // Set Chip Select polarity (SRAM Click requires active low).
    // spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);

    // // Set desired default write (dummy) data.
    // spi_master_set_default_write_data(&spi, 0);

    // // Set desired baud rate (speed).
    // spi_master_set_speed(&spi, 100000);

    // // Set desired mode (SRAM Click requires mode 0).
    // spi_master_set_mode(&spi, SPI_MASTER_MODE_DEFAULT);


    // --- SPI Ethernet context ---
    spi_ethernet_t eth;
    uint8_t mac[6] = { 0x00, 0x04, 0xA3, 0x12, 0x34, 0x56 };

    // eth.spi = &spi;
    memcpy(eth.mac, mac, 6);

    spi_ethernet_init(&eth, &enc28j60_driver);

    // Example outbound frame (ARP request or whatever you want)
    uint8_t tx_buf[10] = {0, 1, 2, 3, 4};
    spi_ethernet_send(&eth, tx_buf, sizeof(tx_buf));

    // Working buffer for RX
    uint8_t rx_buf[10];

    while (1)
    {
        // int available = spi_ethernet_available(&eth);
        // if (available > 0)
        // {
            int len = spi_ethernet_receive(&eth, rx_buf, sizeof(rx_buf));
            if (len > 0)
            {
                // do something with the packet
            }
        // }

        Delay_ms(10);
    }
}
#else
#include "board.h"
#include "log.h"
#include "spi_ethernet.h"
#include "spi_ethernet_enc28j60.h"

#define RX_BUF_SIZE 600

typedef struct {
    uint8_t  dst[6];
    uint8_t  src[6];
    uint16_t type;
} eth_hdr_t;

static uint16_t ntohs(uint16_t v)
{
    return (v << 8) | (v >> 8);
}

int main(void)
{
    log_t logger;
    log_cfg_t log_cfg;
    uint8_t rx_buf[RX_BUF_SIZE];

    uint8_t mac[6] = { 0x00, 0x04, 0xA3, 0x12, 0x34, 0x56 };
    static spi_ethernet_t eth;

    // eth.spi = &spi;
    memcpy(eth.mac, mac, 6);

    log_cfg.rx_pin = USB_UART_RX;
    log_cfg.tx_pin = USB_UART_TX;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    // log_info( &logger, "---- Application Init ----" );

    /* ---- platform init ---- */
    // platform_init();          // clocks, gpio, spi, uart (you implement)
    spi_ethernet_init(&eth, &enc28j60_driver);  // wraps enc28j60 init


    while (1)
    {
        /* Step 1: check if a packet exists */
        if (spi_ethernet_available(&eth) == 0)
            continue;

        /* Step 2: read ONE ethernet frame */
        int len = spi_ethernet_receive(&eth, rx_buf, sizeof(rx_buf));
        if (len < (int)sizeof(eth_hdr_t))
            continue;

        /* Step 3: parse ethernet header */
        eth_hdr_t *hdr = (eth_hdr_t *)rx_buf;
        uint16_t ethertype = ntohs(hdr->type);

        /* Step 4: observe only */
        // log_printf( &logger, "RX frame: type=0x%04X len=%d\n", ethertype, len);

        /* expected values:
           0x0806 -> ARP
           0x0800 -> IPv4
        */
    }
}
#endif