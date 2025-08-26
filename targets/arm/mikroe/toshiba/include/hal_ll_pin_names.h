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

// TODO - Define pin names here!

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
** General Public License version 3 as published by the
** Free Software Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
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
 * @brief Header file containing symbolic pin name definitions (Toshiba).
 */

#ifndef _HAL_LL_PIN_NAMES_H_
#define _HAL_LL_PIN_NAMES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "mcu_definitions.h"
// #include "hal_ll_target_names.h"

#define GPIO_FEATURE_16BIT_PORT

#ifdef __PORT_A_CN
#define GPIO_FEATURE_GROUP_1
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
#ifdef __PORT_N_CN
#define GPIO_FEATURE_GROUP_14
#endif
#ifdef __PORT_U_CN
#define GPIO_FEATURE_GROUP_21
#endif
#ifdef __PORT_V_CN
#define GPIO_FEATURE_GROUP_22
#endif

#ifdef __PA0_CN
#define GPIO_PA0 (0x00)
#define PA0 GPIO_PA0
#endif
#ifdef __PA1_CN
#define GPIO_PA1 (0x01)
#define PA1 GPIO_PA1
#endif
#ifdef __PA2_CN
#define GPIO_PA2 (0x02)
#define PA2 GPIO_PA2
#endif
#ifdef __PA3_CN
#define GPIO_PA3 (0x03)
#define PA3 GPIO_PA3
#endif
#ifdef __PA4_CN
#define GPIO_PA4 (0x04)
#define PA4 GPIO_PA4
#endif
#ifdef __PA5_CN
#define GPIO_PA5 (0x05)
#define PA5 GPIO_PA5
#endif
#ifdef __PA6_CN
#define GPIO_PA6 (0x06)
#define PA6 GPIO_PA6
#endif
#ifdef __PA7_CN
#define GPIO_PA7 (0x07)
#define PA7 GPIO_PA7
#endif
#ifdef __PA8_CN
#define GPIO_PA8 (0x08)
#define PA8 GPIO_PA8
#endif
#ifdef __PA9_CN
#define GPIO_PA9 (0x09)
#define PA9 GPIO_PA9
#endif
#ifdef __PA10_CN
#define GPIO_PA10 (0x0A)
#define PA10 GPIO_PA10
#endif
#ifdef __PA11_CN
#define GPIO_PA11 (0x0B)
#define PA11 GPIO_PA11
#endif
#ifdef __PA12_CN
#define GPIO_PA12 (0x0C)
#define PA12 GPIO_PA12
#endif
#ifdef __PA13_CN
#define GPIO_PA13 (0x0D)
#define PA13 GPIO_PA13
#endif
#ifdef __PA14_CN
#define GPIO_PA14 (0x0E)
#define PA14 GPIO_PA14
#endif
#ifdef __PA15_CN
#define GPIO_PA15 (0x0F)
#define PA15 GPIO_PA15
#endif
#ifdef __PC0_CN
#define GPIO_PC0 (0x20)
#define PC0 GPIO_PC0
#endif
#ifdef __PC1_CN
#define GPIO_PC1 (0x21)
#define PC1 GPIO_PC1
#endif
#ifdef __PC2_CN
#define GPIO_PC2 (0x22)
#define PC2 GPIO_PC2
#endif
#ifdef __PC3_CN
#define GPIO_PC3 (0x23)
#define PC3 GPIO_PC3
#endif
#ifdef __PC4_CN
#define GPIO_PC4 (0x24)
#define PC4 GPIO_PC4
#endif
#ifdef __PC5_CN
#define GPIO_PC5 (0x25)
#define PC5 GPIO_PC5
#endif
#ifdef __PC6_CN
#define GPIO_PC6 (0x26)
#define PC6 GPIO_PC6
#endif
#ifdef __PC7_CN
#define GPIO_PC7 (0x27)
#define PC7 GPIO_PC7
#endif
#ifdef __PC8_CN
#define GPIO_PC8 (0x28)
#define PC8 GPIO_PC8
#endif
#ifdef __PC9_CN
#define GPIO_PC9 (0x29)
#define PC9 GPIO_PC9
#endif
#ifdef __PC10_CN
#define GPIO_PC10 (0x2A)
#define PC10 GPIO_PC10
#endif
#ifdef __PC11_CN
#define GPIO_PC11 (0x2B)
#define PC11 GPIO_PC11
#endif
#ifdef __PC12_CN
#define GPIO_PC12 (0x2C)
#define PC12 GPIO_PC12
#endif
#ifdef __PC13_CN
#define GPIO_PC13 (0x2D)
#define PC13 GPIO_PC13
#endif
#ifdef __PC14_CN
#define GPIO_PC14 (0x2E)
#define PC14 GPIO_PC14
#endif
#ifdef __PC15_CN
#define GPIO_PC15 (0x2F)
#define PC15 GPIO_PC15
#endif
#ifdef __PD0_CN
#define GPIO_PD0 (0x30)
#define PD0 GPIO_PD0
#endif
#ifdef __PD1_CN
#define GPIO_PD1 (0x31)
#define PD1 GPIO_PD1
#endif
#ifdef __PD2_CN
#define GPIO_PD2 (0x32)
#define PD2 GPIO_PD2
#endif
#ifdef __PD3_CN
#define GPIO_PD3 (0x33)
#define PD3 GPIO_PD3
#endif
#ifdef __PD4_CN
#define GPIO_PD4 (0x34)
#define PD4 GPIO_PD4
#endif
#ifdef __PD5_CN
#define GPIO_PD5 (0x35)
#define PD5 GPIO_PD5
#endif
#ifdef __PD6_CN
#define GPIO_PD6 (0x36)
#define PD6 GPIO_PD6
#endif
#ifdef __PD7_CN
#define GPIO_PD7 (0x37)
#define PD7 GPIO_PD7
#endif
#ifdef __PD8_CN
#define GPIO_PD8 (0x38)
#define PD8 GPIO_PD8
#endif
#ifdef __PD9_CN
#define GPIO_PD9 (0x39)
#define PD9 GPIO_PD9
#endif
#ifdef __PD10_CN
#define GPIO_PD10 (0x3A)
#define PD10 GPIO_PD10
#endif
#ifdef __PD11_CN
#define GPIO_PD11 (0x3B)
#define PD11 GPIO_PD11
#endif
#ifdef __PD12_CN
#define GPIO_PD12 (0x3C)
#define PD12 GPIO_PD12
#endif
#ifdef __PD13_CN
#define GPIO_PD13 (0x3D)
#define PD13 GPIO_PD13
#endif
#ifdef __PD14_CN
#define GPIO_PD14 (0x3E)
#define PD14 GPIO_PD14
#endif
#ifdef __PD15_CN
#define GPIO_PD15 (0x3F)
#define PD15 GPIO_PD15
#endif
#ifdef __PE0_CN
#define GPIO_PE0 (0x40)
#define PE0 GPIO_PE0
#endif
#ifdef __PE1_CN
#define GPIO_PE1 (0x41)
#define PE1 GPIO_PE1
#endif
#ifdef __PE2_CN
#define GPIO_PE2 (0x42)
#define PE2 GPIO_PE2
#endif
#ifdef __PE3_CN
#define GPIO_PE3 (0x43)
#define PE3 GPIO_PE3
#endif
#ifdef __PE4_CN
#define GPIO_PE4 (0x44)
#define PE4 GPIO_PE4
#endif
#ifdef __PE5_CN
#define GPIO_PE5 (0x45)
#define PE5 GPIO_PE5
#endif
#ifdef __PE6_CN
#define GPIO_PE6 (0x46)
#define PE6 GPIO_PE6
#endif
#ifdef __PE7_CN
#define GPIO_PE7 (0x47)
#define PE7 GPIO_PE7
#endif
#ifdef __PE8_CN
#define GPIO_PE8 (0x48)
#define PE8 GPIO_PE8
#endif
#ifdef __PE9_CN
#define GPIO_PE9 (0x49)
#define PE9 GPIO_PE9
#endif
#ifdef __PE10_CN
#define GPIO_PE10 (0x4A)
#define PE10 GPIO_PE10
#endif
#ifdef __PE11_CN
#define GPIO_PE11 (0x4B)
#define PE11 GPIO_PE11
#endif
#ifdef __PE12_CN
#define GPIO_PE12 (0x4C)
#define PE12 GPIO_PE12
#endif
#ifdef __PE13_CN
#define GPIO_PE13 (0x4D)
#define PE13 GPIO_PE13
#endif
#ifdef __PE14_CN
#define GPIO_PE14 (0x4E)
#define PE14 GPIO_PE14
#endif
#ifdef __PE15_CN
#define GPIO_PE15 (0x4F)
#define PE15 GPIO_PE15
#endif
#ifdef __PF0_CN
#define GPIO_PF0 (0x50)
#define PF0 GPIO_PF0
#endif
#ifdef __PF1_CN
#define GPIO_PF1 (0x51)
#define PF1 GPIO_PF1
#endif
#ifdef __PF2_CN
#define GPIO_PF2 (0x52)
#define PF2 GPIO_PF2
#endif
#ifdef __PF3_CN
#define GPIO_PF3 (0x53)
#define PF3 GPIO_PF3
#endif
#ifdef __PF4_CN
#define GPIO_PF4 (0x54)
#define PF4 GPIO_PF4
#endif
#ifdef __PF5_CN
#define GPIO_PF5 (0x55)
#define PF5 GPIO_PF5
#endif
#ifdef __PF6_CN
#define GPIO_PF6 (0x56)
#define PF6 GPIO_PF6
#endif
#ifdef __PF7_CN
#define GPIO_PF7 (0x57)
#define PF7 GPIO_PF7
#endif
#ifdef __PF8_CN
#define GPIO_PF8 (0x58)
#define PF8 GPIO_PF8
#endif
#ifdef __PF9_CN
#define GPIO_PF9 (0x59)
#define PF9 GPIO_PF9
#endif
#ifdef __PF10_CN
#define GPIO_PF10 (0x5A)
#define PF10 GPIO_PF10
#endif
#ifdef __PF11_CN
#define GPIO_PF11 (0x5B)
#define PF11 GPIO_PF11
#endif
#ifdef __PF12_CN
#define GPIO_PF12 (0x5C)
#define PF12 GPIO_PF12
#endif
#ifdef __PF13_CN
#define GPIO_PF13 (0x5D)
#define PF13 GPIO_PF13
#endif
#ifdef __PF14_CN
#define GPIO_PF14 (0x5E)
#define PF14 GPIO_PF14
#endif
#ifdef __PF15_CN
#define GPIO_PF15 (0x5F)
#define PF15 GPIO_PF15
#endif
#ifdef __PG0_CN
#define GPIO_PG0 (0x60)
#define PG0 GPIO_PG0
#endif
#ifdef __PG1_CN
#define GPIO_PG1 (0x61)
#define PG1 GPIO_PG1
#endif
#ifdef __PG2_CN
#define GPIO_PG2 (0x62)
#define PG2 GPIO_PG2
#endif
#ifdef __PG3_CN
#define GPIO_PG3 (0x63)
#define PG3 GPIO_PG3
#endif
#ifdef __PG4_CN
#define GPIO_PG4 (0x64)
#define PG4 GPIO_PG4
#endif
#ifdef __PG5_CN
#define GPIO_PG5 (0x65)
#define PG5 GPIO_PG5
#endif
#ifdef __PG6_CN
#define GPIO_PG6 (0x66)
#define PG6 GPIO_PG6
#endif
#ifdef __PG7_CN
#define GPIO_PG7 (0x67)
#define PG7 GPIO_PG7
#endif
#ifdef __PG8_CN
#define GPIO_PG8 (0x68)
#define PG8 GPIO_PG8
#endif
#ifdef __PG9_CN
#define GPIO_PG9 (0x69)
#define PG9 GPIO_PG9
#endif
#ifdef __PG10_CN
#define GPIO_PG10 (0x6A)
#define PG10 GPIO_PG10
#endif
#ifdef __PG11_CN
#define GPIO_PG11 (0x6B)
#define PG11 GPIO_PG11
#endif
#ifdef __PG12_CN
#define GPIO_PG12 (0x6C)
#define PG12 GPIO_PG12
#endif
#ifdef __PG13_CN
#define GPIO_PG13 (0x6D)
#define PG13 GPIO_PG13
#endif
#ifdef __PG14_CN
#define GPIO_PG14 (0x6E)
#define PG14 GPIO_PG14
#endif
#ifdef __PG15_CN
#define GPIO_PG15 (0x6F)
#define PG15 GPIO_PG15
#endif
#ifdef __PN0_CN
#define GPIO_PN0 (0xD0)
#define PN0 GPIO_PN0
#endif
#ifdef __PN1_CN
#define GPIO_PN1 (0xD1)
#define PN1 GPIO_PN1
#endif
#ifdef __PN2_CN
#define GPIO_PN2 (0xD2)
#define PN2 GPIO_PN2
#endif
#ifdef __PN3_CN
#define GPIO_PN3 (0xD3)
#define PN3 GPIO_PN3
#endif
#ifdef __PN4_CN
#define GPIO_PN4 (0xD4)
#define PN4 GPIO_PN4
#endif
#ifdef __PN5_CN
#define GPIO_PN5 (0xD5)
#define PN5 GPIO_PN5
#endif
#ifdef __PN6_CN
#define GPIO_PN6 (0xD6)
#define PN6 GPIO_PN6
#endif
#ifdef __PN7_CN
#define GPIO_PN7 (0xD7)
#define PN7 GPIO_PN7
#endif
#ifdef __PN8_CN
#define GPIO_PN8 (0xD8)
#define PN8 GPIO_PN8
#endif
#ifdef __PN9_CN
#define GPIO_PN9 (0xD9)
#define PN9 GPIO_PN9
#endif
#ifdef __PN10_CN
#define GPIO_PN10 (0xDA)
#define PN10 GPIO_PN10
#endif
#ifdef __PN11_CN
#define GPIO_PN11 (0xDB)
#define PN11 GPIO_PN11
#endif
#ifdef __PN12_CN
#define GPIO_PN12 (0xDC)
#define PN12 GPIO_PN12
#endif
#ifdef __PN13_CN
#define GPIO_PN13 (0xDD)
#define PN13 GPIO_PN13
#endif
#ifdef __PN14_CN
#define GPIO_PN14 (0xDE)
#define PN14 GPIO_PN14
#endif
#ifdef __PN15_CN
#define GPIO_PN15 (0xDF)
#define PN15 GPIO_PN15
#endif
#ifdef __PU0_CN
#define GPIO_PU0 (0x140)
#define PU0 GPIO_PU0
#endif
#ifdef __PU1_CN
#define GPIO_PU1 (0x141)
#define PU1 GPIO_PU1
#endif
#ifdef __PU2_CN
#define GPIO_PU2 (0x142)
#define PU2 GPIO_PU2
#endif
#ifdef __PU3_CN
#define GPIO_PU3 (0x143)
#define PU3 GPIO_PU3
#endif
#ifdef __PU4_CN
#define GPIO_PU4 (0x144)
#define PU4 GPIO_PU4
#endif
#ifdef __PU5_CN
#define GPIO_PU5 (0x145)
#define PU5 GPIO_PU5
#endif
#ifdef __PU6_CN
#define GPIO_PU6 (0x146)
#define PU6 GPIO_PU6
#endif
#ifdef __PU7_CN
#define GPIO_PU7 (0x147)
#define PU7 GPIO_PU7
#endif
#ifdef __PU8_CN
#define GPIO_PU8 (0x148)
#define PU8 GPIO_PU8
#endif
#ifdef __PU9_CN
#define GPIO_PU9 (0x149)
#define PU9 GPIO_PU9
#endif
#ifdef __PU10_CN
#define GPIO_PU10 (0x14A)
#define PU10 GPIO_PU10
#endif
#ifdef __PU11_CN
#define GPIO_PU11 (0x14B)
#define PU11 GPIO_PU11
#endif
#ifdef __PU12_CN
#define GPIO_PU12 (0x14C)
#define PU12 GPIO_PU12
#endif
#ifdef __PU13_CN
#define GPIO_PU13 (0x14D)
#define PU13 GPIO_PU13
#endif
#ifdef __PU14_CN
#define GPIO_PU14 (0x14E)
#define PU14 GPIO_PU14
#endif
#ifdef __PU15_CN
#define GPIO_PU15 (0x14F)
#define PU15 GPIO_PU15
#endif
#ifdef __PV0_CN
#define GPIO_PV0 (0x150)
#define PV0 GPIO_PV0
#endif
#ifdef __PV1_CN
#define GPIO_PV1 (0x151)
#define PV1 GPIO_PV1
#endif
#ifdef __PV2_CN
#define GPIO_PV2 (0x152)
#define PV2 GPIO_PV2
#endif
#ifdef __PV3_CN
#define GPIO_PV3 (0x153)
#define PV3 GPIO_PV3
#endif
#ifdef __PV4_CN
#define GPIO_PV4 (0x154)
#define PV4 GPIO_PV4
#endif
#ifdef __PV5_CN
#define GPIO_PV5 (0x155)
#define PV5 GPIO_PV5
#endif
#ifdef __PV6_CN
#define GPIO_PV6 (0x156)
#define PV6 GPIO_PV6
#endif
#ifdef __PV7_CN
#define GPIO_PV7 (0x157)
#define PV7 GPIO_PV7
#endif
#ifdef __PV8_CN
#define GPIO_PV8 (0x158)
#define PV8 GPIO_PV8
#endif
#ifdef __PV9_CN
#define GPIO_PV9 (0x159)
#define PV9 GPIO_PV9
#endif
#ifdef __PV10_CN
#define GPIO_PV10 (0x15A)
#define PV10 GPIO_PV10
#endif
#ifdef __PV11_CN
#define GPIO_PV11 (0x15B)
#define PV11 GPIO_PV11
#endif
#ifdef __PV12_CN
#define GPIO_PV12 (0x15C)
#define PV12 GPIO_PV12
#endif
#ifdef __PV13_CN
#define GPIO_PV13 (0x15D)
#define PV13 GPIO_PV13
#endif
#ifdef __PV14_CN
#define GPIO_PV14 (0x15E)
#define PV14 GPIO_PV14
#endif
#ifdef __PV15_CN
#define GPIO_PV15 (0x15F)
#define PV15 GPIO_PV15
#endif

