/******************************************************************************
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
******************************************************************************/
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
 * @brief GPIO pin mask for lower 8 bits.
 *
 * @details
 * This macro defines a mask for the lower 8 bits (bits 0-7) of a GPIO port.
 * It is used to isolate or manipulate the lower byte of GPIO pins.
 */
#define GPIO_PIN_MASK_LOW                  (0x00FFUL)

/**
 * @brief GPIO pin mask for higher 8 bits.
 *
 * @details
 * This macro defines a mask for the higher 8 bits (bits 8-15) of a GPIO port.
 * It is used to isolate or manipulate the upper byte of GPIO pins.
 */
#define GPIO_PIN_MASK_HIGH                 (0xFF00UL)

/**
 * @brief GPIO pin mask for all 16 bits.
 *
 * @details
 * This macro defines a mask for all 16 bits of a GPIO port.
 * It is used to isolate or manipulate all pins of a GPIO port.
 */
#define GPIO_PIN_MASK_ALL                  (0xFFFFUL)

/**
 * @brief GPIO pin name mask.
 *
 * @details
 * This macro defines a mask for the lower 8 bits used for GPIO pin naming.
 * It is typically used to extract the pin number from a combined port-pin value.
 */
#define GPIO_PIN_NAME_MASK                 (0xFFUL)

/**
 * @brief GPIO alternate function IO port configuration mask.
 *
 * @details
 * This macro defines a mask used for configuring the GPIO alternate function IO port control register.
 * It is used to mask specific bits related to port configuration in the AFIO PCF0 register.
 */
#define GPIO_AFIO_PCF0_MASK                (0x3741FFFFUL)

/**
 * @brief GPIO control register mode input setting.
 *
 * @details
 * This macro defines the value to set the GPIO control register mode bits for input mode.
 * It configures the pin as an input.
 */
#define GPIO_CTL_MODE_INPUT                (0x0UL)

/**
 * @brief GPIO control register mode output speed 2 MHz setting.
 *
 * @details
 * This macro defines the value to set the GPIO control register mode bits for output mode with 2 MHz speed.
 * It configures the pin as an output with a maximum speed of 2 MHz.
 */
#define GPIO_CTL_MODE_OUTPUT_SPEED_M2      (0x2UL)

/**
 * @brief GPIO control register mode output speed 10 MHz setting.
 *
 * @details
 * This macro defines the value to set the GPIO control register mode bits for output mode with 10 MHz speed.
 * It configures the pin as an output with a maximum speed of 10 MHz.
 */
#define GPIO_CTL_MODE_OUTPUT_SPEED_M10     (0x1UL)

/**
 * @brief GPIO control register mode output speed 50 MHz setting.
 *
 * @details
 * This macro defines the value to set the GPIO control register mode bits for output mode with 50 MHz speed.
 * It configures the pin as an output with a maximum speed of 50 MHz.
 */
#define GPIO_CTL_MODE_OUTPUT_SPEED_M50     (0x3UL)

/**
 * @brief GPIO control register configuration for analog input.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for analog input mode.
 * It configures the pin as an analog input.
 */
#define GPIO_CTL_CFG_INPUT_ANALOG          (0x0UL)

/**
 * @brief GPIO control register configuration for floating input.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for floating input mode.
 * It configures the pin as a digital input with no pull-up or pull-down resistors.
 */
#define GPIO_CTL_CFG_INPUT_FLOATING        (0x4UL)

/**
 * @brief GPIO control register configuration for input with pull-up/pull-down.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for input mode with pull-up or pull-down resistors enabled.
 * It configures the pin as a digital input with internal pull-up or pull-down resistors.
 */
#define GPIO_CTL_CFG_INPUT_PUPD            (0x8UL)

/**
 * @brief GPIO control register configuration for general purpose output push-pull.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for output mode as general purpose push-pull.
 * It configures the pin as a digital output with push-pull type.
 */
#define GPIO_CTL_CFG_OUTPUT_GPIO_PP        (0x0UL)

/**
 * @brief GPIO control register configuration for general purpose output open-drain.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for output mode as general purpose open-drain.
 * It configures the pin as a digital output with open-drain type.
 */
#define GPIO_CTL_CFG_OUTPUT_GPIO_OD        (0x4UL)

/**
 * @brief GPIO control register configuration for alternate function output push-pull.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for output mode as alternate function push-pull.
 * It configures the pin as an alternate function output with push-pull type.
 */
#define GPIO_CTL_CFG_OUTPUT_AFIO_PP        (0x8UL)

/**
 * @brief GPIO control register configuration for alternate function output open-drain.
 *
 * @details
 * This macro defines the value to set the GPIO control register configuration bits for output mode as alternate function open-drain.
 * It configures the pin as an alternate function output with open-drain type.
 */
#define GPIO_CTL_CFG_OUTPUT_AFIO_OD        (0xCUL)

/**
 * @brief GPIO control register mask for configuration bits.
 *
 * @details
 * This macro defines a mask for the configuration bits in the GPIO control register.
 * It is used to isolate or modify the configuration bits of a GPIO pin.
 */
#define GPIO_MASK_BITS_CTL                 (0xCUL)

/**
 * @brief GPIO control register mask for mode bits.
 *
 * @details
 * This macro defines a mask for the mode bits in the GPIO control register.
 * It is used to isolate or modify the mode bits of a GPIO pin.
 */
#define GPIO_MASK_BITS_MD                  (0x3UL)

/**
 * @brief GPIO lock key bit position.
 *
 * @details
 * This macro defines the bit position of the lock key in the GPIO lock register.
 * It is used to identify the lock key bit for locking or unlocking GPIO configuration.
 */
#define GPIO_LOCK_KEY_BIT_POS              (16)

/**
 * @brief GPIO lock key bit mask.
 *
 * @details
 * This macro defines a mask for the lock key bit in the GPIO lock register.
 * It is used to set or clear the lock key bit for locking or unlocking GPIO configuration.
 */
#define GPIO_LOCK_KEY_BIT_MASK             (1UL << GPIO_LOCK_KEY_BIT_POS)

/**
 * @brief GPIO configuration for analog input.
 *
 * @details
 * This macro combines mode and configuration bits to set a GPIO pin as an analog input.
 * It uses input mode and analog input configuration.
 */
#define GPIO_CFG_ANALOG_INPUT              (GPIO_CTL_MODE_INPUT | GPIO_CTL_CFG_INPUT_ANALOG)

/**
 * @brief GPIO configuration for digital input.
 *
 * @details
 * This macro combines mode and configuration bits to set a GPIO pin as a digital input.
 * It uses input mode and floating input configuration.
 */
#define GPIO_CFG_DIGITAL_INPUT             (GPIO_CTL_MODE_INPUT | GPIO_CTL_CFG_INPUT_FLOATING)

/**
 * @brief GPIO configuration for digital output.
 *
 * @details
 * This macro combines mode and configuration bits to set a GPIO pin as a digital output.
 * It uses output mode with 50 MHz speed and general purpose push-pull configuration.
 */
#define GPIO_CFG_DIGITAL_OUTPUT            (GPIO_CTL_MODE_OUTPUT_SPEED_M50 | GPIO_CTL_CFG_OUTPUT_GPIO_PP)

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
