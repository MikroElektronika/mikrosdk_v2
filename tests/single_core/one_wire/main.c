/**
 * @brief: Test procedure for mikroSDK One Wire implementation.
 *
 * @note:
 *      Choose between three types of testing:
 *      - SINGLE UNIQUE ID CLICK test,
 *      - SINGLE THERMO 19 CLICK test,
 *      - TRIPLE CLICK test:
 *        - two UNIQUE ID Clicks and one THERMO 19 Click.
 *
 * @todo:
 *      - Define desired one wire pin
 *      - Define desired signal pin
 *
 * @note:
 *      - Test is a success if TEST_PIN_SIGNAL_SUCCESS pin is logical high at the end.
 *      - Test requires one of or all of the following click boards:
 *          - Unique ID click
 *          - Thermo 19 click
 */
/// @note: Uncomment/comment out, to run desired test.
#define SINGLE_UNIQUE_ID_CLICK_TEST
// #define SINGLE_THERMO_19_CLICK_TEST
// #define TRIPLE_CLICK_TEST

// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "board.h"
#include "drv_one_wire.h"
#include "drv_digital_out.h"
#include "delays.h"

// -------------------------------------------------------------------- MACROS
#define TEST_PIN_ONE_WIRE HAL_PIN_NC // TODO Define OW pin, for example: MIKROBUS_1_PWM.
#define TEST_PIN_SIGNAL_SUCCESS HAL_PIN_NC // TODO Define signal pin, for example: MIKROBUS_5_AN.

#define signal_success(port,pin)    digital_out_init( &port, pin ); \
                                    digital_out_write( &port, 1 )

#if defined SINGLE_THERMO_19_CLICK_TEST
    #define CMD_CONVERT_TEMPERATURE     0x44
    #define CMD_READ_SCRATCHPAD         0xBE
    #define CMD_WRITE_SCRATCHPAD        0x4E
    #define CMD_DETECT_ADDRESS          0x88
    #define CMD_SELECT_ADDRESS          0x70
#endif
// ----------------------------------------------------------------- VARIABLES
static digital_out_t result_pin;

one_wire_t one_wire_pin_1;
one_wire_rom_address_t one_wire_device_list;
one_wire_rom_address_t one_wire_device_list2;
one_wire_rom_address_t one_wire_device_list3;
one_wire_rom_address_t thermo_19_click_1_rom_address = { 0x3B, 0x79, 0x0A, 0x75, 0x00, 0x00, 0x00, 0x38 };
one_wire_rom_address_t thermo_19_click_2_rom_address = { 0x3B, 0xC1, 0x15, 0x75, 0x00, 0x00, 0x00, 0x8D };
one_wire_rom_address_t unique_id_click_1_rom_address = { 0x01, 0x90, 0x53, 0x55, 0x17, 0x00, 0x00, 0x3E };
one_wire_rom_address_t unique_id_click_2_rom_address = { 0x01, 0x8B, 0x53, 0x55, 0x17, 0x00, 0x00, 0x9D };
uint8_t cmd_convert_temperature = 0x44;
uint8_t cmd_read_scratchpad = 0xBE;
uint8_t conversion_status = 0;
uint16_t raw_temperature = 0;

// ----------------------------------------------------------------- USER CODE
err_t application_init() {
    // Configure default One Wire properties.
    one_wire_configure_default( &one_wire_pin_1 );

    // Choose One Wire data pin.
    one_wire_pin_1.data_pin = TEST_PIN_ONE_WIRE;

    // Enable clock for appropriate PORT, configure this pin as digital output.
    if ( ONE_WIRE_SUCCESS != one_wire_open( &one_wire_pin_1 ) ) {
        return ONE_WIRE_ERROR;
    };

    return ONE_WIRE_SUCCESS;
}

