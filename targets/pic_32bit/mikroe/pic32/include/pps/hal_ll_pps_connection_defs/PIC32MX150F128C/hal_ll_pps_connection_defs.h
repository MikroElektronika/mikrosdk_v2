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
 * @file  hal_ll_pps_connection_defs.h
 * @brief This file contains pps maps per chip for LOW LEVEL HAL PPS implementation.
 */

#ifndef _HAL_LL_PPS_CONNECTION_DEFS_H_
#define _HAL_LL_PPS_CONNECTION_DEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_ll_pps_struct_def.h"

// -------------------------------------------------------------

/*!< @brief PPS INPUT FUNCTIONS */
static const hal_ll_pps_pin_map_t hal_ll_pps_input_map[] =
{
    #ifdef __RA1_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x00, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x00, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RB5_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x01, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RB1_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x02, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RB11_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x03, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RB8_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x04, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RA8_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RC8_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x06, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x06, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif
    #ifdef __RA9_CN
    #ifdef HAL_LL_U2RXR_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x07, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_U2RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI1R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x07, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_SDI1R_ADDRESS },
    #endif
    #endif

    #ifdef __RA2_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x00, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x00, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RB6_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x01, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RA4_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x02, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RB13_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x03, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RB2_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x04, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RC6_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RC1_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x06, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x06, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif
    #ifdef __RC3_CN
    #ifdef HAL_LL_U1RXR_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_UART ,     0x07, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_U1RXR_ADDRESS },
    #endif
    #ifdef HAL_LL_SDI2R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_INPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MISO , 0x07, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_SDI2R_ADDRESS },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PORT_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

/*!< @brief PPS OUTPUT FUNCTIONS */
static const hal_ll_pps_pin_map_t hal_ll_pps_output_map[] =
{
    #ifdef __RA0_CN
    #ifdef HAL_LL_RPA0R_ADDRESS
    { GPIO_PIN_0, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA0R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA0R_ADDRESS
    { GPIO_PIN_0, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA0R_ADDRESS },
    #endif
    #endif
    #ifdef __RB3_CN
    #ifdef HAL_LL_RPB3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB3R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB3R_ADDRESS },
    #endif
    #endif
    #ifdef __RB4_CN
    #ifdef HAL_LL_RPB4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB4R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB4R_ADDRESS },
    #endif
    #endif
    #ifdef __RB15_CN
    #ifdef HAL_LL_RPB15R_ADDRESS
    { GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB15R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB15R_ADDRESS
    { GPIO_PIN_15, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB15R_ADDRESS },
    #endif
    #endif
    #ifdef __RB7_CN
    #ifdef HAL_LL_RPB7R_ADDRESS
    { GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB7R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB7R_ADDRESS
    { GPIO_PIN_7, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB7R_ADDRESS },
    #endif
    #endif
    #ifdef __RC7_CN
    #ifdef HAL_LL_RPC7R_ADDRESS
    { GPIO_PIN_7, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC7R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC7R_ADDRESS
    { GPIO_PIN_7, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC7R_ADDRESS },
    #endif
    #endif
    #ifdef __RC0_CN
    #ifdef HAL_LL_RPC0R_ADDRESS
    { GPIO_PIN_0, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC0R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC0R_ADDRESS
    { GPIO_PIN_0, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC0R_ADDRESS },
    #endif
    #endif
    #ifdef __RC5_CN
    #ifdef HAL_LL_RPC5R_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x01, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC5R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC5R_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC5R_ADDRESS },
    #endif
    #endif

    #ifdef __RA1_CN
    #ifdef HAL_LL_RPA1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA1R_ADDRESS },
    #endif
    #endif
    #ifdef __RB5_CN
    #ifdef HAL_LL_RPB5R_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB5R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB5R_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB5R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB5R_ADDRESS
    { GPIO_PIN_5, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB5R_ADDRESS },
    #endif
    #endif
    #ifdef __RB1_CN
    #ifdef HAL_LL_RPB1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB1R_ADDRESS },
    #endif
    #endif
    #ifdef __RB11_CN
    #ifdef HAL_LL_RPB11R_ADDRESS
    { GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB11R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB11R_ADDRESS
    { GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB11R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB11R_ADDRESS
    { GPIO_PIN_11, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB11R_ADDRESS },
    #endif
    #endif
    #ifdef __RB8_CN
    #ifdef HAL_LL_RPB8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB8R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB8R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB8R_ADDRESS },
    #endif
    #endif
    #ifdef __RA8_CN
    #ifdef HAL_LL_RPA8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA8R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA8R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA8R_ADDRESS },
    #endif
    #endif
    #ifdef __RC8_CN
    #ifdef HAL_LL_RPC8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC8R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC8R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC8R_ADDRESS
    { GPIO_PIN_8, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC8R_ADDRESS },
    #endif
    #endif
    #ifdef __RA9_CN
    #ifdef HAL_LL_RPA9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA9R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA9R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA9R_ADDRESS },
    #endif
    #endif

    #ifdef __RA2_CN
    #ifdef HAL_LL_RPA2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPA2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPA2R_ADDRESS },
    #endif
    #endif
    #ifdef __RB6_CN
    #ifdef HAL_LL_RPB6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB6R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB6R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPB6R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPB6R_ADDRESS },
    #endif
    #endif
    #ifdef __RA4_CN
    #ifdef HAL_LL_RPA4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPA4R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA4R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPA4R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPA4R_ADDRESS },
    #endif
    #endif
    #ifdef __RB13_CN
    #ifdef HAL_LL_RPB13R_ADDRESS
    { GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB13R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB13R_ADDRESS
    { GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB13R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB13R_ADDRESS
    { GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPB13R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB13R_ADDRESS
    { GPIO_PIN_13, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPB13R_ADDRESS },
    #endif
    #endif
    #ifdef __RB2_CN
    #ifdef HAL_LL_RPB2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPB2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPB2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPB2R_ADDRESS },
    #endif
    #endif
    #ifdef __RC6_CN
    #ifdef HAL_LL_RPC6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC6R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC6R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPC6R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC6R_ADDRESS
    { GPIO_PIN_6, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPC6R_ADDRESS },
    #endif
    #endif
    #ifdef __RC1_CN
    #ifdef HAL_LL_RPC1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPC1R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC1R_ADDRESS
    { GPIO_PIN_1, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPC1R_ADDRESS },
    #endif
    #endif
    #ifdef __RC3_CN
    #ifdef HAL_LL_RPC3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x03, HAL_LL_PPS_MODULE_INDEX_1, HAL_LL_RPC3R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI, 0x04, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC3R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_4, HAL_LL_RPC3R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x06, HAL_LL_PPS_MODULE_INDEX_5, HAL_LL_RPC3R_ADDRESS },
    #endif
    #endif

    #ifdef __RA3_CN
    #ifdef HAL_LL_RPA3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPA3R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPA3R_ADDRESS
    { GPIO_PIN_3, GPIO_PORT_A, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPA3R_ADDRESS },
    #endif
    #endif
    #ifdef __RB14_CN
    #ifdef HAL_LL_RPB14R_ADDRESS
    { GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB14R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB14R_ADDRESS
    { GPIO_PIN_14, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPB14R_ADDRESS },
    #endif
    #endif
    #ifdef __RB0_CN
    #ifdef HAL_LL_RPB0R_ADDRESS
    { GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB0R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB0R_ADDRESS
    { GPIO_PIN_0, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPB0R_ADDRESS },
    #endif
    #endif
    #ifdef __RB10_CN
    #ifdef HAL_LL_RPB10R_ADDRESS
    { GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB10R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB10R_ADDRESS
    { GPIO_PIN_10, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPB10R_ADDRESS },
    #endif
    #endif
    #ifdef __RB9_CN
    #ifdef HAL_LL_RPB9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPB9R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPB9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_B, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPB9R_ADDRESS },
    #endif
    #endif
    #ifdef __RC9_CN
    #ifdef HAL_LL_RPC9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC9R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC9R_ADDRESS
    { GPIO_PIN_9, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPC9R_ADDRESS },
    #endif
    #endif
    #ifdef __RC2_CN
    #ifdef HAL_LL_RPC2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC2R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC2R_ADDRESS
    { GPIO_PIN_2, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPC2R_ADDRESS },
    #endif
    #endif
    #ifdef __RC4_CN
    #ifdef HAL_LL_RPC4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_UART,     0x02, HAL_LL_PPS_MODULE_INDEX_2, HAL_LL_RPC4R_ADDRESS },
    #endif
    #ifdef HAL_LL_RPC4R_ADDRESS
    { GPIO_PIN_4, GPIO_PORT_C, HAL_LL_GPIO_DIGITAL_OUTPUT, HAL_LL_PPS_FUNCTIONALITY_PWM,      0x05, HAL_LL_PPS_MODULE_INDEX_3, HAL_LL_RPC4R_ADDRESS },
    #endif
    #endif

    { HAL_LL_PIN_NC, HAL_LL_PORT_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_PIN_NC, HAL_LL_MODULE_ERROR, HAL_LL_MODULE_ERROR }
};

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PPS_CONNECTION_DEFS_H_
// ------------------------------------------------------------------------- END
