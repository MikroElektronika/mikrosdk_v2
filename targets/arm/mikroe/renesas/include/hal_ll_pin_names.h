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

#ifdef __P000_CN
#define GPIO_P000 (0x00)
#define P000 GPIO_P000 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA0!
#endif
#ifdef __P001_CN
#define GPIO_P001 (0x01)
#define P001 GPIO_P001 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA1!
#endif
#ifdef __P002_CN
#define GPIO_P002 (0x02)
#define P002 GPIO_P002 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA2!
#endif
#ifdef __P003_CN
#define GPIO_P003 (0x03)
#define P003 GPIO_P003 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA3!
#endif
#ifdef __P004_CN
#define GPIO_P004 (0x04)
#define P004 GPIO_P004 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA4!
#endif
#ifdef __P005_CN
#define GPIO_P005 (0x05)
#define P005 GPIO_P005 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA5!
#endif
#ifdef __P006_CN
#define GPIO_P006 (0x06)
#define P006 GPIO_P006 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA6!
#endif
#ifdef __P007_CN
#define GPIO_P007 (0x07)
#define P007 GPIO_P007 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PA7!
#endif
#ifdef __P008_CN
#define GPIO_P008 (0x08)
#define P008 GPIO_P008 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB0!
#endif
#ifdef __P009_CN
#define GPIO_P009 (0x09)
#define P009 GPIO_P009 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB1!
#endif
#ifdef __P010_CN
#define GPIO_P010 (0x0A)
#define P010 GPIO_P010 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB2!
#endif
#ifdef __P011_CN
#define GPIO_P011 (0x0B)
#define P011 GPIO_P011 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB3!
#endif
#ifdef __P012_CN
#define GPIO_P012 (0x0C)
#define P012 GPIO_P012 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB4!
#endif
#ifdef __P013_CN
#define GPIO_P013 (0x0D)
#define P013 GPIO_P013 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB5!
#endif
#ifdef __P014_CN
#define GPIO_P014 (0x0E)
#define P014 GPIO_P014 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB6!
#endif
#ifdef __P015_CN
#define GPIO_P015 (0x0F)
#define P015 GPIO_P015 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PB7!
#endif

#ifdef __P100_CN
#define GPIO_P100 (0x10)
#define P100 GPIO_P100 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC0!
#endif
#ifdef __P101_CN
#define GPIO_P101 (0x11)
#define P101 GPIO_P101 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC1!
#endif
#ifdef __P102_CN
#define GPIO_P102 (0x12)
#define P102 GPIO_P102 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC2!
#endif
#ifdef __P103_CN
#define GPIO_P103 (0x13)
#define P103 GPIO_P103 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC3!
#endif
#ifdef __P104_CN
#define GPIO_P104 (0x14)
#define P104 GPIO_P104 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC4!
#endif
#ifdef __P105_CN
#define GPIO_P105 (0x15)
#define P105 GPIO_P105 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC5!
#endif
#ifdef __P106_CN
#define GPIO_P106 (0x16)
#define P106 GPIO_P106 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC6!
#endif
#ifdef __P107_CN
#define GPIO_P107 (0x17)
#define P107 GPIO_P107 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PC7!
#endif
#ifdef __P108_CN
#define GPIO_P108 (0x18)
#define P108 GPIO_P108 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD0!
#endif
#ifdef __P109_CN
#define GPIO_P109 (0x19)
#define P109 GPIO_P109 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD1!
#endif
#ifdef __P110_CN
#define GPIO_P110 (0x1A)
#define P110 GPIO_P110 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD2!
#endif
#ifdef __P111_CN
#define GPIO_P111 (0x1B)
#define P111 GPIO_P111 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD3!
#endif
#ifdef __P112_CN
#define GPIO_P112 (0x1C)
#define P112 GPIO_P112 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD4!
#endif
#ifdef __P113_CN
#define GPIO_P113 (0x1D)
#define P113 GPIO_P113 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD5!
#endif
#ifdef __P114_CN
#define GPIO_P114 (0x1E)
#define P114 GPIO_P114 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD6!
#endif
#ifdef __P115_CN
#define GPIO_P115 (0x1F)
#define P115 GPIO_P115 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PD7!
#endif

