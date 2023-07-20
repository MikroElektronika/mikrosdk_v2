/**
 * @file  main.c
 * @brief Main function for test application.
 * Button test for MikroE clicker boards.
 */

#include "clicker_buttons.h"

static digital_in_t buttons[_TEST_PIN_COUNT];
static digital_out_t leds[_TEST_PIN_COUNT];

void application_init() {
    uint8_t i;

    for(i = 0; i < _TEST_PIN_COUNT; i++) {
        digital_in_init(&buttons[i], pins_buttons[i]);
        digital_out_init(&leds[i], pins_leds[i]);
    }
}

void application_task() {
    uint8_t i;

    while(1) {
        for(i = 0; i < _TEST_PIN_COUNT; i++) {
            // Read value
            uint8_t value = digital_in_read(&buttons[i]);
            // Write read value
            digital_out_write(&leds[i], value);
        }
    }
}

int main(void) {
    application_init();
    application_task();
    return 0;
}
