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

#define BOARD_NAME "PIC32 Bluetooth Audio Development Kit"

#include "pim_socket.h"

// Mapping
#define HEADER_CONNECTOR_J8_D3      PIM_PIN_049
#define HEADER_CONNECTOR_J8_D4      PIM_PIN_023
#define HEADER_CONNECTOR_J8_D5      PIM_PIN_050
#define HEADER_CONNECTOR_J8_D6      PIM_PIN_014
#define HEADER_CONNECTOR_J8_D7      PIM_PIN_058
#define HEADER_CONNECTOR_J8_D8      PIM_PIN_001
#define HEADER_CONNECTOR_J8_D9      PIM_PIN_059
#define HEADER_CONNECTOR_J8_D10     PIM_PIN_007
#define HEADER_CONNECTOR_J8_D11     PIM_PIN_011
#define HEADER_CONNECTOR_J8_D12     PIM_PIN_010
#define HEADER_CONNECTOR_J8_D13     PIM_PIN_012
#define HEADER_CONNECTOR_J8_D14     PIM_PIN_053

#define HEADER_CONNECTOR_J9_D3      PIM_PIN_077
#define HEADER_CONNECTOR_J9_D4      PIM_PIN_079
#define HEADER_CONNECTOR_J9_D5      PIM_PIN_078
#define HEADER_CONNECTOR_J9_D6      PIM_PIN_076
#define HEADER_CONNECTOR_J9_D7      PIM_PIN_066
#define HEADER_CONNECTOR_J9_D8      PIM_PIN_001
#define HEADER_CONNECTOR_J9_D9      PIM_PIN_067
#define HEADER_CONNECTOR_J9_D10     PIM_PIN_069
#define HEADER_CONNECTOR_J9_D11     PIM_PIN_072
#define HEADER_CONNECTOR_J9_D12     PIM_PIN_070
#define HEADER_CONNECTOR_J9_D13     PIM_PIN_073
#define HEADER_CONNECTOR_J9_D14     PIM_PIN_053

#define HEADER_CONNECTOR_J10_D1     PIM_PIN_007
#define HEADER_CONNECTOR_J10_D2     PIM_PIN_032
#define HEADER_CONNECTOR_J10_D3     PIM_PIN_010
#define HEADER_CONNECTOR_J10_D4     PIM_PIN_033
#define HEADER_CONNECTOR_J10_D5     PIM_PIN_011
#define HEADER_CONNECTOR_J10_D6     PIM_PIN_018
#define HEADER_CONNECTOR_J10_D7     PIM_PIN_012
#define HEADER_CONNECTOR_J10_D8     PIM_PIN_022
#define HEADER_CONNECTOR_J10_D9     PIM_PIN_087

#define HEADER_CONNECTOR_J11_D1     PIM_PIN_069
#define HEADER_CONNECTOR_J11_D2     PIM_PIN_051
#define HEADER_CONNECTOR_J11_D3     PIM_PIN_070
#define HEADER_CONNECTOR_J11_D5     PIM_PIN_073
#define HEADER_CONNECTOR_J11_D7     PIM_PIN_072

#define AUDIO_DAC_J9_1      // Pin not routed
#define AUDIO_DAC_J9_2      // Pin not routed
#define AUDIO_DAC_J9_3      PIM_PIN_077
#define AUDIO_DAC_J9_4      PIM_PIN_079
#define AUDIO_DAC_J9_5      PIM_PIN_078
#define AUDIO_DAC_J9_6      PIM_PIN_076
#define AUDIO_DAC_J9_7      PIM_PIN_066
#define AUDIO_DAC_J9_8      PIM_PIN_001
#define AUDIO_DAC_J9_9      PIM_PIN_067
#define AUDIO_DAC_J9_10     PIM_PIN_069
#define AUDIO_DAC_J9_11     PIM_PIN_073
#define AUDIO_DAC_J9_12     PIM_PIN_070
#define AUDIO_DAC_J9_13     PIM_PIN_072
#define AUDIO_DAC_J9_14     PIM_PIN_053
#define AUDIO_DAC_J9_15     // Pin not routed
#define AUDIO_DAC_J9_16     // Pin not routed
#define AUDIO_DAC_J9_17     // Pin not routed
#define AUDIO_DAC_J9_18     // Pin not routed
#define AUDIO_DAC_J9_19     // Pin not routed
#define AUDIO_DAC_J9_20     // Pin not routed

#define AUDIO_DAC_J10_1     PIM_PIN_007
#define AUDIO_DAC_J10_2     PIM_PIN_032
#define AUDIO_DAC_J10_3     PIM_PIN_010
#define AUDIO_DAC_J10_4     PIM_PIN_033
#define AUDIO_DAC_J10_5     PIM_PIN_011
#define AUDIO_DAC_J10_6     PIM_PIN_018
#define AUDIO_DAC_J10_7     PIM_PIN_012
#define AUDIO_DAC_J10_8     PIM_PIN_022
#define AUDIO_DAC_J10_9     PIM_PIN_087
#define AUDIO_DAC_J10_10    // Pin not routed
#define AUDIO_DAC_J10_11    // Pin not routed
#define AUDIO_DAC_J10_12    // Pin not routed

#define BLUETOOTH_J8_1      // Pin not routed
#define BLUETOOTH_J8_2      // Pin not routed
#define BLUETOOTH_J8_3      PIM_PIN_049
#define BLUETOOTH_J8_4      PIM_PIN_023
#define BLUETOOTH_J8_5      PIM_PIN_050
#define BLUETOOTH_J8_6      PIM_PIN_014
#define BLUETOOTH_J8_7      PIM_PIN_058
#define BLUETOOTH_J8_8      PIM_PIN_001
#define BLUETOOTH_J8_9      PIM_PIN_059
#define BLUETOOTH_J8_10     PIM_PIN_007
#define BLUETOOTH_J8_11     PIM_PIN_011
#define BLUETOOTH_J8_12     PIM_PIN_010
#define BLUETOOTH_J8_13     PIM_PIN_012
#define BLUETOOTH_J8_14     PIM_PIN_053
#define BLUETOOTH_J8_15     // Pin not routed
#define BLUETOOTH_J8_16     // Pin not routed
#define BLUETOOTH_J8_17     // Pin not routed
#define BLUETOOTH_J8_18     // Pin not routed
#define BLUETOOTH_J8_19     // Pin not routed
#define BLUETOOTH_J8_20     // Pin not routed

#define BLUETOOTH_J11_1     PIM_PIN_069
#define BLUETOOTH_J11_2     PIM_PIN_051
#define BLUETOOTH_J11_3     PIM_PIN_070
#define BLUETOOTH_J11_4     PIM_PIN_020
#define BLUETOOTH_J11_5     PIM_PIN_073
#define BLUETOOTH_J11_6     PIM_PIN_025
#define BLUETOOTH_J11_7     PIM_PIN_072
#define BLUETOOTH_J11_8     PIM_PIN_034
#define BLUETOOTH_J11_9     PIM_PIN_088
#define BLUETOOTH_J11_10    // Pin not routed
#define BLUETOOTH_J11_11    // Pin not routed
#define BLUETOOTH_J11_12    // Pin not routed

#define LED_1       PIM_PIN_060
#define LED_2       PIM_PIN_061
#define LED_3       PIM_PIN_091
#define LED_4       PIM_PIN_092
#define LED_5       PIM_PIN_028

#define BUTTON_1    PIM_PIN_017
#define BUTTON_2    PIM_PIN_038
#define BUTTON_3    PIM_PIN_029
#define BUTTON_4    PIM_PIN_041
#define BUTTON_5    PIM_PIN_042

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
