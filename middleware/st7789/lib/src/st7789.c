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
 * @file  st7789.c
 * @brief ST7789 controller source file.
 */

#include "st7789.h"
#include "st7789_cmd.h"

#ifdef __GNUC__
#include <me_built_in.h>
#endif
#ifdef __MIKROC__
#include "built_in.h"
#endif
#include "drv_digital_out.h"
#include "drv_port.h"
#include "delays.h"

/*!< Set SPI dummy write data. */
#define SPI_DUMMY 0x00

/**
 * @remark SPI object opened in st7789_init, API was
 * built for single display applications which covers most use-cases.
 */
static spi_master_t *display_spi;
/*!< CS pin handle. */
static digital_out_t pin_cs;
/*!< RST pin handle. */
static digital_out_t pin_rst;
/*!< DC pin handle. */
static digital_out_t pin_dc;
/*!< BCK pin handle. */
static digital_out_t pin_bck;

static uint16_t display_width;
static uint16_t display_height;

#define DATA_SELECT()    digital_out_high( &pin_dc )
#define COMMAND_SELECT() digital_out_low( &pin_dc )

#define CS_ACTIVE()      digital_out_low( &pin_cs )
#define CS_DEACTIVE()    digital_out_high( &pin_cs )

#define RESET_ACTIVE()   digital_out_low( &pin_rst )
#define RESET_DEACTIVE() digital_out_high( &pin_rst )

uint16_t st7789_get_display_width()
{
    return display_width;
}

uint16_t st7789_get_display_height()
{
    return display_height;
}

static void _st7789_begin_frame( gl_rectangle_t *rect )
{
    uint16_t start_column = rect->top_left.x;
    uint16_t end_column = rect->top_left.x + rect->width - 1;
    uint16_t start_page = rect->top_left.y;
    uint16_t end_page = rect->top_left.y + rect->height - 1;

    st7789_write_command( ST7789_CMD_CASET );
    st7789_write_param( Hi( start_column ) );
    st7789_write_param( Lo( start_column ) );
    st7789_write_param( Hi( end_column ) );
    st7789_write_param( Lo( end_column ) );

    st7789_write_command( ST7789_CMD_RASET );
    st7789_write_param( Hi( start_page ) );
    st7789_write_param( Lo( start_page ) );
    st7789_write_param( Hi( end_page ) );
    st7789_write_param( Lo( end_page ) );

    st7789_write_command( ST7789_CMD_RAMWR );

    CS_ACTIVE();
    DATA_SELECT();
}

static void _st7789_end_frame()
{
    CS_DEACTIVE();
}

static void _st7789_frame_data( gl_color_t color )
{
    uint8_t color_bytes[2];

    // RAMCTRL is configured with ENDIAN = 1 (little endian), send low byte first.
    color_bytes[0] = Lo( color );
    color_bytes[1] = Hi( color );
    spi_master_write( display_spi, color_bytes, 2 );
}

static void _st7789_fill( gl_rectangle_t *rect, gl_color_t color )
{
    uint32_t length = ( uint32_t )rect->width * ( uint32_t )rect->height;

    if ( !length )
        return;

    _st7789_begin_frame( rect );

    while ( length-- )
        _st7789_frame_data( color );

    _st7789_end_frame();
}

void st7789_init( st7789_t *ctx, st7789_cfg_t *cfg, gl_driver_t *__generic_ptr driver )
{
    spi_master_config_t spi_cfg;

    // Initialize communication pins.
    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck = cfg->sck;
    spi_cfg.miso = cfg->sdo;
    spi_cfg.mosi = cfg->sdi;

    spi_master_open( &ctx->spi, &spi_cfg );
    spi_master_set_default_write_data( &ctx->spi, SPI_DUMMY );
    spi_master_set_mode( &ctx->spi, SPI_MASTER_MODE_0 );
    spi_master_set_speed( &ctx->spi, 5000000 );

    display_spi = &ctx->spi;

    // Initialize control pins.
    digital_out_init( &pin_cs, cfg->cs );
    digital_out_init( &pin_rst, cfg->rst );
    digital_out_init( &pin_dc, cfg->rs );
    digital_out_init( &pin_bck, cfg->bck );
    CS_DEACTIVE();

    display_width = cfg->width;
    display_height = cfg->height;

    // Link Graphic Library driver interface.
    driver->display_width = cfg->width;
    driver->display_height = cfg->height;
    driver->fill_f = _st7789_fill;
    driver->begin_frame_f = _st7789_begin_frame;
    driver->frame_data_f = _st7789_frame_data;
    driver->end_frame_f = _st7789_end_frame;
}

void st7789_write_command( uint8_t command )
{
    CS_ACTIVE();
    COMMAND_SELECT();
    spi_master_write( display_spi, &command, 1 );
    CS_DEACTIVE();
}

void st7789_write_param( uint8_t param )
{
    CS_ACTIVE();
    DATA_SELECT();
    spi_master_write( display_spi, &param, 1 );
    CS_DEACTIVE();
}

void st7789_reset()
{
    RESET_ACTIVE();
    Delay_1ms();
    RESET_DEACTIVE();
    Delay_100ms();
    Delay_100ms();
}

void st7789_set_backlight( uint8_t intensity )
{
    digital_out_write( &pin_bck, intensity );
}

/**
 * @note Not implemented, Hardware does not support tp.
 */
static tp_err_t tp_st7789_process( tp_st7789_t *ctx )
{
    return TP_OK;
}

/**
 * @note Not implemented, Hardware does not support tp.
 */
static tp_event_t tp_st7789_press_detect( tp_st7789_t *ctx )
{
    return TP_EVENT_PRESS_NOT_DET;
}

/**
 * @note Not implemented, Hardware does not support tp.
 */
static void tp_st7789_gesture( tp_st7789_t *ctx, tp_event_t *event )
{
    *event = TP_EVENT_GEST_NONE;
}

/**
 * @note Not implemented, Hardware does not support tp.
 */
static void tp_st7789_coord( void *ctx, tp_touch_item_t *coord )
{
    coord->n_touches = 0;
    return;
}

tp_err_t tp_st7789_init( tp_st7789_t *ctx, tp_st7789_cfg_t *cfg, tp_drv_t *drv )
{
    drv->tp_press_detect_f = tp_st7789_press_detect;
    drv->tp_press_coordinates_f = tp_st7789_coord;
    drv->tp_gesture_f = tp_st7789_gesture;
    drv->tp_process_f = tp_st7789_process;
    return TP_OK;
}

void tp_st7789_cfg_setup( tp_st7789_cfg_t *cfg )
{
}

void tp_st7789_default_cfg( tp_st7789_t *ctx )
{
}

// ------------------------------------------------------------------------- END
