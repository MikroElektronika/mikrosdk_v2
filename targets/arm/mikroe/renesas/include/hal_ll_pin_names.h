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
#ifdef __P008_CN
#define GPIO_P008 (0x08)
#define P008 GPIO_P008 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P008!
#endif
#ifdef __P009_CN
#define GPIO_P009 (0x09)
#define P009 GPIO_P009 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P009!
#endif
#ifdef __P010_CN
#define GPIO_P010 (0x0A)
#define P010 GPIO_P010 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P010!
#endif
#ifdef __P011_CN
#define GPIO_P011 (0x0B)
#define P011 GPIO_P011 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P011!
#endif
#ifdef __P012_CN
#define GPIO_P012 (0x0C)
#define P012 GPIO_P012 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P012!
#endif
#ifdef __P013_CN
#define GPIO_P013 (0x0D)
#define P013 GPIO_P013 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P013!
#endif
#ifdef __P014_CN
#define GPIO_P014 (0x0E)
#define P014 GPIO_P014 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P014!
#endif
#ifdef __P015_CN
#define GPIO_P015 (0x0F)
#define P015 GPIO_P015 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P015!
#endif

// PORT 1
#ifdef __P100_CN
#define GPIO_P100 (0x10)
#define P100 GPIO_P100 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P100!
#endif
#ifdef __P101_CN
#define GPIO_P101 (0x11)
#define P101 GPIO_P101 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P101!
#endif
#ifdef __P102_CN
#define GPIO_P102 (0x12)
#define P102 GPIO_P102 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P102!
#endif
#ifdef __P103_CN
#define GPIO_P103 (0x13)
#define P103 GPIO_P103 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P103!
#endif
#ifdef __P104_CN
#define GPIO_P104 (0x14)
#define P104 GPIO_P104 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P104!
#endif
#ifdef __P105_CN
#define GPIO_P105 (0x15)
#define P105 GPIO_P105 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P105!
#endif
#ifdef __P106_CN
#define GPIO_P106 (0x16)
#define P106 GPIO_P106 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P106!
#endif
#ifdef __P107_CN
#define GPIO_P107 (0x17)
#define P107 GPIO_P107 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P107!
#endif
#ifdef __P108_CN
#define GPIO_P108 (0x18)
#define P108 GPIO_P108 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P108!
#endif
#ifdef __P109_CN
#define GPIO_P109 (0x19)
#define P109 GPIO_P109 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P109!
#endif
#ifdef __P110_CN
#define GPIO_P110 (0x1A)
#define P110 GPIO_P110 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P110!
#endif
#ifdef __P111_CN
#define GPIO_P111 (0x1B)
#define P111 GPIO_P111 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P111!
#endif
#ifdef __P112_CN
#define GPIO_P112 (0x1C)
#define P112 GPIO_P112 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P112!
#endif
#ifdef __P113_CN
#define GPIO_P113 (0x1D)
#define P113 GPIO_P113 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P113!
#endif
#ifdef __P114_CN
#define GPIO_P114 (0x1E)
#define P114 GPIO_P114 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P114!
#endif
#ifdef __P115_CN
#define GPIO_P115 (0x1F)
#define P115 GPIO_P115 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P115!
#endif

