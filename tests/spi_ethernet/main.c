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
#elseif 0
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
#else
#include "spi_ethernet.h"
#include "spi_ethernet_enc28j60.h"
#include <string.h>
#include <stdint.h>

#define MY_IP_0 192
#define MY_IP_1 168
#define MY_IP_2 1
#define MY_IP_3 50

/* Driver object (provided by your ENC28J60 driver) */
extern spi_ethernet_driver_t spi_ethernet_enc28j60_driver;

/* Ethernet instance */
static spi_ethernet_t eth;

/* MAC addresses */
static uint8_t my_mac[6] =
{
    0x02, 0x00, 0x00, 0x00, 0x00, 0x01
};

static uint8_t broadcast_mac[6] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static uint16_t ip_checksum(void *vdata, uint16_t length)
{
    uint8_t *data = (uint8_t*)vdata;
    uint32_t acc = 0;

    for (uint16_t i = 0; i < length; i += 2)
    {
        uint16_t word = data[i] << 8;
        if (i + 1 < length)
            word |= data[i + 1];

        acc += word;
    }

    while (acc >> 16)
        acc = (acc & 0xFFFF) + (acc >> 16);

    return ~acc;
}

int main(void)
{
    /* Initialize SPI ethernet with ENC28J60 driver */
    // spi_ethernet_init(&eth, &spi_ethernet_enc28j60_driver);
    spi_ethernet_init(&eth, &enc28j60_driver);

    /* ---------- SEND TEST FRAME ---------- */

    ethernet_frame_t tx;

    memcpy(tx.dest, broadcast_mac, 6);
    memcpy(tx.src,  my_mac, 6);

    tx.type = 0x88B5;  // custom EtherType for testing

    const char msg[] = "HELLO_FROM_MCU";
    tx.payload_len = sizeof(msg) - 1;
    memcpy(tx.payload, msg, tx.payload_len);

    ethernet_send_frame(&eth, &tx);

    /* ---------- RECEIVE LOOP ---------- */

    while (1)
    {
        ethernet_frame_t rx;
        int len = ethernet_receive_frame(&eth, &rx);

        if (len <= 0)
            continue;

        /* ---------- ARP ---------- */
        if (rx.type == 0x0806)
        {
            uint8_t *arp = rx.payload;

            /* Check if ARP request */
            if (arp[6] == 0x00 && arp[7] == 0x01)   // opcode = request
            {
                if (arp[24] == MY_IP_0 &&
                    arp[25] == MY_IP_1 &&
                    arp[26] == MY_IP_2 &&
                    arp[27] == MY_IP_3)
                {
                    ethernet_frame_t tx;

                    memcpy(tx.dest, rx.src, 6);
                    memcpy(tx.src, my_mac, 6);
                    tx.type = 0x0806;

                    uint8_t *reply = tx.payload;

                    memcpy(reply, arp, 28);

                    reply[6] = 0x00;   // opcode = reply
                    reply[7] = 0x02;

                    memcpy(&reply[8],  my_mac, 6);      // sender MAC
                    reply[14] = MY_IP_0;
                    reply[15] = MY_IP_1;
                    reply[16] = MY_IP_2;
                    reply[17] = MY_IP_3;

                    memcpy(&reply[18], &arp[8], 6);     // target MAC
                    memcpy(&reply[24], &arp[14], 4);    // target IP

                    tx.payload_len = 28;

                    ethernet_send_frame(&eth, &tx);
                }
            }
        }

        /* ---------- IPv4 ---------- */
        if (rx.type == 0x0800)
        {
            uint8_t *ip = rx.payload;

            /* Check protocol = ICMP */
            if (ip[9] == 1)
            {
                /* Check destination IP */
                if (ip[16] == MY_IP_0 &&
                    ip[17] == MY_IP_1 &&
                    ip[18] == MY_IP_2 &&
                    ip[19] == MY_IP_3)
                {
                    uint8_t ip_header_len = (ip[0] & 0x0F) * 4;
                    uint8_t *icmp = &ip[ip_header_len];


                    /* Echo request */
                    if (icmp[0] == 8)
                    {
                        ethernet_frame_t tx;

                        memcpy(tx.dest, rx.src, 6);
                        memcpy(tx.src, my_mac, 6);
                        tx.type = 0x0800;

                        uint8_t *ip_out = tx.payload;

                        memcpy(ip_out, ip, len - 14);

                        /* Swap IPs */
                        ip_out[12] = MY_IP_0;
                        ip_out[13] = MY_IP_1;
                        ip_out[14] = MY_IP_2;
                        ip_out[15] = MY_IP_3;

                        ip_out[16] = ip[12];
                        ip_out[17] = ip[13];
                        ip_out[18] = ip[14];
                        ip_out[19] = ip[15];

                        /* ICMP reply */
                        uint8_t *icmp_out = &ip_out[20];
                        icmp_out[0] = 0;   // Echo reply
                        icmp_out[2] = 0;
                        icmp_out[3] = 0;

                        uint16_t icmp_len = (len - 14) - ip_header_len;
                        uint16_t csum = ip_checksum(icmp_out, icmp_len);
                        icmp_out[2] = csum >> 8;
                        icmp_out[3] = csum & 0xFF;

                        /* Recalculate IP checksum */
                        ip_out[10] = 0;
                        ip_out[11] = 0;
                        uint16_t ip_csum = ip_checksum(ip_out, 20);
                        ip_out[10] = ip_csum >> 8;
                        ip_out[11] = ip_csum & 0xFF;

                        tx.payload_len = len - 14;

                        ethernet_send_frame(&eth, &tx);
                    }
                }
            }
        }
    }

    return 0;
}


#endif
