ST7796 GL test

The test fills the screen with red, green, blue, white and black, draws a square
in each corner, steps through all four rotations and turns the display off and on.

Tested on a 3.5" 320x480 ST7796 SPI module, without an extra init sequence.
Display size, color order and color inversion are set with the macros at the top of main.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, DC - PG10, SCK - PG13, MOSI - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect the display backlight (BL) to 3.3V.