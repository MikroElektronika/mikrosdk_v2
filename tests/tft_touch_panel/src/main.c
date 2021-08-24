/**
 * @file main.c
 * @brief Main function for mikromedia_example TFT Board Capacitive Application.
 * 
 * NOTE Open `tft_connections.h` file and select desired TFT size if
 *      size is not previously defined in toolchain flags.
 *      Toolchain supported flags:
 *          1. NAME=MSDK_TEST_DISPLAY_SIZE, VALUE=3
 *          2. NAME=MSDK_TEST_DISPLAY_SIZE, VALUE=4
 *          3. NAME=MSDK_TEST_DISPLAY_SIZE, VALUE=5
 *          4. NAME=MSDK_TEST_DISPLAY_SIZE, VALUE=7
 * WARNING If no display size is selected macros will be expanded
 *         to void NULL ptr structures.
 */

#include "tft_connections.h"

static gl_driver_t display_driver;
static tp_drv_t tp_interface;
static tp_t tp;
static ft5xx6_t ft5xx6;
static vtft_t vtft;

void board_init()
{
    tft8_cfg_t tft_cfg;
    tp_cfg_t tp_cfg;
    ft5xx6_cfg_t ft5xx6_cfg;

    // Initialize TFT display board.
    TFT8_MAP_PINOUTS(tft_cfg);
    tft_cfg.board = &_TFT_BOARD_;
    tft8_init(&tft_cfg, &display_driver);
    tft8_set_backlight(TFT8_MAX_BACKLIGHT);

    // Initialize Graphic library.
    gl_set_driver(&display_driver);

    // Initialize Touch panel.
    ft5xx6_cfg_setup( &ft5xx6_cfg, &_TFT_TP_CONTROLLER_ );
    FT5XX6_MAP_PINS( ft5xx6_cfg );
    ft5xx6_init( &ft5xx6, &ft5xx6_cfg, &tp_interface  );
    ft5xx6_default_cfg( &ft5xx6 );

    //  TP API initialization.
    tp_cfg_setup( &tp_cfg );
    tp_cfg.width  = _TFT_DISP_WIDTH_;
    tp_cfg.height = _TFT_DISP_HEIGHT_;
    tp_cfg.start_pos = _TFT_TP_ROTATE_;
    tp_init( &tp, &tp_cfg, &tp_interface , &ft5xx6 );
}

/**
 * @brief Application initialization function.
 */
void application_init()
{
    board_init();

    // Initialize VTFT library.
    vtft_init(&vtft, &tp);
    main_screen_show(&vtft);
    Delay_1sec();
    Delay_1sec();
    gl_clear(GL_BLACK);
}

/**
 * @brief Application task function.
 */
void application_task()
{
    if ( !digital_in_read( &ft5xx6.int_pin ) ) {
        ft5xx6_process( &ft5xx6 );
        tp_press_coordinates( &tp, &ft5xx6.touch );
        gl_draw_point( ft5xx6.touch.point[0].coord_x,
                       ft5xx6.touch.point[0].coord_y );
    }
}

/**
 * @brief Application's main function.
 */
void main()
{
    application_init();

    while (1)
    {
        application_task();
    }
}
