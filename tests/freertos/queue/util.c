
#include "systick.h"
#include "core_header.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h" 

void vPortSetupTimerInterrupt( void )
{
    uint32_t ticks = GET_TICK_NUMBER_PER_CLOCK;

    uint32_t status = sysTickConfig( ticks );

    configASSERT( status == 0UL );

    sysTickInit( 15 );
}

TIMER_SYSTICK_HANDLER()
{    
    /* forward to FreeRTOS handler */
    xPortSysTickHandler();
}
