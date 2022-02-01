/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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

#define GPIO_FEATURE_32BIT_PORT

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
#ifdef __PA8_CN
#define PA8  (0x08)
#endif
#ifdef __PA9_CN
#define PA9  (0x09)
#endif
#ifdef __PA10_CN
#define PA10 (0x0A)
#endif
#ifdef __PA11_CN
#define PA11 (0x0B)
#endif
#ifdef __PA12_CN
#define PA12 (0x0C)
#endif
#ifdef __PA13_CN
#define PA13 (0x0D)
#endif
#ifdef __PA14_CN
#define PA14 (0x0E)
#endif
#ifdef __PA15_CN
#define PA15 (0x0F)
#endif
#ifdef __PA16_CN
#define PA16 (0x10)
#endif
#ifdef __PA17_CN
#define PA17 (0x11)
#endif
#ifdef __PA18_CN
#define PA18 (0x12)
#endif
#ifdef __PA19_CN
#define PA19 (0x13)
#endif
#ifdef __PA20_CN
#define PA20 (0x14)
#endif
#ifdef __PA21_CN
#define PA21 (0x15)
#endif
#ifdef __PA22_CN
#define PA22 (0x16)
#endif
#ifdef __PA23_CN
#define PA23 (0x17)
#endif
#ifdef __PA24_CN
#define PA24 (0x18)
#endif
#ifdef __PA25_CN
#define PA25 (0x19)
#endif
#ifdef __PA26_CN
#define PA26 (0x1A)
#endif
#ifdef __PA27_CN
#define PA27 (0x1B)
#endif
#ifdef __PA28_CN
#define PA28 (0x1C)
#endif
#ifdef __PA29_CN
#define PA29 (0x1D)
#endif
#ifdef __PA30_CN
#define PA30 (0x1E)
#endif
#ifdef __PA31_CN
#define PA31 (0x1F)
#endif

#ifdef __PB0_CN
#define PB0  (0x20)
#endif
#ifdef __PB1_CN
#define PB1  (0x21)
#endif
#ifdef __PB2_CN
#define PB2  (0x22)
#endif
#ifdef __PB3_CN
#define PB3  (0x23)
#endif
#ifdef __PB4_CN
#define PB4  (0x24)
#endif
#ifdef __PB5_CN
#define PB5  (0x25)
#endif
#ifdef __PB6_CN
#define PB6  (0x26)
#endif
#ifdef __PB7_CN
#define PB7  (0x27)
#endif
#ifdef __PB8_CN
#define PB8  (0x28)
#endif
#ifdef __PB9_CN
#define PB9  (0x29)
#endif
#ifdef __PB10_CN
#define PB10 (0x2A)
#endif
#ifdef __PB11_CN
#define PB11 (0x2B)
#endif
#ifdef __PB12_CN
#define PB12 (0x2C)
#endif
#ifdef __PB13_CN
#define PB13 (0x2D)
#endif
#ifdef __PB14_CN
#define PB14 (0x2E)
#endif
#ifdef __PB15_CN
#define PB15 (0x2F)
#endif
#ifdef __PB16_CN
#define PB16 (0x30)
#endif
#ifdef __PB17_CN
#define PB17 (0x31)
#endif
#ifdef __PB18_CN
#define PB18 (0x32)
#endif
#ifdef __PB19_CN
#define PB19 (0x33)
#endif
#ifdef __PB20_CN
#define PB20 (0x34)
#endif
#ifdef __PB21_CN
#define PB21 (0x35)
#endif
#ifdef __PB22_CN
#define PB22 (0x36)
#endif
#ifdef __PB23_CN
#define PB23 (0x37)
#endif
#ifdef __PB24_CN
#define PB24 (0x38)
#endif
#ifdef __PB25_CN
#define PB25 (0x39)
#endif
#ifdef __PB26_CN
#define PB26 (0x3A)
#endif
#ifdef __PB27_CN
#define PB27 (0x3B)
#endif
#ifdef __PB28_CN
#define PB28 (0x3C)
#endif
#ifdef __PB29_CN
#define PB29 (0x3D)
#endif
#ifdef __PB30_CN
#define PB30 (0x3E)
#endif
#ifdef __PB31_CN
#define PB31 (0x3F)
#endif

