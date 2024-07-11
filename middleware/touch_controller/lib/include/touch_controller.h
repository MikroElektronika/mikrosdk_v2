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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
 * @file  touch_controller.h
 * @brief Touch controller middle layer API.
 */

#ifndef _TOUCH_CONTROLLER_H_
#define _TOUCH_CONTROLLER_H_

#ifdef __cplusplus
extern "C"{
#endif

#if defined(ft5xx6)
    #include "ft5xx6.h"
    #include "tft8.h"
#elif defined(stmpe811)
    #include "stmpe811.h"
    #include "tft8.h"
#elif defined(tsc2003)
    #include "tsc2003.h"
    #include "tft8.h"
#elif defined(tp_mikroe)
    #include "tp_mikroe.h"
    #include "tft7.h"
#else
    #error "touch_ic not defined"
#endif

#include "tp.h"
#include "board.h"

/**
 * @brief Initializes touch controller.
 *
 * @param display_driver Pointer to @ref gl_driver_t structure.
 * @param backlight Value for display backround lighting.
 *
 * @b Example
 * @code
 *   // Display driver.
 *   gl_driver_t my_display_driver;
 *   // Pass to function.
 *   touch_controller_init(&my_display_driver, 255);
 * @endcode
 */
void touch_controller_init(gl_driver_t* display_driver, uint8_t backlight);

/**
 * @brief Initializes touch panel.
 *
 * @param tp Pointer to @ref tp_t structure.
 * @param tp_interface Pointer to @ref tp_drv_t structure.
 *
 * @b Example
 * @code
 *   // Display driver
 *   tp_t touch_panel;
 *   tp_drv_t touch_interface;
 *   // Pass to function.
 *   touch_controller_tp_init(&touch_panel, &touch_interface);
 * @endcode
 */
void touch_controller_tp_init(tp_t* tp, tp_drv_t *tp_interface);

#ifdef __cplusplus
}
#endif

#endif // _TOUCH_CONTROLLER_H_
