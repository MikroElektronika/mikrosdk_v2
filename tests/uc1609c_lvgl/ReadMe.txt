UC1609C LVGL test

The test shows a title, a card with a seconds counter and the mikroSDK logo.
The counter is updated once per second to check that the display refreshes correctly.

Tested on a 192x64 monochrome LCD module (19264-05 V3.2) with the UC1609C controller,
connected over SPI (4-wire, with the CD pin), without an extra init sequence.
LVGL renders in RGB565 and the driver converts every pixel to black or white, so the
colors in the UI should be chosen for good contrast (this test uses black elements on a
white background). Fine details of the logo are not readable on a 1-bit display of this size.
Display size and pins are set with the macros at the top of display_lvgl.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, CD - PG10, SCK - PG13, SDA - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect VDD to 3.3V (not 5V) and GND to GND. The backlight pins were briefly tested
with A connected to 3.3V and K to GND and it works. The value of the series resistor on
the module is unknown, so an external resistor (100 - 220 ohm) in series with A is
recommended for longer use.
