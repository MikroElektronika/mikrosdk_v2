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
 * @file hal_rtc.c
 * @brief RTC HAL layer implementation.
 */

#include "hal_rtc.h"

// -------------------------------------------------------------------- VARIABLES

DRV_TO_HAL_STATIC bool initialized = false;

//------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hal_rtc_init() {
    if ( !initialized ) {
        hal_ll_rtc_init();
        initialized = true;
    }
}

err_t hal_rtc_start() {
    if ( !initialized ) {
        hal_rtc_init();
    }
    return hal_ll_rtc_start();
}

err_t hal_rtc_stop() {
    if ( !initialized ) {
        hal_rtc_init();
    }
    return hal_ll_rtc_stop();
}

err_t hal_rtc_reset() {
    if ( !initialized ) {
        hal_rtc_init();
    }
    return hal_ll_rtc_reset();
}

err_t hal_rtc_set_time( hal_rtc_time_t *time ) {
    if ( !initialized ) {
        hal_rtc_init();
    }
    if ( HAL_RTC_LIMIT_SECONDS <= time->second  || HAL_RTC_LIMIT_MINUTES <= time->minute || HAL_RTC_LIMIT_HOURS <= time->hour ) {
        return HAL_RTC_TIME_FORMAT_ERROR;
    }
    return hal_ll_rtc_set_time( time );
}

err_t hal_rtc_get_time( hal_rtc_time_t *time ) {
    if ( !initialized ) {
        hal_rtc_init();
    }
    return hal_ll_rtc_get_time( time );
}

void hal_rtc_system_reset() {
    if ( !initialized ) {
        hal_rtc_init();
    }
    hal_ll_rtc_system_reset();
}
