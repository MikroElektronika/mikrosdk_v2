#include "main_screen.h"

lvgl_main_screen_ui_t lvgl_main_screen_ui;

void init_main_screen()
{
  init_main_screen_ui(&lvgl_main_screen_ui);  
}

void show_main_screen()
{
    lv_screen_load(lvgl_main_screen_ui.main_screen);
}
