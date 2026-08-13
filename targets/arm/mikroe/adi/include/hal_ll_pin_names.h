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
#ifdef __P016_CN
#define GPIO_P016 (0x10)
#define P016 GPIO_P016 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P016!
#endif
#ifdef __P017_CN
#define GPIO_P017 (0x11)
#define P017 GPIO_P017 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P017!
#endif
#ifdef __P018_CN
#define GPIO_P018 (0x12)
#define P018 GPIO_P018 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P018!
#endif
#ifdef __P019_CN
#define GPIO_P019 (0x13)
#define P019 GPIO_P019 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P019!
#endif
#ifdef __P020_CN
#define GPIO_P020 (0x14)
#define P020 GPIO_P020 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P020!
#endif
#ifdef __P021_CN
#define GPIO_P021 (0x15)
#define P021 GPIO_P021 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P021!
#endif
#ifdef __P022_CN
#define GPIO_P022 (0x16)
#define P022 GPIO_P022 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P022!
#endif
#ifdef __P023_CN
#define GPIO_P023 (0x17)
#define P023 GPIO_P023 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P023!
#endif
#ifdef __P024_CN
#define GPIO_P024 (0x18)
#define P024 GPIO_P024 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P024!
#endif
#ifdef __P025_CN
#define GPIO_P025 (0x19)
#define P025 GPIO_P025 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P025!
#endif
#ifdef __P026_CN
#define GPIO_P026 (0x1A)
#define P026 GPIO_P026 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P026!
#endif
#ifdef __P027_CN
#define GPIO_P027 (0x1B)
#define P027 GPIO_P027 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P027!
#endif
#ifdef __P028_CN
#define GPIO_P028 (0x1C)
#define P028 GPIO_P028 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P028!
#endif
#ifdef __P029_CN
#define GPIO_P029 (0x1D)
#define P029 GPIO_P029 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P029!
#endif
#ifdef __P030_CN
#define GPIO_P030 (0x1E)
#define P030 GPIO_P030 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P030!
#endif
#ifdef __P031_CN
#define GPIO_P031 (0x1F)
#define P031 GPIO_P031 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P031!
#endif

// PORT 1
#ifdef __P100_CN
#define GPIO_P100 (0x20)
#define P100 GPIO_P100 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P100!
#endif
#ifdef __P101_CN
#define GPIO_P101 (0x21)
#define P101 GPIO_P101 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P101!
#endif
#ifdef __P102_CN
#define GPIO_P102 (0x22)
#define P102 GPIO_P102 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P102!
#endif
#ifdef __P103_CN
#define GPIO_P103 (0x23)
#define P103 GPIO_P103 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P103!
#endif
#ifdef __P104_CN
#define GPIO_P104 (0x24)
#define P104 GPIO_P104 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P104!
#endif
#ifdef __P105_CN
#define GPIO_P105 (0x25)
#define P105 GPIO_P105 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P105!
#endif
#ifdef __P106_CN
#define GPIO_P106 (0x26)
#define P106 GPIO_P106 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P106!
#endif
#ifdef __P107_CN
#define GPIO_P107 (0x27)
#define P107 GPIO_P107 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P107!
#endif
#ifdef __P108_CN
#define GPIO_P108 (0x28)
#define P108 GPIO_P108 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P108!
#endif
#ifdef __P109_CN
#define GPIO_P109 (0x29)
#define P109 GPIO_P109 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P109!
#endif
#ifdef __P110_CN
#define GPIO_P110 (0x2A)
#define P110 GPIO_P110 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P110!
#endif
#ifdef __P111_CN
#define GPIO_P111 (0x2B)
#define P111 GPIO_P111 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P111!
#endif
#ifdef __P112_CN
#define GPIO_P112 (0x2C)
#define P112 GPIO_P112 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P112!
#endif
#ifdef __P113_CN
#define GPIO_P113 (0x2D)
#define P113 GPIO_P113 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P113!
#endif
#ifdef __P114_CN
#define GPIO_P114 (0x2E)
#define P114 GPIO_P114 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P114!
#endif
#ifdef __P115_CN
#define GPIO_P115 (0x2F)
#define P115 GPIO_P115 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P115!
#endif
#ifdef __P116_CN
#define GPIO_P116 (0x30)
#define P116 GPIO_P116 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P116!
#endif
#ifdef __P117_CN
#define GPIO_P117 (0x31)
#define P117 GPIO_P117 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P117!
#endif
#ifdef __P118_CN
#define GPIO_P118 (0x32)
#define P118 GPIO_P118 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P118!
#endif
#ifdef __P119_CN
#define GPIO_P119 (0x33)
#define P119 GPIO_P119 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P119!
#endif
#ifdef __P120_CN
#define GPIO_P120 (0x34)
#define P120 GPIO_P120 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P120!
#endif
#ifdef __P121_CN
#define GPIO_P121 (0x35)
#define P121 GPIO_P121 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P121!
#endif
#ifdef __P122_CN
#define GPIO_P122 (0x36)
#define P122 GPIO_P122 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P122!
#endif
#ifdef __P123_CN
#define GPIO_P123 (0x37)
#define P123 GPIO_P123 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P123!
#endif
#ifdef __P124_CN
#define GPIO_P124 (0x38)
#define P124 GPIO_P124 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P124!
#endif
#ifdef __P125_CN
#define GPIO_P125 (0x39)
#define P125 GPIO_P125 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P125!
#endif
#ifdef __P126_CN
#define GPIO_P126 (0x3A)
#define P126 GPIO_P126 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P126!
#endif
#ifdef __P127_CN
#define GPIO_P127 (0x3B)
#define P127 GPIO_P127 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P127!
#endif
#ifdef __P128_CN
#define GPIO_P128 (0x3C)
#define P128 GPIO_P128 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P128!
#endif
#ifdef __P129_CN
#define GPIO_P129 (0x3D)
#define P129 GPIO_P129 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P129!
#endif
#ifdef __P130_CN
#define GPIO_P130 (0x3E)
#define P130 GPIO_P130 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P130!
#endif
#ifdef __P131_CN
#define GPIO_P131 (0x3F)
#define P131 GPIO_P131 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P131!
#endif

