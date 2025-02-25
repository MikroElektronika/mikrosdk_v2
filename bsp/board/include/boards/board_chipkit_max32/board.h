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

#define BOARD_NAME "chipKIT Max32 Development Board"

#include "hal_target.h"

// Mapping
#define HEADER_CONNECTOR_CN3_D1     PD12
#define HEADER_CONNECTOR_CN3_D2     PG1
#define HEADER_CONNECTOR_CN3_D3     PD3
#define HEADER_CONNECTOR_CN3_D4     PG0
#define HEADER_CONNECTOR_CN3_D5     PD4
#define HEADER_CONNECTOR_CN3_D6     PA6
#define HEADER_CONNECTOR_CN3_D7     PC4
#define HEADER_CONNECTOR_CN3_D8     PA7
#define HEADER_CONNECTOR_CN3_D9     PA2
#define HEADER_CONNECTOR_CN3_D10    PG14
#define HEADER_CONNECTOR_CN3_D11    PA3
#define HEADER_CONNECTOR_CN3_D12    PG12
#define HEADER_CONNECTOR_CN3_D13    // Pin not routed
#define HEADER_CONNECTOR_CN3_D14    PG13
#define HEADER_CONNECTOR_CN3_D15    // Pin not routed
#define HEADER_CONNECTOR_CN3_D16    PA9

#define HEADER_CONNECTOR_CN4_D1     PA14
#define HEADER_CONNECTOR_CN4_D2     PA15
#define HEADER_CONNECTOR_CN4_D3     PD14
#define HEADER_CONNECTOR_CN4_D4     PD15
#define HEADER_CONNECTOR_CN4_D5     PF4
#define HEADER_CONNECTOR_CN4_D6     PF5
#define HEADER_CONNECTOR_CN4_D7     PF12
#define HEADER_CONNECTOR_CN4_D8     PF13

#define HEADER_CONNECTOR_CN5_D1     PB0
#define HEADER_CONNECTOR_CN5_D2     PB1
#define HEADER_CONNECTOR_CN5_D3     PB2
#define HEADER_CONNECTOR_CN5_D4     PB3
#define HEADER_CONNECTOR_CN5_D5     PB4
#define HEADER_CONNECTOR_CN5_D6     PB5
#define HEADER_CONNECTOR_CN5_D7     PB6
#define HEADER_CONNECTOR_CN5_D8     PB7

#define HEADER_CONNECTOR_CN7_D1     PB8
#define HEADER_CONNECTOR_CN7_D2     PB9
#define HEADER_CONNECTOR_CN7_D3     PB10
#define HEADER_CONNECTOR_CN7_D4     PB11
#define HEADER_CONNECTOR_CN7_D6     PB13
#define HEADER_CONNECTOR_CN7_D5     PB12
#define HEADER_CONNECTOR_CN7_D7     PB14
#define HEADER_CONNECTOR_CN7_D8     PB15

#define HEADER_CONNECTOR_CN8_D1     PG9
#define HEADER_CONNECTOR_CN8_D2     PG6
#define HEADER_CONNECTOR_CN8_D3     PG8
#define HEADER_CONNECTOR_CN8_D4     PG7
#define HEADER_CONNECTOR_CN8_D5     PD11
#define HEADER_CONNECTOR_CN8_D6     PD8
#define HEADER_CONNECTOR_CN8_D7     PD6
#define HEADER_CONNECTOR_CN8_D8     PF1
#define HEADER_CONNECTOR_CN8_D9     PF0
#define HEADER_CONNECTOR_CN8_D10    PA10
#define HEADER_CONNECTOR_CN8_D11    PG8
#define HEADER_CONNECTOR_CN8_D12    PB12
#define HEADER_CONNECTOR_CN8_D13    PB13
#define HEADER_CONNECTOR_CN8_D14    PB11
#define HEADER_CONNECTOR_CN8_D15    PD5
#define HEADER_CONNECTOR_CN8_D16    PD10

#define HEADER_CONNECTOR_CN9_D1     PE0
#define HEADER_CONNECTOR_CN9_D2     PE1
#define HEADER_CONNECTOR_CN9_D3     PE2
#define HEADER_CONNECTOR_CN9_D4     PE3
#define HEADER_CONNECTOR_CN9_D5     PE4
#define HEADER_CONNECTOR_CN9_D6     PE5
#define HEADER_CONNECTOR_CN9_D7     PE6
#define HEADER_CONNECTOR_CN9_D8     PE7
#define HEADER_CONNECTOR_CN9_D9     PG7
#define HEADER_CONNECTOR_CN9_D10    PG15
#define HEADER_CONNECTOR_CN9_D11    PG2
#define HEADER_CONNECTOR_CN9_D12    PG3
#define HEADER_CONNECTOR_CN9_D13    PF3
#define HEADER_CONNECTOR_CN9_D14    // Pin not routed
#define HEADER_CONNECTOR_CN9_D15    PC3
#define HEADER_CONNECTOR_CN9_D16    PC2

#define HEADER_CONNECTOR_CN14_D1    PF2
#define HEADER_CONNECTOR_CN14_D2    PA0
#define HEADER_CONNECTOR_CN14_D3    PF8
#define HEADER_CONNECTOR_CN14_D4    PA1
#define HEADER_CONNECTOR_CN14_D5    PE8
#define HEADER_CONNECTOR_CN14_D6    PA4
#define HEADER_CONNECTOR_CN14_D7    PD0
#define HEADER_CONNECTOR_CN14_D8    PA5
#define HEADER_CONNECTOR_CN14_D9    PC14
#define HEADER_CONNECTOR_CN14_D10   PD9
#define HEADER_CONNECTOR_CN14_D11   PD1
#define HEADER_CONNECTOR_CN14_D12   PC13
#define HEADER_CONNECTOR_CN14_D13   PD2
#define HEADER_CONNECTOR_CN14_D14   PD13
#define HEADER_CONNECTOR_CN14_D15   PE9
#define HEADER_CONNECTOR_CN14_D16   PD7

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
