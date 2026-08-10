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

#ifdef __cplusplus
}
#endif

#endif // _HAL_PIN_NAMES_H_
// ------------------------------------------------------------------------- END
