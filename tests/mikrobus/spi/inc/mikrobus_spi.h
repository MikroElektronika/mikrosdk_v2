#include "board.h"
#include "drv_spi_master.h"
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

pin_name_t test_pins_mikrobus[MIKROBUS_COUNT + 1][4] = {
    #if defined(MIKROBUS_1_SCK) && defined(MIKROBUS_1_MISO) && \
        defined(MIKROBUS_1_MOSI) && defined(MIKROBUS_1_CS)
    { MIKROBUS_1_SCK, MIKROBUS_1_MISO, MIKROBUS_1_MOSI, MIKROBUS_1_CS },
    #endif
    #if defined(MIKROBUS_2_SCK) && defined(MIKROBUS_2_MISO) && \
        defined(MIKROBUS_2_MOSI) && defined(MIKROBUS_2_CS)
    { MIKROBUS_2_SCK, MIKROBUS_2_MISO, MIKROBUS_2_MOSI, MIKROBUS_2_CS },
    #endif
    #if defined(MIKROBUS_3_SCK) && defined(MIKROBUS_3_MISO) && \
        defined(MIKROBUS_3_MOSI) && defined(MIKROBUS_3_CS)
    { MIKROBUS_3_SCK, MIKROBUS_3_MISO, MIKROBUS_3_MOSI, MIKROBUS_3_CS },
    #endif
    #if defined(MIKROBUS_4_SCK) && defined(MIKROBUS_4_MISO) && \
        defined(MIKROBUS_4_MOSI) && defined(MIKROBUS_4_CS)
    { MIKROBUS_4_SCK, MIKROBUS_4_MISO, MIKROBUS_4_MOSI, MIKROBUS_4_CS },
    #endif
    #if defined(MIKROBUS_5_SCK) && defined(MIKROBUS_5_MISO) && \
        defined(MIKROBUS_5_MOSI) && defined(MIKROBUS_5_CS)
    { MIKROBUS_5_SCK, MIKROBUS_5_MISO, MIKROBUS_5_MOSI, MIKROBUS_5_CS },
    #endif
    { HAL_PIN_NC, HAL_PIN_NC, HAL_PIN_NC, HAL_PIN_NC }
};
