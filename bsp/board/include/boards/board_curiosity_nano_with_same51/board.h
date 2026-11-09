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

#define BOARD_NAME "SAM E51 CURIOSITY NANO EVALUATION KIT"

#include "hal_target.h"
#include "shield.h"

// Mapping
// Header connector
#define HEADER_CONNECTOR_HC1_PIN7   GPIO_PB12
#define HEADER_CONNECTOR_HC1_PIN8   GPIO_PB13
#define HEADER_CONNECTOR_HC1_PIN9   GPIO_PA12
#define HEADER_CONNECTOR_HC1_PIN10  GPIO_PA13
#define HEADER_CONNECTOR_HC1_PIN11  GPIO_PA16
#define HEADER_CONNECTOR_HC1_PIN12  GPIO_PA19
#define HEADER_CONNECTOR_HC1_PIN13  GPIO_PA17
#define HEADER_CONNECTOR_HC1_PIN14  GPIO_PA18
#define HEADER_CONNECTOR_HC1_PIN16  GPIO_PA8
#define HEADER_CONNECTOR_HC1_PIN17  GPIO_PA9
#define HEADER_CONNECTOR_HC1_PIN18  GPIO_PB14
#define HEADER_CONNECTOR_HC1_PIN19  GPIO_PA6

#define HEADER_CONNECTOR_HC2_PIN7   GPIO_PA7
#define HEADER_CONNECTOR_HC2_PIN8   GPIO_PA4
#define HEADER_CONNECTOR_HC2_PIN9   GPIO_PB9
#define HEADER_CONNECTOR_HC2_PIN10  GPIO_PA11
#define HEADER_CONNECTOR_HC2_PIN11  GPIO_PA10
#define HEADER_CONNECTOR_HC2_PIN12  GPIO_PB8
#define HEADER_CONNECTOR_HC2_PIN13  GPIO_PB3
#define HEADER_CONNECTOR_HC2_PIN14  GPIO_PA2
#define HEADER_CONNECTOR_HC2_PIN16  GPIO_PB4
#define HEADER_CONNECTOR_HC2_PIN17  GPIO_PB5
#define HEADER_CONNECTOR_HC2_PIN18  GPIO_PB6
#define HEADER_CONNECTOR_HC2_PIN19  GPIO_PB7

#define BUTTON0    GPIO_PA15

#define LED0       GPIO_PA14

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
