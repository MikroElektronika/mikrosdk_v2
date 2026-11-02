# mikroSDK GC9107 Display Driver

Display middleware library for GC9107 based displays connected over SPI. It works with the mikroSDK Graphic Library and is used by the LVGL adapter in `components/ips`. Tested with the IPS Display 3 Click (128x115, round display).

## Wiring

The IPS Display 3 Click is connected to a mikroBUS socket (tested in mikroBUS 1 of Fusion for STM32 v8):

| Click pin | mikroBUS pin |
|---|---|
| RST | RST |
| CS | CS |
| SCK | SCK |
| SDI | MOSI |
| DC | INT |
| BCK (backlight) | PWM |

MISO is not connected on the click, but the mikroSDK SPI driver requires all three SPI pins, so set it in the configuration.

## Configuration

`gc9107_cfg_t` fields:

- `bck`, `rst`, `cs`, `rs` - control pins (`rs` is the data/command pin),
- `sck`, `sdi`, `sdo` - SPI pins (must belong to the same SPI module),
- `width`, `height` - visible size in pixels (128x115).

The SPI runs in mode 0 at 5 MHz. The visible area starts 13 rows below the beginning of the controller memory. The driver takes this into account.

## Usage

```c
static gl_driver_t gl_driver;
static gc9107_cfg_t gc9107_cfg;

// Fill gc9107_cfg (pins, width, height), then:
gc9107_gl_init(&gc9107_cfg, &gl_driver);
gl_set_driver(&gl_driver);

gl_clear(GL_RED);
```

`gc9107_gl_init` also turns the backlight on. Other functions: `gc9107_gl_rotate(0..3)` rotates the display (0, 90, 180 and 270 degrees), `gc9107_gl_display_power(1/0)` turns the display output on or off, `gc9107_gl_write_pixels()` sends raw RGB565 pixel data and `gc9107_set_backlight()` controls the backlight pin.

The low level driver (`gc9107_init`, `gc9107_configure`, `gc9107_write_command`, `gc9107_write_param`) can be used without the Graphic Library. See `tests/gc9107` for an example.

## LVGL

The LVGL adapter is in `components/ips/common/gc9107` and is selected automatically for the `IPS_DISPLAY_3_CLICK` board. See `tests/lvgl/lvgl_button_grid` for an example.

## Limitations

- Tested only on Fusion for STM32 v8 with the ARM GCC toolchain. Not tested on PIC.
- The glass of the IPS Display 3 Click is round, so the corners of the 128x115 area are not visible.
- The LVGL adapter was tested with `tests/lvgl/lvgl_button_grid` (colors, drawing and backlight). LVGL rotation was not tested.
- The backlight is only switched on and off, PWM brightness control is not implemented. There is no touch support.
