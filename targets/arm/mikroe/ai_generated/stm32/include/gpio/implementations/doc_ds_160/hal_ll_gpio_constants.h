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
/**
 * @file  hal_ll_gpio_constants.h
 * @brief GPIO HAL LL macros.
 */

#ifndef _HAL_LL_GPIO_CONSTANTS_H_
#define _HAL_LL_GPIO_CONSTANTS_H_

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief GPIO OSPEEDER register mask for pin 0.
 *
 * @details
 * Defines the bit mask for the OSPEEDER register corresponding to pin 0.
 * Used to configure the output speed of GPIO pin 0.
 */
#ifndef GPIO_OSPEEDER_OSPEEDR0
#define GPIO_OSPEEDER_OSPEEDR0             ( uint32_t )0x03
#endif

/**
 * @brief GPIO MODER register mask for pin 0.
 *
 * @details
 * Defines the bit mask for the MODER register corresponding to pin 0.
 * Used to configure the mode of GPIO pin 0.
 */
#ifndef GPIO_MODER_MODER0
#define GPIO_MODER_MODER0                  ( uint32_t )0x03
#endif

/**
 * @brief GPIO OTYPER register mask for pin 0.
 *
 * @details
 * Defines the bit mask for the OTYPER register corresponding to pin 0.
 * Used to configure the output type (push-pull or open-drain) of GPIO pin 0.
 */
#ifndef GPIO_OTYPER_OT_0
#define GPIO_OTYPER_OT_0                   ( uint32_t )0x01
#endif

/**
 * @brief GPIO PUPDR register mask for pin 0.
 *
 * @details
 * Defines the bit mask for the PUPDR register corresponding to pin 0.
 * Used to configure the pull-up/pull-down resistors of GPIO pin 0.
 */
#ifndef GPIO_PUPDR_PUPDR0
#define GPIO_PUPDR_PUPDR0                  ( uint32_t )0x03
#endif

/**
 * @brief GPIO pin mask for lower 8 pins.
 *
 * @details
 * Defines a mask for the lower 8 GPIO pins (pins 0 to 7).
 * Used for operations targeting the lower half of GPIO pins.
 */
#ifndef GPIO_PIN_MASK_LOW
#define GPIO_PIN_MASK_LOW                  ( uint32_t )0x00FF
#endif

/**
 * @brief GPIO pin mask for higher 8 pins.
 *
 * @details
 * Defines a mask for the higher 8 GPIO pins (pins 8 to 15).
 * Used for operations targeting the upper half of GPIO pins.
 */
#ifndef GPIO_PIN_MASK_HIGH
#define GPIO_PIN_MASK_HIGH                 ( uint32_t )0xFF00
#endif

/**
 * @brief GPIO pin mask for all 16 pins.
 *
 * @details
 * Defines a mask for all 16 GPIO pins (pins 0 to 15).
 * Used for operations targeting all GPIO pins.
 */
#ifndef GPIO_PIN_MASK_ALL
#define GPIO_PIN_MASK_ALL                  ( uint32_t )0xFFFF
#endif

/**
 * @brief GPIO alternate function configuration offset.
 *
 * @details
 * Defines the bit offset used for alternate function configuration in GPIO registers.
 */
#ifndef GPIO_AF_CONFIG_OFFSET
#define GPIO_AF_CONFIG_OFFSET              ( uint32_t )20
#endif

/**
 * @brief GPIO alternate function mask.
 *
 * @details
 * Defines the mask used to extract or set the alternate function bits in GPIO registers.
 */
#ifndef GPIO_AF_MASK
#define GPIO_AF_MASK                       ( 0x0F )
#endif

/**
 * @brief GPIO pin name mask.
 *
 * @details
 * Defines the mask used to extract the pin name or number from a GPIO configuration.
 */
#ifndef GPIO_PIN_NAME_MASK
#define GPIO_PIN_NAME_MASK                 ( ( uint32_t )0xFF )
#endif

/**
 * @brief GPIO alternate function configuration mask.
 *
 * @details
 * Defines the mask used to extract or set the alternate function configuration bits in GPIO registers.
 */
#ifndef GPIO_AF_CONFIG_MASK
#define GPIO_AF_CONFIG_MASK                ( ( uint32_t )0x0F << GPIO_AF_CONFIG_OFFSET )
#endif

/**
 * @brief GPIO configuration mode for analog mode.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin to analog mode.
 */
#ifndef GPIO_CFG_MODE_ANALOG
#define GPIO_CFG_MODE_ANALOG               ( uint32_t )0x1
#endif

/**
 * @brief GPIO configuration mode for input mode.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin to input mode.
 */
