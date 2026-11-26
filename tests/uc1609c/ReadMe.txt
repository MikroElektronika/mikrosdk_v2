UC1609C GL test

The test fills the screen with white and black, draws a black square in each corner,
steps through all four rotations (the square grows with each rotation) and turns
the display off and on.

Tested on a 192x64 monochrome LCD module (19264-05 V3.2) with the UC1609C controller,
connected over SPI (4-wire, with the CD pin), without an extra init sequence.
Display size, contrast and color inversion are set in the display configuration in main.c.
The rows are mirrored (UC1609C_SCAN_DIR_MY), so the first display row is at the top of the glass.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, CD - PG10, SCK - PG13, SDA - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect VDD to 3.3V (not 5V) and GND to GND. The backlight pins were briefly tested
with A connected to 3.3V and K to GND and it works. The value of the series resistor on
the module is unknown, so an external resistor (100 - 220 ohm) in series with A is
recommended for longer use.
