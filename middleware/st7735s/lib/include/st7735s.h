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
 * @file  st7735s.h
 * @brief ST7735S Display Controller Driver.
 */
#ifndef ST7735S_H
#define ST7735S_H

#include <stdint.h>
#include "hal_gpio.h"
#include "gl_types.h"
#include "generic_pointer.h"

/**
 * @brief ST7735S Configuration Object.
 * @details Configuration object definition for ST7735S display controller.
 */
typedef struct
{
    hal_pin_name_t rst;                      /*!< Reset pin. */
    hal_pin_name_t cs;                       /*!< Chip Select pin. */
    hal_pin_name_t d_c;                      /*!< Data/Command select pin */
    hal_pin_name_t sck;                      /*!< SPI clock pin (SCL).*/
    hal_pin_name_t miso;                     /*!< SPI MISO pin (not wired to the display, but required by the SPI driver). */
    hal_pin_name_t mosi;                     /*!< SPI data pin (SDA).*/

    uint32_t speed;

    uint16_t width;                          /*!< Panel width in pixels (the visible area). */
    uint16_t height;                         /*!< Panel height in pixels (the visible area). */
    uint16_t ram_width;                      /*!< Controller memory width in pixels (128 or 132, depends on the GM pins of the module). */
    uint16_t ram_height;                     /*!< Controller memory height in pixels (160, 132 or 162, depends on the GM pins of the module). */
    uint16_t col_offset;                     /*!< Column offset of the panel inside the controller memory, for rotation 0. */
    uint16_t row_offset;                     /*!< Row offset of the panel inside the controller memory, for rotation 0. */
    uint8_t invert;                          /*!< 1 if the display colors need to be inverted, 0 if not. */
    uint8_t bgr;                             /*!< 1 if the panel has BGR color order (sets the RGB bit in MADCTL), 0 for RGB. */
    const uint8_t *init_seq;                 /*!< Optional extra init commands: command, number of parameters, parameters..., ends with 0. NULL if not used. */
} st7735s_cfg_t;
/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup st7735s ST7735S Display Controller Driver
 * @brief ST7735S Display Controller Driver API reference.
 * @details API for configuring and manipulating ST7735S Display Controller driver.
 * @{
 */

/**
 * @brief ST7735S Display Controller initialization.
 * @details This function initializes the control pins, the SPI module and the ST7735S Display Controller, and links the driver interface object with the ST7735S driver functions. If the SPI module can not be opened, the driver interface object is left untouched.
 * @param[in] cfg : ST7735S configuration object. See #st7735s_cfg_t structure definition for detailed explanation.
 * @param[out] driver : Graphics Library driver interface object. See #gl_driver_t structure definition and #gl_set_driver function for detailed explanation.
 * @return Nothing.
 */
void st7735s_init(st7735s_cfg_t *cfg, gl_driver_t * __generic_ptr driver);

/**
 * @brief Send command to ST7735S Display Controller.
 * @details This function sends command to ST7735S Display Controller.
 * @param[in] command : command to be sent. See @ref st7735s_commands for command list.
 * @return Nothing.
 */
void st7735s_write_command(uint8_t command);

/**
 * @brief Send data to ST7735S Display Controller.
 * @details This function sends data to ST7735S Display Controller.
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void st7735s_write_param(uint8_t param);

/**
 * @brief Get display width.
 * @details This function returns the width of the ST7735S controller based display.
 * @return Display width.
 */
uint16_t st7735s_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the ST7735S controller based display.
 * @return Display height.
 */
uint16_t st7735s_get_display_height();

/**
 * @brief Change display rotation.
 * @details This function changes the orientation / rotation of the ST7735S display.
 * @param[in] rotation : Rotation mode (0, 1, 2, 3).
 * @return Nothing.
 */
void st7735s_rotate(uint8_t rotation);

/**
 * @brief Turn display on or off.
 * @details This function turns the display output on or off.
 * @param[in] state : 1 for ON, 0 for OFF.
 * @return Nothing.
 */
void st7735s_display_power(uint8_t state);

/**
 * @brief Send pixel data to ST7735S Display Controller.
 * @details Call it after the window is set (begin frame) and before end frame.
 * Data is sent as is, high byte of each RGB565 pixel first.
 * @param[in] data : pixel bytes.
 * @param[in] length : number of bytes to send.
 * @return Nothing.
 */
void st7735s_write_pixels(const uint8_t *data, uint32_t length);

/*! @} */ // st7735s
/*! @} */ // mwgroup

#endif // ST7735S_H
// ------------------------------------------------------------------------- END