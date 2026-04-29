#include "lv_port_indev.h"
#include "lvgl_common.h"

static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);

lv_indev_t * indev_touchpad;

void process_tp(){
    tp_process(&tp);
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    touchpad_init();

    /* Register a touchpad input device. */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
}

/* Initialize your touchpad. */
static void touchpad_init(void)
{
    touch_controller_tp_init(&tp, &tp_interface);
}

/* Will be called by the library to read the touchpad. */
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    /* Save the pressed coordinates and the state. */
    if(touchpad_is_pressed()) {
        touchpad_get_xy(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PR;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    /* Set the last pressed coordinates. */
    data->point.x = last_x;
    data->point.y = last_y;
}

/* Return true is the touchpad is pressed. */
static bool touchpad_is_pressed(void)
{
    check_touchpad();
}

/* Get the x and y coordinates if the touchpad is pressed. */
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
{
    get_touch_coordinates(x,y);
}
