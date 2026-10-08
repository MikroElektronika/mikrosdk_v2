#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "delays.h"
#include "lvgl.h"
#include "display_lvgl.h"
LV_IMAGE_DECLARE(mikrosdk_logo_mali);

static lv_obj_t *counter_label;

static void update_cb(lv_timer_t *timer)
{
    static uint32_t seconds = 0;

    (void)timer;
    seconds++;

    lv_label_set_text_fmt(counter_label, "Seconds: %d", (int)seconds);
}

int main(void)
{

    lv_init();
    lv_port_disp_init();
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xFFC0CB), 0);
    lv_obj_remove_flag(lv_screen_active(), LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = lv_label_create(lv_screen_active());
    lv_label_set_text(title, "ST7735S + LVGL");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 4);

    lv_obj_t *card = lv_obj_create(lv_screen_active());
    lv_obj_set_size(card, 116, 34);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, 24);
    lv_obj_set_style_pad_all(card, 0, 0);
    lv_obj_set_style_radius(card, 16, 0);
    lv_obj_set_style_bg_color(card, lv_color_white(), 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0xFF1493), 0);
    lv_obj_set_style_border_width(card, 3, 0);
    lv_obj_remove_flag(card, LV_OBJ_FLAG_SCROLLABLE);

    counter_label = lv_label_create(card);
    lv_label_set_text(counter_label, "Seconds: 0");
    lv_obj_center(counter_label);

    lv_timer_create(update_cb, 1000, NULL);

    lv_obj_t *logo = lv_image_create(lv_screen_active());
    lv_image_set_src(logo, &mikrosdk_logo_mali);
    lv_image_set_scale(logo, 150);
    lv_obj_align(logo, LV_ALIGN_BOTTOM_MID, 0, 16);

    while (1)
    {
        lv_timer_handler();
        Delay_ms(5);
        lv_tick_inc(5);
    }

    return 0;
}