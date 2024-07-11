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

/*!< @brief SPI Master pin map structure. */
typedef struct
{
    hal_ll_pin_name_t pin;
    uint8_t module_index;
} hal_ll_spi_master_pin_map_t;

/*!< @brief SPI MASTER SCK pins */
static const hal_ll_spi_master_pin_map_t _spi_sck_map[] = {
    //------------ BEGIN SCK
    #ifdef SPI1_SCK_RB6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF6
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE8
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RG6
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_SCK_RC3
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA8_RPI24
    {PA8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA9_RPI25
    {PA9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC5_RPI53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA8_RPI24
    {PA8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA9_RPI25
    {PA9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC5_RPI53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI2_SCK_RA11_RPI27
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA12_RPI28
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC10_RPI58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC15_RPI63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE14_RPI94
    {PE14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE15_RPI95
    {PE15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF0_RPI96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA11_RPI27
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA12_RPI28
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC10_RPI58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC15_RPI63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE14_RPI94
    {PE14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE15_RPI95
    {PE15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF0_RPI96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI2_SCK_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE0_RPI80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE1_RP81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG0_RPI112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE0_RPI80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE1_RP81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG0_RPI112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RB7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD9
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC11_RP59
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RC11_RP59
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_SCK_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_SCK_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_SCK_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_SCK_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_SCK_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_SCK_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_SCK_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_SCK_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_SCK_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_SCK_RC10_RP26
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC11_RP27
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC12_RP28
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC13_RP29
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA0
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC5
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_SCK_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC14_RPI37
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC14_RPI37
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC14_RPI37
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RA14_RPI36
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA15_RPI35
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC1_RPI38
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC2_RPI39
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC3_RPI40
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RC4_RPI41
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD12_RPI42
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD14_RPI43
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE8_RPI33
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RE9_RPI34
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF12_RPI32
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA14_RPI36
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA15_RPI35
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC1_RPI38
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC2_RPI39
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC3_RPI40
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RC4_RPI41
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD12_RPI42
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD14_RPI43
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE8_RPI33
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RE9_RPI34
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF12_RPI32
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA14_RPI36
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA15_RPI35
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC1_RPI38
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC2_RPI39
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC3_RPI40
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC4_RPI41
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD12_RPI42
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD14_RPI43
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE8_RPI33
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RE9_RPI34
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF12_RPI32
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RF6_RPI45
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RF6_RPI45
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RF6_RPI45
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RF7_RPI44
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RF7_RPI44
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RF7_RPI44
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RB4_RPI4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RB4_RPI4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB4_RPI4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_SCK_RF1
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_SCK_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RA11_RPIN29
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA12_RPIN30
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA13_RPIN31
    {PA13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA14_RPIN32
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA11_RPIN29
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA12_RPIN30
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA13_RPIN31
    {PA13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA14_RPIN32
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA11_RPIN29
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA12_RPIN30
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA13_RPIN31
    {PA13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA14_RPIN32
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_SCK_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_SCK_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_SCK_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_SCK_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_SCK_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_SCK_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END SCK
};

/*!< @brief SPI MASTER MISO pins */
static const hal_ll_spi_master_pin_map_t _spi_miso_map[] = {
    //------------ BEGIN MISO
    #ifdef SPI1_MISO_RB5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF2
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RG7
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MISO_RF7
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA9
    {PA9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA8_RPI24
    {PA8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA9_RPI25
    {PA9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC5_RPI53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA8_RPI24
    {PA8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA9_RPI25
    {PA9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC5_RPI53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI2_MISO_RA11_RPI27
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA12_RPI28
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC10_RPI58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC15_RPI63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE14_RPI94
    {PE14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE15_RPI95
    {PE15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF0_RPI96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA11_RPI27
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA12_RPI28
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC10_RPI58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC15_RPI63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE14_RPI94
    {PE14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE15_RPI95
    {PE15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF0_RPI96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI2_MISO_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE0_RPI80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE1_RP81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG0_RPI112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE0_RPI80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE1_RP81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG0_RPI112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RB9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC11_RP59
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RC11_RP59
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MISO_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MISO_RB0_RPI32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB1_RPI33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB10_RPI42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB11_RPI43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB12_RPI44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB13_RPI45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB14_RPI46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB15_RPI47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB2_RPI34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB3_RPI35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB4_RPI36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB5_RPI37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB6_RPI38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB7_RPI39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB8_RPI40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RB9_RPI41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC12_RPI60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC13_RPI61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC14_RPI62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD10_RPI74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD11_RPI75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD8_RPI72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD9_RPI73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE1_RPI81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE3_RPI83
    {PE3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE6_RPI86
    {PE6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG7_RPI119
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG9_RPI121
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MISO_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MISO_RA0_RPI16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA1_RPI17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA14_RPI30
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA15_RPI31
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA2_RPI18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA3_RPI19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA4_RPI20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA5_RPI21
    {PA5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA6_RPI22
    {PA6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RA7_RPI23
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC1_RPI49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC2_RPI50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC3_RPI51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RC4_RPI52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD12_RPI76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD13_RPI77
    {PD13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD14_RPI78
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE8_RPI88
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RE9_RPI89
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG12_RPI124
    {PG12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MISO_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MISO_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MISO_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MISO_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MISO_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MISO_RC10_RP26
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC11_RP27
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC12_RP28
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC13_RP29
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RB0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA7
    {PA7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC3
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MISO_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC14_RPI37
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC14_RPI37
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC14_RPI37
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RA14_RPI36
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA15_RPI35
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC1_RPI38
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC2_RPI39
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC3_RPI40
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RC4_RPI41
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD12_RPI42
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD14_RPI43
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE8_RPI33
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RE9_RPI34
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF12_RPI32
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA14_RPI36
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA15_RPI35
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC1_RPI38
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC2_RPI39
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC3_RPI40
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RC4_RPI41
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD12_RPI42
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD14_RPI43
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE8_RPI33
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RE9_RPI34
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF12_RPI32
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA14_RPI36
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA15_RPI35
    {PA15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC1_RPI38
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC2_RPI39
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC3_RPI40
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC4_RPI41
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD12_RPI42
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD14_RPI43
    {PD14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE8_RPI33
    {PE8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RE9_RPI34
    {PE9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF12_RPI32
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RF6_RPI45
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RF6_RPI45
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RF6_RPI45
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RF7_RPI44
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RF7_RPI44
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RF7_RPI44
    {PF7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RB4_RPI4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RB4_RPI4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB4_RPI4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MISO_RB13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MISO_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RA11_RPIN29
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA12_RPIN30
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA13_RPIN31
    {PA13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA14_RPIN32
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA11_RPIN29
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA12_RPIN30
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA13_RPIN31
    {PA13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA14_RPIN32
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA11_RPIN29
    {PA11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA12_RPIN30
    {PA12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA13_RPIN31
    {PA13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA14_RPIN32
    {PA14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MISO_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MISO_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MISO_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MISO_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MISO_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MISO_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MISO
};

/*!< @brief SPI MASTER MOSI pins */
static const hal_ll_spi_master_pin_map_t _spi_mosi_map[] = {
    //------------ BEGIN MOSI
    #ifdef SPI1_MOSI_RB4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF3
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RG8
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MOSI_RF8
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA4
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI2_MOSI_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI2_MOSI_RE1_RP81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RE1_RP81
    {PE1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RB8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA4_RP20
    {PA4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB11_RP43
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB3_RP35
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB4_RP36
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB5_RP37
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB6_RP38
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB7_RP39
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB8_RP40
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB9_RP41
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RA0_RP16
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RA1_RP17
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RA2_RP18
    {PA2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RA3_RP19
    {PA3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB0_RP32
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB1_RP33
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB12_RP44
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB13_RP45
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB14_RP46
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB15_RP47
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB2_RP34
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RC0_RP48
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC1_RP49
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC6_RP54
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC7_RP55
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC8_RP56
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC9_RP57
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RC10_RP58
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC12_RP60
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC13_RP61
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC2_RP50
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC3_RP51
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC4_RP52
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC5_RP53
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RD10_RP74
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RC14_RP62
    {PC14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC15_RP63
    {PC15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD11_RP75
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD12_RP76
    {PD12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD8_RP72
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD9_RP73
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RB10_RP42
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC11_RP59
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RC11_RP59
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MOSI_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MOSI_RD0_RP64
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD1_RP65
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD2_RP66
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD3_RP67
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD4_RP68
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD5_RP69
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD6_RP70
    {PD6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RD7_RP71
    {PD7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RE0_RP80
    {PE0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RE2_RP82
    {PE2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RE4_RP84
    {PE4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RE5_RP85
    {PE5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RE7_RP87
    {PE7, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF0_RP96
    {PF0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF1_RP97
    {PF1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF3_RP99
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF4_RP100
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF5_RP101
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG6_RP118
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG8_RP120
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MOSI_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MOSI_RD15_RP79
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF12_RP108
    {PF12, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF13_RP109
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF2_RP98
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RF8_RP104
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG0_RP112
    {PG0, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG1_RP113
    {PG1, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG13_RP125
    {PG13, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG14_RP126
    {PG14, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI4_MOSI_RG15_RP127
    {PG15, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MOSI_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MOSI_RF6_RP102
    {PF6, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MOSI_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MOSI_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MOSI_RC10_RP26
    {PC10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC11_RP27
    {PC11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC12_RP28
    {PC12, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RC13_RP29
    {PC13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RA1
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RC4
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI1_MOSI_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RB0_RP0
    {PB0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB1_RP1
    {PB1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB14_RP14
    {PB14, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB15_RP29
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB2_RP13
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB4_RP28
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB5_RP18
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB6_RP6
    {PB6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB7_RP7
    {PB7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB8_RP8
    {PB8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB9_RP9
    {PB9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD0_RP11
    {PD0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD1_RP24
    {PD1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD10_RP3
    {PD10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD11_RP12
    {PD11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD2_RP23
    {PD2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD3_RP22
    {PD3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD4_RP25
    {PD4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD5_RP20
    {PD5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD8_RP2
    {PD8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RD9_RP4
    {PD9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF2_RP30
    {PF2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF3_RP16
    {PF3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF4_RP10
    {PF4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF5_RP17
    {PF5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG6_RP21
    {PG6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG7_RP26
    {PG7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG8_RP19
    {PG8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RG9_RP27
    {PG9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RD15_RP5
    {PD15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF13_RP31
    {PF13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RF8_RP15
    {PF8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB10_RP10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB11_RP11
    {PB11, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB12_RP12
    {PB12, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB13_RP13
    {PB13, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB15_RP15
    {PB15, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB2_RP2
    {PB2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB3_RP3
    {PB3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB5_RP5
    {PB5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC0_RP16
    {PC0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC1_RP17
    {PC1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC2_RP18
    {PC2, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC3_RP19
    {PC3, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC4_RP20
    {PC4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC5_RP21
    {PC5, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC6_RP22
    {PC6, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC7_RP23
    {PC7, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC8_RP24
    {PC8, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RC9_RP25
    {PC9, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI4_MOSI_RB10
    {PB10, hal_ll_spi_master_module_num(SPI_MODULE_4)},
    #endif
    #ifdef SPI1_MOSI_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RA0_RP26
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RA1_RP27
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RB4_RP4
    {PB4, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RA10_RP28
    {PA10, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI1_MOSI_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI1_MOSI_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_1)},
    #endif
    #ifdef SPI2_MOSI_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI2_MOSI_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_2)},
    #endif
    #ifdef SPI3_MOSI_RA0_RP5
    {PA0, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    #ifdef SPI3_MOSI_RA1_RP6
    {PA1, hal_ll_spi_master_module_num(SPI_MODULE_3)},
    #endif
    { HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR }
    //------------ END MOSI
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_SPI_MASTER_PIN_MAP_H_
// ------------------------------------------------------------------------- END
