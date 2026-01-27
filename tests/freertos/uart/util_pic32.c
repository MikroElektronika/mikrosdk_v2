#include <xc.h>

/*
 * FreeRTOS tick setup for PIC32MZ using Timer1, configured via Cyclone's timer.h.
 *
 * IMPORTANT:
 * - Do NOT define your own Timer1 ISR ("_TIMER_1_HANDLER").
 *   The FreeRTOS PIC32MZ port installs its own Timer1 vector via port_asm.S.
 * - This file only configures Timer1 hardware; the ISR logic is FreeRTOS-owned.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "timer.h"

void vApplicationSetupTickTimerInterrupt( void )
{
    /* FreeRTOS expects interrupts to be disabled when this function is called.
     * We enforce that explicitly and keep them disabled on return.
     */
    __builtin_disable_interrupts();

    /* Configure Timer1 for configTICK_RATE_HZ ticks per second. */
    configASSERT( init_1ms_timer() == 1 );

    /* Ensure a clean start. */
    IFS0CLR = _IFS0_T1IF_MASK;

    /* Leave global interrupts disabled. */
    __builtin_disable_interrupts();
}

