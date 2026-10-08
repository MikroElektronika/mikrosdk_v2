ST7796 LVGL test

The test shows a title, a card with a seconds counter and the mikroSDK logo.
The counter is updated once per second to check that the display refreshes correctly.

Tested on a 3.5" 320x480 ST7796 SPI module, without an extra init sequence.
Display size and color order are set with the macros at the top of display_lvgl.c.

Pins (STM32F429ZI, SPI6): RST - PG8, CS - PG9, DC - PG10, SCK - PG13, MOSI - PG14.
MISO (PG12) is not wired to the display, but the SPI driver requires it.
Connect the display backlight (BL) to 3.3V.