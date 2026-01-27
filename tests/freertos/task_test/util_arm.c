    
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

/*
 * Cortex-M0, M23 and M33 ports already define SysTick_Handler in port.c.
 * For all other architectures, we provide it here and forward
 * to the FreeRTOS kernel handler.
 */
#if !defined(MSDK_PORT_PROVIDES_SYSTICK_HANDLER)
TIMER_SYSTICK_HANDLER()
{    
    /* forward to FreeRTOS handler */
    xPortSysTickHandler();
}
#endif