// PORT 2
#ifdef __P200_CN
#define GPIO_P200 (0x40)
#define P200 GPIO_P200 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P200!
#endif
#ifdef __P201_CN
#define GPIO_P201 (0x41)
#define P201 GPIO_P201 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P201!
#endif
#ifdef __P202_CN
#define GPIO_P202 (0x42)
#define P202 GPIO_P202 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P202!
#endif
#ifdef __P203_CN
#define GPIO_P203 (0x43)
#define P203 GPIO_P203 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P203!
#endif
#ifdef __P204_CN
#define GPIO_P204 (0x44)
#define P204 GPIO_P204 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P204!
#endif
#ifdef __P205_CN
#define GPIO_P205 (0x45)
#define P205 GPIO_P205 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P205!
#endif
#ifdef __P206_CN
#define GPIO_P206 (0x46)
#define P206 GPIO_P206 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P206!
#endif
#ifdef __P207_CN
#define GPIO_P207 (0x47)
#define P207 GPIO_P207 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P207!
#endif
#ifdef __P208_CN
#define GPIO_P208 (0x48)
#define P208 GPIO_P208 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P208!
#endif
#ifdef __P209_CN
#define GPIO_P209 (0x49)
#define P209 GPIO_P209 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P209!
#endif
#ifdef __P210_CN
#define GPIO_P210 (0x4A)
#define P210 GPIO_P210 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P210!
#endif
#ifdef __P211_CN
#define GPIO_P211 (0x4B)
#define P211 GPIO_P211 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P211!
#endif
#ifdef __P212_CN
#define GPIO_P212 (0x4C)
#define P212 GPIO_P212 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P212!
#endif
#ifdef __P213_CN
#define GPIO_P213 (0x4D)
#define P213 GPIO_P213 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P213!
#endif
#ifdef __P214_CN
#define GPIO_P214 (0x4E)
#define P214 GPIO_P214 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P214!
#endif
#ifdef __P215_CN
#define GPIO_P215 (0x4F)
#define P215 GPIO_P215 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P215!
#endif
#ifdef __P216_CN
#define GPIO_P216 (0x50)
#define P216 GPIO_P216 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P216!
#endif
#ifdef __P217_CN
#define GPIO_P217 (0x51)
#define P217 GPIO_P217 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P217!
#endif
#ifdef __P218_CN
#define GPIO_P218 (0x52)
#define P218 GPIO_P218 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P218!
#endif
#ifdef __P219_CN
#define GPIO_P219 (0x53)
#define P219 GPIO_P219 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P219!
#endif
#ifdef __P220_CN
#define GPIO_P220 (0x54)
#define P220 GPIO_P220 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P220!
#endif
#ifdef __P221_CN
#define GPIO_P221 (0x55)
#define P221 GPIO_P221 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P221!
#endif
#ifdef __P222_CN
#define GPIO_P222 (0x56)
#define P222 GPIO_P222 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P222!
#endif
#ifdef __P223_CN
#define GPIO_P223 (0x57)
#define P223 GPIO_P223 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P223!
#endif
#ifdef __P224_CN
#define GPIO_P224 (0x58)
#define P224 GPIO_P224 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P224!
#endif
#ifdef __P225_CN
#define GPIO_P225 (0x59)
#define P225 GPIO_P225 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P225!
#endif
#ifdef __P226_CN
#define GPIO_P226 (0x5A)
#define P226 GPIO_P226 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P226!
#endif
#ifdef __P227_CN
#define GPIO_P227 (0x5B)
#define P227 GPIO_P227 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P227!
#endif
#ifdef __P228_CN
#define GPIO_P228 (0x5C)
#define P228 GPIO_P228 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P228!
#endif
#ifdef __P229_CN
#define GPIO_P229 (0x5D)
#define P229 GPIO_P229 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P229!
#endif
#ifdef __P230_CN
#define GPIO_P230 (0x5E)
#define P230 GPIO_P230 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P230!
#endif
#ifdef __P231_CN
#define GPIO_P231 (0x5F)
#define P231 GPIO_P231 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P231!
#endif

