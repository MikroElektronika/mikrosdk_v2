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
 * @file  st7789.h
 * @brief ST7789 Display Controller Driver.
 */
#ifndef ST7789_H
#define ST7789_H
 
#include <stdint.h>
#include "hal_gpio.h"
#include "gl_types.h"
#include "generic_pointer.h"
 
/**
 * @brief ST7789 Configuration Object.
 * @details Configuration object definition for ST7789 display controller.
 */
typedef struct
{
    hal_pin_name_t rst;                      /*!< Reset pin. */
    hal_pin_name_t cs;                       /*!< Chip Select pin. Use HAL_PIN_NC if the display has no CS pin. */
    hal_pin_name_t d_c;                      /*!< Data/Command select pin */
    hal_pin_name_t sck;                      /*!< SPI clock pin (SCL).*/
    hal_pin_name_t miso;                     /*!< SPI MISO pin (not wired to the display, but required by the SPI driver). */
    hal_pin_name_t mosi;                     /*!< SPI data pin (SDA).*/
 
    uint32_t speed;                          /*!< SPI clock speed in Hz. Not used when soft_spi is 1. */
 
    uint16_t width;                          /*!< Display width. */
    uint16_t height;                         /*!< Display height. */
    uint8_t invert;                          /*!< 1 if the display colors need to be inverted, 0 if not. */
    uint8_t spi_mode;                        /*!< SPI mode (0 to 3). Default is 0. Not used when soft_spi is 1. */
    const uint8_t *init_seq;                 /*!< Optional extra init commands: command, number of parameters, parameters..., ends with 0. NULL if not used. */
    uint8_t soft_spi;                        /*!< 1 to send the data with software SPI (GPIO pins), 0 for the SPI module. */
} st7789_cfg_t;
/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */
 
/*!
 * @addtogroup st7789 ST7789 Display Controller Driver
 * @brief ST7789 Display Controller Driver API reference.
 * @details API for configuring and manipulating ST7789 Display Controller driver.
 * @{
 */
 
/**
 * @brief ST7789 Display Controller initialization.
 * @details This function initializes the control pins, the SPI module and the ST7789 Display Controller, and links the driver interface object with the ST7789 driver functions. If the SPI module can not be opened, the driver interface object is left untouched.
 * @param[in] cfg : ST7789 configuration object. See #st7789_cfg_t structure definition for detailed explanation.
 * @param[out] driver : Graphics Library driver interface object. See #gl_driver_t structure definition and #gl_set_driver function for detailed explanation.
 * @return Nothing.
 */
void st7789_init(st7789_cfg_t *cfg, gl_driver_t * __generic_ptr driver);
 
/**
 * @brief Send command to ST7789 Display Controller.
 * @details This function sends command to ST7789 Display Controller.
 * @param[in] command : command to be sent. See @ref st7789_commands for command list.
 * @return Nothing.
 */
void st7789_write_command(uint8_t command);
 
/**
 * @brief Send data to ST7789 Display Controller.
 * @details This function sends data to ST7789 Display Controller.
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void st7789_write_param(uint8_t param);
 
/**
 * @brief Get display width.
 * @details This function returns the width of the ST7789 controller based display.
 * @return Display width.
 */
uint16_t st7789_get_display_width();
 
/**
 * @brief Get display height.
 * @details This function returns the height of the ST7789 controller based display.
 * @return Display height.
 */
uint16_t st7789_get_display_height();
 
/**
 * @brief Change display rotation.
 * @details This function changes the orientation / rotation of the ST7789 display.
 * @param[in] rotation : Rotation mode (0, 1, 2, 3).
 * @return Nothing.
 */
void st7789_rotate(uint8_t rotation);
 
/**
 * @brief Turn display on or off.
 * @details This function turns the display output on or off.
 * @param[in] state : 1 for ON, 0 for OFF.
 * @return Nothing.
 */
void st7789_display_power(uint8_t state);
 
/**
 * @brief Send pixel data to ST7789 Display Controller.
 * @details Call it after the window is set (begin frame) and before end frame.
 * Data is sent as is, high byte of each RGB565 pixel first.
 * @param[in] data : pixel bytes.
 * @param[in] length : number of bytes to send.
 * @return Nothing.
 */
void st7789_write_pixels(const uint8_t *data, uint32_t length);
 
/*! @} */ // st7789
/*! @} */ // mwgroup
 
#endif // ST7789_H
// ------------------------------------------------------------------------- END
