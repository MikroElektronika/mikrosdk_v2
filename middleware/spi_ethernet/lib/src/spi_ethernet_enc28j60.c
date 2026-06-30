#include "spi_ethernet_enc28j60.h"
#include "drv_spi_master.h"
#include <delays.h>

#define GET_LOW_BYTE(param) ((char *)&param)[0]
#define GET_HIGH_BYTE(param) ((char *)&param)[1]

/*
 * bit masks
 */
#define PKTDEC      0x40
#define CSUMEN      0x10
#define DMAST       0x20

#define MARXEN      0x01
#define ECON1_RXEN  0x04
#define AUTOINC     0x80
#define TXRTS       0x08
#define TXRST       0x80
#define TXERIF      0x02
#define TXIF        0x08

#define MACON1_MARXEN (0x1)
#define MACON1_RXPAUS (0x4)
#define MACON1_TXPAUS (0x8)

#define MACON3_PADCFG_MASK (0xE0)
#define MACON3_PADCFG_SET (0x20) // TODO Esma
#define MACON3_TXCRCEN (0x10)
#define MACON3_FULDPX (0x1)

#define MACON4_DEFER (0x40)

static uint8_t current_bank = 0;

// Static functions declaration
static uint8_t enc28j60_read_reg(uint8_t reg);
static uint8_t * enc28j60_read_mem( uint8_t *buf, uint16_t len );
static uint16_t enc28j60_read_mem16();
static void enc28j60_write_reg(uint8_t reg, uint16_t value);
uint8_t enc28j60_packet_available(spi_ethernet_t *eth);
static void enc28j60_write_mem(const uint8_t *buf, uint16_t len);
static void enc28j60_set_bit_reg( uint8_t reg, uint8_t mask );
static void enc28j60_clear_bit_reg( uint8_t reg, uint8_t mask );
static void enc28j60_soft_reset();
static void enc28j60_set_write_ptr(uint16_t addr);
static void enc28j60_set_read_ptr(uint16_t addr);
void enc28j60_write_phy(uint8_t reg, unsigned short higher_byte, unsigned short lower_byte);
void enc28j60_read_phy(uint8_t reg, uint8_t *higher_byte, uint8_t *lower_byte);

void enc28j60_select_bank(uint8_t bank)
{
    if (bank > 3) return; // Sanity guard

    if (bank != current_bank)
    {
        // Clear lower 2 bits
        enc28j60_clear_bit_reg(ECON1, 0x03);
        enc28j60_set_bit_reg(ECON1, bank & 0x03);

        current_bank = bank;
    }
}

// Vars
uint16_t enc28j60_packet_length;          // size of last packet received (CRC non included)

uint8_t enc28j60_mac_addr[6];             // MAC address of the controller
uint8_t enc28j60_ipaddr[4];               // IP address of the device
uint8_t enc28j60_ff_mac[6] =
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // MAC broadcast address
uint8_t enc28j60_subnet_broadcast[4];     // subnet broadcast address

uint8_t enc28j60_gw_ip_addr[4];           // Gateway IP address
uint8_t enc28j60_ipmask[4];               // network mask
uint8_t enc28j60_dns_ip_addr[4];          // DNS server IP
uint8_t enc28j60_rmt_ip_addr[4];          // remote IP Address of host (DNS server reply)

unsigned long enc28j60_usertimersec = 0;  // must be incremented by user 1 time per second

static uint16_t enc_hwRev;                // enc hardware revision

/*
 * union for TCP synchronisation/acknowledgment
 */
union tcp32 {
    struct {
        uint8_t b0, b1, b2, b3;
    } bytes;
    uint8_t raw[4];
    uint32_t value;
};

static uint16_t closeTCP = 0 ; // TCP/IP close flag

/*
 * ARP defines and globals
 */
#define ARP_WAIT_TIME   5

#ifndef NULL
#define NULL    (void *)0
#endif
#define ARPCACHESIZE     3

