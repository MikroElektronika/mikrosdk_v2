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
 * @file spi_ethernet_lan9252.h
 * @brief SPI EtherCAT LAN9252 Driver (minimum bring-up : SPI primitives +
 *        validation BYTE_TEST / HW_CFG.READY / ID_REV).
 */

#ifndef SPI_ETHERNET_LAN9252_H
#define SPI_ETHERNET_LAN9252_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include <stdint.h>
#include <stdbool.h>

#define LAN9252_MAP_MIKROBUS( cfg, mikrobus ) \
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
} lan9252_cfg_t;

// Forward declarations of driver functions
void     lan9252_init( spi_ethernet_t *eth, spi_ethernet_driver_t *drv );
void     lan9252_cfg_setup( lan9252_cfg_t *cfg );
uint8_t  lan9252_configure( spi_ethernet_t *eth, spi_master_t *spi, lan9252_cfg_t *cfg );

// Low-Level SPI Primitives
uint32_t lan9252_read_reg32( uint16_t addr );
void     lan9252_write_reg32( uint16_t addr, uint32_t value );

// Bring-up / identification
uint8_t  lan9252_byte_test_ok( void );
uint8_t  lan9252_wait_ready( void );
uint32_t lan9252_get_id_rev( void );
uint8_t  lan9252_get_rev( void );
// Stubs required by spi_ethernet_driver_t
int      lan9252_reset( void );
uint16_t lan9252_send_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint16_t lan9252_read_packet( spi_ethernet_t *eth, uint8_t *buf, uint16_t len );
uint8_t  lan9252_packet_available( spi_ethernet_t *eth );
uint8_t  lan9252_get_link_status( void );
int      lan9252_set_mac( uint8_t mac[ 6 ] );
int      lan9252_get_mac( uint8_t mac[ 6 ] );
int      lan9252_set_ip( uint8_t ip[ 4 ] );
int      lan9252_get_ip( uint8_t ip[ 4 ] );

extern spi_ethernet_driver_t lan9252_driver;
extern pin_name_t            lan9252_cs_pin;

// SPI Instructions (datasheet table 10-1, simple SPI mode, not SQI)
#define LAN9252_SPI_READ       0x03   // addr 2 bytes, not dummy, max 30 MHz
#define LAN9252_SPI_FASTREAD   0x0B   // addr 2 bytes, 1 dummy byte, max 80 MHz
#define LAN9252_SPI_WRITE      0x02   // addr 2 bytes, not dummy

// System CSR (Table 5-1 / 16-1), offsets d'octet, registres 32 bits
#define LAN9252_ID_REV         0x0050   // Chip ID (31:16, expected 0x9252) + Revision (15:0)
#define LAN9252_BYTE_TEST      0x0064   // fixe, RO, expected 0x87654321
#define LAN9252_HW_CFG         0x0074   // bit 27 = READY

#define LAN9252_BYTE_TEST_PATTERN   0x87654321UL
#define LAN9252_HW_CFG_READY_MASK  ( 1UL << 27 )

#endif

// ------------------------------------------------------------------------ END
