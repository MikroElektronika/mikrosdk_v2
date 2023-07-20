/**
 * @brief: Test procedure for mikroSDK One Wire implementation.
 *
 *
 * @todo:
 *      - Insert Thermo 2 Click into mikroBUS1 slot.
 *      - Insert Tester click into mikroBUS5 slot.
 *
 * @note:
 *      - If Thermo 2 Click had been found, TEST_PIN_SIGNAL_SUCCESS pin on TESTER click turns ON.
 *      - Use UART terminal to check current temperature.
 */

// ------------------------------------------------------------------ INCLUDES
#include "thermo_2.h"
#include "board.h"

// -------------------------------------------------------------------- MACROS
#define TEST_PIN_ONE_WIRE HAL_PIN_NC        // TODO Define One Wire pin, for example: MIKROBUS_1_PWM
#define TEST_PIN_SIGNAL_SUCCESS HAL_PIN_NC  // TODO Define signal pin, for example: MIKROBUS_5_AN
#define TEST_PIN_SIGNAL_FAIL HAL_PIN_NC     // TODO Define signal pin, for example: MIKROBUS_5_PWM

#define signal_status(port,pin,state) digital_out_init( &port, pin ); \
                                      digital_out_write( &port, state )

#define signal_success(port,pin)    signal_status(port,pin,1)
#define signal_fail(port,pin)       signal_status(port,pin,1)

// ----------------------------------------------------------------- VARIABLES
// One Wire specifics.
one_wire_t thermo_2_click;
one_wire_rom_address_t thermo_2_rom_address;
one_wire_rom_address_t thermo_2_rom_address_double_check;
uint8_t cmd_convert_temperature = THERMO_2_CMD_CONVERT_TEMPERATURE;
uint8_t cmd_read_scratchpad = THERMO_2_CMD_READ_SCRATCHPAD;
uint8_t conversion_status = 0;
uint16_t raw_temperature = 0;
volatile float final_temperature = 0.0;

// GPIO specifics.
digital_out_t thermo_2_click_device_found_pin;

// UART specifics.
static uart_t uart_object;
static uart_config_t uart_config;
static uint8_t uart_rx_buffer[128];
static uint8_t uart_tx_buffer[128];
static uint8_t buffer[32];
char *temperature[4] = {"\0"};

// ----------------------------------------------------------------- USER CODE
int8_t application_init() {

    // ----------------------------------------
    // ONE WIRE CONFIGURATION.
    // ----------------------------------------
    // Configure default One Wire properties.
    one_wire_configure_default( &thermo_2_click );

    // Choose One Wire data pin.
    thermo_2_click.data_pin = TEST_PIN_ONE_WIRE;

    // Enable clock for appropriate PORT, configure this pin as digital output.
    if ( ONE_WIRE_SUCCESS != one_wire_open( &thermo_2_click ) ) {
        return ONE_WIRE_ERROR;
    };

    // ----------------------------------------
    // UART CONFIGURATION.
    // ----------------------------------------
    // Default config.
    uart_configure_default( &uart_config );

    // Ring buffer mapping.
    uart_object.tx_ring_buffer = uart_tx_buffer;
    uart_object.rx_ring_buffer = uart_rx_buffer;

    // Pin config.
    uart_config.tx_pin = USB_UART_TX;  // UART TX pin.
    uart_config.rx_pin = USB_UART_RX;  // UART RX pin.
    uart_config.tx_ring_size = sizeof( uart_tx_buffer );
    uart_config.rx_ring_size = sizeof( uart_rx_buffer );

    // Open UART object.
    if( ACQUIRE_FAIL == uart_open( &uart_object, &uart_config ) ) {
        signal_fail( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_FAIL );
    }
    // Set baud rate.
    if ( UART_SUCCESS != uart_set_baud( &uart_object, 9600 ) ) {
        signal_fail( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_FAIL );
    }

    // Set data parity. ( no parity )
    if ( UART_SUCCESS != uart_set_parity( &uart_object, UART_PARITY_DEFAULT ) ) {
        signal_fail( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_FAIL );
    };

    // Set stop bits. ( one stop bit )
    if ( UART_SUCCESS != uart_set_stop_bits( &uart_object, UART_STOP_BITS_DEFAULT ) ) {
        signal_fail( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_FAIL );
    }

    // Set data bits. ( 8-bit data )
    if ( UART_SUCCESS != uart_set_data_bits( &uart_object, UART_DATA_BITS_DEFAULT ) ) {
        signal_fail( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_FAIL );
    }

    // Give it some time to stabilize.
    Delay_100ms();

    return ONE_WIRE_SUCCESS;
}

int8_t application_task() {

    // ----------------------------------------
    // ONE WIRE CONFIGURATION.
    // ----------------------------------------
    // Check whether Thermo 2 Click is visible.
    // NOTE:Family code of this chip must be: 0x3B.
    if ( ONE_WIRE_SUCCESS != one_wire_read_rom( &thermo_2_click, &thermo_2_rom_address ) ) {
        return ONE_WIRE_ERROR;
    };

    // Check whether Thermo 2 Click is visible - double check.
    // NOTE:Family code of this chip must be: 0x3B.
    if ( ONE_WIRE_SUCCESS != one_wire_search_first_device( &thermo_2_click, &thermo_2_rom_address_double_check ) ) {
        return ONE_WIRE_ERROR;
    };

    // If Thermo 2 Click is visible, turn on test LED, and move on with code execution.
    if ( !memcmp( &thermo_2_rom_address, &thermo_2_rom_address_double_check, sizeof( one_wire_rom_address_t ) ) ) {
        signal_success( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_SUCCESS );
    }

    while ( 1 ) {
        // One Wire Reset sequence and "Skip ROM" command.
        one_wire_skip_rom( &thermo_2_click );

        // "Convert Temperature" command.
        one_wire_write_byte( &thermo_2_click, &cmd_convert_temperature, 1 );

        // Wait for 12-bit temperature conversion to be done.
        Delay_ms(750);

        // One Wire Reset sequence and "Skip ROM" command.
        one_wire_skip_rom( &thermo_2_click );

        // Initiate "Read Scratchpad" command.
        one_wire_write_byte( &thermo_2_click, &cmd_read_scratchpad, 1 );

        // Reading raw temperature.
        one_wire_read_byte( &thermo_2_click, &raw_temperature, 2 );

        // Get final temperature.
        final_temperature = thermo_2_convert_temperature(raw_temperature, THERMO_2_DEFAULT_RESOLUTION);

        // Convert float to string.
        float_to_str( final_temperature, temperature );

        // Write out data with new line.
        if ( UART_ERROR == uart_println( &uart_object, temperature ) ) {
            signal_fail( thermo_2_click_device_found_pin, TEST_PIN_SIGNAL_FAIL );
        }

        // Delay needed because of `uart_clear` function, so all data is transmitted.
        Delay_100ms();
    }
    return ONE_WIRE_SUCCESS;
}

int main( void ) {
    // Initialize necessary One Wire protocol properties.
    if ( ONE_WIRE_SUCCESS != application_init() ) {
        return ONE_WIRE_ERROR;
    };

    // Execute according to desired test that had been previously selected.
    if ( ONE_WIRE_SUCCESS != application_task() ) {
        return ONE_WIRE_ERROR;
    };

    return ONE_WIRE_SUCCESS;
}
