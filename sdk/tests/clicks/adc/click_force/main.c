/*!
 * \file
 * \brief Force Click example
 *
 * # Description
 * This example showcases how to initialize and configure the logger and click modules and
 * read and display ADC voltage data read from the analog pin.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * This function initializes and configures the logger and click modules.
 *
 * ## Application Task
 * This function reads and displays ADC voltage data from the analog pin every second.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force.h"

// ------------------------------------------------------------------ VARIABLES

static force_t force;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    force_cfg_t cfg;

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

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force  click    \r\n" );
    log_printf( &logger, "--------------------\r\n\r\n" );

    //  Click initialization.

    force_cfg_setup( &cfg );
    FORCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force_init( &force, &cfg );
}

void application_task ( )
{
    force_data_t tmp;

    //  Task implementation.

    tmp = force_generic_read ( &force );
    log_printf( &logger, " * ADC value : %d \r\n", tmp );
    log_printf( &logger, "--------------------- \r\n" );
    Delay_ms( 1000 );
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
