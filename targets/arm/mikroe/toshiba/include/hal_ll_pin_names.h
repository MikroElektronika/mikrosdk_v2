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
 * @file  hal_ll_pin_names.h
 * @brief Header file containing symbolic pin name definitions.
 */

#ifndef _HAL_LL_PIN_NAMES_H_
#define _HAL_LL_PIN_NAMES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_definitions.h"
#include "hal_ll_target_names.h"

#define GPIO_FEATURE_8BIT_PORT

#ifdef __PORT_A_CN
#define GPIO_FEATURE_GROUP_1
#endif
#ifdef __PORT_B_CN
#define GPIO_FEATURE_GROUP_2
#endif
#ifdef __PORT_C_CN
#define GPIO_FEATURE_GROUP_3
#endif
#ifdef __PORT_D_CN
#define GPIO_FEATURE_GROUP_4
#endif
#ifdef __PORT_E_CN
#define GPIO_FEATURE_GROUP_5
#endif
#ifdef __PORT_F_CN
#define GPIO_FEATURE_GROUP_6
#endif
#ifdef __PORT_G_CN
#define GPIO_FEATURE_GROUP_7
#endif
#ifdef __PORT_H_CN
#define GPIO_FEATURE_GROUP_8
#endif
#ifdef __PORT_J_CN
#define GPIO_FEATURE_GROUP_9
#endif
#ifdef __PORT_K_CN
#define GPIO_FEATURE_GROUP_10
#endif
#ifdef __PORT_L_CN
#define GPIO_FEATURE_GROUP_11
#endif
#ifdef __PORT_M_CN
#define GPIO_FEATURE_GROUP_12
#endif
#ifdef __PORT_N_CN
#define GPIO_FEATURE_GROUP_13
#endif
#ifdef __PORT_U_CN
#define GPIO_FEATURE_GROUP_14
#endif
#ifdef __PORT_V_CN
#define GPIO_FEATURE_GROUP_15
#endif

#ifdef __PA0_CN
#define GPIO_PA0 (0x00)
#define PA0 GPIO_PA0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA0!
#endif
#ifdef __PA1_CN
#define GPIO_PA1 (0x01)
#define PA1 GPIO_PA1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA1!
#endif
#ifdef __PA2_CN
#define GPIO_PA2 (0x02)
#define PA2 GPIO_PA2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA2!
#endif
#ifdef __PA3_CN
#define GPIO_PA3 (0x03)
#define PA3 GPIO_PA3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA3!
#endif
#ifdef __PA4_CN
#define GPIO_PA4 (0x04)
#define PA4 GPIO_PA4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA4!
#endif

#ifdef __PB0_CN
#define GPIO_PB0 (0x10)
#define PB0 GPIO_PB0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB0!
#endif
#ifdef __PB1_CN
#define GPIO_PB1 (0x11)
#define PB1 GPIO_PB1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB1!
#endif
#ifdef __PB2_CN
#define GPIO_PB2 (0x12)
#define PB2 GPIO_PB2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB2!
#endif
#ifdef __PB3_CN
#define GPIO_PB3 (0x13)
#define PB3 GPIO_PB3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB3!
#endif
#ifdef __PB4_CN
#define GPIO_PB4 (0x14)
#define PB4 GPIO_PB4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB4!
#endif
#ifdef __PB5_CN
#define GPIO_PB5 (0x15)
#define PB5 GPIO_PB5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB5!
#endif
#ifdef __PB6_CN
#define GPIO_PB6 (0x16)
#define PB6 GPIO_PB6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB6!
#endif
#ifdef __PB7_CN
#define GPIO_PB7 (0x17)
#define PB7 GPIO_PB7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB7!
#endif

