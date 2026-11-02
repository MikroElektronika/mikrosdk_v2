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
 * @file  gc9107.c
 * @brief GC9107 controller source file.
 */

#include "gc9107.h"
#include "gc9107_cmd.h"

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
 * @remark Configuration copy for display controller driver, API was
 * built for single display applications which covers most use-cases.
 */
static spi_master_t display_spi;

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

/**
 * @brief Gamma set 0 values, from the MikroE IPS Display 3 Click library.
 */
static uint8_t gamma0[ 14 ] = { 0x05, 0x1D, 0x51, 0x2F, 0x85, 0x2A, 0x11,
                                0x62, 0x00, 0x07, 0x07, 0x0F, 0x08, 0x1F };

/**
 * @brief Gamma set 1 values, from the MikroE IPS Display 3 Click library.
 */
static uint8_t gamma1[ 14 ] = { 0x2E, 0x41, 0x62, 0x56, 0xA5, 0x3A, 0x3F,
                                0x60, 0x0F, 0x07, 0x0A, 0x18, 0x18, 0x1D };

/**
 * @brief Send a command followed by its parameters.
 */
static void write_command_params( uint8_t command, uint8_t *params, uint8_t length )
{
    gc9107_write_command( command );

    for ( uint8_t i = 0; i < length; i++ )
    {
        gc9107_write_param( params[ i ] );
    }
}

uint16_t gc9107_get_display_width()
{
    return display_width;
}

uint16_t gc9107_get_display_height()
{
    return display_height;
}

void gc9107_init( gc9107_t *ctx, gc9107_cfg_t *cfg )
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

    display_spi = ctx->spi;

    // Initialize control pins.
    digital_out_init( &pin_cs, cfg->cs );
    digital_out_init( &pin_rst, cfg->rst );
    digital_out_init( &pin_dc, cfg->rs );
    digital_out_init( &pin_bck, cfg->bck );
    CS_DEACTIVE();

    // Store display size.
    ctx->width = cfg->width;
    ctx->height = cfg->height;
    display_width = cfg->width;
    display_height = cfg->height;
}

void gc9107_write_command( uint8_t command )
{
    CS_ACTIVE();
    COMMAND_SELECT();
    spi_master_write( &display_spi, &command, 1 );
    CS_DEACTIVE();
}

void gc9107_write_param( uint8_t param )
{
    CS_ACTIVE();
    DATA_SELECT();
    spi_master_write( &display_spi, &param, 1 );
    CS_DEACTIVE();
}

spi_master_t *gc9107_get_spi( void )
{
    return &display_spi;
}

void gc9107_reset()
{
    RESET_DEACTIVE();
    Delay_10ms();
    RESET_ACTIVE();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    RESET_DEACTIVE();
    Delay_100ms();
    Delay_10ms();
    Delay_10ms();
}

void gc9107_configure()
{
    uint8_t param;

    gc9107_reset();

    // Enable inner registers.
    gc9107_write_command( GC9107_CMD_IREGEN1 );
    gc9107_write_command( GC9107_CMD_IREGEN2 );

    param = 0xC0;
    write_command_params( GC9107_CMD_B0, &param, 1 );
    param = 0x80;
    write_command_params( GC9107_CMD_B1, &param, 1 );
    param = 0x2F;
    write_command_params( GC9107_CMD_B2, &param, 1 );
    param = 0x03;
    write_command_params( GC9107_CMD_B3, &param, 1 );
    param = 0x01;
    write_command_params( GC9107_CMD_B7, &param, 1 );
    param = 0x19;
    write_command_params( GC9107_CMD_B6, &param, 1 );
    param = 0xC8;
    write_command_params( GC9107_CMD_CPRRGB565, &param, 1 );
    param = 0x0F;
    write_command_params( GC9107_CMD_AB, &param, 1 );

    // 16 bit pixel format.
    param = GC9107_COLMOD_16BIT;
    write_command_params( GC9107_CMD_COLMOD, &param, 1 );

    param = 0x04;
    write_command_params( GC9107_CMD_INVCTRL, &param, 1 );
    param = 0x07;
    write_command_params( GC9107_CMD_FRS, &param, 1 );
    param = 0x08;
    write_command_params( GC9107_CMD_B8, &param, 1 );
    param = 0x5A;
    write_command_params( GC9107_CMD_VREGCTL, &param, 1 );
    param = 0x23;
    write_command_params( GC9107_CMD_VGHSET, &param, 1 );
    param = 0x47;
    write_command_params( GC9107_CMD_VGLSET, &param, 1 );
    param = 0x99;
    write_command_params( GC9107_CMD_VGHVGLCLK, &param, 1 );
    param = 0x30;
    write_command_params( GC9107_CMD_C6, &param, 1 );
    param = 0x1F;
    write_command_params( GC9107_CMD_C7, &param, 1 );

    // Gamma control.
    write_command_params( GC9107_CMD_SETGAMMA0, gamma0, 14 );
    write_command_params( GC9107_CMD_SETGAMMA1, gamma1, 14 );

    param = GC9107_MADCTL_DEFAULT;
    write_command_params( GC9107_CMD_MADCTL, &param, 1 );

    // Exit sleep mode.
    gc9107_write_command( GC9107_CMD_SLPOUT );
    Delay_100ms();
    Delay_10ms();
    Delay_10ms();

    // Turn off display inversion and turn on display.
    gc9107_write_command( GC9107_CMD_INVOFF );
    gc9107_write_command( GC9107_CMD_DISPON );
    Delay_100ms();
}

void gc9107_set_backlight( uint8_t intensity )
{
    digital_out_write( &pin_bck, intensity );
}

// ------------------------------------------------------------------------- END
