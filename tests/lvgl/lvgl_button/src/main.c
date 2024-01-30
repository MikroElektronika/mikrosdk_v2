#ifdef __GNUC__
#include "delays.h"
#endif

#include "display_lvgl.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "systick.h"

int main(void)
{
    lv_init();

    lv_port_disp_init();
    lv_port_indev_init();

    lv_obj_t* main_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main_screen, lv_color_make(255, 255, 255), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(main_screen, lv_color_make(255, 170, 255), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(main_screen, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_dither_mode(main_screen, LV_DITHER_ORDERED, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(main_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(main_screen, lv_color_make(0, 0, 0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(main_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* btn = lv_btn_create(main_screen);
    lv_obj_set_style_bg_color(btn, lv_color_make(128, 0, 0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn, lv_color_make(0, 128, 0), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_x(btn, 90);
    lv_obj_set_y(btn, 75);
    lv_obj_set_width(btn, 70);
    lv_obj_set_height(btn, 100);
    lv_scr_load(main_screen);

    // Configure SYSTICK to 1ms interrupt.
    if (!sysTickConfig(GET_TICK_NUMBER_PER_CLOCK)) {
        sysTickInit(15); // Maximum priority - level 15.
    } else {
        while(1);
    }

    while (1)
    {
        lv_task_handler();
        Delay_ms(5);
    }
}

static volatile uint32_t msCount = 0;
__attribute__ ((interrupt("IRQ"))) void SysTick_Handler(void) {
    msCount++;

    if (5 == msCount) {
        msCount = 0;
        lv_tick_inc(5);
        process_tp();
    }
}