// PORT 2
#ifdef __P200_CN
#define GPIO_P200 (0x20)
#define P200 GPIO_P200 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P200!
#endif
#ifdef __P201_CN
#define GPIO_P201 (0x21)
#define P201 GPIO_P201 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P201!
#endif
#ifdef __P202_CN
#define GPIO_P202 (0x22)
#define P202 GPIO_P202 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P202!
#endif
#ifdef __P203_CN
#define GPIO_P203 (0x23)
#define P203 GPIO_P203 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P203!
#endif
#ifdef __P204_CN
#define GPIO_P204 (0x24)
#define P204 GPIO_P204 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P204!
#endif
#ifdef __P205_CN
#define GPIO_P205 (0x25)
#define P205 GPIO_P205 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P205!
#endif
#ifdef __P206_CN
#define GPIO_P206 (0x26)
#define P206 GPIO_P206 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P206!
#endif
#ifdef __P207_CN
#define GPIO_P207 (0x27)
#define P207 GPIO_P207 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P207!
#endif
#ifdef __P208_CN
#define GPIO_P208 (0x28)
#define P208 GPIO_P208 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P208!
#endif
#ifdef __P209_CN
#define GPIO_P209 (0x29)
#define P209 GPIO_P209 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P209!
#endif
#ifdef __P210_CN
#define GPIO_P210 (0x2A)
#define P210 GPIO_P210 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P210!
#endif
#ifdef __P211_CN
#define GPIO_P211 (0x2B)
#define P211 GPIO_P211 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P211!
#endif
#ifdef __P212_CN
#define GPIO_P212 (0x2C)
#define P212 GPIO_P212 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P212!
#endif
#ifdef __P213_CN
#define GPIO_P213 (0x2D)
#define P213 GPIO_P213 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P213!
#endif
#ifdef __P214_CN
#define GPIO_P214 (0x2E)
#define P214 GPIO_P214 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P214!
#endif
#ifdef __P215_CN
#define GPIO_P215 (0x2F)
#define P215 GPIO_P215 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P215!
#endif

// PORT 3
#ifdef __P300_CN
#define GPIO_P300 (0x30)
#define P300 GPIO_P300 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P300!
#endif
#ifdef __P301_CN
#define GPIO_P301 (0x31)
#define P301 GPIO_P301 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P301!
#endif
#ifdef __P302_CN
#define GPIO_P302 (0x32)
#define P302 GPIO_P302 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P302!
#endif
#ifdef __P303_CN
#define GPIO_P303 (0x33)
#define P303 GPIO_P303 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P303!
#endif
#ifdef __P304_CN
#define GPIO_P304 (0x34)
#define P304 GPIO_P304 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P304!
#endif
#ifdef __P305_CN
#define GPIO_P305 (0x35)
#define P305 GPIO_P305 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P305!
#endif
#ifdef __P306_CN
#define GPIO_P306 (0x36)
#define P306 GPIO_P306 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P306!
#endif
#ifdef __P307_CN
#define GPIO_P307 (0x37)
#define P307 GPIO_P307 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P307!
#endif
#ifdef __P308_CN
#define GPIO_P308 (0x38)
#define P308 GPIO_P308 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P308!
#endif
#ifdef __P309_CN
#define GPIO_P309 (0x39)
#define P309 GPIO_P309 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P309!
#endif
#ifdef __P310_CN
#define GPIO_P310 (0x3A)
#define P310 GPIO_P310 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P310!
#endif
#ifdef __P311_CN
#define GPIO_P311 (0x3B)
#define P311 GPIO_P311 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P311!
#endif
#ifdef __P312_CN
#define GPIO_P312 (0x3C)
#define P312 GPIO_P312 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P312!
#endif
#ifdef __P313_CN
#define GPIO_P313 (0x3D)
#define P313 GPIO_P313 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P313!
#endif
#ifdef __P314_CN
#define GPIO_P314 (0x3E)
#define P314 GPIO_P314 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P314!
#endif
#ifdef __P315_CN
#define GPIO_P315 (0x3F)
#define P315 GPIO_P315 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P315!
#endif

