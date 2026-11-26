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
 * @file net_mdns.h
 * @brief mDNS responder (RFC 6762) with DNS-SD services (RFC 6763): the board
 * answers to "<hostname>.local" and announces services such as its web server,
 * so it can be found without knowing its address.
 * @details Uses the lwIP mDNS responder (IPv4). Start it once after net_init();
 * it runs from net_poll(), follows address and link changes and probes that the
 * name is not in use (net_mdns_status() reports a conflict, net_mdns_rename()
 * picks another name). There is no stop: lwIP 2.2.1 can still touch the
 * responder's state up to 0.5 s after removing it (a delayed answer to a
 * truncated query), so it is never removed.
 *
 * The network controller must pass multicast frames (01:00:5E:00:00:FB): the
 * built-in drivers (STM32, Kinetis, TM4C, PIC32) do; for an SPI controller
 * this depends on its receive filter.
 *
 * Leave it out of the build with -DNET_LWIP_MDNS=0 (also disables IGMP); the
 * functions then return NET_ERROR. -DNET_MDNS_MAX_SERVICES=n (default 2).
 *
 * @code
 * net_mdns_start( "my-board" );                                   // my-board.local
 * net_mdns_add_service( "My board", "_http", NET_MDNS_TCP, 80, "path=/", NULL );
 * @endcode
 */

#ifndef _NET_MDNS_H
#define _NET_MDNS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_api.h"

#define NET_MDNS_LABEL_MAX  63      /*!< Longest host name, instance name, service type or TXT item. */

/*! @brief Transport of a service. */
typedef enum
{
    NET_MDNS_TCP = 0,
    NET_MDNS_UDP
} net_mdns_proto_t;

/*!
 * @brief Start answering to "<hostname>.local" (once; it runs from then on).
 * @param hostname Letters, digits and '-', at most 63 characters; NULL uses
 * net_config_t.hostname.
 * @return NET_OK (probing started), NET_NOT_READY (no net_init()), NET_INVALID
 * (bad name or already started), NET_NO_MEMORY, NET_ERROR (mDNS not built in).
 */
net_err_t net_mdns_start( const char *hostname );

/*!
 * @brief Change the host name and probe again, e.g. after a conflict.
 * @return NET_OK, NET_NOT_READY (not started), NET_INVALID (bad name).
 */
net_err_t net_mdns_rename( const char *hostname );

/*!
 * @brief Announce a service, e.g. ( "Board web page", "_http", NET_MDNS_TCP, 80, "path=/", &id ).
 * @param instance Name shown to users (any UTF-8, at most 63 bytes).
 * @param service Service type starting with '_' ("_http", "_mqtt", ...).
 * @param txt NULL, or TXT items separated by ';' ("path=/;version=1"), each at
 * most 63 bytes; the text is copied.
 * @param id Receives the id for net_mdns_remove_service(); may be NULL.
 * @return NET_OK, NET_NOT_READY (not started), NET_INVALID, NET_NO_MEMORY
 * (NET_MDNS_MAX_SERVICES reached).
 */
net_err_t net_mdns_add_service( const char *instance, const char *service, net_mdns_proto_t proto, uint16_t port,
                                const char *txt, uint8_t *id );

/*! @brief Stop announcing a service. @return NET_OK, NET_INVALID (no such service). */
net_err_t net_mdns_remove_service( uint8_t id );

/*!
 * @brief State of the name (and services).
 * @return NET_OK (probing done, announced), NET_NOT_READY (not started or still
 * probing), NET_REFUSED (another device uses the name: net_mdns_rename()).
 */
net_err_t net_mdns_status( void );

#ifdef __cplusplus
}
#endif

#endif // _NET_MDNS_H
// ------------------------------------------------------------------------- END
