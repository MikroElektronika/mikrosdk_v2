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

// TODO - Define macros for GPIO here!
#ifndef GPIO_OSPEEDER_OSPEEDR0
#define GPIO_OSPEEDER_OSPEEDR0             ( uint32_t )0x03
#endif
#ifndef GPIO_MODER_MODER0
#define GPIO_MODER_MODER0                  ( uint32_t )0x03
#endif
#ifndef GPIO_OTYPER_OT_0
#define GPIO_OTYPER_OT_0                   ( uint32_t )0x01
#endif
#ifndef GPIO_PUPDR_PUPDR0
#define GPIO_PUPDR_PUPDR0                  ( uint32_t )0x03
#endif

#ifndef GPIO_PIN_MASK_LOW
#define GPIO_PIN_MASK_LOW                  ( uint32_t )0x00FF
#endif
#ifndef GPIO_PIN_MASK_HIGH
#define GPIO_PIN_MASK_HIGH                 ( uint32_t )0xFF00
#endif
#ifndef GPIO_PIN_MASK_ALL
#define GPIO_PIN_MASK_ALL                  ( uint32_t )0xFFFF
#endif

#ifndef GPIO_AF_CONFIG_OFFSET
#define GPIO_AF_CONFIG_OFFSET              ( uint32_t )20
#endif
#ifndef GPIO_AF_MASK
#define GPIO_AF_MASK                       ( 0x0F )
#endif
#ifndef GPIO_PIN_NAME_MASK
#define GPIO_PIN_NAME_MASK                 ( ( uint32_t )0xFF )
#endif
#ifndef GPIO_AF_CONFIG_MASK
#define GPIO_AF_CONFIG_MASK                ( ( uint32_t )0x0F << GPIO_AF_CONFIG_OFFSET )
#endif

#ifndef GPIO_CFG_MODE_ANALOG
#define GPIO_CFG_MODE_ANALOG               ( uint32_t )0x1
#endif
#ifndef GPIO_CFG_MODE_INPUT
#define GPIO_CFG_MODE_INPUT                ( uint32_t )0x2
#endif
#ifndef GPIO_CFG_MODE_OUTPUT
#define GPIO_CFG_MODE_OUTPUT               ( uint32_t )0x4
#endif
#ifndef GPIO_CFG_MODE_ALT_FUNCTION
#define GPIO_CFG_MODE_ALT_FUNCTION         ( uint32_t )0x8
#endif
#ifndef GPIO_CFG_OTYPE_PP
#define GPIO_CFG_OTYPE_PP                  ( uint32_t )0x10
#endif
#ifndef GPIO_CFG_OTYPE_OD
#define GPIO_CFG_OTYPE_OD                  ( uint32_t )0x20
#endif
#ifndef GPIO_CFG_PULL_NO
#define GPIO_CFG_PULL_NO                   ( uint32_t )0x40
#endif
#ifndef GPIO_CFG_PULL_UP
#define GPIO_CFG_PULL_UP                   ( uint32_t )0x80
#endif
#ifndef GPIO_CFG_PULL_DOWN
#define GPIO_CFG_PULL_DOWN                 ( uint32_t )0x100
#endif
#ifndef GPIO_CFG_SPEED_LOW
#define GPIO_CFG_SPEED_LOW                 ( uint32_t )0x0
#endif
#ifndef GPIO_CFG_SPEED_MEDIUM
#define GPIO_CFG_SPEED_MEDIUM              ( uint32_t )0x200
#endif
#ifndef GPIO_CFG_SPEED_HIGH
#define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x400
#endif
#ifndef GPIO_CFG_SPEED_VERY_HIGH
#define GPIO_CFG_SPEED_VERY_HIGH           ( uint32_t )0x800
#endif
#ifndef GPIO_CFG_SPEED_MAX
#define GPIO_CFG_SPEED_MAX                 ( uint32_t )0x80000
#endif

#ifndef GPIO_AHB_SHIFT
#define GPIO_AHB_SHIFT                     17
#endif

#define GPIO_CFG_PORT_OUTPUT_HIGH         (0x00000001UL) // Sets the output level to HIGH (only valid for output pins)
#define GPIO_CFG_PORT_OUTPUT_LOW          (0x00000000UL) // Sets the output level to LOW (only valid for output pins)
#define GPIO_CFG_PORT_DIRECTION_OUTPUT    (0x00000004UL) // Configures the pin direction as OUTPUT
#define GPIO_CFG_PORT_DIRECTION_INPUT     (0x00000000UL) // Configures the pin direction as INPUT
#define GPIO_CFG_PORT_PULL_UP_ENABLE      (0x00000010UL) // Enables the internal pull-up resistor
#define GPIO_CFG_NMOS_OPEN_DRAIN_ENABLE   (0x00000040UL) // Enables NMOS open-drain output (drives low or floats)
#define GPIO_CFG_PORT_LOW_DRIVE           (0x00000000UL) // Sets the output drive strength to LOW
#define GPIO_CFG_PORT_MIDDLE_DRIVE        (0x00000400UL) // Sets the output drive strength to MIDDLE
#define GPIO_CFG_PORT_MIDDLE_DRIVE_P408   (0x00000800UL) // Sets the output drive strength to MIDDLE for IIC Fast-mode
#define GPIO_CFG_EVENT_RISING_EDGE        (0x00001000UL) // Configures the pin to trigger an event on rising edge
#define GPIO_CFG_EVENT_FALLING_EDGE       (0x00002000UL) // Configures the pin to trigger an event on falling edge
#define GPIO_CFG_EVENT_BOTH_EDGES         (0x00003000UL) // Configures the pin to trigger an event on both edges
#define GPIO_CFG_IRQ_ENABLE               (0x00004000UL) // Enables interrupt generation for this pin
#define GPIO_CFG_ANALOG_ENABLE            (0x00008000UL) // Configures the pin to operate in analog mode
#define GPIO_CFG_PERIPHERAL_PIN           (0x00010000UL) // Configures the pin for peripheral function (not GPIO)

#define GPIO_PRV_PFS_PSEL_OFFSET          (24)           // Bit offset for Peripheral Function Selection (PSEL)
#define GPIO_PRV_PFS_PSEL_MASK            (0x1F000000UL) // Bit mask for Peripheral Function Selection (PSEL)

#define GPIO_CFG_ANALOG_INPUT             ( GPIO_CFG_ANALOG_ENABLE | GPIO_CFG_PORT_DIRECTION_INPUT )
#define GPIO_CFG_DIGITAL_OUTPUT           ( GPIO_CFG_PORT_DIRECTION_OUTPUT )
#define GPIO_CFG_DIGITAL_INPUT            ( GPIO_CFG_PORT_DIRECTION_INPUT )

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END