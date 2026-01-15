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
    #ifdef SPI0_SCK_P102_AF4
    {GPIO_P102, HAL_LL_UART0_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 4},
    #endif
    #ifdef SPI0_SCK_P412_AF4
    {GPIO_P412, HAL_LL_UART0_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 4},
    #endif
    #ifdef SPI1_SCK_P100_AF5
    {GPIO_P100, HAL_LL_UART1_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 5},
    #endif
    #ifdef SPI1_SCK_P112_AF5
    {GPIO_P112, HAL_LL_UART1_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 5},
    #endif
    #ifdef SPI2_SCK_P111_AF4
    {GPIO_P111, HAL_LL_UART2_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_2 ), 4},
    #endif
    #ifdef SPI3_SCK_P410_AF5
    {GPIO_P410, HAL_LL_UART3_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_3 ), 5},
    #endif
    #ifdef SPI4_SCK_P400_AF4
    {GPIO_P400, HAL_LL_UART4_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_4 ), 4},
    #endif
    #ifdef SPI9_SCK_P111_AF5
    {GPIO_P111, HAL_LL_UART9_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_9 ), 5},
    #endif
    #ifdef SPI9_SCK_P600_AF5
    {GPIO_P600, HAL_LL_UART9_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    #ifdef SPI0_MISO_P100_AF4
    {GPIO_P410, HAL_LL_UART0_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 4},
    #endif
    #ifdef SPI0_MISO_P410_AF4
    {GPIO_P100, HAL_LL_UART0_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 4},
    #endif
    #ifdef SPI1_MISO_P212_AF5
    {GPIO_P212, HAL_LL_UART1_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 5},
    #endif
    #ifdef SPI2_MISO_P113_AF4
    {GPIO_P113, HAL_LL_UART2_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_2 ), 4},
    #endif
    #ifdef SPI2_MISO_P301_AF4
    {GPIO_P301, HAL_LL_UART2_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_2 ), 4},
    #endif
    #ifdef SPI3_MISO_P408_AF5
    {GPIO_P408, HAL_LL_UART3_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_3 ), 5},
    #endif
    #ifdef SPI4_MISO_P206_AF4
    {GPIO_P206, HAL_LL_UART4_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_4 ), 4},
    #endif
    #ifdef SPI9_MISO_P110_AF5
    {GPIO_P110, HAL_LL_UART9_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_9 ), 5},
    #endif
    #ifdef SPI9_MISO_P601_AF5
    {GPIO_P601, HAL_LL_UART9_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    #ifdef SPI0_MOSI_P101_AF4
    {GPIO_P101, HAL_LL_UART0_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 4},
    #endif
    #ifdef SPI0_MOSI_P411_AF4
    {GPIO_P411, HAL_LL_UART0_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 4},
    #endif
    #ifdef SPI1_MOSI_P213_AF5
    {GPIO_P213, HAL_LL_UART1_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 5},
    #endif
    #ifdef SPI2_MOSI_P112_AF4
    {GPIO_P112, HAL_LL_UART2_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_2 ), 4},
    #endif
    #ifdef SPI2_MOSI_P302_AF4
    {GPIO_P302, HAL_LL_UART2_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_2 ), 4},
    #endif
    #ifdef SPI3_MOSI_P409_AF5
    {GPIO_P409, HAL_LL_UART3_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_3 ), 5},
    #endif
    #ifdef SPI4_MOSI_P205_AF4
    {GPIO_P205, HAL_LL_UART4_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_4 ), 4},
    #endif
    #ifdef SPI4_MOSI_P207_AF4
    {GPIO_P207, HAL_LL_UART4_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_4 ), 4},
    #endif
    #ifdef SPI9_MOSI_P109_AF5
    {GPIO_P109, HAL_LL_UART9_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_9 ), 5},
    #endif
    #ifdef SPI9_MOSI_P602_AF5
    {GPIO_P602, HAL_LL_UART9_BASE_ADDRESS, hal_ll_spi_master_module_num( SPI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
