SH1107 GL test

The test fills the screen with white and black, draws a square in each corner,
steps through all four rotations (the square grows with each rotation) and turns
the display off and on.

Tested on a 1.5" 128x128 monochrome OLED SH1107 SPI module (GME128128-01-SPI), without
an extra init sequence.
Display size, contrast and color inversion are set in the display configuration in main.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, DC - PG10, SCK - PG13, MOSI - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect VCC to 3.3V. The OLED has no backlight, so there is no BL pin.
