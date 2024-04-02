// ------------------------------------------------------------------ INCLUDES

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "can_test.h"
#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_can.h"
#include "drv_port.h"
#include "board.h"
#include "delays.h"
#ifdef __GNUC__
#include "mcu.h"
#endif

// -------------------------------------------------------------------- MACROS
#define TEST_PIN_CAN_RX HAL_PIN_NC // TODO define CAN RX pin
#define TEST_PIN_CAN_TX HAL_PIN_NC // TODO define CAN TX pin

// TODO Define test pins according to hardware.
#define TEST_PIN_1  HAL_PIN_NC
#define TEST_PIN_2  HAL_PIN_NC
#define TEST_PIN_3  HAL_PIN_NC
#define TEST_PIN_4  HAL_PIN_NC

#define BUTTON_STOP_TRANSMISSION HAL_PIN_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)
// ----------------------------------------------------------------- VARIABLES
static digital_in_t input_pin;    // Digital input driver context structure.
static digital_out_t test_pin;
static can_config_t can_config_struct;
static can_filter_config_t can_filter_config_struct;
static can_t can_struct;
uint8_t tx_data[3];
uint8_t data_byte;
can_transmit_message_struct tx_message;
// ----------------------------------------------------------------- USER CODE
int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    // Default config.
    can_configure_default( &can_config_struct );
    can_filter_configure_default( &can_filter_config_struct );

    // TODO Test different sets of pins.
    can_config_struct.rx_pin = TEST_PIN_CAN_RX;
    can_config_struct.tx_pin = TEST_PIN_CAN_TX;
    if( ACQUIRE_FAIL == can_open( &can_struct, &can_config_struct )) {
        signal_error( TEST_PIN_1 );
    }

    if( CAN_ERROR == can_init( &can_struct )) {
        signal_error( TEST_PIN_2 );
    }

    // TODO Test different baud rate values.
    can_set_frequency( &can_struct, CAN_TEST_FREQUENCY );

    // Button for stopping transmission initiation.
    digital_in_init( &input_pin, BUTTON_STOP_TRANSMISSION );

    tx_message.message.data_len = 3;
    tx_message.message.frame_format = CAN_FRAME_FORMAT_STANDARD_11BITS;
    tx_message.message.std_id = 0x123;
    tx_message.message.ext_id = 0x01;
    while(1) {
            tx_message.message.message_data[0] = 0xAA;
            tx_message.message.message_data[1] = data_byte++;
            tx_message.message.message_data[2] = 0xBB;

            /* Send the data */
            if( CAN_ERROR == can_transmit( &can_struct, &tx_message )) {
                signal_error( TEST_PIN_4 );
            }

            // By pressing the button transmission should stop for 3 seconds.
            if ( digital_in_read( &input_pin )) {
                can_transmission_stop( &can_struct );
                Delay_ms(3000);
            }

            Delay_10ms();
    }

    return 0;
}

// ----------------------------------------------------------------------- END