#ifdef __P200_CN
#define GPIO_P200 (0x20)
#define P200 GPIO_P200 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE0!
#endif
#ifdef __P201_CN
#define GPIO_P201 (0x21)
#define P201 GPIO_P201 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE1!
#endif
#ifdef __P202_CN
#define GPIO_P202 (0x22)
#define P202 GPIO_P202 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE2!
#endif
#ifdef __P203_CN
#define GPIO_P203 (0x23)
#define P203 GPIO_P203 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE3!
#endif
#ifdef __P204_CN
#define GPIO_P204 (0x24)
#define P204 GPIO_P204 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE4!
#endif
#ifdef __P205_CN
#define GPIO_P205 (0x25)
#define P205 GPIO_P205 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE5!
#endif
#ifdef __P206_CN
#define GPIO_P206 (0x26)
#define P206 GPIO_P206 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE6!
#endif
#ifdef __P207_CN
#define GPIO_P207 (0x27)
#define P207 GPIO_P207 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PE7!
#endif
#ifdef __P208_CN
#define GPIO_P208 (0x28)
#define P208 GPIO_P208 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF0!
#endif
#ifdef __P209_CN
#define GPIO_P209 (0x29)
#define P209 GPIO_P209 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF1!
#endif
#ifdef __P210_CN
#define GPIO_P210 (0x2A)
#define P210 GPIO_P210 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF2!
#endif
#ifdef __P211_CN
#define GPIO_P211 (0x2B)
#define P211 GPIO_P211 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF3!
#endif
#ifdef __P212_CN
#define GPIO_P212 (0x2C)
#define P212 GPIO_P212 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF4!
#endif
#ifdef __P213_CN
#define GPIO_P213 (0x2D)
#define P213 GPIO_P213 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF5!
#endif
#ifdef __P214_CN
#define GPIO_P214 (0x2E)
#define P214 GPIO_P214 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF6!
#endif
#ifdef __P215_CN
#define GPIO_P215 (0x2F)
#define P215 GPIO_P215 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PF7!
#endif

#ifdef __P300_CN
#define GPIO_P300 (0x30)
#define P300 GPIO_P300 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG0!
#endif
#ifdef __P301_CN
#define GPIO_P301 (0x31)
#define P301 GPIO_P301 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG1!
#endif
#ifdef __P302_CN
#define GPIO_P302 (0x32)
#define P302 GPIO_P302 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG2!
#endif
#ifdef __P303_CN
#define GPIO_P303 (0x33)
#define P303 GPIO_P303 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG3!
#endif
#ifdef __P304_CN
#define GPIO_P304 (0x34)
#define P304 GPIO_P304 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG4!
#endif
#ifdef __P305_CN
#define GPIO_P305 (0x35)
#define P305 GPIO_P305 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG5!
#endif
#ifdef __P306_CN
#define GPIO_P306 (0x36)
#define P306 GPIO_P306 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG6!
#endif
#ifdef __P307_CN
#define GPIO_P307 (0x37)
#define P307 GPIO_P307 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG7!
#endif
#ifdef __P308_CN
#define GPIO_P308 (0x38)
#define P308 GPIO_P308 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH0!
#endif
#ifdef __P309_CN
#define GPIO_P309 (0x39)
#define P309 GPIO_P309 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH1!
#endif
#ifdef __P310_CN
#define GPIO_P310 (0x3A)
#define P310 GPIO_P310 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH2!
#endif
#ifdef __P311_CN
#define GPIO_P311 (0x3B)
#define P311 GPIO_P311 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH3!
#endif
#ifdef __P312_CN
#define GPIO_P312 (0x3C)
#define P312 GPIO_P312 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH4!
#endif
#ifdef __P313_CN
#define GPIO_P313 (0x3D)
#define P313 GPIO_P313 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH5!
#endif
#ifdef __P314_CN
#define GPIO_P314 (0x3E)
#define P314 GPIO_P314 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH6!
#endif
#ifdef __P315_CN
#define GPIO_P315 (0x3F)
#define P315 GPIO_P315 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH7!
#endif

