// ------------------------------------------------------------------ INCLUDES

#include "drv_digital_out.h"
#include "drv_port.h"
#include "drv_analog_in.h"
#include "board.h"
#include "drv_uart.h"
#include "conversions.h"

// -------------------------------------------------------------------- MACROS

// TODO define pin if MIKROBUS_1_AN doesn't exist
#define TEST_PIN_ADC_AN HAL_PIN_NC

// TODO Define port used for testing.
#define PORT_NAME HAL_PORT_NC // Example: PORT_B

// TODO Define result output
#define ANALOG_IN_PORT_TEST 1 // Display result on defined port ( LED's )
#define ANALOG_IN_UART_TEST 0 // Display result via UART defined pins

#if ANALOG_IN_UART_TEST
#define TEST_PIN_UART_TX HAL_PIN_NC // TODO define pin if displaying result via UART
#define TEST_PIN_UART_RX HAL_PIN_NC // TODO define pin if displaying result via UART

static uart_t uart;  // UART driver context structure.
static uart_config_t uart_cfg;  // UART driver context structure.

static uint8_t uart_rx_buffer[256];
static uint8_t uart_tx_buffer[256];
#else

#endif

// TODO Define values used in test
#define TEST_VREF_VALUE 3.3f
#define TEST_RESOLUTION_VALUE ANALOG_IN_RESOLUTION_12_BIT

// TODO Define test pins according to hardware
// Feel free to add additional ones if required
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_MASK   0xFF

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)

#define signal_end(pin)   signal_error(pin)
// ----------------------------------------------------------------- VARIABLES
static analog_in_t analog_in;  // Analog input driver context structure.ucture.
static analog_in_config_t  analog_in_cfg;  // ADC init configuration structure.
static port_t port;  // Port driver context structure.
static digital_out_t test_pin;
float read_voltage_value;
uint16_t analog_in_read_value;

