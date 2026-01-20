/**
 * @file lv_port_indev.c
 */
#include "lv_port_indev.h"
#include "lvgl_common.h"
#include "lvgl.h"

static void touchpad_init(void);
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

lv_indev_t * indev_touchpad;

void process_tp(void)
{
    tp_process(&tp);
}

void lv_port_indev_init(void)
{
    touchpad_init();

    indev_touchpad = lv_indev_create();

    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);

    lv_indev_set_read_cb(indev_touchpad, touchpad_read);
}


static void touchpad_init(void)
{
    touch_controller_tp_init(&tp, &tp_interface);
}

static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    LV_UNUSED(indev);

    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    if(touchpad_is_pressed()) {
        touchpad_get_xy(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    data->point.x = last_x;
    data->point.y = last_y;
}

static bool touchpad_is_pressed(void)
{
    check_touchpad();
}


static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    get_touch_coordinates(x, y);
}
