/**
 * @file  main.c
 * @brief Main function for test application.
 * Led test for mikrobus GPIO - tester clicks needed.
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

#include "mbus_count.h"

#define DEFINED_DELAY 300  // TODO - delay defined in milliseconds

static digital_out_t mbus_led_port[MBUS_LED_NUM+1];

/*< @brief Initializes all mikroBUS pin as digital output
 *         and sets to logical zero.
 */
void application_init() {
    uint8_t i;

    for(i = 0; i < MBUS_LED_NUM; i++) {
        digital_out_init(&mbus_led_port[i], pins[i]);
    }

    for(i = 0; i < MBUS_LED_NUM; i++) {
        digital_out_low(&mbus_led_port[i]);
    }
}

/*< @brief Toggles all previously initialized
 *         pins with 'DEFINED_DELAY' before each toggle.
 */
void application_task() {
    uint8_t i;

    while(1) {
        for(i = 0; i < MBUS_LED_NUM; i++) {
            digital_out_toggle(&mbus_led_port[i]);
            Delay_ms(DEFINED_DELAY);
            digital_out_toggle(&mbus_led_port[i]);
        }
    }
}

int main(void) {
    application_init();
    application_task();

    return 0;
}
