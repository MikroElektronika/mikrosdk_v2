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
#ifdef __PORT_P_CN
#define GPIO_FEATURE_GROUP_14
#endif
#ifdef __PORT_Q_CN
#define GPIO_FEATURE_GROUP_15
#endif
#ifdef __PORT_R_CN
#define GPIO_FEATURE_GROUP_16
#endif
#ifdef __PORT_S_CN
#define GPIO_FEATURE_GROUP_17
#endif
#ifdef __PORT_T_CN
#define GPIO_FEATURE_GROUP_18
#endif

#ifdef __PA0_CN
#define PA0  (0x00)
#endif
#ifdef __PA1_CN
#define PA1  (0x01)
#endif
#ifdef __PA2_CN
#define PA2  (0x02)
#endif
#ifdef __PA3_CN
#define PA3  (0x03)
#endif
#ifdef __PA4_CN
#define PA4  (0x04)
#endif
#ifdef __PA5_CN
#define PA5  (0x05)
#endif
#ifdef __PA6_CN
#define PA6  (0x06)
#endif
#ifdef __PA7_CN
#define PA7  (0x07)
#endif

#ifdef __PB0_CN
#define PB0  (0x08)
#endif
#ifdef __PB1_CN
#define PB1  (0x09)
#endif
#ifdef __PB2_CN
#define PB2  (0x0A)
#endif
#ifdef __PB3_CN
#define PB3  (0x0B)
#endif
#ifdef __PB4_CN
#define PB4  (0x0C)
#endif
#ifdef __PB5_CN
#define PB5  (0x0D)
#endif
#ifdef __PB6_CN
#define PB6  (0x0E)
#endif
#ifdef __PB7_CN
#define PB7  (0x0F)
#endif

#ifdef __PC0_CN
#define PC0  (0x10)
#endif
#ifdef __PC1_CN
#define PC1  (0x11)
#endif
#ifdef __PC2_CN
#define PC2  (0x12)
#endif
#ifdef __PC3_CN
#define PC3  (0x13)
#endif
#ifdef __PC4_CN
#define PC4  (0x14)
#endif
#ifdef __PC5_CN
#define PC5  (0x15)
#endif
#ifdef __PC6_CN
#define PC6  (0x16)
#endif
#ifdef __PC7_CN
#define PC7  (0x17)
#endif

#ifdef __PD0_CN
#define PD0  (0x18)
#endif
#ifdef __PD1_CN
#define PD1  (0x19)
#endif
#ifdef __PD2_CN
#define PD2  (0x1A)
#endif
#ifdef __PD3_CN
#define PD3  (0x1B)
#endif
#ifdef __PD4_CN
#define PD4  (0x1C)
#endif
#ifdef __PD5_CN
#define PD5  (0x1D)
#endif
#ifdef __PD6_CN
#define PD6  (0x1E)
#endif
#ifdef __PD7_CN
#define PD7  (0x1F)
#endif

#ifdef __PE0_CN
#define PE0  (0x20)
#endif
#ifdef __PE1_CN
#define PE1  (0x21)
#endif
#ifdef __PE2_CN
#define PE2  (0x22)
#endif
#ifdef __PE3_CN
#define PE3  (0x23)
#endif
#ifdef __PE4_CN
#define PE4  (0x24)
#endif
#ifdef __PE5_CN
#define PE5  (0x25)
#endif
#ifdef __PE6_CN
#define PE6  (0x26)
#endif
#ifdef __PE7_CN
#define PE7  (0x27)
#endif

#ifdef __PF0_CN
#define PF0  (0x28)
#endif
#ifdef __PF1_CN
#define PF1  (0x29)
#endif
#ifdef __PF2_CN
#define PF2  (0x2A)
#endif
#ifdef __PF3_CN
#define PF3  (0x2B)
#endif
#ifdef __PF4_CN
#define PF4  (0x2C)
#endif
#ifdef __PF5_CN
#define PF5  (0x2D)
#endif
#ifdef __PF6_CN
#define PF6  (0x2E)
#endif
#ifdef __PF7_CN
#define PF7  (0x2F)
#endif

