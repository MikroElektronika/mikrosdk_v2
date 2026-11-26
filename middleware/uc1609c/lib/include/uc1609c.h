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
 * @file  uc1609c.h
 * @brief UC1609C Display Controller Driver (192x64 monochrome LCD, SPI).
 */
#ifndef UC1609C_H
#define UC1609C_H

#include <stdint.h>
#include "hal_gpio.h"
#include "gl_types.h"
#include "generic_pointer.h"

#define UC1609C_MAX_WIDTH   192   /*!< Maximum supported width in pixels. */
#define UC1609C_MAX_HEIGHT  64   /*!< Maximum supported height in pixels. */

/**
 * @brief UC1609C Configuration Object.
 * @details Configuration object definition for UC1609C display controller.
 */
typedef struct
{
    hal_pin_name_t rst;                      /*!< Reset pin. */
    hal_pin_name_t cs;                       /*!< Chip Select pin. */
    hal_pin_name_t d_c;                      /*!< Data/Command select pin (CD). */
    hal_pin_name_t sck;                      /*!< SPI clock pin (SCK). */
    hal_pin_name_t miso;                     /*!< SPI MISO pin (not wired, required by the SPI driver). */
    hal_pin_name_t mosi;                     /*!< SPI data pin (SDA). */

    uint32_t speed;                          /*!< SPI speed in Hz (the datasheet allows about 12 MHz for writing). */

    uint16_t width;                          /*!< Panel width in pixels (max 192). */
    uint16_t height;                         /*!< Panel height in pixels (max 64). */
    uint8_t contrast;                        /*!< Contrast (0x00 - 0xFF). */
    uint8_t invert;                          /*!< 1 = invert the display (pixel off = lit), 0 = normal. */
    const uint8_t *init_seq;                 /*!< Extra init commands: cmd, count, params..., 0. NULL if unused. */
} uc1609c_cfg_t;
/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup uc1609c UC1609C Display Controller Driver
 * @brief UC1609C Display Controller Driver API reference.
 * @details The UC1609C is a monochrome (1 bit per pixel) controller. The driver keeps a frame buffer in RAM
 * (one bit per pixel) and sends the changed pages to the display. Colors passed by the Graphics Library are
 * converted to black / white: everything darker than half brightness is off, the rest is on.
 * @{
 */

/**
 * @brief UC1609C Display Controller initialization.
 * @details This function initializes the control pins, the SPI module and the UC1609C Display Controller,
 * and links the driver interface object with the UC1609C driver functions. If the SPI module can not be
 * opened, the driver interface object is left untouched.
 * @param[in] cfg : UC1609C configuration object. See #uc1609c_cfg_t structure definition for detailed explanation.
 * @param[out] driver : Graphics Library driver interface object. See #gl_driver_t structure definition
 * and #gl_set_driver function for detailed explanation.
 * @return Nothing.
 */
void uc1609c_init(uc1609c_cfg_t *cfg, gl_driver_t * __generic_ptr driver);

/**
 * @brief Send command to UC1609C Display Controller.
 * @details This function sends command to UC1609C Display Controller.
 * @param[in] command : command to be sent. See @ref uc1609c_commands for command list.
 * @return Nothing.
 */
void uc1609c_write_command(uint8_t command);

/**
 * @brief Send command parameter byte to UC1609C Display Controller.
 * @details This function sends one command parameter byte (for example the contrast value).
 * @param[in] param : parameter to be sent.
 * @return Nothing.
 */
void uc1609c_write_param(uint8_t param);

/**
 * @brief Get display width.
 * @details This function returns the width of the UC1609C controller based display (depends on rotation).
 * @return Display width.
 */
uint16_t uc1609c_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the UC1609C controller based display (depends on rotation).
 * @return Display height.
 */
uint16_t uc1609c_get_display_height();

/**
 * @brief Change display rotation.
 * @details The rotation is done in software while the frame buffer is written.
 * @param[in] rotation : Rotation mode (0, 1, 2, 3).
 * @return Nothing.
 */
void uc1609c_rotate(uint8_t rotation);

/**
 * @brief Turn display on or off.
 * @details This function turns the display output on or off.
 * @param[in] state : 1 for ON, 0 for OFF.
 * @return Nothing.
 */
void uc1609c_display_power(uint8_t state);

/**
 * @brief Set display contrast.
 * @param[in] contrast : 0x00 - 0xFF.
 * @return Nothing.
 */
void uc1609c_set_contrast(uint8_t contrast);

/**
 * @brief Set one pixel in the frame buffer.
 * @details The display is not updated until uc1609c_update is called. Coordinates are in the current rotation.
 * @param[in] x : X coordinate.
 * @param[in] y : Y coordinate.
 * @param[in] on : 1 pixel on, 0 pixel off.
 * @return Nothing.
 */
void uc1609c_draw_pixel(uint16_t x, uint16_t y, uint8_t on);

/**
 * @brief Send an area of the frame buffer to the display.
 * @details Coordinates are in the current rotation (inclusive). Whole 8 pixel high pages are sent.
 * @param[in] x1 : Left.
 * @param[in] y1 : Top.
 * @param[in] x2 : Right.
 * @param[in] y2 : Bottom.
 * @return Nothing.
 */
void uc1609c_update(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/*! @} */ // uc1609c
/*! @} */ // mwgroup

#endif // UC1609C_H
// ------------------------------------------------------------------------- END
