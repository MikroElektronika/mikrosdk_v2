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
 * @file  hal_ll_gpio_constants.h
 * @brief GPIO HAL LL macros.
 */

#ifndef _HAL_LL_GPIO_CONSTANTS_H_
#define _HAL_LL_GPIO_CONSTANTS_H_

#ifdef __cplusplus
extern "C"{
#endif

#define GPIO_CFG_PORT_DIRECTION_INPUT  (0x00000000) // Sets the pin direction to input (default)
#define GPIO_CFG_PORT_DIRECTION_OUTPUT (0x00000004) // Sets the pin direction to output
#define GPIO_CFG_PORT_OUTPUT_LOW       (0x00000000) // Sets the pin level to low
#define GPIO_CFG_PORT_OUTPUT_HIGH      (0x00000001) // Sets the pin level to high
#define GPIO_CFG_PULLUP_ENABLE         (0x00000010) // Enables the pin's internal pull-up
#define GPIO_CFG_PIM_TTL               (0x00000020) // Enables the pin's input mode
#define GPIO_CFG_NMOS_ENABLE           (0x00000040) // Enables the pin's NMOS open-drain output
#define GPIO_CFG_PMOS_ENABLE           (0x00000080) // Enables the pin's PMOS open-drain ouput
#define GPIO_CFG_DRIVE_MID             (0x00000400) // Sets pin drive output to medium
#define GPIO_CFG_DRIVE_HS_HIGH         (0x00000800) // Sets pin drive output to high along with supporting high speed
#define GPIO_CFG_DRIVE_MID_IIC         (0x00000800) // Sets pin to drive output needed for IIC on a 20mA port
#define GPIO_CFG_DRIVE_HIGH            (0x00000C00) // Sets pin drive output to high
#define GPIO_CFG_EVENT_RISING_EDGE     (0x00001000) // Sets pin event trigger to rising edge
#define GPIO_CFG_EVENT_FALLING_EDGE    (0x00002000) // Sets pin event trigger to falling edge
#define GPIO_CFG_EVENT_BOTH_EDGES      (0x00003000) // Sets pin event trigger to both edges
#define GPIO_CFG_IRQ_ENABLE            (0x00004000) // Sets pin as an IRQ pin
#define GPIO_CFG_ANALOG_ENABLE         (0x00008000) // Enables pin to operate as an analog pin
#define GPIO_CFG_PERIPHERAL_PIN        (0x00010000) // Enables pin to operate as a peripheral pin

#define GPIO_PRV_PFS_PSEL_OFFSET       (24)         // Peripheral function selection offset

#define GPIO_CFG_ANALOG_INPUT          ( GPIO_CFG_ANALOG_ENABLE | GPIO_CFG_PORT_DIRECTION_INPUT ) // TODO Esma
#define GPIO_CFG_DIGITAL_OUTPUT        ( GPIO_CFG_PORT_DIRECTION_OUTPUT ) // TODO Esma
#define GPIO_CFG_DIGITAL_INPUT         ( GPIO_CFG_PORT_DIRECTION_INPUT ) // TODO Esma

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