#ifndef GPIO_CFG_MODE_INPUT
#define GPIO_CFG_MODE_INPUT                ( uint32_t )0x2
#endif

/**
 * @brief GPIO configuration mode for output mode.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin to output mode.
 */
#ifndef GPIO_CFG_MODE_OUTPUT
#define GPIO_CFG_MODE_OUTPUT               ( uint32_t )0x4
#endif

/**
 * @brief GPIO configuration mode for alternate function mode.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin to alternate function mode.
 */
#ifndef GPIO_CFG_MODE_ALT_FUNCTION
#define GPIO_CFG_MODE_ALT_FUNCTION         ( uint32_t )0x8
#endif

/**
 * @brief GPIO configuration output type push-pull.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin output type to push-pull.
 */
#ifndef GPIO_CFG_OTYPE_PP
#define GPIO_CFG_OTYPE_PP                  ( uint32_t )0x10
#endif

/**
 * @brief GPIO configuration output type open-drain.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin output type to open-drain.
 */
#ifndef GPIO_CFG_OTYPE_OD
#define GPIO_CFG_OTYPE_OD                  ( uint32_t )0x20
#endif

/**
 * @brief GPIO configuration for no pull-up or pull-down.
 *
 * @details
 * Defines the configuration value for disabling pull-up and pull-down resistors on a GPIO pin.
 */
#ifndef GPIO_CFG_PULL_NO
#define GPIO_CFG_PULL_NO                   ( uint32_t )0x40
#endif

/**
 * @brief GPIO configuration for pull-up resistor enabled.
 *
 * @details
 * Defines the configuration value for enabling the pull-up resistor on a GPIO pin.
 */
#ifndef GPIO_CFG_PULL_UP
#define GPIO_CFG_PULL_UP                   ( uint32_t )0x80
#endif

/**
 * @brief GPIO configuration for pull-down resistor enabled.
 *
 * @details
 * Defines the configuration value for enabling the pull-down resistor on a GPIO pin.
 */
#ifndef GPIO_CFG_PULL_DOWN
#define GPIO_CFG_PULL_DOWN                 ( uint32_t )0x100
#endif

/**
 * @brief GPIO configuration speed low.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin speed to low.
 */
#ifndef GPIO_CFG_SPEED_LOW
#define GPIO_CFG_SPEED_LOW                 ( uint32_t )0x0
#endif

/**
 * @brief GPIO configuration speed medium.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin speed to medium.
 */
#ifndef GPIO_CFG_SPEED_MEDIUM
#define GPIO_CFG_SPEED_MEDIUM              ( uint32_t )0x200
#endif

/**
 * @brief GPIO configuration speed high.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin speed to high.
 */
#ifndef GPIO_CFG_SPEED_HIGH
#define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x400
#endif

/**
 * @brief GPIO configuration speed very high.
 *
 * @details
 * Defines the configuration value for setting a GPIO pin speed to very high.
 */
#ifndef GPIO_CFG_SPEED_VERY_HIGH
#define GPIO_CFG_SPEED_VERY_HIGH           ( uint32_t )0x800
#endif

/**
 * @brief GPIO configuration maximum speed.
 *
 * @details
 * Defines the configuration value representing the maximum GPIO pin speed.
 */
#ifndef GPIO_CFG_SPEED_MAX
#define GPIO_CFG_SPEED_MAX                 ( uint32_t )0x80000
#endif

/**
 * @brief GPIO AHB bus shift value.
 *
 * @details
 * Defines the bit shift value used for AHB bus configuration in GPIO registers.
 */
#ifndef GPIO_AHB_SHIFT
#define GPIO_AHB_SHIFT                     17
#endif

/**
 * @brief GPIO configuration for digital output.
 *
 * @details
 * Defines the combined configuration value for setting a GPIO pin as digital output
 * with maximum speed and push-pull output type.
 */
#ifndef GPIO_CFG_DIGITAL_OUTPUT
#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_SPEED_MAX | GPIO_CFG_OTYPE_PP )
#endif

/**
 * @brief GPIO configuration for digital input.
 *
 * @details
 * Defines the combined configuration value for setting a GPIO pin as digital input
 * with no pull-up or pull-down resistors.
 */
#ifndef GPIO_CFG_DIGITAL_INPUT
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_NO )
#endif

/**
 * @brief GPIO configuration for analog input.
 *
 * @details
 * Defines the combined configuration value for setting a GPIO pin as analog input
 * with no pull-up or pull-down resistors.
 */
#ifndef GPIO_CFG_ANALOG_INPUT
#define GPIO_CFG_ANALOG_INPUT              ( GPIO_CFG_MODE_ANALOG | GPIO_CFG_PULL_NO )
#endif

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
