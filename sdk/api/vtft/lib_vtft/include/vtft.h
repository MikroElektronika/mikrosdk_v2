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
 * \file
 */
#ifndef _VTFT_H_
#define _VTFT_H_

#include "vtft_types.h"

/*! @addtogroup apigroup API
 *  @{
 */

/*! @addtogroup vtftgroup VTFT Library
 *  @{
 */

/*!
 * @brief Initializes the VTFT library with the given gl and tp instances.
 * @details Initializes the VTFT library with the given gl and tp instances.
 * @param[out] vtft_instance VTFT instance to be initialized. See #vtft_t structure definition for detailed explanation.
 *
 * @param[in] tp_instance TP instance. See #tp_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void vtft_init(vtft_t *vtft_instance, tp_t * tp_instance);

/*!
 * @brief Sets the position of the given progress bar.
 * @details Sets the position of the given progress bar.
 * @param[in] instance Initialized VTFT instance.  See #vtft_t structure definition for detailed explanation.
 *
 * @param[in] progress_bar Progress bar whose position is going to be set. See #vtft_progress_bar structure definition for detailed explanation.
 *
 * @param[in] position Position to be set. See #vtft_ucoord_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void vtft_set_progress_bar_position(
    vtft_t *instance,
    vtft_progress_bar *progress_bar,
    vtft_ucoord_t position);

/*!
 * @brief Draws the given component, using the appropriate drawing function.
 * @details Draws the given component, using the appropriate drawing function.
 * @param[in] instance Initialized VTFT instance. See #vtft_t structure definition for detailed explanation.
 *
 * @param[in] component Component to be drawn. See #vtft_component structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void vtft_draw_component(vtft_t *instance, const vtft_component * __generic_ptr component);

/*!
 * @brief Redraws the current screen and all of its components.
 * @details Redraws the current screen and all of its components.
 * @param[in] instance Initialized VTFT instance. See #vtft_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void vtft_refresh_current_screen(vtft_t *instance);

/*!
 * @brief Sets the current screen and draws it.
 * @details Sets the current screen and draws it.
 * @param[in] instance Initialized VTFT instance. See #vtft_t structure definition for detailed explanation.
 *
 * @param[in] screen  Screen to be set as current. See #vtft_screen structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void vtft_set_current_screen(vtft_t *instance, vtft_screen *screen);

/*!
 * @brief Processes the periodic events.
 * @details Processes the periodic events.
 * @param[in] instance Initialized VTFT instance. See #vtft_t structure definition for detailed explanation.
 *
 * @return Nothing.
 *
 * @b Example
 */
void vtft_process(vtft_t *instance);

/*! @} */ // vtftgroup
/*! @} */ // apigroup

#endif // _VTFT_H_
// ------------------------------------------------------------------------- END
