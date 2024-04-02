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
void hal_ll_one_wire_open( hal_ll_one_wire_t *obj ) {
    // Local instance of One Wire pin.
    hal_ll_gpio_pin_t one_wire_pin;

    // Enable appropriate PORT clock, set pin to be digital input.
    hal_ll_gpio_configure_pin( &one_wire_pin, obj->data_pin, HAL_LL_GPIO_DIGITAL_INPUT );

    /* Register One Wire handle (memorize appropriate GPIO registers and bit positions). */
    hal_ll_one_wire_reconfigure( obj );
}

hal_ll_err_t hal_ll_one_wire_reset( hal_ll_one_wire_t *obj ) {
    /* Variable for checking whether there are device(s) on
     * One Wire data pin (0) or there aren't any devices at all (1). */
    uint8_t device_response = 1;

    // Make sure that pin has output capability.
    #if defined(__hal_ll_gpio_subset_1__)
    *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
    #elif defined(__hal_ll_gpio_subset_2__)
    if ( ( one_wire_handle.data_pin ) < 8 ) {
        *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
    } else {
        *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
    }
    #endif

    // Set pin to LOW voltage level.
    *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask(one_wire_handle.data_pin) << RESET_PINS_OFFSET;

    // Timing value for reset of One Wire bus - LOW voltage level.
    one_wire_timing_value_h();

    // Release pin ( pull-up resistor will do the rest (pull the data line up) ).
    #if defined(__hal_ll_gpio_subset_1__)
    *(uint32_t *)one_wire_handle.moder &= one_wire_handle.moder_clear;
    #elif defined(__hal_ll_gpio_subset_2__)
    if ( ( one_wire_handle.data_pin ) < 8 ) {
        *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
    } else {
        *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
    }
    #endif

    // Timing value for reset of One Wire bus - Master sample pulse.
    one_wire_timing_value_i();

    // Check whether there are devices on One Wire data pin.
    device_response = ( *(uint32_t *)one_wire_handle.idr & hal_ll_gpio_pin_mask(one_wire_handle.data_pin) ) ? 0x01 : 0x00;

    // Provide enough time for power injection into internal power logic of devices that are present.
    one_wire_timing_value_j();

    // Return final result of device response.
    return device_response;
}