#define GPIO_PIN_0  (0x00)
#define PIN_0       GPIO_PIN_0
#define GPIO_PIN_1  (0x01)
#define PIN_1       GPIO_PIN_1
#define GPIO_PIN_2  (0x02)
#define PIN_2       GPIO_PIN_2
#define GPIO_PIN_3  (0x03)
#define PIN_3       GPIO_PIN_3
#define GPIO_PIN_4  (0x04)
#define PIN_4       GPIO_PIN_4
#define GPIO_PIN_5  (0x05)
#define PIN_5       GPIO_PIN_5
#define GPIO_PIN_6  (0x06)
#define PIN_6       GPIO_PIN_6
#define GPIO_PIN_7  (0x07)
#define PIN_7       GPIO_PIN_7
#define GPIO_PIN_8  (0x08)
#define PIN_8       GPIO_PIN_8
#define GPIO_PIN_9  (0x09)
#define PIN_9       GPIO_PIN_9
#define GPIO_PIN_10 (0x0A)
#define PIN_10      GPIO_PIN_10
#define GPIO_PIN_11 (0x0B)
#define PIN_11      GPIO_PIN_11
#define GPIO_PIN_12 (0x0C)
#define PIN_12      GPIO_PIN_12
#define GPIO_PIN_13 (0x0D)
#define PIN_13      GPIO_PIN_13
#define GPIO_PIN_14 (0x0E)
#define PIN_14      GPIO_PIN_14
#define GPIO_PIN_15 (0x0F)
#define PIN_15      GPIO_PIN_15

