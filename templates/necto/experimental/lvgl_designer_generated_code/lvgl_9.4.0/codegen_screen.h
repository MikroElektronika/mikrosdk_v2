#ifndef %1_H
#define %1_H

#include "lvgl.h"

typedef struct {
	
%2

} lvgl_%1_ui_t;

%3

%4

extern lvgl_%1_ui_t lvgl_%1_ui;

void init_%1_ui(lvgl_%1_ui_t* ui);


#endif
