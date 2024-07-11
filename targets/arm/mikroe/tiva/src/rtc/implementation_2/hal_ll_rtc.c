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
 * @brief Rtc HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_rtc.h"

/**
 *  Return values
 */
typedef enum
{
    HAL_LL_RTC_SUCCESS = 0,
    HAL_LL_RTC_ERROR = (-1)
} hal_ll_rtc_err_t;

#define SYSCTL_RCGCHIB_R0_BIT 0
#define HIB_IM_WC_BIT         4
#define HIB_CTL_RTCEN_BIT     0
#define HIB_CTL_CLK32EN_BIT   6
#define HIB_CTL_WRC_BIT       31
#define HIB_MIS_WC_BIT        4
#define HIB_CALCTL_CALEN_BIT  0
#define HIB_CALCTL_CAL24_BIT  2

#define WRC !check_reg_bit( registers.hib_ctl, HIB_CTL_WRC_BIT )
#define WC  !check_reg_bit( registers.hib_mis, HIB_MIS_WC_BIT )

#define MASK_SECOND    0x0000003F
#define MASK_MINUTE    0x00003F00
#define MASK_HOUR      0x001f0000
#define MASK_DAY_MONTH 0x0000001F
#define MASK_MONTH     0x00000F00
#define MASK_YEAR      0x007f0000

#define GET_SECOND time_second % 60
#define GET_MINUTE time_second / 60 - GET_HOUR * 60
#define GET_HOUR   time_second / 3600

#define SET_TIME (uint32_t)time->hour * 3600 + (uint32_t)time->minute * 60 + (uint32_t)time->second

#define SECOND_IN_ONE_DAY 86400

#define RESET              0x00000000
#define SOFTWARE_RESET_KEY 0x05FA0004

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
 * @param[in] reg - register address.
 *
 * @return Register(reg) value.
 */
#define read_reg(reg) (selected_reg(reg))

typedef struct
{
    hal_ll_base_addr_t* sysctl_rcgchib;
    hal_ll_base_addr_t* hib_mis;
    hal_ll_base_addr_t* hib_ctl;
    hal_ll_base_addr_t* hib_im;
    hal_ll_base_addr_t* hib_rtcld;
    hal_ll_base_addr_t* nvic_apint;
    hal_ll_base_addr_t* hib_rtcc;
} reg_t;

reg_t registers = { SYSCTL_RCGCHIB_REG_ADDRESS, HIB_MIS_REG_ADDRESS, HIB_CTL_REG_ADDRESS, HIB_IM_REG_ADDRESS, HIB_RTCLD_REG_ADDRESS, NVIC_AP_REG_ADDRESS, HIB_RTCC_REG_ADDRESS };

#ifdef __GNUC__

/**
 * @brief Initialize the RTC module.
 * @details Initialize the RTC module.
 * @param None.
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

#endif

void hal_ll_rtc_init() {
    set_reg_bit( registers.sysctl_rcgchib, SYSCTL_RCGCHIB_R0_BIT );
    if ( !check_reg_bit( registers.hib_ctl, HIB_CTL_CLK32EN ) ) {
        set_reg_bit( registers.hib_im, HIB_IM_WC_BIT );
        while ( WRC );
        set_reg_bit( registers.hib_ctl, HIB_CTL_CLK32EN_BIT );
        while ( WC );
    }
}

err_t hal_ll_rtc_start() {
    while ( WRC );
    set_reg_bit( registers.hib_ctl, HIB_CTL_RTCEN_BIT );
    while ( WRC );
    if ( check_reg_bit( registers.hib_ctl, HIB_CTL_RTCEN_BIT ) ) {
        return HAL_LL_RTC_SUCCESS;
    }
    return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_stop() {
    while ( WRC );
    clear_reg_bit( registers.hib_ctl, HIB_CTL_RTCEN_BIT );
    while ( WRC );
    if ( check_reg_bit( registers.hib_ctl, HIB_CTL_RTCEN_BIT ) ) {
        return HAL_LL_RTC_ERROR;
    }
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_reset() {
    if ( !check_reg_bit( registers.hib_ctl, HIB_CTL_CLK32EN_BIT ) ) {
        return HAL_LL_RTC_ERROR;
    }
    if ( HAL_LL_RTC_ERROR == hal_ll_rtc_stop() ) {
        return HAL_LL_RTC_ERROR;
    }
    while ( WRC );
    write_reg( registers.hib_rtcld, RESET );
    if ( HAL_LL_RTC_ERROR == hal_ll_rtc_start() ) {
        return HAL_LL_RTC_ERROR;
    }
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time ) {
    uint32_t value;
    if ( !check_reg_bit( registers.hib_ctl, HIB_CTL_CLK32EN_BIT ) ) {
        return HAL_LL_RTC_ERROR;
    }
    if ( HAL_LL_RTC_ERROR == hal_ll_rtc_stop() ) {
        return HAL_LL_RTC_ERROR;
    }
    value = SET_TIME;
    while ( WRC );
    write_reg( registers.hib_rtcld, value );
    while ( WRC );
    if ( read_reg( registers.hib_rtcc ) != value ) {
        return HAL_LL_RTC_ERROR;
    }
    if ( HAL_LL_RTC_ERROR == hal_ll_rtc_start() ) {
        return HAL_LL_RTC_ERROR;
    }
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *time ) {
    uint32_t time_second = read_reg( registers.hib_rtcc );
    while ( time_second >= SECOND_IN_ONE_DAY ) {
        while ( WRC );
        write_reg( registers.hib_rtcld, time_second - SECOND_IN_ONE_DAY );
        while ( WRC );
        time_second = read_reg( registers.hib_rtcc );
    }
    time->second = GET_SECOND;
    time->minute = GET_MINUTE;
    time->hour = GET_HOUR;
    return HAL_LL_RTC_SUCCESS;
}

void hal_ll_rtc_system_reset() {
    write_reg( registers.nvic_apint, SOFTWARE_RESET_KEY );
}
