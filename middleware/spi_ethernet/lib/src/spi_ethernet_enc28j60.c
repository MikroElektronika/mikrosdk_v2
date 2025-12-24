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

void enc28j60_select_bank(uint8_t bank)
{
    if (bank > 3) return; // Sanity guard

    if (bank != current_bank)
    {
        // Clear lower 2 bits
        enc28j60_clear_bit_reg(ECON1, 0x03);

        // Set new bank bits
        enc28j60_write_reg(ECON1, bank);

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

spi_master_t spi;
spi_master_config_t spi_config;

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

#define CS_PIN_TODO GPIO_PA4 // TODO Esma
#define RST_PIN_TODO GPIO_PE11 // TODO Esma

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

uint8_t enc28j60_read_reg(uint8_t reg); // TODO Esma declaration

void enc28j60_init(spi_ethernet_t *eth, spi_ethernet_driver_t *drv) {
    // spi init blah blah
    // Set default properties for SRAM Click 1.
    spi_master_configure_default(&spi_config);

    // Set desired basic properties for SRAM Click 1 which is on mikroBUS1.
    spi_config.sck = GPIO_PA5;
    spi_config.miso = GPIO_PA6;
    spi_config.mosi = GPIO_PB5;
    spi_config.speed = 100000;
    spi_config.mode = SPI_MASTER_MODE_DEFAULT;
    spi_config.default_write_data = 0;

    // Try to reserve memory for the SRAM Click 1.
    spi_master_open(&spi, &spi_config);

    // Set Chip Select polarity (SRAM Click requires active low).
    spi_master_set_chip_select_polarity(SPI_MASTER_CHIP_SELECT_DEFAULT_POLARITY);

    // Set desired default write (dummy) data.
    spi_master_set_default_write_data(&spi, 0);

    // Set desired baud rate (speed).
    spi_master_set_speed(&spi, 100000);

    // Set desired mode (SRAM Click requires mode 0).
    spi_master_set_mode(&spi, SPI_MASTER_MODE_DEFAULT);

    // TODO ESMA: SPI initialization placeholder
    spi_master_deselect_device( CS_PIN_TODO );  // CS <- 1, don't talk to ENC

    enc28j60_delay();                  // wait a little bit

    digital_out_high( RST_PIN_TODO );
    enc28j60_delay();                  // wait a little bit
    digital_out_low( RST_PIN_TODO );
    enc28j60_delay();                  // wait a little bit
    digital_out_high( RST_PIN_TODO );
    enc28j60_delay();                  // wait for completion

    spi_master_select_device( CS_PIN_TODO );        // talk to ENC
    enc28j60_soft_reset();
    spi_master_deselect_device( CS_PIN_TODO );      // end of transmission
    enc28j60_delay();                               // wait for completion

    memcpy(enc28j60_mac_addr, eth->mac, sizeof(enc28j60_mac_addr));  // save MAC address
    memcpy(enc28j60_ipaddr, eth->ip, sizeof(enc28j60_ipaddr));       // save IP address

    enc28j60_select_bank(0);

    // receive buffer
    enc28j60_write_reg(ERXSTL, RECEIVE_START);      // set receive start address
    enc28j60_write_reg(ERXNDL, RECEIVE_END);        // set receive end address
    enc28j60_write_reg(ERXRDPTL, RECEIVE_END);     // set receive read pointer. Enc can not write anything in receive
                                                       //    buffer above the address set in this pointer.
                                                       //    Receive buffer is empty now, so we should load the pointer
                                                       //    with receive buffer end address.
    enc28j60_write_reg(ERDPTL, RECEIVE_START);     // set read pointer

    // transmit buffer
    enc28j60_write_reg(ETXSTL, TRANSMIT_START);     // set transmit start address

    // TODO Esma: filter settings?

    enc28j60_select_bank(2);

    uint16_t higher_byte;
    uint16_t lower_byte;

    enc28j60_write_reg(MACON1, eth->fullDuplex ? ( MACON1_MARXEN | MACON1_TXPAUS | MACON1_RXPAUS ) :
                                                ( MACON1_MARXEN ) /*RXPAUS too or no?*/);

    enc28j60_write_reg(MACON3, eth->fullDuplex ? ( MACON3_PADCFG_SET | MACON3_TXCRCEN | MACON3_FULDPX) :
                                                ( MACON3_PADCFG_SET | MACON3_TXCRCEN ));

    // Set the DEFER bit
    enc28j60_write_reg(MACON4, eth->fullDuplex ? 0 : MACON4_DEFER );

    // Maximum frame size
    enc28j60_write_reg( MAMXFLL, ENC28J60_FRAME_SIZE & 0xFF );
    enc28j60_write_reg( MAMXFLH, ( ENC28J60_FRAME_SIZE & 0xFF00 ) >> 8 );

    // Back-to-Back Inter-Packet Gap register. Recommended values are 0x15 for full duplex, 0x12 otherwise.
    enc28j60_write_reg( MABBIPG, eth->fullDuplex ? 0x15 : 0x12 );

    // Non-Back-to-Back Inter-Packet Gap register. Recommended value is 0x12.
    enc28j60_write_reg( MAIPGL, 0x12 );

    // If half duplex is used, recommended value for MAIPGH is 0x0C.
    if ( !eth->fullDuplex )
        enc28j60_write_reg( MAIPGH, 0x0C );

    // Note: If half duplex is used, MACLCON1 and MACLCON2 should be programmed,
    // however most applications won't require alterations.

    enc28j60_select_bank(3);

    // Configure local MAC address
    // TODO Esma: shouldn't it be backwards?
    enc28j60_write_reg( MAADR6, enc28j60_mac_addr[0] );
    enc28j60_write_reg( MAADR5, enc28j60_mac_addr[1] );
    enc28j60_write_reg( MAADR4, enc28j60_mac_addr[2] );
    enc28j60_write_reg( MAADR3, enc28j60_mac_addr[3] );
    enc28j60_write_reg( MAADR2, enc28j60_mac_addr[4] );
    enc28j60_write_reg( MAADR1, enc28j60_mac_addr[5] );

    /*
     * !st: this was taken from microchip tcp/ip stack code!
     * Disable the CLKOUT output to reduce EMI generation
     */
     enc28j60_write_reg(ECOCON, 0x00);        // Output off (0V)

    /*
     * !st: this was taken from microchip tcp/ip stack code!
     * Get the Rev ID so that we can implement the correct errata workarounds
     */
    enc_hwRev = enc28j60_read_reg(EREVID);

    /*
     * other settings
     */
    // set FULDPX bit of PHCON1 // TODO Esma: what?
    // enc28j60_read_phy(PHCON1, &higher_byte, &lower_byte);
    // enc28j60_write_phy(PHCON1, (higher_byte & 0b11111110) | (fullDuplex ? 1 : 0), lower_byte);

    // Disable half duplex loopback
    enc28j60_write_phy( PHCON2, 0x0001, 0x0000 );

    // Enable reception
    enc28j60_set_bit_reg( ECON1, ECON1_RXEN );
    enc28j60_delay();

    // Initialize ARP cache
    memset( &enc28j60_arp_cache, 0, sizeof( enc28j60_arp_cache ) );

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

uint16_t enc28j60_read_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t len) {
    static uint16_t nextPtr = RECEIVE_START; // Initialized only the first time this routine is entered.
    uint8_t header[6];
    uint16_t length;
    uint16_t status;
    uint8_t temp[ENC28J60_FRAME_SIZE];
    uint8_t result;

    /*
     * Packet structure:
     * Next packet pointer : 2 bytes
     * Receive status vector (RSV) : 4 bytes, consisting of:
     *   Byte 0 : Receive byte count low byte
     *   Byte 1 : Receive byte count high byte
     *   Byte 2 : Receive status low byte
     *   Byte 3 : Receive status high byte
     * Ethernet frame data : n bytes
     */

    enc28j60_select_bank(0);
    // Point to the start of the received packet
    enc28j60_write_reg(ERDPTL, GET_LOW_BYTE(nextPtr));
    enc28j60_write_reg(ERDPTH, GET_HIGH_BYTE(nextPtr));

    // The packet is preceded by a 6-byte header
    enc28j60_read_mem(header, sizeof(header));

    // The first two bytes are the address of the next packet
    nextPtr = enc28j60_read_mem(header, 2);
    // Get the length of the received packet
    length = enc28j60_read_mem(header + 2, 2);
    // Get the receive status vector (RSV)
    status = enc28j60_read_mem(header + 4, 2);

    // Make sure no error occurred
    if((status & ENC28J60_RSV_RECEIVED_OK) != 0)
    {
        // Limit the number of data to read
        length = fmin(length, ENC28J60_FRAME_SIZE); // TODO Esma: changed from MIN to fmin
        // Read packet data
        enc28j60_read_mem( temp, length );

        // Valid packet received
        result = 0;
    } else {
        // The received packet contains an error
        result = 1;
    }

    if(nextPtr == ENC28J60_RX_BUFFER_START)
    {
        enc28j60_write_reg(ERXRDPTL, ENC28J60_RX_BUFFER_STOP & 0xFF);
        enc28j60_write_reg(ERXRDPTH, ENC28J60_RX_BUFFER_STOP >> 8);
    } else {
        uint16_t newPtr = nextPtr - 1;
        enc28j60_write_reg(ERXRDPTL, newPtr & 0xFF);
        enc28j60_write_reg(ERXRDPTH, newPtr >> 8);
    }

    // Decrement the packet counter
    enc28j60_set_bit_reg(ECON2, PKTDEC);

    return result;
}

uint8_t enc28j60_packet_available(spi_ethernet_t *eth)
{
    if ( !eth )
        return 0;

    enc28j60_select_bank(1);
    uint8_t num_of_packages = enc28j60_read_reg(EPKTCNT);  // reads EPKTCNT

    return num_of_packages;
}

uint16_t enc28j60_send_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t len) {
    enc28j60_select_bank(0);
    // Set transmit buffer start address
    enc28j60_write_reg(ETXSTL, ENC28J60_TX_BUFFER_START);

    // Set transmit buffer end address
    enc28j60_write_reg(ETXNDL, ENC28J60_TX_BUFFER_START + len);

    // Errata workaround
    enc28j60_set_bit_reg(ECON1, TXRST);
    enc28j60_clear_bit_reg(ECON1, TXRST);
    // Send the contents of the transmit buffer onto the network
    enc28j60_set_bit_reg(ECON1, TXRTS);

    // Write data to transmit buffer
    enc28j60_write_mem( &data, len );

    // // Wait until transmission is complete
    // while(enc28j60_read_reg(ECON1) & TXRTS);

    if( (enc28j60_read_reg(EIR) & TXERIF) ){
        enc28j60_clear_bit_reg(ECON1, TXRTS);
    }

    return 0; // No error
}

/*
 * ENC28J60 SPI instructions implementation
 */
// RCR - Read Control Register
static uint8_t enc28j60_read_reg(uint8_t reg) {
    uint8_t cmd = ENC28J60_RCR_CMD | reg; // 0x00 | reg
    uint8_t data = 0;
    uint8_t dummy = 0;

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write( &spi, &cmd, 1 );

    // If MAC/MII register, one dummy read required
    if (reg & 0x80) {
        spi_master_read( &spi, &dummy, 1 );
    }

    spi_master_read( &spi, &data, 1 );
    spi_master_deselect_device( CS_PIN_TODO );

    return data;
}

// RBM - Read Buffer Memory
static uint8_t * enc28j60_read_mem( uint8_t *buf, uint16_t len ) {
    uint8_t cmd = ENC28J60_RBM_CMD;

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, &cmd, 1);
    spi_master_read(&spi, buf, len);
    spi_master_deselect_device( CS_PIN_TODO );

    return buf;
}

