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
    #ifdef SPI0_SCK_P111_AF6
    {GPIO_P111, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_SCK_P204_AF6
    {GPIO_P204, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_SCK_P702_AF6
    {GPIO_P702, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_SCK_P102_AF6
    {GPIO_P102, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_SCK_P412_AF6
    {GPIO_P412, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_SCK_P209_AF6
    {GPIO_P209, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_SCK_P702_AF6
    {GPIO_P702, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_SCK_P302_AF6
    {GPIO_P302, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #ifdef SPI0_SCK_P610_AF6
    {GPIO_P610, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_SCK_P203_AF6
    {GPIO_P203, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SCI0_SCK_P102_AF4
    {GPIO_P102, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCK_P204_AF4
    {GPIO_P204, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCK_P400_AF4
    {GPIO_P400, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SCK_P100_AF5
    {GPIO_P100, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SCK_P109_AF5
    {GPIO_P109, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SCK_P112_AF5
    {GPIO_P112, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_SCK_P400_AF5
    {GPIO_P400, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCK_P111_AF4
    {GPIO_P111, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI9_SCK_P111_AF5
    {GPIO_P111, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SCK_P204_AF5
    {GPIO_P204, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI0_SCK_P412_AF4
    {GPIO_P412, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SCK_P503_AF5
    {GPIO_P503, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCK_P202_AF4
    {GPIO_P202, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI9_SCK_P600_AF5
    {GPIO_P600, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI3_SCK_P311_AF5
    {GPIO_P311, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_SCK_P410_AF5
    {GPIO_P410, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_SCK_PB00_AF5
    {GPIO_PB00, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_SCK_P204_AF4
    {GPIO_P204, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_SCK_P400_AF4
    {GPIO_P400, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_SCK_P901_AF4
    {GPIO_P901, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI5_SCK_P503_AF5
    {GPIO_P503, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI5_SCK_P508_AF5
    {GPIO_P508, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI6_SCK_P306_AF4
    {GPIO_P306, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI6_SCK_P504_AF4
    {GPIO_P504, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI6_SCK_P508_AF4
    {GPIO_P508, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI7_SCK_P400_AF5
    {GPIO_P400, HAL_LL_SCI7_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI7_SCK_P612_AF5
    {GPIO_P612, HAL_LL_SCI7_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI8_SCK_P106_AF4
    {GPIO_P106, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI8_SCK_PA01_AF4
    {GPIO_PA01, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI1_SCK_P710_AF5
    {GPIO_P710, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI5_SCK_P507_AF5
    {GPIO_P507, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI6_SCK_P507_AF4
    {GPIO_P507, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI0_SCK_P300_AF4
    {GPIO_P300, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SCK_P402_AF5
    {GPIO_P402, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCK_P405_AF4
    {GPIO_P405, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_SCK_P803_AF4
    {GPIO_P803, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI4_SCK_P708_AF4
    {GPIO_P708, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_SCK_P100_AF5
    {GPIO_P100, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_SCK_P211_AF5
    {GPIO_P211, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI0_SCK_P601_AF4
    {GPIO_P601, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_SCK_P611_AF4
    {GPIO_P611, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_SCK_PB00_AF5
    {GPIO_PB00, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_SCK_PA04_AF4
    {GPIO_PA04, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_SCK_P315_AF5
    {GPIO_P315, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MISO pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_miso_map[] = {
    #ifdef SPI0_MISO_P100_AF6
    {GPIO_P100, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MISO_P410_AF6
    {GPIO_P410, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MISO_P110_AF6
    {GPIO_P110, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_MISO_P202_AF6
    {GPIO_P202, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_MISO_P700_AF6
    {GPIO_P700, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MISO_P110_AF6
    {GPIO_P110, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MISO_P202_AF6
    {GPIO_P202, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MISO_P700_AF6
    {GPIO_P700, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MISO_P100_AF6
    {GPIO_P100, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_MISO_P410_AF6
    {GPIO_P410, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MISO_P210_AF6
    {GPIO_P210, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MISO_P700_AF6
    {GPIO_P700, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MISO_P206_AF6
    {GPIO_P206, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #ifdef SPI0_MISO_P609_AF6
    {GPIO_P609, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MISO_P313_AF6
    {GPIO_P313, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SCI0_MISO_P100_AF4
    {GPIO_P100, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MISO_P104_AF4
    {GPIO_P104, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MISO_P206_AF4
    {GPIO_P206, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MISO_P410_AF4
    {GPIO_P410, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_MISO_P212_AF5
    {GPIO_P212, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_MISO_P402_AF5
    {GPIO_P402, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_MISO_P502_AF5
    {GPIO_P502, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_MISO_P301_AF4
    {GPIO_P301, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI9_MISO_P110_AF5
    {GPIO_P110, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MISO_P408_AF5
    {GPIO_P408, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI1_MISO_P708_AF5
    {GPIO_P708, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI9_MISO_P202_AF5
    {GPIO_P202, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MISO_P601_AF5
    {GPIO_P601, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI2_MISO_P113_AF4
    {GPIO_P113, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_MISO_P309_AF5
    {GPIO_P309, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_MISO_P408_AF5
    {GPIO_P408, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_MISO_P706_AF5
    {GPIO_P706, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_MISO_P206_AF4
    {GPIO_P206, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_MISO_P315_AF4
    {GPIO_P315, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_MISO_P511_AF4
    {GPIO_P511, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI5_MISO_P502_AF5
    {GPIO_P502, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI5_MISO_P513_AF5
    {GPIO_P513, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI6_MISO_P304_AF4
    {GPIO_P304, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI6_MISO_P505_AF4
    {GPIO_P505, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI7_MISO_P402_AF5
    {GPIO_P402, HAL_LL_SCI7_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI7_MISO_P614_AF5
    {GPIO_P614, HAL_LL_SCI7_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI8_MISO_P104_AF4
    {GPIO_P104, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI8_MISO_P607_AF4
    {GPIO_P607, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI0_MISO_P113_AF4
    {GPIO_P113, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MISO_P610_AF4
    {GPIO_P610, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_MISO_P401_AF5
    {GPIO_P401, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_MISO_P802_AF4
    {GPIO_P802, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI4_MISO_P414_AF4
    {GPIO_P414, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_MISO_P101_AF5
    {GPIO_P101, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MISO_P208_AF5
    {GPIO_P208, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI0_MISO_P602_AF4
    {GPIO_P602, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI2_MISO_P700_AF4
    {GPIO_P700, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI1_MISO_P706_AF5
    {GPIO_P706, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_MISO_PA02_AF4
    {GPIO_PA02, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_MISO_P901_AF5
    {GPIO_P901, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_MISO_P715_AF4
    {GPIO_P715, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_MISO_PA15_AF5
    {GPIO_PA15, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

/*!< SPI MOSI pins. */
static const hal_ll_spi_master_pin_map_t hal_ll_spi_master_mosi_map[] = {
    #ifdef SPI0_MOSI_P101_AF6
    {GPIO_P101, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MOSI_P411_AF6
    {GPIO_P411, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MOSI_P109_AF6
    {GPIO_P109, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_MOSI_P203_AF6
    {GPIO_P203, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_MOSI_P701_AF6
    {GPIO_P701, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MOSI_P109_AF6
    {GPIO_P109, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MOSI_P203_AF6
    {GPIO_P203, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MOSI_P701_AF6
    {GPIO_P701, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MOSI_P101_AF6
    {GPIO_P101, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI1_MOSI_P411_AF6
    {GPIO_P411, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MOSI_P211_AF6
    {GPIO_P211, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI1_MOSI_P701_AF6
    {GPIO_P701, HAL_LL_SPI1_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_1 ), 6},
    #endif
    #ifdef SPI0_MOSI_P207_AF6
    {GPIO_P207, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #ifdef SPI0_MOSI_P115_AF6
    {GPIO_P115, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MOSI_P202_AF6
    {GPIO_P202, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SPI0_MOSI_P611_AF6
    {GPIO_P611, HAL_LL_SPI0_MASTER_BASE_ADDR, hal_ll_spi_master_module_num( SPI_MODULE_0 ), 6},
    #endif
    #ifdef SCI0_MOSI_P101_AF4
    {GPIO_P101, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MOSI_P205_AF4
    {GPIO_P205, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MOSI_P411_AF4
    {GPIO_P411, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_MOSI_P213_AF5
    {GPIO_P213, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_MOSI_P401_AF5
    {GPIO_P401, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI1_MOSI_P501_AF5
    {GPIO_P501, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_MOSI_P102_AF4
    {GPIO_P102, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_MOSI_P112_AF4
    {GPIO_P112, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_MOSI_P302_AF4
    {GPIO_P302, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI9_MOSI_P109_AF5
    {GPIO_P109, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MOSI_P409_AF5
    {GPIO_P409, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MOSI_P203_AF5
    {GPIO_P203, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MOSI_P602_AF5
    {GPIO_P602, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI3_MOSI_P310_AF5
    {GPIO_P310, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_MOSI_P409_AF5
    {GPIO_P409, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI3_MOSI_P707_AF5
    {GPIO_P707, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_MOSI_P205_AF4
    {GPIO_P205, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_MOSI_P512_AF4
    {GPIO_P512, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI4_MOSI_P900_AF4
    {GPIO_P900, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI5_MOSI_P501_AF5
    {GPIO_P501, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI5_MOSI_P805_AF5
    {GPIO_P805, HAL_LL_SCI5_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_5 ), 5},
    #endif
    #ifdef SCI6_MOSI_P305_AF4
    {GPIO_P305, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI6_MOSI_P506_AF4
    {GPIO_P506, HAL_LL_SCI6_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_6 ), 4},
    #endif
    #ifdef SCI7_MOSI_P401_AF5
    {GPIO_P401, HAL_LL_SCI7_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI7_MOSI_P613_AF5
    {GPIO_P613, HAL_LL_SCI7_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_7 ), 5},
    #endif
    #ifdef SCI8_MOSI_P105_AF4
    {GPIO_P105, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI8_MOSI_PA00_AF4
    {GPIO_PA00, HAL_LL_SCI8_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_8 ), 4},
    #endif
    #ifdef SCI1_MOSI_P709_AF5
    {GPIO_P709, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI4_MOSI_P207_AF4
    {GPIO_P207, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI0_MOSI_P112_AF4
    {GPIO_P112, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI0_MOSI_P609_AF4
    {GPIO_P609, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_MOSI_P400_AF5
    {GPIO_P400, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_MOSI_P406_AF4
    {GPIO_P406, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI2_MOSI_P801_AF4
    {GPIO_P801, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI4_MOSI_P415_AF4
    {GPIO_P415, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_MOSI_P102_AF5
    {GPIO_P102, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI9_MOSI_P209_AF5
    {GPIO_P209, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif
    #ifdef SCI0_MOSI_P603_AF4
    {GPIO_P603, HAL_LL_SCI0_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_0 ), 4},
    #endif
    #ifdef SCI1_MOSI_P707_AF5
    {GPIO_P707, HAL_LL_SCI1_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_1 ), 5},
    #endif
    #ifdef SCI2_MOSI_PA03_AF4
    {GPIO_PA03, HAL_LL_SCI2_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_2 ), 4},
    #endif
    #ifdef SCI3_MOSI_P900_AF5
    {GPIO_P900, HAL_LL_SCI3_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_3 ), 5},
    #endif
    #ifdef SCI4_MOSI_P714_AF4
    {GPIO_P714, HAL_LL_SCI4_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_4 ), 4},
    #endif
    #ifdef SCI9_MOSI_PA14_AF5
    {GPIO_PA14, HAL_LL_SCI9_BASE_ADDR, hal_ll_spi_master_module_num( SCI_MODULE_9 ), 5},
    #endif

    {HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_PIN_NC, HAL_LL_PIN_NC}
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
