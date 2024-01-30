/****************************************************************************
**
** Copyright (C) 2024 MikroElektronika d.o.o.
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
 * @file  hal_ll_pps_defines.h
 * @brief This file contains supporting macros and enums for HAL LOW LEVEL PPS implementation.
 */

#ifndef _HAL_LL_PPS_DEFINES_H_
#define _HAL_LL_PPS_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "mcu_definitions.h"

/*!< @brief Enum defining pps module index */
typedef enum
{
    HAL_LL_PPS_MODULE_INDEX_1 = 0,
    HAL_LL_PPS_MODULE_INDEX_2,
    HAL_LL_PPS_MODULE_INDEX_3,
    HAL_LL_PPS_MODULE_INDEX_4,
    HAL_LL_PPS_MODULE_INDEX_5,
    HAL_LL_PPS_MODULE_INDEX_6,
    HAL_LL_PPS_MODULE_INDEX_7,
    HAL_LL_PPS_MODULE_INDEX_8,
    HAL_LL_PPS_MODULE_INDEX_9,
    HAL_LL_PPS_MODULE_INDEX_10
} hal_ll_pps_module_index_t;

/*!< @brief Enum defining pps functionalities */
typedef enum
{
    HAL_LL_PPS_FUNCTIONALITY_UART = 0,  // UART/USART module
    HAL_LL_PPS_FUNCTIONALITY_I2C_SCL,   // I2C module
    HAL_LL_PPS_FUNCTIONALITY_I2C_SDA,   // I2C module
    HAL_LL_PPS_FUNCTIONALITY_SPI_SCK,   // SPI module
    HAL_LL_PPS_FUNCTIONALITY_SPI_MISO,  // SPI module
    HAL_LL_PPS_FUNCTIONALITY_SPI_MOSI,  // SPI module
    HAL_LL_PPS_FUNCTIONALITY_PWM,       // TIM/PWM module
    HAL_LL_PPS_FUNCTIONALITY_IVT,       // Interrupt mapping
    HAL_LL_PPS_FUNCTIONALITY_CAN,       // CAN module

    HAL_LL_PPS_FUNCTIONALITY_NONE = 0xFF
} hal_ll_pps_functionality_t;

/*!< @brief Enum defining pps return values */
typedef enum
{
    HAL_LL_PPS_SUCCESS = 0,
    HAL_LL_PPS_DIRECTION_ERROR,
    HAL_LL_PPS_PIN_ERROR,
    HAL_LL_PPS_MODULE_ERROR
} hal_ll_pps_err_t;

#define HAL_LL_DEFAULT_PPS_REGISTER_STATE 0x3F3F
#define reg_addr_ptr(reg_addr) *(uint16_t *)reg_addr
#define write_reg_ptr(reg_addr,reg_val) reg_addr_ptr(reg_addr)|=reg_val
#define clear_reg_ptr(reg_addr,reg_val) reg_addr_ptr(reg_addr)&=~reg_val

#ifdef __GB610_FAMILY__
#ifdef HAL_LL_OSCCON_REG_ADDRESS
    /*!< @brief All dsPIC chips have the same unlock sequence */
    #define HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_FIRST #0x46
    #define HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_SECOND #0x57
    #define HAL_LL_PPS_UNLOCK 0
    #define HAL_LL_PPS_LOCK 1
    #define HAL_LL_PPS_UNLOCK_LOCK_BIT #6

    #define LOCK_BIT_REG_ADDRESS #0x0100
    #define LOCK_UNLOCK_BIT_MASK 6
        /*!< @brief Macro defining lock/unlock for PPS */
    #define hal_ll_pps_lock_unlock(value) if ( HAL_LL_PPS_UNLOCK == value ) { \
                                            asm { MOV LOCK_BIT_REG_ADDRESS, W3 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_FIRST, W4 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_SECOND, W5 } \
                                            asm { MOV.B W4, [W3] } \
                                            asm { MOV.B W5, [W3] } \
                                            asm { BCLR 0x0100, HAL_LL_PPS_UNLOCK_LOCK_BIT } \
                                          } else {\
                                            asm { MOV LOCK_BIT_REG_ADDRESS, W3 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_FIRST, W4 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_SECOND, W5 } \
                                            asm { MOV.B W4, [W3] } \
                                            asm { MOV.B W5, [W3] } \
                                            asm { BSET 0x0100, HAL_LL_PPS_UNLOCK_LOCK_BIT } \
                                          }
#endif
#else
#ifdef HAL_LL_OSCCON_REG_ADDRESS
    /*!< @brief All dsPIC chips have the same unlock sequence */
    #define HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_FIRST #0x46
    #define HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_SECOND #0x57
    #define HAL_LL_PPS_UNLOCK 0
    #define HAL_LL_PPS_LOCK 1
    #define HAL_LL_PPS_UNLOCK_LOCK_BIT #6

    #define LOCK_BIT_REG_ADDRESS #0x0742
    #define LOCK_UNLOCK_BIT_MASK 6
    #define hal_ll_pps_lock_unlock(value) if ( HAL_LL_PPS_UNLOCK == value ) { \
                                            asm { MOV LOCK_BIT_REG_ADDRESS, W3 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_FIRST, W4 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_SECOND, W5 } \
                                            asm { MOV.B W4, [W3] } \
                                            asm { MOV.B W5, [W3] } \
                                            asm { BCLR 0x0742, HAL_LL_PPS_UNLOCK_LOCK_BIT } \
                                          } else {\
                                            asm { MOV LOCK_BIT_REG_ADDRESS, W3 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_FIRST, W4 } \
                                            asm { MOV HAL_LL_PPS_LOCK_UNLOCK_SEQUENCE_KEY_SECOND, W5 } \
                                            asm { MOV.B W4, [W3] } \
                                            asm { MOV.B W5, [W3] } \
                                            asm { BSET 0x0742, HAL_LL_PPS_UNLOCK_LOCK_BIT } \
                                          }
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_PPS_DEFINES_H_
// ------------------------------------------------------------------------- END
