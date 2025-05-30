/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
 * @file  drv_port.c
 * @brief Port driver implementation.
 */

#include "drv_port.h"

err_t port_init( port_t *port, port_name_t name, port_size_t mask,
                                                pin_direction_t direction )
{
    if ( !port )
        return PORT_ERROR;

    if ( ( PIN_DIRECTION_DIGITAL_INPUT != direction ) &&
         ( PIN_DIRECTION_DIGITAL_OUTPUT != direction ) ) {
        return PORT_ERROR;
    }

    if ( HAL_PORT_NC != name )
    {
        port->name = name;
        hal_gpio_configure_port( &port->port, name, mask, (hal_gpio_direction_t)direction );
    } else {
        return PORT_ERROR;
    }
}

#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)
err_t port_write( port_t *port, port_size_t value )
{
    if ( port->port.base )
    {
        hal_gpio_write_port_output( &port->port, value );
    } else {
        return PORT_ERROR;
    }
}
#endif

#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)
port_size_t port_read_input( port_t *port )
{
    if ( port->port.base )
    {
        return hal_gpio_read_port_input( &port->port );
    } else {
        return 0;
    }
}
#endif

#if (FLATTEN_ME_LEVEL < FLATTEN_ME_LEVEL_HIGH)
port_size_t port_read_output( port_t *port )
{
    if ( port->port.base )
    {
        return hal_gpio_read_port_output( &port->port );
    } else {
        return 0;
    }
}
#endif

// ------------------------------------------------------------------------- END
