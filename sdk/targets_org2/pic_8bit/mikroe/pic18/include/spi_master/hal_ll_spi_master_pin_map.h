/****************************************************************************
**
** Copyright (C) 2023 MikroElektronika d.o.o.
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
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t module_index;
} hal_ll_spi_master_pin_map_t;

/*!< @brief SPI MASTER SCK pins */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] =
{
    //------------ BEGIN SCK
    #ifdef SPI_MODULE
    #ifdef SPI_SCK_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_SCK_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_SCK_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RA3
    { PA3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RE7
    { PE7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RF5
    { PF5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RG1
    { PG1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_SCK_RG3
    { PG3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_SCK_RA0
    { PA0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RA5
    { PA5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD4
    { PD4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RA2
    { PA2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RA6
    { PA6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RA7
    { PA7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RE2
    { PE2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RE6
    { PE6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RF7
    { PF7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_SCK_RG2
    { PG2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif


    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCK
};

/*!< @brief SPI MASTER MISO pins */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] =
{
    //------------ BEGIN MISO
    #ifdef SPI_MODULE
    #ifdef SPI_MISO_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MISO_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MISO_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA0
    { PA0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RA4
    { PA4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RD4
    { PD4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RE0
    { PE0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RE4
    { PE4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RF6
    { PF6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MISO_RG4
    { PG4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MISO_RA0
    { PA0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RA5
    { PA5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD4
    { PD4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RE1
    { PE1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RE3
    { PE3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MISO_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MISO
};

/*!< @brief SPI MASTER MOSI pins */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] =
{
    //------------ BEGIN MOSI
    #ifdef SPI_MODULE
    #ifdef SPI_MOSI_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #ifdef SPI_MOSI_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE) },
    #endif
    #endif

    #ifdef SPI_MODULE_1
    #ifdef SPI1_MOSI_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RA5
    { PA5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE1
    { PE1, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE3
    { PE3, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #ifdef SPI1_MOSI_RE5
    { PE5, hal_ll_spi_master_module_num(SPI_MODULE_1) },
    #endif
    #endif

    #ifdef SPI_MODULE_2
    #ifdef SPI2_MOSI_RA0
    { PA0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA1
    { PA1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA5
    { PA5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB0
    { PB0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB1
    { PB1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB2
    { PB2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB3
    { PB3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB4
    { PB4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB5
    { PB5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB6
    { PB6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RB7
    { PB7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC0
    { PC0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC1
    { PC1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC2
    { PC2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC3
    { PC3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC4
    { PC4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC5
    { PC5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC6
    { PC6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RC7
    { PC7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD2
    { PD2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD3
    { PD3, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD4
    { PD4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD5
    { PD5, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD6
    { PD6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSi_RD7
    { PD7, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD0
    { PD0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RD1
    { PD1, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RA4
    { PA4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RE0
    { PE0, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RE4
    { PE4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF2
    { PF2, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RF6
    { PF6, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #ifdef SPI2_MOSI_RG4
    { PG4, hal_ll_spi_master_module_num(SPI_MODULE_2) },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MOSI
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
