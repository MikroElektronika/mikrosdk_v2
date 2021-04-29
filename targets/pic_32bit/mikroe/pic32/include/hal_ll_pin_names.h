/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

#ifdef __RA0_CN
#define PA0  (0x00)
#endif
#ifdef __RA1_CN
#define PA1  (0x01)
#endif
#ifdef __RA2_CN
#define PA2  (0x02)
#endif
#ifdef __RA3_CN
#define PA3  (0x03)
#endif
#ifdef __RA4_CN
#define PA4  (0x04)
#endif
#ifdef __RA5_CN
#define PA5  (0x05)
#endif
#ifdef __RA6_CN
#define PA6  (0x06)
#endif
#ifdef __RA7_CN
#define PA7  (0x07)
#endif
#ifdef __RA8_CN
#define PA8  (0x08)
#endif
#ifdef __RA9_CN
#define PA9  (0x09)
#endif
#ifdef __RA10_CN
#define PA10 (0x0A)
#endif
#ifdef __RA11_CN
#define PA11 (0x0B)
#endif
#ifdef __RA12_CN
#define PA12 (0x0C)
#endif
#ifdef __RA13_CN
#define PA13 (0x0D)
#endif
#ifdef __RA14_CN
#define PA14 (0x0E)
#endif
#ifdef __RA15_CN
#define PA15 (0x0F)
#endif

#ifdef __RB0_CN
#define PB0  (0x10)
#endif
#ifdef __RB1_CN
#define PB1  (0x11)
#endif
#ifdef __RB2_CN
#define PB2  (0x12)
#endif
#ifdef __RB3_CN
#define PB3  (0x13)
#endif
#ifdef __RB4_CN
#define PB4  (0x14)
#endif
#ifdef __RB5_CN
#define PB5  (0x15)
#endif
#ifdef __RB6_CN
#define PB6  (0x16)
#endif
#ifdef __RB7_CN
#define PB7  (0x17)
#endif
#ifdef __RB8_CN
#define PB8  (0x18)
#endif
#ifdef __RB9_CN
#define PB9  (0x19)
#endif
#ifdef __RB10_CN
#define PB10 (0x1A)
#endif
#ifdef __RB11_CN
#define PB11 (0x1B)
#endif
#ifdef __RB12_CN
#define PB12 (0x1C)
#endif
#ifdef __RB13_CN
#define PB13 (0x1D)
#endif
#ifdef __RB14_CN
#define PB14 (0x1E)
#endif
#ifdef __RB15_CN
#define PB15 (0x1F)
#endif

#ifdef __RC0_CN
#define PC0  (0x20)
#endif
#ifdef __RC1_CN
#define PC1  (0x21)
#endif
#ifdef __RC2_CN
#define PC2  (0x22)
#endif
#ifdef __RC3_CN
#define PC3  (0x23)
#endif
#ifdef __RC4_CN
#define PC4  (0x24)
#endif
#ifdef __RC5_CN
#define PC5  (0x25)
#endif
#ifdef __RC6_CN
#define PC6  (0x26)
#endif
#ifdef __RC7_CN
#define PC7  (0x27)
#endif
#ifdef __RC8_CN
#define PC8  (0x28)
#endif
#ifdef __RC9_CN
#define PC9  (0x29)
#endif
#ifdef __RC10_CN
#define PC10 (0x2A)
#endif
#ifdef __RC11_CN
#define PC11 (0x2B)
#endif
#ifdef __RC12_CN
#define PC12 (0x2C)
#endif
#ifdef __RC13_CN
#define PC13 (0x2D)
#endif
#ifdef __RC14_CN
#define PC14 (0x2E)
#endif
#ifdef __RC15_CN
#define PC15 (0x2F)
#endif

