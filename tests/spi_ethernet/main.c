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

void mb1_print(const char *str) {
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

static uint16_t ip_checksum(const uint8_t *data, uint16_t len) {
    uint32_t sum = 0;
    for (uint16_t i = 0; i + 1 < len; i += 2)
        sum += ((uint32_t)data[i] << 8) | data[i+1];
    if (len & 1) sum += (uint32_t)data[len-1] << 8;
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (uint16_t)(~sum);
}

int main(void) {
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
        if (rx_len < 14) { Delay_ms(1); continue; }

        uint16_t etype = ((uint16_t)rx_buf[12] << 8) | rx_buf[13];

        if (etype == 0x0806) // ARP
        {
            uint8_t *arp = &rx_buf[14];

            // ARP request (opcode 0x0001) pour notre IP ?
            if (arp[6] == 0x00 && arp[7] == 0x01 &&
                memcmp(&arp[24], local_ip, 4) == 0)
            {
                uint8_t reply[42];

                // Ethernet header
                memcpy(&reply[0], &rx_buf[6], 6);   // dst = MAC expéditeur
                memcpy(&reply[6], local_mac, 6);     // src = notre MAC
                reply[12] = 0x08; reply[13] = 0x06; // ARP

                // ARP payload
                reply[14] = 0x00; reply[15] = 0x01; // HW type Ethernet
                reply[16] = 0x08; reply[17] = 0x00; // IPv4
                reply[18] = 6;    reply[19] = 4;     // tailles adresses
                reply[20] = 0x00; reply[21] = 0x02; // opcode = reply

                memcpy(&reply[22], local_mac, 6);   // sender MAC = nous
                memcpy(&reply[28], local_ip, 4);    // sender IP  = nous
                memcpy(&reply[32], &arp[8], 6);     // target MAC = expéditeur
                memcpy(&reply[36], &arp[14], 4);    // target IP  = expéditeur

                spi_ethernet_send(&eth, reply, 42);
                mb1_print("ARP reply sent \r\n");
            } 
        } else if (etype == 0x0800) // IPv4
        {
            uint8_t *ip = &rx_buf[14];

            // ICMP (protocole 1) pour notre IP ?
            if (ip[9] == 1 && memcmp(&ip[16], local_ip, 4) == 0)
            {
                uint8_t ihl = (ip[0] & 0x0F) * 4;
                uint8_t *icmp = &ip[ihl];

                // Echo request (type 8) ?
                if (icmp[0] == 8)
                {
                    static uint8_t reply[600];
                    uint16_t ip_total = ((uint16_t)ip[2] << 8) | ip[3];
                    uint16_t icmp_len = ip_total - ihl;
                    uint16_t total = 14 + 20 + icmp_len;

                    // Ethernet header
                    memcpy(&reply[0], &rx_buf[6], 6);
                    memcpy(&reply[6], local_mac, 6);
                    reply[12] = 0x08; reply[13] = 0x00;

                    // IP header
                    memcpy(&reply[14], ip, 20);
                    reply[14+8] = 64;  // TTL
                    reply[14+9] = 1;   // ICMP
                    memcpy(&reply[14+12], local_ip, 4); // src = nous
                    memcpy(&reply[14+16], &ip[12], 4);  // dst = expéditeur
                    reply[14+10] = 0; reply[14+11] = 0;
                    uint16_t ip_ck = ip_checksum(&reply[14], 20);
                    reply[14+10] = ip_ck >> 8;
                    reply[14+11] = ip_ck & 0xFF;

                    // ICMP echo reply
                    memcpy(&reply[14+ihl], icmp, icmp_len);
                    reply[14+ihl+0] = 0; // type = Echo Reply
                    reply[14+ihl+1] = 0; // code = 0
                    reply[14+ihl+2] = 0; reply[14+ihl+3] = 0;
                    uint16_t icmp_ck = ip_checksum(&reply[14+ihl], icmp_len);
                    reply[14+ihl+2] = icmp_ck >> 8;
                    reply[14+ihl+3] = icmp_ck & 0xFF;

                    spi_ethernet_send(&eth, reply, total);
                    mb1_print("ICMP Echo Reply sent\r\n");
                }
            }
        }
        Delay_ms(1);
    }
}