
#include "systick.h"
#include "core_header.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h" 
#include "event_groups.h"

/*---------------------------------------------COMMON FOR ALL-------------------------------------------------*/
extern void xPortSysTickHandler( void );

void vPortSetupTimerInterrupt( void )
{


    uint32_t ticks = GET_TICK_NUMBER_PER_CLOCK;

    uint32_t status = sysTickConfig( ticks );

    configASSERT( status == 0UL );


    sysTickInit( 15 );
}

TIMER_SYSTICK_HANDLER()
{    
    int bp1 = 0;


    /* Prosledi prekid FreeRTOS-u */
    xPortSysTickHandler();
}


/* Poziva se na SVAKI tick interrupt (configUSE_TICK_HOOK = 1) */
void vApplicationTickHook( void )
{
   
}


/* Poziva se svaki put kad Idle task dobije CPU (configUSE_IDLE_HOOK = 1) */
void vApplicationIdleHook( void )
{
   
}

/* Poziva se kad pvPortMalloc ne uspe (configUSE_MALLOC_FAILED_HOOK = 1) */
void vApplicationMallocFailedHook( void )
{
    taskDISABLE_INTERRUPTS();
    for( ;; )
    {
       
    }
}

/* Poziva se kad se detektuje stack overflow (configCHECK_FOR_STACK_OVERFLOW = 1 ili 2) */
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char *pcTaskName )
{
    ( void ) xTask;
    ( void ) pcTaskName;

    taskDISABLE_INTERRUPTS();
    for( ;; )
    {
       
    }
}
/*-------------------------------------------------------------------------------------------------------*/