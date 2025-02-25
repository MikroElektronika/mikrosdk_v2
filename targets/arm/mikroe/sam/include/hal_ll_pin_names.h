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
#ifdef __PA5_CN
#define GPIO_PA5 (0x05)
#define PA5 GPIO_PA5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA5!
#endif
#ifdef __PA6_CN
#define GPIO_PA6 (0x06)
#define PA6 GPIO_PA6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA6!
#endif
#ifdef __PA7_CN
#define GPIO_PA7 (0x07)
#define PA7 GPIO_PA7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA7!
#endif
#ifdef __PA8_CN
#define GPIO_PA8 (0x08)
#define PA8 GPIO_PA8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA8!
#endif
#ifdef __PA9_CN
#define GPIO_PA9 (0x09)
#define PA9 GPIO_PA9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA9!
#endif
#ifdef __PA10_CN
#define GPIO_PA10 (0x0A)
#define PA10 GPIO_PA10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA10!
#endif
#ifdef __PA11_CN
#define GPIO_PA11 (0x0B)
#define PA11 GPIO_PA11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA11!
#endif
#ifdef __PA12_CN
#define GPIO_PA12 (0x0C)
#define PA12 GPIO_PA12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA12!
#endif
#ifdef __PA13_CN
#define GPIO_PA13 (0x0D)
#define PA13 GPIO_PA13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA13!
#endif
#ifdef __PA14_CN
#define GPIO_PA14 (0x0E)
#define PA14 GPIO_PA14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA14!
#endif
#ifdef __PA15_CN
#define GPIO_PA15 (0x0F)
#define PA15 GPIO_PA15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA15!
#endif
#ifdef __PA16_CN
#define GPIO_PA16 (0x10)
#define PA16 GPIO_PA16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA16!
#endif
#ifdef __PA17_CN
#define GPIO_PA17 (0x11)
#define PA17 GPIO_PA17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA17!
#endif
#ifdef __PA18_CN
#define GPIO_PA18 (0x12)
#define PA18 GPIO_PA18 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA18!
#endif
#ifdef __PA19_CN
#define GPIO_PA19 (0x13)
#define PA19 GPIO_PA19 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA19!
#endif
#ifdef __PA20_CN
#define GPIO_PA20 (0x14)
#define PA20 GPIO_PA20 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA20!
#endif
#ifdef __PA21_CN
#define GPIO_PA21 (0x15)
#define PA21 GPIO_PA21 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA21!
#endif
#ifdef __PA22_CN
#define GPIO_PA22 (0x16)
#define PA22 GPIO_PA22 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA22!
#endif
#ifdef __PA23_CN
#define GPIO_PA23 (0x17)
#define PA23 GPIO_PA23 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA23!
#endif
#ifdef __PA24_CN
#define GPIO_PA24 (0x18)
#define PA24 GPIO_PA24 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA24!
#endif
#ifdef __PA25_CN
#define GPIO_PA25 (0x19)
#define PA25 GPIO_PA25 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA25!
#endif
#ifdef __PA26_CN
#define GPIO_PA26 (0x1A)
#define PA26 GPIO_PA26 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA26!
#endif
#ifdef __PA27_CN
#define GPIO_PA27 (0x1B)
#define PA27 GPIO_PA27 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA27!
#endif
#ifdef __PA28_CN
#define GPIO_PA28 (0x1C)
#define PA28 GPIO_PA28 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA28!
#endif
#ifdef __PA29_CN
#define GPIO_PA29 (0x1D)
#define PA29 GPIO_PA29 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA29!
#endif
#ifdef __PA30_CN
#define GPIO_PA30 (0x1E)
#define PA30 GPIO_PA30 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA30!
#endif
#ifdef __PA31_CN
#define GPIO_PA31 (0x1F)
#define PA31 GPIO_PA31 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA31!
#endif

