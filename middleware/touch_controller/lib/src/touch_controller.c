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
 * @file  touch_controller.c
 * @brief Touch controller middle layer.
 */

#include "touch_controller.h"

static touch_ic_context_def touch_controller;

void touch_controller_tp_init(tp_t* tp, tp_drv_t *tp_interface)
{
    tp_cfg_t tp_cfg;
    touch_ic_cfg_def touch_ic_cfg;

    // Initialize Touch panel.
    touch_ic_cfg_setup(touch_ic_cfg_setup_param);
    touch_ic_map_pins(touch_ic_cfg);
    touch_ic_init(&touch_controller, &touch_ic_cfg, tp_interface);
    touch_ic_default_cfg(&touch_controller);

    // TP API initialization.
    tp_cfg_setup(&tp_cfg);
    tp_cfg.width = _TFT_WIDTH_;
    tp_cfg.height = _TFT_HEIGHT_;
    tp_cfg.start_pos = _TFT_TP_ROTATE_;
    tp_init(tp, &tp_cfg, tp_interface, &touch_controller);
    #ifdef __TP_MIKROE__
    // Calibration needed for displays with MikroE Touch panel.
    tp_mikroe_calibrate(tp);
    #endif
}

void touch_controller_init( gl_driver_t* display_driver, uint8_t backlight)
{
    tft_cfg_t tft_cfg;

    // Initialize TFT display board.
    TFT_MAP_PINOUTS(tft_cfg);
    tft_cfg.board = &_TFT_BOARD_;
    tft_init(&tft_cfg, display_driver);
    tft_set_backlight(backlight);
}
// ------------------------------------------------------------------------- END
