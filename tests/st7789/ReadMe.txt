ST7789 GL test

Tests the ST7789 display middleware through the mikroSDK GL driver.
The test fills the screen with red, green, blue, white and black,
draws a square in each corner, rotates through all four orientations,
and finally turns the display power off and on.

Default settings are for modules with a CS pin and a 240x320 panel
(GMT020-02, GMT024-10, GMT028-05). For GMT020-02 set invert to 1.

To test the GMT130 (240x240, no CS pin), uncomment "#define TEST_GMT130"
at the top of main.c. This module works only with software (bit-banged)
SPI and needs its own init sequence, both of which are set in that block.