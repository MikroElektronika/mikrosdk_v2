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
 * @file  hal_ll_one_wire.c
 * @brief One Wire HAL LOW LEVEL layer implementation.
 */
#include "hal_ll_one_wire.h"
#include "delays.h"

// ------------------------------------------------------------- PRIVATE MACROS
/*!< @brief Helper macro getting minimum bits per transfer. */
#define HAL_LL_ONE_WIRE_MINIMUM_BITS_PER_TRANSFER   (8)

/*!< @brief Helper macro for reset pins offset. */
#define RESET_PINS_OFFSET                           (16)

// ------------------------------------------------------------------ VARIABLES
/*!< @brief Helper macro for starting to enumerate device ID(s). */
static uint8_t hal_ll_one_wire_search_rom_command = ONE_WIRE_CMD_ROM_SEARCH;

/*!< @brief Helper macro for reading a device ID. */
static uint8_t hal_ll_one_wire_read_rom_command_legacy = ONE_WIRE_CMD_ROM_READ_LEGACY;
static uint8_t hal_ll_one_wire_read_rom_command = ONE_WIRE_CMD_ROM_READ;

/*!< @brief Helper macro for ignoring a device ID. */
static uint8_t hal_ll_one_wire_skip_rom_command = ONE_WIRE_CMD_ROM_SKIP;

/*!< @brief Helper macro for selecting a device with specific ID. */
static uint8_t hal_ll_one_wire_match_rom_command = ONE_WIRE_CMD_ROM_MATCH;

/*!< @brief Helper flag if One Wire device is the last one left on the bus. */
static uint8_t last_device_flag = 0;

/*!< @brief Helper flag for last discrepancy. */
static uint8_t last_discrepancy = 0;

/*!< @brief Helper flag for last family discrepancy. */
static uint8_t last_family_discrepancy = 0;

/*!< @brief Helper instance consisting of hardware specifics. */
static hal_ll_one_wire_local_t one_wire_handle;

__weak void one_wire_timing_value_a( void ) {
    Delay_5us();
}

__weak void one_wire_timing_value_b( void ) {
    Delay_64us();
}

__weak void one_wire_timing_value_c( void ) {
    Delay_60us();
}

__weak void one_wire_timing_value_d( void ) {
    Delay_6us();
}

__weak void one_wire_timing_value_e( void ) {
    Delay_6us();
}

__weak void one_wire_timing_value_f( void ) {
    Delay_50us();
}

__weak void one_wire_timing_value_h( void ) {
    Delay_480us();
}

__weak void one_wire_timing_value_i( void ) {
    Delay_70us();
}

__weak void one_wire_timing_value_j( void ) {
    Delay_410us();
}

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Writes bit to One Wire bus.
 * @details Writes bit to One Wire bus.
 * @param[in] write_data_buffer Data transmit buffer.
 */
static void hal_ll_one_wire_write_bit( uint8_t write_data_buffer );

/**
 * @brief Reads bit from One Wire bus.
 * @details Reads bit from One Wire bus.
 * @param[in] write_data_buffer Data receive buffer.
 */
static void hal_ll_one_wire_read_bit( uint8_t *read_data_buffer );

/**
 * @brief Search One Wire capable device on bus.
 * @details Search One Wire capable device on bus.
 *
 * @param[in] *obj One Wire HAL Low Level object.
 * See #hal_ll_one_wire_t structure definition for detailed explanation.
 * @param[out] *one_wire_device_list Buffer for One Wire device ROM information.
 */
static hal_ll_err_t hal_ll_one_wire_search( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
void hal_ll_one_wire_open( hal_ll_one_wire_t *obj )
{

}

hal_ll_err_t hal_ll_one_wire_reset( hal_ll_one_wire_t *obj )
{

}

hal_ll_err_t hal_ll_one_wire_read_rom( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *device_rom_address )
{
    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_skip_rom( hal_ll_one_wire_t *obj )
{
    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_match_rom( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *device_rom_address )
{
    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_search_first_device( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list )
{
    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_search_next_device( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list )
{
    return HAL_LL_ONE_WIRE_SUCCESS;
}

static hal_ll_err_t hal_ll_one_wire_search( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list )
{

}

void hal_ll_one_wire_write_byte( uint8_t *write_data_buffer, size_t write_data_length )
{

}

void hal_ll_one_wire_read_byte( uint8_t *read_data_buffer, size_t read_data_length )
{

}

void hal_ll_one_wire_reconfigure( hal_ll_one_wire_t *obj )
{

}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_one_wire_write_bit( uint8_t write_data_buffer )
{

}

static void hal_ll_one_wire_read_bit( uint8_t *read_data_buffer )
{

}

// ------------------------------------------------------------------------- END
