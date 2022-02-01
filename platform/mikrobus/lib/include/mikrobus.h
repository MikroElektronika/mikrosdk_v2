/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  mikrobus.h
 * @brief Implements mikroBUS socket.
 */

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _MIKROBUS_H_
#define _MIKROBUS_H_

#define MIKROBUS_AN AN      /*!< mikroBUS AN pin. */
#define MIKROBUS_RST RST    /*!< mikroBUS RST pin. */
#define MIKROBUS_CS CS      /*!< mikroBUS CS pin. */
#define MIKROBUS_SCK SCK    /*!< mikroBUS SCK pin. */
#define MIKROBUS_MISO MISO  /*!< mikroBUS MISO pin. */
#define MIKROBUS_MOSI MOSI  /*!< mikroBUS MOSI pin. */
#define MIKROBUS_PWM PWM    /*!< mikroBUS PWM pin. */
#define MIKROBUS_INT INT    /*!< mikroBUS INT pin. */
#define MIKROBUS_RX RX      /*!< mikroBUS RX pin. */
#define MIKROBUS_TX TX      /*!< mikroBUS TX pin. */
#define MIKROBUS_SCL SCL    /*!< mikroBUS SCL pin. */
#define MIKROBUS_SDA SDA    /*!< mikroBUS SDA pin. */

/*!
 * @brief Concatenate mikroBUS index with pin.
 * @details This macro creates mikroBUS pin macro on coresponding mikroBUS index.
 */
#define MIKROBUS(index, pinout) MIKROBUS_IMPL(index, pinout)
#define MIKROBUS_IMPL(index, pinout) MIKROBUS_##index##_##pinout

#ifdef __cplusplus
}
#endif

#endif // _MIKROBUS_H_
// ------------------------------------------------------------------------- END
