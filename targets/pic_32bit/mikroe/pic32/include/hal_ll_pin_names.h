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

#ifdef __RA0_CN
#define GPIO_PA0 (0x00)
#define PA0 GPIO_PA0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA0!
#endif
#ifdef __RA1_CN
#define GPIO_PA1 (0x01)
#define PA1 GPIO_PA1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA1!
#endif
#ifdef __RA2_CN
#define GPIO_PA2 (0x02)
#define PA2 GPIO_PA2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA2!
#endif
#ifdef __RA3_CN
#define GPIO_PA3 (0x03)
#define PA3 GPIO_PA3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA3!
#endif
#ifdef __RA4_CN
#define GPIO_PA4 (0x04)
#define PA4 GPIO_PA4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA4!
#endif
#ifdef __RA5_CN
#define GPIO_PA5 (0x05)
#define PA5 GPIO_PA5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA5!
#endif
#ifdef __RA6_CN
#define GPIO_PA6 (0x06)
#define PA6 GPIO_PA6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA6!
#endif
#ifdef __RA7_CN
#define GPIO_PA7 (0x07)
#define PA7 GPIO_PA7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA7!
#endif
#ifdef __RA8_CN
#define GPIO_PA8 (0x08)
#define PA8 GPIO_PA8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA8!
#endif
#ifdef __RA9_CN
#define GPIO_PA9 (0x09)
#define PA9 GPIO_PA9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA9!
#endif
#ifdef __RA10_CN
#define GPIO_PA10 (0x0A)
#define PA10 GPIO_PA10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA10!
#endif
#ifdef __RA11_CN
#define GPIO_PA11 (0x0B)
#define PA11 GPIO_PA11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA11!
#endif
#ifdef __RA12_CN
#define GPIO_PA12 (0x0C)
#define PA12 GPIO_PA12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA12!
#endif
#ifdef __RA13_CN
#define GPIO_PA13 (0x0D)
#define PA13 GPIO_PA13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA13!
#endif
#ifdef __RA14_CN
#define GPIO_PA14 (0x0E)
#define PA14 GPIO_PA14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA14!
#endif
#ifdef __RA15_CN
#define GPIO_PA15 (0x0F)
#define PA15 GPIO_PA15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA15!
#endif

#ifdef __RB0_CN
#define GPIO_PB0 (0x10)
#define PB0 GPIO_PB0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB0!
#endif
#ifdef __RB1_CN
#define GPIO_PB1 (0x11)
#define PB1 GPIO_PB1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB1!
#endif
#ifdef __RB2_CN
#define GPIO_PB2 (0x12)
#define PB2 GPIO_PB2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB2!
#endif
#ifdef __RB3_CN
#define GPIO_PB3 (0x13)
#define PB3 GPIO_PB3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB3!
#endif
#ifdef __RB4_CN
#define GPIO_PB4 (0x14)
#define PB4 GPIO_PB4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB4!
#endif
#ifdef __RB5_CN
#define GPIO_PB5 (0x15)
#define PB5 GPIO_PB5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB5!
#endif
#ifdef __RB6_CN
#define GPIO_PB6 (0x16)
#define PB6 GPIO_PB6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB6!
#endif
#ifdef __RB7_CN
#define GPIO_PB7 (0x17)
#define PB7 GPIO_PB7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB7!
#endif
#ifdef __RB8_CN
#define GPIO_PB8 (0x18)
#define PB8 GPIO_PB8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB8!
#endif
#ifdef __RB9_CN
#define GPIO_PB9 (0x19)
#define PB9 GPIO_PB9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB9!
#endif
#ifdef __RB10_CN
#define GPIO_PB10 (0x1A)
#define PB10 GPIO_PB10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB10!
#endif
#ifdef __RB11_CN
#define GPIO_PB11 (0x1B)
#define PB11 GPIO_PB11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB11!
#endif
#ifdef __RB12_CN
#define GPIO_PB12 (0x1C)
#define PB12 GPIO_PB12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB12!
#endif
#ifdef __RB13_CN
#define GPIO_PB13 (0x1D)
#define PB13 GPIO_PB13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB13!
#endif
#ifdef __RB14_CN
#define GPIO_PB14 (0x1E)
#define PB14 GPIO_PB14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB14!
#endif
#ifdef __RB15_CN
#define GPIO_PB15 (0x1F)
#define PB15 GPIO_PB15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB15!
#endif

