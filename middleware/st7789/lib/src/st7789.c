/****************************************************************************
**
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file  st7789.c
 * @brief ST7789 controller source file.
 */

#include "st7789.h"

#ifdef __GNUC__
#include <me_built_in.h>
#endif
#ifdef __MIKROC__
#include "built_in.h"
#endif
#include "drv_digital_out.h"
#include "drv_port.h"
#include "delays.h"

static uint16_t display_width;
static uint16_t display_height;


uint16_t st7789_get_display_width()
{
    return display_width;
}

uint16_t st7789_get_display_height()
{
    return display_height;
}

void st7789_init( st7789_t * ctx, st7789_cfg_t * cfg, tp_drv_t * drv )
{

}

void st7789_write_command( uint8_t command )
{

}

void st7789_write_param( uint8_t param )
{

}

// ------------------------------------------------------------------------- END
