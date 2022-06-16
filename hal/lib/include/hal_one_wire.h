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
 * @file  hal_one_wire.h
 * @brief API for One Wire HAL layer.
 */

#ifndef _HAL_ONE_WIRE_H_
#define _HAL_ONE_WIRE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "hal_target.h"

/**
 * @brief Structure for storing One Wire device address.
 * @details Unique One Wire address used for device addressing.
 */
typedef struct {
    uint8_t address[8]; /*!< HAL One Wire address buffer. */
} hal_one_wire_rom_address_t;

/**
 * @brief One Wire HAL initialization configuration structure.
 *
 * @details
 * - data_pin value - to be configured as desired.
 * - state value    - NOTE must not be altered (it is supposed to be set automatically in Low Level Layer).
 */
typedef struct {
    hal_pin_name_t data_pin; /*!< One Wire pin - user is to configure it as desired. */
    bool state; /*!< State of a pin. NOTE must not be altered. */
} hal_one_wire_t;

/**
 * @details Enum containing predefined module return values.
 */
typedef enum {
    HAL_ONE_WIRE_SUCCESS = 0, /*!< Success. */
    HAL_ONE_WIRE_ERROR = (-1) /*!< Error. */
} hal_one_wire_err_t;

/*!
 * @addtogroup pergroup Microcontroller Peripherals
 * @{
 */

/*!
 * @addtogroup halgroup Hardware Abstraction Layer
 * @{
 */

/**
 * WARNING
 * @brief Important information in regards to CUSTOM One Wire timing.
 * @details One Wire library is currently utilizing recommended
 *          "Maxim Integrated" One Wire timing sequences.
 *          If, by any chance, end-user needs custom timing
 *          sequences, "weak" functions shall be overwritten by end-user functions.
 *          Declaration of those functions can be found at following location:
 *              "\mikrosdk-2.0\hal\lib\include\hal_one_wire.h"
 *
 *          Declarations:
 *              void one_wire_timing_value_a( void );
 *              void one_wire_timing_value_b( void );
 *              void one_wire_timing_value_c( void );
 *              void one_wire_timing_value_d( void );
 *              void one_wire_timing_value_e( void );
 *              void one_wire_timing_value_f( void );
 *              void one_wire_timing_value_h( void );
 *              void one_wire_timing_value_i( void );
 *              void one_wire_timing_value_j( void );
 *
 * @b Example
 * @code
 *
 *   // Configure custom timing "a" sequence value (delay).
 *   one_wire_timing_value_h() {
 *       asm nop;    // To give an example...
 *   }
 *
 *   int main() {
 *       // One Wire driver initialization configuration structure.
 *       static hal_one_wire_t hal_one_wire_object_1;
 *
 *       // Configure default One Wire properties.
 *       hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *       // Specify desired One Wire pin.
 *       hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *       // Allocate resources for One Wire protocol.
 *       if ( ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *           // Error handling strategy.
 *           return ONE_WIRE_ERROR; // To give an example...
 *       }
 *
 *       // Send reset sequence on One Wire bus.
 *       // This funtion will now utilize custom timing
 *       // defined at the top of this code.
 *       hal_one_wire_reset( &hal_one_wire );
 *
 *   }
 *
 * @endcode
 */

/*!
 * @addtogroup halonewiregroup One Wire HAL
 * @brief One Wire Hardware Abstraction Layer API Reference.
 * @details API for configuring and manipulating One Wire HAL module.
 * @{
 */

/**
 * @brief Opens One Wire HAL object.
 * @details Opens One Wire HAL object on selected pin.
 * Enables appropriate PORT clock, configures pin to have digital output functionality,
 * makes sure that HIGH voltage state is applied on pin before any One Wire actions.
 * @param[in,out] obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * err_t, which is dependant on the architecture and ported low level layer.
 * @pre Make sure that \p hal structure has been adequately
 * populated beforehand.
 * @note It is recommended to check return value for error.
 *
 * @b Example
 * @code
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 * @endcode
 */
err_t hal_one_wire_open( hal_one_wire_t *obj );

/**
 * @brief Configures One Wire HAL configuration structure.
 * @details Configures One Wire configuration structure to default initialization values.
 * Take into consideration that this is just
 * structure variable initial values setting.
 * User must redefine only one value - data_pin.
 * @param[in,out] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 *
 * @b Default @b values:
 * Function            | Default value                         |
 * --------------------|---------------------------------------|
 * Data pin            | 0xFFFFFFFF (invalid pin)              |
 * state               | Pin state, do not alter.              |
 * @return Nothing.
 * @pre The user is expected to call this function before #one_wire_open.
 *
 * @b Example
 * @code
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 * @endcode
 */
void hal_one_wire_configure_default( hal_one_wire_t *obj );

