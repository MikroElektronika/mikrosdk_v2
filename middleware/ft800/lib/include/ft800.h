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
#ifndef FT800_H
#define FT800_H

#include <stdint.h>
#include <math.h>
#include "generic_pointer.h"
#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "drv_digital_in.h"
#include "ft800_struct.h"
#include "ft800_const.h"
#include "hal_gpio.h"
#include "mikrobus.h"
#include "gl_text.h"
#include "gl.h"
#include "tp.h"

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of FT800 display to selected MikroBUS.
 */
#define FT800_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.cs_pin   =  MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sck_pin  =  MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.miso_pin =  MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi_pin =  MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.pd_pin   =  MIKROBUS( mikrobus, MIKROBUS_RST )

/**
 * @brief FT800 Pin Mapping.
 * @details Utility macro for mapping FT800 series controllers.
 */
// Note: Will be added with one of upcoming releases when Board with FT800
// capabilities will be added to SDK.
// #define FT800_MAP_PINS( cfg ) \
//     cfg.cs_pin = FT800_CS; \
//     cfg.sck_pin = FT800_SCK; \
//     cfg.miso_pin = FT800_MISO; \
//     cfg.mosi_pin = FT800_MOSI; \
//     cfg.pd_pin = FT800_PD;

/**
 * @brief FT800 Configuration Object Setup Function.
 * @details This function initializes FT800 configuration structure to default
 * values.
 * @param[out] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[in] controller : Controller selector from FT800 series
 * controllers. See #ft800_controller_t structure definition for detailed
 * explanation.
 * @return Nothing.
 * @note All used pins will be set to unconnected state.
 *
 * @b Example
 * @code
 *    // FT800 configuration object.
 *    ft800_cfg_t ft800_cfg;
 *    // FT800 series touch controllers descriptor.
 *    const ft800_controller_t FT800_CONTROLLER =
 *    {
 *        {
 *            { 0x00, TP_EVENT_GEST_NONE },
 *            { 0x1C, TP_EVENT_GEST_LEFT },
 *            { 0x14, TP_EVENT_GEST_RIGHT },
 *            { 0x10, TP_EVENT_GEST_UP },
 *            { 0x18, TP_EVENT_GEST_DOWN },
 *            { 0x48, TP_EVENT_GEST_ZOOM_IN },
 *            { 0x49, TP_EVENT_GEST_ZOOM_OUT }
 *        }
 *    };
 *
 *    // FT800 configuration setup.
 *    ft800_cfg_setup( &ft800_cfg, &FT800_CONTROLLER );
 * @endcode
 */
void ft800_cfg_setup( ft800_cfg_t * cfg, const ft800_controller_t * controller );

/**
 * @brief FT800 Default Configuration Function.
 * @details This function puts the FT800 touch controller to normal operating
 * mode.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return Nothing.
 * @note It's necessary for this function to be executed after Initialization
 * function for proper work of the entire driver.
 *
 * @b Example
 * @code
 *
 *    // FT800 driver default configuration.
 *    ft800_default_cfg( &ft800 );
 * @endcode
 */
void ft800_default_cfg( ft800_cfg_t *cfg );

/**
 * @brief Write 8 Bits of Data Function.
 * @details This function allows user to write any 8-bit data to the selected register
 *          of the FT800 series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                  for detailed explanation.
 * @param[in] address : Register address where data should be written.
 * @param[in] value : Data to be written.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Set falling edge as clock polarity for the display.
 *    ft800_write_8_bits( ctx, FT800_REG_PCLK_POL, FT800_PCLK_POL_VALUE );
 * @endcode
 */
void ft800_write_8_bits( ft800_t *ctx, uint32_t address, uint8_t value );

/**
 * @brief Write 16 Bits of Data Function.
 * @details This function allows user to write any 16-bit data to the selected register
 *          of the FT800 series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                  for detailed explanation.
 * @param[in] address : Register address where data should be written.
 * @param[in] value : Data to be written.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Set vertical synchronisation rising edge.
 *    ft800_write_16_bits( ctx, FT800_REG_VSYNC1, FT800_VSYNC1_VALUE );
 * @endcode
 */
void ft800_write_16_bits( ft800_t *ctx, uint32_t address, uint16_t value );

/**
 * @brief Write 32 Bits of Data Function.
 * @details This function allows user to write any 32-bit data to the selected register
 *          of the FT800 series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                  for detailed explanation.
 * @param[in] address : Register address where data should be written.
 * @param[in] value : Data to be written.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Create blank white display list.
 *    ft800_write_32_bits( ctx, FT800_RAM_DL, FT800_BACKGROUND_WHITE );
 * @endcode
 */
void ft800_write_32_bits( ft800_t *ctx, uint32_t address, uint32_t value );

/**
 * @brief Read 8 Bits of Data Function.
 * @details This function allows user to read any desired register of the FT800
 *          series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                  for detailed explanation.
 * @param[in] address : Register address which from data be read.
 * @return 8-bit read data.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Read value.
 *    uint8_t ft800_read_data;
 *
 *    // Reading activity status of FT800 controller.
 *    ft800_read_data = ft800_read_8_bits( &ctx, FT800_REG_ID );
 * @endcode
 */
