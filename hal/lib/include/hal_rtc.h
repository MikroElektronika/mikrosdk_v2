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

#define HAL_RTC_LIMIT_SECONDS 60
#define HAL_RTC_LIMIT_MINUTES 60
#define HAL_RTC_LIMIT_HOURS   24

#include "hal_ll_rtc.h"

/**
 * @details Return values.
 */
typedef enum
{
    HAL_RTC_SUCCESS = 0,       /*!< Success. */
    HAL_RTC_TIME_FORMAT_ERROR, /*!< Time format error. */

    HAL_RTC_ERROR = (-1)       /*!< Error. */
} hal_rtc_err_t;

/**
 * @brief Structure representing the RTC time.
 * @details This structure is used to hold the real-time clock information, including
 * hour, minute, second and it follows a 24-hour format.
 * @note Take into consideration that any value can be changed explicitly by the user.
 *
 * @b Example
 * @code
 *   // Define RTC time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Fill structure with default values.
 *   #define time_default_value time.second = 0; \
 *                              time.minute = 5; \
 *                              time.hour = 0;
 *
 * @endcode
 */
typedef struct
{
    uint8_t hour;   // 2-digit format - support values from 00 to 23
    uint8_t minute; // 2-digit format - support values from 00 to 59
    uint8_t second; // 2-digit format - support values from 00 to 59
} hal_rtc_time_t;

/**
 * @brief Initialize the RTC module.
 * @details Initialize the RTC module.
 * @param None.
 * @b Example
 * @code
 *   // Initialize RTC.
 *   hal_rtc_init();
 * @endcode
 */
void hal_rtc_init();

/**
 * @brief Start the RTC module.
 * @details Continue the RTC module count from the stored value in the counter register.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to configure RTC module using hal_rtc_set_time( hal_rtc_time_t *time ) before the first start and to check return value for error.
 * @note This function checks if the RTC module is initialized. If it is not, `hal_rtc_init()` is automatically called to initialize the module.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Initalize the RTC module.
 *   hal_rtc_init();
 *
 *   // Start the RTC module.
 *   if ( HAL_RTC_ERROR == hal_rtc_start() ) {
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
 * hal_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @note This function checks if the RTC module is initialized. If it is not, `hal_rtc_init()` is automatically called to initialize the module.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Initalize the RTC module.
 *   hal_rtc_init();
 *
 *   // Stop the RTC module.
 *   if ( HAL_RTC_ERROR == hal_rtc_stop() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_stop();

/**
 * @brief Reset the RTC module.
 * @details Reset the RTC counter to the default values of 0h:0m:0s.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @note This function checks if the RTC module is initialized. If it is not, `hal_rtc_init()` is automatically called to initialize the module.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Initalize the RTC module.
 *   hal_rtc_init();
 *
 *   // Reset the RTC module.
 *   if ( HAL_RTC_ERROR == hal_rtc_reset() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_reset();

/**
 * @brief Configure time of RTC module.
 * @details Configure time registers with the values from hal_rtc_time_t structure.
 * @param time hal_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_rtc_err_t structure, which is size dependant on the architecture.
 * @note This function checks if the RTC module is initialized. If it is not, `hal_rtc_init()` is automatically called to initialize the module.
 *
 * @b Example
 * @code
 *   // Time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Initialize RTC.
 *   hal_rtc_init();
 *
 *   // Modify time.
 *   time.second = 0;
 *   time.minute = 5;
 *   time.hour = 3;
 *
 *   // Set time.
 *   if ( HAL_RTC_SUCCESS != hal_rtc_set_time( &time ) ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_set_time( hal_rtc_time_t *time );

/**
 * @brief Get time and date.
 * @details Configure hal_rtc_time_t structure with the values from time registers.
 * @param time hal_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 * @note This function checks if the RTC module is initialized. If it is not, `hal_rtc_init()` is automatically called to initialize the module.
 *
 * @b Example
 * @code
 *   // Time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Initialize RTC.
 *   hal_rtc_init();
 *
 *   if ( HAL_RTC_SUCCESS != hal_rtc_get_time( &time ) ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t hal_rtc_get_time( hal_rtc_time_t *time );

/**
 * @brief Preforms system reset.
 * @details Resets the core and all on-chip peripherals except the Debug
 * interface.
 * @param None.
 * @warning System reset affects core and periferals,
 * depending on the architecture you will need to reconfigure opened modules.
 *
 * @b Example
 * @code
 *   // Time structure.
 *   static hal_rtc_time_t time;
 *
 *   // Initialize RTC.
 *   hal_rtc_init();
 *
 *   // Reset.
 *   hal_rtc_system_reset();
 * @endcode
 */
void hal_rtc_system_reset();

/*! @} */ // halrtcgroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // HAL_RTC_H
