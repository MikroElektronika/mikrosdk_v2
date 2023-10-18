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

#include "vtft_touch.h"
#include <string.h>
#include "vtft.h"

// Currently used VTFT instance. Needed for TP callbacks.
static vtft_t *_current_instance = 0;

// Local Function Definitions

// Returns the frontmost active component at the given coordinates.
static vtft_active_component * __generic_ptr _get_active_component(vtft_t * instance, vtft_coord_t x, vtft_coord_t y)
{
    int32_t i;
    vtft_component * __generic_ptr * __generic_ptr components = instance->current_screen->components;
    vtft_index_t component_count = instance->current_screen->component_count;

    for (i = component_count - 1; i >= 0; i--)
    {
        vtft_component * __generic_ptr component;
        vtft_component_type type;
        vtft_positioned_component * __generic_ptr positioned_component;
        vtft_coord_t left;
        vtft_coord_t top;

        component = components[i];
        if (component->visible == 0)
            continue;

        type = component->type;

        // Skip if the component isn't an active component.
        if ((type == VTFT_COMPONENT_LINE) || (type == VTFT_COMPONENT_PROGRESS_BAR))
            continue;

        // Skip if the coordinates are to the left or above the component.
        positioned_component = (vtft_positioned_component * __generic_ptr)component;
        left = positioned_component->left;
        top = positioned_component->top;
        if ((x < left) || (y < top))
            continue;

        // Check all component types.

        if ((type == VTFT_COMPONENT_CIRCLE) ||
            (type == VTFT_COMPONENT_CIRCLE_BUTTON))
        {
            vtft_circle * __generic_ptr circle = (vtft_circle *__generic_ptr) component;
            vtft_ucoord_t diameter = circle->radius << 1;
            if ((x < left + diameter) && (y < top + diameter))
                return (vtft_active_component *__generic_ptr)component;
        }

        if ((type == VTFT_COMPONENT_BOX) ||
            (type == VTFT_COMPONENT_ROUNDED_BOX) ||
            (type == VTFT_COMPONENT_BUTTON) ||
            (type == VTFT_COMPONENT_ROUNDED_BUTTON) ||
            (type == VTFT_COMPONENT_ELLIPSE))
        {
            vtft_box * __generic_ptr box = (vtft_box * __generic_ptr)component;
            if ((x < left + box->width) && (y < top + box->height))
                return (vtft_active_component * __generic_ptr)component;
        }

        if (type == VTFT_COMPONENT_LABEL)
        {
            vtft_label * __generic_ptr label = (vtft_label * __generic_ptr)component;
            if ((x < left + label->width) && (y < top + label->height))
                return (vtft_active_component * __generic_ptr)component;
        }

        if (type == VTFT_COMPONENT_IMAGE)
        {
            vtft_image * __generic_ptr image = (vtft_image * __generic_ptr)component;
            if ((x < left + image->width) && (y < top + image->height))
                return (vtft_active_component * __generic_ptr)component;
        }

        if ((type == VTFT_COMPONENT_CHECK_BOX) ||
            (type == VTFT_COMPONENT_RADIO_BUTTON))
        {
            vtft_check_box * __generic_ptr box = (vtft_check_box * __generic_ptr)component;
            if (box->text_align == VTFT_TEXT_ALIGNMENT_LEFT)
            {
                if ((x < (left + box->width)) && (x > (left + box->width - box->height)) && (y < (top + box->height)))
                    return (vtft_active_component * __generic_ptr)component;
            }
            else
            {
                if ((x < (left + box->height)) && (y < (top + box->height)))
                    return (vtft_active_component * __generic_ptr)component;
            }
        }
    }

    return 0;
}

// Checks both non-const and const components at the given coordinates
// and sets the frontmost one to the VTFT instance's appropriate field.
static void _get_top_active_component(vtft_t *instance, vtft_coord_t x, vtft_coord_t y)
{
    const vtft_active_component * __generic_ptr current_active_component = _get_active_component(instance, x, y);
    instance->current_active_component = current_active_component;
}

// Returns true if the given component should be recolored when pressed.
static uint8_t _has_press_color(const vtft_component * __generic_ptr component)
{
    vtft_component_type type = component->type;
    if ((type != VTFT_COMPONENT_LABEL)
        && (type != VTFT_COMPONENT_IMAGE)
        && (type != VTFT_COMPONENT_PROGRESS_BAR))
        return 1;
    else
        return 0;
}

