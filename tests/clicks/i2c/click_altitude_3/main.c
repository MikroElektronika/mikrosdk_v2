/*!
 * \file
 * \brief Altitude3 Click example
 *
 * # Description
 * This application enables high-resolution barometric pressure measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C interface and performs a SW Reset of the device.
 *
 * ## Application Task
 * Selects the desired measurement mode and data reading order, and after that
 * calculates the temperature, pressure and altitude data to standard units and shows results to uart terminal.
 *
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "altitude3.h"

// ------------------------------------------------------------------ VARIABLES

static altitude3_t altitude3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude3_cfg_t cfg;

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

    altitude3_cfg_setup( &cfg );
    ALTITUDE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude3_init( &altitude3, &cfg );

    altitude3_default_cfg ( &altitude3 );

    log_printf( &logger, "** Altitude 3 click is initialized **\r\n\r\n" );
}

void application_task ( void )
{
    uint8_t response;

    response = altitude3_measurement_mode( &altitude3, ALTITUDE3_NORMAL_T_FIRST );

    Delay_ms( 100 );

    response = altitude3_get_data( &altitude3, response );

    if ( response != ALTITUDE3_ERROR )
    {
        log_printf( &logger, "Temperature is : %d C\r\n", ( int16_t ) altitude3.sens_data.temperature );

        log_printf( &logger, "Pressure is : %u  mbar[hPa]\r\n", ( uint16_t ) altitude3.sens_data.pressure );

        log_printf( &logger, "Altitude is : %d m\r\n\r\n", ( int16_t ) altitude3.sens_data.altitude );

        Delay_ms( 400 );
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