// PORT 4
#ifdef __P400_CN
#define GPIO_P400 (0x40)
#define P400 GPIO_P400 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P400!
#endif
#ifdef __P401_CN
#define GPIO_P401 (0x41)
#define P401 GPIO_P401 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P401!
#endif
#ifdef __P402_CN
#define GPIO_P402 (0x42)
#define P402 GPIO_P402 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P402!
#endif
#ifdef __P403_CN
#define GPIO_P403 (0x43)
#define P403 GPIO_P403 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P403!
#endif
#ifdef __P404_CN
#define GPIO_P404 (0x44)
#define P404 GPIO_P404 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P404!
#endif
#ifdef __P405_CN
#define GPIO_P405 (0x45)
#define P405 GPIO_P405 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P405!
#endif
#ifdef __P406_CN
#define GPIO_P406 (0x46)
#define P406 GPIO_P406 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P406!
#endif
#ifdef __P407_CN
#define GPIO_P407 (0x47)
#define P407 GPIO_P407 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P407!
#endif
#ifdef __P408_CN
#define GPIO_P408 (0x48)
#define P408 GPIO_P408 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P408!
#endif
#ifdef __P409_CN
#define GPIO_P409 (0x49)
#define P409 GPIO_P409 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P409!
#endif
#ifdef __P410_CN
#define GPIO_P410 (0x4A)
#define P410 GPIO_P410 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P410!
#endif
#ifdef __P411_CN
#define GPIO_P411 (0x4B)
#define P411 GPIO_P411 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P411!
#endif
#ifdef __P412_CN
#define GPIO_P412 (0x4C)
#define P412 GPIO_P412 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P412!
#endif
#ifdef __P413_CN
#define GPIO_P413 (0x4D)
#define P413 GPIO_P413 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P413!
#endif
#ifdef __P414_CN
#define GPIO_P414 (0x4E)
#define P414 GPIO_P414 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P414!
#endif
#ifdef __P415_CN
#define GPIO_P415 (0x4F)
#define P415 GPIO_P415 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P415!
#endif

// PORT 5
#ifdef __P500_CN
#define GPIO_P500 (0x50)
#define P500 GPIO_P500 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P500!
#endif
#ifdef __P501_CN
#define GPIO_P501 (0x51)
#define P501 GPIO_P501 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P501!
#endif
#ifdef __P502_CN
#define GPIO_P502 (0x52)
#define P502 GPIO_P502 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P502!
#endif
#ifdef __P503_CN
#define GPIO_P503 (0x53)
#define P503 GPIO_P503 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P503!
#endif
#ifdef __P504_CN
#define GPIO_P504 (0x54)
#define P504 GPIO_P504 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P504!
#endif
#ifdef __P505_CN
#define GPIO_P505 (0x55)
#define P505 GPIO_P505 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P505!
#endif
#ifdef __P506_CN
#define GPIO_P506 (0x56)
#define P506 GPIO_P506 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P506!
#endif
#ifdef __P507_CN
#define GPIO_P507 (0x57)
#define P507 GPIO_P507 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P507!
#endif
#ifdef __P508_CN
#define GPIO_P508 (0x58)
#define P508 GPIO_P508 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P508!
#endif
#ifdef __P509_CN
#define GPIO_P509 (0x59)
#define P509 GPIO_P509 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P509!
#endif
#ifdef __P510_CN
#define GPIO_P510(0x5A)
#define P510 GPIO_P510 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P510!
#endif
#ifdef __P511_CN
#define GPIO_P511(0x5B)
#define P511 GPIO_P511 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P511!
#endif
#ifdef __P512_CN
#define GPIO_P512(0x5C)
#define P512 GPIO_P512 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P512!
#endif
#ifdef __P513_CN
#define GPIO_P513(0x5D)
#define P513 GPIO_P513 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P513!
#endif
#ifdef __P514_CN
#define GPIO_P514(0x5E)
#define P514 GPIO_P514 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P514!
#endif
#ifdef __P515_CN
#define GPIO_P515(0x5F)
#define P515 GPIO_P515 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P515!
#endif