/* Port IDs (base offsets) ? samo portovi koje ima? */
#ifdef __PORT_A_CN
#define GPIO_PORT_A (0x00)
#define PORT_A GPIO_PORT_A
#endif
#ifdef __PORT_C_CN
#define GPIO_PORT_C (0x02)
#define PORT_C GPIO_PORT_C
#endif
#ifdef __PORT_D_CN
#define GPIO_PORT_D (0x03)
#define PORT_D GPIO_PORT_D
#endif
#ifdef __PORT_E_CN
#define GPIO_PORT_E (0x04)
#define PORT_E GPIO_PORT_E
#endif
#ifdef __PORT_F_CN
#define GPIO_PORT_F (0x05)
#define PORT_F GPIO_PORT_F
#endif
#ifdef __PORT_G_CN
#define GPIO_PORT_G (0x06)
#define PORT_G GPIO_PORT_G
#endif
#ifdef __PORT_N_CN
#define GPIO_PORT_N (0x0D)
#define PORT_N GPIO_PORT_N
#endif
#ifdef __PORT_U_CN
#define GPIO_PORT_U (0x14)
#define PORT_U GPIO_PORT_U
#endif
#ifdef __PORT_V_CN
#define GPIO_PORT_V (0x15)
#define PORT_V GPIO_PORT_V
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END


















#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END     