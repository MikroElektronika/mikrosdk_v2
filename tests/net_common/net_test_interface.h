/****************************************************************************
**
** Copyright ( C ) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

/*!
 * @file net_test_interface.h
 * @brief Network interface setup shared by the network layer tests
 * (net_web_server, net_http_client): an SPI Ethernet Click or the on-chip
 * Ethernet of PIC32, STM32, Kinetis or TM4C129.
 * @details Include it after the settings in main.c:
 *   NET_INTERFACE (NET_IF_*), SPI_ETH_CHIP and MIKROBUS_POSITION_SPI_ETH for
 *   NET_IF_SPI. net_test_interface.cmake links the matching libraries, reading
 *   the same settings from main.c. Header-only: include it from one file.
 */

#ifndef NET_TEST_INTERFACE_H
#define NET_TEST_INTERFACE_H

#include <string.h>
#include <stdint.h>
#include "log.h"
#include "net_api.h"

#define NET_IF_SPI      0
#define NET_IF_PIC32    1
#define NET_IF_STM32    2
#define NET_IF_KINETIS  3
#define NET_IF_TM4C     4

#ifndef NET_INTERFACE
    #error "Define NET_INTERFACE (NET_IF_SPI, NET_IF_PIC32, NET_IF_STM32, NET_IF_KINETIS or NET_IF_TM4C) before including net_test_interface.h"
#endif
#ifndef MIKROBUS_POSITION_SPI_ETH
    #define MIKROBUS_POSITION_SPI_ETH 1
#endif

#if NET_INTERFACE == NET_IF_SPI
    #include "transport_select.h"
    #include "net_driver_eth_transport.h"
    #define INTERFACE_NAME SPI_ETH_CHIP_NAME " (SPI)"
#elif NET_INTERFACE == NET_IF_PIC32
    #include "mcu.h"
    #include "net_driver_pic32.h"
    #define INTERFACE_NAME "PIC32 Ethernet"
#elif NET_INTERFACE == NET_IF_STM32
    #include "net_driver_stm32.h"
    #define INTERFACE_NAME "STM32 Ethernet"
#elif NET_INTERFACE == NET_IF_KINETIS
    #include "net_driver_kinetis.h"
    #define INTERFACE_NAME "Kinetis Ethernet"
#elif NET_INTERFACE == NET_IF_TM4C
    #include "net_driver_tm4c.h"
    #define INTERFACE_NAME "TM4C129 Ethernet"
#else
    #error "Unknown NET_INTERFACE"
#endif

#if NET_INTERFACE == NET_IF_SPI
static eth_transport_t eth;
static eth_bus_spi_t bus;
#endif

#if NET_INTERFACE == NET_IF_SPI
static void net_test_interface_init( net_driver_t *driver, const uint8_t *mac, log_t *logger )
{
    spi_eth_cfg_t eth_cfg;
    spi_eth_cfg_setup( &eth_cfg );
    SPI_ETH_MAP_MIKROBUS( eth_cfg, MIKROBUS_POSITION_SPI_ETH );
    memcpy( eth_cfg.eth.mac, mac, 6 );

    if ( spi_eth_configure( &eth, &bus, &eth_cfg ) != ETH_TRANSPORT_SUCCESS ||
         eth_transport_init( &eth, &SPI_ETH_DRIVER ) != ETH_TRANSPORT_SUCCESS )
    {
        log_printf( logger, "%s init FAILED\r\n", SPI_ETH_CHIP_NAME );
        for ( ; ; );
    }
    net_driver_eth_transport( driver, &eth );
}
#elif NET_INTERFACE == NET_IF_STM32
static void net_test_interface_init( net_driver_t *driver, const uint8_t *mac, log_t *logger )
{
    net_stm32_cfg_t eth_cfg;
    net_stm32_cfg_setup( &eth_cfg );    // pins and PHY clock as wired on the board
    ( void )mac;
    ( void )logger;
    net_driver_stm32( driver, &eth_cfg );
}
#elif NET_INTERFACE == NET_IF_KINETIS
static void net_test_interface_init( net_driver_t *driver, const uint8_t *mac, log_t *logger )
{
    net_kinetis_cfg_t eth_cfg;
    net_kinetis_cfg_setup( &eth_cfg );  // pins and RMII clock as wired on the board
    ( void )mac;
    ( void )logger;
    net_driver_kinetis( driver, &eth_cfg );
}
#elif NET_INTERFACE == NET_IF_TM4C
static void net_test_interface_init( net_driver_t *driver, const uint8_t *mac, log_t *logger )
{
    net_tm4c_cfg_t eth_cfg;
    net_tm4c_cfg_setup( &eth_cfg );     // integrated PHY, Ethernet LEDs on PK5/PK6
    ( void )mac;
    ( void )logger;
    net_driver_tm4c( driver, &eth_cfg );
}
#else
#if defined( NET_EXAMPLE_PIC32MX )
// EasyPIC Fusion v7 ETH MCU card with PIC32MX795F512L: ERXERR, ERXD0, ERXD1 share
// AN11, AN12, AN13. ERXERR (RB11) is not connected to the PHY on this card: tie it
// to ground, as for CycloneTCP.
static void board_eth_pins( void )
{
    AD1PCFGSET = ( 1UL << 11 ) | ( 1UL << 12 ) | ( 1UL << 13 );
}
#ifndef ETH_RST
    #define ETH_RST GPIO_PG7    // PHY reset of the card
#endif
#elif defined( NET_EXAMPLE_PIC32MZ_144 )
// mikromedia 4/5 for PIC32MZ (144 pins): the RMII pins that share an analog input.
static void board_eth_pins( void )
{
    ANSELJCLR = ( 1UL << 8 ) | ( 1UL << 9 ) | ( 1UL << 11 );   // ETXD0, ETXD1, EREFCLK
    ANSELHCLR = ( 1UL << 4 ) | ( 1UL << 5 );                    // ERXERR, ERXD1
}
#else
// Other packages: clear the analog function (ANSELxCLR) of your board's RMII pins here.
static void board_eth_pins( void )
{
}
#endif

static void net_test_interface_init( net_driver_t *driver, const uint8_t *mac, log_t *logger )
{
    net_pic32_cfg_t eth_cfg;
    net_pic32_cfg_setup( &eth_cfg );
    #ifdef ETH_RST
    eth_cfg.phy_reset = ETH_RST;
    #endif
    eth_cfg.pins_init = board_eth_pins;
    ( void )mac;
    ( void )logger;
    net_driver_pic32( driver, &eth_cfg );
}
#endif

#endif // NET_TEST_INTERFACE_H
// ------------------------------------------------------------------------- END
