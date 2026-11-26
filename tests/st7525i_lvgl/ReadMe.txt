ST7525I LVGL test

The test shows a title, a card with a seconds counter and the mikroSDK logo.
The counter is updated once per second to check that the display refreshes correctly.

Tested on a 192x64 monochrome LCD module (JLX19264G-901) with the ST7525I controller,
connected over SPI, without an extra init sequence. The module must be set to the serial
(SPI) interface: resistors R4, R5 and R9 populated, R3 and R6 empty.
LVGL renders in RGB565 and the driver converts every pixel to black or white, so the
colors in the UI should be chosen for good contrast (white on black works best, the
logo has white parts that disappear on a white background).
Display size and pins are set with the macros at the top of display_lvgl.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, RS (A0) - PG10, D0 (SCL) - PG13, D1 (SDA) - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect VDD to 3.3V and VSS to GND. The backlight (LEDA) is not connected in this test,
so the LCD is read with ambient light only.