#ifdef __RD0_CN
#define PD0  (0x30)
#endif
#ifdef __RD1_CN
#define PD1  (0x31)
#endif
#ifdef __RD2_CN
#define PD2  (0x32)
#endif
#ifdef __RD3_CN
#define PD3  (0x33)
#endif
#ifdef __RD4_CN
#define PD4  (0x34)
#endif
#ifdef __RD5_CN
#define PD5  (0x35)
#endif
#ifdef __RD6_CN
#define PD6  (0x36)
#endif
#ifdef __RD7_CN
#define PD7  (0x37)
#endif
#ifdef __RD8_CN
#define PD8  (0x38)
#endif
#ifdef __RD9_CN
#define PD9  (0x39)
#endif
#ifdef __RD10_CN
#define PD10 (0x3A)
#endif
#ifdef __RD11_CN
#define PD11 (0x3B)
#endif
#ifdef __RD12_CN
#define PD12 (0x3C)
#endif
#ifdef __RD13_CN
#define PD13 (0x3D)
#endif
#ifdef __RD14_CN
#define PD14 (0x3E)
#endif
#ifdef __RD15_CN
#define PD15 (0x3F)
#endif

#ifdef __RE0_CN
#define PE0  (0x40)
#endif
#ifdef __RE1_CN
#define PE1  (0x41)
#endif
#ifdef __RE2_CN
#define PE2  (0x42)
#endif
#ifdef __RE3_CN
#define PE3  (0x43)
#endif
#ifdef __RE4_CN
#define PE4  (0x44)
#endif
#ifdef __RE5_CN
#define PE5  (0x45)
#endif
#ifdef __RE6_CN
#define PE6  (0x46)
#endif
#ifdef __RE7_CN
#define PE7  (0x47)
#endif
#ifdef __RE8_CN
#define PE8  (0x48)
#endif
#ifdef __RE9_CN
#define PE9  (0x49)
#endif
#ifdef __RE10_CN
#define PE10 (0x4A)
#endif
#ifdef __RE11_CN
#define PE11 (0x4B)
#endif
#ifdef __RE12_CN
#define PE12 (0x4C)
#endif
#ifdef __RE13_CN
#define PE13 (0x4D)
#endif
#ifdef __RE14_CN
#define PE14 (0x4E)
#endif
#ifdef __RE15_CN
#define PE15 (0x4F)
#endif

#ifdef __RF0_CN
#define PF0  (0x50)
#endif
#ifdef __RF1_CN
#define PF1  (0x51)
#endif
#ifdef __RF2_CN
#define PF2  (0x52)
#endif
#ifdef __RF3_CN
#define PF3  (0x53)
#endif
#ifdef __RF4_CN
#define PF4  (0x54)
#endif
#ifdef __RF5_CN
#define PF5  (0x55)
#endif
#ifdef __RF6_CN
#define PF6  (0x56)
#endif
#ifdef __RF7_CN
#define PF7  (0x57)
#endif
#ifdef __RF8_CN
#define PF8  (0x58)
#endif
#ifdef __RF9_CN
#define PF9  (0x59)
#endif
#ifdef __RF10_CN
#define PF10 (0x5A)
#endif
#ifdef __RF11_CN
#define PF11 (0x5B)
#endif
#ifdef __RF12_CN
#define PF12 (0x5C)
#endif
#ifdef __RF13_CN
#define PF13 (0x5D)
#endif
#ifdef __RF14_CN
#define PF14 (0x5E)
#endif
#ifdef __RF15_CN
#define PF15 (0x5F)
#endif

#ifdef __RG0_CN
#define PG0  (0x60)
#endif
#ifdef __RG1_CN
#define PG1  (0x61)
#endif
#ifdef __RG2_CN
#define PG2  (0x62)
#endif
#ifdef __RG3_CN
#define PG3  (0x63)
#endif
#ifdef __RG4_CN
#define PG4  (0x64)
#endif
#ifdef __RG5_CN
#define PG5  (0x65)
#endif
#ifdef __RG6_CN
#define PG6  (0x66)
#endif
#ifdef __RG7_CN
#define PG7  (0x67)
#endif
#ifdef __RG8_CN
#define PG8  (0x68)
#endif
#ifdef __RG9_CN
#define PG9  (0x69)
#endif
#ifdef __RG10_CN
#define PG10 (0x6A)
#endif
#ifdef __RG11_CN
#define PG11 (0x6B)
#endif
#ifdef __RG12_CN
#define PG12 (0x6C)
#endif
#ifdef __RG13_CN
#define PG13 (0x6D)
#endif
#ifdef __RG14_CN
#define PG14 (0x6E)
#endif
#ifdef __RG15_CN
#define PG15 (0x6F)
#endif