/**
 * @brief Resets One Wire bus.
 * @details Host shall send reset sequence and devices shall go into reset state.
 * @param[in,out] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_one_wire_open function.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Send reset sequence on One Wire bus.
 *   hal_one_wire_reset( &hal_one_wire );
 * @endcode
 */
err_t hal_one_wire_reset( hal_one_wire_t *obj );

/**
 * @brief Reads device's ROM information.
 * @details Allows the host to read eight-bit family code,
 * 48-bit serial number, and eight-bit CRC.
 *
 * @important THIS FUNCTION IS TO BE ISSUED ONLY IF WE ARE DEALING WITH
 * ONE DEVICE ONLY. THIS FUNCTION AUTOMATICALLY RESETS ONE WIRE BUS.
 * @param[in] *obj One Wire HAL object.
 * See #one_wire_t structure definition for detailed explanation.
 * @param[out] *device_rom_address Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Read "Family Code" (1 byte), serial number (6 bytes) and CRC (1 byte).
 *   hal_one_wire_read_rom( &hal_one_wire_object_1, &hal_one_wire_device_list );
 * @endcode
 */
err_t hal_one_wire_read_rom( hal_one_wire_t *obj, hal_one_wire_rom_address_t *device_rom_address );

/**
 * @brief Access device's level functions without transmitting ROM information.
 * @details Allows the host to access device functions without
 * providing the 64-bit ROM identification number.
 *
 * @important THIS FUNCTION IS TO BE ISSUED ONLY IF WE ARE DEALING WITH
 * ONE DEVICE ONLY. THIS FUNCTION AUTOMATICALLY RESETS ONE WIRE BUS.
 * @param[in] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Convert temperature command sequence for Thermo 19 Click.
 *   uint8_t cmd_convert_temperature = 0x44;
 *
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // One Wire ROM address variable.
 *   hal_one_wire_rom_address_t hal_one_wire_device_list;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Skip sending ROM information of a device
 *   // (this device is the only one on One Wire bus).
 *   hal_one_wire_skip_rom( &hal_one_wire_object_1 );
 *
 *   // Start temperature conversion of a device.
 *   hal_one_wire_write_byte( &hal_one_wire_object_1, &cmd_convert_temperature, 1 );
 * @endcode
 */
err_t hal_one_wire_skip_rom( hal_one_wire_t *obj );

/**
 * @brief Select a specific One Wire capable device on bus.
 * @details Select a One Wire device with specific ID.
 *
 * @param[in] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @param[in] device_rom_address Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #one_wire_open function.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // Convert temperature command sequence for Thermo 19 Click.
 *   uint8_t cmd_convert_temperature = 0x44;
 *
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // One Wire ROM address variable.
 *   hal_one_wire_rom_address_t hal_one_wire_device_list;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Try to match potential device on bus.
 *   hal_one_wire_match( &hal_one_wire, &hal_one_wire_device_list );
 *
 *   // Start temperature conversion of a device.
 *   hal_one_wire_write_byte( &hal_one_wire_object_1, &cmd_convert_temperature, 1 );
 * @endcode
 */
err_t hal_one_wire_match_rom( hal_one_wire_t *obj, hal_one_wire_rom_address_t *device_rom_address );

/**
 * @brief Search One Wire capable device on bus.
 * @details Search and list 1st device that is One Wire capable.
 *
 * @param[in] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @param[out] *one_wire_device_list Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #one_wire_open function.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // One Wire ROM address variable.
 *   hal_one_wire_rom_address_t hal_one_wire_device_1;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Find 1st device on One Wire bus.
 *   hal_one_wire_search_first_device( &hal_one_wire_object_1, &hal_one_wire_device_1 );
 * @endcode
 */
err_t hal_one_wire_search_first_device( hal_one_wire_t *obj, hal_one_wire_rom_address_t *one_wire_device_list );

/**
 * @brief Search One Wire capable devices on bus.
 * @details Search devices that is One Wire capable.
 *
 * @param[in] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @param[out] *one_wire_device_list Buffer for One Wire device ROM information.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #one_wire_open function.
 * @warning The following example describes how the function is used.
 * Take into consideration that different hardware might not have the same pins.
 * Make sure to accommodate pin name based on your hardware specifics.
 *
 * @b Example
 * @code
 *   // One Wire HAL initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // One Wire ROM address variable.
 *   hal_one_wire_rom_address_t hal_one_wire_device_1;
 *   hal_one_wire_rom_address_t hal_one_wire_device_2;
 *   hal_one_wire_rom_address_t hal_one_wire_device_3;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Find 1st device on One Wire bus.
 *   hal_one_wire_search_first_device( &hal_one_wire_object_1, &hal_one_wire_device_1 );
 *
 *   // Find 2nd device on One Wire bus.
 *   hal_one_wire_search_next_device( &hal_one_wire_object_1, &hal_one_wire_device_2 );
 *
 *   // Find 3rd device on One Wire bus.
 *   hal_one_wire_search_next_device( &hal_one_wire_object_1, &hal_one_wire_device_3 );

 * @endcode
 */
