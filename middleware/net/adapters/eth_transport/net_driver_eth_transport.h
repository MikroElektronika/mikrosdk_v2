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
 * @file net_driver_eth_transport.h
 * @brief net_driver_t for the Ethernet controllers of middleware/ethernet
 * (eth_transport_* API: ENC28J60, LAN9250, LAN8651, W5500, W6100, ...).
 * @details Configure and initialise the controller with the eth_transport_*
 * functions first (bus, reset pin, controller driver), then wrap it:
 * @code
 * static net_driver_t drv;
 * net_driver_eth_transport( &drv, &eth );   // eth: an initialised eth_transport_t
 * cfg.driver = &drv;
 * @endcode
 * The controller must pass raw Ethernet frames (MAC mode; for WIZnet chips the
 * MACRAW socket of its eth_transport driver).
 */

#ifndef _NET_DRIVER_ETH_TRANSPORT_H
#define _NET_DRIVER_ETH_TRANSPORT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_driver.h"
#include "eth_transport.h"

/*!
 * @brief Fill @p drv to use @p eth. Both objects must stay valid while the
 * network layer runs. net_init() writes the MAC address of net_config_t to the
 * controller (eth_transport_set_mac(); controllers without set_mac keep theirs,
 * so use the same address in both places).
 */
void net_driver_eth_transport( net_driver_t *drv, eth_transport_t *eth );

#ifdef __cplusplus
}
#endif

#endif // _NET_DRIVER_ETH_TRANSPORT_H
// ------------------------------------------------------------------------- END
