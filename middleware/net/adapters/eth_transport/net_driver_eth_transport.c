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
 * @file net_driver_eth_transport.c
 * @brief net_driver_t on top of the eth_transport_* API (see the header).
 * @details Includes mikroSDK headers only (no stack headers): the two err_t
 * types of mikroSDK and lwIP never meet in one file.
 */

#include "net_driver_eth_transport.h"

static int32_t ethtr_init( void *ctx, const uint8_t *mac )
{
    /* Writes the address to the controller if its driver supports it, and to the cache. */
    return ( ETH_TRANSPORT_SUCCESS == eth_transport_set_mac( ( eth_transport_t * )ctx, ( uint8_t * )mac ) ) ? 0 : -1;
}

static int32_t ethtr_send( void *ctx, const uint8_t *frame, uint16_t len )
{
    eth_transport_t *eth = ( eth_transport_t * )ctx;
    return ( eth_transport_send( eth, ( uint8_t * )frame, len ) == len ) ? 0 : -1;
}

static int32_t ethtr_receive( void *ctx, uint8_t *buf, uint16_t size )
{
    eth_transport_t *eth = ( eth_transport_t * )ctx;
    if ( !eth_transport_available( eth ) )
    {
        return 0;
    }
    uint16_t len = eth_transport_receive( eth, buf, size );
    if ( eth->bus_error )
    {
        return -1;
    }
    return len;
}

static bool ethtr_link_up( void *ctx )
{
    return 0 != eth_transport_get_link_status( ( eth_transport_t * )ctx );
}

void net_driver_eth_transport( net_driver_t *drv, eth_transport_t *eth )
{
    drv->ctx = eth;
    drv->init = ethtr_init;
    drv->send = ethtr_send;
    drv->receive = ethtr_receive;
    drv->link_up = ethtr_link_up;
}

// ------------------------------------------------------------------------- END
