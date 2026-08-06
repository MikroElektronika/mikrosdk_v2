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
 * @file spi_ethernet_wiz-ip20.h
 * @brief SPI Ethernet WIZnet IP20 Driver.
 */

#ifndef SPI_ETHERNET_WIZIP20_H
#define SPI_ETHERNET_WIZIP20_H

#include "drv_digital_out.h"
#include "drv_uart.h"
#include "drv_spi_master.h"
#include <stdint.h>

#define WIZIP20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rx    = MIKROBUS( mikrobus, MIKROBUS_RX );  \
    cfg.tx    = MIKROBUS( mikrobus, MIKROBUS_TX );  \
    cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.boot  = MIKROBUS( mikrobus, MIKROBUS_PWM );

typedef struct {
    pin_name_t rx;
    pin_name_t tx;
    pin_name_t rst;
    pin_name_t boot;
    uint32_t   baud_rate;
} wizip20_cfg_t;

typedef struct {
    uart_t   uart;
    digital_out_t rst_pin;
    digital_out_t boot_pin;
} wizip20_t;

void    wizip20_cfg_setup( wizip20_cfg_t *cfg );
uint8_t wizip20_configure( wizip20_t *dev, wizip20_cfg_t *cfg );
void    wizip20_hw_reset( wizip20_t *dev );

uint16_t wizip20_uart_write( wizip20_t *dev, uint8_t *buf, uint16_t len );
uint16_t wizip20_uart_read( wizip20_t *dev, uint8_t *buf, uint16_t max_len );

#endif
