/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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

#include "tft7.h"
#include "ili9341.h"

/**
 * @brief ILI9341 Context Object.
 * @details Context object definition for ILI9341 display controller.
 */
static ili9341_t ili9341_ctx;

/**
 * @brief Reset procedure for ILI9341 display controller.
 * @details This function initialize ILI9341 display controller reset procedure.
 */
static void _reset_ili9341_controller_320x240_8bit( tft7_orientation_t orientation );

/**
 * @brief EasyTFT Board definition structure.
 */
const tft7_board_t TFT_BOARD_EASY = {
    320, // display_width
    240, // display_height
    _reset_ili9341_controller_320x240_8bit
};

static void _reset_ili9341_controller_320x240_8bit( tft7_orientation_t orientation ) {
    ili9341_write_command( ILI9341_CMD_SOFTWARE_RESET );
    Delay_10ms();
    ili9341_write_command( ILI9341_CMD_SOFTWARE_RESET );
    Delay_10ms();
    ili9341_write_command( ILI9341_CMD_SOFTWARE_RESET );
    Delay_10ms();

    ili9341_write_command( ILI9341_CMD_DISPLAY_OFF );

    ili9341_write_command( ILI9341_CMD_POWER_CONTROL_B );
    ili9341_write_param( ILI9341_PARAM_1_POWER_CONTROL_B_BITS );
    ili9341_write_param( ILI9341_PARAM_2_POWER_CONTROL_B_BITS );
    ili9341_write_param( ILI9341_PARAM_3_POWER_CONTROL_B_BITS );

    ili9341_write_command( ILI9341_CMD_POWER_ON_SEQUENCE_CONTROL );
    ili9341_write_param( ILI9341_PARAM_1_SOFT_START_CONTROL_BITS );
    ili9341_write_param( ILI9341_PARAM_2_DDVDH_VCL_ENABLE_BITS );
    ili9341_write_param( ILI9341_PARAM_3_VGL_VGH_ENABLE_BITS );
    ili9341_write_param( ILI9341_PARAM_4_DDVDH_ENHANCE_MODE_ENABLE_BITS );

    ili9341_write_command( ILI9341_CMD_DRIVER_TIMING_CONTROL_A );
    ili9341_write_param( ILI9341_PARAM_1_GATE_DRIVER_NON_OVERLAP_BITS );
    ili9341_write_param( ILI9341_PARAM_2_EQ_CR_TIMING_CONTROL_BITS );
    ili9341_write_param( ILI9341_PARAM_3_PRE_CHARGE_TIMING_CONTROL_BITS );

    ili9341_write_command( ILI9341_CMD_POWER_CONTROL_A );
    ili9341_write_param( ILI9341_PARAM_1_POWER_CONTROL_A_BITS );
    ili9341_write_param( ILI9341_PARAM_2_POWER_CONTROL_A_BITS );
    ili9341_write_param( ILI9341_PARAM_3_POWER_CONTROL_A_BITS );
    ili9341_write_param( ILI9341_PARAM_4_VCORE_CONTROL_BITS );
    ili9341_write_param( ILI9341_PARAM_5_DDVDH_CONTROL_BITS );

    ili9341_write_command( ILI9341_CMD_PUMP_RATIO_CONTROL );
    ili9341_write_param( ILI9341_PARAM_1_PUMP_RATIO_CONTROL_BITS );

    ili9341_write_command( ILI9341_CMD_DRIVER_TIMING_CONTROL_B );
    ili9341_write_param( ILI9341_PARAM_1_GATE_DRIVER_TIMING_CONTROL_B_BITS );
    ili9341_write_param( ILI9341_PARAM_2_DRIVER_TIMING_CONTROL_B_BITS );

    ili9341_write_command( ILI9341_CMD_POWER_CONTROL_1 );
    ili9341_write_param( ILI9341_PARAM_1_GVDD_VOLTAGE_LEVEL_BITS );

    ili9341_write_command( ILI9341_CMD_POWER_CONTROL_2 );
    ili9341_write_param( ILI9341_PARAM_1_OPERATING_VOLTAGE_STEP_UP_FACTOR_BITS );

    ili9341_write_command( ILI9341_CMD_VCOM_CONTROL_1 );
    ili9341_write_param( ILI9341_PARAM_1_VCOMH_VOLTAGE_BITS );
    ili9341_write_param( ILI9341_PARAM_2_VCOML_VOLTAGE_BITS );

    ili9341_write_command( ILI9341_CMD_VCOM_CONTROL_2 );
    ili9341_write_param( ILI9341_PARAM_1_VCOM_OFFSET_VOLTAGE_BITS );

    ili9341_write_command( ILI9341_CMD_PIXEL_FORMAT_SET );
    ili9341_write_param( ILI9341_PARAM_1_18_BITS_INTERFACE_PIXEL_FORMAT );

    ili9341_write_command( ILI9341_CMD_MEMORY_ACCESS_CONTROL );
    if ( TFT_MODE_LANDSCAPE_UP == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_NO_ROTATION );
    } else if ( TFT_MODE_PORTRAIT_LEFT == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_ROTATE_90 );
    } else if ( TFT_MODE_LANDSCAPE_DOWN == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_ROTATE_180 );
    } else if ( TFT_MODE_PORTRAIT_RIGHT == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_ROTATE_270 );
    }

    ili9341_write_command( ILI9341_CMD_FRAME_CONTROL_NORMAL_MODE );
    ili9341_write_param( ILI9341_PARAM_1_INTERNAL_CLOCK_DIVISION_RATIO_BITS );
    ili9341_write_param( ILI9341_PARAM_2_CLOCK_PER_LINE_BITS );

    ili9341_write_command( ILI9341_CMD_DISPLAY_FUNCTION_CONTROL );
    ili9341_write_param( ILI9341_PARAM_1_PTG_PT_BITS );
    ili9341_write_param( ILI9341_PARAM_2_ISC_SM_SS_GS_REV_BITS );
    ili9341_write_param( ILI9341_PARAM_3_NL_BITS );
    ili9341_write_param( ILI9341_PARAM_4_PCDIV_BITS );

    ili9341_write_command( ILI9341_CMD_ENABLE_3G );
    ili9341_write_param( ILI9341_PARAM_1_GAMA_CONTROL_ENABLE_BITS );

    ili9341_write_command( ILI9341_CMD_GAMMA_SET );
    ili9341_write_param( ILI9341_PARAM_1_GAMMA_CURVE_BITS );

    ili9341_write_command( ILI9341_CMD_POSITIVE_GAMMA_CORRECTION );
    ili9341_write_param( ILI9341_PARAM_1_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_2_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_3_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_4_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_5_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_6_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_7_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_8_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_9_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_10_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_11_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_12_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_13_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_14_POSITIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_15_POSITIVE_GAMMA_CORRECTION_BITS );

    ili9341_write_command( ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION );
    ili9341_write_param( ILI9341_PARAM_1_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_2_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_3_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_4_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_5_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_6_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_7_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_8_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_9_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_10_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_11_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_12_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_13_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_14_NEGATIVE_GAMMA_CORRECTION_BITS );
    ili9341_write_param( ILI9341_PARAM_15_NEGATIVE_GAMMA_CORRECTION_BITS );

    ili9341_write_command( ILI9341_CMD_ENTRY_MODE_SET );
    ili9341_write_param( ILI9341_PARAM_1_GAS_DTE_GON_BITS );

    ili9341_write_command( ILI9341_CMD_SLEEP_OUT );
    Delay_100ms();

    ili9341_write_command( ILI9341_CMD_DISPLAY_ON );
    Delay_100ms();

    ili9341_write_command( ILI9341_CMD_MEMORY_WRITE );
}

