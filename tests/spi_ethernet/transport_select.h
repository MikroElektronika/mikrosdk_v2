// tests/spi_ethernet/spi_ethernet_select.h
#ifndef SPI_ETHERNET_SELECT_H
#define SPI_ETHERNET_SELECT_H

#if SPI_ETH_CHIP == ENC28J60
    #include "enc28j60.h"
    #define SPI_ETH_DRIVER                          enc28j60_driver
    #define SPI_ETH_MAP_MIKROBUS( eth, mikrobus )   ENC28J60_MAP_MIKROBUS( eth, mikrobus )
    #define spi_eth_cfg_setup                        enc28j60_cfg_setup
    #define spi_eth_configure                        enc28j60_configure
    #define spi_eth_get_rev                          enc28j60_get_rev
    #define spi_eth_phy_read                         enc28j60_phy_read
    typedef enc28j60_cfg_t                           spi_eth_cfg_t;
#elif SPI_ETH_CHIP == W5500
    #include "w5500.h"
    #define SPI_ETH_DRIVER                          w5500_driver
    #define SPI_ETH_MAP_MIKROBUS( eth, mikrobus )   W5500_MAP_MIKROBUS( eth, mikrobus )
    #define spi_eth_cfg_setup                        w5500_cfg_setup
    #define spi_eth_configure                        w5500_configure
    #define spi_eth_get_rev                          w5500_get_rev
    typedef w5500_cfg_t                              spi_eth_cfg_t;
#elif SPI_ETH_CHIP == LAN9250
    #include "lan9250.h"
    #define SPI_ETH_DRIVER                          lan9250_driver
    #define SPI_ETH_MAP_MIKROBUS( eth, mikrobus )   LAN9250_MAP_MIKROBUS( eth, mikrobus )
    #define spi_eth_cfg_setup                        lan9250_cfg_setup
    #define spi_eth_configure                        lan9250_configure
    #define spi_eth_get_rev                          lan9250_get_rev
    typedef lan9250_cfg_t                            spi_eth_cfg_t;
#elif SPI_ETH_CHIP == W6100
    #include "w6100.h"
    #define SPI_ETH_DRIVER                          w6100_driver
    #define SPI_ETH_MAP_MIKROBUS( eth, mikrobus )   W6100_MAP_MIKROBUS( eth, mikrobus )
    #define spi_eth_cfg_setup                        w6100_cfg_setup
    #define spi_eth_configure                        w6100_configure
    #define spi_eth_get_rev                          w6100_get_rev
    typedef w6100_cfg_t                              spi_eth_cfg_t;
#else
    #error "Unsupported SPI Ethernet chip selected"
#endif

#endif // SPI_ETHERNET_SELECT_H