#ifdef __PC0_CN
#define PC0  (0x40)
#endif
#ifdef __PC1_CN
#define PC1  (0x41)
#endif
#ifdef __PC2_CN
#define PC2  (0x42)
#endif
#ifdef __PC3_CN
#define PC3  (0x43)
#endif
#ifdef __PC4_CN
#define PC4  (0x44)
#endif
#ifdef __PC5_CN
#define PC5  (0x45)
#endif
#ifdef __PC6_CN
#define PC6  (0x46)
#endif
#ifdef __PC7_CN
#define PC7  (0x47)
#endif
#ifdef __PC8_CN
#define PC8  (0x48)
#endif
#ifdef __PC9_CN
#define PC9  (0x49)
#endif
#ifdef __PC10_CN
#define PC10 (0x4A)
#endif
#ifdef __PC11_CN
#define PC11 (0x4B)
#endif
#ifdef __PC12_CN
#define PC12 (0x4C)
#endif
#ifdef __PC13_CN
#define PC13 (0x4D)
#endif
#ifdef __PC14_CN
#define PC14 (0x4E)
#endif
#ifdef __PC15_CN
#define PC15 (0x4F)
#endif
#ifdef __PC16_CN
#define PC16 (0x50)
#endif
#ifdef __PC17_CN
#define PC17 (0x51)
#endif
#ifdef __PC18_CN
#define PC18 (0x52)
#endif
#ifdef __PC19_CN
#define PC19 (0x53)
#endif
#ifdef __PC20_CN
#define PC20 (0x54)
#endif
#ifdef __PC21_CN
#define PC21 (0x55)
#endif
#ifdef __PC22_CN
#define PC22 (0x56)
#endif
#ifdef __PC23_CN
#define PC23 (0x57)
#endif
#ifdef __PC24_CN
#define PC24 (0x58)
#endif
#ifdef __PC25_CN
#define PC25 (0x59)
#endif
#ifdef __PC26_CN
#define PC26 (0x5A)
#endif
#ifdef __PC27_CN
#define PC27 (0x5B)
#endif
#ifdef __PC28_CN
#define PC28 (0x5C)
#endif
#ifdef __PC29_CN
#define PC29 (0x5D)
#endif
#ifdef __PC30_CN
#define PC30 (0x5E)
#endif
#ifdef __PC31_CN
#define PC31 (0x5F)
#endif

#ifdef __PD0_CN
#define PD0  (0x60)
#endif
#ifdef __PD1_CN
#define PD1  (0x61)
#endif
#ifdef __PD2_CN
#define PD2  (0x62)
#endif
#ifdef __PD3_CN
#define PD3  (0x63)
#endif
#ifdef __PD4_CN
#define PD4  (0x64)
#endif
#ifdef __PD5_CN
#define PD5  (0x65)
#endif
#ifdef __PD6_CN
#define PD6  (0x66)
#endif
#ifdef __PD7_CN
#define PD7  (0x67)
#endif
#ifdef __PD8_CN
#define PD8  (0x68)
#endif
#ifdef __PD9_CN
#define PD9  (0x69)
#endif
#ifdef __PD10_CN
#define PD10 (0x6A)
#endif
#ifdef __PD11_CN
#define PD11 (0x6B)
#endif
#ifdef __PD12_CN
#define PD12 (0x6C)
#endif
#ifdef __PD13_CN
#define PD13 (0x6D)
#endif
#ifdef __PD14_CN
#define PD14 (0x6E)
#endif
#ifdef __PD15_CN
#define PD15 (0x6F)
#endif
#ifdef __PD16_CN
#define PD16 (0x70)
#endif
#ifdef __PD17_CN
#define PD17 (0x71)
#endif
#ifdef __PD18_CN
#define PD18 (0x72)
#endif
#ifdef __PD19_CN
#define PD19 (0x73)
#endif
#ifdef __PD20_CN
#define PD20 (0x74)
#endif
#ifdef __PD21_CN
#define PD21 (0x75)
#endif
#ifdef __PD22_CN
#define PD22 (0x76)
#endif
#ifdef __PD23_CN
#define PD23 (0x77)
#endif
#ifdef __PD24_CN
#define PD24 (0x78)
#endif
#ifdef __PD25_CN
#define PD25 (0x79)
#endif
#ifdef __PD26_CN
#define PD26 (0x7A)
#endif
#ifdef __PD27_CN
#define PD27 (0x7B)
#endif
#ifdef __PD28_CN
#define PD28 (0x7C)
#endif
#ifdef __PD29_CN
#define PD29 (0x7D)
#endif
#ifdef __PD30_CN
#define PD30 (0x7E)
#endif
#ifdef __PD31_CN
#define PD31 (0x7F)
#endif

