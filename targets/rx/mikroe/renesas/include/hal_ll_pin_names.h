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

#ifdef __PORT_0_CN
#define GPIO_FEATURE_GROUP_1
#endif
#ifdef __PORT_1_CN
#define GPIO_FEATURE_GROUP_2
#endif
#ifdef __PORT_2_CN
#define GPIO_FEATURE_GROUP_3
#endif
#ifdef __PORT_3_CN
#define GPIO_FEATURE_GROUP_4
#endif
#ifdef __PORT_4_CN
#define GPIO_FEATURE_GROUP_5
#endif
#ifdef __PORT_5_CN
#define GPIO_FEATURE_GROUP_6
#endif
#ifdef __PORT_6_CN
#define GPIO_FEATURE_GROUP_7
#endif
#ifdef __PORT_7_CN
#define GPIO_FEATURE_GROUP_8
#endif
#ifdef __PORT_8_CN
#define GPIO_FEATURE_GROUP_9
#endif
#ifdef __PORT_9_CN
#define GPIO_FEATURE_GROUP_10
#endif
#ifdef __PORT_A_CN
#define GPIO_FEATURE_GROUP_11
#endif
#ifdef __PORT_B_CN
#define GPIO_FEATURE_GROUP_12
#endif
#ifdef __PORT_C_CN
#define GPIO_FEATURE_GROUP_13
#endif
#ifdef __PORT_D_CN
#define GPIO_FEATURE_GROUP_14
#endif
#ifdef __PORT_E_CN
#define GPIO_FEATURE_GROUP_15
#endif
#ifdef __PORT_F_CN
#define GPIO_FEATURE_GROUP_16
#endif
#ifdef __PORT_G_CN
#define GPIO_FEATURE_GROUP_17
#endif
#ifdef __PORT_H_CN
#define GPIO_FEATURE_GROUP_18
#endif
#ifdef __PORT_K_CN
#define GPIO_FEATURE_GROUP_19
#endif
#ifdef __PORT_N_CN
#define GPIO_FEATURE_GROUP_20
#endif

// PORT 0
#ifdef __P000_CN
#define GPIO_P000 (0x00)
#define P000 GPIO_P000 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P000!
#endif
#ifdef __P001_CN
#define GPIO_P001 (0x01)
#define P001 GPIO_P001 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P001!
#endif
#ifdef __P002_CN
#define GPIO_P002 (0x02)
#define P002 GPIO_P002 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P002!
#endif
#ifdef __P003_CN
#define GPIO_P003 (0x03)
#define P003 GPIO_P003 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P003!
#endif
#ifdef __P004_CN
#define GPIO_P004 (0x04)
#define P004 GPIO_P004 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P004!
#endif
#ifdef __P005_CN
#define GPIO_P005 (0x05)
#define P005 GPIO_P005 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P005!
#endif
#ifdef __P006_CN
#define GPIO_P006 (0x06)
#define P006 GPIO_P006 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P006!
#endif
#ifdef __P007_CN
#define GPIO_P007 (0x07)
#define P007 GPIO_P007 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P007!
#endif

// PORT 1
#ifdef __P100_CN
#define GPIO_P100 (0x08)
#define P100 GPIO_P100 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P100!
#endif
#ifdef __P101_CN
#define GPIO_P101 (0x09)
#define P101 GPIO_P101 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P101!
#endif
#ifdef __P102_CN
#define GPIO_P102 (0x0A)
#define P102 GPIO_P102 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P102!
#endif
#ifdef __P103_CN
#define GPIO_P103 (0x0B)
#define P103 GPIO_P103 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P103!
#endif
#ifdef __P104_CN
#define GPIO_P104 (0x0C)
#define P104 GPIO_P104 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P104!
#endif
#ifdef __P105_CN
#define GPIO_P105 (0x0D)
#define P105 GPIO_P105 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P105!
#endif
#ifdef __P106_CN
#define GPIO_P106 (0x0E)
#define P106 GPIO_P106 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P106!
#endif
#ifdef __P107_CN
#define GPIO_P107 (0x0F)
#define P107 GPIO_P107 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P107!
#endif

