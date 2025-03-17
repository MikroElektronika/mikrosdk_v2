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
/*

  This file is part of mikroSDK.

  Copyright (c) ${COPYRIGHT_YEAR}, MikroElektronika - www.mikroe.com

  All rights reserved.

-------------------------------------------------------------------------- */
/*!
 * @file  hal_ll_spi_master_pin_map.h
 * @brief SPI MASTER HAL LOW LEVEL PIN MAPS.
 */

#ifndef _HAL_LL_SPI_MASTER_PIN_MAP_H_
#define _HAL_LL_SPI_MASTER_PIN_MAP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_pin_names.h"

/*!< @brief Helper macro for getting adequate module index number */
#define hal_ll_spi_master_module_num(_module_num) (_module_num - 1)

/*!< @brief Macro defining `weak` attribute */
#define __weak __attribute__((weak))

/*!< @brief SPI Master pin map structure. */
typedef struct {
    hal_ll_pin_name_t pin;
    uint8_t module_index;
} hal_ll_spi_master_pin_map_t;

/*!< @brief SPI MASTER SCK pins */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] = {
    //------------ BEGIN SCK
    #ifdef SPI0_SCK_PB1
    {GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_SCK_PB7
    {GPIO_PB7, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_SCK_PB5
    {GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_SCK_PD7
    {GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_PC1
    {GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI0_SCK_PC7
    {GPIO_PC7, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI2_SCK_PE7
    {GPIO_PE7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_PF7
    {GPIO_PF7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI0_SCK_PC5
    {GPIO_PC5, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_SCK_PD5
    {GPIO_PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_PE5
    {GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCK
};

/*!< @brief SPI MASTER MISO pins */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] = {
    //------------ BEGIN MISO
    #ifdef SPI0_MISO_PB3
    {GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_MISO_PB6
    {GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_MISO_PB4
    {GPIO_PB4, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_MISO_PE2
    {GPIO_PE2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_PC0
    {GPIO_PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI0_MISO_PC6
    {GPIO_PC6, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_MISO_PD6
    {GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_PE6
    {GPIO_PE6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_PF6
    {GPIO_PF6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MISO
};

/*!< @brief SPI MASTER MOSI pins */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] = {
    //------------ BEGIN MOSI
    #ifdef SPI0_MOSI_PB2
    {GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_MOSI_PB5
    {GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_MOSI_PB3
    {GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_MOSI_PE3
    {GPIO_PE3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI0_MOSI_PC5
    {GPIO_PC5, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_MOSI_PD5
    {GPIO_PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_PE5
    {GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_PF5
    {GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI0_MOSI_PC7
    {GPIO_PC7, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_MOSI_PD7
    {GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_PE7
    {GPIO_PE7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MOSI
};

/*!< @brief SPI MASTER SS pins */
static const hal_ll_spi_master_pin_map_t _spi_ss_map[] = {
    //------------ BEGIN SS
    #ifdef SPI0_SS_PB0
    {GPIO_PB0, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_SS_PB4
    {GPIO_PB4, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI0_SS_PB2
    {GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_SS_PD6
    {GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SS_PE2
    {GPIO_PE2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI0_SS_PC4
    {GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_0)},
    #endif
    #ifdef SPI1_SS_PD4
    {GPIO_PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SS_PE4
    {GPIO_PE4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SS_PF4
    {GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SS
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ---------------------------------------------------------------------- END