#ifdef __PB0_CN
#define GPIO_PB0 (0x20)
#define PB0 GPIO_PB0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB0!
#endif
#ifdef __PB1_CN
#define GPIO_PB1 (0x21)
#define PB1 GPIO_PB1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB1!
#endif
#ifdef __PB2_CN
#define GPIO_PB2 (0x22)
#define PB2 GPIO_PB2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB2!
#endif
#ifdef __PB3_CN
#define GPIO_PB3 (0x23)
#define PB3 GPIO_PB3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB3!
#endif
#ifdef __PB4_CN
#define GPIO_PB4 (0x24)
#define PB4 GPIO_PB4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB4!
#endif
#ifdef __PB5_CN
#define GPIO_PB5 (0x25)
#define PB5 GPIO_PB5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB5!
#endif
#ifdef __PB6_CN
#define GPIO_PB6 (0x26)
#define PB6 GPIO_PB6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB6!
#endif
#ifdef __PB7_CN
#define GPIO_PB7 (0x27)
#define PB7 GPIO_PB7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB7!
#endif
#ifdef __PB8_CN
#define GPIO_PB8 (0x28)
#define PB8 GPIO_PB8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB8!
#endif
#ifdef __PB9_CN
#define GPIO_PB9 (0x29)
#define PB9 GPIO_PB9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB9!
#endif
#ifdef __PB10_CN
#define GPIO_PB10 (0x2A)
#define PB10 GPIO_PB10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB10!
#endif
#ifdef __PB11_CN
#define GPIO_PB11 (0x2B)
#define PB11 GPIO_PB11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB11!
#endif
#ifdef __PB12_CN
#define GPIO_PB12 (0x2C)
#define PB12 GPIO_PB12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB12!
#endif
#ifdef __PB13_CN
#define GPIO_PB13 (0x2D)
#define PB13 GPIO_PB13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB13!
#endif
#ifdef __PB14_CN
#define GPIO_PB14 (0x2E)
#define PB14 GPIO_PB14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB14!
#endif
#ifdef __PB15_CN
#define GPIO_PB15 (0x2F)
#define PB15 GPIO_PB15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB15!
#endif
#ifdef __PB16_CN
#define GPIO_PB16 (0x30)
#define PB16 GPIO_PB16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB16!
#endif
#ifdef __PB17_CN
#define GPIO_PB17 (0x31)
#define PB17 GPIO_PB17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB17!
#endif
#ifdef __PB18_CN
#define GPIO_PB18 (0x32)
#define PB18 GPIO_PB18 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB18!
#endif
#ifdef __PB19_CN
#define GPIO_PB19 (0x33)
#define PB19 GPIO_PB19 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB19!
#endif
#ifdef __PB20_CN
#define GPIO_PB20 (0x34)
#define PB20 GPIO_PB20 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB20!
#endif
#ifdef __PB21_CN
#define GPIO_PB21 (0x35)
#define PB21 GPIO_PB21 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB21!
#endif
#ifdef __PB22_CN
#define GPIO_PB22 (0x36)
#define PB22 GPIO_PB22 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB22!
#endif
#ifdef __PB23_CN
#define GPIO_PB23 (0x37)
#define PB23 GPIO_PB23 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB23!
#endif
#ifdef __PB24_CN
#define GPIO_PB24 (0x38)
#define PB24 GPIO_PB24 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB24!
#endif
#ifdef __PB25_CN
#define GPIO_PB25 (0x39)
#define PB25 GPIO_PB25 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB25!
#endif
#ifdef __PB26_CN
#define GPIO_PB26 (0x3A)
#define PB26 GPIO_PB26 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB26!
#endif
#ifdef __PB27_CN
#define GPIO_PB27 (0x3B)
#define PB27 GPIO_PB27 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB27!
#endif
#ifdef __PB28_CN
#define GPIO_PB28 (0x3C)
#define PB28 GPIO_PB28 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB28!
#endif
#ifdef __PB29_CN
#define GPIO_PB29 (0x3D)
#define PB29 GPIO_PB29 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB29!
#endif
#ifdef __PB30_CN
#define GPIO_PB30 (0x3E)
#define PB30 GPIO_PB30 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB30!
#endif
#ifdef __PB31_CN
#define GPIO_PB31 (0x3F)
#define PB31 GPIO_PB31 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB31!
#endif

