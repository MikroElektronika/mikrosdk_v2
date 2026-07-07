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
#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_ACK 0x10

extern spi_ethernet_driver_t enc28j60_driver;
extern pin_name_t enc28j60_cs_pin;

static spi_ethernet_t eth;
static spi_master_t   spi;
static uart_t         uart;
static uart_config_t  uart_cfg;
static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];

static const uint8_t local_mac[6] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
static const uint8_t local_ip[4]  = { 172, 20, 22, 200 };

// UART helpers
void mb1_print(const char *str) {
    while (*str) { uart_write(&uart, (uint8_t *)str, 1); str++; }
}

void mb1_print_hex(uint8_t val) {
    const char hex[] = "0123456789ABCDEF";
    char buf[5] = "0x";
    buf[2] = hex[val >> 4]; buf[3] = hex[val & 0x0F]; buf[4] = '\0';
    mb1_print(buf);
}

void mb1_print_hex16(uint16_t val) {
    const char hex[] = "0123456789ABCDEF";
    char buf[7];

    buf[0] = '0';
    buf[1] = 'x';
    buf[2] = hex[(val >> 12) & 0x0F];
    buf[3] = hex[(val >> 8)  & 0x0F];
    buf[4] = hex[(val >> 4)  & 0x0F];
    buf[5] = hex[val & 0x0F];
    buf[6] = '\0';

    mb1_print(buf);
}

// Checksums
static uint16_t ip_checksum(const uint8_t *data, uint16_t len) {
    uint32_t sum = 0;
    for (uint16_t i = 0; i + 1 < len; i += 2)
        sum += ((uint32_t)data[i] << 8) | data[i+1];
    if (len & 1) sum += (uint32_t)data[len-1] << 8;
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (uint16_t)(~sum);
}

static uint16_t tcp_checksum(const uint8_t *src_ip, const uint8_t *dst_ip,
                             const uint8_t *tcp_seg, uint16_t tcp_len) {
    uint8_t pseudo[12];
    memcpy(&pseudo[0], src_ip, 4);
    memcpy(&pseudo[4], dst_ip, 4);
    pseudo[8]  = 0;
    pseudo[9]  = 6; // TCP
    pseudo[10] = tcp_len >> 8;
    pseudo[11] = tcp_len & 0xFF;

    uint32_t sum = 0;
    for (int i = 0; i + 1 < 12; i += 2)
        sum += ((uint32_t)pseudo[i] << 8) | pseudo[i+1];
    for (uint16_t i = 0; i + 1 < tcp_len; i += 2)
        sum += ((uint32_t)tcp_seg[i] << 8) | tcp_seg[i+1];
    if (tcp_len & 1) sum += (uint32_t)tcp_seg[tcp_len-1] << 8;
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (uint16_t)(~sum);
}

// Sending a TCP segment
static void send_tcp(spi_ethernet_t *eth,
                     const uint8_t *dst_mac, const uint8_t *dst_ip,
                     uint16_t src_port, uint16_t dst_port,
                     uint32_t seq, uint32_t ack_num, uint8_t flags,
                     const uint8_t *payload, uint16_t payload_len) {

    uint16_t tcp_len   = 20 + payload_len;
    uint16_t ip_len    = 20 + tcp_len;
    uint16_t total_len = 14 + ip_len;

    static uint8_t pkt[700];
    memset(pkt, 0, total_len);

    memcpy(&pkt[0], dst_mac,   6);
    memcpy(&pkt[6], local_mac, 6);
    pkt[12] = 0x08; pkt[13] = 0x00;

    pkt[14] = 0x45; pkt[15] = 0x00;
    pkt[16] = ip_len >> 8; pkt[17] = ip_len & 0xFF;
    pkt[18] = 0x00; pkt[19] = 0x01;
    pkt[20] = 0x40; pkt[21] = 0x00;
    pkt[22] = 64;
    pkt[23] = 6;
    pkt[24] = 0; pkt[25] = 0;
    memcpy(&pkt[26], local_ip, 4);
    memcpy(&pkt[30], dst_ip,   4);
    uint16_t ip_ck = ip_checksum(&pkt[14], 20);
    pkt[24] = ip_ck >> 8; pkt[25] = ip_ck & 0xFF;

    pkt[34] = src_port >> 8;  pkt[35] = src_port & 0xFF;
    pkt[36] = dst_port >> 8;  pkt[37] = dst_port & 0xFF;
    pkt[38] = seq >> 24; pkt[39] = seq >> 16;
    pkt[40] = seq >> 8;  pkt[41] = seq & 0xFF;
    pkt[42] = ack_num >> 24; pkt[43] = ack_num >> 16;
    pkt[44] = ack_num >> 8;  pkt[45] = ack_num & 0xFF;
    pkt[46] = 0x50;
    pkt[47] = flags;
    pkt[48] = 0x20; pkt[49] = 0x00;

    if (payload && payload_len)
        memcpy(&pkt[54], payload, payload_len);

    uint16_t tcp_ck = tcp_checksum(&pkt[26], &pkt[30], &pkt[34], tcp_len);
    pkt[50] = tcp_ck >> 8;
    pkt[51] = tcp_ck & 0xFF;

    spi_ethernet_send(eth, pkt, total_len);
}