uint8_t ft800_read_8_bits( ft800_t *ctx, uint32_t address );

/**
 * @brief Read 16 Bits of Data Function.
 * @details This function allows user to read any desired register of the FT800
 *          series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                  for detailed explanation.
 * @param[in] address : Register address which from data be read.
 * @return 16-bit read data.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Read value.
 *    uint16_t ft800_read_data;
 *
 *    // Reading activity status of FT800 controller.
 *    ft800_read_data = ft800_read_16_bits( &ctx, FT800_REG_ID );
 * @endcode
 */
uint16_t ft800_read_16_bits( ft800_t *ctx, uint32_t address );

/**
 * @brief Read 32 Bits of Data Function.
 * @details This function allows user to read any desired register of the FT800
 *          series controllers.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 *                  for detailed explanation.
 * @param[in] address : Register address which from data be read.
 * @return 32-bit read data.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Read value.
 *    uint32_t ft800_read_data;
 *
 *    // Reading activity status of FT800 controller.
 *    ft800_read_data = ft800_read_32_bits( &ctx, FT800_REG_ID );
 * @endcode
 */
uint32_t ft800_read_32_bits( ft800_t *ctx, uint32_t address );

/**
 * @brief FT800 Initialization Function.
 * @details This function initializes FT800 context object to
 * default values and allows driver interface object to be linked with FT800
 * driver functions.
 * @param[out] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @param[out] drv : TP driver interface object. See #tp_drv_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * See #tp_err_t structure definition for detailed explanation.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // FT800 configuration object.
 *    ft800_cfg_t ft800_cfg;
 *    // FT800 series touch controllers descriptor.
 *    const ft800_controller_t FT800_CONTROLLER;
 *    // TP driver interface object.
 *    tp_drv_t tp_interface;
 *
 *    // FT800 configuration setup.
 *    ft800_cfg_setup( &ft800_cfg, &FT800_CONTROLLER );
 *    // FT800 controller pin mapping.
 *    FT800_MAP_PINS( ft800_cfg );
 *    // FT800 driver initialization.
 *    ft800_init( &ft800, &ft800_cfg, &tp_interface );
 * @endcode
 */
void ft800_init( ft800_t *ctx, ft800_cfg_t *cfg, tp_drv_t *drv );

/**
 * @brief FT800 Default Configuration Function.
 * @details This function puts the FT800 touch controller to normal operating
 * mode.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return Nothing.
 * @note It's necessary for this function to be executed after Initialization
 * function for proper work of the entire driver.
 *
 * @b Example
 * @code
 *
 *    // FT800 driver default configuration.
 *    ft800_default_cfg( &ft800 );
 * @endcode
 */
void ft800_default_cfg( ft800_cfg_t *cfg );

/**
 * @brief FT800 Configuration Function.
 * @details This function configures FT800 registers to active operating
 * mode.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cfg : FT800 configuration object. See #ft800_cfg_t structure
 * definition for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // FT800 configuration object.
 *    ft800_cfg_t cfg;
 *
 *    // FT800 driver active configuration.
 *    ft800_cfg( &ctx, &cfg );
 * @endcode
 */
void ft800_cfg( ft800_t *ctx, ft800_cfg_t *cfg );

/**
 * @brief FT800 Gesture Check Function.
 * @details This function allows user to get the information about the gesture
 * ( slide direction ).
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[out] event : Touch panel gesture data. See #tp_event_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #ft800_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // Gesture event.
 *    tp_event_t event;
 *
 *    // Checking slide direction event of pressed touch.
 *    ft800_gesture( &ft800, &event );
 * @endcode
 */
void ft800_gesture( ft800_t *ctx, tp_event_t *event );

/**
 * @brief FT800 Touch Pressure Detect Function.
 * @details This function allows the touch pressure detection.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return @li @c 3 - Touch pressure is not detected,
 *         @li @c 4 - Touch pressure is detected.
 * See #tp_event_t structure definition for detailed explanation.
 * @note #ft800_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // Touch pressure event.
 *    tp_event_t event;
 *
 *    // Checking touch pressure event.
 *    event = ft800_press_detect( &ft800 );
 * @endcode
 */
tp_event_t ft800_press_detect( ft800_t *ctx );

/**
 * @brief FT800 Pressure Coordinates Check Function.
 * @details This function allows user to get the information about the number
 * of pressed touch points, coordinates and touch event for each pressed touch
 * point.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[out] touch_item : Touch item data. See #tp_touch_item_t structure
 * definition for detailed explanation.
 * @return Nothing.
 * @note #ft800_process function must be called to update all events.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // Touch pressure item.
 *    tp_touch_item_t tp_item;
 *
 *    // To get all necessary data information about pressed touch.
 *    ft800_press_coordinates( &ft800, &tp_item );
 * @endcode
 */
void ft800_press_coordinates( ft800_t *ctx, tp_touch_item_t *touch_item );

/**
 * @brief Initialization Touch Screen.
 * @details This function allows user to set registers of FT800 controller to
 * active state and enable recognition of press on screen.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] run_calibration : Enable a calibration routine for FT800 controller.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // To set touch engine registers at active state and run calibration
 *    // routine.
 *    ft800_init_touch_screen( &ctx, true );
 * @endcode
 */