#ifdef __PC0_CN
#define GPIO_PC0 (0x20)
#define PC0 GPIO_PC0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC0!
#endif
#ifdef __PC1_CN
#define GPIO_PC1 (0x21)
#define PC1 GPIO_PC1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC1!
#endif
#ifdef __PC2_CN
#define GPIO_PC2 (0x22)
#define PC2 GPIO_PC2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC2!
#endif
#ifdef __PC3_CN
#define GPIO_PC3 (0x23)
#define PC3 GPIO_PC3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC3!
#endif
#ifdef __PC4_CN
#define GPIO_PC4 (0x24)
#define PC4 GPIO_PC4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC4!
#endif
#ifdef __PC5_CN
#define GPIO_PC5 (0x25)
#define PC5 GPIO_PC5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC5!
#endif
#ifdef __PC6_CN
#define GPIO_PC6 (0x26)
#define PC6 GPIO_PC6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC6!
#endif
#ifdef __PC7_CN
#define GPIO_PC7 (0x27)
#define PC7 GPIO_PC7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC7!
#endif

#ifdef __PD0_CN
#define GPIO_PD0 (0x30)
#define PD0 GPIO_PD0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD0!
#endif
#ifdef __PD1_CN
#define GPIO_PD1 (0x31)
#define PD1 GPIO_PD1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD1!
#endif
#ifdef __PD2_CN
#define GPIO_PD2 (0x32)
#define PD2 GPIO_PD2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD2!
#endif
#ifdef __PD3_CN
#define GPIO_PD3 (0x33)
#define PD3 GPIO_PD3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD3!
#endif
#ifdef __PD4_CN
#define GPIO_PD4 (0x34)
#define PD4 GPIO_PD4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD4!
#endif
#ifdef __PD5_CN
#define GPIO_PD5 (0x35)
#define PD5 GPIO_PD5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD5!
#endif

#ifdef __PE0_CN
#define GPIO_PE0 (0x40)
#define PE0 GPIO_PE0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE0!
#endif
#ifdef __PE1_CN
#define GPIO_PE1 (0x41)
#define PE1 GPIO_PE1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE1!
#endif
#ifdef __PE2_CN
#define GPIO_PE2 (0x42)
#define PE2 GPIO_PE2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE2!
#endif
#ifdef __PE3_CN
#define GPIO_PE3 (0x43)
#define PE3 GPIO_PE3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE3!
#endif
#ifdef __PE4_CN
#define GPIO_PE4 (0x44)
#define PE4 GPIO_PE4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE4!
#endif
#ifdef __PE5_CN
#define GPIO_PE5 (0x45)
#define PE5 GPIO_PE5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE5!
#endif
#ifdef __PE6_CN
#define GPIO_PE6 (0x46)
#define PE6 GPIO_PE6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE6!
#endif
#ifdef __PE7_CN
#define GPIO_PE7 (0x47)
#define PE7 GPIO_PE7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE7!
#endif

#ifdef __PF0_CN
#define GPIO_PF0 (0x50)
#define PF0 GPIO_PF0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF0!
#endif
#ifdef __PF1_CN
#define GPIO_PF1 (0x51)
#define PF1 GPIO_PF1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF1!
#endif
#ifdef __PF2_CN
#define GPIO_PF2 (0x52)
#define PF2 GPIO_PF2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF2!
#endif
#ifdef __PF3_CN
#define GPIO_PF3 (0x53)
#define PF3 GPIO_PF3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF3!
#endif
#ifdef __PF4_CN
#define GPIO_PF4 (0x54)
#define PF4 GPIO_PF4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF4!
#endif
#ifdef __PF5_CN
#define GPIO_PF5 (0x55)
#define PF5 GPIO_PF5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF5!
#endif
#ifdef __PF6_CN
#define GPIO_PF6 (0x56)
#define PF6 GPIO_PF6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF6!
#endif
#ifdef __PF7_CN
#define GPIO_PF7 (0x57)
#define PF7 GPIO_PF7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF7!
#endif

#ifdef __PG0_CN
#define GPIO_PG0 (0x60)
#define PG0 GPIO_PG0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG0!
#endif
#ifdef __PG1_CN
#define GPIO_PG1 (0x61)
#define PG1 GPIO_PG1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG1!
#endif
#ifdef __PG2_CN
#define GPIO_PG2 (0x62)
#define PG2 GPIO_PG2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG2!
#endif
#ifdef __PG3_CN
#define GPIO_PG3 (0x63)
#define PG3 GPIO_PG3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG3!
#endif
#ifdef __PG4_CN
#define GPIO_PG4 (0x64)
#define PG4 GPIO_PG4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG4!
#endif
#ifdef __PG5_CN
#define GPIO_PG5 (0x65)
#define PG5 GPIO_PG5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG5!
#endif
#ifdef __PG6_CN
#define GPIO_PG6 (0x66)
#define PG6 GPIO_PG6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG6!
#endif

