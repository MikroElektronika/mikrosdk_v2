/**
 * @file main.c
 * @brief Main function for ${PROJECT_NAME} TFT Designer Application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "vtft.h"
#include "gl.h"
#include "main_screen.h"
#include "touch_controller.h"

static gl_driver_t display_driver;
static tp_t tp;
static vtft_t vtft;
static tp_drv_t tp_interface;

void board_init()
{
    touch_controller_init(&display_driver, TFT_MAX_BACKLIGHT);
    // Initialize Graphic library.
    gl_set_driver(&display_driver);

    touch_controller_tp_init(&tp, &tp_interface);
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
}

/**
 * @brief Application task function.
 */
void application_task()
{
    vtft_process(&vtft);
}

/**
 * @brief Application main function.
 */
void main()
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();

    while (1)
    {
        application_task();
    }
}