void ft800_init_touch_screen( ft800_t *ctx, bool run_calibration );

/**
 * @brief FT800 Process Function.
 * @details This function detects a touch pressure, and if any touch pressure
 * was detected, then collects all information about the pressed touch and
 * slide direction ( gesture ).
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return @li @c 0 - OK,
 *         @li @c 5 - Number of pressed touches is out of range.
 * See #tp_err_t structure definition for detailed explanation.
 * @note To update all possible events, call this function before
 * any other function for checking events is called.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ft800;
 *    // TP error code.
 *    tp_err_t error;
 *
 *    // Processing all data and events of the target touch controller.
 *    error = ft800_process( &ft800 );
 * @endcode
 */
 tp_err_t ft800_process( ft800_t *ctx );

  /**
 * @brief Read touch press coordinates.

 * @details This function reads the current touch coordinates from the FT800
 * controller if a touch is detected. It updates the touch data within the
 * provided context.
 * @param[in,out] ctx Pointer to the FT800 context object used to store touch
 * data.
 *
 * @return @c TP_OK if coordinates were successfully read, or an appropriate
 *         @c tp_err_t error code otherwise.
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // TP error code.
 *    tp_err_t error;
 *
 *    // Read touch coordinates.
 *    error = ft800_read_press_coordinates( &ctx );
 *    if ( error == TP_OK )
 *    {
 *      uint16_t x_coordinate = ctx->touch.point[ 0 ].coord_x;
 *      uint16_t y_coordinate = ctx->touch.point[ 0 ].coord_y;
 *    }
 * @endcode
 */
 tp_err_t ft800_read_press_coordinates( ft800_t *ctx );

 /**
 * @brief FT800 Waiting Coprocessor Function.
 * @details This function blocks executing code until values in FT800_REG_CMD_WRITE
 * and FT800_REG_CMD_READ are equal.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Waiting for co-processor to handle FT800_REG_CMD_WRITE and
 *    // FT800_REG_CMD_READ after finishing display list.
 *    ft800_end_display_list( &ctx );
 *    ft800_wait_coprocessor( &ctx );
 * @endcode
 */
void ft800_wait_coprocessor( ft800_t *ctx );

 /**
 * @brief Write into RAM G Function.
 * @details This function writes an image data from generated array into RAM G
 * memory.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] address : Address in FT800_RAM_G memory from where image uploading
 * starts.
 * @param[in] ft800_data : Image data from generated array.
 * @param[in] length : Length of data which is enrolled in FT800_RAM_G.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // First adress in FT800_RAM_G memory.
 *    uint32_t address = 0x0000;
 *    // Images data array.
 *    uint8_t array[ ] = ....
 *    // Size of array.
 *    uint32_t size = sizeof( array )
 *
 *    // Writing image data into FT800_RAM_G memory.
 *    ft800_write_ram_g( &ctx, address, array, size );
 * @endcode
 */
void ft800_write_ram_g( ft800_t *ctx, uint32_t address, uint8_t *ft800_data, uint32_t length );

 /**
 * @brief Send Command Function.
 * @details This function sends command to FT800 co-processor.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] command : Command which is being sent to FT800 co-processor.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which starts touch calibration routine.
 *    ft800_cmd( &ctx, FT800_CMD_CALIBRATE );
 * @endcode
 */
