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

#include "vtft.h"
#include <string.h>
#include "vtft_drawing.h"
#include "vtft_touch.h"
#include "gl.h"
#include "tp.h"

extern void _tp_event_handler( tp_event_t event, uint16_t x, uint16_t y, tp_touch_id_t i);
// Local Variable Definitions


// Draws the given screen and all of its components.
void _draw_screen(vtft_t *instance, const vtft_screen * __generic_ptr screen)
{
    uint32_t index = 0;

    gl_clear(screen->color);

    while (index < screen->component_count)
        vtft_draw_component(instance, screen->components[index++]);
}

// Global Function Definitions

// Initializes the VTFT library with the given tp instance.
void vtft_init(vtft_t *vtft_instance, tp_t * tp_instance)
{
    memset(vtft_instance, 0x00, sizeof(vtft_t));
    vtft_instance->tp_instance = tp_instance;

    tp_press_callback_setup(tp_instance, _tp_event_handler);

    vtft_instance->draw_handles[VTFT_COMPONENT_BOX] = &_draw_box;
    vtft_instance->draw_handles[VTFT_COMPONENT_ROUNDED_BOX] = &_draw_rounded_box;
    vtft_instance->draw_handles[VTFT_COMPONENT_CIRCLE] = &_draw_circle;
    vtft_instance->draw_handles[VTFT_COMPONENT_ELLIPSE] = &_draw_ellipse;
    vtft_instance->draw_handles[VTFT_COMPONENT_LINE] = &_draw_line;
    vtft_instance->draw_handles[VTFT_COMPONENT_LABEL] = &_draw_label;
    vtft_instance->draw_handles[VTFT_COMPONENT_BUTTON] = &_draw_button;
    vtft_instance->draw_handles[VTFT_COMPONENT_ROUNDED_BUTTON] = &_draw_rounded_button;
    vtft_instance->draw_handles[VTFT_COMPONENT_CIRCLE_BUTTON] = &_draw_circle_button;
    vtft_instance->draw_handles[VTFT_COMPONENT_IMAGE] = &_draw_image;
    vtft_instance->draw_handles[VTFT_COMPONENT_CHECK_BOX] = &_draw_check_box;
    vtft_instance->draw_handles[VTFT_COMPONENT_RADIO_BUTTON] = &_draw_radio_button;
    vtft_instance->draw_handles[VTFT_COMPONENT_PROGRESS_BAR] = &_draw_progress_bar;
}

// Sets the position of the given progress bar.
void vtft_set_progress_bar_position(
    vtft_t *instance,
    vtft_progress_bar *progress_bar,
    vtft_ucoord_t position)
{
    uint32_t min_position;
    uint32_t max_position;

    min_position = progress_bar->min_position;
    max_position = progress_bar->max_position;
    if (position < min_position)
        position = min_position;
    if (position > max_position)
        position = max_position;

    progress_bar->position = position;
    _update_progress_bar(instance, progress_bar);
}

// Draws the given component, using the appropriate drawing function.
// void vtft_draw_component(vtft_t *instance, vtft_component *component)
void vtft_draw_component(vtft_t *instance, const vtft_component * __generic_ptr component)
{
    if (component->visible == 0)
        return;

    (instance->draw_handles[component->type])(instance, component);
}

// Redraws the current screen and all of its components.
void vtft_refresh_current_screen(vtft_t *instance)
{
    _draw_screen(instance, instance->current_screen);
}

// Sets the current screen and draws it.
void vtft_set_current_screen(vtft_t *instance, vtft_screen *screen)
{
    if (screen == instance->current_screen)
       return;

    instance->current_screen = screen;
    _set_screen_changed(instance);
    _draw_screen(instance, screen);
}

// Processes the periodic events.
void vtft_process(vtft_t *instance)
{
    _set_current_instance(instance);
    _notify_press_events();
    tp_process(instance->tp_instance);
}
