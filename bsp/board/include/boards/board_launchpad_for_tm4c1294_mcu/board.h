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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
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

#define BOARD_NAME "TM4C1294 LaunchPad Evaluation Kit"

#include "hal_target.h"

// Mapping
// BoosterPack 1
#define HEADER_CONNECTOR_A1_D1       // Pin not routed
#define HEADER_CONNECTOR_A1_D2       GPIO_PE4
#define HEADER_CONNECTOR_A1_D3       GPIO_PC4
#define HEADER_CONNECTOR_A1_D4       GPIO_PC5
#define HEADER_CONNECTOR_A1_D5       GPIO_PC6
#define HEADER_CONNECTOR_A1_D6       GPIO_PE5
#define HEADER_CONNECTOR_A1_D7       GPIO_PD3
#define HEADER_CONNECTOR_A1_D8       GPIO_PC7
#define HEADER_CONNECTOR_A1_D9       GPIO_PB2
#define HEADER_CONNECTOR_A1_D10      GPIO_PB3
#define HEADER_CONNECTOR_B1_D1       // Pin not routed
#define HEADER_CONNECTOR_B1_D2       // Pin not routed
#define HEADER_CONNECTOR_B1_D3       GPIO_PE0
#define HEADER_CONNECTOR_B1_D4       GPIO_PE1
#define HEADER_CONNECTOR_B1_D5       GPIO_PE2
#define HEADER_CONNECTOR_B1_D6       GPIO_PE3
#define HEADER_CONNECTOR_B1_D7       GPIO_PD7
#define HEADER_CONNECTOR_B1_D8       GPIO_PA6
#define HEADER_CONNECTOR_B1_D9       GPIO_PM4
#define HEADER_CONNECTOR_B1_D10      GPIO_PM5
#define HEADER_CONNECTOR_C1_D1       GPIO_PF1
#define HEADER_CONNECTOR_C1_D2       GPIO_PF2
#define HEADER_CONNECTOR_C1_D3       GPIO_PF3
#define HEADER_CONNECTOR_C1_D4       GPIO_PG0
#define HEADER_CONNECTOR_C1_D5       GPIO_PL4
#define HEADER_CONNECTOR_C1_D6       GPIO_PL5
#define HEADER_CONNECTOR_C1_D7       GPIO_PL0
#define HEADER_CONNECTOR_C1_D8       GPIO_PL1
#define HEADER_CONNECTOR_C1_D9       GPIO_PL2
#define HEADER_CONNECTOR_C1_D10      GPIO_PL3
#define HEADER_CONNECTOR_D1_D1       // Pin not routed
#define HEADER_CONNECTOR_D1_D2       GPIO_PM3
#define HEADER_CONNECTOR_D1_D3       GPIO_PH2
#define HEADER_CONNECTOR_D1_D4       GPIO_PH3
#define HEADER_CONNECTOR_D1_D5       // Pin not routed
#define HEADER_CONNECTOR_D1_D6       GPIO_PD1
#define HEADER_CONNECTOR_D1_D7       GPIO_PD0
#define HEADER_CONNECTOR_D1_D8       GPIO_PN2
#define HEADER_CONNECTOR_D1_D9       GPIO_PN3
#define HEADER_CONNECTOR_D1_D10      GPIO_PP2

