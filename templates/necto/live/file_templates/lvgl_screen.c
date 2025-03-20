#include "${SCREEN_NAME}.h"

lvgl_${SCREEN_NAME}_ui_t lvgl_${SCREEN_NAME}_ui;

void init_${SCREEN_NAME}()
{
  init_${SCREEN_NAME}_ui(&lvgl_${SCREEN_NAME}_ui);  
}

void show_${SCREEN_NAME}()
{
    lv_scr_load(lvgl_${SCREEN_NAME}_ui.${SCREEN_NAME});
}
