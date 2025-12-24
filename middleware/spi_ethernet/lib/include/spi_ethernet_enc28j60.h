/*
 *
 *
 * TODO - license and header for this file - spi_ethernet_enc28j60.h
 *
 *
 *
 *
 */
#include "spi_ethernet.h"
#include <stdint.h>
#include <stdbool.h>

/* Forward declarations of driver functions */
void     enc28j60_init(spi_ethernet_t *eth, spi_ethernet_driver_t *drv);
uint16_t enc28j60_send_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t len);
uint16_t enc28j60_read_packet(spi_ethernet_t *eth, uint8_t *data, uint16_t len);
uint8_t  enc28j60_get_link_status(void);
int      enc28j60_set_mac(const uint8_t mac[6]);
int      enc28j60_get_mac(uint8_t mac[6]);
int      enc28j60_set_ip(const uint8_t ip[4]);
int      enc28j60_get_ip(uint8_t ip[4]);

uint16_t beta_enc28j60_available(void);
int      beta_enc28j60_flush(void);
int      beta_enc28j60_set_gateway(const uint8_t gw[4]);
int      beta_enc28j60_get_gateway(uint8_t gw[4]);
int      beta_enc28j60_set_phy_mode(uint8_t mode);
int      beta_enc28j60_ping(const uint8_t ip[4], uint16_t timeout_ms);
int      beta_enc28j60_dhcp_start(void);
int      beta_enc28j60_dhcp_stop(void);
int      beta_enc28j60_ioctl(uint8_t cmd, void *param);

/* Define the driver struct */
extern spi_ethernet_driver_t enc28j60_driver;

// ENC28J60 register addresses and bit positions
#define MIIRD    0x01

#define EIE              0x1B
#define EIR              0x1C
#define ESTAT            0x1D
#define ECON2            0x1E
#define ECON1            0x1F
// Bank 0 registers
#define ERDPTL           (0x00)
#define ERDPTH           (0x01)
#define EWRPTL           (0x02)
#define EWRPTH           (0x03)
#define ETXSTL           (0x04)
#define ETXSTH           (0x05)
#define ETXNDL           (0x06)
#define ETXNDH           (0x07)
#define ERXSTL           (0x08)
#define ERXSTH           (0x09)
#define ERXNDL           (0x0A)
#define ERXNDH           (0x0B)
#define ERXRDPTL         (0x0C)
#define ERXRDPTH         (0x0D)
#define ERXWRPTL         (0x0E)
#define ERXWRPTH         (0x0F)
#define EDMASTL          (0x10)
#define EDMASTH          (0x11)
#define EDMANDL          (0x12)
#define EDMANDH          (0x13)
#define EDMADSTL         (0x14)
#define EDMADSTH         (0x15)
#define EDMACSL          (0x16)
#define EDMACSH          (0x17)
// Bank 1 registers
#define EHT0             (0x00)
#define EHT1             (0x01)
#define EHT2             (0x02)
#define EHT3             (0x03)
#define EHT4             (0x04)
#define EHT5             (0x05)
#define EHT6             (0x06)
#define EHT7             (0x07)
#define EPMM0            (0x08)
#define EPMM1            (0x09)
#define EPMM2            (0x0A)
#define EPMM3            (0x0B)
#define EPMM4            (0x0C)
#define EPMM5            (0x0D)
#define EPMM6            (0x0E)
#define EPMM7            (0x0F)
#define EPMCSL           (0x10)
#define EPMCSH           (0x11)
#define EPMOL            (0x14)
#define EPMOH            (0x15)
#define EWOLIE           (0x16)
#define EWOLIR           (0x17)
#define ERXFCON          (0x18)
#define EPKTCNT          (0x19)
// Bank 2 registers
#define MACON1           (0x00|0x80)
#define MACON2           (0x01|0x80)
#define MACON3           (0x02|0x80)
#define MACON4           (0x03|0x80)
#define MABBIPG          (0x04|0x80)
#define MAIPGL           (0x06|0x80)
#define MAIPGH           (0x07|0x80)
#define MACLCON1         (0x08|0x80)
#define MACLCON2         (0x09|0x80)
#define MAMXFLL          (0x0A|0x80)
#define MAMXFLH          (0x0B|0x80)
#define MAPHSUP          (0x0D|0x80)
#define MICON            (0x11|0x80)
#define MICMD            (0x12|0x80)
#define MIREGADR         (0x14|0x80)
#define MIWRL            (0x16|0x80)
#define MIWRH            (0x17|0x80)
#define MIRDL            (0x18|0x80)
#define MIRDH            (0x19|0x80)
// Bank 3 registers
#define MAADR5           (0x00|0x80)
#define MAADR6           (0x01|0x80)
#define MAADR3           (0x02|0x80)
#define MAADR4           (0x03|0x80)
#define MAADR1           (0x04|0x80)
#define MAADR2           (0x05|0x80)
#define EBSTSD           (0x06)
#define EBSTCON          (0x07)
#define EBSTCSL          (0x08)
#define EBSTCSH          (0x09)
#define MISTAT           (0x0A|0x80)
#define EREVID           (0x12)
#define ECOCON           (0x15)
#define EFLOCON          (0x17)
#define EPAUSL           (0x18)
#define EPAUSH           (0x19)
// PHY registers
#define PHCON1           0x00
#define PHSTAT1          0x01
#define PHHID1           0x02
#define PHHID2           0x03
#define PHCON2           0x10
#define PHSTAT2          0x11
#define PHIE             0x12
#define PHIR             0x13
#define PHLCON           0x14