// BoosterPack 2
#define HEADER_CONNECTOR_A2_D1       // Pin not routed
#define HEADER_CONNECTOR_A2_D2       GPIO_PD2
#define HEADER_CONNECTOR_A2_D3       GPIO_PP0
#define HEADER_CONNECTOR_A2_D4       GPIO_PP1
#define HEADER_CONNECTOR_A2_D5       GPIO_PD4
#define HEADER_CONNECTOR_A2_D6       GPIO_PD5
#define HEADER_CONNECTOR_A2_D7       GPIO_PQ0
#define HEADER_CONNECTOR_A2_D8       GPIO_PP4
#define HEADER_CONNECTOR_A2_D9       GPIO_PN5
#define HEADER_CONNECTOR_A2_D10      GPIO_PN4
#define HEADER_CONNECTOR_B2_D1       // Pin not routed
#define HEADER_CONNECTOR_B2_D2       // Pin not routed
#define HEADER_CONNECTOR_B2_D3       GPIO_PB4
#define HEADER_CONNECTOR_B2_D4       GPIO_PB5
#define HEADER_CONNECTOR_B2_D5       GPIO_PK0
#define HEADER_CONNECTOR_B2_D6       GPIO_PK1
#define HEADER_CONNECTOR_B2_D7       GPIO_PK2
#define HEADER_CONNECTOR_B2_D8       GPIO_PK3
#define HEADER_CONNECTOR_B2_D9       GPIO_PA4
#define HEADER_CONNECTOR_B2_D10      GPIO_PA5
#define HEADER_CONNECTOR_C2_D1       GPIO_PG1
#define HEADER_CONNECTOR_C2_D2       GPIO_PK4
#define HEADER_CONNECTOR_C2_D3       GPIO_PK5
#define HEADER_CONNECTOR_C2_D4       GPIO_PM0
#define HEADER_CONNECTOR_C2_D5       GPIO_PM1
#define HEADER_CONNECTOR_C2_D6       GPIO_PM2
#define HEADER_CONNECTOR_C2_D7       GPIO_PH0
#define HEADER_CONNECTOR_C2_D8       GPIO_PH1
#define HEADER_CONNECTOR_C2_D9       GPIO_PK6
#define HEADER_CONNECTOR_C2_D10      GPIO_PK7
#define HEADER_CONNECTOR_D2_D1       // Pin not routed
#define HEADER_CONNECTOR_D2_D2       GPIO_PM7
#define HEADER_CONNECTOR_D2_D3       GPIO_PP5
#define HEADER_CONNECTOR_D2_D4       GPIO_PA7
#define HEADER_CONNECTOR_D2_D5       // Pin not routed
#define HEADER_CONNECTOR_D2_D6       GPIO_PQ2
#define HEADER_CONNECTOR_D2_D7       GPIO_PQ3
#define HEADER_CONNECTOR_D2_D8       GPIO_PP3
#define HEADER_CONNECTOR_D2_D9       GPIO_PQ1
#define HEADER_CONNECTOR_D2_D10      GPIO_PM6

