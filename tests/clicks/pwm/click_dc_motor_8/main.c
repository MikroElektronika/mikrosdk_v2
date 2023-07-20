/*!
 * \file
 * \brief DcMotor8 Click example
 *
 * # Description
 * This click can drive simple DC motors with brushes, providing them with a significant amount
 * of current and voltage up to 40V. The click has one control input, that uses the PWM signal
 * from the host MCU. It uses the half-bridge topology to regulate the speed of the motor
 * rotation, employs advanced dead-time circuitry that monitors the output stage, providing
 * maximum switching efficiency and features an advanced technique to avoid shoot-through
 * currents.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the click board.
 *
 * ## Application Task
 * Demonstrates the use of DC Motor 8 click board by increasing and decreasing the motor speed.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor8.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor8_t dcmotor8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor8_cfg_setup( &cfg );
    DCMOTOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor8_init( &dcmotor8, &cfg );

    dcmotor8_enable ( &dcmotor8, DCMOTOR8_ENABLE );
    dcmotor8_pwm_start( &dcmotor8 );
}

void application_task ( void )
{
    log_printf( &logger,"\r\nIncreasing the motor RPM...\r\n" );

    for ( float duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        dcmotor8_set_duty_cycle ( &dcmotor8, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 200 );
    }

    log_printf( &logger,"\r\nSlowing down...\r\n" );

    for ( float duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        dcmotor8_set_duty_cycle ( &dcmotor8, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 200 );
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
