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

#ifndef _VTFT_DRAWING_H_
#define _VTFT_DRAWING_H_

#include "vtft_types.h"

// Global Function Declarations

/*! @addtogroup apigroup API
 *  @{
 */

/*! @addtogroup vtftgroup VTFT Library
 *  @{
 */

/**
 * @brief An empty drawing handle for components with an invalid type.
 *
 * @details An empty drawing handle for components with an invalid type.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component Component of invalid type. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_none(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given box component.
 *
 * @details Function uses Graphics Library to draw a box shape.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The box component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */

void _draw_box(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given rounded box component.
 *
 * @details Function uses Graphics Library to draw a rounded box shape.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The rounded box component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_rounded_box(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given circle component.
 *
 * @details Function uses Graphics Library to draw a circle.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The circle component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_circle(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given ellipse component.
 *
 * @details Function uses Graphics Library to draw a ellipse.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The ellipse component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_ellipse(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given line component.
 *
 * @details Function uses Graphics Library to draw a line.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The line component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_line(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given label component.
 *
 * @details Function uses Graphics Library to draw text.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The label component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_label(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given button component.
 *
 * @details Function uses Graphics Library to frst draw button shape, then writes text
 * over said shape.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The button component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_button(vtft_t *instance, const vtft_component *__generic_ptr component);

/**
 * @brief Draws the given rounded button component.
 *
 * @details Function uses Graphics Library to frst draw button shape, then writes text
 * over said shape.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The rounded button component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_rounded_button(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given circle button component.
 *
 * @details Function uses Graphics Library to frst draw circular button shape, then writes text
 * over said shape.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The circle component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_circle_button(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given image component.
 *
 * @details Function uses Graphics Library to draw an image. Supported formats are
 * 16bit BMP, 8bit BMP, 4bit BMP, 1bit BMP and JPEG.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The image component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_image(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given check box.
 *
 * @details Function uses Graphics Library to draw checkbox shape. It's in the nature of check box to change it's value
 * when checked or unchecked so the component itself should probably not be constant.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The check box component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_check_box(vtft_t *instance, const vtft_component * __generic_ptr component);

/**
 * @brief Draws the given radio button.
 *
 * @details Function uses Graphics Library to draw radio button shape. It's in the nature of radio button
 * to change it's value when checked or unchecked so the component itself should probably not be constant.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The radio button component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_radio_button(vtft_t *instance, vtft_component * __generic_ptr component);

/**
 * @brief Draws the given progress bar.
 *
 * @details Function uses Graphics Library to draw progres bar shape. It's in the nature of progress bar
 * to change it's value so the component itself should probably not be constant.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[in] component The progress bar component that will be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _draw_progress_bar(vtft_t *instance, vtft_component * __generic_ptr component);

/**
 * @brief Updates the position of the given progress bar.
 *
 * @details Some components can be constant due to the fact that their values can not be changed
 * while other components, such as progress bar, change their value
 * making them invalid for a const prameter.
 *
 * @param[in] instance Initialized VTFT library instance. See #vtft_t structure definition for detailed explanation.
 * @param[out] progressBar The progres bar component that will be updated. See #vtft_progress_bar structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void _update_progress_bar(vtft_t *instance, vtft_progress_bar * progressBar);

/*! @} */ // vtftgroup
/*! @} */ // apigroup

#endif // _VTFT_DRAWING_H_
