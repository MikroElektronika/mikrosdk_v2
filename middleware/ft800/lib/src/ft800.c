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
#include "delays.h"
#include "ft800_cmd.h"
#include "ft800_reg.h"
#include "ft800_const.h"
#include "ft800_struct.h"

/**
 * @brief FT800 Byte Transmit Function.
 * @details This function sends 1 data byte to FT800 controller.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                   for detailed explanation.
 * @param[in] value : 1 Byte of data for transmition.
 * @return None
 */
static void ft800_transmit_byte( ft800_t *ctx, uint8_t value );

/**
 * @brief FT800 Host Command Function.
 * @details This function sends host command to FT800 controller.
 * @param[out] ctx : FT800 context object. See #ft800_t structure definition
 *                   for detailed explanation.
 * @param[in] command : FT800 host command.
 * @return None
 */
static void ft800_host_command( ft800_t *ctx, uint8_t command );

/**
 * @brief FT800 Write Address Function.
 * @details This function sends register address for writing to FT800 controller.
 * @param[out] ctx : FT800 context object. See #ft800_t structure definition
 *                   for detailed explanation.
 * @param[in] address : FT800 register address.
 * @return None
 */
static void ft800_write_address( ft800_t *ctx, uint32_t address );

/**
 * @brief FT800 Read Address Function.
 * @details This function sends register address for reading to FT800 controller.
 * @param[out] ctx : FT800 context object. See #ft800_t structure definition
 *                   for detailed explanation.
 * @param[in] address : FT800 register address.
 * @return None
 */
static void ft800_read_address( ft800_t *ctx, uint32_t address );

// Global variable to track FT800 command offset.
uint16_t cmdOffset = 0;

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

void ft800_cfg_setup( ft800_cfg_t *cfg, const ft800_controller_t *controller ) {
    cfg->in_pin = HAL_PIN_NC;
    cfg->controller = controller;
    cfg->height = TFT_DISPLAY_HEIGHT;
    cfg->width = TFT_DISPLAY_WIDTH;
}

void ft800_write_8_bits( ft800_t *ctx, uint32_t address, uint8_t value ) {
    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 register address.
    ft800_write_address( ctx, address );
    // Send FT800 command value.
    ft800_transmit_byte( ctx, value );

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );
}

void ft800_write_16_bits( ft800_t *ctx, uint32_t address, uint16_t value ) {
    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 register address.
    ft800_write_address( ctx, address );
    // Send FT800 command value.
    ft800_transmit_byte( ctx, FT800_VALUE_BYTE_1( value ));
    ft800_transmit_byte( ctx, FT800_VALUE_BYTE_2( value ));

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );
}

void ft800_write_32_bits( ft800_t *ctx, uint32_t address, uint32_t value ) {
    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 register address.
    ft800_write_address( ctx, address );
    // Send FT800 command value.
    ft800_transmit_byte( ctx, FT800_VALUE_BYTE_1( value ));
    ft800_transmit_byte( ctx, FT800_VALUE_BYTE_2( value ));
    ft800_transmit_byte( ctx, FT800_VALUE_BYTE_3( value ));
    ft800_transmit_byte( ctx, FT800_VALUE_BYTE_4( value ));

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );
}

uint8_t ft800_read_8_bits( ft800_t *ctx, uint32_t address ) {
    uint8_t ft800_data[ 1 ];

    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 register address.
    ft800_read_address( ctx, address );
    // Send 1 dummy byte.
    ft800_transmit_byte( ctx, 0 );

    // Read 1 byte of data.
    spi_master_read( &ctx->spi_master, ft800_data, FT800_DATA_BYTES_1 );

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );

    return ft800_data[ 0 ];
}

