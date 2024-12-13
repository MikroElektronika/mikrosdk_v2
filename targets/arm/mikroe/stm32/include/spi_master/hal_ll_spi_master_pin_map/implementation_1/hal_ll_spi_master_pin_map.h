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

/*!< If module is remapped. */
#define HAL_LL_SPI_MASTER_REMAP_DISABLE         0
#define HAL_LL_SPI_MASTER_AFIO_MAPR_SWJ_CLEAR   0x04000000ul
#define HAL_LL_SPI_MASTER_REMAP_ENABLE          0x08000000ul

/*!< SPI module base addresses. */
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0x40013000;
#endif
#ifdef SPI_MODULE_2
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = 0x40003800;
#endif
#ifdef SPI_MODULE_3
static const hal_ll_base_addr_t HAL_LL_SPI3_MASTER_BASE_ADDR = 0x40003C00;
#endif
#ifdef SPI_MODULE_4
#ifdef STM32F3xx
static const hal_ll_base_addr_t HAL_LL_SPI4_MASTER_BASE_ADDR = 0x40013C00;
#else
static const hal_ll_base_addr_t HAL_LL_SPI4_MASTER_BASE_ADDR = 0x40013400;
#endif
#endif
#ifdef SPI_MODULE_5
static const hal_ll_base_addr_t HAL_LL_SPI5_MASTER_BASE_ADDR = 0x40015000;
#endif
#ifdef SPI_MODULE_6
static const hal_ll_base_addr_t HAL_LL_SPI6_MASTER_BASE_ADDR = 0x40015400;
#endif

