/**
 * @file lv_port_disp.c
 */
#include "display_lvgl.h"
#include "lvgl_common.h"
#include "lvgl.h"

static void disp_init(void);
static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

static lv_color_t buf_1[_TFT_WIDTH_ * 10];   /* 10 rows buffer */

void lv_port_disp_init(void)
{
    disp_init();

    /* Create display */
    lv_display_t * disp = lv_display_create(_TFT_WIDTH_, _TFT_HEIGHT_);

    /* Set draw buffers */
    lv_display_set_buffers(
        disp,
        buf_1,
        NULL,
        sizeof(buf_1),
        LV_DISPLAY_RENDER_MODE_PARTIAL
    );

    /* Set flush callback */
    lv_display_set_flush_cb(disp, disp_flush);
}

static void disp_init(void)
{
    display_configure();
}

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    /* Clip area to screen */
    if(area->x2 < 0 || area->y2 < 0 ||
       area->x1 > _TFT_WIDTH_ - 1 ||
       area->y1 > _TFT_HEIGHT_ - 1) {
        lv_display_flush_ready(disp);
        return;
    }

    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > _TFT_WIDTH_  - 1 ? _TFT_WIDTH_  - 1 : area->x2;
    int32_t act_y2 = area->y2 > _TFT_HEIGHT_ - 1 ? _TFT_HEIGHT_ - 1 : area->y2;

    uint16_t full_w = area->x2 - area->x1 + 1;
    uint16_t act_w  = act_x2 - act_x1 + 1;

    /* Convert pixel map to your color type */
    uint16_t * color_p = (uint16_t *)px_map;

    set_column();
    set_page();

    frame_start(start_column, end_column, start_page, end_page);

    for(int32_t y = act_y1; y <= act_y2; y++) {
        write_array_data(color_p, act_w);
        color_p += full_w;
    }

    display_deselect();
    
    lv_display_flush_ready(disp);
}
