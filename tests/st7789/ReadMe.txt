Example is meant for testing the ST7789 display using mikroSDK 2.0
Tested with GMT020-02 (2.0" TFT, 240x320, 4-wire SPI) on Fusion for STM32 v8
with STM32F429ZI. Display pins used in the example (see the macros in main.c):

* CS  - PG9
* DC  - PG10
* RST - PG8
* SDA - PG14 (SPI6 MOSI)
* SCL - PG13 (SPI6 SCK)
* VCC - VCC pin of the port header (display supply must be 2.6V - 3.3V)
* GND - GND

PG12 (SPI6 MISO) is not connected to the display, but the SPI driver requires
all three SPI pins, so leave it free.

Expected result:
* The screen is filled with red, green, blue, white and black, 3 seconds each.
* Then a square is drawn in each corner: red top left, green top right,
  blue bottom left and white bottom right.

Go step by step through the example and follow instructions for testing.