// X11 Breadboard Adapter
#define HEADER_CONNECTOR_CN_D1      // Pin not routed
#define HEADER_CONNECTOR_CN_D2      // Pin not routed
#define HEADER_CONNECTOR_CN_D3      // Pin not routed
#define HEADER_CONNECTOR_CN_D4      // Pin not routed
#define HEADER_CONNECTOR_CN_D5      GPIO_PB4
#define HEADER_CONNECTOR_CN_D6      GPIO_PA2
#define HEADER_CONNECTOR_CN_D7      GPIO_PB5
#define HEADER_CONNECTOR_CN_D8      GPIO_PA3
#define HEADER_CONNECTOR_CN_D9      GPIO_PH0
#define HEADER_CONNECTOR_CN_D10     GPIO_PA4
#define HEADER_CONNECTOR_CN_D11     GPIO_PH1
#define HEADER_CONNECTOR_CN_D12     GPIO_PA5
#define HEADER_CONNECTOR_CN_D13     GPIO_PH2
#define HEADER_CONNECTOR_CN_D14     GPIO_PE0
#define HEADER_CONNECTOR_CN_D15     GPIO_PH3
#define HEADER_CONNECTOR_CN_D16     GPIO_PE1
#define HEADER_CONNECTOR_CN_D17     GPIO_PC7
#define HEADER_CONNECTOR_CN_D18     GPIO_PE2
#define HEADER_CONNECTOR_CN_D19     GPIO_PC6
#define HEADER_CONNECTOR_CN_D20     GPIO_PE3
#define HEADER_CONNECTOR_CN_D21     GPIO_PC5
#define HEADER_CONNECTOR_CN_D22     GPIO_PE4
#define HEADER_CONNECTOR_CN_D23     GPIO_PC4
#define HEADER_CONNECTOR_CN_D24     GPIO_PE5
#define HEADER_CONNECTOR_CN_D25     GPIO_PA6
#define HEADER_CONNECTOR_CN_D26     GPIO_PK0
#define HEADER_CONNECTOR_CN_D27     GPIO_PA7
#define HEADER_CONNECTOR_CN_D28     GPIO_PK1
#define HEADER_CONNECTOR_CN_D29     GPIO_PG1
#define HEADER_CONNECTOR_CN_D30     GPIO_PK2
#define HEADER_CONNECTOR_CN_D31     GPIO_PG0
#define HEADER_CONNECTOR_CN_D32     GPIO_PK3
#define HEADER_CONNECTOR_CN_D33     GPIO_PM3
#define HEADER_CONNECTOR_CN_D34     // Pin not routed
#define HEADER_CONNECTOR_CN_D35     // Pin not routed
#define HEADER_CONNECTOR_CN_D36     // Pin not routed
#define HEADER_CONNECTOR_CN_D37     GPIO_PM2
#define HEADER_CONNECTOR_CN_D38     GPIO_PD5
#define HEADER_CONNECTOR_CN_D39     GPIO_PM1
#define HEADER_CONNECTOR_CN_D40     GPIO_PD4
#define HEADER_CONNECTOR_CN_D41     GPIO_PM0
#define HEADER_CONNECTOR_CN_D42     GPIO_PD7
#define HEADER_CONNECTOR_CN_D43     GPIO_PL0
#define HEADER_CONNECTOR_CN_D44     GPIO_PD6
#define HEADER_CONNECTOR_CN_D45     GPIO_PL1
#define HEADER_CONNECTOR_CN_D46     GPIO_PD3
#define HEADER_CONNECTOR_CN_D47     GPIO_PL2
#define HEADER_CONNECTOR_CN_D48     GPIO_PD1
#define HEADER_CONNECTOR_CN_D49     GPIO_PL3
#define HEADER_CONNECTOR_CN_D50     GPIO_PD0
#define HEADER_CONNECTOR_CN_D51     GPIO_PQ0
#define HEADER_CONNECTOR_CN_D52     GPIO_PD2
#define HEADER_CONNECTOR_CN_D53     GPIO_PQ1
#define HEADER_CONNECTOR_CN_D54     GPIO_PP0
#define HEADER_CONNECTOR_CN_D55     GPIO_PQ2
#define HEADER_CONNECTOR_CN_D56     GPIO_PP1
#define HEADER_CONNECTOR_CN_D57     GPIO_PQ3
#define HEADER_CONNECTOR_CN_D58     GPIO_PB0
#define HEADER_CONNECTOR_CN_D59     GPIO_PK7
#define HEADER_CONNECTOR_CN_D60     GPIO_PB1
#define HEADER_CONNECTOR_CN_D61     // Pin not routed
#define HEADER_CONNECTOR_CN_D62     // Pin not routed
#define HEADER_CONNECTOR_CN_D63     GPIO_PK6
#define HEADER_CONNECTOR_CN_D64     GPIO_PF4
#define HEADER_CONNECTOR_CN_D65     GPIO_PL4
#define HEADER_CONNECTOR_CN_D66     GPIO_PF0
#define HEADER_CONNECTOR_CN_D67     GPIO_PB2
#define HEADER_CONNECTOR_CN_D68     GPIO_PF1
#define HEADER_CONNECTOR_CN_D69     GPIO_PB3
#define HEADER_CONNECTOR_CN_D70     GPIO_PF2
#define HEADER_CONNECTOR_CN_D71     GPIO_PP2
#define HEADER_CONNECTOR_CN_D72     GPIO_PF3
#define HEADER_CONNECTOR_CN_D73     GPIO_PP3
#define HEADER_CONNECTOR_CN_D74     GPIO_PA0
#define HEADER_CONNECTOR_CN_D75     GPIO_PK5
#define HEADER_CONNECTOR_CN_D76     GPIO_PA1
#define HEADER_CONNECTOR_CN_D77     GPIO_PK4
#define HEADER_CONNECTOR_CN_D78     GPIO_PP4
#define HEADER_CONNECTOR_CN_D79     GPIO_PL5
#define HEADER_CONNECTOR_CN_D80     GPIO_PP5
#define HEADER_CONNECTOR_CN_D81     GPIO_PN4
#define HEADER_CONNECTOR_CN_D82     GPIO_PJ0
#define HEADER_CONNECTOR_CN_D83     GPIO_PN5
#define HEADER_CONNECTOR_CN_D84     GPIO_PJ1
#define HEADER_CONNECTOR_CN_D85     GPIO_PN0
#define HEADER_CONNECTOR_CN_D86     GPIO_PM7
#define HEADER_CONNECTOR_CN_D87     GPIO_PN1
#define HEADER_CONNECTOR_CN_D88     GPIO_PM6
#define HEADER_CONNECTOR_CN_D89     GPIO_PN2
#define HEADER_CONNECTOR_CN_D90     GPIO_PM5
#define HEADER_CONNECTOR_CN_D91     GPIO_PN3
#define HEADER_CONNECTOR_CN_D92     GPIO_PM4
#define HEADER_CONNECTOR_CN_D93     GPIO_PQ4
#define HEADER_CONNECTOR_CN_D94     // Pin not routed
#define HEADER_CONNECTOR_CN_D95     // Pin not routed
#define HEADER_CONNECTOR_CN_D96     // Pin not routed
#define HEADER_CONNECTOR_CN_D97     // Pin not routed
#define HEADER_CONNECTOR_CN_D98     // Pin not routed

// LEDS
#define LED1    GPIO_PN1
#define LED2    GPIO_PN0
#define LED3    GPIO_PF4
#define LED4    GPIO_PF0

// BUTTONS
#define BUTTON1 GPIO_PJ0
#define BUTTON2 GPIO_PJ1

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END