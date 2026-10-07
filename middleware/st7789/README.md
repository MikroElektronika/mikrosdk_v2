# mikroSDK ST7789 Display Driver

Display middleware library for ST7789 based TFT displays connected over SPI. It works with the mikroSDK Graphic Library and includes an adapter for LVGL. Tested with GMT020-02, GMT028-05 and GMT024-10 (240x320).

## Wiring

The display is connected over SPI. The pins used in the examples (Fusion for STM32 v8, STM32F429ZI, SPI6):

| Display pin | Board pin |
|---|---|
| CS | PG9 |
| DC | PG10 |
| RST (RES) | PG8 |
| SCK (SCL) | PG13 |
| SDA | PG14 |
| VCC, GND | VCC, GND |

The mikroSDK SPI driver requires all three SPI pins (SCK, MISO and MOSI). The display does not use MISO, so leave PG12 unconnected, but set it in the configuration. Check the datasheet of your module for the supply voltage.

## Configuration

`st7789_cfg_t` fields:

- `rst`, `cs`, `d_c` - control pins,
- `sck`, `miso`, `mosi` - SPI pins (must belong to the same SPI module),
- `speed` - SPI clock in Hz (20 MHz was tested),
- `width`, `height` - display size in pixels,
- `invert` - set to 1 if the colors need to be inverted (see the table below).

## Usage

```c
static gl_driver_t gl_driver;
static st7789_cfg_t st7789_cfg;

// Fill st7789_cfg (pins, speed, width, height, invert), then:
st7789_init(&st7789_cfg, &gl_driver);
gl_set_driver(&gl_driver);

gl_clear(GL_RED);
```

Other functions: `st7789_rotate(0..3)` rotates the display (0, 90, 180 and 270 degrees clockwise), `st7789_display_power(1/0)` turns the display output on or off and `st7789_write_pixels()` sends raw RGB565 pixel data.

## LVGL

The adapter is in `middleware/st7789/lvgl` (library `MikroSDK.St7789.LVGL.Common`). The project must define `TFT_RST_PIN`, `TFT_CS_PIN`, `TFT_DC_PIN`, `TFT_SCK_PIN`, `TFT_MISO_PIN`, `TFT_MOSI_PIN`, `_TFT_WIDTH_` and `_TFT_HEIGHT_` before including `lvgl_common.h`. `TFT_SPI_SPEED` (default 20 MHz) and `TFT_INVERT_COLORS` (default 0) are optional. The display must use the byte swapped RGB565 format (`LV_COLOR_FORMAT_RGB565_SWAPPED`). See `tests/st7789_lvgl` for an example with LVGL 9.4.0.

## Tested modules

| Module | Resolution | `invert` |
|---|---|---|
| GMT020-02 | 240x320 | 1 |
| GMT028-05 | 240x320 | 0 |
| GMT024-10 | 240x320 | 0 |

## Limitations

- Tested only on Fusion for STM32 v8 with the ARM GCC toolchain.
- Displays smaller than 240x320 (for example 170x320 or 240x240) are not supported yet.
- The backlight pin is not handled and there is no touch support.