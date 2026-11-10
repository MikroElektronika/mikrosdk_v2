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
 * @file eth_bus_spi.h
 * @brief Ethernet transport SPI bus binding.
 * @details Implements eth_bus_ops_t on top of the mikroSDK SPI master driver.
 * Every device owns one eth_bus_spi_t (SPI master object + chip select), so
 * several controllers can share a SPI module or use different ones.
 * Other buses (I2C, UART, ...) follow the same pattern: a bus object, a
 * bus configuration, an eth_bus_ops_t and an eth_bus_<bus>_configure().
 */

#ifndef _ETH_BUS_SPI_H
#define _ETH_BUS_SPI_H

#ifdef __cplusplus
extern "C"{
#endif

#include "eth_transport.h"
#include "drv_spi_master.h"
#include <stdint.h>

/**
 * @addtogroup eth_transport
 * @{
 */

/**
 * @brief Map the SPI bus pins to a mikroBUS position.
 */
#define ETH_BUS_SPI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );

/**
 * @brief SPI bus configuration.
 */
typedef struct {
    pin_name_t miso;            // SPI MISO pin
    pin_name_t mosi;            // SPI MOSI pin
    pin_name_t sck;             // SPI clock pin
    pin_name_t cs;              // Chip select pin

    uint32_t speed;             // SPI clock speed in Hz
    spi_master_mode_t mode;     // SPI mode
} eth_bus_spi_cfg_t;

/**
 * @brief SPI bus object, one per device, must stay valid while the device is used.
 */
typedef struct {
    spi_master_t spi;           // SPI master object
    digital_out_t cs_out;       // Chip select pin
    pin_name_t cs;              // Chip select pin name, used for device selection
} eth_bus_spi_t;

/**
 * @brief SPI bus operations, referenced by eth_transport_t.bus_ops.
 */
extern eth_bus_ops_t eth_bus_spi_ops;

/**
 * @brief Initialize the SPI bus configuration.
 * @details All pins not connected, 1 MHz, SPI mode 0.
 * @param[out] cfg SPI bus configuration.
 * @return Nothing.
 */
void eth_bus_spi_cfg_setup( eth_bus_spi_cfg_t *cfg );

/**
 * @brief Open the SPI bus and attach it to an Ethernet transport instance.
 * @details Opens the SPI master, initializes the chip select pin and calls
 * eth_transport_configure() with @p eth_cfg. Controller drivers wrap this
 * function and assign their context to eth->driver_ctx.
 * @param[in,out] eth Ethernet transport instance.
 * @param[out] bus SPI bus object for this device.
 * @param[in] bus_cfg SPI bus configuration.
 * @param[in] eth_cfg Device configuration (reset pin, MAC, IP, duplex).
 * @return ETH_TRANSPORT_SUCCESS on success, ETH_TRANSPORT_ERROR otherwise.
 */
err_t eth_bus_spi_configure( eth_transport_t *eth, eth_bus_spi_t *bus,
                             eth_bus_spi_cfg_t *bus_cfg, eth_transport_cfg_t *eth_cfg );

/*! @} */ // eth_transport

#ifdef __cplusplus
}
#endif
#endif // _ETH_BUS_SPI_H

// ------------------------------------------------------------------------ END
