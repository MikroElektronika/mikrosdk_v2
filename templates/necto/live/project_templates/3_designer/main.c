/**
 * @file main.c
 * @brief Main source file for the ${PROJECT_NAME} TFT Designer application.
 *
 * This example demonstrates usage of the Visual TFT (VTFT) and
 * Graphic Library (GL) for creating and running GUI applications
 * on TFT displays with touch support.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#include "vtft.h"
#include "gl.h"
#include "main_screen.h"
#include "touch_controller.h"

static gl_driver_t display_driver; /**< Graphic library display driver. */
static tp_t tp;                    /**< Touch panel driver instance. */
static vtft_t vtft;                /**< VTFT (Visual TFT) application context. */
static tp_drv_t tp_interface;      /**< Touch controller interface. */

/**
 * @brief Initializes board peripherals required for display and touch.
 */
void board_init()
{
    touch_controller_init(&display_driver, TFT_MAX_BACKLIGHT);

    // Initialize the Graphic Library and register the display driver.
    gl_set_driver(&display_driver);

    // Initialize the touch controller and interface.
    touch_controller_tp_init(&tp, &tp_interface);
}

/**
 * @brief Initializes the Visual TFT (VTFT) environment.
 *
 * Configures and initializes the GUI environment using the
 * Visual TFT library and displays the main screen.
 */
void application_init()
{
    board_init();

    // Initialize VTFT and show the default screen.
    vtft_init(&vtft, &tp);
    main_screen_show(&vtft);
}

/**
 * @brief Main application loop.
 *
 * Handles continuous GUI updates and touch input processing.
 */
void application_task()
{
    vtft_process(&vtft);
}

/**
 * @brief Application entry point.
 *
 * Initializes the MCU, peripherals, and starts the VTFT application loop.
 * Do not remove the preinit() call — it ensures proper clock configuration.
 */
void main()
{
    /* Do not remove this line — it ensures correct MCU initialization. */
#ifdef PREINIT_SUPPORTED
    preinit();
#endif

    application_init();

    while (1)
    {
        application_task();
    }
}