#ifdef __RC0_CN
#define GPIO_PC0 (0x20)
#define PC0 GPIO_PC0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC0!
#endif
#ifdef __RC1_CN
#define GPIO_PC1 (0x21)
#define PC1 GPIO_PC1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC1!
#endif
#ifdef __RC2_CN
#define GPIO_PC2 (0x22)
#define PC2 GPIO_PC2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC2!
#endif
#ifdef __RC3_CN
#define GPIO_PC3 (0x23)
#define PC3 GPIO_PC3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC3!
#endif
#ifdef __RC4_CN
#define GPIO_PC4 (0x24)
#define PC4 GPIO_PC4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC4!
#endif
#ifdef __RC5_CN
#define GPIO_PC5 (0x25)
#define PC5 GPIO_PC5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC5!
#endif
#ifdef __RC6_CN
#define GPIO_PC6 (0x26)
#define PC6 GPIO_PC6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC6!
#endif
#ifdef __RC7_CN
#define GPIO_PC7 (0x27)
#define PC7 GPIO_PC7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC7!
#endif
#ifdef __RC8_CN
#define GPIO_PC8 (0x28)
#define PC8 GPIO_PC8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC8!
#endif
#ifdef __RC9_CN
#define GPIO_PC9 (0x29)
#define PC9 GPIO_PC9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC9!
#endif
#ifdef __RC10_CN
#define GPIO_PC10 (0x2A)
#define PC10 GPIO_PC10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC10!
#endif
#ifdef __RC11_CN
#define GPIO_PC11 (0x2B)
#define PC11 GPIO_PC11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC11!
#endif
#ifdef __RC12_CN
#define GPIO_PC12 (0x2C)
#define PC12 GPIO_PC12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC12!
#endif
#ifdef __RC13_CN
#define GPIO_PC13 (0x2D)
#define PC13 GPIO_PC13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC13!
#endif
#ifdef __RC14_CN
#define GPIO_PC14 (0x2E)
#define PC14 GPIO_PC14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC14!
#endif
#ifdef __RC15_CN
#define GPIO_PC15 (0x2F)
#define PC15 GPIO_PC15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC15!
#endif

#ifdef __RD0_CN
#define GPIO_PD0 (0x30)
#define PD0 GPIO_PD0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD0!
#endif
#ifdef __RD1_CN
#define GPIO_PD1 (0x31)
#define PD1 GPIO_PD1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD1!
#endif
#ifdef __RD2_CN
#define GPIO_PD2 (0x32)
#define PD2 GPIO_PD2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD2!
#endif
#ifdef __RD3_CN
#define GPIO_PD3 (0x33)
#define PD3 GPIO_PD3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD3!
#endif
#ifdef __RD4_CN
#define GPIO_PD4 (0x34)
#define PD4 GPIO_PD4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD4!
#endif
#ifdef __RD5_CN
#define GPIO_PD5 (0x35)
#define PD5 GPIO_PD5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD5!
#endif
#ifdef __RD6_CN
#define GPIO_PD6 (0x36)
#define PD6 GPIO_PD6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD6!
#endif
#ifdef __RD7_CN
#define GPIO_PD7 (0x37)
#define PD7 GPIO_PD7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD7!
#endif
#ifdef __RD8_CN
#define GPIO_PD8 (0x38)
#define PD8 GPIO_PD8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD8!
#endif
#ifdef __RD9_CN
#define GPIO_PD9 (0x39)
#define PD9 GPIO_PD9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD9!
#endif
#ifdef __RD10_CN
#define GPIO_PD10 (0x3A)
#define PD10 GPIO_PD10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD10!
#endif
#ifdef __RD11_CN
#define GPIO_PD11 (0x3B)
#define PD11 GPIO_PD11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD11!
#endif
#ifdef __RD12_CN
#define GPIO_PD12 (0x3C)
#define PD12 GPIO_PD12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD12!
#endif
#ifdef __RD13_CN
#define GPIO_PD13 (0x3D)
#define PD13 GPIO_PD13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD13!
#endif
#ifdef __RD14_CN
#define GPIO_PD14 (0x3E)
#define PD14 GPIO_PD14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD14!
#endif
#ifdef __RD15_CN
#define GPIO_PD15 (0x3F)
#define PD15 GPIO_PD15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD15!
#endif

