/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file  hal_ll_gpio_constants.h
 * @brief GPIO HAL LL macros.
 */

#ifndef _HAL_LL_GPIO_CONSTANTS_H_
#define _HAL_LL_GPIO_CONSTANTS_H_

#ifdef __cplusplus
extern "C"{
#endif

#define GPIO_CFG_MODE_INPUT                0x0UL
#define GPIO_CFG_MODE_OUTPUT               0x1UL

#define GPIO_DIR_INPUT                     0
#define GPIO_DIR_OUTPUT                    1

#define GPIO_CFG_PULL_UP                   0x1UL
#define GPIO_CFG_PULL_DOWN                 0x2UL

#define GPIO_CFG_OPEN_DRAIN                0x8UL
#define GPIO_CFG_DRIVE_2mA                 0x10UL
#define GPIO_CFG_DRIVE_4mA                 0x20UL
#define GPIO_CFG_DRIVE_8mA                 0x40UL
#define GPIO_CFG_SLEW_RATE                 0x80UL
#define GPIO_CFG_DIGITAL_ENABLE            0x100UL
#define GPIO_CFG_ISOLATION_DISABLE         0x200UL
#define GPIO_CFG_ALT_FUNCTION              0x400UL
#define GPIO_CFG_ADC_SRC_TRIGGER           0x800UL
#define GPIO_CFG_DRIVE_6mA                 0x1000UL
#define GPIO_CFG_DRIVE_10mA                0x2000UL
#define GPIO_CFG_DRIVE_12mA                0x4000UL

#define GPIO_CFG_ADV_AIN                   ( GPIO_CFG_ALT_FUNCTION | GPIO_CFG_ISOLATION_DISABLE )

#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_DIR_OUTPUT | GPIO_CFG_DIGITAL_ENABLE | GPIO_CFG_DRIVE_8mA )
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_DIR_INPUT  | GPIO_CFG_DIGITAL_ENABLE | GPIO_CFG_DRIVE_8mA )
#define GPIO_CFG_ANALOG_INPUT              ( GPIO_DIR_INPUT  | GPIO_CFG_ADV_AIN )

#define _HAL_GPIO_DIR_OFFSET               ( 0x400UL / 4 )
#define _HAL_GPIO_GPIOPC_OFFSET            ( 0xFC4UL / 4 )
#define _HAL_GPIO_GPIOODR_OFFSET           ( 0x50CUL / 4 )
#define _HAL_GPIO_GPIOPUR_OFFSET           ( 0x510UL / 4 )
#define _HAL_GPIO_GPIOPDR_OFFSET           ( 0x514UL / 4 )
#define _HAL_GPIO_GPIOSLR_OFFSET           ( 0x518UL / 4 )
#define _HAL_GPIO_GPIODEN_OFFSET           ( 0x518UL / 4 )
#define _HAL_GPIO_GPIODR2R_OFFSET          ( 0x500UL / 4 )
#define _HAL_GPIO_GPIODR4R_OFFSET          ( 0x504UL / 4 )
#define _HAL_GPIO_GPIODR8R_OFFSET          ( 0x508UL / 4 )
#define _HAL_GPIO_GPIODR12R_OFFSET         ( 0x53CUL / 4 )
#define _HAL_GPIO_GPIOAMSEL_OFFSET         ( 0x528UL / 4 )
#define _HAL_GPIO_GPIOAFSEL_OFFSET         ( 0x420UL / 4 )
#define _HAL_GPIO_GPIOADCCTL_OFFSET        ( 0x530UL / 4 )
    
#define GPIO_PIN_NAME_MASK                 ( uint32_t )0xFF
#define GPIO_AF_MASK                       0x0F

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