// PORT 2
#ifdef __P200_CN
#define GPIO_P200 (0x10)
#define P200 GPIO_P200 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P200!
#endif
#ifdef __P201_CN
#define GPIO_P201 (0x11)
#define P201 GPIO_P201 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P201!
#endif
#ifdef __P202_CN
#define GPIO_P202 (0x12)
#define P202 GPIO_P202 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P202!
#endif
#ifdef __P203_CN
#define GPIO_P203 (0x13)
#define P203 GPIO_P203 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P203!
#endif
#ifdef __P204_CN
#define GPIO_P204 (0x14)
#define P204 GPIO_P204 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P204!
#endif
#ifdef __P205_CN
#define GPIO_P205 (0x15)
#define P205 GPIO_P205 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P205!
#endif
#ifdef __P206_CN
#define GPIO_P206 (0x16)
#define P206 GPIO_P206 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P206!
#endif
#ifdef __P207_CN
#define GPIO_P207 (0x17)
#define P207 GPIO_P207 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P207!
#endif

// PORT 3
#ifdef __P300_CN
#define GPIO_P300 (0x18)
#define P300 GPIO_P300 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P300!
#endif
#ifdef __P301_CN
#define GPIO_P301 (0x19)
#define P301 GPIO_P301 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P301!
#endif
#ifdef __P302_CN
#define GPIO_P302 (0x1A)
#define P302 GPIO_P302 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P302!
#endif
#ifdef __P303_CN
#define GPIO_P303 (0x1B)
#define P303 GPIO_P303 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P303!
#endif
#ifdef __P304_CN
#define GPIO_P304 (0x1C)
#define P304 GPIO_P304 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P304!
#endif
#ifdef __P305_CN
#define GPIO_P305 (0x1D)
#define P305 GPIO_P305 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P305!
#endif
#ifdef __P306_CN
#define GPIO_P306 (0x1E)
#define P306 GPIO_P306 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P306!
#endif
#ifdef __P307_CN
#define GPIO_P307 (0x1F)
#define P307 GPIO_P307 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P307!
#endif

// PORT 4
#ifdef __P400_CN
#define GPIO_P400 (0x20)
#define P400 GPIO_P400 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P400!
#endif
#ifdef __P401_CN
#define GPIO_P401 (0x21)
#define P401 GPIO_P401 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P401!
#endif
#ifdef __P402_CN
#define GPIO_P402 (0x22)
#define P402 GPIO_P402 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P402!
#endif
#ifdef __P403_CN
#define GPIO_P403 (0x23)
#define P403 GPIO_P403 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P403!
#endif
#ifdef __P404_CN
#define GPIO_P404 (0x24)
#define P404 GPIO_P404 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P404!
#endif
#ifdef __P405_CN
#define GPIO_P405 (0x25)
#define P405 GPIO_P405 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P405!
#endif
#ifdef __P406_CN
#define GPIO_P406 (0x26)
#define P406 GPIO_P406 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P406!
#endif
#ifdef __P407_CN
#define GPIO_P407 (0x27)
#define P407 GPIO_P407 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P407!
#endif

// PORT 5
#ifdef __P500_CN
#define GPIO_P500 (0x28)
#define P500 GPIO_P500 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P500!
#endif
#ifdef __P501_CN
#define GPIO_P501 (0x29)
#define P501 GPIO_P501 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P501!
#endif
#ifdef __P502_CN
#define GPIO_P502 (0x2A)
#define P502 GPIO_P502 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P502!
#endif
#ifdef __P503_CN
#define GPIO_P503 (0x2B)
#define P503 GPIO_P503 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P503!
#endif
#ifdef __P504_CN
#define GPIO_P504 (0x2C)
#define P504 GPIO_P504 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P504!
#endif
#ifdef __P505_CN
#define GPIO_P505 (0x2D)
#define P505 GPIO_P505 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P505!
#endif
#ifdef __P506_CN
#define GPIO_P506 (0x2E)
#define P506 GPIO_P506 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P506!
#endif
#ifdef __P507_CN
#define GPIO_P507 (0x2F)
#define P507 GPIO_P507 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P507!
#endif

// PORT 6
#ifdef __P600_CN
#define GPIO_P600 (0x30)
#define P600 GPIO_P600 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P600!
#endif
#ifdef __P601_CN
#define GPIO_P601 (0x31)
#define P601 GPIO_P601 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P601!
#endif
#ifdef __P602_CN
#define GPIO_P602 (0x32)
#define P602 GPIO_P602 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P602!
#endif
#ifdef __P603_CN
#define GPIO_P603 (0x33)
#define P603 GPIO_P603 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P603!
#endif
#ifdef __P604_CN
#define GPIO_P604 (0x34)
#define P604 GPIO_P604 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P604!
#endif
#ifdef __P605_CN
#define GPIO_P605 (0x35)
#define P605 GPIO_P605 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P605!
#endif
#ifdef __P606_CN
#define GPIO_P606 (0x36)
#define P606 GPIO_P606 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P606!
#endif
#ifdef __P607_CN
#define GPIO_P607 (0x37)
#define P607 GPIO_P607 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P607!
#endif

