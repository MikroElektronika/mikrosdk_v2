#include "lv_port_indev.h"
#include "lvgl_common.h"

/* LVGL v9: read_cb signature changed, and lv_indev_drv_t is removed */
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

    /* LVGL v9+: create indev and configure it (no lv_indev_drv_t anymore) */
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);

    /*
     * If you have multiple displays, ensure the correct display is default
     * before creating the indev, or explicitly bind it:
     * lv_indev_set_display(indev_touchpad, your_display);
     */
}

/* Initialize your touchpad. */
static void touchpad_init(void)
{
    touch_controller_tp_init(&tp, &tp_interface);
}

/* Will be called by LVGL to read the touchpad. */
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

/* Return true if the touchpad is pressed. */
static bool touchpad_is_pressed(void)
{
    /* Your original code missed the return statement. */
    check_touchpad();
}

/* Get the x and y coordinates if the touchpad is pressed. */
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    get_touch_coordinates(x, y);
}

