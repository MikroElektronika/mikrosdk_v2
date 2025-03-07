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
** OF MERCHANTABILITY, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
/*!
* @file hal_ll_errata.c
* @brief ERRATA HAL LOW LEVEL layer implementation.
*/

#include "hal_ll_errata.h"
#include "delays.h"

#ifdef PIC32MZxEC_ERRATA
void hal_ll_errata_i2c_master_stop( hal_ll_pin_name_t scl_pin, hal_ll_pin_name_t sda_pin, uint32_t delay_time, uint32_t i2ccon_reg ) {
    /*
    * According to the Errata document for the EC family of MCUs,
    * the hardware Master Stop control (PEN bit) does not function as expected.
    *
    * `hal_ll_errata_i2c_master_stop` function implements a software-based Stop condition
    * by manually controlling the SDA and SCL pins and using software delays to ensure proper timing.
    */

    // Position of the `ON` bit in the I2CxCON register needed
    // for enabling and disabling the I2C module.
    #define HAL_LL_I2CCON_ON_BIT (15)

    hal_ll_gpio_pin_t sda;
    hal_ll_gpio_pin_t scl;

    hal_ll_gpio_configure_pin( &scl, scl_pin, HAL_LL_GPIO_DIGITAL_OUTPUT );
    hal_ll_gpio_configure_pin( &sda, sda_pin, HAL_LL_GPIO_DIGITAL_INPUT );

    // Clear the LAT bit of the SDA pin.
    hal_ll_gpio_clear_pin_output( &sda );

    // Clear the TRIS bit of the SDA pin to be configured as an output.
    hal_ll_gpio_configure_pin( &sda, sda_pin, HAL_LL_GPIO_DIGITAL_OUTPUT );

    // Set the LAT bit of the SCL pin.
    hal_ll_gpio_write_pin_output( &scl, 1 );

    // Set the TRIS bit of the SCL pin to be configured as an input.
    hal_ll_gpio_configure_pin( &scl, scl_pin, HAL_LL_GPIO_DIGITAL_INPUT );

    // Enable the I2C module by setting the ON bit in the I2CxCON register.
    set_reg_bit( i2ccon_reg, HAL_LL_I2CCON_ON_BIT );

    // Wait for 1 BRG time period.
    Delay_us( delay_time );

    // Disable the I2C module by clearing the ON bit in the I2CxCON register.
    clear_reg_bit( i2ccon_reg, HAL_LL_I2CCON_ON_BIT );

    // Wait for 1 BRG time period.
    Delay_us( delay_time );

    // Set SDA as an input (release the line).
    hal_ll_gpio_configure_pin( &sda, sda_pin, HAL_LL_GPIO_DIGITAL_INPUT );

    // Wait for 2 additional BRG time periods.
    Delay_us( 2 * delay_time );

    // Re-enable the I2C module.
    set_reg_bit( i2ccon_reg, HAL_LL_I2CCON_ON_BIT );

    // Clear the LAT bit of the SDA pin.
    hal_ll_gpio_clear_pin_output( &sda );

    // Clear the TRIS bit of the SDA pin to be configured as an output.
    hal_ll_gpio_configure_pin( &sda, sda_pin, HAL_LL_GPIO_DIGITAL_OUTPUT );

    // Set the LAT bit of the SCL pin.
    hal_ll_gpio_write_pin_output( &scl, 1 );

    // Set the TRIS bit of the SCL pin to be configured as input.
    hal_ll_gpio_configure_pin( &scl, scl_pin, HAL_LL_GPIO_DIGITAL_INPUT );
}
#endif

// ------------------------------------------------------------------------- END