#ifdef __RE0_CN
#define GPIO_PE0 (0x40)
#define PE0 GPIO_PE0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE0!
#endif
#ifdef __RE1_CN
#define GPIO_PE1 (0x41)
#define PE1 GPIO_PE1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE1!
#endif
#ifdef __RE2_CN
#define GPIO_PE2 (0x42)
#define PE2 GPIO_PE2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE2!
#endif
#ifdef __RE3_CN
#define GPIO_PE3 (0x43)
#define PE3 GPIO_PE3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE3!
#endif
#ifdef __RE4_CN
#define GPIO_PE4 (0x44)
#define PE4 GPIO_PE4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE4!
#endif
#ifdef __RE5_CN
#define GPIO_PE5 (0x45)
#define PE5 GPIO_PE5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE5!
#endif
#ifdef __RE6_CN
#define GPIO_PE6 (0x46)
#define PE6 GPIO_PE6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE6!
#endif
#ifdef __RE7_CN
#define GPIO_PE7 (0x47)
#define PE7 GPIO_PE7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE7!
#endif
#ifdef __RE8_CN
#define GPIO_PE8 (0x48)
#define PE8 GPIO_PE8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE8!
#endif
#ifdef __RE9_CN
#define GPIO_PE9 (0x49)
#define PE9 GPIO_PE9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE9!
#endif
#ifdef __RE10_CN
#define GPIO_PE10 (0x4A)
#define PE10 GPIO_PE10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE10!
#endif
#ifdef __RE11_CN
#define GPIO_PE11 (0x4B)
#define PE11 GPIO_PE11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE11!
#endif
#ifdef __RE12_CN
#define GPIO_PE12 (0x4C)
#define PE12 GPIO_PE12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE12!
#endif
#ifdef __RE13_CN
#define GPIO_PE13 (0x4D)
#define PE13 GPIO_PE13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE13!
#endif
#ifdef __RE14_CN
#define GPIO_PE14 (0x4E)
#define PE14 GPIO_PE14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE14!
#endif
#ifdef __RE15_CN
#define GPIO_PE15 (0x4F)
#define PE15 GPIO_PE15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE15!
#endif

#ifdef __RF0_CN
#define GPIO_PF0 (0x50)
#define PF0 GPIO_PF0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF0!
#endif
#ifdef __RF1_CN
#define GPIO_PF1 (0x51)
#define PF1 GPIO_PF1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF1!
#endif
#ifdef __RF2_CN
#define GPIO_PF2 (0x52)
#define PF2 GPIO_PF2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF2!
#endif
#ifdef __RF3_CN
#define GPIO_PF3 (0x53)
#define PF3 GPIO_PF3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF3!
#endif
#ifdef __RF4_CN
#define GPIO_PF4 (0x54)
#define PF4 GPIO_PF4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF4!
#endif
#ifdef __RF5_CN
#define GPIO_PF5 (0x55)
#define PF5 GPIO_PF5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF5!
#endif
#ifdef __RF6_CN
#define GPIO_PF6 (0x56)
#define PF6 GPIO_PF6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF6!
#endif
#ifdef __RF7_CN
#define GPIO_PF7 (0x57)
#define PF7 GPIO_PF7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF7!
#endif
#ifdef __RF8_CN
#define GPIO_PF8 (0x58)
#define PF8 GPIO_PF8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF8!
#endif
#ifdef __RF9_CN
#define GPIO_PF9 (0x59)
#define PF9 GPIO_PF9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF9!
#endif
#ifdef __RF10_CN
#define GPIO_PF10 (0x5A)
#define PF10 GPIO_PF10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF10!
#endif
#ifdef __RF11_CN
#define GPIO_PF11 (0x5B)
#define PF11 GPIO_PF11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF11!
#endif
#ifdef __RF12_CN
#define GPIO_PF12 (0x5C)
#define PF12 GPIO_PF12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF12!
#endif
#ifdef __RF13_CN
#define GPIO_PF13 (0x5D)
#define PF13 GPIO_PF13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF13!
#endif
#ifdef __RF14_CN
#define GPIO_PF14 (0x5E)
#define PF14 GPIO_PF14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF14!
#endif
#ifdef __RF15_CN
#define GPIO_PF15 (0x5F)
#define PF15 GPIO_PF15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF15!
#endif