enc28j60_arp_cache_t enc28j60_arp_cache[ARPCACHESIZE];

spi_ethernet_driver_t enc28j60_driver = {
    .init            = enc28j60_init,
    .send_packet     = enc28j60_send_packet,
    .read_packet     = enc28j60_read_packet,
    .available       = enc28j60_packet_available,
    .get_link_status = enc28j60_get_link_status,
    .set_mac         = enc28j60_set_mac,
    .get_mac         = enc28j60_get_mac,
    .set_ip          = enc28j60_set_ip,
    .get_ip          = enc28j60_get_ip
};

static void enc28j60_compute_broadcast_addr(uint8_t *dst)
{
    for (uint8_t i = 0; i < 4; i++)
        dst[i] = enc28j60_ipaddr[i] | (~enc28j60_ipmask[i]);
}

static spi_ethernet_t *current_eth = NULL;

void enc28j60_init(spi_ethernet_t *eth, spi_ethernet_driver_t *drv) {
    current_eth = eth;

    digital_out_high(&eth->cs);   // CS inactif

    digital_out_high(&eth->reset);
    enc28j60_delay();
    digital_out_low(&eth->reset);
    enc28j60_delay();
    digital_out_high(&eth->reset);
    enc28j60_delay();

    enc28j60_soft_reset();
    enc28j60_delay();

    memcpy(enc28j60_mac_addr, eth->mac, 6);
    memcpy(enc28j60_ipaddr, eth->ip, 4);

    enc28j60_select_bank(0);

    enc28j60_write_reg(ERXSTL, RECEIVE_START & 0xFF);
    enc28j60_write_reg(ERXSTH, RECEIVE_START >> 8);
    enc28j60_write_reg(ERXNDL, RECEIVE_END & 0xFF);
    enc28j60_write_reg(ERXNDH, RECEIVE_END >> 8);
    enc28j60_write_reg(ERXRDPTL, RECEIVE_END & 0xFF);
    enc28j60_write_reg(ERXRDPTH, RECEIVE_END >> 8);
    enc28j60_write_reg(ERDPTL, RECEIVE_START & 0xFF);
    enc28j60_write_reg(ERDPTH, RECEIVE_START >> 8);

    enc28j60_write_reg(ETXSTL, TRANSMIT_START & 0xFF);
    enc28j60_write_reg(ETXSTH, TRANSMIT_START >> 8);

    enc28j60_select_bank(2);
    enc28j60_write_reg(MACON1, eth->fullDuplex ?
        (MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS) : MACON1_MARXEN);
    enc28j60_write_reg(MACON3, eth->fullDuplex ?
        (MACON3_PADCFG_SET | MACON3_TXCRCEN | MACON3_FULDPX) :
        (MACON3_PADCFG_SET | MACON3_TXCRCEN));
    enc28j60_write_reg(MACON4, eth->fullDuplex ? 0 : MACON4_DEFER);
    enc28j60_write_reg(MAMXFLL, ENC28J60_FRAME_SIZE & 0xFF);
    enc28j60_write_reg(MAMXFLH, (ENC28J60_FRAME_SIZE >> 8) & 0xFF);
    enc28j60_write_reg(MABBIPG, eth->fullDuplex ? 0x15 : 0x12);
    enc28j60_write_reg(MAIPGL, 0x12);
    if (!eth->fullDuplex)
        enc28j60_write_reg(MAIPGH, 0x0C);

    enc28j60_select_bank(3);
    enc28j60_write_reg(MAADR6, enc28j60_mac_addr[0]);
    enc28j60_write_reg(MAADR5, enc28j60_mac_addr[1]);
    enc28j60_write_reg(MAADR4, enc28j60_mac_addr[2]);
    enc28j60_write_reg(MAADR3, enc28j60_mac_addr[3]);
    enc28j60_write_reg(MAADR2, enc28j60_mac_addr[4]);
    enc28j60_write_reg(MAADR1, enc28j60_mac_addr[5]);

    enc28j60_write_reg(ECOCON, 0x00);
    enc_hwRev = enc28j60_read_reg(EREVID);

    enc28j60_write_phy(PHCON2, 0x0001, 0x0000);

    enc28j60_set_bit_reg(ECON1, ECON1_RXEN);
    enc28j60_delay();

    memset(&enc28j60_arp_cache, 0, sizeof(enc28j60_arp_cache));

    enc28j60_select_bank(0);
}

