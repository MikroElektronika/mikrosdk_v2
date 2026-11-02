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
 * @file  gc9107_gl.c
 * @brief GC9107 Graphics Library adapter source file.
 */

#include "gc9107_gl.h"
#include "gc9107_cmd.h"
#include "gl.h"

#ifdef __GNUC__
#include <me_built_in.h>
#endif
#ifdef __MIKROC__
#include "built_in.h"
#endif
#include "drv_digital_out.h"
#include "drv_spi_master.h"

#define GC9107_FILL_CHUNK   64    // Number of pixels sent with one SPI write.

// Size of the controller memory, in pixels.
#define GC9107_RAM_WIDTH    128
#define GC9107_RAM_HEIGHT   128

// Position of the visible area in the controller memory, in the default orientation.
#define GC9107_PANEL_COLUMN 0
#define GC9107_PANEL_ROW    13

/**
 * @remark No context for display controller driver, because in most cases only
 * one display on board.
 */
static gc9107_t display;
static digital_out_t pin_cs;
static digital_out_t pin_dc;
static spi_master_t *spi;

static uint16_t display_width;
static uint16_t display_height;

static uint16_t native_width;
static uint16_t native_height;

static uint16_t offset_x;
static uint16_t offset_y;

static gl_driver_t *current_gl_driver = NULL;

#define DATA_SELECT()  digital_out_high( &pin_dc )
#define CS_ACTIVE()    digital_out_low( &pin_cs )
#define CS_DEACTIVE()  digital_out_high( &pin_cs )

static void spi_send( uint8_t *data, uint32_t length )
{
    spi_master_write( spi, data, length );
}

uint16_t gc9107_gl_get_display_width()
{
    return display_width;
}

uint16_t gc9107_gl_get_display_height()
{
    return display_height;
}

static void begin_frame( gl_rectangle_t *rect )
{
    uint16_t start_column = rect->top_left.x + offset_x;
    uint16_t end_column = rect->top_left.x + rect->width - 1 + offset_x;
    uint16_t start_page = rect->top_left.y + offset_y;
    uint16_t end_page = rect->top_left.y + rect->height - 1 + offset_y;

    gc9107_write_command( GC9107_CMD_CASET );
    gc9107_write_param( Hi( start_column ) );
    gc9107_write_param( Lo( start_column ) );
    gc9107_write_param( Hi( end_column ) );
    gc9107_write_param( Lo( end_column ) );

    gc9107_write_command( GC9107_CMD_RASET );
    gc9107_write_param( Hi( start_page ) );
    gc9107_write_param( Lo( start_page ) );
    gc9107_write_param( Hi( end_page ) );
    gc9107_write_param( Lo( end_page ) );

    gc9107_write_command( GC9107_CMD_RAMWR );

    CS_ACTIVE();
    DATA_SELECT();
}

static void end_frame()
{
    CS_DEACTIVE();
}

static void frame_data( gl_color_t color )
{
    uint8_t pixel[ 2 ];

    pixel[ 0 ] = Hi( color );   // High byte first.
    pixel[ 1 ] = Lo( color );   // Low byte second.

    spi_send( pixel, 2 );
}

static void fill( gl_rectangle_t *rect, gl_color_t color )
{
    uint32_t length = ( uint32_t )rect->width * ( uint32_t )rect->height;
    uint8_t buffer[ GC9107_FILL_CHUNK * 2 ];
    uint8_t high = Hi( color );
    uint8_t low = Lo( color );
    uint32_t chunk;
    uint32_t i;

    if ( !length )
    {
        return;
    }

    // Fill the buffer with the color (only as many pixels as needed).
    chunk = ( length < GC9107_FILL_CHUNK ) ? length : GC9107_FILL_CHUNK;

    for ( i = 0; i < chunk; i++ )
    {
        buffer[ i * 2 ] = high;
        buffer[ i * 2 + 1 ] = low;
    }

    begin_frame( rect );

    while ( length >= GC9107_FILL_CHUNK )
    {
        spi_send( buffer, GC9107_FILL_CHUNK * 2 );
        length -= GC9107_FILL_CHUNK;
    }

    if ( length )
    {
        spi_send( buffer, length * 2 );
    }

    end_frame();
}

static void set_orientation( uint8_t rotation )
{
    uint8_t madctl;
    uint8_t landscape;
    uint16_t column_offset;
    uint16_t row_offset;

    switch ( rotation )
    {
        case 1:  madctl = GC9107_MADCTL_MX | GC9107_MADCTL_MV; landscape = 1; break;   // 90 degrees.
        case 2:  madctl = GC9107_MADCTL_MY | GC9107_MADCTL_MX; landscape = 0; break;   // 180 degrees.
        case 3:  madctl = GC9107_MADCTL_MY | GC9107_MADCTL_MV; landscape = 1; break;   // 270 degrees.
        default: madctl = GC9107_MADCTL_DEFAULT; landscape = 0; break;                 // 0 degrees.
    }

    gc9107_write_command( GC9107_CMD_MADCTL );
    gc9107_write_param( madctl );

    // The visible area is smaller than the controller memory and does not start
    // at its beginning. When the order of an axis is reversed, the area sits at
    // the other end of the memory, so the window has to be shifted.
    column_offset = ( madctl & GC9107_MADCTL_MX ) ?
                    ( GC9107_RAM_WIDTH - ( GC9107_PANEL_COLUMN + native_width ) ) : GC9107_PANEL_COLUMN;
    row_offset = ( madctl & GC9107_MADCTL_MY ) ?
                 ( GC9107_RAM_HEIGHT - ( GC9107_PANEL_ROW + native_height ) ) : GC9107_PANEL_ROW;

    if ( madctl & GC9107_MADCTL_MV )
    {
        offset_x = row_offset;
        offset_y = column_offset;
    }
    else
    {
        offset_x = column_offset;
        offset_y = row_offset;
    }

    display_width = landscape ? native_height : native_width;
    display_height = landscape ? native_width : native_height;

    if ( current_gl_driver )
    {
        current_gl_driver->display_width = display_width;
        current_gl_driver->display_height = display_height;
    }
}

void gc9107_gl_init( gc9107_cfg_t *cfg, gl_driver_t *driver )
{
    gc9107_init( &display, cfg );
    gc9107_configure();

    spi = gc9107_get_spi();

    digital_out_init( &pin_cs, cfg->cs );
    digital_out_init( &pin_dc, cfg->rs );
    CS_DEACTIVE();
    DATA_SELECT();

    driver->fill_f = fill;
    driver->begin_frame_f = begin_frame;
    driver->end_frame_f = end_frame;
    driver->frame_data_f = frame_data;

    current_gl_driver = driver;

    native_width = cfg->width;
    native_height = cfg->height;

    set_orientation( 0 );

    gc9107_set_backlight( 1 );
}

void gc9107_gl_write_pixels( uint8_t *data, uint32_t length )
{
    spi_send( data, length );
}

void gc9107_gl_rotate( uint8_t rotation )
{
    set_orientation( rotation );

    if ( current_gl_driver )
    {
        // Graphic library keeps its own copy of the driver, so update it.
        gl_set_driver( current_gl_driver );
    }
}

void gc9107_gl_display_power( uint8_t state )
{
    if ( state )
    {
        gc9107_write_command( GC9107_CMD_DISPON );
    }
    else
    {
        gc9107_write_command( GC9107_CMD_DISPOFF );
    }
}