/****************************************************************************
**
** Copyright (C) 2021 MikroElektronika d.o.o.
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

  Copyright (c) 2021, MikroElektonika - www.mikroe.com

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
__weak static const hal_ll_spi_master_pin_map_t _spi_sck_map[] = {
    //------------ BEGIN SCK
    #ifdef SPI_MODULE
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RF6
    { PF6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_SCK_RB15
    { PB15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RG6
    { PG6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_SCK_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_SCK_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_SCK_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_SCK_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_SCK_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_SCK_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_SCK_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_SCK_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_SCK_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_SCK_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCK
};

/*!< @brief SPI MASTER MISO pins */
__weak static const hal_ll_spi_master_pin_map_t _spi_miso_map[] = {
    //------------ BEGIN MISO
    #ifdef SPI_MODULE
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB11
    { PB11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB8
    { PB8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA8
    { PA8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC8
    { PC8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA9
    { PA9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF12
    { PF12, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF7
    { PF7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MISO_RA2
    { PA2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RA4
    { PA4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB13
    { PB13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF12
    { PF12, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RF7
    { PF7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MISO_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MISO_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MISO_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MISO_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MISO_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MISO_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MISO_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RG9
    { PG9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RF3
    { PF3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MISO_RE8
    { PE8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MISO
};

/*!< @brief SPI MASTER MOSI pins */
__weak static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] = {
    //------------ BEGIN MOSI
    #ifdef SPI_MODULE
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB11
    { PB11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB8
    { PB8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA2
    { PA2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA4
    { PA4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB13
    { PB13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA8
    { PA8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC8
    { PC8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA9
    { PA9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF3
    { PF3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD9
    { PD9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG6
    { PG6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB15
    { PB15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD4
    { PD4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE3
    { PE3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG9
    { PG9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD8
    { PD8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF12
    { PF12, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD12
    { PD12, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF8
    { PF8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE9
    { PE9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF6
    { PF6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE8
    { PE8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MOSI_RA2
    { PA2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA4
    { PA4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB13
    { PB13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB11
    { PB11, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB8
    { PB8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA8
    { PA8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC8
    { PC8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA9
    { PA9, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF3
    { PF3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    #ifdef SPI_MODULE_3
    #ifdef SPI3_MOSI_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF3
    { PF3, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RF8
    { PF8, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #ifdef SPI3_MOSI_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_3) },
    #endif
    #endif

    #ifdef SPI_MODULE_4
    #ifdef SPI4_MOSI_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF3
    { PF3, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RG9
    { PG9, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RE8
    { PE8, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #ifdef SPI4_MOSI_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_4) },
    #endif
    #endif

    #ifdef SPI_MODULE_5
    #ifdef SPI5_MOSI_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG7
    { PG7, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD11
    { PD11, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF0
    { PF0, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC13
    { PC13, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD15
    { PD15, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG0
    { PG0, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RA15
    { PA15, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG8
    { PG8, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF4
    { PF4, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD10
    { PD10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RF1
    { PF1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB9
    { PB9, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB10
    { PB10, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC14
    { PC14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD14
    { PD14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RA14
    { PA14, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #ifdef SPI5_MOSI_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_5) },
    #endif
    #endif

    #ifdef SPI_MODULE_6
    #ifdef SPI6_MOSI_RD9
    { PD9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RG6
    { PG6, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB8
    { PB8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB15
    { PB15, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD4
    { PD4, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RE3
    { PE3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF12
    { PF12, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD12
    { PD12, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF8
    { PF8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RE9
    { PE9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RG9
    { PG9, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB14
    { PB14, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF3
    { PF3, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF13
    { PF13, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_6) },
    #endif
    #ifdef SPI6_MOSI_RE8
    { PE8, hal_ll_spi_master_module_num(SPI_MODULE_6) },
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
