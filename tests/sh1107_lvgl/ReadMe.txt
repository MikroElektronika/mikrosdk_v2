SH1107 LVGL test

The test shows a title, a card with a seconds counter and the mikroSDK logo.
The counter is updated once per second to check that the display refreshes correctly.

Tested on a 1.5" 128x128 monochrome OLED SH1107 SPI module (GME128128-01-SPI), without
an extra init sequence.
LVGL renders in RGB565 and the driver converts every pixel to black or white, so the
colors in the UI should be chosen for good contrast (white on black works best).
Display size and pins are set with the macros at the top of display_lvgl.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, DC - PG10, SCK - PG13, MOSI - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect VCC to 3.3V. The OLED has no backlight, so there is no BL pin.
