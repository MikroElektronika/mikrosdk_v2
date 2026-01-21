#include "lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_%2
#define LV_ATTRIBUTE_IMG_%2
#endif

static const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_%2
uint8_t %1_map[] = {
%3
};

const lv_image_dsc_t %1 = {
    .header.magic = LV_IMAGE_HEADER_MAGIC,
    .header.cf = LV_COLOR_FORMAT_RGB565A8,
    .header.flags = 0,
    .header.w = %4,
    .header.h = %5,
    .header.stride = %6,              /* stride of RGB565 plane */
    .header.reserved_2 = 0,

    .data_size = (%6 * %5) + (%7 * %5), /* RGB565 plane + A8 plane */
    .data = %1_map,
    .reserved = NULL,
    .reserved_2 = NULL,
};