void enc28j60_filters_enable(uint8_t select_filters) {
    enc28j60_select_bank(1);
    enc28j60_set_bit_reg(ERXFCON, select_filters);
    enc28j60_select_bank(0);
}

void enc28j60_filters_disable(uint8_t deselect_filters) {
    enc28j60_select_bank(1);
    enc28j60_clear_bit_reg(ERXFCON, deselect_filters);
    enc28j60_select_bank(0);
}

uint8_t  enc28j60_get_link_status(void) {
    // TODO Esma: implement
    return 0;
}
int enc28j60_set_mac(const uint8_t mac[6]) {
    // TODO Esma: implement
    return 0;
}
int enc28j60_get_mac(uint8_t mac[6]) {
    // TODO Esma: implement
    return 0;
}
int enc28j60_set_ip(const uint8_t ip[4]) {
    // TODO Esma: implement
    return 0;
}
int enc28j60_get_ip(uint8_t ip[4]) {
    // TODO Esma: implement
    return 0;
}

// uint16_t enc28j60_read_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t len) {
//     static uint16_t nextPtr = RECEIVE_START; // Initialized only the first time this routine is entered.
//     uint8_t header[6];
//     uint16_t length;
//     uint16_t status;
//     uint8_t temp[ENC28J60_FRAME_SIZE];
//     uint8_t result;

//     /*
//      * Packet structure:
//      * Next packet pointer : 2 bytes
//      * Receive status vector (RSV) : 4 bytes, consisting of:
//      *   Byte 0 : Receive byte count low byte
//      *   Byte 1 : Receive byte count high byte
//      *   Byte 2 : Receive status low byte
//      *   Byte 3 : Receive status high byte
//      * Ethernet frame data : n bytes
//      */

//     enc28j60_select_bank(0);
//     // Point to the start of the received packet
//     enc28j60_write_reg(ERDPTL, GET_LOW_BYTE(nextPtr));
//     enc28j60_write_reg(ERDPTH, GET_HIGH_BYTE(nextPtr));

//     // The packet is preceded by a 6-byte header
//     enc28j60_read_mem(header, sizeof(header));

//     // The first two bytes are the address of the next packet
//     nextPtr = enc28j60_read_mem(header, 2);
//     // Get the length of the received packet
//     length = enc28j60_read_mem(header + 2, 2);
//     // Get the receive status vector (RSV)
//     status = enc28j60_read_mem(header + 4, 2);

//     // Make sure no error occurred
//     if((status & ENC28J60_RSV_RECEIVED_OK) != 0)
//     {
//         // Limit the number of data to read
//         length = fmin(length, ENC28J60_FRAME_SIZE); // TODO Esma: changed from MIN to fmin
//         // Read packet data
//         enc28j60_read_mem( temp, length );

//         // Valid packet received
//         result = 0;
//     } else {
//         // The received packet contains an error
//         result = 1;
//     }

//     if(nextPtr == ENC28J60_RX_BUFFER_START)
//     {
//         enc28j60_write_reg(ERXRDPTL, ENC28J60_RX_BUFFER_STOP & 0xFF);
//         enc28j60_write_reg(ERXRDPTH, ENC28J60_RX_BUFFER_STOP >> 8);
//     } else {
//         uint16_t newPtr = nextPtr - 1;
//         enc28j60_write_reg(ERXRDPTL, newPtr & 0xFF);
//         enc28j60_write_reg(ERXRDPTH, newPtr >> 8);
//     }

//     // Decrement the packet counter
//     enc28j60_set_bit_reg(ECON2, PKTDEC);