// SPI instruction set for the ENC28J60
#define ENC28J60_WBM_CMD 0x7A       // Write Buffer Memory
#define ENC28J60_RBM_CMD 0x3A       // Read Buffer Memory
#define ENC28J60_BFS_CMD 0x80       // Bit Field Set
#define ENC28J60_BFC_CMD 0xA0       // Bit Field Clear
#define ENC28J60_WCR_CMD 0x40       // Write Control Register
#define ENC28J60_RCR_CMD 0x00       // Read Control Register
#define ENC28J60_SRC_CMD 0xFF       // System Reset Command

// Maximum packet length (Ethernet frames are between 64 and 1518 bytes long)
#define ENC28J60_FRAME_SIZE 1518

// Receive status vector bit definitions
// Bits 0 to 15 are assigned for Received Byte Count
#define ENC28J60_RSV_RECEIVED_OK       0x80    // Frame received OK (bit 23 out of 31)

// Receive and transmit buffers
#define ENC28J60_RX_BUFFER_START 0x0000
#define ENC28J60_RX_BUFFER_STOP  0x17FF
#define ENC28J60_TX_BUFFER_START 0x1800
#define ENC28J60_TX_BUFFER_STOP  0x1FFF

// Memory allocation
// 8kb RAM available
#define RAM_SIZE (8192)
// Transmit buffer start address, a few more bytes for padding pseudo header + transmit status : Even memory address
#define TRANSMIT_START (RAM_SIZE - (ENC28J60_FRAME_SIZE + 100))
// Receive buffer start address : Should be an even memory address; must be 0 for errata
#define RECEIVE_START (0)
// Receive buffer end address : Odd for errata workaround
#define RECEIVE_END (TRANSMIT_START - 1)
// Reply buffer starts after per packet control byte
#define REPLY_START (TRANSMIT_START + 1)
// Receive buffer size
#define RECEIVE_SIZE (RECEIVE_END - RECEIVE_START + 1)

#define NO_ADDR (0xFFFF)

// ARP cache structure
typedef struct {
    bool valid;             // valid/invalid entry flag
    unsigned long time;     // timestamp
    uint8_t ip[4];          // IP address
    uint8_t mac[6];         // MAC address behind the IP address
} enc28j60_arp_cache_t;

typedef struct {
    void *spi;
    void (*cs_low)(void); // pull CS low
    void (*cs_high)(void); // pull CS high
    void (*delay_ms)(uint32_t ms); // millisecond delay

    // optional IRQ pin callback (can be NULL)
    int irq_pin; // for reference; driver won't manipulate pin directly
} enc28j60_cfg_t;

void enc28j60_delay();
