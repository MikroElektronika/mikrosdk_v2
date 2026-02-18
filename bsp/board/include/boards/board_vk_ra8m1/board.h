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

#define BOARD_NAME "RA8M1 Voice User Demonstration Kit"

#include "hal_target.h"

// Mapping
#define PMOD_CONNECTOR_D1   GPIO_P411
#define PMOD_CONNECTOR_D2   GPIO_P409
#define PMOD_CONNECTOR_D3   GPIO_P408
#define PMOD_CONNECTOR_D4   GPIO_P410
#define PMOD_CONNECTOR_D5   // Pin not routed.
#define PMOD_CONNECTOR_D6   // Pin not routed.
#define PMOD_CONNECTOR_D7   GPIO_P415
#define PMOD_CONNECTOR_D8   GPIO_P414
#define PMOD_CONNECTOR_D9   GPIO_P413
#define PMOD_CONNECTOR_D10  GPIO_P412
#define PMOD_CONNECTOR_D11  // Pin not routed.
#define PMOD_CONNECTOR_D12  // Pin not routed.

#define BUTTON1 GPIO_P400

#define LED1    GPIO_P414
#define LED2    GPIO_P405
#define LED3    GPIO_P406

#ifdef __cplusplus
}
#endif

#endif    // _BOARD_H_
// ------------------------------------------------------------------------- END
