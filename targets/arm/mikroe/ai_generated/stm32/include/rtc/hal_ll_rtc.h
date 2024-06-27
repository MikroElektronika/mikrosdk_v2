/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  hal_ll_rtc.h
 * @brief API for RTC HAL LOW level layer.
 */

#ifndef _HAL_LL_RTC_H
#define _HAL_LL_RTC_H

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __GNUC__
#include "mcu.h"
#endif

#include "hal_target.h"
#include "hal_ll_bit_control.h"

/**
 * @brief Structure representing the RTC time.
 * @details This structure is used to hold the real-time clock information, including
 * hour, minute, second and it follows a 24-hour format.
 * @note Take into consideration that any value can be changed explicitly by the user.
 */
typedef struct
{
    uint8_t hour;   // 2-digit format - supports values from 00 to 23
    uint8_t minute; // 2-digit format - supports values from 00 to 59
    uint8_t second; // 2-digit format - supports values from 00 to 59
} hal_ll_rtc_time_t;

/**
 * @brief Initialize the RTC module.
 * @details Initialize the RTC module.
 * @param None.
 */
void hal_ll_rtc_init();

/**
 * @brief Start the RTC module.
 * @details Continue the RTC module count from the stored value in the count register.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @pre Before calling this function, the user is expected
 * to have initialized RTC by using hal_ll_rtc_init() and have the RTC not counting.
 */
err_t hal_ll_rtc_start();

/**
 * @brief Stop the RTC module.
 * @details Stop the RTC module count.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @pre Before calling this function, the user is expected
 * to have the RTC started.
 */
err_t hal_ll_rtc_stop();

/**
 * @brief Reset the RTC module.
 * @details Reset the RTC counter to the default values of 0h:0m:0s.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @pre Before calling this function, the user is expected
 * to have the RTC started.
 */
err_t hal_ll_rtc_reset();

/**
 * @brief Configure time of RTC module.
 * @details Configure time registers with the values from hal_ll_rtc_time_t structure.
 * @param time hal_ll_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @pre Before calling this function, the user is expected
 * to have the RTC enabled.
 */
err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time );

/**
 * @brief Get time from RTC module.
 * @details Configure hal_ll_rtc_time_t structure with the values from time registers.
 * @param time hal_ll_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @pre Before calling this function, the user is expected
 * to have the RTC enabled.
 */
err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *time );

/**
 * @brief Preforms system reset.
 * @details Resets the core and all on-chip peripherals except the Debug
 * interface.
 * @param None.
 * @warning System reset affects core and periferals,
 * depending on the architecture you will need to reconfigure opened modules.
 */
void hal_ll_rtc_system_reset();

#ifdef __cplusplus
}
#endif

#endif // HAL_LL_RTC_H
