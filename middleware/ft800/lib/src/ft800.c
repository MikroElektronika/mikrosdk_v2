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
 * @file  ft800.c
 * @brief FT800 controller source file.
 */

#include "ft800.h"
#include "ft800_cmd.h"
#include "ft800_reg.h"
#include "ft800_const.h"
#include "ft800_struct.h"


const ft800_controller_t FT800_CONTROLLER =
{
    {
        { 0x00, TP_EVENT_GEST_NONE },
        { FT800_EVENT_GEST_LEFT, TP_EVENT_GEST_LEFT },
        { FT800_EVENT_GEST_RIGHT, TP_EVENT_GEST_RIGHT },
        { FT800_EVENT_GEST_UP, TP_EVENT_GEST_UP },
        { FT800_EVENT_GEST_DOWN, TP_EVENT_GEST_DOWN },
        { FT800_EVENT_GEST_ZOOM_IN, TP_EVENT_GEST_ZOOM_IN },
        { FT800_EVENT_GEST_ZOOM_OUT, TP_EVENT_GEST_ZOOM_OUT }
    }
};

void ft800_cfg_setup( ft800_cfg_t *cfg, const ft800_controller_t *controller )
{
    spi_master_select_device( cfg->cs_pin );

    cfg->in_pin = HAL_PIN_NC;
    cfg->controller = controller;
}

void ft800_write_data( ft800_t *ctx,ft800_cfg_t *cfg, uint32_t address, uint32_t value, \
     uint8_t length )
{
    uint8_t data[ 7 ];

    spi_master_select_device( cfg->cs_pin );

    if ( FT800_DATA_LENGTH_BYTES_3 == length )
    {
        if ( 0x00 == ( uint8_t )value )
        {
            data[ 0 ] = 0x00;
            data[ 1 ] = 0x00;
            data[ 2 ] = 0x00;

            spi_master_write( &ctx->spi_master, data, \
                FT800_SPI_SEND_DATA_LENGTH_3 );
        }
        else
        {
            data[ 0 ] = ( ( uint8_t )value & FT800_SELECT_LSB_BITS_6 ) | \
            FT800_SENT_COMMAND_LABEL;
            data[ 1 ] = 0x00;
            data[ 2 ] = 0x00;

            spi_master_write( &ctx->spi_master, data, \
            FT800_SPI_SEND_DATA_LENGTH_3 );
        }
    }
    else if ( FT800_DATA_LENGTH_BYTES_1 == length )
    {
        data[ 0 ] = ( uint8_t )( ( ( address >> FT800_OFFSET_SENT_ADDRESS_BYTES_2 ) \
        & FT800_SELECT_LSB_BITS_6 ) | FT800_SENT_DATA_LABEL );
        data[ 1 ] = ( uint8_t )( ( address >> FT800_OFFSET_SENT_ADDRESS_BYTES_1 ) \
        & FT800_SELECT_BYTE );
        data[ 2 ] = ( uint8_t )( address & FT800_SELECT_BYTE );
        data[ 3 ] = ( uint8_t )value;

        spi_master_write( &ctx->spi_master, data, FT800_SPI_SEND_DATA_LENGTH_4 );
    }
    else if ( FT800_DATA_LENGTH_BYTES_2 == length )
    {
        data[ 0 ] = ( uint8_t )( ( ( address >> FT800_OFFSET_SENT_ADDRESS_BYTES_2 ) \
        & FT800_SELECT_LSB_BITS_6 ) | FT800_SENT_DATA_LABEL );
        data[ 1 ] = ( uint8_t )( ( address >> FT800_OFFSET_SENT_ADDRESS_BYTES_1 ) & \
        FT800_SELECT_BYTE );
        data[ 2 ] = ( uint8_t )( address & FT800_SELECT_BYTE );
        data[ 3 ] = ( uint8_t )( value & FT800_SELECT_BYTE );
        data[ 4 ] = ( uint8_t )( ( value >> FT800_OFFSET_SENT_ADDRESS_BYTES_1 ) & \
        FT800_SELECT_BYTE );

        spi_master_write( &ctx->spi_master, data, FT800_SPI_SEND_DATA_LENGTH_5 );
    }
    else if ( FT800_DATA_LENGTH_BYTES_4 == length )
    {
        data[ 0 ] = ( uint8_t )( ( ( address >> FT800_OFFSET_SENT_ADDRESS_BYTES_2 ) \
        & FT800_SELECT_LSB_BITS_6 ) | FT800_SENT_DATA_LABEL);
        data[ 1 ] = ( uint8_t )( ( address >> FT800_OFFSET_SENT_ADDRESS_BYTES_1 ) & \
        FT800_SELECT_BYTE );
        data[ 2 ] = ( uint8_t )( address & FT800_SELECT_BYTE );
        data[ 3 ] = ( uint8_t )( value & FT800_SELECT_BYTE );
        data[ 4 ] = ( uint8_t )( ( value >> FT800_OFFSET_SENT_ADDRESS_BYTES_1 ) & \
        FT800_SELECT_BYTE );
        data[ 5 ] = ( uint8_t )( ( value >> FT800_OFFSET_SENT_ADDRESS_BYTES_2 ) & \
        FT800_SELECT_BYTE );
        data[ 6 ] = ( uint8_t )( ( value >> FT800_OFFSET_SENT_ADDRESS_BYTES_3 ) & \
        FT800_SELECT_BYTE );

        spi_master_write( &ctx->spi_master, data, FT800_SPI_SEND_DATA_LENGTH_7 );
    }

    spi_master_deselect_device( cfg->cs_pin );
}

