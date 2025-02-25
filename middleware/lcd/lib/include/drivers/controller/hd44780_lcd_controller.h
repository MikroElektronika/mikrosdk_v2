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
 * @file hd44780_lcd_controller.h
 * @brief LCD(Liquid Crystal Display) HD44780 Controller Driver.
 */

#ifndef _HD44780_LCD_CONTROLLER_H_
#define _HD44780_LCD_CONTROLLER_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"

/**
 * @addtogroup middlewaregroup Middleware
 * @brief This section includes the mikroSDK API Reference for Middleware Layer.
 * @{
 */

/*!
 * @addtogroup lcd LCD Driver
 * @brief Generic liquid crystal display APIs.
 * @{
 */

/*!
 * @addtogroup lcd_controller LCD Controller
 * @brief Generic liquid crystal display controller specific APIs.
 * @{
 */

/**
 * @brief Initializes LCD.
 * @details Initializes HD44780 LCD controller with default values.
 * @param[in] lcd_handle LCD handle address.
 * See #lcd_handle_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 * @code
 *  // LCD handle.
 *  lcd_handle_t lcd;
 *  // LCD config structure.
 *  lcd_config_t lcd_cfg;
 *  // Fill structure with default values.
 *  lcd_configure_default(&lcd_cfg);
 *  // Set default pins.
 *  LCD_MAP_PINS(lcd_cfg);
 *
 *  // Initialize handle and pins.
 *  lcd_configure(&lcd, &lcd_cfg);
 *  // Initialize LCD if used from LCD source.
 *  lcd_init(lcd, hd44780_lcd_init);
 *  // hd44780_lcd_init(&lcd); // If used directly through this API.
 * @endcode
 * @note Can be used with controllers similar to HD44780.
 * @note Dclared as @b weak so user can link their own API.
 */
void hd44780_lcd_init( uint32_t lcd_handle );

/*! @} */ // lcd_controller
/*! @} */ // lcd
/*! @} */ // middlewaregroup

#ifdef __cplusplus
}
#endif

#endif // _HD44780_LCD_CONTROLLER_H_

// ------------------------------------------------------------------------ END