// PORT 7
#ifdef __P700_CN
#define GPIO_P700 (0x38)
#define P700 GPIO_P700 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P700!
#endif
#ifdef __P701_CN
#define GPIO_P701 (0x39)
#define P701 GPIO_P701 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P701!
#endif
#ifdef __P702_CN
#define GPIO_P702 (0x3A)
#define P702 GPIO_P702 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P702!
#endif
#ifdef __P703_CN
#define GPIO_P703 (0x3B)
#define P703 GPIO_P703 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P703!
#endif
#ifdef __P704_CN
#define GPIO_P704 (0x3C)
#define P704 GPIO_P704 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P704!
#endif
#ifdef __P705_CN
#define GPIO_P705 (0x3D)
#define P705 GPIO_P705 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P705!
#endif
#ifdef __P706_CN
#define GPIO_P706 (0x3E)
#define P706 GPIO_P706 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P706!
#endif
#ifdef __P707_CN
#define GPIO_P707 (0x3F)
#define P707 GPIO_P707 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P707!
#endif

// PORT 8
#ifdef __P800_CN
#define GPIO_P800 (0x40)
#define P800 GPIO_P800 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P800!
#endif
#ifdef __P801_CN
#define GPIO_P801 (0x41)
#define P801 GPIO_P801 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P801!
#endif
#ifdef __P802_CN
#define GPIO_P802 (0x42)
#define P802 GPIO_P802 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P802!
#endif
#ifdef __P803_CN
#define GPIO_P803 (0x43)
#define P803 GPIO_P803 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P803!
#endif
#ifdef __P804_CN
#define GPIO_P804 (0x44)
#define P804 GPIO_P804 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P804!
#endif
#ifdef __P805_CN
#define GPIO_P805 (0x45)
#define P805 GPIO_P805 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P805!
#endif
#ifdef __P806_CN
#define GPIO_P806 (0x46)
#define P806 GPIO_P806 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P806!
#endif
#ifdef __P807_CN
#define GPIO_P807 (0x47)
#define P807 GPIO_P807 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P807!
#endif

// PORT 9
#ifdef __P900_CN
#define GPIO_P900 (0x48)
#define P900 GPIO_P900 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P900!
#endif
#ifdef __P901_CN
#define GPIO_P901 (0x49)
#define P901 GPIO_P901 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P901!
#endif
#ifdef __P902_CN
#define GPIO_P902 (0x4A)
#define P902 GPIO_P902 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P902!
#endif
#ifdef __P903_CN
#define GPIO_P903 (0x4B)
#define P903 GPIO_P903 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P903!
#endif
#ifdef __P904_CN
#define GPIO_P904 (0x4C)
#define P904 GPIO_P904 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P904!
#endif
#ifdef __P905_CN
#define GPIO_P905 (0x4D)
#define P905 GPIO_P905 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P905!
#endif
#ifdef __P906_CN
#define GPIO_P906 (0x4E)
#define P906 GPIO_P906 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P906!
#endif
#ifdef __P907_CN
#define GPIO_P907 (0x4F)
#define P907 GPIO_P907 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P907!
#endif

// PORT A
#ifdef __PA00_CN
#define GPIO_PA00 (0x50)
#define PA00 GPIO_PA00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA00!
#endif
#ifdef __PA01_CN
#define GPIO_PA01 (0x51)
#define PA01 GPIO_PA01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA01!
#endif
#ifdef __PA02_CN
#define GPIO_PA02 (0x52)
#define PA02 GPIO_PA02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA02!
#endif
#ifdef __PA03_CN
#define GPIO_PA03 (0x53)
#define PA03 GPIO_PA03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA03!
#endif
#ifdef __PA04_CN
#define GPIO_PA04 (0x54)
#define PA04 GPIO_PA04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA04!
#endif
#ifdef __PA05_CN
#define GPIO_PA05 (0x55)
#define PA05 GPIO_PA05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA05!
#endif
#ifdef __PA06_CN
#define GPIO_PA06 (0x56)
#define PA06 GPIO_PA06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA06!
#endif
#ifdef __PA07_CN
#define GPIO_PA07 (0x57)
#define PA07 GPIO_PA07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA07!
#endif

