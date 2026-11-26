#ifndef _DISPLAY_LVGL_H_
#define _DISPLAY_LVGL_H_

#include <stdint.h>
#include <stdbool.h>

/** Rotates the display. Rotation is 0, 1, 2 or 3 (0, 90, 180, 270 degrees). */
void lv_port_disp_rotate(uint8_t rotation);

/** Turns the display output on (true) or off (false). */
void lv_port_disp_power(bool on);

/** Initializes the display and registers it in LVGL. */
void lv_port_disp_init(void);

#endif // _DISPLAY_LVGL_H_
