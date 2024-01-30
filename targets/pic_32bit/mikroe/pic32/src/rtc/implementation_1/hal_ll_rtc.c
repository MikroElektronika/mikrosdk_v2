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

// ---------------------------------------------------------------- PRIVATE MACROS

/*!< @brief MACROS for the code */
#define DEFAULT_TIME               0x00000000
#define DEFAULT_DATE               0x00010107
#define FIRST_KEY                  0xaa996655
#define SECOND_KEY                 0x556699aa
#define ENABLE_WRITE               0x00000008
#define DISABLE_RTC_INTERRUPTION   0x00008000
#define SET_RTCC_OFF               0x00008000
#define SET_RTCC_ON                0x00008000
#define CLOCK_OFF                  0x00000040
#define CLEAR_RTCC_EVENT           0x00008000
#define CLEAR_PRIORITY             0x1f000000
#define CLEAR_RTCALRM              0x0000CFFF
#define RTC_ON                     read_reg(registers.rtc_con) & CLOCK_OFF
#define RTC_OFF                    !(read_reg(registers.rtc_con) & CLOCK_OFF)
#define UNREADABLE_REGISTER        !check_reg_bit(registers.rtc_con, B2)
#define MODIFIED_REGISTER          (read_reg(registers.rtc_time) == new_time)
#define DEFAULT_REGISTER           (read_reg(registers.rtc_time) == DEFAULT_TIME)
#define CLEAR                      0
#define BIT0                       0
#define OFF                        0
#define ON                         1
#define BIT1                       1
#define BIT22                      22

/*!< @brief RTCTIME REGISTER MASKS */
#define RTCTIME_MASK_HR10          0x30000000
#define RTCTIME_MASK_HR01          0x0f000000
#define RTCTIME_MASK_MIN10         0x00700000
#define RTCTIME_MASK_MIN01         0x000f0000
#define RTCTIME_MASK_SEC10         0x00007000
#define RTCTIME_MASK_SEC01         0x00000f00

/*!< @brief REGISTER CONVERTER MACROS */
#define HOUR10_TO_HOUR             ((read_reg(registers.rtc_time) & RTCTIME_MASK_HR10) >> 28) * 10
#define HOUR01_TO_HOUR             (read_reg(registers.rtc_time) & RTCTIME_MASK_HR01) >> 24
#define MINUTE10_TO_MINUTE         ((read_reg(registers.rtc_time) & RTCTIME_MASK_MIN10) >> 20) * 10
#define MINUTE01_TO_MINUTE         (read_reg(registers.rtc_time) & RTCTIME_MASK_MIN01) >> 16
#define SECOND10_TO_SECOND         ((read_reg(registers.rtc_time) & RTCTIME_MASK_SEC10) >> 12) * 10
#define SECOND01_TO_SECOND         (read_reg(registers.rtc_time) & RTCTIME_MASK_SEC01) >> 8

#define SECOND_TO_SECOND01         time->second % 10
#define SECOND_TO_SECOND10         (time->second - seconds_01) / 10
#define MINUTE_TO_MINUTE01         time->minute % 10
#define MINUTE_TO_MINUTE10         (time->minute - minutes_01) / 10
#define HOUR_TO_HOUR01             time->hour % 10
#define HOUR_TO_HOUR10             (time->hour - hours_01) / 10
#define SECOND_TO_REGISTER         ((uint32_t)seconds_01 << 8) | ((uint32_t)seconds_10 << 12)
#define MINUTE_TO_REGISTER         ((uint32_t)minutes_01 << 16) | ((uint32_t)minutes_10 << 20)
#define HOUR_TO_REGISTER           ((uint32_t)hours_01 << 24) | ((uint32_t)hours_10 << 28)

/*!< @brief SOFTWARE RESET MACROS */
#define WAIT_RESET                 asm nop;\
                                   asm nop;\
                                   asm nop;\
                                   asm nop;\
                                   asm nop;

// ----------------------------------------------------------------- PRIVATE TYPES
/**
 *  Return values
 */
