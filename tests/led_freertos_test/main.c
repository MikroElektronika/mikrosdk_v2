
#include "board.h"

#include "drv_digital_out.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "systick.h"
#include <sys/time.h>

// void Systick_Handler(){
//     xPortSysTickHandler();
// }
// __attribute__ ((interrupt("IRQ"))) void PendSV_Handler(){
//     xPortPendSVHandler();
// }
// __attribute__ ((interrupt("IRQ"))) void SVC_Handler(){
//     vPortSVCHandler();
// }
static digital_out_t pinA;
static digital_out_t pinB;
static digital_out_t pinC;
static digital_out_t pinD;
static digital_out_t pinE;
static digital_out_t pinG;
static digital_out_t pinF;
static void foo(void* param)
{
    while(1){
        digital_out_toggle(&pinA);
        vTaskDelay(100);
        digital_out_toggle(&pinA);
        vTaskDelay(100);
        
        //printf_me("Task ");
        
        // for(int i=0; i<1000000; i++){

        // }
    }
}
static void foo2(void* param)
{
    while(1){
        digital_out_toggle(&pinF);
        //printf_me("Task ");
        vTaskDelay(100);
        // for(int i=0; i<10000000; i++){

        // }
    }
}
// void vApplicationIdleHook(void)
// {   
//     digital_out_high(&pinA);
// }
 void vApplicationMallocFailedHook( void ){
     digital_out_high(&pinG);
 }
__attribute__ ((interrupt("IRQ"))) void UsageFault_Handler(){
    digital_out_high(&pinG);
}
__attribute__ ((interrupt("IRQ"))) void HardFault_Handler(void) {
    __asm volatile (
        "TST lr, #4 \n"
        "ITE EQ \n"
        "MRSEQ r0, MSP \n"
        "MRSNE r0, PSP \n"
        "B hard_fault_handler_c \n"
    );
}

void hard_fault_handler_c(uint32_t *stack) {
    uint32_t stacked_r0 = stack[0];
    uint32_t stacked_r1 = stack[1];
    uint32_t stacked_r2 = stack[2];
    uint32_t stacked_r3 = stack[3];
    uint32_t stacked_r12 = stack[4];
    uint32_t stacked_lr = stack[5];
    uint32_t stacked_pc = stack[6];
    uint32_t stacked_psr = stack[7];

    // Log or print the fault information
    printf_me("Hard fault at PC: 0x%08X\n", stacked_pc);
    printf_me("LR:  0x%08X\n", stacked_lr);
    printf_me("R0: 0x%08X\n", stacked_r0);
    printf_me("R1: 0x%08X\n", stacked_r1);
    printf_me("R2: 0x%08X\n", stacked_r2);
    printf_me("R3: 0x%08X\n", stacked_r3);
    printf_me("R12: 0x%08X\n", stacked_r12);
    printf_me("PSR: 0x%08X\n", stacked_psr);

    // Enter an infinite loop to halt the system
    while (1);
}
static uint32_t msCount = 0;
uint32_t timeout = 0;
extern volatile uint32_t systemTicks=0;


// __attribute__ ((interrupt("IRQ"))) void SysTick_Handler(void) {
//     digital_out_toggle(&pinC);    
//     xPortSysTickHandler();
// }

// void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
//     printf_me("Stack Overflow detected in task %s\n", pcTaskName);
//     digital_out_toggle(&pinG);
// }
// void vApplicationIdleHook(void) {
//     // Code to execute when the system is idle, e.g., low-power mode
//     // Put the MCU into low-power mode (this example is for an ARM Cortex-M MCU)
//       digital_out_toggle(&pinB);
//     //Wait For Interrupt (puts the MCU into low-power sleep mode)
// }
#define NVIC_ISER0    (*(volatile uint32_t*)0xE000E100)
void TIM1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    
    uint32_t prescaler = 90000 - 1;  
    TIM1->PSC = prescaler;  
    TIM1->ARR = 999;  


    TIM1->DIER |= TIM_DIER_UIE;

    TIM1->CR1 |= TIM_CR1_CEN;

   
    NVIC_ISER0 |= (1 << 25);
}

__attribute__ ((interrupt("IRQ"))) void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;
        
    }
    digital_out_toggle(&pinD);
}
size_t val;
#define NVIC_SYSTICK  (*(volatile uint32_t*)0xE000E40C)
int main(){
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    // Configure SYSTICK to 1ms interrupt.
    // if (!sysTickConfig(GET_TICK_NUMBER_PER_CLOCK)) {
    //     sysTickInit(15); // Maximum priority - level 15.
    // } else {
    //     while(1);
    // }
    __asm volatile ("cpsie i");
    TIM1_Init();
    // NVIC_SYSTICK&=0x00ffffff;
    // NVIC_SYSTICK|=0x00000000;
    digital_out_init(&pinA, PD5);
    digital_out_init(&pinB, PD3); 
    digital_out_init(&pinC, PC8);
    digital_out_init(&pinD, PC9);
    digital_out_init(&pinF, PD0);
    digital_out_init(&pinG, PF0);
    digital_out_init(&pinE, PF1); 
    //digital_out_high(&pinA);
    //while(2);
    TaskHandle_t ledBlinking;
    //val=xPortGetFreeHeapSize();
    if(xTaskCreate(foo, "task", 128, NULL, 4, NULL)==pdPASS){

        if(xTaskCreate(foo2, "task", 128, NULL, 4, NULL)==pdPASS){  //&& xTaskCreate(foo2, "task", 128, NULL, 15, NULL)==pdPASS

            vTaskStartScheduler();
        }
    }
    
    // else{
    //     //digital_out_high(&pinF);
    // }
    // while(1);
    //  if(xTaskCreate(foo, "task", 128, NULL, 15, &ledBlinking)==pdPASS){

    //     vTaskStartScheduler();
    // }
    
    //vTaskStartScheduler();
    // for(int i=0; i<1000; i++){
    //    // digital_out_toggle(&pinA);
    //     Delay_ms(1000);
    // }
    while(1);
}