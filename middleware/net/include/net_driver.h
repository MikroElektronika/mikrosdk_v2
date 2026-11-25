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
 * @file net_driver.h
 * @brief Ethernet frame driver interface of the mikroSDK network layer.
 * @details A driver moves complete Ethernet frames (destination MAC to the end
 * of the payload, without preamble and FCS) between the network layer and one
 * Ethernet controller: an on-chip MAC with its PHY, or an external controller
 * (see net_driver_eth_transport.h for the SPI controllers of middleware/ethernet).
 * The interface does not depend on the TCP/IP stack behind net_api.h.
 *
 * All callbacks are called from net_poll() and the net_* functions, never from
 * interrupts, so a driver needs no locking towards the network layer.
 */

#ifndef _NET_DRIVER_H
#define _NET_DRIVER_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>

/*! Largest frame the network layer sends or accepts: 14 header + 1500 payload + 4 (VLAN tag). */
#define NET_DRIVER_FRAME_MAX 1518

/*!
 * @brief Ethernet frame driver.
 * @details Fill it in (or let a driver's init function do so) and pass it in
 * net_config_t.driver. Return values: 0 = success, negative = error, as below.
 */
typedef struct net_driver
{
    void *ctx; /*!< Driver state, passed to every callback. */

    /*!
     * @brief Start the controller with the given MAC address. Optional (NULL if
     * the controller is already running). Called once by net_init().
     * @return 0 on success, negative on error (net_init() then fails).
     */
    int32_t ( *init )( void *ctx, const uint8_t *mac );

    /*!
     * @brief Send one complete frame of @p len bytes (14 to NET_DRIVER_FRAME_MAX).
     * The controller pads frames shorter than 60 bytes and appends the FCS.
     * @return 0 when the frame was handed to the controller, negative on error.
     */
    int32_t ( *send )( void *ctx, const uint8_t *frame, uint16_t len );

    /*!
     * @brief Copy the next received frame into @p buf (@p size bytes available).
     * Must not block.
     * @return frame length, 0 when no frame is waiting, negative on error.
     */
    int32_t ( *receive )( void *ctx, uint8_t *buf, uint16_t size );

    /*!
     * @brief Report the link state (PHY link up). Optional: NULL means the link
     * is always up. Called about every NET_LINK_POLL_MS milliseconds.
     */
    bool ( *link_up )( void *ctx );
} net_driver_t;

#ifdef __cplusplus
}
#endif

#endif // _NET_DRIVER_H
// ------------------------------------------------------------------------- END
