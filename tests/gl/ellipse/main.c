#include "tft8.h"
#include "board.h"
#include "gl.h"

/* === APPLICATION CONFIGURATION === */

/*
 * TFT configuration.
 */

#define TEST_GL_ELLIPSE_TFT_MAP_PINOUTS TFT8_MAP_PINOUTS_16BIT
#define TEST_GL_ELLIPSE_TFT_BOARD       TFT_BOARD_4_CAPACITIVE

/*
 * Color configuration.
 */

#define TEST_GL_ELLIPSE_COLOR_CLEAR         GL_BLUE
#define TEST_GL_ELLIPSE_COLOR_PEN           GL_RED
#define TEST_GL_ELLIPSE_COLOR_BRUSH_STYLE   GL_BRUSH_STYLE_FILL
#define TEST_GL_ELLIPSE_COLOR_BRUSH         GL_GREEN
#define TEST_GL_ELLIPSE_COLOR_BRUSH_FROM    GL_DARK_GREEN
#define TEST_GL_ELLIPSE_COLOR_BRUSH_TO      GL_LIGHT_GREEN

/*
 * Size configuration - in pixels.
 * NOTE: You can make a circle by setting the last two macros to the same value.
 */

#define TEST_GL_ELLIPSE_SIZE_PEN_INNER      5
#define TEST_GL_ELLIPSE_SIZE_PEN_OUTER      10
#define TEST_GL_ELLIPSE_SIZE_BRUSH_WIDTH    400 // NOTE: Must be even.
#define TEST_GL_ELLIPSE_SIZE_BRUSH_HEIGHT   200 // NOTE: Must be even.

/*
 * Center configuration - in screen percentage.
 */

#define TEST_GL_ELLIPSE_CENTER_X  0.5f
#define TEST_GL_ELLIPSE_CENTER_Y  0.5f

/* === APPLICATION CODE === */

static gl_driver_t gl_driver;   // Graphic library driver.
static tft8_cfg_t tft_cfg;      // TFT configuration.

void main() {
    // Initialize the GL driver.
    TEST_GL_ELLIPSE_TFT_MAP_PINOUTS(tft_cfg);
    tft_cfg.board = &TEST_GL_ELLIPSE_TFT_BOARD;
    tft8_init(&tft_cfg, &gl_driver);

    // Prepare display for drawing.
    gl_set_driver(&gl_driver);
    gl_clear(TEST_GL_ELLIPSE_COLOR_CLEAR);

    // Set pen and brush.
    gl_set_inner_pen(TEST_GL_ELLIPSE_SIZE_PEN_INNER);
    gl_set_outer_pen(TEST_GL_ELLIPSE_SIZE_PEN_OUTER);
    gl_set_pen_color(TEST_GL_ELLIPSE_COLOR_PEN);
    gl_set_brush_style(TEST_GL_ELLIPSE_COLOR_BRUSH_STYLE);
#   if (TEST_GL_ELLIPSE_BRUSH_STYLE == GL_BRUSH_STYLE_FILL)
        gl_set_brush_color(TEST_GL_ELLIPSE_COLOR_BRUSH);
#   else
        gl_set_brush_color_from(TEST_GL_ELLIPSE_COLOR_BRUSH_FROM);
        gl_set_brush_color_to(TEST_GL_ELLIPSE_COLOR_BRUSH_TO);
#   endif

    // Finnally draw the ellipse, according to the application configuration.
    gl_draw_ellipse(gl_get_screen_width() * TEST_GL_ELLIPSE_CENTER_X,
                    gl_get_screen_height() * TEST_GL_ELLIPSE_CENTER_Y,
                    TEST_GL_ELLIPSE_SIZE_BRUSH_WIDTH * 0.5f,
                    TEST_GL_ELLIPSE_SIZE_BRUSH_HEIGHT * 0.5f);
}
