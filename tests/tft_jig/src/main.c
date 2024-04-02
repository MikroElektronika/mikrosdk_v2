/**
 * @file  main.c
 * @brief Main function for test application.
 * Led test for TFT connections - TFT Jig needed.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "tft_connections.h"
#include "delays.h"

#define DEFINED_DELAY 300  // TODO - delay defined in milliseconds

static digital_out_t tft_jig_leds[TFT_PIN_COUNT];

void application_init() {
    uint8_t i;

    for(i = 0; i < TFT_PIN_COUNT; i++) {
        digital_out_init(&tft_jig_leds[i], pins[i]);
    }
}

void application_task() {
    uint8_t i;

    while(1) {
        for(i = 0; i < TFT_PIN_COUNT; i++) {
            digital_out_toggle(&tft_jig_leds[i]);
            Delay_ms(DEFINED_DELAY);
            digital_out_toggle(&tft_jig_leds[i]);
        }
    }
}

int main( void ) {
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();
    application_task();

    return 0;
}