#ifdef __PC0_CN
#define GPIO_PC0 (0x40)
#define PC0 GPIO_PC0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC0!
#endif
#ifdef __PC1_CN
#define GPIO_PC1 (0x41)
#define PC1 GPIO_PC1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC1!
#endif
#ifdef __PC2_CN
#define GPIO_PC2 (0x42)
#define PC2 GPIO_PC2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC2!
#endif
#ifdef __PC3_CN
#define GPIO_PC3 (0x43)
#define PC3 GPIO_PC3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC3!
#endif
#ifdef __PC4_CN
#define GPIO_PC4 (0x44)
#define PC4 GPIO_PC4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC4!
#endif
#ifdef __PC5_CN
#define GPIO_PC5 (0x45)
#define PC5 GPIO_PC5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC5!
#endif
#ifdef __PC6_CN
#define GPIO_PC6 (0x46)
#define PC6 GPIO_PC6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC6!
#endif
#ifdef __PC7_CN
#define GPIO_PC7 (0x47)
#define PC7 GPIO_PC7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC7!
#endif
#ifdef __PC8_CN
#define GPIO_PC8 (0x48)
#define PC8 GPIO_PC8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC8!
#endif
#ifdef __PC9_CN
#define GPIO_PC9 (0x49)
#define PC9 GPIO_PC9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC9!
#endif
#ifdef __PC10_CN
#define GPIO_PC10 (0x4A)
#define PC10 GPIO_PC10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC10!
#endif
#ifdef __PC11_CN
#define GPIO_PC11 (0x4B)
#define PC11 GPIO_PC11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC11!
#endif
#ifdef __PC12_CN
#define GPIO_PC12 (0x4C)
#define PC12 GPIO_PC12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC12!
#endif
#ifdef __PC13_CN
#define GPIO_PC13 (0x4D)
#define PC13 GPIO_PC13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC13!
#endif
#ifdef __PC14_CN
#define GPIO_PC14 (0x4E)
#define PC14 GPIO_PC14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC14!
#endif
#ifdef __PC15_CN
#define GPIO_PC15 (0x4F)
#define PC15 GPIO_PC15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC15!
#endif
#ifdef __PC16_CN
#define GPIO_PC16 (0x50)
#define PC16 GPIO_PC16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC16!
#endif
#ifdef __PC17_CN
#define GPIO_PC17 (0x51)
#define PC17 GPIO_PC17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC17!
#endif
#ifdef __PC18_CN
#define GPIO_PC18 (0x52)
#define PC18 GPIO_PC18 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC18!
#endif
#ifdef __PC19_CN
#define GPIO_PC19 (0x53)
#define PC19 GPIO_PC19 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC19!
#endif
#ifdef __PC20_CN
#define GPIO_PC20 (0x54)
#define PC20 GPIO_PC20 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC20!
#endif
#ifdef __PC21_CN
#define GPIO_PC21 (0x55)
#define PC21 GPIO_PC21 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC21!
#endif
#ifdef __PC22_CN
#define GPIO_PC22 (0x56)
#define PC22 GPIO_PC22 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC22!
#endif
#ifdef __PC23_CN
#define GPIO_PC23 (0x57)
#define PC23 GPIO_PC23 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC23!
#endif
#ifdef __PC24_CN
#define GPIO_PC24 (0x58)
#define PC24 GPIO_PC24 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC24!
#endif
#ifdef __PC25_CN
#define GPIO_PC25 (0x59)
#define PC25 GPIO_PC25 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC25!
#endif
#ifdef __PC26_CN
#define GPIO_PC26 (0x5A)
#define PC26 GPIO_PC26 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC26!
#endif
#ifdef __PC27_CN
#define GPIO_PC27 (0x5B)
#define PC27 GPIO_PC27 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC27!
#endif
#ifdef __PC28_CN
#define GPIO_PC28 (0x5C)
#define PC28 GPIO_PC28 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC28!
#endif
#ifdef __PC29_CN
#define GPIO_PC29 (0x5D)
#define PC29 GPIO_PC29 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC29!
#endif
#ifdef __PC30_CN
#define GPIO_PC30 (0x5E)
#define PC30 GPIO_PC30 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC30!
#endif
#ifdef __PC31_CN
#define GPIO_PC31 (0x5F)
#define PC31 GPIO_PC31 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC31!
#endif

