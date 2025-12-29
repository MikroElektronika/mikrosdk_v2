/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

// use preemptive round robin scheduling algorithm
#define configUSE_PREEMPTION			1

/*
 * this needs to be set to the frequency that drives the timer which is used for generating tick interrupts which in this case 
   is a mcu frequency.
 * since ARM Cortex-M architecture has a build in internal timer(system timer) for this purpose,its used by default and
   configures reload value proprely in port.c using the configCPU_CLOCK_HZ and configTICK_RATE_HZ values
*/
#define configCPU_CLOCK_HZ				( ( unsigned long ) 400000000 )

// defines how many tick interrupts occur in one second, calculated based on configCPU_CLOCK_HZ value
#define configTICK_RATE_HZ				( 1000 )

// max nubmer of possible priorities for tasks
#define configMAX_PRIORITIES			( 8 )

/*
 * Sets the total size of the FreeRTOS heap, in BYTES
 * this applies only if heap_1, heap_2 or heap_4 are included in the build.
*/
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 64 * 1024 ) )

// this sets the maximum length (in characters) of a task
#define configMAX_TASK_NAME_LEN			( 10 )

/*
  * FreeRTOS uses TickType_t to measure time in 'ticks' which is basically a number 
    of times a tick interrupt has been executed.
  * this sets TickType_t as a uint32_t => max number of tick is 4,294,967,295
  * if tick was set to execute every 1 ms,this would mean that max delay would be in years which is more than enough.
*/
#define configTICK_TYPE_WIDTH_IN_BITS   TICK_TYPE_WIDTH_32_BITS

/*
  * setting this to 1 allows the idle task(lowest priority task which is executing when no other task is in 'ready' state)
    to be interrupted when other tasks enters 'ready' state even if the time slice given to the idle tasks hasnt
    run out yet.
*/
#define configIDLE_SHOULD_YIELD			1

/*
  * set the following constants to 1 to include the named feature in the build
    or 0 to exclude them
*/
#define configUSE_MUTEXES				1
#define configUSE_TASK_NOTIFICATIONS    1
#define configUSE_COUNTING_SEMAPHORES   1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_QUEUE_SETS            0
#define configUSE_APPLICATION_TASK_TAG  0

/*
  * by setting these hooks to 1 freeRTOS is told not to use default callbacks but instead
    we will provide them.
  * handler names must be the same as freeRTOS expects :
    void vApplicationIdleHook( void )
    void vApplicationTickHook( void )
    void vApplicationMallocFailedHook( void )
*/
#define configUSE_IDLE_HOOK				1
#define configUSE_TICK_HOOK				1
#define configUSE_MALLOC_FAILED_HOOK	1

/*
  * Set configCHECK_FOR_STACK_OVERFLOW to 2 for FreeRTOS to check for a
    stack overflow at the time of a context switch.
*/
#define configCHECK_FOR_STACK_OVERFLOW  2 

/*
  * this maps FreeRTOS port handlers to the CMSIS standard names from startup file
  * now FreeRTOS handlers are mapped directly to the corresponding IVT vector
*/
#define vPortSVCHandler      SVC_Handler
#define xPortPendSVHandler   PendSV_Handler
//#define xPortSysTickHandler  SysTick_Handler      /////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/* 
   * minimal stack size FreeRTOS can use when creating tasks.
   * this is defined in words, not bytes.
   * the actual number of bytes used depends on the CPU architecture.
   * stack size (in bytes) = configMINIMAL_STACK_SIZE * sizeof( StackType_t ) 
*/
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 128 )

#define configPRIO_BITS        4

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5
/*
  * following aplies only for ARM CORTEX-M:
  * when entering critical sections, FreeRTOS wrties this value to the BASEPRI register.
  * all interrupts that have lower hardware priority(numerically higher) than configMAX_SYSCALL_INTERRUPT_PRIORITY are masked.
  * => every ISR that calls FreeRTOS API MUST have priority numerically higher than configMAX_SYSCALL_INTERRUPT_PRIORITY.
  * optimal value for this depends of the number of priority bites used by the MCU.
*/
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )  

#define configKERNEL_INTERRUPT_PRIORITY     ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define configMAX_API_CALL_INTERRUPT_PRIORITY  configMAX_SYSCALL_INTERRUPT_PRIORITY

/* Software timer definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 1 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

// /* The MSP430X port uses a callback function to configure its tick interrupt.
// This allows the application to choose the tick interrupt source.
// configTICK_VECTOR must also be set in FreeRTOSConfig.h to the correct interrupt
// vector for the chosen tick interrupt source.  This implementation of
// vApplicationSetupTimerInterrupt() generates the tick from timer A0, so in this
// case configTICK_VECTOR is set to TIMER0_A0_VECTOR. */
// #define configTICK_VECTOR				TIMER0_A0_VECTOR

#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); __asm volatile ( "bkpt 0" ); for( ;; ); }

/* Redefine pdMS_TO_TICKS so it doesn't overflow */
#define pdMS_TO_TICKS( xTimeInMs ) ( ( TickType_t ) ( ( ( unsigned long ) ( xTimeInMs ) * configTICK_RATE_HZ ) / 1000 ) )

#endif /* FREERTOS_CONFIG_H */
