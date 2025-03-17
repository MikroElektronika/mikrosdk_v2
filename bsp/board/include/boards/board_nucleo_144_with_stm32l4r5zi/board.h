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

// Hardware revision number
#define BOARD_REV_MAJOR (B)
#define BOARD_REV_MINOR (01)

#define BOARD_NAME "Nucleo-L4R5ZI"

#include "hal_target.h"
#include "shield.h"

// Mapping
#define HEADER_CONNECTOR_CN11_D1  GPIO_PC10
#define HEADER_CONNECTOR_CN11_D2  GPIO_PC11
#define HEADER_CONNECTOR_CN11_D3  GPIO_PC12
#define HEADER_CONNECTOR_CN11_D4  GPIO_PD2
#define HEADER_CONNECTOR_CN11_D5       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D6       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D7  GPIO_PH3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D8       // Pin not routed.
#define HEADER_CONNECTOR_CN11_D9  GPIO_PF6  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D10      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D11 GPIO_PF7  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D12      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D13 GPIO_PA13
#define HEADER_CONNECTOR_CN11_D14      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D15 GPIO_PA14
#define HEADER_CONNECTOR_CN11_D16      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D17 GPIO_PA15 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D18      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D19      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D20      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D21 GPIO_PB7  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D22      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D23 GPIO_PC13 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D24      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D25      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D26      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D27      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D28 GPIO_PA0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D29 GPIO_PH0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D30 GPIO_PA1
#define HEADER_CONNECTOR_CN11_D31 GPIO_PH1
#define HEADER_CONNECTOR_CN11_D32 GPIO_PA4
#define HEADER_CONNECTOR_CN11_D33      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D34 GPIO_PB0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D35 GPIO_PC2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D36 GPIO_PC1
#define HEADER_CONNECTOR_CN11_D37 GPIO_PC3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D38 GPIO_PC0
#define HEADER_CONNECTOR_CN11_D39 GPIO_PD4  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D40 GPIO_PD3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D41 GPIO_PD5
#define HEADER_CONNECTOR_CN11_D42 GPIO_PG2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D43 GPIO_PD6
#define HEADER_CONNECTOR_CN11_D44 GPIO_PG3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D45 GPIO_PD7  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D46 GPIO_PE2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D47 GPIO_PE3  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D48 GPIO_PE4  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D49      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D50 GPIO_PE5  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D51 GPIO_PF1
#define HEADER_CONNECTOR_CN11_D52 GPIO_PF2  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D53 GPIO_PF0
#define HEADER_CONNECTOR_CN11_D54 GPIO_PF8  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D55 GPIO_PD1  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D56 GPIO_PF9  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D57 GPIO_PD0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D58 GPIO_PG1  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D59 GPIO_PG0  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D60      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D61 GPIO_PE1  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D62 GPIO_PE6  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D63 GPIO_PG9  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D64 GPIO_PG15 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D65 GPIO_PG12 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D66      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D67      // Pin not routed.
#define HEADER_CONNECTOR_CN11_D68 GPIO_PG13 // Pin not routed.
#define HEADER_CONNECTOR_CN11_D69 GPIO_PD9  // Pin not routed.
#define HEADER_CONNECTOR_CN11_D70 GPIO_PG11 // Pin not routed.

#define HEADER_CONNECTOR_CN12_D1  GPIO_PC9
#define HEADER_CONNECTOR_CN12_D2  GPIO_PC8
#define HEADER_CONNECTOR_CN12_D3  GPIO_PB8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D4  GPIO_PC6
#define HEADER_CONNECTOR_CN12_D5  GPIO_PB9  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D6  GPIO_PC5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D7       // Pin not routed.
#define HEADER_CONNECTOR_CN12_D8       // Pin not routed.
#define HEADER_CONNECTOR_CN12_D9       // Pin not routed.
#define HEADER_CONNECTOR_CN12_D10 GPIO_PD8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D11 GPIO_PA5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D12 GPIO_PA12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D13 GPIO_PA6  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D14 GPIO_PA11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D15 GPIO_PA7  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D16 GPIO_PB12
#define HEADER_CONNECTOR_CN12_D17 GPIO_PB6  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D18 GPIO_PB11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D19 GPIO_PC7
#define HEADER_CONNECTOR_CN12_D20      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D21 GPIO_PA9
#define HEADER_CONNECTOR_CN12_D22 GPIO_PB2  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D23 GPIO_PA8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D24 GPIO_PB1  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D25 GPIO_PB10 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D26 GPIO_PB15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D27 GPIO_PB4
#define HEADER_CONNECTOR_CN12_D28 GPIO_PB14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D29 GPIO_PB5
#define HEADER_CONNECTOR_CN12_D30 GPIO_PB13 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D31 GPIO_PB3
#define HEADER_CONNECTOR_CN12_D32      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D33 GPIO_PA10
#define HEADER_CONNECTOR_CN12_D34 GPIO_PC4  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D35 GPIO_PA2
#define HEADER_CONNECTOR_CN12_D36 GPIO_PF5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D37 GPIO_PA3
#define HEADER_CONNECTOR_CN12_D38 GPIO_PF4  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D39      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D40 GPIO_PE8  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D41 GPIO_PD13 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D42 GPIO_PF10 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D43 GPIO_PD12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D44 GPIO_PE7  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D45 GPIO_PD11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D46 GPIO_PD14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D47 GPIO_PE10 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D48 GPIO_PD15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D49 GPIO_PE12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D50 GPIO_PF14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D51 GPIO_PE14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D52 GPIO_PE9
#define HEADER_CONNECTOR_CN12_D53 GPIO_PE15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D54      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D55 GPIO_PE13 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D56 GPIO_PE11
#define HEADER_CONNECTOR_CN12_D57 GPIO_PF13
#define HEADER_CONNECTOR_CN12_D58 GPIO_PF3  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D59 GPIO_PF12 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D60 GPIO_PF15 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D61 GPIO_PG14 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D62 GPIO_PF11 // Pin not routed.
#define HEADER_CONNECTOR_CN12_D63      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D64 GPIO_PE0  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D65 GPIO_PD10
#define HEADER_CONNECTOR_CN12_D66      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D67 GPIO_PG7  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D68 GPIO_PG5  // Pin not routed.
#define HEADER_CONNECTOR_CN12_D69      // Pin not routed.
#define HEADER_CONNECTOR_CN12_D70      // Pin not routed.

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