// PORT B
#ifdef __PB00_CN
#define GPIO_PB00 (0x58)
#define PB00 GPIO_PB00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB00!
#endif
#ifdef __PB01_CN
#define GPIO_PB01 (0x59)
#define PB01 GPIO_PB01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB01!
#endif
#ifdef __PB02_CN
#define GPIO_PB02 (0x5A)
#define PB02 GPIO_PB02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB02!
#endif
#ifdef __PB03_CN
#define GPIO_PB03 (0x5B)
#define PB03 GPIO_PB03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB03!
#endif
#ifdef __PB04_CN
#define GPIO_PB04 (0x5C)
#define PB04 GPIO_PB04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB04!
#endif
#ifdef __PB05_CN
#define GPIO_PB05 (0x5D)
#define PB05 GPIO_PB05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB05!
#endif
#ifdef __PB06_CN
#define GPIO_PB06 (0x5E)
#define PB06 GPIO_PB06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB06!
#endif
#ifdef __PB07_CN
#define GPIO_PB07 (0x5F)
#define PB07 GPIO_PB07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB07!
#endif

// PORT C
#ifdef __PC00_CN
#define GPIO_PC00 (0x60)
#define PC00 GPIO_PC00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC00!
#endif
#ifdef __PC01_CN
#define GPIO_PC01 (0x61)
#define PC01 GPIO_PC01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC01!
#endif
#ifdef __PC02_CN
#define GPIO_PC02 (0x62)
#define PC02 GPIO_PC02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC02!
#endif
#ifdef __PC03_CN
#define GPIO_PC03 (0x63)
#define PC03 GPIO_PC03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC03!
#endif
#ifdef __PC04_CN
#define GPIO_PC04 (0x64)
#define PC04 GPIO_PC04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC04!
#endif
#ifdef __PC05_CN
#define GPIO_PC05 (0x65)
#define PC05 GPIO_PC05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC05!
#endif
#ifdef __PC06_CN
#define GPIO_PC06 (0x66)
#define PC06 GPIO_PC06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC06!
#endif
#ifdef __PC07_CN
#define GPIO_PC07 (0x67)
#define PC07 GPIO_PC07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC07!
#endif

// PORT D
#ifdef __PD00_CN
#define GPIO_PD00 (0x68)
#define PD00 GPIO_PD00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD00!
#endif
#ifdef __PD01_CN
#define GPIO_PD01 (0x69)
#define PD01 GPIO_PD01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD01!
#endif
#ifdef __PD02_CN
#define GPIO_PD02 (0x6A)
#define PD02 GPIO_PD02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD02!
#endif
#ifdef __PD03_CN
#define GPIO_PD03 (0x6B)
#define PD03 GPIO_PD03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD03!
#endif
#ifdef __PD04_CN
#define GPIO_PD04 (0x6C)
#define PD04 GPIO_PD04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD04!
#endif
#ifdef __PD05_CN
#define GPIO_PD05 (0x6D)
#define PD05 GPIO_PD05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD05!
#endif
#ifdef __PD06_CN
#define GPIO_PD06 (0x6E)
#define PD06 GPIO_PD06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD06!
#endif
#ifdef __PD07_CN
#define GPIO_PD07 (0x6F)
#define PD07 GPIO_PD07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD07!
#endif

// PORT E
#ifdef __PE00_CN
#define GPIO_PE00 (0x70)
#define PE00 GPIO_PE00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE00!
#endif
#ifdef __PE01_CN
#define GPIO_PE01 (0x71)
#define PE01 GPIO_PE01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE01!
#endif
#ifdef __PE02_CN
#define GPIO_PE02 (0x72)
#define PE02 GPIO_PE02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE02!
#endif
#ifdef __PE03_CN
#define GPIO_PE03 (0x73)
#define PE03 GPIO_PE03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE03!
#endif
#ifdef __PE04_CN
#define GPIO_PE04 (0x74)
#define PE04 GPIO_PE04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE04!
#endif
#ifdef __PE05_CN
#define GPIO_PE05 (0x75)
#define PE05 GPIO_PE05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE05!
#endif
#ifdef __PE06_CN
#define GPIO_PE06 (0x76)
#define PE06 GPIO_PE06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE06!
#endif
#ifdef __PE07_CN
#define GPIO_PE07 (0x77)
#define PE07 GPIO_PE07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE07!
#endif

