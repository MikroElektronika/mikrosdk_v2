ST7789 LVGL test

Tests the ST7789 display through the LVGL adapter (LVGL 9.4,
RGB565 swapped, partial rendering).

Display settings are at the top of display_lvgl.c. By default they are
for modules with a CS pin and a 240x320 panel (GMT020-02, GMT024-10,
GMT028-05). Optional settings (TFT_INVERT_COLORS, TFT_SPI_MODE,
TFT_SOFT_SPI, TFT_INIT_SEQ) are defined before including lvgl_common.h.

To test the GMT130 (240x240, no CS pin), uncomment "#define TEST_GMT130"
in display_lvgl.c. This module works only with software (bit-banged) SPI
and needs its own init sequence.