#ifdef __PE0_CN
#define PE0  (0x80)
#endif
#ifdef __PE1_CN
#define PE1  (0x81)
#endif
#ifdef __PE2_CN
#define PE2  (0x82)
#endif
#ifdef __PE3_CN
#define PE3  (0x83)
#endif
#ifdef __PE4_CN
#define PE4  (0x84)
#endif
#ifdef __PE5_CN
#define PE5  (0x85)
#endif
#ifdef __PE6_CN
#define PE6  (0x86)
#endif
#ifdef __PE7_CN
#define PE7  (0x87)
#endif
#ifdef __PE8_CN
#define PE8  (0x88)
#endif
#ifdef __PE9_CN
#define PE9  (0x89)
#endif
#ifdef __PE10_CN
#define PE10 (0x8A)
#endif
#ifdef __PE11_CN
#define PE11 (0x8B)
#endif
#ifdef __PE12_CN
#define PE12 (0x8C)
#endif
#ifdef __PE13_CN
#define PE13 (0x8D)
#endif
#ifdef __PE14_CN
#define PE14 (0x8E)
#endif
#ifdef __PE15_CN
#define PE15 (0x8F)
#endif
#ifdef __PE16_CN
#define PE16 (0x90)
#endif
#ifdef __PE17_CN
#define PE17 (0x91)
#endif
#ifdef __PE18_CN
#define PE18 (0x92)
#endif
#ifdef __PE19_CN
#define PE19 (0x93)
#endif
#ifdef __PE20_CN
#define PE20 (0x94)
#endif
#ifdef __PE21_CN
#define PE21 (0x95)
#endif
#ifdef __PE22_CN
#define PE22 (0x96)
#endif
#ifdef __PE23_CN
#define PE23 (0x97)
#endif
#ifdef __PE24_CN
#define PE24 (0x98)
#endif
#ifdef __PE25_CN
#define PE25 (0x99)
#endif
#ifdef __PE26_CN
#define PE26 (0x9A)
#endif
#ifdef __PE27_CN
#define PE27 (0x9B)
#endif
#ifdef __PE28_CN
#define PE28 (0x9C)
#endif
#ifdef __PE29_CN
#define PE29 (0x9D)
#endif
#ifdef __PE30_CN
#define PE30 (0x9E)
#endif
#ifdef __PE31_CN
#define PE31 (0x9F)
#endif

#define PIN_0  (0x00)
#define PIN_1  (0x01)
#define PIN_2  (0x02)
#define PIN_3  (0x03)
#define PIN_4  (0x04)
#define PIN_5  (0x05)
#define PIN_6  (0x06)
#define PIN_7  (0x07)
#define PIN_8  (0x08)
#define PIN_9  (0x09)
#define PIN_10 (0x0A)
#define PIN_11 (0x0B)
#define PIN_12 (0x0C)
#define PIN_13 (0x0D)
#define PIN_14 (0x0E)
#define PIN_15 (0x0F)
#define PIN_16 (0x10)
#define PIN_17 (0x11)
#define PIN_18 (0x12)
#define PIN_19 (0x13)
#define PIN_20 (0x14)
#define PIN_21 (0x15)
#define PIN_22 (0x16)
#define PIN_23 (0x17)
#define PIN_24 (0x18)
#define PIN_25 (0x19)
#define PIN_26 (0x1A)
#define PIN_27 (0x1B)
#define PIN_28 (0x1C)
#define PIN_29 (0x1D)
#define PIN_30 (0x1E)
#define PIN_31 (0x1F)

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

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
