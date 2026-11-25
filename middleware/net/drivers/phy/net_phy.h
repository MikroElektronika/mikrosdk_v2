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
 * @file net_phy.h
 * @brief Generic Ethernet PHY control over MDIO (IEEE 802.3 clause 22).
 * @details Uses only the standard registers every 10/100 PHY has (basic
 * control and status, identifier, auto-negotiation advertisement and link
 * partner ability), so it works with the LAN8720, KSZ8081, DP83848 and others
 * without PHY-specific code. The MAC driver supplies the MDIO access.
 */

#ifndef _NET_PHY_H
#define _NET_PHY_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>

/*! Scan the MDIO bus for the PHY (net_phy_t.addr). */
#define NET_PHY_ADDR_AUTO 0xFF

/*! Clause 22 registers. */
#define NET_PHY_REG_BMCR    0x00    /*!< Basic control */
#define NET_PHY_REG_BMSR    0x01    /*!< Basic status */
#define NET_PHY_REG_ID1     0x02    /*!< PHY identifier 1 */
#define NET_PHY_REG_ID2     0x03    /*!< PHY identifier 2 */
#define NET_PHY_REG_ANAR    0x04    /*!< Auto-negotiation advertisement */
#define NET_PHY_REG_ANLPAR  0x05    /*!< Auto-negotiation link partner ability */

/*! @brief PHY on an MDIO bus. Fill addr and the callbacks, then net_phy_init(). */
typedef struct
{
    void *ctx;                                                                  /*!< Passed to read / write. */
    uint8_t addr;                                                               /*!< 0..31 or NET_PHY_ADDR_AUTO. */
    int32_t ( *read )( void *ctx, uint8_t addr, uint8_t reg, uint16_t *value ); /*!< 0 or negative on error. */
    int32_t ( *write )( void *ctx, uint8_t addr, uint8_t reg, uint16_t value ); /*!< 0 or negative on error. */
    uint32_t id;                                                                /*!< ID1 << 16 | ID2, set by net_phy_init(). */
} net_phy_t;

/*! @brief Negotiated link. */
typedef struct
{
    bool speed_100;     /*!< true: 100 Mbit/s, false: 10 Mbit/s. */
    bool full_duplex;   /*!< true: full duplex. */
} net_phy_mode_t;

/*!
 * @brief Find the PHY (if addr is NET_PHY_ADDR_AUTO), reset it and start
 * auto-negotiation for 10/100 Mbit/s, half and full duplex.
 * @return 0, or negative when no PHY answers or the reset does not finish.
 */
int32_t net_phy_init( net_phy_t *phy );

/*!
 * @brief Read the link state; when the link is up and auto-negotiation has
 * finished, the negotiated mode is stored in @p mode (may be NULL).
 * @return true when the link is up.
 */
bool net_phy_link( net_phy_t *phy, net_phy_mode_t *mode );

#ifdef __cplusplus
}
#endif

#endif // _NET_PHY_H
// ------------------------------------------------------------------------- END
