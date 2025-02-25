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

/*!< If module is remapped. */
#define HAL_LL_SPI_MASTER_REMAP_DISABLE 0x00000000
#define HAL_LL_SPI_MASTER_REMAP_ENABLE 0x80000000

/*!< SPI module base addresses. */
#ifdef SPI_MODULE_0
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0x40013000;  // This module is on APB2 bus.
#endif
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0x40003800;  // This module is on APB1 bus.
#endif
#ifdef SPI_MODULE_2
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = 0x40003C00;  // This module is on APB1 bus.
#endif

/*!< @brief SPI module alternate functions. */
#ifdef SPI_MODULE_0
static const uint32_t HAL_LL_SPI0_MASTER_GPIO_AF = 0x00000001;
#endif
#ifdef SPI_MODULE_2
static const uint32_t HAL_LL_SPI2_MASTER_GPIO_AF = 0x10000000;
#endif

/*!< @brief SPI pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint32_t af;
} hal_ll_spi_master_pin_map_t;

/*!< SPI SCK pins. */
static hal_ll_spi_master_pin_map_t _spi_sck_map[] = {
    #ifdef SPI0_SCK_PA5_REMAP_NONE
    {GPIO_PA5, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI_MASTER_REMAP_DISABLE | HAL_LL_SPI0_MASTER_GPIO_AF},
    #endif
    #ifdef SPI0_SCK_PB3_REMAP_FULL
    {GPIO_PB3, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI_MASTER_REMAP_ENABLE | HAL_LL_SPI0_MASTER_GPIO_AF},
    #endif
    #ifdef SPI1_SCK_PB13_REMAP_NONE
    {GPIO_PB13, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI2_SCK_PB3_REMAP_NONE
    {GPIO_PB3, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI_MASTER_REMAP_DISABLE | HAL_LL_SPI2_MASTER_GPIO_AF},
    #endif
    #ifdef SPI2_SCK_PC10_REMAP_FULL
    {GPIO_PC10, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI_MASTER_REMAP_ENABLE | HAL_LL_SPI2_MASTER_GPIO_AF},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static hal_ll_spi_master_pin_map_t _spi_miso_map[] = {
    #ifdef SPI0_MISO_PA6_REMAP_NONE
    {GPIO_PA6, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI_MASTER_REMAP_DISABLE | HAL_LL_SPI0_MASTER_GPIO_AF},
    #endif
    #ifdef SPI0_MISO_PB4_REMAP_FULL
    {GPIO_PB4, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI_MASTER_REMAP_ENABLE | HAL_LL_SPI0_MASTER_GPIO_AF},
    #endif
    #ifdef SPI1_MISO_PB14_REMAP_NONE
    {GPIO_PB14, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI2_MISO_PB4_REMAP_NONE
    {GPIO_PB4, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI_MASTER_REMAP_DISABLE | HAL_LL_SPI2_MASTER_GPIO_AF},
    #endif
    #ifdef SPI2_MISO_PC11_REMAP_FULL
    {GPIO_PC11, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI_MASTER_REMAP_ENABLE | HAL_LL_SPI2_MASTER_GPIO_AF},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static hal_ll_spi_master_pin_map_t _spi_mosi_map[] = {
    #ifdef SPI0_MOSI_PA7_REMAP_NONE
    {GPIO_PA7, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI_MASTER_REMAP_DISABLE | HAL_LL_SPI0_MASTER_GPIO_AF},
    #endif
    #ifdef SPI0_MOSI_PB5_REMAP_FULL
    {GPIO_PB5, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI_MASTER_REMAP_ENABLE | HAL_LL_SPI0_MASTER_GPIO_AF},
    #endif
    #ifdef SPI1_MOSI_PB15_REMAP_NONE
    {GPIO_PB15, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI_MASTER_REMAP_DISABLE},
    #endif
    #ifdef SPI2_MOSI_PB5_REMAP_NONE
    {GPIO_PB5, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI_MASTER_REMAP_DISABLE | HAL_LL_SPI2_MASTER_GPIO_AF},
    #endif
    #ifdef SPI2_MOSI_PC12_REMAP_FULL
    {GPIO_PC12, HAL_LL_SPI2_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_2), HAL_LL_SPI_MASTER_REMAP_ENABLE | HAL_LL_SPI2_MASTER_GPIO_AF},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
