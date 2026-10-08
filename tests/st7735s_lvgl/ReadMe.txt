ST7735S LVGL test

Tests the ST7735S display through the LVGL adapter (LVGL 9.4,
RGB565 swapped, partial rendering). The test shows a title, a counter
that increases every second and the mikroSDK logo.

Select the module with a define at the top of display_lvgl.c:
  TEST_GMT144 - 1.44", 128x128
  TEST_GMT177 - 1.77", 128x160

Pins used (Fusion for STM32 v8, STM32F429ZI, SPI6):
  RST PG8, CS PG9, DC PG10, SCK PG13, MOSI PG14.
MISO (PG12) is not wired to the display, it is only set to select the
SPI module.