#ifdef __P400_CN
#define GPIO_P400 (0x40)
#define P400 GPIO_P400 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG0!
#endif
#ifdef __P401_CN
#define GPIO_P401 (0x41)
#define P401 GPIO_P401 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG1!
#endif
#ifdef __P402_CN
#define GPIO_P402 (0x42)
#define P402 GPIO_P402 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG2!
#endif
#ifdef __P403_CN
#define GPIO_P403 (0x43)
#define P403 GPIO_P403 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG3!
#endif
#ifdef __P404_CN
#define GPIO_P404 (0x44)
#define P404 GPIO_P404 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG4!
#endif
#ifdef __P405_CN
#define GPIO_P405 (0x45)
#define P405 GPIO_P405 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG5!
#endif
#ifdef __P406_CN
#define GPIO_P406 (0x46)
#define P406 GPIO_P406 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG6!
#endif
#ifdef __P407_CN
#define GPIO_P407 (0x47)
#define P407 GPIO_P407 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PG7!
#endif
#ifdef __P408_CN
#define GPIO_P408 (0x48)
#define P408 GPIO_P408 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH0!
#endif
#ifdef __P409_CN
#define GPIO_P409 (0x49)
#define P409 GPIO_P409 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH1!
#endif
#ifdef __P410_CN
#define GPIO_P410 (0x4A)
#define P410 GPIO_P410 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH2!
#endif
#ifdef __P411_CN
#define GPIO_P411 (0x4B)
#define P411 GPIO_P411 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH3!
#endif
#ifdef __P412_CN
#define GPIO_P412 (0x4C)
#define P412 GPIO_P412 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH4!
#endif
#ifdef __P413_CN
#define GPIO_P413 (0x4D)
#define P413 GPIO_P413 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH5!
#endif
#ifdef __P414_CN
#define GPIO_P414 (0x4E)
#define P414 GPIO_P414 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH6!
#endif
#ifdef __P415_CN
#define GPIO_P415 (0x4F)
#define P415 GPIO_P415 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PH7!
#endif

// TODO Esma ports 5-9
#ifdef __PL0_CN
#define GPIO_PL0 (0x50)
#define PL0 GPIO_PL0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL0!
#endif
#ifdef __PL1_CN
#define GPIO_PL1 (0x51)
#define PL1 GPIO_PL1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL1!
#endif
#ifdef __PL2_CN
#define GPIO_PL2 (0x52)
#define PL2 GPIO_PL2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL2!
#endif
#ifdef __PL3_CN
#define GPIO_PL3 (0x53)
#define PL3 GPIO_PL3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL3!
#endif
#ifdef __PL4_CN
#define GPIO_PL4 (0x54)
#define PL4 GPIO_PL4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL4!
#endif
#ifdef __PL5_CN
#define GPIO_PL5 (0x55)
#define PL5 GPIO_PL5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL5!
#endif
#ifdef __PL6_CN
#define GPIO_PL6 (0x56)
#define PL6 GPIO_PL6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL6!
#endif
#ifdef __PL7_CN
#define GPIO_PL7 (0x57)
#define PL7 GPIO_PL7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PL7!
#endif

#ifdef __PM0_CN
#define GPIO_PM0 (0x58)
#define PM0 GPIO_PM0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM0!
#endif
#ifdef __PM1_CN
#define GPIO_PM1 (0x59)
#define PM1 GPIO_PM1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM1!
#endif
#ifdef __PM2_CN
#define GPIO_PM2 (0x5A)
#define PM2 GPIO_PM2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM2!
#endif
#ifdef __PM3_CN
#define GPIO_PM3 (0x5B)
#define PM3 GPIO_PM3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM3!
#endif
#ifdef __PM4_CN
#define GPIO_PM4 (0x5C)
#define PM4 GPIO_PM4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM4!
#endif
#ifdef __PM5_CN
#define GPIO_PM5 (0x5D)
#define PM5 GPIO_PM5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM5!
#endif
#ifdef __PM6_CN
#define GPIO_PM6 (0x5E)
#define PM6 GPIO_PM6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM6!
#endif
#ifdef __PM7_CN
#define GPIO_PM7 (0x5F)
#define PM7 GPIO_PM7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PM7!
#endif

