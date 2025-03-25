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
 * @file  board.h
 * @brief Main board pin mapping.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define BOARD_NAME "XMEGA-E5 XPLAINED"

#include "hal_target.h"

// Mapping
#define J1_1    GPIO_PC0
#define J1_2    GPIO_PC1
#define J1_3    GPIO_PC2
#define J1_4    GPIO_PC3
#define J1_5    GPIO_PC4
#define J1_6    GPIO_PC7
#define J1_7    GPIO_PC6
#define J1_8    GPIO_PC5

#define J2_1    GPIO_PA0
#define J2_2    GPIO_PA1
#define J2_3    GPIO_PA2
#define J2_4    GPIO_PA3
#define J2_5    GPIO_PA4
#define J2_6    GPIO_PA5
#define J2_7    GPIO_PA6
#define J2_8    GPIO_PA7

#define J3_1    // Pin not routed
#define J3_2    // Pin not routed
#define J3_3    // Pin not routed
#define J3_4    // Pin not routed
#define J3_5    GPIO_PC4
#define J3_6    GPIO_PC7
#define J3_7    GPIO_PC6
#define J3_8    GPIO_PC5

#define J4_1    GPIO_PD0
#define J4_2    GPIO_PD1
#define J4_3    GPIO_PD2
#define J4_4    GPIO_PD3
#define J4_5    GPIO_PD4
#define J4_6    GPIO_PD7
#define J4_7    GPIO_PD6
#define J4_8    GPIO_PD5

#define LED_0   GPIO_PD4
#define LED_1   GPIO_PD5

#define BUTTON_1    GPIO_PD0
#define BUTTON_2    GPIO_PD2

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