uint32_t ft800_read_data( ft800_t *ctx, ft800_cfg_t *cfg, uint32_t address, \
         uint8_t length )
{
    uint8_t tx_data[ FT800_TX_DATA_BUFF ];
    uint8_t rx_data[ FT800_RX_DATA_BUFF ];

    spi_master_select_device( cfg->cs_pin );

    if ( FT800_DATA_LENGTH_BYTES_1 == length )
    {
        tx_data[ 0 ] = ( uint8_t )( ( address >> \
        FT800_OFFSET_RECEIVED_ADDRESS_BYTES_2 ) & FT800_RECEIVE_DATA_LABEL );
        tx_data[ 1 ] = ( uint8_t )( ( address >> \
        FT800_OFFSET_RECEIVED_ADDRESS_BYTES_1 ) & FT800_SELECT_BYTE );
        tx_data[ 2 ] = ( uint8_t )( address & FT800_SELECT_BYTE );

        spi_master_write_then_read( &ctx->spi_master, tx_data, \
        FT800_SPI_SEND_DATA_LENGTH_3, rx_data, FT800_SPI_RECEIVE_DATA_LENGTH_2 );
        spi_master_deselect_device( cfg->cs_pin );

        return rx_data[ 1 ];
    }
    else if ( FT800_DATA_LENGTH_BYTES_2 == length )
    {
        uint16_t result_16;
        tx_data[ 0 ] = ( uint8_t )( ( address >> \
        FT800_OFFSET_RECEIVED_ADDRESS_BYTES_2 ) & FT800_RECEIVE_DATA_LABEL );
        tx_data[ 1 ] = ( uint8_t )( ( address >> \
        FT800_OFFSET_RECEIVED_ADDRESS_BYTES_1 ) & FT800_SELECT_BYTE );
        tx_data[ 2 ] = ( uint8_t )( address & FT800_SELECT_BYTE );

        spi_master_write_then_read( &ctx->spi_master, tx_data, \
        FT800_SPI_SEND_DATA_LENGTH_3, rx_data, FT800_SPI_RECEIVE_DATA_LENGTH_3 );
        spi_master_deselect_device( cfg->cs_pin );

        result_16 = ( rx_data[ 2 ] << FT800_OFFSET_RECEIVED_DATA_BYTES_1 ) | \
        rx_data[ 1 ];

        return result_16;
    }
    else if ( FT800_DATA_LENGTH_BYTES_4 == length )
    {
        uint32_t result_32;
        tx_data[ 0 ] = ( uint8_t )( ( address >> \
        FT800_OFFSET_RECEIVED_ADDRESS_BYTES_2 ) & FT800_RECEIVE_DATA_LABEL );
        tx_data[ 1 ] = ( uint8_t )( ( address >> \
        FT800_OFFSET_RECEIVED_ADDRESS_BYTES_1 ) & FT800_SELECT_BYTE );
        tx_data[ 2 ] = ( uint8_t )( address & FT800_SELECT_BYTE );

        spi_master_write_then_read( &ctx->spi_master, tx_data, \
        FT800_SPI_SEND_DATA_LENGTH_3, rx_data, FT800_SPI_RECEIVE_DATA_LENGTH_5 );
        spi_master_deselect_device( cfg->cs_pin );

        result_32 = ( rx_data[ 4 ] << FT800_OFFSET_RECEIVED_DATA_BYTES_3 ) | \
        ( rx_data[ 3 ] << FT800_OFFSET_RECEIVED_DATA_BYTES_2 ) | ( rx_data[ 2 ] \
        << FT800_OFFSET_RECEIVED_DATA_BYTES_1 ) | rx_data[ 1 ];

        return result_32;
    }
}

