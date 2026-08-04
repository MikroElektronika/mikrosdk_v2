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
 * @file spi_ethernet_wizip20.c
 * @brief SPI Ethernet WIZnet IP20 Driver.
 */

#include "spi_ethernet.h"
#include "spi_ethernet_wiz-ip20.h"
#include "drv_spi_master.h"
#include <delays.h>
#include <string.h>

pin_name_t wizip20_cs_pin;
static spi_ethernet_t *current_eth = NULL;
static uint8_t wizip20_mac_addr[ 6 ];
static uint8_t wizip20_ipaddr[ 4 ];
static uint8_t wizip20_hwRev;

static uint8_t  wizip20_read_reg( uint16_t addr );
static void     wizip20_write_reg( uint16_t addr, uint8_t val_in );
static void     wizip20_read_burst( uint16_t addr, uint8_t *buf, uint16_t len );
static void     wizip20_write_burst( uint16_t addr, uint8_t *buf, uint16_t len );
static void     wizip20_hw_reset( spi_ethernet_t *eth );

spi_ethernet_driver_t wizip20_driver = {
    .init            = wizip20_init,
    .send_packet     = wizip20_send_packet,
    .read_packet     = wizip20_read_packet,
    .available       = wizip20_packet_available,
    .get_link_status = wizip20_get_link_status,
    .set_mac         = wizip20_set_mac,
    .get_mac         = wizip20_get_mac,
    .set_ip          = wizip20_set_ip,
    .get_ip          = wizip20_get_ip
};