#ifdef __PN0_CN
#define GPIO_PN0 (0x60)
#define PN0 GPIO_PN0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN0!
#endif
#ifdef __PN1_CN
#define GPIO_PN1 (0x61)
#define PN1 GPIO_PN1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN1!
#endif
#ifdef __PN2_CN
#define GPIO_PN2 (0x62)
#define PN2 GPIO_PN2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN2!
#endif
#ifdef __PN3_CN
#define GPIO_PN3 (0x63)
#define PN3 GPIO_PN3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN3!
#endif
#ifdef __PN4_CN
#define GPIO_PN4 (0x64)
#define PN4 GPIO_PN4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN4!
#endif
#ifdef __PN5_CN
#define GPIO_PN5 (0x65)
#define PN5 GPIO_PN5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN5!
#endif
#ifdef __PN6_CN
#define GPIO_PN6 (0x66)
#define PN6 GPIO_PN6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN6!
#endif
#ifdef __PN7_CN
#define GPIO_PN7 (0x67)
#define PN7 GPIO_PN7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PN7!
#endif

#ifdef __PP0_CN
#define GPIO_PP0 (0x68)
#define PP0 GPIO_PP0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP0!
#endif
#ifdef __PP1_CN
#define GPIO_PP1 (0x69)
#define PP1 GPIO_PP1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP1!
#endif
#ifdef __PP2_CN
#define GPIO_PP2 (0x6A)
#define PP2 GPIO_PP2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP2!
#endif
#ifdef __PP3_CN
#define GPIO_PP3 (0x6B)
#define PP3 GPIO_PP3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP3!
#endif
#ifdef __PP4_CN
#define GPIO_PP4 (0x6C)
#define PP4 GPIO_PP4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP4!
#endif
#ifdef __PP5_CN
#define GPIO_PP5 (0x6D)
#define PP5 GPIO_PP5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP5!
#endif
#ifdef __PP6_CN
#define GPIO_PP6 (0x6E)
#define PP6 GPIO_PP6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP6!
#endif
#ifdef __PP7_CN
#define GPIO_PP7 (0x6F)
#define PP7 GPIO_PP7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PP7!
#endif

#ifdef __PQ0_CN
#define GPIO_PQ0 (0x70)
#define PQ0 GPIO_PQ0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ0!
#endif
#ifdef __PQ1_CN
#define GPIO_PQ1 (0x71)
#define PQ1 GPIO_PQ1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ1!
#endif
#ifdef __PQ2_CN
#define GPIO_PQ2 (0x72)
#define PQ2 GPIO_PQ2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ2!
#endif
#ifdef __PQ3_CN
#define GPIO_PQ3 (0x73)
#define PQ3 GPIO_PQ3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ3!
#endif
#ifdef __PQ4_CN
#define GPIO_PQ4 (0x74)
#define PQ4 GPIO_PQ4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ4!
#endif
#ifdef __PQ5_CN
#define GPIO_PQ5 (0x75)
#define PQ5 GPIO_PQ5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ5!
#endif
#ifdef __PQ6_CN
#define GPIO_PQ6 (0x76)
#define PQ6 GPIO_PQ6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ6!
#endif
#ifdef __PQ7_CN
#define GPIO_PQ7 (0x77)
#define PQ7 GPIO_PQ7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PQ7!
#endif