#ifdef __PH0_CN
#define GPIO_PH0 (0x70)
#define PH0 GPIO_PH0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH0!
#endif
#ifdef __PH1_CN
#define GPIO_PH1 (0x71)
#define PH1 GPIO_PH1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH1!
#endif

#ifdef __PJ0_CN
#define GPIO_PJ0 (0x80)
#define PJ0 GPIO_PJ0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ0!
#endif
#ifdef __PJ1_CN
#define GPIO_PJ1 (0x81)
#define PJ1 GPIO_PJ1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ1!
#endif
#ifdef __PJ2_CN
#define GPIO_PJ2 (0x82)
#define PJ2 GPIO_PJ2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ2!
#endif
#ifdef __PJ3_CN
#define GPIO_PJ3 (0x83)
#define PJ3 GPIO_PJ3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ3!
#endif
#ifdef __PJ4_CN
#define GPIO_PJ4 (0x84)
#define PJ4 GPIO_PJ4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ4!
#endif
#ifdef __PJ5_CN
#define GPIO_PJ5 (0x85)
#define PJ5 GPIO_PJ5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ5!
#endif

#ifdef __PK0_CN
#define GPIO_PK0 (0x90)
#define PK0 GPIO_PK0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK0!
#endif
#ifdef __PK1_CN
#define GPIO_PK1 (0x91)
#define PK1 GPIO_PK1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK1!
#endif
#ifdef __PK2_CN
#define GPIO_PK2 (0x92)
#define PK2 GPIO_PK2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK2!
#endif
#ifdef __PK3_CN
#define GPIO_PK3 (0x93)
#define PK3 GPIO_PK3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK3!
#endif
#ifdef __PK4_CN
#define GPIO_PK4 (0x94)
#define PK4 GPIO_PK4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK4!
#endif

#ifdef __PL0_CN
#define GPIO_PL0 (0xA0)
#define PL0 GPIO_PL0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL0!
#endif
#ifdef __PL1_CN
#define GPIO_PL1 (0xA1)
#define PL1 GPIO_PL1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL1!
#endif
#ifdef __PL2_CN
#define GPIO_PL2 (0xA2)
#define PL2 GPIO_PL2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL2!
#endif
#ifdef __PL3_CN
#define GPIO_PL3 (0xA3)
#define PL3 GPIO_PL3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL3!
#endif
#ifdef __PL4_CN
#define GPIO_PL4 (0xA4)
#define PL4 GPIO_PL4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL4!
#endif
#ifdef __PL5_CN
#define GPIO_PL5 (0xA5)
#define PL5 GPIO_PL5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL5!
#endif
#ifdef __PL6_CN
#define GPIO_PL6 (0xA6)
#define PL6 GPIO_PL6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL6!
#endif
#ifdef __PL7_CN
#define GPIO_PL7 (0xA7)
#define PL7 GPIO_PL7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL7!
#endif

#ifdef __PM0_CN
#define GPIO_PM0 (0xB0)
#define PM0 GPIO_PM0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM0!
#endif
#ifdef __PM1_CN
#define GPIO_PM1 (0xB1)
#define PM1 GPIO_PM1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM1!
#endif
#ifdef __PM2_CN
#define GPIO_PM2 (0xB2)
#define PM2 GPIO_PM2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM2!
#endif

#ifdef __PN0_CN
#define GPIO_PN0 (0xC0)
#define PN0 GPIO_PN0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN0!
#endif
#ifdef __PN1_CN
#define GPIO_PN1 (0xC1)
#define PN1 GPIO_PN1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN1!
#endif
#ifdef __PN2_CN
#define GPIO_PN2 (0xC2)
#define PN2 GPIO_PN2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN2!
#endif

