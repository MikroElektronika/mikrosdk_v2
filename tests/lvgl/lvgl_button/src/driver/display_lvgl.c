/**
 * @file display_lvgl.c
 */
#include "display_lvgl.h"
#include "lvgl_common.h"

static void disp_init(void);
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display.
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing.
     *----------------------------*/
    static lv_disp_draw_buf_t draw_buf_dsc_1;
    static lv_color_t buf_1[_TFT_WIDTH_*10];                               /* A buffer for 10 rows. */
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, _TFT_WIDTH_*10);   /* Initialize the display buffer. */

    /*-----------------------------------
     * Register the display in LVGL.
     *----------------------------------*/
    static lv_disp_drv_t disp_drv;    /* Descriptor of a display driver. */
    lv_disp_drv_init(&disp_drv);      /* Basic initialization. */

    /* Set the resolution of the display. */
    disp_drv.hor_res = _TFT_WIDTH_;
    disp_drv.ver_res = _TFT_HEIGHT_;

    /* Used to copy the buffer's content to the display. */
    disp_drv.flush_cb = disp_flush;

    /* Set a display buffer. */
    disp_drv.draw_buf = &draw_buf_dsc_1;

    /* Finally register the driver. */
    lv_disp_drv_register(&disp_drv);
}

/* Initialize your display and the required peripherals. */
static void disp_init(void)
{
    display_configure();
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /* Return if the area is outside the screen. */
    if(area->x2 < 0) return;
    if(area->y2 < 0) return;
    if(area->x1 > _TFT_WIDTH_ - 1) return;
    if(area->y1 > _TFT_HEIGHT_ - 1) return;

    /* Truncate the area to the screen. */
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > _TFT_WIDTH_ - 1 ? _TFT_WIDTH_ - 1 : area->x2;
    int32_t act_y2 = area->y2 > _TFT_HEIGHT_ - 1 ? _TFT_HEIGHT_ - 1 : area->y2;

    /* Begin frame. */
    uint16_t full_w = area->x2 - area->x1 + 1;
    uint16_t act_w = act_x2 - act_x1 + 1;

    /* Orientation dependent. */
    set_column();
    set_page();

    /* Start frame. */
    frame_start(start_column, end_column, start_page, end_page);

    /* Flush data to data port pins. */
    int16_t i;
    for(i = act_y1; i <= act_y2; i++) {
        write_array_data((uint16_t *)&color_p->full, act_w);
        color_p += full_w;
    }

    /* Deselect display. */
    display_deselect();

    /* Must be called when buffer is sent to screen. */
    lv_disp_flush_ready(disp_drv);
}
