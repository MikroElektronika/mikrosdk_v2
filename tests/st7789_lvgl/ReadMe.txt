Example is meant for testing the ST7789 display with LVGL using mikroSDK 2.0.

Tested with GMT020-02 (2.0" TFT, 240x320, 4-wire SPI) on Fusion for STM32 v8
with STM32F429ZI and LVGL 9.4.0. Display pins used in the example (see
display_lvgl.c):

* CS  - PG9
* DC  - PG10
* RST - PG8
* SDA - PG14 (SPI6 MOSI)
* SCL - PG13 (SPI6 SCK)
* VCC - VCC pin of the port header
* GND - GND

PG12 (SPI6 MISO) is not connected to the display, but the SPI driver requires
all three SPI pins, so leave it free.

Expected result: a button with the text "ST7789 + LVGL" in the middle of the screen.

Go step by step through the example and follow instructions for testing.
