#include "board.h"
#include "drv_i2c_master.h"
#include "drv_digital_in.h"
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
    #if defined(MIKROBUS_1_SCL) && defined(MIKROBUS_1_SDA)
    { MIKROBUS_1_SCL, MIKROBUS_1_SDA },
    #endif
    #if defined(MIKROBUS_2_SCL) && defined(MIKROBUS_2_SDA)
    { MIKROBUS_2_SCL, MIKROBUS_2_SDA },
    #endif
    #if defined(MIKROBUS_3_SCL) && defined(MIKROBUS_3_SDA)
    { MIKROBUS_3_SCL, MIKROBUS_3_SDA },
    #endif
    #if defined(MIKROBUS_4_SCL) && defined(MIKROBUS_4_SDA)
    { MIKROBUS_4_SCL, MIKROBUS_4_SDA },
    #endif
    #if defined(MIKROBUS_5_SCL) && defined(MIKROBUS_5_SDA)
    { MIKROBUS_5_SCL, MIKROBUS_5_SDA },
    #endif
    { HAL_PIN_NC, HAL_PIN_NC }
};