// PORT F
#ifdef __PF00_CN
#define GPIO_PF00 (0x78)
#define PF00 GPIO_PF00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF00!
#endif
#ifdef __PF01_CN
#define GPIO_PF01 (0x79)
#define PF01 GPIO_PF01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF01!
#endif
#ifdef __PF02_CN
#define GPIO_PF02 (0x7A)
#define PF02 GPIO_PF02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF02!
#endif
#ifdef __PF03_CN
#define GPIO_PF03 (0x7B)
#define PF03 GPIO_PF03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF03!
#endif
#ifdef __PF04_CN
#define GPIO_PF04 (0x7C)
#define PF04 GPIO_PF04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF04!
#endif
#ifdef __PF05_CN
#define GPIO_PF05 (0x7D)
#define PF05 GPIO_PF05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF05!
#endif
#ifdef __PF06_CN
#define GPIO_PF06 (0x7E)
#define PF06 GPIO_PF06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF06!
#endif
#ifdef __PF07_CN
#define GPIO_PF07 (0x7F)
#define PF07 GPIO_PF07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF07!
#endif

// PORT G
#ifdef __PG00_CN
#define GPIO_PG00 (0x80)
#define PG00 GPIO_PG00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG00!
#endif
#ifdef __PG01_CN
#define GPIO_PG01 (0x81)
#define PG01 GPIO_PG01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG01!
#endif
#ifdef __PG02_CN
#define GPIO_PG02 (0x82)
#define PG02 GPIO_PG02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG02!
#endif
#ifdef __PG03_CN
#define GPIO_PG03 (0x83)
#define PG03 GPIO_PG03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG03!
#endif
#ifdef __PG04_CN
#define GPIO_PG04 (0x84)
#define PG04 GPIO_PG04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG04!
#endif
#ifdef __PG05_CN
#define GPIO_PG05 (0x85)
#define PG05 GPIO_PG05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG05!
#endif
#ifdef __PG06_CN
#define GPIO_PG06 (0x86)
#define PG06 GPIO_PG06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG06!
#endif
#ifdef __PG07_CN
#define GPIO_PG07 (0x87)
#define PG07 GPIO_PG07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG07!
#endif

// PORT H
#ifdef __PH00_CN
#define GPIO_PH00 (0x88)
#define PH00 GPIO_PH00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH00!
#endif
#ifdef __PH01_CN
#define GPIO_PH01 (0x89)
#define PH01 GPIO_PH01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH01!
#endif
#ifdef __PH02_CN
#define GPIO_PH02 (0x8A)
#define PH02 GPIO_PH02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH02!
#endif
#ifdef __PH03_CN
#define GPIO_PH03 (0x8B)
#define PH03 GPIO_PH03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH03!
#endif
#ifdef __PH04_CN
#define GPIO_PH04 (0x8C)
#define PH04 GPIO_PH04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH04!
#endif
#ifdef __PH05_CN
#define GPIO_PH05 (0x8D)
#define PH05 GPIO_PH05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH05!
#endif
#ifdef __PH06_CN
#define GPIO_PH06 (0x8E)
#define PH06 GPIO_PH06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH06!
#endif
#ifdef __PH07_CN
#define GPIO_PH07 (0x8F)
#define PH07 GPIO_PH07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH07!
#endif

// PORT K
#ifdef __PK00_CN
#define GPIO_PK00 (0x90)
#define PK00 GPIO_PK00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK00!
#endif
#ifdef __PK01_CN
#define GPIO_PK01 (0x91)
#define PK01 GPIO_PK01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK01!
#endif
#ifdef __PK02_CN
#define GPIO_PK02 (0x92)
#define PK02 GPIO_PK02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK02!
#endif
#ifdef __PK03_CN
#define GPIO_PK03 (0x93)
#define PK03 GPIO_PK03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK03!
#endif
#ifdef __PK04_CN
#define GPIO_PK04 (0x94)
#define PK04 GPIO_PK04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK04!
#endif
#ifdef __PK05_CN
#define GPIO_PK05 (0x95)
#define PK05 GPIO_PK05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK05!
#endif
#ifdef __PK06_CN
#define GPIO_PK06 (0x96)
#define PK06 GPIO_PK06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK06!
#endif
#ifdef __PK07_CN
#define GPIO_PK07 (0x97)
#define PK07 GPIO_PK07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PK07!
#endif

