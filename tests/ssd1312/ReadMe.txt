SSD1312 GL test

The test fills the screen with white and black, draws a square in each corner,
steps through all four rotations (the square grows with each rotation) and turns
the display off and on.

Tested on a 1.3" 64x128 monochrome OLED SSD1312 I2C module (GME64128-02), without
an extra init sequence.
Display size, I2C address, contrast, display offset and color inversion are set in
the macros at the top of main.c.
The module needs a display offset of 0x20 (TEST_SSD1312_DISPLAY_OFFSET).

Pins (STM32F429ZI, I2C1): SCL - PB8, SDA - PB9.
The module has no RST pin, so the display cannot be reset from the MCU. If the picture
looks wrong after programming, disconnect all four wires for about 10 seconds.
I2C address is 0x3C. Connect VCC to 3.3V.
The OLED has no backlight, so there is no BL pin.
