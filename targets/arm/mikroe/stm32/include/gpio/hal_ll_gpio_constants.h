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
 * @file  hal_ll_gpio_constants.h
 * @brief GPIO HAL LL macros.
 */

#ifndef _HAL_LL_GPIO_CONSTANTS_H_
#define _HAL_LL_GPIO_CONSTANTS_H_

#ifdef __cplusplus
extern "C"{
#endif

#if defined(STM32F1xx)
    #define GPIO_SET_ALL_OUTPUT                ( uint32_t )0x33333333
    #define GPIO_SET_ALL_INPUT                 ( uint32_t )0x44444444
    #define GPIO_LSB_MASK                      ( uint16_t )0xFFFF
    #define GPIO_DBGAFR_POSITION_MASK          ( uint32_t )0x000F0000
    #define GPIO_DBGAFR_SWJCFG_MASK            ( uint32_t )0xF8FFFFFF
    #define GPIO_DBGAFR_LOCATION_MASK          ( uint32_t )0x00200000
    #define GPIO_DBGAFR_NUMBITS_MASK           ( uint32_t )0x00100000
    #define GPIO_AFIO_REG_SELECT               ( uint32_t )0x80000000
    #define GPIO_AFIO_MAPR_SWJ                 ( uint32_t )0x07000000
    #if defined (STM32F100xx)
    #define GPIO_AFIO_MAPR_MASK                ( uint32_t )0x07019FFF
    #define GPIO_AFIO_MAPR2_MASK               ( uint32_t )0x0000FFFF
    #else
    #define GPIO_AFIO_MAPR_MASK                ( uint32_t )0x77E1FFFF
    #define GPIO_AFIO_MAPR2_MASK               ( uint32_t )0x000007E0
    #endif
#endif

#define GPIO_OSPEEDER_OSPEEDR0             ( uint32_t )0x03
#define GPIO_MODER_MODER0                  ( uint32_t )0x03
#define GPIO_OTYPER_OT_0                   ( uint32_t )0x01
#define GPIO_PUPDR_PUPDR0                  ( uint32_t )0x03

#define GPIO_PIN_MASK_LOW                  ( uint32_t )0x00FF
#define GPIO_PIN_MASK_HIGH                 ( uint32_t )0xFF00
#define GPIO_PIN_MASK_ALL                  ( uint32_t )0xFFFF

#define GPIO_AF_CONFIG_OFFSET              ( uint32_t )20
#define GPIO_AF_MASK                       0x0F
#define GPIO_PIN_NAME_MASK                 ( uint32_t )0xFF
#define GPIO_AF_CONFIG_MASK                ( ( uint32_t )0x0F << GPIO_AF_CONFIG_OFFSET )

#define GPIO_CFG_MODE_ANALOG               ( uint32_t )0x1
#define GPIO_CFG_MODE_INPUT                ( uint32_t )0x2
#define GPIO_CFG_MODE_OUTPUT               ( uint32_t )0x4
#define GPIO_CFG_MODE_ALT_FUNCTION         ( uint32_t )0x8
#define GPIO_CFG_OTYPE_PP                  ( uint32_t )0x10
#define GPIO_CFG_OTYPE_OD                  ( uint32_t )0x20
#define GPIO_CFG_PULL_NO                   ( uint32_t )0x40
#define GPIO_CFG_PULL_UP                   ( uint32_t )0x80
#define GPIO_CFG_PULL_DOWN                 ( uint32_t )0x100
#if defined(STM32F1xx)
    #define GPIO_CFG_SPEED_2MHZ                ( uint32_t )0x200
    #define GPIO_CFG_SPEED_LOW                 GPIO_CFG_SPEED_2MHZ
    #define GPIO_CFG_SPEED_10MHZ               ( uint32_t )0x400
    #define GPIO_CFG_SPEED_MEDIUM              GPIO_CFG_SPEED_2MHZ
    #define GPIO_CFG_SPEED_50MHZ               ( uint32_t )0x800
    #define GPIO_CFG_SPEED_HIGH                GPIO_CFG_SPEED_50MHZ
#endif
#if defined(STM32F4xx) || defined(STM32L4xx) || defined(STM32F3xx) || \
    defined(STM32F7xx) || defined(STM32H7xx) || defined(STM32F2xx) || \
    defined(STM32L1xx)
    #define GPIO_CFG_SPEED_LOW                 ( uint32_t )0x0
    #define GPIO_CFG_SPEED_MEDIUM              ( uint32_t )0x200
#endif
#if defined(STM32F0xx) || defined(STM32L0xx) || defined(STM32G0xx)
    #define GPIO_CFG_SPEED_LOW                 ( uint32_t )0x0
    #define GPIO_CFG_SPEED_MEDIUM              ( uint32_t )0x200
    #define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x400
    #define GPIO_CFG_SPEED_VERY_HIGH           ( uint32_t )0x800
#endif
#if defined(STM32F411xx) || defined(STM32F412xx) || defined(STM32F413xx) || \
    defined(STM32F423xx) || defined(STM32F446xx)
    #define GPIO_CFG_SPEED_FAST                ( uint32_t )0x400
    #define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x800
#elif defined(STM32F3xx)
    #define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x800
#elif defined(STM32F4xx) || defined(STM32L4xx) || defined(STM32F7xx) || \
      defined(STM32H7xx) || defined(STM32F2xx) || defined(STM32L1xx)
    #define GPIO_CFG_SPEED_HIGH                ( uint32_t )0x400
    #define GPIO_CFG_SPEED_VERY_HIGH           ( uint32_t )0x800
#endif
#define GPIO_CFG_SPEED_MAX                 ( uint32_t )0x80000

#define GPIO_AHB_SHIFT                     17

#define GPIO_AHB_SHIFT                     17

#define GPIO_CFG_DIGITAL_OUTPUT            ( GPIO_CFG_MODE_OUTPUT | GPIO_CFG_SPEED_MAX | GPIO_CFG_OTYPE_PP )
#define GPIO_CFG_DIGITAL_INPUT             ( GPIO_CFG_MODE_INPUT | GPIO_CFG_PULL_NO )
#define GPIO_CFG_ANALOG_INPUT              ( GPIO_CFG_MODE_ANALOG | GPIO_CFG_PULL_NO )

#ifdef __cplusplus
}
#endif

#endif  // _HAL_LL_GPIO_CONSTANTS_H_
// ------------------------------------------------------------------------- END