uint16_t ft800_read_16_bits( ft800_t *ctx, uint32_t address ) {
    uint8_t ft800_data[ 2 ];

    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 register address.
    ft800_read_address( ctx, address );
    // Send 1 dummy byte.
    ft800_transmit_byte( ctx, 0 );

    // Read 2 bytes of data.
    spi_master_read( &ctx->spi_master, ft800_data, FT800_DATA_BYTES_2 );

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );

    return (( uint16_t )ft800_data[ 1 ] << FT800_OFFSET_BITS_8 ) | ft800_data[ 0 ];
}

uint32_t ft800_read_32_bits( ft800_t *ctx, uint32_t address ) {
    uint8_t ft800_data[ 4 ];

    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 register address.
    ft800_read_address( ctx, address );
    // Send 1 dummy byte.
    ft800_transmit_byte( ctx, 0 );

    // Read 4 bytes of data.
    spi_master_read( &ctx->spi_master, ft800_data, FT800_DATA_BYTES_4 );

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );

    return FT800_READ_VALUE_4_BYTES( \
        ft800_data[ 0 ], ft800_data[ 1 ], ft800_data[ 2 ], ft800_data[ 3 ] );
}

void ft800_default_cfg( ft800_cfg_t *cfg ) {
    spi_master_configure_default( &cfg->spi_master_cfg );
    cfg->spi_master_cfg.sck = cfg->sck_pin;
    cfg->spi_master_cfg.miso = cfg->miso_pin;
    cfg->spi_master_cfg.mosi = cfg->mosi_pin;
    cfg->spi_master_cfg.speed = FT800_SPI_SPEED;
    cfg->spi_master_cfg.mode = SPI_MASTER_MODE_0;
    cfg->spi_master_cfg.default_write_data = 0x00;
    cfg->height = TFT_DISPLAY_HEIGHT;
    cfg->width = TFT_DISPLAY_WIDTH;
}

void ft800_cfg( ft800_t *ctx, ft800_cfg_t *cfg ) {
    // Send "ACTIVE" host command.
    ft800_host_command( ctx, FT800_ACTIVE );
    // Send "CLKEXT" host command.
    ft800_host_command( ctx, FT800_CLKEXT );
    // Send "CLK48" host command.
    ft800_host_command( ctx, FT800_CLK48M );

    // Set number of horizontal cycles for the display.
    ft800_write_16_bits( ctx, FT800_REG_HCYCLE, FT800_HCYCLE_VALUE );
    // Set horizontal offset from start signal.
    ft800_write_16_bits( ctx, FT800_REG_HOFFSET, FT800_HOFFSET_VALUE );
    // Set horizontal synchronization falling edge.
    ft800_write_16_bits( ctx, FT800_REG_HSYNC0, 0 );
    // Set horizontal synchronization rising edge.
    ft800_write_16_bits( ctx, FT800_REG_HSYNC1, FT800_HSYNC1_VALUE );
    // Set number of vertical cycles for display.
    ft800_write_16_bits( ctx, FT800_REG_VCYCLE, FT800_VCYCLE_VALUE );
    // Set vertical offset from start signal.
    ft800_write_16_bits( ctx, FT800_REG_VOFFSET, FT800_VOFFSET_VALUE );
    // Set vertical synchronization falling edge.
    ft800_write_16_bits( ctx, FT800_REG_VSYNC0, 0 );
    // Set vertical synchronization rising edge.
    ft800_write_16_bits( ctx, FT800_REG_VSYNC1, FT800_VSYNC1_VALUE );
    // Set falling edge as clock polarity for the display.
    ft800_write_8_bits( ctx, FT800_REG_PCLK_POL, FT800_PCLK_POL_VALUE );
    // Set width resolution (width of the display).
    ft800_write_16_bits( ctx, FT800_REG_HSIZE, cfg->width );
    // Set height resolution (height of the display).
    ft800_write_16_bits( ctx, FT800_REG_VSIZE, cfg->height );
    // Disable output clock spread.
    ft800_write_8_bits( ctx, FT800_REG_CSPREAD, 0 );

    // Create blank white display list.
    ft800_write_32_bits( ctx, FT800_RAM_DL, FT800_BACKGROUND_WHITE );
    ft800_write_32_bits( ctx, FT800_RAM_DL + FT800_RAM_DL_OFFSET_4, FT800_FULL_CLEAR );
    ft800_write_32_bits( ctx, FT800_RAM_DL + FT800_RAM_DL_OFFSET_8, FT800_DISPLAY() );

    // Swap display list.
    ft800_write_8_bits( ctx, FT800_REG_DLSWAP, FT800_DLSWAP_VALUE );

    // Enable display bit.
    ft800_write_8_bits( ctx, FT800_REG_GPIO_DIR, FT800_GPIO_DIR_VALUE );
    ft800_write_8_bits( ctx, FT800_REG_GPIO, FT800_GPIO_VALUE );

    // Set backlight frequency.
    ft800_write_16_bits( ctx, FT800_REG_PWM_HZ, FT800_PWM_HZ_VALUE );
    // Set backlight intensity.
    ft800_write_8_bits( ctx, FT800_REG_PWM_DUTY, FT800_PWM_DUTY_VALUE );

    // Enable pixel clocking.
    ft800_write_8_bits( ctx, FT800_REG_PCLK, FT800_PCLK_VALUE );
}