void ft800_default_cfg( ft800_cfg_t *cfg )
{
    spi_master_configure_default( &cfg->spi_master_cfg );
    cfg->spi_master_cfg.sck = cfg->sck_pin;
    cfg->spi_master_cfg.miso = cfg->miso_pin;
    cfg->spi_master_cfg.mosi = cfg->mosi_pin;
    cfg->spi_master_cfg.speed = FT800_SPI_SPEED;
    cfg->spi_master_cfg.mode = SPI_MASTER_MODE_0;
    cfg->spi_master_cfg.default_write_data = 0x00;
}

void ft800_cfg( ft800_t *ctx, ft800_cfg_t *cfg )
{
    ft800_write_data( ctx, cfg, FT800_CMD_ADDRESS, FT800_ACTIVE, \
    FT800_DATA_LENGTH_BYTES_3 );
    Delay_ms( 20 );
    ft800_write_data( ctx, cfg, FT800_CMD_ADDRESS, FT800_CLKEXT, \
    FT800_DATA_LENGTH_BYTES_3 );
    Delay_ms( 20 );
    ft800_write_data( ctx, cfg, FT800_CMD_ADDRESS, FT800_CLK48M, \
    FT800_DATA_LENGTH_BYTES_3 );
    Delay_ms( 20 );
    ft800_write_data( ctx, cfg, FT800_REG_GPIO, 0x00, FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_PCLK, 0x00, FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_HCYCLE, FT800_HCYCLE_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_HOFFSET, FT800_HOFFSET_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_HSYNC0, 0, FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_HSYNC1, FT800_HSYNC1_VALUE , \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_VCYCLE, FT800_VCYCLE_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_VOFFSET, FT800_VOFFSET_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_VSYNC0, 0, FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_VSYNC1, FT800_VSYNC1_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_PCLK_POL, FT800_PCLK_POL_VALUE ,\
    FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_HSIZE, FT800_HSIZE_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_VSIZE, FT800_VSIZE_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_CSPREAD, 0, FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_RAM_DL + 0, FT800_CLEAR_COLOR_RGB( \
    FT800_RGB_INIT_VALUE, FT800_RGB_INIT_VALUE, FT800_RGB_INIT_VALUE ), \
    FT800_DATA_LENGTH_BYTES_4 );
    ft800_write_data( ctx, cfg, FT800_RAM_DL + FT800_RAM_DL_OFFSET_4, FT800_CLEAR( \
    FT800_CLR_BUFF_MASK, FT800_CLR_BUFF_MASK, FT800_CLR_BUFF_MASK ), \
    FT800_DATA_LENGTH_BYTES_4 );
    ft800_write_data( ctx, cfg, FT800_RAM_DL + FT800_RAM_DL_OFFSET_8, FT800_DISPLAY(), \
    FT800_DATA_LENGTH_BYTES_4 );
    ft800_write_data( ctx, cfg, FT800_REG_DLSWAP, FT800_DLSWAP_VALUE, \
    FT800_DATA_LENGTH_BYTES_4 );
    ft800_write_data( ctx, cfg, FT800_REG_GPIO_DIR, FT800_GPIO_DIR_VALUE, \
    FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_GPIO, FT800_GPIO_VALUE, \
    FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_PWM_HZ, FT800_PWM_HZ_VALUE, \
    FT800_DATA_LENGTH_BYTES_2 );
    ft800_write_data( ctx, cfg, FT800_REG_PWM_DUTY, FT800_PWM_DUTY_VALUE, \
    FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_PCLK, FT800_PCLK_VALUE, \
    FT800_DATA_LENGTH_BYTES_1 );
}

