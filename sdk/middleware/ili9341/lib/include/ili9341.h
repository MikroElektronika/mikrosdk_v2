/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  ili9341.h
 * @brief ILI9341 Display Controller Driver.
 */

#ifndef _ILI9341_H_
#define _ILI9341_H_

#include "drv_pwm.h"
#include "tp_mikroe.h"
#include "ili9341_cmd.h"
#include "ili9341_defines.h"
#include "drv_port.h"

/*!
 * \brief Mapping for PWM config structure.
 */
#define ILI9341_PWM_CONFIG( ili9341_cfg ) \
    ili9341_cfg.pwm_cfg.pin = TFT_BPWM;\
    ili9341_cfg.pwm_cfg.freq_hz = (5000);

/**
 * @brief ILI9341 Interface Mode.
 * @details interface mode for ILI9341 display controller.
 */
typedef enum
{
    ILI9341_HOST_INTERFACE_8BIT = 0, /*!< 8-bit mode. */
    ILI9341_HOST_INTERFACE_16BIT     /*!< 16-bit mode. */
} ili9341_host_interface_t;

 /*!
 * \brief Mapping structure for display orientation.
 */
typedef enum
{
    ILI9341_MODE_LANDSCAPE_UP = 0,
    ILI9341_MODE_PORTRAIT_LEFT,
    ILI9341_MODE_LANDSCAPE_DOWN,
    ILI9341_MODE_PORTRAIT_RIGHT
} ili9341_orientation_t;

/**
 * @brief ILI9341 Configuration Object.
 * @details Configuration object definition for ILI9341 display controller.
 */
typedef struct
{
    pin_name_t rst;   /*!< Reset pin. */
    pin_name_t cs;    /*!< Chip Select pin. */
    pin_name_t rs;    /*!< Data/Command select pin. */
    pin_name_t rd;    /*!< Read pin. */
    pin_name_t wr;    /*!< Write pin. */

    hal_port_name_t data_channel_0; /*!< 8-bit data port. */
    uint32_t data_channel_0_mask;   /*!< Data port mask. */

    hal_port_name_t data_channel_1; /*!< 8-bit data port. */
    uint32_t data_channel_1_mask;   /*!< Data port mask. */

    ili9341_orientation_t orientation; /*!< Display orientation. */

    ili9341_host_interface_t host_interface; /*!< Device mode. */

    pwm_config_t pwm_cfg; /*!< PWM configuration structure. */

    uint16_t width;  /*!< Display width. */
    uint16_t height; /*!< Display height. */
} ili9341_cfg_t;

/**
 * @brief ILI9341 Context Object.
 * @details Context object definition for ILI9341 display controller.
 */
typedef struct
{
    tp_rotate_t rotate;    /**< Panel rotation. */

    pwm_t pwm; /*!< PWM context structure. */

    uint16_t width;  /**< Touch panel width in pixels. */
    uint16_t height; /**< Touch panel height in pixels. */
} ili9341_t;

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ili9341 ILI9341 Display Controller Driver
 * @brief ILI9341 Display Controller Driver API reference.
 * @details API for configuring and manipulating ILI9341 Display Controller driver.
 * @{
 */

/**
 * @brief ILI9341 Display Controller initialization.
 * @details This function initializes ILI9341 Display Controller context object to default values and allows
 * driver interface object to be linked with ILI9341 Display Controller driver functions.
 * @param[in] cfg : ILI9341 configuration object. See #ili9341_cfg_t structure definition for detailed explanation.
 * @param[out] driver : Graphics Library driver interface object. See #gl_driver_t structure definition and #gl_set_driver function for detailed explanation.
 * @return Nothing.
 */
void ili9341_init( ili9341_cfg_t *cfg, gl_driver_t *__generic_ptr driver, ili9341_t *ctx );

/**
 * @brief ILI9341 Default Configuration Function.
 * @details This function initializes PWM default configuration.
 * @param[in] cfg : ILI9341 configuration object.
 * See #ili9341_cfg_t structure definition for detailed explanation.
 * @retval Nothing.
 */
void ili9341_default_cfg( ili9341_cfg_t *cfg );

/**
 * @brief Send command to ILI9341 Display Controller.
 * @details This function sends command to ILI9341 Display Controller.
 * @param[in] command : command to be sent. See @ref ili9341_commands for command list.
 * @return Nothing.
 */
void ili9341_write_command( uint8_t command );

/**
 * @brief Send data to ILI9341 Display Controller.
 * @details This function sends data to ILI9341 Display Controller.
 * @param[in] param : data to be sent.
 * @return Nothing.
 */
void ili9341_write_param( uint8_t param );

/**
 * @brief Get display width.
 * @details This function returns the width of the ILI9341 controller based display.
 * @return Display width.
 */
uint16_t ili9341_get_display_width();

/**
 * @brief Get display height.
 * @details This function returns the height of the ILI9341 controller based display.
 * @return Display height.
 */
uint16_t ili9341_get_display_height();

/**
 * @brief ILI9341 Display Controller PWM initialization.
 * @details Initialize PWM module for controlling display backlight intensity.
 * @return Nothing.
 */
void ili9341_backlight_control_init( ili9341_cfg_t *cfg, ili9341_t *ctx );

/**
 * @brief ILI9341 Display controller backlight intensity.
 * @details Set active intensity of display controller.
 * @return Nothing.
 */
void ili9341_set_backlight_intensity( float intensity, ili9341_t *ctx );

/**
 * @brief Function used for changing display rotation.
 * @details This function is necessary for interfacing with touch panel library as it's
 * address is stored in tp_drv_t driver structure during the ILI9341 context initialization.
 * @param[out] ctx Initialized ILI9341 context structure. See @ref ili9341_t for more
 * information about the context structure.
 * @param[in] rotate Structure with desired orientation set.
 * @return Nothing.
 */
void ili9341_rotate( ili9341_t *ctx, tp_rotate_t *rotate );

/*! @} */ // ili9341
/*! @} */ // mwgroup

#endif // _ILI9341_H_
// ------------------------------------------------------------------------- END