#ifdef __PR0_CN
#define GPIO_PR0 (0x78)
#define PR0 GPIO_PR0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR0!
#endif
#ifdef __PR1_CN
#define GPIO_PR1 (0x79)
#define PR1 GPIO_PR1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR1!
#endif
#ifdef __PR2_CN
#define GPIO_PR2 (0x7A)
#define PR2 GPIO_PR2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR2!
#endif
#ifdef __PR3_CN
#define GPIO_PR3 (0x7B)
#define PR3 GPIO_PR3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR3!
#endif
#ifdef __PR4_CN
#define GPIO_PR4 (0x7C)
#define PR4 GPIO_PR4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR4!
#endif
#ifdef __PR5_CN
#define GPIO_PR5 (0x7D)
#define PR5 GPIO_PR5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR5!
#endif
#ifdef __PR6_CN
#define GPIO_PR6 (0x7E)
#define PR6 GPIO_PR6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR6!
#endif
#ifdef __PR7_CN
#define GPIO_PR7 (0x7F)
#define PR7 GPIO_PR7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PR7!
#endif

#ifdef __PS0_CN
#define GPIO_PS0 (0x80)
#define PS0 GPIO_PS0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS0!
#endif
#ifdef __PS1_CN
#define GPIO_PS1 (0x81)
#define PS1 GPIO_PS1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS1!
#endif
#ifdef __PS2_CN
#define GPIO_PS2 (0x82)
#define PS2 GPIO_PS2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS2!
#endif
#ifdef __PS3_CN
#define GPIO_PS3 (0x83)
#define PS3 GPIO_PS3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS3!
#endif
#ifdef __PS4_CN
#define GPIO_PS4 (0x84)
#define PS4 GPIO_PS4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS4!
#endif
#ifdef __PS5_CN
#define GPIO_PS5 (0x85)
#define PS5 GPIO_PS5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS5!
#endif
#ifdef __PS6_CN
#define GPIO_PS6 (0x86)
#define PS6 GPIO_PS6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS6!
#endif
#ifdef __PS7_CN
#define GPIO_PS7 (0x87)
#define PS7 GPIO_PS7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PS7!
#endif

#ifdef __PT0_CN
#define GPIO_PT0 (0x88)
#define PT0 GPIO_PT0 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT0!
#endif
#ifdef __PT1_CN
#define GPIO_PT1 (0x89)
#define PT1 GPIO_PT1 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT1!
#endif
#ifdef __PT2_CN
#define GPIO_PT2 (0x8A)
#define PT2 GPIO_PT2 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT2!
#endif
#ifdef __PT3_CN
#define GPIO_PT3 (0x8B)
#define PT3 GPIO_PT3 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT3!
#endif
#ifdef __PT4_CN
#define GPIO_PT4 (0x8C)
#define PT4 GPIO_PT4 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT4!
#endif
#ifdef __PT5_CN
#define GPIO_PT5 (0x8D)
#define PT5 GPIO_PT5 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT5!
#endif
#ifdef __PT6_CN
#define GPIO_PT6 (0x8E)
#define PT6 GPIO_PT6 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT6!
#endif
#ifdef __PT7_CN
#define GPIO_PT7 (0x8F)
#define PT7 GPIO_PT7 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PT7!
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
#ifdef __PORT_10_CN
#define GPIO_PORT_10 (0x0A)
#define PORT_10 GPIO_PORT_10 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_10!
#endif
#ifdef __PORT_11_CN
#define GPIO_PORT_11 (0x0B)
#define PORT_11 GPIO_PORT_11 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_11!
#endif
#ifdef __PORT_12_CN
#define GPIO_PORT_12 (0x0C)
#define PORT_12 GPIO_PORT_12 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_12!
#endif
#ifdef __PORT_13_CN
#define GPIO_PORT_13 (0x0D)
#define PORT_13 GPIO_PORT_13 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_13!
#endif
#ifdef __PORT_14_CN
#define GPIO_PORT_14 (0x0E)
#define PORT_14 GPIO_PORT_14 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_14!
#endif
#ifdef __PORT_15_CN
#define GPIO_PORT_15 (0x0F)
#define PORT_15 GPIO_PORT_15 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_15!
#endif
#ifdef __PORT_16_CN
#define GPIO_PORT_16 (0x10)
#define PORT_16 GPIO_PORT_16 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_16!
#endif
#ifdef __PORT_17_CN
#define GPIO_PORT_17 (0x11)
#define PORT_17 GPIO_PORT_17 // Notice: Will be removed in one of the upcoming releases. Use GPIO_PORT_17!
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
