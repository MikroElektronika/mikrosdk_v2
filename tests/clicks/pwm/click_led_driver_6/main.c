/*!
 * \file
 * \brief Leddriver6 Click example
 *
 * # Description
 * This application designed to be used in tunable Smart Connected Lighting applications.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and PWM driver for the LED driver 6 control.
 *
 * ## Application Task
 * Shows the best way how the LED driver 6 click board can be controlled by using
 * functions from this click driver.
 *
 * \author Nemanja Medakovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver6.h"

static leddriver6_t leddriver6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;

    /**
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX
     * are defined as HAL_PIN_NC, you will
     * need to define them manually for log to work.
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init... ----" );

    leddriver6_cfg_t leddriver6_cfg;

    //  Click initialization.

    leddriver6_cfg_setup( &leddriver6_cfg );
    LEDDRIVER6_MAP_MIKROBUS( leddriver6_cfg, MIKROBUS_1 );

    if ( leddriver6_init( &leddriver6, &leddriver6_cfg ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );

    if ( leddriver6_pwm_start( &leddriver6 ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- PWM can't be started. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- PWM is started. ----" );
}

void application_task ( void )
{
    log_info( &logger, "---- PWM ratio increasing. ----" );

    for ( float duty_ratio = 0.1; duty_ratio <= 1; duty_ratio += 0.1 )
    {
        leddriver6_set_duty_cycle( &leddriver6, duty_ratio );

        Delay_ms( 1000 );
    }

    log_info( &logger, "---- PWM ratio decreasing. ----" );

    for ( float duty_ratio = 0.9; duty_ratio >= 0.2; duty_ratio -= 0.1 )
    {
        leddriver6_set_duty_cycle( &leddriver6, duty_ratio );

        Delay_ms( 1000 );
    }

    float leddriver6_pg_vol;

    if ( leddriver6_get_pg_voltage( &leddriver6, &leddriver6_pg_vol ) == LEDDRIVER6_OK )
    {
        log_printf( &logger, "---- Power Good Voltage [V] : %.2f ----\r\n", leddriver6_pg_vol );

        Delay_ms( 1000 );
    }

    if ( !leddriver6_get_interrupt_state( &leddriver6 ) )
    {
        log_info( &logger, "---- Fault conditions report! ----" );

        Delay_ms( 1000 );
    }
}

int main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