static uint8_t analog_in_read_buffer[32];
// ----------------------------------------------------------------- USER CODE
int main( void ) {

    #if ANALOG_IN_PORT_TEST
    port_init( &port, PORT_NAME, 0xFFFF, GPIO_DIGITAL_OUTPUT );
    #elif ANALOG_IN_UART_TEST
    uart_configure_default(&uart_cfg);
    uart.tx_ring_buffer = uart_tx_buffer;
    uart.rx_ring_buffer = uart_rx_buffer;

    uart_cfg.rx_pin = TEST_PIN_UART_RX;  // UART RX pin.
    uart_cfg.tx_pin = TEST_PIN_UART_TX;  // UART TX pin.

    uart_cfg.tx_ring_size = sizeof(uart_tx_buffer);
    uart_cfg.rx_ring_size = sizeof(uart_rx_buffer);

    uart_open( &uart, &uart_cfg );
    uart_set_baud( &uart, 115200 );  // Set baud rate.
    uart_println( &uart, "Hello!!!" );  // Write out data.
    #endif

    // Default config
    analog_in_configure_default( &analog_in_cfg );

    // TODO Test different set of pins.
    // Make sure to test higher nibble pins, ie. pins
    // higher then 7. For example, for porta, pins
    // PA8, PA9, PA10 etc.
    analog_in_cfg.input_pin = TEST_PIN_ADC_AN;  // Set AN pin.

    // TODO Test different resolutions.
    // Make sure to test `ALL` possible resolutions for
    // implemantation using potentiometer.
    // If using PORT Test, test by debugging and check
    // read value in debug watch window whilst checking PORT state.
    // Make sure to also check min and max values.
    // If using UART Test, test by reading values using UART terminal.
    analog_in_cfg.resolution = TEST_RESOLUTION_VALUE;  // Set ADC resolution.

    // TODO Test different vref input.
    // Make sure to test `ALL` possible VREFs for implemantation.
    // External test description:
    //     In CODEGRIP Suite set Vref to X value,
    //     using Multimeter check for potentiometer output value.
    //     In debug check if max value is read for
    //     current resolution.

    // Internal test description:
    //     Internal vref is on aVDD and aVSS(3.3v)
    //     check with potentiometer, for 3.3v, if read
    //     value is max for set resolution.
    analog_in_cfg.vref_input = ANALOG_IN_VREF_EXTERNAL;

    // TODO Test different vref values.
    // Test description for read_voltage:
    //     Set ext vref in CODEGRIP Suite, max v for potentiometer,
    //     check the output of the potentiometer with a multimeter
    //     and check the output for read_voltage through debug.
    //     Expect similar values.
    analog_in_cfg.vref_value = TEST_VREF_VALUE;

    if( ACQUIRE_FAIL == analog_in_open( &analog_in, &analog_in_cfg ) ) {
        signal_error( TEST_PIN_1 );
    }

    // Set ADC resolution.
    // TODO Test different resolutions.
    // Make sure to test `ALL` possible resolutions for
    // implemantation using potentiometer.
    // If using PORT Test, test by debugging and check read
    // value in debug watch window whilst checking PORT state.
    // Make sure to also check min and max values.
    // If using UART Test, test by reading values on UART terminal.
    if ( ADC_ERROR == analog_in_set_resolution( &analog_in, TEST_RESOLUTION_VALUE ) ) {
        signal_error( TEST_PIN_2 );
    }

    // TODO Test different vref input.
    // Make sure to test `ALL` possible VREFs for implemantation.
    // External test description:
    //     In CODEGRIP Suite set Vref to X value,
    //     using Multimeter check for potentiometer output value.
    //     In debug check if max value is read for
    //     current resolution.

    // Internal test description:
    //     Internal vref is on aVDD and aVSS(3.3v)
    //     check with potentiometer, for 3.3v, if read value is max for set resolution.
    if ( ADC_ERROR == analog_in_set_vref_input( &analog_in, ANALOG_IN_VREF_EXTERNAL) ) {
        signal_error( TEST_PIN_3 );
    }

    // TODO Test different vref values.
    // Test description for read_voltage:
    //     Set the ext vref in the CodeGrip, max v for potentiometer,
    //     check the output of the potentiometer with a multimeter and
    //     check the output for read_voltage in the debug.
    //     Expect similar values.
    if ( ADC_ERROR == analog_in_set_vref_value( &analog_in, TEST_VREF_VALUE ) ) {
        signal_error( TEST_PIN_3 );
    }

    #if ANALOG_IN_PORT_TEST
    while (1) {
        // TODO Read ADC value.
        // Test by debugging and reading value of analog_in_port_read_value.
        // Also check PORT status.
        if ( ADC_ERROR == analog_in_read( &analog_in, &analog_in_read_value ) ) {
            signal_error( TEST_PIN_4 );
        }

        // TODO Read voltage.
        // Test by debugging and reading value of read_voltage_value.
        if ( ADC_ERROR == analog_in_read_voltage( &analog_in, &read_voltage_value ) ) {
            signal_error( TEST_PIN_5 );
        }

        port_write( &port, analog_in_read_value );

        Delay_10ms();
    }
    #elif ANALOG_IN_UART_TEST
    while(1) {
        // TODO Read ADC value.
        // Test by reading value of analog_in_port_read_value and check
        // that value in UART terminal.
        if ( ADC_ERROR == analog_in_read( &analog_in, &analog_in_read_value ) ) {
            signal_error( TEST_PIN_4 );
        }

        // Convert read value to String.
        uint16_to_str(analog_in_read_value, &analog_in_read_buffer);

        // Print analog_in value to UART terminal.
        uart_println( &uart, analog_in_read_buffer );

        // TODO Read voltage.
        // Test by debugging and reading value of read_voltage_value.
        if ( ADC_ERROR == analog_in_read_voltage( &analog_in, &read_voltage_value ) ) {
            signal_error( TEST_PIN_5 );
        }

        Delay_100ms();
    }
    #endif

    // Close ADC module.
    // TODO Test by debugging and stepping into.
    // Make sure to confirm that everything is
    // disabled/dealocated etc.
    // Make sure that the values of both macros,
    // ANALOG_IN_PORT_TEST and ANALOG_IN_UART_TEST, are set to 0.
    analog_in_close( &analog_in );
    signal_end( TEST_PIN_6 );

    return 0;
}

// ----------------------------------------------------------------------- END