hal_ll_err_t hal_ll_one_wire_read_rom( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *device_rom_address ) {
    // Initiate Reset sequence.
    if ( hal_ll_one_wire_reset( obj ) ) {
        return HAL_LL_ONE_WIRE_ERROR;
    }

    // Initiate "Read ROM" command.
    hal_ll_one_wire_write_byte( &hal_ll_one_wire_read_rom_command, 1 );

    // Read ROM address.
    hal_ll_one_wire_read_byte( &device_rom_address->address[0], 8 );

    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_skip_rom( hal_ll_one_wire_t *obj ) {
    // Initiate Reset sequence.
    if ( hal_ll_one_wire_reset( obj ) ) {
        return HAL_LL_ONE_WIRE_ERROR;
    }

    // Initiate "Skip ROM" command.
    hal_ll_one_wire_write_byte( &hal_ll_one_wire_skip_rom_command, 1 );

    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_match_rom( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *device_rom_address ) {
    // Initiate Reset sequence.
    if ( hal_ll_one_wire_reset( obj ) ) {
        return HAL_LL_ONE_WIRE_ERROR;
    }

    // Initiate "Match" command.
    hal_ll_one_wire_write_byte( &hal_ll_one_wire_match_rom_command, 1 );

    // Send ROM address.
    hal_ll_one_wire_write_byte( (uint32_t)device_rom_address, 8 );

    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_search_first_device( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list ) {
    // Reset the search state.
    last_discrepancy = 0;
    last_device_flag = 0;
    last_family_discrepancy = 0;

    // Initiate search algorithm, in order to get first device on One Wire grid.
    hal_ll_one_wire_search( obj, one_wire_device_list );

    return HAL_LL_ONE_WIRE_SUCCESS;
}

hal_ll_err_t hal_ll_one_wire_search_next_device( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list ) {
    // Initiate search algorithm, in order to get first device on One Wire grid.
    hal_ll_one_wire_search( obj, one_wire_device_list );

    return HAL_LL_ONE_WIRE_SUCCESS;
}

static hal_ll_err_t hal_ll_one_wire_search( hal_ll_one_wire_t *obj, hal_ll_one_wire_rom_address_t *one_wire_device_list ) {
    // Final search result variable.
    uint8_t search_result = 0;

    // Initialize variables for search method.
    uint8_t rom_byte_number = 0;
    uint8_t rom_byte_mask = 1;
    uint8_t id_bit_number = 1;
    uint8_t last_zero = 0;

    // The first bit read in a bit search sequence.
    // ( logical AND of all of the id_bit_number bits of the devices that are still participating in the search ).
    uint8_t id_bit = 0;

    // The complement of id_bit.
    // ( logical AND of the complement of all id_bit_number bits of the devices that are still participating in the search ).
    uint8_t cmp_id_bit = 0;

    // Search direction ( bit-per-bit search ).
    uint8_t search_direction = 0;

    // If the last call was not the last one...
    if ( !last_device_flag ) {

        // If there were no any device while executing One Wire reset sequence...
        if ( hal_ll_one_wire_reset( obj ) ) {

            // Reset all the important variables.
            last_device_flag = 0;
            last_discrepancy = 0;
            last_family_discrepancy = 0;

            // Stop searching because there are no any One Wire capable devices.
            return HAL_LL_ONE_WIRE_ERROR;
        }

        // If device(s) has(have) been found, initiate "Search" command.
        hal_ll_one_wire_write_byte( &hal_ll_one_wire_search_rom_command, 1 );

        // Iterate until all 64 bits (8 bytes) of unique ROM 'registration' numbers have not been found.
        do {
            // Read a bit.
            hal_ll_one_wire_read_bit( &id_bit );

            // Then, read its complement.
            hal_ll_one_wire_read_bit( &cmp_id_bit );

            // Check whether no devices participating in current search.
            if ( ( id_bit == 1 ) && ( cmp_id_bit == 1 ) ) {
                break;
            // Proceed, because we have found some device(s).
            } else {
                // We are going to check once again whether read bit and
                // its complement of all the devices on the One Wire grid are not the same.
                // If they are not the same, we are going to start our search with non-complement bit.
                if ( id_bit != cmp_id_bit ) {
                    search_direction = id_bit;  // Bit write value for search.

                // Otherwise, there are both binary zeros and ones in the current
                // bit position of the participating ROM numbers. This is a discrepancy.
                } else {
                    if ( id_bit_number < last_discrepancy ) {
                        search_direction = ( ( one_wire_device_list->address[ rom_byte_number ] & rom_byte_mask ) > 0 );
                    } else {
                        search_direction = ( id_bit_number == last_discrepancy );
                    }

                    // If 0 is picked, save its position.
                    if ( search_direction == 0) {
                        last_zero = id_bit_number;

                        // Check for last discrepancy in family.
                        if ( last_zero < 9 ) {
                            last_family_discrepancy = last_zero;
                        }
                    }
                }

                // Set or clear bit in the ROM byte rom_byte_number with mask rom_byte_mask.
                if ( search_direction == 1 ) {
                    one_wire_device_list->address[ rom_byte_number ] |= rom_byte_mask;
                } else {
                    one_wire_device_list->address[ rom_byte_number ] &= ~rom_byte_mask;
                }

                // Search number search direction write bit.
                hal_ll_one_wire_write_bit( search_direction );

                // Increment the byte counter "id_bit_number", and shift the mask "rom_byte_mask".
                id_bit_number++;
                rom_byte_mask <<= 1;

                // If the mask is zero, then go to new "serial_num" byte, "rom_byte_number" and "reset_mask".
                if ( rom_byte_mask == 0 ) {
                    rom_byte_number++;
                    rom_byte_mask = 1;
                }
            }
        } while ( rom_byte_number < HAL_LL_ONE_WIRE_MINIMUM_BITS_PER_TRANSFER );

        // If the search was successful then...
        if ( !( id_bit_number < 65 ) ) {

            last_discrepancy = last_zero;

            // Check for last device.
            if ( last_discrepancy == 0 ) {
                last_device_flag = 1;
            }
            search_result = 1;
        }
    }
    // If no device found then reset counters so next "search" will be like a first.
    if ( !search_result  || !one_wire_device_list->address[0] ) {
        last_discrepancy = 0;
        last_family_discrepancy = 0;
        last_device_flag = 0;
        search_result = 0;
    }

    // Return info whether we have found some device ID or not.
    return search_result;
}

void hal_ll_one_wire_write_byte( uint8_t *write_data_buffer, size_t write_data_length ) {
    size_t local_byte_checker = 0;
    uint8_t local_bit_checker = 0;
    uint8_t local_byte = 0;
    uint8_t bit_state = 0;

    // For every byte to be sent...
    while ( local_byte_checker != write_data_length ) {

        // ...restart bit checker...
        local_bit_checker = 0;

        // ...get current byte...
        local_byte = write_data_buffer[local_byte_checker++];

        // For every bit in byte to be sent...
        while ( local_bit_checker != HAL_LL_ONE_WIRE_MINIMUM_BITS_PER_TRANSFER ) {
            bit_state = ( local_byte >> local_bit_checker++ ) & 1;

            if( bit_state ) {
                // Set pin to be digital output.
                #if defined(__hal_ll_gpio_subset_1__)
                *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
                #elif defined(__hal_ll_gpio_subset_2__)
                if ( ( one_wire_handle.data_pin ) < 8 ) {
                    *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
                } else {
                    *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
                }
                #endif

                // Set pin to LOW voltage level.
                *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask( one_wire_handle.data_pin ) << RESET_PINS_OFFSET;

                // Timing value "a" for writing logical '1' - LOW voltage level.
                one_wire_timing_value_a();

                // Release One Wire data line ( pull-up resistor will pull the data line up ).
                #if defined(__hal_ll_gpio_subset_1__)
                *(uint32_t *)one_wire_handle.moder &= one_wire_handle.moder_clear;
                #elif defined(__hal_ll_gpio_subset_2__)
                if ( ( one_wire_handle.data_pin ) < 8 ) {
                    *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
                } else {
                    *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
                }
                #endif
                // Timing value "b" for writing logical '1' - LOW voltage level.
                one_wire_timing_value_b();
            } else {
                // Set pin to be digital output.
                #if defined(__hal_ll_gpio_subset_1__)
                *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
                #elif defined(__hal_ll_gpio_subset_2__)
                if ( ( one_wire_handle.data_pin ) < 8 ) {
                    *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
                } else {
                    *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
                }
                #endif

                // Set pin to LOW voltage level.
                *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask(one_wire_handle.data_pin) << RESET_PINS_OFFSET;

                // Timing value "c" for writing logical '0' - LOW voltage level.
                one_wire_timing_value_c();

                // Release One Wire data line ( pull-up resistor will pull the data line up ).
                #if defined(__hal_ll_gpio_subset_1__)
                *(uint32_t *)one_wire_handle.moder &= one_wire_handle.moder_clear;
                #elif defined(__hal_ll_gpio_subset_2__)
                if ( ( one_wire_handle.data_pin ) < 8 ) {
                    *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
                } else {
                    *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
                }
                #endif
                // Timing value "d" for writing logical '0' - HIGH voltage level.
                one_wire_timing_value_d();
            }
        }
    }
}

void hal_ll_one_wire_read_byte( uint8_t *read_data_buffer, size_t read_data_length ) {
    size_t local_byte_checker = 0;
    uint8_t local_bit_checker = 0;
    uint8_t local_buffer = 0;

    // For every byte to be read...
    while ( local_byte_checker != read_data_length ) {

        // ...restart bit checker and buffer...
        local_bit_checker = 0;
        local_buffer = 0;

        // For every bit in byte to be read...
        while ( local_bit_checker != HAL_LL_ONE_WIRE_MINIMUM_BITS_PER_TRANSFER ) {
            // Set pin to be digital output.
            #if defined(__hal_ll_gpio_subset_1__)
            *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
            #elif defined(__hal_ll_gpio_subset_2__)
            if ( ( one_wire_handle.data_pin ) < 8 ) {
                *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
            } else {
                *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
            }
            #endif
            // Set pin to LOW voltage level.
            *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask( one_wire_handle.data_pin ) << RESET_PINS_OFFSET;

            // Timing value "a" for bit reading - LOW voltage level.
            one_wire_timing_value_a();

            // Release One Wire data line ( pull-up resistor will pull the data line up ).
            #if defined(__hal_ll_gpio_subset_1__)
            *( uint32_t* )one_wire_handle.moder &= one_wire_handle.moder_clear;
            #elif defined(__hal_ll_gpio_subset_2__)
            if ( ( one_wire_handle.data_pin ) < 8 ) {
                *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
            } else {
                *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
            }
            #endif
            // Hold the data line for 6us more.
            one_wire_timing_value_e();

            // Read bit.
            local_buffer += ( ( *(uint32_t *)one_wire_handle.idr & hal_ll_gpio_pin_mask(one_wire_handle.data_pin) ) ? 0x01 : 0x00 ) << local_bit_checker++;

            // Timing value "f" for the rest of the read operation.
            one_wire_timing_value_f();
        }

        // Send back one logical level up a byte of data that has been just read.
        read_data_buffer[local_byte_checker++] = local_buffer;
    }
}

void hal_ll_one_wire_reconfigure( hal_ll_one_wire_t *obj ) {
    // Local instance of One Wire pin.
    hal_ll_gpio_pin_t one_wire_pin;

    // Get pin base address and mask.
    one_wire_pin.base = (hal_ll_gpio_base_t)hal_ll_gpio_port_base(hal_ll_gpio_port_index(obj->data_pin));
    one_wire_pin.mask = hal_ll_gpio_pin_mask(obj->data_pin);

    // Memorize info about pin number (for future use).
    one_wire_handle.data_pin = obj->data_pin % PORT_SIZE;

    // Get all the GPIO register addresses for appropriate One Wire pin.
    hal_ll_gpio_base_handle_t *gpio_ptr = (hal_ll_gpio_base_handle_t *)one_wire_pin.base;

    // Memorize appropriate pin Direction Register (MODER register).
    #if defined(__hal_ll_gpio_subset_1__)
    one_wire_handle.moder = (uint32_t)&gpio_ptr->moder;
    #elif defined(__hal_ll_gpio_subset_2__)
    one_wire_handle.crl = (uint32_t)&gpio_ptr->crl;
    one_wire_handle.crh = (uint32_t)&gpio_ptr->crh;
    #endif

    // Memorize appropriate pin Port Register (IDR register).
    one_wire_handle.idr = (uint32_t)&gpio_ptr->idr;

    // Memorize bit location of One Wire pin (Digital Output capability).
    #if defined(__hal_ll_gpio_subset_1__)
    one_wire_handle.moder_set = 0x1UL << ( one_wire_handle.data_pin * 2 );
    #elif defined(__hal_ll_gpio_subset_2__)
    if ( ( one_wire_handle.data_pin ) < 8 ) {
        one_wire_handle.crx_set = 0x3UL << ( one_wire_handle.data_pin * 4 );
    } else {
        one_wire_handle.crx_set = 0x3UL << ( ( ( one_wire_handle.data_pin ) % 8 ) * 4 );
    }
    #endif
    // Memorize bit location of One Wire pin (Input - reset state).
    #if defined(__hal_ll_gpio_subset_1__)
    one_wire_handle.moder_clear = ~ ( 0x3UL << ( one_wire_handle.data_pin * 2 ) );
    #elif defined(__hal_ll_gpio_subset_2__)
    if ( ( one_wire_handle.data_pin ) < 8 ) {
        one_wire_handle.crx_clear = ~ ( 0x3UL << ( one_wire_handle.data_pin * 4 ) );
    } else {
        one_wire_handle.crx_clear = ~ ( 0x3UL <<  ( ( ( one_wire_handle.data_pin ) % 8 ) * 4 ) );
    }
    #endif
    // Memorize appropriate bit Set/Reset Register (BSRR register).
    one_wire_handle.bsrr = (uint32_t)&gpio_ptr->bsrr;

    // Set object state to true.
    obj->state = true;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void hal_ll_one_wire_write_bit( uint8_t write_data_buffer ) {
    uint8_t bit_state = 0;
    size_t local_byte_checker = 0;
    uint8_t local_bit_checker = 7;
    bit_state = write_data_buffer & 0x1;

    if ( bit_state ) {
        // Set pin to be digital output.
        #if defined(__hal_ll_gpio_subset_1__)
        *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
        #elif defined(__hal_ll_gpio_subset_2__)
        if ( ( one_wire_handle.data_pin ) < 8 ) {
            *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
        } else {
            *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
        }
        #endif
        // Set pin to LOW voltage level.
        *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask( one_wire_handle.data_pin ) << RESET_PINS_OFFSET;

        // Timing value "a" for writing logical '1' - LOW voltage level.
        one_wire_timing_value_a();

        // Release One Wire data line ( pull-up resistor will pull the data line up ).
        #if defined(__hal_ll_gpio_subset_1__)
        *(uint32_t *)one_wire_handle.moder &= one_wire_handle.moder_clear;
        #elif defined(__hal_ll_gpio_subset_2__)
        if ( ( one_wire_handle.data_pin ) < 8 ) {
            *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
        } else {
            *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
        }
        #endif

        // Timing value "b" for writing logical '1' - LOW voltage level.
        one_wire_timing_value_b();
    } else {
        // Set pin to be digital output.
        #if defined(__hal_ll_gpio_subset_1__)
        *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
        #elif defined(__hal_ll_gpio_subset_2__)
        if ( ( one_wire_handle.data_pin ) < 8 ) {
            *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
        } else {
            *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
        }
        #endif

        // Set pin to LOW voltage level.
        *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask( one_wire_handle.data_pin ) << RESET_PINS_OFFSET;

        // Timing value "c" for writing logical '0' - LOW voltage level.
        one_wire_timing_value_c();

        // Release One Wire data line ( pull-up resistor will pull the data line up ).
        #if defined(__hal_ll_gpio_subset_1__)
        *(uint32_t *)one_wire_handle.moder &= one_wire_handle.moder_clear;
        #elif defined(__hal_ll_gpio_subset_2__)
        if ( ( one_wire_handle.data_pin ) < 8 ) {
            *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
        } else {
            *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
        }
        #endif

        // Timing value "d" for writing logical '0' - HIGH voltage level.
        one_wire_timing_value_d();
    }
}

static void hal_ll_one_wire_read_bit( uint8_t *read_data_buffer ) {
    uint8_t local_bit_checker = 0;

    // Set pin to be digital output.
    #if defined(__hal_ll_gpio_subset_1__)
    *(uint32_t *)one_wire_handle.moder |= one_wire_handle.moder_set;
    #elif defined(__hal_ll_gpio_subset_2__)
    if ( ( one_wire_handle.data_pin ) < 8 ) {
        *(uint32_t *)one_wire_handle.crl |= one_wire_handle.crx_set;
    } else {
        *(uint32_t *)one_wire_handle.crh |= one_wire_handle.crx_set;
    }
    #endif
    // Set pin to LOW voltage level.
    *(uint32_t *)one_wire_handle.bsrr = hal_ll_gpio_pin_mask( one_wire_handle.data_pin ) << RESET_PINS_OFFSET;

    // Timing value "a" for bit reading - LOW voltage level.
    one_wire_timing_value_a();

    // Release One Wire data line ( pull-up resistor will pull the data line up ).
    #if defined(__hal_ll_gpio_subset_1__)
    *(uint32_t *)one_wire_handle.moder &= one_wire_handle.moder_clear;
    #elif defined(__hal_ll_gpio_subset_2__)
    if ( ( one_wire_handle.data_pin ) < 8 ) {
        *(uint32_t *)one_wire_handle.crl &= one_wire_handle.crx_clear;
    } else {
        *(uint32_t *)one_wire_handle.crh &= one_wire_handle.crx_clear;
    }
    #endif
    // Timing value "e" for sampling read information.
    one_wire_timing_value_e();

    // Read bit.
    *read_data_buffer =  ( ( *(uint32_t *)one_wire_handle.idr & hal_ll_gpio_pin_mask( one_wire_handle.data_pin ) ) ? 0x01 : 0x00 );

    // Timing value "f" for the rest of the read operation.
    one_wire_timing_value_f();
}

// ------------------------------------------------------------------------- END
