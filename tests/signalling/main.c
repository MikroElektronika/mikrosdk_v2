
#include "board.h"

#include "drv_digital_out.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "semphr.h"
#include "systick.h"
#include <sys/time.h>
#include "drv_port.h"

static digital_out_t pinA;
static digital_out_t pinB;
static digital_out_t pinC;
static digital_out_t pinD;
static digital_out_t pinE;
static digital_out_t pinG;
static digital_out_t pinF;
static SemaphoreHandle_t  sema; 
static SemaphoreHandle_t  sema2; 
static port_t portD;
int number=0;
static void f(void* param)
{

    while(1){
        xSemaphoreTake(sema, portMAX_DELAY);
        port_write(&portD, 0xff);
        vTaskDelay(100);
        xSemaphoreGive(sema2);
    }
}
static void f2(void* param)
{
    uint8_t elem;
    while(1){
        xSemaphoreTake(sema2, portMAX_DELAY);
        port_write(&portD, 0);
        vTaskDelay(50);
        xSemaphoreGive(sema);
    }
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

#define NVIC_ISER0    (*(volatile uint32_t*)0xE000E100)

void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    
    uint32_t prescaler = 90000 - 1;  
    TIM2->PSC = prescaler;  
    TIM2->ARR = 999;  


    TIM2->DIER |= TIM_DIER_UIE;

    TIM2->CR1 |= TIM_CR1_CEN;

   
    NVIC_ISER0 |= (1 << 25);
}

__attribute__ ((interrupt("IRQ"))) void TIM2_UP_TIM20_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
        
    }
}
size_t val;
#define NVIC_SYSTICK  (*(volatile uint32_t*)0xE000E40C)
int main(){
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    __asm volatile ("cpsie i");
    TIM2_Init();
    port_init(&portD,PORT_D,0xff, PIN_DIRECTION_DIGITAL_OUTPUT);
    sema=xSemaphoreCreateBinary();
    sema2=xSemaphoreCreateBinary();
    xSemaphoreGive(sema);
    if(xTaskCreate(f, "task1", 128, NULL, 4, NULL)==pdPASS){
            if(xTaskCreate(f2, "task2", 128, NULL, 4, NULL)==pdFALSE){
                // Enter an infinite loop to halt the system
                while(1);
            } 
        vTaskStartScheduler();
    }
    while(1);
}