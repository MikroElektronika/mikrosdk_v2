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
static const hal_ll_base_addr_t HAL_LL_SPI0_MASTER_BASE_ADDR = 0x40061000UL;
#endif
#ifdef SPI_MODULE_1
static const hal_ll_base_addr_t HAL_LL_SPI1_MASTER_BASE_ADDR = 0x40062000UL;
#endif
#ifdef SPI_MODULE_2
static const hal_ll_base_addr_t HAL_LL_SPI2_MASTER_BASE_ADDR = 0x40063000UL;
#endif
#ifdef SPI_MODULE_3
static const hal_ll_base_addr_t HAL_LL_SPI3_MASTER_BASE_ADDR = 0x40064000UL;
#endif

/*!< SPI alternate functions numbers. */
#ifdef SPI_MODULE_0
#define HAL_LL_SPI0_MASTER_GPIO_AF4        4
#define HAL_LL_SPI0_MASTER_GPIO_AF5        5
#endif
#ifdef SPI_MODULE_1
#define HAL_LL_SPI1_MASTER_GPIO_AF3        3
#define HAL_LL_SPI1_MASTER_GPIO_AF4        4
#define HAL_LL_SPI1_MASTER_GPIO_AF5        5
#define HAL_LL_SPI1_MASTER_GPIO_AF6        6
#define HAL_LL_SPI1_MASTER_GPIO_AF7        7
#endif
#ifdef SPI_MODULE_2
#define HAL_LL_SPI2_MASTER_GPIO_AF3        3
#define HAL_LL_SPI2_MASTER_GPIO_AF4        4
#define HAL_LL_SPI2_MASTER_GPIO_AF5        5
#endif
#ifdef SPI_MODULE_3
#define HAL_LL_SPI3_MASTER_GPIO_AF5        5
#define HAL_LL_SPI3_MASTER_GPIO_AF6        6
#define HAL_LL_SPI3_MASTER_GPIO_AF11       11
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
    #ifdef SPI0_SCK_PA2_AF4
    {GPIO_PA2,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_SCK_PB14_AF4
    {GPIO_PB14,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_SCK_PD2_AF4
    {GPIO_PD2,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_SCK_PF8_AF5
    {GPIO_PF8,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_PH6_AF3
    {GPIO_PH6,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI1_SCK_PA7_AF4
    {GPIO_PA7,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI1_SCK_PB3_AF5
    {GPIO_PB3,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PD5_AF5
    {GPIO_PD5,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_SCK_PH8_AF6
    {GPIO_PH8,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI1_SCK_PC1_AF7
    {GPIO_PC1,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF7},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_SCK_PG3_AF3
    {GPIO_PG3,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI2_SCK_PA10_AF4
    {GPIO_PA10,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI2_SCK_PA13_AF5
    {GPIO_PA13,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_SCK_PE8_AF5
    {GPIO_PE8,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_SCK_PE4_AF5
    {GPIO_PE4,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI3_SCK_PC10_AF6
    {GPIO_PC10,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_SCK_PB11_AF11
    {GPIO_PB11,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF11},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    
    #ifdef SPI_MODULE_0
    #ifdef SPI0_MISO_PA1_AF4
    {GPIO_PA1,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_MISO_PB13_AF4
    {GPIO_PB13,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_MISO_PD1_AF4
    {GPIO_PD1,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_MISO_PF7_AF5
    {GPIO_PF7,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_PH4_AF3
    {GPIO_PH4,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI1_MISO_PC7_AF4
    {GPIO_PC7,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI1_MISO_PB5_AF5
    {GPIO_PB5,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PD7_AF5
    {GPIO_PD7,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MISO_PE1_AF6
    {GPIO_PE1,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI1_MISO_PC3_AF7
    {GPIO_PC3,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF7},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MISO_PG4_AF3
    {GPIO_PG4,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI2_MISO_PA9_AF4
    {GPIO_PA9,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI2_MISO_PA14_AF5
    {GPIO_PA14,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MISO_PE9_AF5
    {GPIO_PE9,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MISO_PE3_AF5
    {GPIO_PE3,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI3_MISO_PC12_AF6
    {GPIO_PC12,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MISO_PB9_AF11
    {GPIO_PB9,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF11},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    
    #ifdef SPI_MODULE_0
    #ifdef SPI0_MOSI_PA0_AF4
    {GPIO_PA0,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_MOSI_PB12_AF4
    {GPIO_PB12,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_MOSI_PD0_AF4
    {GPIO_PD0,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI0_MOSI_PF6_AF5
    {GPIO_PF6,  HAL_LL_SPI0_MASTER_BASE_ADDR, SPI_MODULE_0, HAL_LL_SPI0_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_PH5_AF3
    {GPIO_PH5,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI1_MOSI_PC6_AF4
    {GPIO_PC6,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI1_MOSI_PB4_AF5
    {GPIO_PB4,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PD6_AF5
    {GPIO_PD6,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI1_MOSI_PE0_AF6
    {GPIO_PE0,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI1_MOSI_PC2_AF7
    {GPIO_PC2,  HAL_LL_SPI1_MASTER_BASE_ADDR, SPI_MODULE_1, HAL_LL_SPI1_MASTER_GPIO_AF7},
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MOSI_PF11_AF3
    {GPIO_PF11,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF3},
    #endif
    #ifdef SPI2_MOSI_PA8_AF4
    {GPIO_PA8,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF4},
    #endif
    #ifdef SPI2_MOSI_PA15_AF5
    {GPIO_PA15,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI2_MOSI_PE10_AF5
    {GPIO_PE10,  HAL_LL_SPI2_MASTER_BASE_ADDR, SPI_MODULE_2, HAL_LL_SPI2_MASTER_GPIO_AF5},
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MOSI_PE2_AF5
    {GPIO_PE2,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF5},
    #endif
    #ifdef SPI3_MOSI_PC11_AF6
    {GPIO_PC11,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF6},
    #endif
    #ifdef SPI3_MOSI_PB8_AF11
    {GPIO_PB8,  HAL_LL_SPI3_MASTER_BASE_ADDR, SPI_MODULE_3, HAL_LL_SPI3_MASTER_GPIO_AF11},
    #endif
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END