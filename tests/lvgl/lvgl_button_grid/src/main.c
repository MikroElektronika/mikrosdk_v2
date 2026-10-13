// TODO
// Test is done with IPS Display Clickboard with ST7789 driver.
// TODO
// Make sure output labels matches colors, shapes and screen orientation.  

#ifdef __GNUC__
#include "delays.h"
#endif

#include "display_lvgl.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "systick.h"

static void event_cb(lv_event_t * e) {
    lv_obj_t * obj = lv_event_get_target_obj(e);
    lv_draw_task_t * draw_task = lv_event_get_draw_task(e);
    lv_draw_dsc_base_t * base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

    if(base_dsc->part == LV_PART_ITEMS) {
        bool pressed = false;
        if(lv_buttonmatrix_get_selected_button(obj) == base_dsc->id1 && lv_obj_has_state(obj, LV_STATE_PRESSED)) {
            pressed = true;
        }

        /* Button 0: Red */
        if(base_dsc->id1 == 0) {
            lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
            if(fill_draw_dsc) {
                if(pressed) fill_draw_dsc->color = lv_palette_darken(LV_PALETTE_RED, 3);
                else fill_draw_dsc->color = lv_palette_main(LV_PALETTE_RED);
            }
        }
        /* Button 1: Green (pill) */
        else if(base_dsc->id1 == 1) {
            lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
            if(fill_draw_dsc) {
                fill_draw_dsc->radius = LV_RADIUS_CIRCLE;
                if(pressed) fill_draw_dsc->color = lv_palette_darken(LV_PALETTE_GREEN, 3);
                else fill_draw_dsc->color = lv_palette_main(LV_PALETTE_GREEN);
            }
            lv_draw_box_shadow_dsc_t * box_shadow_draw_dsc = lv_draw_task_get_box_shadow_dsc(draw_task);
            if(box_shadow_draw_dsc) {
                box_shadow_draw_dsc->radius = LV_RADIUS_CIRCLE;
            }
        }

        /* Button 2: Blue (No rounded corners) */
        else if(base_dsc->id1 == 2) {
            lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
            if(fill_draw_dsc) {
                fill_draw_dsc->radius = 0;
                if(pressed) fill_draw_dsc->color = lv_palette_darken(LV_PALETTE_BLUE, 3);
                else fill_draw_dsc->color = lv_palette_main(LV_PALETTE_BLUE);
            }
            lv_draw_box_shadow_dsc_t * box_shadow_draw_dsc = lv_draw_task_get_box_shadow_dsc(draw_task);
            if(box_shadow_draw_dsc) {
                box_shadow_draw_dsc->radius = 0;
            }
        }

        /* Button 3: Yellow (Rounded corners)*/
        else if(base_dsc->id1 == 3) {
            lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
            if(fill_draw_dsc) {
                fill_draw_dsc->radius = 25;
                if(pressed) fill_draw_dsc->color = lv_palette_darken(LV_PALETTE_YELLOW, 3);
                else fill_draw_dsc->color = lv_palette_main(LV_PALETTE_YELLOW);
            }
            lv_draw_box_shadow_dsc_t * box_shadow_draw_dsc = lv_draw_task_get_box_shadow_dsc(draw_task);
            if(box_shadow_draw_dsc) {
                box_shadow_draw_dsc->radius = 25;
            }
            lv_draw_label_dsc_t * label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
            if(label_draw_dsc) {
                label_draw_dsc->color = lv_color_black();
            }
        }
    }
}

int main(void)
{
    lv_init();

    lv_port_disp_init();
    lv_port_indev_init();

    /* Define 4 buttons in a 2x2 layout */
    static const char * btnm_map[] = {
        "Red", "Green", "\n",
        "Blue", "Yellow", ""
    };

    lv_obj_t * btnm = lv_buttonmatrix_create(lv_screen_active());
    lv_buttonmatrix_set_map(btnm, btnm_map);

    lv_obj_set_size(btnm, lv_pct(100), lv_pct(100)); 
    lv_obj_set_style_pad_all(btnm, 10, LV_PART_MAIN);
    lv_obj_set_style_border_width(btnm, 0, LV_PART_MAIN);
    lv_obj_set_style_outline_width(btnm, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(btnm, 4, LV_PART_MAIN);
    lv_obj_set_style_pad_column(btnm, 4, LV_PART_MAIN);
    lv_obj_add_event_cb(btnm, event_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_flag(btnm, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

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
