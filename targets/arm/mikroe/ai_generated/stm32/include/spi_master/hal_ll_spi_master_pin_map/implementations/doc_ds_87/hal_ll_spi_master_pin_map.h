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
#ifdef SPI_MODULE_4
#define SPI4_BASE_ADDRESS (0x40013C00UL)
#define SPI4_BASE_ADDR SPI4_BASE_ADDRESS
#define HAL_LL_SPI4_BASE_ADDR SPI4_BASE_ADDRESS
#define HAL_LL_SPI4_BASE_ADDRESS SPI4_BASE_ADDRESS
#endif

/*!< @brief SPI SCK pins. */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] =
{
    #ifdef SPI1_SCK_PA5_AF5
    {GPIO_PA5, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI1_SCK_PB3_AF5
    {GPIO_PB3, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI1_SCK_PG2_AF5
    {GPIO_PG2, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI2_SCK_PB13_AF5
    {GPIO_PB13, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI2_SCK_PF10_AF5
    {GPIO_PF10, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI2_SCK_PF1_AF5
    {GPIO_PF1, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI2_SCK_PF9_AF5
    {GPIO_PF9, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI3_SCK_PB3_AF6
    {GPIO_PB3, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI3_SCK_PC10_AF6
    {GPIO_PC10, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI3_SCK_PG9_AF6
    {GPIO_PG9, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI4_SCK_PE12_AF5
    {GPIO_PE12, SPI4_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_4), 5},
    #endif
    #ifdef SPI4_SCK_PE2_AF5
    {GPIO_PE2, SPI4_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_4), 5},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< @brief SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] =
{
    #ifdef SPI1_MISO_PA6_AF5
    {GPIO_PA6, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI1_MISO_PB4_AF5
    {GPIO_PB4, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI1_MISO_PG3_AF5
    {GPIO_PG3, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI2_MISO_PA10_AF5
    {GPIO_PA10, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI2_MISO_PB14_AF5
    {GPIO_PB14, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI3_MISO_PB4_AF6
    {GPIO_PB4, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI3_MISO_PC11_AF6
    {GPIO_PC11, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI4_MISO_PE13_AF5
    {GPIO_PE13, SPI4_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_4), 5},
    #endif
    #ifdef SPI4_MISO_PE5_AF5
    {GPIO_PE5, SPI4_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_4), 5},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< @brief SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] =
{
    #ifdef SPI1_MOSI_PA7_AF5
    {GPIO_PA7, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI1_MOSI_PB5_AF5
    {GPIO_PB5, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI1_MOSI_PG4_AF5
    {GPIO_PG4, SPI1_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_1), 5},
    #endif
    #ifdef SPI2_MOSI_PA11_AF5
    {GPIO_PA11, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI2_MOSI_PB15_AF5
    {GPIO_PB15, SPI2_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_2), 5},
    #endif
    #ifdef SPI3_MOSI_PB5_AF6
    {GPIO_PB5, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI3_MOSI_PC12_AF6
    {GPIO_PC12, SPI3_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_3), 6},
    #endif
    #ifdef SPI4_MOSI_PE14_AF5
    {GPIO_PE14, SPI4_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_4), 5},
    #endif
    #ifdef SPI4_MOSI_PE6_AF5
    {GPIO_PE6, SPI4_BASE_ADDRESS, hal_ll_spi_module_num(SPI_MODULE_4), 5},
    #endif
    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
