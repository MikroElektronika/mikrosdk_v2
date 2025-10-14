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
extern "C"{
#endif

#define BOARD_NAME "Nuvoton NuMaker M2354"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_P1             GPIO_PB5
#define HEADER_CONNECTOR_P2             GPIO_PB4
#define HEADER_CONNECTOR_P3             GPIO_PB3
#define HEADER_CONNECTOR_P4             GPIO_PB2
#define HEADER_CONNECTOR_P5             GPIO_PC12
#define HEADER_CONNECTOR_P6             GPIO_PC11
#define HEADER_CONNECTOR_P7             GPIO_PC10
#define HEADER_CONNECTOR_P8             GPIO_PC9
#define HEADER_CONNECTOR_P9             GPIO_PB1
#define HEADER_CONNECTOR_P10            GPIO_PB0
#define HEADER_CONNECTOR_P11            // Pin not routed
#define HEADER_CONNECTOR_P12            // Pin not routed
#define HEADER_CONNECTOR_P13            GPIO_PA11
#define HEADER_CONNECTOR_P14            GPIO_PA10
#define HEADER_CONNECTOR_P15            GPIO_PA9
#define HEADER_CONNECTOR_P16            GPIO_PA8
#define HEADER_CONNECTOR_P17            GPIO_PC13
#define HEADER_CONNECTOR_P18            GPIO_PD12
#define HEADER_CONNECTOR_P19            GPIO_PD11
#define HEADER_CONNECTOR_P20            GPIO_PD10
#define HEADER_CONNECTOR_P21            GPIO_PG2
#define HEADER_CONNECTOR_P22            GPIO_PG3
#define HEADER_CONNECTOR_P23            GPIO_PG4
#define HEADER_CONNECTOR_P24            GPIO_PF11
#define HEADER_CONNECTOR_P25            GPIO_PF10
#define HEADER_CONNECTOR_P26            GPIO_PF9
#define HEADER_CONNECTOR_P27            GPIO_PF8
#define HEADER_CONNECTOR_P28            GPIO_PF7
#define HEADER_CONNECTOR_P29            GPIO_PF6
#define HEADER_CONNECTOR_P30            // Pin not routed
#define HEADER_CONNECTOR_P31            GPIO_PF5
#define HEADER_CONNECTOR_P32            GPIO_PF4
#define HEADER_CONNECTOR_P33            GPIO_PH4
#define HEADER_CONNECTOR_P34            GPIO_PH5
#define HEADER_CONNECTOR_P35            GPIO_PH6
#define HEADER_CONNECTOR_P36            GPIO_PH7
#define HEADER_CONNECTOR_P37            GPIO_PF3
#define HEADER_CONNECTOR_P38            GPIO_PF2
#define HEADER_CONNECTOR_P39            // Pin not routed
#define HEADER_CONNECTOR_P40            // Pin not routed
#define HEADER_CONNECTOR_P41            GPIO_PE8
#define HEADER_CONNECTOR_P42            GPIO_PE9
#define HEADER_CONNECTOR_P43            GPIO_PE10
#define HEADER_CONNECTOR_P44            GPIO_PE11
#define HEADER_CONNECTOR_P45            GPIO_PE12
#define HEADER_CONNECTOR_P46            GPIO_PE13
#define HEADER_CONNECTOR_P47            GPIO_PC8
#define HEADER_CONNECTOR_P48            GPIO_PC7
#define HEADER_CONNECTOR_P49            GPIO_PC6
#define HEADER_CONNECTOR_P50            GPIO_PA7
#define HEADER_CONNECTOR_P51            GPIO_PA6
#define HEADER_CONNECTOR_P52            // Pin not routed
#define HEADER_CONNECTOR_P53            // Pin not routed
#define HEADER_CONNECTOR_P54            // Pin not routed
#define HEADER_CONNECTOR_P55            GPIO_PA5
#define HEADER_CONNECTOR_P56            GPIO_PA4
#define HEADER_CONNECTOR_P57            GPIO_PA3
#define HEADER_CONNECTOR_P58            GPIO_PA2
#define HEADER_CONNECTOR_P59            GPIO_PA1
#define HEADER_CONNECTOR_P60            GPIO_PA0
#define HEADER_CONNECTOR_P61            // Pin not routed
#define HEADER_CONNECTOR_P62            GPIO_PE14
#define HEADER_CONNECTOR_P63            GPIO_PE15
#define HEADER_CONNECTOR_P64            // Pin not routed
#define HEADER_CONNECTOR_P65            GPIO_PF0
#define HEADER_CONNECTOR_P66            GPIO_PF1
#define HEADER_CONNECTOR_P67            GPIO_PD9
#define HEADER_CONNECTOR_P68            GPIO_PD8
#define HEADER_CONNECTOR_P69            GPIO_PC5
#define HEADER_CONNECTOR_P70            GPIO_PC4
#define HEADER_CONNECTOR_P71            GPIO_PC3
#define HEADER_CONNECTOR_P72            GPIO_PC2
#define HEADER_CONNECTOR_P73            GPIO_PC1
#define HEADER_CONNECTOR_P74            GPIO_PC0
#define HEADER_CONNECTOR_P75            // Pin not routed
#define HEADER_CONNECTOR_P76            // Pin not routed
#define HEADER_CONNECTOR_P77            GPIO_PG9
#define HEADER_CONNECTOR_P78            GPIO_PG10
#define HEADER_CONNECTOR_P79            GPIO_PG11
#define HEADER_CONNECTOR_P80            GPIO_PG12
#define HEADER_CONNECTOR_P81            GPIO_PG13
#define HEADER_CONNECTOR_P82            GPIO_PG14
#define HEADER_CONNECTOR_P83            GPIO_PG15
#define HEADER_CONNECTOR_P84            GPIO_PD7
#define HEADER_CONNECTOR_P85            GPIO_PD6
#define HEADER_CONNECTOR_P86            GPIO_PD5
#define HEADER_CONNECTOR_P87            GPIO_PD4
#define HEADER_CONNECTOR_P88            GPIO_PD3
#define HEADER_CONNECTOR_P89            GPIO_PD2
#define HEADER_CONNECTOR_P90            GPIO_PD1
#define HEADER_CONNECTOR_P91            GPIO_PD0
#define HEADER_CONNECTOR_P92            // Pin not routed
#define HEADER_CONNECTOR_P93            GPIO_PA12
#define HEADER_CONNECTOR_P94            GPIO_PA13
#define HEADER_CONNECTOR_P95            GPIO_PA14
#define HEADER_CONNECTOR_P96            GPIO_PA15
#define HEADER_CONNECTOR_P97            GPIO_PE7
#define HEADER_CONNECTOR_P98            GPIO_PE6
#define HEADER_CONNECTOR_P99            GPIO_PE5
#define HEADER_CONNECTOR_P100           GPIO_PE4
#define HEADER_CONNECTOR_P101           GPIO_PE3
#define HEADER_CONNECTOR_P102           GPIO_PE2
#define HEADER_CONNECTOR_P103           // Pin not routed
#define HEADER_CONNECTOR_P104           // Pin not routed
#define HEADER_CONNECTOR_P105           GPIO_PE1
#define HEADER_CONNECTOR_P106           GPIO_PE0
#define HEADER_CONNECTOR_P107           GPIO_PH8
#define HEADER_CONNECTOR_P108           GPIO_PH9
#define HEADER_CONNECTOR_P109           GPIO_PH10
#define HEADER_CONNECTOR_P110           GPIO_PH11
#define HEADER_CONNECTOR_P111           GPIO_PD14
#define HEADER_CONNECTOR_P112           // Pin not routed
#define HEADER_CONNECTOR_P113           // Pin not routed
#define HEADER_CONNECTOR_P114           // Pin not routed
#define HEADER_CONNECTOR_P115           // Pin not routed
#define HEADER_CONNECTOR_P116           GPIO_PB15
#define HEADER_CONNECTOR_P117           GPIO_PB14
#define HEADER_CONNECTOR_P118           GPIO_PB13
#define HEADER_CONNECTOR_P119           GPIO_PB12
#define HEADER_CONNECTOR_P120           // Pin not routed
#define HEADER_CONNECTOR_P121           // Pin not routed
#define HEADER_CONNECTOR_P122           // Pin not routed
#define HEADER_CONNECTOR_P123           GPIO_PB11
#define HEADER_CONNECTOR_P124           GPIO_PB10
#define HEADER_CONNECTOR_P125           GPIO_PB9
#define HEADER_CONNECTOR_P126           GPIO_PB8
#define HEADER_CONNECTOR_P127           GPIO_PB7
#define HEADER_CONNECTOR_P128           GPIO_PB6

#define HEADER_CONNECTOR_D0             GPIO_PA8
#define HEADER_CONNECTOR_D1             GPIO_PA9
#define HEADER_CONNECTOR_D2             GPIO_PC1
#define HEADER_CONNECTOR_D3             GPIO_PC0
#define HEADER_CONNECTOR_D4             GPIO_PE7
#define HEADER_CONNECTOR_D5             GPIO_PE6
#define HEADER_CONNECTOR_D6             GPIO_PC12
#define HEADER_CONNECTOR_D7             GPIO_PC11
#define HEADER_CONNECTOR_D8             GPIO_PC9
#define HEADER_CONNECTOR_D9             GPIO_PC10
#define HEADER_CONNECTOR_D10            GPIO_PA3
#define HEADER_CONNECTOR_D11            GPIO_PA0
#define HEADER_CONNECTOR_D12            GPIO_PA1
#define HEADER_CONNECTOR_D13            GPIO_PA2

#define HEADER_CONNECTOR_ANALOG_IN_A0   GPIO_PB11
#define HEADER_CONNECTOR_ANALOG_IN_A1   GPIO_PB10
#define HEADER_CONNECTOR_ANALOG_IN_A2   GPIO_PB9
#define HEADER_CONNECTOR_ANALOG_IN_A3   GPIO_PB8
#define HEADER_CONNECTOR_ANALOG_IN_A4   GPIO_PB7
#define HEADER_CONNECTOR_ANALOG_IN_A5   GPIO_PB6

#define HEADER_CONNECTOR_DIGITAL_SCL    GPIO_PG3
#define HEADER_CONNECTOR_DIGITAL_SDA    GPIO_PG2
#define HEADER_CONNECTOR_DIGITAL_SCK    GPIO_PH8
#define HEADER_CONNECTOR_DIGITAL_CIPO   GPIO_PE1
#define HEADER_CONNECTOR_DIGITAL_COPI   GPIO_PE0
#define HEADER_CONNECTOR_DIGITAL_SS     GPIO_PH9

#define LED1 GPIO_PD12
#define LED2 GPIO_PC13

#define USB_UART_TX SHIELD_SW1_TX
#define USB_UART_RX SHIELD_SW1_RX

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_
// ------------------------------------------------------------------------- END
