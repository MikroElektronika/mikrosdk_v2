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
 * @file hal_ll_rtc.c
 * @brief RTC HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_rtc.h"
#include "hal_ll_bit_control.h"
#include "delays.h"

/**
 *  Return values
 */
typedef enum
{
    HAL_LL_RTC_SUCCESS = 0,
    HAL_LL_RTC_ERROR = (-1)
} hal_ll_rtc_err_t;

/**
 * @defgroup WDOG_macros
 * @brief WDOG macros for the configuration of the system reset.
 * @{
 */
#define WDOG_UNLOCK_1           0xC520
#define WDOG_UNLOCK_2           0xD928
#define WDOG_VALUE_HIGH         0x0000
#define WDOG_VALUE_LOW          0x0004
#define WDOG_INCORRECT_SEQUENCE 0x0000
/** @}*/

/**
 * @brief Macro used to retrieve the value of the rtc_tsr regsiter.
 */
#define CONVERT_RTC_TSR (*(uint32_t *)registers.rtc_tsr) %  86400

/**
 * @brief Bit used to enable access write for RTC.
 */
#define SIM_SCGC_B29 29

/**
 * @defgroup RTC_bits
 * @brief RTC bit numbers used for the configuration.
 * @{
 */
#define RTC_CR_B8  8
#define RTC_SR_B4  4
#define RTC_IER_B2 2
/** @}*/

/**
 * @defgroup WDOG_bits
 * @brief WDOG bit numbers used for the configuration.
 * @{
 */
#define WDOG_STCTRLH_B0 0
#define WDOG_STCTRLH_B2 2
/** @}*/

/**
 * @defgroup Time_getters
 * @brief Getters used to retrieve the date and time.
 * @{
 */
#define GET_HOUR            seconds / 3600
#define GET_MINUTE          seconds / 60
#define GET_SECONDS         seconds % 60
#define GET_HOUR_TO_SECONDS seconds % 3600
/** @}*/

/**
 * @brief Macro used to initialize seconds.
 */
#define SECOND_INIT 0

/**
 * @defgroup Time_converters
 * @brief Getters used to retrieve the date and time.
 * @{
 */
#define HOUR_IN_SECONDS    ( uint32_t )( time->hour ) * 3600
#define MINUTE_IN_SECONDS  ( uint32_t )( time->minute ) * 60
#define SECONDS_IN_SECONDS ( uint32_t )( time->second )
/** @}*/

/**
 * @brief Macro used to reset RTC register.
 */
#define RTC_TSR_NULL 0


/**
 * @brief Macro used to adjust seconds correctly.
 */
#define MINUS_SECOND_1 -1

/*!< @brief Mask used for register clearing */
#define HAL_LL_CLEAR 0x00UL

/**
 * @brief Writes specified value to
 *        specified register.
 *
 * @param[in] reg  - register address.
 * @param[in] _val - Value to be written.
 */
#define write_reg(reg,_val) (selected_reg(reg) = (_val))

/**
 * @brief Returns value stored
 *        in a register.
 *
 * @param[in] reg  - register address.
 *
 * @return Register(reg) value.
 */
#define read_reg(reg) (selected_reg(reg))

/**
 * @brief Clears all bits in a register.
 *
 * @param[in] reg  - register address
 */
#define clear_reg(reg) write_reg(reg, HAL_LL_CLEAR)

typedef struct
{
    hal_ll_base_addr_t* sim_scgc6;
    hal_ll_base_addr_t* rtc_tsr;
    hal_ll_base_addr_t* rtc_cr;
    hal_ll_base_addr_t* rtc_sr;
    hal_ll_base_addr_t* rtc_ier;
    hal_ll_base_addr_t* rtc_tar;
    uint16_t* wdog_refresh;
    uint16_t* wdog_stctrlh;
    uint16_t* wdog_unlock;
    uint16_t* wdog_tovalh;
    uint16_t* wdog_tovall;
} reg2_t;

typedef struct
{
    hal_ll_base_addr_t* seconds2;
} regsec_t;

reg2_t registers = { SIM_SCGC6_REG_ADDRESS, RTC_TSR_REG_ADDRESS, RTC_CR_REG_ADDRESS, RTC_SR_REG_ADDRESS, RTC_IER_REG_ADDRESS, RTC_TAR_REG_ADDRESS, WDOG_REFRESH_REG_ADDRESS, WDOG_STCTRLH_REG_ADDRESS, WDOG_UNLOCK_REG_ADDRESS, WDOG_TOVALH_REG_ADDRESS, WDOG_TOVALL_REG_ADDRESS };

