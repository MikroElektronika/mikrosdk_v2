/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
#define hal_ll_spi_module_num(_module_num) hal_ll_spi_master_module_num(_module_num)

/*!< @brief Pin function structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint32_t af;
} hal_ll_spi_master_pin_map_t;

#ifdef SPI_MODULE_1
#define SPI1_BASE_ADDRESS (0x40013000UL)
#define SPI1_BASE_ADDR SPI1_BASE_ADDRESS
#define HAL_LL_SPI1_BASE_ADDR SPI1_BASE_ADDRESS
#define HAL_LL_SPI1_BASE_ADDRESS SPI1_BASE_ADDRESS
#endif
#ifdef SPI_MODULE_2
#define SPI2_BASE_ADDRESS (0x40003800UL)
#define SPI2_BASE_ADDR SPI2_BASE_ADDRESS
#define HAL_LL_SPI2_BASE_ADDR SPI2_BASE_ADDRESS
#define HAL_LL_SPI2_BASE_ADDRESS SPI2_BASE_ADDRESS
#endif
#ifdef SPI_MODULE_3
#define SPI3_BASE_ADDRESS (0x40003C00UL)
#define SPI3_BASE_ADDR SPI3_BASE_ADDRESS
#define HAL_LL_SPI3_BASE_ADDR SPI3_BASE_ADDRESS
#define HAL_LL_SPI3_BASE_ADDRESS SPI3_BASE_ADDRESS
#endif

/*!< @brief SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] =
{
    #ifdef SPI1_SCK_PA1_AF0
    {PA1, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_SCK_PA5_AF0
    {PA5, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_SCK_PB3_AF0
    {PB3, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_SCK_PD8_AF1
    {PD8, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 1},
    #endif
    #ifdef SPI2_SCK_PA0_AF0
    {PA0, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_SCK_PB10_AF5
    {PB10, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI2_SCK_PB13_AF0
    {PB13, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_SCK_PB8_AF1
    {PB8, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI2_SCK_PD1_AF1
    {PD1, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI3_SCK_PB3_AF9
    {PB3, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 9},
    #endif
    #ifdef SPI3_SCK_PC10_AF4
    {PC10, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 4},
    #endif
    #ifdef SPI1_SCK_PE13_AF0
    {PE13, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< @brief SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] =
{
    #ifdef SPI1_MISO_PA11_AF0
    {PA11, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MISO_PA6_AF0
    {PA6, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MISO_PB4_AF0
    {PB4, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MISO_PD5_AF1
    {PD5, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 1},
    #endif
    #ifdef SPI2_MISO_PA3_AF0
    {PA3, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_MISO_PA9_AF4
    {PA9, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 4},
    #endif
    #ifdef SPI2_MISO_PB14_AF0
    {PB14, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_MISO_PB2_AF1
    {PB2, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI2_MISO_PB6_AF4
    {PB6, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 4},
    #endif
    #ifdef SPI2_MISO_PC2_AF1
    {PC2, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI2_MISO_PD3_AF1
    {PD3, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI3_MISO_PB4_AF9
    {PB4, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 9},
    #endif
    #ifdef SPI3_MISO_PC11_AF4
    {PC11, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 4},
    #endif
    #ifdef SPI1_MISO_PE14_AF0
    {PE14, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< @brief SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] =
{
    #ifdef SPI1_MOSI_PA12_AF0
    {PA12, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MOSI_PA2_AF0
    {PA2, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MOSI_PA7_AF0
    {PA7, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MOSI_PB5_AF0
    {PB5, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    #ifdef SPI1_MOSI_PD6_AF1
    {PD6, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 1},
    #endif
    #ifdef SPI2_MOSI_PA10_AF0
    {PA10, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_MOSI_PA4_AF1
    {PA4, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI2_MOSI_PB11_AF0
    {PB11, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_MOSI_PB15_AF0
    {PB15, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 0},
    #endif
    #ifdef SPI2_MOSI_PB7_AF1
    {PB7, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI2_MOSI_PC3_AF1
    {PC3, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI2_MOSI_PD4_AF1
    {PD4, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 1},
    #endif
    #ifdef SPI3_MOSI_PB5_AF9
    {PB5, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 9},
    #endif
    #ifdef SPI3_MOSI_PC12_AF4
    {PC12, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 4},
    #endif
    #ifdef SPI1_MOSI_PE15_AF0
    {PE15, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 0},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