err_t application_task() {
    #if defined SINGLE_UNIQUE_ID_CLICK_TEST
    // Read "Family Code" (1 byte), serial number (6 bytes) and CRC (1 byte).
    // NOTE: Family code must be 0x01.
    one_wire_read_rom( &one_wire_pin_1, &one_wire_device_list );

    // Check if Unique ID Click device has been found.
    if ( ( !memcmp( &one_wire_device_list, &unique_id_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
         ( !memcmp( &one_wire_device_list, &unique_id_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ) {
        signal_success( result_pin, TEST_PIN_SIGNAL_SUCCESS );
    }
    #endif
    #if defined SINGLE_THERMO_19_CLICK_TEST
    // Read "Family Code" (1 byte), serial number (6 bytes) and CRC (1 byte).
    // NOTE: Family code must be 0x3B. Check "one_wire_device_list" variable.
    if ( ONE_WIRE_SUCCESS != one_wire_read_rom( &one_wire_pin_1, &one_wire_device_list ) ) {
        return ONE_WIRE_ERROR;
    };

    // Sequence for reading temperature raw value.
    while (1) {
        // 1st cycle.
            // Initiate "Reset" sequence.
            // one_wire_reset( &one_wire_pin_1 );

            // NOTE: Now is the perfect time to test "Skip ROM" and "Match ROM" One Wire commands.
            one_wire_skip_rom( &one_wire_pin_1 );
            // one_wire_match_rom( &one_wire_pin_1, thermo_19_click_1_rom_address );

            // Start temperature conversion.
            one_wire_write_byte( &one_wire_pin_1, &cmd_convert_temperature, 1 );

            // Check temperature conversion status.
            one_wire_read_byte( &one_wire_pin_1, &conversion_status, 1 );

            // Device stabilization time.
            Delay_ms( 750 );

        // 2nd cycle.
            // Initiate "Reset" sequence.
            // one_wire_reset( &one_wire_pin_1 );

            // Initiate "ROM" command.
            one_wire_skip_rom( &one_wire_pin_1 );

            // Initiate "Read Scratchpad" command.
            one_wire_write_byte( &one_wire_pin_1, &cmd_read_scratchpad, 1 );

            // Read raw temperature.
            one_wire_read_byte( &one_wire_pin_1, &raw_temperature, 2 );

        // Check whether eighth bit is set (indicator that current ambient temperature is AT LEAST 16 degrees of Celsius).
        if ( raw_temperature & 0x0100 ) {
            signal_success( result_pin, TEST_PIN_SIGNAL_SUCCESS );
        }

        // Give it a little time in order for conversion action to become stable.
        Delay_1sec();

        // Turn off pin which indicates whether test is a success or failure.
        digital_out_write( &result_pin, 0 );
        Delay_1sec();
    }
    #endif
    #if defined TRIPLE_CLICK_TEST
    // Find 1st device on One Wire grid.
    one_wire_search_first_device( &one_wire_pin_1, &one_wire_device_list );

    // Find 2nd device on One Wire grid.
    one_wire_search_next_device( &one_wire_pin_1, &one_wire_device_list2 );

    // Find 3rd device on One Wire grid.
    one_wire_search_next_device( &one_wire_pin_1, &one_wire_device_list3 );

    // Check if all three devices have been found.
    if ( ( ( !memcmp( &one_wire_device_list, &thermo_19_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list, &unique_id_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list, &unique_id_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list, &thermo_19_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ) &&
        ( ( !memcmp( &one_wire_device_list2, &thermo_19_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list2, &unique_id_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list2, &unique_id_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list2, &thermo_19_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ) &&
        ( ( !memcmp( &one_wire_device_list3, &thermo_19_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list3, &unique_id_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list3, &unique_id_click_2_rom_address, sizeof( one_wire_rom_address_t ) ) ) ||
        ( !memcmp( &one_wire_device_list3, &thermo_19_click_1_rom_address, sizeof( one_wire_rom_address_t ) ) ) ) ) {
        signal_success( result_pin, TEST_PIN_SIGNAL_SUCCESS );
    }
    #endif

    return ONE_WIRE_SUCCESS;
}

int main( void ) {
    err_t result = ONE_WIRE_SUCCESS;
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Initialize necessary One Wire protocol properties.
    if ( ONE_WIRE_SUCCESS != application_init() ) {
        return ONE_WIRE_ERROR;
    };

    // Execute according to desired test that had been previously selected.
    result = application_task();

    return (int)result;
}