#ifdef __PD0_CN
#define GPIO_PD0 (0x60)
#define PD0 GPIO_PD0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD0!
#endif
#ifdef __PD1_CN
#define GPIO_PD1 (0x61)
#define PD1 GPIO_PD1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD1!
#endif
#ifdef __PD2_CN
#define GPIO_PD2 (0x62)
#define PD2 GPIO_PD2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD2!
#endif
#ifdef __PD3_CN
#define GPIO_PD3 (0x63)
#define PD3 GPIO_PD3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD3!
#endif
#ifdef __PD4_CN
#define GPIO_PD4 (0x64)
#define PD4 GPIO_PD4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD4!
#endif
#ifdef __PD5_CN
#define GPIO_PD5 (0x65)
#define PD5 GPIO_PD5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD5!
#endif
#ifdef __PD6_CN
#define GPIO_PD6 (0x66)
#define PD6 GPIO_PD6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD6!
#endif
#ifdef __PD7_CN
#define GPIO_PD7 (0x67)
#define PD7 GPIO_PD7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD7!
#endif
#ifdef __PD8_CN
#define GPIO_PD8 (0x68)
#define PD8 GPIO_PD8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD8!
#endif
#ifdef __PD9_CN
#define GPIO_PD9 (0x69)
#define PD9 GPIO_PD9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD9!
#endif
#ifdef __PD10_CN
#define GPIO_PD10 (0x6A)
#define PD10 GPIO_PD10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD10!
#endif
#ifdef __PD11_CN
#define GPIO_PD11 (0x6B)
#define PD11 GPIO_PD11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD11!
#endif
#ifdef __PD12_CN
#define GPIO_PD12 (0x6C)
#define PD12 GPIO_PD12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD12!
#endif
#ifdef __PD13_CN
#define GPIO_PD13 (0x6D)
#define PD13 GPIO_PD13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD13!
#endif
#ifdef __PD14_CN
#define GPIO_PD14 (0x6E)
#define PD14 GPIO_PD14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD14!
#endif
#ifdef __PD15_CN
#define GPIO_PD15 (0x6F)
#define PD15 GPIO_PD15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD15!
#endif
#ifdef __PD16_CN
#define GPIO_PD16 (0x70)
#define PD16 GPIO_PD16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD16!
#endif
#ifdef __PD17_CN
#define GPIO_PD17 (0x71)
#define PD17 GPIO_PD17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD17!
#endif
#ifdef __PD18_CN
#define GPIO_PD18 (0x72)
#define PD18 GPIO_PD18 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD18!
#endif
#ifdef __PD19_CN
#define GPIO_PD19 (0x73)
#define PD19 GPIO_PD19 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD19!
#endif
#ifdef __PD20_CN
#define GPIO_PD20 (0x74)
#define PD20 GPIO_PD20 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD20!
#endif
#ifdef __PD21_CN
#define GPIO_PD21 (0x75)
#define PD21 GPIO_PD21 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD21!
#endif
#ifdef __PD22_CN
#define GPIO_PD22 (0x76)
#define PD22 GPIO_PD22 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD22!
#endif
#ifdef __PD23_CN
#define GPIO_PD23 (0x77)
#define PD23 GPIO_PD23 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD23!
#endif
#ifdef __PD24_CN
#define GPIO_PD24 (0x78)
#define PD24 GPIO_PD24 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD24!
#endif
#ifdef __PD25_CN
#define GPIO_PD25 (0x79)
#define PD25 GPIO_PD25 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD25!
#endif
#ifdef __PD26_CN
#define GPIO_PD26 (0x7A)
#define PD26 GPIO_PD26 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD26!
#endif
#ifdef __PD27_CN
#define GPIO_PD27 (0x7B)
#define PD27 GPIO_PD27 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD27!
#endif
#ifdef __PD28_CN
#define GPIO_PD28 (0x7C)
#define PD28 GPIO_PD28 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD28!
#endif
#ifdef __PD29_CN
#define GPIO_PD29 (0x7D)
#define PD29 GPIO_PD29 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD29!
#endif
#ifdef __PD30_CN
#define GPIO_PD30 (0x7E)
#define PD30 GPIO_PD30 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD30!
#endif
#ifdef __PD31_CN
#define GPIO_PD31 (0x7F)
#define PD31 GPIO_PD31 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD31!
#endif

