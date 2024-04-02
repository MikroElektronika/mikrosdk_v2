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
#define TEST_PIN_5  HAL_PIN_NC
#define TEST_PIN_6  HAL_PIN_NC
#define TEST_PIN_7  HAL_PIN_NC
#define TEST_PIN_8  HAL_PIN_NC
#define TEST_PIN_9  HAL_PIN_NC
#define TEST_PIN_10 HAL_PIN_NC
#define TEST_PORT   HAL_PORT_NC

#define signal_error(pin) digital_out_init( &test_pin, pin ); \
                          digital_out_high( &test_pin ); \
                          while(1)
#define signal_receive_error(pin) digital_out_init( &test_pin, pin ); \
                                  digital_out_high( &test_pin ); \
                                  Delay_ms(3000); \
                                  digital_out_low( &test_pin );
// ----------------------------------------------------------------- VARIABLES
static digital_out_t test_pin;
static port_t port;
static can_config_t can_config_struct;
static can_filter_config_t can_filter_config_struct;
static can_t can_struct;
can_receive_message_struct rx_message;

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
    can_filter_config_struct.can_filter_fifo = CAN_FILTER_FIFO0;
    can_filter_config_struct.can_filter_bank = 0;
    if( CAN_ERROR == can_set_filter( &can_struct, &can_filter_config_struct ) ) {
        signal_error( TEST_PIN_3 );
    }

    // TODO Test different CAN modes.
    if( CAN_ERROR == can_set_mode( &can_struct, CAN_MODE_NORMAL)) {
        signal_error( TEST_PIN_4 );
    }

    // TODO Test different baud rate values.
    if( CAN_ERROR == can_set_frequency( &can_struct, CAN_TEST_FREQUENCY )) {
        signal_error( TEST_PIN_5 );
    }

    port_init( &port, TEST_PORT, 0xFF, PIN_DIRECTION_DIGITAL_OUTPUT );

    Delay_ms(1000);

    // TODO test different RX FIFOs.
    // NOTE if no data was received by this FIFO can_receive will return error.
    rx_message.rx_fifo_number = 0;
    while(1) {
        /* Receive the data */
        if( CAN_ERROR != can_receive( &can_struct, &rx_message )) {
            if( rx_message.message.message_data[0] == 0xAA && rx_message.message.message_data[2] == 0xBB ) {
                port_write( &port, rx_message.message.message_data[1] );
            } else {
                signal_receive_error( TEST_PIN_6 );
            }
        }
    }

    return 0;
}

// ----------------------------------------------------------------------- END
