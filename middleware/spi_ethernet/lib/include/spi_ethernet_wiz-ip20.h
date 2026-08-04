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
 * @file spi_ethernet_wiz-ip20.h
 * @brief SPI Ethernet WIZnet IP20 Driver.
 */

#ifndef SPI_ETHERNET_WIZIP20_H
#define SPI_ETHERNET_WIZIP20_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include <stdint.h>
#include <stdbool.h>

#define WIZIP20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST );

typedef struct {
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    pin_name_t rst;

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;

    uint8_t mac[ 6 ];
    uint8_t ip[ 4 ];
    uint8_t full_duplex;
} wizip20_cfg_t;

void     wizip20_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );
void     wizip20_cfg_setup( wizip20_cfg_t *cfg );
uint8_t  wizip20_configure( spi_ethernet_t *eth, spi_master_t *spi, wizip20_cfg_t *cfg );
uint16_t wizip20_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint16_t wizip20_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint8_t  wizip20_packet_available( spi_ethernet_t *eth );
uint8_t  wizip20_get_link_status( void );
uint8_t  wizip20_get_rev( void );
int      wizip20_set_mac( uint8_t mac[ 6 ] );
int      wizip20_get_mac( uint8_t mac[ 6 ] );
int      wizip20_set_ip( uint8_t ip[ 4 ] );
int      wizip20_get_ip( uint8_t ip[ 4 ] );

extern spi_ethernet_driver_t wizip20_driver;
extern pin_name_t            wizip20_cs_pin;

#define WIZIP20_RWB_READ      0x00   // TODO
#define WIZIP20_RWB_WRITE     0x00   // TODO

// Common registers
#define WIZIP20_SHAR          0x0000 // TODO adresse MAC
#define WIZIP20_SIPR          0x0000 // TODO adresse IP
#define WIZIP20_VERSIONR      0x0000 // TODO registre version/chip ID
#define WIZIP20_PHYCFGR       0x0000 // TODO registre PHY/link status
#define WIZIP20_PHYCFGR_LNK_MASK 0x01 // TODO bit link

// Socket 0 registers
#define WIZIP20_Sn_MR         0x0000 // TODO
#define WIZIP20_Sn_CR         0x0000 // TODO
#define WIZIP20_Sn_MR_MACRAW  0x00   // TODO
#define WIZIP20_Sn_CR_OPEN    0x00   // TODO
#define WIZIP20_Sn_CR_SEND    0x00   // TODO
#define WIZIP20_Sn_CR_RECV    0x00   // TODO
#define WIZIP20_Sn_TX_WR      0x0000 // TODO
#define WIZIP20_Sn_RX_RD      0x0000 // TODO
#define WIZIP20_Sn_RX_RSR     0x0000 // TODO

#endif
