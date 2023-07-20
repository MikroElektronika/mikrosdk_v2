#include "board.h"
#include "drv_uart.h"
#include "conversions.h"
#include "drv_analog_in.h"

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

pin_name_t test_pins_mikrobus[MIKROBUS_COUNT + 1] = {
    #if defined(MIKROBUS_1_AN)
    MIKROBUS_1_AN,
    #endif
    #if defined(MIKROBUS_2_AN)
    MIKROBUS_2_AN,
    #endif
    #if defined(MIKROBUS_3_AN)
    MIKROBUS_3_AN,
    #endif
    #if defined(MIKROBUS_4_AN)
    MIKROBUS_4_AN,
    #endif
    #if defined(MIKROBUS_5_AN)
    MIKROBUS_5_AN,
    #endif
    HAL_PIN_NC
};
