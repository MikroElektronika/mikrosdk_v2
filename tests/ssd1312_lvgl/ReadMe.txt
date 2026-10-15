SSD1312 LVGL test

The test shows a title, a card with a seconds counter and the mikroSDK logo.
The counter is updated once per second to check that the display refreshes correctly.

Tested on a 1.3" 64x128 monochrome OLED SSD1312 I2C module (GME64128-02), without
an extra init sequence.
LVGL renders in RGB565 and the driver converts every pixel to black or white, so the
colors in the UI should be chosen for good contrast (white on black works best).
Display size, pins, I2C address and speed are set with the macros at the top of
display_lvgl.c. The module needs a display offset of 0x20, which is the default
in lvgl_common.h.

Pins (STM32F429ZI, I2C1): SCL - PB8, SDA - PB9.
The module has no RST pin, so the display cannot be reset from the MCU. If the picture
looks wrong after programming, disconnect all four wires for about 10 seconds.
I2C address is 0x3C. Connect VCC to 3.3V.
The OLED has no backlight, so there is no BL pin.