#ifdef __PG0_CN
#define PG0  (0x30)
#endif
#ifdef __PG1_CN
#define PG1  (0x31)
#endif
#ifdef __PG2_CN
#define PG2  (0x32)
#endif
#ifdef __PG3_CN
#define PG3  (0x33)
#endif
#ifdef __PG4_CN
#define PG4  (0x34)
#endif
#ifdef __PG5_CN
#define PG5  (0x35)
#endif
#ifdef __PG6_CN
#define PG6  (0x36)
#endif
#ifdef __PG7_CN
#define PG7  (0x37)
#endif

#ifdef __PH0_CN
#define PH0  (0x38)
#endif
#ifdef __PH1_CN
#define PH1  (0x39)
#endif
#ifdef __PH2_CN
#define PH2  (0x3A)
#endif
#ifdef __PH3_CN
#define PH3  (0x3B)
#endif
#ifdef __PH4_CN
#define PH4  (0x3C)
#endif
#ifdef __PH5_CN
#define PH5  (0x3D)
#endif
#ifdef __PH6_CN
#define PH6  (0x3E)
#endif
#ifdef __PH7_CN
#define PH7  (0x3F)
#endif

#ifdef __PJ0_CN
#define PJ0  (0x40)
#endif
#ifdef __PJ1_CN
#define PJ1  (0x41)
#endif
#ifdef __PJ2_CN
#define PJ2  (0x42)
#endif
#ifdef __PJ3_CN
#define PJ3  (0x43)
#endif
#ifdef __PJ4_CN
#define PJ4  (0x44)
#endif
#ifdef __PJ5_CN
#define PJ5  (0x45)
#endif
#ifdef __PJ6_CN
#define PJ6  (0x46)
#endif
#ifdef __PJ7_CN
#define PJ7  (0x47)
#endif

#ifdef __PK0_CN
#define PK0  (0x48)
#endif
#ifdef __PK1_CN
#define PK1  (0x49)
#endif
#ifdef __PK2_CN
#define PK2  (0x4A)
#endif
#ifdef __PK3_CN
#define PK3  (0x4B)
#endif
#ifdef __PK4_CN
#define PK4  (0x4C)
#endif
#ifdef __PK5_CN
#define PK5  (0x4D)
#endif
#ifdef __PK6_CN
#define PK6  (0x4E)
#endif
#ifdef __PK7_CN
#define PK7  (0x4F)
#endif

#ifdef __PL0_CN
#define PL0  (0x50)
#endif
#ifdef __PL1_CN
#define PL1  (0x51)
#endif
#ifdef __PL2_CN
#define PL2  (0x52)
#endif
#ifdef __PL3_CN
#define PL3  (0x53)
#endif
#ifdef __PL4_CN
#define PL4  (0x54)
#endif
#ifdef __PL5_CN
#define PL5  (0x55)
#endif
#ifdef __PL6_CN
#define PL6  (0x56)
#endif
#ifdef __PL7_CN
#define PL7  (0x57)
#endif

#ifdef __PM0_CN
#define PM0  (0x58)
#endif
#ifdef __PM1_CN
#define PM1  (0x59)
#endif
#ifdef __PM2_CN
#define PM2  (0x5A)
#endif
#ifdef __PM3_CN
#define PM3  (0x5B)
#endif
#ifdef __PM4_CN
#define PM4  (0x5C)
#endif
#ifdef __PM5_CN
#define PM5  (0x5D)
#endif
#ifdef __PM6_CN
#define PM6  (0x5E)
#endif
#ifdef __PM7_CN
#define PM7  (0x5F)
#endif

#ifdef __PN0_CN
#define PN0  (0x60)
#endif
#ifdef __PN1_CN
#define PN1  (0x61)
#endif
#ifdef __PN2_CN
#define PN2  (0x62)
#endif
#ifdef __PN3_CN
#define PN3  (0x63)
#endif
#ifdef __PN4_CN
#define PN4  (0x64)
#endif
#ifdef __PN5_CN
#define PN5  (0x65)
#endif
#ifdef __PN6_CN
#define PN6  (0x66)
#endif
#ifdef __PN7_CN
#define PN7  (0x67)
#endif

#ifdef __PP0_CN
#define PP0  (0x68)
#endif
#ifdef __PP1_CN
#define PP1  (0x69)
#endif
#ifdef __PP2_CN
#define PP2  (0x6A)
#endif
#ifdef __PP3_CN
#define PP3  (0x6B)
#endif
#ifdef __PP4_CN
#define PP4  (0x6C)
#endif
#ifdef __PP5_CN
#define PP5  (0x6D)
#endif
#ifdef __PP6_CN
#define PP6  (0x6E)
#endif
#ifdef __PP7_CN
#define PP7  (0x6F)
#endif

