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
 * @file  hal_ll_spi_master_pin_map.h
 * @brief SPI HAL LOW LEVEL MASTER PIN MAP.
 */

#ifndef _HAL_LL_SPI_MASTER_PIN_MAP_H_
#define _HAL_LL_SPI_MASTER_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))
/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_spi_master_module_num(_module_num) (_module_num - 1)

/*!< SPI module base addresses. */
#ifdef SPI_MODULE_0
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0X40008000;
#endif
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0X40009000;
#endif
#ifdef SPI_MODULE_2
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = 0X4000A000;
#endif
#ifdef SPI_MODULE_3
static const hal_ll_base_addr_t HAL_LL_SPI3_MASTER_BASE_ADDR = 0X4000B000;
#endif

/*!< @brief SPI pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint8_t af;
} hal_ll_spi_master_pin_map_t;

/*!< SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] = {
    #ifdef SPI0_SCK_PA2_AF2
    {PA2, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 2},
    #endif
    #ifdef SPI1_SCK_PD0_AF2
    {PD0, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif
    #ifdef SPI1_SCK_PF2_AF2
    {PF2, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif
    #ifdef SPI2_SCK_PB4_AF2
    {PB4, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 2},
    #endif
    #ifdef SPI3_SCK_PD0_AF1
    {PD0, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 1},
    #endif
    #ifdef SPI2_SCK_PH4_AF2
    {PH4, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 2},
    #endif
    #ifdef SPI3_SCK_PH0_AF2
    {PH0, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 2},
    #endif
    #ifdef SPI3_SCK_PK0_AF2
    {PK0, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 2},
    #endif
    #ifdef SPI0_SCK_PA2_AF15
    {PA2, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 15},
    #endif
    #ifdef SPI1_SCK_PB5_AF15
    {PB5, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 15},
    #endif
    #ifdef SPI2_SCK_PD3_AF15
    {PD3, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 15},
    #endif
    #ifdef SPI2_SCK_PG7_AF15
    {PG7, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 15},
    #endif
    #ifdef SPI3_SCK_PF2_AF14
    {PF2, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif
    #ifdef SPI3_SCK_PF3_AF14
    {PF3, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif
    #ifdef SPI3_SCK_PQ0_AF14
    {PQ0, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] = {
    #ifdef SPI0_MISO_PA4_AF2
    {PA4, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 2},
    #endif
    #ifdef SPI1_MISO_PD2_AF2
    {PD2, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif
    #ifdef SPI1_MISO_PF0_AF2
    {PF0, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif
    #ifdef SPI2_MISO_PB6_AF2
    {PB6, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 2},
    #endif
    #ifdef SPI3_MISO_PD2_AF1
    {PD2, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 1},
    #endif
    #ifdef SPI2_MISO_PH6_AF2
    {PH6, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 2},
    #endif
    #ifdef SPI3_MISO_PH2_AF2
    {PH2, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 2},
    #endif
    #ifdef SPI3_MISO_PK2_AF2
    {PK2, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 2},
    #endif
    #ifdef SPI0_MISO_PA5_AF15
    {PA5, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 15},
    #endif
    #ifdef SPI1_MISO_PE5_AF15
    {PE5, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 15},
    #endif
    #ifdef SPI2_MISO_PD0_AF15
    {PD0, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 15},
    #endif
    #ifdef SPI2_MISO_PG4_AF15
    {PG4, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 15},
    #endif
    #ifdef SPI3_MISO_PF0_AF14
    {PF0, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif
    #ifdef SPI3_MISO_PQ3_AF14
    {PQ3, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] = {
    #ifdef SPI0_MOSI_PA5_AF2
    {PA5, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 2},
    #endif
    #ifdef SPI1_MOSI_PD3_AF2
    {PD3, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif
    #ifdef SPI1_MOSI_PF1_AF2
    {PF1, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif
    #ifdef SPI2_MOSI_PB7_AF2
    {PB7, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 2},
    #endif
    #ifdef SPI3_MOSI_PD3_AF1
    {PD3, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 1},
    #endif
    #ifdef SPI2_MOSI_PH7_AF2
    {PH7, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 2},
    #endif
    #ifdef SPI3_MOSI_PH3_AF2
    {PH3, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 2},
    #endif
    #ifdef SPI3_MOSI_PK3_AF2
    {PK3, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 2},
    #endif
    #ifdef SPI0_MOSI_PA4_AF15
    {PA4, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 15},
    #endif
    #ifdef SPI1_MOSI_PE4_AF15
    {PE4, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 15},
    #endif
    #ifdef SPI2_MOSI_PD1_AF15
    {PD1, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 15},
    #endif
    #ifdef SPI2_MOSI_PG5_AF15
    {PG5, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), 15},
    #endif
    #ifdef SPI3_MOSI_PF1_AF14
    {PF1, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif
    #ifdef SPI3_MOSI_PQ2_AF14
    {PQ2, HAL_LL_SPI3_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_3), 14},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
