#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "semphr.h"
#include "systick.h"
#include <sys/time.h>
#include "drv_port.h"

#define NVIC_ISER0   *(volatile uint32_t*) NVIC

static SemaphoreHandle_t  sema; 
static SemaphoreHandle_t  sema2; 
static port_t portD;

static void f(void* param);
static void f2(void* param);

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
