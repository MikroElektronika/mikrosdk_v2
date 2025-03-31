
#include "board.h"

#include "drv_digital_out.h"
#include "FreeRTOS.h"
#include "task.h"
#include "systick.h"
#include <sys/time.h>

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
        digital_out_toggle(&pinC);
        vTaskDelay(100);
    }
}
static void foo2(void* param)
{
    while(1){
        digital_out_toggle(&pinD);
        vTaskDelay(200);
    }
}

static uint32_t msCount = 0;
uint32_t timeout = 0;

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
    digital_out_init(&pinC, PC8);
    digital_out_init(&pinD, PC9);
    TaskHandle_t ledBlinking;
    if(xTaskCreate(foo, "task", 128, NULL, 4, NULL)==pdPASS){

        if(xTaskCreate(foo2, "task", 128, NULL, 4, NULL)==pdPASS){ 

            vTaskStartScheduler();
        }
    }
    
   
    while(1);
}