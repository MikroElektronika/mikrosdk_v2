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
 * @file  lvgl_common.c
 * @brief Shared state of the common LVGL TFT interface for SSD1963 displays.
 */

#include "lvgl_common.h"

/*!< CS pin handle. */
digital_out_t pin_cs;
/*!< WR pin handle. */
digital_out_t pin_wr;
/*!< DC pin handle. */
digital_out_t pin_dc;

/*!< Data port handle. */
port_t port_high;
port_t port_low;

/*!< Display driver handle. */
gl_driver_t display_driver;

/*!< Touch panel handle. */
tp_drv_t tp_interface;
tp_t tp;

/*!< Initial value for 16-bit port check. */
volatile bool port_16bit_single = false;
volatile bool port_16bit_dual = false;

/*!< Initial value for data shifting. */
volatile uint8_t shift_data_port_low = 0;
volatile uint8_t shift_data_port_high = 0;

// ------------------------------------------------------------------------- END
