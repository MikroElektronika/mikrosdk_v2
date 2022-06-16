/****************************************************************************
**
** Copyright (C) 2022 MikroElektronika d.o.o.
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
 * @file  hal_ll_one_wire.h
 * @brief API for One Wire HAL LOW LEVEL layer.
 */

#ifndef _HAL_LL_ONE_WIRE_H_
#define _HAL_LL_ONE_WIRE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_ll_gpio.h"

/**
 * @brief Structure for storing One Wire device address.
 * @details Unique One Wire address used for device addressing.
 */
typedef struct {
    uint8_t address[8]; /*!< One Wire address buffer. */
} hal_ll_one_wire_rom_address_t;

/**
 * @brief One Wire HAL Low Level context structure.
 * @details The context structure for storing driver internal state. The contents of the
 * context structure are used by the module and must not be altered. Reading or
 * writing data directly from a control structure by user should be avoided.
 */
#if defined(__hal_ll_gpio_subset_1__)
typedef struct {
    hal_ll_pin_name_t data_pin; // One Wire data pin.
    volatile uint32_t moder; // Register for altering GPIO pin direction.
    volatile uint32_t moder_set; // Variable for configuring pin as General purpose output.
    volatile uint32_t moder_clear; // Variable for configuring pin as General purpose input (reset state).
    volatile uint32_t bsrr; // Register for GPIO port bit set/reset.
    volatile uint32_t idr; // Register for reading current GPIO pin state.
} hal_ll_one_wire_local_t;
#elif defined(__hal_ll_gpio_subset_2__)
typedef struct {
    hal_ll_pin_name_t data_pin; // One Wire data pin.
    volatile uint32_t crl; // Register for altering GPIO pin direction (lower eight pins).
    volatile uint32_t crh; // Register for altering GPIO pin direction (higher eight pins).
    volatile uint32_t crx_set; // Variable for configuring pin as General purpose output.
    volatile uint32_t crx_clear; // Variable for configuring pin as General purpose input (reset state).
    volatile uint32_t bsrr; // Register for GPIO port bit set/reset.
    volatile uint32_t idr; // Register for reading current GPIO pin state.
} hal_ll_one_wire_local_t;
#endif
/**
 * @brief One Wire HAL Low Level initialization configuration structure.
 *
 * @details
 * - data_pin value - to be configured as desired.
 * - state value    - NOTE must not be altered (it is supposed to be set automatically in Low Level Layer).
 */
typedef struct {
    hal_ll_pin_name_t data_pin; /*!< One Wire pin - user is to configure it as desired. */
    bool state; /*!< State of a pin. NOTE must not be altered. */
} hal_ll_one_wire_t;

/**
 * @details Enum containing predefined module return values.
 */
typedef enum {
    HAL_LL_ONE_WIRE_SUCCESS = 0, /*!< Success. */
    HAL_LL_ONE_WIRE_ERROR = (-1) /*!< Error. */
} hal_ll_one_wire_err_t;

/**
 * @brief Opens One Wire HAL Low Level object.
 * @details Opens One Wire HAL Low Level object on selected pin.
 * Enables appropriate PORT clock, configures pin to have digital output functionality,
 * makes sure that HIGH voltage state is applied on pin before any One Wire actions.
 * @param[in,out] *obj One Wire HAL Low Level object.
 * See #hal_ll_one_wire_t structure definition for detailed explanation.
 * @return None.
 * @pre Make sure that \p LowLevel structure has been adequately
 * populated beforehand.
 * @note It is recommended to check return value for error.
 */
void hal_ll_one_wire_open( hal_ll_one_wire_t *obj );

/**
 * @brief Reset One Wire bus.
 * @details Host shall send reset sequence and devices shall go into reset state.
 * @param[in,out] *handle One Wire HAL Low Level object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_ll_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_ll_one_wire_open function.
 */
hal_ll_err_t hal_ll_one_wire_reset( hal_ll_one_wire_t *obj );

/**
 * @brief Reads device's ROM information.
 * @details Allows the host to read eight-bit family code,
 * 48-bit serial number, and eight-bit CRC.
 *
 * @important THIS FUNCTION IS TO BE ISSUED ONLY IF WE ARE DEALING WITH
 * ONE DEVICE ONLY. THIS FUNCTION AUTOMATICALLY RESETS ONE WIRE BUS.
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @param[out] *device_rom_address Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_ll_one_wire_err_t, which is size dependant on the architecture.
 */
hal_ll_err_t hal_ll_one_wire_read_rom( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *device_rom_address );

/**
 * @brief Access device's level functions without transmitting ROM information.
 * @details Allows the host to access device functions without
 * providing the 64-bit ROM identification number.
 *
 * @important THIS FUNCTION IS TO BE ISSUED ONLY IF WE ARE DEALING WITH
 * ONE DEVICE ONLY. THIS FUNCTION AUTOMATICALLY RESETS ONE WIRE BUS.
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_ll_one_wire_err_t, which is size dependant on the architecture.
 */
hal_ll_err_t hal_ll_one_wire_skip_rom( hal_ll_one_wire_t *obj );

/**
 * @brief Selects a specific One Wire capable device on bus.
 * @details Select a One Wire device with specific ID.
 *
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_ll_one_wire_t structure definition for detailed explanation.
 * @param[in] device_rom_address Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_ll_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_one_wire_open function.
 */
hal_ll_err_t hal_ll_one_wire_match_rom( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *device_rom_address );

/**
 * @brief Search One Wire capable device on bus.
 * @details Search and list 1st device that is One Wire capable.
 *
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_ll_one_wire_t structure definition for detailed explanation.
 * @param[out] *one_wire_device_list Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_ll_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_ll_one_wire_open function.
 */
hal_ll_err_t hal_ll_one_wire_search_first_device( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list );

/**
 * @brief Search One Wire capable devices on bus.
 * @details Search devices that is One Wire capable.
 *
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_ll_one_wire_t structure definition for detailed explanation.
 * @param[out] *one_wire_device_list Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_ll_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_ll_one_wire_open function.
 */
hal_ll_err_t hal_ll_one_wire_search_next_device( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list );

/**
 * @brief Writes byte to One Wire bus.
 * @details Writes byte to One Wire bus.
 * @param[in] *write_data_buffer Data transmit buffer.
 * @param[in] write_data_length Number of bytes to write from data transmit buffer.
 * @return None.
 * @pre Before calling this function,
 * the user is expected to call #hal_ll_one_wire_open function.
 */
void hal_ll_one_wire_write_byte( uint8_t *write_data_buffer, size_t write_data_length );

/**
 * @brief Reads byte from One Wire bus.
 * @details Reads byte from One Wire bus.
 * @param[out] *read_data_buffer Data receive buffer.
 * @param[in] read_data_length Number of bytes to be read.
 * @return None.
 * @pre Before calling this function,
 * the user is expected to call #hal_ll_one_wire_open function.
 */
void hal_ll_one_wire_read_byte( uint8_t *read_data_buffer, size_t read_data_length );

/**
 * @brief Reconfigures One Wire pin settings.
 * @details Enables appropriate PORT clock, configures pin to have digital output functionality,
 * makes sure that HIGH voltage state is applied on pin before any One Wire actions.
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_ll_one_wire_t structure definition for detailed explanation.
 * @return None.
 * @pre Before calling this function,
 * the user is expected to call #hal_one_wire_open function.
 */
void hal_ll_one_wire_reconfigure( hal_ll_one_wire_t *obj );

#ifdef __cplusplus
}
#endif

#endif // _HAL_LL_ONE_WIRE_H_
// ------------------------------------------------------------------------- END
