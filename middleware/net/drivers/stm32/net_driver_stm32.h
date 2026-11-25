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
 * @file net_driver_stm32.h
 * @brief net_driver_t for the Ethernet MAC of STM32F107, F2x7, F4x7/F4x9 and
 * F74x-F77x (RMII).
 * @details Polled (no interrupts): received frames are taken from a ring of
 * DMA descriptors by net_poll(). The PHY is handled through net_phy.h.
 * Pins and the PHY reference clock are set up by the driver through the
 * mikroSDK GPIO layer, no vendor HAL needed. The family (NET_STM32_F1/F2/F4/F7)
 * and the default board wiring come from the build (middleware/net/CMakeLists.txt).
 *
 * Board wiring, as in the mikroSDK boards and MCU cards:
 *   PA1 REF_CLK, PA2 MDIO, PA7 CRS_DV, PC1 MDC, PC4 RXD0, PC5 RXD1, and
 *   TX_EN/TXD0/TXD1 on PB11/PB12/PB13 or (mikromedia 7 / Plus) PG11/PG13/PG14;
 *   the 50 MHz reference clock of the PHY from MCO1 on PA8 (default) or from
 *   an oscillator on the board.
 *
 * @code
 * static net_driver_t drv;
 * net_stm32_cfg_t eth_cfg;
 * net_stm32_cfg_setup( &eth_cfg );   // board defaults
 * net_driver_stm32( &drv, &eth_cfg );
 * cfg.driver = &drv;                 // net_config_t, then net_init()
 * @endcode
 */

#ifndef _NET_DRIVER_STM32_H
#define _NET_DRIVER_STM32_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_driver.h"
#include "net_phy.h"
#include "drv_digital_out.h"

/*! Receive and transmit buffers (one frame each, 1536 bytes). */
#ifndef NET_STM32_RX_BUFFERS
#define NET_STM32_RX_BUFFERS 8
#endif
#ifndef NET_STM32_TX_BUFFERS
#define NET_STM32_TX_BUFFERS 4
#endif

/*! @brief Pins of TX_EN, TXD0, TXD1. */
typedef enum
{
    NET_STM32_TX_PINS_PB11_PB12_PB13 = 0,   /*!< Most boards and MCU cards. */
    NET_STM32_TX_PINS_PG11_PG13_PG14        /*!< mikromedia 7 / mikromedia Plus for STM32F4/F7.
                                                 Packages without port G use PB11-PB13. */
} net_stm32_tx_pins_t;

/*! @brief Source of the PHY's 50 MHz RMII reference clock. */
typedef enum
{
    NET_STM32_REF_CLOCK_MCO = 0,    /*!< MCO1 on PA8 (F1: MCO, system clock), see mco_div. */
    NET_STM32_REF_CLOCK_BOARD       /*!< Oscillator on the board: PA8 is left alone. */
} net_stm32_ref_clock_t;

/*! @brief Driver configuration, see net_stm32_cfg_setup(). */
typedef struct
{
    net_stm32_tx_pins_t tx_pins;
    net_stm32_ref_clock_t ref_clock;
    uint8_t mco_div;            /*!< F2/F4/F7: MCO1 = main PLL / mco_div (2..5) must give 50 MHz.
                                     Defaults as the boards are set up: F2 2, F4 3, F7 4. */
    pin_name_t phy_reset;       /*!< PHY reset pin (active low), HAL_PIN_NC if none (default). */
    uint8_t phy_addr;           /*!< PHY address 0..31, or NET_PHY_ADDR_AUTO (default) to scan. */
} net_stm32_cfg_t;

/*! @brief Defaults for the board the SDK is built for. */
void net_stm32_cfg_setup( net_stm32_cfg_t *cfg );

/*!
 * @brief Fill @p drv for the on-chip Ethernet MAC. The hardware is started by
 * net_init() (driver init callback); init fails when the PHY gives no
 * reference clock or does not answer. Only one instance exists.
 * @param[in] cfg Copied, may be discarded afterwards.
 */
void net_driver_stm32( net_driver_t *drv, const net_stm32_cfg_t *cfg );

/*! @brief The PHY found at init (address, identifier), for diagnostics. */
const net_phy_t *net_driver_stm32_phy( void );

#ifdef __cplusplus
}
#endif

#endif // _NET_DRIVER_STM32_H
// ------------------------------------------------------------------------- END
