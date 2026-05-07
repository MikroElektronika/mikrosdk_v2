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

/*!< @brief SPI pin structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint8_t af;
    uint8_t channel;
} hal_ll_spi_master_pin_map_t;

/*!< SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_sck_map[] = {
    #ifdef SAU_SPI00_SCK_P102_AF3
    {GPIO_P102, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 0},
    #endif
    #ifdef SAU_SPI00_SCK_P108_AF3
    {GPIO_P108, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 0},
    #endif
    #ifdef SAU_SPI00_SCK_P112_AF2
    {GPIO_P112, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 2, 0},
    #endif
    #ifdef SAU_SPI00_SCK_P500_AF2
    {GPIO_P500, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 2, 0},
    #endif
    #ifdef SAU_SPI01_SCK_P204_AF1
    {GPIO_P204, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 1, 1},
    #endif
    #ifdef SAU_SPI01_SCK_P208_AF3
    {GPIO_P208, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 1},
    #endif
    #ifdef SAU_SPI10_SCK_P104_AF3
    {GPIO_P104, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 2},
    #endif
    #ifdef SAU_SPI11_SCK_P201_AF3
    {GPIO_P201, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 3},
    #endif
    #ifdef SAU_SPI11_SCK_P407_AF1
    {GPIO_P407, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 1, 3},
    #endif
    #ifdef SAU_SPI11_SCK_P409_AF1
    {GPIO_P409, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 1, 3},
    #endif
    #ifdef SAU_SPI11_SCK_P411_AF1
    {GPIO_P411, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 1, 3},
    #endif
    #ifdef SAU_SPI20_SCK_P112_AF2
    {GPIO_P112, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 2, 0},
    #endif
    #ifdef SAU_SPI20_SCK_P410_AF1
    {GPIO_P410, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 1, 0},
    #endif
    #ifdef SAU_SPI21_SCK_P115_AF1
    {GPIO_P115, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 1, 1},
    #endif
    #ifdef SAU_SPI21_SCK_P302_AF2
    {GPIO_P302, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 2, 1},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    #ifdef SAU_SPI00_MISO_P100_AF3
    {GPIO_P100, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 0},
    #endif
    #ifdef SAU_SPI00_MISO_P110_AF2
    {GPIO_P110, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 2, 0},
    #endif
    #ifdef SAU_SPI00_MISO_P502_AF2
    {GPIO_P502, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 2, 0},
    #endif
    #ifdef SAU_SPI01_MISO_P205_AF1
    {GPIO_P205, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 1, 1},
    #endif
    #ifdef SAU_SPI01_MISO_P207_AF3
    {GPIO_P207, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 1},
    #endif
    #ifdef SAU_SPI10_MISO_P105_AF3
    {GPIO_P105, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 2},
    #endif
    #ifdef SAU_SPI11_MISO_P212_AF4
    {GPIO_P212, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 4, 3},
    #endif
    #ifdef SAU_SPI20_MISO_P110_AF2
    {GPIO_P110, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 2, 0},
    #endif
    #ifdef SAU_SPI20_MISO_P403_AF1
    {GPIO_P403, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 1, 0},
    #endif
    #ifdef SAU_SPI21_MISO_P114_AF1
    {GPIO_P114, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 1, 1},
    #endif
    #ifdef SAU_SPI21_MISO_P301_AF2
    {GPIO_P301, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 2, 1},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    #ifdef SAU_SPI00_MOSI_P101_AF3
    {GPIO_P101, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 0},
    #endif
    #ifdef SAU_SPI00_MOSI_P109_AF2
    {GPIO_P109, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 2, 0},
    #endif
    #ifdef SAU_SPI00_MOSI_P501_AF2
    {GPIO_P501, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 2, 0},
    #endif
    #ifdef SAU_SPI01_MOSI_P206_AF1
    {GPIO_P206, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 1, 1},
    #endif
    #ifdef SAU_SPI01_MOSI_P915_AF3
    {GPIO_P915, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 1},
    #endif
    #ifdef SAU_SPI10_MOSI_P106_AF3
    {GPIO_P106, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 3, 2},
    #endif
    #ifdef SAU_SPI11_MOSI_P213_AF4
    {GPIO_P213, HAL_LL_SAU0_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_0 ), 4, 3},
    #endif
    #ifdef SAU_SPI20_MOSI_P109_AF2
    {GPIO_P109, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 2, 0},
    #endif
    #ifdef SAU_SPI20_MOSI_P402_AF1
    {GPIO_P402, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 1, 0},
    #endif
    #ifdef SAU_SPI21_MOSI_P113_AF1
    {GPIO_P113, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 1, 1},
    #endif
    #ifdef SAU_SPI21_MOSI_P303_AF2
    {GPIO_P303, HAL_LL_SAU1_BASE_ADDR, hal_ll_spi_master_module_num( SAU_SPI_MODULE_1 ), 2, 1},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
