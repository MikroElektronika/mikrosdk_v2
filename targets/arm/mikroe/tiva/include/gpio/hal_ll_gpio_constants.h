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
 * @brief GPIO configuration mode for input.
 *
 * @details
 * Defines the configuration mode value for setting a GPIO pin as input.
 */
#define GPIO_CFG_MODE_INPUT                0x0UL

/**
 * @brief GPIO configuration mode for output.
 *
 * @details
 * Defines the configuration mode value for setting a GPIO pin as output.
 */
#define GPIO_CFG_MODE_OUTPUT               0x1UL

/**
 * @brief GPIO direction input.
 *
 * @details
 * Defines the direction value representing input mode for GPIO pins.
 */
#define GPIO_DIR_INPUT                     0

/**
 * @brief GPIO direction output.
 *
 * @details
 * Defines the direction value representing output mode for GPIO pins.
 */
#define GPIO_DIR_OUTPUT                    1

/**
 * @brief GPIO pull-up resistor configuration.
 *
 * @details
 * Defines the configuration flag to enable internal pull-up resistor on a GPIO pin.
 */
#define GPIO_CFG_PULL_UP                   0x1UL

/**
 * @brief GPIO pull-down resistor configuration.
 *
 * @details
 * Defines the configuration flag to enable internal pull-down resistor on a GPIO pin.
 */
#define GPIO_CFG_PULL_DOWN                 0x2UL

/**
 * @brief GPIO open-drain configuration.
 *
 * @details
 * Defines the configuration flag to set a GPIO pin as open-drain.
 */
#define GPIO_CFG_OPEN_DRAIN                0x8UL

/**
 * @brief GPIO drive strength 2mA configuration.
 *
 * @details
 * Defines the configuration flag to set GPIO pin drive strength to 2mA.
 */
#define GPIO_CFG_DRIVE_2mA                 0x10UL

/**
 * @brief GPIO drive strength 4mA configuration.
 *
 * @details
 * Defines the configuration flag to set GPIO pin drive strength to 4mA.
 */
#define GPIO_CFG_DRIVE_4mA                 0x20UL

/**
 * @brief GPIO drive strength 8mA configuration.
 *
 * @details
 * Defines the configuration flag to set GPIO pin drive strength to 8mA.
 */
#define GPIO_CFG_DRIVE_8mA                 0x40UL

/**
 * @brief GPIO slew rate configuration.
 *
 * @details
 * Defines the configuration flag to enable slew rate control on a GPIO pin.
 */
#define GPIO_CFG_SLEW_RATE                 0x80UL

/**
 * @brief GPIO digital enable configuration.
 *
 * @details
 * Defines the configuration flag to enable digital functionality on a GPIO pin.
 */
#define GPIO_CFG_DIGITAL_ENABLE            0x100UL

/**
 * @brief GPIO isolation disable configuration.
 *
 * @details
 * Defines the configuration flag to disable isolation on a GPIO pin.
 */
#define GPIO_CFG_ISOLATION_DISABLE         0x200UL

/**
 * @brief GPIO alternate function configuration.
 *
 * @details
 * Defines the configuration flag to enable alternate function mode on a GPIO pin.
 */
#define GPIO_CFG_ALT_FUNCTION              0x400UL

/**
 * @brief GPIO ADC source trigger configuration.
 *
 * @details
 * Defines the configuration flag to enable ADC source trigger on a GPIO pin.
 */
#define GPIO_CFG_ADC_SRC_TRIGGER           0x800UL

/**
 * @brief GPIO drive strength 6mA configuration.
 *
 * @details
 * Defines the configuration flag to set GPIO pin drive strength to 6mA.
 */
#define GPIO_CFG_DRIVE_6mA                 0x1000UL

/**
 * @brief GPIO drive strength 10mA configuration.
 *
 * @details
 * Defines the configuration flag to set GPIO pin drive strength to 10mA.
 */
#define GPIO_CFG_DRIVE_10mA                0x2000UL

/**
 * @brief GPIO drive strength 12mA configuration.
 *
 * @details
 * Defines the configuration flag to set GPIO pin drive strength to 12mA.
 */
#define GPIO_CFG_DRIVE_12mA                0x4000UL

/**
 * @brief GPIO advanced analog input configuration.
 *
 * @details
 * Combination of alternate function and isolation disable flags used for advanced analog input configuration.
 */
#define GPIO_CFG_ADV_AIN                   ( GPIO_CFG_ALT_FUNCTION | GPIO_CFG_ISOLATION_DISABLE )

/**
 * @brief GPIO digital output configuration.
 *
 * @details
 * Combination of direction output, digital enable, and 8mA drive strength flags used for digital output configuration.
 */
