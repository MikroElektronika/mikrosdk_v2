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
#define hal_ll_spi_master_module_num(_module_num) (_module_num)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< SPI module base addresses. */
#ifdef QSPI_SPI
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0x4007C000;
#else
#ifdef SPI_MODULE_0
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0x40008000;
#endif
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0x40058000;
#endif
#endif

/*!< @brief Pin function structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    hal_ll_base_addr_t base;
    uint8_t module_index;
    uint32_t af;
} hal_ll_spi_master_pin_map_t;

/*!< @brief SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] =
{
    #ifdef SPI0_SCK_PA14_AFA
    {GPIO_PA14, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 0},
    #endif
    #ifdef SPI0_SCK_PD22_AFB
    {GPIO_PD22, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 1},
    #endif
    #ifdef SPI1_SCK_PC24_AFC
    {GPIO_PC24, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< @brief SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] =
{
    #ifdef SPI0_MISO_PA12_AFA
    {GPIO_PA12, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 0},
    #endif
    #ifdef SPI0_MISO_PD20_AFB
    {GPIO_PD20, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 1},
    #endif
    #ifdef SPI1_MISO_PC26_AFC
    {GPIO_PC26, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< @brief SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] =
{
    #ifdef SPI0_MOSI_PA13_AFA
    {GPIO_PA13, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 0},
    #endif
    #ifdef SPI0_MOSI_PD21_AFB
    {GPIO_PD21, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_0), 1},
    #endif
    #ifdef SPI1_MOSI_PC27_AFC
    {GPIO_PC27, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num(SPI_MODULE_1), 2},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
