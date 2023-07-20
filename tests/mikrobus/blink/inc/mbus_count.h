/**
 * @file  mbus_count.h
 * @brief Main header file.
 * Led test for mikrobus GPIO - tester clicks needed.
 * NOTHING NEEDS TO BE CHANGED IN THIS FILE!!!
 * //            MBUS             //
 * //  -------------------------  //
 * //  1  - AN          9  - PWM  //
 * //  2  - RST         10 - INT  //
 * //  3  - CS          11 - RX   //
 * //  4  - SCK         12 - TX   //
 * //  5  - SDO         13 - SCL  //
 * //  6  - SDI         14 - SDA  //
 * // *7  - 3.3v       *15 - 5.0v //
 * // *8  - GND        *16 - GND  //
 * //  -------------------------  //
 */

#include "drv_digital_out.h"
#include "board.h"

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

// Number of MIKROBUS pins
// Defined by number of MIKROBUS'es * 12 pins
// 1 MIKROBUS --> 1 * 12 = 12 pins
// 2 MIKROBUS'es --> 2 * 12 = 24 pins
// etc.
#define MBUS_LED_NUM ((MIKROBUS_1_CNT + \
                       MIKROBUS_2_CNT + \
                       MIKROBUS_3_CNT + \
                       MIKROBUS_4_CNT + \
                       MIKROBUS_5_CNT) * 12)

pin_name_t pins[MBUS_LED_NUM+1] = {
    #ifdef MIKROBUS_1
    MIKROBUS_1_AN,  MIKROBUS_1_RST, MIKROBUS_1_CS, MIKROBUS_1_SCK, MIKROBUS_1_MISO, MIKROBUS_1_MOSI,
    MIKROBUS_1_PWM, MIKROBUS_1_INT, MIKROBUS_1_RX, MIKROBUS_1_TX,  MIKROBUS_1_SCL,  MIKROBUS_1_SDA,
    #endif
    #ifdef MIKROBUS_2
    MIKROBUS_2_AN,  MIKROBUS_2_RST, MIKROBUS_2_CS, MIKROBUS_2_SCK, MIKROBUS_2_MISO, MIKROBUS_2_MOSI,
    MIKROBUS_2_PWM, MIKROBUS_2_INT, MIKROBUS_2_RX, MIKROBUS_2_TX,  MIKROBUS_2_SCL,  MIKROBUS_2_SDA,
    #endif
    #ifdef MIKROBUS_3
    MIKROBUS_3_AN,  MIKROBUS_3_RST, MIKROBUS_3_CS, MIKROBUS_3_SCK, MIKROBUS_3_MISO, MIKROBUS_3_MOSI,
    MIKROBUS_3_PWM, MIKROBUS_3_INT, MIKROBUS_3_RX, MIKROBUS_3_TX,  MIKROBUS_3_SCL,  MIKROBUS_3_SDA,
    #endif
    #ifdef MIKROBUS_4
    MIKROBUS_4_AN,  MIKROBUS_4_RST, MIKROBUS_4_CS, MIKROBUS_4_SCK, MIKROBUS_4_MISO, MIKROBUS_4_MOSI,
    MIKROBUS_4_PWM, MIKROBUS_4_INT, MIKROBUS_4_RX, MIKROBUS_4_TX,  MIKROBUS_4_SCL,  MIKROBUS_4_SDA,
    #endif
    #ifdef MIKROBUS_5
    MIKROBUS_5_AN,  MIKROBUS_5_RST, MIKROBUS_5_CS, MIKROBUS_5_SCK, MIKROBUS_5_MISO, MIKROBUS_5_MOSI,
    MIKROBUS_5_PWM, MIKROBUS_5_INT, MIKROBUS_5_RX, MIKROBUS_5_TX,  MIKROBUS_5_SCL,  MIKROBUS_5_SDA,
    #endif
    HAL_PIN_NC
};