void ft800_cmd( ft800_t *ctx, uint32_t command );

 /**
 * @brief Send Command Text Function.
 * @details This function sends command to FT800 co-processor for drawing text.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x1 : X coordinate from which to start drawing the line.
 * @param[in] y1 : Y coordinate from which to start drawing the line.
 * @param[in] x2 : X coordinate to which the line is drawn.
 * @param[in] y2 : Y coordinate to which the line is drawn.
 * @param[in] color : Setting color of line.
 * @param[in] width : Setting width of line.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws red line from position ( 50, 50 ) to position
 *    // ( 100, 100) with width 5.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_line( &ctx, 50, 50, 100, 100, 0x7F800, 5 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_line( ft800_t *ctx, uint16_t x1, uint16_t y1, uint16_t x2, \
     uint16_t y2, uint16_t color, uint8_t width );

 /**
 * @brief Send Command Text Function.
 * @details This function sends command to FT800 co-processor for drawing text.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the text.
 * @param[in] y : Y coordinate from which to start drawing the text.
 * @param[in] font : Setting one of the available built-in fonts.
 * @param[in] option : Additional options for text centering.
 * @param[in] s : Text to be drawn.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws text FT800 at position ( 50, 50 ) with font 31.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_text( &ctx, 50, 50, 31, 0, "FT800" );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_text( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t font, \
     uint16_t options, char *s );

/**
 * @brief Send Command Number Function.
 * @details This function sends command to FT800 co-processor for drawing number.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the number.
 * @param[in] y : Y coordinate from which to start drawing the number.
 * @param[in] font : Setting one of the available built-in fonts.
 * @param[in] option : Additional options for number centering.
 * @param[in] num : Number to be drawn.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws number 800 at position ( 50, 50 ) with font 31.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_number( &ctx, 50, 50, 31, 0, "800" );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_number( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t font, \
     uint16_t options, int32_t num );

/**
 * @brief Send Command Button Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in button widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the button.
 * @param[in] y : Y coordinate from which to start drawing the button.
 * @param[in] w : Width of button.
 * @param[in] h : Height of button.
 * @param[in] font : Setting one of the available built-in fonts for text drawn on
 * the button.
 * @param[in] option : If it's 0, the button is displayed in 3D, else if it's 256,
 * the button is displayed in 2D.
 * @param[in] s : Text on button to be drawn.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3D button at position ( 50, 50 ) with width 100 and
 *    // height 50 on which it is drawn "Press" with font 31.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_button( &ctx, 50, 50, 100, 50, 26, 0, "Press" );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_button( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
     uint16_t h, uint16_t font, uint16_t options, const char *s );

/**
 * @brief Send Command Clock Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in clock widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate of center of the clock.
 * @param[in] y : Y coordinate of center of the clock.
 * @param[in] r : Radius of the clock.
 * @param[in] option : Options for drawing flat clock instead of 3D or remove
 * certain tick.
 * @param[in] h : Position of hour tick.
 * @param[in] m : Position of minutes tick.
 * @param[in] sec : Position of seconds tick.
 * @param[in] ms : Value of milliseconds.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3D clock with position of center at ( 50, 50 )
 *    // with radius 100 which shows 12 hour and 15 minutes.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_clock( &ctx, 50, 50, 100, 0, 12, 15, 0, 0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_clock( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t r, \
     uint16_t options, uint16_t h, uint16_t m, uint16_t sec, uint16_t ms );

/**
 * @brief Send Command Gauge Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in clock widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate of center of the clock.
 * @param[in] y : Y coordinate of center of the clock.
 * @param[in] r : Radius of the clock.
 * @param[in] option : Options for drawing flat gauge instead of 3D or remove
 * certain tick.
 * @param[in] major : Number of major subdivisions on the dial.
 * @param[in] minor : Number of minor subdivisions on the dial.
 * @param[in] val : Gauge indicated value, between 0 and range, inclusive.
 * @param[in] range : Maximum value of gauge.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3D gauge with position of center at ( 50, 50 ) with
 *    // radius 100 which shows value 30 form maximum 100.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_gauge( &ctx, 50, 50, 100, 0, 5, 4, 30, 100 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_gauge( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t r, \
     uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range );

/**
 * @brief Send Command Gradient Function.
 * @details This function sends command to FT800 co-processor for drawing
 * gradient color in rectangle.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x0 : X coordinate from which to start drawing the gradient rectangle.
 * @param[in] y0 : Y coordinate from which to start drawing the gradient rectangle.
 * @param[in] x1 : X coordinate to which it is drawn.
 * @param[in] y1 : Y coordinate to which it is drawn.
 * @param[in] r1 : Value of starting red color component.
 * @param[in] g1 : Value of starting green color component.
 * @param[in] b1 : Value of starting blue color component.
 * @param[in] r2 : Value of ending red color component.
 * @param[in] g2 : Value of ending green color component.
 * @param[in] b2 : Value of ending blue color component.
 * @return Nothing.
 * @note To prevent color bleed, use in combination with FT800_SCISSOR_XY and
 * FT800_SCISSOR_SIZE.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws red-blue gradient rectangle with width 100 and
 *    // height 100 from position ( 50, 50 ).
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd( &ctx, FT800_SCISSOR_XY( 50, 50 ));
 *    ft800_cmd( &ctx, FT800_SCISSOR_SIZE( 100, 100 ));
 *    ft800_cmd_gradient( &ctx, 50, 50, 100, 100, 255, 0, 0, \
 *    0, 0, 255 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_gradient( ft800_t *ctx, uint16_t x0, uint16_t y0, uint16_t x1, \
     uint16_t y1, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2 );

/**
 * @brief Send Command Keys Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in keys widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the keys.
 * @param[in] y : Y coordinate from which to start drawing the keys.
 * @param[in] w : Width of one key.
 * @param[in] h : Height of one key.
 * @param[in] font : Setting one of the available built-in fonts for text drawn on
 * button.
 * @param[in] option : If it's 0, key is displayed in 3D, else if it's 256, key
 * is displayed in 2D.
 * @param[in] s : Text where each letter represents the letter on each key,
 * respectively.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3 3D keys at position from ( 50, 50 ) with width 50
 *    // and height 50 on which one number is drawn, each starting from 1 with
 *    // font 20.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_keys( &ctx, 50, 50, 50, 50, 20, 0, "123" );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_keys( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
     uint16_t h, uint16_t font, uint16_t options, const char *s );

/**
 * @brief Send Command Progress Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in progress bar widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the progress bar.
 * @param[in] y : Y coordinate from which to start drawing the progress bar.
 * @param[in] w : Width of progress bar.
 * @param[in] h : Height of progress bar.
 * @param[in] option : If it's 0, progress bar is displayed in 3D, else if
 * it's 256, progress bar is displayed in 2D.
 * @param[in] val : Current value of progress bar.
 * @param[in] range : Maximum value of progress bar.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3 3D progress bars at position from ( 50, 50 ) with
 *    // width 150 and height 10 with 75% progress of maximum 100%.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_progress( &ctx, 50, 50, 150, 10, 0, 75, 100 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_progress( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
     uint16_t h, uint16_t options, uint16_t val, uint16_t range );

/**
 * @brief Send Command Slider Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in slider widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the slider.
 * @param[in] y : Y coordinate from which to start drawing the slider.
 * @param[in] w : Width of slider.
 * @param[in] h : Height of slider.
 * @param[in] option : If it's 0, progress bar is displayed in 3D, else if
 * it's 256, progress bar is displayed in 2D.
 * @param[in] val : Current value of slider.
 * @param[in] range : Maximum value of slider.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3 3D sliders at position from ( 50, 50 ) with width
 *    // 150 and height 10 with position at 50% of maximum 100%.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_slider( &ctx, 50, 50, 150, 10, 0, 75, 100 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_slider( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
     uint16_t h, uint16_t options, uint16_t val, uint16_t range );

/**
 * @brief Send Command Scrollbar Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in scrollbar widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the scrollbar.
 * @param[in] y : Y coordinate from which to start drawing the scrollbar.
 * @param[in] w : Width of scrollbar.
 * @param[in] h : Height of scrollbar.
 * @param[in] option : If it's 0, scrollbar is displayed in 3D, else if it's
 * 256, scrollbar is displayed in 2D.
 * @param[in] val : Current value of scrollbar.
 * @param[in] size : Size of bar.
 * @param[in] range : Maximum value of scrollbar.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3 3D scrollbars at position from ( 20, 50 ) with
 *    // width 120 and height 8 and size of bar 40 at position 10 out of
 *    // maximum 100.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_scrollbar( &ctx, 20, 50, 120, 8, 0, 10, 40, 100 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_scrollbar( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
     uint16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range );

/**
 * @brief Send Command Dial Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in dial widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate of center of dial.
 * @param[in] y : Y coordinate of center of dial.
 * @param[in] r : Radius of dial.
 * @param[in] option : Options for drawing flat dial instead of 3D.
 * @param[in] val : Position of dial pointer in range between 0 and 65535.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3D dial with position of center at ( 100, 100 )
 *    // with radius 50 with position of pointer straight up.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_dial( &ctx, 100, 100, 50, 0, 0x8000 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_dial( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t r, \
     uint16_t options, uint16_t val );

/**
 * @brief Send Command Toggle Function.
 * @details This function sends command to FT800 co-processor for drawing
 * built-in toggle widget.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start drawing the toggle.
 * @param[in] y : Y coordinate from which to start drawing the toggle.
 * @param[in] w : Width of toggle.
 * @param[in] font : Setting one of the available built-in fonts for text drawn on
 * toggle.
 * @param[in] option : If it's 0, toggle is displayed in 3D, else if it's
 * 256, toggle is displayed in 2D.
 * @param[in] state : The position the toggle is currently in.
 * @param[in] s : Text which marks the state of toggle.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command which draws 3D toggle at position ( 60, 20 ) with width 33 in
 *    // state 0 ( no ).
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_cmd_toggle( &ctx, 60, 20, 33, 27, 0, 0, \
 *    “no” “ \xff” “yes” );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_cmd_toggle( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, \
     uint16_t font, uint16_t options, uint16_t state, const char *s );

/**
 * @brief Send Command Track Function.
 * @details This function sends command to FT800 co-processor to start tracking
 * movement of press applied at drawn object after this function.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x : X coordinate from which to start tracking press and movement.
 * @param[in] y : Y coordinate from which to start tracking press and movement.
 * @param[in] w : Width of area on which press and movement are tracked
 * (for linear object; for rotary object is constant 1).
 * @param[in] h : Height of area on which press and movement are tracked
 * (for linear object; for rotary object is constant 1).
 * @param[in] tag : Tag of the object that is being tracked.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value read from register.
 *    uint32_t tracker;
 *
 *    // Command for tracking movement of dial and moving its pointer.
 *    ft800_cmd( &ctx, FT800_TAG_MASK( 1 ) );
 *    ft800_cmd( &ctx, FT800_TAG( 1 ) );
 *    dial_draw( &ctx, 90, 180, 50, angle );
 *    ft800_cmd( &ctx, FT800_TAG_MASK( 0 ) );
 *
 *    ft800_cmd_track( &ctx, 90, 180, 1, 1, 1 );
 *    tracker = ft800_read_data( &ctx, FT800_REG_TRACKER, 32 );
 *    if ( ( tracker & 0xFF ) == 1) {
 *      angle = tracker >> 16;
 *    }
 * @endcode
 */
