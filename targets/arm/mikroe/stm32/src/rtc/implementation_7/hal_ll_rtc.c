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
 * @file  hal_ll_rtc.c
 * @brief RTC HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_rtc.h"
#include "delays.h"

// ---------------------------------------------------------------- PRIVATE MACROS
#define HOUR_TENS_MASK  0x00300000
#define HOUR_UNITS_MASK 0x000F0000
#define MIN_TENS_MASK   0x00007000
#define MIN_UNITS_MASK  0x00000F00
#define SEC_TENS_MASK   0x00000070
#define SEC_UNITS_MASK  0x0000000F

#define RTCAPBEN_BIT 16
#define DBP_BIT      8
#define RTCSEL_BIT   9
#define LSION_BIT    0
#define LSIRDY_BIT   1
#define INITF_BIT    6
#define INIT_BIT     7
#define FMT_BIT      6
#define RTCEN_BIT    15

#define SOFTWARE_RESET_KEY 0xCCCC
#define CLEAR              0x00
#define FIRST_KEY          0xCA
#define SECOND_KEY         0x53

#define unlock_write_protection set_reg_bit( registers.pwr_cr1, DBP_BIT );\
                                while ( read_reg_bits( registers.pwr_cr1, DBP_BIT ) );\
                                write_reg( registers.rtc_wpr, CLEAR );\
                                write_reg( registers.rtc_wpr, FIRST_KEY );\
                                write_reg( registers.rtc_wpr, SECOND_KEY )

#define enter_init_mode set_reg_bit( registers.rtc_isr, INIT_BIT );\
                        while ( !check_reg_bit( registers.rtc_isr, INITF_BIT ) );
#define leave_init_mode clear_reg_bit( registers.rtc_isr, INIT_BIT );\
                        while ( check_reg_bit( registers.rtc_isr, INITF_BIT ) )

#define SET_TIME (((uint32_t)time->hour / 10) << 20) | (((uint32_t)time->hour % 10) << 16) | (((uint32_t)time->minute / 10)  << 12) | (((uint32_t)time->minute % 10) << 8) | (((uint32_t)time->second / 10) << 4) | (uint32_t)time->second % 10

#define GET_HOUR   (uint8_t)(((value & HOUR_TENS_MASK) >> 20) * 10 + ((value & HOUR_UNITS_MASK) >> 16))
#define GET_MINUTE (uint8_t)(((value & MIN_TENS_MASK) >> 12) * 10 + ((value & MIN_UNITS_MASK) >> 8))
#define GET_SECOND (uint8_t)(((value & SEC_TENS_MASK) >> 4) * 10 + (value & SEC_UNITS_MASK))

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

// ----------------------------------------------------------------- PRIVATE TYPES
/*!< @brief RTC register structure. */
/**
 *  Return values
 */
typedef enum
{
    HAL_LL_RTC_SUCCESS = 0,
    HAL_LL_RTC_ERROR = (-1)
} hal_ll_rtc_err_t;

typedef struct
{
    hal_ll_base_addr_t* rtc_wpr;
    hal_ll_base_addr_t* rtc_isr;
    hal_ll_base_addr_t* rtc_prer;
    hal_ll_base_addr_t* rtc_tr;
    hal_ll_base_addr_t* rtc_dr;
    hal_ll_base_addr_t* rtc_cr;
    hal_ll_base_addr_t* rtc_bkp0r;
    hal_ll_base_addr_t* rcc_bdcr;
    hal_ll_base_addr_t* pwr_cr1;
    hal_ll_base_addr_t* wwdg_cr;
    hal_ll_base_addr_t* rcc_csr;
    hal_ll_base_addr_t* rcc_apb4enr;
    hal_ll_base_addr_t* iwdg_kr;
} reg_t;

// -------------------------------------------------------------------- VARIABLES

/*!< @brief RTC registers info  */
 reg_t registers = { RTC_WPR_REG_ADDRESS, RTC_ISR_REG_ADDRESS, RTC_PRER_REG_ADDRESS, RTC_TR_REG_ADDRESS, RTC_DR_REG_ADDRESS, RTC_CR_REG_ADDRESS, RTC_BKP0R_REG_ADDRESS, RCC_BDCR_REG_ADDRESS, PWR_CR1_REG_ADDRESS, WWDG_CR_REG_ADDRESS, RCC_CSR_REG_ADDRESS, RCC_APB4ENR_REG_ADDRESS, IWDG_KR_REG_ADDRESS };

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
#endif

//------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
void hal_ll_rtc_init() {
    set_reg_bit( registers.rcc_apb4enr, RTCAPBEN_BIT);
    unlock_write_protection;
    set_reg_bit( registers.rcc_bdcr, RTCSEL_BIT );
    set_reg_bit( registers.rcc_csr, LSION_BIT );
    while ( !check_reg_bit( registers.rcc_csr, LSIRDY_BIT ) );
    hal_ll_rtc_start();
    enter_init_mode;
    clear_reg_bit( registers.rtc_cr, FMT_BIT );
    leave_init_mode;
    hal_ll_rtc_stop();
}

err_t hal_ll_rtc_start() {
    unlock_write_protection;
    set_reg_bit( registers.rcc_bdcr, RTCEN_BIT );
    if ( !check_reg_bit( registers.rcc_bdcr, RTCEN_BIT ) ) {
        return HAL_LL_RTC_ERROR;
    }
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_stop() {
    unlock_write_protection;
    clear_reg_bit( registers.rcc_bdcr, RTCEN_BIT );
    if ( check_reg_bit( registers.rcc_bdcr, RTCEN_BIT ) ) {
        return HAL_LL_RTC_ERROR;
    }
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_reset() {
    unlock_write_protection;
    enter_init_mode;
    Delay_100ms();
    write_reg( registers.rtc_tr, 0);
    Delay_100ms();
    leave_init_mode;
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time ) {
    uint32_t value;
    hal_ll_rtc_start();
    unlock_write_protection;
    enter_init_mode;
    value = SET_TIME;
    Delay_100ms();
    write_reg(registers.rtc_tr,value);
    Delay_100ms();
    leave_init_mode;
    return HAL_LL_RTC_SUCCESS;
}

err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *time ) {
    uint32_t value = read_reg( registers.rtc_tr );
    time->second = GET_SECOND; 
    time->minute = GET_MINUTE; 
    time->hour = GET_HOUR; 
    return HAL_LL_RTC_SUCCESS;
}

void hal_ll_rtc_system_reset() {
    unlock_write_protection;
    write_reg( registers.iwdg_kr, SOFTWARE_RESET_KEY );
    Delay_ms(1000);
}
