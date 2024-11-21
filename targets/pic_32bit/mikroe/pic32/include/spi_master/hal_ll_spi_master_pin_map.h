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
    #ifdef SPI_MODULE
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RF6
    { GPIO_PF6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD1
    { GPIO_PD1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_SCK_RB15
    { GPIO_PB15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RG6
    { GPIO_PG6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_SCK_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_SCK_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_SCK_RD1
    { GPIO_PD1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_SCK_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_SCK_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_SCK_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_SCK_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_SCK_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_SCK_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_SCK_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCK
};

/*!< @brief SPI MASTER MISO pins */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] = {
    //------------ BEGIN MISO
    #ifdef SPI_MODULE
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_RA1
    { GPIO_PA1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB11
    { GPIO_PB11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB8
    { GPIO_PB8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA8
    { GPIO_PA8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC8
    { GPIO_PC8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA9
    { GPIO_PA9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF12
    { GPIO_PF12, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF7
    { GPIO_PF7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MISO_RA2
    { GPIO_PA2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB6
    { GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RA4
    { GPIO_PA4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB13
    { GPIO_PB13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB2
    { GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC3
    { GPIO_PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC6
    { GPIO_PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF12
    { GPIO_PF12, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF7
    { GPIO_PF7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MISO_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MISO_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MISO_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MISO_RD1
    { GPIO_PD1, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RG9
    { GPIO_PG9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RD0
    { GPIO_PD0, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RB6
    { GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RD5
    { GPIO_PD5, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RB2
    { GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RF3
    { GPIO_PF3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RC2
    { GPIO_PC2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RE8
    { GPIO_PE8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MISO
};

/*!< @brief SPI MASTER MOSI pins */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] = {
    //------------ BEGIN MOSI
    #ifdef SPI_MODULE
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_RA1
    { GPIO_PA1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB11
    { GPIO_PB11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB8
    { GPIO_PB8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA2
    { GPIO_PA2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB6
    { GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA4
    { GPIO_PA4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB13
    { GPIO_PB13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB2
    { GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC3
    { GPIO_PC3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA8
    { GPIO_PA8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC8
    { GPIO_PC8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA9
    { GPIO_PA9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC6
    { GPIO_PC6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF3
    { GPIO_PF3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD9
    { GPIO_PD9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG6
    { GPIO_PG6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB15
    { GPIO_PB15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD4
    { GPIO_PD4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB0
    { GPIO_PB0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE3
    { GPIO_PE3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB7
    { GPIO_PB7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD1
    { GPIO_PD1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG9
    { GPIO_PG9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD0
    { GPIO_PD0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD8
    { GPIO_PD8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD5
    { GPIO_PD5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF12
    { GPIO_PF12, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD12
    { GPIO_PD12, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF8
    { GPIO_PF8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE9
    { GPIO_PE9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF6
    { GPIO_PF6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC2
    { GPIO_PC2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE8
    { GPIO_PE8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MOSI_RA2
    { GPIO_PA2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB6
    { GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA4
    { GPIO_PA4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB13
    { GPIO_PB13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB2
    { GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA1
    { GPIO_PA1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB11
    { GPIO_PB11, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB8
    { GPIO_PB8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC3
    { GPIO_PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC6
    { GPIO_PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA8
    { GPIO_PA8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC8
    { GPIO_PC8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA9
    { GPIO_PA9, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF3
    { GPIO_PF3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MOSI_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF3
    { GPIO_PF3, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF8
    { GPIO_PF8, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MOSI_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF3
    { GPIO_PF3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD1
    { GPIO_PD1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG9
    { GPIO_PG9, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD0
    { GPIO_PD0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB6
    { GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD5
    { GPIO_PD5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB2
    { GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC2
    { GPIO_PC2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RE8
    { GPIO_PE8, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MOSI_RD3
    { GPIO_PD3, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG7
    { GPIO_PG7, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF5
    { GPIO_PF5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD11
    { GPIO_PD11, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF0
    { GPIO_PF0, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB1
    { GPIO_PB1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RE5
    { GPIO_PE5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC13
    { GPIO_PC13, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB3
    { GPIO_PB3, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC4
    { GPIO_PC4, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD15
    { GPIO_PD15, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG0
    { GPIO_PG0, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RA15
    { GPIO_PA15, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD2
    { GPIO_PD2, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG8
    { GPIO_PG8, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF4
    { GPIO_PF4, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD10
    { GPIO_PD10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF1
    { GPIO_PF1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB9
    { GPIO_PB9, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB10
    { GPIO_PB10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC14
    { GPIO_PC14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB5
    { GPIO_PB5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC1
    { GPIO_PC1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD14
    { GPIO_PD14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG1
    { GPIO_PG1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RA14
    { GPIO_PA14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD7
    { GPIO_PD7, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD6
    { GPIO_PD6, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MOSI_RD9
    { GPIO_PD9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RG6
    { GPIO_PG6, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB8
    { GPIO_PB8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB15
    { GPIO_PB15, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD4
    { GPIO_PD4, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB0
    { GPIO_PB0, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RE3
    { GPIO_PE3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB7
    { GPIO_PB7, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF12
    { GPIO_PF12, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD12
    { GPIO_PD12, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF8
    { GPIO_PF8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RC3
    { GPIO_PC3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RE9
    { GPIO_PE9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD1
    { GPIO_PD1, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RG9
    { GPIO_PG9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB14
    { GPIO_PB14, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD0
    { GPIO_PD0, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB6
    { GPIO_PB6, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD5
    { GPIO_PD5, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB2
    { GPIO_PB2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF3
    { GPIO_PF3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF13
    { GPIO_PF13, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF2
    { GPIO_PF2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RC2
    { GPIO_PC2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RE8
    { GPIO_PE8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MOSI
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ---------------------------------------------------------------------- END
