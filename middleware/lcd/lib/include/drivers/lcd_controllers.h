/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
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
 * @file  lcd_controllers.h
 * @brief mikroSDK supported LCD controller list.
 */

#ifndef __LCD_CONTROLLERS_H__
#define __LCD_CONTROLLERS_H__

#ifdef __cplusplus
extern "C" {
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
 * @brief File includes all available LCD controllers.
 */

// Include Hitachi HD44780 LCD controller driver.
#include "hd44780_lcd_controller.h"

/*! @} */ // lcd_controller
/*! @} */ // lcd
/*! @} */ // middlewaregroup

#ifdef __cplusplus
}
#endif

#endif // __LCD_CONTROLLERS_H__