void ft800_cmd_track( ft800_t *ctx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t tag );

/**
 * @brief Start Display List.
 * @details This function starts new display list displayed on FT800 screen.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command starting new display list.
 *    ft800_start_display_list( &ctx );
 * @endcode
 */
void ft800_start_display_list( ft800_t *ctx );

/**
 * @brief End Display List.
 * @details This function finishes display list displayed on FT800 screen.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command ending new display list.
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_end_display_list( ft800_t *ctx );

/**
 * @brief Set Screen Background.
 * @details This function sets the background color on FT800 screen.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] screen : Structure which contains all necessary parameters from
 * NECTO Designer for setting the background color.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // Command for setting background color.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_set_screen_background( &ctx );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_set_screen_background( ft800_t *ctx, ft800_screen *screen );

/**
 * @brief Execute Drawing Process.
 * @details This function executes rectangle primitive drawing commands used to
 * fill an object with a gradient color.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x_s: X coordinate from which start drawing rectangle primitive.
 * @param[in] y_s: Y coordinate from which start drawing rectangle primitive.
 * @param[in] x_e: The end X coordinate of the rectangular primitive.
 * @param[in] y_e: The end Y coordinate of the rectangular primitive.
 * @param[in] r_color: The value of the red color component.
 * @param[in] g_color: The value of the green color component.
 * @param[in] b_color: The value of the blue color component.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions will draw red rectangular primitive started from
 *    // ( 50, 50 ) to ( 150, 100 ).
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_execute_drawing_process( &ctx, 50, 50, 150, 100, \
 *    255, 0, 0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_execute_drawing_process( ft800_t *ctx, uint16_t x_s, uint16_t y_s, uint16_t x_e, \
     uint16_t y_e, uint16_t r_color, uint16_t g_color, uint16_t b_color );

/**
 * @brief Draw Button Function.
 * @details This function draws a button from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] button : Structure which contains all necessary parameters from
 * NECTO Designer for drawing a button.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a button from NECTO Designer and showing
 *    // it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_button( &ctx, main_screen.RoundedButton_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_button( ft800_t *ctx, ft800_rounded_button *button );

/**
 * @brief Draw Circle Function.
 * @details This function draws circle from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] circle : Structure which contains all necessary parameters from
 * NECTO Designer for drawing circle.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a circle from NECTO Designer and showing
 *    // it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_circle( &ctx, main_screen.Circle_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_circle( ft800_t *ctx, ft800_circle *circle );

/**
 * @brief Draw Label Function.
 * @details This function draws text label from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] label : Structure which contains all necessary parameters from
 * NECTO Designer for drawing text label.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a text label from NECTO Designer and
 *    // showing it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_label( &ctx, main_screen.Label_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_label( ft800_t *ctx, ft800_label *label );

/**
 * @brief Draw Line Function.
 * @details This function draws line from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] line : Structure which contains all necessary parameters from
 * NECTO Designer for drawing line.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a line from NECTO Designer and showing it on
 *    // the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_line( &ctx, main_screen.Line_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_line( ft800_t *ctx, ft800_line *line );

/**
 * @brief Function Draw Box Function.
 * @details This function draws box from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] box : Structure which contains all necessary parameters from
 * NECTO Designer for drawing box.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a box from NECTO Designer and showing it on
 *    // the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_box( &ctx, main_screen.RoundedBox_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_box( ft800_t *ctx, ft800_rounded_box *box );

/**
 * @brief Draw Progress Bar Function.
 * @details This function draws progress bar from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] progress_bar : Structure which contains all necessary parameters
 * from NECTO Designer for drawing progress bar.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a progress bar from NECTO Designer and
 *    // showing it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_progress_bar( &ctx, main_screen.ProgressBar_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_progress_bar( ft800_t *ctx, ft800_progress_bar *progress_bar );

/**
 * @brief Draw Check Box Function.
 * @details This function draws check box from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] check_box : Structure which contains all necessary parameters from
 * NECTO Designer for drawing check box.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a check box from NECTO Designer and
 *    // showing it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_check_box( &ctx, main_screen.CheckBox_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_check_box( ft800_t *ctx, ft800_check_box *check_box );

/**
 * @brief Draw Radio Button Function.
 * @details This function draws radio button from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] radio_button: Structure which contains all necessary parameters
 * from NECTO Designer for drawing check box.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing a radio button from NECTO Designer and
 *    // showing it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_radio_button( &ctx, main_screen.RadioButton_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_radio_button( ft800_t *ctx, ft800_radio_button *radio_button );

/**
 * @brief Draw Ellipse Function.
 * @details This function draws ellipse from NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] ellipse: Structure which contains all necessary parameters from
 * NECTO Designer for drawing ellipse.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing an ellipse from NECTO Designer and showing
 *    // it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_ellipse( &ctx, main_screen.Ellipse_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_ellipse( ft800_t *ctx, ft800_ellipse *ellipse );

/**
 * @brief Draw Image Function.
 * @details This function draws image uploaded in NECTO Designer window.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] image: Structure which contains all necessary parameters from
 * NECTO Designer for drawing image.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *
 *    // These functions are drawing an image uploaded in NECTO Designer and showing
 *    // it on the screen of FT800.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_image( &ctx, main_screen.Image_0 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_image( ft800_t *ctx, ft800_image *image );

/**
 * @brief RGB Converter Function
 * @details This function converts hex number which represents RGB565 color data
 * into 0 - 255 value for specific color.
 * @param[in] color : Hex number which represents RGB565 data of color.
 * @param[in] name: The name of the color ( red, green or blue ) extracted
 * from the hex value.
 * @return Value in range 0 - 255.
 *
 * @b Example
 * @code
 *
 *    // Value of color in RGB565 format.
 *    uint16_t color = 0x8BD0;
 *
 *    // Variable for red color.
 *    uint8_t r_color;
 *
 *    // This function gets value of red component from RGB565 color.
 *    r_color = ft800_rgb_convert( color, "red" );
 * @endcode
 */