// PORT N
#ifdef __PN00_CN
#define GPIO_PN00 (0x98)
#define PN00 GPIO_PN00 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN00!
#endif
#ifdef __PN01_CN
#define GPIO_PN01 (0x99)
#define PN01 GPIO_PN01 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN01!
#endif
#ifdef __PN02_CN
#define GPIO_PN02 (0x9A)
#define PN02 GPIO_PN02 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN02!
#endif
#ifdef __PN03_CN
#define GPIO_PN03 (0x9B)
#define PN03 GPIO_PN03 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN03!
#endif
#ifdef __PN04_CN
#define GPIO_PN04 (0x9C)
#define PN04 GPIO_PN04 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN04!
#endif
#ifdef __PN05_CN
#define GPIO_PN05 (0x9D)
#define PN05 GPIO_PN05 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN05!
#endif
#ifdef __PN06_CN
#define GPIO_PN06 (0x9E)
#define PN06 GPIO_PN06 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN06!
#endif
#ifdef __PN07_CN
#define GPIO_PN07 (0x9F)
#define PN07 GPIO_PN07 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN07!
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

#ifdef __PORT_0_CN
#define GPIO_PORT_0 (0x00)
#define PORT_0 GPIO_PORT_0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_0!
#endif
#ifdef __PORT_1_CN
#define GPIO_PORT_1 (0x01)
#define PORT_1 GPIO_PORT_1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_1!
#endif
#ifdef __PORT_2_CN
#define GPIO_PORT_2 (0x02)
#define PORT_2 GPIO_PORT_2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_2!
#endif
#ifdef __PORT_3_CN
#define GPIO_PORT_3 (0x03)
#define PORT_3 GPIO_PORT_3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_3!
#endif
#ifdef __PORT_4_CN
#define GPIO_PORT_4 (0x04)
#define PORT_4 GPIO_PORT_4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_4!
#endif
#ifdef __PORT_5_CN
#define GPIO_PORT_5 (0x05)
#define PORT_5 GPIO_PORT_5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_5!
#endif
#ifdef __PORT_6_CN
#define GPIO_PORT_6 (0x06)
#define PORT_6 GPIO_PORT_6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_6!
#endif
#ifdef __PORT_7_CN
#define GPIO_PORT_7 (0x07)
#define PORT_7 GPIO_PORT_7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_7!
#endif
#ifdef __PORT_8_CN
#define GPIO_PORT_8 (0x08)
#define PORT_8 GPIO_PORT_8 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_8!
#endif
#ifdef __PORT_9_CN
#define GPIO_PORT_9 (0x09)
#define PORT_9 GPIO_PORT_9 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_9!
#endif
#ifdef __PORT_A_CN
#define GPIO_PORT_A (0x0A)
#define PORT_A GPIO_PORT_A // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_A!
#endif
#ifdef __PORT_B_CN
#define GPIO_PORT_B (0x0B)
#define PORT_B GPIO_PORT_B // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_B!
#endif
#ifdef __PORT_C_CN
#define GPIO_PORT_C (0x0C)
#define PORT_C GPIO_PORT_C // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_C!
#endif
#ifdef __PORT_D_CN
#define GPIO_PORT_D (0x0D)
#define PORT_D GPIO_PORT_D // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_D!
#endif
#ifdef __PORT_E_CN
#define GPIO_PORT_E (0x0E)
#define PORT_E GPIO_PORT_E // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_E!
#endif
#ifdef __PORT_F_CN
#define GPIO_PORT_F (0x0F)
#define PORT_F GPIO_PORT_F // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_F!
#endif
#ifdef __PORT_G_CN
#define GPIO_PORT_G (0x10)
#define PORT_G GPIO_PORT_G // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_G!
#endif
#ifdef __PORT_H_CN
#define GPIO_PORT_H (0x11)
#define PORT_H GPIO_PORT_H // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_H!
#endif
#ifdef __PORT_K_CN
#define GPIO_PORT_K (0x12)
#define PORT_K GPIO_PORT_K // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_K!
#endif
#ifdef __PORT_N_CN
#define GPIO_PORT_N (0x13)
#define PORT_N GPIO_PORT_N // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_N!
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