/**
 * @note @b FT800 hardware does not support gestures.
 */
void ft800_gesture( ft800_t* ctx, tp_event_t * event ) {
    *event = TP_EVENT_GEST_NONE;
}

tp_event_t ft800_press_detect( ft800_t* ctx ) {
    return ctx->press_det;
}

void ft800_press_coordinates( ft800_t *ctx, tp_touch_item_t *touch_item ) {
    touch_item->n_touches = FT800_TOUCH_NUM;
    touch_item->point[ 0 ] = ctx->touch.point[ 0 ];
}

void ft800_init( ft800_t *ctx, ft800_cfg_t *cfg, tp_drv_t *drv ) {
    // Initialize GPIO pins to control FT800 chip.
    digital_out_init( &ctx->cs_pin, cfg->cs_pin );
    digital_out_init( &ctx->pd_pin, cfg->pd_pin );

    // Initialize SPI interface.
    spi_master_open( &ctx->spi_master, &cfg->spi_master_cfg );

    // Set SPI speed.
    spi_master_set_speed( &ctx->spi_master, cfg->spi_master_cfg.speed );

    // Reset FT800 controller.
    digital_out_low( &ctx->pd_pin );
    Delay_ms( 20 );
    digital_out_high( &ctx->pd_pin );
    Delay_ms( 20 );

    // Configure FT800 controller.
    ft800_cfg( ctx, cfg );

    // Initialize touch screen.
    ft800_init_touch_screen( ctx, true );

    // Assign touch panel handlers.
    drv->tp_press_detect_f      = ft800_press_detect;
    drv->tp_press_coordinates_f = ft800_press_coordinates;
    drv->tp_gesture_f           = ft800_gesture;
    drv->tp_process_f           = ft800_process;
}

void ft800_init_touch_screen( ft800_t *ctx, bool run_calibration )
{
    // Request touch calibration from FT800 controller.
    ft800_write_8_bits( ctx, FT800_REG_TOUCH_MODE, 0x00 );
    Delay_ms( 10 );

    if ( run_calibration ) {
        // Create blank black display list.
        ft800_cmd( ctx, FT800_CMD_DLSTART );
        ft800_cmd( ctx, FT800_BACKGROUND_BLACK );
        ft800_cmd( ctx, FT800_FULL_CLEAR );

        // Add calibration text ob the screen.
        ft800_cmd_text( ctx, FT800_CALIBRATE_TEXT_X, \
            FT800_CALIBRATE_TEXT_Y, FT800_CALIBRATE_TEXT_FONT, 0, \
            "Touch the dots to calibrate" );

        // Start calibration process.
        ft800_cmd( ctx, FT800_CMD_CALIBRATE );

        // Display everything.
        ft800_cmd( ctx, FT800_CMD_SWAP );

        // Inform FT800 about the current command offset value.
        ft800_write_16_bits( ctx, FT800_REG_CMD_WRITE, cmdOffset );

        // Wait for calibration to finish.
        ft800_wait_coprocessor( ctx );

        Delay_ms( 100 );
    }

    // Set continuous mode of touch detection.
    ft800_write_8_bits( ctx, FT800_REG_TOUCH_MODE, FT800_TOUCH_ACTIVATION_VALUE );
}

