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
} hal_ll_spi_master_pin_map_t;

/*!< SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_sck_map[] = {
    #ifdef SCI11_SCK_PB04_AF45
    {GPIO_PB04, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SCK_PB07_AF45
    {GPIO_PB07, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_SCK_PD04_AF45
    {GPIO_PD04, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI12_SCK_P802_AF12
    {GPIO_P802, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_SCK_PB07_AF12
    {GPIO_PB07, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI1_SCK_PD04_AF10
    {GPIO_PD04, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 10},
    #endif
    #ifdef SCI5_SCK_P700_AF10
    {GPIO_P700, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SCK_PB07_AF10
    {GPIO_PB07, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_SCK_PD02_AF10
    {GPIO_PD02, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI6_SCK_P802_AF10
    {GPIO_P802, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SCK_PA04_AF10
    {GPIO_PA04, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_SCK_PB03_AF10
    {GPIO_PB03, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI8_SCK_P101_AF45
    {GPIO_P101, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCK_P202_AF45
    {GPIO_P202, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCK_P204_AF45
    {GPIO_P204, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCK_P300_AF44
    {GPIO_P300, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_SCK_P904_AF45
    {GPIO_P904, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCK_PA03_AF45
    {GPIO_PA03, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_SCK_PD02_AF45
    {GPIO_PD02, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI9_SCK_P101_AF44
    {GPIO_P101, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SCK_P902_AF44
    {GPIO_P902, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SCK_PA00_AF44
    {GPIO_PA00, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SCK_PD07_AF44
    {GPIO_PD07, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SCK_PE04_AF44
    {GPIO_PE04, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_SCK_PE05_AF44
    {GPIO_PE05, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SPI0_SCK_P200_AF13
    {GPIO_P200, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_SCK_P204_AF13
    {GPIO_P204, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_SCK_P207_AF13
    {GPIO_P207, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_SCK_PA04_AF13
    {GPIO_PA04, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_SCK_PB03_AF13
    {GPIO_PB03, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_SCK_PD00_AF13
    {GPIO_PD00, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI1_SCK_P200_AF14
    {GPIO_P200, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_P204_AF14
    {GPIO_P204, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_P207_AF14
    {GPIO_P207, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_P700_AF14
    {GPIO_P700, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_P901_AF14
    {GPIO_P901, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_P906_AF51
    {GPIO_P906, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 51},
    #endif
    #ifdef SPI1_SCK_PA04_AF14
    {GPIO_PA04, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_PB05_AF14
    {GPIO_PB05, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_SCK_PD00_AF14
    {GPIO_PD00, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    #ifdef SCI11_MISO_P903_AF45
    {GPIO_P903, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_MISO_PA01_AF45
    {GPIO_PA01, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_MISO_PB06_AF45
    {GPIO_PB06, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_MISO_PD05_AF45
    {GPIO_PD05, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI12_MISO_P000_AF12
    {GPIO_P000, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MISO_P202_AF12
    {GPIO_P202, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MISO_P800_AF12
    {GPIO_P800, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MISO_PB04_AF12
    {GPIO_PB04, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MISO_PB06_AF12
    {GPIO_PB06, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MISO_PD06_AF12
    {GPIO_PD06, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI1_MISO_PD05_AF10
    {GPIO_PD05, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 10},
    #endif
    #ifdef SCI5_MISO_P307_AF10
    {GPIO_P307, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_MISO_P901_AF10
    {GPIO_P901, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_MISO_PB06_AF10
    {GPIO_PB06, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_MISO_PE00_AF10
    {GPIO_PE00, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI6_MISO_P800_AF10
    {GPIO_P800, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_MISO_P905_AF10
    {GPIO_P905, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_MISO_PA05_AF10
    {GPIO_PA05, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_MISO_PB01_AF10
    {GPIO_PB01, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI8_MISO_P200_AF45
    {GPIO_P200, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_MISO_P202_AF44
    {GPIO_P202, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_MISO_P905_AF45
    {GPIO_P905, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_MISO_PA05_AF45
    {GPIO_PA05, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_MISO_PD01_AF45
    {GPIO_PD01, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI9_MISO_P000_AF44
    {GPIO_P000, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_MISO_PA02_AF45
    {GPIO_PA02, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 45},
    #endif
    #ifdef SPI0_MISO_P202_AF13
    {GPIO_P202, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MISO_P905_AF13
    {GPIO_P905, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MISO_PA05_AF13
    {GPIO_PA05, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MISO_PB04_AF13
    {GPIO_PB04, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MISO_PD01_AF13
    {GPIO_PD01, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI1_MISO_P202_AF14
    {GPIO_P202, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MISO_P701_AF14
    {GPIO_P701, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MISO_P902_AF14
    {GPIO_P902, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MISO_P905_AF51
    {GPIO_P905, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 51},
    #endif
    #ifdef SPI1_MISO_PA05_AF14
    {GPIO_PA05, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MISO_PB06_AF14
    {GPIO_PB06, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MISO_PD01_AF14
    {GPIO_PD01, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    #ifdef SCI11_MOSI_P902_AF45
    {GPIO_P902, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_MOSI_PA00_AF45
    {GPIO_PA00, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_MOSI_PB05_AF45
    {GPIO_PB05, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI11_MOSI_PD03_AF45
    {GPIO_PD03, HAL_LL_SCI11_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_11 ), 45},
    #endif
    #ifdef SCI12_MOSI_P001_AF12
    {GPIO_P001, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MOSI_P201_AF12
    {GPIO_P201, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MOSI_P203_AF12
    {GPIO_P203, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MOSI_P801_AF12
    {GPIO_P801, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MOSI_PB03_AF12
    {GPIO_PB03, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MOSI_PB05_AF12
    {GPIO_PB05, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI12_MOSI_PD04_AF12
    {GPIO_PD04, HAL_LL_SCI12_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_12 ), 12},
    #endif
    #ifdef SCI1_MOSI_PD03_AF10
    {GPIO_PD03, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 10},
    #endif
    #ifdef SCI5_MOSI_P306_AF10
    {GPIO_P306, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_MOSI_P900_AF10
    {GPIO_P900, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_MOSI_PB05_AF10
    {GPIO_PB05, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI5_MOSI_PD07_AF10
    {GPIO_PD07, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 10},
    #endif
    #ifdef SCI6_MOSI_P801_AF10
    {GPIO_P801, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_MOSI_PB00_AF10
    {GPIO_PB00, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI6_MOSI_PB02_AF10
    {GPIO_PB02, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 10},
    #endif
    #ifdef SCI8_MOSI_P201_AF44
    {GPIO_P201, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_MOSI_P203_AF44
    {GPIO_P203, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_MOSI_PA04_AF45
    {GPIO_PA04, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_MOSI_PB00_AF44
    {GPIO_PB00, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 44},
    #endif
    #ifdef SCI8_MOSI_PD00_AF45
    {GPIO_PD00, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI8_MOSI_PD07_AF45
    {GPIO_PD07, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 45},
    #endif
    #ifdef SCI9_MOSI_P001_AF44
    {GPIO_P001, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_MOSI_P100_AF44
    {GPIO_P100, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_MOSI_P903_AF44
    {GPIO_P903, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_MOSI_P904_AF44
    {GPIO_P904, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_MOSI_PA01_AF44
    {GPIO_PA01, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SCI9_MOSI_PA03_AF44
    {GPIO_PA03, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 44},
    #endif
    #ifdef SPI0_MOSI_P201_AF13
    {GPIO_P201, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MOSI_P203_AF13
    {GPIO_P203, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MOSI_PB00_AF13
    {GPIO_PB00, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI0_MOSI_PD02_AF13
    {GPIO_PD02, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 13},
    #endif
    #ifdef SPI1_MOSI_P201_AF14
    {GPIO_P201, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MOSI_P203_AF14
    {GPIO_P203, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MOSI_P702_AF14
    {GPIO_P702, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MOSI_P903_AF14
    {GPIO_P903, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MOSI_PB00_AF14
    {GPIO_PB00, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MOSI_PD02_AF14
    {GPIO_PD02, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif
    #ifdef SPI1_MOSI_PD03_AF14
    {GPIO_PD03, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 14},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
