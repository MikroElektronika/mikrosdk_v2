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
#define TEST_PIN_1        HAL_PIN_NC
#define TEST_PIN_2        HAL_PIN_NC
#define TEST_PIN_3        HAL_PIN_NC
#define TEST_PIN_4        HAL_PIN_NC
#define TEST_PIN_5        HAL_PIN_NC
#define TEST_PIN_6        HAL_PIN_NC
#define TEST_PIN_7        HAL_PIN_NC
#define TEST_PIN_8        HAL_PIN_NC
#define TEST_PIN_SUCCESS  HAL_PIN_NC

// TODO Test different byte values with different filter configurations.
#define BYTE1 0x01
#define BYTE2 0x32
#define BYTE3 0xAB
#define BYTE4 0xCD
#define BYTE5 0x45
#define BYTE6 0x89
#define BYTE7 0xEF
#define BYTE8 0x67

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)
#define signal_success    digital_out_high( &test_pin_success ); \
                          Delay_1sec(); \
                          digital_out_low( &test_pin_success ); \
                          Delay_1sec();


// ----------------------------------------------------------------- VARIABLES

static can_config_t can_config_struct;
static can_filter_config_t can_filter_config_struct;
static can_t can_struct;
static uint8_t byte_check[8];
can_transmit_message_struct tx_message;
can_receive_message_struct rx_message;
static digital_out_t test_pin, test_pin_success;

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

    // TODO Test different CAN filer parameters.
    can_filter_config_struct.can_filter_scale = CAN_FILTER_SCALE_32BIT;
    // NOTE: If you don't have any filters enabled for FIFO, message won't be received.
    can_filter_config_struct.can_filter_enable = CAN_FILTER_ENABLE;
    can_filter_config_struct.can_filter_frame_type[0] = CAN_FRAME_TYPE_DATA;
    can_filter_config_struct.can_filter_frame_type[1] = CAN_FRAME_TYPE_DATA;
    can_filter_config_struct.can_filter_id = 0x00000000ul;
    can_filter_config_struct.can_filter_mask_id = 0x00000000ul;
    can_filter_config_struct.can_filter_mode = CAN_FILTER_MODE_IDMASK;
    can_filter_config_struct.can_filter_fifo = CAN_FILTER_FIFO1;
    can_filter_config_struct.can_filter_bank = 0;
    if( CAN_ERROR == can_set_filter( &can_struct, &can_filter_config_struct ) ) {
        signal_error( TEST_PIN_3 );
    }

    // TODO Test different CAN modes.
    if( CAN_ERROR == can_set_mode( &can_struct, CAN_MODE_LOOPBACK )) {
        signal_error( TEST_PIN_4 );
    }

    // TODO Test different baud rate values.
    if( CAN_ERROR == can_set_frequency( &can_struct, CAN_TEST_FREQUENCY )) {
        signal_error( TEST_PIN_5 );
    }

    // TODO test different data lengths.
    tx_message.message.message_data[0] = BYTE1;
    tx_message.message.message_data[1] = BYTE2;
    tx_message.message.message_data[2] = BYTE3;
    tx_message.message.message_data[3] = BYTE4;
    tx_message.message.message_data[4] = BYTE5;
    tx_message.message.message_data[5] = BYTE6;
    tx_message.message.message_data[6] = BYTE7;
    tx_message.message.message_data[7] = BYTE8;
    tx_message.message.data_len = 8;
    // TODO test different identifier formats.
    tx_message.message.frame_format = CAN_FRAME_FORMAT_STANDARD_11BITS;
    tx_message.message.std_id = 0x48cUL;
    tx_message.message.ext_id = 0x01;
    /* Send the data */
    if( CAN_ERROR == can_transmit( &can_struct, &tx_message )) {
        signal_error( TEST_PIN_6 );
    }

    Delay_100ms();

    // TODO test different RX FIFOs.
    // NOTE if no data was received by this FIFO can_receive will return error.
    rx_message.rx_fifo_number = 1;
    /* Get the data */
    if( CAN_ERROR == can_receive( &can_struct, &rx_message )) {
        signal_error( TEST_PIN_7 );
    }

    Delay_100ms();

    digital_out_init( &test_pin_success, TEST_PIN_SUCCESS );

    byte_check[0] = BYTE1;
    byte_check[1] = BYTE2;
    byte_check[2] = BYTE3;
    byte_check[3] = BYTE4;
    byte_check[4] = BYTE5;
    byte_check[5] = BYTE6;
    byte_check[6] = BYTE7;
    byte_check[7] = BYTE8;

    if( !memcmp( &byte_check, &rx_message.message.message_data, sizeof( byte_check )))
    {
        while(1) {
            signal_success;
        }
    }
    else {
        signal_error( TEST_PIN_8 );
    }

    return 0;
}

// ----------------------------------------------------------------------- END