// Toggles the value of the given component if it is checkable.
static void _toggle_checkable_component(vtft_component * __generic_ptr component)
{
    vtft_component_type type;
    vtft_abstract_check_box * __generic_ptr abstract_check_box;

    type = component->type;
    if ((type != VTFT_COMPONENT_CHECK_BOX) && (type != VTFT_COMPONENT_RADIO_BUTTON))
        return;

    // Here the component must not be in the flash memory
    if ((long) component & 0x800000 == 0)
        return;

    abstract_check_box = (vtft_abstract_check_box * __generic_ptr)component;
    abstract_check_box->checked = (abstract_check_box->checked == 0) ? 1 : 0;
}

// Checks and calls the given event.
static void _call_event(vtft_event event)
{
    if (event != 0)
        event();
}

// Global Function Definitions

// Processes a touch down event.
void _process_touch_down(tp_coord_t x, tp_coord_t y)
{
    const vtft_active_component * __generic_ptr active;

    _current_instance->pen_down = 1;

    // _get_top_active_component returns intersected component. (1)
    _get_top_active_component(_current_instance, (vtft_coord_t)x, (vtft_coord_t)y);
    active = _current_instance->current_active_component;

    if (active != 0)
    {
        // Because _get_top_active_component returns intersected component (1), not active
        if (active->active != 0)
        {
            _current_instance->pressed_component = active;
            // Recolor the pressed component.
            if (_has_press_color((const vtft_component * __generic_ptr)active))
                vtft_draw_component(_current_instance, (const vtft_component * __generic_ptr)active);

            // Process the down event of the pressed component.
            _call_event(active->event_set.down_event);

            return;
        }
    }

    _call_event(_current_instance->current_screen->down_event);
}

// Processes a touch up event.
void _process_touch_up(tp_coord_t x, tp_coord_t y)
{
    vtft_active_component * __generic_ptr active;
    vtft_active_component * __generic_ptr pressed;

    _current_instance->pen_down = 0;

    if (_current_instance->screen_changed != 0)
    {
        // Don't handle touch up if the Screen was changed during the touch.
        _current_instance->screen_changed = 0;
        return;
    }

    _get_top_active_component(_current_instance, (vtft_coord_t)x, (vtft_coord_t)y);
    active = _current_instance->current_active_component;
    pressed = _current_instance->pressed_component;

    // Recolor the pressed component.
    if (pressed != 0)
    {
        _current_instance->pressed_component = 0;
        _toggle_checkable_component((vtft_component * __generic_ptr)pressed);
        if (_has_press_color((vtft_component * __generic_ptr)pressed))
        {
            vtft_draw_component(_current_instance, (vtft_component * __generic_ptr)pressed);
        }
    }

    if (active != 0)
    {
        if (active->active != 0)
        {
            // Process the up event of the active component.
            _call_event(active->event_set.up_event);

            // If the pressed component is the active one, process its click event.
            if (active == pressed)
                _call_event(active->event_set.click_event);

            return;
        }
    }

    // Process the up event of the screen.
    _call_event(_current_instance->current_screen->up_event);
}

// Sets the screen changed indicator.
void _set_screen_changed(vtft_t *instance)
{
    if (instance->pen_down)
        instance->screen_changed = 1;
}

// Sets the current VTFT instance.
void _set_current_instance(vtft_t *instance)
{
    _current_instance = instance;
}

void _notify_press_events()
{
    vtft_active_component * __generic_ptr active;
    active = _current_instance->current_active_component;

    if (active != 0)
    {
        if (active->active != 0)
        {
            _call_event(active->event_set.press_event);
            return;
        }
    }

    _call_event(_current_instance->current_screen->press_event);
}


void _tp_event_handler( tp_event_t event, tp_coord_t x, tp_coord_t y, tp_touch_id_t i)
{
    if (i != 0)
        return;

    switch (event)
    {
    case TP_EVENT_PRESS_DOWN:
        // _process_touch_press(x, y);
        _process_touch_down(x, y);
        break;

    case TP_EVENT_PRESS_MOVE:
        _get_top_active_component(_current_instance, (vtft_coord_t)x, (vtft_coord_t)y);
        // _process_touch_press(x, y);
        break;

    case TP_EVENT_PRESS_UP:
        _process_touch_up(x, y);
        break;
    }
}