//     return result;
// }
uint16_t enc28j60_read_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t max_len)
{
    static uint16_t nextPtr = RECEIVE_START;
    uint8_t header[6];
    uint16_t length, status;

    current_eth = eth;
    if (!enc28j60_packet_available(eth)) return 0;

    enc28j60_select_bank(0);
    enc28j60_write_reg(ERDPTL, nextPtr & 0xFF);
    enc28j60_write_reg(ERDPTH, nextPtr >> 8);

    enc28j60_read_mem(header, sizeof(header));

    nextPtr = header[0] | (header[1] << 8);
    length  = header[2] | (header[3] << 8);
    status  = header[4] | (header[5] << 8);

    if ((status & ENC28J60_RSV_RECEIVED_OK) == 0) {
        enc28j60_set_bit_reg(ECON2, PKTDEC);
        return 0;
    }

    if (length > 4) length -= 4;
    if (length > max_len) length = max_len;
    enc28j60_read_mem(data, length);

    uint16_t newPtr = (nextPtr == RECEIVE_START) ? RECEIVE_END : nextPtr - 1;
    enc28j60_write_reg(ERXRDPTL, newPtr & 0xFF);
    enc28j60_write_reg(ERXRDPTH, newPtr >> 8);

    enc28j60_set_bit_reg(ECON2, PKTDEC);
    return length;
}

uint8_t enc28j60_packet_available(spi_ethernet_t *eth)
{
    if ( !eth )
        return 0;

    enc28j60_select_bank(0);
    enc28j60_set_bit_reg(ECON1, ECON1_RXEN);

    enc28j60_select_bank(1);
    uint8_t num_of_packages = enc28j60_read_reg(EPKTCNT);  // reads EPKTCNT

    return num_of_packages;
}

uint16_t enc28j60_send_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t len) {
    current_eth = eth;
    enc28j60_select_bank(0);

    enc28j60_write_reg(ETXSTL, ENC28J60_TX_BUFFER_START & 0xFF);
    enc28j60_write_reg(ETXSTH, ENC28J60_TX_BUFFER_START >> 8);
    uint16_t txnd = ENC28J60_TX_BUFFER_START + len;
    enc28j60_write_reg(ETXNDL, txnd & 0xFF);
    enc28j60_write_reg(ETXNDH, txnd >> 8);

    enc28j60_set_bit_reg(ECON1, TXRST);
    enc28j60_clear_bit_reg(ECON1, TXRST);
    enc28j60_clear_bit_reg(EIR, TXERIF | TXIF);

    enc28j60_set_write_ptr(ENC28J60_TX_BUFFER_START);
    uint8_t ctrl = 0x00;
    enc28j60_write_mem(&ctrl, 1);
    enc28j60_write_mem(data, len);

    enc28j60_set_bit_reg(ECON1, TXRTS);

    if (enc28j60_read_reg(EIR) & TXERIF)
        enc28j60_clear_bit_reg(ECON1, TXRTS);

    return 0;
}

uint8_t enc28j60_get_rev(void)
{
    return enc_hwRev;
}

/*
 * ENC28J60 SPI instructions implementation
 */
// RCR - Read Control Register
static uint8_t enc28j60_read_reg(uint8_t reg) {
    uint8_t cmd = ENC28J60_RCR_CMD | reg;
    uint8_t data = 0, dummy = 0;

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, &cmd, 1);
    if (reg & 0x80) spi_master_read(current_eth->spi, &dummy, 1);
    spi_master_read(current_eth->spi, &data, 1);
    digital_out_high(&current_eth->cs);

    return data;
}

// RBM - Read Buffer Memory
static uint8_t * enc28j60_read_mem( uint8_t *buf, uint16_t len ) {
    uint8_t cmd = ENC28J60_RBM_CMD;

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, &cmd, 1);
    spi_master_read(current_eth->spi, buf, len);
    digital_out_high(&current_eth->cs);

    return buf;
}

