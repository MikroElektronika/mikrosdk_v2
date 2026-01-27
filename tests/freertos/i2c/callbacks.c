#include "FreeRTOS.h"
#include "task.h"
#include "timers.h" 

/* this hook function is called from a systick ISR (configUSE_TICK_HOOK = 1) */
void vApplicationTickHook( void )
{
   /* if anything is implemented here it must be as short as possible, systick ISR needs to be quick */
}

/* this hook function is called from an Idle task (configUSE_TICK_HOOK = 1) */
void vApplicationIdleHook( void )
{
   /* put MCU into low power mode for example */
}

/* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues or
    semaphores. */
void vApplicationMallocFailedHook( void )
{
    /* mask global IRQ interrupts */
    taskDISABLE_INTERRUPTS();
    for( ;; )
    {
       
    }
}

/* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char *pcTaskName )
{
    ( void ) xTask;
    ( void ) pcTaskName;
    
    /* mask global IRQ interrupts */
    taskDISABLE_INTERRUPTS();
    for( ;; )
    {
       
    }
}
