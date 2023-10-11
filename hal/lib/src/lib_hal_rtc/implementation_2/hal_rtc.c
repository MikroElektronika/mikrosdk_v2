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
 * @file hal_rtc.c
 * @brief Rtc HAL layer implementation.
 */

#include "hal_rtc.h"

void hal_rtc_init() {
    if ( hal_ll_rtc_init ) {
        hal_ll_rtc_init();
    }
}

err_t hal_configure_default( hal_rtc_t *time ) {
    if ( hal_ll_configure_default ) {
        return hal_ll_configure_default( time );
    }
    return RTC_ERROR;
}

err_t hal_rtc_start() {
    if ( hal_ll_rtc_start ) {
        return hal_ll_rtc_start();
    }
    return RTC_ERROR;
}

err_t hal_rtc_stop() {
    if ( hal_ll_rtc_stop ) {
        return hal_ll_rtc_stop();
    }
    return RTC_ERROR;
}
err_t hal_rtc_reset() {
    if ( hal_ll_rtc_reset ) {
        return hal_ll_rtc_reset();
    }
    return RTC_ERROR;
}

err_t hal_rtc_set_time( hal_rtc_t *time ) {
    if ( hal_ll_rtc_set_time ) {
        return hal_ll_rtc_set_time( time );
    }
    return RTC_ERROR;
}

err_t hal_rtc_get_time( hal_rtc_t *time ) {
    if ( hal_ll_rtc_get_time ) {
        return hal_ll_rtc_get_time( time );
    }
    return RTC_ERROR;
}

void hal_software_reset() {
    if ( hal_ll_software_reset ) {
        hal_ll_software_reset();
    }
}