// PORT 3
#ifdef __P300_CN
#define GPIO_P300 (0x60)
#define P300 GPIO_P300 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P300!
#endif
#ifdef __P301_CN
#define GPIO_P301 (0x61)
#define P301 GPIO_P301 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P301!
#endif
#ifdef __P302_CN
#define GPIO_P302 (0x62)
#define P302 GPIO_P302 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P302!
#endif
#ifdef __P303_CN
#define GPIO_P303 (0x63)
#define P303 GPIO_P303 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P303!
#endif
#ifdef __P304_CN
#define GPIO_P304 (0x64)
#define P304 GPIO_P304 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P304!
#endif
#ifdef __P305_CN
#define GPIO_P305 (0x65)
#define P305 GPIO_P305 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P305!
#endif
#ifdef __P306_CN
#define GPIO_P306 (0x66)
#define P306 GPIO_P306 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P306!
#endif
#ifdef __P307_CN
#define GPIO_P307 (0x67)
#define P307 GPIO_P307 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P307!
#endif
#ifdef __P308_CN
#define GPIO_P308 (0x68)
#define P308 GPIO_P308 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P308!
#endif
#ifdef __P309_CN
#define GPIO_P309 (0x69)
#define P309 GPIO_P309 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P309!
#endif
#ifdef __P310_CN
#define GPIO_P310 (0x6A)
#define P310 GPIO_P310 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P310!
#endif
#ifdef __P311_CN
#define GPIO_P311 (0x6B)
#define P311 GPIO_P311 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P311!
#endif
#ifdef __P312_CN
#define GPIO_P312 (0x6C)
#define P312 GPIO_P312 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P312!
#endif
#ifdef __P313_CN
#define GPIO_P313 (0x6D)
#define P313 GPIO_P313 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P313!
#endif
#ifdef __P314_CN
#define GPIO_P314 (0x6E)
#define P314 GPIO_P314 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P314!
#endif
#ifdef __P315_CN
#define GPIO_P315 (0x6F)
#define P315 GPIO_P315 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P315!
#endif
#ifdef __P316_CN
#define GPIO_P316 (0x70)
#define P316 GPIO_P316 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P316!
#endif
#ifdef __P317_CN
#define GPIO_P317 (0x71)
#define P317 GPIO_P317 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P317!
#endif
#ifdef __P318_CN
#define GPIO_P318 (0x72)
#define P318 GPIO_P318 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P318!
#endif
#ifdef __P319_CN
#define GPIO_P319 (0x73)
#define P319 GPIO_P319 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P319!
#endif
#ifdef __P320_CN
#define GPIO_P320 (0x74)
#define P320 GPIO_P320 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P320!
#endif
#ifdef __P321_CN
#define GPIO_P321 (0x75)
#define P321 GPIO_P321 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P321!
#endif
#ifdef __P322_CN
#define GPIO_P322 (0x76)
#define P322 GPIO_P322 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P322!
#endif
#ifdef __P323_CN
#define GPIO_P323 (0x77)
#define P323 GPIO_P323 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P323!
#endif
#ifdef __P324_CN
#define GPIO_P324 (0x78)
#define P324 GPIO_P324 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P324!
#endif
#ifdef __P325_CN
#define GPIO_P325 (0x79)
#define P325 GPIO_P325 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P325!
#endif
#ifdef __P326_CN
#define GPIO_P326 (0x7A)
#define P326 GPIO_P326 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P326!
#endif
#ifdef __P327_CN
#define GPIO_P327 (0x7B)
#define P327 GPIO_P327 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P327!
#endif
#ifdef __P328_CN
#define GPIO_P328 (0x7C)
#define P328 GPIO_P328 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P328!
#endif
#ifdef __P329_CN
#define GPIO_P329 (0x7D)
#define P329 GPIO_P329 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P329!
#endif
#ifdef __P330_CN
#define GPIO_P330 (0x7E)
#define P330 GPIO_P330 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P330!
#endif
#ifdef __P331_CN
#define GPIO_P331 (0x7F)
#define P331 GPIO_P331 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P331!
#endif

