/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  mcu_card.h
 * @brief MCU card connections mapping.
 */

#ifndef _MCU_CARD_H_
#define _MCU_CARD_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

// Hardware revision number
#define MCU_CARD_REV_MAJOR (1)
#define MCU_CARD_REV_MINOR (00)

#define NC HAL_PIN_NC

// Top of Board.
#define TOP_CN_PIN_001 NC
#define TOP_CN_PIN_003 NC
#define TOP_CN_PIN_005 NC
#define TOP_CN_PIN_007 NC
#define TOP_CN_PIN_009 NC
#define TOP_CN_PIN_011 NC
#define TOP_CN_PIN_013 NC
#define TOP_CN_PIN_015 NC
#define TOP_CN_PIN_017 PA2 // MIKROBUS_1_TX
#define TOP_CN_PIN_019 PA3 // MIKROBUS_1_RX
#define TOP_CN_PIN_021 NC
#define TOP_CN_PIN_023 NC
#define TOP_CN_PIN_025 NC
#define TOP_CN_PIN_027 NC
#define TOP_CN_PIN_029 NC
#define TOP_CN_PIN_031 NC
#define TOP_CN_PIN_033 NC
#define TOP_CN_PIN_035 NC
#define TOP_CN_PIN_037 NC
#define TOP_CN_PIN_039 NC
#define TOP_CN_PIN_041 NC
#define TOP_CN_PIN_043 NC
#define TOP_CN_PIN_045 NC
#define TOP_CN_PIN_047 NC
#define TOP_CN_PIN_049 NC
#define TOP_CN_PIN_051 NC
#define TOP_CN_PIN_053 NC
#define TOP_CN_PIN_055 PC4 // MIKROBUS_1_CS
#define TOP_CN_PIN_057 PA5 // MIKROBUS_1_SCK
#define TOP_CN_PIN_059 PA7 // MIKROBUS_1_MOSI
#define TOP_CN_PIN_061 PA6 // MIKROBUS_1_MISO
#define TOP_CN_PIN_063 NC
#define TOP_CN_PIN_065 NC
#define TOP_CN_PIN_067 NC
#define TOP_CN_PIN_069 NC
#define TOP_CN_PIN_071 NC
#define TOP_CN_PIN_073 NC
#define TOP_CN_PIN_075 NC


// Bottom of Board.
#define BOTTOM_CN_PIN_002 NC
#define BOTTOM_CN_PIN_004 NC
#define BOTTOM_CN_PIN_006 NC
#define BOTTOM_CN_PIN_008 NC
#define BOTTOM_CN_PIN_010 PC0 // MIKROBUS_1_INT
#define BOTTOM_CN_PIN_012 PB11 // MIKROBUS_1_SDA
#define BOTTOM_CN_PIN_014 PB10 // MIKROBUS_1_SCL
#define BOTTOM_CN_PIN_016 PB1 // I2C_INT
#define BOTTOM_CN_PIN_018 PC1 // MIKROBUS_1_RST
#define BOTTOM_CN_PIN_020 NC
#define BOTTOM_CN_PIN_022 NC
#define BOTTOM_CN_PIN_024 NC
#define BOTTOM_CN_PIN_026 NC
#define BOTTOM_CN_PIN_028 NC
#define BOTTOM_CN_PIN_030 NC
#define BOTTOM_CN_PIN_032 PC6 // MIKROBUS_1_PWM
#define BOTTOM_CN_PIN_034 PC5 // MIKROBUS_1_AN
#define BOTTOM_CN_PIN_036 NC
#define BOTTOM_CN_PIN_038 NC
#define BOTTOM_CN_PIN_040 NC
#define BOTTOM_CN_PIN_042 NC
#define BOTTOM_CN_PIN_044 NC
#define BOTTOM_CN_PIN_046 NC
#define BOTTOM_CN_PIN_048 NC
#define BOTTOM_CN_PIN_050 NC
#define BOTTOM_CN_PIN_052 NC
#define BOTTOM_CN_PIN_054 NC
#define BOTTOM_CN_PIN_056 NC
#define BOTTOM_CN_PIN_058 NC
#define BOTTOM_CN_PIN_060 NC
#define BOTTOM_CN_PIN_062 NC
#define BOTTOM_CN_PIN_064 NC
#define BOTTOM_CN_PIN_066 NC
#define BOTTOM_CN_PIN_068 NC
#define BOTTOM_CN_PIN_070 NC
#define BOTTOM_CN_PIN_072 NC
#define BOTTOM_CN_PIN_074 NC

#ifdef __cplusplus
}
#endif

#endif // _MCU_CARD_H_
// ------------------------------------------------------------------------- END
