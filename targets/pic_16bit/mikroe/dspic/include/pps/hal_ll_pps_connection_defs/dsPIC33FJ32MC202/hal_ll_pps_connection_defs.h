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
 * @file  hal_ll_pps_connection_defs.h
 * @brief This file contains pps maps per chip for LOW LEVEL HAL PPS
 *        implementation for dsPIC33FJ32MC202.
 */

#ifndef _HAL_LL_PPS_CONNECTION_DEFS_H_
#define _HAL_LL_PPS_CONNECTION_DEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_pps_struct_def.h"

/**
 * NOTE:
 * This macro is used for pins that do not have adequate PPS
 * registers according to datasheet.
 */
#define INVALID_PPS_ADDRESS (0) // TODO

// -------------------------------------------------------------

/*!< @brief PPS INPUT FUNCTIONS */
static const hal_ll_pps_pin_map_t hal_ll_pps_input_map[] =
{
    #ifdef UART1_RX_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 1, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 10, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 11, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 12, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 13, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 14, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 15, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 2, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 3, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 4, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 5, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 6, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 7, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 8, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef UART1_RX_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 9, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR18_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 0, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 1, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 10, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 11, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 12, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 13, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 14, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 15, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 2, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 3, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 4, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 5, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 6, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 7, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 8, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif
    #ifdef SPI1_MISO_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO, 9, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPINR20_REG_ADDRESS},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PORT_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

/*!< @brief PPS OUTPUT FUNCTIONS */
static const hal_ll_pps_pin_map_t hal_ll_pps_output_map[] =
{
    #ifdef UART1_TX_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, 0x0003, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef UART1_TX_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART, (0x0003ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x0007, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef SPI1_MOSI_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, (0x0007ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, 0x0008, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef SPI1_SCK_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_SCK, (0x0008ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC1_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP1_OC2_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC1_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP2_OC2_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0012, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC1_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0012ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB0_RP0
    {GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB1_RP1
    {GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR0_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB10_RP10
    {GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB11_RP11
    {GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR5_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB12_RP12
    {GPIO_PIN_12, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB13_RP13
    {GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR6_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB14_RP14
    {GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB15_RP15
    {GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR7_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB2_RP2
    {GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB3_RP3
    {GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR1_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB4_RP4
    {GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB5_RP5
    {GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR2_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB6_RP6
    {GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB7_RP7
    {GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR3_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB8_RP8
    {GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, 0x0013, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR4_REG_ADDRESS},
    #endif
    #ifdef PWM_CCP3_OC2_RB9_RP9
    {GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM, (0x0013ul << 8), HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPOR4_REG_ADDRESS},
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PORT_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PPS_CONNECTION_DEFS_H_
// ------------------------------------------------------------------------- END