#ifdef __PE0_CN
#define GPIO_PE0 (0x80)
#define PE0 GPIO_PE0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE0!
#endif
#ifdef __PE1_CN
#define GPIO_PE1 (0x81)
#define PE1 GPIO_PE1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE1!
#endif
#ifdef __PE2_CN
#define GPIO_PE2 (0x82)
#define PE2 GPIO_PE2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE2!
#endif
#ifdef __PE3_CN
#define GPIO_PE3 (0x83)
#define PE3 GPIO_PE3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE3!
#endif
#ifdef __PE4_CN
#define GPIO_PE4 (0x84)
#define PE4 GPIO_PE4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE4!
#endif
#ifdef __PE5_CN
#define GPIO_PE5 (0x85)
#define PE5 GPIO_PE5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE5!
#endif
#ifdef __PE6_CN
#define GPIO_PE6 (0x86)
#define PE6 GPIO_PE6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE6!
#endif
#ifdef __PE7_CN
#define GPIO_PE7 (0x87)
#define PE7 GPIO_PE7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE7!
#endif
#ifdef __PE8_CN
#define GPIO_PE8 (0x88)
#define PE8 GPIO_PE8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE8!
#endif
#ifdef __PE9_CN
#define GPIO_PE9 (0x89)
#define PE9 GPIO_PE9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE9!
#endif
#ifdef __PE10_CN
#define GPIO_PE10 (0x8A)
#define PE10 GPIO_PE10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE10!
#endif
#ifdef __PE11_CN
#define GPIO_PE11 (0x8B)
#define PE11 GPIO_PE11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE11!
#endif
#ifdef __PE12_CN
#define GPIO_PE12 (0x8C)
#define PE12 GPIO_PE12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE12!
#endif
#ifdef __PE13_CN
#define GPIO_PE13 (0x8D)
#define PE13 GPIO_PE13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE13!
#endif
#ifdef __PE14_CN
#define GPIO_PE14 (0x8E)
#define PE14 GPIO_PE14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE14!
#endif
#ifdef __PE15_CN
#define GPIO_PE15 (0x8F)
#define PE15 GPIO_PE15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE15!
#endif
#ifdef __PE16_CN
#define GPIO_PE16 (0x90)
#define PE16 GPIO_PE16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE16!
#endif
#ifdef __PE17_CN
#define GPIO_PE17 (0x91)
#define PE17 GPIO_PE17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE17!
#endif
#ifdef __PE18_CN
#define GPIO_PE18 (0x92)
#define PE18 GPIO_PE18 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE18!
#endif
#ifdef __PE19_CN
#define GPIO_PE19 (0x93)
#define PE19 GPIO_PE19 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE19!
#endif
#ifdef __PE20_CN
#define GPIO_PE20 (0x94)
#define PE20 GPIO_PE20 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE20!
#endif
#ifdef __PE21_CN
#define GPIO_PE21 (0x95)
#define PE21 GPIO_PE21 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE21!
#endif
#ifdef __PE22_CN
#define GPIO_PE22 (0x96)
#define PE22 GPIO_PE22 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE22!
#endif
#ifdef __PE23_CN
#define GPIO_PE23 (0x97)
#define PE23 GPIO_PE23 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE23!
#endif
#ifdef __PE24_CN
#define GPIO_PE24 (0x98)
#define PE24 GPIO_PE24 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE24!
#endif
#ifdef __PE25_CN
#define GPIO_PE25 (0x99)
#define PE25 GPIO_PE25 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE25!
#endif
#ifdef __PE26_CN
#define GPIO_PE26 (0x9A)
#define PE26 GPIO_PE26 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE26!
#endif
#ifdef __PE27_CN
#define GPIO_PE27 (0x9B)
#define PE27 GPIO_PE27 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE27!
#endif
#ifdef __PE28_CN
#define GPIO_PE28 (0x9C)
#define PE28 GPIO_PE28 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE28!
#endif
#ifdef __PE29_CN
#define GPIO_PE29 (0x9D)
#define PE29 GPIO_PE29 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE29!
#endif
#ifdef __PE30_CN
#define GPIO_PE30 (0x9E)
#define PE30 GPIO_PE30 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE30!
#endif
#ifdef __PE31_CN
#define GPIO_PE31 (0x9F)
#define PE31 GPIO_PE31 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE31!
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
#define GPIO_PIN_16 (0x10)
#define PIN_16 GPIO_PIN_16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_16!
#define GPIO_PIN_17 (0x11)
#define PIN_17 GPIO_PIN_17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_17!
#define GPIO_PIN_18 (0x12)
#define PIN_18 GPIO_PIN_18 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_18!
#define GPIO_PIN_19 (0x13)
#define PIN_19 GPIO_PIN_19 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_19!
#define GPIO_PIN_20 (0x14)
#define PIN_20 GPIO_PIN_20 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_20!
#define GPIO_PIN_21 (0x15)
#define PIN_21 GPIO_PIN_21 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_21!
#define GPIO_PIN_22 (0x16)
#define PIN_22 GPIO_PIN_22 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_22!
#define GPIO_PIN_23 (0x17)
#define PIN_23 GPIO_PIN_23 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_23!
#define GPIO_PIN_24 (0x18)
#define PIN_24 GPIO_PIN_24 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_24!
#define GPIO_PIN_25 (0x19)
#define PIN_25 GPIO_PIN_25 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_25!
#define GPIO_PIN_26 (0x1A)
#define PIN_26 GPIO_PIN_26 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_26!
#define GPIO_PIN_27 (0x1B)
#define PIN_27 GPIO_PIN_27 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_27!
#define GPIO_PIN_28 (0x1C)
#define PIN_28 GPIO_PIN_28 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_28!
#define GPIO_PIN_29 (0x1D)
#define PIN_29 GPIO_PIN_29 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_29!
#define GPIO_PIN_30 (0x1E)
#define PIN_30 GPIO_PIN_30 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_30!
#define GPIO_PIN_31 (0x1F)
#define PIN_31 GPIO_PIN_31 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_31!

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

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
