#include "display_lvgl.h"
#include "lvgl.h"

// ---------------------------------------------------- DISPLAY CONFIGURATION

#define TFT_RST_PIN HAL_PIN_NC
#define TEST_SSD1312_SCL HAL_PIN_NC // SCL
#define TEST_SSD1312_SDA HAL_PIN_NC // SDA

#define TFT_I2C_ADDRESS 0x3C
#define TFT_I2C_SPEED   I2C_MASTER_SPEED_STANDARD // 100 kHz.
// Display size of the 64x128 module (GME64128-02), portrait.
#define _TFT_WIDTH_  64
#define _TFT_HEIGHT_ 128

#include "lvgl_common.h"

#define TEST_LVGL_BUFFER_LINES 32 // Number of display lines in the draw buffer.

// Draw buffer: partial rendering, RGB565 (2 bytes per pixel), _TFT_WIDTH_ x TEST_LVGL_BUFFER_LINES.
static uint16_t draw_buffer[_TFT_WIDTH_ * TEST_LVGL_BUFFER_LINES] __attribute__((aligned(4)));
static lv_display_t *display;

static void display_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    int32_t width  = lv_display_get_horizontal_resolution(disp);
    int32_t height = lv_display_get_vertical_resolution(disp);

    int32_t act_x1 = area->x1 < 0 ? 0 :area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 :area->y1;
    int32_t act_x2 = area->x2 > width - 1 ? width -1 : area->x2;
    int32_t act_y2 = area->y2 > height - 1 ? height -1 : area->y2;

    uint16_t full_w = area->x2 - area->x1 + 1;
    uint16_t act_w  = act_x2 - act_x1 + 1;
    const uint16_t *row_p = (const uint16_t *)px_map;

    set_column();
    set_page();
    frame_start(start_column, end_column, start_page, end_page);

    for (int16_t i = act_y1; i <= act_y2; i++)
    {
        write_array_data(row_p, act_w);
        row_p += full_w;
    }

    display_deselect();

    lv_display_flush_ready(disp);
}

void lv_port_disp_init(void)
{
    display_configure();

    display = lv_display_create(_TFT_WIDTH_, _TFT_HEIGHT_);
    lv_display_set_flush_cb(display, display_flush);
    lv_display_set_color_format(display, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(display, draw_buffer, NULL, sizeof(draw_buffer), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

void lv_port_disp_rotate(uint8_t rotation)
{
    ssd1312_rotate(rotation);
    lv_display_set_resolution(display, ssd1312_get_display_width(), ssd1312_get_display_height());
    lv_obj_invalidate(lv_screen_active());
}

void lv_port_disp_power(bool on)
{
    ssd1312_display_power(on ? 1 : 0);
}
