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
 * @file net_phy.c
 * @brief Generic clause 22 PHY control, written from IEEE 802.3 clause 22.
 */

#include "net_phy.h"

/* BMCR */
#define BMCR_RESET          0x8000u
#define BMCR_AN_ENABLE      0x1000u
#define BMCR_AN_RESTART     0x0200u
/* BMSR */
#define BMSR_AN_COMPLETE    0x0020u
#define BMSR_LINK           0x0004u     /* latched low: read twice for the current state */
/* ANAR / ANLPAR */
#define AN_SELECTOR_8023    0x0001u
#define AN_10_HALF          0x0020u
#define AN_10_FULL          0x0040u
#define AN_100_HALF         0x0080u
#define AN_100_FULL         0x0100u

/* MDIO reads while waiting for the reset to finish (each takes ~30 us at 2.5 MHz). */
#define RESET_POLLS         20000u

static bool id_valid( uint16_t id1, uint16_t id2 )
{
    return !( ( 0xFFFFu == id1 && 0xFFFFu == id2 ) || ( 0x0000u == id1 && 0x0000u == id2 ) );
}

int32_t net_phy_init( net_phy_t *phy )
{
    uint16_t id1 = 0xFFFFu, id2 = 0xFFFFu;
    if ( !phy || !phy->read || !phy->write )
    {
        return -1;
    }

    if ( NET_PHY_ADDR_AUTO == phy->addr )
    {
        for ( uint8_t a = 0; a < 32; a++ )
        {
            if ( 0 == phy->read( phy->ctx, a, NET_PHY_REG_ID1, &id1 ) &&
                 0 == phy->read( phy->ctx, a, NET_PHY_REG_ID2, &id2 ) && id_valid( id1, id2 ) )
            {
                phy->addr = a;
                break;
            }
        }
        if ( NET_PHY_ADDR_AUTO == phy->addr )
        {
            return -1;      /* nothing answers on MDIO */
        }
    }
    else if ( phy->read( phy->ctx, phy->addr, NET_PHY_REG_ID1, &id1 ) ||
              phy->read( phy->ctx, phy->addr, NET_PHY_REG_ID2, &id2 ) || !id_valid( id1, id2 ) )
    {
        return -1;
    }
    phy->id = ( ( uint32_t )id1 << 16 ) | id2;

    /* Software reset; the bit clears itself when the reset is done. */
    if ( phy->write( phy->ctx, phy->addr, NET_PHY_REG_BMCR, BMCR_RESET ) )
    {
        return -1;
    }
    uint16_t bmcr = BMCR_RESET;
    for ( uint32_t i = 0; ( i < RESET_POLLS ) && ( bmcr & BMCR_RESET ); i++ )
    {
        if ( phy->read( phy->ctx, phy->addr, NET_PHY_REG_BMCR, &bmcr ) )
        {
            return -1;
        }
    }
    if ( bmcr & BMCR_RESET )
    {
        return -1;
    }

    /* Advertise 10/100, half/full duplex, then (re)start auto-negotiation. */
    if ( phy->write( phy->ctx, phy->addr, NET_PHY_REG_ANAR,
                     AN_SELECTOR_8023 | AN_10_HALF | AN_10_FULL | AN_100_HALF | AN_100_FULL ) ||
         phy->write( phy->ctx, phy->addr, NET_PHY_REG_BMCR, BMCR_AN_ENABLE | BMCR_AN_RESTART ) )
    {
        return -1;
    }
    return 0;
}

bool net_phy_link( net_phy_t *phy, net_phy_mode_t *mode )
{
    uint16_t bmsr = 0;
    /* The link bit latches low: the first read clears an old link failure. */
    if ( phy->read( phy->ctx, phy->addr, NET_PHY_REG_BMSR, &bmsr ) ||
         phy->read( phy->ctx, phy->addr, NET_PHY_REG_BMSR, &bmsr ) )
    {
        return false;
    }
    if ( !( bmsr & BMSR_LINK ) || !( bmsr & BMSR_AN_COMPLETE ) )
    {
        return false;
    }
    if ( mode )
    {
        uint16_t anar = 0, anlpar = 0;
        if ( phy->read( phy->ctx, phy->addr, NET_PHY_REG_ANAR, &anar ) ||
             phy->read( phy->ctx, phy->addr, NET_PHY_REG_ANLPAR, &anlpar ) )
        {
            return false;
        }
        /* Highest mode both sides offer (IEEE 802.3 priority order). */
        uint16_t common = anar & anlpar;
        if ( common & AN_100_FULL )
        {
            mode->speed_100 = true;  mode->full_duplex = true;
        }
        else if ( common & AN_100_HALF )
        {
            mode->speed_100 = true;  mode->full_duplex = false;
        }
        else if ( common & AN_10_FULL )
        {
            mode->speed_100 = false; mode->full_duplex = true;
        }
        else
        {
            mode->speed_100 = false; mode->full_duplex = false;
        }
    }
    return true;
}

// ------------------------------------------------------------------------- END