tp_err_t ft800_process( ft800_t *ctx )
{
    tp_err_t status;

    status = ft800_read_press_coordinates( ctx );

    return status;
}

tp_err_t ft800_read_press_coordinates( ft800_t *ctx )
{
    uint32_t position = ft800_read_32_bits( ctx, FT800_REG_TOUCH_SCREEN_XY );

    if ( FT800_REG_TOUCH_PRESS != position )
    {
        ctx->touch.point[ 0 ].coord_x = position >> FT800_OFFSET_READ_COORD_BYTES_2;
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

void ft800_wait_coprocessor( ft800_t *ctx )
{
    uint16_t write_cmdOffset = ft800_read_16_bits( ctx, FT800_REG_CMD_WRITE );

    // Wait while FT800 command offset is the same as for host commands.
    while ( ft800_read_16_bits( ctx, FT800_REG_CMD_READ ) != write_cmdOffset );
}

void ft800_write_ram_g( ft800_t *ctx, \
    uint32_t address, uint8_t *ft800_data, uint32_t length )
{
    if ( !ft800_data || !length )
        return;

    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );
    // Send FT800 RAM_G register address.
    ft800_write_address( ctx, address );

    spi_master_write( &ctx->spi_master, ft800_data, length );
    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );
}

void ft800_start_display_list( ft800_t *ctx )
{
    ft800_cmd( ctx, FT800_CMD_DLSTART );
    ft800_cmd( ctx, FT800_BACKGROUND_WHITE );
    ft800_cmd( ctx, FT800_FULL_CLEAR );
}

void ft800_end_display_list( ft800_t *ctx )
{
    // Display the current list of items.
    ft800_cmd( ctx, FT800_CMD_DISPLAY );
    ft800_cmd( ctx, FT800_CMD_SWAP );

    // FT800 has only 4KB of internal RAM memory.
    if ( 4095 <= cmdOffset )
        cmdOffset = 4095;

    // Inform FT800 about the current command offset value.
    ft800_write_16_bits( ctx, FT800_REG_CMD_WRITE, cmdOffset );
}

static void ft800_transmit_byte( ft800_t *ctx, uint8_t value ) {
    spi_master_write( &ctx->spi_master, &value, 1 );
}

static void ft800_host_command( ft800_t *ctx, uint8_t command ) {
    // Select FT800 display.
    digital_out_low( &ctx->cs_pin );

    // Send FT800 host command.
    ft800_transmit_byte( ctx, command );
    ft800_transmit_byte( ctx, 0 );
    ft800_transmit_byte( ctx, 0 );

    // Deselect FT800 display.
    digital_out_high( &ctx->cs_pin );
}

static void ft800_write_address( ft800_t *ctx, uint32_t address ) {
    ft800_transmit_byte( ctx, FT800_ADDRESS_BYTE_1_WRITE( address ));
    ft800_transmit_byte( ctx, FT800_ADDRESS_BYTE_2( address ));
    ft800_transmit_byte( ctx, address );
}

static void ft800_read_address( ft800_t *ctx, uint32_t address ) {
    ft800_transmit_byte( ctx, FT800_ADDRESS_BYTE_1_READ( address ));
    ft800_transmit_byte( ctx, FT800_ADDRESS_BYTE_2( address ));
    ft800_transmit_byte( ctx, address );
}

// ------------------------------------------------------------------------- END
