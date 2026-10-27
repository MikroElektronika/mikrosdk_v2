// tests/spi_ethernet/transport_select.h
// Maps the generic spi_eth_* names used by main.c to the selected SPI Ethernet controller driver.
#ifndef TRANSPORT_SELECT_H
#define TRANSPORT_SELECT_H

#include "eth_bus_spi.h"

// Supported SPI Ethernet controllers, select one with SPI_ETH_CHIP
#define SPI_ETH_CHIP_ENC28J60   0
#define SPI_ETH_CHIP_W5500      1
#define SPI_ETH_CHIP_WIZ_IP55   SPI_ETH_CHIP_W5500
#define SPI_ETH_CHIP_LAN9250    2
#define SPI_ETH_CHIP_W6100      3
#define SPI_ETH_CHIP_LAN8651    4

#ifndef SPI_ETH_CHIP
    #error "Define SPI_ETH_CHIP (one of SPI_ETH_CHIP_*) before including transport_select.h"
#endif

#if SPI_ETH_CHIP == SPI_ETH_CHIP_ENC28J60
    #include "enc28j60.h"
    #define SPI_ETH_DRIVER                          enc28j60_driver
    #define SPI_ETH_MAP_MIKROBUS( cfg, mikrobus )   ENC28J60_MAP_MIKROBUS( cfg, mikrobus )
    #define spi_eth_cfg_setup                       enc28j60_cfg_setup
    #define spi_eth_configure                       enc28j60_configure
    #define spi_eth_get_rev                         enc28j60_get_rev
    #define spi_eth_phy_read                        enc28j60_phy_read
    typedef enc28j60_cfg_t                          spi_eth_cfg_t;
#elif SPI_ETH_CHIP == SPI_ETH_CHIP_W5500
    #include "w5500.h"
    #define SPI_ETH_DRIVER                          w5500_driver
    #define SPI_ETH_MAP_MIKROBUS( cfg, mikrobus )   W5500_MAP_MIKROBUS( cfg, mikrobus )
    #define spi_eth_cfg_setup                       w5500_cfg_setup
    #define spi_eth_configure                       w5500_configure
    #define spi_eth_get_rev                         w5500_get_rev
    typedef w5500_cfg_t                             spi_eth_cfg_t;
#elif SPI_ETH_CHIP == SPI_ETH_CHIP_LAN9250
    #include "lan9250.h"
    #define SPI_ETH_DRIVER                          lan9250_driver
    #define SPI_ETH_MAP_MIKROBUS( cfg, mikrobus )   LAN9250_MAP_MIKROBUS( cfg, mikrobus )
    #define spi_eth_cfg_setup                       lan9250_cfg_setup
    #define spi_eth_configure                       lan9250_configure
    #define spi_eth_get_rev                         lan9250_get_rev
    typedef lan9250_cfg_t                           spi_eth_cfg_t;
#elif SPI_ETH_CHIP == SPI_ETH_CHIP_W6100
    #include "w6100.h"
    #define SPI_ETH_DRIVER                          w6100_driver
    #define SPI_ETH_MAP_MIKROBUS( cfg, mikrobus )   W6100_MAP_MIKROBUS( cfg, mikrobus )
    #define spi_eth_cfg_setup                       w6100_cfg_setup
    #define spi_eth_configure                       w6100_configure
    #define spi_eth_get_rev                         w6100_get_rev
    typedef w6100_cfg_t                             spi_eth_cfg_t;
#elif SPI_ETH_CHIP == SPI_ETH_CHIP_LAN8651
    #include "lan8651.h"
    #define SPI_ETH_DRIVER                          lan8651_driver
    #define SPI_ETH_MAP_MIKROBUS( cfg, mikrobus )   LAN8651_MAP_MIKROBUS( cfg, mikrobus )
    #define spi_eth_cfg_setup                       lan8651_cfg_setup
    #define spi_eth_configure                       lan8651_configure
    #define spi_eth_get_rev                         lan8651_get_rev
    #define spi_eth_get_phy_id                      lan8651_get_phy_id
    typedef lan8651_cfg_t                           spi_eth_cfg_t;
#else
    #error "Unsupported SPI Ethernet chip selected"
#endif

#endif // TRANSPORT_SELECT_H
