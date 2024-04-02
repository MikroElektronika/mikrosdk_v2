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
 * @file hal_ll_rtc.c
 * @brief RTC HAL LOW LEVEL layer implementation.
 */

#include "hal_ll_rtc.h"
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
 * @brief Returns value of specified bit
 *        mask from a register.
 *
 * @param[in] reg  - register address
 * @param[in] bit_mask - bit mask.
 *
 * @return Register(reg) bits value.
 */

#define read_reg_bits(reg,bit_mask) (selected_reg(reg) & (bit_mask))

#define PMU_CTL_BKPWEN_BIT     8
#define RCU_BDCTL_LXTALEN_BIT  0
#define RCU_BDCTL_LXTALSTB_BIT 1
#define RCU_BDCTL_RTCSRC_BIT   8
#define RCU_BDCTL_RTCEN_BIT    15
#define RCU_BDCTL_BKPRST_BIT   16
#define RCU_APB1EN_WWDGTEN_BIT 11
#define RCU_APB1EN_BKPIEN_BIT  27
#define RCU_APB1EN_PMUEN_BIT   28
#define RTC_INTEN_SCIE_BIT     0
#define RTC_CTL_CMF_BIT        4
#define RTC_CTL_LWOFF_BIT      6
#define FWDGT_CTL_BIT_2        2
#define FWDGT_CTL_BIT_3        3
#define FWDGT_CTL_BIT_6        6
#define FWDGT_CTL_BIT_7        7
#define FWDGT_CTL_BIT_10       10
#define FWDGT_CTL_BIT_11       11
#define FWDGT_CTL_BIT_14       14
#define FWDGT_CTL_BIT_15       15
#define FWDGT_PRESCALER_BIT_0  0

#define SEC_IN_MIN   60
#define SEC_IN_HOUR  3600
#define SEC_IN_DAY   86400
#define SEC_IN_MONTH 2592000
#define SEC_IN_YEAR  31536000

#define START_FWDGT                   0x5555
#define UNLOCK_FWDGT_WRITE_PROTECTION 0xCCCC
#define LOCK_FWDGT_WRITE_PROTECTION   0x0000

#define TIME_TO_RTCH (time2&0xFFFF0000)>>16
#define TIME_TO_RTCL time2&0x0000FFFF

#define RTCH_TO_TIME (read_reg(registers.rtc_cnth))<<16
#define RTCL_TO_TIME read_reg(registers.rtc_cntl)

#define SET_TIME time->hour * 3600 + time->minute * 60 + time->second

typedef struct
{
    hal_ll_base_addr_t* pmu_ctl;
    hal_ll_base_addr_t* rtc_ctl;
    hal_ll_base_addr_t* rtc_cntl;
    hal_ll_base_addr_t* rtc_cnth;
    hal_ll_base_addr_t* rcu_apb1en;
    hal_ll_base_addr_t* rcu_bdctl;
    hal_ll_base_addr_t* fwdgt_ctl;
    hal_ll_base_addr_t* rtc_inten;
    hal_ll_base_addr_t* fwdgt_psc;   
} reg_t;

reg_t registers = { PMU_CTL_REG_ADDRESS, RTC_CTL_REG_ADDRESS, RTC_CNTL_REG_ADDRESS, RTC_CNTH_REG_ADDRESS, RCU_APB1EN_REG_ADDRESS, RCU_BDCTL_REG_ADDRESS, FWDGT_CTL_REG_ADDRESS, RTC_INTEN_REG_ADDRESS, FWDGT_PSC_REG_ADDRESS };

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
    if( !check_reg_bit( registers.pmu_ctl, PMU_CTL_BKPWEN_BIT ) ) {
        set_reg_bit( registers.rcu_apb1en, RCU_APB1EN_BKPIEN_BIT );
        set_reg_bit( registers.rcu_apb1en, RCU_APB1EN_PMUEN_BIT );
        set_reg_bit( registers.pmu_ctl, PMU_CTL_BKPWEN_BIT );
        set_reg_bit( registers.rcu_apb1en, RCU_APB1EN_WWDGTEN_BIT );
        set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_LXTALEN_BIT );
        set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_RTCSRC_BIT );
    }
}

err_t hal_ll_rtc_reset() {
    set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_BKPRST_BIT );
    clear_reg_bit( registers.rcu_bdctl, RCU_BDCTL_BKPRST_BIT );
    Delay_100ms();
    hal_ll_rtc_init();
    
    while( !check_reg_bit( registers.rcu_bdctl, RCU_BDCTL_LXTALSTB_BIT ) ){
        set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_LXTALEN_BIT );
        set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_RTCSRC_BIT );
    }

    Delay_100ms();
    hal_ll_rtc_start();

    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_start() {
    set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_RTCEN_BIT );
    set_reg_bit( registers.rcu_bdctl, RCU_BDCTL_LXTALEN_BIT );
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_stop() {
    clear_reg_bit( registers.rcu_bdctl, RCU_BDCTL_RTCEN_BIT );
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time ) {
    uint32_t time2 = SET_TIME;
    
    hal_ll_rtc_init();
 
    set_reg_bit( registers.rtc_ctl, RTC_CTL_CMF_BIT );
    
    write_reg( registers.rtc_cnth, TIME_TO_RTCH );
    write_reg( registers.rtc_cntl, TIME_TO_RTCL );
    
    clear_reg_bit( registers.rtc_ctl, RTC_CTL_CMF_BIT );
    
    Delay_100ms();
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *time ) {
    uint32_t sec = RTCL_TO_TIME;
    sec += RTCH_TO_TIME;
    
    time->hour = sec / SEC_IN_HOUR;
    sec %= SEC_IN_HOUR;
    
    time->minute = sec / SEC_IN_MIN;
    sec %= SEC_IN_MIN;
    
    time->second = sec;
    
    if( time->hour >= 24 ) { 
        time->hour -= 24;
        hal_ll_rtc_set_time( time );
    }
    
    if (time->minute >= 60 ) {
        time->minute -= 60;
        hal_ll_rtc_set_time( time );
    }
    
    if ( time->second >= 60 ) {
        time->second -= 60;
        hal_ll_rtc_set_time( time );
    }
    
    return HAL_LL_RTC_SUCCESS;
}

void hal_ll_rtc_system_reset() {
    write_reg( registers.fwdgt_ctl, UNLOCK_FWDGT_WRITE_PROTECTION );
    write_reg( registers.fwdgt_psc, FWDGT_PRESCALER_BIT_0 );
    write_reg( registers.fwdgt_ctl, LOCK_FWDGT_WRITE_PROTECTION );
    write_reg( registers.fwdgt_ctl, START_FWDGT );
}
