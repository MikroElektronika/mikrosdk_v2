#include "board.h"
#include "drv_uart.h"
#include "drv_digital_out.h"

#define signal_error(pin)        digital_out_init( &test_pin, pin ); \
                                 digital_out_high( &test_pin ); \
                                 while(1)

#define signal_success(port,pin) digital_out_init( &port, pin ); \
                                 digital_out_write( &port, 1 )

#ifdef MIKROBUS_1
#define MIKROBUS_1_CNT 1
#else
#define MIKROBUS_1_CNT 0
#endif

#ifdef MIKROBUS_2
#define MIKROBUS_2_CNT 1
#else
#define MIKROBUS_2_CNT 0
#endif

#ifdef MIKROBUS_3
#define MIKROBUS_3_CNT 1
#else
#define MIKROBUS_3_CNT 0
#endif

#ifdef MIKROBUS_4
#define MIKROBUS_4_CNT 1
#else
#define MIKROBUS_4_CNT 0
#endif

#ifdef MIKROBUS_5
#define MIKROBUS_5_CNT 1
#else
#define MIKROBUS_5_CNT 0
#endif

// Number of MIKROBUS connections
#define MIKROBUS_COUNT (MIKROBUS_1_CNT + \
                        MIKROBUS_2_CNT + \
                        MIKROBUS_3_CNT + \
                        MIKROBUS_4_CNT + \
                        MIKROBUS_5_CNT)

pin_name_t test_pins_mikrobus[MIKROBUS_COUNT + 1][2] = {
    #if defined(MIKROBUS_1_TX) && defined(MIKROBUS_1_RX)
    { MIKROBUS_1_TX, MIKROBUS_1_RX },
    #endif
    #if defined(MIKROBUS_2_TX) && defined(MIKROBUS_2_RX)
    { MIKROBUS_2_TX, MIKROBUS_2_RX },
    #endif
    #if defined(MIKROBUS_3_TX) && defined(MIKROBUS_3_RX)
    { MIKROBUS_3_TX, MIKROBUS_3_RX },
    #endif
    #if defined(MIKROBUS_4_TX) && defined(MIKROBUS_4_RX)
    { MIKROBUS_4_TX, MIKROBUS_4_RX },
    #endif
    #if defined(MIKROBUS_5_TX) && defined(MIKROBUS_5_RX)
    { MIKROBUS_5_TX, MIKROBUS_5_RX },
    #endif
    { HAL_PIN_NC, HAL_PIN_NC }
};
