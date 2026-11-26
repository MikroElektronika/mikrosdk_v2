ST7735S GL test

Tests the ST7735S display middleware through the mikroSDK GL driver.
The test fills the screen with red, green, blue, white and black,
draws a square in each corner, rotates through all four orientations,
and finally turns the display power off and on.

Select the module with a define at the top of main.c:
  TEST_GMT144 - 1.44", 128x128
  TEST_GMT177 - 1.77", 128x160

Pins used (Fusion for STM32 v8, STM32F429ZI, SPI6):
  RST PG8, CS PG9, DC PG10, SCK PG13, MOSI PG14.
MISO (PG12) is not wired to the display, it is only set to select the
SPI module.