uint8_t ft800_rgb_convert( uint16_t color, char *name );

/**
 * @brief Draw Circle's Edges Function.
 * @details This function draws edges of circle, without interior filling.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cx: X coordinate of center of the circle.
 * @param[in] cy: Y coordinate of center of the circle.
 * @param[in] width: Diameter of the circle.
 * @param[in] pen_color: The color in which the edges will be drawn.
 * @param[in] pen_width: Width of edges.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of color.
 *    uint16_t pen_color = 0xFFFF;
 *
 *    // These functions draw white edges of circle with width of 5
 *    // and with position of center at ( 100, 100 ) and with diameter of 100
 *    // and show on the screen.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_edges_circle( &ctx, 100, 100, 100, pen_color, 5 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_edges_circle( ft800_t *ctx, uint16_t cx, uint16_t cy, \
     uint16_t width, uint16_t pen_color, uint16_t pen_width );

/**
 * @brief Draw Circle Gradient Function.
 * @details This function draws the circle filled with specific colors with
 * gradient transition.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cx: X coordinate of center of the circle.
 * @param[in] cy: Y coordinate of center of the circle.
 * @param[in] diameter: Diameter of the circle.
 * @param[in] s_color: The starting color with which the circle will be filled.
 * @param[in] e_color: The final color with which the circle will be filled.
 * @param[in] gradient: Type of gradient transition.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of starting color.
 *    uint16_t pen_color = 0xF800;
 *    // Value of ending color.
 *    uint16_t pen_color = 0x001F;
 *
 *    // These functions fill a circular area with two-color gradient
 *    // centered at (50, 50) with a width of 100, and display it on
 *    // the FT800 screen.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_gradient_circle( &ctx, 50, 50, 100, s_color, \
 *     e_color, FT800_GRADIENT_TOP_BOTTOM );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_gradient_circle( ft800_t *ctx, uint16_t cx, uint16_t cy, \
     uint16_t diameter, uint16_t s_color, uint16_t e_color, ft800_gradient_style gradient );

/**
 * @brief Draw Ellipse's Edges Function.
 * @details This function draws edges of ellipse, without interior filling.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cx: X coordinate of center of the ellipse.
 * @param[in] cy: Y coordinate of center of the ellipse.
 * @param[in] width: Width of the ellipse.
 * @param[in] height: Height of the ellipse.
 * @param[in] pen_color: The color in which the edges will be drawn.
 * @param[in] pen_width: Width of edges.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of color.
 *    uint16_t pen_color = 0xFFFF;
 *
 *    // These functions draw white edges of the ellipse with width of 5
 *    // and with position of center at ( 100, 100 ) and with width of 100 and
 *    // height of 50 and show it on the screen.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_edges_ellipse( &ctx, 100, 100, 100, 50, \
 *    pen_color, 5 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_edges_ellipse( ft800_t *ctx, uint16_t cx, uint16_t cy, \
     uint16_t width, uint16_t height, uint16_t pen_color, uint16_t pen_width );

/**
 * @brief Draw Ellipse Gradient Function.
 * @details Draws an ellipse filled with a smooth gradient between two colors.
 * gradient transition.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x: X coordinate of center of the ellipse.
 * @param[in] y: Y coordinate of center of the ellipse.
 * @param[in] width: Width of the ellipse.
 * @param[in] height: Height of the ellipse.
 * @param[in] s_color: The starting color with which the ellipse will be filled.
 * @param[in] e_color: The final color with which the ellipse will be filled.
 * @param[in] gradient: Type of gradient transition.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of starting color.
 *    uint16_t pen_color = 0xF800;
 *    // Value of ending color.
 *    uint16_t pen_color = 0x001F;
 *
 *    // These functions fill an elliptical area with two-colored gradient
 *    // with position of center at ( 50, 50 ), width of 100 and height
 *    // of 50 and display them on the FT800 display.
 *
 *    ft800_draw_gradient_ellipse( &ctx, 50, 50, 100, s_color, \
 *    e_color, FT800_GRADIENT_TOP_BOTTOM );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_gradient_ellipse( ft800_t *ctx, uint16_t cx, uint16_t cy, \
     uint16_t width, uint16_t height, uint16_t s_color, uint16_t e_color, \
     ft800_gradient_style gradient );

/**
 * @brief Draw Rectangle Edges Function.
 * @details This function draws edges of rectangle, without interior filling.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] cx: X coordinate from which to start drawing the edges of rectangle.
 * @param[in] width Width of the rectangle.
 * @param[in] height Height of the rectangle.
 * @param[in] radius Radius of the rectangle's corner curves.
 * @param[in] radius: Radius of corners of edges of rectangle.
 * @param[in] color: The color in which the edges will be drawn.
 * @param[in] pen_width: Width of edges.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of color.
 *    uint16_t pen_color = 0xFFFF;
 *    // These functions draw white edges of a rectangle with width of 5
 *    // and from position ( 50, 50 ) with width of 100 and height of 100, with
 *    // radius of corners 10 and display them on the FT800 display.
 *    // radius of corners 10 and plot them on the FT800 display.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_edges_rectangle( &ctx, 50, 50, 100, 100,10, \
 *    color, 5 );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_edges_rectangle( ft800_t *ctx, uint16_t x, uint16_t y, \
     uint16_t width, uint16_t height,uint16_t radius, uint16_t color, uint8_t pen_width );

/**
 * @brief Draw Rectangle Gradient Function.
 * @details This function draws rectangular area filled with specific colors with
 * gradient transition.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x1: X coordinate from which to start drawing the filled rectangle.
 * @param[in] y1: Y coordinate from which to start drawing the filled rectangle.
 * @param[in] width: Width of the rectangular area.
 * @param[in] height: Height of the rectangular area.
 * @param[in] width: Width of the rectangular area.
 * @param[in] height: Height of the rectangular area.
 * @param[in] radius: Radius of the rectangular area's corner curves.
 * @param[in] gradient: Type of gradient transition.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of color.
 *    uint16_t pen_color = 0xFFFF;
 *    // gradient and from position ( 50, 50 ) with width of 100 and height of 100,
 *    // These functions fill rectangular area with two-colored gradient
 *    // from position ( 50, 50 ) with width of 100 and height of 100,
 *    // with radius of corners 10 and display them on the FT800 display.
 *    ft800_draw_gradient_rectangle( &ctx, 50, 50, 100, 100, 10, \
 *    s_color, e_color, FT800_GRADIENT_TOP_BOTTOM );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_gradient_rectangle( ft800_t *ctx, uint16_t x1, uint16_t y1, \
     uint16_t width, uint16_t height, uint16_t radius, uint16_t s_color, uint16_t e_color, \
     ft800_gradient_style gradient );

/**
 * @brief Draw Aligned Text Function.
 * @details This function draws text with the possibility of alignment.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x: X coordinate from which start drawing the text.
 * @param[in] y: Y coordinate from which start drawing the text.
 * @param[in] width: Width of object which the text is aligned.
 * @param[in] height: Height of object which the text is aligned.
 * @param[in] width: Width of the object which the text is aligned to.
 * @param[in] height: Height of the object which the text is aligned to.
 * @param[in] text_height: Height of the text.
 * @param[in] alignment: Type of the alignment.
 * @param[in] pen: Width of the edges of the object which the text is aligned to.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of color.
 *    uint16_t pen_color = 0xFFFF;
 *
 *    uint16_t pen_color = 0xFFFF;
 *    // These functions will draw the edges of the rectangle and text "FT800"
 *    // inside of them, aligned to the center of rectangle and display them on
 *    // the FT800 display.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_edges_rectangle( &ctx, 50, 50, 100, 50,10, \
 *    color, 5 );
 *    ft800_draw_aligned_text( &ctx, 50, 50, 100, 50, 80, \
 *    FT800_TEXT_ALIGNMENT_CENTER, 5, "FT800" );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_aligned_text( ft800_t *ctx, uint16_t x, uint16_t y, \
     uint16_t width, uint16_t height, uint16_t text_height, \
     ft800_text_alignment alignment, uint8_t pen, char *text );

/**
 * @brief Draw Aligned Text Function.
 * @details This function draws vertical text with the possibility of alignment.
 * @param[in] ctx : FT800 context object. See #ft800_t structure definition
 * for detailed explanation.
 * @param[in] x: X coordinate from which to start drawing the text.
 * @param[in] y: Y coordinate from which to start drawing the text.
 * @param[in] width: Width of the object which the text is aligned to.
 * @param[in] height: Height of the object which the text is aligned to.
 * @param[in] text_height: Height of the text.
 * @param[in] text_width: Width of the text.
 * @param[in] alignment: Type of the alignment.
 * @param[in] pen: Width of the edges of the object which the text is aligned to.
 * @param[in] text: Text being drawn.
 * @return Nothing.
 *
 * @b Example
 * @code
 *    // FT800 driver object.
 *    ft800_t ctx;
 *    // Value of color.
 *    uint16_t pen_color = 0xFFFF;
 *
 *    // These functions will draw the edges of the rectangle and vertical text "FT800"
 *    // inside of them, aligned to the center of the rectangle and display them on the
 *    // FT800 display.
 *    ft800_start_display_list( &ctx );
 *
 *    ft800_draw_edges_rectangle( &ctx, 50, 50, 100, 50,10, \
 *    color, 5 );
 *    ft800_draw_vertical_text( &ctx, 50, 50, 100, 50, 80, \
 *    FT800_TEXT_ALIGNMENT_CENTER, 5, "FT800" );
 *
 *    ft800_end_display_list( &ctx );
 * @endcode
 */
void ft800_draw_vertical_text( ft800_t *ctx, uint16_t x , uint16_t y, \
     uint16_t width, uint16_t height, uint16_t text_height, uint16_t text_width, \
     uint16_t pen, ft800_text_alignment alignment, char *text );

#endif // FT800_H

// ------------------------------------------------------------------------- END
