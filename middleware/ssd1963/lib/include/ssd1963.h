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
/*!
 * @file  ssd1963.h
 * @brief SSD1963 Display Controller Driver.
 */

#ifndef SSD1963_H
#define SSD1963_H

#include <stdint.h>
#include "hal_gpio.h"
#include "gl_types.h"
#include "generic_pointer.h"

/**
 * @brief SSD1963 Interface Mode.
 * @details interface mode for SSD1963 display controller.
 */
typedef enum
{
    SSD1963_HOST_INTERFACE_8BIT = 0, /*!< 8-bit mode */
    SSD1963_HOST_INTERFACE_16BIT,    /*!< 16-bit mode. */
    SSD1963_HOST_INTERFACE_CUSTOM    /*!< Custom mode. */
} ssd1963_host_interface_t;

/**
 * @brief SSD1963 Configuration Object.
 * @details Configuration object definition for SSD1963 display controller.
 */
typedef struct
{
    hal_pin_name_t rst;                      /*!< Reset pin. */
    hal_pin_name_t cs;                       /*!< Chip Select pin. */
    hal_pin_name_t d_c;                      /*!< Data/Command select pin */
    hal_pin_name_t rd;                       /*!< Read pin */
    hal_pin_name_t wr;                       /*!< Write pin. */

    hal_port_name_t data_channel_0;          /*!< 8-bit data port. */
    uint32_t data_channel_0_mask;            /*!< Data port mask. */

    hal_port_name_t data_channel_1;          /*!< 8-bit data port. */
    uint32_t data_channel_1_mask;            /*!< Data port mask. */

    ssd1963_host_interface_t host_interface; /*!< Device mode. See #ssd1963_host_interface_t structure definition for detailed explanation. */

    uint16_t  width;                         /*!< Display width. */
    uint16_t height;                         /*!< Display height. */

    // ssd1963_color_depth_t color_depth;
} ssd1963_cfg_t;

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ssd1963 SSD1963 Display Controller Driver
 * @brief SSD1963 Display Controller Driver API reference.
 * @details API for configuring and manipulating SSD1963 Display Controller driver.
 * @{
 */

/**
 * @brief SSD1963 Display Controller initialization.
 * @details This function initializes SSD1963 Display Controller context object to default values and allows driver interface object to be linked with SSD1963 Display Controller driver functions.
 * @param[in] cfg : SSD1963 configuration object. See #ssd1963_cfg_t structure definition for detailed explanation.
 * @param[out] driver : Graphics Library driver interface object. See #gl_driver_t structure definition and #gl_set_driver function for detailed explanation.
 * @return Nothing.
 */
void ssd1963_init(ssd1963_cfg_t *cfg, gl_driver_t * __generic driver);

/**
 * @brief Send command to SSD1963 Display Controller.
 * @details This function sends command to SSD1963 Display Controller.
 * @param[in] command : command to be sent. See @ref ssd1963_commands for command list.
 * @return Nothing.
 */
void ssd1963_write_command(uint8_t command);

/**
 * @brief Send data to SSD1963 Display Controller.
 * @details This function sends data to SSD1963 Display Controller.
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void ssd1963_write_param(uint8_t param);

/**
 * @brief Get display width.
 * @details This function returns the width of the SSD1963 controller based display.
 * @return Display width.
 */
uint16_t ssd1963_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the SSD1963 controller based display.
 * @return Display height.
 */
uint16_t ssd1963_get_display_height();

/*! @} */ // ssd1963
/*! @} */ // mwgroup

#endif // SSD1963_H
// ------------------------------------------------------------------------- END