// PORT 4
#ifdef __P400_CN
#define GPIO_P400 (0x80)
#define P400 GPIO_P400 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P400!
#endif
#ifdef __P401_CN
#define GPIO_P401 (0x81)
#define P401 GPIO_P401 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P401!
#endif
#ifdef __P402_CN
#define GPIO_P402 (0x82)
#define P402 GPIO_P402 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P402!
#endif
#ifdef __P403_CN
#define GPIO_P403 (0x83)
#define P403 GPIO_P403 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P403!
#endif
#ifdef __P404_CN
#define GPIO_P404 (0x84)
#define P404 GPIO_P404 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P404!
#endif
#ifdef __P405_CN
#define GPIO_P405 (0x85)
#define P405 GPIO_P405 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P405!
#endif
#ifdef __P406_CN
#define GPIO_P406 (0x86)
#define P406 GPIO_P406 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P406!
#endif
#ifdef __P407_CN
#define GPIO_P407 (0x87)
#define P407 GPIO_P407 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P407!
#endif
#ifdef __P408_CN
#define GPIO_P408 (0x88)
#define P408 GPIO_P408 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P408!
#endif
#ifdef __P409_CN
#define GPIO_P409 (0x89)
#define P409 GPIO_P409 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P409!
#endif
#ifdef __P410_CN
#define GPIO_P410 (0x8A)
#define P410 GPIO_P410 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P410!
#endif
#ifdef __P411_CN
#define GPIO_P411 (0x8B)
#define P411 GPIO_P411 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P411!
#endif
#ifdef __P412_CN
#define GPIO_P412 (0x8C)
#define P412 GPIO_P412 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P412!
#endif
#ifdef __P413_CN
#define GPIO_P413 (0x8D)
#define P413 GPIO_P413 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P413!
#endif
#ifdef __P414_CN
#define GPIO_P414 (0x8E)
#define P414 GPIO_P414 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P414!
#endif
#ifdef __P415_CN
#define GPIO_P415 (0x8F)
#define P415 GPIO_P415 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P415!
#endif
#ifdef __P416_CN
#define GPIO_P416 (0x90)
#define P416 GPIO_P416 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P416!
#endif
#ifdef __P417_CN
#define GPIO_P417 (0x91)
#define P417 GPIO_P417 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P417!
#endif
#ifdef __P418_CN
#define GPIO_P418 (0x92)
#define P418 GPIO_P418 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P418!
#endif
#ifdef __P419_CN
#define GPIO_P419 (0x93)
#define P419 GPIO_P419 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P419!
#endif
#ifdef __P420_CN
#define GPIO_P420 (0x94)
#define P420 GPIO_P420 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P420!
#endif
#ifdef __P421_CN
#define GPIO_P421 (0x95)
#define P421 GPIO_P421 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P421!
#endif
#ifdef __P422_CN
#define GPIO_P422 (0x96)
#define P422 GPIO_P422 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P422!
#endif
#ifdef __P423_CN
#define GPIO_P423 (0x97)
#define P423 GPIO_P423 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P423!
#endif
#ifdef __P424_CN
#define GPIO_P424 (0x98)
#define P424 GPIO_P424 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P424!
#endif
#ifdef __P425_CN
#define GPIO_P425 (0x99)
#define P425 GPIO_P425 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P425!
#endif
#ifdef __P426_CN
#define GPIO_P426 (0x9A)
#define P426 GPIO_P426 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P426!
#endif
#ifdef __P427_CN
#define GPIO_P427 (0x9B)
#define P427 GPIO_P427 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P427!
#endif
#ifdef __P428_CN
#define GPIO_P428 (0x9C)
#define P428 GPIO_P428 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P428!
#endif
#ifdef __P429_CN
#define GPIO_P429 (0x9D)
#define P429 GPIO_P429 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P429!
#endif
#ifdef __P430_CN
#define GPIO_P430 (0x9E)
#define P430 GPIO_P430 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P430!
#endif
#ifdef __P431_CN
#define GPIO_P431 (0x9F)
#define P431 GPIO_P431 // Notice: Will be removed in one of the upcoming releases. Use GPIO_P431!
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