err_t hal_one_wire_search_next_device( hal_one_wire_t *obj, hal_one_wire_rom_address_t *one_wire_device_list );

/**
 * @brief Writes byte to One Wire bus.
 * @details Writes byte to One Wire bus.
 * @param[in] obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @param[in] *write_data_buffer Data transmit buffer.
 * @param[in] write_data_length Number of bytes to write from data transmit buffer.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_one_wire_open function.
 *
 * @b Example
 * @code
 *   // Command to write on bus.
 *   uint8_t cmd_write_command = 0x44;
 *
 *   // One Wire driver initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // One Wire ROM address variable.
 *   hal_one_wire_rom_address_t hal_one_wire_device_list;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Skip sending ROM information of a device
 *   // (this device is the only one on One Wire bus).
 *   hal_one_wire_skip_rom( &hal_one_wire_object_1 );
 *
 *   // Start temperature conversion of a device.
 *   hal_one_wire_write_byte( &hal_one_wire_object_1, &cmd_write_command, 1 );
 * @endcode
 */
err_t hal_one_wire_write_byte( hal_one_wire_t *obj, uint8_t *write_data_buffer, size_t write_data_length );

/**
 * @brief Reads byte from One Wire bus.
 * @details Reads byte from One Wire bus.
 * @param[in] *obj One Wire HAL object.
 * See #hal_one_wire_t structure definition for detailed explanation.
 * @param[out] *read_data_buffer Data receive buffer.
 * @param[in] read_data_length Number of bytes to be read.
 * @return The function can return one of the values defined by
 * #hal_one_wire_err_t, which is size dependant on the architecture.
 * @pre Before calling this function,
 * the user is expected to call #hal_one_wire_open function.
 *
 * @b Example
 * @code
 *   // Command to write on bus.
 *   uint8_t cmd_write_command = 0x44;
 *
 *   // Variable for storing temperature conversion status.
 *   uint8_t conversion_status = 0;
 *
 *   // One Wire driver initialization configuration structure.
 *   static hal_one_wire_t hal_one_wire_object_1;
 *
 *   // One Wire ROM address variable.
 *   hal_one_wire_rom_address_t hal_one_wire_device_list;
 *
 *   // Configure default One Wire properties.
 *   hal_one_wire_configure_default( &hal_one_wire_object_1 );
 *
 *   // Specify desired One Wire pin.
 *   hal_one_wire_object_1.data_pin = MIKROBUS_1_PWM;
 *
 *   // Allocate resources for One Wire protocol.
 *   if ( HAL_ONE_WIRE_SUCCESS != hal_one_wire_open( &hal_one_wire_object_1 ) ) {
 *       // Error handling strategy.
 *       return HAL_ONE_WIRE_ERROR; // To give an example...
 *   }
 *
 *   // Skip sending ROM information of a device
 *   // (this device is the only one on One Wire bus).
 *   hal_one_wire_skip_rom( &hal_one_wire_object_1 );
 *
 *   // Start temperature conversion of a device.
 *   hal_one_wire_write_byte( &hal-one_wire_object_1, &cmd_write_command, 1 );
 *
 *   // Check temperature conversion status.
 *   hal_one_wire_read_byte( &hal_one_wire_pin_1, &conversion_status, 1 );
 * @endcode
 */
err_t hal_one_wire_read_byte( hal_one_wire_t *obj, uint8_t *read_data_buffer, size_t read_data_length );

/**
 * @brief Configures device-specific timing "a" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_a( void );

/**
 * @brief Configures device-specific timing "b" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_b( void );

/**
 * @brief Configures device-specific timing "c" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_c( void );

/**
 * @brief Configures device-specific timing "d" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_d( void );

/**
 * @brief Configures device-specific timing "e" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_e( void );

/**
 * @brief Configures device-specific timing "f" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_f( void );

/**
 * @brief Configures device-specific timing "h" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_h( void );

/**
 * @brief Configures device-specific timing "i" sequence value.
 * @details Configures custom One Wire delay.

 * @return none
 */
void one_wire_timing_value_i( void );

/**
 * @brief Configures device-specific timing "j" sequence value.
 * @details Configures custom One Wire delay.
 * @return none
 */
void one_wire_timing_value_j( void );

/*! @} */ // halonewiregroup
/*! @} */ // halgroup
/*! @} */ // pergroup

#ifdef __cplusplus
}
#endif

#endif // _HAL_ONE_WIRE_H_
// ------------------------------------------------------------------------- END
