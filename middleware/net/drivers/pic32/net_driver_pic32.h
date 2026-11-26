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
 * @file net_driver_pic32.h
 * @brief net_driver_t for the Ethernet controller of PIC32MX 6xx/7xx and PIC32MZ
 * EC/EF (RMII, XC32): the same controller, at another address.
 * @details Polled (no interrupts): received frames are taken from a ring of
 * DMA descriptors by net_poll(). The PHY is handled through net_phy.h (any
 * clause 22 PHY, e.g. the LAN8720 of the mikromedia 4/5 for PIC32MZ and of the
 * MCU cards for PIC32MX).
 *
 * The RMII/MII choice and the default/alternate Ethernet pins are device
 * configuration bits (FMIIEN, FETHIO) set by the setup's preinit; the pins
 * that share an analog function must be made digital by the board (pins_init).
 *
 * @code
 * static net_driver_t drv;
 * net_pic32_cfg_t eth_cfg;
 * net_pic32_cfg_setup( &eth_cfg );
 * eth_cfg.phy_reset = ETH_RST;            // from board.h, HAL_PIN_NC if none
 * eth_cfg.pins_init = my_board_eth_pins;  // ANSELxCLR for the RMII pins
 * net_driver_pic32( &drv, &eth_cfg );
 * cfg.driver = &drv;                      // net_config_t, then net_init()
 * @endcode
 */

#ifndef _NET_DRIVER_PIC32_H
#define _NET_DRIVER_PIC32_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_driver.h"
#include "net_phy.h"
#include "drv_digital_out.h"

/*! Receive descriptors (one full frame each, 1536 bytes). */
#ifndef NET_PIC32_RX_BUFFERS
#define NET_PIC32_RX_BUFFERS 8
#endif

/*! @brief Driver configuration, see net_pic32_cfg_setup(). */
typedef struct
{
    pin_name_t phy_reset;           /*!< PHY reset pin (active low), HAL_PIN_NC if none. */
    uint8_t phy_addr;               /*!< PHY address 0..31, or NET_PHY_ADDR_AUTO (default) to scan. */
    void ( *pins_init )( void );    /*!< Board-specific pin setup (analog off), may be NULL. */
} net_pic32_cfg_t;

/*! @brief Defaults: no reset pin, PHY address found by scanning, no pin setup. */
void net_pic32_cfg_setup( net_pic32_cfg_t *cfg );

/*!
 * @brief Fill @p drv for the on-chip Ethernet controller. The hardware is
 * started by net_init() (driver init callback). Only one instance exists.
 * @param[in] cfg Copied, may be discarded afterwards.
 */
void net_driver_pic32( net_driver_t *drv, const net_pic32_cfg_t *cfg );

/*! @brief The PHY found at init (address, identifier), for diagnostics. */
const net_phy_t *net_driver_pic32_phy( void );

#ifdef __cplusplus
}
#endif

#endif // _NET_DRIVER_PIC32_H
// ------------------------------------------------------------------------- END
