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
 * @file  gc9107_gl.h
 * @brief GC9107 Graphics Library adapter.
 */
#ifndef GC9107_GL_H
#define GC9107_GL_H

#include <stdint.h>
#include "gc9107.h"
#include "gl_types.h"

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup gc9107_gl GC9107 Graphics Library Adapter
 * @brief GC9107 Graphics Library adapter API reference.
 * @details Links the GC9107 driver with the Graphics Library (gl_* functions)
 *          and adds rotation and display power control.
 * @{
 */

/**
 * @brief GC9107 Graphics Library adapter initialization.
 * @details Initializes the GC9107 driver and the display, turns the backlight
 * on and links the driver interface object with the GC9107 functions.
 * @param[in] cfg : GC9107 configuration object. See #gc9107_cfg_t.
 * @param[out] driver : Graphics Library driver interface object. See
 * #gl_driver_t and #gl_set_driver.
 * @return Nothing.
 */
void gc9107_gl_init( gc9107_cfg_t *cfg, gl_driver_t *driver );

/**
 * @brief Get display width.
 * @details Returns the current width, which depends on the rotation.
 * @return Display width.
 */
uint16_t gc9107_gl_get_display_width();

/**
 * @brief Get display height.
 * @details Returns the current height, which depends on the rotation.
 * @return Display height.
 */
uint16_t gc9107_gl_get_display_height();

/**
 * @brief Change display rotation.
 * @param[in] rotation : Rotation mode (0, 1, 2, 3).
 * @return Nothing.
 */
void gc9107_gl_rotate( uint8_t rotation );

/**
 * @brief Turn display on or off.
 * @param[in] state : 1 for ON, 0 for OFF.
 * @return Nothing.
 */
void gc9107_gl_display_power( uint8_t state );

/**
 * @brief Send pixel data to GC9107 Display Controller.
 * @details Call it after the window is set (begin frame) and before end frame.
 * Data is sent as is, high byte of each RGB565 pixel first.
 * @param[in] data : pixel bytes.
 * @param[in] length : number of bytes to send.
 * @return Nothing.
 */
void gc9107_gl_write_pixels( uint8_t *data, uint32_t length );

/*! @} */ // gc9107_gl
/*! @} */ // middlewaregroup

#endif // GC9107_GL_H
// ------------------------------------------------------------------------- END