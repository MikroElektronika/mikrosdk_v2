#include "board.h"
#include "drv_pwm.h"

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

pin_name_t test_pins_mikrobus[MIKROBUS_COUNT+1] = {
    #ifdef MIKROBUS_1_PWM
    MIKROBUS_1_PWM,
    #endif
    #ifdef MIKROBUS_2_PWM
    MIKROBUS_2_PWM,
    #endif
    #ifdef MIKROBUS_3_PWM
    MIKROBUS_3_PWM,
    #endif
    #ifdef MIKROBUS_4_PWM
    MIKROBUS_4_PWM,
    #endif
    #ifdef MIKROBUS_5_PWM
    MIKROBUS_5_PWM,
    #endif
    HAL_PIN_NC
};