// PORT 6
#ifdef __P600_CN
#define GPIO_P600 (0x60)
#define P600 GPIO_P600 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P600!
#endif
#ifdef __P601_CN
#define GPIO_P601 (0x61)
#define P601 GPIO_P601 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P601!
#endif
#ifdef __P602_CN
#define GPIO_P602 (0x62)
#define P602 GPIO_P602 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P602!
#endif
#ifdef __P603_CN
#define GPIO_P603 (0x63)
#define P603 GPIO_P603 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P603!
#endif
#ifdef __P604_CN
#define GPIO_P604 (0x64)
#define P604 GPIO_P604 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P604!
#endif
#ifdef __P605_CN
#define GPIO_P605 (0x65)
#define P605 GPIO_P605 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P605!
#endif
#ifdef __P606_CN
#define GPIO_P606 (0x66)
#define P606 GPIO_P606 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P606!
#endif
#ifdef __P607_CN
#define GPIO_P607 (0x67)
#define P607 GPIO_P607 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P607!
#endif
#ifdef __P608_CN
#define GPIO_P608 (0x68)
#define P608 GPIO_P608 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P608!
#endif
#ifdef __P609_CN
#define GPIO_P609 (0x69)
#define P609 GPIO_P609 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P609!
#endif
#ifdef __P610_CN
#define GPIO_P610 (0x6A)
#define P610 GPIO_P610 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P610!
#endif
#ifdef __P611_CN
#define GPIO_P611 (0x6B)
#define P611 GPIO_P611 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P611!
#endif
#ifdef __P612_CN
#define GPIO_P612 (0x6C)
#define P612 GPIO_P612 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P612!
#endif
#ifdef __P613_CN
#define GPIO_P613 (0x6D)
#define P613 GPIO_P613 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P613!
#endif
#ifdef __P614_CN
#define GPIO_P614 (0x6E)
#define P614 GPIO_P614 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P614!
#endif
#ifdef __P615_CN
#define GPIO_P615 (0x6F)
#define P615 GPIO_P615 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P615!
#endif

// PORT 7
#ifdef __P700_CN
#define GPIO_P700 (0x70)
#define P700 GPIO_P700 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P700!
#endif
#ifdef __P701_CN
#define GPIO_P701 (0x71)
#define P701 GPIO_P701 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P701!
#endif
#ifdef __P702_CN
#define GPIO_P702 (0x72)
#define P702 GPIO_P702 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P702!
#endif
#ifdef __P703_CN
#define GPIO_P703 (0x73)
#define P703 GPIO_P703 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P703!
#endif
#ifdef __P704_CN
#define GPIO_P704 (0x74)
#define P704 GPIO_P704 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P704!
#endif
#ifdef __P705_CN
#define GPIO_P705 (0x75)
#define P705 GPIO_P705 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P705!
#endif
#ifdef __P706_CN
#define GPIO_P706 (0x76)
#define P706 GPIO_P706 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P706!
#endif
#ifdef __P707_CN
#define GPIO_P707 (0x77)
#define P707 GPIO_P707 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P707!
#endif
#ifdef __P708_CN
#define GPIO_P708 (0x78)
#define P708 GPIO_P708 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P708!
#endif
#ifdef __P709_CN
#define GPIO_P709 (0x79)
#define P709 GPIO_P709 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P709!
#endif
#ifdef __P710_CN
#define GPIO_P710 (0x7A)
#define P710 GPIO_P710 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P710!
#endif
#ifdef __P711_CN
#define GPIO_P711 (0x7B)
#define P711 GPIO_P711 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P711!
#endif
#ifdef __P712_CN
#define GPIO_P712 (0x7C)
#define P712 GPIO_P712 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P712!
#endif
#ifdef __P713_CN
#define GPIO_P713 (0x7D)
#define P713 GPIO_P713 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P713!
#endif
#ifdef __P714_CN
#define GPIO_P714 (0x7E)
#define P714 GPIO_P714 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P714!
#endif
#ifdef __P715_CN
#define GPIO_P715 (0x7F)
#define P715 GPIO_P715 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P715!
#endif

