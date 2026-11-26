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
 * @file net_driver_kinetis.h
 * @brief net_driver_t for the ENET controller of NXP Kinetis MK60, MK61, MK63,
 * MK64, MK65, MK66 and MKV58 (RMII).
 * @details Polled (no interrupts): received frames are taken from a ring of
 * buffer descriptors by net_poll(). The PHY is handled through net_phy.h. The
 * pins, the RMII clock source and the system MPU are set up by the driver. The
 * variant (NET_KINETIS_K60_K64, NET_KINETIS_K65_K66, NET_KINETIS_KV58) comes
 * from the build (middleware/net/CMakeLists.txt).
 *
 * Board wiring, as in the mikroSDK boards and MCU cards:
 *   RXER PTA5, RXD1 PTA12, RXD0 PTA13, CRS_DV PTA14, TXEN PTA15, TXD0 PTA16,
 *   TXD1 PTA17, MDIO/MDC on PTB0/PTB1 (MK60, MK64) or PTA7/PTA8 (MK65, MK66,
 *   MKV58), and the 50 MHz RMII clock into ENET_1588_CLKIN (PTE26).
 *
 * @code
 * static net_driver_t drv;
 * net_kinetis_cfg_t eth_cfg;
 * net_kinetis_cfg_setup( &eth_cfg );   // board defaults
 * net_driver_kinetis( &drv, &eth_cfg );
 * cfg.driver = &drv;                   // net_config_t, then net_init()
 * @endcode
 */

#ifndef _NET_DRIVER_KINETIS_H
#define _NET_DRIVER_KINETIS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_driver.h"
#include "net_phy.h"
#include "drv_digital_out.h"

/*! Receive and transmit buffers (one frame each, 1536 bytes). */
#ifndef NET_KINETIS_RX_BUFFERS
#define NET_KINETIS_RX_BUFFERS 8
#endif
#ifndef NET_KINETIS_TX_BUFFERS
#define NET_KINETIS_TX_BUFFERS 4
#endif

/*! @brief Pin layout. */
typedef enum
{
    NET_KINETIS_PINS_K60_K64 = 0,   /*!< MDIO PTB0, MDC PTB1, data pins on mux 4. */
    NET_KINETIS_PINS_K65_K66,       /*!< MDIO PTA7, MDC PTA8 (mux 5), data pins on mux 4. */
    NET_KINETIS_PINS_KV58           /*!< MDIO PTA7, MDC PTA8, data pins (except RXER) on mux 5. */
} net_kinetis_pins_t;

/*! @brief Source of the 50 MHz RMII clock. */
typedef enum
{
    NET_KINETIS_REF_CLOCK_CLKIN = 0,    /*!< ENET_1588_CLKIN on PTE26 (MikroE boards). */
    NET_KINETIS_REF_CLOCK_EXTAL         /*!< The oscillator on EXTAL (50 MHz). */
} net_kinetis_ref_clock_t;

/*! @brief Driver configuration, see net_kinetis_cfg_setup(). */
typedef struct
{
    net_kinetis_pins_t pins;
    net_kinetis_ref_clock_t ref_clock;
    bool disable_mpu;           /*!< true (default): switch off the system MPU, which otherwise
                                     blocks the ENET DMA from RAM (as NXP's SDK examples do). */
    pin_name_t phy_reset;       /*!< PHY reset pin (active low), HAL_PIN_NC if none (default). */
    uint8_t phy_addr;           /*!< PHY address 0..31, or NET_PHY_ADDR_AUTO (default) to scan. */
} net_kinetis_cfg_t;

/*! @brief Defaults for the MCU the SDK is built for. */
void net_kinetis_cfg_setup( net_kinetis_cfg_t *cfg );

/*!
 * @brief Fill @p drv for the on-chip ENET. The hardware is started by
 * net_init() (driver init callback). Only one instance exists.
 * @param[in] cfg Copied, may be discarded afterwards.
 */
void net_driver_kinetis( net_driver_t *drv, const net_kinetis_cfg_t *cfg );

/*! @brief The PHY found at init (address, identifier), for diagnostics. */
const net_phy_t *net_driver_kinetis_phy( void );

#ifdef __cplusplus
}
#endif

#endif // _NET_DRIVER_KINETIS_H
// ------------------------------------------------------------------------- END
