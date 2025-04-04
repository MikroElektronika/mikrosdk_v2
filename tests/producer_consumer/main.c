#include "board.h"
#include "drv_digital_out.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "queue.h"
#include "systick.h"
#include <sys/time.h>
#include "drv_port.h"

#define NVIC_ISER0    (*(volatile uint32_t*)0xE000E100)
#define NVIC_SYSTICK  (*(volatile uint32_t*)0xE000E40C)

static digital_out_t pinA;
static digital_out_t pinB;
static digital_out_t pinC;
static digital_out_t pinD;
static digital_out_t pinE;
static digital_out_t pinG;
static digital_out_t pinF;
static QueueHandle_t buffer;
static port_t portD;
static size_t val;
static int number=0;
static void producer(void* param);
static void consumer(void* param);

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
static void producer(void* param)
{

    while(1){
        number=(number+1)%256;
        xQueueSendToBack(buffer, &number, portMAX_DELAY);
        printf_me("Producer produced\n");
        vTaskDelay(100);
    }
}
static void consumer(void* param)
{
    uint8_t elem;
    while(1){
        xQueueReceive(buffer, &elem, portMAX_DELAY);
        printf_me("Consumer took\n");
        vTaskDelay(50);
    }
}

int main(){
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    __asm volatile ("cpsie i");
    TIM2_Init();
    port_init(&portD,PORT_D,0xff, PIN_DIRECTION_DIGITAL_OUTPUT);
    buffer=xQueueCreate(8,sizeof(uint8_t));
    if(xTaskCreate(producer, "producer", 128, NULL, 4, NULL)==pdPASS){
        for(int i=0; i<1; i++){
            char string[10]={'c','o','n','s','u','m','e','r','0','\0'};
            string[8]+=i;
            if(xTaskCreate(consumer, string, 128, NULL, 4, NULL)==pdFALSE){
                // Enter an infinite loop to halt the system
                while(1);
            }
        }
        vTaskStartScheduler();
    }
    while(1);
}
