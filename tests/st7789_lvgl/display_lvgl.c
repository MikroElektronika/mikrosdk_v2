#include "display_lvgl.h"
#include "lvgl.h"

#include "display_lvgl.h"
#include "lvgl.h"

// GMT130 manufacturer power, voltage and gamma settings: command, number of parameters, parameters. Ends with 0.
static const uint8_t gmt130_init[] =
{
    0xB2, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,
    0xB7, 1, 0x35,
    0xBB, 1, 0x19,
    0xC0, 1, 0x2C,
    0xC2, 1, 0x01,
    0xC3, 1, 0x12,
    0xC4, 1, 0x20,
    0xC6, 1, 0x0F,
    0xD0, 2, 0xA4, 0xA1,
    0xE0, 14, 0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23,
    0xE1, 14, 0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23,
    0
};

// ---------------------------------------------------- DISPLAY CONFIGURATION

#define TFT_RST_PIN   GPIO_PG8
#define TFT_CS_PIN    HAL_PIN_NC   // GMT130 has no CS pin.
#define TFT_DC_PIN    GPIO_PG10
#define TFT_SCK_PIN   GPIO_PG13   // SCL
#define TFT_MISO_PIN  GPIO_PG12   // Not wired, but required by the SPI driver.
#define TFT_MOSI_PIN  GPIO_PG14   // SDA

#define _TFT_WIDTH_   240
#define _TFT_HEIGHT_  240
#define TFT_INVERT_COLORS 1
#define TFT_SOFT_SPI  1
#define TFT_INIT_SEQ  gmt130_init

#include "lvgl_common.h"

#include "lvgl_common.h"

#define TEST_LVGL_BUFFER_LINES 20   // Number of display lines in the draw buffer.

// Draw buffer: partial rendering, 2 bytes per pixel (RGB565).
static uint8_t draw_buffer[_TFT_WIDTH_ * TEST_LVGL_BUFFER_LINES * 2] __attribute__((aligned(4)));
static lv_display_t *display;

static void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    int32_t width  = lv_display_get_horizontal_resolution(disp);
    int32_t height = lv_display_get_vertical_resolution(disp);

    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > width - 1 ? width- 1 : area->x2;
    int32_t act_y2 = area->y2 > height - 1 ? height - 1 : area->y2;

    uint16_t full_w = area->x2 - area->x1 + 1;
    uint16_t act_w  = act_x2 - act_x1 + 1;
    uint16_t *color_p = (uint16_t *)px_map;

    set_column();
    set_page();
    frame_start(start_column, end_column, start_page, end_page);

    for (int16_t i = act_y1; i <= act_y2; i++)
    {
        write_array_data(color_p, act_w);
        color_p += full_w;
    }

    display_deselect();

    lv_display_flush_ready(disp);
}

void lv_port_disp_init(void)
{
    display_configure();

    display = lv_display_create(_TFT_WIDTH_, _TFT_HEIGHT_);
    lv_display_set_flush_cb(display, display_flush);
    lv_display_set_color_format(display, LV_COLOR_FORMAT_RGB565_SWAPPED);
    lv_display_set_buffers(display, draw_buffer, NULL, sizeof(draw_buffer), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void lv_port_disp_rotate(uint8_t rotation)
{
    st7789_rotate(rotation);
    lv_display_set_resolution(display, st7789_get_display_width(), st7789_get_display_height());
    lv_obj_invalidate(lv_screen_active());
}

void lv_port_disp_power(bool on)
{
    st7789_display_power(on ? 1 : 0);
}