// Special - read 2 bytes from buffer memory and return as uint16_t
static uint16_t enc28j60_read_mem16() {
    uint8_t cmd = ENC28J60_RBM_CMD;
    uint8_t buf[2];

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, &cmd, 1);
    spi_master_read(current_eth->spi, buf, 2);
    digital_out_high(&current_eth->cs);

    return ( (uint16_t)buf[0] | ( (uint16_t)buf[1] << 8 ) );
}

// WCR - Write Control Register
static void enc28j60_write_reg(uint8_t reg, uint16_t value) {
    uint8_t cmd[2] = {
        (uint8_t)(ENC28J60_WCR_CMD | (reg & 0x1F)),
        (uint8_t)value
    };

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, cmd, 2);
    digital_out_high(&current_eth->cs);
}

// WBM - Write Buffer Memory
static void enc28j60_write_mem(const uint8_t *buf, uint16_t len) {
    uint8_t cmd = ENC28J60_WBM_CMD;

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, &cmd, 1);
    spi_master_write(current_eth->spi, buf, len);
    digital_out_high(&current_eth->cs);
}

// BSF - Bit Field Set
static void enc28j60_set_bit_reg( uint8_t reg, uint8_t mask ) {
    uint8_t cmd[2] = {
        (uint8_t)(ENC28J60_BFS_CMD | (reg & 0x1F)),
        mask
    };

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, cmd, 2);
    digital_out_high(&current_eth->cs);
}

// BFC - Bit Field Clear
static void enc28j60_clear_bit_reg( uint8_t reg, uint8_t mask ) {
    uint8_t cmd[2] = {
        (uint8_t)(ENC28J60_BFC_CMD | (reg & 0x1F)),
        mask
    };

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, cmd, 2);
    digital_out_high(&current_eth->cs);
}

// SRC - System Reset Command
static void enc28j60_soft_reset() {
    uint8_t cmd = ENC28J60_SRC_CMD;

    digital_out_low(&current_eth->cs);
    spi_master_write(current_eth->spi, &cmd, 1);
    digital_out_high(&current_eth->cs);
    Delay_ms(1);
}

// More helper functions?
static void enc28j60_set_write_ptr(uint16_t addr)
{
    enc28j60_write_reg(EWRPTL, addr & 0xFF);
    enc28j60_write_reg(EWRPTH, addr >> 8);
}

static void enc28j60_set_read_ptr(uint16_t addr)
{
    enc28j60_write_reg(ERDPTL, addr & 0xFF);
    enc28j60_write_reg(ERDPTH, addr >> 8);
}

// Correct PHY register access functions (with delays)
void enc28j60_write_phy(uint8_t reg, unsigned short higher_byte, unsigned short lower_byte) {
    enc28j60_select_bank(2);
    enc28j60_write_reg(MIREGADR, reg);              // set address of PHY register
    enc28j60_delay();
    enc28j60_write_reg(MIWRL, lower_byte);                   // writes low byte
    enc28j60_delay();
    enc28j60_write_reg(MIWRH, higher_byte);                   // then high byte
    enc28j60_delay();
}

void enc28j60_read_phy(uint8_t reg, uint8_t *higher_byte, uint8_t *lower_byte) {
    enc28j60_select_bank(2);
    enc28j60_write_reg(MIREGADR, reg);              // set address of PHY register
    enc28j60_set_bit_reg(MICMD, MIIRD);             // ask for reading
    // Alternatively poll MISTAT.BUSY bit here
    enc28j60_delay();                               // wait a little bit
    enc28j60_clear_bit_reg(MICMD, MIIRD);           // clear request
    *lower_byte = enc28j60_read_reg(MIRDL);         // get low byte
    *higher_byte = enc28j60_read_reg(MIRDH);        // get high byte
}

void enc28j60_delay() {
    uint16_t i;

    for(i = 0; i < 200; i++)
    {
        Delay_500us();
        Delay_500us();
    }
}

// ------------------------------------------------------------------------ END
