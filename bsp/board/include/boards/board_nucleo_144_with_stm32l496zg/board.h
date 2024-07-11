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

// Hardware revision number
#define BOARD_REV_MAJOR (B)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Nucleo-L496ZG"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_CN11_D1  PC10
#define HEADER_CONNECTOR_CN11_D2  PC11
#define HEADER_CONNECTOR_CN11_D3  PC12
#define HEADER_CONNECTOR_CN11_D4  PD2
#define HEADER_CONNECTOR_CN11_D5       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D6       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D7       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D8       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D9  PF6  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D10      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D11 PF7  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D12      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D13 PA13
#define HEADER_CONNECTOR_CN11_D14      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D15 PA14
#define HEADER_CONNECTOR_CN11_D16      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D17 PA15 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D18      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D19      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D20      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D21 PB7  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D22      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D23 PC13 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D24      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D25      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D26      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D27      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D28 PA0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D29 PH0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D30 PA1
#define HEADER_CONNECTOR_CN11_D31 PH1
#define HEADER_CONNECTOR_CN11_D32 PA4
#define HEADER_CONNECTOR_CN11_D33      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D34 PB0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D35 PC2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D36 PC1
#define HEADER_CONNECTOR_CN11_D37 PC3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D38 PC0
#define HEADER_CONNECTOR_CN11_D39 PD4  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D40 PD3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D41 PD5
#define HEADER_CONNECTOR_CN11_D42 PG2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D43 PD6
#define HEADER_CONNECTOR_CN11_D44 PG3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D45 PD7  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D46 PE2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D47 PE3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D48 PE4  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D49      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D50 PE5  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D51 PF1
#define HEADER_CONNECTOR_CN11_D52 PF2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D53 PF0
#define HEADER_CONNECTOR_CN11_D54 PF8  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D55 PD1  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D56 PF9  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D57 PD0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D58 PG1  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D59 PG0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D60      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D61 PE1  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D62 PE6  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D63 PG9  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D64 PG15 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D65 PG12 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D66      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D67      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D68 PG13 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D69 PD9  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D70 PG11 // Pin not routed.

#define HEADER_CONNECTOR_CN12_D1  PC9
#define HEADER_CONNECTOR_CN12_D2  PC8
#define HEADER_CONNECTOR_CN12_D3  PB8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D4  PC6
#define HEADER_CONNECTOR_CN12_D5  PB9  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D6  PC5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D7       // Pin not routed.
#define HEADER_CONNECTOR_CN12_D8       // Pin not routed.
#define HEADER_CONNECTOR_CN12_D9       // Pin not routed.
#define HEADER_CONNECTOR_CN12_D10 PD8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D11 PA5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D12 PA12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D13 PA6  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D14 PA11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D15 PA7  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D16 PB12
#define HEADER_CONNECTOR_CN12_D17 PB6  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D18 PB11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D19 PC7
#define HEADER_CONNECTOR_CN12_D20      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D21 PA9
#define HEADER_CONNECTOR_CN12_D22 PB2  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D23 PA8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D24 PB1  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D25 PB10 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D26 PB15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D27 PB4
#define HEADER_CONNECTOR_CN12_D28 PB14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D29 PB5
#define HEADER_CONNECTOR_CN12_D30 PB13 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D31 PB3
#define HEADER_CONNECTOR_CN12_D32      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D33 PA10
#define HEADER_CONNECTOR_CN12_D34 PC4  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D35 PA2
#define HEADER_CONNECTOR_CN12_D36 PF5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D37 PA3
#define HEADER_CONNECTOR_CN12_D38 PF4  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D39      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D40 PE8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D41 PD13 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D42 PF10 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D43 PD12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D44 PE7  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D45 PD11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D46 PD14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D47 PE10 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D48 PD15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D49 PE12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D50 PF14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D51 PE14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D52 PE9
#define HEADER_CONNECTOR_CN12_D53 PE15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D54      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D55 PE13 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D56 PE11
#define HEADER_CONNECTOR_CN12_D57 PF13
#define HEADER_CONNECTOR_CN12_D58 PF3  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D59 PF12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D60 PF15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D61 PG14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D62 PF11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D63      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D64 PE0  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D65 PD10
#define HEADER_CONNECTOR_CN12_D66      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D67 PG7  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D68 PG5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D69      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D70      // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
