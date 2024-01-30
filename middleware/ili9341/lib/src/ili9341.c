/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  ili9341.c
 * @brief ILI9341 controller source file.
 */

#include "ili9341.h"

#ifdef __GNUC__
#include <me_built_in.h>
#endif
#ifdef __MIKROC__
#include "built_in.h"
#endif

static digital_out_t pin_rst;
static digital_out_t pin_cs;
static digital_out_t pin_rs;
static digital_out_t pin_wr;
static digital_out_t pin_rd;

static digital_out_t pin_up;
static digital_out_t pin_right;

#ifdef ILI9341_PIC32
static digital_out_t pin_left;
static digital_out_t pin_down;

static digital_in_t in_pin_up;
static digital_in_t in_pin_right;
static digital_in_t in_pin_left;
static digital_in_t in_pin_down;
#else
static digital_in_t  pin_left;
static digital_in_t  pin_down;
#endif

static port_t data_channel_0;
static port_t data_channel_1;

uint16_t display_width;
uint16_t display_height;

static uint8_t port_shift_8bit = 0;
static uint8_t port_shift_16bit_low = 0;
static uint8_t port_shift_16bit_high = 0;

uint16_t ili9341_get_display_width() {
    return display_width;
}

uint16_t ili9341_get_display_height() {
    return display_height;
}

void _ili9341_begin_frame( gl_rectangle_t *rect ) {
    uint16_t start_column = rect->top_left.x;
    uint16_t end_column = rect->top_left.x + rect->width - 1;
    uint16_t start_page = rect->top_left.y;
    uint16_t end_page = rect->top_left.y + rect->height - 1;

    ili9341_write_command( ILI9341_CMD_COLUMN_ADDRESS_SET );
    ili9341_write_param( Hi( start_column ) );
    ili9341_write_param( Lo( start_column ) );
    ili9341_write_param( Hi( end_column ) );
    ili9341_write_param( Lo( end_column ) );

    ili9341_write_command( ILI9341_CMD_PAGE_ADDRESS_SET );
    ili9341_write_param( Hi( start_page ) );
    ili9341_write_param( Lo( start_page ) );
    ili9341_write_param( Hi( end_page ) );
    ili9341_write_param( Lo( end_page ) );

    ili9341_write_command( ILI9341_CMD_MEMORY_WRITE );

    CS_ACTIVE();
    DATA_SELECT();
}

void _ili9341_end_frame() {
    CS_DEACTIVE();
}

void _fill_8bit_host_interface( gl_rectangle_t *rect, gl_color_t color ) {
    uint32_t length = ( uint32_t )rect->width * ( uint32_t )rect->height;
    uint32_t red_value = RED_OF( color );
    uint32_t green_value = GREEN_OF( color );
    uint32_t blue_value = BLUE_OF( color );

    if ( !length )
        return;

    _ili9341_begin_frame( rect );

    while ( length-- )
    {
        port_write( &data_channel_0, red_value );
        WRITE_STROBE();

        port_write( &data_channel_0, green_value );
        WRITE_STROBE();

        port_write( &data_channel_0, blue_value );
        WRITE_STROBE();
    }

    _ili9341_end_frame();
}

void _frame_data_8bit_host_interface( gl_color_t color ) {
    port_write( &data_channel_0, R_BITS( color ) );
    WRITE_STROBE();

    port_write( &data_channel_0, G_BITS( color ) );
    WRITE_STROBE();

    port_write( &data_channel_0, B_BITS( color ) );
    WRITE_STROBE();
}

void _fill_16bit_host_interface_single_channel( gl_rectangle_t *rect, gl_color_t color ) {
    uint32_t length = ( uint32_t )rect->width * ( uint32_t )rect->height;

    if ( !length )
        return;

    _ili9341_begin_frame( rect );

    port_write( &data_channel_0, color << port_shift_16bit_low );

    while( length-- )
    {
        WRITE_STROBE();
    }

    _ili9341_end_frame();
}

void _frame_data_16bit_host_interface_single_channel( gl_color_t color ) {
    port_write( &data_channel_0, color << port_shift_16bit_low );
    WRITE_STROBE();
}

void _fill_16bit_host_interface( gl_rectangle_t *rect, gl_color_t color ) {
    uint32_t length = ( uint32_t )rect->width * ( uint32_t )rect->height;

    if ( !length )
        return;

    _ili9341_begin_frame( rect );

    port_write( &data_channel_0, Lo( color ) << port_shift_16bit_low );
    port_write( &data_channel_1, Hi( color ) << port_shift_16bit_high );

    while( length-- )
    {
        WRITE_STROBE();
    }

    _ili9341_end_frame();
}

void _frame_data_16bit_host_interface( gl_color_t color ) {
    port_write( &data_channel_0, Lo( color ) << port_shift_16bit_low );
    port_write( &data_channel_1, Hi( color ) << port_shift_16bit_high );
    WRITE_STROBE();
}

