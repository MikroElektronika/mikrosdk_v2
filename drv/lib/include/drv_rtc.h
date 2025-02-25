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
 * @file drv_rtc.h
 * @brief RTC DRV layer implementation.
 */

#ifndef _DRV_RTC_H
#define _DRV_RTC_H

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_rtc.h"

/**
 * @details Return values.
 */
typedef enum
{
    RTC_SUCCESS = 0, /*!< Success. */
    RTC_ERROR = (-1) /*!< Error. */
} rtc_err_t;

/**
 * @brief Structure representing the RTC time.
 * @details This structure is used to hold the real-time clock information, including
 * hour, minute, second and it follows a 24-hour format.
 * @note Take into consideration that any value can be changed explicitly by the user.
 *
 * @b Example
 * @code
 *   // Define RTC time structure.
 *   static rtc_time_t time;
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
    uint8_t hour;   // 2-digit format - support values from 00 to 23.
    uint8_t minute; // 2-digit format - support values from 00 to 59.
    uint8_t second; // 2-digit format - support values from 00 to 59.
} rtc_time_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @brief This section includes the mikroSDK API Reference for the Microcontroller Peripherals.
 * @details Microcontroller Peripherals can be separated into two hierarchical layers - Driver and Hardware Abstraction Layer :
 *
 * <b>Device drivers</b> are the software libraries that initialize
 * the hardware and manage access to the hardware by higher layers
 * of software. Device drivers are the architecture independent
 * liaison between the hardware and the middleware,
 * application layers and plugins.
 *
 * <b>Hardware Abstraction Layer</b> is a layer
 * of code that allows driver interaction with a hardware device at a
 * general or abstract level rather than at a detailed hardware level.
 * @b HAL can be called from either the @b DRV layer or directly from user code.
 * In either case, the calling program can interact with the device in a
 * more general way than it would otherwise.
 *
 * @note All @b mikroSDK.HAL and @b mikroSDK.Driver layers prototypes are architecture independent
 * with the goal of having one unique code base supporting cross-platform
 * devices.
 * @{
 */

/*!
 * @addtogroup drvgroup Driver Layer
 * @brief This section includes the mikroSDK API Reference for the Driver.
 * @details
 * Device drivers are the software libraries that initialize
 * the hardware and manage access to the hardware by higher layers
 * of software. Device drivers are the architecture independent
 * liaison between the hardware and the middleware,
 * application layers and plugins.
 *
 * @note All @b mikroSDK.Driver layer prototypes are architecture independent
 * with the goal of having one unique code base supporting cross-platform
 * devices.
 * @{
 */

/*!
 * @addtogroup drvrtcgroup RTC Driver
 * @brief RTC Driver API Reference.
 * @details The RTC driver provides standard RTC functionality
 * including start, reset and stop of RTC counter, it also allows setting custom values.
 * @{
 */

/**
 * @brief Initialize the RTC module.
 * @details Initialize the RTC module.
 * @param None.
 *
 * @b Example
 * @code
 *   // Initialize RTC.
 *   rtc_init();
 * @endcode
 */
void rtc_init();

/**
 * @brief Start the RTC module.
 * @details Continue the RTC module count from the stored value in the counter register.
 * @param None.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to configure RTC module using rtc_set_time( rtc_time_t *time ) before the first start and to check return value for error.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static rtc_time_t time;
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
err_t rtc_start();

/**
 * @brief Stop the RTC module.
 * @details Stop the RTC module count.
 * @param None.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static rtc_time_t time;
 *
 *   // Initalize the RTC module.
 *   rtc_init();
 *
 *   // Stop the RTC module.
 *   if ( RTC_ERROR == rtc_stop() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t rtc_stop();

/**
 * @brief Reset the RTC module.
 * @details Reset the RTC counter to the default values of 0h:0m:0s.
 * @param None.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // RTC time structure.
 *   static rtc_time_t time;
 *
 *   // Initalize the RTC module.
 *   rtc_init();
 *
 *   // Reset the RTC module.
 *   if ( RTC_ERROR == rtc_reset() ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t rtc_reset();

/**
 * @brief Configure time of RTC module.
 * @details Configure time registers with the values from rtc_time_t structure.
 * @param time rtc_time_t structure.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Time structure.
 *   static rtc_time_t time;
 *
 *   // Initialize RTC.
 *   rtc_init();
 *
 *   // Modify time.
 *   time.second = 0;
 *   time.minute = 5;
 *   time.hour = 3;
 *
 *   // Set time.
 *   if ( RTC_SUCCESS != rtc_set_time( &time ) ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t rtc_set_time( rtc_time_t *time );

/**
 * @brief Get time from RTC module.
 * @details Configure rtc_time_t structure with the values from time registers.
 * @param time rtc_time_t structure.
 * @return The function can return one of the values defined by
 * rtc_err_t structure, which is size dependant on the architecture.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // Time structure.
 *   static rtc_time_t time;
 *
 *   // Initialize RTC.
 *   rtc_init();
 *
 *   if ( RTC_SUCCESS != rtc_get_time( &time ) ) {
 *       // Error handling strategy.
 *   }
 * @endcode
 */
err_t rtc_get_time( rtc_time_t *time );

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
 *   static rtc_time_t time;
 *
 *   // Initialize RTC.
 *   rtc_init();
 *
 *   // Reset.
 *   rtc_system_reset();
 * @endcode
 */
void rtc_system_reset();

/*! @} */ // drvrtcgroup
/*! @} */ // drvgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif //DRV_RTC_H
