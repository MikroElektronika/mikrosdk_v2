ST7525I GL test

The test fills the screen with white and black, draws a black square in each corner,
steps through all four rotations (the square grows with each rotation) and turns
the display off and on.

Tested on a 192x64 monochrome LCD module (JLX19264G-901) with the ST7525I controller,
connected over SPI, without an extra init sequence. The module must be set to the serial
(SPI) interface: resistors R4, R5 and R9 populated, R3 and R6 empty.
Display size, contrast and color inversion are set in the display configuration in main.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, RS (A0) - PG10, D0 (SCL) - PG13, D1 (SDA) - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect VDD to 3.3V and VSS to GND. The backlight (LEDA) is not connected in this test,
so the LCD is read with ambient light only.