void tft7_init( tft7_cfg_t *cfg, gl_driver_t *driver ) {
    ili9341_cfg_t ili9341_cfg;

    ili9341_default_cfg( &ili9341_cfg );

    ili9341_cfg.rst = cfg->tft_rst;
    ili9341_cfg.cs = cfg->tft_cs;
    ili9341_cfg.rs = cfg->tft_rs;
    ili9341_cfg.rd = cfg->tft_rd;
    ili9341_cfg.wr = cfg->tft_wr;

    // PWM module is used for backlight control.
    ILI9341_PWM_CONFIG( ili9341_cfg );

    ili9341_cfg.data_channel_0 = cfg->data_channel_0;
    ili9341_cfg.data_channel_0_mask = cfg->data_channel_0_mask;

    ili9341_cfg.data_channel_1 = cfg->data_channel_1;
    ili9341_cfg.data_channel_1_mask = cfg->data_channel_1_mask;

    ili9341_cfg.width  = cfg->board->display_width;
    ili9341_cfg.height = cfg->board->display_height;

    cfg->orientation = TFT_MODE_LANDSCAPE_UP;
    ili9341_cfg.orientation = cfg->orientation;

    ili9341_cfg.host_interface = cfg->host_interface;

    ili9341_init( &ili9341_cfg, driver, &ili9341_ctx );
    cfg->board->reset_procedure( cfg->orientation );

    tft7_set_backlight( TFT7_MAX_BACKLIGHT );
}

uint16_t tft7_display_width() {
    return ili9341_get_display_width();
}

uint16_t tft7_display_height() {
    return ili9341_get_display_height();
}

void tft7_set_backlight( float intensity ) {
    ili9341_set_backlight_intensity ( intensity, &ili9341_ctx );
}

void tft7_set_display_orientation( tft7_cfg_t *cfg, gl_driver_t *driver, tft7_orientation_t orientation ) {
    ili9341_write_command( ILI9341_CMD_MEMORY_ACCESS_CONTROL );
    if ( TFT_MODE_LANDSCAPE_UP == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_NO_ROTATION );
        driver->display_width = cfg->board->display_width;
        driver->display_height = cfg->board->display_height;
    } else if ( TFT_MODE_PORTRAIT_LEFT == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_ROTATE_90 );
        driver->display_width = cfg->board->display_height;
        driver->display_height = cfg->board->display_width;
    } else if ( TFT_MODE_LANDSCAPE_DOWN == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_ROTATE_180 );
        driver->display_width = cfg->board->display_width;
        driver->display_height = cfg->board->display_height;
    } else if ( TFT_MODE_PORTRAIT_RIGHT == orientation ) {
        ili9341_write_param( ILI9341_PARAM_1_ROTATE_270 );
        driver->display_width = cfg->board->display_height;
        driver->display_height = cfg->board->display_width;
    }
    gl_set_driver( driver );
}