#ifdef __RH0_CN
#define PH0  (0x70)
#endif
#ifdef __RH1_CN
#define PH1  (0x71)
#endif
#ifdef __RH2_CN
#define PH2  (0x72)
#endif
#ifdef __RH3_CN
#define PH3  (0x73)
#endif
#ifdef __RH4_CN
#define PH4  (0x74)
#endif
#ifdef __RH5_CN
#define PH5  (0x75)
#endif
#ifdef __RH6_CN
#define PH6  (0x76)
#endif
#ifdef __RH7_CN
#define PH7  (0x77)
#endif
#ifdef __RH8_CN
#define PH8  (0x78)
#endif
#ifdef __RH9_CN
#define PH9  (0x79)
#endif
#ifdef __RH10_CN
#define PH10 (0x7A)
#endif
#ifdef __RH11_CN
#define PH11 (0x7B)
#endif
#ifdef __RH12_CN
#define PH12 (0x7C)
#endif
#ifdef __RH13_CN
#define PH13 (0x7D)
#endif
#ifdef __RH14_CN
#define PH14 (0x7E)
#endif
#ifdef __RH15_CN
#define PH15 (0x7F)
#endif

#ifdef __RJ0_CN
#define PJ0  (0x80)
#endif
#ifdef __RJ1_CN
#define PJ1  (0x81)
#endif
#ifdef __RJ2_CN
#define PJ2  (0x82)
#endif
#ifdef __RJ3_CN
#define PJ3  (0x83)
#endif
#ifdef __RJ4_CN
#define PJ4  (0x84)
#endif
#ifdef __RJ5_CN
#define PJ5  (0x85)
#endif
#ifdef __RJ6_CN
#define PJ6  (0x86)
#endif
#ifdef __RJ7_CN
#define PJ7  (0x87)
#endif
#ifdef __RJ8_CN
#define PJ8  (0x88)
#endif
#ifdef __RJ9_CN
#define PJ9  (0x89)
#endif
#ifdef __RJ10_CN
#define PJ10 (0x8A)
#endif
#ifdef __RJ11_CN
#define PJ11 (0x8B)
#endif
#ifdef __RJ12_CN
#define PJ12 (0x8C)
#endif
#ifdef __RJ13_CN
#define PJ13 (0x8D)
#endif
#ifdef __RJ14_CN
#define PJ14 (0x8E)
#endif
#ifdef __RJ15_CN
#define PJ15 (0x8F)
#endif

#ifdef __RK0_CN
#define PK0  (0x90)
#endif
#ifdef __RK1_CN
#define PK1  (0x91)
#endif
#ifdef __RK2_CN
#define PK2  (0x92)
#endif
#ifdef __RK3_CN
#define PK3  (0x93)
#endif
#ifdef __RK4_CN
#define PK4  (0x94)
#endif
#ifdef __RK5_CN
#define PK5  (0x95)
#endif
#ifdef __RK6_CN
#define PK6  (0x96)
#endif
#ifdef __RK7_CN
#define PK7  (0x97)
#endif
#ifdef __RK8_CN
#define PK8  (0x98)
#endif
#ifdef __RK9_CN
#define PK9  (0x99)
#endif
#ifdef __RK10_CN
#define PK10 (0x9A)
#endif
#ifdef __RK11_CN
#define PK11 (0x9B)
#endif
#ifdef __RK12_CN
#define PK12 (0x9C)
#endif
#ifdef __RK13_CN
#define PK13 (0x9D)
#endif
#ifdef __RK14_CN
#define PK14 (0x9E)
#endif
#ifdef __RK15_CN
#define PK15 (0x9F)
#endif

#define PIN_0 (0x00)
#define PIN_1 (0x01)
#define PIN_2 (0x02)
#define PIN_3 (0x03)
#define PIN_4 (0x04)
#define PIN_5 (0x05)
#define PIN_6 (0x06)
#define PIN_7 (0x07)
#define PIN_8 (0x08)
#define PIN_9 (0x09)
#define PIN_10 (0x0A)
#define PIN_11 (0x0B)
#define PIN_12 (0x0C)
#define PIN_13 (0x0D)
#define PIN_14 (0x0E)
#define PIN_15 (0x0F)

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

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