#ifdef __RG0_CN
#define GPIO_PG0 (0x60)
#define PG0 GPIO_PG0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG0!
#endif
#ifdef __RG1_CN
#define GPIO_PG1 (0x61)
#define PG1 GPIO_PG1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG1!
#endif
#ifdef __RG2_CN
#define GPIO_PG2 (0x62)
#define PG2 GPIO_PG2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG2!
#endif
#ifdef __RG3_CN
#define GPIO_PG3 (0x63)
#define PG3 GPIO_PG3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG3!
#endif
#ifdef __RG4_CN
#define GPIO_PG4 (0x64)
#define PG4 GPIO_PG4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG4!
#endif
#ifdef __RG5_CN
#define GPIO_PG5 (0x65)
#define PG5 GPIO_PG5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG5!
#endif
#ifdef __RG6_CN
#define GPIO_PG6 (0x66)
#define PG6 GPIO_PG6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG6!
#endif
#ifdef __RG7_CN
#define GPIO_PG7 (0x67)
#define PG7 GPIO_PG7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG7!
#endif
#ifdef __RG8_CN
#define GPIO_PG8 (0x68)
#define PG8 GPIO_PG8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG8!
#endif
#ifdef __RG9_CN
#define GPIO_PG9 (0x69)
#define PG9 GPIO_PG9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG9!
#endif
#ifdef __RG10_CN
#define GPIO_PG10 (0x6A)
#define PG10 GPIO_PG10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG10!
#endif
#ifdef __RG11_CN
#define GPIO_PG11 (0x6B)
#define PG11 GPIO_PG11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG11!
#endif
#ifdef __RG12_CN
#define GPIO_PG12 (0x6C)
#define PG12 GPIO_PG12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG12!
#endif
#ifdef __RG13_CN
#define GPIO_PG13 (0x6D)
#define PG13 GPIO_PG13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG13!
#endif
#ifdef __RG14_CN
#define GPIO_PG14 (0x6E)
#define PG14 GPIO_PG14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG14!
#endif
#ifdef __RG15_CN
#define GPIO_PG15 (0x6F)
#define PG15 GPIO_PG15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG15!
#endif

#ifdef __RH0_CN
#define GPIO_PH0 (0x70)
#define PH0 GPIO_PH0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH0!
#endif
#ifdef __RH1_CN
#define GPIO_PH1 (0x71)
#define PH1 GPIO_PH1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH1!
#endif
#ifdef __RH2_CN
#define GPIO_PH2 (0x72)
#define PH2 GPIO_PH2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH2!
#endif
#ifdef __RH3_CN
#define GPIO_PH3 (0x73)
#define PH3 GPIO_PH3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH3!
#endif
#ifdef __RH4_CN
#define GPIO_PH4 (0x74)
#define PH4 GPIO_PH4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH4!
#endif
#ifdef __RH5_CN
#define GPIO_PH5 (0x75)
#define PH5 GPIO_PH5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH5!
#endif
#ifdef __RH6_CN
#define GPIO_PH6 (0x76)
#define PH6 GPIO_PH6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH6!
#endif
#ifdef __RH7_CN
#define GPIO_PH7 (0x77)
#define PH7 GPIO_PH7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH7!
#endif
#ifdef __RH8_CN
#define GPIO_PH8 (0x78)
#define PH8 GPIO_PH8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH8!
#endif
#ifdef __RH9_CN
#define GPIO_PH9 (0x79)
#define PH9 GPIO_PH9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH9!
#endif
#ifdef __RH10_CN
#define GPIO_PH10 (0x7A)
#define PH10 GPIO_PH10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH10!
#endif
#ifdef __RH11_CN
#define GPIO_PH11 (0x7B)
#define PH11 GPIO_PH11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH11!
#endif
#ifdef __RH12_CN
#define GPIO_PH12 (0x7C)
#define PH12 GPIO_PH12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH12!
#endif
#ifdef __RH13_CN
#define GPIO_PH13 (0x7D)
#define PH13 GPIO_PH13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH13!
#endif
#ifdef __RH14_CN
#define GPIO_PH14 (0x7E)
#define PH14 GPIO_PH14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH14!
#endif
#ifdef __RH15_CN
#define GPIO_PH15 (0x7F)
#define PH15 GPIO_PH15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH15!
#endif

