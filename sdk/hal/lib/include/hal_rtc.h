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
 * @file hal_rtc.h
 * @brief RTC HAL layer implementation.
 */

#ifndef _HAL_RTC_H
#define _HAL_RTC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_rtc.h"

/**
 * @brief RTC time structure, consisted of the following fields:
 * @details User needs to specify values into the structure.
 * @note Take into consideration that any value can be changed explicitly by the user.
 * @warning The following example includes time registers for the RTC.
 * Take into consideration that some MCUs do not have time registers.
 * Default values are imprecise if you do not have time registers.
 *
 * @b Example
 * @code
 *   // Define RTC Time structure.
 *   static hal_rtc_t time;
 *
 *   // Fill structure with default values.
 *   #define time_default_value time.second = 0; \
 *                              time.minute = 5; \
 *                              time.hour = 0; \
 *                              time.day_week = 1; \
 *                              time.day_month = 1; \
 *                              time.month = 1; \
 *                              time.year = 0;
 *
 *   // Use the structure:
 *   hal_rtc_configure_default( &time );
 *
 * @endcode
 */
typedef struct
{                       // If calendar mode enable:
    uint16_t year;      // 4-digit format e.g.: 08 for 2008     // Can go from 00 to 99
    uint16_t month;     // 2-digit format e.g.: 02 for february // Can go from 01 to 12
    uint16_t day_month; // 2-digit format                       // Can go from 01 to 31
    uint16_t day_week;  // 1-digit format e.g.: 01 for tuesday  // Can go from 0 to 6
    uint16_t hour;      // 2-digit format                       // Can go from 00 to 59
    uint16_t minute;    // 2-digit format                       // Can go from 00 to 59
    uint32_t second;    // 2-digit format                       // Can go from 00 to 59
} hal_rtc_t;

/**
 * @brief Initialize the RTC counter.
 * @details Set the date to 01/01/2000 at 00:00:00.
 * @b Example.
 * @code
 * // Initialize RTC.
 * hal_rtc_init();
 * @endcode
 * */
void hal_rtc_init();

/**
 * @brief Initialize the default value of counter.
 * @details Set the RTC time value.
 * @note It is recommended to check return value for error.
 * @b Example.
 * @code
 * // Time structure.
 * static rtc_t time;
 *
 * // Initialize RTC.
 * rtc_init();
 *
 * // Configure RTC.
 * if ( RTC_ERROR == rtc_configure_default( time ) ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 * */
err_t hal_configure_default( hal_rtc_t *time );

/**
 * @brief Start the RTC module.
 * @details Continue the RTC module count from the stored value in the counter register.
 * @param None.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected
 * to have initialized RTC by using rtc_init() and have the RTC not counting.
 * @note It is recommended to configure RTC module using rtc_configure_default( rtc_t *time ) before the first start and to check return value for error.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static rtc_t time;
 *
 *   // Initalize the RTC module.
 *   rtc_init();
 *
 *   // Start the RTC module.
 *   if ( RTC_ERROR == rtc_start() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_start();

/**
 * @brief Stop the RTC module.
 * @details Stop the RTC module count.
 * @param None.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected
 * to have the RTC module started using rtc_start().
 * @note It is recommended to check return value for error.
 * @b Example.
 * @code
 *   // RTC time structure.
 *   static rtc_t time;
 *
 *   // Initalize the RTC module.
 *   rtc_init();
 *
 *   // Start the RTC module.
 *   rtc_start();
 *
 *   // Stop the RTC module.
 *   if ( RTC_ERROR == rtc_stop() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_stop();

/**
 * @brief Reset the RTC module.
 * @details Reset the RTC counter to the default values for the time and date registers.
 * @param None.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected
 * to have the RTC module started using rtc_start().
 * @note It is recommended to check return value for error.
 * @b Example.
 * @code
 *   // RTC time structure.
 *   static rtc_t time;
 *
 *   // Initalize the RTC module.
 *   rtc_init();
 *
 *   // Start the RTC module.
 *   rtc_start();
 *
 *   // Reset the RTC module.
 *   if ( RTC_ERROR == rtc_reset() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_reset();

/**
 * @brief Configure time of RTC module.
 * @details Allow to configure the date and time of the calendar of the rtc.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @pre Before calling this function, the user is expected
 * to have the RTC module started using rtc_start().
 * @note It is recommended to check return value for error.
 *
 * @b Example.
 * @code
 *  // Time structure.
 *  static rtc_t time;
 *
 *  // Initialize RTC.
 *  rtc_init();
 *
 *  // Modify time.
 *  time.second = 0;
 *  time.minute = 5;
 *  time.hour = 3;
 *  time.day_week = 1;
 *  time.day_month = 2;
 *  time.month = 2;
 *  time.year = 1;
 *
 *  // Set time.
 *  if ( RTC_SUCCESS != hal_rtc_set_time( &time ) ) {
 *      // Error handling strategy.
 *  }
 * @endcode
 * */
err_t hal_rtc_set_time( hal_rtc_t *time );

/**
 * @brief Get time and date.
 * @details Get the value from the counter register.
 * @return The time and date.
 * @pre Before calling this function, the user is expected
 * to have the RTC module started using rtc_start().
 * @note It is recommended to check return value for error.
 *
 * @b Example.
 * @code
 *  // Time structure.
 *  static rtc_t time;
 *
 *  // Initialise RTC.
 *  rtc_init();
 *
 *  // Start RTC;
 *  if ( RTC_SUCCESS != rtc_start() ) {
 *      // Error handling strategy.
 *  }
 *
 *  if ( RTC_SUCCESS != hal_rtc_get_time( &time ) ) {
 *      // Error handling strategy.
 *  }
 *  @endcode
 * */
err_t hal_rtc_get_time( hal_rtc_t *time );

/**
 * @brief Reset the microcontoller.
 * @details Resets the core and all on-chip peripherals except the Debug
 * interface.
 * @note It is recommended to check return value for error.
 *
 * @b Example.
 * @code
 *  // Time structure.
 *  static rtc_t time;
 *
 *  // Initialize RTC.
 *  rtc_init();
 *
 *  // Reset
 *  hal_software_reset();
 *  @endcode
 * */
void hal_software_reset();

#ifdef __cplusplus
}
#endif

#endif // HAL_RTC_H
