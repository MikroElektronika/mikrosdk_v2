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

/*!< SPI module base addresses. */
#ifdef SPI_MODULE_0
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0x400CA000;
#endif
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0x400CA400;
#endif

#ifdef SPI_MODULE_0
static const uint8_t HAL_LL_SPI0_MASTER_GPIO_AF1 = 1;
static const uint8_t HAL_LL_SPI0_MASTER_GPIO_AF3 = 3;
#endif
#ifdef SPI_MODULE_1
static const uint8_t HAL_LL_SPI1_MASTER_GPIO_AF1 = 1;
static const uint8_t HAL_LL_SPI1_MASTER_GPIO_AF2 = 2;
#endif

/*!< @brief SPI pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint8_t af;
} hal_ll_spi_master_pin_map_t;

/*!< SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_sck_map[] = {
    #ifdef SPI_MODULE_0
    #ifdef SPI0_SCK_PA4_AF1
    {GPIO_PA4,  HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI0_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI0_SCK_PC5_AF3
    {GPIO_PC5,  HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI0_MASTER_GPIO_AF3},
    #endif
    #endif
    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_PG6_AF1
    {GPIO_PG6,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF1},
    #endif
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    #ifdef SPI_MODULE_0
    #ifdef SPI0_MISO_PA3_AF1
    {GPIO_PA3,  HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI0_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI0_MISO_PC4_AF3
    {GPIO_PC4,  HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI0_MASTER_GPIO_AF3},
    #endif
    #endif
    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_PG4_AF1
    {GPIO_PG4,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF1},
    #endif
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    #ifdef SPI_MODULE_0
    #ifdef SPI0_MOSI_PA2_AF1
    {GPIO_PA2,  HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI0_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI0_MOSI_PC3_AF3
    {GPIO_PC3,  HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), HAL_LL_SPI0_MASTER_GPIO_AF3},
    #endif
    #endif
    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_PG5_AF1
    {GPIO_PG5,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF1},
    #endif
    #ifdef SPI1_MOSI_PV1_AF2
    {GPIO_PV1,  HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), HAL_LL_SPI1_MASTER_GPIO_AF2},
    #endif
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END