#ifdef __PU0_CN
#define GPIO_PU0 (0xD0)
#define PU0 GPIO_PU0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU0!
#endif
#ifdef __PU1_CN
#define GPIO_PU1 (0xD1)
#define PU1 GPIO_PU1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU1!
#endif
#ifdef __PU2_CN
#define GPIO_PU2 (0xD2)
#define PU2 GPIO_PU2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU2!
#endif
#ifdef __PU3_CN
#define GPIO_PU3 (0xD3)
#define PU3 GPIO_PU3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU3!
#endif
#ifdef __PU4_CN
#define GPIO_PU4 (0xD4)
#define PU4 GPIO_PU4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU4!
#endif
#ifdef __PU5_CN
#define GPIO_PU5 (0xD5)
#define PU5 GPIO_PU5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU5!
#endif
#ifdef __PU6_CN
#define GPIO_PU6 (0xD6)
#define PU6 GPIO_PU6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU6!
#endif
#ifdef __PU7_CN
#define GPIO_PU7 (0xD7)
#define PU7 GPIO_PU7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PU7!
#endif

#ifdef __PV0_CN
#define GPIO_PV0 (0xE0)
#define PV0 GPIO_PV0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PV0!
#endif
#ifdef __PV1_CN
#define GPIO_PV1 (0xE1)
#define PV1 GPIO_PV1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PV1!
#endif

#define GPIO_PIN_0 (0x00)
#define PIN_0 GPIO_PIN_0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_0!
#define GPIO_PIN_1 (0x01)
#define PIN_1 GPIO_PIN_1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_1!
#define GPIO_PIN_2 (0x02)
#define PIN_2 GPIO_PIN_2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_2!
#define GPIO_PIN_3 (0x03)
#define PIN_3 GPIO_PIN_3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_3!
#define GPIO_PIN_4 (0x04)
#define PIN_4 GPIO_PIN_4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_4!
#define GPIO_PIN_5 (0x05)
#define PIN_5 GPIO_PIN_5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_5!
#define GPIO_PIN_6 (0x06)
#define PIN_6 GPIO_PIN_6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_6!
#define GPIO_PIN_7 (0x07)
#define PIN_7 GPIO_PIN_7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_7!

#ifdef __PORT_A_CN
#define GPIO_PORT_A (0x00)
#define PORT_A GPIO_PORT_A // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_A!
#endif
#ifdef __PORT_B_CN
#define GPIO_PORT_B (0x01)
#define PORT_B GPIO_PORT_B // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_B!
#endif
#ifdef __PORT_C_CN
#define GPIO_PORT_C (0x02)
#define PORT_C GPIO_PORT_C // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_C!
#endif
#ifdef __PORT_D_CN
#define GPIO_PORT_D (0x03)
#define PORT_D GPIO_PORT_D // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_D!
#endif
#ifdef __PORT_E_CN
#define GPIO_PORT_E (0x04)
#define PORT_E GPIO_PORT_E // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_E!
#endif
#ifdef __PORT_F_CN
#define GPIO_PORT_F (0x05)
#define PORT_F GPIO_PORT_F // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_F!
#endif
#ifdef __PORT_G_CN
#define GPIO_PORT_G (0x06)
#define PORT_G GPIO_PORT_G // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_G!
#endif
#ifdef __PORT_H_CN
#define GPIO_PORT_H (0x07)
#define PORT_H GPIO_PORT_H // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_H!
#endif
#ifdef __PORT_J_CN
#define GPIO_PORT_J (0x08)
#define PORT_J GPIO_PORT_J // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_J!
#endif
#ifdef __PORT_K_CN
#define GPIO_PORT_K (0x09)
#define PORT_K GPIO_PORT_K // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_K!
#endif
#ifdef __PORT_L_CN
#define GPIO_PORT_L (0x0A)
#define PORT_L GPIO_PORT_L // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_L!
#endif
#ifdef __PORT_M_CN
#define GPIO_PORT_M (0x0B)
#define PORT_M GPIO_PORT_M // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_M!
#endif
#ifdef __PORT_N_CN
#define GPIO_PORT_N (0x0C)
#define PORT_N GPIO_PORT_N // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_N!
#endif
#ifdef __PORT_U_CN
#define GPIO_PORT_U (0x0D)
#define PORT_U GPIO_PORT_U // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_U!
#endif
#ifdef __PORT_V_CN
#define GPIO_PORT_V (0x0E)
#define PORT_V GPIO_PORT_V // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_V!
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