#ifdef __PQ0_CN
#define PQ0  (0x70)
#endif
#ifdef __PQ1_CN
#define PQ1  (0x71)
#endif
#ifdef __PQ2_CN
#define PQ2  (0x72)
#endif
#ifdef __PQ3_CN
#define PQ3  (0x73)
#endif
#ifdef __PQ4_CN
#define PQ4  (0x74)
#endif
#ifdef __PQ5_CN
#define PQ5  (0x75)
#endif
#ifdef __PQ6_CN
#define PQ6  (0x76)
#endif
#ifdef __PQ7_CN
#define PQ7  (0x77)
#endif

#ifdef __PR0_CN
#define PR0  (0x78)
#endif
#ifdef __PR1_CN
#define PR1  (0x79)
#endif
#ifdef __PR2_CN
#define PR2  (0x7A)
#endif
#ifdef __PR3_CN
#define PR3  (0x7B)
#endif
#ifdef __PR4_CN
#define PR4  (0x7C)
#endif
#ifdef __PR5_CN
#define PR5  (0x7D)
#endif
#ifdef __PR6_CN
#define PR6  (0x7E)
#endif
#ifdef __PR7_CN
#define PR7  (0x7F)
#endif

#ifdef __PS0_CN
#define PS0  (0x80)
#endif
#ifdef __PS1_CN
#define PS1  (0x81)
#endif
#ifdef __PS2_CN
#define PS2  (0x82)
#endif
#ifdef __PS3_CN
#define PS3  (0x83)
#endif
#ifdef __PS4_CN
#define PS4  (0x84)
#endif
#ifdef __PS5_CN
#define PS5  (0x85)
#endif
#ifdef __PS6_CN
#define PS6  (0x86)
#endif
#ifdef __PS7_CN
#define PS7  (0x87)
#endif

#ifdef __PT0_CN
#define PT0  (0x88)
#endif
#ifdef __PT1_CN
#define PT1  (0x89)
#endif
#ifdef __PT2_CN
#define PT2  (0x8A)
#endif
#ifdef __PT3_CN
#define PT3  (0x8B)
#endif
#ifdef __PT4_CN
#define PT4  (0x8C)
#endif
#ifdef __PT5_CN
#define PT5  (0x8D)
#endif
#ifdef __PT6_CN
#define PT6  (0x8E)
#endif
#ifdef __PT7_CN
#define PT7  (0x8F)
#endif

#define PIN_0  (0x00)
#define PIN_1  (0x01)
#define PIN_2  (0x02)
#define PIN_3  (0x03)
#define PIN_4  (0x04)
#define PIN_5  (0x05)
#define PIN_6  (0x06)
#define PIN_7  (0x07)

#ifdef __PORT_A_CN
#define PORT_A (0x00)
#endif
#ifdef __PORT_B_CN
#define PORT_B (0x01)
#endif
#ifdef __PORT_C_CN
#define PORT_C (0x02)
#endif
#ifdef __PORT_D_CN
#define PORT_D (0x03)
#endif
#ifdef __PORT_E_CN
#define PORT_E (0x04)
#endif
#ifdef __PORT_F_CN
#define PORT_F (0x05)
#endif
#ifdef __PORT_G_CN
#define PORT_G (0x06)
#endif
#ifdef __PORT_H_CN
#define PORT_H (0x07)
#endif
#ifdef __PORT_J_CN
#define PORT_J (0x08)
#endif
#ifdef __PORT_K_CN
#define PORT_K (0x09)
#endif
#ifdef __PORT_L_CN
#define PORT_L (0x0A)
#endif
#ifdef __PORT_M_CN
#define PORT_M (0x0B)
#endif
#ifdef __PORT_N_CN
#define PORT_N (0x0C)
#endif
#ifdef __PORT_P_CN
#define PORT_P (0x0D)
#endif
#ifdef __PORT_Q_CN
#define PORT_Q (0x0E)
#endif
#ifdef __PORT_R_CN
#define PORT_R (0x0F)
#endif
#ifdef __PORT_S_CN
#define PORT_S (0x10)
#endif
#ifdef __PORT_T_CN
#define PORT_T (0x11)
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