/*!< @brief SPI module alternate functions */
#ifdef SPI_MODULE_1
static const uint8_t HAL_LL_SPI1_MASTER_GPIO_AF0 = 0;
static const uint8_t HAL_LL_SPI1_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI1_MASTER_GPIO_AF6 = 6;
static const uint32_t HAL_LL_SPI1_MASTER_GPIO_AF = 0x04000001;
#endif
#ifdef SPI_MODULE_2
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF0 = 0;
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF1 = 1;
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF3 = 3;
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF4 = 4;
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI2_MASTER_GPIO_AF7 = 7;
#endif
#ifdef SPI_MODULE_3
static const uint8_t HAL_LL_SPI3_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI3_MASTER_GPIO_AF6 = 6;
static const uint8_t HAL_LL_SPI3_MASTER_GPIO_AF7 = 7;
static const uint32_t HAL_LL_SPI3_MASTER_GPIO_AF = 0x10000000;
#endif
#ifdef SPI_MODULE_4
static const uint8_t HAL_LL_SPI4_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI4_MASTER_GPIO_AF6 = 6;
#endif
#ifdef SPI_MODULE_5
static const uint8_t HAL_LL_SPI5_MASTER_GPIO_AF5 = 5;
static const uint8_t HAL_LL_SPI5_MASTER_GPIO_AF6 = 6;
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
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] =
{
    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_PA1_AF0
    {GPIO_PA1,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_SCK_PA1_AF5
    {GPIO_PA1,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PA5
    {GPIO_PA5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI1_SCK_PA5_AF0
    {GPIO_PA5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_SCK_PA5_AF5
    {GPIO_PA5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PA12_AF6
    {GPIO_PA12, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI1_SCK_PB3_REMAP
    {GPIO_PB3,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), ( HAL_LL_SPI1_MASTER_GPIO_AF | HAL_LL_SPI_MASTER_REMAP_ENABLE )},
    #endif
    #ifdef SPI1_SCK_PB3_AF0
    {GPIO_PB3,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_SCK_PB3_AF5
    {GPIO_PB3,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PC7_AF5
    {GPIO_PC7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PD8_AF0
    {GPIO_PD8,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_SCK_PE13_AF0
    {GPIO_PE13, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_SCK_PE13_AF5
    {GPIO_PE13, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PG2_AF5
    {GPIO_PG2,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PG11_AF5
    {GPIO_PG11, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_SCK_PA0_AF0
    {GPIO_PA0,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_SCK_PA8_AF5
    {GPIO_PA8,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PA9_AF3
    {GPIO_PA9,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI2_SCK_PA9_AF5
    {GPIO_PA9,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PA12_AF5
    {GPIO_PA12, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PB3_AF0
    {GPIO_PB3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_SCK_PB8_AF0
    {GPIO_PB8,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_SCK_PB8_AF1
    {GPIO_PB8, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI2_SCK_PB8_AF5
    {GPIO_PB8,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PB10_AF0
    {GPIO_PB10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_SCK_PB10_AF5
    {GPIO_PB10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PB13
    {GPIO_PB13, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI2_SCK_PB13_AF0
    {GPIO_PB13, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_SCK_PB13_AF5
    {GPIO_PB13, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PC7_AF5
    {GPIO_PC7,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PD1_AF0
    {GPIO_PD1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_SCK_PD1_AF1
    {GPIO_PD1, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI2_SCK_PD1_AF5
    {GPIO_PD1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PD3_AF5
    {GPIO_PD3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PD7_AF5
    {GPIO_PD7,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PD8_AF5
    {GPIO_PD8,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PF1_AF5
    {GPIO_PF1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PF9_AF5
    {GPIO_PF9,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PF10_AF5
    {GPIO_PF10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PI1_AF5
    {GPIO_PI1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_SCK_PA1_AF6
    {GPIO_PA1,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_SCK_PB3
    {GPIO_PB3,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI_MASTER_AFIO_MAPR_SWJ_CLEAR},
    #endif
    #ifdef SPI3_SCK_PB3_AF5
    {GPIO_PB3,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI3_SCK_PB3_AF6
    {GPIO_PB3,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_SCK_PB12_AF7
    {GPIO_PB12, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF7},
    #endif
    #ifdef SPI3_SCK_PC10_REMAP
    {GPIO_PC10, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  ( HAL_LL_SPI3_MASTER_GPIO_AF | HAL_LL_SPI_MASTER_REMAP_ENABLE )},
    #endif
    #ifdef SPI3_SCK_PC10_AF6
    {GPIO_PC10, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_SCK_PG9_AF6
    {GPIO_PG9,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_SCK_PB13_AF6
    {GPIO_PB13, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI4_SCK_PE2_AF5
    {GPIO_PE2,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_SCK_PE12_AF5
    {GPIO_PE12, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_SCK_PG11_AF6
    {GPIO_PG11, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_SCK_PB0_AF6
    {GPIO_PB0,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_SCK_PE2_AF6
    {GPIO_PE2,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_SCK_PE12_AF6
    {GPIO_PE12, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_SCK_PF7_AF5
    {GPIO_PF7,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_SCK_PH6_AF5
    {GPIO_PH6,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_SCK_PK0_AF5
    {GPIO_PK0,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_SCK_PB3_AF8
    {GPIO_PB3,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_SCK_PA5_AF8
    {GPIO_PA5,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_SCK_PG13_AF5
    {GPIO_PG13, HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF5},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] =
{
    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_PA6
    {GPIO_PA6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI1_MISO_PA6_AF0
    {GPIO_PA6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MISO_PA6_AF5
    {GPIO_PA6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PA11_AF0
    {GPIO_PA11, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MISO_PA11_AF5
    {GPIO_PA11, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PA13_AF6
    {GPIO_PA13, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI1_MISO_PB4_REMAP
    {GPIO_PB4,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), ( HAL_LL_SPI1_MASTER_GPIO_AF | HAL_LL_SPI_MASTER_REMAP_ENABLE )},
    #endif
    #ifdef SPI1_MISO_PB4_AF0
    {GPIO_PB4,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MISO_PB4_AF5
    {GPIO_PB4,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PC8_AF5
    {GPIO_PC8,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PD5_AF0
    {GPIO_PD5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MISO_PE14_AF0
    {GPIO_PE14, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MISO_PE14_AF5
    {GPIO_PE14, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PG3_AF5
    {GPIO_PG3,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PG9_AF5
    {GPIO_PG9,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MISO_PA3_AF0
    {GPIO_PA3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PA9_AF0
    {GPIO_PA9,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PA9_AF4
    {GPIO_PA9, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI2_MISO_PA9_AF5
    {GPIO_PA9,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PA10_AF5
    {GPIO_PA10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PA12_AF5
    {GPIO_PA12, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PB2_AF0
    {GPIO_PB2,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PB2_AF1
    {GPIO_PB2, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI2_MISO_PB4_AF0
    {GPIO_PB4,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PB6_AF0
    {GPIO_PB6,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PB6_AF4
    {GPIO_PB6, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI2_MISO_PB14
    {GPIO_PB14, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI2_MISO_PB14_AF0
    {GPIO_PB14, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PB14_AF5
    {GPIO_PB14, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PC2_AF0
    {GPIO_PC2,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PC2_AF5
    {GPIO_PC2,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PD3_AF0
    {GPIO_PD3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MISO_PD3_AF1
    {GPIO_PD3, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI2_MISO_PD3_AF5
    {GPIO_PD3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PI2_AF5
    {GPIO_PI2,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MISO_PA2_AF6
    {GPIO_PA2,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MISO_PB4
    {GPIO_PB4,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI_MASTER_AFIO_MAPR_SWJ_CLEAR},
    #endif
    #ifdef SPI3_MISO_PB4_AF6
    {GPIO_PB4,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MISO_PC11_REMAP
    {GPIO_PC11, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  ( HAL_LL_SPI3_MASTER_GPIO_AF | HAL_LL_SPI_MASTER_REMAP_ENABLE )},
    #endif
    #ifdef SPI3_MISO_PC11_AF6
    {GPIO_PC11, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MISO_PG10_AF6
    {GPIO_PG10, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MISO_PA11_AF6
    {GPIO_PA11, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI4_MISO_PD0_AF5
    {GPIO_PD0,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MISO_PE5_AF5
    {GPIO_PE5,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MISO_PE13_AF5
    {GPIO_PE13, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MISO_PG12_AF6
    {GPIO_PG12, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MISO_PA12_AF6
    {GPIO_PA12, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MISO_PE5_AF6
    {GPIO_PE5,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MISO_PE13_AF6
    {GPIO_PE13, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MISO_PF8_AF5
    {GPIO_PF8,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MISO_PH7_AF5
    {GPIO_PH7,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MISO_PJ11_AF5
    {GPIO_PJ11, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MISO_PA6_AF8
    {GPIO_PA6,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MISO_PB4_AF8
    {GPIO_PB4,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MISO_PG12_AF5
    {GPIO_PG12, HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF5},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] =
{
    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_PA2_AF0
    {GPIO_PA2,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MOSI_PA7
    {GPIO_PA7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI1_MOSI_PA7_AF0
    {GPIO_PA7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MOSI_PA7_AF5
    {GPIO_PA7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PA12_AF0
    {GPIO_PA12, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MOSI_PA12_AF5
    {GPIO_PA12, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PB0_AF5
    {GPIO_PB0,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PB5_REMAP
    {GPIO_PB5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), ( HAL_LL_SPI1_MASTER_GPIO_AF | HAL_LL_SPI_MASTER_REMAP_ENABLE )},
    #endif
    #ifdef SPI1_MOSI_PB5_AF0
    {GPIO_PB5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MOSI_PB5_AF5
    {GPIO_PB5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PC9_AF5
    {GPIO_PC9,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PD6_AF0
    {GPIO_PD6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MOSI_PD7_AF5
    {GPIO_PD7,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PE15_AF0
    {GPIO_PE15, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI1_MOSI_PE15_AF5
    {GPIO_PE15, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PF6_AF5
    {GPIO_PF6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PG4_AF5
    {GPIO_PG4,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MOSI_PA4_AF0
    {GPIO_PA4,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PA4_AF1
    {GPIO_PA4, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI2_MOSI_PA10_AF0
    {GPIO_PA10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PA10_AF5
    {GPIO_PA10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PA11_AF5
    {GPIO_PA11, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PB5_AF0
    {GPIO_PB5,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PB7_AF0
    {GPIO_PB7,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PB7_AF1
    {GPIO_PB7, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI2_MOSI_PB11_AF0
    {GPIO_PB11, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PB15
    {GPIO_PB15, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI2_MOSI_PB15_AF0
    {GPIO_PB15, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PB15_AF5
    {GPIO_PB15, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PC1_AF3
    {GPIO_PC1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI2_MOSI_PC1_AF5
    {GPIO_PC1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PC1_AF7
    {GPIO_PC1,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF7},
    #endif
    #ifdef SPI2_MOSI_PC3_AF0
    {GPIO_PC3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PC3_AF5
    {GPIO_PC3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PD4_AF0
    {GPIO_PD4,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF0},
    #endif
    #ifdef SPI2_MOSI_PD4_AF5
    {GPIO_PD4,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PI3_AF5
    {GPIO_PI3,  HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2),  HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MOSI_PA3_AF6
    {GPIO_PA3,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PB0_AF7
    {GPIO_PB0,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF7},
    #endif
    #ifdef SPI3_MOSI_PB2_AF7
    {GPIO_PB2,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF7},
    #endif
    #ifdef SPI3_MOSI_PB5
    {GPIO_PB5,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI_MASTER_AFIO_MAPR_SWJ_CLEAR},
    #endif
    #ifdef SPI3_MOSI_PB5_AF6
    {GPIO_PB5,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PC1_AF5
    {GPIO_PC1,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI3_MOSI_PC12_REMAP
    {GPIO_PC12, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  ( HAL_LL_SPI3_MASTER_GPIO_AF | HAL_LL_SPI_MASTER_REMAP_ENABLE )},
    #endif
    #ifdef SPI3_MOSI_PC12_AF6
    {GPIO_PC12, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PD0_AF6
    {GPIO_PD0,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PD6_AF5
    {GPIO_PD6,  HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI3_MOSI_PG11_AF6
    {GPIO_PG11, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3),  HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MOSI_PA1_AF5
    {GPIO_PA1,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MOSI_PE6_AF5
    {GPIO_PE6,  HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MOSI_PE14_AF5
    {GPIO_PE14, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI4_MOSI_PG13_AF6
    {GPIO_PG13, HAL_LL_SPI4_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_4),  HAL_LL_SPI4_MASTER_GPIO_AF6},
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MOSI_PA10_AF6
    {GPIO_PA10, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MOSI_PB8_AF6
    {GPIO_PB8,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MOSI_PE6_AF6
    {GPIO_PE6,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MOSI_PE14_AF6
    {GPIO_PE14, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI5_MOSI_PF9_AF5
    {GPIO_PF9,  HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MOSI_PF11_AF5
    {GPIO_PF11, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI5_MOSI_PJ10_AF5
    {GPIO_PJ10, HAL_LL_SPI5_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_5),  HAL_LL_SPI5_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MOSI_PA7_AF8
    {GPIO_PA7,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MOSI_PB5_AF8
    {GPIO_PB5,  HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF8},
    #endif
    #ifdef SPI6_MOSI_PG14_AF5
    {GPIO_PG14, HAL_LL_SPI6_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_6),  HAL_LL_SPI6_MASTER_GPIO_AF5},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