uint32_t  seconds;

#ifdef __GNUC__
/**
 * @brief Initialize the RTC counter.
 * @details Set the date to 01/01/2000 at 00:00:00.
 * @b Example
 * @code
 * // Initialize RTC.
 * hal_ll_rtc_init();
 * @endcode
 */
void __attribute__ ((weak)) hal_ll_rtc_init();

/**
 * @brief Start the RTC module.
 * @details Continue the RTC module count from the stored value in the counter register.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_start();

/**
 * @brief Stop the RTC module.
 * @details Stop the RTC module count.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_stop();

/**
 * @brief Reset the RTC module.
 * @details Reset the RTC counter to the default values of 0h:0m:0s.
 * @param None.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_reset();

/**
 * @brief Configure time of RTC module.
 * @details Configure time registers with the values from hal_ll_rtc_time_t structure.
 * @param time hal_ll_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__ ((weak)) hal_ll_rtc_set_time( hal_ll_rtc_time_t *time );

/**
 * @brief Get time and date.
 * @details Configure hal_ll_rtc_time_t structure with the values from time registers.
 * @param time hal_ll_rtc_time_t structure.
 * @return The function can return one of the values defined by
 * hal_ll_rtc_err_t structure, which is size dependant on the architecture.
 */
err_t __attribute__((weak)) hal_ll_rtc_get_time( hal_ll_rtc_time_t *rtc );

/**
 * @brief Preforms system reset.
 * @details Resets the core and all on-chip peripherals except the Debug
 * interface.
 * @param None.
 * @warning System reset affects core and periferals,
 * depending on the architecture you will need to reconfigure opened modules.
 */
void __attribute__ ((weak)) hal_ll_rtc_system_reset();

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Configure the watchdog.
 * @details Conifguration in order to do a system reset.
 */
void __attribute__((weak)) configureWatchdog();
#endif
// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Configure the watchdog.
 * @details Conifguration in order to do a system reset.
 */
void configureWatchdog();

//------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hal_ll_rtc_init() {
    set_reg_bit( registers.sim_scgc6, SIM_SCGC_B29 );
    if ( read_reg( registers.rtc_tsr ) == RTC_TSR_NULL ) {
        hal_ll_rtc_reset();
    }
    set_reg_bit( registers.rtc_cr, RTC_CR_B8 );
    Delay_100ms();
    clear_reg_bit( registers.rtc_sr, RTC_SR_B4 );
    clear_reg_bit( registers.rtc_ier, RTC_IER_B2 );
}

err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time ) {
    seconds = SECOND_INIT;
    seconds += HOUR_IN_SECONDS;
    seconds += MINUTE_IN_SECONDS;
    seconds += SECONDS_IN_SECONDS;
    hal_ll_rtc_stop();
    write_reg( registers.rtc_tsr, seconds );
    hal_ll_rtc_start();
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_start() {
    set_reg_bit( registers.rtc_sr, RTC_SR_B4 );
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_stop() {
    clear_reg_bit( registers.rtc_sr, RTC_SR_B4 );
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *time ) {
    seconds = CONVERT_RTC_TSR;
    time -> hour = GET_HOUR;
    seconds = GET_HOUR_TO_SECONDS;
    time -> minute = GET_MINUTE;
    time -> second = GET_SECONDS;
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_set_alarm( long time ) {
    registers.rtc_tar = time - MINUS_SECOND_1;
    set_reg_bit( registers.rtc_ier, RTC_IER_B2 );
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_reset() {
    hal_ll_rtc_stop();
    clear_reg( registers.rtc_tsr );
    hal_ll_rtc_start();
    return HAL_LL_RTC_SUCCESS;
}

void hal_ll_rtc_system_reset() {
    configureWatchdog();
    write_reg( registers.wdog_refresh, WDOG_INCORRECT_SEQUENCE );
}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS
void configureWatchdog() {
    uint16_t var = RTC_TSR_REG_ADDRESS;
    clear_reg_bit( registers.wdog_stctrlh, WDOG_STCTRLH_B0 );
    write_reg( registers.wdog_unlock, WDOG_UNLOCK_1 );
    write_reg( registers.wdog_unlock, WDOG_UNLOCK_2 );
    write_reg( registers.wdog_tovalh, WDOG_VALUE_HIGH );
    write_reg( registers.wdog_tovall, WDOG_VALUE_LOW );
    set_reg_bit( registers.wdog_stctrlh, WDOG_STCTRLH_B2 );
    set_reg_bit( registers.wdog_stctrlh, WDOG_STCTRLH_B0 );
}