void ili9341_init( ili9341_cfg_t *cfg, gl_driver_t *__generic_ptr driver, ili9341_t *ctx ) {
    digital_out_init( &pin_cs, cfg->cs );
    digital_out_init( &pin_rs, cfg->rs );
    digital_out_init( &pin_wr, cfg->wr );
    digital_out_init( &pin_rd, cfg->rd );
    digital_out_init( &pin_rst, cfg->rst );

    digital_out_high( &pin_cs );
    digital_out_high( &pin_rs );
    digital_out_high( &pin_wr );
    digital_out_high( &pin_rd );
    digital_out_low( &pin_rst );

    port_init( &data_channel_0, cfg->data_channel_0, cfg->data_channel_0_mask, GPIO_DIGITAL_OUTPUT );
    port_write( &data_channel_0, PORT_DEFAULT_VALUE );

    if ( ILI9341_HOST_INTERFACE_8BIT == cfg->host_interface ) {
        driver->fill_f = _fill_8bit_host_interface;
        driver->frame_data_f = _frame_data_8bit_host_interface;

        port_shift_8bit = 0;
        if ( DATA_PORT_NIBBLE_HIGH == cfg->data_channel_0_mask ) {
            port_shift_8bit = 8;
        }
    }

    if ( ILI9341_HOST_INTERFACE_16BIT == cfg->host_interface ) {
        if ( HAL_PORT_NC == cfg->data_channel_1 ) {
            driver->fill_f = _fill_16bit_host_interface_single_channel;
            driver->frame_data_f = _frame_data_16bit_host_interface_single_channel;

            port_shift_16bit_low = 0;
            if ( DATA_PORT_NIBBLE_HIGH == cfg->data_channel_0_mask ) {
                port_shift_16bit_low = 8;
            }
        } else {
            port_init( &data_channel_1, cfg->data_channel_1, cfg->data_channel_1_mask, GPIO_DIGITAL_OUTPUT );
            port_write( &data_channel_1, PORT_DEFAULT_VALUE );

            driver->fill_f = _fill_16bit_host_interface;
            driver->frame_data_f = _frame_data_16bit_host_interface;

            port_shift_16bit_low = 0;
            port_shift_16bit_high = 0;
            if ( DATA_PORT_NIBBLE_HIGH == cfg->data_channel_0_mask ) {
                port_shift_16bit_low = 8;
            }
            if ( DATA_PORT_NIBBLE_HIGH == cfg->data_channel_1_mask ) {
                port_shift_16bit_high = 8;
            }
        }
    }

    ili9341_backlight_control_init( cfg, ctx );
    ili9341_set_backlight_intensity( BACKLIGHT_DEFAULT_INTENSITY, ctx );

    if ( ILI9341_MODE_LANDSCAPE_UP == cfg->orientation || ILI9341_MODE_LANDSCAPE_DOWN == cfg->orientation ) {
        display_width = cfg->width;
        driver->display_width = cfg->width;
        display_height = cfg->height;
        driver->display_height = cfg->height;
    } else {
        display_width = cfg->height;
        driver->display_width = cfg->height;
        display_height = cfg->width;
        driver->display_height = cfg->width;
    }

    driver->begin_frame_f = _ili9341_begin_frame;
    driver->end_frame_f = _ili9341_end_frame;

    Delay_100ms();

    digital_out_high( &pin_rst );

    Delay_100ms();
    Delay_100ms();
}

void ili9341_write_command( uint8_t command ) {
    CS_ACTIVE();
    COMMAND_SELECT();

    port_write( &data_channel_0, command );
    WRITE_STROBE();
    CS_DEACTIVE();
}

void ili9341_write_param( uint8_t param ) {
    CS_ACTIVE();
    DATA_SELECT();

    port_write( &data_channel_0, param );
    WRITE_STROBE();
    CS_DEACTIVE();
}

void ili9341_default_cfg( ili9341_cfg_t *cfg ) {
    pwm_configure_default( &cfg->pwm_cfg );
}

void ili9341_backlight_control_init( ili9341_cfg_t *cfg, ili9341_t *ctx ) {
    pwm_open( &ctx->pwm, &cfg->pwm_cfg );
    pwm_set_freq( &ctx->pwm, cfg->pwm_cfg.freq_hz );
    pwm_start( &ctx->pwm );
}

void ili9341_set_backlight_intensity( float intensity, ili9341_t *ctx ) {
    ili9341_write_command( ILI9341_CMD_DISPLAY_OFF );
    pwm_set_duty( &ctx->pwm, intensity );
    ili9341_write_command( ILI9341_CMD_DISPLAY_ON );
}

void ili9341_rotate( ili9341_t *ctx, tp_rotate_t *rotate ) {
    uint16_t tmp = 0;
    ctx->rotate = (tp_rotate_t)rotate;

    ili9341_write_command( ILI9341_CMD_MEMORY_ACCESS_CONTROL );
    switch( ctx->rotate ){
        case TP_ROTATE_0 :
            ili9341_write_param( ILI9341_PARAM_1_NO_ROTATION );
            break;
        case TP_ROTATE_90 :
            ili9341_write_param( ILI9341_PARAM_1_ROTATE_90 );
            tmp = ctx->width;
            ctx->width = ctx->height;
            ctx->height = tmp;
            break;
        case TP_ROTATE_180 :
            ili9341_write_param( ILI9341_PARAM_1_ROTATE_180 );
            break;
        case TP_ROTATE_270 :
            ili9341_write_param( ILI9341_PARAM_1_ROTATE_270 );
            tmp = ctx->width;
            ctx->width = ctx->height;
            ctx->height = tmp;
            break;

        default :
            ili9341_write_param( ILI9341_PARAM_1_NO_ROTATION );
            break;
    }
}

// ------------------------------------------------------------------------- END
