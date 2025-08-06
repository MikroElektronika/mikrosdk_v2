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
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0x40072000UL;
#endif
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0x40072100UL;
#endif
#ifdef SPI_MODULE_2
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = 0x40072200UL;
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
    #ifdef SPI0_SCK_P102_AF6
    {GPIO_P102, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_SCK_P111_AF6
    {GPIO_P111, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_SCK_P204_AF6
    {GPIO_P204, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_SCK_P412_AF6
    {GPIO_P412, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    #ifdef SPI0_MISO_P100_AF6
    {GPIO_P100, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MISO_P110_AF6
    {GPIO_P110, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MISO_P410_AF6
    {GPIO_P410, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MISO_P202_AF6
    {GPIO_P202, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    #ifdef SPI0_MOSI_P101_AF6
    {GPIO_P101, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MOSI_P109_AF6
    {GPIO_P109, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MOSI_P411_AF6
    {GPIO_P411, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MOSI_P203_AF6
    {GPIO_P203, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
