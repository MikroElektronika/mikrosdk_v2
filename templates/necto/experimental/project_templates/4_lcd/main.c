/**
 * @file main.c
 * @brief Main source file for the ${PROJECT_NAME} application.
 *
 * This example demonstrates basic usage of the mikroSDK LCD library
 * for displaying text and controlling the cursor on a 2x16 LCD.
 */

#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
#if MikroCCoreVersion >= 1
#include "delays.h"
#endif
#endif

#include "board.h"
#include "lcd.h"
#include "drv_digital_out.h"
#include "mikrosdk_version.h"

#if mikroSDK_GET_VERSION < 21000ul
#error "SDK version must be 2.10.0 or higher."
#endif

static lcd_config_t lcd_cfg;  /**< LCD configuration structure. */
static lcd_handle_t lcd;      /**< LCD handle instance. */

/**
 * @brief Displays a simple "Hello World" message on the LCD.
 */
static void lcd_demo_hello_world(void)
{
    Delay_ms(1000);
    lcd_clear(lcd);
    lcd_write_text(lcd, "Hello World", LCD_ROW_1);
    Delay_ms(1000);
}

/**
 * @brief Demonstrates turning the LCD cursor ON and OFF.
 */
static void lcd_demo_cursor_on_off(void)
{
    lcd_cursor_off(lcd);
    Delay_ms(1000);
    lcd_cursor_on(lcd);
    Delay_ms(1000);
    lcd_cursor_off(lcd);
    Delay_ms(1000);
    lcd_cursor_on(lcd);
    Delay_ms(1000);
}

/**
 * @brief Initializes the LCD module and runs demo functions.
 *
 * Configures LCD pins, initializes the display, and executes
 * basic text and cursor control demonstrations.
 */
void application_init()
{
    lcd_configure_default(&lcd_cfg);
    LCD_MAP_PINS(lcd_cfg);

    // Increase delay between LCD data writes.
    lcd_cfg.waitBetweenWrites = 0xFFFF;

    if (LCD_ERROR == lcd_configure(&lcd, &lcd_cfg))
        while (1);

    /** 
     * Initialize the LCD using the HD44780 driver sequence.
     */
    lcd_init(lcd, hd44780_lcd_init);

    lcd_demo_hello_world();
    Delay_ms(1000);
    lcd_clear(lcd);
    lcd_demo_cursor_on_off();
}

/**
 * @brief Main application loop.
 *
 * Add custom application logic here. This function is
 * called repeatedly after initialization.
 */
void application_task()
{
    /* Add your application code here. */
}

/**
 * @brief Application entry point.
 *
 * Initializes the MCU, peripherals, and runs the LCD demonstration.
 * Do not remove the preinit() call, as it ensures proper MCU clock setup.
 */
int main(void)
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

    return 0;
}
