/**
 * @file lv_port_disp_templ.c
 */
#include "display_lvgl.h"
#include "lvgl_common.h"

static void disp_init(void);
static void disp_flush(lv_display_t * display, const lv_area_t * area, uint8_t * px_map);

static lv_display_t * g_disp;

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display.
     * -----------------------*/
    disp_init();

    /*-----------------------------------
     * Create the display in LVGL (v9+).
     *----------------------------------*/
    g_disp = lv_display_create(_TFT_WIDTH_, _TFT_HEIGHT_);

    /* Used to copy the buffer's content to the display. */
    lv_display_set_flush_cb(g_disp, disp_flush);

    /*-----------------------------
     * Create a buffer for drawing.
     *----------------------------*/
    /* Your old code used "10 rows" -> PARTIAL render mode is the right match. */
    static lv_color_t buf_1[_TFT_WIDTH_ * 10];

    /* buf_size is in BYTES in v9 */
    lv_display_set_buffers(g_disp,
                           buf_1,
                           NULL,
                           sizeof(buf_1),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/* Initialize your display and the required peripherals. */
static void disp_init(void)
{
    display_configure();
}

/* Flush the content of the internal buffer to the display.
 * Call lv_display_flush_ready(display) when done. */
static void disp_flush(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    LV_UNUSED(display);

    /* Return if the area is outside the screen. */
    if(area->x2 < 0) return;
    if(area->y2 < 0) return;
    if(area->x1 > _TFT_WIDTH_  - 1) return;
    if(area->y1 > _TFT_HEIGHT_ - 1) return;

    /* Truncate the area to the screen. */
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > _TFT_WIDTH_  - 1 ? _TFT_WIDTH_  - 1 : area->x2;
    int32_t act_y2 = area->y2 > _TFT_HEIGHT_ - 1 ? _TFT_HEIGHT_ - 1 : area->y2;

    /* Widths in pixels */
    uint16_t full_w = (uint16_t)(area->x2 - area->x1 + 1);
    uint16_t act_w  = (uint16_t)(act_x2 - act_x1 + 1);

    /* LVGL v9 gives pixels as a byte pointer. For RGB565, treat it as uint16_t. */
    uint16_t * color_p = (uint16_t *)px_map;

    /* Orientation dependent. */
    set_column();
    set_page();

    /* Start frame. */
    frame_start(start_column, end_column, start_page, end_page);

    /* Flush data line-by-line */
    for(int32_t y = act_y1; y <= act_y2; y++) {
        write_array_data(color_p, act_w);
        color_p += full_w; /* advance by the originally rendered line width */
    }

    /* Deselect display. */
    display_deselect();

    /* IMPORTANT: tell LVGL flushing is finished. */
    lv_display_flush_ready(display);
}