typedef enum
{
    HAL_LL_RTC_SUCCESS = 0,
    HAL_LL_RTC_ERROR = (-1)
} hal_ll_rtc_err_t;

/*!< @brief RTC register structure. */
typedef struct
{
    hal_ll_base_addr_t sys_key;
    hal_ll_base_addr_t osc_con;
    hal_ll_base_addr_t rtc_con;
    hal_ll_base_addr_t rtc_con_set;
    hal_ll_base_addr_t rtc_con_clr;
    hal_ll_base_addr_t rtc_date;
    hal_ll_base_addr_t rtc_time;
    hal_ll_base_addr_t rtc_alrm_clr;
    hal_ll_base_addr_t rswrst_set;
    hal_ll_base_addr_t rswrst;
    hal_ll_base_addr_t iec1_clr;
    hal_ll_base_addr_t ifs1_clr;
    hal_ll_base_addr_t ipc8_clr;
} reg_t;

// -------------------------------------------------------------------- VARIABLES

/*!< @brief RTC registers info  */
reg_t registers = { SYSKEY_REG_ADDRESS, OSCCON_REG_ADDRESS, RTCCON_REG_ADDRESS, RTCCONSET_REG_ADDRESS, RTCCONCLR_REG_ADDRESS, RTCDATE_REG_ADDRESS, RTCTIME_REG_ADDRESS, RTCALRMCLR_REG_ADDRESS, RSWRSTSET_REG_ADDRESS, RSWRST_REG_ADDRESS, IEC1CLR_REG_ADDRESS, IFS1CLR_REG_ADDRESS, IPC8CLR_REG_ADDRESS };

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Create an uint32_t variable that can be used to change the time register.
 * @param[in] time: RTC time structure.
 * @return uint32_t variable that suits the RTC time register requirement.
 * @details Use the different values of the RTC time structure to create a variable that can be used to change the time register.
 *
 * @b Example
 * @code
 *  // Time structure.
 *  static rtc_t time;
 *
 *  // Create a new variable that can be used in the time register.
 *  uint32_t NEW_TIME = set_time_register(time);
 *  @endcode
 * */
static uint32_t set_time_register( hal_ll_rtc_time_t *time );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

err_t hal_ll_rtc_get_time( hal_ll_rtc_time_t *rtc ) {
    uint8_t rtc_state = ON ;
    if( RTC_OFF){
        hal_ll_rtc_start(); 
        rtc_state = OFF;
    }

    while( UNREADABLE_REGISTER );

    rtc->hour  = HOUR10_TO_HOUR;
    rtc->hour += HOUR01_TO_HOUR;

    rtc->minute  = MINUTE10_TO_MINUTE;
    rtc->minute += MINUTE01_TO_MINUTE;

    rtc->second  = SECOND10_TO_SECOND;
    rtc->second += SECOND01_TO_SECOND;

    if( !rtc_state ){
        hal_ll_rtc_stop();
    }
    return HAL_LL_RTC_SUCCESS;
}

void hal_ll_rtc_init() {

    // Unlock write protection.
    write_reg( registers.sys_key, CLEAR );
    write_reg( registers.sys_key, CLEAR );
    write_reg( registers.sys_key, FIRST_KEY );
    write_reg( registers.sys_key, SECOND_KEY );

    set_reg_bit( registers.osc_con, BIT1 );
    set_reg_bit( registers.osc_con, BIT22 );
    // Turn off the RTCC.
    write_reg( registers.rtc_con_set, ENABLE_WRITE );
    write_reg( registers.iec1_clr, DISABLE_RTC_INTERRUPTION );
    write_reg( registers.rtc_con_clr, SET_RTCC_OFF );

     // Wait for RTCC to be turned off.
    while ( RTC_ON );

    write_reg( registers.ifs1_clr, CLEAR_RTCC_EVENT );
    write_reg( registers.ipc8_clr, CLEAR_PRIORITY );
    write_reg( registers.rtc_alrm_clr, CLEAR_RTCALRM );
    write_reg( registers.sys_key, CLEAR );
}

