/**
 * @file  clicker_buttons.h
 * @brief Main header file.
 * NOTE   Define only _BUTTON_x and _LED_x macros here.
 */

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "board.h"

// NOTE 8 pins added because Clicker 4 has 8 buttons
// -------------------------------------------------
#ifndef BUTTON_1
    #define _BUTTON_COUNT_1 0
#else
    #define _BUTTON_COUNT_1 1
#endif

#ifndef BUTTON_2
    #define _BUTTON_COUNT_2 0
#else
    #define _BUTTON_COUNT_2 1
#endif

#ifndef BUTTON_3
    #define _BUTTON_COUNT_3 0
#else
    #define _BUTTON_COUNT_3 1
#endif

#ifndef BUTTON_4
    #define _BUTTON_COUNT_4 0
#else
    #define _BUTTON_COUNT_4 1
#endif

#ifndef BUTTON_5
    #define _BUTTON_COUNT_5 0
#else
    #define _BUTTON_COUNT_5 1
#endif

#ifndef BUTTON_6
    #define _BUTTON_COUNT_6 0
#else
    #define _BUTTON_COUNT_6 1
#endif

#ifndef BUTTON_7
    #define _BUTTON_COUNT_7 0
#else
    #define _BUTTON_COUNT_7 1
#endif

#ifndef BUTTON_8
    #define _BUTTON_COUNT_8 0
#else
    #define _BUTTON_COUNT_8 1
#endif
// -------------------------------------------------

#define _BUTTON_COUNT (_BUTTON_COUNT_1 + \
                       _BUTTON_COUNT_2 + \
                       _BUTTON_COUNT_3 + \
                       _BUTTON_COUNT_4 + \
                       _BUTTON_COUNT_5 + \
                       _BUTTON_COUNT_6 + \
                       _BUTTON_COUNT_7 + \
                       _BUTTON_COUNT_8)

#if _BUTTON_COUNT == 0
    #define _TEST_PIN_COUNT 1
#else
    #define _TEST_PIN_COUNT _BUTTON_COUNT
#endif

pin_name_t pins_buttons[_TEST_PIN_COUNT+1] = {
    #ifdef BUTTON_1
    BUTTON_1,
    #endif
    #ifdef BUTTON_2
    BUTTON_2,
    #endif
    #ifdef BUTTON_3
    BUTTON_3,
    #endif
    #ifdef BUTTON_4
    BUTTON_4,
    #endif
    #ifdef BUTTON_5
    BUTTON_5,
    #endif
    #ifdef BUTTON_6
    BUTTON_6,
    #endif
    #ifdef BUTTON_7
    BUTTON_7,
    #endif
    #ifdef BUTTON_8
    BUTTON_8,
    #endif
    HAL_PIN_NC
};

pin_name_t pins_leds[_TEST_PIN_COUNT+1] = {
    #ifdef LED_1
    LED_1,
    #endif
    #ifdef LED_2
    LED_2,
    #endif
    #ifdef LED_3
    LED_3,
    #endif
    #ifdef LED_4
    LED_4,
    #endif
    #ifdef LED_5
    LED_5,
    #endif
    #ifdef LED_6
    LED_6,
    #endif
    #ifdef LED_7
    LED_7,
    #endif
    #ifdef LED_8
    LED_8,
    #endif
    HAL_PIN_NC
};