/**
 * @note @b FT800 hardware does not support gestures.
 */
void ft800_gesture( ft800_t* ctx, tp_event_t * event )
{
    *event = TP_EVENT_GEST_NONE;
}

tp_event_t ft800_press_detect( ft800_t* ctx )
{
    return ctx->press_det;
}

void ft800_press_coordinates( ft800_t *ctx, tp_touch_item_t *touch_item )
{
    touch_item->n_touches = FT800_TOUCH_NUM;
    touch_item->point[ 0 ] = ctx->touch.point[ 0 ];
}

void ft800_init( ft800_t *ctx, ft800_cfg_t *cfg, tp_drv_t *drv )
{
    digital_out_init( &ctx->cs_pin, cfg->cs_pin );
    digital_out_init( &ctx->pd_pin, cfg->pd_pin );

    if ( SPI_MASTER_SUCCESS == spi_master_open( &ctx->spi_master, \
    &cfg->spi_master_cfg ) )
    {
        spi_master_set_chip_select_polarity( \
        SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW );
    }

    spi_master_set_speed( &ctx->spi_master, cfg->spi_master_cfg.speed );

    digital_out_low( &ctx->pd_pin );
    Delay_ms( 20 );
    digital_out_high( &ctx->pd_pin );
    Delay_ms( 20 );

    ft800_cfg( ctx, cfg );

    ft800_init_touch_screen( ctx, cfg, true );

    drv->tp_press_detect_f      = ft800_press_detect;
    drv->tp_press_coordinates_f = ft800_press_coordinates;
    drv->tp_gesture_f           = ft800_gesture;
    drv->tp_process_f           = ft800_process;
}

void ft800_init_touch_screen( ft800_t *ctx, ft800_cfg_t *cfg, bool run_calibration )
{
    uint16_t cmdOffset = 0;

    ft800_write_data( ctx, cfg, FT800_REG_TOUCH_MODE, 0x00, FT800_DATA_LENGTH_BYTES_1 );

    Delay_ms( 10 );

    if ( run_calibration ) {
        ft800_cmd( ctx, cfg, FT800_CMD_DLSTART, &cmdOffset );
        ft800_cmd( ctx, cfg, FT800_CLEAR_COLOR_RGB( 0, 0, 0 ), &cmdOffset );
        ft800_cmd( ctx, cfg, FT800_CLEAR( FT800_CLR_BUFF_MASK , FT800_CLR_BUFF_MASK , \
        FT800_CLR_BUFF_MASK  ), &cmdOffset );
        ft800_cmd_text( ctx, cfg, &cmdOffset, FT800_CALIBRATE_TEXT_X, \
        FT800_CALIBRATE_TEXT_Y, FT800_CALIBRATE_TEXT_FONT, 0, \
        "Touch the dots to calibrate" );
        ft800_cmd( ctx, cfg, FT800_CMD_CALIBRATE, &cmdOffset );
        ft800_cmd( ctx, cfg, FT800_CMD_SWAP, &cmdOffset );

        ft800_write_data( ctx, cfg, FT800_REG_CMD_WRITE, cmdOffset, \
        FT800_DATA_LENGTH_BYTES_2 );

        ft800_wait_coprocessor( ctx, cfg );

        Delay_ms( 100 );
    }

    ft800_write_data( ctx, cfg, FT800_REG_TOUCH_MODE,FT800_TOUCH_ACTIVATION_VALUE, \
    FT800_DATA_LENGTH_BYTES_1 );
    ft800_write_data( ctx, cfg, FT800_REG_TOUCH_TAG, 0x00, FT800_DATA_LENGTH_BYTES_1 );
}

