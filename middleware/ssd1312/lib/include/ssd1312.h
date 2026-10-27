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
 * @file  ssd1312.h
 * @brief SSD1312 Display Controller Driver (monochrome OLED, I2C, tested on a 64x128 module).
 */
#ifndef SSD1312_H
#define SSD1312_H

#include <stdint.h>
#include "hal_gpio.h"
#include "gl_types.h"
#include "generic_pointer.h"

#define SSD1312_MAX_WIDTH   128 /*!< Maximum supported width in pixels. */
#define SSD1312_MAX_HEIGHT  128 /*!< Maximum supported height in pixels. */

/**
 * @brief SSD1312 Configuration Object.
 * @details Configuration object definition for SSD1312 display controller.
 */
typedef struct
{
    hal_pin_name_t rst;                      /*!< Reset pin. */
    hal_pin_name_t scl;                      /*!< I2C clock pin (SCL). */
    hal_pin_name_t sda;                      /*!< I2C data pin (SDA). */

    uint8_t address;                         /*!< 7-bit I2C slave address (0x3C or 0x3D). */
    uint32_t speed;                          /*!< I2C speed (I2C_MASTER_SPEED_STANDARD or I2C_MASTER_SPEED_FULL). */

    uint16_t width;                          /*!< Panel width in pixels (max 128, 64 for the 64x128 module). */
    uint16_t height;                         /*!< Panel height in pixels (max 128). */
    uint8_t col_offset;                      /*!< First RAM column used by the panel (0 for the 64x128 module). */
    uint8_t display_offset;                  /*!< Display offset (COM shift), see datasheet. 0 if unused. */
    uint8_t contrast;                        /*!< Contrast (0x00 - 0xFF). */
    uint8_t invert;                          /*!< 1 = invert the display (pixel off = lit), 0 = normal. */
    const uint8_t *init_seq;                 /*!< Extra init commands: cmd, count, params..., 0. NULL if unused. */
} ssd1312_cfg_t;
/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ssd1312 SSD1312 Display Controller Driver
 * @brief SSD1312 Display Controller Driver API reference.
 * @details The SSD1312 is a monochrome (1 bit per pixel) controller. The driver keeps a frame buffer in RAM
 * (one bit per pixel) and sends the changed pages to the display. Colors passed by the Graphics Library are
 * converted to black / white: everything darker than half brightness is off, the rest is on.
 * @{
 */

/**
 * @brief SSD1312 Display Controller initialization.
 * @details This function initializes the pins, the I2C module and the SSD1312 Display Controller
 * and links the driver interface object with the SSD1312 driver functions. If the I2C module can not
 * be opened, the driver interface object is left untouched.
 * @param[in] cfg : SSD1312 configuration object. See #ssd1312_cfg_t structure definition for detailed explanation.
 * @param[out] driver : Graphics Library driver interface object. See #gl_driver_t structure definition
 * and #gl_set_driver function for detailed explanation.
 * @return Nothing.
 */
void ssd1312_init(ssd1312_cfg_t *cfg, gl_driver_t * __generic_ptr driver);

/**
 * @brief Send command to SSD1312 Display Controller.
 * @details This function sends command to SSD1312 Display Controller.
 * @param[in] command : command to be sent. See @ref ssd1312_commands for command list.
 * @return Nothing.
 */
void ssd1312_write_command(uint8_t command);

/**
 * @brief Send data byte to SSD1312 Display Controller.
 * @details This function sends one byte to the display RAM (or a command parameter).
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void ssd1312_write_param(uint8_t param);

/**
 * @brief Get display width.
 * @details This function returns the width of the SSD1312 controller based display (depends on rotation).
 * @return Display width.
 */
uint16_t ssd1312_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the SSD1312 controller based display (depends on rotation).
 * @return Display height.
 */
uint16_t ssd1312_get_display_height();

/**
 * @brief Change display rotation.
 * @details The rotation is done in software while the frame buffer is written.
 * @param[in] rotation : Rotation mode (0, 1, 2, 3).
 * @return Nothing.
 */
void ssd1312_rotate(uint8_t rotation);

/**
 * @brief Turn display on or off.
 * @details This function turns the display output on or off.
 * @param[in] state : 1 for ON, 0 for OFF.
 * @return Nothing.
 */
void ssd1312_display_power(uint8_t state);

/**
 * @brief Set display contrast.
 * @param[in] contrast : 0x00 - 0xFF.
 * @return Nothing.
 */
void ssd1312_set_contrast(uint8_t contrast);

/**
 * @brief Set one pixel in the frame buffer.
 * @details The display is not updated until ssd1312_update is called. Coordinates are in the current rotation.
 * @param[in] x : X coordinate.
 * @param[in] y : Y coordinate.
 * @param[in] on : 1 pixel on, 0 pixel off.
 * @return Nothing.
 */
void ssd1312_draw_pixel(uint16_t x, uint16_t y, uint8_t on);

/**
 * @brief Send an area of the frame buffer to the display.
 * @details Coordinates are in the current rotation (inclusive). Whole 8 pixel high pages are sent.
 * @param[in] x1 : Left.
 * @param[in] y1 : Top.
 * @param[in] x2 : Right.
 * @param[in] y2 : Bottom.
 * @return Nothing.
 */
void ssd1312_update(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/*! @} */ // ssd1312
/*! @} */ // mwgroup

#endif // SSD1312_H
// ------------------------------------------------------------------------- END