// PORT 8
#ifdef __P800_CN
#define GPIO_P800 (0x80)
#define P800 GPIO_P800 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P800!
#endif
#ifdef __P801_CN
#define GPIO_P801 (0x81)
#define P801 GPIO_P801 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P801!
#endif
#ifdef __P802_CN
#define GPIO_P802 (0x82)
#define P802 GPIO_P802 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P802!
#endif
#ifdef __P803_CN
#define GPIO_P803 (0x83)
#define P803 GPIO_P803 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P803!
#endif
#ifdef __P804_CN
#define GPIO_P804 (0x84)
#define P804 GPIO_P804 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P804!
#endif
#ifdef __P805_CN
#define GPIO_P805 (0x85)
#define P805 GPIO_P805 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P805!
#endif
#ifdef __P806_CN
#define GPIO_P806 (0x86)
#define P806 GPIO_P806 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P806!
#endif
#ifdef __P807_CN
#define GPIO_P807 (0x87)
#define P807 GPIO_P807 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P807!
#endif
#ifdef __P808_CN
#define GPIO_P808 (0x88)
#define P808 GPIO_P808 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P808!
#endif
#ifdef __P809_CN
#define GPIO_P809 (0x89)
#define P809 GPIO_P809 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P809!
#endif
#ifdef __P810_CN
#define GPIO_P810 (0x8A)
#define P810 GPIO_P810 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P810!
#endif
#ifdef __P811_CN
#define GPIO_P811 (0x8B)
#define P811 GPIO_P811 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P811!
#endif
#ifdef __P812_CN
#define GPIO_P812 (0x8C)
#define P812 GPIO_P812 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P812!
#endif
#ifdef __P813_CN
#define GPIO_P813 (0x8D)
#define P813 GPIO_P813 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P813!
#endif
#ifdef __P814_CN
#define GPIO_P814 (0x8E)
#define P814 GPIO_P814 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P814!
#endif
#ifdef __P815_CN
#define GPIO_P815 (0x8F)
#define P815 GPIO_P815 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P815!
#endif

// PORT 9
#ifdef __P900_CN
#define GPIO_P900 (0x90)
#define P900 GPIO_P900 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P900!
#endif
#ifdef __P901_CN
#define GPIO_P901 (0x91)
#define P901 GPIO_P901 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P901!
#endif
#ifdef __P902_CN
#define GPIO_P902 (0x92)
#define P902 GPIO_P902 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P902!
#endif
#ifdef __P903_CN
#define GPIO_P903 (0x93)
#define P903 GPIO_P903 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P903!
#endif
#ifdef __P904_CN
#define GPIO_P904 (0x94)
#define P904 GPIO_P904 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P904!
#endif
#ifdef __P905_CN
#define GPIO_P905 (0x95)
#define P905 GPIO_P905 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P905!
#endif
#ifdef __P906_CN
#define GPIO_P906 (0x96)
#define P906 GPIO_P906 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P906!
#endif
#ifdef __P907_CN
#define GPIO_P907 (0x97)
#define P907 GPIO_P907 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P907!
#endif
#ifdef __P908_CN
#define GPIO_P908 (0x98)
#define P908 GPIO_P908 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P908!
#endif
#ifdef __P909_CN
#define GPIO_P909 (0x99)
#define P909 GPIO_P909 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P909!
#endif
#ifdef __P910_CN
#define GPIO_P910 (0x9A)
#define P910 GPIO_P910 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P910!
#endif
#ifdef __P911_CN
#define GPIO_P911 (0x9B)
#define P911 GPIO_P911 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P911!
#endif
#ifdef __P912_CN
#define GPIO_P912 (0x9C)
#define P912 GPIO_P912 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P912!
#endif
#ifdef __P913_CN
#define GPIO_P913 (0x9D)
#define P913 GPIO_P913 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P913!
#endif
#ifdef __P914_CN
#define GPIO_P914 (0x9E)
#define P914 GPIO_P914 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P914!
#endif
#ifdef __P915_CN
#define GPIO_P915 (0x9F)
#define P915 GPIO_P915 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P915!
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
#define GPIO_PIN_10 (0x10)
#define PIN_10 GPIO_PIN_10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_10!
#define GPIO_PIN_11 (0x11)
#define PIN_11 GPIO_PIN_11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_11!
#define GPIO_PIN_12 (0x12)
#define PIN_12 GPIO_PIN_12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_12!
#define GPIO_PIN_13 (0x13)
#define PIN_13 GPIO_PIN_13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_13!
#define GPIO_PIN_14 (0x14)
#define PIN_14 GPIO_PIN_14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_14!
#define GPIO_PIN_15 (0x15)
#define PIN_15 GPIO_PIN_15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PIN_15!

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

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