err_t hal_ll_rtc_stop() {

    write_reg( registers.sys_key, CLEAR );
    write_reg( registers.sys_key, FIRST_KEY );
    write_reg( registers.sys_key, SECOND_KEY );
    
    // Turn off the RTCC.
    write_reg( registers.rtc_con_set, ENABLE_WRITE );
    write_reg( registers.rtc_con_clr, SET_RTCC_OFF );

    // Wait for RTCC to be turned off.
    while ( RTC_ON );
    write_reg( registers.sys_key, CLEAR );
    if ( RTC_OFF )
      return HAL_LL_RTC_SUCCESS;
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_start() {

    // Turn on the clock.
    write_reg( registers.sys_key, CLEAR );
    write_reg( registers.sys_key, FIRST_KEY );
    write_reg( registers.sys_key, SECOND_KEY );
    set_reg_bit( registers.osc_con, BIT1 );
    set_reg_bit( registers.osc_con, BIT22 );
     // Unlock write protection.

    // Turn on the RTCC.
    write_reg( registers.rtc_con_set, ENABLE_WRITE );
    write_reg( registers.rtc_con_set, SET_RTCC_ON );

    // Wait for RTCC to be turned on.
    while ( RTC_OFF );

    if ( RTC_ON )
      return HAL_LL_RTC_SUCCESS;
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_set_time( hal_ll_rtc_time_t *time ) {

    uint32_t new_time = set_time_register( time );

    // Turn off the RTCC.
    write_reg( registers.iec1_clr, DISABLE_RTC_INTERRUPTION );
    write_reg( registers.rtc_con_clr, SET_RTCC_OFF );

    // Wait for clock to be turned off.
    while ( RTC_ON );

    // Update the time and date.
    write_reg( registers.rtc_time, new_time );
    // Turn on the RTCC.
    write_reg( registers.rtc_con_set, SET_RTCC_ON );

    // Wait for clock to be turned on.
    while ( RTC_OFF );

    if ( MODIFIED_REGISTER )
        return HAL_LL_RTC_SUCCESS;
    else
        return HAL_LL_RTC_ERROR;
}

err_t hal_ll_rtc_reset() {

    // Turn off the RTCC.
    write_reg( registers.iec1_clr, DISABLE_RTC_INTERRUPTION );
    write_reg( registers.rtc_con_clr, SET_RTCC_OFF );

    // Wait for clock to be turned off.
    while ( RTC_ON );

    // Update the date to date.
    write_reg( registers.rtc_time, DEFAULT_TIME );

    // Turn on the RTCC.
    write_reg( registers.rtc_con_set, SET_RTCC_ON );

    // Wait for clock to be turned on.
    while ( RTC_OFF );

    if ( DEFAULT_REGISTER )
        return HAL_LL_RTC_SUCCESS;
    else
        return HAL_LL_RTC_ERROR;
}

void hal_ll_software_reset() {

    uint32_t volatile read;

    // Turn on the clock.
    write_reg( registers.sys_key, CLEAR );
    write_reg( registers.sys_key, FIRST_KEY );
    write_reg( registers.sys_key, SECOND_KEY );

    // Enable reset.
    set_reg_bit(registers.rswrst_set, BIT0);

    // Lauch reset.
    read = read_reg( registers.rswrst );
    set_reg_bit(registers.rswrst_set, BIT0);
    
    WAIT_RESET;
}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS

static uint32_t set_time_register( hal_ll_rtc_time_t *time ) {

    uint8_t seconds_01 = SECOND_TO_SECOND01;
    uint8_t seconds_10 = SECOND_TO_SECOND10;

    uint8_t minutes_01 = MINUTE_TO_MINUTE01;
    uint8_t minutes_10 = MINUTE_TO_MINUTE10;

    uint8_t hours_01 = HOUR_TO_HOUR01;
    uint8_t hours_10 = HOUR_TO_HOUR10;

    uint32_t new_time = SECOND_TO_REGISTER;

    new_time |= MINUTE_TO_REGISTER;
    new_time |= HOUR_TO_REGISTER;

    return new_time;
}
