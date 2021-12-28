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
static vtft_t vtft;

static touch_ic_def touch_ic;

void board_init()
{
    tft8_cfg_t tft_cfg;
    tp_cfg_t tp_cfg;
    touch_ic_cfg_def touch_ic_cfg;

    // Initialize TFT display board.
    TFT8_MAP_PINOUTS(tft_cfg);
    tft_cfg.board = &_TFT_BOARD_;
    tft8_init(&tft_cfg, &display_driver);
    tft8_set_backlight(TFT8_MAX_BACKLIGHT);

    // Initialize Graphic library.
    gl_set_driver(&display_driver);

    // Initialize Touch panel.
    #ifdef FT5xx6
    ft5xx6_cfg_setup( &touch_ic_cfg, &_TFT_TP_CONTROLLER_ );
    FT5XX6_MAP_PINS( touch_ic_cfg );
    ft5xx6_init( &touch_ic, &touch_ic_cfg, &tp_interface  );
    ft5xx6_default_cfg( &touch_ic );
    #elif defined(Stmpe811)
    stmpe811_cfg_setup( &touch_ic_cfg );
    STMPE811_MAP_PINS( touch_ic_cfg );
    stmpe811_init( &touch_ic, &touch_ic_cfg, &tp_interface  );
    stmpe811_default_cfg( &touch_ic );
    #elif defined(Tsc2003)
    tsc2003_cfg_setup( &touch_ic_cfg );
    TSC2003_MAP_PINS( touch_ic_cfg );
    tsc2003_init( &touch_ic, &touch_ic_cfg, &tp_interface  );
    tsc2003_default_cfg( &touch_ic );
    #endif
    //  TP API initialization.
    tp_cfg_setup( &tp_cfg );
    tp_cfg.start_pos = _TFT_TP_ROTATE_;
    tp_init( &tp, &tp_cfg, &tp_interface , &touch_ic );
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
    if ( !digital_in_read( &touch_ic.int_pin ) ) {
        #ifdef FT5xx6
        ft5xx6_process( &touch_ic );
        #elif defined(Stmpe811)
        stmpe811_process( &touch_ic );
        #elif defined(Tsc2003)
        tsc2003_process( &touch_ic );
        #endif
        tp_press_coordinates( &tp, &touch_ic.touch );
        gl_draw_point( touch_ic.touch.point[0].coord_x,
                       touch_ic.touch.point[0].coord_y );
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