static const char http_response[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<!DOCTYPE html><html><body>"
    "<h1>Hello from ENC28J60!</h1>"
    "<p>STM32F429ZIT6 - UNI-DS v8</p>"
    "<p>IP: 172.20.22.200</p>"
    "</body></html>\r\n";

// Handler ARP
static void handle_arp(spi_ethernet_t *eth, uint8_t *pkt, uint16_t len) {
    if (len < 14 + 28) return;
    uint8_t *arp = &pkt[14];

    // ARP request (opcode 0x0001) for our IP ?
    if (arp[6] != 0x00 || arp[7] != 0x01) return;
    if (memcmp(&arp[24], local_ip, 4) != 0) return;

    uint8_t reply[42];

    memcpy(&reply[0], &pkt[6], 6);       // dst = sender MAC
    memcpy(&reply[6], local_mac, 6);     // src = your MAC
    reply[12] = 0x08; reply[13] = 0x06; // ARP

    reply[14] = 0x00; reply[15] = 0x01; // HW type Ethernet
    reply[16] = 0x08; reply[17] = 0x00; // IPv4
    reply[18] = 6;    reply[19] = 4;     // sizes and addresses
    reply[20] = 0x00; reply[21] = 0x02; // opcode = reply

    memcpy(&reply[22], local_mac, 6);   // sender MAC = you
    memcpy(&reply[28], local_ip, 4);    // sender IP  = you
    memcpy(&reply[32], &arp[8], 6);     // target MAC = sender
    memcpy(&reply[36], &arp[14], 4);    // target IP  = sender

    spi_ethernet_send(eth, reply, 42);
    mb1_print("ARP reply sent\r\n");
}

// Handler ICMP (ping)
static void handle_icmp(spi_ethernet_t *eth, uint8_t *pkt, uint16_t len) {
    uint8_t *ip = &pkt[14];
    uint8_t ihl = (ip[0] & 0x0F) * 4;
    uint8_t *icmp = &ip[ihl];

    // Echo request (type 8) ?
    if (icmp[0] != 8) return;

    static uint8_t reply[600];
    uint16_t ip_total = ((uint16_t)ip[2] << 8) | ip[3];
    uint16_t icmp_len = ip_total - ihl;
    uint16_t total = 14 + 20 + icmp_len;

    // Ethernet header
    memcpy(&reply[0], &pkt[6], 6);
    memcpy(&reply[6], local_mac, 6);
    reply[12] = 0x08; reply[13] = 0x00;

    // IP header
    memcpy(&reply[14], ip, 20);
    reply[14+8] = 64;  // TTL
    reply[14+9] = 1;   // ICMP
    memcpy(&reply[14+12], local_ip, 4); // src = you
    memcpy(&reply[14+16], &ip[12], 4);  // dst = sender
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

    spi_ethernet_send(eth, reply, total);
    mb1_print("ICMP Echo Reply sent\r\n");
}

// Handler TCP/HTTP
static void handle_tcp(spi_ethernet_t *eth, uint8_t *pkt, uint16_t len) {
    uint8_t *ip = &pkt[14];
    uint8_t ihl = (ip[0] & 0x0F) * 4;
    uint8_t *tcp = &ip[ihl];

    uint16_t dst_port = ((uint16_t)tcp[2] << 8) | tcp[3];
    if (dst_port != 80) return;
    if (memcmp(&ip[16], local_ip, 4) != 0) return;

    uint16_t src_port = ((uint16_t)tcp[0] << 8) | tcp[1];
    uint32_t seq = ((uint32_t)tcp[4] << 24) | ((uint32_t)tcp[5] << 16) |
                   ((uint32_t)tcp[6] << 8)  | tcp[7];
    uint8_t  tcp_hlen = (tcp[12] >> 4) * 4;
    uint8_t  flags = tcp[13];
    uint16_t ip_total = ((uint16_t)ip[2] << 8) | ip[3];
    uint16_t tcp_payload_len = ip_total - ihl - tcp_hlen;

    uint8_t *src_ip_addr  = &ip[12];
    uint8_t *src_mac_addr = &pkt[6];

    static uint32_t our_seq = 0x12345678;

    if (flags & TCP_FLAG_SYN) {
        mb1_print("TCP SYN recu -> SYN-ACK\r\n");
        send_tcp(eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, seq + 1, TCP_FLAG_SYN | TCP_FLAG_ACK, NULL, 0);
        our_seq++;
        return;
    }

    if ((flags & TCP_FLAG_ACK) && tcp_payload_len > 0) {
        mb1_print("TCP DATA recu -> HTTP 200\r\n");
        uint32_t new_ack = seq + tcp_payload_len;

        send_tcp(eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, new_ack, TCP_FLAG_ACK, NULL, 0);

        uint16_t resp_len = (uint16_t)(sizeof(http_response) - 1);
        send_tcp(eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, new_ack, TCP_FLAG_ACK | TCP_FLAG_FIN,
                 (const uint8_t*)http_response, resp_len);
        our_seq += resp_len + 1;
        return;
    }

    if (flags & TCP_FLAG_FIN) {
        send_tcp(eth, src_mac_addr, src_ip_addr, 80, src_port,
                 our_seq, seq + 1, TCP_FLAG_ACK, NULL, 0);
        mb1_print("TCP FIN -> ACK\r\n");
    }
}

// Handler IPv4 (dispatch ICMP/TCP)
static void handle_ip(spi_ethernet_t *eth, uint8_t *pkt, uint16_t len) {
    if (len < 34) return;
    uint8_t *ip = &pkt[14];

    if (memcmp(&ip[16], local_ip, 4) != 0) return;

    if (ip[9] == 1) { handle_icmp(eth, pkt, len); return; }  // ICMP
    if (ip[9] == 6) { handle_tcp(eth, pkt, len);  return; }  // TCP
}

int main(void) {
    #ifdef PREINIT_SUPPORTED
        preinit();
    #endif

    // Init UART
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
    mb1_print("\r\n\n");
    mb1_print("=== ENC28J60 INIT TEST ===\r\n");

    // Init SPI
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

    // GPIO
    digital_out_init(&eth.cs, MIKROBUS2_CS);
    digital_out_init(&eth.reset, MIKROBUS2_RST);

    enc28j60_cs_pin = MIKROBUS2_CS;
    spi_master_deselect_device(enc28j60_cs_pin);

    // Ethernet context
    eth.spi = &spi;
    memcpy(eth.mac, local_mac, 6);
    memcpy(eth.ip, local_ip, 4);
    eth.fullDuplex = 0;

    // Init ENC28J60
    mb1_print("ENC28J60 INIT...");
    spi_ethernet_init(&eth, &enc28j60_driver);
    mb1_print(" OK\r\n");

    // SPI
    uint8_t rev = enc28j60_get_rev();
    mb1_print("EREVID = ");
    mb1_print_hex(rev);
    mb1_print(rev == 0x00 || rev == 0xFF ? " NOT OK\r\n" : "\r\n");

    // PHY ID
    uint8_t low, high;
    enc28j60_phy_read(PHHID1, &low, &high);
    mb1_print("PHHID1 = ");
    mb1_print_hex16((uint16_t)high << 8 | low);
    mb1_print(" (expected 0x0083)\r\n");
    if (!(high == 0x00 && low == 0x83)) mb1_print(" NOT OK\r\n");

    // Waiting link
    mb1_print("\r\nWAIT LINK (10s max)...\r\n");
    uint8_t link_ok = 0;
    for (int i = 0; i < 100; i++) {
        if (spi_ethernet_get_link_status(&eth)) {
            link_ok = 1;
            mb1_print(">>> LINK UP\r\n");
            break;
        }
        mb1_print(".");
        if ((i + 1) % 10 == 0) mb1_print("\r\n");
        Delay_ms(100);
    }
    if (!link_ok) mb1_print("\r\n>>> LINK DOWN (no Ethernet cable)\r\n");

    // Frame test EtherType custom 0x88B5
    uint8_t tx_buf[60];
    memset(tx_buf, 0, sizeof(tx_buf));
    memset(&tx_buf[0], 0xFF, 6);
    memcpy(&tx_buf[6], local_mac, 6);
    tx_buf[12] = 0x88; tx_buf[13] = 0xB5;
    const char msg[] = "HELLO_FROM_MCU";
    memcpy(&tx_buf[14], msg, sizeof(msg)-1);

    mb1_print("TX TEST...");
    spi_ethernet_send(&eth, tx_buf, sizeof(tx_buf));
    mb1_print(" OK\r\n");

    mb1_print("\r\n=== HTTP SERVER READY - open http://172.20.22.200 ===\r\n");

    static uint8_t rx_buf[1518];

    while (1) {
        uint16_t rx_len = spi_ethernet_receive(&eth, rx_buf, sizeof(rx_buf));
        if (rx_len < 14) { Delay_ms(1); continue; }

        uint16_t etype = ((uint16_t)rx_buf[12] << 8) | rx_buf[13];

        if (etype == 0x0806)
            handle_arp(&eth, rx_buf, rx_len);
        else if (etype == 0x0800)
            handle_ip(&eth, rx_buf, rx_len);

        Delay_ms(1);
    }
}