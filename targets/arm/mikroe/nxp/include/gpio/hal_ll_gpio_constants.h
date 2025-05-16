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
 * @brief GPIO Multiplexer offset macro.
 *
 * @details
 * Defines the offset value used for GPIO pin multiplexer configuration.
 * This offset is used to calculate the position of the multiplexer bits
 * within the GPIO configuration register.
 */
#define GPIO_MUX_OFFSET                    0x8UL

/**
 * @brief GPIO Pin name mask macro.
 *
 * @details
 * Defines the mask used to extract the pin name or number from a GPIO pin
 * identifier. This mask isolates the lower 5 bits which represent the pin.
 */
#define GPIO_PIN_NAME_MASK                 0x1FUL

/**
 * @brief GPIO Pull Select configuration macros.
 *
 * @details
 * Defines the macros for configuring the pull-up or pull-down resistors
 * on a GPIO pin.
 */
#define GPIO_CFG_PULL_UP                   0x1UL
#define GPIO_CFG_PULL_DOWN                 0x0

/**
 * @brief GPIO Pull Enable configuration macros.
 *
 * @details
 * Defines the macros for enabling or disabling the internal pull resistor
 * on a GPIO pin.
 */
#define GPIO_CFG_PULL_ENABLE               0x2UL
#define GPIO_CFG_PULL_DISABLE              0x0

/**
 * @brief GPIO Slew Rate configuration macros.
 *
 * @details
 * Defines the macros for configuring the slew rate of a GPIO pin, which
 * affects the speed of signal transitions.
 */
#define GPIO_CFG_SLEW_RATE_SLOW            0x4UL
#define GPIO_CFG_SLEW_RATE_FAST            0x0

/**
 * @brief GPIO Passive Filter configuration macros.
 *
 * @details
 * Defines the macros for enabling or disabling the passive input filter
 * on a GPIO pin to reduce noise.
 */
#define GPIO_CFG_PASSIVE_FILT_ENABLE       0x10UL
#define GPIO_CFG_PASSIVE_FILT_DISABLE      0x0

/**
 * @brief GPIO Open Drain configuration macros.
 *
 * @details
 * Defines the macros for enabling or disabling the open-drain output type
 * on a GPIO pin.
 */
#define GPIO_CFG_TYPE_OD_ENABLED           0x20UL
#define GPIO_CFG_TYPE_OD_DISABLED          0x0

/**
 * @brief GPIO Drive Strength configuration macros.
 *
 * @details
 * Defines the macros for configuring the drive strength of a GPIO pin,
 * which affects the current driving capability.
 */
#define GPIO_CFG_DRIVE_STRENGTH_HIGH       0x40UL
#define GPIO_CFG_DRIVE_STRENGTH_LOW        0x0

/**
 * @brief GPIO Mode configuration macros.
 *
 * @details
 * Defines the macros for setting the mode of a GPIO pin, such as analog,
 * input, output, or alternate function.
 */
#define GPIO_CFG_MODE_ANALOG               0x10000UL
#define GPIO_CFG_MODE_INPUT                0x20000UL
#define GPIO_CFG_MODE_OUTPUT               0x40000UL
#define GPIO_CFG_MODE_ALT_FUNCTION         0x80000UL

/**
 * @brief GPIO Pin Multiplexer Alternate Function macros.
 *
 * @details
 * Defines the macros for selecting the alternate function mode of a GPIO pin
 * through the multiplexer settings.
 */
#define GPIO_CFG_MUX_ALT0                  0x0UL
#define GPIO_CFG_MUX_ALT1                  0x100UL
#define GPIO_CFG_MUX_ALT2                  0x200UL
#define GPIO_CFG_MUX_ALT3                  0x300UL
#define GPIO_CFG_MUX_ALT4                  0x400UL
#define GPIO_CFG_MUX_ALT5                  0x500UL
#define GPIO_CFG_MUX_ALT6                  0x600UL
#define GPIO_CFG_MUX_ALT7                  0x700UL

/**
 * @brief GPIO Analog Input configuration macro.
 *
 * @details
 * Defines the configuration macro for setting a GPIO pin as an analog input.
 * This combines analog mode with the appropriate multiplexer setting.
 */
#define GPIO_CFG_ANALOG_INPUT              ( GPIO_CFG_MODE_ANALOG | GPIO_CFG_MUX_ALT0 )

/**
 * @brief GPIO Digital Input configuration macro.
 *
 * @details
 * Defines the configuration macro for setting a GPIO pin as a digital input.
 * This includes input mode, pull-up enabled, slow slew rate, passive filter
 * disabled, low drive strength, and multiplexer alternate function 1.
 */
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_ENABLE | GPIO_CFG_SLEW_RATE_SLOW | \
                                             GPIO_CFG_PASSIVE_FILT_DISABLE | GPIO_CFG_DRIVE_STRENGTH_LOW | GPIO_CFG_MUX_ALT1 )

/**
 * @brief GPIO Digital Output configuration macro.
 *
 * @details
 * Defines the configuration macro for setting a GPIO pin as a digital output.
 * This includes output mode, pull disabled, slow slew rate, passive filter
 * disabled, open-drain disabled, low drive strength, and multiplexer alternate
 * function 1.
 */
#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_PULL_DISABLE | GPIO_CFG_SLEW_RATE_SLOW | \
                                             GPIO_CFG_PASSIVE_FILT_DISABLE | GPIO_CFG_TYPE_OD_DISABLED | GPIO_CFG_DRIVE_STRENGTH_LOW | \
                                             GPIO_CFG_MUX_ALT1 )

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
