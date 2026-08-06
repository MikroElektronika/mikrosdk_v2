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
 * @file spi_ethernet_wizip20.c
 * @brief SPI Ethernet WIZnet IP20 Driver.
 */

#include "spi_ethernet_wiz-ip20.h"
#include <delays.h>

void wizip20_cfg_setup( wizip20_cfg_t *cfg ) {
    cfg->rx = HAL_PIN_NC;
    cfg->tx = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->boot = HAL_PIN_NC;
    cfg->baud_rate = 115200;
}

uint8_t wizip20_configure( wizip20_t *dev, wizip20_cfg_t *cfg ) {
    uart_config_t uart_cfg;
    uart_configure_default( &uart_cfg );
    uart_cfg.rx_pin = cfg->rx;
    uart_cfg.tx_pin = cfg->tx;
    uart_cfg.baud_rate = cfg->baud_rate;

    if ( uart_open( &dev->uart, &uart_cfg ) != 0 )
        return 1;

    digital_out_init( &dev->rst_pin, cfg->rst );
    digital_out_init( &dev->boot_pin, cfg->boot );
    digital_out_high( &dev->boot_pin );
    digital_out_high( &dev->rst_pin );

    return 0;
}

void wizip20_hw_reset( wizip20_t *dev ) {
    digital_out_low( &dev->rst_pin );
    Delay_ms( 50 );
    digital_out_high( &dev->rst_pin );
    Delay_ms( 500 );
}

uint16_t wizip20_uart_write( wizip20_t *dev, uint8_t *buf, uint16_t len ) {
    return uart_write( &dev->uart, buf, len );
}

uint16_t wizip20_uart_read( wizip20_t *dev, uint8_t *buf, uint16_t max_len ) {
    return uart_read( &dev->uart, buf, max_len );
}