#ifdef __RJ0_CN
#define GPIO_PJ0 (0x80)
#define PJ0 GPIO_PJ0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ0!
#endif
#ifdef __RJ1_CN
#define GPIO_PJ1 (0x81)
#define PJ1 GPIO_PJ1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ1!
#endif
#ifdef __RJ2_CN
#define GPIO_PJ2 (0x82)
#define PJ2 GPIO_PJ2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ2!
#endif
#ifdef __RJ3_CN
#define GPIO_PJ3 (0x83)
#define PJ3 GPIO_PJ3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ3!
#endif
#ifdef __RJ4_CN
#define GPIO_PJ4 (0x84)
#define PJ4 GPIO_PJ4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ4!
#endif
#ifdef __RJ5_CN
#define GPIO_PJ5 (0x85)
#define PJ5 GPIO_PJ5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ5!
#endif
#ifdef __RJ6_CN
#define GPIO_PJ6 (0x86)
#define PJ6 GPIO_PJ6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ6!
#endif
#ifdef __RJ7_CN
#define GPIO_PJ7 (0x87)
#define PJ7 GPIO_PJ7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ7!
#endif
#ifdef __RJ8_CN
#define GPIO_PJ8 (0x88)
#define PJ8 GPIO_PJ8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ8!
#endif
#ifdef __RJ9_CN
#define GPIO_PJ9 (0x89)
#define PJ9 GPIO_PJ9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ9!
#endif
#ifdef __RJ10_CN
#define GPIO_PJ10 (0x8A)
#define PJ10 GPIO_PJ10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ10!
#endif
#ifdef __RJ11_CN
#define GPIO_PJ11 (0x8B)
#define PJ11 GPIO_PJ11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ11!
#endif
#ifdef __RJ12_CN
#define GPIO_PJ12 (0x8C)
#define PJ12 GPIO_PJ12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ12!
#endif
#ifdef __RJ13_CN
#define GPIO_PJ13 (0x8D)
#define PJ13 GPIO_PJ13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ13!
#endif
#ifdef __RJ14_CN
#define GPIO_PJ14 (0x8E)
#define PJ14 GPIO_PJ14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ14!
#endif
#ifdef __RJ15_CN
#define GPIO_PJ15 (0x8F)
#define PJ15 GPIO_PJ15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PJ15!
#endif

#ifdef __RK0_CN
#define GPIO_PK0 (0x90)
#define PK0 GPIO_PK0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK0!
#endif
#ifdef __RK1_CN
#define GPIO_PK1 (0x91)
#define PK1 GPIO_PK1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK1!
#endif
#ifdef __RK2_CN
#define GPIO_PK2 (0x92)
#define PK2 GPIO_PK2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK2!
#endif
#ifdef __RK3_CN
#define GPIO_PK3 (0x93)
#define PK3 GPIO_PK3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK3!
#endif
#ifdef __RK4_CN
#define GPIO_PK4 (0x94)
#define PK4 GPIO_PK4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK4!
#endif
#ifdef __RK5_CN
#define GPIO_PK5 (0x95)
#define PK5 GPIO_PK5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK5!
#endif
#ifdef __RK6_CN
#define GPIO_PK6 (0x96)
#define PK6 GPIO_PK6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK6!
#endif
#ifdef __RK7_CN
#define GPIO_PK7 (0x97)
#define PK7 GPIO_PK7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK7!
#endif
#ifdef __RK8_CN
#define GPIO_PK8 (0x98)
#define PK8 GPIO_PK8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK8!
#endif
#ifdef __RK9_CN
#define GPIO_PK9 (0x99)
#define PK9 GPIO_PK9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK9!
#endif
#ifdef __RK10_CN
#define GPIO_PK10 (0x9A)
#define PK10 GPIO_PK10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK10!
#endif
#ifdef __RK11_CN
#define GPIO_PK11 (0x9B)
#define PK11 GPIO_PK11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK11!
#endif
#ifdef __RK12_CN
#define GPIO_PK12 (0x9C)
#define PK12 GPIO_PK12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK12!
#endif
#ifdef __RK13_CN
#define GPIO_PK13 (0x9D)
#define PK13 GPIO_PK13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK13!
#endif
#ifdef __RK14_CN
#define GPIO_PK14 (0x9E)
#define PK14 GPIO_PK14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK14!
#endif
#ifdef __RK15_CN
#define GPIO_PK15 (0x9F)
#define PK15 GPIO_PK15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK15!
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
#define GPIO_PIN_8 (0x08)
#define PIN_8 GPIO_PIN_8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_8!
#define GPIO_PIN_9 (0x09)
#define PIN_9 GPIO_PIN_9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_9!
#define GPIO_PIN_10 (0x0A)
#define PIN_10 GPIO_PIN_10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_10!
#define GPIO_PIN_11 (0x0B)
#define PIN_11 GPIO_PIN_11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_11!
#define GPIO_PIN_12 (0x0C)
#define PIN_12 GPIO_PIN_12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_12!
#define GPIO_PIN_13 (0x0D)
#define PIN_13 GPIO_PIN_13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_13!
#define GPIO_PIN_14 (0x0E)
#define PIN_14 GPIO_PIN_14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_14!
#define GPIO_PIN_15 (0x0F)
#define PIN_15 GPIO_PIN_15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_15!

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

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
