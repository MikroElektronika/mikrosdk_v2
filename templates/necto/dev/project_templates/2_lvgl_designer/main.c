/**
 * @file main.c
 * @brief Main function for ${PROJECT_NAME} LVGL Designer Application.
 */

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef __GNUC__
#include "delays.h"
#endif

#include "display_lvgl.h"
#include "lv_port_indev.h"
#include "1ms_Timer.h"
#include "screens.h"

void board_init()
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    // Configure 1ms interrupt.
    timerInit();
}

void application_init()
{
    //Initialize driver
    board_init();
    //Initialize all available screens
    init_screens();
    //Show main screen. If you want any other screen to show call its show function
    show_main_screen();
}

int main(void)
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    //Call all initialization methods
    application_init();

    /////////////////////////////LVGL specific timing routine (DO NOT DELETE)/////////////////////////
    while (1)
    {
        lv_task_handler();
        Delay_ms(5);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
}

static volatile uint32_t msCount = 0;
INTERRUPT_ROUTINE
{
    msCount++;

    if (5 == msCount) {
        msCount = 0;
        lv_tick_inc(5);
        process_tp();
    }
    CLEAR_FLAG;
}
