/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file  hal_ll_spi_master_pin_map.h
 * @brief SPI HAL LOW LEVEL MASTER PIN MAP.
 */

#ifndef _HAL_LL_SPI_MASTER_PIN_MAP_H_
#define _HAL_LL_SPI_MASTER_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_spi_master_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< SPI module base addresses. */
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR   = 0x40013000;
#endif
#ifdef SPI_MODULE_2
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR   = 0x40003800;
#endif
#ifdef SPI_MODULE_3
static const hal_ll_base_addr_t HAL_LL_SPI3_MASTER_BASE_ADDR   = 0x40003C00;
#endif
#ifdef SPI_MODULE_4
static const hal_ll_base_addr_t HAL_LL_SPI4_MASTER_BASE_ADDR   = 0x40013400;
#endif
#ifdef SPI_MODULE_5
static const hal_ll_base_addr_t HAL_LL_SPI5_MASTER_BASE_ADDR   = 0x40015000;
#endif
#ifdef SPI_MODULE_6
static const hal_ll_base_addr_t HAL_LL_SPI6_MASTER_BASE_ADDR   = 0x58001400;
#endif

/*!< SPI modules. */
#ifdef SPI_MODULE_1
static const uint8_t HAL_LL_SPI1_MASTER_GPIO_AF5 = 5;
#endif
#ifdef SPI_MODULE_2
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF5 = 5;
#endif
#ifdef SPI_MODULE_3
static const uint8_t HAL_LL_SPI3_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI3_MASTER_GPIO_AF6 = 6;
static const uint8_t HAL_LL_SPI3_MASTER_GPIO_AF7 = 7;
#endif
#ifdef SPI_MODULE_4
static const uint8_t HAL_LL_SPI4_MASTER_GPIO_AF5 = 5;
#endif
#ifdef SPI_MODULE_5
static const uint8_t HAL_LL_SPI5_MASTER_GPIO_AF5 = 5;
#endif
#ifdef SPI_MODULE_6
static const uint8_t HAL_LL_SPI6_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI6_MASTER_GPIO_AF8 = 8;
#endif

/*!< @brief Pin function structure. */
typedef struct
{
    hal_ll_pin_name_t       pin;
    hal_ll_base_addr_t      base;
    uint8_t                 module_index;
    uint32_t                af;
} hal_ll_spi_master_pin_map_t;

/*!< SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] = {
    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_PA5_AF5
    {PA5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PB3_AF5
    {PB3,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PG11_AF5
    {PG11, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_SCK_PB10_AF5
    {PB10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PB13_AF5
    {PB13, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PA9_AF5
    {PA9,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PI1_AF5
    {PI1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PD3_AF5
    {PD3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PA12_AF5
    {PA12, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_SCK_PB3_AF5
    {PB3,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_SCK_PC10_AF6
    {PC10, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_SCK_PE2_AF5
    {PE2,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4), HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_SCK_PE12_AF5
    {PE12, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4), HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_SCK_PF7_AF5
    {PF7,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_SCK_PH6_AF5
    {PH6,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_SCK_PK0_AF5
    {PK0,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_SCK_PB3_AF8
    {PB3,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_SCK_PA5_AF8
    {PA5,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_SCK_PG13_AF5
    {PG13, HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF5},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] =
{
    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_PA6_AF5
    {PA6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PB4_AF5
    {PB4,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PG9_AF5
    {PG9,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MISO_PB14_AF5
    {PB14, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PC2_AF5
    {PC2,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PI2_AF5
    {PI2,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MISO_PB4_AF6
    {PB4,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MISO_PC11_AF6
    {PC11, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MISO_PE5_AF5
    {PE5,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MISO_PE13_AF5
    {PE13, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4), HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MISO_PF8_AF5
    {PF8,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MISO_PH7_AF5
    {PH7,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MISO_PJ11_AF5
    {PJ11, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MISO_PA6_AF8
    {PA6,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MISO_PB4_AF8
    {PB4,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MISO_PG12_AF5
    {PG12, HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF5},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] =
{
    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_PA7_AF5
    {PA7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PB5_AF5
    {PB5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PD7_AF5
    {PD7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MOSI_PB15_AF5
    {PB15, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PC1_AF5
    {PC1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PC3_AF5
    {PC3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PI3_AF5
    {PI3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MOSI_PB2_AF7
    {PB2,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF7},
    #endif
    #ifdef SPI3_MOSI_PB5_AF6
    {PB5,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PC12_AF6
    {PC12, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PD6_AF5
    {PD6,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MOSI_PE6_AF5
    {PE6,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4), HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MOSI_PE14_AF5
    {PE14, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4), HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MOSI_PF9_AF5
    {PF9,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MOSI_PF11_AF5
    {PF11, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MOSI_PJ10_AF5
    {PJ10, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5), HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MOSI_PA7_AF8
    {PA7,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MOSI_PB5_AF8
    {PB5,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MOSI_PG14_AF5
    {PG14, HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6), HAL_LL_SPI6_MASTER_GPIO_AF5},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