tp_err_t ft800_process( ft800_t *ctx, ft800_cfg_t *cfg )
{
    tp_err_t status;

    status = ft800_read_press_coordinates( ctx, cfg );

    return status;
}

tp_err_t ft800_read_press_coordinates( ft800_t *ctx, ft800_cfg_t *cfg )
{
    uint32_t position = ft800_read_data( ctx, cfg, FT800_REG_TOUCH_SCREEN_XY, \
    FT800_DATA_LENGTH_BYTES_4 );

    if ( FT800_REG_TOUCH_PRESS != position )
    {
        ctx->touch.point[ 0 ].coord_x = position >> \
        FT800_OFFSET_READ_COORD_BYTES_2;
        ctx->touch.point[ 0 ].coord_y = position & FT800_READ_COORD_MASK;
        ctx->press_det = TP_EVENT_PRESS_DET;
    }
    else
    {
        ctx->touch.point[ 0 ].coord_x = 0;
        ctx->touch.point[ 0 ].coord_y = 0;
        ctx->press_det = TP_EVENT_PRESS_NOT_DET;
    }

    return TP_OK;
}

void ft800_wait_coprocessor( ft800_t *ctx, ft800_cfg_t *cfg )
{
    uint16_t read_buff = ft800_read_data( ctx, cfg, FT800_REG_CMD_READ, \
    FT800_DATA_LENGTH_BYTES_2 );
    uint16_t write_buff = ft800_read_data( ctx, cfg, FT800_REG_CMD_WRITE, \
    FT800_DATA_LENGTH_BYTES_2 );

    while( read_buff != write_buff )
    {
        read_buff = ft800_read_data( ctx, cfg, FT800_REG_CMD_READ, \
        FT800_DATA_LENGTH_BYTES_2 );
        write_buff = ft800_read_data( ctx, cfg, FT800_REG_CMD_WRITE, \
        FT800_DATA_LENGTH_BYTES_2 );
    }
}

void ft800_write_ram_g( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset, \
     uint32_t addr, const uint8_t *data, uint32_t length )
{
    if ( !data || !length )
        return;

    uint32_t aligned_addr = ( addr + FT800_ALIGNMENT_ADDRESS ) & ~ \
    ( FT800_ALIGNMENT_ADDRESS );

    if ( aligned_addr != addr )
    {
        addr = aligned_addr;
    }

    uint8_t header[ FT800_RAM_G_HEADER ];
    header[ 0 ] = ( (addr >> FT800_OFFSET_SENT_ADDRESS_BYTES_2 ) & \
    FT800_SELECT_LSB_BITS_6 ) | FT800_SENT_DATA_LABEL;
    header[ 1 ] = ( addr >> FT800_OFFSET_SENT_ADDRESS_BYTES_1 ) & \
    FT800_SELECT_BYTE;
    header[ 2 ] = addr & FT800_SELECT_BYTE;

    spi_master_select_device( cfg->cs_pin );
    spi_master_write( &ctx->spi_master, header, FT800_SPI_SEND_DATA_LENGTH_3 );
    spi_master_write( &ctx->spi_master, data, length );
    spi_master_deselect_device( cfg->cs_pin );
}

void ft800_start_display_list( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset )
{
    ft800_cmd( ctx, cfg, FT800_CMD_DLSTART, cmdOffset );
    ft800_cmd( ctx, cfg, FT800_CLEAR_COLOR_RGB( FT800_RGB_INIT_VALUE, \
    FT800_RGB_INIT_VALUE, FT800_RGB_INIT_VALUE ), cmdOffset );
    ft800_cmd( ctx, cfg, FT800_CLEAR( FT800_CLR_BUFF_MASK, FT800_CLR_BUFF_MASK, \
    FT800_CLR_BUFF_MASK ), cmdOffset );
}

void ft800_end_display_list( ft800_t *ctx, ft800_cfg_t *cfg, uint16_t *cmdOffset )
{
    ft800_cmd( ctx, cfg, FT800_CMD_DISPLAY, cmdOffset );
    ft800_cmd( ctx, cfg, FT800_CMD_SWAP, cmdOffset );
    *cmdOffset = 0;
}

// ------------------------------------------------------------------------- END