// Special - read 2 bytes from buffer memory and return as uint16_t
static uint16_t enc28j60_read_mem16() {
    uint8_t cmd = ENC28J60_RBM_CMD;
    uint8_t buf[2];

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, &cmd, 1);
    spi_master_read(&spi, buf, 2);
    spi_master_deselect_device( CS_PIN_TODO );

    return ( (uint16_t)buf[0] | ( (uint16_t)buf[1] << 8 ) );
}

// WCR - Write Control Register
static void enc28j60_write_reg(uint8_t reg, uint16_t value) {
    uint8_t cmd[2] = {
        (uint8_t)(ENC28J60_WCR_CMD | (reg & 0x1F)),
        value
    };

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, cmd, 2);
    spi_master_deselect_device( CS_PIN_TODO );
}

// WBM - Write Buffer Memory
static void enc28j60_write_mem(const uint8_t *buf, uint16_t len) {
    uint8_t cmd = ENC28J60_WBM_CMD;

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, &cmd, 1);
    spi_master_write(&spi, buf, len);
    spi_master_deselect_device( CS_PIN_TODO );
}

// BSF - Bit Field Set
static void enc28j60_set_bit_reg( uint8_t reg, uint8_t mask ) {
    uint8_t cmd[2] = {
        (uint8_t)(ENC28J60_BFS_CMD | (reg & 0x1F)),
        mask
    };

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, cmd, 2);
    spi_master_deselect_device( CS_PIN_TODO );
}

// BFC - Bit Field Clear
static void enc28j60_clear_bit_reg( uint8_t reg, uint8_t mask ) {
    uint8_t cmd[2] = {
        (uint8_t)(ENC28J60_BFC_CMD | (reg & 0x1F)),
        mask
    };

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, cmd, 2);
    spi_master_deselect_device( CS_PIN_TODO );
}

// SRC - System Reset Command
static void enc28j60_soft_reset() {
    uint8_t cmd = ENC28J60_SRC_CMD;

    spi_master_select_device( CS_PIN_TODO );
    spi_master_write(&spi, &cmd, 1);
    spi_master_deselect_device( CS_PIN_TODO );
    // Let PHY stabilize
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