#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_DIR_OUTPUT | GPIO_CFG_DIGITAL_ENABLE | GPIO_CFG_DRIVE_8mA )

/**
 * @brief GPIO digital input configuration.
 *
 * @details
 * Combination of direction input, digital enable, and 8mA drive strength flags used for digital input configuration.
 */
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_DIR_INPUT  | GPIO_CFG_DIGITAL_ENABLE | GPIO_CFG_DRIVE_8mA )

/**
 * @brief GPIO analog input configuration.
 *
 * @details
 * Combination of direction input and advanced analog input flags used for analog input configuration.
 */
#define GPIO_CFG_ANALOG_INPUT              ( GPIO_DIR_INPUT  | GPIO_CFG_ADV_AIN )

/**
 * @brief GPIO direction register offset.
 *
 * @details
 * Defines the offset value for the GPIO direction register.
 */
#define _HAL_GPIO_DIR_OFFSET               ( 0x400UL / 4 )

/**
 * @brief GPIO port control register offset.
 *
 * @details
 * Defines the offset value for the GPIO port control register.
 */
#define _HAL_GPIO_GPIOPC_OFFSET            ( 0xFC4UL / 4 )

/**
 * @brief GPIO open drain register offset.
 *
 * @details
 * Defines the offset value for the GPIO open drain register.
 */
#define _HAL_GPIO_GPIOODR_OFFSET           ( 0x50CUL / 4 )

/**
 * @brief GPIO pull-up resistor register offset.
 *
 * @details
 * Defines the offset value for the GPIO pull-up resistor register.
 */
#define _HAL_GPIO_GPIOPUR_OFFSET           ( 0x510UL / 4 )

/**
 * @brief GPIO pull-down resistor register offset.
 *
 * @details
 * Defines the offset value for the GPIO pull-down resistor register.
 */
#define _HAL_GPIO_GPIOPDR_OFFSET           ( 0x514UL / 4 )

/**
 * @brief GPIO slew rate register offset.
 *
 * @details
 * Defines the offset value for the GPIO slew rate register.
 */
#define _HAL_GPIO_GPIOSLR_OFFSET           ( 0x518UL / 4 )

/**
 * @brief GPIO digital enable register offset.
 *
 * @details
 * Defines the offset value for the GPIO digital enable register.
 */
#define _HAL_GPIO_GPIODEN_OFFSET           ( 0x518UL / 4 )

/**
 * @brief GPIO 2mA drive strength register offset.
 *
 * @details
 * Defines the offset value for the GPIO 2mA drive strength register.
 */
#define _HAL_GPIO_GPIODR2R_OFFSET          ( 0x500UL / 4 )

/**
 * @brief GPIO 4mA drive strength register offset.
 *
 * @details
 * Defines the offset value for the GPIO 4mA drive strength register.
 */
#define _HAL_GPIO_GPIODR4R_OFFSET          ( 0x504UL / 4 )

/**
 * @brief GPIO 8mA drive strength register offset.
 *
 * @details
 * Defines the offset value for the GPIO 8mA drive strength register.
 */
#define _HAL_GPIO_GPIODR8R_OFFSET          ( 0x508UL / 4 )

/**
 * @brief GPIO 12mA drive strength register offset.
 *
 * @details
 * Defines the offset value for the GPIO 12mA drive strength register.
 */
#define _HAL_GPIO_GPIODR12R_OFFSET         ( 0x53CUL / 4 )

/**
 * @brief GPIO analog mode select register offset.
 *
 * @details
 * Defines the offset value for the GPIO analog mode select register.
 */
#define _HAL_GPIO_GPIOAMSEL_OFFSET         ( 0x528UL / 4 )

/**
 * @brief GPIO alternate function select register offset.
 *
 * @details
 * Defines the offset value for the GPIO alternate function select register.
 */
#define _HAL_GPIO_GPIOAFSEL_OFFSET         ( 0x420UL / 4 )

/**
 * @brief GPIO ADC control register offset.
 *
 * @details
 * Defines the offset value for the GPIO ADC control register.
 */
#define _HAL_GPIO_GPIOADCCTL_OFFSET        ( 0x530UL / 4 )

/**
 * @brief GPIO pin name mask.
 *
 * @details
 * Mask used to extract the pin name from a GPIO pin identifier.
 */
#define GPIO_PIN_NAME_MASK                 ( uint32_t )0xFF

/**
 * @brief GPIO alternate function mask.
 *
 * @details
 * Mask used to extract the alternate function value from a GPIO pin configuration.
 */
#define GPIO_AF_MASK                       0x0F

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
