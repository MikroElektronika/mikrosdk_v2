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
 * @file net_driver_tm4c.h
 * @brief net_driver_t for the Ethernet controller of TI TM4C129 with its
 * integrated PHY.
 * @details Polled (no interrupts): received frames are taken from a ring of
 * DMA descriptors by net_poll(). The integrated PHY is reached over MDIO
 * (net_phy.h). Clocks, power, resets and the Ethernet LED pins are set up by
 * the driver, no TivaWare needed.
 *
 * @code
 * static net_driver_t drv;
 * net_tm4c_cfg_t eth_cfg;
 * net_tm4c_cfg_setup( &eth_cfg );
 * net_driver_tm4c( &drv, &eth_cfg );
 * cfg.driver = &drv;                 // net_config_t, then net_init()
 * @endcode
 */

#ifndef _NET_DRIVER_TM4C_H
#define _NET_DRIVER_TM4C_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_driver.h"
#include "net_phy.h"

/*! Receive and transmit buffers (one frame each, 1536 bytes). */
#ifndef NET_TM4C_RX_BUFFERS
#define NET_TM4C_RX_BUFFERS 8
#endif
#ifndef NET_TM4C_TX_BUFFERS
#define NET_TM4C_TX_BUFFERS 4
#endif

/*! @brief Driver configuration, see net_tm4c_cfg_setup(). */
typedef struct
{
    bool leds;          /*!< true (default): Ethernet LEDs on PK5 (EN0LED2) and PK6 (EN0LED1),
                             as the MikroE boards wire them. */
    uint8_t phy_addr;   /*!< Integrated PHY address, NET_PHY_ADDR_AUTO (default) to scan. */
} net_tm4c_cfg_t;

/*! @brief Defaults. */
void net_tm4c_cfg_setup( net_tm4c_cfg_t *cfg );

/*!
 * @brief Fill @p drv for the on-chip Ethernet. The hardware is started by
 * net_init() (driver init callback). Only one instance exists.
 * @param[in] cfg Copied, may be discarded afterwards.
 */
void net_driver_tm4c( net_driver_t *drv, const net_tm4c_cfg_t *cfg );

/*! @brief The PHY found at init (address, identifier), for diagnostics. */
const net_phy_t *net_driver_tm4c_phy( void );

#ifdef __cplusplus
}
#endif

#endif // _NET_DRIVER_TM4C_H
// ------------------------------------------------------------------------- END
